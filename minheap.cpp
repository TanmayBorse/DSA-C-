/*Get the name,age and address of students who enrolled for admission 
of a certificate course and order them based on their age using bubble sort.*/
#include <iostream>
#include <vector>
#include <string>
using namespace std;


// PRIVATE : heapifyUP | heapifyDown | left        | right   | parent
// PUBLIC  : insert    | print       | extract_min | get_min | sorted array

class MinHeap{

private:

    vector<int>heap;

    // in vector it is start form last index till we reach to root
    void heapifyUp(int index){
        while(index != 0 && heap[index] < heap[parent(index)]){
            swap(heap[index], heap[parent(index)]);
            index = parent(index);
        }
    }

    // in vector it is start form abovec till we reach last level
    void heapifyDown(int index){
        int lc = left(index);
        int rc = right(index);
        int smallest = index;

        if(lc < heap.size() && heap[lc] < heap[smallest]){
            smallest = lc;
        }
        if(rc < heap.size() && heap[rc] < heap[smallest]){
            smallest = rc;
        }

        if(smallest != index){
            swap(heap[index], heap[smallest]);
            heapifyDown(smallest);
        }
    }

    int left(int index){ return (index * 2) + 1;}
    int right(int index){ return (index * 2) + 2;}
    int parent(int index){ return (index - 1) / 2;}

public:

    void insert(int value){
        heap.push_back(value); // insert at last of vector
        heapifyUp(heap.size() -1); // heapify on last index of vector
       }

    void printHeap(){
        if(heap.empty()){
            cout<<"\nempty";
        }
        for(int &v : heap){
            cout<<v<<" ";
        }
    }

    int extractMin(){
        int temp = heap[0];
        heap[0] = heap.back();
        heap.pop_back();

        if(!heap.empty()){
            heapifyDown(0);
        }
        return temp;
    }

    int getMin(){
        return heap[0];
    }

    void sortedArray(){
        vector<int> arr;
        int n = heap.size();
        while(!heap.empty()){
            arr.push_back(heap[0]);
            extractMin();
        }

        for(int &i : arr){
            cout<<i<<" ";
        }
    }
};


int main(){

    MinHeap h;
    h.insert(5);
    h.insert(8);
    h.insert(7);
    h.insert(4);
    h.insert(6);
    h.insert(2);
    h.insert(0);
    h.insert(1);
    h.insert(10);
    h.insert(3);

    h.printHeap();

    cout<<"\nMinimum in heap is "<<h.getMin()<<endl;

    MinHeap dup = h;
    dup.sortedArray();
    cout<<endl;
    h.printHeap();

    return 0;
}