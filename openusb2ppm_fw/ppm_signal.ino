void ppm_command(int mode){
  
  if(mode == mode_serial){ //Serial mode ppm generation
    //Channel 1 to Channel 4 receives command values for control
      pulses[0] = map(cmd_val[0]+0.1*trim_val[0], 0, 1023, 650, 1800); // Copy Pulse values
      pulses[1] = map(cmd_val[1], 0, 1023, 650, 1800); //Map Pulse values
      pulses[2] = map(cmd_val[2]+0.1*trim_val[1], 0, 1023, 650, 1800); // Copy Pulse values
      pulses[3] = map(cmd_val[3]+0.1*trim_val[3], 0, 1023, 650, 1800); // Copy Pulse values
   
    }
  else if(mode == mode_trim ){
      //Channel 1 to Channel 4 receives command values only from trim levers
      pulses[0] = 1200 + trim_val[0];
      pulses[2] = 1200 + trim_val[1];
      pulses[1] = 650+trim_val[2];
      pulses[3] = 1200 + trim_val[3];
    }
     pulses[4] = 1000; // Channel 5
     
  if(arm_stat==1){ //Values from Channel 6 is defined by arming switch
     pulses[5]=1550;  
    }
    else {
     pulses[5]=800;
    }
    pulses[6] = 1000; // Channel 7
    pulses[7] = 1000; // Channel 8
}
    

void ppm_default(){
  for(int i=0; i<4; i++){
      cmd_val[i]=1000;
  }
}

void ppm_minmax(){
  for(int i=0; i<8; i++){
  if(pulses[i]>1800){
    pulses[i]=1800;
  }
  else if(pulses[i]<650){
    pulses[i]=650;
  }
}
}
