#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

//KNOWN ERRORS: main game loop does not exit properly w/ user input, certain variables are/aren't being reset 

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
  blackjackDeck = fopen("blackjackdeck2.txt", "r");
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
  blackjackDeck = fopen("blackjackdeck2.txt", "w");
  for (i=0; i<104; i++) {
    fprintf(blackjackDeck, lines[i]);
  }
  fclose(blackjackDeck);
}

//HAND VALUE CALCULATION FUNCTION
int hand_value_calculation(Card *hand) {
  int playerHandValue = 0;
  int i = 0;
  
  for (i = 0; i < 10; i++) { //sums all cards
    playerHandValue += hand[i].value;
  }
  
  if (playerHandValue > 21) { //ace function
    for (i=0; i<10; i++) {
      if (strncmp(hand[i].name, "Ace", 3) == 0) {
        hand[i].value = 1;
        
        playerHandValue = 0; //recalculates if ace value is changed
        for (i = 0; i < 10; i++) {
          playerHandValue += hand[i].value;
        }
        break;
      }
    }
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

// FUNDS FUNCTION
void funding(int *funds, int *bet) {
    int choice, moolah;
    
    printf("\n\nYour current funds are: $%d", *funds);
    printf("\nWould you like to add funds?");
    printf("\n  [1] Yes or [2] No\n");
    choice = input_verification_type_int("Invalid Input. [1] Yes or [2] No\n");
     
    while (choice<1 || choice>2) {
      printf("\nInvalid Input. [1] Yes or [2] No\n");
      choice = input_verification_type_int("Invalid Input. [1] Yes or [2] No\n");
    }
    
    if (choice==1) {
      printf("\nHow much would you like to add? ");
      moolah = input_verification_type_int("\nInvalid Input. How much would you like to add? ");
      *funds = *funds + moolah;
      printf("\nYour funds are now: $%d", *funds);
    }
    
    printf("\nHow much would you like to bet on the next hand? ");
    *bet = input_verification_type_int("Invalid Input. How much would you like to bet on the next hand? ");
    
    while (*bet < 0 || *bet > *funds) {
      printf("\nYou can't bet that much!");
      printf("\nHow much would you like to bet on the next hand? ");
      *bet = input_verification_type_int("Invalid Input. How much would you like to bet on the next hand? ");
    }
}


int main() {
  //INT DECLARATIONS  
  int choice, playerHandValue, dealerHandValue, playerIndexPos, dealerIndexPos, exitFlag, i, newCard, wincon=0, funds, bet, playerCardIndex, dealerCardIndex, playAgain=1;
  char line[128];
  srand(time(0));
  
  //DEFINING THE CARD DECK
  Card deck[104];
  Card playerHand[10];
  Card dealerHand[10];
  
  while (playAgain == 1) { //MAIN GAME LOOP
  
    //reads in from file || Note: idk if it would be more efficient to use a deck array or to just read in from file
    deckShuffle();
    deckShuffle();
    FILE *blackjackDeck;
    blackjackDeck = fopen("blackjackdeck2.txt", "r");
    if (blackjackDeck == NULL) {
      printf("Error: Could not open file.\n");
      return 0;
    }
  
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
    
    /*
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
    */
    
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
    
    
    
    //INITIATES USER'S FUNDS
    funds = 0;
    bet = 0;
    funding(&funds, &bet);
  
  
    //POPULATING PLAYER & DEALER HANDS
    for (i = 0; i < 2; i++) {
      newCard = (rand() % 104);
      while (deck[newCard].drawn == 1) {
        newCard = (rand() % 104);
      }
      playerHand[i] = deck[newCard];
    
      newCard = (rand() % 104);
      while (deck[newCard].drawn == 1) {
        newCard = (rand() % 104);
      }
      dealerHand[i] = deck[newCard];
    }
  
    playerIndexPos = 2;
    dealerIndexPos = 2;
  
    //PRINT PLAYER HAND TO TERMINAL
    printf("\n\tCard 1: %s, Value %d\n", playerHand[0].name, playerHand[0].value);
    printf("\tCard 2: %s, Value %d\n", playerHand[1].name, playerHand[1].value);
  
    //PLAYER CHOICE MENU LOOP
    while (exitFlag != 1) {
      if (exitFlag == 1) {
        return 0;
      }
      
      //INSTANT WIN CASE
      if (playerHand[0].value + playerHand[1].value == 21) {
        printf("\nI CAN'T STOP WINNING!!\n");
        wincon = 1;
        break;
      }
      else if (dealerHand[0].value + playerHand[1].value == 21) {
        printf("\nAW DANGIT\n");
        wincon = 2;
        break;
      }
    
      //PLAYER HAND VALUE CALCULATION
      playerHandValue = hand_value_calculation(playerHand);
      printf("\nPlayer Hand Value: %d\n", playerHandValue);
      if (playerHandValue > 21) {
        printf("You busted.\n");
        wincon = 2;
        break;
      }
    
      //PLAYER SELECTION PRINT
      printf("Please select from the following options: Choose (1) to hit, (2) to stand, (3) to split\n");
      choice = input_verification_type_int("Invalid Selection: Choose (1) to hit, (2) to stand, (3) to split\n");
  
      switch (choice) {
        //HIT CASE
        case 1:
          playerIndexPos++;
          playerHand[playerIndexPos] = deck[(rand() % 104)];
          printf("\tCard %d: %s, Value %d\n", playerIndexPos,playerHand[playerIndexPos].name,playerHand[playerIndexPos].value);
          break;
          
        //STAND CASE
        case 2: 
          exitFlag = 1;
          break;
          
        //STAND CASE
        case 3:
          exitFlag = 1; //temporary safety measure
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
    while (dealerHandValue < 17 && wincon == 0) {    
      for (i = 0; i < 10; i++) {
        dealerHandValue += dealerHand[i].value;
        printf("Dealer Hand Value: %d\n", dealerHandValue);
      
        if (dealerHandValue > 21 && playerHandValue < 21) {
          printf("I CAN'T STOP WINNING\n");
          wincon = 1;
          break;
        }
        dealerHand[dealerIndexPos] = deck[(rand() % 104)];
        dealerIndexPos++;
      }
    }
  
    //WIN CONDITIONS
    if (playerHandValue > dealerHandValue && playerHandValue < 21) {
      funds = funds + (2*bet);
      printf("\nI CAN'T STOP WINNING!");
      printf("\nYour winnings: $%d", 2*bet);
      printf("\nYour new funds: $%d", funds);
      wincon = 1;
    }
    else if (playerHandValue < dealerHandValue && dealerHandValue < 21) {
      funds = funds - bet;
      printf("\nAW DANGIT");
      printf("\nYou lost: $%d", bet);
      printf("\nYour new funds: $%d", funds);
      wincon = 2;
    }
    else if (playerHandValue == dealerHandValue && playerHandValue < 21) {
      printf("\nIt's a tie!");
      printf("\nYour new funds: $%d", funds);
      wincon = 3;
    }
    else {
      printf("If you're seeing this, it be brogen.\n");
    }
    
    printf("\nWould you like to play again? [1] to continue, [2] to quit: ");
    playAgain = input_verification_type_int("Invalid Input. [1] to continue, [2] to quit: ");
  
  } //ends main game loop
  return 0;
} //ends main
