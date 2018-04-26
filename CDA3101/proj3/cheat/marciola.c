#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int getTag(int address, int offsetSize);
int getIndex(int address, int tagSize, int setSize);

int main(int argc, char *argv[])
{
    const char blockArg = 'b';
    const char setArg = 's';
    const char cacheArg = 'n';
    const char Arg = '-';
    int blockSize;
    int setSize;
    int cacheAssoc;
    int offsetSize;
    int indexSize;
    int tagSize;
    int cacheSize;
    char* accessToken = "";
    int addressToken;
    char* delim = " \n"; 
    char instruction[100];
    int count = 0;
    int found_WT = 0;
    int hits_WT = 0;
    int misses_WT = 0;
    int memRef_WT = 0;
    int found_WB = 0;
    int hits_WB = 0;
    int misses_WB = 0;
    int memRef_WB = 0;
    int i;
   
    // Parses Command Line Arguments
    if ( argc == 1 ) {
        printf( "No arguments were passed.\n" );
    } else {
        for ( i = 1; i < argc; ++i ) {

            // Check for '-b' argument
            if (argv[i][0] == Arg && argv[i][1] == blockArg) {
                blockSize = strtol(argv[i+1], '\0', 10);
            }

            // Check for '-s' argument
            if (argv[i][0] == Arg && argv[i][1] == setArg) {
                setSize = strtol(argv[i+1], '\0', 10);
            }

            // Check for '-n' argument
            if (argv[i][0] == Arg && argv[i][1] == cacheArg) {
                cacheAssoc = strtol(argv[i+1], '\0', 10);
            }
        }
    }

    // Set variables and output sizes
    offsetSize = (int) log2(blockSize);
    indexSize = (int) log2(setSize);
    tagSize = 32 - (offsetSize + indexSize);
    cacheSize = pow(2, indexSize);

    printf("Block size: %d\n", blockSize);
    printf("Number of sets: %d\n", setSize);
    printf("Associativity: %d\n", cacheAssoc);
    printf("Number of offset bits: %d\n", offsetSize);
    printf("Number of index bits: %d\n", indexSize);
    printf("Number of tag bits: %d\n\n", tagSize);

    // Cache entry object
    struct entry {
        int address;
        int index;
        int tag;
        int offset;
        int referenceNum;
        int valid;
        int dirty;
    } cache_WT[cacheSize][cacheAssoc], cache_WB[cacheSize][cacheAssoc], emptyEntry, tempEntry;

    // Initializing emptyEntry to zero's
    emptyEntry.index = -1;
    emptyEntry.tag = -1;
    emptyEntry.referenceNum = -1;
    emptyEntry.valid = -1;
    emptyEntry.dirty = -1;

    // Parses Input Traces Files
    while (fgets(instruction, 100, stdin) != NULL) {
        tempEntry = emptyEntry;
        accessToken = strtok(instruction, delim);    
        addressToken = atoi(strtok(NULL, delim));   
        count++;
       
        // Fill temp entry with values
        tempEntry.address = addressToken;
        tempEntry.index = getIndex(addressToken, offsetSize, setSize);
        tempEntry.tag = getTag(addressToken, tagSize);
        tempEntry.offset = offsetSize;
        tempEntry.referenceNum = count;
        tempEntry.valid = 1;
        tempEntry.dirty = 1;

        // Check if address is in caches
        found_WT = -1;
        found_WB = -1;
        for (i = 0; i < cacheAssoc; ++i) {
            if (cache_WT[tempEntry.index][i].index == tempEntry.index && cache_WT[tempEntry.index][i].tag == tempEntry.tag && cache_WT[tempEntry.index][i].valid == 1)
            { found_WT = i; }
            if (cache_WB[tempEntry.index][i].index == tempEntry.index && cache_WB[tempEntry.index][i].tag == tempEntry.tag && cache_WB[tempEntry.index][i].valid == 1)
            { found_WB = i; }
        }

        // WT Cache (Write-Through with No Write Allocate)
        if (found_WT != -1) {
            hits_WT++;
        } else {
            misses_WT++;
            memRef_WT++;

            if (*accessToken == 'R') {      
                // Check if open slot in cache by valid bit
                for (i = 0; i < cacheAssoc; ++i) {
                    if (cache_WT[tempEntry.index][i].valid == 0) {
                        found_WT = i;
                    }
                }

                if (found_WT != -1) {
                    cache_WT[tempEntry.index][found_WT] = tempEntry; 
                } else {
                    //int min = cache_WT[tempEntry.index][0].referenceNum;
                    int min = 0;

                    // Find least recently used cache item
                    for (i = 0; i < cacheAssoc; ++i) {
                        if (cache_WT[tempEntry.index][i].referenceNum < min) {
                            min = i;
                        }
                    }

                    cache_WT[tempEntry.index][min] = tempEntry;
                }
            }
        }

        // WB Cache (Write-Back with Write Allocate)
        if (found_WB != -1) {
            hits_WB++;
        } else {
            misses_WB++;
            memRef_WB++;


            if (found_WB != -1) {
                cache_WB[tempEntry.index][found_WB] = tempEntry; 
            } else {
                int min = cache_WB[tempEntry.index][0].referenceNum;

                // Find least recently used cache item
                for (i = 0; i < cacheAssoc; ++i) {
                    if (cache_WB[tempEntry.index][i].referenceNum < min) {
                        min = cache_WB[tempEntry.index][i].referenceNum;
                    }
                }

                cache_WB[tempEntry.index][min] = tempEntry;
            }

        }
        
        // Zero out found variables
        found_WT = 0;
        found_WB = 0;

    }
    
    printf("****************************************\n");
    printf("Write-through with No Write Allocate\n");
    printf("****************************************\n");
    printf("Total Number of References: %d\n", count);
    printf("Hits: %d\n", hits_WT);
    printf("Misses: %d\n", misses_WT);
    printf("Memory References: %d\n", memRef_WT);
    printf("\n");

    printf("****************************************\n");
    printf("Write-back with Write Allocate\n");
    printf("****************************************\n");
    printf("Total Number of References: %d\n", count);
    printf("Hits: %d\n", hits_WB);
    printf("Misses: %d\n", misses_WB);
    printf("Memory References: %d\n", memRef_WB);
    return 0;
}

int getIndex(int address, int offsetSize, int setSize)
{
    return (address >> offsetSize) % setSize;
}

int getTag(int address, int tagSize)
{
    return (address >> (32-tagSize));
}
