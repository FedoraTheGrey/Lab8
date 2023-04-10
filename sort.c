#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int extraMemoryAllocated;

void * memcpy ( void * destination, const void * source, size_t num );

// typedef struct tree_node{
// 	int data;
// 	struct tree_node *left, *right;
// }tree_node;

// struct tree_node* create_node(int val){

// 	tree_node *temp;
// 	temp = (tree_node*)malloc(sizeof(tree_node));

// 	temp->data = val;

// 	return temp;

// }

// tree_node* insert(tree_node* root, tree_node* new){
// 	if(root == NULL){
// 		return new;
// 	}
// 	if(root->data > new->data){
// 		if(root->right != NULL){
// 			root->right = insert(root->right, new);
// 		}
// 		else{
// 			root->right = new;
// 		}
// 	}
// 	if(root->data < new->data){
// 		if(root->left != NULL){
// 			root->left = insert(root->left, new);
// 		}
// 		else{
// 			root->left = new;
// 		}
// 	}
// 	return root;
// }

// void heapify(tree_node* root){
// 	int temp;
// 	if(root->left != NULL){
// 		heapify(root->left);
// 	}
// 	if(root->data < root->left->data){
// 			temp = root->data;
// 			root->data = root->left->data;
// 			root->left->data = temp;
// 	}
// 	if(root->right != NULL){
// 		heapify(root->right);	
// 	}
// 	if(root->data < root->right->data){
// 			temp = root->data;
// 			root->data = root->right->data;
// 			root->right->data = temp;
// 	}
// }

void swap(int* a, int* b){
	int temp = *a;
	*a = *b;
	*b = temp;
}

void heapify(int arr[], int N, int i){
	int largest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;

	// if(left < N && arr[right] > arr[largest]){
	// 	largest = right;
	// }

	// if(left < N && arr[left] > arr[largest]){
	// 	largest = left;
	// }

	// if(largest != i){
	// 	heapify(arr, N, largest);
	// 	int temp = arr[i];
	// 	arr[i] = arr[largest];
	// 	arr[largest] = temp;
	// }
	if(left < N + 1){
		heapify(arr, N, left);
	}
	if(right < N + 1){
		heapify(arr, N, right);
	}
	if(left < N + 1 && arr[i] < arr[left]){
		int temp = arr[i];
		arr[i] = arr[left];
		arr[left] = temp;
	}
	if(right < N + 1 && arr[i] < arr[right]){
		int temp = arr[i];
		arr[i] = arr[right];
		arr[right] = temp;
	}

}

// implements heap sort
// extraMemoryAllocated counts bytes of memory allocated
void heapSort(int arr[], int n)
{



	for(int i = n - 1; i >= 0; i--){
		heapify(arr, i, 0);
		int temp = arr[i];
		arr[i] = arr[0];
		arr[0] = temp;

	}

	


}

void merge(int pData[], int l, int m, int r){
	
	int a = m - l + 1, b = r - m;
	int A[a], B[b], i, j, k;
	for(i = 0; i < a; i++){
		A[i] = pData[l + i];
	}
	for(j = 0; j < b; j++){
		B[j] = pData[m + j];
	}

	

	i = 0;
	j = 0;
	k = l;	
	while(i < a && j < b){
		if(A[i] <= B[j]){
			pData[k] = A[i];
			i++;
		}
		else{
			pData[k] = B[j];
			j++;
		}
		k++;
	}
	while(i < a){
		pData[k++] = A[i++];
	}
	while(j < b){
		pData[k++] = A[j++];
	}
}


// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void mergeSort(int pData[], int l, int r)
{
	int m = 1 + (l + r)/2;

	if(r > l){
		mergeSort(pData, l, m - 1);
		mergeSort(pData, m, r);
	}
	merge(pData, m, l, r);
}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
	int i, n, *data;
	*ppData = NULL;
	
	if (inFile)
	{
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)malloc(sizeof(int) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i=0;i<dataSz;++i)
		{
			fscanf(inFile, "%d ",&n);
			data = *ppData + i;
			*data = n;
		}

		fclose(inFile);
	}
	
	return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
	if(dataSz > 200){
		int i, sz = dataSz - 100;
		printf("\tData:\n\t");
		for (i=0;i<100;++i)
		{
			printf("%d ",pData[i]);
		}
		printf("\n\t");
		
		for (i=sz;i<dataSz;++i)
		{
			printf("%d ",pData[i]);
		}
		printf("\n\n");
	}
	else{
		printf("\tData:\n\t");
		for (int i = 0;i < dataSz; ++i)
		{
			printf("%d ",pData[i]);
		}
		printf("\n\t");
		
	}
}

int main(void)
{
	clock_t start, end;
	int i;
    double cpu_time_used;
	char* fileNames[] = { "input1.txt", "input2.txt", "input3.txt", "input4.txt" };
	
	for (i=0;i<4;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");
		
		printf("Heap Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		heapSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		free(pDataCopy);
		free(pDataSrc);
	}
	
}