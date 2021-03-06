/*
 * Copyright 2011, Ben Langmead <langmea@cs.jhu.edu>
 *
 * This file is part of Bowtie 2.
 *
 * Bowtie 2 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Bowtie 2 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Bowtie 2.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdint.h>

/* Generated by gen_lookup_tables.pl */

uint8_t cCntLUT_4[4][4][256];
uint8_t cCntLUT_4_rev[4][4][256];
uint8_t cCntBIT[8][256];

int countCnt(int by, int c, uint8_t str) {
    int count = 0;
    if(by == 0) by = 4;
    while(by-- > 0) {
        int c2 = str & 3;
        str >>= 2;
        if(c == c2) count++;
    }
    
    return count;
}

int countCnt_rev(int by, int c, uint8_t str) {
    int count = 0;
    if(by == 0) by = 4;
    while(by-- > 0) {
        int c2 = (str >> 6) & 3;
        str <<= 2;
        if(c == c2) count++;
    }
    
    return count;
}

void initializeCntLut() {
    for(int by = 0; by < 4; by++) {
        for(int c = 0; c < 4; c++) {
            for(int str = 0; str < 256; str++) {
                cCntLUT_4[by][c][str] = countCnt(by, c, str);
                cCntLUT_4_rev[by][c][str] = countCnt_rev(by, c, str);
            }
        }
    }
}

int countBit(int b, uint8_t str) {
    int count = 0;
    if(b == 0) b = 8;
    while(b-- > 0) {
        if(str & 0x1) count++;
        str >>= 1;
    }
    
    return count;
}

void initializeCntBit() {
    for(int b = 0; b < 8; b++) {
        for(int str = 0; str < 256; str++) {
            cCntBIT[b][str] = countBit(b, str);
        }
    }
}
