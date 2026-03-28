#include "vars.h"
#include <string.h>

static char hex_value[8] = "#000000";

const char *get_var_hex_value() {
    return hex_value;
}

void set_var_hex_value(const char *value) {
    strncpy(hex_value, value, sizeof(hex_value) - 1);
}
