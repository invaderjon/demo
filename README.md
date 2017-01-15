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
3. Create new directory named build
4. Open CMake GUI
5. Configure using Visual Studio 2015
6. Once configuration completes press "Generate"
7. After generation completes press "Open Project"
8. TODO: include instructions to change working directory
 
## Demo Previews ##
### Demo 1 - Simple Blinn-Phong Renderer ###
Renders models as solid gray objects that are lit using the 
Blinn-Phong shading method. There are no controls.
<img src="http://i.imgur.com/YFlAEFd.png" width="300" height="200" />
<img src="http://i.imgur.com/YilEqRU.png" width="300" height="200" />
