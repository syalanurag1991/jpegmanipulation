#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIZE 16
#define BPP 1
#define BytesPerPixel 1

#define PI 3.14159265
#define SQRT_2 1.41421356

int main(int argc, const char *argv[])
{
    if (argc != 2) {
        printf("\nThere should be 2 inputs. Usage:");
        printf("\nProgram 16x16_RAW_Image\n");
        exit(1);
    }
	printf("\nHope this works...");
	
	long i=0, j=0, k=0, file_len=0, uniq_sym=0;
	FILE *file_ptr1, *file_ptr2;
	char buffer[10];
	
	int quantMatrix[8][8] = {
	{16, 11, 10, 16, 24,  40,  51,  61},
	{12, 12, 14, 19, 26,  58,  60,  55},
    {14, 13, 16, 24, 40,  57,  69,  56},
	{14, 17, 22, 29, 51,  87,  80,  62},
    {18, 22, 37, 56, 68,  109, 103, 77},
	{24, 35, 55, 64, 81,  104, 113, 92},
    {49, 64, 78, 87, 103, 121, 120, 101},
	{72, 92, 95, 98, 112, 100, 103, 99}};
	
	// image data array
	int size = SIZE, x, y, z;
	//int BytesPerPixel = BPP;
	unsigned char Imagedata[size][size][BytesPerPixel];
	int ImageValues[size][size][BytesPerPixel];
	unsigned char blocks[4][8][8][BytesPerPixel];
	int blocksValues[4][8][8][BytesPerPixel];
	
	
	/*Using fopen, Open in binary mode
	Using fread, Read the file into the Imagedata
	Using fseek, Seek to the end of file
	Using ftell, find the current location of the file pointer
	Using rewind, bring file pointer to the start of the file*/
	file_ptr1 = fopen(argv[1],"rb");
	//file_ptr1 = fopen("walter.raw", "rb");
	if (!(file_ptr1)){
		printf("\nCannot open file!!");
		exit(1);}
	fread(Imagedata, sizeof(unsigned char), size*size*BytesPerPixel, file_ptr1);
	fseek(file_ptr1, 0, SEEK_END);
	file_len = ftell(file_ptr1);
	printf("\n\nThe size of the file is: %ld bytes", file_len);
	rewind(file_ptr1);
	fclose(file_ptr1);
	
	//Printing the image in char Values
	//Creating signed integer image Values
	printf("\n\nThe image is (char values):\n\n");
	for(y=0; y<size; y++){
		for(x=0; x<size; x++){
			ImageValues[y][x][0] = (int)Imagedata[y][x][0];
			printf("%c ", Imagedata[y][x][0]);}
		printf("\n");}
	
	//Converting to four 8x8 blocks
	for(z=0, y=0; y<size; y++){
		if(y>=8) z=1;
		for(x=0; x<size; x++){
			if(x>=8) z++; 
			blocks[z][y][x%8][0] = Imagedata[y][x][0];
			//printf("%d ", z);
			//printf("%c ", blocks[z][y][x%8][0]);
			if(x>=8) z--; }
		/*printf("\n");*/}

	//Printing the image blocks
	printf("\nThe blocks are:\n\n");
	for(z=0; z<4; z++){
		for(y=0; y<8; y++){
			for(x=0; x<8; x++){
				printf("%c ", blocks[z][y][x][0]);}
			printf("\n");}
		printf("\n");}	
		
	//Printing the image in int values
	printf("\n\nThe image is (int values):\n\n");
	for(y=0; y<size; y++){
		for(x=0; x<size; x++){
			printf("%03d ", Imagedata[y][x][0]);}
		printf("\n");}
	
	//Re-centering the Image values
	printf("\n\nAfter recentering (int values):\n\n");
	for(y=0; y<size; y++){
		for(x=0; x<size; x++){
			ImageValues[y][x][0]-= 128;
			printf("%04d ", ImageValues[y][x][0]);}
		printf("\n");}

	//Creating Re-centred blocks from signed image Values
	for(z=0, y=0; y<size; y++){
		if(y>=8) z=1;
		for(x=0; x<size; x++){
			if(x>=8){z++;} 
			blocksValues[z][y][x%8][0] = ImageValues[y][x][0];
			//printf("%d ", z);
			//printf("%c ", blocks[z][y][x%8][0]);
			if(x>=8){z--;}}
			/*printf("\n");*/}

	//Printing the Re-Centred signed image blocks Values
	printf("\nThe Re-Centred Blocks are:\n\n");
	for(z=0; z<4; z++){
		for(y=0; y<8; y++){
			for(x=0; x<8; x++){
				printf("%04d ", blocksValues[z][y][x][0]);}
			printf("\n");}
		printf("\n");}

	
	//Calculating DCT Coefficients for each cell of each block
	printf("\nThe DCT Coefficeints for Recentred blocks are:\n\n");	
	double dctValues[4][8][8][BytesPerPixel] = {0}, xCosProduct, yCosProduct;
	for(k=0; k<4; k++){
		for(j=0; j<8; j++){
			for(i=0; i<8; i++){
				for(y=0; y<8; y++){		
					
					double sumXforY[8] = {0};
					//printf("%.2f  ", sumXforY[y]);
					for(x=0; x<8; x++){
						xCosProduct = blocksValues[k][y][x][0] * cos( ((2*x+1)*i*PI)/16 );
						sumXforY[y] += xCosProduct;}
					
					yCosProduct = sumXforY[y] * cos( ((2*y+1)*j*PI)/16 );		
					dctValues[k][j][i][0] += yCosProduct;
				}
				
				if((i==0) && (j==0)) 
					dctValues[k][j][i][0] = dctValues[k][j][i][0]/8;
				else if ( ((i==0) || (j==0)) && (i!=j) )
					dctValues[k][j][i][0] = dctValues[k][j][i][0]/(4*SQRT_2);
				else{
				
					dctValues[k][j][i][0] = dctValues[k][j][i][0]/4;
					//printf("%.2f ", dctValues[k][j][i][0]);
					}
				printf("%07.2f ", dctValues[k][j][i][0]);
			}
		printf("\n");
		}
	printf("\n");
	}
	
	//Printing the basic Quantization Matrix
	printf("\nBasic Quantization Matrix (Luminance) for 50%% Quality:\n\n");	
	for(j=0; j<8; j++){
		for(i=0; i<8; i++){
			printf("%03d  ", quantMatrix[j][i]);
			}
		printf("\n");
	}
	
	//Quantizing the DCT Coefficeints with the given Quantization Matrix
	printf("\n\nQuantized DCT Coefficeints for Re-Centered blocks are:\n\n");	
	int quantDCTValues[4][8][8][BytesPerPixel] = {0};
	for(k=0; k<4; k++){
		for(j=0; j<8; j++){
			for(i=0; i<8; i++){
				quantDCTValues[k][j][i][0] = round(dctValues[k][j][i][0]/quantMatrix[j][i]);
				printf("%03d ", quantDCTValues[k][j][i][0]);}
			printf("\n");}
		printf("\n");}	
		
	//Calculating the Quality Factor Multiplier
	double qFactor = 90, qMultiplier = 1;
	if(qFactor < 50)
		qMultiplier = 50/qFactor;
	if(qFactor > 50)
		qMultiplier = (100 - qFactor)/50;
	
	//Printing the Quantization Matrix for 90% Quality
	printf("\nQuantization Matrix (Luminance) for 90%% Quality:\n\n");	
	for(j=0; j<8; j++){
		for(i=0; i<8; i++){
			//printf("%.2f  ", (float)quantMatrix[j][i]/(float)qDivider);
			printf("%05.2f  ", quantMatrix[j][i]*qMultiplier);
			}
		printf("\n");
	}
	
	//Quantizing the DCT Coefficeints with the given Quantization Matrix
	printf("\n\nQuantized DCT Coefficeints for Re-Centered blocks at 90%% Quality:\n\n");	
	//int quantDCTValues[4][8][8][BytesPerPixel] = {0};
	for(k=0; k<4; k++){
		for(j=0; j<8; j++){
			for(i=0; i<8; i++){
				quantDCTValues[k][j][i][0] = round( dctValues[k][j][i][0] /  (qMultiplier * quantMatrix[j][i]) );
				printf("%04d ", quantDCTValues[k][j][i][0]);}
			printf("\n");}
		printf("\n");}
		
	//Calculating the Quality Factor Multiplier
	qFactor = 10; qMultiplier = 1;
	if(qFactor < 50)
		qMultiplier = 50/qFactor;
	if(qFactor > 50)
		qMultiplier = (100 - qFactor)/50;
	
	//Printing the Quantization Matrix for 10% Quality
	printf("\nQuantization Matrix (Luminance) for 10%% Quality:\n\n");	
	for(j=0; j<8; j++){
		for(i=0; i<8; i++){
			//printf("%.2f  ", (float)quantMatrix[j][i]/(float)qDivider);
			printf("%06.2f  ", quantMatrix[j][i]*qMultiplier);
			}
		printf("\n");
	}
	
	//Quantizing the DCT Coefficeints with the given Quantization Matrix
	printf("\n\nQuantized DCT Coefficeints for Re-Centered blocks at 10%% Quality:\n\n");	
	//int quantDCTValues[4][8][8][BytesPerPixel] = {0};
	for(k=0; k<4; k++){
		for(j=0; j<8; j++){
			for(i=0; i<8; i++){
				quantDCTValues[k][j][i][0] = round( dctValues[k][j][i][0] /  (qMultiplier * quantMatrix[j][i]) );
				printf("%02d ", quantDCTValues[k][j][i][0]);}
			printf("\n");}
		printf("\n");}
	
}
