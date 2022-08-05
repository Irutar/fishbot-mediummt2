#ifndef TEXTRECOGNITION_H
#define TEXTRECOGNITION_H

#include <iostream>
#include <memory>
#include <baseapi.h>
#include <allheaders.h>
#include <fstream>
#include <regex>
#include <string>
#include <vector>

void moveTextFromImageToFile(const char* sourceImage, const char* fileName);
char getTextFromImages(const char* sourceImage);
int numberOfSpacesToPress(const char* file, int correctLineNumber);
std::string checkAnimationType(const char* file);

#endif
