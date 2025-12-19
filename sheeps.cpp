#include <iostream>
#include <ctime>
#include <cmath>
#include <cstdlib> 
#include <algorithm>

using namespace std;

int* kClosestValues(int key, int k, int* herd, int size, int left, int right){
    int* result = new int[k];
    for (int i = 0; i < k; i++){
        if (left < 0){
            result[i] = herd[right];
            right++;
        }
        else if(right >= size){
            result[i] = herd[left];
            left--;
        }
        else if(key - herd[left] <= herd[right] - key){
            result[i] = herd[left];
            left--;
        }
        else{
            result[i] = herd[right];
            right++;
        }
    }
    return result;
}

int* linearSearch(int key, int k, int* herd, int begin, int end, int size){
    int left, right;
    if (herd[begin] > key){
        left = begin - 1;
        right = begin;
    }
    else if(herd[end] < key){
        left = end;
        right = end + 1;
    }
    else{
        for (int i = begin; i < end; i++){
            if(herd[i] <= key && herd[i+1]>key){
                if(herd[i] == key){
                    int* result = new int[1] ;
                    result[0] = i ;
                    return result;
                }
                else{
                    left = i;
                    right = i + 1;
                }
            }
        }
    }
    return kClosestValues(key, k, herd, size, left, right);
}

int* binarySearch( int* herd, int k, int size, int key ){
    int left, right;
    if (herd[0] > key){
            left = -1;
            right = 0;
        }
    else if(herd[size-1] < key){
        left = size - 1;
        right = size;
    }
    else{
        int low = 1, high = size - 2;
        while ( low <= high ) {
            int mid = (low + high) / 2;
            if ( herd[ mid ] < key ){
                if(herd[mid + 1] > key){
                    left = mid;
                    right = mid + 1;
                    break;
                }
                else{
                    low = mid + 1; 
                }  
            }
            else if ( herd[ mid ] > key ){
                if ( herd[mid-1] < key){
                    left = mid -1;
                    right = mid;
                    break;
                }
                else{
                    high = mid - 1; 
                }
            }
            else {
                int* result = new int[1];
                result[0] = mid;
                return result;
            }
        } 
    }
    return kClosestValues(key, k, herd, size, left, right);
}   

int* jumpSearch(int* herd, int k, int size, int key){
    int step, prev;
    if (herd[0] > key){
            prev = -1;
            step = 0;
        }
    else if(herd[size-1] < key){
        prev = size - 1;
        step = size;
    }
    else{
        int n = sqrt(size);
        step = n;
        prev = 0;
        while (herd[step] < key){
            prev = step;
            if(step + n >= size){
                step = size -1;
                break;
            }
            step += n;
        }   
    }
    return linearSearch(key, k, herd, prev, step, size);
}

int main(){
    srand(time(0));

    for(int p = 3; p < 13; p++){
        int N = pow(2, p);
        int* herd = new int[N];

        for(int i = 0; i < N; i++){
            herd[i] = rand() % (10 * N + 1);
        }
        std::sort(herd, herd + N);

        int key;
        bool found;
        do{
            key = rand() % (10 * N + 1);
            found = false;
            for(int i = 0; i < N; i++){
                if(herd[i] == key){
                    found = true;
                    break;
                }
            }
        }
        while(found) ;

        int kValues[4] = {1, N/8, N/4, N/2};

        for(int i = 0; i < 4; i++){
            int K = kValues[i];

            clock_t start = clock();
            int* linear;
            for (int i = 0; i < 100000; i++){
                linear = linearSearch(key, K, herd, 0, N-1, N);
                delete[] linear;
            }
            clock_t end = clock();
            double duration = 1000.0 * double(end - start) / (CLOCKS_PER_SEC * 100000);
            cout << "Linear Search N=" << N << " K=" << K << " Key=" << key << " Time(ms)= " << duration << endl;
            
            
            start = clock();
            int* binary;
            for (int i = 0; i < 100000; i++){
                binary = binarySearch(herd, K, N, key);
                delete[] binary;
            }
            end = clock();
            duration = 1000.0 * double(end - start) / (CLOCKS_PER_SEC * 100000);
            cout << "Binary Search N=" << N << " K=" << K << " Key=" << key << " Time(ms)= " << duration << endl;
            

            start = clock();
            int* jump;
            for (int i = 0; i < 100000; i++){
                jump = jumpSearch(herd, K, N, key);
                delete[] jump;
            }
            end = clock();
            duration = 1000.0 * double(end - start) / (CLOCKS_PER_SEC * 100000);
            cout << "Jump Search N=" << N << " K=" << K << " Key=" << key << " Time(ms)= " << duration << endl;
            
        }

        delete[] herd;
    }
    return 0;
}