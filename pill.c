#include "header.h"
#include "constants.h"
#include "function.h"
#include "queue.h"
#include "semaphores.h"
#include "shared_memories.h"


pid_t gl_pid;
int approvedsamples=0;
int damaged=0;
int performAction(int energy);
void signal_handler(int sig);
void Finishsignal_handler(int sig);
void startsignal_handler(int sig);
void* checkMed(void* args);
void* packiging(void* args);
int indexx=0;

int indexx2=0;

time_t start_time;

typedef void (*sighandler_t)(int);
sighandler_t sigset(int sig, sighandler_t disp);
int whichsignal ; 
int new=0;
sem_t mutex;
pthread_mutex_t count_mutex[100][100]= PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t package_mutex[100]= PTHREAD_MUTEX_INITIALIZER;
pthread_t workersid[100][100];

void ForPause(int sig){


	whichsignal =2;
	printf("fooooooooor pause signals is reached OMGGGGGGGGGGGGGGGGGGGGGGGGGGGGG whichsignal == %d🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️\n", whichsignal);
	
	fflush(stdout);

	
	}
	
void goPause(int sig){

	printf("thread is enter pauseeee🥸️🥸️🥸️🥸️🥸️🥸️🥸️🥸️🥸️🥸️🥸️🥸️🥸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️\n");
	fflush(stdout);
	  pthread_t thread_id = pthread_self();
	 printf("🤩️🤩️🤩️🤩️🤩️🤩️🤩️🤩️🤩️🤩️🤩️Thread %lu  form process %d🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️\n", (unsigned long)thread_id,getpid());
   	 fflush(stdout);

		pause();	
}

void Forcreate(int sig){

	whichsignal =1;

	printf("fooooooooor create signals is reached OMGGGGGGGGGGGGGGGGGGGGGGGGGGGGG🤮️🤮️🤮️🤮️🤮️🤮️🤮️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️\n");
	fflush(stdout);
}

int main(int argc, char** argv) {
    readFile("arguments.txt");
    pid_t parent_id = getpid();
    
        start_time = time(NULL); // Record start time of the simulation

    if (argc < 1) {
        perror("Argc less than 1\n");
        exit(-1);
    }
    
    
    
    		FILE* pid_read_filegl = fopen("openglid.txt", "r");
		fscanf(pid_read_filegl, "%d", &gl_pid);
		 fclose(pid_read_filegl);
		    
    
    
    int  liquidpid = atoi(argv[1]); 

    pid_t pill_id = getpid();
    //pthread_t workersid[pill_plines][workers_number];
    pid_t production_lines[pill_plines];
    FILE* pid_file = fopen("pids2.txt", "w");

    if (pid_file == NULL) {
        perror("Error opening pids.txt\n");
        exit(-1);
    }


    for (int i = 0; i < pill_plines; i++) {
        production_lines[i] = fork();

        if (production_lines[i] == -1) {
            perror("No memory\n");
            exit(-5);
        } else if (production_lines[i] == 0) {
        
            readFile("arguments.txt");
        
        
            // Child process
            
            
            printf(" i am pid =========%d 😁️😁️😁️😁️😁️😁️😁️😁️😁️😁️😁️😁️😁️😁️😁️😁️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️\n" , getpid());
            fflush(stdout);
            
            for (int k = 0; k < workers_number; k++) {

                      kill(gl_pid,SIGUSR2); ////ADDED BY AMAL FOR GL
                pthread_create(&workersid[i][k], NULL, checkMed, (void *)&i);
                sleep(2);  ////ADDED BY AMAL FOR GL            
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
	
	printf("🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️\n" );
			fflush(stdout);

		




		if (whichsignal == 1){
			
			printf("111111111111SIGNALLLLLLLLLLLLLLLLLLLLLw🤣️🤣️🤣️🤣️🤣️🤣️🤣️🤣️🤣️🤣️🤣️🤣️🤣️🤣️🤣️🤣️🤣️🤣️🤣️🤣️🤣️which ===== %d  process === %d🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️\n", whichsignal, getpid());
			fflush(stdout);
	
              	     pthread_create(&workersid[i][workers_number+new], NULL, checkMed, (void *)&i);
			new++;
			printf("newwwww in %d🤣️🤣️🤣️🤣️🤣️🤣️🤣️🤣️🤣️🤣️🤣️🤣️🤣️🤣️🤣️🤣️🤣️🤣️🤣️🤣️🤣️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️\n", i);
					fflush(stdout);
			}
			
		
             		else if(whichsignal = 2){
			printf("2222222SIGNALLLLLLLLLLLLLLLLLLLLLw🤣️🤣️🤣️🤣️🤣️🤣️🤣️🤣️🤣️🤣️🤣️🤣️🤣️🤣️🤣️🤣️🤣️🤣️🤣️🤣️🤣️ which ===== %d  processs %d🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️\n", whichsignal,getpid());
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
            printf("-----> The pill production line file, create the production line number %d with id %d🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️\n", i, production_lines[i]);
        }
    }

    fclose(pid_file);

    if (parent_id == getpid()) { // Parent process logic
    
    int shmid = shmget(pillFor_AcceptedAndpackagededSamplesCount_key, SHM_SIZE, IPC_CREAT | 0666);
		    if (shmid == -1) {
		        perror("shmget");
		        exit(EXIT_FAILURE);
		    }
		    pillFor_AcceptedAndpackagededSamplesCount *pillsharedmem = (pillFor_AcceptedAndpackagededSamplesCount *)shmat(shmid, NULL, 0);
		    if (pillsharedmem == (void *)-1) {
		        perror("shmat pill line 190");
		        exit(EXIT_FAILURE);
		    }
		    
		    
		    
		    
		    
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
        while (time(NULL) - start_time > runduration/2  &&  once ==1) {
       
        once=0;
         approvedsamples=0;
         damaged=0;
		 
		    
		     for(int o=0;o<liquid_plines;o++){
   	approvedsamples += liquidsharedmem->Approved_Samples[o];
   	 }
   	 
   	  for(int o=0;o<pill_plines;o++){
   	approvedsamples += pillsharedmem->Approved_Samples[o];
   	   	 damaged+= (pillsharedmem->checked_Samples[o]-pillsharedmem->Approved_Samples[o]);
   	 }
   	
 	 
   	 if(approvedsamples>=medicinenum){
   	 		 

    printf("FINISH KILLINGGGGGGGGG by the approvedsamples!!!!!!!!!!!!!!!!!!!!!!!!!! = %d🔪️🔪️🔪️🔪️🔪️🔪️🔪️🔪️🔪️🔪️🔪️🔪️🔪️🔪️🔪️🔪️🔪️🔪️🔪️🔪️🔪️🔪️🔪️🔪️🔪️🔪️🔪️🔪️🔪️🔪️🔪️🔪️\n", approvedsamples);
    fflush(stdout);
    
    
     kill(gl_pid,SIGCHLD);
     	break;
 
	}
	
	if(damaged>canceledpill){
	
	 
    
    printf("FINISH KILLINGGGGGGGGG by pill damaged!!!!!!!!!!!! ==%d🔪️🔪️🔪️🔪️🔪️🔪️🔪️🔪️🔪️🔪️🔪️🔪️🔪️🔪️🔪️🔪️🔪️🔪️🔪️🔪️🔪️🔪️🔪️🔪️🔪️🔪️🔪️🔪️🔪️🔪️🔪️🔪️\n",damaged);
    fflush(stdout);
    
	
	           
     kill(gl_pid,SIGCHLD);
	break;

	}
        }
        }
    }

    return 0;
}

void* packiging(void* args) {
    pthread_t thread_id = pthread_self();
    int i = *((int*) args);
     int last_state,last_type;   
  pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, &last_state);   
  pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, &last_type);   
  
  
    printf("😋️😋️😋️😋️😋️😋️😋️😋️😋️😋️😋️😋️😋️😋️😋️😋️😋️😋️😋️😋️hiiiiiiiiii i am thread %lu from production line %d🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️\n", (unsigned long)thread_id, i);
    fflush(stdout);
sleep(5);
      int shmid;
            checkedpillsharedmemory *shared_memory2;


            shmid = shmget(0x3000+i, SHM_SIZE, IPC_CREAT | 0666);
            shared_memory2 = (checkedpillsharedmemory *)shmat(shmid, NULL, 0);
            pillsharedmemory *shared_memory;
            shmid = shmget(0x4000+i, SHM_SIZE, IPC_CREAT | 0666);
            shared_memory = (pillsharedmemory *)shmat(shmid, NULL, 0);
            shmid = shmget(pillFor_AcceptedAndpackagededSamplesCount_key, SHM_SIZE, IPC_CREAT | 0666);
             pillFor_AcceptedAndpackagededSamplesCount *numofpackaged = (pillFor_AcceptedAndpackagededSamplesCount *)shmat(shmid, NULL, 0);
             shmid = shmget(0x8000+i, SHM_SIZE, IPC_CREAT | 0666);
             Approved_PillSamples_SHM *Approved_PillSamples_SHMm = (Approved_PillSamples_SHM *)shmat(shmid, NULL, 0);  
       
       

            int rc = pthread_mutex_trylock(&package_mutex[i]);
   	  if (rc == !EBUSY) { // Successfully locked the mutex
	
		  	    

		    if(Approved_PillSamples_SHMm->Approved[indexx].numofcontainers==0){
		        printf(" BEFOREEE🎀️🎀️🎀️🎀️🎀️🎀️🎀️🎀️🎀️🎀️🎀️🎀️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️  %d  🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️ in %d\n",  Approved_PillSamples_SHMm->Approved[indexx].numofcontainers,i);
		  fflush(stdout);
		    
		    
		    Approved_PillSamples_SHMm->Approved[indexx].numofcontainers=shared_memory->pill[0].numofcontainers;
		    
		      printf(" AFTERRR🎀️🎀️🎀️🎀️🎀️🎀️🎀️🎀️🎀️🎀️🎀️🎀️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️  %d  🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️ in %d\n",  Approved_PillSamples_SHMm->Approved[indexx].numofcontainers,i);
		  fflush(stdout);

		    	}
		    		    	
			int index2 =0 ;
	    	
	    		while ( Approved_PillSamples_SHMm->Approved[indexx].numofcontainers>0){
	    		
	    		
	    		
	    		for(int p=0 ; p<numofsamplesofpill ; p++){
	    		
	    	          if (shared_memory2->accepted[p] == 1  && Approved_PillSamples_SHMm->Approved[indexx].numofcontainers > 0 ) {
	    		
	    	    Approved_PillSamples_SHMm->Approved[indexx].pill[index2].size = shared_memory->pill[p].size;
	    	    Approved_PillSamples_SHMm->Approved[indexx].pill[index2].color=shared_memory->pill[p].color;
	    	    Approved_PillSamples_SHMm->Approved[indexx].pill[ index2].dateprinted=shared_memory->pill[p].dateprinted;
		    Approved_PillSamples_SHMm->Approved[indexx].pill[index2].properdate=shared_memory->pill[p].properdate;
		  
			  index2++;
		  		
	    		Approved_PillSamples_SHMm->Approved[indexx].numofcontainers--;
	    		                  shared_memory2->accepted[p] = 0;
	    		                  
	    		                  if(shared_memory->pill[0].numofcontainers == index2){
	    		                 // sleep(5);
	    		                   numofpackaged->packaged_Samples[i]++;
	    		                   Approved_PillSamples_SHMm->Approved[indexx].Persrciptions=1;
	    		                   }
	    		                  
	    	 printf("🎀️🎀️🎀️🎀️🎀️🎀️🎀️🎀️🎀️🎀️🎀️🎀️🎀️🎀️🎀️🎀️🎀️ in indexx =%d with container number %d in line %d  🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️\n", indexx , index2, i);
                   fflush(stdout);               
	    		                  
	    		}
	    			
	    		}
	    	
	   	 	}



            printf("🎀️🎀️🎀️🎀️🎀️🎀️🎀️🎀️🎀️🎀️🎀️🎀️🎀️🎀️🎀️🎀️🎀️Thread %lu from production line %d complete packaging the full containers of the pill , NumberOF packaged Samples = %d🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️\n", (unsigned long)thread_id, i, numofpackaged->packaged_Samples[i]);
                   fflush(stdout);

//packaged smaple
 		printf("🛄️🛄️🛄️🛄️🛄️🛄️🛄️The packaged pill of %d containers percption is  %d and its dateprinted = %d  , pill size = %d🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️\n",shared_memory->pill[0].numofcontainers,Approved_PillSamples_SHMm->Approved[indexx].Persrciptions, Approved_PillSamples_SHMm->Approved[indexx].pill[0].dateprinted , Approved_PillSamples_SHMm->Approved[indexx].pill[0].size);
                    fflush(stdout);
		

	    	
	    	    		index2=0;
	    	    		indexx++;
	          //  numofpackaged->packaged_Samples[i]++;

 
	    	
	   
                    sleep(4);                                    
                    pthread_mutex_unlock(&package_mutex[i]);
                    pthread_testcancel();   
          
            }
            else {
              kill(gl_pid,SIGUSR2);  //ADDED BY AMAL FOR GL 
               pthread_testcancel();   
            	checkMed((void *)&i);
            	//sleep(3);    //ADDED BY AMAL FOR GL
            }
            


    }
void* checkMed(void* args) {
            readFile("arguments.txt");

    pthread_t thread_id = pthread_self();
    int i = *((int*) args);

 int last_state,last_type;   
  pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, &last_state);   
  pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, &last_type);   


    printf("🤩️🤩️🤩️🤩️🤩️🤩️🤩️🤩️🤩️🤩️🤩️Thread %lu  form process %dchecking production line %d🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️\n", (unsigned long)thread_id,getpid(), i);
    fflush(stdout);
    
            int shmid;
            pillsharedmemory *shared_memory;

            // Create the shared memory segment
            shmid = shmget(0x4000+i, SHM_SIZE, IPC_CREAT | 0666);
            // Attach the shared memory segment to the process's address space
            shared_memory = (pillsharedmemory *)shmat(shmid, NULL, 0);
     
            
            int shmid2;
            checkedpillsharedmemory *shared_memory2;

            shmid2 = shmget(0x3000+i, SHM_SIZE, IPC_CREAT | 0666);     
            shared_memory2 = (checkedpillsharedmemory *)shmat(shmid2, NULL, 0);
            
                                               
                            
		    shmid = shmget(pillFor_AcceptedAndpackagededSamplesCount_key, SHM_SIZE, IPC_CREAT | 0666);

		   pillFor_AcceptedAndpackagededSamplesCount *shmforcount = (pillFor_AcceptedAndpackagededSamplesCount *)shmat(shmid, NULL, 0);
   

    while (1) {
       
       


           // int found_unchecked_sample = 0; // Flag to indicate if an unchecked sample was found
            for (int j = 0; j < numofsamplesofpill; j++) {
            
            int rc = pthread_mutex_trylock(&count_mutex[i][j]);
        if (rc == !EBUSY) { // Successfully locked the mutex
           
                if (shared_memory2->check[j]== 0) {
                                    shared_memory2->check[j]= 1;
                                   // sleep(3);
                                       shmforcount->checked_Samples[i]++;

                    printf("⛔️Thread %lu from production line %d found unchecked sample %d🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️\n", (unsigned long)thread_id, i, j);
                    fflush(stdout);

               
                   
                    
                    
                   printf("❓️❓️❓️❓️❓️❓️☑️Sample %d from %d checked by thread %lu , number of checked_Samples = %d🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️☑️☑️☑️☑️☑️\n", j, i,(unsigned long)thread_id,shmforcount->checked_Samples[i] );
                    fflush(stdout);





                    if (shared_memory->pill[j].size >= min_size && shared_memory->pill[j].size <= max_size) {
                        if (shared_memory->pill[j].color == COLOR[shared_memory->pill[j].correctcolor] ) {
                        if(shared_memory->pill[j].filledcontainers==CONTAINERSNUM[shared_memory->pill[j].correctpillsnum]&&shared_memory->pill[j].dateprinted==1){
                        
                     
			    // Extract year, month, and day from the concatenated string
			    char yearStr[5], monthStr[3], dayStr[3];
			    strncpy(yearStr, shared_memory->pill[j].actualDate, 4);
			    yearStr[4] = '\0';
			    strncpy(monthStr, shared_memory->pill[j].actualDate + 4, 2);
			    monthStr[2] = '\0';
			    strncpy(dayStr, shared_memory->pill[j].actualDate + 6, 2);
			    dayStr[2] = '\0';

			    // Convert extracted strings back to integers
			    int extractedYear = atoi(yearStr);
			    int extractedMonth = atoi(monthStr);
			    int extractedDay = atoi(dayStr);


           
     	if(  shared_memory->pill[j].properdate.day  == extractedDay &&  shared_memory->pill[j].properdate.month== extractedMonth &&  shared_memory->pill[j].properdate.year==extractedYear){
     	
                            shared_memory2->accepted[j] = 1;
		              shmforcount->Approved_Samples[i]++;
		          

                           printf("✅️✅️✅️✅️✅️🥶️🥶️🥶️Sample %d from prduction line%d accepted by thread %lu , ApprovedSamples = %d🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️\n", j, i,(unsigned long)thread_id,    shmforcount->Approved_Samples[i]);
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
            
            if (j==numofsamplesofpill-1){
          
                        kill(gl_pid,SIGHUP);  ///ADDED BY AMAL FOR GL
                        pthread_testcancel();   
            		packiging((void *)&i);
            		sleep(3);  ///ADDED BY AMAL FOR GL
            }
           

		
            
            }
            }//for

       


     
    }//while

    printf("Thread %lu has finished processing.🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️🇵🇸️\n", (unsigned long)thread_id);
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


