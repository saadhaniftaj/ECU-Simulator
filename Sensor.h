#ifndef SENSOR_H
#define SENSOR_H
#include <string>

class Sensor {
public:
    Sensor(const std::string& name, const std::string& unit, double initialValue)
        : name(name), unit(unit), value(initialValue) {}
    
    virtual ~Sensor() = default;
    
    const std::string& getName() const { return name; }
    const std::string& getUnit() const { return unit; }
    double getValue() const { return value; }
    void setValue(double newValue) { value = newValue; }
    
    virtual double readValue() { return value; }

protected:
    std::string name;
    std::string unit;
    double value;
};

#endif // SENSOR_H 