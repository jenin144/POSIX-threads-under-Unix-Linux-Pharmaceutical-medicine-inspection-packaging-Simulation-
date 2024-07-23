
#include "header.h"
#include "constants.h"
#include "function.h"
#include "queue.h"
#include "semaphores.h"
#include "shared_memories.h"

pid_t gl_pid;
time_t start_time;
void create_shared_memorypill();
void create_shared_memorycheck();
void create_shared_memoryliquid();
void create_shared_memoryforSharedCount();
void create_shared_memoryforSharedPillCount();
void create_approvedpillsharedmem();
void create_pillshared_memorycheck();
void create_shared_replace();



 pid_t liquid_pid, pill_pid;	

int main(){


	readFile("arguments.txt");
	
	
         pid_t glpid = fork();
   	 
   	 if(glpid == 0 ){
   	 execlp("./gl","gl",NULL);
   	 perror("ERROR Execute GL\n");
   	 }
   	 
   	 
   	 sleep(2);

 	start_time = time(NULL); // Record start time of the simulation
	 time_t lastenter = time(NULL) ;		
			 
			    	 

   	  


	pid_t parent_id = getpid();

        create_shared_memoryliquid();
        create_shared_memorycheck();
        create_shared_memoryforSharedCount();
        create_shared_memorypill();
        create_shared_memoryforSharedPillCount();
        create_approvedpillsharedmem();
        create_pillshared_memorycheck();
        create_shared_replace();
   	 pid_t production_line[2];
   	 
   	 
   	
for (int i = 0; i < 2; ++i) {
        production_line[i] = fork();
        // the team will continue from here
        if(production_line[i] == -1){
            perror("No memory\n");
            exit(-5);
        } else if(production_line[i] == 0){
        
	if (i == 0) {
	     
		printf("Liquid Production Line (PID: %d)\n", getpid()); // Liquid Production Line go to liquid.c file 
		 execlp("./liquid", "liquid" , NULL); // i can  pass any number of arguments
		// If exec fails
		    perror("Exec failed\n");
		    exit(-1);
		
	 } else {
	 char liquidpid[20];
	 	    sprintf(liquidpid, "%d", production_line[0]); // Convert energy1 to a string
		 printf("Pill Production Line (PID: %d)\n", getpid()); // Pill Production Line go to pill.c file 
		// pause();
		 execlp("./pill", "pill",liquidpid, NULL);
		    perror("Exec failed\n");
		    exit(-1);
		}

        
        }else{
	if (i==0){
            printf("The main file, create the Liquid Production Line with id = %d\n", production_line[i]);
        }        
        else{
        
            printf("The main file, create the Pill Production Line with id = %d\n", production_line[i]);
        }

        }
    }
        if (parent_id == getpid()) { // Parent process logic
                     srand(time(NULL)); // Seed the random number generator
                     
                    
    
    
      FILE *file = fopen("process_ids.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Write process IDs to the file
    fprintf(file, "%d\n", production_line[0]);
    fprintf(file, "%d\n", production_line[1]);
    fprintf(file, "%d\n", getpid());

    // Close the file
    fclose(file);
    
 
    
           FILE* pid_file = fopen("pids1.txt", "r");   //liquid
           FILE* pid2_file = fopen("pids2.txt", "r");    //pill
           
           
               	int shmid = shmget(liquiqFor_AcceptedAndpackagededSamplesCount_key, SHM_SIZE, IPC_CREAT | 0666);

	    liquiqFor_AcceptedAndpackagededSamplesCount *shmforcountliquid = (liquiqFor_AcceptedAndpackagededSamplesCount *)shmat(shmid, NULL, 0);
           
           
         shmid = shmget(pillFor_AcceptedAndpackagededSamplesCount_key, SHM_SIZE, IPC_CREAT | 0666);

	pillFor_AcceptedAndpackagededSamplesCount *shmforcountpill = (pillFor_AcceptedAndpackagededSamplesCount *)shmat(shmid, NULL, 0); 
	
	
	    int shmid2 = shmget(replace_key, SHM_SIZE, IPC_CREAT | 0666);    //added by amal for gl

	    replace *replaceShm= (replace *)shmat(shmid2, NULL, 0);     //added by amal for gl
           
    double throughput[100];
    double throughput_pill[100];



     pid_t pid;
     
     
      	
 	    FILE* pid_read_filegl = fopen("openglid.txt", "r");
			 fscanf(pid_read_filegl, "%d", &gl_pid);
			 fclose(pid_read_filegl);

			 
    		while (time(NULL) - start_time < runduration) {




	if( time(NULL) - lastenter > 20) {  // more than half of time is passed
	    int min_index = -1;
	    int max_index = -1;
	    int min_type = -1; // 0 for liquid, 1 for pill
	    int max_type = -1; // 0 for liquid, 1 for pill
	    double min_throughput = __DBL_MAX__;
	    double max_throughput = -__DBL_MAX__;
	    
    
	lastenter = time(NULL) ;
	while(min_index == max_index ){
        for (int n = 0; n < liquid_plines; n++) {
            throughput[n] = (double) shmforcountliquid->Approved_Samples[n]/ shmforcountliquid->checked_Samples[n] ;

            if (throughput[n] < min_throughput) {
                min_throughput = throughput[n];
                min_index = n;
                min_type = 0; // liquid
                replaceShm->minType=0;  //ADDED BY AMAL FOR GL
                replaceShm->minIndex=n;  //ADDED BY AMAL FOR GL
             
                
                
            }

            if (throughput[n] > max_throughput) {
                max_throughput = throughput[n];
                max_index = n;
                max_type = 0; // liquid
                replaceShm->maxType=0; //ADDED BY AMAL FOR GL
                replaceShm->maxIndex=n; //ADDED BY AMAL FOR GL
                 
            }
        }

        for (int n = 0; n < pill_plines; n++) {
            throughput_pill[n] = (double)shmforcountpill->Approved_Samples[n]  / shmforcountpill->checked_Samples[n] ;

            if (throughput_pill[n] < min_throughput) {
                min_throughput = throughput_pill[n];
                min_index = n;
                min_type = 1; // pill
                replaceShm->minType=1;//ADDED BY AMAL FOR GL
                replaceShm->minIndex=n;//ADDED BY AMAL FOR GL
            }

            if (throughput_pill[n] > max_throughput) {
                max_throughput = throughput_pill[n];
                max_index = n;
                max_type = 1; // pill
                replaceShm->maxType=1;  //ADDED BY AMAL FOR GL
                replaceShm->maxIndex=n; //ADDED BY AMAL FOR GL
               //  kill(gl_pid,SIGILL);   //ADDED BY AMAL FOR GL
            }
        }
        
        
		if (min_index != max_index ){
    printf("👑️👑️👑️👑️👑️👑️👑️👑️👑️👑️👑️👑️👑️👑️👑️Minimum throughput is on %d , line = %d with value %.2f👑️👑️👑️👑️👑️👑️👑️👑️👑️👑️\n", min_type, min_index, min_throughput);
    fflush(stdout);
    printf("👑️👑️👑️👑️👑️👑️👑️👑️👑️👑️👑️👑️👑️👑️Maximum throughput is on %d, line = %d with value %.2f👑️👑️👑️👑️👑️👑️👑️👑️👑️👑️\n", max_type, max_index, max_throughput);
    fflush(stdout);

        
         
        ////////////
        
        
        
        	 int k=0;
        	 
        	 
        	 if(min_type ==0 || max_type==0){//liquid
        	         	         	 
        	  while (fscanf(pid_file, "%d\n", &pid) == 1) {
		 
 		  if (k== min_index && min_type==0 ){
		

     		//min
     		  if (kill(pid, SIGUSR1) == 0) {
                printf("Successfully sent SIGUSR1 to pid %d\n", pid);
                  
            } else {
                perror("Failed to send SIGUSR1");
            }
            printf("  MIN pid =========%d   in liquid😶‍🌫️️😶‍🌫️️😶‍🌫️️😶‍🌫️️😶‍🌫️️😶‍🌫️️😶‍🌫️️😶‍🌫️️😶‍🌫️️😶‍🌫️️😶‍🌫️️😶‍🌫️️😶‍🌫️️😶‍🌫️️😶‍🌫️️😶‍🌫️️😶‍🌫️️😶‍🌫️️😶‍🌫️️😶‍🌫️️😶‍🌫️️😶‍🌫️️😶‍🌫️️😶‍🌫️️\n" , pid);
            fflush(stdout);     		 
     		 sleep(2);
		}
		
		else if(k == max_index && max_type==0){
		
     		     //max
     		     if (kill(pid, SIGUSR2) == 0) {
                printf("Successfully sent SIGUSR1 to pid %d\n", pid);
                
               
            } else {
                perror("Failed to send SIGUSR1");
            }
	 printf("  MAX pid =========%d in liquid😶‍🌫️️😶‍🌫️️😶‍🌫️️😶‍🌫️️😶‍🌫️️😶‍🌫️️😶‍🌫️️😶‍🌫️️😶‍🌫️️😶‍🌫️️😶‍🌫️️😶‍🌫️️😶‍🌫️️😶‍🌫️️😶‍🌫️️😶‍🌫️️😶‍🌫️️😶‍🌫️️😶‍🌫️️😶‍🌫️️😶‍🌫️️😶‍🌫️️😶‍🌫️️😶‍🌫️️\n" , pid);
            fflush(stdout); 
		}
	
		k++;
		
		}
	
	    fclose(pid_file);
        	 
        	 
        	 
        	 
        	 
        	 }
        	 
        	 //****************************************************
		     k=0;
        	 
        	 
        	 if(min_type ==1 || max_type==1){//pill
        	         	         	 
        	  while (fscanf(pid2_file, "%d\n", &pid) == 1) {
		 
 		  if (k== min_index && min_type==1 ){
		

     		//min
     		  if (kill(pid, SIGUSR1) == 0) {
                printf("Successfully sent SIGUSR1 to pid %d\n", pid);
            } else {
                perror("Failed to send SIGUSR1");
            }
            printf("  MIN pid =========%d  in pill😶‍🌫️️😶‍🌫️️😶‍🌫️️😶‍🌫️️😶‍🌫️️😶‍🌫️️😶‍🌫️️😶‍🌫️️😶‍🌫️️😶‍🌫️️😶‍🌫️️😶‍🌫️️😶‍🌫️️😶‍🌫️️😶‍🌫️️😶‍🌫️️😶‍🌫️️😶‍🌫️️😶‍🌫️️😶‍🌫️️😶‍🌫️️😶‍🌫️️😶‍🌫️️😶‍🌫️️\n" , pid);
            fflush(stdout);     		 
     		 sleep(2);
		}
		
		else if(k == max_index && max_type==1){
		
     		     //max
     		     if (kill(pid, SIGUSR2) == 0) {
                printf("Successfully sent SIGUSR1 to pid %d\n", pid);
               
            } else {
                perror("Failed to send SIGUSR1");
            }
	 printf("  MAX pid =========%d  in pill 😶‍🌫️️😶‍🌫️️😶‍🌫️️😶‍🌫️️😶‍🌫️️😶‍🌫️️😶‍🌫️️😶‍🌫️️😶‍🌫️️😶‍🌫️️😶‍🌫️️😶‍🌫️️😶‍🌫️️😶‍🌫️️😶‍🌫️️😶‍🌫️️😶‍🌫️️😶‍🌫️️😶‍🌫️️😶‍🌫️️😶‍🌫️️😶‍🌫️️😶‍🌫️️😶‍🌫️️\n" , pid);
            fflush(stdout); 
		}
	
		k++;
		
		}
	
	    fclose(pid2_file);
        	 
        	       	 
        	 }
        }
       
        
    }
    
     kill(gl_pid,SIGXCPU);   //ADDED BY AMAL FOR GL
    }
}


    

    
     kill(gl_pid,SIGCHLD);
    

    
    printf("👀️👀️👀️👀️👀️👀️👀️👀️👀️👀️👀️👀️👀️👀️👀️👀️👀️👀️👀️👀️👀️👀️👀️👀️👀️👀️👀️👀️👀️👀️👀️👀️👀️👀️👀️👀️👀️👀️👀️👀️👀️👀️👀️👀️👀️👀️👀️👀️👀️👀️👀️👀️👀️👀️Maximum simulation time exceeded.\n");
    fflush(stdout);
    
    
  }
}

void create_shared_memoryliquid() {

	readFile("arguments.txt");
	
	int samplesCreated =0;

		for(int i=0 ; i < liquid_plines ; i++){
		   int shmid = shmget(i+1, SHM_SIZE, IPC_CREAT | 0666);
		    if (shmid == -1) {
		        perror("shmget");
		        exit(EXIT_FAILURE);
		    }
		    liquidsharedmemory *shared_memory = (liquidsharedmemory *)shmat(shmid, NULL, 0);
		    if (shared_memory == (void *)-1) {
		        perror("shmat main line 272");
		        exit(EXIT_FAILURE);
		    }
		    
		    		                srand(time(0)+i);
		  for(int j =0 ; j <= numofsamplesofliquid ; j++){

			samplesCreated++;
		
		shared_memory->liquid[j].correctcolor = rand() % (1 - 0 + 1) + 0;  
	    // Get the current time
	    time_t now = time(NULL);

	    // Convert the time to local time (broken-down time)
	    struct tm *local = localtime(&now);

	    // Get the current year, month, and day
	    int year = local->tm_year + 1900;
	    int month = local->tm_mon + 1; // tm_mon is in the range 0-11, so add 1
	    int day = local->tm_mday;

	    // Create a string to hold the concatenated date
	    char dateStr[11]; // YYYYMMDD format requires 10 characters plus null terminator

	    // Format the date as a string
	    snprintf(dateStr, sizeof(dateStr), "%04d%02d%02d", year, month, day);


	   strcpy(shared_memory->liquid[j].actualDate,dateStr);
	   //	printf("actual date ===== %s\n", shared_memory->liquid[j].actualDate);
	  //	fflush(stdout);
   
             
 double probability =5; // Adjust as needed

	    // Generate a random number between 0 and 1
	    double rand_num = rand() % (10 - 1 + 1) + 1;

	    // Check if the random number is greater than the probability
	    if (rand_num < probability) {
		
		  shared_memory->liquid[j].level = rand() % (100 - 90 + 1) + 90;
            shared_memory->liquid[j].color = COLOR[rand() % (1 - 0 + 1) + 0];
            shared_memory->liquid[j].correctcolor = rand() % (1 - 0 + 1) + 0;
            shared_memory->liquid[j].sealed = rand() % (1 - 0 + 1) + 0;
            shared_memory->liquid[j].lable = rand() % (1 - 0 + 1) + 0;
            shared_memory->liquid[j].dateprinted = rand() % (1 - 0 + 1) + 0;
            shared_memory->liquid[j].properdate.day = (rand() % 2) + (day - 1);
            shared_memory->liquid[j].properdate.month = (rand() % 2) + (month - 1);
            shared_memory->liquid[j].properdate.year = (rand() % 2) + (year - 1);
                 // 	printf("random  day ===== %d ,, motnth %d ,,,, year ===%d\n", shared_memory->liquid[j].properdate.day,shared_memory->liquid[j].properdate.month,shared_memory->liquid[j].properdate.year);
		//fflush(stdout);  
            
            
		    } else {
	    shared_memory->liquid[j].level = 95;
            shared_memory->liquid[j].color = COLOR[ shared_memory->liquid[j].correctcolor];
            shared_memory->liquid[j].sealed = 1;
            shared_memory->liquid[j].lable = 1;
            shared_memory->liquid[j].dateprinted = 1;
            shared_memory->liquid[j].properdate.day = day;
            shared_memory->liquid[j].properdate.month = month;
            shared_memory->liquid[j].properdate.year = year;   
			
		    }
            
            
            
            
            

                        
            }
                        //deatch
            if (shmdt(shared_memory) == -1) {
                perror("shmdt");
                exit(EXIT_FAILURE);
            }
            
            	}


        
    
    	printf("Liquid shared memory is initialized.\n");
        printf("There is %d liquid sample created .\n",samplesCreated );
        fflush(stdout);
    


}




void create_shared_memorycheck() {




	readFile("arguments.txt");


		for(int i=0 ; i < liquid_plines ; i++){
		   int shmid = shmget(0x2000+i, SHM_SIZE, IPC_CREAT | 0666);
		    if (shmid == -1) {
		        perror("shmget");
		        exit(EXIT_FAILURE);
		    }
		    checkedsharedmemory *shared_memory = (checkedsharedmemory *)shmat(shmid, NULL, 0);
		    if (shared_memory == (void *)-1) {
		        perror("shmat");
		        exit(EXIT_FAILURE);
		    }
		  for(int j =0 ; j <= numofsamplesofliquid ; j++){

	    shared_memory->check[j]=0;
            shared_memory->accepted[j] = 0;
            
            }
                        //deatch
            if (shmdt(shared_memory) == -1) {
                perror("shmdt");
                exit(EXIT_FAILURE);
            }
            
            	}


        
    
    printf("Liquid shared memory is initialized.\n");


}

void create_shared_memoryforSharedCount(){



		   int shmid = shmget(liquiqFor_AcceptedAndpackagededSamplesCount_key, SHM_SIZE, IPC_CREAT | 0666);
		    if (shmid == -1) {
		        perror("shmget");
		        exit(EXIT_FAILURE);
		    }
		    liquiqFor_AcceptedAndpackagededSamplesCount *shared_memory = (liquiqFor_AcceptedAndpackagededSamplesCount *)shmat(shmid, NULL, 0);
		    if (shared_memory == (void *)-1) {
		        perror("shmat main line 419");
		        exit(EXIT_FAILURE);
		    }

		for(int j=0 ; j < liquid_plines ; j++){
		    shared_memory->Approved_Samples[j]=0;
		    shared_memory->packaged_Samples[j]= 0;
		    shared_memory->checked_Samples[j]= 0;
		 }
	 
		                //deatch
		    if (shmdt(shared_memory) == -1) {
		        perror("shmdt");
		        exit(EXIT_FAILURE);
		    }


}

void create_shared_replace(){



		   int shmid = shmget(replace_key, SHM_SIZE, IPC_CREAT | 0666);
		    if (shmid == -1) {
		        perror("shmget");
		        exit(EXIT_FAILURE);
		    }
		    replace *shared_memory = (replace *)shmat(shmid, NULL, 0);
		    if (shared_memory == (void *)-1) {
		        perror("shmat main line 483");
		        exit(EXIT_FAILURE);
		    }

                    shared_memory->minType=-1;
		    shared_memory->maxType=-1;
		
		   
		    shared_memory->minIndex=-1;
		    shared_memory->maxIndex=-1;
		
	 
		                //deatch
		    if (shmdt(shared_memory) == -1) {
		        perror("shmdt");
		        exit(EXIT_FAILURE);
		    }


}



//////////////////////////////////////////////////
void create_shared_memorypill() {

            

	readFile("arguments.txt");
	
	int samplesCreated =0;

		for(int i=0 ; i < pill_plines ; i++){
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
		    
		                srand(time(0)+i);
		    
		 int containernumber=rand() % (3 - 1 + 1) + 1;
		    
		  for(int j =0 ; j <= numofsamplesofpill; j++){

			samplesCreated++;
		
		shared_memory->pill[j].correctcolor = rand() % (1 - 0 + 1) + 0;  
	    // Get the current time
	    time_t now = time(NULL);

	    // Convert the time to local time (broken-down time)
	    struct tm *local = localtime(&now);

	    // Get the current year, month, and day
	    int year = local->tm_year + 1900;
	    int month = local->tm_mon + 1; // tm_mon is in the range 0-11, so add 1
	    int day = local->tm_mday;

	    // Create a string to hold the concatenated date
	    char dateStr[11]; // YYYYMMDD format requires 10 characters plus null terminator

	    // Format the date as a string
	    snprintf(dateStr, sizeof(dateStr), "%04d%02d%02d", year, month, day);


	   strcpy(shared_memory->pill[j].actualDate,dateStr);
	   //	printf("actual date ===== %s\n", shared_memory->liquid[j].actualDate);
	  //	fflush(stdout);
   
             
 double probability =5; // Adjust as needed

	    // Generate a random number between 0 and 1
	    double rand_num = rand() % (10 - 1 + 1) + 1;

	    // Check if the random number is greater than the probability
	    if (rand_num < probability) {

		
		  shared_memory->pill[j].size = rand() % (13 - 9 + 1) + 9;
            shared_memory->pill[j].color = COLOR[rand() % (1 - 0 + 1) + 0];
            shared_memory->pill[j].correctcolor = rand() % (1 - 0 + 1) + 0;
            
          
            shared_memory->pill[j].numofcontainers = containernumber;    
            shared_memory->pill[j].filledcontainers = CONTAINERSNUM[rand() % (1 - 0 + 1) + 0];
            shared_memory->pill[j].correctpillsnum = rand() % (1 - 0 + 1) + 0;
            shared_memory->pill[j].dateprinted = rand() % (1 - 0 + 1) + 0;
            shared_memory->pill[j].properdate.day = (rand() % 2) + (day - 1);
            shared_memory->pill[j].properdate.month = (rand() % 2) + (month - 1);
            shared_memory->pill[j].properdate.year = (rand() % 2) + (year - 1);
                 // 	printf("random  day ===== %d ,, motnth %d ,,,, year ===%d\n", shared_memory->liquid[j].properdate.day,shared_memory->liquid[j].properdate.month,shared_memory->liquid[j].properdate.year);
		//fflush(stdout);  
            
            
		    } else {
	    shared_memory->pill[j].size = 10;
            shared_memory->pill[j].color = COLOR[ shared_memory->pill[j].correctcolor];
 shared_memory->pill[j].filledcontainers= CONTAINERSNUM[ shared_memory->pill[j].correctpillsnum];
            shared_memory->pill[j].correctpillsnum = 1;
            shared_memory->pill[j].dateprinted = 1;
            shared_memory->pill[j].properdate.day = day;
            shared_memory->pill[j].properdate.month = month;
            shared_memory->pill[j].properdate.year = year;  
            shared_memory->pill[j].numofcontainers = containernumber; 
            
           
		    }
          

                        
            }
                        //deatch
            if (shmdt(shared_memory) == -1) {
                perror("shmdt");
                exit(EXIT_FAILURE);
            }
            
            	}
            	
            	


        
    
    	printf("Liquid shared memory is initialized.\n");
        printf("There is %d liquid sample created .\n",samplesCreated );
        fflush(stdout);
    


}


void create_approvedpillsharedmem() {

	readFile("arguments.txt");


		for(int i=0 ; i < pill_plines ; i++){
		   int shmid = shmget(Approved_PillSamples_SHM_key, SHM_SIZE, IPC_CREAT | 0666);
		    if (shmid == -1) {
		        perror("shmget");
		        exit(EXIT_FAILURE);
		    }
		    Approved_PillSamples_SHM *shared_memory = (Approved_PillSamples_SHM *)shmat(shmid, NULL, 0);
		    if (shared_memory == (void *)-1) {
		        perror("shmat");
		        exit(EXIT_FAILURE);
		    }


	   // shared_memory->Approved[i].numofcontainers=rand() % (2 - 1 + 1) + 1;
           
            
          
                        //deatch
            if (shmdt(shared_memory) == -1) {
                perror("shmdt");
                exit(EXIT_FAILURE);
            }
            
            	}
      
    
    printf("Pillllll shared memory is initialized.\n");


}


void create_shared_memoryforSharedPillCount(){



		   int shmid = shmget(pillFor_AcceptedAndpackagededSamplesCount_key, SHM_SIZE, IPC_CREAT | 0666);
		    if (shmid == -1) {
		        perror("shmget");
		        exit(EXIT_FAILURE);
		    }
		    pillFor_AcceptedAndpackagededSamplesCount *shared_memory = (pillFor_AcceptedAndpackagededSamplesCount *)shmat(shmid, NULL, 0);
		    if (shared_memory == (void *)-1) {
		        perror("shmat");
		        exit(EXIT_FAILURE);
		    }

		for(int j=0 ; j < pill_plines ; j++){
		    shared_memory->Approved_Samples[j]=0;
		    shared_memory->packaged_Samples[j]= 0;
		    shared_memory->checked_Samples[j]= 0;
		 }
	 
		 
	 
		                //deatch
		    if (shmdt(shared_memory) == -1) {
		        perror("shmdt");
		        exit(EXIT_FAILURE);
		    }


}

void create_pillshared_memorycheck() {




	readFile("arguments.txt");


		for(int i=0 ; i < pill_plines ; i++){
		   int shmid = shmget(0x3000+i, SHM_SIZE, IPC_CREAT | 0666);
		    if (shmid == -1) {
		        perror("shmget");
		        exit(EXIT_FAILURE);
		    }
		    checkedpillsharedmemory *shared_memory = (checkedpillsharedmemory *)shmat(shmid, NULL, 0);
		    if (shared_memory == (void *)-1) {
		        perror("shmat");
		        exit(EXIT_FAILURE);
		    }
		  for(int j =0 ; j <= numofsamplesofpill ; j++){

	    shared_memory->check[j]=0;
            shared_memory->accepted[j] = 0;
            
            }
                        //deatch
            if (shmdt(shared_memory) == -1) {
                perror("shmdt");
                exit(EXIT_FAILURE);
            }
            
            	}


        
    
    printf("Pill shared memory is initialized.\n");


}


