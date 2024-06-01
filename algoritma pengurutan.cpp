#include <iostream>
#include <chrono>
#include <algorithm> 
#include <cstdlib> 
using namespace std;
using namespace std::chrono;

// Fungsi Bubble Sort
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

// Fungsi Insertion Sort
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// Fungsi Selection Sort
void selectionSort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        int min_idx = i;
        for (int j = i+1; j < n; j++) {
            if (arr[j] < arr[min_idx])
                min_idx = j;
        }
        int temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}

// Fungsi Merge Sort
void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// Fungsi Quick Sort
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Fungsi untuk mengukur waktu eksekusi
void measureTime(void (*sortFunc)(int[], int), int arr[], int n) {
    auto start = high_resolution_clock::now();
    sortFunc(arr, n);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken: " << duration.count() << " microseconds" << endl;
}

// Fungsi utama
int main() {
    int sizes[] = {10, 100, 500, 1000, 10000};
    for (int size : sizes) {
        int *arr = new int[size];
        

        // Kondisi data: acak, terurut terbalik, dan sudah terurut
        cout << "Array size: " << size << endl;
        for (const string& condition : {"Random", "Reverse Sorted", "Sorted"}) {
            cout << "Condition: " << condition << endl;

            // Generate data sesuai kondisi
            int *tempArr = new int[size];
            copy(arr, arr + size, tempArr);

            if (condition == "Reverse Sorted") {
                sort(tempArr, tempArr + size, greater<int>());
            } else if (condition == "Sorted") {
                sort(tempArr, tempArr + size);
            }

            int *arrBubble = new int[size];
            int *arrInsertion = new int[size];
            int *arrSelection = new int[size];
            int *arrMerge = new int[size];
            int *arrQuick = new int[size];

            copy(tempArr, tempArr + size, arrBubble);
            copy(tempArr, tempArr + size, arrInsertion);
            copy(tempArr, tempArr + size, arrSelection);
            copy(tempArr, tempArr + size, arrMerge);
            copy(tempArr, tempArr + size, arrQuick);

            cout << "Bubble Sort: ";
            measureTime(bubbleSort, arrBubble, size);

            cout << "Insertion Sort: ";
            measureTime(insertionSort, arrInsertion, size);

            cout << "Selection Sort: ";
            measureTime(selectionSort, arrSelection, size);

            cout << "Merge Sort: ";
            measureTime([](int arr[], int n) { mergeSort(arr, 0, n-1); }, arrMerge, size);

            cout << "Quick Sort: ";
            measureTime([](int arr[], int n) { quickSort(arr, 0, n-1); }, arrQuick, size);
            cout << endl;

            delete[] arrBubble;
            delete[] arrInsertion;
            delete[] arrSelection;
            delete[] arrMerge;
            delete[] arrQuick;
            delete[] tempArr;
        }
        delete[] arr;
        cout << "-------------------------" << endl;
    }
    return 0;
}
