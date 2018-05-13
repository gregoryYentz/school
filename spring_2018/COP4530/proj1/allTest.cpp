/*
Gregory Yentz

This program reads text from the user and produces the count and top 10 of the
characters, words, and numbers given.

Expect a 10-20 second run-time for files similar in size to test3 (1.63 MBs)

*/
#include<iostream>
#include<vector>

using namespace std;

class getMost{
	private:
		//charVect holds the count of each character in each index corresponding with the ascii value
		vector<int> charVect;
		//charCount holds the total number of different ascii values read in
		int charCount;

		//wordVect[0][0] will be the total number of different words, wordVect[i][0] will be the number of instances for each individual word
		//wordVect[i][1->n] will hold each ascii value for the each word. 
		vector<vector<unsigned int> > wordVect;
		vector<unsigned int> wordCount;
		vector<unsigned int> wordTemp;
		//numVect is made in the same structure of wordVect
		vector<vector<unsigned int> > numVect;
		vector<unsigned int> numCount;
		vector<unsigned int> numTemp;

		//i is the current ascii value read in
		char i;
	public:
		//getMost constructor sets the structure of the vectors as explained above
		getMost(){
			charVect.resize(128);
			charCount = 0;
		
			wordVect.resize(1);
			wordCount.resize(1);
			wordCount[0] = 0;
			wordVect[0] = wordCount;
			wordTemp.resize(1);
			wordTemp[0]=1;

			numVect.resize(1);
			numCount.resize(1);
			numCount[0] = 0;
			numVect[0] = numCount;
			numTemp.resize(1);
			numTemp[0] = 1;
		}

		//reads in each character, calling a different set of functions dependend on the ascii type
		void parseList(){
			while(cin.get(i)){
				if((i >= 48) && (i <= 57)){
					numList();
					charList();
				}
				else{
					charList();
				}
			}
		};

		//fills the charVect with any ascii value and iterates charCount if its the first time seeing i's ascii value
		//calls wordList() if the ascii value is a letter
		void charList(){
			int a = charVect[i];
			charVect[int(i)]++;
			if(a==0){
				charCount++;
			}
			if(((i >= 65) && (i <= 90)) || ((i >= 97) && (i <= 122))){
				wordList();
			}
		};

		//fills the wordVect
		void wordList(){
			if((i >= 65) && (i <= 90)){
                i = i+32;
                wordTemp.push_back (i);
            }
			else{  
				wordTemp.push_back (i);
            }
            if((cin.peek() < 65) || ((cin.peek() > 90) && (cin.peek() < 97)) || (cin.peek() > 122)){
                bool match = false;
                unsigned int matchIndex;
                for(unsigned int a = 1; a < wordVect.size(); a++){
                    if(wordVect[a].size()==wordTemp.size()){
                        for(unsigned int b = 1; b < wordTemp.size(); b++){
                            if(wordTemp[b]==wordVect[a][b]){
                                if(b==(wordTemp.size()-1)){
                                    match = true;
                                    matchIndex = a;
                                    a = wordVect.size();
                                }
                            }
                            else if(wordTemp[b]!=wordVect[a][b]){
                                match=false;
                                b = wordTemp.size();
                            }
                        }
                    }
                }
                if(match==false){
                    wordVect[0][0]++;
                    wordVect.push_back (wordTemp);
                    wordTemp.clear();
                    wordTemp.push_back (1);
                }
                else if(match==true){
                    wordVect[matchIndex][0]++;
					wordTemp.clear();
					wordTemp.push_back (1);
                }
            }
		};

		void numList(){
			numTemp.push_back (i);
			if((cin.peek() < 48) || (cin.peek() > 57)){
				bool match = false;
				unsigned int matchIndex;
				for(unsigned int a = 1; a < numVect.size(); a++){
					if(numVect[a].size() == numTemp.size()){
						for(unsigned int b = 1; b < numTemp.size(); b++){
							if(numTemp[b]==numVect[a][b]){
								if(b==(numTemp.size()-1)){
									match = true;
									matchIndex = a;
									a = numVect.size();
								}
							}
							else if(numTemp[b]!=numVect[a][b]){
								match=false;
								b = numTemp.size();
							}
						}
					}
				}
				if(match==false){
					numVect[0][0]++;
					numVect.push_back (numTemp);
					numTemp.clear();
					numTemp.push_back (1);
				}
				else if(match==true){
					numVect[matchIndex][0]++;
					numTemp.clear();
					numTemp.push_back (1);
				}
			}
		};

		void printList(){
			unsigned int largest = 1;
			for(unsigned int i = 1; i < wordVect.size(); i++){
				if(wordVect[i].size() > largest){
					largest = wordVect[i].size();
				}
			}
			for(unsigned int i = 1; i < numVect.size(); i++){
				if(numVect[i].size() > largest){
					largest = numVect[i].size();
				}
			}
			largest+=5;
			
			//print characters
			if(charCount>=10){
				cout << "Total " << charCount << " different characters, 10 most used characters: " << endl;
            	for(int i = 0; i < 10; i++){
            	    int maxValue = i;
            	    int maxCount = charVect[i];
            	    for(int j = 0; j < 128; j++){
            	        if(charVect[j] > maxCount){
            	            maxValue = j;
            	            maxCount = charVect[j];
            	        }
            	    }
					if(maxValue==10){
						cout << "No. " << i << ": \\n";
						for(unsigned int i = 0; i < largest-2; i++){
							cout << " ";
						}
						cout << maxCount << endl;
                    	charVect[maxValue]=0;	
					}
					else if(maxValue!=10){
            	    	cout << "No. " << i << ": " << char(maxValue);
						for(unsigned int i = 0; i < largest-1; i++){
							cout << " ";
						}
						cout << maxCount << endl;
            	    	charVect[maxValue]=0;
            		}
				}
			}
			else if(charCount<10){
                cout << "Total " << charCount << " different characters, " << charCount << " most used characters: " << endl;
                for(int i = 0; i < charCount; i++){
                    int maxValue = i;
                    int maxCount = charVect[i];
                    for(int j = 0; j < 128; j++){
                        if(charVect[j] >= maxCount){
                            maxValue = j;
                            maxCount = charVect[j];
                        }
                    }
					if(maxValue==10){
                        cout << "No. " << i << ": \\n";
                        for(unsigned int i = 0; i < largest-2; i++){
                            cout << " ";
                        }
                        cout << maxCount << endl;
                        charVect[maxValue]=0;
                    }
                    else if(maxValue!=10){
                        cout << "No. " << i << ": " << char(maxValue);
                        for(unsigned int i = 0; i < largest-1; i++){
                            cout << " ";
                        }
                        cout << maxCount << endl;
                        charVect[maxValue]=0;
                    }
	/*
                    cout << "No. " << i << ": " << char(maxValue);
					for(unsigned int i = 0; i < largest-1){
						cout << " ";
					}
					cout << maxCount << endl;
                    charVect[maxValue]=0;
                }
*/
            }
			cout << endl;	

			//print words
			 if(wordVect[0][0]>=10){
                cout << "Total " << wordVect[0][0] << " different words, 10 most used words: " << endl;
                for(unsigned int i = 0; i < 10; i++){
                    unsigned int maxCount = 0;
                    unsigned int maxIndex = 1;
                    for(unsigned int j = 1; j < wordVect.size(); j++){
                        if(wordVect[j][0] > maxCount){
                            maxIndex = j;
                            maxCount = wordVect[j][0];
                        }
                    }
					cout << "No. " << i << ": ";
                    for(unsigned int k = 1; k < wordVect[maxIndex].size(); k++){
                        cout << (char)wordVect[maxIndex][k];
                    }
					for(unsigned int i = 0; i < largest-wordVect[maxIndex].size(); i++){
                    	cout << " ";
					}
					cout << maxCount << endl;
                    wordVect[maxIndex][0]=0;
                }
            }

			else if(wordVect[0][0]<10){
				cout << "Total " << wordVect[0][0] << " different words, " << wordVect[0][0] << " most used words: " << endl;
				for(unsigned int i = 0; i < wordVect[0][0]; i++){
					unsigned int maxCount = 0;
                    unsigned int maxIndex = 1;
                    for(unsigned int j = 1; j < wordVect.size(); j++){
                        if(wordVect[j][0] > maxCount){
                            maxIndex = j;
                            maxCount = wordVect[j][0];
                        }
                    }
                    cout << "No. " << i << ": ";
                    for(unsigned int k = 1; k < wordVect[maxIndex].size(); k++){
                        cout << (char)wordVect[maxIndex][k];
                    }
					for(unsigned int i = 0; i < largest-wordVect[maxIndex].size(); i++){
						cout << " ";
					}
					cout << maxCount << endl;
                	wordVect[maxIndex][0]=0;
            	}
			}
			cout<<endl;



			//print numbers
			if(numVect[0][0]>=10){
				cout << "Total " << numVect[0][0] << " different numbers, 10 most used numbers: " << endl;
        		for(unsigned int i = 0; i < 10; i++){
            		unsigned int maxCount = 0;
            		unsigned int maxIndex = 1;
            		for(unsigned int j = 1; j < numVect.size(); j++){
					    if(numVect[j][0] > maxCount){
            		        maxIndex = j;
            		        maxCount = numVect[j][0];
            		    }
            		}
            		cout << "No. " << i << ": ";
            		for(unsigned int k = 1; k < numVect[maxIndex].size(); k++){
						cout << (char)numVect[maxIndex][k];
            		}
            		cout << "\t\t" << maxCount << endl;
            		numVect[maxIndex][0]=0;
        		}
    		}
			else if(numVect[0][0]<10){
        		cout << "Total " << numVect[0][0] << " different numbers, " << numVect[0][0]<< " most used numbers: " << endl;
        		for(unsigned int i = 0; i < numVect[0][0]; i++){
        		    unsigned int maxCount = 0;
            		unsigned int maxIndex = 1;
            		for(unsigned int j = 1; j < numVect.size(); j++){
                		if(numVect[j][0] > maxCount){
                    		maxIndex = j;
							maxCount = numVect[j][0];
						}
					}
					cout << "No. " << i << ": ";
					for(unsigned int k = 1; k < numVect[maxIndex].size(); k++){
						cout << (char)numVect[maxIndex][k];
					}
					cout << "\t\t" << maxCount << endl;
					numVect[maxIndex][0]=0;
				}
			}
	
		};
};

int main(){
		getMost test;
		test.parseList();
		test.printList();

	return 0;
}
