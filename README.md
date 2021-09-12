# AnglerRT
AnglerRT is a simple Ray Tracing engine.
AnglerED is a optional GUI interface using [imgui](https://github.com/ocornut/imgui) to adjust different settings in AnglerRT.

## Getting Started
Visual Studio Code is recommended, Angler is officially untested on other development environments whilst I focus on a Windows build.
I use the MinGW GCC compiler for windows. This project is untested on other compilers.

By default AnglerRT is compiled as a .lib file and linked against AnglerED.

<ins>**Downloading the repository:**</ins>  
Start by cloning the repository with `git clone --recursive https://github.com/botmelive/Angler.git`.

If the repository was cloned non-recursively previously, use `git submodule update --init` to clone the necessary submodules.


Now you should be able to build the project in CMake.

***
## Dependencies
 [Imgui](https://github.com/ocornut/imgui) ( For AnglerRT GUI interface)   
 [GLFW](https://www.glfw.org/).  
 [Tinyobjloader](https://github.com/tinyobjloader/tinyobjloader) (To load .obj files from blender).  
 [spdlog](https://github.com/gabime/spdlog) (Logging).  
 
## License
AnglerRT and AnglerED is licensed under the MIT License, see the LICENSE file for more information.