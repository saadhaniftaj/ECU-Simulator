#ifndef ENGINE_H
#define ENGINE_H
#include <vector>
#include <iostream>
#include "Sensor.h"
#include "Actuator.h"

class Engine {
public:
    Engine() : status("OK") {}
    
    void update(const std::vector<Sensor*>& sensors, const std::vector<Actuator*>& actuators) {
        // Simple engine status update based on sensor readings
        bool boostOk = sensors[3]->getValue() < 2.0;  // MAP/Boost sensor
        bool afrOk = sensors[1]->getValue() > 10.0 && sensors[1]->getValue() < 16.0;  // AFR sensor
        
        status = (boostOk && afrOk) ? "OK" : "WARNING";
    }
    
    void showStatus() const {
        std::cout << "Engine Status: " << status << std::endl;
    }

private:
    std::string status;
};

#endif // ENGINE_H 