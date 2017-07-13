/* fr.h -- defines types (so that CUDA and C can know struct fr_t), and
        -- enum values for fractals

  This file is part of the small-summit-fractal project.

  small-summit-fractal source code, as well as any other resources in this
project are free software; you are free to redistribute it and/or modify them
under the terms of the GNU General Public License; either version 3 of the
license, or any later version.

  These programs are hopefully useful and reliable, but it is understood
that these are provided WITHOUT ANY WARRANTY, or MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE. See the GPLv3 or email at
<cade@cade.site> for more info on this.

  Here is a copy of the GPL v3, which this software is licensed under. You
can also find a copy at http://www.gnu.org/licenses/.

*/

#ifndef __FR_H__
#define __FR_H__


// fractal_type enums

// this is the default set, z**2 + c
#define FR_MANDELBROT        (0x0101)

// a slightly modified version, a `multibrot` with exp 3, so the equation is:
// z**3 + c
#define FR_MANDELBROT_3      (0x0102)

/* extra functions, not fully fleshed out */

// testing sin function, sin(z) + c. This needs work testing for escape bounds!
#define FR_SIN               (0x0103)


// how many fractal types
#define FR_FRACTAL_NUM            3


// the main fractal type. This type handles parameters (center, zoom, iter count
// what kind of equation) as well as memory descriptions, as width, height,
// memory width (pitch from SDL), and how many cores are rendering this fractal.

// additionally, this is translated as the MPI datatype mpi_fr_t so that fr_t
// variables may be transmitted to each render node in case of a change in
// fractal or memory parameters (for example, if the mouse pans and zooms, all
// render nodes must receive the new parameters).

typedef struct fr_t {
    // center x (real), center y (imag), and zoom
    // the coordinates of an image range from cX - 1/Z to cX + 1/Z, and from
    // cY + h/(Z*w) to cY - h/(Z*w), linearly scaled so that 1 x pixel = 1 y
    // pixel. this is important to create accurate fractals, instead of
    // stretched and distorted. Most of my implementations handle this by
    // creating a dppx variable (which should have a value of 2.0 / (Z * w))
    double cX, cY, Z;

    // how many iterations (at maximum) should be carried out to determine the
    // colorization of a pixel. In practice, most pixels reach only a fraction
    // of max_iter; they will 'escape' and be ruled out far before this many
    // are neccessary
    int max_iter;

    // TODO: add colorization parameters to scale and shift fractional
    // iterations
    // double coffset, cscale;

    // memory parameters, w is the actual image width, in pixels, h is the
    // actual image height, and mem_w is the memory width of a row (is >=
    // 4 * w), and is used because of restrictions of SDL
    int w, h, mem_w;

    // a fractal enum, see FR_* macros in this file (fr.h), this is typically
    // handled in a case switch block
    int fractal_type;

    // how many workers are working on the current image, and take note that
    // while initially equal to the macro `compute_size`, the render node can
    // change this to demonstrate the speedup achieved by adding or removing
    // nodes
    int num_workers;

} fr_t;



// holds colors, essentially an array. Most functions require this to be
// allocatedm which col should be 4 * num bytes. The ordering is RGBA, and A
// should be 255 most of the time
typedef struct fr_col_t {

    // how many colors
    int num;


    // RGBA packed byte array
    unsigned char * col;
} fr_col_t;


#endif
