#include<stdio.h>
#include<stdlib.h>

struct INSTRUCT{
	int instAddress;
	int instType;		//0=HALT, 1=R, 2=I, 3=NOOP
	int instOP;
	int instRS;
	int instRT;
	int instRD;			//only R type
	int instShamt;		//only R type
	int instFunct;		//only R type
	int instImm;		//only I type
};

int PC = 0;
int dataMem[32];
int regFile[32];

struct IF_ID_{
	int PCPlus4;
};

struct ID_EX_{
	int PCPlus4;
	int branchTarget;
	int readData1;
	int readData2;
	int immed;
	int rs;
	int rt;
	int rd;
};

struct EX_MEM_{
	int aluResult;
	int writeDataReg;
	int writeReg;
};

struct MEM_WB_{
	int writeDataMem;
	int writeDataALU;
	int writeReg;
};

struct processorState{
	struct IF_ID_ IF_ID;
	struct ID_EX_ ID_EX;
	struct EX_MEM_ EX_MEM;
	struct MEM_WB_ MEM_WB;	
};

struct branchPredictor{
	int PC;
	int branchTarget;
	int state;	
};

void nextState(struct processorState *lastState, struct processorState *currentState, struct INSTRUCT line[], int i, int size);

void printOP(struct INSTRUCT line[], int i);
char *decimal_to_binary(int);
int ipow(int, int);
void intoReg(int);

void printOutput(struct processorState *currentState, int i, struct INSTRUCT line[]);

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

	struct INSTRUCT line[size+8];		//3 NOOPs, size Instructions, HALT, 3 NOOPs

	int i;
	int j;
	int temp;

	for(i=-1; i<size; i++){		//fill the INSTRUCT structure with the parsed data from input
		if(machineInst[i]!=0){
			binInst[i]=decimal_to_binary(machineInst[i]);
			
			//fill instOP
			for(j=0; j<6; j++){
				temp += (*(binInst[i]+j)-48) * ipow(2, abs(j-5));
			}	
			line[i+4].instOP = temp;
			temp = 0;

			//fill instRS
			for(j=6; j<11; j++){
				temp += (*(binInst[i]+j)-48) * ipow(2, abs(j-10));
			}
			line[i+4].instRS = temp;
			temp = 0;

			//fill instRT
			for(j=11; j<16; j++){
				temp += (*(binInst[i]+j)-48) * ipow(2, abs(j-15));
			}
			line[i+4].instRT = temp;
			temp = 0;

			//R Types
			if(line[i+4].instOP==32||line[i+4].instOP==34||line[i+4].instOP==0){
				line[i+4].instType = 1;
			}
			//I Types

			else if(line[i+4].instOP==35||line[i+4].instOP==43||line[i+4].instOP==12||line[i+4].instOP==13||line[i+4].instOP==5){
				line[i+4].instType = 2;
				line[i+4].instRD = 0;
				line[i+4].instShamt = 0;
				line[i+4].instFunct = 0;
			}

				//fill instRD
				for(j=16; j<21; j++){
					temp += (*(binInst[i]+j)-48) * ipow(2, abs(j-20));
				}
				line[i+4].instRD = temp;
				temp = 0;

				//fill instShamt
				for(j=21; j<26; j++){
					temp += (*(binInst[i]+j)-48) * ipow(2, abs(j-25));
				}
				line[i+4].instShamt = temp;
				temp = 0;

				//fill instFunct
				for(j=26; j<32; j++){
					temp += (*(binInst[i]+j)-48) * ipow(2, abs(j-31));
				}
				line[i+4].instFunct = temp;
				temp = 0;

			

				//fill instImm
				for(j=16; j<32; j++){
					temp += (*(binInst[i]+j)-48) * ipow(2, abs(j-31));
				}
				line[i+4].instImm = temp;
				temp = 0;

			//fill instAddress
			line[i+4].instAddress = (i+1)*4;
		}
		else{
			line[i+4].instType = 3;
			line[i+4].instOP = 0;
			line[i+4].instRS = 0;
			line[i+4].instRT = 0;
			line[i+4].instRD = 0;
			line[i+4].instShamt = 0;
			line[i+4].instFunct = 0;
			line[i+4].instImm = 0;
		}
	}

	//Used for ID/EX, EX/MEM, MEM/WB for first real instruction IF/ID
	for(i=0; i<4; i++){
		line[i].instAddress = 0;
		line[i].instType = 3;
		line[i].instOP = 0;
		line[i].instRS = 0;
		line[i].instRT = 0;
		line[i].instRD = 0;
		line[i].instShamt = 0;
		line[i].instFunct = 0;
		line[i].instImm = 0;
	}

	line[size+4].instAddress = i*4;
	line[size+4].instType = 0;
	line[size+4].instOP = 1;
	line[size+4].instRS = 0;
	line[size+4].instRT = 0;
	line[size+4].instRD = 0;
	line[size+4].instShamt = 0;
	line[size+4].instFunct = 0;
	line[size+4].instImm = 1;

	for(i=size+5; i<size+8; i++){
		line[i].instAddress = 0;
		line[i].instType = 3;
		line[i].instOP = 0;
		line[i].instRS = 0;
		line[i].instRT = 0;
		line[i].instRD = 0;
		line[i].instShamt = 0;
		line[i].instFunct = 0;
		line[i].instImm = 0;
	}

	//initialize structures and fill default variables
	for(i=0; i<32; i++){
		dataMem[i] = 0;
		regFile[i] = 0;
	}

	for(i=0; i<32; i++){
		scanf("%d", &dataMem[i]);
	}

	struct processorState lastState;
		lastState.IF_ID.PCPlus4 = 0;
		lastState.ID_EX.PCPlus4 = 0;
		lastState.ID_EX.branchTarget = 0;
		lastState.ID_EX.readData1 = 0;
		lastState.ID_EX.readData2 = 0;
		lastState.ID_EX.immed = 0;
		lastState.ID_EX.rs = 0;
		lastState.ID_EX.rt = 0;
		lastState.ID_EX.rd = 0;
		lastState.EX_MEM.aluResult = 0;
		lastState.EX_MEM.writeDataReg = 0;
		lastState.EX_MEM.writeReg = 0;
		lastState.MEM_WB.writeDataMem = 0;
		lastState.MEM_WB.writeDataALU = 0;
		lastState.MEM_WB.writeReg = 0;

	struct processorState currentState;
		currentState.IF_ID.PCPlus4 = 0;
		currentState.ID_EX.PCPlus4 = 0;
		currentState.ID_EX.branchTarget = 0;
		currentState.ID_EX.readData1 = 0;
		currentState.ID_EX.readData2 = 0;
		currentState.ID_EX.immed = 0;
		currentState.ID_EX.rs = 0;
		currentState.ID_EX.rt = 0;
		currentState.ID_EX.rd = 0;
		currentState.EX_MEM.aluResult = 0;
		currentState.EX_MEM.writeDataReg = 0;
		currentState.EX_MEM.writeReg = 0;
		currentState.MEM_WB.writeDataMem = 0;
		currentState.MEM_WB.writeDataALU = 0;
		currentState.MEM_WB.writeReg = 0;



	for(i=3; i<size+8; i++){
		nextState(&lastState, &currentState, line, i, size);
		printOutput(&currentState, i, line);
	}

	return 0;
}

void nextState(struct processorState *lastState, struct processorState *currentState, struct INSTRUCT line[], int i, int size){


	currentState->IF_ID.PCPlus4 = PC;
	currentState->ID_EX.PCPlus4 = lastState->IF_ID.PCPlus4;
	currentState->ID_EX.branchTarget = 0;
	currentState->ID_EX.readData1 = 0;
	currentState->ID_EX.readData2 = 0;
	currentState->ID_EX.immed = line[i-1].instImm;
	currentState->ID_EX.rs = line[i-1].instRS;
	currentState->ID_EX.rt = line[i-1].instRT;
	currentState->ID_EX.rd = line[i-1].instRD;
	currentState->EX_MEM.aluResult = 0;
	currentState->EX_MEM.writeDataReg = 0;
	currentState->EX_MEM.writeReg = 0;
	currentState->MEM_WB.writeDataMem = 0;
	currentState->MEM_WB.writeDataALU = lastState->EX_MEM.aluResult;
	currentState->MEM_WB.writeReg = lastState->EX_MEM.writeReg;


	//ID_EX
		if(line[i-1].instType==1){
			currentState->ID_EX.readData1 = regFile[line[i-1].instRS];
			currentState->ID_EX.readData2 = regFile[line[i-1].instRT];
		}

	//Data Hazard
	if(currentState->ID_EX.readData1 == lastState->EX_MEM.writeReg || currentState->ID_EX.readData2 == lastState->EX_MEM.writeReg){
		//callDataHazardFunct();


	}



	//EX_MEM		
		//ADD
		if(line[i-2].instOP==0 && line[i-2].instFunct==32){
			currentState->EX_MEM.aluResult = regFile[line[i-2].instRS] + regFile[line[i-2].instRT];
			currentState->EX_MEM.writeReg = line[i-2].instRD;
		}

		//SUB
		else if(line[i-2].instOP==0 && line[i-2].instFunct==34){
			currentState->EX_MEM.aluResult = regFile[line[i-2].instRS] - regFile[line[i-2].instRT];
			currentState->EX_MEM.writeReg = line[i-2].instRD;
		}

		//SLL
		else if(line[i-2].instOP==0 && line[i-2].instFunct==0){
			currentState->EX_MEM.aluResult = regFile[line[i-2].instRT] << line[i-2].instShamt;
			currentState->EX_MEM.writeReg = line[i-2].instRD;
		}

		//ANDI
		else if(line[i-2].instOP==12){
			currentState->EX_MEM.aluResult = regFile[line[i-2].instRS] & line[i-2].instImm;
			currentState->EX_MEM.writeReg = line[i-2].instRT;
		}

		//ORI
		else if(line[i-2].instOP==13){
			currentState->EX_MEM.aluResult = regFile[line[i-2].instRS] | line[i-2].instImm;
			currentState->EX_MEM.writeReg = line[i-2].instRT;
		}

		//LW
		else if(line[i-2].instOP==35){
			currentState->EX_MEM.aluResult = line[i-2].instRS + line[i-2].instImm;
			currentState->EX_MEM.writeReg = line[i-2].instRT;
		}

		//SW
		else if(line[i-2].instOP==43){
			currentState->EX_MEM.aluResult = regFile[line[i-2].instRS] + line[i-2].instImm/4;
			currentState->EX_MEM.writeDataReg = regFile[line[i-2].instRT];
			//currentState->EX_MEM.writeReg = line[i-2].instRT;
		}

	//MEM_WB
		//LW
		if(line[i-3].instOP==35){
			currentState->MEM_WB.writeDataMem = dataMem[regFile[line[i-3].instRS] + (line[i-3].instImm/4) - ((size+1)*4)];
			//printf("\n%d\n%d\n%d\n", regFile[line[i-3].instRS], (line[i-3].instImm/4), ((size+1)*4));
		}

		//SW
		else if(line[i-3].instOP==43){
			dataMem[regFile[line[i-3].instRS] + (line[i-3].instImm/4) - ((size+1)*4)] = regFile[line[i-3].instRT];
			//printf("\n%d\n%d\n%d", regFile[line[i-3].instRT], regFile[line[i-3].instRS], (line[i-3].instImm/4));
		}	


	//Reg Update
		//ADD
		if(line[i-4].instOP==0 && line[i-4].instFunct==32){
			regFile[line[i-4].instRD] = regFile[line[i-4].instRS] + regFile[line[i-4].instRT];
		}

		//SUB
		else if(line[i-4].instOP==0 && line[i-4].instFunct==34){
			regFile[line[i-4].instRD] = regFile[line[i-4].instRS] - regFile[line[i-4].instRT];
		}

		//SLL
		else if(line[i-4].instOP==0 && line[i-4].instFunct==0){
			regFile[line[i-4].instRD] = regFile[line[i-4].instRT] << line[i-4].instShamt;
		}

		//ANDI
		else if(line[i-4].instOP==12){
			regFile[line[i-4].instRT] = regFile[line[i-4].instRS] & line[i-4].instImm;
		}

		//ORI
		else if(line[i-4].instOP==13){
			regFile[line[i-4].instRT] = regFile[line[i-4].instRS] | line[i-4].instImm;
		}

		//LW
		else if(line[i-4].instOP==35){
			regFile[line[i-4].instRT] = dataMem[regFile[line[i-4].instRS] + (line[i-4].instImm/4) - ((size+1)*4)];
		}


	PC=PC+4;

	lastState->IF_ID.PCPlus4 = currentState->IF_ID.PCPlus4;
	lastState->ID_EX.PCPlus4 = currentState->ID_EX.PCPlus4;
	lastState->ID_EX.branchTarget = currentState->ID_EX.branchTarget;
	lastState->ID_EX.readData1 = currentState->ID_EX.readData1;
	lastState->ID_EX.readData2 = currentState->ID_EX.readData2;
	lastState->ID_EX.immed = currentState->ID_EX.immed;
	lastState->ID_EX.rs = currentState->ID_EX.rs;
	lastState->ID_EX.rt = currentState->ID_EX.rt;
	lastState->ID_EX.rd = currentState->ID_EX.rd;
	lastState->EX_MEM.aluResult = currentState->EX_MEM.aluResult;
	lastState->EX_MEM.writeDataReg = currentState->EX_MEM.writeDataReg;
	lastState->EX_MEM.writeReg = currentState->EX_MEM.writeReg;
	lastState->MEM_WB.writeDataMem = currentState->MEM_WB.writeDataMem;
	lastState->MEM_WB.writeDataALU = currentState->MEM_WB.writeDataALU;
	lastState->MEM_WB.writeReg = currentState->MEM_WB.writeReg;
}

//converts the decimal input to a binary string
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

//power function for integers; used in binary string to integer conversion
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

void intoReg(int reg){
	if(reg==2 || reg==3){
		printf("v%d\n", reg-2);
	}
	else if(reg>=4 && reg<=7){
		printf("a%d\n", reg-4);
	}
	else if(reg>=8 && reg<=15){
		printf("t%d\n", reg-8);
	}
	else if(reg>=16 && reg<=23){
		printf("s%d\n", reg-16);
	}
	else if(reg==24 || reg==25){
		printf("t%d\n", reg-16);
	}
	else{
		printf("0\n");
	}
}

void printOutput(struct processorState *currentState, int i, struct INSTRUCT line[]){
	printf("********************\n");
	printf("State at the beginning of cycle %d:\n", i-2);
	printf("\tPC = %d\n", currentState->IF_ID.PCPlus4);
	printf("\tData Memory:\n");
	printf("\t\tdataMem[0] = %d\t\tdataMem[16] = %d\n", dataMem[0], dataMem[16]);
	printf("\t\tdataMem[1] = %d\t\tdataMem[17] = %d\n", dataMem[1], dataMem[17]);
	printf("\t\tdataMem[2] = %d\t\tdataMem[18] = %d\n", dataMem[2], dataMem[18]);
	printf("\t\tdataMem[3] = %d\t\tdataMem[19] = %d\n", dataMem[3], dataMem[19]);
	printf("\t\tdataMem[4] = %d\t\tdataMem[20] = %d\n", dataMem[4], dataMem[20]);
	printf("\t\tdataMem[5] = %d\t\tdataMem[21] = %d\n", dataMem[5], dataMem[21]);
	printf("\t\tdataMem[6] = %d\t\tdataMem[22] = %d\n", dataMem[6], dataMem[22]);
	printf("\t\tdataMem[7] = %d\t\tdataMem[23] = %d\n", dataMem[7], dataMem[23]);
	printf("\t\tdataMem[8] = %d\t\tdataMem[24] = %d\n", dataMem[8], dataMem[24]);
	printf("\t\tdataMem[9] = %d\t\tdataMem[25] = %d\n", dataMem[9], dataMem[25]);
	printf("\t\tdataMem[10] = %d \tdataMem[26] = %d\n", dataMem[10], dataMem[26]);
	printf("\t\tdataMem[11] = %d \tdataMem[27] = %d\n", dataMem[11], dataMem[27]);
	printf("\t\tdataMem[12] = %d \tdataMem[28] = %d\n", dataMem[12], dataMem[28]);
	printf("\t\tdataMem[13] = %d \tdataMem[29] = %d\n", dataMem[13], dataMem[29]);
	printf("\t\tdataMem[14] = %d \tdataMem[30] = %d\n", dataMem[14], dataMem[30]);
	printf("\t\tdataMem[15] = %d \tdataMem[31] = %d\n", dataMem[15], dataMem[31]);
	printf("\tRegisters:\n");
	printf("\t\tregFile[0] = %d\t\tregFile[16] = %d\n", regFile[0], regFile[16]);	
	printf("\t\tregFile[1] = %d\t\tregFile[17] = %d\n", regFile[1], regFile[17]);
	printf("\t\tregFile[2] = %d\t\tregFile[18] = %d\n", regFile[2], regFile[18]);
	printf("\t\tregFile[3] = %d\t\tregFile[19] = %d\n", regFile[3], regFile[19]);
	printf("\t\tregFile[4] = %d\t\tregFile[20] = %d\n", regFile[4], regFile[20]);
	printf("\t\tregFile[5] = %d\t\tregFile[21] = %d\n", regFile[5], regFile[21]);
	printf("\t\tregFile[6] = %d\t\tregFile[22] = %d\n", regFile[6], regFile[22]);
	printf("\t\tregFile[7] = %d\t\tregFile[23] = %d\n", regFile[7], regFile[23]);
	printf("\t\tregFile[8] = %d\t\tregFile[24] = %d\n", regFile[8], regFile[24]);
	printf("\t\tregFile[9] = %d\t\tregFile[25] = %d\n", regFile[9], regFile[25]);
	printf("\t\tregFile[10] = %d \tregFile[26] = %d\n", regFile[10], regFile[26]);
	printf("\t\tregFile[11] = %d \tregFile[27] = %d\n", regFile[11], regFile[27]);
	printf("\t\tregFile[12] = %d \tregFile[28] = %d\n", regFile[12], regFile[28]);
	printf("\t\tregFile[13] = %d \tregFile[29] = %d\n", regFile[13], regFile[29]);
	printf("\t\tregFile[14] = %d \tregFile[30] = %d\n", regFile[14], regFile[30]);
	printf("\t\tregFile[15] = %d \tregFile[31] = %d\n", regFile[15], regFile[31]);
	printf("\tIF/ID:\n");
	printf("\t\tInstruction: ");
	printOP(line, i);
	printf("\t\tPCPlus4: %d\n", currentState->IF_ID.PCPlus4);
	printf("\tID/EX:\n");
	printf("\t\tInstruction: ");
	printOP(line, i-1);
	printf("\t\tPCPlus4: %d\n", currentState->ID_EX.PCPlus4);
	printf("\t\tbranchTarget: %d\n", currentState->ID_EX.branchTarget);
	printf("\t\treadData1: %d\n", currentState->ID_EX.readData1);
	printf("\t\treadData2: %d\n", currentState->ID_EX.readData2);
	printf("\t\timmed: %d\n", currentState->ID_EX.immed);
	printf("\t\trs: ");
	intoReg(currentState->ID_EX.rs);
	printf("\t\trt: ");
	intoReg(currentState->ID_EX.rt);
	printf("\t\trd: ");
	intoReg(currentState->ID_EX.rd);
	printf("\tEX/MEM:\n");
	printf("\t\tInstruction: ");
	printOP(line, i-2);
	printf("\t\taluResult: %d\n", currentState->EX_MEM.aluResult);
	printf("\t\twriteDataReg: %d\n", currentState->EX_MEM.writeDataReg);
	printf("\t\twriteReg: ");
	intoReg(currentState->EX_MEM.writeReg);
	printf("\tMEM/WB:\n");
	printf("\t\tInstruction: ");
	printOP(line, i-3);
	printf("\t\twriteDataMem: %d\n", currentState->MEM_WB.writeDataMem);
	printf("\t\twriteDataALU: %d\n", currentState->MEM_WB.writeDataALU);
	printf("\t\twriteReg: ");
	intoReg(currentState->MEM_WB.writeReg);
}

void printOP(struct INSTRUCT line[], int i){
	if(line[i].instOP==35){
		printf("lw\n");
	}
	else if(line[i].instType==0){
		printf("HALT\n");
	}
	else if(line[i].instType==3){
		printf("NOOP\n");
	}
	else if(line[i].instOP==43){
		printf("sw\n");
	}
	else if(line[i].instOP==0){
		if(line[i].instFunct==32){
			printf("add\n");
		}
		else if(line[i].instFunct==34){
			printf("sub\n");
		}
		else if(line[i].instFunct==0){
			printf("sll\n");
		}
	}
	else if(line[i].instOP==12){
		printf("andi\n");
	}
	else if(line[i].instOP==13){
		printf("ori\n");
	}
	else if(line[i].instOP==5){
		printf("bne\n");
	}
	
	else{
		printf("ERROR!\n");
	}
}