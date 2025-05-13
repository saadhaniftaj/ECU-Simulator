#ifndef ECU_H
#define ECU_H
#include "Sensor.h"
#include "Actuator.h"
#include "Engine.h"
#include "Logger.h"
#include "Differential.h"
#include <vector>
#include <string>
#include <map>

class ECU {
public:
    ECU();
    void simulateStep();
    void showLastLog() const;
    void showSensors() const;
    void showActuators() const;
    void showEngineStatus() const;
    void showAllLogs() const;
    double getSensorValue(int sensorId) const;
    std::string getSensorsInfo() const;
    std::string getActuatorsInfo() const;
    std::string getEngineStatusInfo() const;
    std::string getLogsInfo() const;
private:
    std::vector<Sensor*> sensors;
    std::vector<Actuator*> actuators;
    Engine* engine;
    Logger* logger;
    Differential* diff;
    // Sensor values
    std::map<int, double> sensorValues;
    
    // Actuator states
    std::map<std::string, bool> actuatorStates;
    
    // Engine parameters
    double rpm;
    double throttle;
    double boost;
    double afr;
    double fuelPressure;
    
    // Logs
    std::vector<std::string> logs;
    
    void updateSensors();
    void updateActuators();
    void logEvent(const std::string& event);
};

#endif // ECU_H 