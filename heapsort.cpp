#include <stdio.h>
#include <stdlib.h>

void max_heapify(int *arr, int num, int heapsize)
{
	int left = num*2 + 1;
	int right = num*2 + 2;
	int largest;
	
	if ( left <= heapsize && arr[left] > arr[num] ) {
		largest = left;
	} else {
		largest = num;
	}
	
	if ( right <= heapsize && arr[right] > arr[largest] ) {
		largest = right;
	}
	
	if ( largest != num ) {
		int temp = arr[largest];
		arr[largest] = arr[num];
		arr[num] = temp;
		max_heapify(arr, largest, heapsize);
	}
}

void buildmaxheap(int *arr, int length)
{
	int i;
	int heapsize = length;
	
	for ( i = length/2 - 1; i >= 0; i-- ) {
		max_heapify(arr, i, heapsize);
	}
}

int main(void)
{
	int n, i, length, heapsize;
	scanf("%d", &n);
	int *arr = (int *)malloc(sizeof(int)*n);
	
	for ( i = 0; i < n; i++ ) {
		scanf("%d", &arr[i]);
	}
	
	length = n-1;
	heapsize = n-1;
	
	buildmaxheap(arr, length);
	
	for ( i = length; i >= 1; i-- ) {
		int temp = arr[0];
		arr[0] = arr[i];
		arr[i] = temp;
		heapsize--;
		max_heapify(arr, 0, heapsize);
	}
	
	for ( i = 0; i < n; i++ ) {
		printf("%d\n", arr[i]);
	}
	
	free(arr);
	return 0;
}
