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
    //checks if file has a valid height and width above 0
    fscanf(pfile, "%s %s", height, width);
    h = atoi(height);
    w = atoi(width);
    if (h <= 0 || w <= 0) {
        fprintf(stderr, "Error: Invalid dimensions.");
    }
    //checks to make sure color bit size is 8 bits
    fscanf(pfile, "%s", maxcolor);
    colormax = atoi(maxcolor);
    if (colormax != channel_size) {
        fprintf(stderr, "Error: Channel size must be 8 bits.");
    }
    //check file then go to buffer to store data
    printf("%s\n", format);
    buffer();
    //close file
    fclose (pfile);
    //open output file or creates it if it does not exist
    outputfile = fopen(argv[3],"w");
    //chooses which format to output as
    if(atoi(argv[1])=='3'){
        //Outputs file parameters to a p3 data which uses the conversion to make it into ASCII code
        fprintf(outputfile, "P3\n");
        fprintf(outputfile, "%s %s\n", height, width);
        fprintf(outputfile, "%s\n", maxcolor);
        for(int i=0; i<(sizeof(Pixel)*h*w); i++){
            fprintf(outputfile, "%d\n", Data[i]);
        }
    }else{
        //Outputs file parameters to a p6 data
        fprintf(outputfile, "P6\n");
        fprintf(outputfile, "%s %s\n", height, width);
        fprintf(outputfile, "%s\n", maxcolor);
        fwrite(Data, sizeof(Pixel), h*w, outputfile);
    }
    fclose(outputfile);
    
}

//makes the buffer
void buffer(){
    Data = malloc(sizeof(Pixel)*h*w);
    //this converts a p3 format into ASCII data
    if (format[1] == '3') {
        char temp[3];
        for(int i=0; i<(sizeof(Pixel)*h*w); i++) {
            fscanf(pfile, "%s", temp);
            Data[i] = (char)atoi(temp);
        }
        
    } else {
        //remains AsSCII as a p6
        fscanf(pfile, "%s", Data);
    }
}