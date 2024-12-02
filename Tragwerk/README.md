/*! \mainpage Description
##External tools
You need to have installed on your computer cmake and QT. In the following links you find the corresponding webpages of the external tools: cmake https://cmake.org/ and qt https://www.qt.io/

##Instruction to compile
First of all you have to compile the backend part into a static library. To accomplish that you can do "cmake -S . -B ../bin" in the folder Tragwerk/Backend/ and then after all the required makefiles have been built you have to do "make" in the same folder. 

Afterwards, you have to move to folder Tragwerk/ and do "cmake -S . -B build". An executable file "main" will be prepared. You just then need to open it using the console command "./main" and a window will open. 


##Information about units
When entering data, there are no units. The user is responsible for providing data regarding consistent units
e.g.
point coordinates in m, loads in N, cross sections in m² and the modulus of elasticity in N/m²,
displacements then will be in m, bar forces in N, normal stress in N/m².
*/







