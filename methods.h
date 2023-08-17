//
//  methods.h
//  Project 2 - Image Processing
//
//  Created by David Denis on 3/20/23.
//

#define methods_h
#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <unordered_map>
#include "image.h"

using namespace std;

float normalize(float value);
int clampValue(int value);

void Multiply(Image &topLayer, Image &bottomLayer);
void Screen(Image &topLayer, Image &bottomLayer);
void Subtract(Image &topLayer, Image &bottomLayer);
void Overlay(Image &topLayer, Image &bottomLayer);

// **** TASKS ****

void task1();
void task2();
void task3();
void task4();
void task5();
void task6();
void task7();
void task8();
void task9();
void task10();


// **** Additional Methods ****

void initialize_map(map<string, int> &map);
bool check_file_exists(string file_to_check);
bool file_correct_format(string file);
bool digit_conversion(string str);

bool check_file_args(string file, bool num = false);
bool check_args(int i, int n_args, int argc);
