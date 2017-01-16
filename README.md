# Demo #

## Overview ##
A handful of rendering and game demos.

## Support ##
This project officially supports Windows 7 and Ubuntu 16.04+.

## Requirements ##

### Ubuntu ###
 * CMake 3.0+
 * GCC 5.4.0+ (older versions may work)
 * Git 2.5.0+
 * OpenGL
 * GLFW 3
 * GLM
 * Assimp 2.0+

### Windows 7 ###
 * CMake 3.0+
 * Visual Studio 2015
 * Git 2.5.0+
 * OpenGL
 * GLFW 3
 * GLEW
 * GLM
 * Assimp 2.0+
 
## Build Instructions ##
### Ubuntu ###
1. Clone project to desired location
2. Open terminal and navigate to project folder
3. mkdir build
4. cd build
5. cmake ..
6. make
7. cd bin
8. run the demo of choice (ie for "Demo 1" call: ./demo1)
 
### Windows ###
#### Prepatory Steps ####
1. Download GLEW, GLFW, GLM, and Assimp binaries for Visual Studio
2. Create the following folders:
  * C:\Program Files\lib
  * C:\Program Files\include
3. Copy the library (lib and dll) files to C:\Program Files\lib. (i.e. C:\Program Files\lib\assimp.lib) (see note)
4. Copy the include directory contents to C:\Program Files\include (ie. C:\Program Files\include\assimp).
5. Add C:\Program Files\lib to the path

Note: If on a 64 bit system use the 64 bit libraries

#### Building ####
1. Clone project to desired location
2. Open project folder in Explorer
3. Create a new directory named build
4. Open CMake GUI
5. Set the source directory to the project root
6. Set the build directory to the directory created in step 3
7. Configure using Visual Studio 2015
8. Once configuration completes press "Generate"
9. After generation completes press "Open Project"
10. Set the demo of choice as the startup project (ie demo1)
11. Build
12. It will fail to run however as it will complain that assimp is missing
13. Copy assimp.dll (from the prep steps) to bin/Debug (in build)
14. Copy the directory bin/res to bin/Debug (resulting in bin/Debug/res)
15. Open the properties of the project you want to run
16. Go to the debugging item in "Configuration Properties"
17. Change the working directory to:  $(SolutionDir)/bin/Debug
18. Run the application

Note: If creating a release build than replace all instances of Debug with Release.
 
## Demo Previews ##
### Demo 1 - Simple Blinn-Phong Renderer ###
Renders models as solid gray objects that are lit using the 
Blinn-Phong shading method. There are no controls.
<img src="http://i.imgur.com/YFlAEFd.png" width="300" height="200" />
<img src="http://i.imgur.com/YilEqRU.png" width="300" height="200" />
