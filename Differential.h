#ifndef DIFFERENTIAL_H
#define DIFFERENTIAL_H
#include <string>

class Differential {
public:
    Differential() : ratio(3.73), status("OK") {}
    
    void update(double speed) {
        // Simple differential logic based on speed
        status = (speed < 200.0) ? "OK" : "WARNING";
    }
    
    void showStatus() const {
        std::cout << "Differential Status: " << status << " (Ratio: " << ratio << ":1)" << std::endl;
    }

private:
    double ratio;
    std::string status;
};

#endif // DIFFERENTIAL_H 