#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>



//PRINTING A 1D ARRAY AS A MATRIX
void printMatrix(double *a, int col, int row){
	
	int columnLimit = 20;
	
	if(col < columnLimit){ 
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				printf(" %lf ",a[i*col+j]);
			}
			printf("\n");
		}
		
	}else{ printf("\t| MATRIX HAS TOO MANY COLUMNS |\n"); }
}




//READING A FILE CONTAINING 3 COLUMNS
void readFile(char s[], double* x1, double* x2,double* y, int size){

	FILE *fp;
	
	if ((fp = fopen(s,"r")) == NULL){
		printf("Error opening file!\n");
		exit(1);
	}
	fp = fopen(s, "r");
	char* token;
	
	
	int count = 0;
	int numRead = 0;
	int i = 0;
	
	while (i != size)
	{
	    numRead = fscanf(fp, "%lf %lf %lf\r\n", &x1[i], &x2[i], &y[i]);
	    i++;
	}
}



// LOGISTIC FUNCTION
double g(double a0, double a1, double a2, double x1, double x2)
{
	double ax = a0 + a1*x1 + a2*x2;
	return (1/(1+exp(-ax)));
}


// COST FUNCTION AT INDEX
double cost(double a0, double a1, double a2, double x1, double x2, double y)
{
	double res;

	if ((int)y == 1)
		res = -log( g(a0,a1,a2,x1,x2) );
	if ((int)y == 0)
		res = -log( 1 - g(a0,a1,a2,x1,x2) );
	return res;
}






// COST FUNCTION FOR DATASET
double J(double a0, double a1, double a2, double* x1, double* x2, double* y, int size)
{
	double s = 0;
	
	for (int i = 0; i < size; i++)
	{
		s += cost(a0, a1, a2, x1[i], x2[i], y[i]);
	}
	
	return s/size;
}



// DERIVATIVE
double derivativeCost(double a0, double a1, double a2, double* x1, double* x2, double* y, int k, int size)
{

	double s = 0;
	for (int i = 0; i < size ; i++)
	{
		if (k==0)
			s += ( g(a0, a1, a2, x1[i], x2[i]) - y[i] );
		if (k==1)
			s += ( g(a0, a1, a2, x1[i], x2[i]) - y[i] ) * x1[i];
		if (k==2)
			s += ( g(a0, a1, a2, x1[i], x2[i]) - y[i] ) * x2[i];
	}
	
	return s/size;
}













int main(int argc, char **args)
{

	// Memory allocation and reading file

	int size = atoi(args[2]);
	double* x1 = (double*)malloc(sizeof(double)*size);
	double* x2 = (double*)malloc(sizeof(double)*size);
	double* y = (double*)malloc(sizeof(double)*size);
	
	readFile(args[1], x1, x2, y, size);
	
	
	
	
	
	// Computing Jgrid	
	
	printf("\nComputing Jgrid...\n");
	FILE *fptr;
	if ((fptr = fopen("Jgrid.dat", "w")) == NULL){
		printf("Error opening file : Jgrid.dat\n");
		exit(1);
	}
	
	fptr = fopen("Jgrid.dat", "w");
	printf("\tOpened file : Jgrid.dat\n");
	

	
	
	double a0_min = -15;
	double a0_max = -5;
	double a1_min = 0;
	double a1_max = 0.6;
	
	double dots = 76;
	double a0_step = (a0_max - a0_min)/(dots-1);
	double a1_step = (a1_max - a1_min)/(dots-1);
		
	for (double a0 = a0_min; a0 < a0_max; a0 += a0_step)
	{
		for (double a1 = a1_min; a1 < a1_max; a1 += a1_step)
		{
			fprintf(fptr, "%lf %lf %lf \n", a0, a1, J(a0, a1, 0, x1, x2, y, size));
		}
	}
	
	fclose(fptr);
	printf("\tSuccess!\n");
	
	
	// Derivative of a0 and a1
	printf("\nTesting derivative function...\n");
	FILE* fptr_a0;
	FILE* fptr_a1;
	if ((fptr_a0 = fopen("deriv_a0.dat", "w")) == NULL){
		printf("Error opening file : deriv_a0\n");
		exit(1);
	}
	if ((fptr = fopen("deriv_a1.dat", "w")) == NULL){
		printf("Error opening file : deriv_a1.dat\n");
		exit(1);
	}
	
	fptr_a0 = fopen("deriv_a0.dat", "w");
	printf("\tOpened file : deriv_a0.dat\n");
	fptr_a1 = fopen("deriv_a1.dat", "w");
	printf("\tOpened file : deriv_a1.dat\n");
	
	for (double a0 = a0_min; a0 < a0_max; a0 += a0_step)
	{
		for (double a1 = a1_min; a1 < a1_max; a1 += a1_step)
		{
			fprintf(fptr_a0, "%lf %lf %lf \n", a0, a1, derivativeCost(a0, a1, 0, x1, x2, y, 0, size));
			fprintf(fptr_a1, "%lf %lf %lf \n", a0, a1, derivativeCost(a0, a1, 0, x1, x2, y, 1, size));
		}
	}
	
	fclose(fptr_a0);
	fclose(fptr_a1);
	printf("\tSuccess!\n");
	
	



	
	// Search for the minimum by stepping
	printf("\nSearch for the minimum by stepping...\n");
	
	double alpha;
	double a0_iter = -15;
	double a1_iter = 0;
	dots = 201;
	
	
// alpha = 0.015	
	alpha = 0.015;
	printf("\talpha = %lf\n", alpha);


	if ((fptr = fopen("deriv_015.dat", "w")) == NULL){
		printf("Error opening file : deriv_015.dat\n");
		exit(1);
	}
	fptr = fopen("deriv_015.dat", "w");
	printf("\tOpened file : deriv_015.dat\n");
	
	
	for (int i = 0; i < dots*dots; i++)
	{
		a0_iter = a0_iter - alpha*derivativeCost(a0_iter, a1_iter, 0, x1, x2, y, 0, size);
		a1_iter = a1_iter - alpha*derivativeCost(a0_iter, a1_iter, 0, x1, x2, y, 1, size);
		
		fprintf(fptr, "%lf %lf %lf \n", a0_iter, a1_iter, J(a0_iter, a1_iter, 0, x1, x2, y, size));
	}


	fclose(fptr);
	printf("\tSuccess!\n");
	
		
	
	
	
// alpha = 0.01
	alpha = 0.01;
	printf("\talpha = %lf\n", alpha);


	if ((fptr = fopen("deriv_010.dat", "w")) == NULL){
		printf("Error opening file : deriv_010.dat\n");
		exit(1);
	}
	fptr = fopen("deriv_010.dat", "w");
	printf("\tOpened file : deriv_010.dat\n");
	
	
	for (int i = 0; i < dots*dots; i++)
	{
		a0_iter = a0_iter - alpha*derivativeCost(a0_iter, a1_iter, 0, x1, x2, y, 0, size);
		a1_iter = a1_iter - alpha*derivativeCost(a0_iter, a1_iter, 0, x1, x2, y, 1, size);
		
		fprintf(fptr, "%lf %lf %lf \n", a0_iter, a1_iter, J(a0_iter, a1_iter, 0, x1, x2, y, size));
	}


	fclose(fptr);
	printf("\tSuccess!\n");



// alpha = 0.02
	alpha = 0.02;
	printf("\talpha = %lf\n", alpha);


	if ((fptr = fopen("deriv_020.dat", "w")) == NULL){
		printf("Error opening file : deriv_020.dat\n");
		exit(1);
	}
	fptr = fopen("deriv_020.dat", "w");
	printf("\tOpened file : deriv_020.dat\n");
	
	
	for (int i = 0; i < dots*dots; i++)
	{
		a0_iter = a0_iter - alpha*derivativeCost(a0_iter, a1_iter, 0, x1, x2, y, 0, size);
		a1_iter = a1_iter - alpha*derivativeCost(a0_iter, a1_iter, 0, x1, x2, y, 1, size);
		
		fprintf(fptr, "%lf %lf %lf \n", a0_iter, a1_iter, J(a0_iter, a1_iter, 0, x1, x2, y, size));
	}


	fclose(fptr);
	printf("\tSuccess!\n");
	
	
	
	

// alpha = 0.0125
	alpha = 0.0125;
	printf("\talpha = %lf\n", alpha);


	if ((fptr = fopen("deriv_0125.dat", "w")) == NULL){
		printf("Error opening file : deriv_0125.dat\n");
		exit(1);
	}
	fptr = fopen("deriv_0125.dat", "w");
	printf("\tOpened file : deriv_0125.dat\n");
	
	
	for (int i = 0; i < dots*dots; i++)
	{
		a0_iter = a0_iter - alpha*derivativeCost(a0_iter, a1_iter, 0, x1, x2, y, 0, size);
		a1_iter = a1_iter - alpha*derivativeCost(a0_iter, a1_iter, 0, x1, x2, y, 1, size);
		
		fprintf(fptr, "%lf %lf %lf \n", a0_iter, a1_iter, J(a0_iter, a1_iter, 0, x1, x2, y, size));
	}


	fclose(fptr);
	printf("\tSuccess!\n");
	
	
	
	
	
	
	
	// Shifing dataset with average
	printf("Applying gradient method in 2D\n");
	printf("\tSubtracting average from arrays...\n");
	
	double* X1 = (double*)malloc(sizeof(double)*size);
	double* X2 = (double*)malloc(sizeof(double)*size);
	
	double x1_sum = 0, x2_sum = 0;
	for(int i = 0; i < size; i++){
		x1_sum += x1[i];
		x2_sum += x2[i];
	}
	double x1_avg = x1_sum/size;
	double x2_avg = x2_sum/size;
	
	for(int i = 0; i < size; i++){
		X1[i] = x1[i] - x1_avg;
		X2[i] = x2[i] - x2_avg;
	}
	
	printf("\tShifted dataset complete!\n");
	
	
	
	// alpha = 0.01
	alpha = 0.01;
	printf("\talpha = %lf\n", alpha);


	if ((fptr = fopen("deriv_shift_010.dat", "w")) == NULL){
		printf("Error opening file : deriv_shift_010.dat\n");
		exit(1);
	}
	fptr = fopen("deriv_shift_010.dat", "w");
	printf("\tOpened file : deriv_shift_010.dat\n");
	
	
	
	
	// Computing Jgrid2
	
	printf("\tComputing Jgrid2_init...\n");
	if ((fptr = fopen("Jgrid2_init.dat", "w")) == NULL){
		printf("Error opening file : Jgrid2_init.dat\n");
		exit(1);
	}
	
	fptr = fopen("Jgrid2_init.dat", "w");
	printf("\tOpened file : Jgrid2_init.dat\n");
	

	
	
	
	printf("\tInitial Guess\n");
	
	a0_min = -5;
	a0_max = 5;
	a1_min = -0.5;
	a1_max = 0.5;
	
	dots = 76;
	a0_step = (a0_max - a0_min)/(dots-1);
	a1_step = (a1_max - a1_min)/(dots-1);
		
	for (double a0 = a0_min; a0 < a0_max; a0 += a0_step)
	{
		for (double a1 = a1_min; a1 < a1_max+a1_step; a1 += a1_step)
		{
			fprintf(fptr, "%lf %lf %lf \n", a0, a1, J(a0, a1, 0, X1, X2, y, size));
		}
	}
	
	fclose(fptr);
	printf("\tSuccess!\n");

	
	
	
	/*
	a0_iter = -11;
	a1_iter = 0;
	
	for (int i = 0; i < dots*dots; i++)
	{
		a0_iter = a0_iter - alpha*derivativeCost(a0_iter, a1_iter, 0, x1, x2, y, 0, size);
		a1_iter = a1_iter - alpha*derivativeCost(a0_iter, a1_iter, 0, x1, x2, y, 1, size);
		
		fprintf(fptr, "%lf %lf %lf \n", a0_iter, a1_iter, J(a0_iter, a1_iter, 0, x1, x2, y, size));
	}


	fclose(fptr);
	printf("\tSuccess!\n");
	*/
	
	
	
	
	
	
	
	
	





/*	
	// Recycling variables for the same purpose
	a0_min = -15;
	a0_max = -5;
//	a0_max = 15;
	a1_min = 0;
	a1_max = 0.6;
	

	a0_step = (a0_max - a0_min)/(dots-1);
	a1_step = (a1_max - a1_min)/(dots-1);
	
	
	
	int CUNT_a0 = 0;
	int CUNT_a1 = 0;
	
	for (double a0 = a0_min; a0 < a0_max; a0 += a0_step)
	{
		CUNT_a0 += 1;
		CUNT_a1 = 0;
		for (double a1 = a1_min; a1 < a1_max; a1 += a1_step)
		{
			fprintf(fptr, "%lf %lf %lf \n",
					a0,
					a1, 
					J( a0 - alpha*derivativeCost(a0, a1, 0, x1, x2, y , 0, size), a1 - alpha*derivativeCost(a0, a1, 0, x1, x2, y, 1, size), 0, x1, x2, y, size)
				);
			CUNT_a1 += 1;
		}
	}
	
	printf("CUNT : %i\t%i", CUNT_a0, CUNT_a1);
*/



return 0;
}
