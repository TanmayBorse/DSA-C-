/*
(a) Logical Fixes: Fixed the array initialization error.
(b) Singly Linked List: Created a linked list to store the generated random numbers.
(c) Adding Seed: The seed value is added both at the beginning and end of the linked list.
(d) Find and Delete Maximum: We find the maximum value in the list and delete the corresponding node.
*/

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

struct Node {
    int data;
    Node* next;
};

int countDigits(int num) {
    int count = 0;
    while (num > 0) {
        num /= 10;
        count++;
    }
    return count;
}

// Mid-square method to generate random numbers
int midSquare(int seed, int digits) {
    int square = seed * seed;
    int totalDigits = countDigits(square);

    // Find the middle digits
    int start = (totalDigits / 2) - (digits / 2);
    int divisor = pow(10, start);
    square /= divisor;
    int newSeed = square % static_cast<int>(pow(10, digits));

    return newSeed;
}

// Function to insert a node at the end of the list
void insertEnd(Node*& head, int value) {
    Node* newNode = new Node();
    newNode->data = value;
    newNode->next = nullptr;

    if (head == nullptr) {
        head = newNode;
    } else {
        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// Function to traverse and print the linked list
void traverse(Node* head) {
    Node* temp = head;
    while (temp) {
        cout << temp->data << " -> ";
        temp = temp->next;
    }
    cout << "NULL" << endl;
}

void insertBeginning(Node*& head, int value) {
    Node* newNode = new Node();
    newNode->data = value;
    newNode->next = head;
    head = newNode;
}

// Function to find the maximum value in the linked list
int findMax(Node* head) {
    if (head == nullptr) return -1; // Empty list
    
    int maxVal = head->data;
    Node* temp = head->next;
    while (temp != nullptr) {
        if (temp->data > maxVal) {
            maxVal = temp->data;
        }
        temp = temp->next;
    }
    return maxVal;
}

// Function to delete a node with a specific value
void deleteNode(Node*& head, int value) {
    if (head == nullptr) return;

    // If the node to be deleted is the head node
    if (head->data == value) {
        Node* temp = head;
        head = head->next;
        delete temp;
        return;
    }

    Node* current = head;
    Node* previous = nullptr;

    // Search for the node to delete
    while (current != nullptr && current->data != value) {
        previous = current;
        current = current->next;
    }

    if (current == nullptr) return; // Value not found

    // Unlink the node and delete it
    previous->next = current->next;
    delete current;
}

int main() {
    int seed, n, digits;

    // Input from the user
    cout << "Enter the initial seed (positive integer): ";
    cin >> seed;
    cout << "Enter the number of random numbers to generate: ";
    cin >> n;
    cout << "Enter the number of digits for the generated numbers: ";
    cin >> digits;

    // Declare array after knowing 'n'
    int rno[n];
    
    Node* head = nullptr;

    // Generate random numbers and store in linked list
    for (int i = 0; i < n; i++) {
        seed = midSquare(seed, digits);
        insertEnd(head, seed);
    }

    // Add seed number at the beginning and end of the list
    insertBeginning(head, seed);
    insertEnd(head, seed);

    // Output the linked list
    cout << "Random numbers in the linked list:" << endl;
    traverse(head);

    // Find and delete the maximum value
    int maxVal = findMax(head);
    cout << "Maximum value found: " << maxVal << endl;
    deleteNode(head, maxVal);

    // Output the updated linked list
    cout << "Linked list after deleting the maximum value:" << endl;
    traverse(head);

    return 0;
}
