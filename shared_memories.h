#ifndef SHARED_MEMORIES
#define SHARED_MEMORIES

#include "header.h"
#include "semaphores.h"
#include "constants.h"
#include "function.h"
#include <time.h>

typedef struct {
    int day;
    int month;
    int year;
} date;

typedef struct {
    int level;
    char color;
    int sealed;
    int lable;
    date properdate;
    int dateprinted;
    int correctcolor;
    char actualDate[20];
} liquids;

typedef struct{
  int minType;
  int maxType;
  int minIndex;
  int maxIndex;
} replace;

key_t replace_key=0x1646;

typedef struct {

    liquids liquid;
     int Persrciptions;
} ApprovedSamples_Struct; // struct of approved sample struct + Persrciptions

typedef struct {

	ApprovedSamples_Struct Approved[1000];
} Approved_LiqSamples_SHM; // shared memory of the struct of  approved sample struct + Persrciptions

key_t Approved_LiqSamples_SHM_key=  0x2242;
key_t Approved_PillSamples_SHM_key=  0x8000;
key_t pillFor_AcceptedAndpackagededSamplesCount_key=  0x1490;
key_t liquiqFor_AcceptedAndpackagededSamplesCount_key=  0x1478;

char COLOR[10] = {'R', 'W'};
int CONTAINERSNUM[10] = {15,20};

#define SHM_SIZE  10000 // Size of shared memory
typedef struct {
	liquids liquid[1000];
} liquidsharedmemory;

typedef struct {
	int check[1000];
	int accepted[1000];
} checkedsharedmemory;




typedef struct {
	int Approved_Samples[100];
	int packaged_Samples[100];
	int checked_Samples[100];
} liquiqFor_AcceptedAndpackagededSamplesCount;



/////

typedef struct {
    int size;
    char color;
    int filledcontainers;
    int correctpillsnum;
    date properdate;
    int dateprinted;
    int correctcolor;
    char actualDate[20];
    int numofcontainers;
} pills;

typedef struct {
	pills pill[1000];
} pillsharedmemory;

typedef struct {

    pills pill[100];
    int numofcontainers;
     int Persrciptions;
} ApprovedPillSamples_Struct; // struct of approved sample struct + Persrciptions


typedef struct {
ApprovedPillSamples_Struct Approved[500];
} Approved_PillSamples_SHM; // shared memory of the struct of  approved sample struct + Persrciptions

typedef struct {
	int check[1000];
	int accepted[1000];
} checkedpillsharedmemory;

typedef struct {
	int Approved_Samples[100];
	int packaged_Samples[100];
	int checked_Samples[100];
} pillFor_AcceptedAndpackagededSamplesCount;




#endif
