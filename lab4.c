#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void bubblesort(int*  arr, int n){
	for (int i = 0; i<n-1; i++){
		int swapped = 0;
		for (int j=0; j<n-i-1; j++){
			if (arr[j]>arr[j + 1]){
				int temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
				swapped = 1;
			}
		}
		if (!swapped) break;
	}
}

void insertsort(int* arr, int n){
	for (int i=1; i<n; i++){
		int key = arr[i];
		int j = i-1;
		while (j>=0 && arr[j]>key){
			arr[j+1] = arr[j];
			j--;
		}
		arr[j+1] = key;
	}
}

void merge(int* arr, int left, int mid, int right){
	int n1 = mid - left + 1;
	int n2 = right - mid;
	
	int* L = (int*)malloc(n1 * sizeof(int));
	int* R = (int*)malloc(n2 * sizeof(int));
	
	for (int i = 0; i<n1; i++){
		L[i] <= arr[left + i];
	}
	for ( int j = 0; j< n2; j++){
		R[j] = arr[mid + 1 + j];
	}
	int i =0, j=0, k=left;
	while (i < n1 && j < n2){
		if (L[i] <= R[j]){
			arr[k++] = L[i++];
		} else {
			arr[k++] = R[j++];
		}
	}
	while (i < n1){
		arr[k++] = L[i++];
	}
	while (j < n2){
		arr[k++] = R[j++];
	}
	free(L);
	free(R);
}

void mergesort(int* arr, int left, int right) {
	if (left<right){
		int mid = left + (right - left)/2;
		mergesort(arr, left,mid);
		mergesort(arr, mid+1, right);
		merge(arr, left, mid, right);
	}
}

void copyarray(int* source, int* dest, int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = source[i];
    }
}

int main(){
	srand(time(NULL));
	int sizes[] = {10,1000, 10000, 100000};
	int num_sizes = 4;
	printf("| Размер     | Пузырьком (сек) | Вставками (сек) | Слиянием (сек)  |\n");

	for (int s = 0; s < num_sizes; s++) {
		int n = sizes[s];
		int* base_arr=(int*)malloc(n * sizeof(int));
		int* test_arr=(int*)malloc(n * sizeof(int));

		for (int i = 0; i < n; i++){
			base_arr[i] = rand();
		}
		clock_t start, end;
		copyarray(base_arr,test_arr,n);
		start = clock();
		bubblesort(test_arr, n);
		end = clock();
		double time_bubble = (double)(end-start) / CLOCKS_PER_SEC;

		copyarray(base_arr, test_arr, n);
		start = clock();
		insertsort(test_arr, n);
		end = clock();
		double time_insertion = (double)(end - start) / CLOCKS_PER_SEC;

		copyarray(base_arr, test_arr, n);
		start = clock();
		mergesort(test_arr, 0, n - 1);
		end = clock();
		double time_merge = (double)(end - start) / CLOCKS_PER_SEC;
		
		printf("| %-10d \t| %-15.6f \t| %-15.6f \t| %-15.6f |\n", n, time_bubble, time_insertion, time_merge);
		free(base_arr);
		free(test_arr);
	}
	return 0;
}
