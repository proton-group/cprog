//
// Created by Alexa on 14.11.2021.
//
#ifndef _BCD_H_
#define _BCD_H_

#include <stdlib.h>
#include <math.h>
#include <stdio.h>

typedef unsigned int Bcd;

#define INVALID_BCD 0xFFFFFFFFU

/* Арифметика */
Bcd bcd_add(Bcd n1, Bcd n2);
Bcd bcd_sub(Bcd n1, Bcd n2);
Bcd bcd_mul(Bcd n1, Bcd n2);
void bcd_div(Bcd n1, Bcd n2, Bcd *pq, Bcd *pr);
/* pq и pr -- указатели на частное и остаток */

/* Сравнение */
int bcd_compare(Bcd n1, Bcd n2);
/* возвращает -1, 0 или 1 (n1 < n2, n1 == n2, n1 > n2) */

/* Преобразования */
Bcd bcd_from_int(int n);
int bcd_to_int(Bcd n);
char *bcd_to_str(Bcd n, char *buf, int bufsize);

#endif