# pdc-transform
Adds rotation and scale to PDC drawing commands on Pebble, by defining a function `pdc_transform_gdraw_command_image_draw_transformed`. In addition to the standard `gdraw_command_image_draw` this allows to specify a rotation and scale.

## Interface
`void pdc_transform_gdraw_command_image_draw_transformed(GContext * ctx, GDrawCommandImage * image, GPoint offset, int scale10, int rotation, GColor fill_color, GColor stroke_color, int stroke_width);`

`scale10`: scaling factor times 10. For example a scale of 1.5 equals `scale10=15`

`rotation`: rotation angle in degrees

`fill_color`: custom fill color applied to the PDC

`stroke_color`: custom stroke color applied to the PDC

`stroke_width`: override the default stroke width in the PDC (=0 to use the standard one)

`void pdc_transform_scale_image(GDrawCommandImage * image, int scale10);`

`void pdc_transform_rotate_image(GDrawCommandImage * image, int rotation);`

`void pdc_transform_recolor_image(GDrawCommandImage * image, GColor fill_color, GColor stroke_color);`

## Usage
* Run `pebble package install pdc-transform`.
* Include the library in any C files that will use it:

```
#include <pdc-transform/pdc-transform.h>
```

* `pdc_transform_gdraw_command_image_draw_transformed` will make a copy of the `GDrawCommandImage` internally such as to leave your original unharmed.

* The other functions _will_ modify the passed in `GDrawCommandImage`.

* This repository contains a sample app that cycles through 64 standard PDCs provided by Pebble and shows what can be created using this little library.

![screenshot](screenshots/animation.gif)

## Credits
The sample application is built upon [pdc-image](https://github.com/pebble-examples/pdc-image) by @C-D-Lewis
