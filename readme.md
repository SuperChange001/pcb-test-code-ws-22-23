# How to setup the environment?
1. in the `CMakeLists.txt` you should change the `PICO_SDK_PATH` to the directory on your PC.
2. To get the Pico SDK
```
https://github.com/raspberrypi/pico-sdk
```

# How to build all the test program
1. Create a new folder named with build, and change directory to build folder. e.g,
```
mkdir build
cd build
```
2. Call cmake and specify the buildings system:
```
cmake -G "MinGW Makefiles" ..
```
3. Now you can either build all test program with:
```
make -j4
```
or build a single one with:
```
make -j4 test_sht31
```
4. To clean the build before you build again, you would use:
```
make clean
```
# How to flash the device

1. connect the device to your computersss
2. press and hold the BOOT button
3. press the RESET button
4. release the BOOT button
5. copy the _hardware_test.uf2_ file to the device
6. open a serial connection to the device (i.e. via `screen` or `Putty`)

