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
    //open file and checks if file exists
    pfile = fopen(argv[2], "r");
    if (!pfile){
        fprintf(stderr, "File not found.");
    }
    //Checks for valid format of said file
    fscanf(pfile, "%s", format);
    if (format[0] != 'P' || (format[1] != '3' && format[1] != '6')) {
        fprintf(stderr, "Please use a P3 or a P6 image", argv[2]);
    }
    
}