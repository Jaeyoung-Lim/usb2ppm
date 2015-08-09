void sw_read(){
    if(digitalRead(armsw_PIN)==HIGH){
      arm_stat = 1;
    }
    else {
     arm_stat =0;
    }
    if(digitalRead(mode_PIN)==HIGH){
      mode = mode_trim;
    }
    else {
      mode = mode_serial;
    }
}

void sw_readTrim(){
    trim_val[0]=0.2*analogRead(A0)-102;
    trim_val[1]=0.2*analogRead(A1)-102;
    trim_val[2]=analogRead(A2); //Thrust Trim
    trim_val[3]=0.2*analogRead(A3)-102;
}

void sw_led(){
 if(arm_stat == 0){
  digitalWrite(led_PIN, HIGH); // LED On if arm
  if(count>50){ //Blink if not armed
    digitalWrite(led_PIN, LOW); // LED On
  }
 }
 else if(arm_stat!=0) {
    digitalWrite(led_PIN, LOW); // LED On
  }
}

