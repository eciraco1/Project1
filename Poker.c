#include <stdio.h>
typedef int bool;
#define TRUE 1
#define FALSE 0




typedef struct Cards{
    int n;
    char s;
} Card;
Card hand[7];


struct Player{
  Card hand[7]; //makes an array of cards, check if it works
  int handValue;
} p1, p2 ,p3;



int getHandValue(Card h[]);
int highest(Card h[]);
//void sortCards(Card * h[]);
bool checkRFlush(Card h[]);
bool isRoyalty(Card a);
bool checkFlush(Card h[]);
bool checkSFlush(Card h[]);
int numOfPair(Card h[]);
bool checkStraight(Card h[]);
bool checkFull(Card h[]);
bool checkFour(Card h[]);
bool checkT(Card h[]);
void makePlayersHands(struct Player p1, struct Player p2, struct Player p3, FILE *fp);
Card makeCard(char num, char suite);










int main(){
  char buff[255];
  FILE *fp= fopen("sampleinput.txt", "r"); //check syntax
  while(fgets(buff, sizeof(buff), fp)){
    makePlayersHands(p1, p2, p3, fp);
    p1.handValue= getHandValue(p1.hand);
    p2.handValue= getHandValue(p2.hand);
    p3.handValue= getHandValue(p3.hand);
  }
//----
  if (p1.handValue > p3.handValue){
        if(p1.handValue > p2.handValue){
          printf("Player 1 wins \n");
        }else{
          printf("Player 3 wins \n");
        }
//-----
  }else if (p2.handValue > p3.handValue){
      printf("Player 2 wins \n");
//------
  }else
      printf("Player 3 wins \n");
  fclose(fp);
}




Card makeCard(char num, char suite){
  Card ret;
  int number;
  if(num=='T'){
      number=10;
    }else if(num=='J'){
        number=11;
    }else if(num=='Q'){
        number=12;
    }else if(num=='K'){
        number=13;
    }else if(num=='A'){
        number=14;
    }else{
        number=num - '0';
    }
  ret.n=num;
  ret.s=suite;
  return ret;
}
//------------------------------------------------------------------------------------------------------------
//Calculates hand value, whoever has the highest hand value wins
int getHandValue(Card h[]){

  if(checkRFlush(h) )
    return 1000+highest(h);

  if(checkSFlush( h) )
    return 900+highest(h);

  if(checkFour( h) )
    return 800+highest(h);

  if(checkT( h ) && (numOfPair(h) > 1)) // checks for full house
    return 700+highest(h);

  if( checkFlush(h) ) // checks for flush
    return 600+highest(h);

  if(checkStraight(h)) // checks for a straight
    return 500+highest(h);

  if(checkT(h))
    return 400+highest(h);

  if(numOfPair( h )>1) //checks for 2 pairs
    return 300+highest(h);

  if (numOfPair( h ) == 1) { //checks for a pair
    return 200+highest(h);

  } else { //if the player has nothing, it returns highest card
    return highest(h);
  }


}

//--------------------------------------------------------------------------------------------------------------
//finds the highest faced card
int highest(Card h[]){
  int i;
  int g=0; //return value
  for(i=0; i<2; i++){
    if(h[i].n>g)
      g=h[i].n;
  }
  return g;
}

//--------------------------------------------------------------------------------------------------------------

//Sorting using bubble sort
/*void sortCards(Card h[]){
  int i;
  int j;
  Card * temp;
   for (i=0; i<6; i++){
    for (j=0; j<6-i; j++){
      if ((*h)[j].n>(*h)[j+1].n)
          //swap(&h[j], &h[j+1]);
          temp=h[j];
          h[j]=h[j+1];
          h[j+1]=temp;


      }
    }
}*/

//--------------------------------------------------------------------------------------------------------------
//checks to see if all of the cards are a K Q J or T by using isRoyalty, and then checks if theyre al the same suit
bool checkRFlush(Card h[]){
  int i;
  bool fin= FALSE;
  for(i=0; i<3; i++){
    if( isRoyalty(h[i]) && (h[i].s == h[i+1].s) &&
        isRoyalty(h[i+1]) && (h[i].s == h[i+2].s) &&
        isRoyalty(h[i+2]) && (h[i].s == h[i+3].s) &&
        isRoyalty(h[i+3]) && (h[i].s == h[i+4].s) &&
        isRoyalty(h[i+4]) )
        fin=TRUE;
  }
  return fin;
}

//--------------------------------------------------------------------------------------------------------------

//checks to see if a card is a K Q J or T
bool isRoyalty(Card a){
  return(a.n == 10 || a.s == 11 || a.s == 12 || a.s == 13 || a.s == 14);
}

//---------------------------------------------------------------------------------------------------------------
//checks for a flush by counting the number of each suit
bool checkFlush(Card h[]){
  int hearts=0;
  int diamonds=0;
  int clubs=0;
  int spades=0;
  int i;
  for(i=0; i<7; i++){
    if(h[i].s== 'H')
      hearts++;
    if(h[i].s == 'D')
      diamonds++;
    if(h[i].s == 'C')
      clubs++;
    if(h[i].s == 'S')
        spades++;
  }

  return( (hearts>4) || (diamonds>4) || (clubs>4) || (spades>4) );
}


//--------------------------------------------------------------------------------------------------------------
bool checkSFlush(Card h[]){
  bool fin; //checks for a straight and then checks to see if those cards have the same suit
  int i;
  for(i=0; i<3; i++){
    if( (h[i].n == h[i+1].n) && (h[i].s == h[i+1].s) &&
        (h[i].n == h[i+2].n) && (h[i].s == h[i+2].s) &&
        (h[i].n == h[i+3].n) && (h[i].s == h[i+3].s) &&
        (h[i].n == h[i+4].n) && (h[i].s == h[i+4].s)
        )
        fin=TRUE;
  }
  return fin;
}



//--------------------------------------------------------------------------------------------------------------
//counts number of pairs(handles 2 of a kind, adn 4 of a kind)
int numOfPair(Card h[]){
  int counter=0;
  int i, j;
  for(i=0; i<7; i++){
    for(j=i; j<7; j++){
      if(i!=j){
        if(h[i].n == h[j].n)
          counter++;
      }
    }
  }
  return counter;
}

//--------------------------------------------------------------------------------------------------------------
//checks for a straight
bool checkStraight(Card h[]){
  bool fin= FALSE;
  int i;
  for(i=0; i<3; i++){
    if( (h[i].n == h[i+1].n) &&
        (h[i].n == h[i+2].n) &&
        (h[i].n == h[i+3].n) &&
        (h[i].n == h[i+4].n)
        )
        fin=TRUE;
  }
    return fin;

}


//----------------------------------------------------------------------------------------------------------------
//checks for a full by checking for a pair and a triple
bool checkFull(Card h[]){
  bool tri= FALSE; //boolean that stores whether there is a triple or not

  int a;
  int b;
  int c;
  int i;

  for(i=0; i<4; i++){
    if((h[i].n == h[i+1].n) && (h[i].n == h[i+2].n)){ //checks for a triple and saves the cards that have been used
      a=i;
      b=i+1;
      c=i+2;
      tri=TRUE;
      break;
    }
  }

  Card re[4]; //new Array without cards used in the triple (re)
  int counter=0;
  int z;
  for(z=0; z<7; z++){ //populating re
    if(z!=a && z!=b && z!=c){
      re[counter]=h[z];
      counter++;
    }
  }

  bool cp=FALSE; //cp=check for pair

  //checks for a pair
  int x;
  int f;
  for(x=0; x<4; x++){
    for(f=x; f<4; f++){
      if((re[x].n==re[f].n) && (x!=f))
        cp=TRUE;
        break;
    }
  }
  //checks to see if there is a pair and a triple
  return(cp && tri);
}

//----------------------------------------------------------
//checks for three of a kind
bool checkFour(Card h[]){
  bool fin= FALSE;
  int i;
  for(i=0; i<3; i++){
    if((h[i].n == h[i+1].n) && (h[i].n == h[i+2].n) && (h[i].n == h[i+3].n)) {
      fin=TRUE;
      break;
    }
  }
  return fin;
}

//----------------------------------------------------------
//checks for three of a kind
bool checkT(Card h[]){
  bool fin= FALSE;
  int i;
  for(i=0; i<4; i++){
    if((h[i].n == h[i+1].n) && (h[i].n == h[i+2].n)){
      fin=TRUE;
    }
  }
  return fin;
}

//-----------------------------------------------------------------

//reads file and fills players
void makePlayersHands(struct Player p1, struct Player p2, struct Player p3, FILE *fp){ // HELP -------------------

  if(fp!=NULL){
  char p11[3];
  char p12[3]; char p21[3]; char p22[3]; char p31[3]; char p32[3];
  char c1[3];
  char c2[3], c3[3], c4[3], c5[3];
  char num;
  char suite;

  fscanf(fp, "%s", p11);
  suite= p11[1];
  num=p11[0];

  p1.hand[0]=makeCard(num, suite);

  fscanf(fp, "%s", p12);
  suite= p12[1];
  num=p12[0];

  p1.hand[1]=makeCard(num, suite);

  fscanf(fp, "%s", p21);
  suite= p21[1];
  num=p21[0];

  p2.hand[0]=makeCard(num, suite);

  fscanf(fp, "%s", p22);
  suite= p22[1];
  num=p22[0];

  p2.hand[1]=makeCard(num, suite);

  fscanf(fp, "%s", p31);
  suite= p31[1];
  num=p31[0];

  p3.hand[0]=makeCard(num, suite);


  fscanf(fp, "%s", p32);
  suite= p32[1];
  num=p32[0];

  p3.hand[1]=makeCard(num, suite);

  fscanf(fp, "%s", c1);
  suite= c1[1];
  num=c1[0];

  p1.hand[2]=makeCard(num, suite);
  p2.hand[2]=makeCard(num, suite);
  p3.hand[2]=makeCard(num, suite);

  fscanf(fp, "%s", c2);
  suite= c2[1];
  num=c2[0];

  p1.hand[3]=makeCard(num, suite);
  p2.hand[3]=makeCard(num, suite);
  p3.hand[3]=makeCard(num, suite);

  fscanf(fp, "%s", c3);
  suite= c3[1];
  num=c3[0];

  p1.hand[4]=makeCard(num, suite);
  p2.hand[4]=makeCard(num, suite);
  p3.hand[4]=makeCard(num, suite);

  fscanf(fp, "%s", c4);
  suite= c4[1];
  num=c4[0];

  p1.hand[5]=makeCard(num, suite);
  p2.hand[5]=makeCard(num, suite);
  p3.hand[5]=makeCard(num, suite);

  fscanf(fp, "%s", c5);
  suite= c5[1];
  num=c5[0];

  p1.hand[6]=makeCard(num, suite);
  p2.hand[6]=makeCard(num, suite);
  p3.hand[6]=makeCard(num, suite);


}else{
  printf("File not found");
}
}
