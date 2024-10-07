This is the backend part:
Here in the root you find a class Element.cpp, in which a finite element of the truss is described. Through this one the local stiffness matrix of a finite element (i.e. a rod) is computed.

This class is used in the class Assembler, which assembles and solves the linear system of equation, determined by the nodes, rods, forces and bearings.

Finally, Assembler is called in the simulator class, which then runs everyting. NOTE: The simulator class has not been completed yet, as we shall discuss how to complete it.

You can also find a CMakeLists file, which generates Makefiles for the running of Simulator.cpp. The generated files and executables are stored in the build folder. 

You find then a Naive version, which has a naive version of the classes Assembler and Element. 

There is also a folder "Test Backend". Inside there is a test for the class Assembler and Element. The test is run using cmake and googletest, therefore to run it you need to have googletest. To do that, you can just go in the folder "Test Backend", then write the following commands consecutively:

cmake -S . -B build

cmake --build build

cd build && ctest

This three commands should run the test correctly (and they will be passed as well). If you need extra information, check this website:http://google.github.io/googletest/quickstart-cmake.html




