//
//  image.h
//  Project 2 - Image Processing
//
//  Created by David Denis on 3/20/23.
//


#define image_h
#pragma once

#include <iostream>
#include <fstream>
#include <vector>
//#include "methods.h"
using namespace std;

struct Image {
  
    struct Header
    {
        char idLength;
        char colorMapType;
        char dataTypeCode;
        short colorMapOrigin;
        short colorMapLength;
        char colorMapDepth;
        short xOrigin;
        short yOrigin;
        short width;
        short height;
        char bitsPerPixel;
        char imageDescriptor;
    };
   
    
    int image_size;
    vector<vector<unsigned char> > imageData;
    Header head;
    string input_file;
    string output_file;
    
    
    Image();                                        // Default constructor
    Image(string in_file);                          // This costructor reads the passed file to combine it with others
    Image(string out_file, string in_file);         // This constructor takes in a file, modifiies it and stores the name of the output file to return
    
    
    // BIG 3
    
    Image(const Image& d);
    Image& operator=(const Image& d);
    ~Image();
    
    
    void readFile();
    void writeFile();
    
    // **** Additional Tasks ****
    
    void addred(int red);
    void addgreen(int green);
    void addblue(int blue);

    void scalered(int red);
    void scalegreen(int green);
    void scaleblue(int blue);

    void onlyred();
    void onlygreen();
    void onlyblue();

    void flip();
    
    void combine(Image &green, Image &blue);
};
