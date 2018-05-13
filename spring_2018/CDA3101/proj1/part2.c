/*
Gregory Yentz
gcy16
01/09/2018

this program reads in a mips program (.asm) from the standard input.
the first parsing recognizes labels and stores the instruction address found.
the second parsing converts all other mips code to decimal, then to hex.

this is a work-in-progress and not a completed assignment.
please be nice. it was hard.

*/

#include<stdlib.h>
#include<stdio.h>
#include<string.h>

int registerAddress(char, char);				
int labelAddress(char[100][32], char[]);		
void printHex();								

/*
void ADD();
void ADDI();
void NOR();
void ORI();
void SLL();
void LUI();
void SW();
void LW();
void BNE();
*/
void J(char[100][32], char[]);
//void LA();

int main(){
	char instructions[200][100];
	char labels[100][32];
	int lineCount;
	int i,j,k;


/*
----------
First Pass
---------
*/
	for(i=0;i<200;i++){
		for(j=0;j<100;j++){
			scanf("%c", &instructions[i][j]);	/*store character into instruction array*/

/*Find Labels*/
			if(instructions[i][j]==':'){
				for(k=0;k<j;k++){
					labels[i][k]=instructions[i][k];
				}
			}

/*NewLine, also searchs for .text and .data to ignore for lineCount, and works the psuedoinstruction for LA*/
			if(instructions[i][j]=='\n'){
				if(strcmp(instructions[i],"\t.text\n")==0||(strcmp(instructions[i],"\t.data\n")==0)){
					strcpy(instructions[i],"\0");
					--i;	
					break;
				}
				for(k=0;k<j;k++){
					if(instructions[i][k]=='l'){
						if(instructions[i][k+1]=='a'){
							if(instructions[i][k+2]=='\t'){
								int l;
								int m=0;
								char reg[2]={instructions[i][k+4],instructions[i][k+5]};
								char mem[32];
								for(l=k+7;l<j;l++){
									mem[m]=instructions[i][l];
									m=m+1;
								}
								strcpy(instructions[i],"\tlui\t$1,");
								strcat(instructions[i],mem);
								strcat(instructions[i],"[31-16]\n");
								i=i+1;
								strcpy(instructions[i],"\tori\t$");
								strcat(instructions[i],reg);
								strcat(instructions[i],",$1,");
								strcat(instructions[i],mem);
								strcat(instructions[i],"[15-0]\n");
							}
						}
					}
				}
				break;
			}
			if(instructions[i][j]=='\0'){
				lineCount=i;
				i=200;
				break;
			}		
		}
	}

/*prints the file with the LA conversion to LUI and SLL, without the .text and.data lines*/

	for(i=0;i<lineCount;i++){
		printf("%d:\t%s",i*4,instructions[i]);
	}

/*prints the lineCount, exluding the .text and .data lines*/
	printf("%d\n", lineCount);


/*Prints the labels and the decimal addresses*/
	for(i=0;i<lineCount;i++){
		if(labels[i][0]!='\0'){
			printf("%s:\t%d\n", labels[i], i*4);
		}
	}
	
/*---------------------
*SECOND PASS*-----------
*/
	
	for(i=0;i<lineCount;i++){
		for(j=0;j<100;j++){
			if(instructions[i][j]=='\n'){
				break;
			}
/*exchanges register names with decimal representations*/
			if(instructions[i][j]=='$'){
				int regAddr;
				char a = instructions[i][j+1];
				char b = instructions[i][j+2];
				regAddr = registerAddress(a, b);
				printf("%d\t", regAddr);
			}

/*searches the instruction line for what instruction is being used. only have jump working for now*/
			char temp[4];
            char tempJ[2];
			tempJ[0]=instructions[i][j];
                        tempJ[1]=instructions[i][j+1];

                        temp[0]=instructions[i][j];
                        temp[1]=instructions[i][j+1];
                        temp[2]=instructions[i][j+2];
                        temp[3]=instructions[i][j+3];
/*
                        if(strcmp(temp, "add\t")==0){
                                ADD();
                        }
                        if(strcmp(temp, "addi")==0){
                                ADDI();
                        }
                        if(strcmp(temp, "nor\t")==0){
                                NOR();
                        }
                        if(strcmp(temp, "ori\t")==0){
                                ORI();
                        }
                        if(strcmp(temp, "sll\t")==0){
                                SLL();
                        }
                        if(strcmp(temp, "lui\t")==0){
                                LUI();
                        }
                        if(strcmp(temp, "sw\t$")==0){
                                SW();
                        }
                        if(strcmp(temp, "lw\t$")==0){
                                LW();
                        }
                        if(strcmp(temp, "bne\t")==0){
                                BNE();
                        }
*/
                        if(strcmp(tempJ, "j\t")==0){
                                J(labels, instructions[i]);
                        }
/*                        if(strcmp(temp, "la\t$")==0){
                                LA();
                        }
*/






/*
			if(instructions[i][j]==':'){
				int labAddr;
				labAddr = labelAddress(labels,instructions[i],j);	
				printf("%d\t", labAddr);		
			}*/
		}
		printf("\n");
	}
	return 0;
}


/*inputs are the label list and the current instruction line. Searches the instruction line for a match with one of the labels in the list, returns the position of the label matched*/
int labelAddress(char label[100][32],char instruction[]){
	int i;
	int k;
	int match = 0;
	for(i=0;i<100;i++){
		char temp[32];
		strcpy(temp, label[i]);
	//	strcat(temp, "\n");
		printf("%d\t%s\t%s\n", i, instruction, temp);
	/*	if(strstr(temp, instruction)){
			return i;
		}*/
		for(k=0;k<32;k++){
			if(temp[k]==instruction[k+3]){
				match=1;
			}
		}
		if(match==1){
			return i;
		}
	}
};


/*inputs are the characters right after a $, returns the decimal representation of the register address*/
int registerAddress(char lett, char numm){
	if(lett=='t'){
		int i;
		for(i='0';i<'8';i++){
			if(numm==i){
				return i-40;
			}
		}
	}
	if(lett=='s'){
		int i;
		for(i='0';i<'8';i++){
			if(numm==i){
				return i-32;
			}
		}
	}
	if(lett=='0'){
		return 0;
	}
	if(lett=='1'){
		return 1;
	}
};

/*works the J jump instruction. prints the decimal opcode with the address of the label being jumped to.*/
void J(char label[100][32], char instruction[]){
	int addr = labelAddress(label, instruction);
	printf("2 %d", addr);


};
