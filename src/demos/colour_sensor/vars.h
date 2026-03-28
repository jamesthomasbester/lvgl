#ifndef EEZ_LVGL_UI_VARS_H
#define EEZ_LVGL_UI_VARS_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// enum declarations

// Flow global variables

enum FlowGlobalVariables {
    FLOW_GLOBAL_VARIABLE_RED_VALUE = 0,
    FLOW_GLOBAL_VARIABLE_GREEN_VALUE = 1,
    FLOW_GLOBAL_VARIABLE_BLUE_VALUE = 2,
    FLOW_GLOBAL_VARIABLE_HEX_VALUE = 3,
    FLOW_GLOBAL_VARIABLE_HISTORY_VALUE = 4,
    FLOW_GLOBAL_VARIABLE_COLOUR_DISPLAY_VALUE = 5
};

// Native global variables

extern const char *get_var_hex_value();
extern void set_var_hex_value(const char *value);

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_VARS_H*/