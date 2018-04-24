#include<stdlib.h>
#include<stdio.h>

int blockSize;
int numSets;
int ativity;
int numRef;
typedef struct line{
	char inst;
	int addr;
	
} line;

line lineArr[100];

void parse(){
	scanf("%d", &blockSize);
	scanf("%d", &numSets);
	scanf("%d\n", &ativity);
	for(numRef=0; numRef<100; numRef++){
		scanf("%c\t%d\n", &lineArr[numRef].inst, &lineArr[numRef].addr);
		if(lineArr[numRef].inst!='W' && lineArr[numRef].inst!='R'){
			break;
		}
	}
/*
	printf("numRef:   %d\n", numRef);
	int i;
	for(i=0; i< numRef; i++){
		printf("lineArr[%d].inst: %c\tlineArr[%d].addr: %d\n", i, lineArr[i].inst, i, lineArr[i].addr);
	}
*/	
};

void output(){
	printf("Block size: %d\n", blockSize);
	printf("Number of sets: %d\n", numSets);
	printf("Associativity: %d\n", ativity);
	printf("Number of offset bits: %d\n", 4);
	printf("Number of index bits: %d\n", 6);
	printf("Number of tag bits: %d\n", 22);
	printf("****************************************\n");
	printf("Write-through with No Write Allocate\n");
	printf("****************************************\n");
	printf("Total number of references: %d\n", numRef);
	printf("Hits: %d\n", 0);
	printf("Misses: %d\n", 0);
	printf("Memory References: %d\n", 0);
	printf("****************************************\n");
	printf("Write-back with Write Allocate\n");
	printf("****************************************\n");
	printf("Total number of references: %d\n", numRef);
	printf("Hits: %d\n", 0);
	printf("Misses: %d\n", 0);
	printf("Memory References: %d\n", 0);



};

int main(){
	blockSize = 0;
	numSets = 0;
	ativity = 0;
	parse();
	


	output();

	return 0;
}
