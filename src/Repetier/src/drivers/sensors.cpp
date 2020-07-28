#include "../Repetier.h"

template <class IOPin>
void SensorDHT22<IOPin>::process() {
    if (reattachIntFunc == nullptr) {
        return;
    }
    millis_t curTime = HAL::timeInMilliseconds();
    if ((curTime - lastSampleMS) < sampleDelayMS) {
        return;
    }
    if (sensorState == INITIALIZATION) {
        sampleDelayMS = 2000;
        HAL::pinMode(IOPin::pin(), OUTPUT);
        HAL::digitalWrite(IOPin::pin(), LOW);
        sensorState = SENDING_REQUEST;
        lastStateChangeMS = curTime;
    } else if (sensorState == SENDING_REQUEST) {
        if ((curTime - lastStateChangeMS) < 1) {
            return;
        }
        HAL::pinMode(IOPin::pin(), INPUT_PULLUP);
        if ((curTime - lastStateChangeMS) > 30) {
            sampleDelayMS = 4000;
            lastSampleMS = curTime;
            sensorState = INITIALIZATION;
            return;
        }
        receiveDelayUS = micros();
        lastStateChangeMS = curTime;
        sensorState = RECEIVING_DATA;
        reattachIntFunc();
    } else if (sensorState == RECEIVING_DATA) {
        if ((curTime - lastStateChangeMS) > 10) {
            detachInterrupt(IOPin::pin());
            lastSampleMS = curTime;
            sensorState = lastPulseUS = pulseIndex = 0;
            if (errorCount++ == 3) {
                lastTemperature = lastHumidity = -99.9f;
            }
            return;
        }
        if (pulseIndex < 41 || pulses[0] < 40) {
            return;
        }

        fast8_t data[5] = { 0 };
        for (size_t i = 0; i < 40; ++i) {
            data[i / 8] <<= 1;
            if (pulses[i + 1] > 40) {
                data[i / 8] |= 1;
            }
        }
        if (((data[0] + data[1] + data[2] + data[3]) & 0xff) != data[4]) { // CRC
            return;
        }

        lastHumidity = ((data[0] * 0xff) + data[1]) * 0.1f;
        lastTemperature = (((data[2] & 0x7f) * 0xff) + data[3]) * 0.1f;

        if (data[2] & 0x80) {
            lastTemperature *= -1.0f;
        }

        detachInterrupt(IOPin::pin());
        lastSampleMS = curTime;
        lastPulseUS = pulseIndex = errorCount = 0;
        sensorState = INITIALIZATION;
    }
}

template <class IOPin>
void SensorDHT22<IOPin>::pinInterrupt() {
    if ((micros() - receiveDelayUS) < 40) {
        return;
    }

    if (pulseIndex < 41) {
        fast8_t pinState = IOPin::get();
        if (pinState) {
            lastPulseUS = micros();
        } else if (lastPulseUS) {
            pulses[pulseIndex++] = micros() - lastPulseUS;
        }
    }
}

#undef IO_TARGET
#define IO_TARGET IO_TARGET_TOOLS_TEMPLATES
#include "../io/redefine.h"
