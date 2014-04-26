#include "mitsu.h"

// byte array containing data
unsigned char template[] = { 35, 203, 38, 1, 0, 255, 8, 255, 48, 64, 255, 0, 0, 0, 255, 0, 0, 255 };

void pulse(unsigned int us) {
    float i = 0;
    while(i < us) {
        digitalWrite(LED, HIGH);
        delayMicroseconds(EMPIRICAL_DELAY);
        digitalWrite(LED, LOW);
        delayMicroseconds(EMPIRICAL_DELAY);
        i = i + 27.77; // 36 KHz
    }    
}

void send(unsigned char temp, unsigned char on, enum mode operation) {
    
    
    wiringPiSetup();
    // set RT priority
    piHiPri(99);
    pinMode(LED, OUTPUT);  
    
    time_t timer;
    struct tm *timeinfo;
    int i,j;
    struct timeval start, stop;
    gettimeofday(&start, NULL);
    
    timer = time(NULL);    
    timeinfo = localtime(&timer);    
    unsigned char weekday = timeinfo->tm_wday;
    // set monday to be 0 day of week
    weekday = weekday - 1;
    if(weekday == -1) {
        weekday = 6;
    }
    if(weekday > 3) {
        weekday = (weekday - 4) | 0x80;
    }
    // time
    unsigned char time = (timeinfo->tm_hour * 6) + (timeinfo->tm_min / 10);
    if(DEBUG) {
        printf("Weekday: %d\n", time);
    }   
    if(DEBUG) {
        printf("Time: %d\n", time);
    }        
    
    // temperature
    if(DEBUG) {
        printf("Temperature: %d\n", temp);
    }    
    temp = (temp - 16) & 0xf;
    
    template[TEMP] = temp;
    template[TIME] = time;
    template[DAY] = weekday;
    if(DEBUG) {
        printf("ON: %d\n", on);
    }    
    if(DEBUG) {
        printf("Mode: %d\n", operation);
    }    
    
    
    if(on == 0) {
       template[ON_OFF] = 0;
    }
    else {
       template[ON_OFF] = 32;
    }
    
    // calculate checksum
    int summa = 0;
    unsigned char * t = &template[0];
    for(i = 0; i < sizeof(template) - 1; i++) {
        summa = summa + (int) *(t++);
    }
    *t = (unsigned char) (summa & 0xff);
    
    t = &template[0];
    
    int size = 2 + ((sizeof(template) * 2) * 2 * 8) + 4 + 1;
    
    if(DEBUG) {
        printf("Size of data: %d\n", size);
    }
    
    unsigned int result[size];    
    unsigned int *u = &result[0];
    
    t = &template[0];
    *(u++) = P_H1;
    *(u++) = P_H2;    
    for(i = 0; i < sizeof(template); i++) {
        for(j = 0; j < 8; j++) {            
            if((*t & 1) == 1) {
                *(u++) = P_DEL;
                *(u++) = P_ONE;
            }
            else
            {
                *(u++) = P_DEL;
                *(u++) = P_ZERO;
            }
            *t = *t >> 1;
        }
        t++;
    }
    *(u++) = P_DEL;
    *(u++) = P_H3;
    
    *(u++) = P_H1;
    *(u++) = P_H2;
    t = &template[0];
    for(i = 0; i < sizeof(template); i++) {
        for(j = 0; j < 8; j++) {            
            if((*t & 1) == 1) {
                *(u++) = P_DEL;
                *(u++) = P_ONE;
            }
            else
            {
                *(u++) = P_DEL;
                *(u++) = P_ZERO;
            }
            *t = *t >> 1;
        }
        t++;
    }
    *(u++) = P_DEL;
    
    if(DUMP_RAW) {
        printf("Raw timings:\n");
        for(i = 0; i < size; i++) {
            if(i % 2 == 0) {
                printf("pulse ");
            }
            else
            {
                printf("space ");
            }
            printf("%d\n", result[i]);
        }
    }
    
    
    for(i = 0; i < size; i++) {
        if(i % 2 == 0) {
            pulse(result[i]);
        }
        else
        {
            delayMicroseconds(result[i]);
        }
    }
    
    long total = 0;
    for(i = 0; i < size; i++) {
        total += result[i];
    }
    
    
    if(DEBUG) {
        printf("Total should be: %f\n", total/1000000.0);    
        gettimeofday(&stop, NULL);
        printf("Elapsed %f\n", (double)(((stop.tv_sec-start.tv_sec)*1000000ULL+(stop.tv_usec-start.tv_usec)))/1000000.0);
    }
}

