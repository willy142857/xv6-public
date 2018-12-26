#include "types.h"
#include "stat.h"
#include "user.h"

// Funtion to read characters from STDIN (1 byte at a time)

static void
getc(int fd, char ** buffer){
	int  i = 0;
	char buf[256];	// read input into buffer
	while(read(fd, &buf[i], 1)){
		if((buf[i] == '\n' || buf[i] == ' ' || buf[i] == '\t' || buf[i] == '\r' || buf[i] == '\v' || buf[i] == '\f')){
			break;
		}
		else{
			i++;
		}
	}
	buf[i] = '\0';
	*(buffer) = buf;
}

int atoi_decimal(char *buf){	
	int res = 0;  
	int sign = 1;  
	int i = 0;  // Initialize index of first digit
  
	if (buf[0] == '-'){	// If number is negative, then update sign
		sign = -1;  
		i++;  
	}
      	for (; buf[i] != '\0'; i++){
    		if(buf[i] - '0' < 0 || buf[i] - '0' > 9)  // If a non numeric character is found, break
    			break ;
        res = res*10 + buf[i] - '0';
    	}
	return sign*res;
}

// Function to convert Octal integer to a decimal integer
uint atoi_octal(char *buf, int start){   
	uint res = 0 ;
	int i = start ;

	for(; buf[i] != '\0' ; i++){
		if(buf[i] - '0' >= 0 && buf[i] - '0' <= 7)
			res = res*8 + buf[i] - '0' ;
		else
			return res ;
	}
	return res ;
}

int generalized_atoi(char *buf){          // atoi function for decimal, hexa and octal numbers 

	if(buf[0] != '0' )           // String is of a decimal integer
		return atoi_decimal(buf) ;

	else
		return atoi_octal(buf, 1) ;   // Octal number
}

// %c : character
// %d : signed integer
// %s : string
// %o : Octal number

void scanf(int fd, char * fmt, ...){
	int i = 0;
	char c;
	char * buf = "";	// holds the input temporarily
	int count_args = 1;
	uint var = *((uint*)(void*)&fmt + count_args);
	count_args++;
	for(i = 0; fmt[i]; i++){
		c = fmt[i] & 0xff;
		switch(c){
			case 'c':
				getc(fd, &buf);
				*(char *)(var) = buf[0];	// assign the variable with the character read into buffer
				buf = "";
				var = *((uint*)(void*)&fmt + count_args);
				count_args++;
				break;
			case 'd':
				getc(fd,&buf);
				*(int *)(var) = atoi_decimal(buf);	// convert to an integer and assign to the given variable
				buf = "";
				var = *((uint*)(void*)&fmt + count_args);
				count_args++;
				break;
			case 's':
				getc(fd, &buf);
				strcpy((char *)var, buf);		// copy the string in buffer to the given variable
				var = *((uint*)(void*)&fmt + count_args);
				count_args++;
				buf = "";	
				break;
			case 'o':
				getc(fd, &buf);
				*(uint *)(var) = atoi_octal(buf, 0);	// convert to an integer and assign to the given variable
				buf = "";
				var = *((uint*)(void*)&fmt + count_args);
				count_args++;
				break; 
		}
	}
}