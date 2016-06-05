# pdc-transform
Adds rotation and scale to PDC drawing commands on Pebble, by defining a function `gdraw_command_image_draw_transformed`. In addition to the standard `gdraw_command_image_draw` this allows to specify a rotation and scale.

## Interface
`void gdraw_command_image_draw_transformed(GContext * ctx, GDrawCommandImage * image, GPoint offset, int scale10, int rotation);`

`scale10`: scaling factor times 10. For example a scale of 1.5 equals `scale10=15`

`rotation`: rotation angle in deg.

## Usage
Simply include `pdc_transform.h` and call the above function. It will make a copy of the `GDrawCommandImage` internally such as to leave your original unharmed. This repository contains a sample app that can be compiled with `pebble build`. It allows to cycle through 64 standard PDCs provided by Pebble and shows what can be created using this little library.

![screenshot](screenshots/animation.gif)

## Credits
The sample application is built upon [pdc-image](https://github.com/pebble-examples/pdc-image) by @C-D-Lewis