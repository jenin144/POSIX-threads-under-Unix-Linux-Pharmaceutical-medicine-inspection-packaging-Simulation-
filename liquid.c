
#include "header.h"
#include "constants.h"
#include "function.h"
#include "queue.h"
#include "semaphores.h"
#include "shared_memories.h"

pid_t gl_pid;
int damaged=0;
int approvedsamples=0;
int performAction(int energy);
void signal_handler(int sig);
void Finishsignal_handler(int sig);
void startsignal_handler(int sig);
void* checkMed(void* args);
void* packiging(void* args);
int indexx=0;
typedef void (*sighandler_t)(int);
sighandler_t sigset(int sig, sighandler_t disp);
int whichsignal ; 
int new=0;
sem_t mutex;
pthread_mutex_t count_mutex[100][100]= PTHREAD_MUTEX_INITIALIZER;
time_t start_time;
pthread_mutex_t package_mutex[100]= PTHREAD_MUTEX_INITIALIZER;
pthread_t workersid[100][100];


void ForPause(int sig){


	whichsignal =2;
	printf("fooooooooor pause signals is reached OMGGGGGGGGGGGGGGGGGGGGGGGGGGGGG whichsignal == %d\n", whichsignal);
	
	fflush(stdout);

	
	}
	

void Forcreate(int sig){



	whichsignal =1;

	printf("fooooooooor create signals is reached OMGGGGGGGGGGGGGGGGGGGGGGGGGGGGG🤮️🤮️🤮️🤮️🤮️🤮️🤮️🤮️\n");
	fflush(stdout);
 

}

int main(int argc, char** argv) {
    readFile("arguments.txt");
    pid_t parent_id = getpid();
    
    start_time = time(NULL); // Record start time of the simulation

     
     FILE* pid_read_filegl = fopen("openglid.txt", "r");
	fscanf(pid_read_filegl, "%d", &gl_pid);
	 fclose(pid_read_filegl);


    if (argc < 1) {
        perror("Argc less than 1\n");
        exit(-1);
    }

    pid_t liquid_id = getpid();

    pid_t production_lines[liquid_plines];
    FILE* pid_file = fopen("pids1.txt", "w");

    if (pid_file == NULL) {
        perror("Error opening pids.txt\n");
        exit(-1);
    }


    for (int i = 0; i < liquid_plines; i++) {
        production_lines[i] = fork();

        if (production_lines[i] == -1) {
            perror("No memory\n");
            exit(-5);
        } else if (production_lines[i] == 0) {
        
            readFile("arguments.txt");
        
        
            // Child process
            
            
            printf(" i am pid =========%d 😁️😁️😁️😁️😁️😁️😁️😁️😁️😁️😁️😁️😁️😁️😁️😁️\n" , getpid());
            fflush(stdout);
            
            for (int k = 0; k < workers_number; k++) {

                kill(gl_pid,SIGUSR1); ////ADDED BY AMAL FOR GL
                pthread_create(&workersid[i][k], NULL, checkMed, (void *)&i);
                  sleep(2);   ////ADDED BY AMAL FOR GL ((this sleep makes line  0 & 1 stop working))
            }
           
           
           
           
           while(1){
           
           whichsignal == 0;
					
	if(sigset(SIGUSR1, Forcreate) == SIG_ERR){
	perror("error\n");
	exit(-1);
	}        
           
 
	if(sigset(SIGUSR2, ForPause) == SIG_ERR){
	perror("error\n");
	exit(-1);
	}
			


		
	pause();




		if (whichsignal == 1){
			
			printf("111111111111SIGNALLLLLLLLLLLLLLLLLLLLLw🤣️🤣️🤣️🤣️🤣️🤣️🤣️🤣️🤣️🤣️🤣️🤣️🤣️🤣️🤣️🤣️🤣️🤣️🤣️🤣️🤣️which ===== %d  process === %d\n", whichsignal, getpid());
			fflush(stdout);
	
              	     pthread_create(&workersid[i][workers_number+new], NULL, checkMed, (void *)&i);
			new++;
			printf("newwwww in %d🤣️🤣️🤣️🤣️🤣️🤣️🤣️🤣️🤣️🤣️🤣️🤣️🤣️🤣️🤣️🤣️🤣️🤣️🤣️🤣️🤣️\n", i);
					fflush(stdout);
			}
			
		
             		else if(whichsignal = 2){
			printf("2222222SIGNALLLLLLLLLLLLLLLLLLLLLw🤣️🤣️🤣️🤣️🤣️🤣️🤣️🤣️🤣️🤣️🤣️🤣️🤣️🤣️🤣️🤣️🤣️🤣️🤣️🤣️🤣️ which ===== %d  processs %d\n", whichsignal,getpid());
			fflush(stdout);
	
			pthread_cancel(workersid[i][workers_number-1]);   
			
			}

           
           
             
           }
           
           
       
           

            for (int k = 0; k < workers_number; k++) {
                pthread_join(workersid[i][k], NULL);
            }
            
            // Exit the child process
            exit(0);
        } else {
            // Parent process
            fprintf(pid_file, "%d\n", production_lines[i]);
            printf("-----> The liquid production line file, create the production line number %d with id %d\n", i, production_lines[i]);
        }
    }

    fclose(pid_file);

    if (parent_id == getpid()) { // Parent process logic

    
		     int shmid2 = shmget(liquiqFor_AcceptedAndpackagededSamplesCount_key, SHM_SIZE, IPC_CREAT | 0666);
		    if (shmid2 == -1) {
		        perror("shmget");
		        exit(EXIT_FAILURE);
		    }
		    liquiqFor_AcceptedAndpackagededSamplesCount *liquidsharedmem = (liquiqFor_AcceptedAndpackagededSamplesCount *)shmat(shmid2, NULL, 0);
		    if (liquidsharedmem == (void *)-1) {
		        perror("shmat pill line 205");
		        exit(EXIT_FAILURE);
		    }
		    
		                int once=1;
	while(time(NULL) - start_time < runduration){
/////////////////////////////////////  
      while (time(NULL) - start_time > runduration/2  &&  once ==1) {
	once=0;
         damaged=0;	    
	 for(int o=0; o<liquid_plines; o++){
   	 damaged+= (liquidsharedmem->checked_Samples[o]-liquidsharedmem->Approved_Samples[o]);
   	 }
		    
		    
		if(damaged>canceledliquid){
	
		 
    
    printf("FINISH KILLINGGGGGGGGG by liquid damaged!!!!!!!!!!!! ==%d🔪️🔪️🔪️🔪️🔪️🔪️🔪️🔪️🔪️🔪️🔪️🔪️🔪️🔪️🔪️🔪️🔪️🔪️🔪️🔪️🔪️🔪️🔪️🔪️🔪️🔪️🔪️🔪️🔪️🔪️🔪️🔪️\n",damaged);
    fflush(stdout);
    
    
    
	     kill(gl_pid,SIGCHLD);
           	break;
	
	}

        }
/////////////////////////////////////     
        
    }}

    return 0;
}

void* packiging(void* args) {
    pthread_t thread_id = pthread_self();
    int i = *((int*) args);
    
    
     int last_state,last_type;   
  pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, &last_state);   
  pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, &last_type);   
    
    
    printf("😋️😋️😋️😋️😋️😋️😋️😋️😋️😋️😋️😋️😋️😋️😋️😋️😋️😋️😋️😋️hiiiiiiiiii i am thread %lu from production line %d\n", (unsigned long)thread_id, i);
    fflush(stdout);
sleep(5);
      int shmid;
            checkedsharedmemory *shared_memory2;


            shmid = shmget(0x2000+i, SHM_SIZE, IPC_CREAT | 0666);
            shared_memory2 = (checkedsharedmemory *)shmat(shmid, NULL, 0);
            liquidsharedmemory *shared_memory;
            shmid = shmget(i+1, SHM_SIZE, IPC_CREAT | 0666);
            shared_memory = (liquidsharedmemory *)shmat(shmid, NULL, 0);
            shmid = shmget(liquiqFor_AcceptedAndpackagededSamplesCount_key, SHM_SIZE, IPC_CREAT | 0666);
             liquiqFor_AcceptedAndpackagededSamplesCount *numofpackaged = (liquiqFor_AcceptedAndpackagededSamplesCount *)shmat(shmid, NULL, 0);



    while (1) {
       

           // int found_unchecked_sample = 0; // Flag to indicate if an unchecked sample was found
            for (int j = 0; j < numofsamplesofliquid; j++) {
 
            int rc = pthread_mutex_trylock(&package_mutex[i]);
        if (rc == !EBUSY) { // Successfully locked the mutex
           
    
           
           
                if (shared_memory2->accepted[j] == 1) {
                
                //sleep(3);
                
		    numofpackaged->packaged_Samples[i]++;

                    printf("😎️😎️😎️😎️😎️😎️😎️😎️😎️😎️😎️Thread %lu from production line %d found accepted sample %d , (((NumberOF packaged Samples = %d))\n", (unsigned long)thread_id, i, j, numofpackaged->packaged_Samples[i]);
                    fflush(stdout);

			///*********************************
			



		   int shmid = shmget(Approved_LiqSamples_SHM_key+ i , SHM_SIZE, IPC_CREAT | 0666);
		    Approved_LiqSamples_SHM *Approved_LiqSamples_SHMm = (Approved_LiqSamples_SHM *)shmat(shmid, NULL, 0);




		    Approved_LiqSamples_SHMm->Approved[indexx].Persrciptions=1;
		    Approved_LiqSamples_SHMm->Approved[indexx].liquid.level=shared_memory->liquid[j].level;
		    Approved_LiqSamples_SHMm->Approved[indexx].liquid.lable=shared_memory->liquid[j].lable;
		    Approved_LiqSamples_SHMm->Approved[indexx].liquid.dateprinted=shared_memory->liquid[j].dateprinted;
		    Approved_LiqSamples_SHMm->Approved[indexx].liquid.color=shared_memory->liquid[j].color;
		    Approved_LiqSamples_SHMm->Approved[indexx].liquid.sealed=shared_memory->liquid[j].sealed;

		    		    	indexx++;	    		    

  		printf("🛄️🛄️🛄️🛄️🛄️🛄️🛄️The packaged sample percption is  %d and its level = %d  , color = %c\n",Approved_LiqSamples_SHMm->Approved[j].Persrciptions, Approved_LiqSamples_SHMm->Approved[j].liquid.level , Approved_LiqSamples_SHMm->Approved[j].liquid.color);
                    fflush(stdout);
 	
                  


			//****************************
                    sleep(4);                    
                    shared_memory2->accepted[j] = 0;
                    
                }
                
                                pthread_mutex_unlock(&package_mutex[i]);
                                                pthread_testcancel();   
            }
            else {
            if(j==numofsamplesofliquid-1){
               kill(gl_pid,SIGUSR1);  //ADDED BY AMAL FOR GL 
                pthread_testcancel();   
            	checkMed((void *)&i);

            	
            }

		
            
            }
            }


    }
    pthread_exit(NULL);
    
    }
void* checkMed(void* args) {
    pthread_t thread_id = pthread_self();
    int i = *((int*) args);
     int last_state,last_type;   
  pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, &last_state);   
  pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, &last_type);   
    printf("🤩️🤩️🤩️🤩️🤩️🤩️🤩️🤩️🤩️🤩️🤩️Thread %lu  form process %dchecking production line %d\n", (unsigned long)thread_id,getpid(), i);
    fflush(stdout);
    
    
            int shmid;
            liquidsharedmemory *shared_memory;

            // Create the shared memory segment
            shmid = shmget(i+1, SHM_SIZE, IPC_CREAT | 0666);
            // Attach the shared memory segment to the process's address space
            shared_memory = (liquidsharedmemory *)shmat(shmid, NULL, 0);
     
            
            int shmid2;
            checkedsharedmemory *shared_memory2;

            shmid2 = shmget(0x2000+i, SHM_SIZE, IPC_CREAT | 0666);     
            shared_memory2 = (checkedsharedmemory *)shmat(shmid2, NULL, 0);
            
                                               
                            
		    shmid = shmget(liquiqFor_AcceptedAndpackagededSamplesCount_key, SHM_SIZE, IPC_CREAT | 0666);

		    liquiqFor_AcceptedAndpackagededSamplesCount *shmforcount = (liquiqFor_AcceptedAndpackagededSamplesCount *)shmat(shmid, NULL, 0);
   

    while (1) {
       
       


           // int found_unchecked_sample = 0; // Flag to indicate if an unchecked sample was found
            for (int j = 0; j < numofsamplesofliquid; j++) {
            
            int rc = pthread_mutex_trylock(&count_mutex[i][j]);
        if (rc == !EBUSY) { // Successfully locked the mutex
           
                if (shared_memory2->check[j]== 0) {
                                    shared_memory2->check[j]= 1;
                                //    sleep(3);
                                   shmforcount->checked_Samples[i]++;

                    printf("⛔️Thread %lu from production line %d found unchecked sample %d\n", (unsigned long)thread_id, i, j);
                    fflush(stdout);

                   
                   
                    printf("❓️❓️❓️❓️❓️❓️☑️Sample %d from %d checked by thread %lu , number of ((checked_Samples = %d))\n", j, i,(unsigned long)thread_id,shmforcount->checked_Samples[i] );
                    fflush(stdout);




                    if (shared_memory->liquid[j].level >= min_level && shared_memory->liquid[j].level <= max_level) {
                        if (shared_memory->liquid[j].color == COLOR[shared_memory->liquid[j].correctcolor] ) {
                        if(shared_memory->liquid[j].sealed==1&&shared_memory->liquid[j].lable==1&&shared_memory->liquid[j].dateprinted==1){
                        
                        	    	    

			    // Extract year, month, and day from the concatenated string
			    char yearStr[5], monthStr[3], dayStr[3];
			    strncpy(yearStr, shared_memory->liquid[j].actualDate, 4);
			    yearStr[4] = '\0';
			    strncpy(monthStr, shared_memory->liquid[j].actualDate + 4, 2);
			    monthStr[2] = '\0';
			    strncpy(dayStr, shared_memory->liquid[j].actualDate + 6, 2);
			    dayStr[2] = '\0';

			    // Convert extracted strings back to integers
			    int extractedYear = atoi(yearStr);
			    int extractedMonth = atoi(monthStr);
			    int extractedDay = atoi(dayStr);


           
     	if(  shared_memory->liquid[j].properdate.day  == extractedDay &&  shared_memory->liquid[j].properdate.month== extractedMonth &&  shared_memory->liquid[j].properdate.year==extractedYear){
     	
                            shared_memory2->accepted[j] = 1;
                            
                            

			  //    shmforcount->checked_Samples[i]++;
		              shmforcount->Approved_Samples[i]++;
		              
                printf("✅️✅️✅️✅️✅️🥶️🥶️🥶️Sample %d from prduction line%d accepted by thread %lu ,((( ApprovedSamples = %d))) +++++++++++++++++++++ canceled = %d\n", j, i,(unsigned long)thread_id,    shmforcount->Approved_Samples[i], shmforcount->checked_Samples[i]-shmforcount->Approved_Samples[i]);
                            fflush(stdout);
                            

                            
                       }
                        }
                        }
                    }
                    
 

                    sleep(4);

                }
                

                
                
                
                                pthread_mutex_unlock(&count_mutex[i][j]);
                                   pthread_testcancel();   
                                
                
             //   break;
            }
            else {
            
            if (j==numofsamplesofliquid-1){
          
            		 kill(gl_pid,SIGBUS);  /////ADDED BY AMAL FOR GL
            		pthread_testcancel();   
            		packiging((void *)&i);
            		sleep(3);    /////ADDED BY AMAL FOR GL
            		
            }
           

		
            
            }
            }//for

       

            // Unlock the mutex
            //pthread_mutex_unlock(&count_mutex[i]);

     
    }//while

    printf("Thread %lu has finished processing.\n", (unsigned long)thread_id);
    fflush(stdout);
    pthread_exit(NULL);
}


int performAction(int energy) {
    int energyPause = (110 - energy) / 3;
    sleep(energyPause);

    if (energy > 40) {
        int randomConsumption = rand() % 5 + 1;
        return energy - randomConsumption;
    } else {
        return energy;
    }
}


