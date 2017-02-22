/*
 ============================================================================
 Name        : drinkmachine.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

//==============PREPOCESSORS==============
//========================================

	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include "drinkmachine.h"
	#include <stdbool.h>

/* "drinkmachine.h" is a header with the following structures:
 * DrinkItem
 * DrinkItem.id (int)
 * DrinkItem.*name (c-style string name read from file)
 * DrinkItem.price (double)
 * DrinkItem.inventory (int)
 * DrinkItem.sold (int)
 *
 * DrinkMachine
 * DrinkMachine.version (int)
 * DrinkMachine.DrinkItemCount (int)
 * DrinkItem.*types (array of DrinkItem structures)
 * DrinkMachine.current (int - current location in array)
 *
 * */

//==Global Constants==

	const int CURRENT_VERSION = 1; //Current version number of drink machine structures
	const int STRING_BUFFER_SIZE = 128; //Temporary Buffer to hold string after reading from the file
	const int INVALID_INDEX = -1;
	const char* INPUT_FILE_NAME = "drink_machine.txt"; //File name

//==============MAIN==============
//================================
//	int main(void) {

//		DrinkMachine *firstDrinkMachine;
//		firstDrinkMachine = create();

//		printf("DEBUG version is %d.\n\n", firstDrinkMachine->version);

//		destroy(firstDrinkMachine);

//		return EXIT_SUCCESS;
//	}



//==============FUNCTIONS==============
//=====================================

	//====Create Drink Machine====
	//============================
	DrinkMachine* create(void)
	{
		DrinkMachine* myMachine;
		myMachine = calloc(1, sizeof(DrinkMachine));

		//Check for NULL returned, i.e. not enough space to allocate to memory
		if(myMachine == NULL){
//			printf("DEBUG: Not enough memory available to create Drink Machine.\n");
			return NULL;
		}

		myMachine->version = CURRENT_VERSION;
		myMachine->currentLocation = INVALID_INDEX;

		FILE* inFile; //File pointer

	//======================Open File, Read==============================
		inFile = fopen(INPUT_FILE_NAME, "r"); //Open file with file pointer and ready to read

		//Check if Successfully Opened to Read
		if(!inFile)
		{
//			printf("DEBUG: Error opening file\n");
			return NULL;
		}
	//=======================Find Number of Drink Types============================
		fscanf(inFile, "%d", &(myMachine->DrinkItemCount));
//		printf("DEBUG readFile int: %d\n", myMachine->DrinkItemCount);

	//====================Create an array of DrinkItem Types=======================
		//(myMachine->types is pointer to first element in array of DrinkItems)
		myMachine->types = calloc(myMachine->DrinkItemCount,sizeof(DrinkItem));
		if (myMachine->types == NULL)
		{
//			printf("DEBUG: Not enough memory available to create array of drinks.\n");
					return NULL;
		}

	//==========Loop to Populate Each Member in each Drink Item====================
		for(int i=0; i < myMachine->DrinkItemCount; i++)
		{
			//==Save the Drink Number==
			myMachine->types[i].id = i+1;

			//==Copy Drink Name into Drink Name Member==
			char tempBuff[STRING_BUFFER_SIZE];
			int stringLength;
			fscanf(inFile, "%s", tempBuff);
			stringLength = strlen(tempBuff);
//			printf("DEBUG scanned in string %d is '%s' and has length %d\n", i, tempBuff, stringLength);
			fflush(stdout);

			//==Dynamically allocate memory for each name==
			myMachine->types[i].name = malloc(stringLength+1);
			if(myMachine->types[i].name == NULL)
			{
//				printf("DEBUG: Not enough memory available to create drink name %d\n", i);
				return NULL;
			}

			//==Copy from the Buffer into the Drink Item name member==
			memcpy(myMachine->types[i].name, tempBuff, stringLength+1);

			//==Scan in the remaining two members from text file: price and inventory==
			fscanf(inFile, "%lf %d", &(myMachine->types[i].price), &(myMachine->types[i].inventory));
			myMachine->types[i].sold = 0;

//			printf("DEBUG Drink Item #%d is %s -- Price: %.2f -- Inventory: %d -- Sold: %d\n\n",
//					myMachine->types[i].id, myMachine->types[i].name, myMachine->types[i].price, myMachine->types[i].inventory, myMachine->types[i].sold);
			fflush(stdout);

		}

		fclose(inFile); //Close the text file
		return myMachine;
	}


	//=====Destroy Drink Items and Machines=====
	//==========================================
	void destroy(DrinkMachine*myMachine)
	{
		//==Check first that the Drink Machine exists==
		if(myMachine == NULL){
			printf("That drink machine does not exist.\n\n");
			return;
		}

		printf("\n\nPowering down and freeing all dynamically allocated memory.\n");
		//Free each name dynamically created
		for(int i=0; i < myMachine->DrinkItemCount; i++)
		{
			printf("DEBUG: Freeing string %d\n", i);
			free(myMachine->types[i].name);
		}

		//Free array of Drink Items
		printf("DEBUG: Freeing Drink Items Array\n");
		free(myMachine->types);

		//Free the Drink Machine itself
		printf("DEBUG: Freeing Drink Machine\n");
		free(myMachine);

		return;
	}

	//==========Find First Drink Item and Set Current Array Location==========
	//========================================================================
	DrinkItem* firstDrink(DrinkMachine* myMachine) //Returns the address of the first drink item
	{
		if(myMachine == NULL)
		{
//			printf("DEBUG: That drink machine does not exist.\n\n");
			return NULL;
		}

		myMachine->currentLocation = 0;

		return &(myMachine->types[0]);

	}

	//===========Find Next Drink Item and Set Current Array Location==========
	//========================================================================
	DrinkItem* nextDrink(DrinkMachine* myMachine) //Returns the address of the next drink item
	{
		if(myMachine == NULL)
		{
//			printf("DEBUG: That drink machine does not exist.\n\n");
			return NULL;
		}

//		printf("DEBUG: Your current location in the drink array is %d\n", myMachine->currentLocation);

		if(myMachine->currentLocation < 0 || myMachine->currentLocation > (myMachine->DrinkItemCount)-1)
		{
			printf("DEBUG: Error: Must go to first drink before cycling items in the drink machine.\n\n");
			return NULL;
		}

		if(myMachine->currentLocation == (myMachine->DrinkItemCount)-1)
		{
			myMachine->currentLocation = INVALID_INDEX;
//			printf("DEBUG: You have reached the end of the list.\n");
			return NULL;
		}
		else
			(myMachine->currentLocation)++;

//		printf("DEBUG: My location now is %d\n\n", myMachine->currentLocation);

		return &(myMachine->types[myMachine->currentLocation]);
	}

	//==========Find Number of Unique Drink Items==========
	//=========================================================
	int items(DrinkMachine* myMachine) //Returns how many different unique drinks are in the machine
	{
		if(myMachine == NULL)
		{
//			printf("DEBUG: That drink machine does not exist.\n\n");
			return -1;
		}

		return myMachine->DrinkItemCount;
	}

	//==========Check for Availability of Drink==========
	//===================================================
	bool available(DrinkMachine* myMachine, int drinkID) //Returns if the current item selected is available for purchase
	{
		drinkID--; //Sets drink id equal to array index

		if(myMachine == NULL)
		{
//			printf("DEBUG: That drink machine does not exist.\n\n");
			return NULL;
		}
		if(drinkID < 0 || drinkID > (myMachine->DrinkItemCount)-1)
		{
//			printf("DEBUG: That drink ID does not exist.\n\n");
			return NULL;
		}

		if (myMachine->types[drinkID].inventory > 0)
			return true;

		else
			return false;

	}

	//==========Check for Cost of Drink==================
	//===================================================
	double cost(DrinkMachine* myMachine, int drinkID) //Returns the cost of the current item
	{
		drinkID--; //Sets drink id equal to array index

		if(myMachine == NULL)
		{
//			printf("DEBUG: That drink machine does not exist.\n\n");
			return -1.00;
		}
		if(drinkID < 0 || drinkID > (myMachine->DrinkItemCount)-1)
		{
//			printf("DEBUG: That drink ID does not exist.\n\n");
			return -1.00;
		}

		return myMachine->types[drinkID].price;
	}

	//==========Function for Making a Purchase===========
	//===================================================
	Purchase purchase(DrinkMachine* myMachine, int drinkID, double payment, double* change) //Purchase function returning change and enumerated status of transaction
	{
		drinkID--; //Sets drink id equal to array index

		if(myMachine == NULL)
		{
//			printf("DEBUG: That drink machine does not exist.\n\n");
			return INVALID;
		}
		if(drinkID < 0 || drinkID > (myMachine->DrinkItemCount)-1)
		{
//			printf("DEBUG: That drink ID does not exist.\n\n");
			return INVALID;
		}
		if(payment < 0)
		{
//			printf("DEBUG: Currency amount must be a positive value.\n\n");
			return INVALID;
		}

		//There is the case where the drink is not available (payment does not matter)
		if(myMachine->types[drinkID].inventory < 1)
		{
//			printf("DEBUG: %s is not available.\n\n", myMachine->types[drinkID].name);
			return NOT_AVAILABLE;
		}
		else{
			//There is the case where there is a drink to sell and the payment is sufficient
			if(payment > myMachine->types[drinkID].price)
			{
				//Return change, deduct inventory, increment sales
				*change = payment - myMachine->types[drinkID].price;
//				printf("DEBUG: My change is $%.2f.\n", *change);
				myMachine->types[drinkID].inventory--;
//				printf("DEBUG: %s now has %d remaining for purchase.\n\n", myMachine->types[drinkID].name, myMachine->types[drinkID].inventory);
				myMachine->types[drinkID].sold++;
//				printf("DEBUG: There are now %d sold drinks.\n\n", myMachine->types[drinkID].sold);

				return PURCHASED;
			}
			else
			{
				return INSUFFICIENT_FUNDS;
			}

		}

	}


	//==========Function for Making a Purchase===========
	//===================================================
	void dumpDrinkMachine(DrinkMachine* myMachine) //Displays contents of the drinks in the drink machine
	{
		if(myMachine == NULL)
		{
			printf("DEBUG: That drink machine does not exist.\n\n");
			return;
		}

		printf("    Id             Name    Price   Qty  Sold\n");
		for(int i=0; i < myMachine->DrinkItemCount; i++)
		{
			printf("%6d %16s %8.2f %5d %5d\n",
					myMachine->types[i].id,
					myMachine->types[i].name,
					myMachine->types[i].price,
					myMachine->types[i].inventory,
					myMachine->types[i].sold);
		}
		printf("\n\n");
		return;
	}
