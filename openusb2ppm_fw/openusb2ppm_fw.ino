/*
  USB2PPM Firmware
  This program receives commands for 4 channels from the PC via string and convert it into 9 channels of ppm signals to interface with the transmitter.
  Currently this code has been tested only on Turnigy 9X. Other transmitters may be compatible but may have volatage issues

  Version 1.0.0
  
  Jaeyoung Lim
*/

//Timer Initialization
#define timer_correction_factor 1.00                        //timer correction factor. This is needed if your arduino is too fast or slow, like mine. :(
#define timer_framelength 22000 * timer_correction_factor   //Maximum framelength in counter ticks
#define timer_pause 300 * timer_correction_factor           //Pause between pluses in counter ticks
// Pin Definitions
#define led_PIN  7 //LED Status LED
#define armsw_PIN 5 // Arm switch pin
#define mode_PIN 4 //Trim enable switch
#define ppmout_PIN 10 // PPM output

//Mode ID
#define mode_trim 0
#define mode_serial 1
int mode=0;



//String Variable initialization
boolean stringComplete = false;  // whether the string is complete
char cmd_Char[26]="";
int inputString[4][26];         // a string to hold incoming data
int cmd_val[4];
int trim_val[4];
int inChar=0;

//Timer variables
int timer_accumulator = 0;         //accumulator. Used to calculate the frame padding
int timer_ptr = 0;                 //timer array pointer
int pulses[8];
int number_of_outputs =8;

int count=650;
int arm_stat =0;

void setup() {
  //Set Pinmodes
  pinMode(ppmout_PIN, OUTPUT);
  pinMode(armsw_PIN, INPUT);
  pinMode(led_PIN, OUTPUT);

  Serial.begin(115200); // Initialize Serial
  init_buffer(); //Initialize buffer
  
                      // Setup Timer
  TCCR1A = B00110001; // Compare register B used in mode '3'
  TCCR1B = B00010010; // WGM13 and CS11 set to 1
  TCCR1C = B00000000; // All set to 0
  TIMSK1 = B00000010; // Interrupt on compare B
  TIFR1  = B00000010; // Interrupt on compare B
  OCR1A = timer_framelength;
  OCR1B = timer_pause;    
}
// Main Loop will run at 50Hz
void loop() {
   sw_read(); // Read mode switch / arm switches
   serial_Event(); //Read String to buffer
  
   if(mode==mode_trim){ //Enter Trim Mode
    sw_readTrim();
    }
  else {// Serial Mode
    if (stringComplete) {//Execute if serial is received
    serial_Decode(); //Decode and copy the packet
    }
  }
  
  ppm_command(mode); //Set pulse values for PPM signal
  ppm_minmax(); //Constrain pulse values to the minimum and maximum
  sw_led();
  timer_loopcount(); //Counter for handshake
  
  //Always disable serial monitor before operating, only for development use
  //serial_monitor(); //For debugging through Serial Monitor
  serial_handshake();
  
  delay(20);
}
