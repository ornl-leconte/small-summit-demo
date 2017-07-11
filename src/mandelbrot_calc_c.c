//

#include "mandelbrot.h"
#include "mandelbrot_calc_c.h"
#include "math.h"

// calculates iterations
void mand_c(int w, int h, double cX, double cY, double Z, int max_iter, unsigned char * output) {
    int px, py, ci, ri;
    double c_r, _c_i, c_i, z_r, z_i, z_r2, z_i2, fri, dppx, tmp;
    _c_i = cY + h / (w * Z);
    c_r = cX - 1.0 / Z;
    dppx = 2.0 / (w * Z);
    for (px = 0; px < w; ++px) {
        c_i = _c_i;
        for (py = 0; py < h; ++py) {
            ri = 4 * (px + py * w);
            z_r = c_r;
            z_i = c_i;
            z_r2 = z_r * z_r;
            z_i2 = z_i * z_i;
            for (ci = 0; ci < max_iter && z_r2 + z_i2 < 16.0; ++ci) {
                z_i = 2 * z_r * z_i + c_i;
                z_r = z_r2 - z_i2 + c_r;
                z_r2 = z_r * z_r;
                z_i2 = z_i * z_i;
            }
            if (ci == max_iter) {
                fri = 0.0;
            } else {
                fri = 2.0 + ci - log(log(z_r2 + z_i2)) / log(2.0);
            }
            output[ri + 0] = (int)floor(255 * (sin(fri) + 1) / 2);
            output[ri + 1] = (int)floor(255 * (sin(fri) + 1) / 2);
            output[ri + 2] = 0;
            output[ri + 3] = 255;
            c_i -= dppx;
        }
    c_r += dppx;
    }
}
