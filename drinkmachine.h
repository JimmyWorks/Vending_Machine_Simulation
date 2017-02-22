
	#include <stdbool.h>

/*==Structures==*/

	typedef struct _DrinkItem
	{
		int id;
		char *name;
		double price;
		int inventory;
		int sold;
	} DrinkItem;

	typedef struct _DrinkMachine
	{
		int version;
		int DrinkItemCount;
		DrinkItem *types;
		int currentLocation;
	} DrinkMachine;

	typedef enum _Purchase
	{
		PURCHASED,
        INVALID,
        NOT_AVAILABLE,
        INSUFFICIENT_FUNDS
	} Purchase;

	typedef enum _UserChoices
	{
		QUIT,
		DEPOSIT,
		EJECT,
		MAKE_PURCHASE
	} UserChoices;


/*==Function Prototypes==*/

	DrinkMachine* create(void); //Dynamically create DrinkMachine Structure
	void destroy(DrinkMachine*); // Free all allocated memory in create function
    DrinkItem* firstDrink(DrinkMachine*); //Returns the address of the first drink item
    DrinkItem* nextDrink(DrinkMachine*); //Returns the address of the next drink item
    int items(DrinkMachine*); //Returns how many drink items are in the machine
    bool available(DrinkMachine*, int); //Returns if the current item selected is available for purchase
    double cost(DrinkMachine*, int); //Returns the cost of the current item
    Purchase purchase(DrinkMachine*, int, double, double*); //Purchase function returning change and enumerated status of transaction
    void dumpDrinkMachine(DrinkMachine*); //Displays contents of the drinks in the drink machine
