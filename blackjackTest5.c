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

//HAND VALUE CALCULATION FUNCTION
int hand_value_calculation(Card *hand)
{
  int playerHandValue = 0;
  int i = 0;
  
  for (i = 0; i < 10; i++)
  {
    //printf("hand[i].value: %d\nplayerHandValue: %d\n", hand[i].value, playerHandValue);
    playerHandValue += hand[i].value;
  }
  return playerHandValue;
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

void ace(Card *playerHand)
{ 
  int ace, i = 0;
  for (i = 0; i < 10; i++)
  {
    if (playerHand[i].value == 11 || playerHand[i].value == 1)
    {
      printf("Would you like your ace to have a value of 1 or 11?\n");
      
      while (ace != 1 && ace != 11)
      {
        ace = input_verification_type_int("Invalid input. Please input 1 or 11.\n");
      }
      
      playerHand[i].value = ace;
    }
  }
}   

int main() {
  //INT DECLARATIONS  
  int choice, playerHandValue, dealerHandValue, playerIndexPos, dealerIndexPos, exitFlag, i, playerCardIndex, dealerCardIndex;
  char line[128];
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
    return 0;
  }
  
  //SCAN DECK INTO ARRAY
  i = 0;  
  while (fgets(line, sizeof(line), blackjackDeck) != NULL) 
  {
    if (sscanf(line, " %20[^0-9] %d", deck[i].name, &deck[i].value) == 2) 
    {
      //printf("%s %d; i=%d\n", deck[i].name, deck[i].value, i);
      i++; 
    }
  }
  fclose(blackjackDeck);
  
  //sets drawn status to 0
  for (i=0; i<104; i++) {
    deck[i].drawn = 0;
  }
  

  for (i = 0; i < 2; i++) 
  {  
    while (1) 
    { 
      playerCardIndex = rand() % 104; 
      if (deck[playerCardIndex].drawn == 0)
      { 
        playerHand[i] = deck[playerCardIndex]; 
        deck[playerCardIndex].drawn = 1; 
        break; 
      }
    }

    while (1) 
    { 
      dealerCardIndex = rand() % 104; 
      if (deck[dealerCardIndex].drawn == 0) 
      { 
        dealerHand[i] = deck[dealerCardIndex]; 
        deck[dealerCardIndex].drawn = 1; 
        break; 
      }
    }
  }

  
  
  
  ace(playerHand);
  
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
    playerHandValue = hand_value_calculation(playerHand);
    printf("Player Hand Value: %d\n", playerHandValue);
    if (playerHandValue > 21)
    {
      printf("You busted.\n");
      exitFlag = 1;
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
        playerIndexPos++;
        playerHand[playerIndexPos] = deck[(rand() % 104)];
        printf("\tCard %d name & value: %s %d\n",
              playerIndexPos,
              playerHand[playerIndexPos].name,
              playerHand[playerIndexPos].value);
        ace(playerHand);
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
  
//  dealerHandValue = dealerHand[0].value + dealerHand[1].value;
//  printf("Dealer Hand Value: %d\n", dealerHandValue); 
  
  //DEALER BEHAVIOR
  //TBA: INSERT DEALER HIT INTO ELSE IF IN FOR LOOP
  while (dealerHandValue < 17 && playerHandValue < 22)
  {
      
    /*for (i = 0; i < 10; i++)
    {
      dealerHandValue += dealerHand[i].value;
      printf("Dealer Hand Value: %d\n", dealerHandValue);
      
      if (dealerHandValue > 21)
      {
        break;
      }
    }*/
    dealerHandValue = hand_value_calculation(dealerHand);
    printf("Dealer Hand Value: %d\n", dealerHandValue);
    
    dealerHand[dealerIndexPos] = deck[(rand() % 104)];
    dealerIndexPos++;
  }
  
  //WIN CONDITIONS
  if (playerHandValue > dealerHandValue && playerHandValue < 22)
  {
    printf("I CAN'T STOP WINNING\n");
  }
  else if (playerHandValue < 22 && dealerHandValue > 21)
  {
    printf("I CAN'T STOP WINNING\n");
  }
  else if (playerHandValue < dealerHandValue && dealerHandValue < 22)
  {
    printf("AW DANGIT\n");
  }
  else if (playerHandValue > 21 && dealerHandValue < 22)
  {
    printf("AW DANGIT\n");
  }
  else if (playerHandValue == dealerHandValue && playerHandValue < 22)
  {
    printf("It's a tie\n");
  }
  else if (playerHandValue > 21 && dealerHandValue > 21)
  {
    printf("It's a tie\n");
  }
  else
    printf("If you're seeing this, it be brogen.\n");

  return 0;
}


// COPIED WIP FUNCTIONS FROM LAST ITERATION
/*void ace(Card *playerHand)
{ 
  int ace = 0;
  for (i = 0; i < 10; i++)
  {
    if (playerHand[i].value == 11 || playerHand[i].value == 1)
    {
      printf("Would you like your ace to have a value of 1 or 11?\n");
      
      while (ace != 1 || ace != 11)
      {
        ace = input_validation_check_int("Invalid input. Please input 1 or 11.\n");
      }
      
      playerHand[i].value = input_validation_check_int("Invalid input. Please input 1 or 11.\n");
    }
  }
} */


/* int bank(int win, int bet[ii], int funds[ii])
{
  int i;
  if win == 1
  {
    printf("Players Win! \n");
    for (i = 0; i > player_num, i++)
    {
      bet[ii] = bet[ii]*2;
      funds[ii] = funds[ii] + bet[ii];
      printf("Player %d, your new funds are now %d \n", ii, funds[ii]);
    }
  }

  if win == 2
  {
    printf("House Win! \n");
    for (i = 0; i > player_num, i++)
    {
      funds[ii] = funds[ii] - bet[ii];
      printf("Player %d, your new funds are now %d \n", ii, funds[ii]);
    }
  }

  if win == 3
  {
    for (i = 0; i > player_num, i++)
    {
      return funds[ii];
    }
  }
}
*/
