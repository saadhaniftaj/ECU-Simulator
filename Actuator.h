#ifndef ACTUATOR_H
#define ACTUATOR_H
#include <string>

class Actuator {
public:
    Actuator(const std::string& name, bool initialState)
        : name(name), state(initialState) {}
    
    virtual ~Actuator() = default;
    
    const std::string& getName() const { return name; }
    bool getState() const { return state; }
    void setState(bool newState) { state = newState; }
    
    virtual void activate() { state = true; }
    virtual void deactivate() { state = false; }

protected:
    std::string name;
    bool state;
};

#endif // ACTUATOR_H 