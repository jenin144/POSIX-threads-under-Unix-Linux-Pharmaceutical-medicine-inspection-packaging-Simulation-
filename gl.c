#include <GL/glut.h>
#include <math.h>
#include <stdbool.h>
#include "header.h"
#include "constants.h"
#include "function.h"
#include "shared_memories.h"
#include "queue.h"
#include "semaphores.h"

// Number of workers for each square
int numWorkers = 5;
float rectWidth = 0.1; // Width of the rectangles
float rectHeight = 0.3; // Height of the rectangles
float smallSquareSize = 0.05; // Size of the small square
int shmidLiquid;
int shmidPill ;
float ballX[100][100] ;
float ballXA[100][100] ;
float ballXP[100][100] ;
float ballY[100][100] ;
float ballYA[100][100] ;
float ballYP[100][100] ;
float spacing;
void glutWMCloseFunc(void (*func)(void));
float workerXOffset[100][100] ;
float workerYOffset[100][100] ;
int worker_liquid[50];
int worker_pill[50];
int liquid=0;
int pill=0;
float ballSpacing = 0.03;
//int check=0;
bool endSimulation = false;
int pillwork=0;
int liqwork=0;
int num_worker_liquid[50];
int num_worker_pill[50];
int num_samples_liquid[100];
int num_packaged_liquid[100];
int num_approved_liquid[100];
int num_liquid=0;
int num_packaged_pill[100];
int num_approved_pill[100];
int num_samples_pill[100];
int cont[50];
int rem[50];
int itr[50];
int flag[50];
typedef void (*sighandler_t)(int);
sighandler_t sigset(int sig, sighandler_t disp);



void killProcesses(){


 //terminateProcesses 
	    FILE *file = fopen("pids1.txt", "r");
	    if (!file) {
		perror("Error opening file");
		exit(EXIT_FAILURE);
	    }

	    pid_t pid;
	    while (fscanf(file, "%d\n", &pid) == 1) {
		printf("Terminating process with ID: %d\n", pid);
		kill(pid, SIGKILL);
	    }
	    fclose(file);
	    
	    
	    //terminateProcesses 
	    FILE *file2 = fopen("pids2.txt", "r");
	    if (!file2) {
		perror("Error opening file");
		exit(EXIT_FAILURE);
	    }

	    pid_t pid2;
	    while (fscanf(file2, "%d\n", &pid2) == 1) {
		printf("Terminating process with ID: %d\n", pid2);
		kill(pid2, SIGKILL);
	    }
	    fclose(file2);
	    
	    
	    
	//terminateProcesses 
	    FILE *file3 = fopen("process_ids.txt", "r");
	    if (!file3) {
		perror("Error opening file");
		exit(EXIT_FAILURE);
	    }

	    pid_t pid3;
	    while (fscanf(file3, "%d\n", &pid3) == 1) {
		printf("Terminating process with ID: %d\n", pid3);
		kill(pid3, SIGKILL);
	    }
	    fclose(file3);
	    
	       // Write end simulation here >>>>>>>>>>>>>>>>>>>
    endSimulation = true;
    glutPostRedisplay();
 



}













void closeCallback() {

    readFile("arguments.txt");

    printf("Window is closing. Performing cleanup...\n");

    int shmid_liquid = shmget(liquiqFor_AcceptedAndpackagededSamplesCount_key, 1024, IPC_CREAT | 0666); // Create or get the shared memory segment
    if (shmid_liquid == -1) {
        perror("shmget 29 gl");
        exit(EXIT_FAILURE);
    }

    // Use shmctl to delete the shared memory segment
    if (shmctl(shmid_liquid, IPC_RMID, NULL) == -1) {
        perror("shmctl");
        exit(EXIT_FAILURE);
    }
    
    /////////////////////////////////
    
     int shmid_replace = shmget(replace_key, 1024, IPC_CREAT | 0666); // Create or get the shared memory segment
    if (shmid_replace == -1) {
        perror("shmget 29 gl");
        exit(EXIT_FAILURE);
    }

    // Use shmctl to delete the shared memory segment
    if (shmctl(shmid_replace, IPC_RMID, NULL) == -1) {
        perror("shmctl");
        exit(EXIT_FAILURE);
    }
    
    //////////////////////
    
    
    for(int i =0; i<liquid_plines;i++){
    
    int shmidliqchek = shmget(0x2000+i, SHM_SIZE, IPC_CREAT | 0666); // Create or get the shared memory segment
    if (shmidliqchek == -1) {
        perror("shmget 52 gl");
        exit(EXIT_FAILURE);
    }

    // Use shmctl to delete the shared memory segment
    if (shmctl(shmidliqchek, IPC_RMID, NULL) == -1) {
        perror("shmctl");
        exit(EXIT_FAILURE);
    }
    
    
    
       int shmidliq = shmget(i+1, SHM_SIZE, IPC_CREAT | 0666); // Create or get the shared memory segment
    if (shmidliq == -1) {
        perror("shmget 64 gl");
        exit(EXIT_FAILURE);
    }

    // Use shmctl to delete the shared memory segment
    if (shmctl(shmidliq, IPC_RMID, NULL) == -1) {
        perror("shmctl");
        exit(EXIT_FAILURE);
    }


}
    ///////////////////
    
    
    int shmid_pill = shmget(pillFor_AcceptedAndpackagededSamplesCount_key, 1024, IPC_CREAT | 0666); // Create or get the shared memory segment
    if (shmid_pill == -1) {
        perror("shmget 29 gl");
        exit(EXIT_FAILURE);
    }

    // Use shmctl to delete the shared memory segment
    if (shmctl(shmid_pill, IPC_RMID, NULL) == -1) {
        perror("shmctl");
        exit(EXIT_FAILURE);
    }
    killProcesses();
    
}




void drawWorker(float x, float y) {
    // Draw a simple human figure using a circle for the head and lines for the body
    float headRadius = 0.02;
    float bodyHeight = 0.06;

    // Draw head
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        float theta = i * 3.14159f / 180;
        glVertex2f(x + headRadius * cos(theta), y + headRadius * sin(theta) + bodyHeight / 2);
    }
    glEnd();

    // Draw body
    glBegin(GL_LINES);
    glVertex2f(x, y + bodyHeight / 2);
    glVertex2f(x, y - bodyHeight / 2);
    glEnd();

    // Draw arms
    glBegin(GL_LINES);
    glVertex2f(x, y);
    glVertex2f(x - headRadius, y - headRadius / 2);
    glVertex2f(x, y);
    glVertex2f(x + headRadius, y - headRadius / 2);
    glEnd();

    // Draw legs
    glBegin(GL_LINES);
    glVertex2f(x, y - bodyHeight / 2);
    glVertex2f(x - headRadius / 2, y - bodyHeight);
    glVertex2f(x, y - bodyHeight / 2);
    glVertex2f(x + headRadius / 2, y - bodyHeight);
    glEnd();
}

void drawText(char* text, float x, float y) {
    glRasterPos2f(x, y);
    while (*text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *text);
        text++;
    }
    glutPostRedisplay();
}



int read_liquid_shared(int i,int num){
    readFile("arguments.txt");

    // ID for shared memory
    shmidLiquid = shmget(liquiqFor_AcceptedAndpackagededSamplesCount_key, SHM_SIZE, IPC_CREAT | 0666);
    if (shmidLiquid == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    // Attach shared memory
    liquiqFor_AcceptedAndpackagededSamplesCount *shared_liquid = (liquiqFor_AcceptedAndpackagededSamplesCount *)shmat(shmidLiquid, NULL, 0);
    if (shared_liquid == (void *)-1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }
    int liquidChecked = shared_liquid->checked_Samples[i];
 int liquidPackaged = shared_liquid->packaged_Samples[i];
  int liquidApproved = shared_liquid->Approved_Samples[i];
  
    if (shmdt(shared_liquid) == -1) {
        perror("shmdt");
        exit(EXIT_FAILURE);
    }
    
    switch(num){
    case 0:
    return liquidChecked;
    break;
    case 1:
    return liquidApproved;    
    break;
    case 2:
    return liquidPackaged;
    break;
    }
    
}

/////////////////////////////////////////
void replacement(){

    readFile("arguments.txt");

    // ID for shared memory
    int shmidReplace = shmget(replace_key, SHM_SIZE, IPC_CREAT | 0666);
    if (shmidReplace == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    // Attach shared memory
    replace *shared_replace = (replace *)shmat(shmidReplace, NULL, 0);
    if (shared_replace == (void *)-1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }
    
    int minType = shared_replace->minType;
   int maxType = shared_replace->maxType;
   int minIndex = shared_replace->minIndex;
   int maxIndex=shared_replace->maxIndex;
  
    if (shmdt(shared_replace) == -1) {
        perror("shmdt");
        exit(EXIT_FAILURE);
    }
    

    
    if(liqwork<num_worker_liquid[maxIndex] && num_worker_liquid[maxIndex] >0) {
    // workerXOffset[maxIndex][liqwork]= (liqwork% 2) * 0.05+0.1 + x;
    if(maxType==0){
     num_worker_liquid[maxIndex]= num_worker_liquid[maxIndex]-1;
     }
     if(minType==0){
     num_worker_liquid[minIndex]= num_worker_liquid[minIndex]+1;
     }
     liqwork++;
     }
     else if (liqwork>=num_worker_liquid[maxIndex]) {
     liqwork=0;
     }
     
       if(pillwork<num_worker_pill[maxIndex] && num_worker_pill[maxIndex] >0){
       //  workerXOffset[maxIndex][pillwork]= (pillwork% 2) * 0.05+0.1 + x;
        if(maxType==1){
          num_worker_pill[maxIndex]= num_worker_pill[maxIndex]-1;
          }
          if(minType==1){
          num_worker_pill[minIndex]= num_worker_pill[minIndex]+1;
          }
          pillwork++;
         }
         else if(pillwork>=num_worker_pill[maxIndex] ){
         pillwork=0;
         }
     
     
    glutPostRedisplay();
   
}

////////////////////////////////////////////
/*void replace_pill(){
    readFile("arguments.txt");

    // ID for shared memory
    int shmidReplace = shmget(replace_key, SHM_SIZE, IPC_CREAT | 0666);
    if (shmidReplace == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    // Attach shared memory
    replace *shared_replace = (replace *)shmat(shmidReplace, NULL, 0);
    if (shared_replace == (void *)-1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }
   int minType = shared_replace->minType;
   int maxType = shared_replace->maxType;
   int minIndex = shared_replace->minIndex[1];
   int maxIndex=shared_replace->maxIndex[1];
     
    if (shmdt(shared_replace) == -1) {
        perror("shmdt");
        exit(EXIT_FAILURE);
    }
    

          int totalLines = liquid_plines + pill_plines;
    float spacing = 2.0 / totalLines; // Spacing between lines
     float x = -1.0 + ( minIndex+ 0.5) * spacing;
     if(pillwork<num_worker_pill[maxIndex] && num_worker_pill[maxIndex] >0){
       //  workerXOffset[maxIndex][pillwork]= (pillwork% 2) * 0.05+0.1 + x;
          num_worker_pill[maxIndex]= num_worker_pill[maxIndex]-1;
          num_worker_pill[minIndex]= num_worker_pill[minIndex]+1;
          pillwork++;
         }
         else if(pillwork>=num_worker_pill[maxIndex] ){
         pillwork=0;
         }
    glutPostRedisplay();
        
    
        
 }*/

////////////////////////////////////////////
int read_pill_shared(int i,int num){
    readFile("arguments.txt");

    // ID for shared memory
    shmidPill = shmget(pillFor_AcceptedAndpackagededSamplesCount_key, SHM_SIZE, IPC_CREAT | 0666);
    if (shmidPill == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    // Attach shared memory
    pillFor_AcceptedAndpackagededSamplesCount *shared_pill = (pillFor_AcceptedAndpackagededSamplesCount *)shmat(shmidPill, NULL, 0);
    if (shared_pill == (void *)-1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }
    int pillChecked = shared_pill->checked_Samples[i];
    int pillPackaged = shared_pill->packaged_Samples[i];
    int pillApproved = shared_pill->Approved_Samples[i];
  
    if (shmdt(shared_pill) == -1) {
        perror("shmdt");
        exit(EXIT_FAILURE);
    }
    
    switch(num){
    case 0:
    return pillChecked;
    break;
    case 1:
   // check=pillApproved;
    return pillApproved;
    break;
    case 2:
    return pillPackaged;
    break;
    }
    
}


void drawRectangle(float x, float a, float b){
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
    glVertex2f(x - rectWidth, a);
    glVertex2f(x + rectWidth, a);
    glVertex2f(x + rectWidth, b);
    glVertex2f(x - rectWidth, b);
    glEnd();
}

void drawSquare(float x, float a){
    glColor3f(1.0, 0.0, 0.0); // Set color to red
    glBegin(GL_LINE_LOOP);
    glVertex2f(x - smallSquareSize, a - smallSquareSize);
    glVertex2f(x + smallSquareSize, a - smallSquareSize);
    glVertex2f(x + smallSquareSize, a + smallSquareSize);
    glVertex2f(x - smallSquareSize, a + smallSquareSize);
    glEnd();
}

void drawBalls(float x, float y,float r, float g, float b) {
    float ballRadius = 0.01;
   
    glColor3f(r,g,b); // Indigo color

   

        glBegin(GL_POLYGON);
        for (int j = 0; j < 360; j++) {
            float theta = j * 3.14159f / 180;
            glVertex2f(x + ballRadius * cos(theta), y + ballRadius * sin(theta));
        }
        glEnd();
    
}

int read_containers_num(int i,int j){

     int shmid = shmget(0x4000+i, SHM_SIZE, IPC_CREAT | 0666);
		    if (shmid == -1) {
		        perror("shmget");
		        exit(EXIT_FAILURE);
		    }
		    pillsharedmemory *shared_memory = (pillsharedmemory *)shmat(shmid, NULL, 0);
		    if (shared_memory == (void *)-1) {
		        perror("shmat main line 457");
		        exit(EXIT_FAILURE);
		    }
		    
		    int num= shared_memory->pill[j].numofcontainers;
		    
		       if (shmdt(shared_memory) == -1) {
                perror("shmdt");
                exit(EXIT_FAILURE);
                }
            
            return num;	    

}

///////////////////////////////////

int liquid_plines, pill_plines;
void display() {
    readFile("arguments.txt");
    glClear(GL_COLOR_BUFFER_BIT);

    // Set the color to black for the lines
    glColor3f(0.0, 0.0, 0.0);

    // Calculate the total number of lines and the spacing
    int totalLines = liquid_plines + pill_plines;
    float spacing = 2.0 / totalLines; // Spacing between lines

    // Draw liquid lines in the left half of the window
    for (int i = 0; i < liquid_plines; i++) {
        float x = -1.0 + (i + 0.5) * spacing; // X position of the vertical line for liquid

        // Draw the vertical line
        glBegin(GL_LINES);
        glVertex2f(x, -1.0);
        glVertex2f(x, 1.0);
        glEnd();

        // Draw the line name above it
        drawText("Liquid Line", x - 0.05, 0.95);

        // Draw rectangles
        drawRectangle(x, 0.1, 0.4);
        glColor3f(0.0, 0.0, 0.0);
        drawText("Checking", x - 0.09, 0.42);
        drawRectangle(x, -0.4, -0.1);
        glColor3f(0.0, 0.0, 0.0);
        drawText("Approved", x - 0.09, -0.08);
        drawRectangle(x, -0.9, -0.6);
        glColor3f(0.0, 0.0, 0.0);
        drawText("Packaged", x - 0.09, -0.58);

        // Draw small squares
        drawSquare(x, 0.15);
        drawSquare(x, -0.35);
        drawSquare(x, -0.85);

        // Draw indigo balls inside the first rectangle
      /*  for (int s = 0; s < numofsamplesofliquid; s++) {
            drawBalls(ballX[i][s], ballY[i][s], 0.29, 0.0, 0.51);
        }*/
                
        
        // Read and display shared data
         num_samples_liquid[i] = read_liquid_shared(i, 0);
        if (num_samples_liquid[i] > 0) {
         glColor3f(0.0, 0.0, 0.0);
            char label[3];
            snprintf(label, sizeof(label), "%d", num_samples_liquid[i]);
            drawText(label, x - smallSquareSize / 2, 0.15 - smallSquareSize / 2);
              // Draw indigo balls inside the first rectangle
        for (int s = 0; s < num_samples_liquid[i]-num_approved_liquid[i]; s++) {
            drawBalls(ballX[i][s], ballY[i][s], 0.29, 0.0, 0.51);    ///AMAL
        } 
        }

         num_approved_liquid[i] = read_liquid_shared(i, 1);
        if (num_approved_liquid[i] > 0) {
         glColor3f(0.0, 0.0, 0.0);
            char label[3];
            snprintf(label, sizeof(label), "%d", num_approved_liquid[i]);
            drawText(label, x - smallSquareSize / 2, -0.35 - smallSquareSize / 2);
                for (int s = 0; s < num_approved_liquid[i]-num_packaged_liquid[i]; s++) {
            drawBalls(ballXA[i][s], ballYA[i][s], 0.0, 1.0, 0.0);    ///AMAL
           
        } 
       
        }

         num_packaged_liquid[i] = read_liquid_shared(i, 2);
        if (num_packaged_liquid[i] > 0) {
            char label[3];
         glColor3f(0.0, 0.0, 0.0);
            snprintf(label, sizeof(label), "%d", num_packaged_liquid[i]);
            drawText(label, x - smallSquareSize / 2, -0.85 - smallSquareSize / 2);
           for (int s = 0; s < num_packaged_liquid[i]; s++) {
            drawBalls(ballXP[i][s], ballYP[i][s], 0.0, 0.0, 1.0);    ///AMAL
            } 
        }

        // Draw workers next to the small squares
        for (int j = 0; j < num_worker_liquid[i]; j++) {
            glColor3f(1.0, 0.3, 0.4);
            drawWorker(x + workerXOffset[i][j], 0.15 + workerYOffset[i][j]);
           // drawWorker(x + workerXOffset[i][j], -0.35 + workerYOffset[i][j]);
           
        }

        glColor3f(0.0, 0.0, 0.0); // Reset color for next line
    }

    // Draw pill lines in the right half of the window
    for (int i = 0; i < pill_plines; i++) {
        float x = -1.0 + ((liquid_plines + i + 0.5) * spacing); // X position of the vertical line for pill

        // Draw the vertical line
        glBegin(GL_LINES);
        glVertex2f(x, -1.0);
        glVertex2f(x, 1.0);
        glEnd();

        // Draw the line name above it
        drawText("Pill Line", x - 0.05, 0.95);

        // Draw rectangles
        drawRectangle(x, 0.1, 0.4);
        glColor3f(0.0, 0.0, 0.0);
        drawText("Checking", x - 0.09, 0.42);
        drawRectangle(x, -0.4, -0.1);
        glColor3f(0.0, 0.0, 0.0);
        drawText("Approved", x - 0.09, -0.08);
        drawRectangle(x, -0.9, -0.6);
        glColor3f(0.0, 0.0, 0.0);
        drawText("Packaged", x - 0.09, -0.58);

        // Draw small squares
        drawSquare(x, 0.15);
        drawSquare(x, -0.35);
        drawSquare(x, -0.85);

        // Draw indigo balls inside the first rectangle
     
        // Read and display shared data
         num_samples_pill[i] = read_pill_shared(i, 0);
        if (num_samples_pill[i] > 0) {
         glColor3f(0.0, 0.0, 0.0);
            char label[3];
            snprintf(label, sizeof(label), "%d", num_samples_pill[i]);
            drawText(label, x - smallSquareSize / 2, 0.15 - smallSquareSize / 2);
            
               for (int s = 0; s < num_samples_pill[i]-num_approved_pill[i]; s++) {
            drawBalls(ballX[liquid_plines + i][s], ballY[liquid_plines + i][s], 0.29, 0.0, 0.51);
        }

        }

         num_approved_pill[i] = read_pill_shared(i, 1);
        if (num_approved_pill[i] > 0) {
         glColor3f(0.0, 0.0, 0.0);
            char label[3];
            snprintf(label, sizeof(label), "%d", num_approved_pill[i]);
            drawText(label, x - smallSquareSize / 2, -0.35 - smallSquareSize / 2);
            
          rem[i]=(num_approved_pill[i] - (num_packaged_pill[i]*cont[i]));
         if(rem[i]>=cont[i] || flag[i]==0){
            itr[i]=rem[i];
            flag[i]=1;
         }
         else{
            itr[i]=num_approved_pill[i]%cont[i];
         }  
           
            
          
               for (int s = 0; s < itr[i]; s++) {
            drawBalls(ballXA[liquid_plines + i][s], ballYA[liquid_plines + i][s], 0.0, 1.0, 0.0);
        }


        }

         num_packaged_pill[i] = read_pill_shared(i, 2);
        if (num_packaged_pill[i] > 0) {
         glColor3f(0.0, 0.0, 0.0);
            char label[3];
            snprintf(label, sizeof(label), "%d", num_packaged_pill[i]);
            drawText(label, x - smallSquareSize / 2, -0.85 - smallSquareSize / 2);
            
          //  cont=read_containers_num(i,s);
            
                    for (int s = 0; s < num_packaged_pill[i]; s++) {
                      cont[i]=read_containers_num(i,s);
            drawBalls(ballXP[liquid_plines + i][s], ballYP[liquid_plines + i][s], 0.0, 0.0, 1.0);
             char label[3];
            snprintf(label, sizeof(label), "%d", cont[i]);
            drawText(label, ballXP[liquid_plines + i][s], ballYP[liquid_plines + i][s]);
         //   containers=cont[i];
        }
        }

        
        // Draw workers next to the small squares
        for (int j = 0; j < num_worker_pill[i]; j++) {
            glColor3f(1.0, 0.3, 0.4);
            drawWorker(x + workerXOffset[liquid_plines + i][j], 0.15 + workerYOffset[liquid_plines + i][j]);
          //  drawWorker(x + workerXOffset[liquid_plines + i][j], -0.35 + workerYOffset[liquid_plines + i][j]);
        }

        glColor3f(0.0, 0.0, 0.0); // Reset color for next line
    }

if (endSimulation) {
        glColor3f(1.0, 0.0, 0.0); // Set color to red
           glRasterPos2f(-0.2, 0.8);
           char *text="Simulation has ended";
    while (*text) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *text);
        text++;
    }
        
    }
    glFlush();
}

void move_worker_liquid(){


  for(int i=0;i<liquid_plines;i++){
  if(worker_liquid[i]<num_worker_liquid[i]){
    workerXOffset[i][worker_liquid[i]]= (worker_liquid[i] % 2) * 0.05+0.1;
    workerYOffset[i][worker_liquid[i]]= (worker_liquid[i] / 2) * 0.05;
    worker_liquid[i]=worker_liquid[i]+1;
  }

//make worker=0 when return to checking from packeging

if(worker_liquid[i]==num_worker_liquid[i]){
    worker_liquid[i]=0;
}
}
    glutPostRedisplay();
}

void move_worker_pill(){

 for(int i=0;i<pill_plines;i++){
if(worker_pill[i]<num_worker_pill[i]){
 
    workerXOffset[liquid_plines+i][worker_pill[i]]= (worker_pill[i] % 2) * 0.05+0.1;
    workerYOffset[liquid_plines+i][worker_pill[i]]= (worker_pill[i] / 2) * 0.05;
     worker_pill[i]=worker_pill[i]+1;
  }

//make worker=0 when return to checking from packeging
if(worker_pill[i]==num_worker_pill[i]){
   worker_pill[i]=0;
}
}
    glutPostRedisplay();
}



void move_worker_to_approved_liquid(){

for(int i=0;i<liquid_plines;i++){
if(worker_liquid[i]<num_worker_liquid[i]){
  
    workerXOffset[i][worker_liquid[i]]= (worker_liquid[i] % 2) * 0.05+0.1;
    workerYOffset[i][worker_liquid[i]]= (worker_liquid[i] / 2) * 0.05-0.5;
  
worker_liquid[i]=worker_liquid[i]+1;
//make worker=0 when return to checking from packeging
}

if(worker_liquid[i]==num_worker_liquid[i]){
    worker_liquid[i]=0;
}
}
    glutPostRedisplay();
}

void move_worker_to_approved_pill(){


  for(int i=0;i<pill_plines;i++){
  if(worker_pill[i]<num_worker_pill[i]){
    workerXOffset[liquid_plines+i][worker_pill[i]]= (worker_pill[i] % 2) * 0.05+0.1;
    workerYOffset[liquid_plines+i][worker_pill[i]]= (worker_pill[i] / 2) * 0.05-0.5;
  
worker_pill[i]=worker_pill[i]+1;
//make worker=0 when return to checking from packeging
}

if(worker_pill[i]==num_worker_pill[i]){
   worker_pill[i]=0;
}
}
    glutPostRedisplay();
}


void amal(){
}


void init() {
    glClearColor(0.8f, 0.8f, 1.0f, 1.0f); // Set the background color
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv) {
    readFile("arguments.txt");
    

    for(int i=0;i<10;i++){
    num_worker_pill[i]=workers_number;   //i line number
      num_worker_liquid[i]=workers_number;
      worker_pill[i]=0;
      worker_liquid[i]=0;
    }
      FILE* glpid_file = fopen("openglid.txt", "w"); // Open the file in write mode
	
		    if (glpid_file == NULL) {
			perror("Error opening glpid_file.txt\n");
			exit(-1);
		    }
		    
  	fprintf(glpid_file, "%d\n", getpid()); // Save child PID to the file
    			fclose(glpid_file);
    			
    			

    spacing = 2.0 / (liquid_plines + pill_plines);
      for (int i = 0; i < liquid_plines ; i++) {
                // bool isLiquidLine = (i < liquid_plines);
                float x = -1.0 + (i + 0.5) * spacing; // X position of the vertical line
               //  if(isLiquidLine){
                  for (int j = 0; j <numofsamplesofliquid; j++){
                  
                   num_packaged_liquid[j]=0;
                   num_approved_liquid[j]=0;
                   num_samples_liquid[j]=0;
                  
                  ballX[i][j]= x + (j % 5) * ballSpacing - 0.06;
                  ballY[i][j]= 0.3 - (j / 5) * ballSpacing;
                  
                      
               
           ballXA[i][j]= x + (j % 5) * ballSpacing - 0.06;
           ballYA[i][j]=0.3 - (j/ 5) * ballSpacing-0.5;
                  
                  
                        
           ballXP[i][j]= x + (j % 5) * ballSpacing - 0.06;
           ballYP[i][j]=0.3 - (j/ 5) * ballSpacing-1.0;
           
                  }
                  
                       for (int j = 0; j < workers_number; j++) {
                    workerXOffset[i][j] = 0.03 + (j % 2) * 0.05; // Offset to the right of the small square, space between pairs
                    workerYOffset[i][j] = (j / 2) * 0.05+0.5; // Offset between pairs
             }
             
                  }
                 
               //  }else{
                for (int i = 0; i < pill_plines ; i++) {
                cont[i]=1;
                rem[i]=0;
                itr[i]=0;
                flag[i]=0;
                  float x = -1.0 + (i+liquid_plines + 0.5) * spacing; // X position of the vertical line
                   for (int j = 0; j <numofsamplesofpill; j++){
                   num_packaged_pill[j]=0;
                   num_approved_pill[j]=0;
                   num_samples_pill[j]=0;
                     ballX[liquid_plines+i][j]= x + (j % 5) * ballSpacing - 0.06;
                     ballY[liquid_plines+i][j]= 0.3 - (j / 5) * ballSpacing;
                     
                              
                ballXA[liquid_plines+i][j]= x + (j % 5) * ballSpacing - 0.06;
                ballYA[liquid_plines+i][j]=0.3 - (j/ 5) * ballSpacing-0.5;
                
                  ballXP[liquid_plines+i][j]= x + (j % 5) * ballSpacing - 0.06;
                ballYP[liquid_plines+i][j]=0.3 - (j/ 5) * ballSpacing-1.0;
                  
                  }
                  
                       for (int j = 0; j < workers_number; j++) {
                    workerXOffset[liquid_plines+i][j] = 0.03 + (j % 2) * 0.05; // Offset to the right of the small square, space between pairs
                    workerYOffset[liquid_plines+i][j] = (j / 2) * 0.05+0.5; // Offset between pairs

                 }
                 
               //  }
                 
           
      }
     
      
      
      
        if (sigset(SIGUSR1, move_worker_liquid) == SIG_ERR) {
            perror("Signal Error\n");
            exit(-1);
        }
        
         if (sigset(SIGUSR2, move_worker_pill) == SIG_ERR) {
            perror("Signal Error\n");
            exit(-1);
        }
        
          if (sigset(SIGBUS, move_worker_to_approved_liquid) == SIG_ERR) {
            perror("Signal Error\n");
            exit(-1);
        }
        
           if (sigset(SIGHUP, move_worker_to_approved_pill) == SIG_ERR) {
            perror("Signal Error\n");
            exit(-1);
        }
         
            if (sigset(SIGXCPU, replacement) == SIG_ERR) {
            perror("Signal Error\n");
            exit(-1);
        }
    
        
           if (sigset(SIGCHLD, killProcesses) == SIG_ERR) {
            perror("Signal Error\n");
            exit(-1);
        }

       
        
        
        
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 900);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Pharmaceutical medicine inspection & packaging Simulation");
    init();
    glutDisplayFunc(display);
    glutWMCloseFunc(closeCallback);
    glutMainLoop();
    return 0;
}
