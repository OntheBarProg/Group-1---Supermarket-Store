#include <iostream>

#include <string>

#include <cctype>
using namespace std;

struct Product {

    string name;

    double price;

};

const int MAX_PRODUCTS = 100;

Product products[MAX_PRODUCTS];

int productCount = 0;

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




// Function to Add Product
void addProduct() {
    
    string tempvar;
    
    if (productCount < MAX_PRODUCTS) {
        cout << "Enter product name: ";
        
        cin.ignore();
        getline(cin, tempvar);

        if (!checkletter(tempvar)) { 
            cout << "Not possible\n";  
            return;  
        }
        else{
            products[productCount].name = tempvar;
        }

        cout << "Enter product price: ";
        cin >> products[productCount].price;

        productCount++;

        quickSort(products, 0, productCount - 1);

        cout << "Product added and sorted by price!\n";
    } else {
        cout << "Product list is full!\n";
    }
}

// Function to Update Product Price

void updateProduct() {

    string name;

    cout << "Enter product name to update: ";
    

    cin.ignore();
        getline(cin, name);

        if (!checkletter(name)) { 
            cout << "Not possible\n";  
            return;  
        }


    int index = binarySearch(products, productCount, name);

    if (index != -1) {

        cout << "Enter new price: ";

        cin >> products[index].price;

        quickSort(products, 0, productCount - 1);

        cout << "Product price updated!\n";

    } else {

        cout << "Product not found!\n";

    }

}

// Function to View Products Sorted by Price

void viewProductsbyPrice() {

    quickSort(products, 0, productCount - 1);

    cout << "\n--- Product List (Sorted by Price: High to Low) ---\n";

    for (int i = 0; i < productCount; i++) {

        cout << products[i].name << " - $" << products[i].price << "\n";

    }

}

// Function to View Products Alphabetically

void viewProductsbyAlpha() {

    mergeSort(products, 0, productCount - 1);

    cout << "\n--- Product List (Sorted Alphabetically) ---\n";

    for (int i = 0; i < productCount; i++) {

        cout << products[i].name << " - $" << products[i].price << "\n";

    }

}

// Function to Delete Product

void deleteProduct() {

    string name;

    cout << "Enter product name to delete: ";

     cin.ignore();
        getline(cin, name);

        if (!checkletter(name)) { 
            cout << "Not possible\n";  
            return;  
        }

    int index = binarySearch(products, productCount, name);

    if (index != -1) {

        for (int i = index; i < productCount - 1; i++) {

            products[i] = products[i + 1];

        }

        productCount--;

        quickSort(products, 0, productCount - 1);

        cout << "Product deleted and sorted!\n";

    } else {

        cout << "Product not found!\n";

    }

}

// Function to Search Product

void searchProduct() {

    string name;

    cout << "Enter product name to search: ";

     cin.ignore();
        getline(cin, name);

        if (!checkletter(name)) { 
            cout << "Not possible\n";  
            return;  
        }

    int index = binarySearch(products, productCount, name);

    if (index != -1) {

        cout << "Product found: " << products[index].name << " - $" << products[index].price << "\n";

    } else {

        cout << "Product not found!\n";

    }

}

// Main Menu

void menu() {

    int choice;

    do {

        cout << "\n========= Store Management System =========\n";

        cout << "1. Add New Product\n";

        cout << "2. View Products by Price\n";

        cout << "3. View Products by Alphabetically\n";

        cout << "4. Update Product Details\n";

        cout << "5. Delete Product\n";

        cout << "6. Search Product\n";

        cout << "7. Exit\n";

        cout << "===========================================\n";

        cout << "Enter your choice: ";

        while (!(cin >> choice) || choice < 1 || choice > 7) {

            cin.clear();

            cin.ignore(1000, '\n');

            cout << "Invalid input! Please enter a number between 1 and 7: ";

        }

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

        }

    } while (choice != 7);

}

int main() {

    menu();

    return 0;

}
 