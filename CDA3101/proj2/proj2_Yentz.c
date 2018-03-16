#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct INSTRUCT{
	int instAddress;
	int instType;		//1=R, 2=I, 3=NOOP
	int instOP;
	int instRS;
	int instRT;
	int instRD;			//only R type
	int instShamt;		//only R type
	int instFunct;		//only R type
	int instImm;		//only I type
};

void printOP(int);
char *decimal_to_binary(int);
int ipow(int, int);

int main(){
	signed int machineInst[100];		//signed integer input
	char *binInst[100];					//binary conversion of input
	int size;							//number of inputs
	for(size=0; size<100; size++){
		scanf("%d", &machineInst[size]);
		if(machineInst[size]==1){
			break;
		}
	}

	struct INSTRUCT line[size];
	
	int i;
	int j;
	for(i=0; i<size; i++){
		binInst[i]=decimal_to_binary(machineInst[i]);
	}


//Test prints
/*	for(i=0; i<size; i++){
		printf("Machine Instruction %d: %d\n", i, machineInst[i]);
		printf("Binary Instruction %d:  %s\n\n", i, binInst[i]);
	}
*/

	int temp;
	for(i=0; i<size; i++){
		temp = 0;
		for(j=0; j<6; j++){
			//temp1 = *(binInst[i]+j)-48;
			temp += (*(binInst[i]+j)-48) * ipow(2, abs(j-5));
		}	
		line[i].instOP = temp;
		temp = 0;
		for(j=6; j<11; j++){
			temp += (*(binInst[i]+j)-48) * ipow(2, abs(j-10));
		}
		line[i].instRS = temp;
		temp = 0;
		for(j=11; j<16; j++){
			temp += (*(binInst[i]+j)-48) * ipow(2, abs(j-15));
		}
		line[i].instRT = temp;
		temp = 0;
		if(line[i].instOP==32||line[i].instOP==34||line[i].instOP==0){
			line[i].instType = 1;
			line[i].instImm = 999;
			for(j=16; j<21; j++){
				temp += (*(binInst[i]+j)-48) * ipow(2, abs(j-20));
			}
			line[i].instRD = temp;
			temp = 0;
			for(j=21; j<26; j++){
				temp += (*(binInst[i]+j)-48) * ipow(2, abs(j-26));
			}
			line[i].instShamt = temp;
			temp = 0;
			for(j=26; j<32; j++){
				temp += (*(binInst[i]+j)-48) * ipow(2, abs(j-31));
			}
			line[i].instFunct = temp;
			temp = 0;
		}
		else if(line[i].instOP==35||line[i].instOP==43||line[i].instOP==12||line[i].instOP==13||line[i].instOP==5){
			line[i].instType = 2;
			line[i].instRD = 999;
			line[i].instShamt = 999;
			line[i].instFunct = 999;
			for(j=16; j<32; j++){
				temp += (*(binInst[i]+j)-48) * ipow(2, abs(j-31));
			}
			line[i].instImm = temp;
			temp = 0;
		}
		line[i].instAddress = i*4;
	}

	for(i=0; i<size; i++){
		printf("Line[%d].instAddress: %d\n", i, line[i].instAddress);
		printf("Line[%d].instType:  %d\n", i, line[i].instType);
		printf("Line[%d].instOP:    %d\n", i, line[i].instOP);
		printf("Line[%d].instRS:    %d\n", i, line[i].instRS);
		printf("Line[%d].instRT:    %d\n", i, line[i].instRT);
		printf("Line[%d].instRD:    %d\n", i, line[i].instRD);
		printf("Line[%d].instShamt: %d\n", i, line[i].instShamt);
		printf("Line[%d].instFunct: %d\n", i, line[i].instFunct);
		printf("Line[%d].instImm:   %d\n", i, line[i].instImm);
		
		printOP(line[i].instOP);
	}

	return 0;
}

void printOP(int instOP){
	if(instOP==32){
		printf("add\n");
	}
	else if(instOP==34){
		printf("sub\n");
	}
	else if(instOP==35){
		printf("lw\n");
	}
	else if(instOP==43){
		printf("sw\n");
	}
	else if(instOP==0){
		printf("sll\n");
	}
	else if(instOP==12){
		printf("andi\n");
	}
	else if(instOP==13){
		printf("ori\n");
	}
	else if(instOP==5){
		printf("bne\n");
	}
	else{
		printf("ERROR!\n");
	}
}





char *decimal_to_binary(int n){
	int c, d, count;
	char *pointer;
 
	count = 0;
	pointer = (char*)malloc(32+1);
 
	if (pointer == NULL)
		exit(EXIT_FAILURE);
 
	for (c = 31 ; c >= 0 ; c--){
		d = n >> c;

		if (d & 1){
			*(pointer+count) = 1 + '0';
    	}  
		else{
			*(pointer+count) = 0 + '0';
 		}
		count++;
	}
	*(pointer+count) = '\0';
 
	return  pointer;
}

int ipow(int base, int exp){
    int result = 1;
    while (exp){
        if (exp & 1){
            result *= base;
		}
        exp >>= 1;
        base *= base;
    }
    return result;
}
