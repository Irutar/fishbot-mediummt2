#ifndef OPERATIONSONIMAGE_H
#define OPERATIONSONIMAGE_H

#include<opencv2/opencv.hpp>
#include<iostream>
#include "ScreenShot.h"
#include "mouseAndKeyboard.h"
#include "textRecognition.h"
#include <chrono> 



class operationsOnImage {


public:
	struct val {
		int x;
		int y;
		double maxValue;
	}values;


	void find(const char* sourceImage, const char* imageToFind);


};


class findAllImages {
public:

	struct pozycje {
		int x;
		int y;
		std::chrono::high_resolution_clock::time_point time;
		bool waiting;

		pozycje() {
			x = 0;
			y = 0;
			time = std::chrono::high_resolution_clock::now();
			waiting = false;
		}
	};

	std::vector<pozycje> coordy;

	void find(const char* sourceImage, const char* imageToFind, double threshold, int distanceToIgnore);

};

void preapareImageToReadText(const char* sourceImage, const char* outputImage, int resizeValue);
void clickEmotion(const char* filePath, int metinWindowNumber);
void lookForEmotions(const char* filePath, int metinWindowNumber);
void linkImages(int numberOfImages, const char* imageName, const char* finalImageName);
void changeImageToBlackImage(const char* imageName);

#endif
