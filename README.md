# ECU Simulator

A modern, real-time Engine Control Unit (ECU) simulator with a beautiful web-like interface, built using Qt6 and C++.



## Features

- 🎨 Modern, website-like user interface
- 📊 Real-time sensor monitoring
- 🔄 Dynamic actuator control
- 🚗 Engine status visualization
- 📝 System logging
- 🎯 Interactive simulation controls

## Components

### Dashboard
- Real-time boost pressure monitoring
- Air/Fuel ratio tracking
- Fuel pressure visualization
- System status indicators

### Sensors Panel
- Road Speed
- AFR (Air/Fuel Ratio)
- Wideband O2
- MAP/Boost
- Fuel Pressure

### Actuators Panel
- NO2 Solenoid control
- Fuel Injectors status
- Boost Controller monitoring

### Engine Status
- Real-time engine parameters
- System health monitoring
- Performance metrics

### System Logs
- Detailed operation logs
- Event tracking
- System messages

## Requirements

- C++17 or higher
- Qt6
- CMake 3.16 or higher
- Modern C++ compiler

## Building the Project

```bash
# Clone the repository
git clone https://github.com/saadhaniftaj/ECU-Simulator.git
cd ECU-Simulator

# Create build directory
mkdir build && cd build

# Configure with CMake
cmake ..

# Build the project
make

# Run the application
./ECU_Simulator
```

## Project Structure

```
ECU-Simulator/
├── CMakeLists.txt
├── main.cpp
├── MainWindow.h
├── MainWindow.cpp
├── ECU.h
├── ECU.cpp
└── README.md
```

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Author

Saad Hanif Taj

## Acknowledgments

- Built with Qt6 for modern UI
- Uses CMake for cross-platform build support
- Implements modern C++ practices 
