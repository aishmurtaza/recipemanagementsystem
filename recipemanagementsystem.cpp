#include <iostream>
#include <string>
#include <iomanip> // For std::setw
#include <fstream> // For file handling
#include <cstdlib> 
using namespace std;

const int MAX_RECIPES = 100;
const int MAX_INGREDIENTS = 10;

// Structure for recipes
struct Recipe {
    string name;
    string category;
    string ingredients[MAX_INGREDIENTS];
    int ingredientCount;
};

// Class for managing recipe display functions
class DisplayFunctions {
public:
    void displayAvailableRecipes(const Recipe recipes[], int recipeCount) 
	{
		
    cout << "Available Recipes:" << endl;
    cout << setw(20) << left << "Name" << setw(20) << left << "Category" << "Ingredients" << endl;// used setw for setting width of display table
    cout << setfill('-') << setw(60) << "-" << setfill(' ') << endl;
    
    for (int i = 0; i < recipeCount; ++i) {
    cout << setw(20) << left << recipes[i].name;
    cout << setw(20) << left << recipes[i].category;
    for (int j = 0; j < recipes[i].ingredientCount; ++j) {
    cout << recipes[i].ingredients[j];
    if (j < recipes[i].ingredientCount - 1) cout << ", "; }// print space after every ingredient after checking if not last
    cout << endl;
        }
    }
};

// Class for adding new recipes
class AddRecipe {
public:
    void addRecipe(Recipe recipes[], int& recipeCount, const Recipe& newRecipe) {
    if (recipeCount < MAX_RECIPES) {
    recipes[recipeCount++] = newRecipe;
    cout << "Recipe added successfully!" << endl;}
    else {
     cout << "Cannot add more recipes. Recipe limit reached." << endl;}
    }
};

// Class for searching recipes
class SearchRecipe {
public:
void searchRecipe(const Recipe recipes[], int recipeCount, const string& searchTerm) {
bool found = false;
    cout << "Search Results:" << endl;
    for (int i = 0; i < recipeCount; ++i) {
     if (recipes[i].name.find(searchTerm) != string::npos ||
    recipes[i].category.find(searchTerm) != string::npos) {
    cout << "Name: " << recipes[i].name << endl;
    cout << "Category: " << recipes[i].category << endl;
    cout << "Ingredients: ";
    for (int j = 0; j < recipes[i].ingredientCount; ++j) {
    cout << recipes[i].ingredients[j];
    if (j < recipes[i].ingredientCount - 1) cout << ", ";}       
     cout << endl << endl;
    found = true;}}
        if (!found) {
    cout << "No matching recipes found." << endl;
        }
    }
};
// Class for deleting recipes
class DeleteRecipe {
public:
    void deleteRecipe(Recipe recipes[], int& recipeCount, const string& recipeToDelete) {
     for (int i = 0; i < recipeCount; ++i) {
     if (recipes[i].name == recipeToDelete) {
     for (int j = i; j < recipeCount - 1; ++j) {
   recipes[j] = recipes[j + 1];
          }
     --recipeCount;
     cout << "Recipe deleted successfully!" << endl;}
   }
        cout << "Recipe not found!" << endl;}
};

// file handling class
class FileHandler {
public:	
void saveRecipesToFile(const Recipe recipes[], int recipeCount, const string& filename) {
ofstream file(filename, ios::app); 
if (file.is_open()) {
 // Write recipes to the file
file<<"name"<<"\t"<<"category"<<"\t"<<"ingredients"<<endl;
 for (int i = 0; i < recipeCount; ++i) {
file << recipes[i].name << "\t" << recipes[i].category << "\t\t";
for (int j = 0; j < recipes[i].ingredientCount; ++j) {
file << recipes[i].ingredients[j];
 if (j < recipes[i].ingredientCount - 1)
 file << ", ";}       
file << endl;}
 file.close();
cout << "Recipes added  to the  " << filename << " successfully!" << endl;}
else {
cout << "Unable to open file " << filename << " for writing." << endl;
}
  }
};

int main() {
	
Recipe recipes[MAX_RECIPES];
int recipeCount = 0;
DisplayFunctions display;
AddRecipe add;
SearchRecipe search;
DeleteRecipe del;
FileHandler fileHandler;

char opt;

do {
int choice;
string recipeName;
string recipeCategory;
string searchTerm;

        cout << "\t\t\tRecipe Management System" << endl;
        cout << "1. Display available recipes" << endl;
        cout << "2. Add a new recipe" << endl;
        cout << "3. Search for a recipe" << endl;
        cout << "4. Delete a recipe" << endl;
        cout << "5. Save to file" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        	
       case 1:
     display.displayAvailableRecipes(recipes, recipeCount);
        break;
        
        case 2:char option;
   do {
cout << "Enter the name of the recipe to add: ";
cin >> recipeName;
cout << "Enter the category of the recipe: ";
cin >> recipeCategory;
                
      Recipe newRecipe;
      newRecipe.name = recipeName;
      newRecipe.category = recipeCategory;
      newRecipe.ingredientCount = 0; 
cout << "Enter ingredients (enter 'done' or 'DONE' to finish): ";
while (cin >> recipeName) {
if (recipeName == "done" || recipeName == "DONE" || newRecipe.ingredientCount >= MAX_INGREDIENTS) {
         break;}
                    
newRecipe.ingredients[newRecipe.ingredientCount++] = recipeName;}
add.addRecipe(recipes, recipeCount, newRecipe);

cout << "Want to add more recipes? (y/n): ";
cin >> option;
   } while (option == 'y' || option == 'Y');
         break;
        
        case 3:
        do {
        	
        cout << "Enter search term by name or category: ";
        cin >> searchTerm;
        search.searchRecipe(recipes, recipeCount, searchTerm);
        cout << "Want to Search more recipes? (y/n): ";
cin >> option;
   } while (option == 'y' || option == 'Y');
         break;
    
        case 4:
        do {
        	
        cout << "Enter the name of the recipe to delete: ";
        cin >> recipeName;
        del.deleteRecipe(recipes, recipeCount, recipeName);
        cout << "Want to delete more recipes? (y/n): ";
cin >> option;
   } while (option == 'y' || option == 'Y');
         break;
       
        case 5:
          {
        string filename;
        cout << "Enter the filename to save recipes: ";
          cin >> filename;
         fileHandler.saveRecipesToFile(recipes, recipeCount, filename);
          }
        break;
                
        case 6:
        cout << "Exiting Application " << endl;
         default:
          cout << "Invalid choice. Please try again." << endl;
        }
        
        cout << "\nwant to perform more tasks?(y/n)";
        cin >> opt;
        
        system("cls");
    } while (opt == 'y' || opt == 'Y');

    cout << "\t\t\t\tHOPE YOU LIKED THE SERVICE:)" << endl;

}
