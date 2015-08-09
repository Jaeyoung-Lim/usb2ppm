/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
 
void serial_Event() {
  int p=0;
  int j=0;
  init_buffer(); //Reiniitialize buffer
  while (Serial.available()) {
    inChar = Serial.read();  // get the new byte:
    if(inChar == 'x'){
      j=0;
      p=0;
    }
    else if(inChar =='y'){
      j=1;
      p=0;
    }
    else if(inChar =='z'){
      j=2;
      p=0;
    }
    else if(inChar =='k'){
      j=3;
      p=0;
    }
     else if (inChar == '\0') {
      stringComplete = true;     // if the incoming character is a newline, set a flag
      break;
    }
    else if(inChar >= 48 && inChar <= 57) {
      inputString[j][p] += inChar; // add it to the inputString:
      p++;
    }
  }
}

void serial_Decode(){
   int p; //pointer to read string
 for(int j=0; j<4; j++){
  p=0;
 while(inputString[j][p]!=0){
      cmd_val[j]=10*cmd_val[j]+(inputString[j][p]-48); //String is sent in a decimal value
      p++; //move the pointer
    }
}
}

void init_buffer(){
  for(int j=0; j<4; j++){
    for(int i=0; i<26; i++){
    inputString[j][i] = 0; //Initialize string buffer
    }
    cmd_val[j]=0; //Initialize decoded command values
   }
   stringComplete = false; //Disable flag
}

void serial_monitor(){
  Serial.print(" armSW: "); Serial.print(arm_stat);
  Serial.print(" modeSW: "); Serial.println(mode);
  
  Serial.print("Ch1: ");  Serial.print(pulses[0]);
  Serial.print(" Ch2: "); Serial.print(pulses[1]);
  Serial.print(" Ch3: "); Serial.print(pulses[2]);
  Serial.print(" Ch4: "); Serial.print(pulses[3]);
   Serial.print(" Ch4: "); Serial.print(pulses[6]);
  /*
  Serial.print("trim1: ");  Serial.print(trim_val[0]);
  Serial.print(" trim2: "); Serial.print(trim_val[1]);
  Serial.print(" trim3: "); Serial.print(trim_val[2]);
  Serial.print(" trim4: "); Serial.print(trim_val[3]);
  */
}

void serial_handshake(){
  if(count>50){
  Serial.print("Ack");
  }
}

