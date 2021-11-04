# Code Organization

This file defines Angler's file structure.

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
        * `includes/core` - Contains the core header files of AnglerRT.
        * `includes/image_formats` - Contains the image file formats that angler uses to save the images.
        * `includes/materials` - All the materials supported by AnglerRT.
        * `includes/shapes`
    * `src`
