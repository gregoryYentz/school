#include<stdio.h>
#include<stdlib.h>
#include<string.h>
 
int main()
	{int n, c, k;
	char final[32];
	printf("Enter an integer in decimal number system\n");
	scanf("%d", &n);

	printf("%d in binary number system is:\n", n);

	char one[1];
	char zip[1]; 
	strcpy(one, "1");
	strcpy(zip, "0");

	for (c = 31; c >= 0; c--){
		k = n >> c;
 	
		if (k & 1){
			strcat(final, one);
		}
		else{
			strcat(final, zip);
		}
//		printf("Binary: %s", final);
	}
 
	printf("Binary: %s\n", final);
 
  return 0;
}
