# AnglerRT

```
   _____                 .__              _____________________
  /  _  \   ____    ____ |  |   __________\______   \__    ___/
 /  /_\  \ /    \  / ___\|  | _/ __ \_  __ \       _/ |    |   
/    |    \   |  \/ /_/  >  |_\  ___/|  | \/    |   \ |    |   
\____|__  /___|  /\___  /|____/\___  >__|  |____|_  / |____|   
        \/     \//_____/           \/             \/           
```

AnglerRT is a simple Ray Tracing engine.  
AnglerED is a optional GUI interface using [imgui](https://github.com/ocornut/imgui) to adjust different settings in AnglerRT.

It is roughly based on the [Ray Tracing in One Weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html) book.


## Getting Started
Visual Studio Code is recommended, Angler is officially untested on other development environments whilst I focus on a Windows build.
I use the MinGW GCC compiler for windows. This project is untested on other compilers.

By default AnglerRT is compiled as a .lib file and linked against AnglerED.

**Downloading the repository:**  
Start by cloning the repository with  
`git clone --recursive https://github.com/botmelive/Angler.git`.

If the repository was cloned non-recursively previously, use `git submodule update --init` to clone the necessary submodules.


Now you should be able to build the project in CMake.

***

## USEAGE AND DOCUMENTATION
Checkout the `docs/USEAGE.md` on how to get started with Angler.  
The `docs/ORGANIZATION.md` file contains the file structure and layout 
of the project.
***
## Dependencies
 [Imgui](https://github.com/ocornut/imgui) ( For AnglerRT GUI)   
 [GLFW](https://www.glfw.org/).  
 [Tinyobjloader](https://github.com/tinyobjloader/tinyobjloader) (To load .obj files from blender).  
 [spdlog](https://github.com/gabime/spdlog) (Logging).

 ## Refrences

 * [PBRT](https://www.pbrt.org/)  
 * [Ray Tracing in One Weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html)  


 
## License
AnglerRT and AnglerED is licensed under the MIT License, see the LICENSE file for more information.
