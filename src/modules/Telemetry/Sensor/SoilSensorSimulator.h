#pragma once
#include "configuration.h"
#if !MESHTASTIC_EXCLUDE_ENVIRONMENTAL_SENSOR && USE_SOIL_SIMULATOR
#include "../mesh/generated/meshtastic/telemetry.pb.h"
#include "TelemetrySensor.h"

class SoilSensorSimulator : public TelemetrySensor 
{
  private:
    // Current simulated values
    float temperature = 25.0f;    
    float moisture = 35.0f;       
    float conductivity = 800.0f;  
    float ph = 6.8f;             
    uint32_t nitrogen = 37;      
    uint32_t phosphorus = 49;     
    uint32_t potassium = 40;     

    // Value ranges from sensor datasheet
    static constexpr float TEMP_MIN = -40.0f;
    static constexpr float TEMP_MAX = 80.0f;
    static constexpr float MOISTURE_MIN = 0.0f;
    static constexpr float MOISTURE_MAX = 100.0f;
    static constexpr float CONDUCTIVITY_MIN = 0.0f;
    static constexpr float CONDUCTIVITY_MAX = 2000.0f;
    static constexpr float PH_MIN = 3.0f;
    static constexpr float PH_MAX = 9.0f;
    static constexpr uint32_t NPK_MIN = 0;
    static constexpr uint32_t NPK_MAX = 1999;

    // Maximum variations
    static constexpr float TEMP_DELTA = 0.2f;
    static constexpr float MOISTURE_DELTA = 0.5f;
    static constexpr float CONDUCT_DELTA = 25.0f;
    static constexpr float PH_DELTA = 0.1f;
    static constexpr uint32_t NPK_DELTA = 5;

  protected:
    virtual void setup() override;

  public:
    SoilSensorSimulator();
    virtual int32_t runOnce() override;
    virtual bool getMetrics(meshtastic_Telemetry *measurement) override;
};
#endif
