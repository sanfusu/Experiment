#include "crc.h"
#include <stdint.h>
void crc_tab_gen(uint32_t* table, uint32_t poly) {
    uint32_t reg;
    for(int i = 0; i <= 255; i ++) {
        reg = i << 24;
        for(int j = 0; j <= 7; j++) {
            if(reg >> 31) {
                reg = (reg ^ poly) << 1;
            } else {
                reg <<= 1;
            }
        }
        table[i] = reg;
    }
}

int main() {
    
}