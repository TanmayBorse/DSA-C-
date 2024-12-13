#include <iostream>
using namespace std;

struct Node {
    int val;
    Node* left;
    Node* right;

    Node(int k) {
        val = k;
        left = nullptr;
        right = nullptr;
    }
};

class BST {
public:
    Node* root;

    BST() : root(nullptr) {}

    Node* insertNode(Node* node, int val) {
        if (node == nullptr) {
            return new Node(val);
        }

        if (val < node->val) {
            node->left = insertNode(node->left, val);
        } 
        
        else if (val > node->val) {
            node->right = insertNode(node->right, val);
        }

        return node;
    }

    Node* findMin(Node* node) {
        while (node && node->left) {
            node = node->left;
        }
        return node;
    }

    Node* findMax(Node* node) {
        while (node && node->right) {
            node = node->right;
        }
        return node;
    }

    void inorder(Node* node) {
        if (node == nullptr) {
            return;
        }
        inorder(node->left);
        cout << node->val << " ";
        inorder(node->right);
    }

    Node* deleteNode(Node* node, int val) {
        if (node == nullptr) {
            return node;
        }

        if (val < node->val) {
            node->left = deleteNode(node->left, val);
        } 
        
        else if (val > node->val) {
            node->right = deleteNode(node->right, val);
        }
        
        else {
            // Node with one child or no child
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            
            
            else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            // Node with two children
            Node* temp = findMin(node->right);
            node->val = temp->val;
            node->right = deleteNode(node->right, temp->val);
        }
        return node;
    }

    bool search(Node* node, int key) {
        if (node == nullptr) {
            return false;
        }
        if (node->val == key) {
            return true;
        }
        
        else if (key < node->val) {
            return search(node->left, key);
        } else {
            return search(node->right, key);
        }
    }
};

int main() {
    int choice, key;
    BST tree;

    do {
        cout << "\nEnter Choice\n1. Insert\n2. Delete\n3. Search\n4. Find min\n5. Find max\n6. Inorder\n7. Exit\n";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter key to insert: ";
                cin >> key;
                tree.root = tree.insertNode(tree.root, key);
                break;

            case 2:
                cout << "Enter key to delete: ";
                cin >> key;
                tree.root = tree.deleteNode(tree.root, key);
                break;

            case 3:
                cout << "Enter key to search: ";
                cin >> key;
                if (tree.search(tree.root, key)) {
                    cout << "Key found in the BST.\n";
                } else {
                    cout << "Key not found in the BST.\n";
                }
                break;

            case 4:
                if (Node* mini = tree.findMin(tree.root)) {
                    cout << "Minimum is " << mini->val << endl;
                } else {
                    cout << "The BST is empty.\n";
                }
                break;

            case 5:
                if (Node* maxa = tree.findMax(tree.root)) {
                    cout << "Maximum is " << maxa->val << endl;
                } else {
                    cout << "The BST is empty.\n";
                }
                break;

            case 6:
                cout << "In-order traversal: ";
                tree.inorder(tree.root);
                cout << endl;
                break;

            case 7:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice! Please try again.\n";
                break;
        }
    } while (choice != 7);

    return 0;
}
