# Steps to install Arduino ESP32 support on Windows
#### 1. Download and install the [Arduino.exe](http://www.roboparty.org/ArduinoESP32.exe)
#### 2. Open arduino.exe on C:/program files(x86)/Arduino/Arduino/arduino.exe (Or from the Desktop shortcut created)

#### 3. On arduino IDE go to Tools/Board and select BnrOneA_ESP32
![Board Select](https://github.com/botnroll/BnrOneA_ESP32/blob/master/Installation/Resources/images/board.png "Board Select")

#### 4. Now connect the BnrOneA to your computer and select the serial port
![Port](https://github.com/botnroll/BnrOneA_ESP32/blob/master/Installation/Resources/images/SerialPort.png "Port")

#### 5. Got to File/Examples/BnrOneA/ESP32/BnrOneA_RGB
![RGB](https://github.com/botnroll/BnrOneA_ESP32/blob/master/Installation/Resources/images/RGB.png "RGB")

#### 6. Finally upload BnrOneA_RGB example to the robot, in the end you should see the RGB led changing it’s color from red to green an blue
![Upload](https://github.com/botnroll/BnrOneA_ESP32/blob/master/Installation/Resources/images/Upload.png "Upload")

#### 7. (Optional) To program the robot without a cable (Over The Air) please go to: [BnrOneA_OTA](https://github.com/botnroll/BnrOneA_ESP32/tree/master/BnrOneA/examples/ESP32/BnrOneA_OTA)

## License 

Copyright (c) botnroll.com. All right reserved.

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
Lesser General Public License for more details.
