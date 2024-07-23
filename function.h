#ifndef __FUNCTIONS__
#define __FUNCTIONS__
#include "header.h"
#include "constants.h"

void readFile(char* filename){
char line[200];
char lable[50];
FILE *file;
file=fopen(filename,"r");
if (file==NULL){
perror("THE FILE IS NOT EXIST");
exit(-2);
}
char seperator[]="=";
while (fgets(line,sizeof(line),file)!=NULL){
char *str= strtok(line,seperator);
strcpy(lable,str);
str=strtok(NULL,seperator);
if (strcmp(lable,"workers_number")==0){
workers_number=atoi(str);
}
else if(strcmp(lable,"liquid_plines")==0){
liquid_plines=atoi(str);
}
else if(strcmp(lable,"runduration")==0){
runduration=atoi(str);
}
else if(strcmp(lable,"numofsamplesofliquid")==0){
numofsamplesofliquid=atoi(str);
}
else if(strcmp(lable,"pill_plines")==0){
pill_plines=atoi(str);
}
else if(strcmp(lable,"medicinenum")==0){
medicinenum=atoi(str);
}
else if(strcmp(lable,"canceledliquid")==0){
canceledliquid=atoi(str);
}
else if(strcmp(lable,"canceledpill")==0){
canceledpill=atoi(str);
}
else if(strcmp(lable,"numofsamplesofpill")==0){
numofsamplesofpill=atoi(str);
}
else if(strcmp(lable,"min_size")==0){
min_size=atoi(str);
}
else if(strcmp(lable,"max_size")==0){
max_size=atoi(str);
}
else if(strcmp(lable,"max_level")==0){
max_level=atoi(str);
}
else if(strcmp(lable,"min_level")==0){
min_level=atoi(str);
}
else if(strcmp(lable,"minmed_level")==0){
minmed_level=atoi(str);
}
else if(strcmp(lable,"maxmed_level")==0){
maxmed_level=atoi(str);
}

}
fclose(file);

}
#endif
