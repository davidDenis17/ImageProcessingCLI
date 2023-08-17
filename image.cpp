//
//  image.cpp
//  Project 2 - Image Processing
//
//  Created by David Denis on 3/20/23.
//

#include <stdio.h>
#include "image.h"
#include "methods.h"

                                                                                            // ******* CONSTRUCTION / DESTRUCTION *******

Image:: Image()
{
    
}

Image:: Image(const Image &d)
{
    output_file = d.output_file;
    image_size = d.image_size;
    head.idLength = d.head.idLength;
    head.colorMapType = d.head.colorMapType;
    head.dataTypeCode = d.head.dataTypeCode;
    head.colorMapOrigin = d.head.colorMapOrigin;
    head.colorMapDepth = d.head.colorMapDepth;
    head.xOrigin = d.head.xOrigin;
    head.yOrigin = d.head.yOrigin;
    head.width = d.head.width;
    head.height = d.head.height;
    head.bitsPerPixel = d.head.bitsPerPixel;
    head.imageDescriptor = d.head.imageDescriptor;
    
    image_size = d.image_size;
    imageData.resize(image_size);
    
    for(int i = 0; i < image_size; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            imageData[i].push_back(d.imageData[i][j]);
        }
    }
    
}

Image& Image::operator=(const Image &d)
{
    output_file = d.output_file;
    image_size = d.image_size;
    head.idLength = d.head.idLength;
    head.colorMapType = d.head.colorMapType;
    head.dataTypeCode = d.head.dataTypeCode;
    head.colorMapOrigin = d.head.colorMapOrigin;
    head.colorMapDepth = d.head.colorMapDepth;
    head.xOrigin = d.head.xOrigin;
    head.yOrigin = d.head.yOrigin;
    head.width = d.head.width;
    head.height = d.head.height;
    head.bitsPerPixel = d.head.bitsPerPixel;
    head.imageDescriptor = d.head.imageDescriptor;
    
    image_size = d.image_size;
    imageData.resize(image_size);
    
    for(int i = 0; i < image_size; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            imageData[i].push_back(d.imageData[i][j]);
        }
    }
    
    return *this;
}

Image:: ~Image()
{
    
}


Image:: Image(string out_file, string in_file)
{
    
    input_file = in_file;                                                         // directory + file name
    output_file = out_file;                                                      // directory + desired file name
    
    readFile();                                                                              // read file automatically
}


Image:: Image(string in_file)
{
    input_file = in_file;                                                         // directory + file name
    readFile();
}


                                                                                            // ******** READ / WRITE *******

// reads passed file
void Image:: readFile()
{
    fstream readFile(input_file, ios_base::in | ios_base::binary);                           // read entire file
    
    char idLength;
    readFile.read((char*)(&idLength), 1);
    head.idLength = idLength;
    
    char colorMapType;
    readFile.read((char*)(&colorMapType), 1);
    head.colorMapType = colorMapType;
    
    char dataTypeCode;
    readFile.read((char*)(&dataTypeCode), 1);
    head.dataTypeCode = dataTypeCode;
    
    short colorMapOrigin;
    readFile.read((char*)(&colorMapOrigin), 2);
    head.colorMapOrigin = colorMapOrigin;
    
    short ColorMapLength;
    readFile.read((char*)(&ColorMapLength), 2);
    head.colorMapLength = ColorMapLength;
    
    char colorMapDepth;
    readFile.read((char*)(&colorMapDepth), 1);
    head.colorMapDepth = colorMapDepth;
    
    short xOrigin;
    readFile.read((char*)(&xOrigin), 2);
    head.xOrigin = xOrigin;
    
    short yOrigin;
    readFile.read((char*)(&yOrigin), 2);
    head.yOrigin = yOrigin;
    
    short width;
    readFile.read((char*)(&width), 2);
    head.width = width;
    
    short height;
    readFile.read((char*)(&height), 2);
    head.height = height;
    
    char bitsPerPixel;
    readFile.read((char*)(&bitsPerPixel), 1);
    head.bitsPerPixel = bitsPerPixel;
    
    char imageDescriptor;
    readFile.read((char*)(&imageDescriptor), 1);
    head.imageDescriptor = imageDescriptor;
    
    image_size = head.width * head.height;                                                  // compute image size
    
    imageData.resize(image_size);                                                           // set vector size to image size
    
    for(int i =  0; i < image_size; i++)
    {
        for(int j = 0; j < 3; j++)                                                          // push back each value for each pixel (B G R)
        {
            unsigned char value;
            readFile.read((char*)(&value), 1);
            imageData[i].push_back(value);
        }
    }
}


// writes out modified file
void Image::writeFile()
{
    // write complete file
    
    fstream outFile(output_file, ios_base::out | ios_base::binary);
    
    outFile.write((char*)(&head.idLength), sizeof(head.idLength));
    outFile.write((char*)(&head.colorMapType), sizeof(head.colorMapType));
    outFile.write((char*)(&head.dataTypeCode), sizeof(head.dataTypeCode));
    outFile.write((char*)(&head.colorMapOrigin), sizeof(head.colorMapOrigin));
    outFile.write((char*)(&head.colorMapLength), sizeof(head.colorMapLength));
    outFile.write((char*)(&head.colorMapDepth), sizeof(head.colorMapDepth));
    outFile.write((char*)(&head.xOrigin), sizeof(head.xOrigin));
    outFile.write((char*)(&head.yOrigin), sizeof(head.yOrigin));
    outFile.write((char*)(&head.width), sizeof(head.width));
    outFile.write((char*)(&head.height), sizeof(head.height));
    outFile.write((char*)(&head.bitsPerPixel), sizeof(head.bitsPerPixel));
    outFile.write((char*)(&head.imageDescriptor), sizeof(head.imageDescriptor));
    
    for(int i = 0; i < image_size; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            outFile.write((char*)(&imageData[i][j]), sizeof(imageData[i][j]));
        }
    }
}



                                                                                            // ******* Additional Tasks *******


// Additions

void Image:: addred(int red)
{
    for(int i = 0; i < image_size; i++)
    {
        imageData[i][2] = (unsigned char) (clampValue(imageData[i][2] + red));
    }

}

void Image:: addgreen(int green)
{
    for(int i = 0; i < image_size; i++)
    {
        imageData[i][1] = (unsigned char) (clampValue(imageData[i][1] + green));
    }

}

void Image:: addblue(int blue)
{
    for(int i = 0; i < image_size; i++)
    {
        imageData[i][0] = (unsigned char) (clampValue(imageData[i][0] + blue));
    }

}


// Scaling

void Image:: scalered(int red)
{
    
    for(int i = 0; i < image_size; i++)
    {
        imageData[i][2] = (unsigned char)(clampValue(((normalize(imageData[i][2]) * red) * 255) + 0.5f));
    }
    
}

void Image:: scalegreen(int green)
{
    
    for(int i = 0; i < image_size; i++)
    {
        imageData[i][1] = (unsigned char)(clampValue(((normalize(imageData[i][1]) * green) * 255) + 0.5f));
    }
    
}

void Image:: scaleblue(int blue)
{
    
    for(int i = 0; i < image_size; i++)
    {
        imageData[i][0] = (unsigned char)(clampValue(((normalize(imageData[i][0]) * blue) * 255) + 0.5f));
    }
    
}


// Only Channels

void Image:: onlyred()
{
    for(int i = 0; i < image_size; i++)
    {
        // All Channels to Red
        imageData[i][0] = (imageData[i][2]);
        imageData[i][1] = (imageData[i][2]);
        imageData[i][2] = (imageData[i][2]);
    }
}

void Image:: onlygreen()
{
    for(int i = 0; i < image_size; i++)
    {
        // All Channels to Green
        imageData[i][0] = imageData[i][1];
        imageData[i][1] = imageData[i][1];
        imageData[i][2] = imageData[i][1];
    }
}

void Image:: onlyblue()
{
    for(int i = 0; i < image_size; i++)
    {
        // All Channels to Blue
        imageData[i][0] = imageData[i][0];
        imageData[i][1] = imageData[i][0];
        imageData[i][2] = imageData[i][0];
    }
}


// Flip

void Image:: flip()
{
    int count = 0;
    
    vector<vector<unsigned char> > dataCopy;
    dataCopy.resize(image_size);
    
    
    
    for(int i = 0; i < image_size; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            dataCopy[i].push_back(imageData[i][j]);
        }
    }
    
    
    for(int i = image_size - 1; i > -1; --i)
    {
        imageData[i][0] = dataCopy[count][0];
        imageData[i][1] = dataCopy[count][1];
        imageData[i][2] = dataCopy[count][2];
        
        count++;
    }
    
}


// Combine

void Image:: combine(Image &green, Image &blue)
{
    for(int i = 0; i < image_size; i++)
    {
        imageData[i][0] = blue.imageData[i][0];
        imageData[i][1] = green.imageData[i][1];
        
    }
}
