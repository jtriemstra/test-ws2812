// Credit: https://wp.josh.com/2014/05/13/ws2812-neopixels-are-not-so-finicky-once-you-get-to-know-them/
// These values depend on which pins your 8 strings are connected to and what board you are using 
// More info on how to find these at http://www.arduino.cc/en/Reference/PortManipulation

// PORTD controls Digital Pins 0-7 on the Uno

// You'll need to look up the port/bit combination for other boards. 

// Note that you could also include the DigitalWriteFast header file to not need to to this lookup.

#define PIXEL_PORT  PORTD  // Port of the pin the pixels are connected to
#define PIXEL_PORT2  PORTC  // Port of the pin the pixels are connected to
#define PIXEL_DDR   DDRD   // Port of the pin the pixels are connected to
#define PIXEL_DDR2   DDRC

// These are the timing constraints taken mostly from the WS2812 datasheets 
// These are chosen to be conservative and avoid problems rather than for maximum throughput 

#define T1H  900    // Width of a 1 bit in ns
#define T1L  600    // Width of a 1 bit in ns

#define T0H  400    // Width of a 0 bit in ns
#define T0L  900    // Width of a 0 bit in ns

#define RES 6000    // Width of the low gap between bits to cause a frame to latch

// Here are some convience defines for using nanoseconds specs to generate actual CPU delays

#define NS_PER_SEC (1000000000L)          // Note that this has to be SIGNED since we want to be able to check for negative values of derivatives

#define CYCLES_PER_SEC (F_CPU)

#define NS_PER_CYCLE ( NS_PER_SEC / CYCLES_PER_SEC )

#define NS_TO_CYCLES(n) ( (n) / NS_PER_CYCLE )

const int STRING_LENGTH = 40;

// Actually send the next set of 8 WS2812B encoded bits to the 8 pins.
// We must to drop to asm to enusre that the complier does
// not reorder things and make it so the delay happens in the wrong place.

static inline __attribute__ ((always_inline)) void sendBitX8( uint8_t bits ) {

    const uint8_t onBits = 0xff;          // We need to send all bits on on all pins as the first 1/3 of the encoded bits
            
    asm volatile (
      
      "out %[port1], %[onBits] \n\t"           // 1st step - send T0H high 
      "out %[port2], %[onBits] \n\t"
      
      ".rept %[T0HCycles] \n\t"               // Execute NOPs to delay exactly the specified number of cycles
        "nop \n\t"
      ".endr \n\t"
      
      "out %[port1], %[bits] \n\t"             // set the output bits to thier values for T0H-T1H
      "out %[port2], %[bits] \n\t"
      ".rept %[dataCycles] \n\t"               // Execute NOPs to delay exactly the specified number of cycles
      "nop \n\t"
      ".endr \n\t"
      
      "out %[port1],__zero_reg__  \n\t"        // last step - T1L all bits low
      "out %[port2],__zero_reg__  \n\t"
      
      // Don't need an explicit delay here since the overhead that follows will always be long enough
    
      ::
      [port1]    "I" (_SFR_IO_ADDR(PIXEL_PORT)),
      [port2]    "I" (_SFR_IO_ADDR(PIXEL_PORT2)),
      [bits]   "d" (bits),
      [onBits]   "d" (onBits),
      
      [T0HCycles]  "I" (NS_TO_CYCLES(T0H) - 3),           // 1-bit width less overhead  for the actual bit setting, note that this delay could be longer and everything would still work
      
      [dataCycles]   "I" (NS_TO_CYCLES((T1H-T0H)) - 3)     // Minimum interbit delay. Note that we probably don't need this at all since the loop overhead will be enough, but here for correctness

    );
                                  

    // Note that the inter-bit gap can be as long as you want as long as it doesn't exceed the reset timeout (which is A long time)
    
}  


// Each string is one bit in "row" represening on or off

static inline void __attribute__ ((always_inline)) sendWhiteRow( uint8_t row ) {
  uint8_t bit=24;       

  while (bit--) {
      sendBitX8( row );
  }
}
    
static inline void __attribute__ ((always_inline)) sendGreenRow( uint8_t row ) {
  uint8_t bit=24;       

  while (bit--) {
      if (bit > 16) sendBitX8( row );
      else sendBitX8(0b00000000) ;
  }
}

static inline void __attribute__ ((always_inline)) sendRedRow( uint8_t row ) {
  uint8_t bit=24;       

  while (bit--) {
      if (bit <= 16 && bit > 8) sendBitX8( row );
      else sendBitX8(0b00000000) ;
  }
}

static inline void __attribute__ ((always_inline)) sendBlueRow( uint8_t row ) {
  uint8_t bit=24;       

  while (bit--) {
      if (bit <= 8) sendBitX8( row );
      else sendBitX8(0b00000000) ;
  }
}

static inline void __attribute__ ((always_inline)) sendColorRow( uint8_t row, uint8_t red, uint8_t green, uint8_t blue ) {
  if (row == 0) 
  {
    uint8_t bit=24;   
    while (bit--) {
      sendBitX8(0b00000000) ;
    }    
  }
  else
  {
    for (int i=0; i<8; i++){
      
    }
  }
  
}



// Just wait long enough without sending any bits to cause the pixels to latch and display the last sent frame
void show() {
  _delay_us( (RES / 1000UL) + 1);       // Round up since the delay must be _at_least_ this long (too short might not work, too long not a problem)
}

void clearAll(){
  cli();                        // No time for interruptions!
  for (int i=0; i<STRING_LENGTH; i++) sendWhiteRow(0b00000000);
  sei();
  show();
}
int loopCount = 0;
bool blnIncrement = true;
bool blnRunning = false;

void setup() {
  PIXEL_DDR = 0xff;    // Set all row pins to output
  PIXEL_DDR2 = 0xff;    // Set all row pins to output
  
  clearAll();
  delay(500);

}


void loop() {
  sendRedRow(0b11111111);
  sendBlueRow(0b11111111);
  sendGreenRow(0b11111111);
  while(true);
}
