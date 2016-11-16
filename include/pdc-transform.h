#ifndef PDC_TRANSFORM_H
#define PDC_TRANSFORM_H

#include <pebble.h>

// Expected parameters:
// scale10: scaling factor * 10 (15 == 1.5)
// rotation: rotation in degrees around the center of the image
// offset: translation of left upper corner of the image

void pdc_transform_gdraw_command_image_draw_transformed(GContext * ctx, GDrawCommandImage * image, GPoint offset, int scale10, int rotation, GColor fill_color, GColor stroke_color, int custom_stroke_width);
#endif // PDC_TRANSFORM_H
