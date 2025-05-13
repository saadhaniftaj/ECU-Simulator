#include "ECU.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <QString>

ECU::ECU() {
    // Initialize sensors
    sensors.push_back(new Sensor("Road Speed", "km/h", 0.0));
    sensors.push_back(new Sensor("AFR", "ratio", 14.7));
    sensors.push_back(new Sensor("Wideband O2", "lambda", 1.0));
    sensors.push_back(new Sensor("MAP/Boost", "bar", 1.0));
    sensors.push_back(new Sensor("Fuel Pressure", "bar", 3.0));

    // Initialize actuators
    actuators.push_back(new Actuator("NO2 Solenoid", false));
    actuators.push_back(new Actuator("Fuel Injectors", false));
    actuators.push_back(new Actuator("Boost Controller", false));

    // Initialize other components
    engine = new Engine();
    logger = new Logger();
    diff = new Differential();
}

void ECU::simulateStep() {
    // Simulate sensor readings with some variation
    for (auto sensor : sensors) {
        double currentValue = sensor->getValue();
        double variation = (rand() % 100 - 50) / 1000.0; // Small random variation
        sensor->setValue(currentValue + variation);
    }

    // Simulate actuator states based on sensor readings
    double boost = sensors[3]->getValue(); // MAP/Boost sensor
    double afr = sensors[1]->getValue();   // AFR sensor

    // Simple control logic
    actuators[0]->setState(boost > 1.5);  // NO2 solenoid
    actuators[1]->setState(afr < 14.0);   // Fuel injectors
    actuators[2]->setState(boost < 1.8);  // Boost controller

    // Update engine status
    engine->update(sensors, actuators);

    // Log the simulation step
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2);
    ss << "Simulation step completed:\n";
    ss << "Boost: " << boost << " bar\n";
    ss << "AFR: " << afr << "\n";
    logger->log(ss.str());
}

void ECU::showLastLog() const {
    logger->showLastLog();
}

void ECU::showSensors() const {
    std::cout << "\n=== Sensor Readings ===\n";
    for (const auto& sensor : sensors) {
        std::cout << sensor->getName() << ": " 
                  << sensor->getValue() << " " 
                  << sensor->getUnit() << "\n";
    }
}

void ECU::showActuators() const {
    std::cout << "\n=== Actuator States ===\n";
    for (const auto& actuator : actuators) {
        std::cout << actuator->getName() << ": " 
                  << (actuator->getState() ? "ON" : "OFF") << "\n";
    }
}

void ECU::showEngineStatus() const {
    engine->showStatus();
}

void ECU::showAllLogs() const {
    logger->showAllLogs();
}

std::string ECU::getSensorsInfo() const {
    std::string info = "\n=== Sensor Readings ===\n";
    for (const auto& sensor : sensors) {
        info += sensor->getName() + ": " +
                std::to_string(sensor->getValue()) + " " +
                sensor->getUnit() + "\n";
    }
    return info;
}

std::string ECU::getActuatorsInfo() const {
    std::string info = "\n=== Actuator States ===\n";
    for (const auto& actuator : actuators) {
        info += actuator->getName() + ": " +
                (actuator->getState() ? "ON" : "OFF") + "\n";
    }
    return info;
}

std::string ECU::getEngineStatusInfo() const {
    std::string info = "\n=== Engine Status ===\n";
    info += "Status: ";
    // Use the same logic as showStatus
    bool boostOk = sensors[3]->getValue() < 2.0;
    bool afrOk = sensors[1]->getValue() > 10.0 && sensors[1]->getValue() < 16.0;
    info += (boostOk && afrOk) ? "OK" : "WARNING";
    info += "\n";
    return info;
}

std::string ECU::getLogsInfo() const {
    std::string info = "\n=== Logs ===\n";
    info += logger->getAllLogsQString().toStdString();
    return info;
}

double ECU::getSensorValue(int sensorId) const {
    if (sensorId >= 0 && sensorId < sensors.size()) {
        return sensors[sensorId]->getValue();
    }
    return 0.0;
} 