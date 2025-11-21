/*
Blackjack Game Functions
Team: Gambling is Cool
Members: Saya Cottle, Ryan Chatham, Ari Chai
Assignment: CS125 Group Project
File: blackjackFunctions.c
Date: 11/23/2025
*/

//DECK SHUFFLING FUNCTION - Ari Chai
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

//HAND VALUE CALCULATION FUNCTION - Ryan Chatham, Ari Chai, Saya Cottle
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
  

//INPUT VALIDATION FUNCTION FROM HW5 - Ryan Chatham
int input_verification_type_int(char *err_msg) {
  int input = 0;

  while (1) {
    if (scanf("%d", &input) == 1) {
      return input;
    } 
    else {
      printf("%s\n", err_msg);
      scanf("%*[^\n]");
    }
  }
}

// FUNDS FUNCTION - Ari Chai, Saya Cottle
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
      while (moolah<0) {
        printf("\nStop trying to steal!! >:(");
        printf("\n\nHow much would you like to add? ");
        moolah = input_verification_type_int("\nInvalid Input. How much would you like to add?");
      }
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