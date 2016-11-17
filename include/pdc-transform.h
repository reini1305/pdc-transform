#ifndef PDC_TRANSFORM_H
#define PDC_TRANSFORM_H

#include <pebble.h>

// Expected parameters:
// scale10: scaling factor * 10 (15 == 1.5)
// rotation: rotation in degrees around the center of the image
// offset: translation of left upper corner of the image

void pdc_transform_gdraw_command_image_draw_transformed(GContext * ctx, GDrawCommandImage * image, GPoint offset, int scale10, int rotation, GColor fill_color, GColor stroke_color, int stroke_width);

// Note that the follow functions DO change the image
void pdc_transform_scale_image(GDrawCommandImage * image, int scale10);
void pdc_transform_rotate_image(GDrawCommandImage * image, int rotation);
void pdc_transform_recolor_image(GDrawCommandImage * image, GColor fill_color, GColor stroke_color);
#endif // PDC_TRANSFORM_H
