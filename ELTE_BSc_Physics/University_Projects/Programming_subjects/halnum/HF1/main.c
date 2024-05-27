#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>





// BUBBLE SORT
void bubblesort(float arr[], int arr_len, unsigned long int *iter){ // array, length of array, passing the number of iterations
	
	unsigned long int N_swap = 0; // variable for counting swaps
	float buffer; // buffer variable
	
	for (int i = 0; i < arr_len; i++) // iterate along the array, the N-th iteration places the N-th biggest number to the right position
	{
		for (int j = 0; j < arr_len - i - 1; j++) // iterate to the element at [N-1], the rest of the array is already sorted
		{
			if (arr[j] > arr[j + 1]) // swap elements if they are in incorrect order
			{
				N_swap +=1;
				buffer = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = buffer;
			}
		}
	}
	*iter = N_swap;
}




// SMALLEST ELEMENT
void smallest(float arr[], int arr_len, int *location, float *elem){ // array, length of array, index of the smallest, value of the smallest
	int c;
	int loc = 0;
	for (c = 0; c < arr_len; c++)
		if (arr[c] < arr[loc])
			loc = c;
	*elem = arr[loc];
	*location = loc;
}



// AVERAGE AND STANDARD DEVIATION
void avg_dev(float arr[], int arr_len, float *average, float *deviation){ //
	//int c; // iteration variable
	
	// computing the average
	float s = 0;
	for (int c = 0; c < arr_len; c++)
		s += arr[c];
	float avg = s/arr_len;
	*average = avg;
	
	// computing the deviation
	float k = 0;
	for (int c = 0; c < arr_len; c++)
		k += pow(arr[c]-avg, 2);
	//*szoras = k/n;
	*deviation = pow((k/arr_len),0.5);
}




//QUICKSORT
void quicksort(float arr[],int low,int high){
	int i, j, pivot; // array indeces
	float buffer;
	
	
	if(low < high){
		pivot=low;
		i=low;
		j=high;
	
		while(i<j){

			while(arr[i] <= arr[pivot] && i < high) // iterate i until we find an element greater than the pivot
				i++;
			
			while(arr[j] > arr[pivot]) // iterate j from the back until we find an element smaller than the pivot
				// might want to add && j > low
				j--; 
			

			if(i<j){ // if the greater element is on the left side of the smaller one, we swap them
				buffer = arr[i];
				arr[i] = arr[j];
				arr[j] = buffer;
			}
      		}
      		// at this point :
      		// - everything smaller than the pivot has an index smaller than j
      		// - everything greater than the pivot has an index greater than j
		// *everything inculding the pivot itself
		
		// now we switch the pivot and the greatest element that is smaller than the pivot
		buffer = arr[pivot];
		arr[pivot] = arr[j];
		arr[j] = buffer;
		
		// now the pivot is in the same position as it would be in the sorted array
		// repeat the process with the sub-arrays on the left and right of the pivot
		quicksort(arr,low,j-1);
		quicksort(arr,j+1,high);
	}
	// if low = high, we get an array with a single element, which is trivial
}



// IS AN ELEMENT PART OF AN ARRAY
void partof(float arr[], int arr_len, float elem, bool *is_partof, int *index_partof, int *comparisons){

	bool inside = false;
	int index = -1;
	int iterations = 0;
	
	for (int c = 0; c < arr_len; c++){
		iterations++;
		if(elem==arr[c])
		{
			inside = true;
			index = c;
			break;
		}
	}
	
	
	*is_partof = inside;
	*comparisons = iterations;
	*index_partof = index;
}









////// MAIN FUNCTION //////


int main(int argc, char **args)
{

// PASS THE CHOSEN ELEMENT
	
	float elem = atof(args[3]);
	
	
	
// OPEN FILE
	
	FILE *fptr;
	if ((fptr = fopen(args[1],"r")) == NULL){
		printf("Error! opening file");
		exit(1);
	}
	
	
	
// ALLOCATE MEMORY
	
	int size = atoi(args[2]);
	float main_array[size];
	
	
	
// READ FILE

	int numRead = 0;
	int i = 0;
	while (i!=size){
		
			numRead = fscanf(fptr, "%f\n", &main_array[i]);
			i++;
	}
	
	
	
	
	
// FIND THE SMALLEST ELEMENT
	
	printf("\n------THE SMALLEST ELEMENT------\n");
	int index_smallest;
	float value_smallest;
	smallest(main_array, size, &index_smallest, &value_smallest);
	printf("The index and value of the smallest element is : %d and %f.\n", index_smallest, value_smallest);
	
	
	
// AVERAGE AND DEVIATION
	
	printf("\n------AVERAGE AND DEVIATION------\n");
	float avg, dev;
	avg_dev(main_array, size, &avg, &dev);
	printf("Average : %f\nDevation : %f\n", avg, dev);
	
	
	
	
	
unsigned long int it; // variable for counting iterations
	
	
// BUBBLE SORT
	
	printf("\n------BUBBLE SORT------\n");	
	float bubble_array[size];
	for(int c = 0; c < size; c++){ // copy the main array
		bubble_array[c] = main_array[c];
	}
	
	bubblesort(bubble_array, size, &it);
	printf("The elements of the vector sorted with Bubble Sort:\n");
	
	int N = size;
	if(size > 20){
		N = 20;
		printf("WARNING : The program only prints vectors having less than 20 elements!\n");
	}
	
	for(int c =0; c < N; c++)
			printf("%f\n", bubble_array[c]);

	printf("The number of swaps : %lu\n", it);




// IS THE GIVEN ELEMENT PART OF THE VECTOR
	printf("\n------IS THE GIVEN ELEMENT PART OF THE VECTOR------\n");
	int index_partof, comparisons;
	bool is_partof;
	
	
	printf("\t - WITH THE ORIGINAL VECTOR :\n");
	
	partof(main_array, size, elem, &is_partof, &index_partof, &comparisons);
	
	if(is_partof==false) printf("\t%f is not an element of the vector.\n", elem);
	else printf("\t%f is inside the vector at index %d\n", elem, index_partof);
	printf("\tNumber of comparisons : %d\n", comparisons);
	


	printf("\n\t - WITH THE SORTED VECTOR :\n");
	
	partof(bubble_array, size, elem, &is_partof, &index_partof, &comparisons);
	
	if(is_partof==false) printf("\t%f is not an element of the vector.\n", elem);
	else printf("\t%f is inside the vector at index %d\n", elem, index_partof);
	printf("\tNumber of comparisons : %d\n", comparisons);
	
	

// QUICKSORT

	printf("\n------QUICK SORT------\n");	
	float quick_array[size];
	for(int c = 0; c < size; c++){ // copy the main array
		quick_array[c] = main_array[c];
	}
	
	quicksort(quick_array, 0, size-1);
	printf("The elements of the vector sorted with Quicksort:\n");
	
	
	if(size > 20){
		N = 20;
		printf("WARNING : The program only prints vectors having less than 20 elements!\n");
	}
	
	for(int c = 0; c < N; c++)
			printf("%f\n", quick_array[c]);
	
	
	
	
	return 0;
}
