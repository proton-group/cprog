//
// Created by Alexa on 14.11.2021.
//

#include "bcd.h"

Bcd bcd_from_int(int n) {
    Bcd out = 0;
    int buf = 0;
    if (n < 0) {
        out += 0x0000000F;
        n = -n;
    }
    for (int i = 6; i>=0; i--) {
        buf = n/pow(10,i+1);
        out = out + ((n / (int)pow(10,i) - buf*10) << 4*(i+1));
    }
}

int bcd_to_int(Bcd n){
    int out = 0;
    for(int i = 0; i < 7; i++) {
        out += (((0xF << 4*(i+1)) & n) >> 4*(i+1)) * pow(10, i);
    }
    if(n&0xF == 0xF){
        out = -out;
    }
}


Bcd bcd_add(Bcd n1, Bcd n2) {
    Bcd out = 0;
    int base = 0;
    int del = 0;
    for(int i = 0; i<7; i++){
        base = (0xF << 4*(i+1))&n1 + (0xF << 4*(i+1))&n2 + del;
        del = (0xF << 4*(i+2))&base;
        base = base - del;
        out += base;
    }

}

int main() {
    Bcd new1 = bcd_from_int(12);
    Bcd new2 = bcd_from_int(15);
    Bcd out = bcd_add(new1, new2);
    return 0;
}