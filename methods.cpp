//
//  methods.cpp
//  Project 2 - Image Processing
//
//  Created by David Denis on 3/20/23.
//
//  P1 is top layer --- P2 is bottom layer --- N stands for normalize function
//

#include <stdio.h>
#include "methods.h"


float normalize(float value)
{
    return (value / 255.0);
}

int clampValue(int value)
{
    if(value <= 0)
        return 0;
    else if (value >= 255)
        return 255;
    
    return value;
}



/*
    Implements this formula
    NP1·NP2
 */

void Multiply(Image &topLayer, Image &bottomLayer)
{
    for(int i = 0; i < topLayer.image_size; i++)
    {
        topLayer.imageData[i][0] = (unsigned char)((((normalize((topLayer.imageData[i][0])) * (normalize((bottomLayer.imageData[i][0])))) * 255) + 0.5f)  );                 // Blue Channel
        topLayer.imageData[i][1] = (unsigned char)((((normalize((topLayer.imageData[i][1])) * (normalize((bottomLayer.imageData[i][1])))) * 255) + 0.5f)  );                 // Green Channel
        topLayer.imageData[i][2] = (unsigned char)((((normalize((topLayer.imageData[i][2])) * (normalize((bottomLayer.imageData[i][2])))) * 255) + 0.5f)  );                 // Red Channel
        
    }
}



/*
    Implements this formula
    1−[(1−NP1)·(1−NP2)]
 */

void Screen(Image &topLayer, Image &bottomLayer)
{
    for(int i = 0; i < topLayer.image_size; i++)
    {
        topLayer.imageData[i][0] = (unsigned char)(clampValue(((1 - ((1 - (normalize((topLayer.imageData[i][0])))) * (1 - (normalize((bottomLayer.imageData[i][0])))))) * 255) + 0.5f));      // Blue Channel
        topLayer.imageData[i][1] = (unsigned char)(clampValue(((1 - ((1 - (normalize((topLayer.imageData[i][1])))) * (1 - (normalize((bottomLayer.imageData[i][1])))))) * 255) + 0.5f));      // Green Channel
        topLayer.imageData[i][2] = (unsigned char)(clampValue(((1 - ((1 - (normalize((topLayer.imageData[i][2])))) * (1 - (normalize((bottomLayer.imageData[i][2])))))) * 255) + 0.5f));      // Red Channel
        
    }
}



/*
    Implements this formula
    P1−P2
 */

void Subtract(Image &bottomLayer, Image &topLayer)
{
    for(int i = 0; i < topLayer.image_size; i++)
    {
        bottomLayer.imageData[i][0] = (unsigned char)(clampValue(bottomLayer.imageData[i][0] - topLayer.imageData[i][0]));     // Blue Channel
        bottomLayer.imageData[i][1] = (unsigned char)(clampValue(bottomLayer.imageData[i][1] - topLayer.imageData[i][1]));     // Green Channel
        bottomLayer.imageData[i][2] = (unsigned char)(clampValue(bottomLayer.imageData[i][2] - topLayer.imageData[i][2]));     // Red Channel
    }
}




/*
    Implements this formula (P1 is top layer, P2 is bottom layer) (N is normalize)
    NP2 ≤ 0.5: 2·NP1 ·NP2
    NP2 > 0.5: 1−[2·(1−NP1)·(1−NP2)]
 */

void Overlay(Image &topLayer, Image &bottomLayer)
{
    //vector<float> NP1;
    //vector<float> NP2;
    
    float NP1;
    float NP2;
    
    for(int i = 0; i < topLayer.image_size; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            NP1 = normalize(topLayer.imageData[i][j]);
            NP2 = normalize(bottomLayer.imageData[i][j]);
            
            if(NP2 <= 0.5)
            {
                topLayer.imageData[i][j] = clampValue((2 * NP1 * NP2) * 255 + 0.5f);
            }
            else
            {
                topLayer.imageData[i][j] = clampValue(((1 - (2 * (1 - NP1) * (1 - NP2)))) * 255 + 0.5f);
            }
        }
        
        
        
    }
}


// ************ TASKS ************

void task1()
{
    Image image1("part1.tga", "layer1.tga");
    Image image2("pattern1.tga");
    Multiply(image1, image2);
    image1.writeFile();
}

void task2()
{
    // Test 2
    Image image3("layer2.tga");
    Image image4("part2.tga", "car.tga");
    
    Subtract(image4, image3);
    image4.writeFile();
}


void task3()
{
    // Test 3
    Image image5("layer1.tga");
    Image image6("pattern2.tga");
    Image image7("part3.tga", "text.tga");
    
    Multiply(image5, image6);
    Screen(image7, image5);
    
    image7.writeFile();
}

void task4()
{
    // Test 4
    Image image8("part4.tga", "layer2.tga");
    Image image9("circles.tga");
    
    Multiply(image8, image9);
    
    
    Image image10("pattern2.tga");
    
    Subtract(image8, image10);
    
    image8.writeFile();
}

void task5()
{
    Image image1("part5.tga", "layer1.tga");
    Image image2("pattern1.tga");
    
    Overlay(image1, image2);
    
    image1.writeFile();
}


void task6()
{
    Image image1("part6.tga", "car.tga");
    
    image1.addgreen(200);
    
    image1.writeFile();
}


void task7()
{
    Image image1("part7.tga", "car.tga");
    
    image1.scalered(4);
    image1.scaleblue(0);
    
    image1.writeFile();
}


void task8()
{
    Image imageB("part8_b.tga", "car.tga");
    Image imageG("part8_g.tga", "car.tga");
    Image imageR("part8_r.tga", "car.tga");
    
    imageB.onlyblue();
    imageG.onlygreen();
    imageR.onlyred();
    
    
    // Write Each File
    imageB.writeFile();
    imageG.writeFile();
    imageR.writeFile();
}


void task9()
{
    // Load required files
    Image layerR("part9.tga", "layer_red.tga");
    Image layerG("layer_green.tga");
    Image layerB("layer_blue.tga");
    
    layerR.combine(layerG, layerB);
    
    layerR.writeFile();
}


void task10()
{
    Image toFlip("text2.tga");
    toFlip.output_file = "output/part10.tga";
    
    toFlip.flip();
    
    toFlip.writeFile();
}



// **** Additional Methods ****

void initialize_map(map<string, int> &map)
{
    for(int i = 0; i < 15; ++i)
    {
        map.emplace("combine", 2);
        map.emplace("screen", 1);
        map.emplace("multiply", 1);
        map.emplace("subtract", 1);
        map.emplace("overlay", 1);
        
        map.emplace("addred", 1);
        map.emplace("addgreen", 1);
        map.emplace("addblue", 1);
        map.emplace("scalered", 1);
        map.emplace("scalegreen", 1);
        map.emplace("scaleblue", 1);
        
        map.emplace("onlyred", 0);
        map.emplace("onlygreen", 0);
        map.emplace("onlyblue", 0);
        map.emplace("flip", 0);
        
    }
}

bool check_file_exists(string file_to_check)
{
    string input = file_to_check;
    fstream file(input, ios_base::in | ios_base::binary);
    
    if (file.is_open())
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool file_correct_format(string file)
{
    string sub = ".tga";
    
    if(file.length() < sub.length())
    {
        return false;
    }
    return file.compare(file.length() - sub.length(), sub.length(), sub) == 0;
}

bool digit_conversion(string str)
{
    try
    {
        int num = stoi(str);
        
    }
    catch(invalid_argument)
    {
        cout << "Invalid argument, expected number." << endl;
        return false;
    }
    
    return true;
}

// takes in i (current iteration), file (name of file), n_args(necessary arguments for method), argc (number of total arguments given by the command line)
bool check_file_args(string file, bool num)
{
    
        if(num)
        {
            return digit_conversion(file);
        }
        else
        {
            if(file_correct_format(file))
            {
                if(check_file_exists(file))
                {
                    return true;
                }
                else
                {
                    cout << "Invalid argument, file does not exist." << endl;
                    return false;
                }
            }
            else
            {
                cout << "Invalid argument, invalid file name." << endl;
                return false;
            }
        }
}

bool check_args(int i, int n_args, int argc)
{
    if(i + n_args < argc)
    {
        return true;
    }
    else
    {
        cout << "Missing argument." << endl;
        return false;
    }
}
