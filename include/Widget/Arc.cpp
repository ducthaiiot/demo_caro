#include <lvgl.h>
#include <stdio.h>
// static void value_changed_event_cb(lv_event_t * e);

// void lv_example_arc_1(void)
//   {
//     lv_obj_t * label = lv_label_create(lv_scr_act());

//     /*Create an Arc*/
//     lv_obj_t * arc = lv_arc_create(lv_scr_act());
//     lv_obj_set_size(arc, 150, 150);
//     lv_arc_set_rotation(arc, 135);
//     lv_arc_set_bg_angles(arc, 0, 270);
//     lv_arc_set_value(arc, 80);
//     lv_obj_center(arc);
//     // lv_obj_add_event_cb(arc, value_changed_event_cb, LV_EVENT_VALUE_CHANGED, label);

//     /*Manually update the label for the first time*/
//     lv_event_send(arc, LV_EVENT_VALUE_CHANGED, NULL);
//   }

// static void value_changed_event_cb(lv_event_t * e)
// {
//     lv_obj_t * arc = lv_event_get_target(e);
//     lv_obj_t * label = lv_event_get_user_data(e);

//     lv_label_set_text_fmt(label, "%d%%", lv_arc_get_value(arc));

//     /*Rotate the label to the current position of the arc*/
//     lv_arc_rotate_obj_to_angle(arc, label, 25);
// }

// --------------

static void set_angle(void * obj, int32_t v) {
    lv_arc_set_value((lv_obj_t *)obj, v);
}

void lv_example_arc_2(void) {
    /* Create an Arc */
    lv_obj_t * arc = lv_arc_create(lv_scr_act());
    lv_arc_set_rotation(arc, 270);
    lv_arc_set_bg_angles(arc, 0, 360);
    lv_obj_remove_style(arc, NULL, LV_PART_KNOB); /* Ensure the knob is not displayed */
    lv_obj_clear_flag(arc, LV_OBJ_FLAG_CLICKABLE); /* Prevent adjusting by click */
    lv_obj_center(arc);

    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, arc);
    lv_anim_set_exec_cb(&a, set_angle);
    lv_anim_set_time(&a, 1000);
    lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE); /* Just for the demo */
    lv_anim_set_repeat_delay(&a, 5);
    lv_anim_set_values(&a, 0, 100);
    lv_anim_start(&a);
    printf("Thai dep trai");
}








