#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


//READING A FILE INTO A 1D ARRAY
void fileToArray(char filename[], unsigned short *arr){ // filename, columns, rows, destiantion array
	
	printf("Reading file %s...\n", filename);
	FILE *fptr;
	char str[256];
	
	if( (fptr = fopen(filename, "r")) == NULL){
		printf("\tError opening file %s!\n", filename);
		exit(1);
	}
	fptr = fopen(filename, "r");
		
	char *token;
	while(1){
		if( fgets(str,256,fptr) == NULL ) break;
		if( str[0] != '#' && str[0] != '\n' ){
			
			token = strtok(str, " ");
			while( token != NULL){
				
				arr[i] = (float)( atof(token) );
				
				token = strtok(NULL, " ");
				i++;
			}
		
		}
	}
	
	
	fclose(fptr);
	printf("\tFile %s has been read.\n", filename);
	
}



// PRINTING 1D ARRAY AS MATRIX
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



// ADDING ROWS
// arr[row_dest][i] += arr[row_add][i]*quotient
void addRow(float *arr, int row_len, int row_add, int row_dest, float quotient){
	for(int i = 0; i < row_len + 1; i++){ // because the rowlen is for the original matrix, but this is matrix|vector
		arr[i + row_dest*(row_len+1)] += arr[i + row_add*(row_len+1)] * quotient;
	}
}



// GAUSS-JORDAN ELIMINATION
void GaussElimination(float *mat, float *vec, int n, float *x){
	printf("Gauss-Jordan elimination\n");
	
	
	// constructing the matrix|vector matrix
	float *data = (float*) malloc( sizeof(float) * n*(n+1) );
	
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			data[i*(n+1) + j] = mat[i*n + j];
		}
	data[(i+1)*(n+1)-1] = vec[i];
	}
	printf("\n\tThe original matrix :\n");
	printMatrix(data, n+1, n);
	
	
	// achieving 0s under the diagonal
	printf("\n\tAchievig 0s under the diagonal :\n");
	for(int j = 0; j < n - 1; j++){
		for(int i = j+1; i < n; i++){
			addRow(data, n, j, i, -g[i*(n+1) + j] / g[j*(n+1) + j]);
		}
	}
	printMatrix(data, n+1, n);
	
	
	// achieving 0s above the diagonal
	printf("\n\tAchieving 0s above the diagonal :\n");
	for (int j = 0; j < n; j++){
		for (int i = 0; i < j; i++){
			addRow(data, n, j, i, -g[i*(n+1) + j] / g[j*(n+1) + j]);
		}
	}
	printf("\n\tAchieving 0s above the diagonal :\n");
	printMatrix(data, n+1, n);
	
	
	// we divide each row in order to norm every non-zero element to 1
	printf("Normed matrix :\n");
	for(int i = 0; i < n; i++){
		addRow(data, n, i, i, -(g[i*(n+1) + i]-1) / g[i*(n+1) + i]);
	}
	printMatrix(data, n+1, n);
		
}





























