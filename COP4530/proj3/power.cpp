#include <iostream>
#include <math.h>

using namespace std;

int main(){
	float temp = 5;
	for(int dec = 1; dec < 5; dec++){
		temp = temp+(temp/pow(10, dec));
		cout<<temp<<endl;
	}

	return 0;
}
