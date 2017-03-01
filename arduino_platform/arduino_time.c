
#include "arduino_time.h"

#include <unabto/unabto_external_environment.h>

#include <avr/io.h>
#include <avr/interrupt.h>

#ifndef F_CPU
#error F_CPU not defined
#endif

static nabto_stamp_t millis = 0;

nabto_stamp_t nabtoGetStamp(void)
{
    return millis;
}

#define MAX_STAMP_DIFF 0x7FFFFFFF

bool nabtoIsStampPassed(nabto_stamp_t* stamp)
{
    nabto_stamp_t now = nabtoGetStamp();
    if ((*stamp - now) > (uint32_t)MAX_STAMP_DIFF) {
        return true;
    }
    return false;
}

ISR (TIMER1_COMPA_vect)
{
    millis++;
}

void arduino_timer1_setup()
{
    cli();
    TCCR1A = 0;
    TCCR1B = 0;
    
    // set up timer with prescaler = 64
    TCCR1B |= (1 << CS10);
    TCCR1B |= (1 << CS11);

    // set up timer to CTC mode
    TCCR1B |= (1 << WGM12);

    // initialize counter
    TCNT1 = 0;

    // initialize compare value
    // ticks pr ms at 16mhz = ((16*10^6/64)/1000) = 250
#define TICKS_PR_MS (((F_CPU/64)/1000))
    OCR1A = TICKS_PR_MS;

    TIMSK1 |= (1 << OCIE1A);
  
    // enable global interrupts
    sei();
}
