# Sierra Wireless EM7565
## Scope
This project aim to communicate with EM7565 (Module Sim 4G) through Serial using AT command.
- [EM7565](https://source.sierrawireless.com/devices/em-series/em7565/)
## Install driver for EM7565
- __Step 1__: Download driver with this [Link](https://source.sierrawireless.com/resources/airprime/software/mbpl/mbpl-software-latest/#sthash.A75t1bEi.dpbs) 
![source](docs/usb_source.png)\
- __Step 2__: Follow these step to build driver source
```
$ make
$ make install
```
- __Step 3__: Check driver. Connect EM7565 to your device
```
$ lsusb -t
```
See the result like the image below: _qcserial_, _cdc_mbim_
![driver](docs/check_driver.png)
## Build
_Build project with Makefile_
```
$ make
```
## Run
```
$ ./build/uart_test
```
Run AT command