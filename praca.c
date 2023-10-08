/* link with pthread and realtime libraries            */
/* e.g. gcc -std=c99 reader.c -lpthread -lrt -o reader */

/**********  writer.c  ***********/
#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/fcntl.h>


/* check /dev/shm for OS representation                 */
/* of shm and sem POSIX objects                         */

char shm_fn[] = "my_shm";
char sem_fn[] = "my_sem";


int main(){
  void* shmptr;
  unsigned int mode;
  int shmdes, index;
  sem_t *Sem_des;
  sem_t *sem_des;
  int SHM_SIZE;
  int semvalue;
  int tp, tpCO, tpB, W=0, Pp=0, pB=0, PCO=0, info=0 ;

  mode = S_IRWXU|S_IRWXG;

  /* Open the shared memory object */

  if ( (shmdes = shm_open(shm_fn,O_CREAT|O_RDWR|O_TRUNC, mode)) == -1 ) {
     perror("shm_open failure");
     _exit(-1);
   }

/*  Preallocate a shared memory area   */

  SHM_SIZE = sysconf(_SC_PAGESIZE);
/* The size equal to one OS page e.g. 4kb */

  if(ftruncate(shmdes, SHM_SIZE) == -1){
    perror("ftruncate failure");
    _exit(-1);
  }

  if((shmptr = mmap(0, SHM_SIZE, PROT_WRITE|PROT_READ, MAP_SHARED,
                shmdes,0)) == (void*)-1){
    perror("mmap failure");
    _exit(-1);
  }

  /* Create a semaphore in locked state */

 Sem_des = sem_open(sem_fn, O_CREAT, 0644, 0);

 if(Sem_des == (void*)-1){
   perror("sem_open failure writer");
   _exit(-1);
 }
 sem_getvalue(Sem_des,&semvalue);printf("semvalue:%d\n",semvalue);
    /* Access to the shared memory area */

/* cast  the *void pointer in order to use e.g. as char... */
int r=0;
for(r = 0; r < 6; r++){
char *shm_ptr = (char *)shmptr;
    for(index = 0; index < 11; index++){
       printf("write %d into the shared memory shmptr[%d]\n", index*0, index);
       shm_ptr[index]=index*0;
       }

  /* Release the semaphore lock */
if(r==1){
system("gnome-terminal --execute ./piec");
}
if(r==2){
system("gnome-terminal --execute ./co");
}
if(r==3){
system("gnome-terminal --execute ./boiler");
}
if(r==4){
system("gnome-terminal --execute ./perf");
}
if(r==5){
system("gnome-terminal --execute ./POS");
}

printf("press ENTER ");
char ch;scanf("%c",&ch);
  sem_post(Sem_des);
  
}
sem_getvalue(Sem_des,&semvalue);printf("semvalue:%d\n",semvalue);
//koniec Semdes 
 sem_des = sem_open(sem_fn, 0);

 if(sem_des == (void*) -1){
   perror("sem_open failure reader");
   _exit(-1);
 }

sem_getvalue(sem_des,&semvalue);printf("semvalue:%d\n",semvalue);
    /* Access to the shared memory area */

/* cast  the *void pointer in order to use e.g. as char... */

for(index = 0; 1 < 3; index++){
char *shm_ptr = shmptr;
sem_getvalue(sem_des,&semvalue);printf("semvalue:%d\n",semvalue);
   for(index = 0; index < 11; index++)
   if(index == 0){
   printf("Temperatura pieca to %d\n", shm_ptr[index]);
   tp=shm_ptr[index];
   }
   else if(index == 1){
   printf("Temperatura CO %d\n", shm_ptr[index]);
   tpCO=shm_ptr[index];
   
   }
   else if(index == 2){
   printf("Temperatura boilera %d\n", shm_ptr[index]);
   tpB=shm_ptr[index];
   }  
   else if(index == 6){
   W=shm_ptr[index];
   }  
   else if(index == 7){
   Pp=shm_ptr[index];
   }  
   
       // sem_post(sem_des);
        //munmap(shmptr, SHM_SIZE);
        
   if((tp>=60) && (tp<=80)){
   	info=1;//praca nadzór
   	shm_ptr[3]=info;
   	printf("praca nadzór\n");
   
   }
   else if(tp>40 && tp<60){
   	info=2;//praca dogrzewanie
   	shm_ptr[3]=info;
   	printf("praca dogrzewanie\n");
   
   }
   else if(tp<40){
   	info=3;//awaria zgasło
   	shm_ptr[3]=info;
   	printf("praca awaria zgasło\n");
   
   }
   else if(tp>80){
   	info=4;//awaria za wysoka temperatura
   	shm_ptr[3]=info;
   	printf("praca awaria za wysoka temperatura\n");
   
   }
   if(tpCO>=10 && tpCO<=25 && info==1){
   	PCO=1;//praca pompy CO
   	shm_ptr[4]=PCO;
        
   }
   else if(tpCO>25){
   	PCO=0;//pompa CO nie działa
   	shm_ptr[4]=PCO;
   	
   
   }
   if(tpB>=0 && tpB<=50 && info==1){
   	pB=1;//pompa bojlera działa
   	shm_ptr[5]=pB;
   	
   }
   else if(tp>50){
   	pB=0;//pompa boilera nie działa
   	shm_ptr[5]=pB;
   	
   
   }
   if(W==1){
   printf("wiatrak działa \n");
   } 
   else if(W==0){
   printf("wiatrak nie działa \n");
   }
   if(Pp==1){
   printf("podajnik paliwa działa \n");
   } 
   else if(Pp==0){
   printf("podajnik paliwa nie działa\n");
   }
   if(shm_ptr[4]==1){
   printf("Pompa CO działa \n");
   } 
   else if(shm_ptr[4]==0){
   printf("Pompa CO nie działa \n");
   }
   if(shm_ptr[5]==1){
   printf("Pompa bojlera działa \n");
   } 
   else if(shm_ptr[5]==0){
   printf("Pompa bojlera nie działa \n");
   }
    

	sleep(1);system("clear");
	if(shm_ptr[10] == 3){
	shm_ptr[3]=5;
	break;
	}
} 
  /* Release the semaphore lock */ 


printf("press ENTER to release semaphore");
char ch2;scanf("%c",&ch2);

  sem_post(sem_des);

sem_getvalue(sem_des,&semvalue);printf("semvalue:%d\n",semvalue);

printf("press ENTER to unlink semaphore");
scanf("%c",&ch2);

  munmap(shmptr, SHM_SIZE);

  /* Close the shared memory object */

  close(shmdes);

  /* Close the Semaphore */

  sem_close(sem_des);

  /* Delete the shared memory object */

  shm_unlink(shm_fn);
  sem_unlink(sem_fn);
}
