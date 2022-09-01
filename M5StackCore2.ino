/***************************************************
Copyright (c) 2020 Luis Llamas
(www.luisllamas.es)

This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by
the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public License along with this program.  If not, see <http://www.gnu.org/licenses
****************************************************/


#include <M5Core2.h>

#include <stdio.h>

#include <lvgl.h>
#include <lv_examples.h>


/**********************
 *  STATIC PROTOTYPES
 **********************/
static void selectors_create(lv_obj_t * parent);
static void text_input_create(lv_obj_t * parent);
static void msgbox_create(void);

static void focus_cb(lv_group_t * g);
static void msgbox_event_cb(lv_obj_t * msgbox, lv_event_t e);
static void tv_event_cb(lv_obj_t * ta, lv_event_t e);
static void ta_event_cb(lv_obj_t * ta, lv_event_t e);
static void kb_event_cb(lv_obj_t * kb, lv_event_t e);

/**********************
 *  STATIC VARIABLES
 **********************/
static lv_group_t*  g;
static lv_obj_t * tv;
static lv_obj_t * t1;
static lv_obj_t * t2;
static lv_obj_t * t3;

struct {
    lv_obj_t * btn;
    lv_obj_t * cb;
    lv_obj_t * slider;
    lv_obj_t * sw;
    lv_obj_t * spinbox;
    lv_obj_t * dropdown;
    lv_obj_t * roller;
    lv_obj_t * list;
}selector_objs;

struct {
    lv_obj_t * ta1;
    lv_obj_t * ta2;
    lv_obj_t * kb;
}textinput_objs;

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

LV_EVENT_CB_DECLARE(dd_enc)
{
    if(e == LV_EVENT_VALUE_CHANGED) {
        /*printf("chg\n");*/
    }
}

void lv_demo_keypad_encoder(void)
{
    g = lv_group_create();
    lv_group_set_focus_cb(g, focus_cb);

#if LV_EX_KEYBOARD
    lv_indev_drv_t kb_drv;
    lv_indev_drv_init(&kb_drv);
    kb_drv.type = LV_INDEV_TYPE_KEYPAD;
    kb_drv.read_cb = keyboard_read;
    lv_indev_t * kb_indev = lv_indev_drv_register(&kb_drv);
    lv_indev_set_group(kb_indev, g);
#endif

#if LV_EX_MOUSEWHEEL
    lv_indev_drv_t enc_drv;
    lv_indev_drv_init(&enc_drv);
    enc_drv.type = LV_INDEV_TYPE_ENCODER;
    enc_drv.read_cb = mousewheel_read;
    lv_indev_t * enc_indev = lv_indev_drv_register(&enc_drv);
    lv_indev_set_group(enc_indev, g);
#endif

    tv = lv_tabview_create(lv_scr_act(), NULL);
    lv_obj_set_event_cb(tv, tv_event_cb);

    t1 = lv_tabview_add_tab(tv, "Selectors");
    t2 = lv_tabview_add_tab(tv, "Text input");

    lv_group_add_obj(g, tv);

    selectors_create(t1);
    text_input_create(t2);

    msgbox_create();
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static void selectors_create(lv_obj_t * parent)
{
    lv_page_set_scrl_layout(parent, LV_LAYOUT_COLUMN_MID);

   selector_objs.btn = lv_btn_create(parent, NULL);

   lv_obj_t * label = lv_label_create(selector_objs.btn, NULL);
   lv_label_set_text(label, "Button");

   selector_objs.cb = lv_checkbox_create(parent, NULL);

   selector_objs.slider = lv_slider_create(parent, NULL);
   lv_slider_set_range(selector_objs.slider, 0, 10);
   lv_slider_set_type(selector_objs.slider, LV_SLIDER_TYPE_RANGE);

   selector_objs.sw = lv_switch_create(parent, NULL);

   selector_objs.spinbox = lv_spinbox_create(parent, NULL);

   selector_objs.dropdown = lv_dropdown_create(parent, NULL);
   lv_obj_set_event_cb(selector_objs.dropdown, dd_enc);

   selector_objs.roller = lv_roller_create(parent, NULL);

   selector_objs.list = lv_list_create(parent, NULL);
   if(lv_obj_get_height(selector_objs.list) > lv_page_get_height_fit(parent)) {
       lv_obj_set_height(selector_objs.list, lv_page_get_height_fit(parent));
   }
   lv_obj_t * bt;

  bt=lv_list_add_btn(selector_objs.list, LV_SYMBOL_OK, "1");lv_group_add_obj(g,bt);
  bt=lv_list_add_btn(selector_objs.list, LV_SYMBOL_CLOSE, "2");lv_group_add_obj(g,bt);
  bt=lv_list_add_btn(selector_objs.list, LV_SYMBOL_EYE_CLOSE, "3");lv_group_add_obj(g,bt);
  bt=lv_list_add_btn(selector_objs.list, LV_SYMBOL_TRASH, "4");lv_group_add_obj(g,bt);
  bt=lv_list_add_btn(selector_objs.list, LV_SYMBOL_COPY, "5");lv_group_add_obj(g,bt);
  bt=lv_list_add_btn(selector_objs.list, LV_SYMBOL_COPY, "6");lv_group_add_obj(g,bt);
  bt=lv_list_add_btn(selector_objs.list, LV_SYMBOL_OK, "7");lv_group_add_obj(g,bt);
  bt=lv_list_add_btn(selector_objs.list, LV_SYMBOL_CLOSE, "8");lv_group_add_obj(g,bt);
  bt=lv_list_add_btn(selector_objs.list, LV_SYMBOL_EYE_CLOSE, "9");lv_group_add_obj(g,bt);
  bt=lv_list_add_btn(selector_objs.list, LV_SYMBOL_TRASH, "10");lv_group_add_obj(g,bt);
  bt=lv_list_add_btn(selector_objs.list, LV_SYMBOL_COPY, "11");lv_group_add_obj(g,bt);
  bt=lv_list_add_btn(selector_objs.list, LV_SYMBOL_COPY, "12");lv_group_add_obj(g,bt);


}

static void text_input_create(lv_obj_t * parent)
{
    textinput_objs.ta1 = lv_textarea_create(parent, NULL);
    lv_obj_set_event_cb(textinput_objs.ta1, ta_event_cb);
    lv_obj_align(textinput_objs.ta1, NULL, LV_ALIGN_IN_TOP_MID, 0, LV_DPI / 20);
    lv_textarea_set_one_line(textinput_objs.ta1, true);
    lv_textarea_set_cursor_hidden(textinput_objs.ta1, true);
    lv_textarea_set_placeholder_text(textinput_objs.ta1, "Type something");
    lv_textarea_set_text(textinput_objs.ta1, "");

    textinput_objs.ta2 = lv_textarea_create(parent, textinput_objs.ta1);
    lv_obj_align(textinput_objs.ta2, textinput_objs.ta1, LV_ALIGN_OUT_BOTTOM_MID, 0, LV_DPI / 20);

    textinput_objs.kb = NULL;
}

static void msgbox_create(void)
{
    lv_obj_t * mbox = lv_msgbox_create(lv_layer_top(), NULL);
    lv_msgbox_set_text(mbox, "Welcome to the keyboard and encoder demo");
    lv_obj_set_event_cb(mbox, msgbox_event_cb);
    lv_group_add_obj(g, mbox);
    lv_group_focus_obj(mbox);
#if LV_EX_MOUSEWHEEL
    lv_group_set_editing(g, true);
#endif
    lv_group_focus_freeze(g, true);

    static const char * btns[] = {"Ok", "Cancel", ""};
    lv_msgbox_add_btns(mbox, btns);
    lv_obj_align(mbox, NULL, LV_ALIGN_CENTER, 0, 0);

    lv_obj_set_style_local_bg_opa(lv_layer_top(), LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_70);
    lv_obj_set_style_local_bg_color(lv_layer_top(), LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_GRAY);
    lv_obj_set_click(lv_layer_top(), true);
}


static void msgbox_event_cb(lv_obj_t * msgbox, lv_event_t e)
{
    if(e == LV_EVENT_CLICKED) {
        uint16_t b = lv_msgbox_get_active_btn(msgbox);
        if(b == 0 || b == 1) {
            lv_obj_del(msgbox);
            lv_obj_reset_style_list(lv_layer_top(), LV_OBJ_PART_MAIN);
            lv_obj_set_click(lv_layer_top(), false);
            lv_event_send(tv, LV_EVENT_REFRESH, NULL);
        }
    }
}

static void focus_cb(lv_group_t * group)
{
    lv_obj_t * obj = lv_group_get_focused(group);
    if(obj != tv) {
        uint16_t tab = lv_tabview_get_tab_act(tv);
        switch(tab) {
        case 0:
            lv_page_focus(t1, obj, LV_ANIM_ON);
            break;
        case 1:
            lv_page_focus(t2, obj, LV_ANIM_ON);
            break;
        case 2:
            lv_page_focus(t3, obj, LV_ANIM_ON);
            break;
        }
    }
}

static void tv_event_cb(lv_obj_t * ta, lv_event_t e)
{
    if(e == LV_EVENT_VALUE_CHANGED || e == LV_EVENT_REFRESH) {
        lv_group_remove_all_objs(g);

        uint16_t tab = lv_tabview_get_tab_act(tv);
        size_t size = 0;
        lv_obj_t ** objs = NULL;
        if(tab == 0) {
            size = sizeof(selector_objs);
            objs = (lv_obj_t**) &selector_objs;
        }
        else if(tab == 1) {
            size = sizeof(textinput_objs);
            objs = (lv_obj_t**) &textinput_objs;
        }

        lv_group_add_obj(g, tv);

        uint32_t i;
        for(i = 0; i < size / sizeof(lv_obj_t *); i++) {
            if(objs[i] == NULL) continue;
            lv_group_add_obj(g, objs[i]);
        }

    }

}

static void ta_event_cb(lv_obj_t * ta, lv_event_t e)
{
    /*Create a virtual keyboard for the encoders*/
    lv_indev_t * indev = lv_indev_get_act();
    if(indev == NULL) return;
    lv_indev_type_t indev_type = lv_indev_get_type(indev);

    if(e == LV_EVENT_FOCUSED) {
        lv_textarea_set_cursor_hidden(ta, false);
        if(lv_group_get_editing(g)) {
            if(textinput_objs.kb == NULL) {
                textinput_objs.kb = lv_keyboard_create(lv_scr_act(), NULL);
                lv_group_add_obj(g, textinput_objs.kb);
                lv_obj_set_event_cb(textinput_objs.kb, kb_event_cb);
                lv_obj_set_height(tv, LV_VER_RES - lv_obj_get_height(textinput_objs.kb));
            }

            lv_keyboard_set_textarea(textinput_objs.kb, ta);
            lv_group_focus_obj(textinput_objs.kb);
            lv_group_set_editing(g, true);
            lv_page_focus(t2, lv_textarea_get_label(ta), LV_ANIM_ON);
        }
    }
    else if(e == LV_EVENT_DEFOCUSED) {
        if(indev_type == LV_INDEV_TYPE_ENCODER) {
            if(textinput_objs.kb == NULL) {
                lv_textarea_set_cursor_hidden(ta, true);
            }
        } else {
            lv_textarea_set_cursor_hidden(ta, true);
        }
    }
}

static void kb_event_cb(lv_obj_t * kb, lv_event_t e)
{
    lv_keyboard_def_event_cb(kb, e);

    if(e == LV_EVENT_APPLY || e == LV_EVENT_CANCEL) {
        lv_group_focus_obj(lv_keyboard_get_textarea(kb));
        lv_obj_del(kb);
        textinput_objs.kb = NULL;
        lv_obj_set_height(tv, LV_VER_RES);
    }
}

static lv_disp_buf_t disp_buf;
static lv_color_t buf[LV_HOR_RES_MAX * 10];


/* Display flushing */
void my_disp_flush(lv_disp_drv_t* disp, const lv_area_t* area, lv_color_t* color_p)
{
	uint32_t w = (area->x2 - area->x1 + 1);
	uint32_t h = (area->y2 - area->y1 + 1);

	M5.Lcd.startWrite();
	M5.Lcd.setAddrWindow(area->x1, area->y1, w, h);
	M5.Lcd.pushColors(&color_p->full, w * h, true);
	M5.Lcd.endWrite();

	lv_disp_flush_ready(disp);
}

/*Read the touchpad*/
bool my_touchpad_read(lv_indev_drv_t* indev_driver, lv_indev_data_t* data)
{
	TouchPoint_t pos = M5.Touch.getPressPoint();
	bool touchStateNow = (pos.x == -1) ? false : true;
	if (touchStateNow)
	{
		data->state = LV_INDEV_STATE_PR;

		//  /*Set the coordinates*/
		data->point.x = pos.x;
		data->point.y = pos.y;

	}
	else
	{
		data->state = LV_INDEV_STATE_REL;
	}

	return false;
}



void setup()
{
	M5.begin();

	lv_init();

	M5.Lcd.begin(); /* TFT init */
	M5.Lcd.setRotation(1); /* Landscape orientation */

	lv_disp_buf_init(&disp_buf, buf, NULL, LV_HOR_RES_MAX * 10);

	/*Initialize the display*/
	lv_disp_drv_t disp_drv;
	lv_disp_drv_init(&disp_drv);
	disp_drv.hor_res = 320;
	disp_drv.ver_res = 240;
	disp_drv.flush_cb = my_disp_flush;
	disp_drv.buffer = &disp_buf;
	lv_disp_drv_register(&disp_drv);

	/*Initialize the (dummy) input device driver*/
	lv_indev_drv_t indev_drv;
	lv_indev_drv_init(&indev_drv);
	indev_drv.type = LV_INDEV_TYPE_POINTER;
	indev_drv.read_cb = my_touchpad_read;
	lv_indev_drv_register(&indev_drv);

	lv_demo_keypad_encoder();
}

unsigned long prevMillis;
void loop()
{
	lv_task_handler(); /* let the GUI do its work */
	delay(5);

}
