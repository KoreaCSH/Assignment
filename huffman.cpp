#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int N;

typedef struct Node{
	int weight;
	struct Node* left_child;
	struct Node* right_child;
}Node;

typedef struct {
	Node* ptree;
	int key;
}element;

typedef struct {
	element heap[1000]; 
	int heap_size;
}Heaptype;

void Insert(Heaptype* h, element item)
{
	int i = ++(h->heap_size);
	
	while( i != 1 && item.key < h->heap[i/2].key ) {
		h->heap[i] = h->heap[i/2];
		i /= 2;
	}
	h->heap[i] = item;
}

element Extract_Min(Heaptype *h)
{
	int parent = 1, child = 2;
	element min, temp;
	
	min = h->heap[1];
	temp = h->heap[h->heap_size];
	h->heap_size -= 1;
	
	while ( child <= h->heap_size ) {
		if ((child < h->heap_size) && (h->heap[child].key) > h->heap[child+1].key) {
			child++;
		}
		
		if(temp.key <= h->heap[child].key) {
			break;
		}
		
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	
	h->heap[parent] = temp;
	return min;
}

Node* make_tree(Node* left, Node* right)
{
	Node* z = (Node*)malloc(sizeof(Node));
	z->left_child = left;
	z->right_child = right;
	return z;
}

void destroy_tree(Node *root)
{
	if ( root == NULL ) {
		return;
	}
	destroy_tree(root->left_child);
	destroy_tree(root->right_child);
	free(root);
}

void print_tree(Node* z, int n, int k, char* code)
{
	if(z) {
		n++;
		code[n] = '0';
		print_tree(z->left_child, n, k, code);
		code[n] = '1';
		print_tree(z->right_child, n, k, code);
		code[n] = '\0';
		
		if( (z->left_child == NULL && z->right_child == NULL) && z->weight == k ) {
			printf("%s\n", code);
		}
	}
}

void Huffman(int freq[])
{
	int i;
	Node *z, *x;
	element e, e1, e2;
	Heaptype heap;
	char* code = (char*)malloc(sizeof(char));
	
	heap.heap_size = 0;
	
	for ( i = 0; i < N; i++ ) {
		z = make_tree(NULL, NULL);
		e.key = z->weight = freq[i];
		e.ptree = z;
		Insert(&heap, e);
	}
	
	for ( i = 0 ; i < N-1; i++ ) {
		e1 = Extract_Min(&heap);
		e2 = Extract_Min(&heap);
		
		x = make_tree(e1.ptree, e2.ptree);
		
		e.key = x->weight = e1.key + e2.key;
		e.ptree = x;
		Insert(&heap, e);
	}
	
	// 완성된 트리 
	e = Extract_Min(&heap);
	
	for( i = 0; i < N; i++ ) {
		print_tree(e.ptree, -1, freq[i], code);	
	}
	destroy_tree(e.ptree);
}

int main(void)
{
	int i;
	scanf("%d", &N);
	
	int freq[N];
	
	for ( i = 0; i < N; i++ ) {
		scanf("%d", &freq[i]);
	}
	
	Huffman(freq);
	
	return 0;
}
