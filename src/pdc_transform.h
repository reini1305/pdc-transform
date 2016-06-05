#ifndef PDC_TRANSFORM_H
#define PDC_TRANSFORM_H

#include <pebble.h>

// Expected parameters:
// scale10: scaling factor * 10 (15 == 1.5)
// rotation: rotation in degrees around the center of the image
// offset: translation of left upper corner of the image

void gdraw_command_image_draw_similarity(GContext * ctx, GDrawCommandImage * image, GPoint offset, int scale10, int rotation);
#endif // PDC_TRANSFORM_H
