#Test

##Location
The tests scripts are located in the backend part and refers just to it (therefore no frontend).

##Compiling instruction
To run the tests googletest and cmake are required. For cmake: https://cmake.org/ and for googletest: https://github.com/google/googletest

In this folder run in the following order these commands:

cmake -S . -B build

cmake --build build

cd build && ctest

##Remark
There is already a test, which was written by the developers. The results of the test refer to the follwoing website:https://valdivia.staff.jade-hs.de/fachwerk_en.html
