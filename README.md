arduino-joystick
================

This is code for a Arduino-based joystick project.

This code is copyright Mattias Erlo, open source MIT License, see http://opensource.org/licenses/MIT

The code assumes a joystick is connected to the gpio pins on Arduino. (See source code for the pin configuration.)

When the joystick is used, usb hid keyboard commands are sent on the usb port. (See source code for key mappings.)

To flash the program, first flash the Arduino-usbserial-uno.hex firmware:  
1. Put Arduino in dfu mode by bridging the reset pin and ground. See for example http://arduino.cc/en/Hacking/DFUProgramming8U2  
2. Do "sudo dfu-programmer atmega16u2 erase"  
3. Do "sudo dfu-programmer atmega16u2 flash --debug 1 Arduino-usbserial-uno.hex" (Latest firmware can be downloaded from https://github.com/arduino/Arduino/tree/master/hardware/arduino/firmwares)  
4. Do "sudo dfu-programmer atmega16u2 reset"  
5. Disconnect and reconnect the usb cable.  
6. Now you can flash the program from the Arduino IDE. Make sure Tools -> Board and Serial Port matches your setup.  

After having flashed the program, you need to flash another firmware, Arduino-keyboard-0.3.hex, that turns Arduino into a usb hid device. Download from https://github.com/coopermaa/USBKeyboard/blob/master/firmware/Arduino-keyboard-0.3.hex  
7. Put Arduino in dfu mode again as in 1 above.  
8. Do "sudo dfu-programmer atmega16u2 erase"  
9. Do "sudo dfu-programmer atmega16u2 flash Arduino-keyboard-0.3.hex"  
10. Do "sudo dfu-programmer atmega16u2 reset"  
11. Disconnect and reconnect the usb cable.  
12. Now you should be able to use the joystick.  

Note that as long as the usb hid firmware is used, Arduino will not show up in the Arduino IDE and cannot be reprogrammed.
To reprogram you must first put it in dfu mode and reflash the usb serial firmware, as from step 1 above.

