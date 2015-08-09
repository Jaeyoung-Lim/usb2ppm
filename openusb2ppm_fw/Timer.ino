
ISR(TIMER1_COMPA_vect)
{
 if (timer_ptr == number_of_outputs) {
   timer_ptr = 0;  //reset the pointer to 0
   OCR1A = timer_framelength - (timer_accumulator * timer_correction_factor); //calculate the padding
   timer_accumulator = 0;  //set the accumulator to 0
 } 
 else {
   OCR1A = (pulses[timer_ptr] + timer_pause) * timer_correction_factor; //set the pulse length
   timer_accumulator += pulses[timer_ptr] + timer_pause; //add the pulse length to the accumulator
   timer_ptr++;  //increment the pointer
 } 
}

void timer_loopcount(){
    count++;
  if(count>100){
    count =0;
  }
}

