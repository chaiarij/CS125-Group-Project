#include "blackjackGame.h"
#include "blackjackFunctions.c"

/*
Blackjack Game
Team: Gambling is Cool
Members: Saya Cottle, Ryan Chatham, Ari Chai
Assignment: CS125 Group Project
File: blackjackGame.c
Date: 11/23/2025
*/


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

int main() {
  //INT DECLARATIONS  
  int choice, playerHandValue, dealerHandValue, playerIndexPos, dealerIndexPos, exitFlag, i, newCard, wincon=0, funds=0, bet=0, playerCardIndex, dealerCardIndex, playAgain=1, winnings;
  char line[128];
  srand(time(0));
  
  //DEFINING THE CARD DECK
  Card deck[104];
  Card playerHand[10];
  Card dealerHand[10];
  
  while (playAgain == 1) { //MAIN GAME LOOP
    playerHandValue=0; //resets values
    dealerHandValue=0;
    exitFlag=0; 
    wincon=0;
    playerIndexPos=2;
    dealerIndexPos=2;
    winnings=0;
    
    for (i=0; i<10; i++) { //empties player's hand
      playerHand[i].value = 0;
      dealerHand[i].value = 0;
    }
  
    //reads in from file
    deckShuffle();
    deckShuffle();
    FILE *blackjackDeck;
    blackjackDeck = fopen("blackjackdeck2.txt", "r");
    if (blackjackDeck == NULL) {
      printf("Error: Could not open file.\n");
      return 0;
    }
  
    i = 0;  
    while (fgets(line, sizeof(line), blackjackDeck) != NULL) {
      if (sscanf(line, " %20[^0-9] %d", deck[i].name, &deck[i].value) == 2) {
        i++; 
      }
    }
    fclose(blackjackDeck);
    
    //sets drawn status to 0
    for (i=0; i<104; i++) {
      deck[i].drawn = 0;
    }
    
    //POPULATING PLAYER & DEALER HANDS
    for (i = 0; i < 2; i++) {  
      while (1) { 
        playerCardIndex = rand() % 104; 
        if (deck[playerCardIndex].drawn == 0) { 
          playerHand[i] = deck[playerCardIndex]; 
          deck[playerCardIndex].drawn = 1; 
          break; 
        }
      }
  
      while (1) { 
        dealerCardIndex = rand() % 104; 
        if (deck[dealerCardIndex].drawn == 0) { 
          dealerHand[i] = deck[dealerCardIndex]; 
          deck[dealerCardIndex].drawn = 1; 
          break; 
        }
      }
    }
    
    //INITIATES USER'S FUNDS
    funding(&funds, &bet);
  
    playerIndexPos = 2;
    dealerIndexPos = 2;
  
    //PRINT PLAYER HAND TO TERMINAL
    printf("\n\tCard 1: %s, Value %d\n", playerHand[0].name, playerHand[0].value);
    printf("\tCard 2: %s, Value %d\n", playerHand[1].name, playerHand[1].value);
    
    //CALCULATES INITIAL PLAYER AND DEALER HAND VALUES
    playerHandValue = hand_value_calculation(playerHand);
    dealerHandValue = hand_value_calculation(dealerHand);
  
    //PLAYER CHOICE MENU LOOP
    while (exitFlag != 1) {
      if (exitFlag == 1) {
        return 0;
      }
      
      //INSTANT WIN CASE
      if (playerHandValue == 21) {
        printf("\nBLACKJACK!!\n");
        wincon = 4;
        break;
      }
      else if (dealerHandValue == 21) {
        printf("\nDealer Blackjack!!\n");
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
    } //end player choice loop
  
  
    //DEALER BEHAVIOR
    dealerHandValue = hand_value_calculation(dealerHand);
    printf("\nDealer Hand Value: %d\n", dealerHandValue);
    while (dealerHandValue < 17 && wincon != 2 && wincon != 4) {    
      
      dealerHand[dealerIndexPos] = deck[(rand() % 104)];
      dealerIndexPos++;
      printf("\nDealer hits to %d...", dealerIndexPos);
      
      dealerHandValue = hand_value_calculation(dealerHand);
      printf("\nDealer Hand Value: %d", dealerHandValue);
      
      if (dealerHandValue > 21) {
        printf("\nDealer busted!\n");
        wincon = 1;
        break;
      }
    }
  
    //WIN CONDITIONS IF NO BUST
    if (playerHandValue > dealerHandValue && playerHandValue <= 21) {
      wincon = 1;
    }
    else if (playerHandValue < dealerHandValue && dealerHandValue <= 21) {
      wincon = 2;
    }
    else if (playerHandValue == dealerHandValue && playerHandValue <= 21) {
      wincon = 3;
    }
    
    //PRINTS RESULTS AND UPDATES FUNDS
    if (wincon==1) {
      winnings = 2*bet;
      funds = funds + winnings;
      printf("\n\nI CAN'T STOP WINNING!");
      printf("\nYour winnings: $%d", winnings);
      printf("\nYour new funds: $%d", funds);
    }
    else if (wincon==2) {
      funds = funds - bet;
      printf("\n\nAW DANGIT");
      printf("\nYou lost: $%d", bet);
      printf("\nYour new funds: $%d", funds);
    }
    else if (wincon==3) {
      printf("\n\nIt's a tie!");
      printf("\nYour new funds: $%d", funds);
    }
    else if (wincon==4) {
      winnings = (5/2*bet);
      funds = funds + winnings;
      printf("\n\nI CAN'T STOP WINNING!");
      printf("\nYour winnings: $%d", winnings);
      printf("\nYour new funds: $%d", funds);
    }
    else {
      printf("\nAn unexpected error has occurred. Please contact the developers.\n\n");
      return 0;
    }
    
    printf("\nWould you like to play again? [1] to continue, [2] to quit: ");
    playAgain = input_verification_type_int("Invalid Input. [1] to continue, [2] to quit: ");
  
  } //ends main game loop
  return 0;
} //ends main
