/*
 * drinkMachineDriver.c
 *
 *  Created on: Oct 12, 2016
 *      Author: Jimmy Nguyen
 */
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <stdbool.h>
	#include "drinkmachine.h"

int main(void){

	DrinkMachine *myDrinkMachine;
	myDrinkMachine = create();


	printf("--------------------------------------------------------------\n\n"
			"Welcome to Jimmy's Drink Machine!\n"
			"Feeling thirsty?  Quench that thirst here!\n\n");

	double wallet = 0.00;
	float deposit = 0.00;
	int selection = -1;
	int selectDrink = -1;
	double change = -1.00;

	while(true)
	{
		printf("--------------------------------------------------------------\n"
				"Current Funds: $%.2f\n\n"
				"What would you like to do?\n\n"
				"0 - Quit\n"
				"1 - Deposit Money\n"
				"2 - Eject Money\n"
				"3 - Purchase a Drink\n\n"
				"Please enter the corresponding number.\n", wallet);
		fflush(stdout);
		scanf("%d", &selection);

		switch(selection)
		{
		case QUIT:
			if(wallet != 0)
			{
				printf("Please eject all money before powering down the machine.\n\n");
			}
			else
			{
			printf("\n\n--------------------------------------------------------------\n\n"
					"Thank you for using Jimmy's Drink Machine!\n\n"
					"Written by: Jimmy Nguyen\n"
					"For all questions, email: Jimmy@JimmyWorks.net\n\n"
					"--------------------------------------------------------------\n\n");
			destroy(myDrinkMachine);
			return EXIT_SUCCESS;
			}
			break;
		case DEPOSIT:
			printf("\nLet's put some money in the machine!\n"
					"Enter currency in the following format: 0.00\n\n"
					"(note: this machine only accepts nickels, dimes, quarters, \n"
					"$1 bills, $5 bills, $10 bills and $20 bills)\n"
					"Enter 0 to quit.\n\n");
			fflush(stdout);

			do{
				scanf("%f", &deposit);
				deposit = deposit*100;
				if(deposit == 5  ||
				   deposit == 10  ||
				   deposit == 25  ||
				   deposit == 100  ||
				   deposit == 500  ||
				   deposit == 1000  ||
				   deposit == 2000)
				{
					deposit = deposit/100;
					wallet = wallet + (deposit);
					printf("You have deposited $%.2f into the machine.\n"
						   "Current funds available: $%.2f\n"
						   "Enter '0' to quit.\n\n", deposit, wallet);
				}
				else if(deposit==0)
					printf("Done adding money to the machine.  Back to Main Menu.\n\n");
				else
					printf("Invalid entry.  Make sure you enter each nickel, dime, quarter,\n"
							"$1 bill, $5 bill, $10 bill or $20 bill individually.\n"
							"Enter '0' to quit.\n\n");
				fflush(stdout);
			}while(deposit);
			break;
		case EJECT:
			if(wallet>0)
			{
				printf("\nThe machine returns your remaining funds of $%.2f.\n\n", wallet);
				wallet = 0.00;
			}
			else if(wallet ==0)
				printf("\nYou have no funds to eject.  Please make a deposit!\n\n");
			else
				printf("\nMachine Error.  Please contact technician.\n\n");
			break;
		case MAKE_PURCHASE:
			printf("\nYou have selected to purchase a drink!\n");
			do{
				printf("Which drink would you like to purchase?\n\n");
				dumpDrinkMachine(myDrinkMachine);
				printf("Please enter the drink id for the purchase or 0 to exit.\n\n");
				fflush(stdout);
				scanf("%d", &selectDrink);

				if(!selectDrink)
					printf("Done purchasing drinks.  Returning to Main Menu.\n\n");
				else
				{
				switch(purchase(myDrinkMachine, selectDrink, wallet, &change))
				{
					case INVALID:
						printf("That is not a valid drink id.  Please try again.\n\n");
						break;
					case PURCHASED:
						wallet = change;
						printf("\nYour drink has been purchased!\n\n\n"
								"Your remaining funds are $%.2f.\n", wallet);
						break;
					case NOT_AVAILABLE:
						printf("Sorry, we are out of your selected choice.\n"
						"Please try another selection!\n\n");
						break;
					case INSUFFICIENT_FUNDS:
						printf("You do not have enough funds to make this purchase.\n"
								"This drink costs $%.2f and you have $%.2f available.\n"
								"Please deposit more funds and try again.\n\n", cost(myDrinkMachine,selectDrink), wallet);
						break;
					default: printf("\nFatal Error.  Please contact technician.\n\n");
				}
				}
			}while(selectDrink);
			selectDrink = -1;
			break;
		default:
			printf("\nInvalid selection.  Please try again.\n\n");
		}
	}
	printf("\nFatal Error.  Please contact technician.");
	return EXIT_FAILURE;
}

