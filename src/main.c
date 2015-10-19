#include <pebble.h>

static Window *s_main_window;
static TextLayer *s_weekday_layer, *s_date_layer, *s_time_layer, *s_current_class_layer, *s_current_loc_layer, *s_next_class_layer, *s_next_loc_layer;
static BitmapLayer *s_bt_layer;
static GBitmap *s_bt_bitmap;

static void update_weekday() {
  time_t temp = time(NULL);
  struct tm *tick_time = localtime(&temp);
  int day = tick_time->tm_wday;
  
  if(day == 0) {
    text_layer_set_text(s_weekday_layer, "Zo");
  }
  else if(day == 1) {
    text_layer_set_text(s_weekday_layer, "Ma");
  }
  else if(day == 2) {
    text_layer_set_text(s_weekday_layer, "Di");
  }
  else if(day == 3) {
    text_layer_set_text(s_weekday_layer, "Wo");
  }
  else if(day == 4) {
    text_layer_set_text(s_weekday_layer, "Do");
  }
  else if(day == 5) {
    text_layer_set_text(s_weekday_layer, "Vr");
  }
  else if(day == 6) {
    text_layer_set_text(s_weekday_layer, "Za");
  }
}

static void update_date() {
  time_t temp = time(NULL);
  struct tm *tick_time = localtime(&temp);
  
  static char date_buffer[] = "00/00";
  
  strftime(date_buffer, sizeof("00/00"), "%d/%m", tick_time);
  
  text_layer_set_text(s_date_layer, date_buffer);
}

static void update_time() {
  time_t temp = time(NULL);
  struct tm *tick_time = localtime(&temp);

  static char time_buffer[] = "00:00";
  
  if(clock_is_24h_style() == true) {
    strftime(time_buffer, sizeof("00:00"), "%H:%M", tick_time);
  } else {
    strftime(time_buffer, sizeof("00:00"), "%I:%M", tick_time);
  }
  
  text_layer_set_text(s_time_layer, time_buffer);
}

static void update_class() {
  time_t temp = time(NULL);
  struct tm *tick_time = localtime(&temp);
  int day = tick_time->tm_wday;
  int hour = tick_time->tm_hour;
  int min = tick_time->tm_min;
  
//  text_layer_set_text(s_current_class_layer, "");
//  text_layer_set_text(s_current_loc_layer, "");
//  text_layer_set_text(s_next_class_layer, "");
//  text_layer_set_text(s_next_loc_layer, "");
  
  if(day == 0) {
    
  }
  else if(day == 1) {
    if(hour == 8) {
      if(min < 30) {
        text_layer_set_text(s_current_class_layer, "");
        text_layer_set_text(s_current_loc_layer, "");
        text_layer_set_text(s_next_class_layer, "Ges");
        text_layer_set_text(s_next_loc_layer, "T125");
      }
      else if(min < 30) {
        text_layer_set_text(s_current_class_layer, "Ges");
        text_layer_set_text(s_current_loc_layer, "T125");
        text_layer_set_text(s_next_class_layer, "Ned");
        text_layer_set_text(s_next_loc_layer, "T010");
      }
    }
    else if(hour == 9) {
      if(min < 25) {
        text_layer_set_text(s_current_class_layer, "Ges");
        text_layer_set_text(s_current_loc_layer, "T125");
        text_layer_set_text(s_next_class_layer, "Ned");
        text_layer_set_text(s_next_loc_layer, "T010");
      }
      else if(min > 25) {
        text_layer_set_text(s_current_class_layer, "Ned");
        text_layer_set_text(s_current_loc_layer, "T010");
        text_layer_set_text(s_next_class_layer, "LO");
        text_layer_set_text(s_next_loc_layer, "EdAr");
      }
    }
    else if(hour == 10) {
      if(min < 15) {
        text_layer_set_text(s_current_class_layer, "Ned");
        text_layer_set_text(s_current_loc_layer, "T010");
        text_layer_set_text(s_next_class_layer, "LO");
        text_layer_set_text(s_next_loc_layer, "EdAr");
      }
      else if(min < 30) {
        text_layer_set_text(s_current_class_layer, "");
        text_layer_set_text(s_current_loc_layer, "");
        text_layer_set_text(s_next_class_layer, "LO");
        text_layer_set_text(s_next_loc_layer, "EdAr");
      }
      else if(min > 30) {
        text_layer_set_text(s_current_class_layer, "LO");
        text_layer_set_text(s_current_loc_layer, "EdAr");
        text_layer_set_text(s_next_class_layer, "Inf");
        text_layer_set_text(s_next_loc_layer, "O/A");
      }
    }
    else if(hour == 11) {
      if(min < 25) {
        text_layer_set_text(s_current_class_layer, "LO");
        text_layer_set_text(s_current_loc_layer, "EdAr");
        text_layer_set_text(s_next_class_layer, "Inf");
        text_layer_set_text(s_next_loc_layer, "O/A");
      }
      else if(min > 25) {
        text_layer_set_text(s_current_class_layer, "Inf");
        text_layer_set_text(s_current_loc_layer, "O/A");
        text_layer_set_text(s_next_class_layer, "Wis");
        text_layer_set_text(s_next_loc_layer, "T009");
      }
    }
    else if(hour == 12) {
      if(min < 15) {
        text_layer_set_text(s_current_class_layer, "Inf");
        text_layer_set_text(s_current_loc_layer, "O/A");
        text_layer_set_text(s_next_class_layer, "Wis");
        text_layer_set_text(s_next_loc_layer, "T009");
      }
      else if(min > 15) {
        text_layer_set_text(s_current_class_layer, "");
        text_layer_set_text(s_current_loc_layer, "");
        text_layer_set_text(s_next_class_layer, "Wis");
        text_layer_set_text(s_next_loc_layer, "T009");
      }
    }
    else if(hour == 13) {
      if(min > 25) {
        text_layer_set_text(s_current_class_layer, "Wis");
        text_layer_set_text(s_current_loc_layer, "T009");
        text_layer_set_text(s_next_class_layer, "God");
        text_layer_set_text(s_next_loc_layer, "T010");
      }
    }
    else if(hour == 14) {
      if(min < 20) {
        text_layer_set_text(s_current_class_layer, "Wis");
        text_layer_set_text(s_current_loc_layer, "T009");
        text_layer_set_text(s_next_class_layer, "God");
        text_layer_set_text(s_next_loc_layer, "T010");
      }
      else if(min > 20) {
        text_layer_set_text(s_current_class_layer, "God");
        text_layer_set_text(s_current_loc_layer, "T009");
        text_layer_set_text(s_next_class_layer, "Ned");
        text_layer_set_text(s_next_loc_layer, "T010");
      }
    }
    else if(hour == 15) {
      if(min < 10) {
        text_layer_set_text(s_current_class_layer, "God");
        text_layer_set_text(s_current_loc_layer, "T010");
        text_layer_set_text(s_next_class_layer, "Ned");
        text_layer_set_text(s_next_loc_layer, "T010");
      }
      else if(min > 10) {
        text_layer_set_text(s_current_class_layer, "Ned");
        text_layer_set_text(s_current_loc_layer, "T011");
        text_layer_set_text(s_next_class_layer, "");
        text_layer_set_text(s_next_loc_layer, "");
      } 
    }
  }
  else if(day == 2) {
    if(hour == 20) {
      if(min < 30) {
        text_layer_set_text(s_current_class_layer, "");
        text_layer_set_text(s_current_loc_layer, "");
        text_layer_set_text(s_next_class_layer, "Ens");
        text_layer_set_text(s_next_loc_layer, "M217");
      }
      else if(min > 30) {
        text_layer_set_text(s_current_class_layer, "Ens");
        text_layer_set_text(s_current_loc_layer, "M217");
        text_layer_set_text(s_next_class_layer, "");
        text_layer_set_text(s_next_loc_layer, "");
      }
    }
    else if(hour == 21) {
      if(min < 30) {
        text_layer_set_text(s_current_class_layer, "Ens");
        text_layer_set_text(s_current_loc_layer, "M217");
        text_layer_set_text(s_next_class_layer, "");
        text_layer_set_text(s_next_loc_layer, "");
      }
      else if(min > 30) {
        text_layer_set_text(s_current_class_layer, "");
        text_layer_set_text(s_current_loc_layer, "");
        text_layer_set_text(s_next_class_layer, "");
        text_layer_set_text(s_next_loc_layer, "");
      }
    }
  }
  else if(day == 3) {
    if(hour == 8) {
      if(min < 30) {
        text_layer_set_text(s_next_class_layer, "LO");
        text_layer_set_text(s_next_loc_layer, "TZ");
      }
      else if(min > 30) {
        text_layer_set_text(s_current_class_layer, "TZ");
        text_layer_set_text(s_current_loc_layer, "LO");
        text_layer_set_text(s_next_class_layer, "Fra");
        text_layer_set_text(s_next_loc_layer, "T012");
      }
    }
    else if(hour == 9) {
      if(min < 25) {
        text_layer_set_text(s_current_class_layer, "LO");
        text_layer_set_text(s_current_loc_layer, "TZ");
        text_layer_set_text(s_next_class_layer, "Fra");
        text_layer_set_text(s_next_loc_layer, "T012");
      }
      else if(min > 25) {
        text_layer_set_text(s_current_class_layer, "Fra");
        text_layer_set_text(s_current_loc_layer, "T012");
        text_layer_set_text(s_next_class_layer, "Eng");
        text_layer_set_text(s_next_loc_layer, "T125");
      }
    }
    else if(hour == 10) {
      if(min < 15) {
        text_layer_set_text(s_current_class_layer, "Fra");
        text_layer_set_text(s_current_loc_layer, "T012");
        text_layer_set_text(s_next_class_layer, "Eng");
        text_layer_set_text(s_next_loc_layer, "T126");
      }
      else if(min < 30) {
        text_layer_set_text(s_current_class_layer, "");
        text_layer_set_text(s_current_loc_layer, "");
        text_layer_set_text(s_next_class_layer, "Eng");
        text_layer_set_text(s_next_loc_layer, "T126");
      }
      else if(min > 30) {
        text_layer_set_text(s_current_class_layer, "Eng");
        text_layer_set_text(s_current_loc_layer, "T126");
        text_layer_set_text(s_next_class_layer, "Ges");
        text_layer_set_text(s_next_loc_layer, "T125");
      }
    }
    else if(hour == 11) {
      if(min < 25) {
        text_layer_set_text(s_current_class_layer, "Eng");
        text_layer_set_text(s_current_loc_layer, "T126");
        text_layer_set_text(s_next_class_layer, "Ges");
        text_layer_set_text(s_next_loc_layer, "T125");
      }
      else if(min > 25) {
        text_layer_set_text(s_current_class_layer, "Ges");
        text_layer_set_text(s_current_loc_layer, "T126");
        text_layer_set_text(s_next_class_layer, "");
        text_layer_set_text(s_next_loc_layer, "");
      }
    }
    else if(hour == 12) {
      if(min < 15) {
        text_layer_set_text(s_current_class_layer, "Ges");
        text_layer_set_text(s_current_loc_layer, "T125");
        text_layer_set_text(s_next_class_layer, "");
        text_layer_set_text(s_next_loc_layer, "");
      }
      else if(min > 15) {
        text_layer_set_text(s_current_class_layer, "");
        text_layer_set_text(s_current_loc_layer, "");
        text_layer_set_text(s_next_class_layer, "");
        text_layer_set_text(s_next_loc_layer, "");
      }
    }
  }
  else if(day == 4) {
    
  }
  else if(day == 5) {
    
  }
  else if(day == 6) {
    
  }
  else {
    text_layer_set_text(s_current_class_layer, "Ned");
    text_layer_set_text(s_current_loc_layer, "T055");
    text_layer_set_text(s_next_class_layer, "Wat");
    text_layer_set_text(s_next_loc_layer, "Wat");
  }
}

static void main_window_load(Window *window) {
  s_weekday_layer = text_layer_create(GRect(0, 6, 54, 30));
  s_date_layer = text_layer_create(GRect(58, 6, 70, 30));
  s_time_layer = text_layer_create(GRect(0, 30, 144, 50));
  s_current_class_layer = text_layer_create(GRect(0, 84, 56, 50));
  s_current_loc_layer = text_layer_create(GRect(62, 84, 82, 50));
  s_next_class_layer = text_layer_create(GRect(0, 120, 66, 34));
  s_next_loc_layer = text_layer_create(GRect(72, 120, 72, 34));
  
  s_bt_layer = bitmap_layer_create(GRect(0, 0, 14, 25));
  
  bitmap_layer_set_bitmap(s_bt_layer, s_bt_bitmap);
  
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_weekday_layer));
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_date_layer));
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_time_layer));
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_current_class_layer));
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_current_loc_layer));
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_next_class_layer));
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_next_loc_layer));
  layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(s_bt_layer));
  
  text_layer_set_text_color(s_weekday_layer, GColorWhite);
  text_layer_set_text_color(s_date_layer, GColorWhite);
  text_layer_set_text_color(s_time_layer, GColorWhite);
  text_layer_set_text_color(s_current_class_layer, GColorWhite);
  text_layer_set_text_color(s_current_loc_layer, GColorWhite);
  text_layer_set_text_color(s_next_class_layer, GColorWhite);
  text_layer_set_text_color(s_next_loc_layer, GColorWhite);
  
  text_layer_set_font(s_weekday_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
  text_layer_set_font(s_date_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
  text_layer_set_font(s_time_layer, fonts_get_system_font(FONT_KEY_BITHAM_42_MEDIUM_NUMBERS));
  text_layer_set_font(s_current_class_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
  text_layer_set_font(s_current_loc_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
  text_layer_set_font(s_next_class_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
  text_layer_set_font(s_next_loc_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
  
  text_layer_set_text_alignment(s_weekday_layer, GTextAlignmentRight);
  text_layer_set_text_alignment(s_date_layer, GTextAlignmentLeft);
  text_layer_set_text_alignment(s_time_layer, GTextAlignmentCenter);
  text_layer_set_text_alignment(s_current_class_layer, GTextAlignmentRight);
  text_layer_set_text_alignment(s_current_loc_layer, GTextAlignmentLeft);
  text_layer_set_text_alignment(s_next_class_layer, GTextAlignmentRight);
  text_layer_set_text_alignment(s_next_loc_layer, GTextAlignmentLeft);
  
  text_layer_set_background_color(s_weekday_layer, GColorClear);
  text_layer_set_background_color(s_date_layer, GColorClear);
  text_layer_set_background_color(s_time_layer, GColorClear);
  text_layer_set_background_color(s_current_class_layer, GColorClear);
  text_layer_set_background_color(s_current_loc_layer, GColorClear);
  text_layer_set_background_color(s_next_class_layer, GColorClear);
  text_layer_set_background_color(s_next_loc_layer, GColorClear);
  
//  s_bt_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BLUETOOTH);
}


static void main_window_unload(Window *window) {
  text_layer_destroy(s_weekday_layer);
  text_layer_destroy(s_date_layer);
  text_layer_destroy(s_time_layer);
  text_layer_destroy(s_current_class_layer);
  text_layer_destroy(s_current_loc_layer);
  text_layer_destroy(s_next_class_layer);
  text_layer_destroy(s_next_loc_layer);
  
  gbitmap_destroy(s_bt_bitmap);
  bitmap_layer_destroy(s_bt_layer);
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  update_weekday();
  update_date();
  update_time();
  update_class();
}

static void init() {
  s_main_window = window_create();
  
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });
  
  window_set_background_color(s_main_window, GColorBlack);
  window_stack_push(s_main_window, true);

  update_weekday();
  update_date();
  update_time();
  update_class();

  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
}

static void deinit() {
  window_destroy(s_main_window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}