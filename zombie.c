/*Yakın zamanda kod içinde bidaha düzenleme olacaktır */
/*Yusuf YALÇIN 
18120205032 
Optimum doorman sayısı 1 dir.En azından benim randteki şanstan böyle çıktı(srand kullnasaydım değişirdi) 2 de kafa kafayalar zombi kazanıyor ilk. 3'ten sonra zombiler.
Matematiksel olarakta böyledir
*/
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<stdlib.h>
/*number of zombies in the game: 
you should synchronize threads editing this variable*/
int zombieCounter = 0;
int killedZombie = 0;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
/* Keeps track of number of zombies entered.*/
void zombieEntered(){
    zombieCounter++;
    printf("Zombi sayısı %d \n",getInTheRoomCount());
}
/* Keeps track of number of zombies killed.*/
void zombieKilled(){
    zombieCounter--;
    killedZombie ++;
    printf("Öldürülen Zombi sayısı %d \n ",getKilledCount());
}
/* Returns true if number of zombies in the room are 
greater than or equal to 100.*/
int tooManyZombiesInTheRoom(){
       if(zombieCounter >= 100){
        printf("Zombiler kazandı!\n");
       return 1;
       }else
       return 0;
}

/*Returns true if more than 100 zombies have been killed.*/
int killed100Zombies(){
    if(killedZombie>100){
        printf("Siz kazandınız!\n");
    return 1;
    }else
    return 0;
}

/* Returns true if there is at least one zombies in the room.*/
int zombiesExist(){
    if(zombieCounter > 0)
    return 1;
    return 0;
}
/*Returns the number of zombies killed.*/
int getKilledCount(){
    return killedZombie;
}

/* Returns the number of zombies in the room.*/
int getInTheRoomCount(){
    return zombieCounter;
}
/*doorman thread*/
void *doorMan(void *p){
   
    while(!((tooManyZombiesInTheRoom() || killed100Zombies() ))){
    usleep(2000);
    if(rand() %2 == 0);
    pthread_mutex_lock(&m);
    zombieEntered();
    pthread_mutex_unlock(&m);
    }
   
}

/*slayer thread*/
void *slayer(void *p){
    while(!(tooManyZombiesInTheRoom() || killed100Zombies())){
    if(zombiesExist()){
    usleep(2000);
    pthread_mutex_lock(&m);
    zombieKilled();
    pthread_mutex_unlock(&m);
    }
    }
    
}
/*simulator main thread*/
int main(int argc, char **argv){    
    int j = atoi(argv[1]);
    pthread_t ds[j+1];
    for(int i = 0;i < j;++i){
    pthread_create(&ds[i], NULL, doorMan, NULL);
    }
    pthread_create(&ds[j], NULL, slayer, NULL);
    for(int i = 0;i < j;++i){
    pthread_join(ds[i],NULL);//doorman için
    }
    pthread_join(ds[j],NULL);//slayer için
    printf("Program Bitti!\n");
}
