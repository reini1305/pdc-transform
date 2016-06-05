/**
 * main.c - Sets up a Window and Layer that draws the GDrawCommandImage
 * in its LayerUpdateProc.
 */

#include <pebble.h>
#include "pdc_transform.h"
#define NUM_IMAGES 11
static Window *s_main_window;
static Layer *s_canvas_layer;

static GDrawCommandImage *s_command_image;
static int s_scale;
static int s_scale_increment;
static int s_angle;
static AppTimer *s_animation_timer;
static int32_t resource_ids[]={RESOURCE_ID_DRAW_COMMAND1,RESOURCE_ID_DRAW_COMMAND2,RESOURCE_ID_DRAW_COMMAND3,RESOURCE_ID_DRAW_COMMAND4,RESOURCE_ID_DRAW_COMMAND5,RESOURCE_ID_DRAW_COMMAND6,RESOURCE_ID_DRAW_COMMAND7,RESOURCE_ID_DRAW_COMMAND8,RESOURCE_ID_DRAW_COMMAND9,RESOURCE_ID_DRAW_COMMAND10,RESOURCE_ID_DRAW_COMMAND11};
static int image_id;

static void animation_callback(void* data) {
  s_scale+=s_scale_increment;
  if(s_scale>30 || s_scale<10)
    s_scale_increment*=-1;
  s_angle = (s_angle+5)%360;
  s_animation_timer = app_timer_register(20,animation_callback,NULL);
  layer_mark_dirty(s_canvas_layer);
}

static void update_proc(Layer *layer, GContext *ctx) {
  // Place image in the center of the Window
  GSize img_size = {.w=80,.h=80};
  GRect bounds = layer_get_bounds(layer);

  // Make sure it is in the middle of the frame
  img_size.h = img_size.h * s_scale / 10;
  img_size.w = img_size.w * s_scale / 10;
  const GEdgeInsets frame_insets = {
    .top = (bounds.size.h - img_size.h) / 2 ,
    .left = (bounds.size.w - img_size.w) / 2
  };

  // If the image was loaded successfully...
  if (s_command_image) {
    // Draw it
    gdraw_command_image_draw_similarity(ctx, s_command_image, grect_inset(bounds, frame_insets).origin,s_scale,s_angle);
  }
}

static void change_sequence(int delta) {
  
  // Load the next resource
  image_id += delta;
  if(image_id > NUM_IMAGES) {
    image_id = 0;
  }
  if(image_id < 0) {
    image_id = NUM_IMAGES;
  }
  gdraw_command_image_destroy(s_command_image);
  s_command_image = gdraw_command_image_create_with_resource(resource_ids[image_id]);
}

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  change_sequence(-1);
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
  change_sequence(1);
}

static void config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  // Load the image and check it was succcessful
  s_command_image = gdraw_command_image_create_with_resource(resource_ids[0]);
  if (!s_command_image) {
    APP_LOG(APP_LOG_LEVEL_ERROR, "Image is NULL!");
  }
  image_id = 0;
  s_scale=10;
  s_scale_increment=1;
  s_angle=0;
  // Create canvas Layer and set up the update procedure
  s_canvas_layer = layer_create(bounds);
  layer_set_update_proc(s_canvas_layer, update_proc);
  layer_add_child(window_layer, s_canvas_layer);
  s_animation_timer = app_timer_register(33,animation_callback,NULL);
}

static void window_unload(Window *window) {
  // Destroy canvas Layer
  layer_destroy(s_canvas_layer);

  // Destroy the image
  gdraw_command_image_destroy(s_command_image);
}

static void init() {
  // Set up main Window
  s_main_window = window_create();
  window_set_background_color(s_main_window, PBL_IF_COLOR_ELSE(GColorJazzberryJam, GColorWhite));
  window_set_click_config_provider(s_main_window, config_provider);
  window_set_window_handlers(s_main_window, (WindowHandlers) {
      .load = window_load,
      .unload = window_unload,
  });
  window_stack_push(s_main_window, true);
}

static void deinit() {
  // Destroy main Window
  window_destroy(s_main_window);
}

int main() {
  init();
  app_event_loop();
  deinit();
}
