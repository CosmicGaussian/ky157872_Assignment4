#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int extraMemoryAllocated;

// Implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void merge(int pData[], int l, int m, int r)
{
    //merge two sorted subarryas into single sorted main array
    int i, j, k;
    int a = m - l + 1;//calculate size of left sub
    int b = r - m;//same but for right
    //need memory for left and right subs
    int* L = (int*)malloc(a * sizeof(int));
    int* R = (int*)malloc(b * sizeof(int));
    //update count of extra mem. Personal:double check this later
    extraMemoryAllocated += a * sizeof(int) + b * sizeof(int);
    //do for loops for copying data from main to the temps
    for (i = 0; i < a; i++)
        L[i] = pData[l + i];
    for (j = 0; j < b; j++)
        R[j] = pData[m + 1 + j];
    //initialize needed indices for the subs
    i = 0;
    j = 0;
    k = l;
    //merge subs into main array sorted
    while (i < a && j < b) {
        if (L[i] <= R[j]) {
            pData[k] = L[i];
            i++;
        }
        else {
            pData[k] = R[j];
            j++;
        }
        k++;
    }
    //copy remaining eles in left and right
    while (i < a) {
        pData[k] = L[i];
        i++;
        k++;
    }

    while (j < b) {
        pData[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

// Implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void mergeSort(int pData[], int l, int r)
{
    //check if there is more than one ele. calc middle index. do recursive calls for left and righ half sorts. merge the sorted halves at the end
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(pData, l, m);
        mergeSort(pData, m + 1, r);
        merge(pData, l, m, r);
    }
}

// Implement insertion sort
// extraMemoryAllocated counts bytes of memory allocated
void insertionSort(int* pData, int n)
{
    //use key like you saw in txtbook, start from second element and think of it as the key. 
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = pData[i];//store current ele to be inserted in sorted
        j = i - 1;

        // Move elements of pData[0..i-1] that are greater than key to one position ahead of their current position
        while (j >= 0 && pData[j] > key) {
            pData[j + 1] = pData[j];
            j--;
        }
        pData[j + 1] = key;
    }
}

// Implement bubble sort
// extraMemoryAllocated counts bytes of extra memory allocated
void bubbleSort(int* pData, int n)
{
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (pData[j] > pData[j + 1]) {
                // Swap elements if they are in the wrong order
                temp = pData[j];
                pData[j] = pData[j + 1];
                pData[j + 1] = temp;
            }
        }
    }
}

// Implement selection sort
// extraMemoryAllocated counts bytes of extra memory allocated
void selectionSort(int* pData, int n)
{
    int i, j, minIndex, temp;
    for (i = 0; i < n - 1; i++) {
        // Find the minimum element in the unsorted portion of the array
        minIndex = i;
        for (j = i + 1; j < n; j++) {
            if (pData[j] < pData[minIndex])
                minIndex = j;
        }

        // Swap the found minimum element with the first element of the unsorted portion
        temp = pData[minIndex];
        pData[minIndex] = pData[i];
        pData[i] = temp;
    }
}

// Parses input file to an integer array
int parseData(char* inputFileName, int** ppData)
{
    FILE* inFile = fopen(inputFileName, "r");
    int dataSz = 0;
    *ppData = NULL;

    if (inFile) {
        fscanf(inFile, "%d\n", &dataSz);
        *ppData = (int*)malloc(sizeof(int) * dataSz);
        // Implement parse data block
        for (int i = 0; i < dataSz; i++)
            fscanf(inFile, "%d", &(*ppData)[i]);
    }

    fclose(inFile); // Close the file after reading

    return dataSz;
}

// Prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
    int i, sz = dataSz - 100;
    printf("\tData:\n\t");
    for (i = 0; i < 100; ++i) {
        printf("%d ", pData[i]);
    }
    printf("\n\t");

    for (i = sz; i < dataSz; ++i) {
        printf("%d ", pData[i]);
    }
    printf("\n\n");
}

int main(void)
{
    clock_t start, end;
    int i;
    double cpu_time_used;
    char* fileNames[] = { "Assgn4input1.txt", "Assgn4input2.txt", "Assgn4input3.txt" };

    for (i = 0; i < 3; ++i) {
        int* pDataSrc, * pDataCopy;
        int dataSz = parseData(fileNames[i], &pDataSrc);

        if (dataSz <= 0)
            continue;

        pDataCopy = (int*)malloc(sizeof(int) * dataSz);

        printf("---------------------------\n");
        printf("Dataset Size : %d\n", dataSz);
        printf("---------------------------\n");

        printf("Selection Sort:\n");
        memcpy(pDataCopy, pDataSrc, dataSz * sizeof(int));
        extraMemoryAllocated = 0;
        start = clock();
        selectionSort(pDataCopy, dataSz);
        end = clock();
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("\truntime\t\t\t: %.1lf\n", cpu_time_used);
        printf("\textra memory allocated\t: %d\n", extraMemoryAllocated);
        printArray(pDataCopy, dataSz);

        printf("Insertion Sort:\n");
        memcpy(pDataCopy, pDataSrc, dataSz * sizeof(int));
        extraMemoryAllocated = 0;
        start = clock();
        insertionSort(pDataCopy, dataSz);
        end = clock();
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("\truntime\t\t\t: %.1lf\n", cpu_time_used);
        printf("\textra memory allocated\t: %d\n", extraMemoryAllocated);
        printArray(pDataCopy, dataSz);

        printf("Bubble Sort:\n");
        memcpy(pDataCopy, pDataSrc, dataSz * sizeof(int));
        extraMemoryAllocated = 0;
        start = clock();
        bubbleSort(pDataCopy, dataSz);
        end = clock();
        cpu_time_used = ((double)(end- start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		free(pDataCopy);
		free(pDataSrc);
	}
	
}