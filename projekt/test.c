#include <stdio.h>
#include <stdint.h>

int main(void){
    uint32_t color32 = 0;
    color32 = 
        ((uint32_t)(10) << 24) |
        ((uint32_t)(20) << 16) |
        ((uint32_t)(30) << 8)  |
        ((uint32_t)(40));
    printf("%d\n", color32);

    // int x = color32 >> (32 - 8); // upierdala  najstarsze 24 bity (od prawej)
    int s = (color32 >> 16) & ((1 << 8) - 1);
    printf("%d\n", s);
}