#include<iostream>
using namespace std;
struct node{
    int x;
    node *n;
};
/********************************************  INSERT  ********************************************* */
void Ifront(node *&head, int data){

    node *newNode = new node;
    newNode->x = data;
    newNode->n = head;
    head = newNode;    
}

void Iend(node *&head, int data){
    
    node *newNode = new node;
    newNode->x = data;
    newNode->n = NULL;

    if(!head){
        head = newNode;
    }

    node *temp1 = head;

    while(temp1->n){
        temp1 = temp1->n;
    }
    temp1->n = newNode;  
}

void Iposition(node *&head, int position, int data){

    if(position < 0){
        cout<<"invalid position\n";
    }

    node *newNode = new node;
    newNode->x = data;
    newNode->n = NULL;
    
    if(position == 0){
        newNode->n = head;
        head = newNode;
        return;
    }

    node *temp2 = head;

    for(int i = 0 ; temp2 != NULL && i < position-1; ++i){
        temp2 = temp2->n;
    }
    newNode->n = temp2->n;
    temp2->n = newNode;
}
/**************************************************  DELETE   ****************************************************** */

void delF(node *&head){
    if(!head){
        cout<< "list is empth\n";
    }
    node *temp = head;
    head = head->n;
    delete temp;
}

void delE(node *&head){
    if(!head){
        cout<< "list is empth\n";
    }

    if(!head->n){
        delete head;
        head = NULL;
        return;
    }

    node *temp = head;
    while(temp->n && temp->n->n){
        temp = temp->n;
    }
    delete temp->n;
    temp->n = NULL;
}

void delPosition(node *&head, int position){
    if(!head){
        cout<< "list is empth\n";
    }

    if(position < 0){
        cout<<" Invalid Position\n";
    }

    if(position == 0){
        node *temp = head;
        head = head->n;
        delete temp;
        return;
    }

    node *temp = head;
    
    for(int i = 0; i < position-1 && temp->n != NULL; ++i){
        temp = temp->n;
    }

    node *nodeDel = temp->n;
    temp->n = temp->n->n;
    delete nodeDel;      
}

int main(){
    int size = 5;
    int arr[size];

    for(int i = 0; i < size; i++){
        arr[i] = i*i;
    }

    for(int i = 0; i < size; i++){
        cout<<arr[i]<<" ";
    }

    node *head;

    node *temp = new node;

    head = temp;
    
    temp->x = arr[0];
    temp->n = NULL;

    for(int i = 1; i < size; i++){

        node *newNode = new node; //creating new node
        newNode->x = arr[i]; //new node data field value is arrys respective index value
        newNode->n = NULL; //new node pointing to null
        temp->n = newNode; // previous node temp pointing to newnode
        temp = newNode; // new node is now temp
    }
    
    
 // Insert function calling   
    Ifront(head, 20);
    Iend(head, 50);
    Iposition(head, 0, 101);

// Delete fuction calling
    delF(head);
    delE(head);
    delPosition(head, 2);

// Printing the linked list

    temp = head; // temp back again to point first node
    cout<<endl;
    while(temp){
        cout<<temp->x<<" ";
        temp = temp->n;
    }
    
    return 0;
}

