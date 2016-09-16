/* 
 * File:   main.c
 * Author: David
 *
 * Created on September 14, 2016, 10:51 AM
 */

#include <stdio.h>
#include <stdlib.h>
#define channel_size 255


typedef struct{
    char r;
    char g;
    char b;
} Pixel;
FILE* pfile;
FILE* outputfile;
int h,w;
char format[8];
unsigned char* Data;
int colormax;
char height[8];
char width[8];
char maxcolor[8];
void buffer();

void main(int argc, char* argv[]) {
    //check for proper arguments
    if (argc != 4) {
        fprintf(stderr, "Please put the commands in the following format: format, source file, destination file.");
    }
    