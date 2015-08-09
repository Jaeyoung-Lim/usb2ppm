#include <stdio.h>
#include <tchar.h>
#include "SerialClass.h"	// Library described above
#include <string>
#include "usb2PPM.h"

// application reads from the specified serial port and reports the collected data

char* rtrn = NULL;

int _tmain(int argc, _TCHAR* argv[])
{
	printf("Serial Interface Application for USB2PPM\n");
	printf("Ver. 1.0.0\n");
	printf("Developed in Interactive / Network Robotics Lab, Seoul National University\n");
	printf("////////////////////////////////////////\n");
	Serial* SP = new Serial("\\\\.\\COM24");    // adjust as needed

	if (SP->IsConnected()) printf("Connection Verified\n");

	char incomingData[27] = "";			// don't forget to pre-allocate memory
	char outgoingData[27] = "";
	
	int dataLength = 26;
	int readResult = 0;
	int i=0;
	int ch1=650;
	int cnt = 0;
	int cnt_hz = 0;
	
	while (SP->IsConnected())
	{
		//readResult = SP->ReadData(incomingData, dataLength);
		//printf("Bytes read: (-1 means no data available) %i\n", readResult);
	
		strcpy_s(outgoingData, 26, encode_PPM(ch1+50, ch1, ch1+100, ch1+150));
		//printf("Incoming data : %s\n", incomingData);
		//SP->WriteData(outgoingData, dataLength);
		SP->WriteData(outgoingData, dataLength);
		//std::string test(incomingData);
		readResult = SP->ReadData(incomingData, dataLength);
		
		ch1 ++;
		

		free(rtrn);
		cnt++;
		printf("data : %s ", outgoingData);
		//printf("data : %d\n", sizeof(outgoingData));
		printf("loop count : %d ", cnt);
		//printf("count : %d ", cnt_hz);
		printf("handshake :%d ", readResult);
		printf("data : %s\n ", incomingData);
		if (cnt == 50){
			//printf("loop count : %d\t", cnt);
			//printf("count : %d\t", cnt_hz);
			//readResult = SP->ReadData(incomingData, dataLength);
			//printf("handshake :%d\n", readResult);
			
			cnt_hz++;
			cnt = 0; 
		}
		if (ch1 ==1023){
			ch1 = 0;
		}
		
	Sleep(20);
	}
	return 0;
}
