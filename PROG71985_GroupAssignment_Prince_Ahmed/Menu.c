#define _CRT_SECURE_NO_WARNINGS
#include "Menu.h"
#include <stdio.h>
#include <string.h>

void displayLogo() {

	int backslash = 92;

	printf("                 .##########.\n"
		"      ########/###          ###/########\n"
		"   ###(       #,              .#       (###\n"
		"  ##.                                     ##		__________________   __________________\n"
		" (##                                      ###      .-/|                  %c /                  |%c-.\n"
		"  ##                                      ##       ||||                   |                   ||||\n"
		"   ##                                    ##.       ||||                   |                   ||||\n"
		"     ###(                            /###.         ||||                   |       ~~*~~       ||||\n"
		"     ##(                            /##            ||||    --==*==--      |                   ||||\n"
		"     ##(                            /##            ||||                   |                   ||||\n"
		"     ##(                            /##            ||||     Recipe        |                   ||||\n"
		"     ##################################            ||||     Manager       |     --==*==--     ||||\n"
		"     #############/####################            ||||                   |                   ||||\n"
		"      ##########...........##########              ||||    By: Nick  &    |                   ||||\n"
		"     ######...  0 ....... 0 ....######             ||||        Islam      |                   ||||\n"
		"     ##.............................##             ||||                   |                   ||||\n"
		"     %c##...##..................##...##             ||||__________________ | __________________||||\n"
		"      ##..,# #...##########..# #*..##              ||/===================%c|/===================%c||\n"
		"        ###.,# ######  ###### #*.###               `--------------------~___~-------------------''\n"
		"           ####               ####\n"
		"              .##############,\n\n", backslash, backslash, backslash, backslash, backslash);

	printf("---------------------------------------------------------------------------------------------------------\n\n");

	
}

void displayAccountFunctions() {

	printf("Welcome to the recipe manager, please select one of the options:\n\n"
		"a) Login to your account\n"
		"b) Create an account\n"
		"c) exit\n");
		
}

void getAccountOption(USER* userArray) {

	char* userOption;
	bool validOption = false;

	do {

		char* userOption = getMenuInput();
		
		switch (*userOption) {
		case 'A':
			validOption = true;
			getLoginFromUser(userArray);
			break;

		case 'B':
			validOption = true;
			createAccount();
			break;

		case 'C':
			validOption = true;
			exit(EXIT_SUCCESS);
			break;

		default:
			printf("Please enter a valid option: ");
			validOption = false;
			break;
		}

		free(userOption);

	} while (!validOption);

}

void displayRecipeFunctions() {
	
	printf("\nRecipe functions:\n\n");
	printf("a) Display a single recipe\n"
			"b) Display a range of recipes\n"
			"c) Display all recipes\n"
			"\n"
			"d) Create a new recipe\n"
			"e) Edit an exisiting recipe\n"
			"f) Delete an exisiting recipe\n"
			"\n"
			"g) Search for an existing recipe\n"
			"h) Sort existing recipes (????????)\n"
			"\n"
			"i) Quit\n\n");
	printf("Choose a function: ");

}

bool getRecipeMenuOption(PRLIST recipeList) {

	char* userOption = getMenuInput();
	bool yesNo = true;
	int recipeOption = 1;
	switch (*userOption) {
	case 'A':
		displayRecipeList(recipeList);
		printf("\nPlease select a recipe ID: ");
		recipeOption = getRecipeIDInput();

		if (!displayRecipe(recipeList, recipeOption)) {
			printf("\nThis recipe doesn't exist\n");
		}

		free(userOption);
		return true;

	case 'B':
		displayRecipeList(recipeList);
		printf("\nPlease select the first recipe ID: ");
		int recipeOption1 = getRecipeIDInput();
		printf("Please select the second recipe ID: ");
		int recipeOption2 = getRecipeIDInput();

		for (recipeOption1; recipeOption1 <= recipeOption2; recipeOption1++) {
			if (!displayRecipe(recipeList, recipeOption1)) {
				break;
			}
		}

		free(userOption);
		return true;

	case 'C':
		do {
			if (!displayRecipe(recipeList, recipeOption)) {
				break;
			}
			recipeOption++;
		} while (true);

		free(userOption);
		return true;

	case 'D':
		printf("\nPlease name your recipe: ");
		char* userRecipeName = getUserInput();
		int userRecipeID = getLastRecipeID(recipeList) + 1;
		RECIPE userRecipe = createRecipe(userRecipeName, userRecipeID);
		addRecipeToList(recipeList, userRecipe);
		
		yesNo = true;
		int id = 1;
		printf("\nIngredients:\n");
		do {
			INGREDIENT userIngredient = getIngredientInput(id);
			addIngredientToList(getIngredientList(getRecipeFromRecipeList(recipeList, userRecipeID + 1)), userIngredient);
			yesNo = yesNoAddIngredient();
			id++;
		} while (yesNo);

		writeRecipeList(recipeList);
		free(userOption);
		return true;

	case 'E':
		displayRecipeList(recipeList);
		printf("\nPlease select an ID to edit a recipe: ");
		recipeOption = getRecipeIDInput();
		yesNo = true;

		if (!displayRecipe(recipeList, recipeOption)) {
			printf("\nThis recipe doesn't exist\n");
		} else {

			do {
				printf("\nWould you like to add (1) or edit (2) an ingredient in the recipe? ");
				int addEditOption = getRecipeIDInput();

				if (addEditOption == 1) {
					//get last id
					int lastIngredientID = getLastIngredientID(getIngredientList(getRecipeFromRecipeList(recipeList, recipeOption)));
					INGREDIENT userIngredient = getIngredientInput(lastIngredientID + 1);
					addIngredientToList(getIngredientList(getRecipeFromRecipeList(recipeList, recipeOption)), userIngredient);
					
					yesNo = yesNoAddEditIngredient();

				} else if (addEditOption == 2) {
					printf("\nPlease select an ID to edit an ingredient: ");
					int ingredientOption = getRecipeIDInput();
					PINGREDIENT selectedIngredient = getIngredientFromIngredientList(getIngredientList(getRecipeFromRecipeList(recipeList, recipeOption)), ingredientOption); 
					INGREDIENT userIngredient = getIngredientInput(ingredientOption);
					memcpy(selectedIngredient, &userIngredient, sizeof(INGREDIENT));
					yesNo = yesNoAddEditIngredient();

				} else {
					printf("\nYour Input Was Invalid\n");
				}
			} while (yesNo);
		}

		writeRecipeList(recipeList);
		free(userOption);
		return true;

	case 'F':
		displayRecipeList(recipeList);
		printf("\nPlease select an ID to delete a recipe: ");
		recipeOption = getRecipeIDInput();

		if (checkRecipeExists(recipeList, recipeOption)) {
			deleteRecipeTextFile(recipeList, recipeOption);
			removeRecipeFromList(recipeList, recipeOption);
			writeRecipeList(recipeList);
		} else {
			printf("\nThis recipe doesn't exist\n");
		}
		free(userOption);
		return true;

	case 'G':
		free(userOption);
		return true;

	case 'H':
		free(userOption);
		return true;

	case 'I':
		free(userOption);
		return false;

	default:
		printf("Please enter a valid option: ");
		free(userOption);
		getRecipeMenuOption(recipeList);
	}
}

void displayRecipeList(PRLIST recipeList) {

	printf("\nRecipe list: \n\n");
	getRecipeListFromADT(recipeList);

}
