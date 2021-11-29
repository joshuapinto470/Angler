# Code Organization

This file defines Angler's file structure.

### <ins>AnglerRT</ins>
The project source code is split between source and header files.
The source code is under the `src` folder and the header files 
are under the `includes` folder.

### <ins>docs</ins>
Contains the documentation files for Angler.


## Code Overview
* `/` - root is where the main project files exists.
* `AnglerED` - The AnglerED project files and any files specific to AnglerED can be found here.
    * `includes` - All of AnglerED's include files. This contains files
    from 3'rd party and AnglerED's own files.
    * `src` - The source files for AnglerED and any 3'rd party source files.   
    <ins>_I know this is a bad file structure. But I dont focus on ED too much._</ins>
    * `vendor` - 3'rd party source files.
* `AnglerRT` - This is probably what your here for. All the files specific to AnglerRT.
    * `includes` - Include files for AnglerRT.
        * `includes/accelerators` - Contains the BVH decleration
        * `includes/core` - Contains the core header files of AnglerRT. The definitions for the Render class, Scene class, 
        Geometry, Ray, Materials etc. is all defined here.
        * `includes/image_formats` - Contains the image file formats that angler uses to save the images.
        * `includes/materials` - All the specific materials supported by AnglerRT are defined here. This should inherit from the `src/core/Material.h` class.
        * `includes/shapes` - The shapes defined for the renderer. (Spheres, Triangles etc..). This should inherit from the `src/core/Shape.h` class.
    * `src` - The source files for AnglerRT.
        * `core` - Anglers core source files.
        * `image_formats` - PNG, PPM file formats.
        * `materials` - Defines the BRDF materials.

