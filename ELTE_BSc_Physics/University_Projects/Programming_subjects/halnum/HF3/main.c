#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>



//  matrix dimensions from arguments
/*int col1 = atoi(args[2]);
int row1 = atoi(args[3]);
int col2 = atoi(args[5]);
int row2 = atoi(args[6]);*/




//READING A FILE INTO A 1D ARRAY
void fileToArray(char filename[], int col, int row, unsigned short *arr){ // filename, columns, rows, destiantion array
	
	printf("Reading file %s...\n", filename);
	FILE *fptr;
	char str[4*col];
	
	if( (fptr = fopen(filename, "r")) == NULL){
		printf("\tError opening file %s!\n", filename);
		exit(1);
	}
	fptr = fopen(filename, "r");
	
	int index = 0;
	while(1){
		if( fgets(str, col*row, fptr) == NULL ) break;
		
		char* token = strtok(str, " "); // get the first token and store string pointer (internal state)
		while(token != NULL){ // if the token is terminated with NULL value, we reached the end of the string
			arr[index] = (unsigned short)( atoi(token) );
			token = strtok(NULL, " "); // NULL tells strtok() to continue with the string (internal state) until the token is terminated by the delimeter
			index++;
		}
	}
	
	fclose(fptr);
	printf("\tFile %s has been read.\n", filename);
	
}





// PRINTING 1D ARRAY AS A MATRIX
void printMatrix(unsigned short *arr, int col, int row){

	if(col <= 20){
		for(int i = 0; i < row; i++){
			for(int j = 0; j < col; j++){
				printf(" %u ", arr[i * col+j]);
			}
			printf("\n");
		}
	}
	else printf("Matrix too wide to display!\n");
}




//CORRELATION - shiftless, assuming same number of columns
// this function exists because the assignment requires it
// correlationShiftless() is a more general implementation
float correlationSimpleShiftless(unsigned short *arr1, int size1, unsigned short *arr2, int size2){
	
	float x1_sum = 0.0, x2_sum = 0.0, x1_sqsum = 0.0, x2_sqsum = 0.0, xy_sum = 0.0;
	
	// calculate the sums
	for(int i = 0; i < size1; i++){
		x1_sum += (float)( arr1[i] );
		x1_sqsum += (float)( pow(arr1[i], 2) );
		
		xy_sum += ( float)(arr1[i]*arr2[i] ); // we only consider the mutual elements
	}
	for(int j = 0; j < size2; j++){
		x2_sum += (float)( arr2[j] );
		x2_sqsum += (float)( pow(arr2[j], 2) );
	}
	
	// average of (x_i)
	float x1_avg = (float)( x1_sum/size1 );
	float x2_avg = (float)( x2_sum/size2 );
	
	
	// average of (x_i)^2
	float x1_sqavg = (float)( x1_sqsum/size1 );
	float x2_sqavg = (float)( x2_sqsum/size2 );
	
	
	// average of (x1_i*x2_i), which is (x_i*y_i) in the .pdf
	float xy_avg = xy_sum/size1; // size1 because we only consider the mutual elements
	
	// return the formula in the .pdf
	return (float)( (xy_avg - x1_avg*x2_avg) / sqrt( (x1_sqavg - x1_avg*x1_avg) * (x2_sqavg - x2_avg*x2_avg) ) );
}




//CORRELATION - shiftless, assuming different number of columns
// this function exists because the assignment requires it
// correlation() is a more general implementation
float correlationShiftless(unsigned short *arr1, int row1, int col1, unsigned short *arr2, int row2, int col2){
	
	
	int size1 = col1 * row1;
	int size2 = col2 * row2;
	
	float x1_sum = 0.0, x2_sum = 0.0, x1_sqsum = 0.0, x2_sqsum = 0.0, xy_sum = 0.0;
	
	
	
	// 2 indeces of the matrix : [(int)floor(i/col1), i-(int)floor(i/col1)*col]
	// after finishing a row in arr1 : we have to skip the rest of the row in arr2 if arr2 has more columns
	// there are (col2-col1) number of columns left in the row of arr2, this difference accumulates
	// the number of skipped line-ends is (int)floor(i/col1)
	int arr2_index_add;
	
	for(int i = 0; i < size1; i++){
		
		x1_sum   += (float)( arr1[i] );
		x1_sqsum += (float)( pow(arr1[i], 2) );
		
		arr2_index_add = (col2-col1)*(int)floor(i/col1); // explained above
		
		x2_sum   += (float)( arr2[i + arr2_index_add] );
		x2_sqsum += (float)( pow(arr2[i + arr2_index_add], 2) );
		
		xy_sum += (float)( arr1[i] * arr2[i + arr2_index_add] );
	}
	
	
	// average of (x_i)
	float x1_avg = (float)( x1_sum/size1 );
	float x2_avg = (float)( x2_sum/size2 );
	
	
	// average of (x_i)^2
	float x1_sqavg = (float)( x1_sqsum/size1 );
	float x2_sqavg = (float)( x2_sqsum/size2 );
	
	
	// average of (x1_i*x2_i), which is (x_i*y_i) in the .pdf
	float xy_avg = xy_sum/size1; // size1 because we only consider the mutual elements
	
	
	// return the formula in the .pdf
	return (float)( (xy_avg - x1_avg*x2_avg) / sqrt( (x1_sqavg - x1_avg*x1_avg) * (x2_sqavg - x2_avg*x2_avg) ) );
}




//CORRELATION - with a given shift (pos), assuming different number of columns
// this is the most general function
float correlation(unsigned short *arr1, int row1, int col1, unsigned short *arr2, int row2, int col2, int pos){
	
	int size1 = col1 * row1;
	int size2 = col2 * row2;
	
	float x1_sum = 0.0, x2_sum = 0.0, x1_sqsum = 0.0, x2_sqsum = 0.0, xy_sum = 0.0;
	
	int arr2_index_add;
	
	for(int i = 0; i < size1; i++){
		
		x1_sum   += (float)( arr1[i] );
		x1_sqsum += (float)( pow(arr1[i], 2) );
		
		// Note : pos is a pixel index in the bigger picture's 1D array
		// the rest is explained in detail at correlationShiftless()
		arr2_index_add = (col2-col1)*(int)floor(i/col1) + pos;
		
		x2_sum   += (float)( arr2[i + arr2_index_add] );
		x2_sqsum += (float)( pow(arr2[i + arr2_index_add], 2) );
		
		xy_sum += (float)( arr1[i] * arr2[i + arr2_index_add] );
	}
	
	
	// average of (x_i)
	float x1_avg = (float)( x1_sum/size1 );
	float x2_avg = (float)( x2_sum/size1 );
	
	
	// average of (x_i)^2
	float x1_sqavg = (float)( x1_sqsum/size1 );
	float x2_sqavg = (float)( x2_sqsum/size1 );
	
	
	// average of (x1_i*x2_i), which is (x_i*y_i) in the .pdf
	float xy_avg = xy_sum/size1; // size1 because we only consider the mutual elements
	
	
	// return the formula in the .pdf
	return (float)( (xy_avg - x1_avg*x2_avg) / sqrt( (x1_sqavg - x1_avg*x1_avg) * (x2_sqavg - x2_avg*x2_avg) ) );
}






//int main(int argc, char **args){
int main(){

	
// PART (A)
// - mainly serves to test functions
// - this runs independently from the given arguments
// - testing on : "smiley10x11.dat", "sad10x11.dat", "tree10x11.dat"
	
	printf("\n-----PART (A)-----\n\n");
	printf("TESTING : reading from file\n");
	
	
// allocating memory
	
	int col_smiley = 10, col_sad = 10, col_tree = 10;
	int row_smiley = 11, row_sad = 11, row_tree = 11;
	unsigned short *arr_smiley	= (unsigned short*) malloc(sizeof(unsigned short)* col_smiley	* row_smiley	);
	unsigned short *arr_sad		= (unsigned short*) malloc(sizeof(unsigned short)* col_sad	* row_sad	);
	unsigned short *arr_tree	= (unsigned short*) malloc(sizeof(unsigned short)* col_tree	* row_tree	);
	
	
// reading files

	fileToArray("data/smiley10x11.dat",	col_smiley,	row_smiley,	arr_smiley);
	fileToArray("data/sad10x11.dat",	col_sad,	row_sad,	arr_sad);
	fileToArray("data/tree10x11.dat",	col_tree,	row_tree,	arr_tree);
	
// printing matrices
	
	printf("TESTING : printing matrix\n");
	
	printf("\'smiley10x11.dat\' shown as a matrix: \n");
	printMatrix(arr_smiley,	col_smiley,	row_smiley);
	
	printf("\'sad10x11.dat\' shown as a matrix: \n");
	printMatrix(arr_sad,		col_sad,	row_sad);
	
	printf("\'tree10x11.dat\' shown as a matrix: \n");
	printMatrix(arr_tree,		col_tree,	row_tree);
	
	printf("SUCCESS!\n\n");	
	







// PART (B)
// - mainly serves to test functions
// - this runs independently from the given arguments
// - testing on : "smiley10x11.dat", "sad10x11.dat", "tree10x11.dat"
	 
	printf("\n-----PART (B)-----\n\n");
	printf("TESTING : calculating correlation\n");
	printf("**DISPLAY FORMAT** \t|| file1 | file2 ||\t correlation \n\n");	
	
// calculating correlation
	
	printf("|| smiley10x11.dat | smiley10x11.dat ||");
	printf( "\t%.8f\n", correlationSimpleShiftless(arr_smiley, col_smiley * row_smiley ,	arr_smiley, col_smiley * row_smiley) );
	
	printf("|| smiley10x11.dat | sad10x11.dat ||");
	printf( "\t%.8f\n", correlationSimpleShiftless(arr_smiley, col_smiley * row_smiley ,	arr_sad, col_sad * row_sad) );
	
	printf("|| smiley10x11.dat | tree10x11.dat ||");
	printf( "\t%.8f\n", correlationSimpleShiftless(arr_smiley, col_smiley * row_smiley ,	arr_tree, col_tree * row_tree) );
	
	
// PART (C)
// - mainly serves to test functions
// - this runs independently from the given arguments
// - testing on : "smiley10x11.dat", "sad10x11.dat", "tree10x11.dat", "smileybig24x19.dat"
	
	printf("\n-----PART (C)-----\n\n");
	printf("TESTING : calculating correlation for different sized arrays\n");
	
	int col_smileybig = 24;
	int row_smileybig = 19;
	unsigned short *arr_smileybig = (unsigned short*)malloc( sizeof(unsigned short)*col_smileybig*row_smileybig );
	
	fileToArray("data/smileybig24x19.dat",col_smileybig, row_smileybig, arr_smileybig);
	printMatrix(arr_smileybig, col_smileybig, row_smileybig);
	
	printf("**FORMAT** \t|| file1 | file2 ||\t number \n\n");	
	
	
	printf("|| sad10x11.dat | smileybig24x19.dat ||");
	printf("\t%.8f\n", correlationShiftless(arr_sad, row_sad, col_sad, arr_smileybig, row_smileybig, col_smileybig));
	printf("|| sad10x11.dat | smiley10x11.dat ||");
	printf("\t%.8f\n", correlationShiftless(arr_sad, row_sad, col_sad, arr_smiley, row_smiley ,col_smiley));
	
	
	
// PART (D)
// - mainly serves to test functions
// - this runs independently from the given arguments
// - testing on : "smiley10x11.dat", "sad10x11.dat", "tree10x11.dat", "smileybig24x19.dat"
	
	printf("\n-----PART (D)-----\n\n");
	printf("TESTING : calculating correlation while iterating on a bigger picture\n");
	
	
	int col_lostcat = 80, row_lostcat = 57;
	unsigned short *arr_lostcat = (unsigned short*)malloc( sizeof(unsigned short)*col_lostcat*row_lostcat );
	
	int col_catsearch = 640, row_catsearch = 360;
	unsigned short *arr_catsearch = (unsigned short*)malloc( sizeof(unsigned short)*col_catsearch*row_catsearch );
	
	
	fileToArray("data/lost-cat80x57.dat", col_lostcat, row_lostcat, arr_lostcat);
	printMatrix(arr_lostcat, col_lostcat, row_lostcat);
	
	fileToArray("data/cat-search640x360.dat", col_catsearch, row_catsearch, arr_catsearch);
	printMatrix(arr_catsearch, col_catsearch, row_catsearch);
	
	
	printf("Testing: shifting little picture on big picture, calculating corr. along the way\n");
	printf("**FORMAT** \t|| file1 | file2 ||\t number \n\n");
	printf("|| lost-cat80x57.dat | cat-search640x360.dat ||\n");
	printf("searching in : lower half\n");
	
	int pixel_step = 5;
	float corr_lim = 0.4;
	printf("Iteration step size : %d", pixel_step);
	printf("position of top left corner where corr. > %.4f :\n", corr_lim);
	
	
	// for finding the best match
	float corr_best = 0.0;
	int i_best = 0, j_best = 0;
	
	
	for(int j = (int)( floor((row_catsearch/2)/pixel_step) ); j < (int)( floor((row_catsearch - row_lostcat)/pixel_step) ); j++){ // stepping vertically
		
    		for(int i = 0; i < (int)( floor((col_catsearch - col_lostcat)/pixel_step) ); i++){ // stepping horizontally
			
			float corr_buffer = correlation(arr_lostcat, row_lostcat, col_lostcat, arr_catsearch, row_catsearch, col_catsearch, 
							pixel_step*i + pixel_step*j * col_catsearch);
			
			if(corr_buffer > corr_lim){
			
				printf("\t\t| row : %i ; col : %i ; pos : %i | corr : %.8f\n", 
					j*pixel_step + 1 , i*pixel_step + 1, i*pixel_step + j*pixel_step * col_catsearch, corr_buffer);
				
				if(corr_buffer > corr_best){ // getting the value and the indeces of the best match
					corr_best = corr_buffer;
					i_best = i * pixel_step;
					j_best = j * pixel_step;
				}
				
			}
		}
	}
	


// PART (E)
// - mainly serves to test functions
// - this runs independently from the given arguments
// - testing on : "smiley10x11.dat", "sad10x11.dat", "tree10x11.dat", "smileybig24x19.dat"
	
	printf("\n-----PART (E)-----\n\n");
	printf("TESTING : searching for the greatest correlation\n");
	
	
	printf("The best match is currently at:\n");
	printf("\t\t| row : %i ; col : %i ; pos : %i | corr : %.8f\n", j_best+1, i_best+1, i_best + j_best*col_catsearch, corr_best);
	
	printf("Initial iteration step size : %d\n", pixel_step);
	printf("Searching in the +/-%d vicinity of the best match...\n", pixel_step-1);
	
	float corr_foundcat = corr_best;
	int i_foundcat  = 0, j_foundcat = 0;
	
	for(int j = j_best-(pixel_step-1); j < j_best+(pixel_step-1); j++){
		for(int i = i_best-(pixel_step-1); i < i_best+(pixel_step-1); i++){
			
			float corr_buffer = correlation(arr_lostcat, row_lostcat, col_lostcat, arr_catsearch, row_catsearch, col_catsearch, i + j*col_catsearch);
			
			if(corr_buffer > corr_foundcat){
				
				printf("Found an even better match!");
				
				corr_foundcat = corr_buffer;
				i_foundcat = i;
				j_foundcat = j;
				
				printf("\t\t| row : %i ; col : %i ; pos : %i | corr : %.8f\n", j_foundcat+1, i_foundcat+1, i_foundcat + j_foundcat*col_catsearch, corr_foundcat);
			}
		}
	}
	
	
	
	printf("The best match is :\n");
	printf("\t\t| row : %i ; col : %i ; pos : %i | corr : %.8f\n", j_foundcat+1, i_foundcat+1, i_foundcat + j_foundcat*col_catsearch, corr_foundcat);
	
	
	
	
	
	
	
	
return 0;
}
