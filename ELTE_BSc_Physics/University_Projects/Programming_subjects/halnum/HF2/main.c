#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>




// COUNT HOW MANY PIXELS ARE IN THE INTERVALS
void interval(unsigned short data[], int data_len, int div, unsigned short start, unsigned short end, int *arr)
{
	
	int length = (int)((1+end-start)/div); // length of the interval
	
	for (int i = 0; i < div; i++)
		arr[i]=0;
	
	int s;
	
	for (int i = 0; i < data_len; i++){
		s = (int)(trunc((data[i]-start)/length));
		arr[s-1]+=1;
	}
}




int main(int argc, char **args){
	
	int horizontal 	= atoi(args[2]); // number of pixels in a row
	int vertical 	= atoi(args[3]); // number of pixels in a column
	
	int size = horizontal*vertical; // total number of pixels
	
	unsigned short data[size]; // allocate memory for storing data
	
	
	char str[8]; // character arry for reading buffer
	
	
	
	
// OPEN FILE (RAW IMAGE DATA)
	
	char filename[25];
	strcpy(filename, "data/");
	strcpy(filename+strlen("data/"), args[1]);
	
	FILE *fp;
	if ( (fp = fopen(filename, "r")) == NULL ){
	
		printf("Error opening file %s!\n", args[1]);
		exit(1);
	}	
	fp = fopen(filename, "r");
	
	
	printf("Reading file : %s\n", filename);
	int i = 0;
	printf("%d\n", size);
	while(1){
		if(fgets(str, size, fp) == NULL) break;
		data[i] = (unsigned short)(atoi(str));
		i++;
	}
	fclose(fp);
	
	
// DIVISION TO 8 PINS

	printf("DIVISION TO 8 PINS\n");

	int div = 8; // number divisions in the histogram
	int* hist_8 = (int*) malloc(sizeof(int)*div); // allocate memory for histogram heights
	unsigned short start, end; // start and end of the interval we divide
	
	start = 0;
	end = 255;
	


	// calculate histogram pin heights
	interval(data, size, div, start, end, hist_8);
	
	printf("\tHistogram results :\n");
	for (int i = 0; i < div; i++)
		printf("\t\t%i\n",hist_8[i]);
	
	
// writing result into a file

	FILE *fptr;
	
	if ((fptr = fopen("data/hist.dat","w")) == NULL){
		printf("Error! opening file!\n");
		exit(1);
	}
	fptr = fopen("data/hist.dat", "w");
	
	
	printf("Writing hist.dat ...\n");
	float length = (1+end-start)/div;
	
	printf("\tCenter of histogram pins :\n");
	for (int i = 0; i < div; i++)
	{
		printf("\t\t%f\n",(i*length+length/2));
		fprintf(fptr, "%f %i\n",(i*length+length/2),hist_8[i]);
	}
	fclose(fptr);
	
	
	
	
	
	
// DIVISION TO 256 PINS
	
	printf("\n\nDIVISION TO 256 PINS\n");
	
	div = 256; // number of pins
	int* hist_256 = (int*)malloc(sizeof(int)*div); // allocate memory for histogram heights
	
	
	start = 0;
	end = 255;
	
	interval(data, size, div, start, end, hist_256);
	
	
// writing result into a file

	if ((fptr = fopen("data/hist_256.dat","w")) == NULL){
		printf("Error! opening file!\n");
		exit(1);
	}
	//fptr = fopen("data/histeq.dat", "w");
	fptr = fopen("data/hist_256.dat", "w");
	
	
	printf("Writing hist_256.dat ...\n");
	length = (1+end-start)/div;
	
	printf("\tCenter of histogram pins :\n");
	for (int i = 0; i < div; i++)
	{
		printf("\t\t%f\n",(i*length+length/2));
		fprintf(fptr, "%f %i\n",(i*length+length/2),hist_256[i]);
	}
	fclose(fptr);

	
	
// cumulative distribution
	
	int* cumul = (int*)malloc(sizeof(int)*div); // allocate memory for cumulative distribution
	
	// calculate cumulative distribution
	cumul[0] = hist_256[0];
	for (int i = 1; i < div; i++)
	{
		cumul[i] = cumul[i-1] + hist_256[i];
	}

// write result into a file

	if ((fptr = fopen("data/cumul.dat","w")) == NULL){
		printf("Error! opening file!\n");
		exit(1);
	}
	
	
	fptr = fopen("data/cumul.dat", "w");
	printf("Writing cumul.dat ...\n");
	for (int i = 0; i < div; i++)
	{
		//printf("%i %i\n",i,cumul[i]);
		fprintf(fptr, "%i %i\n",i+1,cumul[i]);
	}
	fclose(fptr);
	
	
	
	
	
	
	
// export pixels
	
	int* k = (int*)malloc(sizeof(int)*div); // defined in the .pdf
	for (int i = 0; i < div; i++)
	{
		k[i] = (int)(floor(255*cumul[i]/size));
	}
	
	// generate pixel data
	int* pixel = (int*)malloc(sizeof(int)*size);
	for (int i = 0; i < size; i++)
	{
		pixel[i] = k[data[i]];
	}
	
	
	// write pixel data to file
	if ((fptr = fopen("data/equalized.dat","w")) == NULL){
		printf("Error! opening file!\n");
		exit(1);
	}

	printf("Writing equalized.dat ...\n");
	fptr = fopen("data/equalized.dat", "w");
	for (int i = 0; i < size; i++)
	{
		fprintf(fptr, "%i\n",pixel[i]);
	}
	fclose(fptr);




















// ANALYZING TRANSFORMED IMAGE
	
	printf("\n\nANALYZING EQUALIZED IMAGES\n\n");
	printf("Using data written to \'equatlized.dat\'\n");
	
	
	
	unsigned short dataeq[size]; // allocate memory for storing data
	
	for(i = 0; i < size; i++){
		dataeq[i] = (unsigned short)(pixel[i]);
	}
	
	
	

// histogram	
	div = 256; // number of pins	
	start = 0;
	end = 255;
	int* histeq = (int*)malloc(sizeof(int)*div); // allocate memory for histogram heights
	
	interval(dataeq, size, div, start, end, histeq);
	

	if ((fptr = fopen("data/histeq.dat","w")) == NULL){
		printf("Error! opening file!\n");
		exit(1);
	}
	fptr = fopen("data/histeq.dat", "w");
	
	
	
	printf("Writing histeq.dat ...\n");
	length = (1+end-start)/div;
	
	printf("\tCenter of histogram pins :\n");
	for (int i = 0; i < div; i++)
	{
		printf("\t\t%f\n",(i*length+length/2));
		fprintf(fptr, "%f %i\n",(i*length+length/2),histeq[i]);
	}
	fclose(fptr);
	
	
// cumulative distribution
	
	int* cumuleq = (int*)malloc(sizeof(int)*div); // allocate memory for cumulative distribution
	
	// calculate cumulative distribution
	cumuleq[0] = histeq[0];
	for (int i = 1; i < div; i++)
	{
		cumuleq[i] = cumuleq[i-1] + histeq[i];
	}

// write result into a file

	if ((fptr = fopen("data/cumuleq.dat","w")) == NULL){
		printf("Error! opening file!\n");
		exit(1);
	}
	
	
	fptr = fopen("data/cumuleq.dat", "w");
	printf("Writing cumuleq.dat ...\n");
	for (int i = 0; i < div; i++)
	{
		fprintf(fptr, "%i %i\n",i+1,cumuleq[i]);
	}
	fclose(fptr);
	
// export pixels
	
	int* keq = (int*)malloc(sizeof(int)*div); // defined in the .pdf
	for (int i = 0; i < div; i++)
	{
		keq[i] = (int)(floor(255*cumuleq[i]/size));
	}
	
	// generate pixel data
	int* pixeleq = (int*)malloc(sizeof(int)*size);
	for (int i = 0; i < size; i++)
	{
		pixeleq[i] = keq[pixel[i]];
	}
	
	
// write pixel data to file
	if ((fptr = fopen("data/equalizedeq.dat","w")) == NULL){
		printf("Error! opening file!\n");
		exit(1);
	}
	
	fptr = fopen("data/equalizedeq.dat", "w");
	printf("Writing equalizedeq.dat ...\n");
	
	for (int i = 0; i < size; i++)
	{
		fprintf(fptr, "%i\n",pixeleq[i]);
	}
	fclose(fptr);


return 0;
}
