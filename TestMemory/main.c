#include "string.h"
#include "stdio.h"
#include "stdlib.h"

typedef enum {
    PSKEY_CAPSENSE = 0x12,
    PSKEY_IR,
    PSKEY_HALL
}PSKey_T;

typedef struct capsenseData {
    int myData1;
    char myData2;
}capsenseData_T;

typedef struct irData {
    int myData1;
    int myData2;
    int myData3;
}irData_T;

typedef struct hallData {
    char myData1;
    char myData2;
    char myData3;
}hallData_T;

void ReadPSData(PSKey_T psKey, void* getPtr, unsigned int getBytes);
void* PSKeyRetrieve(PSKey_T psKey, unsigned int getBytes);

int main(void) {
    PSKey_T myModule1 = PSKEY_CAPSENSE;
    PSKey_T myModule2 = PSKEY_IR;
    PSKey_T myModule3 = PSKEY_HALL;

    capsenseData_T*  myCapDataPtr;
    irData_T*        myIrDataPtr;
    hallData_T*      myHallDataPtr;

    //Allocate Dynamic Memory 
    myCapDataPtr = malloc(sizeof(capsenseData_T));
    printf("Dynamically allocated %i bytes for myCapDataPtr\n", sizeof(capsenseData_T));

    myIrDataPtr = malloc(sizeof(irData_T));
    printf("Dynamically allocated %i bytes for myIRDataPtr\n", sizeof(irData_T));

    myHallDataPtr = malloc(sizeof(hallData_T));
    printf("Dynamically allocated %i bytes for myHallDataPtr\n", sizeof(hallData_T));

    //Module Info + Module Data Ptr
    ReadPSData(myModule1, myCapDataPtr, sizeof(capsenseData_T));
    printf("    myCapDataPtr->myData1: 0x%2X\n", myCapDataPtr->myData1);
    printf("    myCapDataPtr->myData2: 0x%2X\n", myCapDataPtr->myData2);

    ReadPSData(myModule2, myIrDataPtr, sizeof(irData_T));
    printf("    myIrDataPtr->myData1: 0x%2X\n", myIrDataPtr->myData1);
    printf("    myIrDataPtr->myData2: 0x%2X\n", myIrDataPtr->myData2);
    printf("    myIrDataPtr->myData3: 0x%2X\n", myIrDataPtr->myData3);

    ReadPSData(myModule3, myHallDataPtr, sizeof(hallData_T));
    printf("    myHallDataPtr->myData1: 0x%2X\n", myHallDataPtr->myData1);
    printf("    myHallDataPtr->myData2: 0x%2X\n", myHallDataPtr->myData2);
    printf("    myHallDataPtr->myData3: 0x%2X\n", myHallDataPtr->myData3);

    free(myCapDataPtr);
    printf("Free myCapDataPtr\n");
    myCapDataPtr = NULL;

    free(myIrDataPtr);
    printf("Free myIrDataPtr\n");
    myIrDataPtr = NULL;

    free(myHallDataPtr);
    printf("Free myHallDataPtr\n");
    myHallDataPtr = NULL;

    return 0;
}

void ReadPSData(PSKey_T psKey, void* getPtr, unsigned int getBytes) {
    printf("  Read PS KEY: %i\n", psKey);
    memcpy(getPtr, PSKeyRetrieve(psKey, getBytes), getBytes);
}

void* PSKeyRetrieve(PSKey_T psKey, unsigned int getBytes) {
    switch(psKey) {
        case PSKEY_CAPSENSE:
        {
            //Declare as static to ensure local variable exist
            //returned as pointer
            static capsenseData_T myCapData;
            myCapData.myData1 = 0x11;
            myCapData.myData2 = 0x12;
            return &myCapData;
        }
        break;
        
        case PSKEY_IR:
        {
            //Declare as static to ensure local variable exist
            //returned as pointer
            static irData_T myIrData;
            myIrData.myData1 = 0x21;
            myIrData.myData2 = 0x22;
            myIrData.myData3 = 0x23;
            return &myIrData;
        }
        break;

        case PSKEY_HALL:
        {
            //Declare as static to ensure local variable exist
            //returned as pointer
            static hallData_T myHallData;
            myHallData.myData1 = 0x31;
            myHallData.myData2 = 0x32;
            myHallData.myData3 = 0x33;
            return &myHallData;
        }
        break;
    }
}

/////////////////////////////////////////////////////////////////
void MyFunc(void* getPtr, int mode);
void TestDynamicMemory(void) {
    unsigned char* myUCPtr = NULL;
    myUCPtr = malloc(10 * sizeof(unsigned char));
    MyFunc(myUCPtr, 0);
    for(int i = 0; i < 10; i ++) {
        //printf("%i:    0x%2X\n", i, *myUCPtr);
        myUCPtr++;
    }
    free(myUCPtr);

    ////////////////////////////////////////////////////////
    int* myIntPtr = NULL;
    myIntPtr = malloc(10 * sizeof(int));
    MyFunc(myIntPtr, 1);
    for(int i = 0; i < 10; i ++) {
        //printf("%i:     0x%2X\n", i, *myIntPtr);
        myUCPtr++;
    }
    free(myIntPtr);
}
void MyFunc(void* getPtr, int mode) {
    if(mode == 0)
        memset(getPtr, 0xFF, sizeof(unsigned char) * 10);
    else {
        memset(getPtr, 0x12, sizeof(int) * 10);
    }
}