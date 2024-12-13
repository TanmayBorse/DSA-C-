int getmaxVal(int arr[], int n){
    int maxVal = arr[0];
    for(int i = 1; i < n; i++){
        if(arr[i] > maxVal){
            maxVal = arr[i];
        }
    }
    return maxVal;
}

void printArray(int arr[], int n){
    for(int i = 0; i < n; i++){
        cout<<arr[i]<<" | ";
        if(i > 0 && i % 10 == 0) cout<<endl;
    }
}

void cs(int arr[], int n, int exp){
    vector<int> output(n);
    
    int count[10] = {0};
    
    
    for(int i = 0; i < n; i++){
        count[arr[i] / exp % 10]++;
    }
    
    for(int i =1; i < 10; i++){
        count[i] += count[i-1];
    }
    
    for(int i = n-1; i >=0; i--){
        output[count[(arr[i] / exp % 10)] - 1] = arr[i];
        count[(arr[i] / exp % 10)]--;
    }
    
    for(int i = 0; i < n; i++){
        arr[i] = output[i];
    }
}

void radix(int arr[], int n){
    int maxVal = getmaxVal(arr, n);
    
    for(int exp = 1; maxVal / exp >0; exp *= 10){
        cs(arr, n, exp);
    }
}

int main(){
    
    int arr[] = {170, 45, 75, 90, 802, 24, 2, 66};
    
    int n = sizeof(arr) / sizeof(arr[0]);
    
    cout<<"Input array is :"<< endl;
    printArray(arr, n);
    cout<<endl;
    
    radix(arr, n);
    
    cout<<"Output array is :"<<endl;
    printArray(arr, n);
    cout<<"\n\n";
    
    // for randomly generated 10 intgers
    int randomArr[10];
    for(int i = 0; i < 10; i++){
        randomArr[i] = rand() % 10;
    }
    cout<<"Randomly generated Array with 10 integers array is :"<< endl;
    printArray(randomArr, 10);
    cout<<endl;
    
    radix(randomArr, 10);
    
    cout<<"\nSorted Randomly generated array with 10 intgers array is :"<< endl;
    printArray(randomArr, 10);
    cout<<"\n\n";
    
    
    // for randomly generated 100 intgers
    int randomArr100[100];
    for(int i = 0; i < 100; i++){
        randomArr100[i] = rand() % 100;
    }
    cout<<"Randomly generated Array with 100 integers array is :"<< endl;
    printArray(randomArr100, 100);
    cout<<endl;
    
    radix(randomArr100, 100);
    
    cout<<"\nSorted Randomly generated array with 100 intgers array is :"<< endl;
    printArray(randomArr100, 100);
    cout<<"\n\n";
    
    // for randomly generated 100 intgers
    int randomArr1000[1000];
    for(int i = 0; i < 1000; i++){
        randomArr1000[i] = rand() % 1000;
    }
    cout<<"Randomly generated Array with 1000 integers array is :"<< endl;
    printArray(randomArr1000, 1000);
    cout<<endl;
    
    radix(randomArr1000, 1000);
    
    cout<<"\nSorted Randomly generated array with 1000 intgers array is :"<< endl;
    printArray(randomArr1000, 1000);
    cout<<endl;
}
