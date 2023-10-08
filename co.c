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

int n;

    printf("Temperatura CO to: ");
    while(scanf("%d",&n) != 1) 
    {
        printf("Please enter an integer: ");
        while(getchar() != '\n');
    }
char *shm_ptr = (int *)shmptr;
    for(index = 0; index < 3; index++){
    if( index == 1){
       printf("write %d into the shared memory shmptr[%d]\n", n, index);
       shm_ptr[index]=n;
   printf("Temperatura CO %d\n", shm_ptr[index]);
   sem_getvalue(sem_des,&semvalue);printf("semvalue:%d\n",semvalue);
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

  
}}
