#include<stdlib.h>
#include<stdio.h>

int blockSize;
int numSets;
int ativity;
int numOffsetBits;
int numIndexBits;
int numTagBits;
int numRef;
int WB_miss;
int WB_hit;
int WT_miss;
int WT_hit;


typedef struct line{
	char inst;
	int addr;
	int tag;
	int index;
	int offset;
	
} line;

line lineArr[100];

int ipow(int base, int exp){
	int result = 1;
	for (;;){
		if (exp & 1){
			result *= base;
		}
		exp >>= 1;
		if (!exp){
			break;
		}
		base *= base;
	}
	return result;
};

void parse(){
	scanf("%d", &blockSize);
	scanf("%d", &numSets);
	scanf("%d\n", &ativity);
	int temp = blockSize*4;
	numOffsetBits = 0;
	while(temp >>= 1) ++numOffsetBits;
	temp = numSets;
	numIndexBits = 0;
	while(temp >>= 1) ++numIndexBits;
	numTagBits = 32-numOffsetBits-numIndexBits;
	printf("%d %d %d\n", numTagBits, numIndexBits, numOffsetBits);
	for(numRef=0; numRef<100; numRef++){
		/*Fill Read/Write and Address values*/
		scanf("%c\t%d\n", &lineArr[numRef].inst, &lineArr[numRef].addr);
		if(lineArr[numRef].inst!='W' && lineArr[numRef].inst!='R'){
			break;
		}
		
		/*Fill Offset, Index, and Tag values*/		
		int i;
		int temp = lineArr[numRef].addr;
		lineArr[numRef].offset = 0;
		for(i = 0; i<numOffsetBits; i++){
			lineArr[numRef].offset += (temp%2) * ipow(2, i);
			temp = temp>>1;
		}
		lineArr[numRef].index = 0;
		for(i = 0; i<numIndexBits; i++){
			lineArr[numRef].index += (temp%2) * ipow(2, i);
			temp = temp>>1;
		}	
		lineArr[numRef].tag = 0;
		for(i = 0; i<numTagBits; i++){
			lineArr[numRef].tag += (temp%2) * ipow(2, i);
			temp = temp>>1;
		}
	}


	int j = 0;
	for(j=0; j<numRef; j++){
		int i = 0;
		for(i = 31; i >= 0; i--){
			if(i==(numOffsetBits-1) || i==(numIndexBits+numOffsetBits-1)){
				printf(" ");
			}
			if((lineArr[j].addr & (1 << i)) != 0){
				printf("1");
			}
			else{
				printf("0");
			}
		}
		printf(" %c\t%d\t%d\t%d\n", lineArr[j].inst, lineArr[j].tag, lineArr[j].index, lineArr[j].offset);
	}	

};

void buildCache(){
	int tagArr[numSets][ativity];
	int cacheArr[numSets][ativity];
	int i, j;
	for(i=0; i<numSets; i++){
		for(j=0; j<ativity; j++){
			tagArr[i][j] = 0;
			cacheArr[i][j] = 0;
		}
	}
	int k;
	for(i=0; i<numRef; i++){
		for(j=0; j<ativity; j++){
			int match = 0;
			for(k=0; k<j; k++){
				if(tagArr[lineArr[i].index][k]==lineArr[i].tag){
					match = 1;
				}
			}
			/*
			if(tagArr[lineArr[i].index][j]==0 && match==0 && lineArr[i].inst=='W'){
				tagArr[lineArr[i].index][j]=lineArr[i].tag;
				cacheArr[lineArr[i].index][j]=lineArr[i].tag;
			}
			else if(match==1 && lineArr[i].inst=='R'){
				WT_hit++;
			}
			WT_miss=numRef-WT_hit;
			*/
			if(match==1 && lineArr[i].inst=='R'){
				WT_hit++;
				//tagArr[lineArr[i].index][j] = lineArr[i].tag;
				//cacheArr[lineArr[i].index][j] = lineArr[i].tag;
			}
			else if(match==1 && lineArr[i].inst=='W'){
				WT_hit++;
				tagArr[lineArr[i].index][j] = lineArr[i].tag;
				cacheArr[lineArr[i].index][j] = lineArr[i].tag;
			}
			else if(match==0 && lineArr[i].inst=='R'){
				WT_miss++;
				tagArr[lineArr[i].index][j] = lineArr[i].tag;
				cacheArr[lineArr[i].index][j] = lineArr[i].tag;
			}
			else if(match==0 && lineArr[i].inst=='W'){
				WT_miss++;
				
			}
		}
	}


	for(i=0; i<numSets; i++){
		printf("%d\t", i);
		for(j=0; j<ativity; j++){
			printf("%d\t", tagArr[i][j]);
		}
		printf("\n");
	}

};

void output(){
	printf("Block size: %d\n", blockSize);
	printf("Number of sets: %d\n", numSets);
	printf("Associativity: %d\n", ativity);
	printf("Number of offset bits: %d\n", numOffsetBits);
	printf("Number of index bits: %d\n", numIndexBits);
	printf("Number of tag bits: %d\n", numTagBits);
	printf("****************************************\n");
	printf("Write-through with No Write Allocate\n");
	printf("****************************************\n");
	printf("Total number of references: %d\n", numRef);
	printf("Hits: %d\n", WT_hit);
	printf("Misses: %d\n", WT_miss);
	printf("Memory References: %d\n", numRef);
	printf("****************************************\n");
	printf("Write-back with Write Allocate\n");
	printf("****************************************\n");
	printf("Total number of references: %d\n", numRef);
	printf("Hits: %d\n", WB_hit);
	printf("Misses: %d\n", WB_miss);
	printf("Memory References: %d\n", 0);
};

int main(){
	blockSize = 0;
	numSets = 0;
	ativity = 0;
	WT_hit=0;
	WT_miss=0;
	WB_hit=0;
	WB_miss=0;
	parse();
	buildCache();
	

	output();

	return 0;
}
