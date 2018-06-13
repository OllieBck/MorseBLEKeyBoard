# Morse to Switch Access BLE Keyboard

A keyboard designed to move between the Morse code GBoard virtual keyboard on Android devices and switch access.

Spring 2018 Google released a Morse code option for the GBoard.  The keyboard allows for morse code input via an onscreen touch keyboard or with external switches.

The Morse to Switch Access BLE Keyboard is developed in a collaboration between the [Adaptive Design Association](http://www.adaptivedesign.org/) and [NottLimited](http://www.tandemmaster.org/home.html) for the Morse code [GBoard](https://experiments.withgoogle.com/collection/morse).

# Installation

Download the [Arduino IDE](https://www.arduino.cc/en/Main/Software).

Add the [Adafruit Feather NRF52 Board](https://learn.adafruit.com/bluefruit-nrf52-feather-learning-guide).

Clone or download the file.

Unzip the file and rename "HelloMorseKeyboard".

Move file into Arduino sketch folder.

Upload the firmware.

# Credits

The code for the project builds heavily from NottLimited's [Morse Code Gboard Switch](https://www.instructables.com/id/Gboard-Input-Switch-for-Morse-Code/) which interfaces the TandemMaster with the GBoard keyboard via an Arduino. For the code see: https://github.com/NottLimited/MorseCodeGboardSwitch.

The BLE example builds off the NRF52 API and examples developed by Adafruit for use with the Feather: https://learn.adafruit.com/bluefruit-nrf52-feather-learning-guide.

NottLimited's code base was wrapped in an Arduino Class to easily add more switches if desired.
