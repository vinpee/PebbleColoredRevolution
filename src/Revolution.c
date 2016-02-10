// Copyright (c) 2013 Douwe Maan <http://www.douwemaan.com/>
// The above copyright notice shall be included in all copies or substantial portions of the program.

// Envisioned as a watchface by Jean-Noël Mattern
// Based on the display of the Freebox Revolution, which was designed by Philippe Starck.

// ImageMagick - pour convertir couleurs des images : 
// c:\images\batch>FOR %G IN (*.png) DO convert %G +level-colors green green\green_%G

#include <pebble.h>

// Settings
bool USE_AMERICAN_DATE_FORMAT = false;
bool VIBE_ON_HOUR = false;
#define TIME_SLOT_ANIMATION_DURATION  500

// Magic numbers
#define SCREEN_WIDTH        144
#define SCREEN_HEIGHT       168

#define TIME_IMAGE_WIDTH    70
#define TIME_IMAGE_HEIGHT   70

#define DATE_IMAGE_WIDTH    20
#define DATE_IMAGE_HEIGHT   20

#define SECOND_IMAGE_WIDTH  10
#define SECOND_IMAGE_HEIGHT 10

#define DAY_IMAGE_WIDTH     20
#define DAY_IMAGE_HEIGHT    10

#define MARGIN              1
#define TIME_SLOT_SPACE     2
#define DATE_PART_SPACE     4


// Images
#define NUMBER_OF_TIME_IMAGES 10
int TIME_IMAGE_RESOURCE_IDS[NUMBER_OF_TIME_IMAGES] = {
  RESOURCE_ID_IMAGE_TIME_0, 
  RESOURCE_ID_IMAGE_TIME_1, RESOURCE_ID_IMAGE_TIME_2, RESOURCE_ID_IMAGE_TIME_3, 
  RESOURCE_ID_IMAGE_TIME_4, RESOURCE_ID_IMAGE_TIME_5, RESOURCE_ID_IMAGE_TIME_6, 
  RESOURCE_ID_IMAGE_TIME_7, RESOURCE_ID_IMAGE_TIME_8, RESOURCE_ID_IMAGE_TIME_9
};
int WHITE_TIME_IMAGE_RESOURCE_IDS[NUMBER_OF_TIME_IMAGES] = {
  RESOURCE_ID_IMAGE_TIME_0, 
  RESOURCE_ID_IMAGE_TIME_1, RESOURCE_ID_IMAGE_TIME_2, RESOURCE_ID_IMAGE_TIME_3, 
  RESOURCE_ID_IMAGE_TIME_4, RESOURCE_ID_IMAGE_TIME_5, RESOURCE_ID_IMAGE_TIME_6, 
  RESOURCE_ID_IMAGE_TIME_7, RESOURCE_ID_IMAGE_TIME_8, RESOURCE_ID_IMAGE_TIME_9
};
int RED_TIME_IMAGE_RESOURCE_IDS[NUMBER_OF_TIME_IMAGES] = {
  RESOURCE_ID_RED_IMAGE_TIME_0, 
  RESOURCE_ID_RED_IMAGE_TIME_1, RESOURCE_ID_RED_IMAGE_TIME_2, RESOURCE_ID_RED_IMAGE_TIME_3, 
  RESOURCE_ID_RED_IMAGE_TIME_4, RESOURCE_ID_RED_IMAGE_TIME_5, RESOURCE_ID_RED_IMAGE_TIME_6, 
  RESOURCE_ID_RED_IMAGE_TIME_7, RESOURCE_ID_RED_IMAGE_TIME_8, RESOURCE_ID_RED_IMAGE_TIME_9
};
int BLUE_TIME_IMAGE_RESOURCE_IDS[NUMBER_OF_TIME_IMAGES] = {
  RESOURCE_ID_BLUE_IMAGE_TIME_0, 
  RESOURCE_ID_BLUE_IMAGE_TIME_1, RESOURCE_ID_BLUE_IMAGE_TIME_2, RESOURCE_ID_BLUE_IMAGE_TIME_3, 
  RESOURCE_ID_BLUE_IMAGE_TIME_4, RESOURCE_ID_BLUE_IMAGE_TIME_5, RESOURCE_ID_BLUE_IMAGE_TIME_6, 
  RESOURCE_ID_BLUE_IMAGE_TIME_7, RESOURCE_ID_BLUE_IMAGE_TIME_8, RESOURCE_ID_BLUE_IMAGE_TIME_9
};
int GREEN_TIME_IMAGE_RESOURCE_IDS[NUMBER_OF_TIME_IMAGES] = {
  RESOURCE_ID_GREEN_IMAGE_TIME_0, 
  RESOURCE_ID_GREEN_IMAGE_TIME_1, RESOURCE_ID_GREEN_IMAGE_TIME_2, RESOURCE_ID_GREEN_IMAGE_TIME_3, 
  RESOURCE_ID_GREEN_IMAGE_TIME_4, RESOURCE_ID_GREEN_IMAGE_TIME_5, RESOURCE_ID_GREEN_IMAGE_TIME_6, 
  RESOURCE_ID_GREEN_IMAGE_TIME_7, RESOURCE_ID_GREEN_IMAGE_TIME_8, RESOURCE_ID_GREEN_IMAGE_TIME_9
};
int BLACK_TIME_IMAGE_RESOURCE_IDS[NUMBER_OF_TIME_IMAGES] = {
  RESOURCE_ID_BLACK_IMAGE_TIME_0, 
  RESOURCE_ID_BLACK_IMAGE_TIME_1, RESOURCE_ID_BLACK_IMAGE_TIME_2, RESOURCE_ID_BLACK_IMAGE_TIME_3, 
  RESOURCE_ID_BLACK_IMAGE_TIME_4, RESOURCE_ID_BLACK_IMAGE_TIME_5, RESOURCE_ID_BLACK_IMAGE_TIME_6, 
  RESOURCE_ID_BLACK_IMAGE_TIME_7, RESOURCE_ID_BLACK_IMAGE_TIME_8, RESOURCE_ID_BLACK_IMAGE_TIME_9
};
int FB_TIME_IMAGE_RESOURCE_IDS[NUMBER_OF_TIME_IMAGES] = {
  RESOURCE_ID_FB_IMAGE_TIME_0, 
  RESOURCE_ID_FB_IMAGE_TIME_1, RESOURCE_ID_FB_IMAGE_TIME_2, RESOURCE_ID_FB_IMAGE_TIME_3, 
  RESOURCE_ID_FB_IMAGE_TIME_4, RESOURCE_ID_FB_IMAGE_TIME_5, RESOURCE_ID_FB_IMAGE_TIME_6, 
  RESOURCE_ID_FB_IMAGE_TIME_7, RESOURCE_ID_FB_IMAGE_TIME_8, RESOURCE_ID_FB_IMAGE_TIME_9
};

#define NUMBER_OF_DATE_IMAGES 10
int DATE_IMAGE_RESOURCE_IDS[NUMBER_OF_DATE_IMAGES] = {
  RESOURCE_ID_IMAGE_DATE_0, 
  RESOURCE_ID_IMAGE_DATE_1, RESOURCE_ID_IMAGE_DATE_2, RESOURCE_ID_IMAGE_DATE_3, 
  RESOURCE_ID_IMAGE_DATE_4, RESOURCE_ID_IMAGE_DATE_5, RESOURCE_ID_IMAGE_DATE_6, 
  RESOURCE_ID_IMAGE_DATE_7, RESOURCE_ID_IMAGE_DATE_8, RESOURCE_ID_IMAGE_DATE_9
};
int WHITE_DATE_IMAGE_RESOURCE_IDS[NUMBER_OF_DATE_IMAGES] = {
  RESOURCE_ID_IMAGE_DATE_0, 
  RESOURCE_ID_IMAGE_DATE_1, RESOURCE_ID_IMAGE_DATE_2, RESOURCE_ID_IMAGE_DATE_3, 
  RESOURCE_ID_IMAGE_DATE_4, RESOURCE_ID_IMAGE_DATE_5, RESOURCE_ID_IMAGE_DATE_6, 
  RESOURCE_ID_IMAGE_DATE_7, RESOURCE_ID_IMAGE_DATE_8, RESOURCE_ID_IMAGE_DATE_9
};
int RED_DATE_IMAGE_RESOURCE_IDS[NUMBER_OF_DATE_IMAGES] = {
  RESOURCE_ID_RED_IMAGE_DATE_0, 
  RESOURCE_ID_RED_IMAGE_DATE_1, RESOURCE_ID_RED_IMAGE_DATE_2, RESOURCE_ID_RED_IMAGE_DATE_3, 
  RESOURCE_ID_RED_IMAGE_DATE_4, RESOURCE_ID_RED_IMAGE_DATE_5, RESOURCE_ID_RED_IMAGE_DATE_6, 
  RESOURCE_ID_RED_IMAGE_DATE_7, RESOURCE_ID_RED_IMAGE_DATE_8, RESOURCE_ID_RED_IMAGE_DATE_9
};
int BLUE_DATE_IMAGE_RESOURCE_IDS[NUMBER_OF_DATE_IMAGES] = {
  RESOURCE_ID_BLUE_IMAGE_DATE_0, 
  RESOURCE_ID_BLUE_IMAGE_DATE_1, RESOURCE_ID_BLUE_IMAGE_DATE_2, RESOURCE_ID_BLUE_IMAGE_DATE_3, 
  RESOURCE_ID_BLUE_IMAGE_DATE_4, RESOURCE_ID_BLUE_IMAGE_DATE_5, RESOURCE_ID_BLUE_IMAGE_DATE_6, 
  RESOURCE_ID_BLUE_IMAGE_DATE_7, RESOURCE_ID_BLUE_IMAGE_DATE_8, RESOURCE_ID_BLUE_IMAGE_DATE_9
};
int GREEN_DATE_IMAGE_RESOURCE_IDS[NUMBER_OF_DATE_IMAGES] = {
  RESOURCE_ID_GREEN_IMAGE_DATE_0, 
  RESOURCE_ID_GREEN_IMAGE_DATE_1, RESOURCE_ID_GREEN_IMAGE_DATE_2, RESOURCE_ID_GREEN_IMAGE_DATE_3, 
  RESOURCE_ID_GREEN_IMAGE_DATE_4, RESOURCE_ID_GREEN_IMAGE_DATE_5, RESOURCE_ID_GREEN_IMAGE_DATE_6, 
  RESOURCE_ID_GREEN_IMAGE_DATE_7, RESOURCE_ID_GREEN_IMAGE_DATE_8, RESOURCE_ID_GREEN_IMAGE_DATE_9
};
int BLACK_DATE_IMAGE_RESOURCE_IDS[NUMBER_OF_DATE_IMAGES] = {
  RESOURCE_ID_BLACK_IMAGE_DATE_0, 
  RESOURCE_ID_BLACK_IMAGE_DATE_1, RESOURCE_ID_BLACK_IMAGE_DATE_2, RESOURCE_ID_BLACK_IMAGE_DATE_3, 
  RESOURCE_ID_BLACK_IMAGE_DATE_4, RESOURCE_ID_BLACK_IMAGE_DATE_5, RESOURCE_ID_BLACK_IMAGE_DATE_6, 
  RESOURCE_ID_BLACK_IMAGE_DATE_7, RESOURCE_ID_BLACK_IMAGE_DATE_8, RESOURCE_ID_BLACK_IMAGE_DATE_9
};
int FB_DATE_IMAGE_RESOURCE_IDS[NUMBER_OF_DATE_IMAGES] = {
  RESOURCE_ID_FB_IMAGE_DATE_0, 
  RESOURCE_ID_FB_IMAGE_DATE_1, RESOURCE_ID_FB_IMAGE_DATE_2, RESOURCE_ID_FB_IMAGE_DATE_3, 
  RESOURCE_ID_FB_IMAGE_DATE_4, RESOURCE_ID_FB_IMAGE_DATE_5, RESOURCE_ID_FB_IMAGE_DATE_6, 
  RESOURCE_ID_FB_IMAGE_DATE_7, RESOURCE_ID_FB_IMAGE_DATE_8, RESOURCE_ID_FB_IMAGE_DATE_9
};

#define NUMBER_OF_SECOND_IMAGES 10
int SECOND_IMAGE_RESOURCE_IDS[NUMBER_OF_SECOND_IMAGES] = {
  RESOURCE_ID_IMAGE_SECOND_0, 
  RESOURCE_ID_IMAGE_SECOND_1, RESOURCE_ID_IMAGE_SECOND_2, RESOURCE_ID_IMAGE_SECOND_3, 
  RESOURCE_ID_IMAGE_SECOND_4, RESOURCE_ID_IMAGE_SECOND_5, RESOURCE_ID_IMAGE_SECOND_6, 
  RESOURCE_ID_IMAGE_SECOND_7, RESOURCE_ID_IMAGE_SECOND_8, RESOURCE_ID_IMAGE_SECOND_9
};
int WHITE_SECOND_IMAGE_RESOURCE_IDS[NUMBER_OF_SECOND_IMAGES] = {
  RESOURCE_ID_IMAGE_SECOND_0, 
  RESOURCE_ID_IMAGE_SECOND_1, RESOURCE_ID_IMAGE_SECOND_2, RESOURCE_ID_IMAGE_SECOND_3, 
  RESOURCE_ID_IMAGE_SECOND_4, RESOURCE_ID_IMAGE_SECOND_5, RESOURCE_ID_IMAGE_SECOND_6, 
  RESOURCE_ID_IMAGE_SECOND_7, RESOURCE_ID_IMAGE_SECOND_8, RESOURCE_ID_IMAGE_SECOND_9
};
int RED_SECOND_IMAGE_RESOURCE_IDS[NUMBER_OF_SECOND_IMAGES] = {
  RESOURCE_ID_RED_IMAGE_SECOND_0, 
  RESOURCE_ID_RED_IMAGE_SECOND_1, RESOURCE_ID_RED_IMAGE_SECOND_2, RESOURCE_ID_RED_IMAGE_SECOND_3, 
  RESOURCE_ID_RED_IMAGE_SECOND_4, RESOURCE_ID_RED_IMAGE_SECOND_5, RESOURCE_ID_RED_IMAGE_SECOND_6, 
  RESOURCE_ID_RED_IMAGE_SECOND_7, RESOURCE_ID_RED_IMAGE_SECOND_8, RESOURCE_ID_RED_IMAGE_SECOND_9
};
int BLUE_SECOND_IMAGE_RESOURCE_IDS[NUMBER_OF_SECOND_IMAGES] = {
  RESOURCE_ID_BLUE_IMAGE_SECOND_0, 
  RESOURCE_ID_BLUE_IMAGE_SECOND_1, RESOURCE_ID_BLUE_IMAGE_SECOND_2, RESOURCE_ID_BLUE_IMAGE_SECOND_3, 
  RESOURCE_ID_BLUE_IMAGE_SECOND_4, RESOURCE_ID_BLUE_IMAGE_SECOND_5, RESOURCE_ID_BLUE_IMAGE_SECOND_6, 
  RESOURCE_ID_BLUE_IMAGE_SECOND_7, RESOURCE_ID_BLUE_IMAGE_SECOND_8, RESOURCE_ID_BLUE_IMAGE_SECOND_9
};
int GREEN_SECOND_IMAGE_RESOURCE_IDS[NUMBER_OF_SECOND_IMAGES] = {
  RESOURCE_ID_GREEN_IMAGE_SECOND_0, 
  RESOURCE_ID_GREEN_IMAGE_SECOND_1, RESOURCE_ID_GREEN_IMAGE_SECOND_2, RESOURCE_ID_GREEN_IMAGE_SECOND_3, 
  RESOURCE_ID_GREEN_IMAGE_SECOND_4, RESOURCE_ID_GREEN_IMAGE_SECOND_5, RESOURCE_ID_GREEN_IMAGE_SECOND_6, 
  RESOURCE_ID_GREEN_IMAGE_SECOND_7, RESOURCE_ID_GREEN_IMAGE_SECOND_8, RESOURCE_ID_GREEN_IMAGE_SECOND_9
};
int BLACK_SECOND_IMAGE_RESOURCE_IDS[NUMBER_OF_SECOND_IMAGES] = {
  RESOURCE_ID_BLACK_IMAGE_SECOND_0, 
  RESOURCE_ID_BLACK_IMAGE_SECOND_1, RESOURCE_ID_BLACK_IMAGE_SECOND_2, RESOURCE_ID_BLACK_IMAGE_SECOND_3, 
  RESOURCE_ID_BLACK_IMAGE_SECOND_4, RESOURCE_ID_BLACK_IMAGE_SECOND_5, RESOURCE_ID_BLACK_IMAGE_SECOND_6, 
  RESOURCE_ID_BLACK_IMAGE_SECOND_7, RESOURCE_ID_BLACK_IMAGE_SECOND_8, RESOURCE_ID_BLACK_IMAGE_SECOND_9
};
int FB_SECOND_IMAGE_RESOURCE_IDS[NUMBER_OF_SECOND_IMAGES] = {
  RESOURCE_ID_FB_IMAGE_SECOND_0, 
  RESOURCE_ID_FB_IMAGE_SECOND_1, RESOURCE_ID_FB_IMAGE_SECOND_2, RESOURCE_ID_FB_IMAGE_SECOND_3, 
  RESOURCE_ID_FB_IMAGE_SECOND_4, RESOURCE_ID_FB_IMAGE_SECOND_5, RESOURCE_ID_FB_IMAGE_SECOND_6, 
  RESOURCE_ID_FB_IMAGE_SECOND_7, RESOURCE_ID_FB_IMAGE_SECOND_8, RESOURCE_ID_FB_IMAGE_SECOND_9
};

#define NUMBER_OF_DAY_IMAGES 7
int DAY_IMAGE_RESOURCE_IDS[NUMBER_OF_DAY_IMAGES] = {
  RESOURCE_ID_IMAGE_DAY_0, RESOURCE_ID_IMAGE_DAY_1, RESOURCE_ID_IMAGE_DAY_2, 
  RESOURCE_ID_IMAGE_DAY_3, RESOURCE_ID_IMAGE_DAY_4, RESOURCE_ID_IMAGE_DAY_5, 
  RESOURCE_ID_IMAGE_DAY_6
};
int WHITE_DAY_IMAGE_RESOURCE_IDS[NUMBER_OF_DAY_IMAGES] = {
  RESOURCE_ID_IMAGE_DAY_0, RESOURCE_ID_IMAGE_DAY_1, RESOURCE_ID_IMAGE_DAY_2, 
  RESOURCE_ID_IMAGE_DAY_3, RESOURCE_ID_IMAGE_DAY_4, RESOURCE_ID_IMAGE_DAY_5, 
  RESOURCE_ID_IMAGE_DAY_6
};
int RED_DAY_IMAGE_RESOURCE_IDS[NUMBER_OF_DAY_IMAGES] = {
  RESOURCE_ID_RED_IMAGE_DAY_0, RESOURCE_ID_RED_IMAGE_DAY_1, RESOURCE_ID_RED_IMAGE_DAY_2, 
  RESOURCE_ID_RED_IMAGE_DAY_3, RESOURCE_ID_RED_IMAGE_DAY_4, RESOURCE_ID_RED_IMAGE_DAY_5, 
  RESOURCE_ID_RED_IMAGE_DAY_6
};
int BLUE_DAY_IMAGE_RESOURCE_IDS[NUMBER_OF_DAY_IMAGES] = {
  RESOURCE_ID_BLUE_IMAGE_DAY_0, RESOURCE_ID_BLUE_IMAGE_DAY_1, RESOURCE_ID_BLUE_IMAGE_DAY_2, 
  RESOURCE_ID_BLUE_IMAGE_DAY_3, RESOURCE_ID_BLUE_IMAGE_DAY_4, RESOURCE_ID_BLUE_IMAGE_DAY_5, 
  RESOURCE_ID_BLUE_IMAGE_DAY_6
};
int GREEN_DAY_IMAGE_RESOURCE_IDS[NUMBER_OF_DAY_IMAGES] = {
  RESOURCE_ID_GREEN_IMAGE_DAY_0, RESOURCE_ID_GREEN_IMAGE_DAY_1, RESOURCE_ID_GREEN_IMAGE_DAY_2, 
  RESOURCE_ID_GREEN_IMAGE_DAY_3, RESOURCE_ID_GREEN_IMAGE_DAY_4, RESOURCE_ID_GREEN_IMAGE_DAY_5, 
  RESOURCE_ID_GREEN_IMAGE_DAY_6
};
int BLACK_DAY_IMAGE_RESOURCE_IDS[NUMBER_OF_DAY_IMAGES] = {
  RESOURCE_ID_BLACK_IMAGE_DAY_0, RESOURCE_ID_BLACK_IMAGE_DAY_1, RESOURCE_ID_BLACK_IMAGE_DAY_2, 
  RESOURCE_ID_BLACK_IMAGE_DAY_3, RESOURCE_ID_BLACK_IMAGE_DAY_4, RESOURCE_ID_BLACK_IMAGE_DAY_5, 
  RESOURCE_ID_BLACK_IMAGE_DAY_6
};
int FB_DAY_IMAGE_RESOURCE_IDS[NUMBER_OF_DAY_IMAGES] = {
  RESOURCE_ID_FB_IMAGE_DAY_0, RESOURCE_ID_FB_IMAGE_DAY_1, RESOURCE_ID_FB_IMAGE_DAY_2, 
  RESOURCE_ID_FB_IMAGE_DAY_3, RESOURCE_ID_FB_IMAGE_DAY_4, RESOURCE_ID_FB_IMAGE_DAY_5, 
  RESOURCE_ID_FB_IMAGE_DAY_6
};


// General
static Window *window;


#define EMPTY_SLOT -1
typedef struct Slot {
  int         number;
  GBitmap     *image;
  BitmapLayer *image_layer;
  int         state;
} Slot;

// Time
typedef struct TimeSlot {
  Slot              slot;
  int               new_state;
  PropertyAnimation *slide_out_animation;
  PropertyAnimation *slide_in_animation;
  bool              updating;
} TimeSlot;

#define NUMBER_OF_TIME_SLOTS 4
static Layer *time_layer;
static TimeSlot time_slots[NUMBER_OF_TIME_SLOTS];

// Footer
static Layer *footer_layer;

// Day
typedef struct DayItem {
  GBitmap     *image;
  BitmapLayer *image_layer;
  Layer       *layer;
  bool       loaded;
} DayItem;
static DayItem day_item;

// Date
#define NUMBER_OF_DATE_SLOTS 4
static Layer *date_layer;
static Slot date_slots[NUMBER_OF_DATE_SLOTS];

// Seconds
#define NUMBER_OF_SECOND_SLOTS 2
static Layer *seconds_layer;
static Slot second_slots[NUMBER_OF_SECOND_SLOTS];


// General
void destroy_property_animation(PropertyAnimation **prop_animation);
BitmapLayer *load_digit_image_into_slot(Slot *slot, int digit_value, Layer *parent_layer, GRect frame, const int *digit_resource_ids);
void unload_digit_image_from_slot(Slot *slot);

// Time
void display_time(struct tm *tick_time);
void display_time_value(int value, int row_number);
void update_time_slot(TimeSlot *time_slot, int digit_value);
GRect frame_for_time_slot(TimeSlot *time_slot);
void slide_in_digit_image_into_time_slot(TimeSlot *time_slot, int digit_value);
void time_slot_slide_in_animation_stopped(Animation *slide_in_animation, bool finished, void *context);
void slide_out_digit_image_from_time_slot(TimeSlot *time_slot);
void time_slot_slide_out_animation_stopped(Animation *slide_out_animation, bool finished, void *context);

// Day
void display_day(struct tm *tick_time);
void unload_day_item();

// Date
void display_date(struct tm *tick_time);
void display_date_value(int value, int part_number);
void update_date_slot(Slot *date_slot, int digit_value);

// Seconds
void display_seconds(struct tm *tick_time);
void update_second_slot(Slot *second_slot, int digit_value);

// Handlers
int main(void);
void init();
void handle_second_tick(struct tm *tick_time, TimeUnits units_changed);
void deinit();

// Recuperation des parametres
#define KEY_TIME_COLOR 0
#define KEY_DATE_COLOR 1
#define KEY_SECOND_COLOR 2
#define KEY_DAY_COLOR 3
#define KEY_BACKGROUND_COLOR 4
#define KEY_AMERICAN_FORMAT 5
#define KEY_VIBE_HOUR 6

static void inbox_received_handler(DictionaryIterator *iter, void *context) {
  Tuple *time_color_t = dict_find(iter, KEY_TIME_COLOR);
  Tuple *date_color_t = dict_find(iter, KEY_DATE_COLOR);
  Tuple *second_color_t = dict_find(iter, KEY_SECOND_COLOR);
  Tuple *day_color_t = dict_find(iter, KEY_DAY_COLOR);
  Tuple *background_color_t = dict_find(iter, KEY_BACKGROUND_COLOR);
  Tuple *american_format_t = dict_find(iter, KEY_AMERICAN_FORMAT);
  Tuple *vibe_hour_t = dict_find(iter, KEY_VIBE_HOUR);

  persist_write_int(KEY_TIME_COLOR, (int)time_color_t->value->int32);
  persist_write_int(KEY_DATE_COLOR, (int)date_color_t->value->int32);
  persist_write_int(KEY_SECOND_COLOR, (int)second_color_t->value->int32);
  persist_write_int(KEY_DAY_COLOR, (int)day_color_t->value->int32);
  persist_write_int(KEY_BACKGROUND_COLOR, background_color_t->value->uint8);
  persist_write_int(KEY_AMERICAN_FORMAT, (int)american_format_t->value->int32);
  persist_write_int(KEY_VIBE_HOUR, (int)vibe_hour_t->value->int32);
  
  init();
}

// General
void destroy_property_animation(PropertyAnimation **animation) {
  if (*animation == NULL)
    return;

  if (animation_is_scheduled((Animation *)*animation)) {
    animation_unschedule((Animation *)*animation);
  }

  property_animation_destroy(*animation);
  *animation = NULL;
}

BitmapLayer *load_digit_image_into_slot(Slot *slot, int digit_value, Layer *parent_layer, GRect frame, const int *digit_resource_ids) {
  if (digit_value < 0 || digit_value > 9)
    return NULL;

  if (slot->state != EMPTY_SLOT)
    return NULL;

  slot->state = digit_value;

  slot->image = gbitmap_create_with_resource(digit_resource_ids[digit_value]);

  slot->image_layer = bitmap_layer_create(frame);
  // transparence images
  bitmap_layer_set_compositing_mode(slot->image_layer, GCompOpSet);
  bitmap_layer_set_bitmap(slot->image_layer, slot->image);
  layer_add_child(parent_layer, bitmap_layer_get_layer(slot->image_layer));

  return slot->image_layer;
}

void unload_digit_image_from_slot(Slot *slot) {
  if (slot->state == EMPTY_SLOT)
    return;

  layer_remove_from_parent(bitmap_layer_get_layer(slot->image_layer));
  bitmap_layer_destroy(slot->image_layer);

  gbitmap_destroy(slot->image);

  slot->state = EMPTY_SLOT;
}

// Time
void display_time(struct tm *tick_time) {
  int hour = tick_time->tm_hour;

  if (!clock_is_24h_style()) {
    hour = hour % 12;
    if (hour == 0) {
      hour = 12;
    }
  }

  display_time_value(hour,              0);
  display_time_value(tick_time->tm_min, 1);
}

void display_time_value(int value, int row_number) {
  value = value % 100; // Maximum of two digits per row.

  for (int column_number = 1; column_number >= 0; column_number--) {
    int time_slot_number = (row_number * 2) + column_number;

    TimeSlot *time_slot = &time_slots[time_slot_number];

    update_time_slot(time_slot, value % 10);

    value = value / 10;
  }
}

void update_time_slot(TimeSlot *time_slot, int digit_value) {
  if (time_slot->slot.state == digit_value)
    return;

  if (time_slot->updating) {
    // Otherwise we'll crash when the animation is replaced by a new animation before we're finished.
    return;
  }

  if (time_slot->slot.state == EMPTY_SLOT) {
    GRect frame = frame_for_time_slot(time_slot);
    
    load_digit_image_into_slot(&time_slot->slot, digit_value, time_layer, frame, TIME_IMAGE_RESOURCE_IDS);
  }
  else {
    time_slot->updating = true;
    time_slot->new_state = digit_value;
    slide_out_digit_image_from_time_slot(time_slot);
  }
}

GRect frame_for_time_slot(TimeSlot *time_slot) {
  int x = MARGIN + (time_slot->slot.number % 2) * (TIME_IMAGE_WIDTH + TIME_SLOT_SPACE);
  int y = MARGIN + (time_slot->slot.number / 2) * (TIME_IMAGE_HEIGHT + TIME_SLOT_SPACE);

  return GRect(x, y, TIME_IMAGE_WIDTH, TIME_IMAGE_HEIGHT);
}

void slide_in_digit_image_into_time_slot(TimeSlot *time_slot, int digit_value) {
  destroy_property_animation(&time_slot->slide_in_animation);

  GRect to_frame = frame_for_time_slot(time_slot);

  int from_x = to_frame.origin.x;
  int from_y = to_frame.origin.y;
  switch (time_slot->slot.number) {
    case 0:
      from_x -= TIME_IMAGE_WIDTH + MARGIN;
      break;
    case 1:
      from_y -= TIME_IMAGE_HEIGHT + MARGIN;
      break;
    case 2:
      from_y += TIME_IMAGE_HEIGHT + MARGIN;
      break;
    case 3:
      from_x += TIME_IMAGE_WIDTH + MARGIN;
      break;
  }
  GRect from_frame = GRect(from_x, from_y, TIME_IMAGE_WIDTH, TIME_IMAGE_HEIGHT);
  
  BitmapLayer *image_layer = load_digit_image_into_slot(&time_slot->slot, digit_value, time_layer, from_frame, TIME_IMAGE_RESOURCE_IDS);

  time_slot->slide_in_animation = property_animation_create_layer_frame(bitmap_layer_get_layer(image_layer), &from_frame, &to_frame);

  Animation *animation = (Animation *)time_slot->slide_in_animation;
  animation_set_duration( animation,  TIME_SLOT_ANIMATION_DURATION);
  animation_set_curve(    animation,  AnimationCurveLinear);
  animation_set_handlers( animation,  (AnimationHandlers){
    .stopped = (AnimationStoppedHandler)time_slot_slide_in_animation_stopped
  }, (void *)time_slot);

  animation_schedule(animation);
}

void time_slot_slide_in_animation_stopped(Animation *slide_in_animation, bool finished, void *context) {
  TimeSlot *time_slot = (TimeSlot *)context;

  destroy_property_animation(&time_slot->slide_in_animation);

  time_slot->updating = false;
}

void slide_out_digit_image_from_time_slot(TimeSlot *time_slot) {
  destroy_property_animation(&time_slot->slide_out_animation);

  GRect from_frame = frame_for_time_slot(time_slot);

  int to_x = from_frame.origin.x;
  int to_y = from_frame.origin.y;
  switch (time_slot->slot.number) {
    case 0:
      to_y -= TIME_IMAGE_HEIGHT + MARGIN;
      break;
    case 1:
      to_x += TIME_IMAGE_WIDTH + MARGIN;
      break;
    case 2:
      to_x -= TIME_IMAGE_WIDTH + MARGIN;
      break;
    case 3:
      to_y += TIME_IMAGE_HEIGHT + MARGIN;
      break;
  }
  GRect to_frame = GRect(to_x, to_y, TIME_IMAGE_WIDTH, TIME_IMAGE_HEIGHT);

  BitmapLayer *image_layer = time_slot->slot.image_layer;

  time_slot->slide_out_animation = property_animation_create_layer_frame(bitmap_layer_get_layer(image_layer), &from_frame, &to_frame);

  Animation *animation = (Animation *)time_slot->slide_out_animation;
  animation_set_duration( animation,  TIME_SLOT_ANIMATION_DURATION);
  animation_set_curve(    animation,  AnimationCurveLinear);
  animation_set_handlers(animation, (AnimationHandlers){
    .stopped = (AnimationStoppedHandler)time_slot_slide_out_animation_stopped
  }, (void *)time_slot);

  animation_schedule(animation);
}

void time_slot_slide_out_animation_stopped(Animation *slide_out_animation, bool finished, void *context) {
  TimeSlot *time_slot = (TimeSlot *)context;

  destroy_property_animation(&time_slot->slide_out_animation);

  if (time_slot->new_state == EMPTY_SLOT) {
    time_slot->updating = false;
  }
  else {
    unload_digit_image_from_slot(&time_slot->slot);

    slide_in_digit_image_into_time_slot(time_slot, time_slot->new_state);

    time_slot->new_state = EMPTY_SLOT;
  }
}

// Day
void display_day(struct tm *tick_time) {
  unload_day_item();

  day_item.image = gbitmap_create_with_resource(DAY_IMAGE_RESOURCE_IDS[tick_time->tm_wday]);

  day_item.image_layer = bitmap_layer_create(gbitmap_get_bounds(day_item.image));
  // transparence images
  bitmap_layer_set_compositing_mode(day_item.image_layer, GCompOpSet);
  bitmap_layer_set_bitmap(day_item.image_layer, day_item.image);
  layer_add_child(day_item.layer, bitmap_layer_get_layer(day_item.image_layer));

  day_item.loaded = true;
}

void unload_day_item() {
  if (!day_item.loaded) 
    return;

  layer_remove_from_parent(bitmap_layer_get_layer(day_item.image_layer));
  bitmap_layer_destroy(day_item.image_layer);

  gbitmap_destroy(day_item.image);
}

// Date
void display_date(struct tm *tick_time) {
  int day   = tick_time->tm_mday;
  int month = tick_time->tm_mon + 1;

  if (USE_AMERICAN_DATE_FORMAT) {
    display_date_value(month, 0);
    display_date_value(day,   1);
  } else {
    display_date_value(day,   0);
    display_date_value(month, 1);
  }
}

void display_date_value(int value, int part_number) {
  value = value % 100; // Maximum of two digits per row.

  for (int column_number = 1; column_number >= 0; column_number--) {
    int date_slot_number = (part_number * 2) + column_number;

    Slot *date_slot = &date_slots[date_slot_number];

    update_date_slot(date_slot, value % 10);

    value = value / 10;
  }
}

void update_date_slot(Slot *date_slot, int digit_value) {
  if (date_slot->state == digit_value)
    return;

  int x = date_slot->number * (DATE_IMAGE_WIDTH + MARGIN);
  if (date_slot->number >= 2) {
    x += 3; // 3 extra pixels of space between the day and month
  }
  GRect frame =  GRect(x, 0, DATE_IMAGE_WIDTH, DATE_IMAGE_HEIGHT);

  unload_digit_image_from_slot(date_slot);
  load_digit_image_into_slot(date_slot, digit_value, date_layer, frame, DATE_IMAGE_RESOURCE_IDS);
}

// Seconds
void display_seconds(struct tm *tick_time) {
  int seconds = tick_time->tm_sec;

  seconds = seconds % 100; // Maximum of two digits per row.

  for (int second_slot_number = 1; second_slot_number >= 0; second_slot_number--) {
    Slot *second_slot = &second_slots[second_slot_number];

    update_second_slot(second_slot, seconds % 10);
    
    seconds = seconds / 10;
  }
}

void update_second_slot(Slot *second_slot, int digit_value) {
  if (second_slot->state == digit_value)
    return;

  GRect frame = GRect(
    second_slot->number * (SECOND_IMAGE_WIDTH + MARGIN), 
    0, 
    SECOND_IMAGE_WIDTH, 
    SECOND_IMAGE_HEIGHT
  );

  unload_digit_image_from_slot(second_slot);
  load_digit_image_into_slot(second_slot, digit_value, seconds_layer, frame, SECOND_IMAGE_RESOURCE_IDS);
}

// Handlers
int main(void) {
  init();
  app_event_loop();
  deinit();
}

void init() {
  // gestion de la couleur de l'heure
  int time_color_code = persist_read_int(KEY_TIME_COLOR);
  switch (time_color_code) {   
    case 0:
    memcpy(TIME_IMAGE_RESOURCE_IDS, WHITE_TIME_IMAGE_RESOURCE_IDS, sizeof TIME_IMAGE_RESOURCE_IDS);    
    break;
    case 1:
    memcpy(TIME_IMAGE_RESOURCE_IDS, RED_TIME_IMAGE_RESOURCE_IDS, sizeof TIME_IMAGE_RESOURCE_IDS);    
    break;
    case 2:
    memcpy(TIME_IMAGE_RESOURCE_IDS, BLUE_TIME_IMAGE_RESOURCE_IDS, sizeof TIME_IMAGE_RESOURCE_IDS);
    break;
    case 3:
    memcpy(TIME_IMAGE_RESOURCE_IDS, GREEN_TIME_IMAGE_RESOURCE_IDS, sizeof TIME_IMAGE_RESOURCE_IDS);
    break;
    case 4:
    memcpy(TIME_IMAGE_RESOURCE_IDS, BLACK_TIME_IMAGE_RESOURCE_IDS, sizeof TIME_IMAGE_RESOURCE_IDS);
    break;
    case 5:
    memcpy(TIME_IMAGE_RESOURCE_IDS, FB_TIME_IMAGE_RESOURCE_IDS, sizeof TIME_IMAGE_RESOURCE_IDS);
    break;
  }
  
  // gestion de la couleur de la date
  int date_color_code = persist_read_int(KEY_DATE_COLOR);
  switch (date_color_code) { 
    case 0:
    memcpy(DATE_IMAGE_RESOURCE_IDS, WHITE_DATE_IMAGE_RESOURCE_IDS, sizeof DATE_IMAGE_RESOURCE_IDS);    
    break;
    case 1:
    memcpy(DATE_IMAGE_RESOURCE_IDS, RED_DATE_IMAGE_RESOURCE_IDS, sizeof DATE_IMAGE_RESOURCE_IDS);    
    break;
    case 2:
    memcpy(DATE_IMAGE_RESOURCE_IDS, BLUE_DATE_IMAGE_RESOURCE_IDS, sizeof DATE_IMAGE_RESOURCE_IDS);
    break;
    case 3:
    memcpy(DATE_IMAGE_RESOURCE_IDS, GREEN_DATE_IMAGE_RESOURCE_IDS, sizeof DATE_IMAGE_RESOURCE_IDS);
    break;
    case 4:
    memcpy(DATE_IMAGE_RESOURCE_IDS, BLACK_DATE_IMAGE_RESOURCE_IDS, sizeof DATE_IMAGE_RESOURCE_IDS);
    break;
    case 5:
    memcpy(DATE_IMAGE_RESOURCE_IDS, FB_DATE_IMAGE_RESOURCE_IDS, sizeof DATE_IMAGE_RESOURCE_IDS);
    break;
  }
  
  // gestion de la couleur des secondes
  int second_color_code = persist_read_int(KEY_SECOND_COLOR);
  switch (second_color_code) {     
    case 0:
    memcpy(SECOND_IMAGE_RESOURCE_IDS, WHITE_SECOND_IMAGE_RESOURCE_IDS, sizeof SECOND_IMAGE_RESOURCE_IDS);    
    break;
    case 1:
    memcpy(SECOND_IMAGE_RESOURCE_IDS, RED_SECOND_IMAGE_RESOURCE_IDS, sizeof SECOND_IMAGE_RESOURCE_IDS);    
    break;
    case 2:
    memcpy(SECOND_IMAGE_RESOURCE_IDS, BLUE_SECOND_IMAGE_RESOURCE_IDS, sizeof SECOND_IMAGE_RESOURCE_IDS);
    break;
    case 3:
    memcpy(SECOND_IMAGE_RESOURCE_IDS, GREEN_SECOND_IMAGE_RESOURCE_IDS, sizeof SECOND_IMAGE_RESOURCE_IDS);
    break;
    case 4:
    memcpy(SECOND_IMAGE_RESOURCE_IDS, BLACK_SECOND_IMAGE_RESOURCE_IDS, sizeof SECOND_IMAGE_RESOURCE_IDS);
    break;
    case 5:
    memcpy(SECOND_IMAGE_RESOURCE_IDS, FB_SECOND_IMAGE_RESOURCE_IDS, sizeof SECOND_IMAGE_RESOURCE_IDS);
    break;
  }
  
  // gestion de la couleur du jour
  int day_color_code = persist_read_int(KEY_DAY_COLOR);
  switch (day_color_code) { 
    case 0:
    memcpy(DAY_IMAGE_RESOURCE_IDS, WHITE_DAY_IMAGE_RESOURCE_IDS, sizeof DAY_IMAGE_RESOURCE_IDS);    
    break;
    case 1:
    memcpy(DAY_IMAGE_RESOURCE_IDS, RED_DAY_IMAGE_RESOURCE_IDS, sizeof DAY_IMAGE_RESOURCE_IDS);    
    break;
    case 2:
    memcpy(DAY_IMAGE_RESOURCE_IDS, BLUE_DAY_IMAGE_RESOURCE_IDS, sizeof DAY_IMAGE_RESOURCE_IDS);
    break;
    case 3:
    memcpy(DAY_IMAGE_RESOURCE_IDS, GREEN_DAY_IMAGE_RESOURCE_IDS, sizeof DAY_IMAGE_RESOURCE_IDS);
    break;
    case 4:
    memcpy(DAY_IMAGE_RESOURCE_IDS, BLACK_DAY_IMAGE_RESOURCE_IDS, sizeof DAY_IMAGE_RESOURCE_IDS);
    break;
    case 5:
    memcpy(DAY_IMAGE_RESOURCE_IDS, FB_DAY_IMAGE_RESOURCE_IDS, sizeof DAY_IMAGE_RESOURCE_IDS);
    break;
  }
  
  // maj de american format
  int am_format = persist_read_int(KEY_AMERICAN_FORMAT);
  if (am_format == 1) {
    USE_AMERICAN_DATE_FORMAT = true;
  } else {
    USE_AMERICAN_DATE_FORMAT = false;
  } 
  
  // maj de vibe on hour
  int vibe_hour = persist_read_int(KEY_VIBE_HOUR);
  if (vibe_hour == 1) {
    VIBE_ON_HOUR = true;
  } else {
    VIBE_ON_HOUR = false;
  } 
  
  window = window_create();
  window_stack_push(window, true /* Animated */);
  
  GColor background_color;
  background_color.argb = persist_read_int(KEY_BACKGROUND_COLOR);
  window_set_background_color(window, background_color);

  Layer *root_layer = window_get_root_layer(window);

  // Time
  for (int i = 0; i < NUMBER_OF_TIME_SLOTS; i++) {
    TimeSlot *time_slot = &time_slots[i];
    time_slot->slot.number  = i;
    time_slot->slot.state   = EMPTY_SLOT;
    time_slot->new_state    = EMPTY_SLOT;
    time_slot->updating     = false;
  }

  time_layer = layer_create(GRect(0, 0, SCREEN_WIDTH, SCREEN_WIDTH));
  layer_set_clips(time_layer, true);
  layer_add_child(root_layer, time_layer);

  // Footer
  int footer_height = SCREEN_HEIGHT - SCREEN_WIDTH;

  footer_layer = layer_create(GRect(0, SCREEN_WIDTH, SCREEN_WIDTH, footer_height));
  layer_add_child(root_layer, footer_layer);

  // Day
  day_item.loaded = false;

  GRect day_layer_frame = GRect(
    MARGIN, 
    footer_height - DAY_IMAGE_HEIGHT - MARGIN, 
    DAY_IMAGE_WIDTH, 
    DAY_IMAGE_HEIGHT
  );
  day_item.layer = layer_create(day_layer_frame);
  layer_add_child(footer_layer, day_item.layer);

  // Date
  for (int i = 0; i < NUMBER_OF_DATE_SLOTS; i++) {
    Slot *date_slot = &date_slots[i];
    date_slot->number = i;
    date_slot->state  = EMPTY_SLOT;
  }

  GRect date_layer_frame = GRectZero;
  date_layer_frame.size.w   = DATE_IMAGE_WIDTH + MARGIN + DATE_IMAGE_WIDTH + DATE_PART_SPACE + DATE_IMAGE_WIDTH + MARGIN + DATE_IMAGE_WIDTH;
  date_layer_frame.size.h   = DATE_IMAGE_HEIGHT;
  date_layer_frame.origin.x = (SCREEN_WIDTH - date_layer_frame.size.w) / 2;
  date_layer_frame.origin.y = footer_height - DATE_IMAGE_HEIGHT - MARGIN;

  date_layer = layer_create(date_layer_frame);
  layer_add_child(footer_layer, date_layer);

  // Seconds
  for (int i = 0; i < NUMBER_OF_SECOND_SLOTS; i++) {
    Slot *second_slot = &second_slots[i];
    second_slot->number = i;
    second_slot->state  = EMPTY_SLOT;
  }

  GRect seconds_layer_frame = GRect(
    SCREEN_WIDTH - SECOND_IMAGE_WIDTH - MARGIN - SECOND_IMAGE_WIDTH - MARGIN, 
    footer_height - SECOND_IMAGE_HEIGHT - MARGIN, 
    SECOND_IMAGE_WIDTH + MARGIN + SECOND_IMAGE_WIDTH, 
    SECOND_IMAGE_HEIGHT
  );
  seconds_layer = layer_create(seconds_layer_frame);
  layer_add_child(footer_layer, seconds_layer);


  // Display
  time_t now = time(NULL);
  struct tm *tick_time = localtime(&now);
  display_time(tick_time);
  display_day(tick_time);
  display_date(tick_time);
  display_seconds(tick_time);

  tick_timer_service_subscribe(SECOND_UNIT, handle_second_tick);
  
  app_message_register_inbox_received(inbox_received_handler);
  app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());
}

void handle_second_tick(struct tm *tick_time, TimeUnits units_changed) {
  display_seconds(tick_time);

  if ((units_changed & MINUTE_UNIT) == MINUTE_UNIT) {
    display_time(tick_time);
  }

  if (VIBE_ON_HOUR) {
    if ((units_changed & HOUR_UNIT) == HOUR_UNIT) {
      vibes_double_pulse();
    }
  }

  if ((units_changed & DAY_UNIT) == DAY_UNIT) {
    display_day(tick_time);
    display_date(tick_time);
  }
}

void deinit() {
  // Time
  for (int i = 0; i < NUMBER_OF_TIME_SLOTS; i++) {
    unload_digit_image_from_slot(&time_slots[i].slot);

    destroy_property_animation(&time_slots[i].slide_in_animation);
    destroy_property_animation(&time_slots[i].slide_out_animation);
  }
  layer_destroy(time_layer);

  // Day
  unload_day_item();
  layer_destroy(day_item.layer);

  // Date
  for (int i = 0; i < NUMBER_OF_DATE_SLOTS; i++) {
    unload_digit_image_from_slot(&date_slots[i]);
  }
  layer_destroy(date_layer);

  // Seconds
  for (int i = 0; i < NUMBER_OF_SECOND_SLOTS; i++) {
    unload_digit_image_from_slot(&second_slots[i]);
  }
  layer_destroy(seconds_layer);


  layer_destroy(footer_layer);

  window_destroy(window);
}