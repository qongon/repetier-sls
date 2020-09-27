
template <typename IOPin>
class SensorDHT22 : public Sensors {
private:
    enum {
        INITIALIZATION = 0,
        SENDING_REQUEST = 1,
        RECEIVING_DATA = 2
    };

    ufast8_t sensorState;
    ufast8_t pulseIndex;
    ufast8_t pulses[41];

    ticks_t lastPulseUS;
    ticks_t receiveDelayUS;
    millis_t lastSampleMS;
    millis_t lastStateChangeMS;
    millis_t sampleDelayMS;

    float lastHumidity;
    float lastTemperature;
    fast8_t errorCount;

public:
    // We need to reattach our interrupt after a pin state change.
    void (*reattachIntFunc)(void);
    SensorDHT22()
        : sensorState(0)
        , pulseIndex(0)
        , lastPulseUS(0)
        , receiveDelayUS(0)
        , lastSampleMS(0)
        , lastStateChangeMS(0)
        , sampleDelayMS(2000)
        , lastHumidity(0.0f)
        , lastTemperature(0.0f)
        , errorCount(0) {
    }
    inline float getTemperature() final { return lastTemperature; }
    inline float getHumidity() final { return lastHumidity; }
    inline uint16_t getError() final { return (errorCount > 2); }
    void pinInterrupt();
    void process();
};
