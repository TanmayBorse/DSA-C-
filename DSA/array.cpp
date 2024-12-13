#include <iostream>
using namespace std;

void insert(int arr[], int& size, int pos, int value) {
    if (pos < 0 || pos > size) {
        cout << "Invalid position!" << endl;
        return;
    }
    for (int i = size; i > pos; --i) {
        arr[i] = arr[i - 1];
    }
    arr[pos] = value;
    ++size;
    cout << "Element inserted!" << endl;
}

void remove(int arr[], int& size, int pos) {
    if (pos < 0 || pos >= size) {
        cout << "Invalid position!" << endl;
        return;
    }
    for (int i = pos; i < size - 1; ++i) {
        arr[i] = arr[i + 1];
    }
    --size;
    cout << "Element removed!" << endl;
}

void travel(int arr[], int size) {
    if (size == 0) {
        cout << "Array is empty!" << endl;
        return;
    }
    cout << "Array elements: ";
    for (int i = 0; i < size; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int linearSearch(int arr[], int size, int value) {
    for (int i = 0; i < size; ++i) {
        if (arr[i] == value) {
            return i;
        }
    }
    return -1; // Element not found
}

void update(int arr[], int size, int pos, int value) {
    if (pos >= 0 && pos < size) {
        arr[pos] = value;
        cout << "Element updated!" << endl;
    } else {
        cout << "Invalid position!" << endl;
    }
}

int main() {
    const int MAX_SIZE = 100;
    int arr[MAX_SIZE];
    int size = 0;
    int choice, pos, value;

    do {
        // Display the menu
        cout << "\nMenu:\n";
        cout << "1. Insert\n";
        cout << "2. Delete\n";
        cout << "3. Traverse\n";
        cout << "4. Search\n";
        cout << "5. Update\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                // Insert operation
                cout << "Enter position to insert: ";
                cin >> pos;
                cout << "Enter value to insert: ";
                cin >> value;
                insert(arr, size, pos, value);
                break;
            
            case 2:
                // Delete operation
                cout << "Enter position to delete: ";
                cin >> pos;
                remove(arr, size, pos);
                break;
            
            case 3:
                // Traverse operation
                travel(arr, size);
                break;

            case 4:
                // Search operation
                cout << "Enter value to search: ";
                cin >> value;
                pos = linearSearch(arr, size, value);
                if (pos != -1) {
                    cout << "Element found at position " << pos << endl;
                } else {
                    cout << "Element not found!" << endl;
                }
                break;

            case 5:
                // Update operation
                cout << "Enter position to update: ";
                cin >> pos;
                cout << "Enter new value: ";
                cin >> value;
                update(arr, size, pos, value);
                break;

            case 6:
                // Exit
                cout << "Exiting..." << endl;
                break;

            default:
                cout << "Invalid choice! Please try again." << endl;
                break;
        }

    } while (choice != 6);

    return 0;
}
