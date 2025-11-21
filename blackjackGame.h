/*
Blackjack Game Header File
Team: Gambling is Cool
Members: Saya Cottle, Ryan Chatham, Ari Chai
Assignment: CS125 Group Project
File Name: blackjackGame.h
Date: 11/23/2025
*/

#ifndef BLACKJACKGAME_H
#define BLACKJACKGAME_H

//INCLUDES
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

//CARD STRUCT
typedef struct {
  int value;
  char name[20];
  int drawn;
} Card;

//FUNCTION PROTOTYPES
void deckShuffle(void);
int hand_value_calculation(Card *hand);
int input_verification_type_int(char *err_msg);
void funding(int *funds, int *bet);

#endif