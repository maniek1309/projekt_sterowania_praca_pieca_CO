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
  int shmdes, index, semvalue;
  sem_t *semdes;
  int SHM_SIZE;

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
 semdes = sem_open(sem_fn, 0);

 if(semdes == (void*) -1){
   perror("sem_open failure");
   _exit(-1);
 }

 /* Lock the semaphore */

 if(!sem_wait(semdes)){

 int r=0;
for(index = 0; 1< 3; index++){


  /* Access to the shared memory area */
char *shm_ptr = shmptr;
sem_getvalue(semdes,&semvalue);
   printf("semvalue:%d\n",semvalue);
   for(index = 0; index < 11; index++){
   
        printf("The shared memory shmptr[%d] = %d\n", index,shm_ptr[index]);
}
 int n;
    printf("wciśnij 0 żeby wyłaczyć piec lub dowolną liczbe aby piec działał");
    if(scanf("%d",&n) != 1) 
    {
        
        printf("Please enter an integer: \n");
        while(getchar() != '\n');
        
    }
    if(n==0){
    shm_ptr[10]=3;
    }
     if(shm_ptr[3] == 5){
    break; 
    }
}
      

 /* Release the semaphore lock */
   sem_post(semdes);
  

  munmap(shmptr, SHM_SIZE);

  /* Close the shared memory object */

  close(shmdes);

  /* Close the Semaphore */

  sem_close(semdes);
}}
