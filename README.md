# pdc-transform
Adds rotation and scale to PDC drawing commands on Pebble, by defining a function `pdc_transform_gdraw_command_image_draw_transformed`. In addition to the standard `gdraw_command_image_draw` this allows to specify a rotation and scale.

## Interface
`void pdc_transform_gdraw_command_image_draw_transformed(GContext * ctx, GDrawCommandImage * image, GPoint offset, int scale10, int rotation);`

`scale10`: scaling factor times 10. For example a scale of 1.5 equals `scale10=15`

`rotation`: rotation angle in deg.

## Usage
* Run `pebble package install pdc-transform`.
* Include the library in any C files that will use it:

```
#include <pdc-transform/pdc-transform.h>
```

* The function will make a copy of the `GDrawCommandImage` internally such as to leave your original unharmed. This repository contains a sample app that cycles through 64 standard PDCs provided by Pebble and shows what can be created using this little library.

![screenshot](screenshots/animation.gif)

## Credits
The sample application is built upon [pdc-image](https://github.com/pebble-examples/pdc-image) by @C-D-Lewis
