#include "configuration.h"
#if !MESHTASTIC_EXCLUDE_ENVIRONMENTAL_SENSOR
#include "../mesh/generated/meshtastic/telemetry.pb.h"
#include "SoilSensorSimulator.h"
#include "TelemetrySensor.h"

SoilSensorSimulator::SoilSensorSimulator() 
    : TelemetrySensor(meshtastic_TelemetrySensorType_SOIL_SENSOR, "SOIL_SIM") {}

int32_t SoilSensorSimulator::runOnce()
{
    LOG_INFO("Init sensor: %s", sensorName);
    status = true; // Simulator is always ready
    return DEFAULT_SENSOR_MINIMUM_WAIT_TIME_BETWEEN_READS;
}

void SoilSensorSimulator::setup()
{
    // Seed random number generator
    randomSeed(millis());
}

bool SoilSensorSimulator::getMetrics(meshtastic_Telemetry *measurement)
{
    // Add random variations
    float tempVar = ((random(1000) / 1000.0f) * 2.0f - 1.0f) * TEMP_DELTA;
    float moistVar = ((random(1000) / 1000.0f) * 2.0f - 1.0f) * MOISTURE_DELTA;
    float condVar = ((random(1000) / 1000.0f) * 2.0f - 1.0f) * CONDUCT_DELTA;
    float phVar = ((random(1000) / 1000.0f) * 2.0f - 1.0f) * PH_DELTA;
    int32_t npkVar = random(-NPK_DELTA, NPK_DELTA + 1);

    // Update values with constraints
    temperature = constrain(temperature + tempVar, TEMP_MIN, TEMP_MAX);
    moisture = constrain(moisture + moistVar, MOISTURE_MIN, MOISTURE_MAX);
    conductivity = constrain(conductivity + condVar, CONDUCTIVITY_MIN, CONDUCTIVITY_MAX);
    ph = constrain(ph + phVar, PH_MIN, PH_MAX);
    nitrogen = constrain(nitrogen + npkVar, NPK_MIN, NPK_MAX);
    phosphorus = constrain(phosphorus + npkVar, NPK_MIN, NPK_MAX);
    potassium = constrain(potassium + npkVar, NPK_MIN, NPK_MAX);

    // Update measurement with soil metrics
    measurement->which_variant = meshtastic_Telemetry_soil_metrics_tag;
    
    measurement->variant.soil_metrics.temperature = temperature;
    measurement->variant.soil_metrics.has_temperature = true;

    measurement->variant.soil_metrics.moisture = moisture;
    measurement->variant.soil_metrics.has_moisture = true;

    measurement->variant.soil_metrics.conductivity = conductivity;
    measurement->variant.soil_metrics.has_conductivity = true;

    measurement->variant.soil_metrics.ph = ph;
    measurement->variant.soil_metrics.has_ph = true;

    measurement->variant.soil_metrics.nitrogen = nitrogen;
    measurement->variant.soil_metrics.has_nitrogen = true;

    measurement->variant.soil_metrics.phosphorus = phosphorus;
    measurement->variant.soil_metrics.has_phosphorus = true;

    measurement->variant.soil_metrics.potassium = potassium;
    measurement->variant.soil_metrics.has_potassium = true;

    LOG_DEBUG("Soil Sim - T:%.1f°C M:%.1f%% C:%.0fμS/cm pH:%.1f N:%dmg/kg P:%dmg/kg K:%dmg/kg",
              temperature, moisture, conductivity, ph, nitrogen, phosphorus, potassium);

    return true;
}
#endif
