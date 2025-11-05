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

//DECK SHUFFLING FUNCTION
void deckShuffle() {

  // Opens file containing the deck of cards
  FILE *blackjackDeck;
  blackjackDeck = fopen("blackjackdeck.txt", "r");
  if (blackjackDeck == NULL) {
    printf("Error: Could not open file.\n");
    return;
  }
  
  // Variable declarations and reads file to lines array
  char lines[110][256];
  char line1[256], line2[256];
  int targetLine1, targetLine2, i=0, j;
  srand(time(0));
  
  while (fgets(lines[i], sizeof(lines[i]), blackjackDeck)) {
    i++;
  }
  fclose(blackjackDeck);
  
  // Shuffles lines array
  for (j=0; j<1000000; j++) {
  
    // Finds a two random target lines and saves them to line1 and line2
    targetLine1 = rand() % (104);
    strcpy(line1, lines[targetLine1]);
  
    targetLine2 = rand() % (104);
    strcpy(line2, lines[targetLine2]);
  
  
    // Swaps line1 and line2 within the lines array
    strcpy(lines[targetLine2], line1);
    strcpy(lines[targetLine1], line2);
  }
    
  // Prints the shuffled lines array all back to the file
  blackjackDeck = fopen("blackjackdeck.txt", "w");
  for (i=0; i<104; i++) {
    fprintf(blackjackDeck, lines[i]);
  }
  fclose(blackjackDeck);
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

int main() {
  //INT DECLARATIONS  
  int choice, playerHandValue, dealerHandValue, playerIndexPos, dealerIndexPos, exitFlag, i;
  srand(time(0));
  
  //DEFINING THE CARD DECK
  Card deck[104];
  Card playerHand[10];
  Card dealerHand[10];
  
  //reads in from file || Note: idk if it would be more efficient to use a deck array or to just read in from file
  deckShuffle();
  deckShuffle();
  FILE *blackjackDeck;
  blackjackDeck = fopen("blackjackdeck.txt", "r");
  if (blackjackDeck == NULL) {
    printf("Error: Could not open file.\n");
    return;
  }
  
  i=0;
  while (fgets(deck[i].name, sizeof(deck[i].name), blackjackDeck)) {
    i++;
  }
  fclose(blackjackDeck);
  
  //assigns values to each card based on name and sets "drawn" to 0
  for (i=0; i<104; i++) {
    if ( strncmp(deck[i].name, "Ace", 3) == 0) {
      deck[i].value = 11;
    }
    else if ( strncmp(deck[i].name, "King", 4) == 0
    || strncmp(deck[i].name, "Queen", 5) == 0
    || strncmp(deck[i].name, "Jack", 4) == 0
    || strncmp(deck[i].name, "Ten", 3) == 0) {
      deck[i].value = 10;
    }
    else if ( strncmp(deck[i].name, "Nine", 4) == 0) {
      deck[i].value = 9;
    }
    else if ( strncmp(deck[i].name, "Eight", 5) == 0) {
      deck[i].value = 8;
    }
    else if ( strncmp(deck[i].name, "Seven", 5) == 0) {
      deck[i].value = 7;
    }
    else if ( strncmp(deck[i].name, "Six", 3) == 0) {
      deck[i].value = 6;
    }
    else if ( strncmp(deck[i].name, "Five", 4) == 0) {
      deck[i].value = 5;
    }
    else if ( strncmp(deck[i].name, "Four", 4) == 0) {
      deck[i].value = 4;
    }
    else if ( strncmp(deck[i].name, "Three", 5) == 0) {
      deck[i].value = 3;
    }
    else if ( strncmp(deck[i].name, "Two", 3) == 0) {
      deck[i].value = 2;
    }
    
    deck[i].drawn = 0;
  }
  
  //printf("Break 1\n");
  //printf("%ld\n", __STDC_VERSION__);
  
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


// COPIED WIP FUNCTIONS FROM LAST ITERATION
/* int Ace(Card *playerHand)
{ 
  int ace;
  for (i = 0; i < 10; i++)
  {
    if (playerHand[i] == 11)
    {
      printf("You pulled an Ace! Would you like to keep it as a 1, or change it to an 11? \n");
     scanf("%d", &ace);

     
      // insert error checking here 
      ace = input_validation_check_int("Invalid input. Please input 1 or 11.\n");
      // this is Ryan's error handling function. 

      if (ace == 11)
      {
        playerHand[i].value += 11;
      }

      else if (ace == 1)
      {
        playerHand[i].value += 1;
      }
      else
      {
        // insert shit be borke
        printf("Shit be broke\n");
      }
  }
  return playerhand[i].value;
} */


// idea: make a function for Dealer hits depending on CPU difficulty that the player chose 

/* int Dealer_Hit()
{
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
  // can change function depending on how we want to do the dealer difficulty and such. 
} */

/* int funds()
{
    gambling/funding functions for later if wanted
    for ( i = 0; i < player_num; i++)
    {
    printf("Player %d, would you like to add funds?", i) ;
    // something something scanf
    // if 1, scanf for funds amount 
    // if 2, check if they're in debt
    // if they're in debt for a certain amount, kick them out lol 
    
    }
}
*/
