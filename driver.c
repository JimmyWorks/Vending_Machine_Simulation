/*
 * driver.c
 *
 *  Created on: Oct 11, 2016
 *      Author: Jimmy Nguyen
 */
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <stdbool.h>
	#include "drinkmachine.h"

//int main(void) {
//	DrinkMachine *firstDrinkMachine;
//	firstDrinkMachine = create();
//
//	for(DrinkItem* pDrink = firstDrink(firstDrinkMachine); pDrink != NULL; pDrink = nextDrink(firstDrinkMachine))
//	{
//		printf("The current drink is drink #%d, '%s', which costs %.2f and %d are left.\n", pDrink->id, pDrink->name, pDrink->price, pDrink->inventory);
//	}
//
//	printf("\nThere are %d different types of drinks in this machine.\n\n", items(firstDrinkMachine));
//
//	bool drinkavail = true; //To test drink available with available inventory the first time
//	while(drinkavail){
//	if(available(firstDrinkMachine, 2)>0) //Will remain true the first time
//	{
//		printf("The second drink is %s and that drink is available\n", firstDrinkMachine->types[1].name);
//		firstDrinkMachine->types[1].inventory = 0; //Change inventory to 0 to test not available
//		printf("To test available function, we set the inventory of %s to %d\n", firstDrinkMachine->types[1].name, firstDrinkMachine->types[1].inventory);
//	}
//	else //Will be false the second time
//	{
//		printf("The second drink is %s and that drink is not available\n", firstDrinkMachine->types[1].name);
//		drinkavail = false;
//	}
//	}
//
//	printf("The price of the 5th drink is %.2f\n\n", cost(firstDrinkMachine, 5));
//
//	double change = -1.00;
//	double payment = -1.00;
//	Purchase transaction = INVALID;
//	int selection = -1;
//	printf("Welcome to mini-purchase program!  How much money do you have?\n\n");
//	fflush(stdout);
//	scanf("%lf", &payment);
//	printf("You have $%.2f\n\n", payment);
//
//	printf("What would you like to purchase? \n");
//  dumpDrinkMachine(firstDrinkMachine);
//	fflush(stdout);
//	scanf("%d", &selection);
//
//	selection--; //corrected to array subscript
//	printf("I have $%.2f and I want to buy a %s.\n", payment, firstDrinkMachine->types[selection].name);
//	transaction = purchase(firstDrinkMachine, firstDrinkMachine->types[selection].id, payment, &change);
//
//	switch(transaction)
//	{
//		case PURCHASED:
//			printf("\nPurchase completed. Your change is $%.2f\n\n", change);
//			break;
//		case NOT_AVAILABLE:
//			printf("\nDrink is not available.\n\n");
//			break;
//		case INSUFFICIENT_FUNDS:
//			printf("\nYou do not have enough money to complete purchase.\n\n");
//			break;
//		case INVALID:
//		default: printf("\nPlease try again.\n\n");
//	}
//
//
//	destroy(firstDrinkMachine);
//
//	return EXIT_SUCCESS;
//}
//

