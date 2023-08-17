//
//  main.cpp
//  Project 2 - Image Processing
//
//  Created by David Denis on 3/20/23.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <string>
#include <ctype.h>
#include "image.h"
#include "methods.h"
using namespace std;



int main(int argc, char* argv[])
{
    
    map<string, int> methods;
    initialize_map(methods);
    

    if((argc < 2) or (strcmp(argv[1], "--help") == 0))
    {
        cout << "Project 2: Image Processing, Spring 2023" << "\n"
                 << "\n"
                 << "Usage:" << "\n"
                 << "\t./project2.out [output] [firstImage] [method] [...]"
                 << endl;
        
            return 0;
    }
    
    string file_out = argv[1];
    if(!file_correct_format(file_out))
    {
        cout << "Invalid file name." << endl;
        return 0;
    }
    
    string file_in = argv[2];
    if(file_correct_format(file_in))
    {
        if(check_file_exists(file_in))
        {
            
        }
        else
        {
            cout << "File does not exist." << endl;
            return 0;
        }
    }
    else
    {
        cout << "Invalid file name." << endl;
        return 0;
    }
    
    Image bot(file_out, file_in);
    
    for(int i = 3; i < argc; i++)
    {
        
        if(methods.find(argv[i]) != methods.end())
        {
            int method_args = methods[argv[i]];
            
            // Check Combine Method
            
            if((strcasecmp(argv[i], "combine") == 0))
            {
                if(!check_args(i, method_args, argc))
                    return 0;
                
                if(check_file_args(argv[++i]))
                {
                    Image green(argv[i]);
                    
                    if(check_file_args(argv[++i]))
                    {
                        Image blue(argv[i]);
                        bot.combine(green, blue);
                        
                    }
                    else
                        return 0;
                }
                else
                    return 0;
               
            
            }
            
            // Check Screen Method
            else if((strcasecmp(argv[i], "screen") == 0))
            {
                if(!check_args(i, method_args, argc))
                    return 0;
                
                if(check_file_args(argv[++i]))
                {
                    Image to_screen(argv [i]);
                    Screen(bot, to_screen);
                    
                    //i++;
                }
                else
                    return 0;
                
            }
            
            // Check Multiply Method
            else if((strcasecmp(argv[i], "multiply") == 0))
            {
                if(!check_args(i, method_args, argc))
                    return 0;
                
                if(check_file_args(argv[++i]))
                {
                    Image to_multiply(argv[i]);
                    Multiply(bot, to_multiply);
                    //i++;
                }
                else
                    return 0;
            }
            
            // Check Overlay Method
            else if((strcasecmp(argv[i], "overlay") == 0))
            {
                if(!check_args(i, method_args, argc))
                    return 0;
                
               if(check_file_args(argv[++i]))
               {
                   Image to_overlay(argv[i]);
                   Overlay(bot, to_overlay);
                   //i++;
               }
               else
                   return 0;
                
            }
            
            // Check Subtract Method
            else if((strcasecmp(argv[i], "subtract") == 0))
            {
                if(!check_args(i, method_args, argc))
                    return 0;
                
                if(check_file_args(argv[++i]))
                {
                    Image to_subtract(argv[i]);
                    Subtract(bot, to_subtract);
                   // i++;
                }
                else
                    return 0;
                   
            }
            
            // Check Add Red Method
            else if((strcasecmp(argv[i], "addred") == 0))
            {
                if(!check_args(i, method_args, argc))
                    return 0;
                
                if(check_file_args( argv[++i], true))
                {
                    int num = stoi(argv[i]);
                    bot.addred(num);
                    
                    //i++;
                }
                else
                    return 0;
                
            }
            
            // Check Add Green Method
            else if((strcasecmp(argv[i], "addgreen") == 0))
            {
                if(!check_args(i, method_args, argc))
                    return 0;
                
                if(check_file_args(argv[++i], true))
                {
                    int num = stoi(argv[i]);
                    bot.addgreen(num);
                    
                    //i++;
                }
                else
                    return 0;
            }
            
            // Check Add Blue Method
            else if((strcasecmp(argv[i], "addblue") == 0))
            {
                if(!check_args(i, method_args, argc))
                    return 0;
                
                if(check_file_args(argv[++i], true))
                {
                    int num = stoi(argv[i]);
                    bot.addblue(num);
                    
                    //i++;
                }
                else
                    return 0;
                
            }
            
            // Check Scale Red Method
            else if((strcasecmp(argv[i], "scalered") == 0))
            {
                if(!check_args(i, method_args, argc))
                    return 0;
                
                if(check_file_args(argv[++i], true))
                {
                    int num = stoi(argv[i]);
                    bot.scalered(num);
                    
                   //i++;
                }
                else
                    return 0;
                
            }
            
            // Check Scale Green Method
            else if((strcasecmp(argv[i], "scalegreen") == 0))
            {
                if(!check_args(i, method_args, argc))
                    return 0;
                
                if(check_file_args(argv[++i], true))
                {
                    int num = stoi(argv[i]);
                    bot.scalegreen(num);
                    
                    //i++;
                }
                else
                    return 0;
            }
                
            
            // Check Scale Blue Method
            else if((strcasecmp(argv[i], "scaleblue") == 0))
            {
                if(!check_args(i, method_args, argc))
                    return 0;
                
                if(check_file_args(argv[++i], true))
                {
                    int num = stoi(argv[i]);
                    bot.scaleblue(num);
                    
                    //i++;
                }
                else
                    return 0;
                
            }
            
            // Check Only Red Method
            else if((strcasecmp(argv[i], "onlyred") == 0))
            {
                bot.onlyred();
            }
            
            // Check Only Green Method
            else if((strcasecmp(argv[i], "onlygreen") == 0))
            {
                bot.onlygreen();
            }
            
            // Check Only Blue Method
            else if((strcasecmp(argv[i], "onlyblue") == 0))
            {
                bot.onlyblue();
            }
            
            // Check Flip Method
            else if((strcasecmp(argv[i], "flip") == 0))
            {
                bot.flip();
            }
        }
        else
        {
            cout << "Invalid method name." << endl;
            return 0;
        }
        
    }
    
    //cout << "... and saving output to " << file_out << "!" << endl;
    
    bot.writeFile();
    
    
    return 0;
}



