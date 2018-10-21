#include "poker.h"





typedef struct Cards{
    int n;
    char s;
} Card;
Card hand[7];


typedef struct Players{
  Card hand[7]; //makes an array of cards, check if it works
  int count[15]; //gives the amount of times that a certain card value is seen in the hand
  int handValue;
}Player;
Player p1, p2 ,p3;



int main(){
  char buff[255];
  FILE *fp; // file to read
  FILE *ap; //used for while loop
  FILE *pp; //file to print to
  fp= fopen("sampleinput.txt", "r");
  pp= fopen("finalPrint.txt", "w");
  ap= fopen("sampleinput.txt", "r");
  while(fgets(buff, 255, ap)!=NULL){
    makePlayersHands(&p1, &p2, &p3, fp);


    //---------------------
    sortCards((p1.hand));
    sortCards((p2.hand));
    sortCards((p3.hand));

    makeCount(&p1);
    makeCount(&p2);
    makeCount(&p3);
    //------------------------

    p1.handValue= getHandValue(p1);
    int one= getHandValue(p1);

    p2.handValue= getHandValue(p2);
    int two= getHandValue(p2);

    p3.handValue= getHandValue(p3);
    int three= getHandValue(p3);




//----
  if (one > two){
      if(one > three){
        fprintf(pp, "Player 1 wins \n");

      }else{
        fprintf(pp, "Player 3 wins \n");
      }
//-----
}else if (two > three){
      fprintf(pp, "Player 2 wins \n");
//------
  }else{
      fprintf(pp, "Player 3 wins \n");
    }
  }
  fclose(fp);
  fclose(pp);
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
  ret.n=number;
  ret.s=suite;
  return ret;
}
//------------------------------------------------------------------------------------------------------------
//Calculates hand value, whoever has the highest hand value wins
int getHandValue(Player p){

  if(checkRFlush(p.hand) ){
    //printf("Rflush\n");
    return 1000+highest(p.hand);
  }

  if(checkSFlush(p.hand) ){
    //printf("Sflush\n");
    return 900+highest(p.hand);
  }

  if(checkFour( p.count) ){
    //printf("Four of a Kind\n");
    return 800+highest(p.hand);
  }

  if(checkFull(p.count)){ // checks for full house
    //printf("Full House\n");
    return 700+highest(p.hand);

  }

  if( checkFlush(p.hand) ){ // checks for flush
    //printf("Flush\n");
    return 600+highest(p.hand);

  }

  if(checkStraight(p.count)){ // checks for a straight
    //printf("Straight\n");
    return 500+highest(p.hand);

  }

  if(checkT(p.count)){
    //printf("Triple\n");
    return 400+highest(p.hand);

  }

  if(numOfPair( p.count)>1){ //checks for 2 pairs
    //printf("2 Pairs\n");
    return 300+highest(p.hand);

  }

  if (numOfPair( p.count) == 1) { //checks for a pair
    //printf("1 Pair\n");
    return 200+highest(p.hand);


  } else { //if the player has nothing, it returns highest card
    return highest(p.hand);
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

int comparator(void *p, void *q){
    int x = ((Card *)p)->n;
    int y = ((Card *)q)->n;
    return (x - y);
}

//--------------------------------------------------------------------------------------------------------------
//Sorting using  qsort
void sortCards(Card h[]){
  qsort((void*)h, 7, sizeof(h[0]), comparator);
}

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
  return(a.n == 10 || a.n == 11 || a.n == 12 || a.n == 13 || a.n == 14);
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

//------------------------------------------------------------------
void makeCount(Player* p){
  for(int i=0; i<7; i++){
    p->count[p->hand[i].n-1]+=1;
  }
}


//--------------------------------------------------------------------------------------------------------------
bool checkSFlush(Card h[]){
  bool fin=FALSE; //checks for a straight and then checks to see if those cards have the same suit
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
int numOfPair(int count[]){
  int counter=0;
  int i;
  for(i=0; i<14; i++){
    if(count[i]==2)
      counter++;
    if(counter==2)
      return 2;
  }
  return counter;
}

//--------------------------------------------------------------------------------------------------------------
//checks for a straight
bool checkStraight(int count[]){
  bool fin= FALSE;
  int i;
  for(i=0; i<10; i++){
    if( count[i]>0 && count[i+1]>0 && count[i+2]>0 && count[i+3]>0 && count[i+4>0])
        return TRUE;
  }
    return fin;

}


//----------------------------------------------------------------------------------------------------------------
//checks for a full by checking for a pair and a triple
bool checkFull(int count[]){
  bool tri= FALSE; //boolean that stores whether there is a triple or not
  bool two= FALSE;
  int i;
  for(i=0; i<14; i++){
    if(count[i]==2)
      two=TRUE;
    else if(count[i]==3)
      tri=TRUE;
  }
  //checks to see if there is a pair and a triple
  return(two && tri);
}

//----------------------------------------------------------
//checks for three of a kind
bool checkFour(int count[]){
  bool fin= FALSE;
  int i;
  for(i=0; i<14; i++){
      if(count[i]>3)
        return TRUE;
    }
  return fin;
}

//----------------------------------------------------------
//checks for three of a kind
bool checkT(int count[]){
  bool fin= FALSE;
  int i;
  for(i=0; i<14; i++){
      if(count[i]>2)
        return TRUE;
    }
  return fin;
}


//-----------------------------------------------------------------

//reads file and fills players
void makePlayersHands(Player* p1, Player* p2, Player* p3, FILE *fp){ //  -------------------

  if(fp){
  char p11[3];
  char p12[3]; char p21[3]; char p22[3]; char p31[3]; char p32[3];
  char c1[3];
  char c2[3], c3[3], c4[3], c5[3];
  char num;
  char suite;

  fscanf(fp, "%s", p11);
  suite= p11[1]; //segmentation fault
  num=p11[0];

  p1->hand[0]=makeCard(num, suite);

  fscanf(fp, "%s", p12);
  suite= p12[1];
  num=p12[0];

  p1->hand[1]=makeCard(num, suite);


  fscanf(fp, "%s", p21);
  suite= p21[1];
  num=p21[0];

  p2->hand[0]=makeCard(num, suite);

  fscanf(fp, "%s", p22);
  suite= p22[1];
  num=p22[0];

  p2->hand[1]=makeCard(num, suite);

  fscanf(fp, "%s", p31);
  suite= p31[1];
  num=p31[0];

  p3->hand[0]=makeCard(num, suite);


  fscanf(fp, "%s", p32);
  suite= p32[1];
  num=p32[0];

  p3->hand[1]=makeCard(num, suite);

  fscanf(fp, "%s", c1);
  suite= c1[1];
  num=c1[0];

  p1->hand[2]=makeCard(num, suite);
  p2->hand[2]=makeCard(num, suite);
  p3->hand[2]=makeCard(num, suite);

  fscanf(fp, "%s", c2);
  suite= c2[1];
  num=c2[0];

  p1->hand[3]=makeCard(num, suite);
  p2->hand[3]=makeCard(num, suite);
  p3->hand[3]=makeCard(num, suite);


  fscanf(fp, "%s", c3);
  suite= c3[1];
  num=c3[0];

  p1->hand[4]=makeCard(num, suite);
  p2->hand[4]=makeCard(num, suite);
  p3->hand[4]=makeCard(num, suite);


  fscanf(fp, "%s", c4);
  suite= c4[1];
  num=c4[0];

  p1->hand[5]=makeCard(num, suite);
  p2->hand[5]=makeCard(num, suite);
  p3->hand[5]=makeCard(num, suite);


  fscanf(fp, "%s", c5);
  suite= c5[1];
  num=c5[0];

  p1->hand[6]=makeCard(num, suite);
  p2->hand[6]=makeCard(num, suite);
  p3->hand[6]=makeCard(num, suite);




}else{
  printf("File not found");
}
}
