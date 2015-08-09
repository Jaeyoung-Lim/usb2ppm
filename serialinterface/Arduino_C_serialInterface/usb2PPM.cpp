#include "usb2PPM.h"

char* encode_PPM(int cmd_ch1, int cmd_ch2, int cmd_ch3, int cmd_ch4){
	
	int cmd_ch[4] = { 0, 0, 0, 0}; //Default values for each channels
	char output_string[26]="\0";
	char* output_string_p = output_string;
	rtrn = (char*)malloc(26);

	char const_ch[4] = { 'x','y', 'z', 'k' };

	cmd_ch[0] = cmd_ch1;
	cmd_ch[1] = cmd_ch2;
	cmd_ch[2] = cmd_ch3;
	cmd_ch[3] = cmd_ch4;
	
	int j = 0;
	
	//for loop for each channel value processing
	for (int i = 0; i < 4; i++){
		//Set maximum values
		if (cmd_ch[i] > 1023){
			cmd_ch[i] = 1023;
		}
		else if (cmd_ch[i] < 1){
			cmd_ch[i] = 0;
		}		
		char cmd_ch_s[5]="";
		char* cmd_ch_sp = cmd_ch_s;

		_itoa_s(cmd_ch[i], cmd_ch_s, 10);


		
		//convert to single string for communication with Arduino

		*(output_string_p + j) = const_ch[i];
		j++;
		while (*(output_string_p + j) = *(cmd_ch_sp++))
		{
			j++;
		}
		
	}
	//printf("string :%s\n", output_string);
	strcpy_s(rtrn,25, output_string);
	return rtrn;
}