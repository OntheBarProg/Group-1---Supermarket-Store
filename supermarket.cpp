#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <iomanip>

using namespace std;

struct Product {

    string name;

    double price;

};

const int MAX_PRODUCTS = 100;

Product products[MAX_PRODUCTS];

int productCount = 0;

// Function to load product data from file

void loadFromFile() {
    ifstream file("MarketDataa.txt");

    if (!file) {
        // File doesn't exist, create an empty file
        ofstream newfile("MarketDataa.txt");
        newfile.close();
        return;
    }

    productCount = 0;
    while (getline(file, products[productCount].name) && file >> products[productCount].price) {
        file.ignore(); // Ignore newline after price to avoid reading issues
        productCount++;

        if (productCount >= MAX_PRODUCTS) break;
    }
    file.close();
}

// Function to save product data to file
void saveToFile() {
    ofstream file("MarketDataa.txt", ios::trunc); 

    if (!file) {
        cout << "Error saving data to file!\n";
        return;
    }

    for (int i = 0; i < productCount; i++) {
        file << products[i].name << endl << products[i].price << endl;
    }

    file.close();
}

// Quick Sort for Sorting by Price (Descending Order)

void quickSort(Product arr[], int low, int high) {

    if (low < high) {

        double pivot = arr[high].price;

        int i = low - 1;

        for (int j = low; j < high; j++) {

            if (arr[j].price > pivot) { // Sorting in descending order

                i++;

                Product temp = arr[i];

                arr[i] = arr[j];

                arr[j] = temp;

            }

        }

        Product temp = arr[i + 1];

        arr[i + 1] = arr[high];

        arr[high] = temp;

        int pi = i + 1;

        quickSort(arr, low, pi - 1);

        quickSort(arr, pi + 1, high);

    }

}


// Merge Sort for Sorting Alphabetically (Case-Insensitive)

void merge(Product arr[], int left, int mid, int right) {

    int n1 = mid - left + 1;

    int n2 = right - mid;

    Product L[n1], R[n2];

    for (int i = 0; i < n1; i++) L[i] = arr[left + i];

    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {

        string leftName = L[i].name, rightName = R[j].name;

        for (int x = 0; x < leftName.length(); x++) leftName[x] = tolower(leftName[x]);

        for (int x = 0; x < rightName.length(); x++) rightName[x] = tolower(rightName[x]);

        if (leftName <= rightName) arr[k++] = L[i++];

        else arr[k++] = R[j++];

    }

    while (i < n1) arr[k++] = L[i++];

    while (j < n2) arr[k++] = R[j++];

}

void mergeSort(Product arr[], int left, int right) {

    if (left < right) {

        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);

        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);

    }

}

// Binary Search for Product Name

int binarySearch(Product arr[], int size, string key) {

    int left = 0, right = size - 1;

    while (left <= right) {

        int mid = left + (right - left) / 2;

        if (arr[mid].name == key) return mid;

        else if (arr[mid].name < key) left = mid + 1;

        else right = mid - 1;

    }

    return -1;

}

//checking for letters

bool checkletter(string name) {
    int size = name.length();

    for (int i = 0; i < size; i++) {
        if (!isalpha(name[i])&& name[i] != ' ') {  
            return false;
        }
    }
    return true;
}

// Checking for existing product name (COMMENT IF NOT NEEDED)

bool equalsIgnoreCase(const string& a, const string& b) {
	
    if (a.length() != b.length()) return false;
    
    for (size_t i = 0; i < a.length(); i++) {
    	
        if (tolower(a[i]) != tolower(b[i])) return false;
    }
    
    return true;
}

//UI STUFF
void printHeader(const string& title) {
	
    cout << "\n+---------------------------------------+" << endl;
    
    cout << "| " << left << setw(37) << title << " |" << endl;
    
    cout << "+---------------------------------------+" << endl;
}

void printMessage(const string& message, bool isError = false) {
	
    string border = isError ? "!!! " : "";
    
    cout << "\n" << border << "+ " << left << setw(36) << message << " +" << border << endl;
    
}


void viewProductsTable() {
	
    cout << "+---------------------------------------+" << endl;
    
    cout << "| " << left << setw(25) << "Product Name" << " | " << setw(10) << "Price" << "|" << endl;
    
    cout << "+---------------------------------------+" << endl;
    
    for (int i = 0; i < productCount; i++) {
    	
        cout << "| " << left << setw(25) << products[i].name 
        
             << " | $" << setw(9) << fixed << setprecision(2) << products[i].price << " |" << endl;
    }
    cout << "+---------------------------------------+" << endl;
}
//UI STUFF


// Function to Add Product
void addProduct() {
    printHeader("ADD NEW PRODUCT");
    
    string tempvar;
    
    if (productCount < MAX_PRODUCTS) {
    	
       
        cout << "| Enter product name: ";
        
        cin.ignore();
        
        getline(cin, tempvar);

        // Check for existing product (case-insensitive)
        bool exists = false;
        
        for (int i = 0; i < productCount; i++) {
        	
            if (equalsIgnoreCase(products[i].name, tempvar)) {
            	
                exists = true;
                
                break;
                
            }
        }
        
        if (exists) {
		// Checking for existing product name (COMMENT IF NOT NEEDED)
        	
            printMessage("Product already exists! Please try again.", true);
            
            return;
        }

        if (!checkletter(tempvar)) { 
        
            printMessage("Invalid characters! Use letters only.", true);
            
            return;  
        }

        products[productCount].name = tempvar;

        cout << "| Enter product price: $";
        
        cin >> products[productCount].price;

        productCount++;
        
        quickSort(products, 0, productCount - 1);
        
        saveToFile();

        printMessage("Product added successfully!");
        
    } else {
    	
        printMessage("Product list is full!", true);
    }
}


// Function to Update Product Price

void updateProduct() {
	
    printHeader("UPDATE PRODUCT");
    
    string name;
    
    cout << "| Enter product name: ";
    
    cin.ignore();
    
    getline(cin, name);

    int index = binarySearch(products, productCount, name);
    
    if (index != -1) {
    	
        cout << "| Current price: $" << products[index].price << endl;
        
        cout << "| Enter new price: $";
        
        cin >> products[index].price;
        
        quickSort(products, 0, productCount - 1);
        
        saveToFile();
        
        printMessage("Price updated successfully!");
        
    } else {
    	
        printMessage("Product not found!", true);
        
    }
}

// Function to View Products Sorted by Price

void viewProductsbyPrice() { // shortened version (made viewProductsbyPrice)
	
    printHeader("PRODUCTS BY PRICE");
    
    quickSort(products, 0, productCount - 1);
    
    viewProductsTable();
}

// Function to View Products Alphabetically

void viewProductsbyAlpha() { // shortened version (made viewProductsbyPrice)
	
    printHeader("PRODUCTS ALPHABETICALLY");
    
    mergeSort(products, 0, productCount - 1);
    
    viewProductsTable();
    
}

// Function to Delete Product

void deleteProduct() {
	
    printHeader("DELETE PRODUCT");
    
    string name;
    
    cout << "| Enter product name: ";
    
    cin.ignore();
    
    getline(cin, name);

    int index = binarySearch(products, productCount, name);
    
    if (index != -1) {
    	
        for (int i = index; i < productCount - 1; i++) {
        	
            products[i] = products[i + 1];
        }
        
        productCount--;
        
        quickSort(products, 0, productCount - 1);
        
        saveToFile();
        
        printMessage("Product deleted successfully!");
        
    } 
	
	else {
    	
        printMessage("Product not found!", true);
        
    }
    
}
// Function to Search Product

void searchProduct() {
	
    printHeader("SEARCH PRODUCT");
    
    string name;
    
    cout << "| Enter product name: ";
    
    cin.ignore();
    
    getline(cin, name);
    

    int index = binarySearch(products, productCount, name);
    
    if (index != -1) {
    	
        cout << "+---------------------------------------+" << endl;
        cout << "| " << left << setw(25) << "Product Name" << " | " << setw(10) << "Price" << " |" << endl;
        cout << "+---------------------------------------+" << endl;
        cout << "| " << left << setw(25) << products[index].name << " | $" << setw(9) << fixed << setprecision(2) << products[index].price << " |" << endl;
        cout << "+---------------------------------------+" << endl;
        
    } 
	else {
		
        printMessage("Product not found!", true);
    }
}
// Main Menu

void menu() {
    string input;
    int choice;

   do {
        cout << "\n+---------------------------------------+" << endl;
        cout << "|         STORE MANAGEMENT SYSTEM       |" << endl;
        cout << "+---------------------------------------+" << endl;
        cout << "| " << left << setw(35) << "1. Add New Product" << "   |" << endl;
        cout << "| " << left << setw(35) << "2. View Products by Price" << "   |" << endl;
        cout << "| " << left << setw(35) << "3. View Products Alphabetically" << "   |" << endl;
        cout << "| " << left << setw(35) << "4. Update Product Details" << "   |" << endl;
        cout << "| " << left << setw(35) << "5. Delete Product" << "   |" << endl;
        cout << "| " << left << setw(35) << "6. Search Product" << "   |" << endl;
        cout << "| " << left << setw(35) << "7. Exit" << "   |" << endl;
        cout << "+---------------------------------------+" << endl;
        cout << "Enter your choice: ";

        cin >> input;

        if (input.length() != 1 || input[0] < '1' || input[0] > '7') {
            cout << "Invalid input! Please enter a number between 1 and 7: ";
            continue;
        }

        choice = input[0] - '0';
        
        switch (choice) {

            case 1: addProduct();

                break;

            case 2: viewProductsbyPrice();

                break;

            case 3: viewProductsbyAlpha();

                break;

            case 4: updateProduct();

                break;

            case 5: deleteProduct();

                break;

            case 6: searchProduct();

                break;

            case 7: cout << "Exiting...\n";

                break;

            default: cout << "Invalid choice! Try again.\n";

                break;

        }

    } while (choice != 7);

}


int main() {
	
	loadFromFile();
	
    menu();

    return 0;

}