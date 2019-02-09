# Simplelcd Class 16x2 LCD library 
This is a simlpe C++ library that you can use to drive a 16x2 LCD display with an Orange Pi utilizing it's GPIO ports.

This library has been tested on:
- Orange Pi One Plus
- running Armbian Stretch https://www.armbian.com/orange-pi-one-plus/
- halherta's GPIOClass C++ class https://github.com/halherta/RaspberryPi-GPIOClass-v2

### To compile the example, enter this command:
```sh
$ g++ -fpermissive -Wall ./src/GPIOClass.cpp ./src/simplelcd.cpp lcd_test.cpp -o lcd_test 
```
# Orange Pi One Plus pinout / Pin definition:
![Pinout](https://github.com/RamasyaR/simplelcd/blob/master/pinoutOrangePiOnePlus.jpg)
