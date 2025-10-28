#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <time.h>

//CARD STRUCT
typedef struct {
  int value;
  char name[];
  int drawn;
} Card;


//GENERATE DECK IN SEPARATE .TXT FILE, IMPORT DECK, SHUFFLE FOR ACTUAL PROGRAM

//RANDOMLY GENERATING CARD DECK
//TBA: ENSURE NO CARD REPEATED MORE THAN 4 TIMES PER DECK USED
void deckShuffle(char *cardList, Card *deck)
{
  int i;
  srand(time(0)); //INCLUDE IN MAIN?
  
  for (i = 0; i < 104; i++)
  {
    //SETTING CARD VALUE FROM 2 TO 11
    deck[i].value = (rand() % 11 - 2 + 1) + 2;
    
    //SETTING CARD NAME
    //FOR CARD VALUE 10, PICKS RANDOM NAME FROM "ten" TO "King" 
    if (deck[i].value == 10)
    {
      deck[i].name = cardList[(rand() % (11 - 8 + 1)) + 8];
    }
    //FOR CARD VALUE 11, SET NAME TO "Ace"
    else if (deck[i].value == 11)
    {
      deck[i].name = cardList[12];
    }
    //FOR CARD VALUE UNDER 10, SET NAME TO CARD VALUE
    else
      deck[i].name = cardList[deck[i].value - 2];
    
    //ENSURING DRAWN VALUE SET TO 0
    deck[i].drawn = 0;
  }
}

//INPUT VALIDATION FUNCTION FROM HW5
int input_verification_type_int(char *err_msg)
{
  int input = 0;

  while (1) 
  {
    if (scanf("%d", &input) == 1) 
    {
      return input;
    } 
    else 
    {
      printf("%s\n", err_msg);
      scanf("%*[^\n]");
    }
  }
}

int main()
{
  //ARRAY OF STRINGS FOR CARD NAMES
  cardlist[12] = {"two", "three", "four", "five", "six", "seven", "eight", 
                  "nine", "ten", "Jack", "Queen", "King", "Ace"};
  //ARRAY OF STRUCTS FOR CARDS
  Card deck[103];
  Card playerHand[10];
  Card dealerHand[10];
  //PLAYER CHOICE OPTION VAR
  int choice, playerHandValue, dealerHandValue, playerIndexPos, dealerIndexPos;
  
  srand(time(0));
  
  //EXECUTING SHUFFLE FUNCTION
  deckShuffle(&cardlist, &deck);
  
  //POPULATING PLAYER & DEALER HANDS
  //TBA: ADD FUNCTIONALITY FOR CHECKING DRAWN STATUS
  for (i = 0; i < 2; i++)
  {
    playerHand[i] = deck[(rand() % 104)];
    dealerHand[i] = deck[(rand() % 104)];
  }
  
  playerIndexPos = 2;
  dealerIndexPos = 2;
  
  //PRINT PLAYER HAND TO TERMINAL
  printf("\t\t\t\t\tCard 1 name & value: %s\t%d\n\
          Card 2 name & value: %s\t%d\n",
          playerHand[0].name,
          playerHand[0].value,
          playerHand[1].name,
          playerHand[1].value);
  
  //BLACKJACK WIN CASE
  if (playerHand[0].value + playerHand[1].value == 21)
  {
    printf("YOUR WINNER\n");
  }
  else if (dealerHand[0].value + playerHand[1].value == 21)
  {
    printf("YOUR LOOSER\n");
  }
  
  //PLAYER CHOICE MENU LOOP
  while (exitFlag != 1)
  {
    //PLAYER SELECTION PRINT
    printf("Please select from the following options: Choose (1) to hit, (2) to stand, (3) to split\n");
    choice = input_verification_type_int("Invalid Selection: Choose (1) to hit, (2) to stand, (3) to split\n");
    
    //PLAYER HAND VALUE CALCULATION
    for (i = 0; i < 10; i++)
    {
      playerHandValue += playerHand[i].value;
      
      if (playerHandValue > 21)
      {
        printf("You busted\n");
        exitFlag = 1;
        break
      }
    }
    
    //PLAYER HAND VALUE PRINT STATEMENT
    printf("Player hand value is: %d\n", playerHandValue);
  
    switch (choice)
    {
      //HIT CASE
      case 1:
        playerHand[playerIndexPos] = deck[(rand() % 104)];
        playerIndexPos++;
        break;
      //STAND CASE
      case 2: 
        exitFlag = 1;
        break;
      case 3:
        //SPLIT FUNCTION
        //playerHand1[0] = playerHand[0];
        //playerHand2[0] = playerHand[1];
        break;
      default;
        printf("Invalid Selection: Choose (1) to hit, (2) to stand, (3) to split\n");
        break;
    }
  }
  
  dealerHandValue = dealerHand[0].value + dealerHand[1].value; 
  
  //DEALER BEHAVIOR
  while (dealerHandValue < 17)
  {
    dealerHand[dealerIndexPos] = deck[(rand() % 104)];
    dealerIndexPos++;
    
    for (i = 0; i < 10; i++)
    {
      dealerHandValue += dealerHand[i].value;
      
      if (dealerHandValue > 21)
      {
        printf("YOUR WINNER\n");
        break
      }
    }
  }
  
  //WIN CONDITIONS
  if (playerHandValue > dealerHandValue)
  {
    printf("YOUR WINNER\n");
  }
  else if (playerHandValue < dealerHandValue)
  {
    printf("YOUR LOOSER\n");
  }
  else if (playerHandValue == dealerHandValue)
  {
    printf("It's a tie");
  }
  else
    printf("If you're seeing this, it be brogen.\n");

  return 0;
}
  
  
          
          
  