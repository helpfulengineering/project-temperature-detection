# Components

## Measuring sensors

### Single point thermopile sensors 
These sesnors are recomended if only one spot hast to be measured
* MLX90615
* MLX90614
* [ZPT-115M](https://www.mouser.com/datasheet/2/18/AAS-920-550A-Thermometrics-ZPT-115M-032114-web-1139409.pdf)

### Thermopile array 
These sensors scan several spots
* Grid eye
* [TPA81](https://www.robot-electronics.co.uk/htm/tpa81tech.htm)

A good overview: https://www.youtube.com/watch?v#xre5y_jYn8c

### Smartphone IR cameras
* iPhoneX infrared cameras
* Flir One

## Aiming (How to ensure the sensor measures the right spot)
* face tracing
* ultrasonic distance measureing
* a mirror with a contour. If your face fits in your foreheard is at the right position.
* scan a larger area and output the maximum

[Video of the mirror rig](https://helpfulengineering.slack.com/archives/CVCEV2V0V/p1584772258240900?thread_ts#1584656787.186800&cid#CVCEV2V0V)

## Trigger(how to start a measurement)
* Continuous time tagged trigger
* face detection
* temperature sensor reading
* can we use the same sensors that are in automatic doors? or in paper towel dispensers?

## Control & Software
* Raspberry Pi
* Arduino
* STM32 microcontroller
* https://github.com/nt-com/CTmeasure

## Display
* Minimalistic: 3 LEDs (green#low temperature, yellow# elevated temperature, red#fever)
* 10 or so LEDs with different temperatures
* digital display
* smart phone
* PC monitor

## Power supply
* switching
* batteries
* solar cells

## Housing
* 3D printed 
* wood
* laser cut

[Go back to main page](../README.md)