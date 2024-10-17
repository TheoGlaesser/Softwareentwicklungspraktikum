This is the backend part:
Here in the root you find a class Element.cpp, in which a finite element of the truss is described. Through this one the local stiffness matrix of a finite element (i.e. a rod) is computed.

This class is used in the class Assembler, which assembles and solves the linear system of equation, determined by the nodes, rods, forces and bearings.

Finally, Assembler is called in the simulator class, which then runs everyting.

You can also find a CMakeLists file, which generates Makefiles for the running of Simulator.cpp. The generated files and executables are stored in the build folder. 
 

There is also a folder "testBackend". Inside there is a test for the class Assembler.



