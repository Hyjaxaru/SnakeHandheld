//
// tm1638.h
// 
// Utilities for working with the TM1638 expansion board
//

#ifndef TM1638_H
#define TM1638_H

#include <TM1638plus.h>

// These defines were taken from one of the worksheets
#define STROBE_TM D5    // strobe = GPIO connected to strobe line of module
#define CLOCK_TM D4     // clock = GPIO connected to clock line of module
#define DIO_TM D3       // data = GPIO connected to data line of module
#define HIGH_FREQ false // default false, If using a high freq CPU > ~100 MHZ set to true.

class TM1638Utility
{
public:
  // initialise and return the expansion board
  static TM1638plus Init();

  // setup the expansion board. Intended to be put in the setup() function
  static void Setup(TM1638plus& tm);

  // check if a specific button has been pressed
  static bool IsButtonPressed(TM1638plus& tm, int buttonIndex);
};

#endif // TM1638_H