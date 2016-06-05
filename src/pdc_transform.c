#include <pebble.h>
#include "pdc_transform.h"

typedef struct similarity_transform_data {
  GPoint offset;
  int scale10;
  int32_t c;
  int32_t s;
  GPoint rotation_offset;
}similarity_transform_data;

bool prv_similarity_iterator(GDrawCommand *command,uint32_t index, void* context) {
  // get transformation data
  similarity_transform_data *data = (similarity_transform_data*) context;

  // scale stroke width
  gdraw_command_set_stroke_width(command,gdraw_command_get_stroke_width(command)*data->scale10/10);

  // GDrawCommandTypePrecisePath has to be treated differently
  GDrawCommandType type = gdraw_command_get_type(command);
  int scale_factor = (type==GDrawCommandTypePrecisePath)? 8:1;

  GPoint temp_point;
  uint16_t num_points = gdraw_command_get_num_points(command);
  for(uint16_t i=0;i<num_points;i++) {
    temp_point = gdraw_command_get_point(command,i);
    // rotation around point
    const int x = temp_point.x-data->rotation_offset.x*scale_factor;
    const int y = temp_point.y-data->rotation_offset.y*scale_factor;
    temp_point.x = x*data->c/ TRIG_MAX_RATIO - y*data->s/ TRIG_MAX_RATIO + data->rotation_offset.x*scale_factor;
    temp_point.y = x*data->s/ TRIG_MAX_RATIO + y*data->c/ TRIG_MAX_RATIO + data->rotation_offset.y*scale_factor;
    // scaling and transformation
    temp_point.x = (temp_point.x * data->scale10) / 10 + data->offset.x*scale_factor;
    temp_point.y = (temp_point.y * data->scale10) / 10 + data->offset.y*scale_factor;
    gdraw_command_set_point(command,i,temp_point);
  }
  return true;
}

void prv_gdraw_command_list_draw_transformed(GContext * ctx, GDrawCommandList * list,
                                               GPoint offset, int scale10, GPoint rotation_offset, int rotation) {
  const int32_t angle = DEG_TO_TRIGANGLE(rotation);
  similarity_transform_data data = {
    .scale10 = scale10,
    .offset = offset,
    .c = cos_lookup(angle),
    .s = sin_lookup(angle),
    .rotation_offset = rotation_offset
  };
  gdraw_command_list_iterate(list,prv_similarity_iterator,(void*)&data);
  gdraw_command_list_draw(ctx,list);
}

void gdraw_command_image_draw_transformed(GContext * ctx, GDrawCommandImage * image,
                                     GPoint offset, int scale10, int rotation) {
  GDrawCommandImage *temp_image = gdraw_command_image_clone(image);
  GDrawCommandList *list = gdraw_command_image_get_command_list(temp_image);
  GSize img_size = gdraw_command_image_get_bounds_size(temp_image);
  GPoint rotation_offset = { .x= img_size.w/2,.y=img_size.h/2};
//  GPoint rotation_offset = { .x= 0,.y=0};
  prv_gdraw_command_list_draw_transformed(ctx,list,offset,scale10,rotation_offset,rotation);
  gdraw_command_image_destroy(temp_image);
}
