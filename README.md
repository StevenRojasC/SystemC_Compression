# SystemC_SampleProject

Simple Hello Wold example using [SystemC](https://github.com/accellera-official/systemc) and [CMake](https://cmake.org/).

It's recommended to clone this repo using the command `git clone --recurse-submodules https://github.com/StevenRojasC/SystemC_SampleProject.git`

To build run the shell script:
```
./build.sh
```

This will take a while since all the source files are being build.

If this doesn't work, make sure the shell script has execution permissions using `chmod +x build.sh`.

To run the Hello World example once built use:
```
./build/test/test
```

If you want to understand how this project works look at the [CMake File](CMakeLists.txt).