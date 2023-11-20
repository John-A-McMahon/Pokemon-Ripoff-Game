#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>




//for the sleep function
#include<unistd.h>
typedef struct{
	char name[50];
	int health;
	int stun;
	int class;
} character;


int lightAttackDamage=1;
int heavyAttackDamage=3;
int spellAttackDamage=5;
int rangeAttackDamage=2;
int shieldStun=5;
int startingHealth=10;




int classes = 0;
/*
 *0=disabled
  1=Physical
  2=Mage
  3=Marksman
  Physical > Marksman
  Mage     > Physical
  Marksman > mage
 * */


void monsterClass(character* monster){
	char* name = (*monster).name;



	//set monster class to physical
	if(
			strcmp(name,"Zombie")==0||
			strcmp(name,"Warewolf")==0||
			strcmp(name,"Mummy")==0||
			strcmp(name,"Bear")==0||
			strcmp(name,"Zombie")==0||
			strcmp(name,"Clown")==0||
			strcmp(name,"Fire Elemental")==0||
			strcmp(name,"Werewolf")==0

			){
		(*monster).class=1;
	}else if(
			
			strcmp(name,"Wicked Witch of the West")==0||
			strcmp(name,"Voldemort")==0||
			strcmp(name,"Ghost")==0||
			strcmp(name,"Sauron")==0
			){
				(*monster).class=2;
			}
	
	else{
		(*monster).class=3;
	}


}





int numMonsterTypes=18;
char* monsterNames[]={"Zombie","Warewolf","Wicked Witch of the West","Clown",
	              "Mummy","Grendel","Hydra", "Bear",
		      "Gangsta","Ghost","Vampire","Kraken",
			"Fire Elemental","Voldemort","Werewolf","Napoleon","Mad Scientist","Sauron"};

char* humanAttacks[] = {"SAVE","light attack","heavy attack", "magic attack","Shield Bash attack","heal","ranged attack" };
char* monsterAttacks[] = {"MISS","scratch","BITE", "CURSE","clobber","regen","Longshot" };
int getNum(){
	int x;
	scanf("%d",&x);
	getchar();
	return x;
}

int isValid(int start, int end,int value){
	return value>=start&&value<=end;
}

void isValidLoop(int start, int end,int* value){
	do
	{	
		(*value)=getNum();

	}
	while(!isValid(start,end,*value));
	return;
}
void printHealthBar(int health, int precision,char full, char empty){
	for(int i=0; i<startingHealth; i+=precision){
		if(i<health){
			printf("%c",full);
		}
		else{
			printf("%c",empty);
		}
	}
}
void wait(long time){
	int timekiller =0;
	for(int i=0; i<time; i++){
		timekiller+=rand()%2;	
	}

}












int gameOver(int gameSize, character humans[], character monsters[]){
	
	int stillMonsters=0;
	int stillHumans=0;
	
	
	for(int i=0; i<gameSize; i++){
		
		if(monsters[i].health>0){
			stillMonsters=1;
		}
	}

	for(int i=0; i<gameSize; i++){
		if(humans[i].health>0){
			stillHumans=1;
		}
	}
	if(stillHumans&&stillMonsters){
		return 0;
	}
	if(stillHumans){
		return 1;
	}
	return -1;
}

//Calcualtes if attack should miss, damage and accuracy are inverses of eachother
int shouldMiss(int move){
	if(move==1){	
		return rand()%lightAttackDamage; 
	}
	if(move==2){	
		return rand()%heavyAttackDamage; 
	}

	if(move==3){	
		return rand()%spellAttackDamage; 
	}
	if(move==4){	
		return rand()%shieldStun; 
	}
	if(move==6){	
		return rand()%rangeAttackDamage; 
	}

	return 1;

}

int isValidMove(character person,int move){
	/*light attack==1 (everyone)
	 *heavy attack==2 (physical class only)
	 *spell attack==3 (mage only)
	 *shield bash ==4 (physical class only)
	 *heal        ==5 (mage only)
	 *ranged attack==6 (marksman only)
	 * */
	if(person.class==0||move==1){
		return 1;
	}
	
	//warrior trying to heal, spell or ranged attack
	if(person.class==1&&(move==3||move==5||move==6)){
		return 0;
	}
	//mage trying to strong attack, shield bash or ranged attack
	if(person.class == 2&&(move==2||move==4||move==6)){
		return 0;
	}
	//marksman trying to shield bash
	if(person.class==3&&(move==2||move==3||move==4||move==5)){
		return 0;		
	}


	//if not invalid return 1
	return 1;
}

void printValidMoves(character human){
	printf("What will you do\n");
	printf("0 SAVE\n");
	if(human.class==1){
		printf("1 Light attack\n");
		printf("2 Heavy Attack\n");
		printf("4 Shield Bash\n");				
	}
	if(human.class==2){
				printf("1 Light attack\n");
				printf("3 Spell\n");
				printf("5 Heal\n");
			
	}
	if(human.class==3){
				printf("1 Light attack\n");
				printf("6 Ranged Attack\n");	
	}
}


void printCool(char* text, int pause){
				//cool animated text
				printf("hi");
				for(int i=0; i<strlen(text); i++){
					printf("%c\n",text[i]);
					sleep(pause);
				}
}


void runGame(int turn,int gameSize,  character humans[], character monsters[]){

	int decision = -1;

		while(1)
		{
			sleep(1);
			printf("\n\n");

			int gameState=gameOver(gameSize,humans, monsters);
				
			if(gameState==-1){
				printf("MONSTERS WON\n");


				//cool animated text
				char* text= "DEFEAT";
				printCool(text,2);
				return;
			}

			if(gameState==1){
				printf("HUMANS WON\n");
				//cool animated text
				char* text= "VICTORY";
				printCool(text,2);
				return;
			}



			//humans turn
			int relativeTurn=turn%gameSize;





			//Humans Turn
			if(turn%(2*gameSize)<gameSize){
			//printf("HUMANS:\n");


				//skip turn if player is dead
				if(humans[relativeTurn].health<=0){
					if(turn%(2*gameSize)<gameSize){
						turn+=gameSize;
					}
					continue;
				}

				if(humans[relativeTurn].stun>0){
					printf("%s is confused.....\n",humans[relativeTurn].name);
					humans[relativeTurn].stun--;
					
					
					if(turn%(2*gameSize)<gameSize){
						turn+=gameSize;
					}
					continue;
				}


				printf("%s 's health:     ",humans[relativeTurn].name);
				//health bars
				//printf("%d",humans[0].health);

				for(int i=0; i<startingHealth; i++){
					if(i<=humans[relativeTurn].health){
						printf("=");
						
					}
					else{
						//printf(" %d<%d ",i,humans[relativeTurn].health);
						printf("-");
					}
				}




				printf("\n");

				//Attack selection
				if (!classes){
				printf("What will you do\n");
				printf("0 SAVE\n");
				printf("1 Light attack\n");
				printf("2 Heavy Attack\n");
				printf("3 Spell\n");
				printf("4 Shield Bash\n");
				printf("5 Heal\n");
				printf("6 Ranged Attack\n");
				}else{
					printValidMoves(humans[relativeTurn]);	
				}
				decision=-1;
				int move = -1;
				do{
				isValidLoop(0,7,&decision);
				}while(!isValidMove(humans[relativeTurn],decision));
				move = decision;
				
				
				//saving game
				if(move==0){
					char fileName[30];
					printf("What would like to name your save file?\n");
					fgets(fileName,30,stdin);	




					for(int i=0; i<30; i++){
						if(fileName[i]=='\n'){
							fileName[i]='\0';
						}
					}

					if(fileName[0]=='\0'){
						printf("INVALID file name, defaulting to saveFile.bin\n");
						//fileName={'s','a','v','e','F','i','l','e','.','b','i','n','\0'};
						//fileName="saveFile.bin";
						strcpy(fileName,"saveFile.bin");
					
					printf("SAVING: ");

					}
					


					FILE* saveFile = fopen(fileName,"wb");
					printf(".");	
					//save game size
					fwrite(&gameSize,sizeof(int),1,saveFile);		
					printf(".");
					//save turn	
					fwrite(&turn,sizeof(int),1,saveFile);		
					printf(".");	
			
					fwrite(humans,sizeof(character),gameSize,saveFile);		
					printf(".");	
					fwrite(monsters,sizeof(character),gameSize,saveFile);		
					printf(".");	
					
					fclose(saveFile);

					printf(". GAME SAVED");	
					return;

				}	
				
				
				
				//Select Target

				//wont choose target if saving
				if(move>0&&move!=5){
					
					int target =-1;
				
					printf("Select target\n");
					printf("# MONSTERNAME                    HP\n");
					for(int i=0; i<gameSize; i++){
						if(monsters[i].health>0){
							/*
							printf("%s       %d\n",monsters[i].name,i);
							printHealthBar(monsters[i].health,1,'=','-');
							*/

							printf("\n%d  %s",i,monsters[i].name);
							//aligns everything better
							for(int offset=0; offset<30-strlen(monsters[i].name); offset++){
								printf(" ");
							}


							printHealthBar(monsters[i].health,1,'=','-');	
								



						}
					}
					printf("\n");
					do{
						isValidLoop(0,gameSize-1,&target);
					}while(monsters[target].health<=0);
			


				
				if(shouldMiss(move)){
					printf("%s MISSED!\n",humans[relativeTurn].name);
					move=-1;
				}


				//light attack
				if(move==1){
					monsters[target].health-=lightAttackDamage;
				}	
				//heavy attack
				if(move==2){
					monsters[target].health-=heavyAttackDamage;
					if(monsters[target].class==3){
						monsters[target].health--;
						printf("It is super effective!!!\n");
					}
				}	
				//magic attack
				if(move==3){
					monsters[target].health-=spellAttackDamage;
					if(monsters[target].class==1){
						monsters[target].health--;
						printf("It is super effective!!!\n");
					}
				}	
				//Shield bash
				if(move==4){
					//Note to self, add stun feature
					monsters[target].stun+=(rand()%3)*(rand()%2);
				}	

				//ranged attack
				if(move==6){
					monsters[target].health-=rangeAttackDamage;
					if(monsters[target].class==2){
						monsters[target].health--;
						printf("It is super effective!!!\n");
					}
				}	
				
				if(humans[target].health<=0){
					printf("%s is dead!\n", humans[target].name);


					

				}
				
				sleep(1);
				if(move!=-1){
				printf("%s used %s on %s!\n",humans[relativeTurn].name,humanAttacks[move],monsters[target].name);				
				}				
				}
				
				if(move==5){
					//humans[relativeTurn].health+=(rand()%5)*(rand()%2);
					printf("%s used HEAL!\n",humans[relativeTurn].name);				


					for(int humanTarget=0; humanTarget <gameSize; humanTarget++){

						if(humans[humanTarget].health<=0){

							continue;
						}


						printf("%d %s",humanTarget,humans[humanTarget].name);

						for(int offset=0; offset<30-strlen(humans[humanTarget].name); offset++){
							printf(" ");

						}
						printHealthBar(humans[humanTarget].health,1,'=','-');
						printf("\n");
					}


					int choice;
					do{
						isValidLoop(0,gameSize-1,&choice);
					}while(humans[choice].health<=0);
					

					if(humans[choice].health<startingHealth){
						humans[choice].health+=(rand()%5)*(rand()%2);
					}
					printf("%s healed %s\n",humans[relativeTurn].name,humans[choice].name);



				}	


			}
			//Monsters turn
			else{
			//printf("MONSTERS TURN:\n");
				//skip turn if monster is dead
				if(monsters[relativeTurn].health<=0){
					turn+=gameSize+1;
					continue;
				}
				

				

				//skip turn if monster is stunned
				if(monsters[relativeTurn].stun>0){
					printf("%s is confused.....\n",monsters[relativeTurn].name);
					humans[relativeTurn].stun--;
					turn+=gameSize+1;
					continue;
				}
				int target = rand()%gameSize;

				while(humans[target].health<=0){
					target = rand()%gameSize;
				}
				int move = rand()%6+1;
				while(!isValidMove(monsters[relativeTurn],move)||(move==1&&rand()%100<50)){	
					move = rand()%6+1;
				}	


				if(shouldMiss(move)){
					move = 0;
				}

				sleep(1);
				if(move>0){
					if(move!=5){
					printf("%s used %s on %s\n", monsters[relativeTurn].name,monsterAttacks[move],humans[target].name);
					
					}else{
					
						printf("%s used %s!\n",monsters[relativeTurn].name,monsterAttacks[move]);
					}


					
				//light attack
				if(move==1){
					humans[target].health-=lightAttackDamage;
				}	
				//heavy attack
				if(move==2){
					humans[target].health-=heavyAttackDamage;

					if(humans[target].class==3){
						humans[target].health--;
						printf("It is super effective!!!\n");
					}

				}	
				//magic attack
				if(move==3){
					humans[target].health-=spellAttackDamage;
					if(humans[target].class==1){
						humans[target].health--;
						printf("It is super effective!!!\n");
					}
				}	
				//Shield bash
				if(move==4){
					//Note to self, add stun feature
					humans[target].stun+=rand()%3*(rand()%2);
				}	

				if(move==5){
					//monsters[relativeTurn].health+=(rand()%5)*(rand()%2);
					int minHealth = startingHealth;
					int lowestHealthIndex = 0;
					//heals ally with the lowest health (that is not dead)
					for(int monsterIndex = 0; monsterIndex<gameSize; monsterIndex++){
						if(minHealth>monsters[monsterIndex].health&&monsters[monsterIndex].health!=0){
							lowestHealthIndex = monsterIndex;

							minHealth=monsters[monsterIndex].health;
						}
					}
					monsters[lowestHealthIndex].health+=(rand()%5)*(rand()%2);

					//prevent infinite healing
					if(monsters[lowestHealthIndex].health>startingHealth){
						monsters[lowestHealthIndex].health=startingHealth;
					}

					printf("%s healed %s\n",monsters[relativeTurn].name,monsters[lowestHealthIndex].name);

				}	
				//ranged attack
				if(move==6){
					humans[target].health-=rangeAttackDamage;
					if(humans[target].class==2){
						humans[target].health--;
						printf("It is super effective!!!\n");
					}
				}	

				if(humans[target].health<=0){
					printf("%s is dead\n", humans[target].name);
				}


				}
				else{
					printf("%s missed!\n",monsters[relativeTurn].name);

				}
					
			}
					//if humans switch to monsters
					if(turn%(2*gameSize)<gameSize){
						turn+=gameSize;
					}
					//if monsters swich to humans and shift the index
					else{
						turn+=gameSize+1;
					}
		
		}




}
int main(){
	srand(time(NULL));
	int decision=-1;	
	printf("NEW GAME (0)\nLOAD GAME (1)\n");
	do{
		decision = getNum();
	}

	while(!isValid(0,1,decision));

	if(decision == 0){
		printf("Do you want to enable classes?\n");
		printf("NO 0\n");
		printf("YES 1\n");

		classes=-1;
		isValidLoop(0,1,&classes);




		int gameSize=-1;
		printf("Game Size (how many players on each team)?\n");
		isValidLoop(1,100,&gameSize);
		character humans[gameSize];
		character monsters[gameSize];


		for(int i=0; i<gameSize; i++){
			printf("human %d name:  ",i);
			//getchar();
			//fflush(stdin);
			fgets(humans[i].name,49*sizeof(char),stdin);
					if(!classes){
						humans[i].class=0;
					
					}else{
					
			printf("What class is %s?\n",humans[i].name);
			printf("1 Warior/physical (Strong against ranged)\n");
			printf("2 mage/magical (Strong against physical)\n");
			printf("3 Marksman/ranged (Strong against magical)\n");

			isValidLoop(1,3,&(humans[i].class));
			

					}
			for(int e=0; e<50; e++){
				if(humans[i].name[e]=='\n'){
					humans[i].name[e]='\0';
					humans[i].stun=0;

				}
			}


			humans[i].health=startingHealth;	
		}

		for(int i=0; i<gameSize; i++){
			strcpy(monsters[i].name,monsterNames[rand()%numMonsterTypes]);
			//strcpy(monsters[i].name,monsterNames[2]);
			monsters[i].health=startingHealth;	
			monsters[i].stun=0;
			monsterClass(&monsters[i]);
		}	
		
		int turn=0;
		runGame(turn,gameSize,humans,monsters);
		
		




	}
	else if (decision==1){
		char filename[100];

		printf("What is the absolute/relative path of the save file?\n");
		
		fgets(filename,100,stdin);

		for(int i=0; i<100; i++){
			if(filename[i]=='\n'){
				filename[i]='\0';
			}
		}


		FILE* file = fopen(filename,"rb");

		if(file==NULL){
			printf("FAILED TO OPEN SAVE FILE\n");
			return 1;
		}





		int gameSize;
		fread(&gameSize,sizeof(int),1,file);
		int turn;
		fread(&turn,sizeof(int),1,file);
			
		character humans[gameSize];
		character monsters[gameSize];

		fread(humans,sizeof(character),gameSize,file);	
		
		fread(monsters,sizeof(character),gameSize,file);	
	
		//check if classes are enabled
		for(int i=0; i<gameSize; i++){
			if(humans[i].class!=0||monsters[i].class!=0){
				classes=1;
				break;
			}
		}

		runGame(turn,gameSize,humans,monsters);
	
	}
	


}

