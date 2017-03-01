#include <unabto/unabto.h>
#include <modules/network/w5100/w5100_network.h>
#include <unabto/unabto_common_main.h>

#include <avr/io.h>
#include <util/delay.h>

#include <stdio.h>
#include <stdbool.h>
#include <spi.h>
#include <string.h>

char idBuffer[64];

uint8_t mac[] = { 
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

#define PORT_LED PORTB
#define PIN_LED PORTB7
#define DDR_LED DDRB

void init_led(void);

int main (void)
{
    init_led();
    
    platform_init();
    NABTO_LOG_INFO(("starting"));
    
    network_initialize(mac);

    // Initialize Nabto
    nabto_main_setup* nms = unabto_init_context();
    memset(idBuffer,0, 64);
    sprintf(idBuffer, "%02x%02x%02x.starterkit.u.nabto.net", mac[3], mac[4], mac[5]);
    nms->id = idBuffer;

    nms->cryptoSuite = CRYPT_W_AES_CBC_HMAC_SHA256;
    nms->secureAttach = 1;
    nms->secureData = 1;
    memset(nms->presharedKey, 0, PRE_SHARED_KEY_SIZE);
    
    unabto_init();
    nabto_stamp_t ticker = nabtoGetStamp();
    nabtoSetFutureStamp(&ticker, 1000);
    while(true) {
        if (nabtoIsStampPassed(&ticker)) {
            static int i = 0;
            NABTO_LOG_INFO(("tick %i", i++));
            nabtoSetFutureStamp(&ticker, 1000);
        }
        network_tick();
        unabto_tick();
    }
    return 1;
}

void init_led() {
    DDR_LED |= _BV(PORTB7);
}

// Set first onboard LED and return state,
// only using ID #1 in this simple example  
uint8_t set_led(char led_id, char led_on) {
    if (led_id == 1) {
        if (led_on) {
            PORT_LED |= _BV(PIN_LED);
        } else {
            PORT_LED &= ~(_BV(PIN_LED));
        }
        return (PORT_LED & _BV(PIN_LED));
    }
    else {
        return 0;
    }
}

// Return first onboard LED state,
// only using ID #1 in this simple example
uint8_t read_led(char led_id) {
    if (led_id == 1) {
        return (PORT_LED & _BV(PIN_LED));
    }
    else {
        return 0;
    }
}

/***************** The uNabto application logic *****************
 * This is where the user implements his/her own functionality
 * to the device. When a Nabto message is received, this function
 * gets called with the message's request id and parameters.
 * Afterwards a user defined message can be sent back to the
 * requesting browser.
 ****************************************************************/
application_event_result application_event(application_request* request, unabto_query_request* read_buffer, unabto_query_response* write_buffer) {
  switch(request->queryId) {
  case 1: 
    {
      //  <query name="light_write.json" description="Turn light on and off" id="1">
      //    <request>
      //      <parameter name="light_id" type="uint8"/>
      //      <parameter name="light_on" type="uint8"/>
      //    </request>
      //    <response>
      //      <parameter name="light_state" type="uint8"/>
      //    </response>
      //  </query>

      uint8_t light_id;
      uint8_t light_on;
      uint8_t light_state;

      // Read parameters in request
      if (!unabto_query_read_uint8(read_buffer, &light_id)) return AER_REQ_TOO_SMALL;
      if (!unabto_query_read_uint8(read_buffer, &light_on)) return AER_REQ_TOO_SMALL;

      // Set light according to request
      light_state = set_led(light_id, light_on);

      // Write back led state
      if (!unabto_query_write_uint8(write_buffer, light_state)) return AER_REQ_RSP_TOO_LARGE;

      return AER_REQ_RESPONSE_READY;
    }
  case 2: 
    {
      //  <query name="light_read.json" description="Read light status" id="2">
      //    <request>
      //      <parameter name="light_id" type="uint8"/>
      //    </request>
      //    <response>
      //      <parameter name="light_state" type="uint8"/>
      //    </response>
      //  </query>

      uint8_t light_id;
      uint8_t light_state;

      // Read parameters in request
      if (!unabto_query_read_uint8(read_buffer, &light_id)) return AER_REQ_TOO_SMALL;

      // Read light state
      light_state = read_led(light_id);

      // Write back led state
      if (!unabto_query_write_uint8(write_buffer, light_state)) return AER_REQ_RSP_TOO_LARGE;

      return AER_REQ_RESPONSE_READY;
      
    default:
      return AER_REQ_INV_QUERY_ID;
    }
  }
}
