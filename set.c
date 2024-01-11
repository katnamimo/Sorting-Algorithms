#include "set.h"

#include <stdint.h>
#include <stdio.h>

Set set_empty(void) {
    return 0;
}
Set set_insert(Set s, uint8_t x) {
    return (s | (1u << x));
}
bool set_member(Set s, uint8_t x) {
    return (s & (1u << x)) != 0;
}
