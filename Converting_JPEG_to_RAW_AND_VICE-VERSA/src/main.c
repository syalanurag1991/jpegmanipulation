#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <jerror.h>
#include <jpeglib.h>
#include <setjmp.h>

	
	/*The standard inout to the read function is a JPEG image.
 	* The function read_jpeg_file Reads from a JPEG file on disk
 	* specified by filename and saves into the raw_image buffer
 	* in an uncompressed format. It returns positive integer if 
 	* successful, -1 otherwise. Parameter "char *nameOfJPEGfile" 
 	* specifies the JPEG file to read from.
 	*/
int read_JPEG_file(char *nameOfJPEGfile, bool writeRAWfile, char *nameOfOutputRAWfile)
{
	//Defining the data structure for storing the raw image
	unsigned char *raw_image = NULL;
	unsigned int size;

	//printf("\n%s\n", nameOfJPEGfile);
    /* these are standard libjpeg structures for reading(decompression) */
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;
    
	/* libjpeg data structure for storing one row, that is, scanline of an image */
	/* Output row buffer */
    JSAMPROW row_pointer[1];
    /* Physical row width in output buffer */
	int row_stride;
    
	FILE *infile = fopen(nameOfJPEGfile, "rb");
	//printf("%ld", infile);
    
    int i = 0;
    if (!infile)
	{
        printf("\nError opening JPEG file %s!\n", infile);
        return 0;
    }

	void print_jpeg_info(struct jpeg_decompress_struct cinfo)
	{
    	printf("\nJPEG File info: ");
    	printf("\n	Image width and height: %d x %d", cinfo.image_width, cinfo.image_height);
    	printf("\n	Color components per pixel: %d", cinfo.num_components);
    	printf("\n	Color space: %d", cinfo.jpeg_color_space);
    	//printf("\n	Raw flag is: %d", cinfo.raw_data_out);
	}

   
    /*STEP 1: Here we set up the standard libjpeg error handler 
	the "err" seems to be an attribute of the object created of class cinfo
	It's nothing but a pointer "jerr", where "jerr" is the location to be pointed to in case of an error*/
    cinfo.err = jpeg_std_error(&jerr);
    
	/* setup decompression process and source, then read JPEG header
	cinfo is pointer to the location where the file is stored temporarily*/
    jpeg_create_decompress(&cinfo);
    
	/*STEP 2: This assignes a source to the address "cinfo",
	basically makes the library read from infile and store it at "cinfo" \*/
    jpeg_stdio_src(&cinfo, infile);
    
	/*STEP 3: Reading the image header which contains image information
	TRUE ensures that we will write a complete interchange-JPEG file.
    Pass TRUE unless you are very sure of what you're doing.*/
    jpeg_read_header(&cinfo, TRUE);
    print_jpeg_info(cinfo);
    
	/*STEP 4: Start Decompression.
	NOTE: In this example, we don't need to change any of the defaults set by
    jpeg_read_header(), so we do nothing here.*/
	jpeg_start_decompress(&cinfo);

    /* allocate memory to hold the uncompressed image 
	Example, a color image of size 600px by 400px will have num_components = 3*/
	size = cinfo.output_width*cinfo.output_height*cinfo.num_components;
	raw_image = (unsigned char*)malloc(size);
	/* We may need to do some setup of our own at this point before reading
    the data.  After jpeg_start_decompress() we have the correct scaled
    output image dimensions available, as well as the output colormap
    if we asked for color quantization.
    
	In this example, we need to make an output work buffer of the right size.*/ 
    /* JSAMPLEs per row in output buffer.
	So a 600px long row of a color image will have a size of 1800*/
	row_stride = cinfo.output_width * cinfo.output_components;
    
	/* now actually read the jpeg into the raw buffer */
    row_pointer[0] = (unsigned char *)malloc(row_stride);
    
    
    /*STEP 5: Here we use the library's state variable cinfo.output_scanline as the
    loop counter, so that we don't have to keep track ourselves.
    Read one scan line at a time */
    unsigned long location = 0;
    while (cinfo.output_scanline < cinfo.image_height)
    {
    	/* Here, "jpeg_read_scanlines" expects an array of pointers to scanlines.
     	Since the "row_pointer" array is only "1" element long, we pass it the address of the 1st pointer, i.e. cinfo*/
        jpeg_read_scanlines(&cinfo, row_pointer, 1 );
        
        for (i=0; i<cinfo.image_width*cinfo.num_components;i++)
        {
            raw_image[location++] = row_pointer[0][i];
        }
    }

     /*STEP 6: Wrap up decompression, destroy objects, free pointers and close open files */
    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);
    free(row_pointer[0]);
    fclose(infile);
    /* yup, we succeeded! */


    //STEP 7(OPTIONAL): Output the rawfile if needed
    //RAW File writing block

    if(writeRAWfile)
    {
    	FILE *outputRAWfile;
    	outputRAWfile = fopen(nameOfOutputRAWfile, "w");
    	fwrite(raw_image, sizeof(char), size, outputRAWfile);
    	fclose(outputRAWfile);	
    }
    
    return 3;
}



	/*The standard input image format is a rectangular array of pixels, with
 	* each pixel having the same number of "component" values (color channels).
 	* Each pixel row is an array of JSAMPLEs (which typically are unsigned chars).
 	* If you are working with color data, then the color values for each pixel
 	* must be adjacent in the row; for example, R,G,B,R,G,B,R,G,B,... for 24-bit
 	* RGB color.
 	*/

int write_JPEG_file (char *filename, int quality, int image_height, int image_width, int numberOfComponents, J_COLOR_SPACE colorSpace, char *rawFileName)
{

	FILE *rawfile = fopen(rawFileName, "rb");
	//printf("\nReading RAW file: %s\n", rawFileName);	
    if (!rawfile)
	{
        printf("\n\nError opening RAW file %s!\n", rawfile);
        return 0;
    }


	JSAMPLE *image_buffer; /* Points to large array of R,G,B-order data */
	long image_size = image_height*image_width*numberOfComponents; /* Number of rows in image*Number of columns in image */
	image_buffer = (JSAMPLE*) malloc(image_size);
	fread(image_buffer, sizeof(char), image_size, rawfile);
	
	/* This struct contains the JPEG compression parameters and pointers to
	* working space (which is allocated as needed by the JPEG library).
	* It is possible to have several such structures, representing multiple
	* compression/decompression processes, in existence at once.  We refer
	* to any one struct (and its associated working data) as a "JPEG object".
	*/
	struct jpeg_compress_struct cinfo;
	/* This struct represents a JPEG error handler.  It is declared separately
	* because applications often want to supply a specialized error handler
	* (see the second half of this file for an example).  But here we just
	* take the easy way out and use the standard error handler, which will
	* print a message on stderr and call exit() if compression fails.
	* Note that this struct must live as long as the main JPEG parameter
	* struct, to avoid dangling-pointer problems.
	*/
	struct jpeg_error_mgr jerr;
	/* More stuff */
	FILE * outfile;		/* target file */
	JSAMPROW row_pointer[1];	/* pointer to JSAMPLE row[s] */
	int row_stride;		/* physical row width in image buffer */

	/* Step 1: allocate and initialize JPEG compression object */

	/* We have to set up the error handler first, in case the initialization
	* step fails.  (Unlikely, but it could happen if you are out of memory.)
	* This routine fills in the contents of struct jerr, and returns jerr's
	* address which we place into the link field in cinfo.
	*/
	cinfo.err = jpeg_std_error(&jerr);
	/* Now we can initialize the JPEG compression object. */
	jpeg_create_compress(&cinfo);

	/* Step 2: specify data destination (eg, a file) */
	/* Note: steps 2 and 3 can be done in either order. */

	/* Here we use the library-supplied code to send compressed data to a
	* stdio stream.  You can also write your own code to do something else.
	* VERY IMPORTANT: use "b" option to fopen() if you are on a machine that
	* requires it in order to write binary files.
	*/
	if ((outfile = fopen(filename, "wb")) == NULL)
	{
    	fprintf(stderr, "Library error! Can't open %s\n", filename);
    	exit(1);
  	}
  
  	jpeg_stdio_dest(&cinfo, outfile);

	/* Step 3: set parameters for compression */

	/* First we supply a description of the input image.
	* Four fields of the cinfo struct must be filled in:
	*/
	cinfo.image_width = image_width; 	/* image width and height, in pixels */
	cinfo.image_height = image_height;
	cinfo.input_components = numberOfComponents;		/* # of color components per pixel */
	//cinfo.in_color_space = JCS_RGB; 	/* colorspace of input image */
	cinfo.in_color_space = colorSpace; 	/* colorspace of input image */
	//cinfo.in_color_space = JCS_GRAYSCALE; 	/* colorspace of input image */
	/* Now use the library's routine to set default compression parameters.
	* (You must set at least cinfo.in_color_space before calling this,
	* since the defaults depend on the source color space.)
	*/
	jpeg_set_defaults(&cinfo);
	/* Now you can set any non-default parameters you wish to.
	* Here we just illustrate the use of quality (quantization table) scaling:
	*/
	jpeg_set_quality(&cinfo, quality, TRUE /* limit to baseline-JPEG values */);

	/* Step 4: Start compressor */

	/* TRUE ensures that we will write a complete interchange-JPEG file.
	* Pass TRUE unless you are very sure of what you're doing.
	*/
	jpeg_start_compress(&cinfo, TRUE);

	/* Step 5: while (scan lines remain to be written) */
	/*           jpeg_write_scanlines(...); */

	/* Here we use the library's state variable cinfo.next_scanline as the
	* loop counter, so that we don't have to keep track ourselves.
	* To keep things simple, we pass one scanline per call; you can pass
	* more if you wish, though.
	*/
	row_stride = image_width * numberOfComponents;	/* JSAMPLEs per row in image_buffer */

	while (cinfo.next_scanline < cinfo.image_height)
	{
    	/* jpeg_write_scanlines expects an array of pointers to scanlines.
		* Here the array is only one element long, but you could pass
		* more than one scanline at a time if that's more convenient.
		*/
		row_pointer[0] = & image_buffer[cinfo.next_scanline * row_stride];
		(void) jpeg_write_scanlines(&cinfo, row_pointer, 1);
	}

	/* Step 6: Finish compression */

	jpeg_finish_compress(&cinfo);
	/* After finish_compress, we can close the output file. */
	fclose(outfile);

	/* Step 7: release JPEG compression object */

	/* This is an important step since it will release a good deal of memory. */
	jpeg_destroy_compress(&cinfo);

	/* And we're done! */
	return 2;
}


long int findFILEsize(char *fileName)
{
		FILE *file = fopen(fileName, "rb");
		if ( !(file) )
		{
			printf("\n	Cannot open file!!!\n");
			exit(1);
		}
		fseek(file, 0, SEEK_END);
		long int file_len = ftell(file);
		//printf("\nThe size of the file is: %ld bytes\n", file_len);
		rewind(file);
		fclose(file);
		return file_len;
}


void analyseNewJPEG (char *outputJPEG, char *outputRAW, char *inputRAW, int xImageSize, int yImageSize, int BytesPerPixel)
{

	//Setting up FILE IO
	FILE *tempFileRead1 = fopen(outputRAW, "rb");
	FILE *tempFileRead2 = fopen(inputRAW, "rb");
	unsigned char rawOriginal[yImageSize][xImageSize][BytesPerPixel];
	unsigned char  rawCreated[yImageSize][xImageSize][BytesPerPixel];

	//Open file and stop if it does not open
	if ( !(tempFileRead1) && !(tempFileRead2) )
	{
		printf("\n	Cannot open files!\n	PSNR Calculation failed!\n");
		exit(1);
	}

	//Read the files into 'temporary' image buffers
	fread(rawOriginal, sizeof(unsigned char), yImageSize*xImageSize*BytesPerPixel, tempFileRead1);
	fread(rawCreated, sizeof(unsigned char), yImageSize*xImageSize*BytesPerPixel, tempFileRead2);
	fclose(tempFileRead1);
	fclose(tempFileRead2);
	
	//PSNR Calculation
	//The MAX value a pixel can take is 255 or 2^b-1
	//Where b is the number of bits for 1 pixel
	//Which is 8 in case of grayscale images
	printf("\nJPEG Analysis info:");
	
	//Setting up parameters	
	long int sizeRAWinput    = findFILEsize(inputRAW);
	long int sizeJPEGcreated = findFILEsize(outputJPEG);
	double compressionRatio  = ((double)sizeRAWinput)/((double)sizeJPEGcreated);
	double savingsRatio      = 100 - (((double)sizeJPEGcreated*100)/((double)sizeRAWinput));
	double sumSqDiff = 0;
	double meanSqError = 0;
	double psnr = 0;
	double  MAX = 255;
	int xSizeOfPSNRblock = xImageSize;
	int ySizeOfPSNRblock = yImageSize;
	long numberOfPixels = xImageSize*yImageSize;
	int psnrCalcBlock[ySizeOfPSNRblock][xSizeOfPSNRblock][BytesPerPixel];

	//Calculating the PSNR for the supplied pair of images
	for(int y=0; y<ySizeOfPSNRblock; y++){
		for(int x=0; x<xSizeOfPSNRblock; x++){
			psnrCalcBlock[y][x][0] = rawCreated[y][x][0] - rawOriginal[y][x][0];
			//psnrCalcBlock[y][x][0] = (int)rawCreated[y][x][0] - (int)rawOriginal[y][x][0];
			sumSqDiff += pow(psnrCalcBlock[y][x][0], 2);
		}
	}
	
	meanSqError = sumSqDiff/numberOfPixels;
	psnr = 10*log10( pow(MAX, 2) / meanSqError );
	
	printf("\n	Size: %ld bytes", sizeJPEGcreated);
	printf("\n	Size: %ld bytes", sizeRAWinput);
	printf("\n	Compression Ratio: %.02f", compressionRatio);
	printf("\n	Savings: %.02f(%%)", savingsRatio);
	printf("\n	MSE: %.02f", meanSqError);
	printf("\n	PSNR: %.02f", psnr);

}


int main ()
{
// int main (int argc, char *argv[])
// {
	
// 	 if(argc != 2)
// 	 {
// 	 	printf("\nThere should be 2 inputs.\nProgram creates images for QF 100, 60, 40, 20, 10 and 1");
// 	 	printf("\n\nUsage:\nProgram RAw_Image_File\n");
// 	 	printf("\nPlease make sure that there is a folder named 'results' in the directory\n");
// 	 	exit(1);
// 	 }

	 printf("\nPlease make sure that there is a folder named 'results' in the directory\n");

	//Setting up INPUT Block
	char *subjectRAWfile = "../src/clock.raw"; 
	//char *subjectRAWfile = argv[1]; 
	int jpegQualityIndex[6] = {100, 60, 40, 20, 10, 1};
	
	//Setting up OUTPUT file names
	char *outputJPEGfileIndex[6] =  {"../results/outputJPEGimage_100.jpg",
									 "../results/outputJPEGimage_60.jpg",
									 "../results/outputJPEGimage_40.jpg",
									 "../results/outputJPEGimage_20.jpg",
									 "../results/outputJPEGimage_10.jpg",
									 "../results/outputJPEGimage_1.jpg"};
	
	char *outputRAWfileIndex[6] =   {"../results/outputRAWimage_100.raw",
									 "../results/outputRAWimage_60.raw",
									 "../results/outputRAWimage_40.raw",
									 "../results/outputRAWimage_20.raw",
									 "../results/outputRAWimage_10.raw",
									 "../results/outputRAWimage_1.raw"};

	
	printf("\nProcessing input RAW file: %s\n", subjectRAWfile);	
	
	for(int i = 0; i < 6; i++)
	{
		//JPEG Writing Block
		//Setting up Parameters
		int outputImageHeight  = 256;	
		int outputImageWidth   = 256;
		int numberOfComponents = 1;
		J_COLOR_SPACE colorSpace = JCS_GRAYSCALE;
		
		//Setting up FILE IO
		char *inputRAWfile = subjectRAWfile; 
		char *outputJPEGfile = outputJPEGfileIndex[i];
		
		//Generating JPEG Files of desired quality
		int jpegQuality = jpegQualityIndex[i];
		if(write_JPEG_file(outputJPEGfile, jpegQuality, outputImageHeight, outputImageWidth, numberOfComponents, colorSpace, inputRAWfile))
		{
			printf("\n\n\nAn output JPEG file,  %s, was written with quality: %d%%", outputJPEGfileIndex[i], jpegQualityIndex[i]);
		}

		//JPEG Reading Block
		//Setting up Parameters
		char *inputJPEGfile = outputJPEGfileIndex[i];
		char *outputRAWfile = outputRAWfileIndex[i];
		bool createRawfile = TRUE;
		
		//Generating RAW Files
		if(read_JPEG_file(inputJPEGfile, createRawfile, outputRAWfile))
		{
			//printf("\n	JPEG file was read: %s\n", inputJPEGfile);
			if (createRawfile)
			{
				printf("\nRAW file was written: %s", outputRAWfile);
			}
		}

		//JPEG Analysis block
		analyseNewJPEG (outputJPEGfile, outputRAWfile, inputRAWfile, outputImageWidth, outputImageHeight, numberOfComponents);
		printf("\n");
	}

}