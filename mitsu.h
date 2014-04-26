


#include "wiringPi.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/time.h>

#define LED              5 // IR LED wiringPi pin
#define EMPIRICAL_DELAY 12 // to achieve 36 KHz
#define ON               1
#define OFF              0

// position of interesting values within byte array
#define TEMP    7
#define DAY    10
#define TIME   14
#define CRC    17
#define ON_OFF  5
#define MODE    6

// timings
#define P_DEL    460
#define P_ZERO   379
#define P_ONE   1190
#define P_H1    3400
#define P_H2    1650
#define P_H3   11275

#define DEBUG 0
#define DUMP_RAW 0

enum mode {
    HEATING    = 8,
    DEHUMIDIFY = 16,
    COOLING   = 24
};

void send(unsigned char temp, unsigned char on, enum mode operation);
