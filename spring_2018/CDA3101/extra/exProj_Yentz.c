#include<stdio.h>
#include<stdlib.h>

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

int main(){
	char *mipsInst[100];
	int size;
	for(size=0; size<100; size++){
		scanf("%[^\n]%s", mipsInst[size]);
		if(mipsInst[size]==".data"){
			break;
		}
		printf("%s\n", mipsInst[size]);
	}
	struct INSTRUCT line[size];

	return 0;
}
