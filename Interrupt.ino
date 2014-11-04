
uint_fast16_t volatile samp_rate = 4;        // Hz
uint_fast16_t volatile number_of_ms = 1000 / samp_rate;     // ms

void interruptSetup()
{
  NRF_TIMER2->TASKS_STOP = 1;	// Stop timer
  NRF_TIMER2->MODE = TIMER_MODE_MODE_Timer;  // taken from Nordic dev zone
  NRF_TIMER2->BITMODE = TIMER_BITMODE_BITMODE_16Bit;
  NRF_TIMER2->PRESCALER = 9;	// 32us resolution
  NRF_TIMER2->TASKS_CLEAR = 1; // Clear timer
  // With 32 us ticks, we need to multiply by 31.25 to get milliseconds
  NRF_TIMER2->CC[0] = number_of_ms * 31;
  NRF_TIMER2->CC[0] += number_of_ms / 4; 
  NRF_TIMER2->INTENSET = TIMER_INTENSET_COMPARE0_Enabled << TIMER_INTENSET_COMPARE0_Pos;  // taken from Nordic dev zone
  NRF_TIMER2->SHORTS = (TIMER_SHORTS_COMPARE0_CLEAR_Enabled << TIMER_SHORTS_COMPARE0_CLEAR_Pos);
  attachInterrupt(TIMER2_IRQn, TIMER2_Interrupt);    // also used in variant.cpp to configure the RTC1 
  NRF_TIMER2->TASKS_START = 1;	// Start TIMER
}

void TIMER2_Interrupt(void)
{
  if (NRF_TIMER2->EVENTS_COMPARE[0] != 0)
  {
    // blinks a led just for testing
    ledState = !ledState;
    digitalWrite(ledPinGreen, ledState);
    
    NRF_TIMER2->EVENTS_COMPARE[0] = 0;
  }
}
