#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

//RESOURCES: FINGOLIAN FEMBOY FOR 2D ARRAY, I CAN'T STOP WINNING

/*printf("
....................................................................................................
....................................................................................................
....................................................................................................
....................................................................................................
.....................................................@@@@@@@@@@@@@@@@@@@@@..........................
.......@@@@@@@@@@@@@@@@.........................@@@@@......................@@@@@@@@@@@@.............
......@@..............@@@@@@................@@@........................................@@...........
......@@...................@@@@@........@@@@@@@@........@@@@@@@@@@..................@@@@@...........
.......@@.......................@@@.....@.......@@@@@@@@..........@@@@@@@@.....@@@@@....@...........
........@@@@@.....................@@...@...................................@@@..........@...........
......@@....@@@@@@@@@@@............@..@@....................................@...........@...........
.......@...........@@@.@@@@@@@@@@@@...@@...@@@@@...@@@@@@@..@@@@@@@@@@@@....@..........@@...........
.......@@@@.....@@@.@@@@@...........@@@...@...@...@@..@....@@.......@..@....@..........@............
..........@@@@@@@....@..@@@@@....@@@@.@..@@.@....@@..@..@..@@.@@..@@...@....@..........@............
.....................@@......@@@@@....@..@..@..@.@..@@..@.@@.@@.@.@.@.@@....@..........@............
.....................@@..............@..@@.@@.@.@@.@@..@@.@....@..@.@.@@...@@..........@............
.....................@@..............@..@.@......@.@...@@.@.@.@...@.@.@....@...........@............
.....................@@..............@..@@.@...@.@.@..@.@.@.@.@.@.@@..@....@..........@@............
.....................@@..............@..@@.@..@@.@..@.@..@.@..@@@..@.@@....@...........@............
.....................@@.............@...@..@...@.@@.@.@..@.@...@@..@..@....@...........@............
.................@@@@@@.............@...@@..@....@@..@.@...@.@..@@.@@.@...@@...........@............
................@@...@@@............@....@@.@..@@@.@..@.@@.@..@.@.@.@.@...@...........@@............
................@@.....@@@.........@@.....@..@....@....@.@..@.@.......@@..@............@............
................@@@@@@@..@@........@@......@@......@........@@@@@@@@@@@...@...........@@............
...........@@@@@.@.....@@.@@.......@.........@@@@@@@@@@@@@.................@.........@@.............
...........@.@..@@@@@@@@@@@@@......@.......................................@......@@@...............
...........@..@@........@.@@@@@@@@@@............................@@.........@.@@@@@..................
..........@@@@@@@@@@@@@@..@@........@@@@@@@@@@@@@@@@@@@@@@@@@@@@..@@@@@@@@@@@.......................
..........@...............@.........................................................................
..........@@@@@@@@@@@@@@@@@.........................................................................
....................................................................................................
  ___    ____    _    _   _ _ _____   ____ _____ ___  ____   __        _____ _   _ _   _ ___ _   _  ____ 
 |_ _|  / ___|  / \  | \ | ( )_   _| / ___|_   _/ _ \|  _ \  \ \      / /_ _| \ | | \ | |_ _| \ | |/ ___|
  | |  | |     / _ \ |  \| |/  | |   \___ \ | || | | | |_) |  \ \ /\ / / | ||  \| |  \| || ||  \| | |  _ 
  | |  | |___ / ___ \| |\  |   | |    ___) || || |_| |  __/    \ V  V /  | || |\  | |\  || || |\  | |_| |
 |___|  \____/_/   \_\_| \_|   |_|   |____/ |_| \___/|_|        \_/\_/  |___|_| \_|_| \_|___|_| \_|\____|
");*/                                                                                                         



//CARD STRUCT
typedef struct {
  int value;
  char name[20];
  int drawn;
} Card;

//GENERATE DECK IN SEPARATE .TXT FILE, IMPORT DECK, SHUFFLE FOR ACTUAL PROGRAM

//RANDOMLY GENERATING CARD DECK
//TBA: ENSURE NO CARD REPEATED MORE THAN 4 TIMES PER DECK USED
void deckShuffle(const char cardList[][16], Card *deck)
{
  int i;
  srand(time(0)); //INCLUDE IN MAIN?
  
  //printf("deckShuffle check 1");
  
  for (i = 0; i < 104; i++)
  {
    //SETTING CARD VALUE FROM 2 TO 11
    deck[i].value = (rand() % 10) + 2;
    
    //printf("deckShuffle check 2");
    
    //SETTING CARD NAME
    //FOR CARD VALUE 10, PICKS RANDOM NAME FROM "ten" TO "King" 
    if (deck[i].value == 10)
    {
      //deck[i].name = cardList[(rand() % (11 - 8 + 1)) + 8];
      strcpy(deck[i].name, cardList[(rand() % 3) + 9]);
    }
    //FOR CARD VALUE 11, SET NAME TO "Ace"
    else if (deck[i].value == 11)
    {
      //deck[i].name = cardList[12];
      strcpy(deck[i].name, cardList[12]);
    }
    //FOR CARD VALUE UNDER 10, SET NAME TO CARD VALUE
    else
    {
      //deck[i].name = cardList[deck[i].value - 2];
      strcpy(deck[i].name, cardList[deck[i].value - 2]);
    }
    
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
  //const char *cardList[13] = {"two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "Jack", "Queen", "King", "Ace"};
  const char cardList[][16] = {"two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "Jack", "Queen", "King", "Ace"};
  //ARRAY OF STRUCTS FOR CARDS
  Card deck[103];
  Card playerHand[10];
  Card dealerHand[10];
  //INT DECLARATIONS  
  int choice, playerHandValue, dealerHandValue, playerIndexPos, dealerIndexPos, exitFlag, i;
  
  srand(time(0));
  
  //printf("Break 1\n");
  //printf("%ld\n", __STDC_VERSION__);
  
  //EXECUTING SHUFFLE FUNCTION
  deckShuffle(cardList, deck);
  
  //printf("Break 2\n");
  //POPULATING PLAYER & DEALER HANDS
  //TBA: ADD FUNCTIONALITY FOR CHECKING DRAWN STATUS
  for (i = 0; i < 2; i++)
  {
    playerHand[i] = deck[(rand() % 104)];
    dealerHand[i] = deck[(rand() % 104)];
  }
  
  //ace(Card *playerHand)

  
  playerIndexPos = 2;
  dealerIndexPos = 2;
  
  //PRINT PLAYER HAND TO TERMINAL
  printf("\tCard 1 name & value: %s %d\n\
        Card 2 name & value: %s %d\n",
        playerHand[0].name,
        playerHand[0].value,
        playerHand[1].name,
        playerHand[1].value);
  
  //BLACKJACK WIN CASE
  if (playerHand[0].value + playerHand[1].value == 21)
  {
    printf("I CAN'T STOP WINNING\n");
    return 0;
  }
  else if (dealerHand[0].value + playerHand[1].value == 21)
  {
    printf("AW DANGIT\n");
    return 0;
  }
  
  //PLAYER CHOICE MENU LOOP
  while (exitFlag != 1)
  {
    //PLAYER HAND VALUE CALCULATION
    //MAKE WHILE LOOP EXIT IF PLAYERHANDVALUE > 21
    playerHandValue = 0;
    for (i = 0; i < 10; i++)
    {
      playerHandValue += playerHand[i].value;
      
      if (playerHandValue > 21)
      {
        printf("You busted\n");
        exitFlag = 1;
        break;
      }
    }
    
    //PLAYER HAND VALUE PRINT STATEMENT
    printf("\tPlayer hand value is: %d\n", playerHandValue);
    
    //FIXME
    if (exitFlag == 1)
      break;
    
    //PLAYER SELECTION PRINT
    printf("Please select from the following options: Choose (1) to hit, (2) to stand, (3) to split\n");
    choice = input_verification_type_int("Invalid Selection: Choose (1) to hit, (2) to stand, (3) to split\n");
  
    switch (choice)
    {
      //HIT CASE
      case 1:
        playerHand[playerIndexPos] = deck[(rand() % 104)];
        //ace(Card *playerHand)
        printf("\tCard %d name & value: %s %d\n",
              playerIndexPos,
              playerHand[playerIndexPos].name,
              playerHand[playerIndexPos].value);
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
      default:
        printf("Invalid Selection: Choose (1) to hit, (2) to stand, (3) to split\n");
        break;
    }
  }
  
  dealerHandValue = dealerHand[0].value + dealerHand[1].value;
  printf("Dealer Hand Value: %d\n", dealerHandValue); 
  
  //DEALER BEHAVIOR
  //TBA: INSERT DEALER HIT INTO ELSE IF IN FOR LOOP
  while (dealerHandValue < 17)
  {    
    for (i = 0; i < 10; i++)
    {
      dealerHandValue += dealerHand[i].value;
      printf("Dealer Hand Value: %d\n", dealerHandValue);
      
      if (dealerHandValue > 21 && playerHandValue < 21)
      {
        printf("I CAN'T STOP WINNING\n");
        return 0;
        break;
      }
    dealerHand[dealerIndexPos] = deck[(rand() % 104)];
    dealerIndexPos++;
    }
  }
  
  //WIN CONDITIONS
  if (playerHandValue > dealerHandValue && playerHandValue < 21)
  {
    printf("I CAN'T STOP WINNING\n");
  }
  else if (playerHandValue < dealerHandValue && dealerHandValue < 21)
  {
    printf("AW DANGIT\n");
  }
  else if (playerHandValue == dealerHandValue && playerHandValue < 21)
  {
    printf("It's a tie");
  }
  else
    printf("If you're seeing this, it be brogen.\n");

  return 0;
}
  
  
          
          
  