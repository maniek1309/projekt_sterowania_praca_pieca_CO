/* link with pthread and realtime libraries            */
/* e.g. gcc -std=c99 reader.c -lpthread -lrt -o reader */

/**********  reader.c  ***********/
#include <unistd.h>
#include <semaphore.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <stdio.h>

char shm_fn[] = "my_shm";
char sem_fn[] = "my_sem";

/**** READER ****/

int main(){
  void* shmptr;
  int shmdes, index;
  sem_t *sem_des;
  int SHM_SIZE;
  int semvalue;

  /* Open the shared memory object */

  SHM_SIZE = sysconf(_SC_PAGESIZE);

  if ( (shmdes = shm_open(shm_fn, O_RDWR, 0)) == -1 ) {
     perror("shm_open failure");
     _exit(-1);
   }

  if((shmptr = mmap(0, SHM_SIZE, PROT_WRITE|PROT_READ, MAP_SHARED,
               shmdes,0)) == (void*) -1){
     perror("mmap failure");
    _exit(-1);
  }

 /* Open the Semaphore */

 /* semdes = sem_open(sem_fn, 0, 0644, 0); */
 sem_des = sem_open(sem_fn, 0);

 if(sem_des == (void*) -1){
   perror("sem_open failure");
   _exit(-1);
 }

 /* Lock the semaphore */

 if(!sem_wait(sem_des)){

  /* Access to the shared memory area */
for(index = 0; 1< 3; index++){


char *shm_ptr = (int *)shmptr;
    for(index = 0; index < 10; index++){
    if( index == 3){//praca nadzor wpis na 6 +1* piec co 1sek wiatrak
    	if(shm_ptr[index] == 1 ){
    	shm_ptr[6]=1;//6 wiatrak
        shm_ptr[0]+=5;
        sleep(1);
        shm_ptr[6]=0;
        printf("praca nadzor  \n");
    	}
        else if(shm_ptr[index] == 2 ){//praca dogrzanie wpis na 6 i 7 +1* piec co 1sek wiatrak
    	shm_ptr[6]=1;//6 wiatrak
    	shm_ptr[7]=1;//7 podajnik
        shm_ptr[0]+=7;
        sleep(1);
        shm_ptr[6]=0;
        shm_ptr[7]=0;
        printf("praca dogrzanie \n");
    	}
    	else if(shm_ptr[index] == 3 ){//praca awaria zgasł
    	shm_ptr[6]=0;//6 wiatrak
    	shm_ptr[7]=0;//7 podjnik
    	printf("praca awaria zgasł \n");
    	}
    	else if(shm_ptr[index] == 4 ){//praca zgasło 
    	shm_ptr[6]=0;//6 wiatrak
    	shm_ptr[0]-=2;
    	shm_ptr[7]=0;//7 podajnik
    	shm_ptr[1]+=2;
    	shm_ptr[2]+=2;
    	sleep(1);
    	printf("za wysoka temp \n");
    	}
       }
    if( index == 4){
    	if(shm_ptr[index] == 1 ){
    	shm_ptr[8]=1;//praca pompy co
        shm_ptr[1]+=2;
        shm_ptr[0]-=1;
        sleep(2);
        shm_ptr[8]=0;
        printf("w pompa co \n");
    	}//praca pompy CO piec o 1
    	else if (shm_ptr[index] == 0)
        shm_ptr[7]=0;
        sleep(2);
        shm_ptr[0]-=1;
        printf("pompa co nie działa \n");
       }
   if( index == 5){    
       if(shm_ptr[index] == 1 ){//praca pompy bojlera piec o 1
       shm_ptr[9]=1;
       sleep(2);
       shm_ptr[0]-=1;
       shm_ptr[2]+=2;
       printf("pompa Bojlera działa \n");
       }
          
       else if(shm_ptr[index] == 0){//praca pompy Bojlera na 9 piec co 1 sek
       shm_ptr[9]=0;
       sleep(2);
       shm_ptr[2]-=1;
       printf("pompa Bojlera nie działa \n");
       }
       }
        if(shm_ptr[3] == 5){
    break;
    }
       }
       if(shm_ptr[3] == 5){
    break;
    }
        
}///koniec
  /* Release the semaphore lock */

printf("press ENTER to release semaphore");
char ch;scanf("%c",&ch);

  sem_post(sem_des);

sem_getvalue(sem_des,&semvalue);printf("semvalue:%d\n",semvalue);

printf("press ENTER to unlink semaphore");
scanf("%c",&ch);

  //munmap(shmptr, SHM_SIZE);

  /* Close the shared memory object */


  munmap(shmptr, SHM_SIZE);

  /* Close the shared memory object */

  close(shmdes);

  /* Close the Semaphore */

  sem_close(sem_des);
}}
