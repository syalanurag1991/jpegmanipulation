The program JPEG_PART_A.exe helps in understanding how quantization in JEPG works.
Typical usage:
JPEG_PART_A.exe walter.raw

It does NOT create any output, however the results are dsiplayed on the terminal
and be redirected to a text file using the > operator.
Example
JPEG_PART_A.exe walter.raw > results.txt

1. The program takes the input RAW file.
2. Breaks the input image into blocks of 8x8 and dsiplays them.
3. 1) Displays the Baseline JPEG Quantization Matrix.
   2) Quantizes the blocks by performing an element by element division
      with the Baseline JPEG Quantization Matrix.
   3) Displays the quantized blocks.
4. 1) Displays the JPEG Quantization Matrix for a given quality factor.
   2) Quantizes the blocks by performing an element by element division
      with the JPEG Quantization Matrix for the given quality factor.
   3) Displays the quantized blocks.