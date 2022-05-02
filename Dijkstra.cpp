#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 1000
#define Inf 1000000000

typedef struct {
	int index;
	int delta;
}element;

typedef struct {
	element heap[MAX];
	int size;
}Heap;

int g[MAX][MAX];
int is_connect[MAX][MAX] = {0,};
int d[MAX];
int v_length;

void decrease_delta(Heap* h, int idx, int key)
{
	int target;
	for ( int i = 1; i <= h->size; i++ ) {
		if ( h->heap[i].index == idx ) {
			target = i;
			break;
		}
	}
	h->heap[target].delta = key;
	while ( target > 1 && h->heap[target/2].delta > h->heap[target].delta )
	{
		element temp = h->heap[target/2];
		h->heap[target/2] = h->heap[target];
		h->heap[target] = temp;
		target /= 2;
	}
	
}

void Make_Min_Heap(Heap* h, element item)
{
	int i;
	i = ++(h->size);
	
	while ((i != 1) && (item.delta < h->heap[i/2].delta)) {
		h->heap[i] = h->heap[i/2];
		i /= 2;
	}
	
	h->heap[i] = item;
}

element Extract_Min(Heap *h)
{
	int parent, child;
	element item, temp;
	
	item = h->heap[1];
	temp = h->heap[(h->size)--];
	parent = 1;
	child = 2;
	
	while ( child <= h->size ) {
		if ((child < h->size) && ((h->heap[child].delta) > h->heap[child+1].delta)) {
			child++;
		}
		
		if ( temp.delta < h->heap[child].delta ) {
			break;
		}
		
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
				
	}
	
	h->heap[parent] = temp;
	
	return item;
	
}

void Initialize(void)
{
	for ( int i = 1; i <= v_length; i++ ) {
		d[i] = Inf;
	}
	d[1] = 0;
}

void Dijkstra(int start)
{
	Initialize();
	
	Heap min_heap;
	element item;
	for ( int i = 1; i <= v_length; i++ ) {
		item.delta = d[i];
		item.index = i;
		Make_Min_Heap(&min_heap, item);
	}
	
	while ( min_heap.size > 0 ) {
		element min = Extract_Min(&min_heap);
		for ( int j = 1; j <= v_length; j++ ) {
			if (is_connect[min.index][j] == 1 ) {
				if ( d[j] > d[min.index] + g[min.index][j] ) {
					d[j] = d[min.index] + g[min.index][j];
					decrease_delta(&min_heap, j, d[j]);
				}
			}
		}
	}
}

int main(void)
{
	char v[MAX];
	scanf("%s", v);
	v_length = strlen(v) / 2 + 1;
	
	int e;
	scanf("%d", &e);
	
	for ( int i = 0; i < e; i++ ) {
		int n = 0;
		int weight;
		
		char edge[MAX];
		char first;
		char second;
		scanf("%s", edge);
		char* ptr = strtok(edge, ",");
		first = *ptr;
		ptr = strtok(NULL, ",");
		second = *ptr;
		ptr = strtok(NULL, ",");
		weight = atoi(ptr);
		
		g[first-64][second-64] = weight;
		is_connect[first-64][second-64] = 1;
		
	}
	
	Dijkstra(1);
	
	for ( int j = 1; j <= v_length; j++ ) {
		printf("%d\n", d[j]);
	}
	
	return 0;
}
