#include "vars.h"
#include <string.h>

static char hex_value[8] = "#000000";

const char *get_var_hex_value() {
    return hex_value;
}

static char history_value[8][8] = {
    "", "", "", "",
    "", "", "", ""
};

const char *get_var_history_value(int index) {
    return history_value[index];
}

void set_var_hex_value(const char *value) {
    strncpy(hex_value, value, sizeof(hex_value) - 1);
}

static int history_index = 0;
void set_var_history_value(const char *value) {
    if (history_index == 8) {
        history_index = 0;
    }
    strncpy(history_value[history_index], value, sizeof(history_value[0]) - 1);
    history_index++;
}