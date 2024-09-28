#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include <wiringPi.h>
#include <wiringSerial.h>

char device[] = "/dev/ttyACM0";
int fd;
int str_len;
int baud = 9600;

int main(){
	char *pArray[2] = {0};
	char ser_buf[100] = {0};
	int buf_idx = 0;
	char *pToken;
	int temp, humi;
	int flag = 0;

	printf("Start UP\n");
	if((fd = serialOpen(device, baud)) < 0)
		exit(1);
	if(wiringPiSetup() == -1)
		return -1;

	while(1){
//		printf("check1\n");
		ser_buf[buf_idx++] = serialGetchar(fd);
		if(ser_buf[buf_idx-1] == 'L'){
			ser_buf[buf_idx-1] = '\0';
//			printf("check2\n");
			str_len = strlen(ser_buf);
			printf("test ser_buf = %s, str_len = %d\n", ser_buf, str_len);
			pToken = strtok(ser_buf, ":");
			int i = 0;
			while(pToken != NULL){
				pArray[i] = pToken;
				if(++i > 3)
					break;
				pToken = strtok(NULL, " ");
			}
			humi = atoi(pArray[0]);
			temp = atoi(pArray[1]);
			printf("humi = %d, temp = %d\n", humi, temp);
			for(i = 0; i< str_len; i++)
					ser_buf[i] = 0;
			buf_idx = 0;
		}
	}
	return 0;
}
