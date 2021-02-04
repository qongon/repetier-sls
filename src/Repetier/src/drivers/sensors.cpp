#include "../Repetier.h"

template <class IOPin>
void SensorDHT22<IOPin>::process() {
    if (!pinCallback || isStopped()) {
        return;
    }
    millis_t curTime = HAL::timeInMilliseconds();
    if ((curTime - lastSampleMS) < sampleDelayMS) {
        return;
    }
    if (curStage == DHTStage::INITIALIZATION) {
        sampleDelayMS = 2000ul;
        HAL::pinMode(IOPin::pin(), OUTPUT);
        HAL::digitalWrite(IOPin::pin(), LOW);
        curStage = DHTStage::SENDING_REQUEST;
        lastStageChangeMS = curTime;
    } else if (curStage == DHTStage::SENDING_REQUEST) {
        if ((curTime - lastStageChangeMS) < 1ul) {
            return;
        }
        HAL::pinMode(IOPin::pin(), INPUT_PULLUP);
        if ((curTime - lastStageChangeMS) > 30ul) {
            sampleDelayMS = 4000ul;
            lastSampleMS = curTime;
            curStage = DHTStage::INITIALIZATION;
            return;
        }
        receiveDelayUS = micros();
        lastStageChangeMS = curTime;
        curStage = DHTStage::RECEIVING_DATA;
         
        attachInterrupt( IOPin::pin(), pinCallback, CHANGE);
    } else if (curStage == DHTStage::RECEIVING_DATA) {
        if ((curTime - lastStageChangeMS) > 10ul) { // Failure, longer than 10ms
            detachInterrupt(IOPin::pin());
            lastSampleMS = curTime;
            lastPulseUS = pulseIndex = 0u;
            curStage = DHTStage::INITIALIZATION;
            if (errorCount++ == 3u) {
                lastTemperature = lastHumidity = -99.9f;
            }
            return;
        }
        if (pulseIndex < 41u || pulses[0u] < 40u) {
            return;
        }

        ufast8_t data[5u] = { 0u };
        for (size_t i = 0u; i < 40u; ++i) {
            data[i / 8u] <<= 1u;
            if (pulses[i + 1u] > 40u) {
                data[i / 8u] |= 1u;
            }
        }
        if (((data[0u] + data[1u] + data[2u] + data[3u]) & 255u) != data[4u]) { // CRC
            return;
        }

        lastHumidity = ((data[0u] * 255u) + data[1u]) * 0.1f;
        lastTemperature = (((data[2u] & 127u) * 255u) + data[3u]) * 0.1f;

        if (data[2u] & 128u) {
            lastTemperature *= -1.0f;
        }

        detachInterrupt(IOPin::pin());
        lastSampleMS = curTime;
        lastPulseUS = pulseIndex = errorCount = 0u;
        curStage = DHTStage::INITIALIZATION;
    }
}

template <class IOPin>
void SensorDHT22<IOPin>::pinInterrupt() {
    if ((micros() - receiveDelayUS) < 40ul) {
        return;
    }

    if (pulseIndex < 41u) {
        if (IOPin::get()) {
            lastPulseUS = micros();
        } else if (lastPulseUS) {
            pulses[pulseIndex++] = micros() - lastPulseUS;
        }
    }
}
template <class IOPin>
bool SensorDHT22<IOPin>::stop() {
    if (isStopped()) {
        return false;
    }
    stopped = true;
    detachInterrupt(IOPin::pin());
    lastPulseUS = pulseIndex = errorCount = 0u;
    lastTemperature = lastHumidity = 0.0f;
    curStage = DHTStage::INITIALIZATION;
    HAL::pinMode(IOPin::pin(), INPUT_PULLUP);
    return true;
}

#undef IO_TARGET
#define IO_TARGET IO_TARGET_TOOLS_TEMPLATES
#include "../io/redefine.h"
