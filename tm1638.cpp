//
// tm1638.cpp
// 
// Utilities for working with the TM1638 expansion board
//

#include "tm1638.h"

#include <TM1638plus.h>

TM1638plus TM1638Utility::Init() {
  TM1638plus tm(STROBE_TM, CLOCK_TM , DIO_TM, HIGH_FREQ);
  return tm;
}

void TM1638Utility::Setup(TM1638plus& tm) {
  tm.displayBegin();
  tm.reset();
}

bool TM1638Utility::IsButtonPressed(TM1638plus& tm, int buttonIndex) {
  // get the buttons current state
  byte buttons = tm.readButtons();
  // shift the bits over and mask to just the 1s
  byte isEnabled = buttons >> buttonIndex & 0b000000001;
  // return true if we find anything other than 0
  return isEnabled == true;
}