// FishBot.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "operationsOnImage.h"
#include <chrono>
#include "mouseAndKeyboard.h"
#include "ScreenShot.h"


#define selectInfo 0
#define resizeDialogBox 1
#define moveDialogBox 0


#define SPACEBAR_DELAY 80
#define RESIZE_VALUE 2


void clickInfo(int x, int y) {
	SetCursorPos(x, y);
	Sleep(100);
	mouseLeftButtonClick();
}


void makeDialogBoxHigher(int x, int y) {
	SetCursorPos(x, y);
	Sleep(100);
	mouseLeftDown();
	Sleep(100);
	SetCursorPos(x, y + 12);
	Sleep(100);
	mouseLeftUp();
	Sleep(100);
}


void setupMetinScreen(findAllImages images) {
	for (int i = 0; i < images.coordy.size(); i++) {
		if (selectInfo) {
			clickInfo(images.coordy[i].x + +255, images.coordy[i].y - 14);
		}
		if (resizeDialogBox) {
			makeDialogBoxHigher(images.coordy[i].x + 428, images.coordy[i].y + 70);
		}
	}
}


void pressSpacebarXTimes(int nmbOfPresses) {
	int i;
	for (i = 0; i < nmbOfPresses; i++) {
		keyboardDirectXPress(0x39);
		Sleep(SPACEBAR_DELAY);
	}
}

void findNmbOfSpacesToClick(findAllImages imageWithLineNumbers, findAllImages &protokol, int numberOfLine) {
	int i;
	int metinWindowNumber;
	char filename[64];
	char filename2[64];



	for (i = 0; i < imageWithLineNumbers.coordy.size(); i++) {
		metinWindowNumber = imageWithLineNumbers.coordy[i].y / 60;  //60 jest wysokością jednego protokolu,

		SetCursorPos(protokol.coordy[metinWindowNumber].x, protokol.coordy[metinWindowNumber].y);
		Sleep(50);
		mouseRightButtonClick();

		sprintf(filename, "images/tylkoProtokol%d.png", metinWindowNumber);
		sprintf(filename2, "images/protokolDoOdczytu%d.png", metinWindowNumber);

		preapareImageToReadText(filename, filename2, 2);

		moveTextFromImageToFile(filename2, "files/textFromImage.txt");

		int presses;
		presses = numberOfSpacesToPress("files/textFromImage.txt", numberOfLine);

		std::cout << presses << std::endl;
		pressSpacebarXTimes(presses);

		protokol.coordy[metinWindowNumber].waiting = true;
		protokol.coordy[metinWindowNumber].time = std::chrono::high_resolution_clock::now();

		changeImageToBlackImage(filename);

	}
}





void putBait() {
	keyboardDirectXPress(0x03);
}


void startFishing() {
	keyboardDirectXPress(0x39);
}


void lookForMessages() {
	findAllImages message;
	SetCursorPos(0, 0);
	fullScreenShot("images/fullSS.png");
	message.find("images/fullSS.png", "images/message.png", 0.98, 5);

	if (message.coordy.size() > 0) {
		system("start files/slackMessage.exe");
	}
}

int main()
{	
	Sleep(5000);


	int i;
	char filename[64];
	
	auto start = std::chrono::high_resolution_clock::now();
	

	std::chrono::milliseconds timeToWaitBeforeBait;
	timeToWaitBeforeBait = std::chrono::milliseconds{ 10000 };

	std::chrono::milliseconds timeToCheckMessage;
	timeToCheckMessage = std::chrono::milliseconds{ 10000 };

	SetCursorPos(0, 0);
	fullScreenShot("images/fullSS.png");

	findAllImages protokolWiadomosci;
	protokolWiadomosci.find("images/fullSS.png", "images/protokolWiadomosci.png", 0.95, 100);
	
	for (i = 0; i < protokolWiadomosci.coordy.size(); i++) {
		protokolWiadomosci.coordy[i].x = protokolWiadomosci.coordy[i].x - 10;	//correction for dialog box
		protokolWiadomosci.coordy[i].y = protokolWiadomosci.coordy[i].y + 40;	//correction for dialog box
	}



	//system("start files/slackMessage.exe");

	setupMetinScreen(protokolWiadomosci);

	findAllImages pierwszy;
	findAllImages drugi;
	findAllImages trzeci;

	auto start4 = std::chrono::high_resolution_clock::now();

	while (1) {

		for (i = 0; i < protokolWiadomosci.coordy.size(); i++) {

			if (protokolWiadomosci.coordy[i].waiting == false) {
				sprintf(filename, "images/tylkoProtokol%d.png", i);
				ScreenShot(filename, protokolWiadomosci.coordy[i].x, protokolWiadomosci.coordy[i].y, protokolWiadomosci.coordy[i].x + 397, protokolWiadomosci.coordy[i].y + 60);
			}
		}

		linkImages(protokolWiadomosci.coordy.size(), "images/tylkoProtokol%d.png", "images/polaczoneProtokoly.png");

		preapareImageToReadText("images/polaczoneProtokoly.png", "images/polaczoneProtokolyDoOdczytu.png", 1);

		pierwszy.find("images/polaczoneProtokolyDoOdczytu.png", "files/pierwszy.png", 0.98, 0);
		drugi.find("images/polaczoneProtokolyDoOdczytu.png", "files/drugi.png", 0.98, 0);
		trzeci.find("images/polaczoneProtokolyDoOdczytu.png", "files/trzeci.png", 0.98, 0);

		if (pierwszy.coordy.size()) {
			findNmbOfSpacesToClick(pierwszy, protokolWiadomosci, 1);
		}
		if (drugi.coordy.size()) {
			findNmbOfSpacesToClick(drugi, protokolWiadomosci, 2);
		}
		if (trzeci.coordy.size()) {
			findNmbOfSpacesToClick(trzeci, protokolWiadomosci, 3);
		}


		for (i = 0; i < protokolWiadomosci.coordy.size(); i++) {
			auto stop1 = std::chrono::high_resolution_clock::now();
			
			auto duration1 = std::chrono::duration_cast<std::chrono::milliseconds>(stop1 - protokolWiadomosci.coordy[i].time);

			if ((duration1 > timeToWaitBeforeBait) && (protokolWiadomosci.coordy[i].waiting == true)) {

				SetCursorPos(protokolWiadomosci.coordy[i].x, protokolWiadomosci.coordy[i].y);
				Sleep(50);
				mouseRightButtonClick();

				Sleep(100);

				pressSpacebarXTimes(4);
				Sleep(100);
				putBait();
				Sleep(200);
				startFishing();

				protokolWiadomosci.coordy[i].waiting = false;
				protokolWiadomosci.coordy[i].time = std::chrono::high_resolution_clock::now();
			}


		}
		
		auto stop4 = std::chrono::high_resolution_clock::now();
		//Sleep(50);
		auto duration4 = std::chrono::duration_cast<std::chrono::milliseconds>(stop4 - start4);

		//sprawdzanie czy nie dostaliśmy jakiejś wiadomości
		if (duration4 > timeToCheckMessage) {
			lookForMessages();
			Sleep(300);
			lookForMessages();
			start4 = std::chrono::high_resolution_clock::now();
		}
		
		pierwszy.coordy.clear();
		drugi.coordy.clear();
		trzeci.coordy.clear();


	}


	auto finish = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> elapsed = finish - start;
	std::cout << elapsed.count() << std::endl;
	
	
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
