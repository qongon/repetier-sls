
template <class IOPin>
class SensorDHT22 : public HumiditySensor {
public:
    SensorDHT22(PGM_P _name, void_fn_t cb)
        : HumiditySensor(_name)
        , curStage(DHTStage::INITIALIZATION)
        , stopped(false)
        , pulseIndex(0u)
        , pulses { 0u }
        , lastPulseUS(0ul)
        , receiveDelayUS(0ul)
        , lastSampleMS(0ul)
        , lastStageChangeMS(0ul)
        , sampleDelayMS(2000ul)
        , lastHumidity(0.0f)
        , lastTemperature(0.0f)
        , errorCount(0u)
        , pinCallback(cb) { }
    virtual inline bool start() final override { return stopped ? !(stopped = false) : false; }
    virtual bool stop() final override;
    virtual inline bool reset() final override { return (stop() && start()); }
    virtual inline float getTemperature() const final override { return lastTemperature; }
    virtual inline float getHumidity() const final override { return lastHumidity; }
    virtual inline PGM_P getName() const final override { return name; }
    virtual inline bool isBusy() const final override {
        return (curStage != DHTStage::INITIALIZATION);
    }
    virtual inline bool isStopped() const final override { return stopped; }
    virtual inline State getState() const final override {
        return (errorCount > 2u) ? State::STATE_ERROR : State::STATE_OK;
    }
    void pinInterrupt();
    void process();

private:
    enum class DHTStage {
        INITIALIZATION,
        SENDING_REQUEST,
        RECEIVING_DATA
    };

    DHTStage curStage;
    bool stopped;
    ufast8_t pulseIndex;
    ufast8_t pulses[41u];

    ticks_t lastPulseUS;
    ticks_t receiveDelayUS;
    millis_t lastSampleMS;
    millis_t lastStageChangeMS;
    millis_t sampleDelayMS;

    float lastHumidity;
    float lastTemperature;
    ufast8_t errorCount;
    void_fn_t pinCallback;
};

template <class IOPin>
class SensorFanTach : public TachometerSensor {
public:
    SensorFanTach(PWMHandler* fan, bool interrupts, const uint8_t div, PGM_P _name, void_fn_t cb)
        : TachometerSensor(_name)
        , targetFan(fan)
        , useInterrupts(interrupts)
        , divisor(div)
        , fanRPM(0u)
        , lastTickUS(0ul)
        , pinCallback(cb) { }
    virtual inline bool start() final override { return true; }
    virtual inline bool stop() final override { return true; }
    virtual inline bool reset() final override { return true; }
    virtual inline bool isBusy() const final override { return false; }
    virtual inline bool isStopped() const final override { return false; }
    virtual inline State getState() const final override { return State::STATE_OK; }
    virtual inline PGM_P getName() const final override { return name; }
    virtual inline uint32_t getRPM() const final override { return fanRPM; }
    void pinInterrupt() { }
    void process() { }

private:
    PWMHandler* targetFan;
    bool useInterrupts;
    const uint8_t divisor;
    uint32_t fanRPM;
    uint32_t lastTickUS;
    void_fn_t pinCallback;
};
