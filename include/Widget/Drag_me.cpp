#include<lvgl.h>

// void lv_example_obj_1(void)
// {
//     lv_obj_t * obj1;
//     obj1 = lv_obj_create(lv_scr_act());
//     lv_obj_set_size(obj1, 100, 50);
//     lv_obj_align(obj1, LV_ALIGN_CENTER, -60, -30);

//     static lv_style_t style_shadow;
//     lv_style_init(&style_shadow);
//     lv_style_set_shadow_width(&style_shadow, 10);
//     lv_style_set_shadow_spread(&style_shadow, 5);
//     lv_style_set_shadow_color(&style_shadow, lv_palette_main(LV_PALETTE_BLUE));

//     lv_obj_t * obj2;
//     obj2 = lv_obj_create(lv_scr_act());
//     lv_obj_add_style(obj2, &style_shadow, 0);
//     lv_obj_align(obj2, LV_ALIGN_CENTER, 60, 30);
// }


//--------------

static void drag_event_handler(lv_event_t * e)
{
    lv_obj_t * obj = lv_event_get_target(e);

    lv_indev_t * indev = lv_indev_get_act();
    if(indev == NULL)  return;

    lv_point_t vect;
    lv_indev_get_vect(indev, &vect);

    lv_coord_t x = lv_obj_get_x(obj) + vect.x;
    lv_coord_t y = lv_obj_get_y(obj) + vect.y;
    lv_obj_set_pos(obj, x, y);
}

//  Make an object dragable.

void lv_example_obj_2(void)
{
    lv_obj_t * screen1;
    screen1 = lv_obj_create(lv_scr_act());
    lv_obj_set_size(screen1, 150, 100);
    lv_obj_add_event_cb(screen1, drag_event_handler, LV_EVENT_PRESSING, NULL);

    lv_obj_t * label = lv_label_create(screen1);
    lv_label_set_text(label, "Drag me");
    lv_obj_center(label);

}





