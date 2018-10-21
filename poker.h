#include <stdio.h>
#include <stdlib.h>
typedef int bool;
#define TRUE 1
#define FALSE 0

int getHandValue(Player p);
int highest(Card h[]);
void sortCards(Card* h);
bool checkRFlush(Card h[]);
bool isRoyalty(Card a);
bool checkFlush(Card h[]);
bool checkSFlush(Card h[]);
int numOfPair(int count[]);
bool checkStraight(int count[]);
bool checkFull(int count[]);
bool checkFour(int count[]);
bool checkT(int count[]);
void makePlayersHands( Player* p1, Player* p2, Player* p3, FILE *fp);
Card makeCard(char num, char suite);
int comparator(void *p, void *q);
void makeCount(Player* p);
void getWinner(Player p1, Player p2, Player p3);

