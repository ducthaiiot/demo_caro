#include <Arduino.h>
#include <Arduino_GFX_Library.h>
#include <Lvgl.h>
// #include "Widget/Arc.cpp"
// #include "Widget/Button.cpp"
// #include "Widget/Button_matrix.c+pp"
// #include"Widget/Canvas.cpp"
// #include "Widget/Checkbox.cpp"
// #include"Widget/Drop_down_list.cpp"
// #include "Widget/Image.cpp
// #include "Widget/Label.cpp"
// #include "Widget/Line.cpp"
// #include "Widget/Roller.cpp" 
// #include "Widget/Slider.cpp"
// #include "Widget/Switch.cpp"
// #include "Widget/Table.cpp"
// #include "Widget/Text_area.cpp"
// #include "Widget/Animation_image.cpp"
// #include "Widget/Chart.cpp"
// #include "Widget/Color_wheel.cpp"
// #include "Widget/Image_button.cpp"
// #include "Widget/Keyboard.cpp"
// #include "Widget/Led.cpp"
// #include "Widget/Calender.cpp"
// #include "Widget/List.cpp"
// #include "Widget/Menu.cpp"
// #include "Widget/Meter.cpp"
// #include "Widget/Message_box.cpp"
// #include "Widget/Span.cpp"
// #include "Widget/Spinbox.cpp"
// #include "Widget/Spinner.cpp"
// #include "Widget/Tabview.cpp"
// #include "Widget/Tile_view.cpp"
// #include "Widget/Window.cpp"
// #include "Overview/Animation.cpp"

#include "demo_caro.h"




// #define MQTT_AUTH_USER ""
// #define MQTT_AUTH_PASSWORD ""

#define TOPIC_NEW_QR_CODE "um6p/new_qrcode"
#define TOPIC_GET_QR_CODE "um6p/get_qrcode"

Arduino_ESP32RGBPanel *bus = new Arduino_ESP32RGBPanel(
    39 /* CS */, 48 /* SCK */, 47 /* SDA */,
    18 /* DE */, 17 /* VSYNC */, 16 /* HSYNC */, 21 /* PCLK */,
    11 /* R0 */, 12 /* R1 */, 13 /* R2 */, 14 /* R3 */, 0 /* R4 */,
    8 /* G0 */, 20 /* G1 */, 3 /* G2 */, 46 /* G3 */, 9 /* G4 */, 10 /* G5 */,
    4 /* B0 */, 5 /* B1 */, 6 /* B2 */, 7 /* B3 */, 15 /* B4 */
);
Arduino_ST7701_RGBPanel *gfx = new Arduino_ST7701_RGBPanel(
    bus, GFX_NOT_DEFINED /* RST */, 0 /* rotation */,
    true /* IPS */, 480 /* width */, 480 /* height */,
    st7701_type1_init_operations, sizeof(st7701_type1_init_operations), true /* BGR */,
    10 /* hsync_front_porch */, 8 /* hsync_pulse_width */, 50 /* hsync_back_porch */,
    10 /* vsync_front_porch */, 8 /* vsync_pulse_width */, 20 /* vsync_back_porch */);

#define GFX_BL 38

/* Change to your screen resolution */
static lv_disp_draw_buf_t draw_buf;
static lv_color_t *disp_draw_buf;
static lv_disp_drv_t disp_drv;

/*******************************************************************************
 * Please config the touch panel in touch.h
 ******************************************************************************/
#include "touch.h"

#define LV_COLOR_WIHTE LV_COLOR_MAKE(0xff, 0xff, 0xff)
#define LV_COLOR_BLACK LV_COLOR_MAKE(0x00, 0x00, 0x00)

// void display_wait(String message)
// {
//   /*Create a style for the shadow*/

//   lv_obj_clean(lv_scr_act());

//   lv_obj_t *background = lv_obj_create(lv_scr_act());
//   lv_obj_set_size(background, lv_disp_get_hor_res(NULL), lv_disp_get_ver_res(NULL));
//   lv_obj_set_style_bg_color(background, LV_COLOR_WIHTE, 0);

//   lv_obj_t *label = lv_label_create(background);
//   lv_label_set_long_mode(label, LV_LABEL_LONG_WRAP); /*Break the long lines*/
//   lv_label_set_recolor(label, true);                 /*Enable re-coloring by commands in the text*/
//   lv_label_set_text(label, message.c_str());
//   lv_obj_set_width(label, 400); /*Set smaller width to make the lines wrap*/

//   lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, 0);
//   lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);

//   lv_timer_handler();
// }

/* Display flushing */
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{

  // gfx->fillScreen(0x0000);

  gfx->draw16bitRGBBitmap(area->x1 + 1,
                          area->y1 + 1,
                          (uint16_t *)&color_p->full,
                          (area->x2 - area->x1 + 1),
                          (area->y2 - area->y1 + 1));

  lv_disp_flush_ready(disp);
}

void my_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data)
{
  if (touch_has_signal())
  {
    if (touch_touched())
    {
      data->state = LV_INDEV_STATE_PR;

      /*Set the coordinates*/
      data->point.x = touch_last_x;
      data->point.y = touch_last_y;
      // Serial.printf("X: %d - Y: %d", touch_last_x, touch_last_y);
    }
    else if (touch_released())
    {
      data->state = LV_INDEV_STATE_REL;
    }
  }
  else
  {
    data->state = LV_INDEV_STATE_REL;
  }
}



void setup()
{
  Wire.setPins(19,20);
  Serial.begin(115200);
  // TODO: try to cennect to API init and send the serial number

  // Init Display
  gfx->begin(10000000);

  // Init touch device
  touch_init();

  pinMode(GFX_BL, OUTPUT);
  digitalWrite(GFX_BL, HIGH);

  gfx->fillScreen(BLACK);

  lv_init();
  disp_draw_buf = (lv_color_t *)malloc(sizeof(lv_color_t) * ((gfx->width() * 200) + 1));
  if (!disp_draw_buf)
  {
    disp_draw_buf = (lv_color_t *)malloc(sizeof(lv_color_t) * ((gfx->width() * 200) + 1));
    if (!disp_draw_buf)
      return;
  }
  lv_disp_draw_buf_init(&draw_buf, disp_draw_buf, NULL, (gfx->width() * 200) + 1);
  // /* Initialize the display */
  lv_disp_drv_init(&disp_drv);
  /* Change the following line to your display resolution */
  disp_drv.hor_res = gfx->width();
  disp_drv.ver_res = gfx->height();
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.draw_buf = &draw_buf;
  lv_disp_drv_register(&disp_drv);

  /* Initialize the (dummy) input device driver */
  static lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = my_touchpad_read;
  lv_indev_drv_register(&indev_drv);

  // lv_demo_widgets()


  // Chicky code



  demo_caro();


  



  Serial.println("Setup done");
  
}

void loop()
{ 
  lv_timer_handler(); /* let the GUI do its work */
  delay(1);
}




