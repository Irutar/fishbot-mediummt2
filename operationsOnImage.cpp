#include "operationsOnImage.h"




void operationsOnImage::find(const char* sourceImage, const char* imageToFind)
{

	cv::Mat img = cv::imread(sourceImage);
	cv::Mat temp = cv::imread(imageToFind);

	cv::Mat templ;

	int result_cols = img.cols - templ.cols + 1;
	int result_rows = img.rows - templ.rows + 1;

	cv::Mat result;
	result.create(result_rows, result_cols, CV_32FC1);


	matchTemplate(img, temp, result, CV_TM_CCORR_NORMED);


	/// Localizing the best match with minMaxLoc
	double minVal; double maxVal; cv::Point minLoc; cv::Point maxLoc;



	minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, cv::Mat());

	values = { maxLoc.x, maxLoc.y, maxVal };

}


void preapareImageToReadText(const char* sourceImage, const char* outputImage, int resizeValue) {


	cv::Mat img = cv::imread(sourceImage);

	//Image to black and white
	cv::Mat grayMat;
	cvtColor(img, grayMat, cv::COLOR_RGB2GRAY);


	//scaling picture 2 times
	cv::Mat resize;
	cv::resize(grayMat, resize, cv::Size(), resizeValue, resizeValue, cv::INTER_CUBIC);
	//cv::cvtColor(resize, resize, CV_BGR2RGBA, 4);


	//segmentation method
	cv::Mat threshhold;
	cv::threshold(resize, threshhold, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
	cv::imwrite("images/threshhold.png", threshhold);

	threshhold = cv::imread("images/threshhold.png");

	//Bluring
	cv::Mat medianBlur;
	cv::medianBlur(threshhold, medianBlur, 1);
	cv::imwrite("images/medianBlur.png", medianBlur);


	medianBlur = cv::imread("images/medianBlur.png");

	//Sharpening
	cv::Mat bilateralFilter;
	cv::bilateralFilter(medianBlur, bilateralFilter, 7, 55, 55);

	//inverting black and white
	cv::Mat bitwise_not;
	cv::bitwise_not(bilateralFilter, bitwise_not);
	cv::imwrite("images/bitwise_not.png", bitwise_not);

	


	cv::imwrite(outputImage, bitwise_not);
}


void clickEmotion(const char* filePath, int metinWindowNumber) {
	SetCursorPos(0, 0);
	findAllImages emocja;
	Sleep(50);
	fullScreenShot("images/fullScreen.png");
	Sleep(50);
	emocja.find("images/fullScreen.png", filePath, 0.99, 100);
	SetCursorPos(emocja.coordy[metinWindowNumber].x + 10, emocja.coordy[metinWindowNumber].y + 10);
	Sleep(50);
	mouseRightButtonClick();
	Sleep(50);
}


void lookForEmotions(const char* filePath, int metinWindowNumber) {
	std::string x;


	x = checkAnimationType(filePath);

	std::cout << x << std::endl;
	if ((x == "Klaszcz") || (x == "klaszcz")) {
		clickEmotion("files/klaszcz.png", metinWindowNumber);
	}
	else if ((x == "wybaczy") || (x == "Wybaczy")) {
		clickEmotion("files/wybaczyc.png", metinWindowNumber);
	}
	else if ((x == "Denerwowa") || (x == "denerwowa")) {
		clickEmotion("files/denerwowac.png", metinWindowNumber);
	}
	else if ((x == "Smutek") || (x == "smutek")) {
		clickEmotion("files/smutek.png", metinWindowNumber);
	}
	else if ((x == "Odmowa") || (x == "odmowa")) {
		clickEmotion("files/odmowa.png", metinWindowNumber);
	}
	else if ((x == "Drwi") || (x == "drwi")) {
		clickEmotion("files/drwic.png", metinWindowNumber);
	}
	else if ((x == "Zgoda") || (x == "zgoda")) {
		clickEmotion("files/zgoda.png", metinWindowNumber);
	}
	else if ((x == "Rozwesela") || x == ("rozwesela")) {
		clickEmotion("files/rozweselac.png", metinWindowNumber);
	}
	else if ((x == "Rado") || (x == "rado")) {
		clickEmotion("files/radosc.png", metinWindowNumber);
	}
	else if ((x == "Powitanie 1") || (x == "powitanie 1")) {
		clickEmotion("files/powitanie1.png", metinWindowNumber);
	}
	else if ((x == "Powitanie 2") || (x == "powitanie 2")) {
		clickEmotion("files/powitanie2.png", metinWindowNumber);
	}
	else if ((x == "Taniec 1") || (x == "taniec 1")) {
		clickEmotion("files/taniec1.png", metinWindowNumber);
	}
	else if ((x == "Taniec 2") || (x == "taniec 2")) {
		clickEmotion("files/taniec2.png", metinWindowNumber);
	}
	else if ((x == "Taniec 3") || (x == "taniec 3")) {
		clickEmotion("files/taniec3.png", metinWindowNumber);
	}
	else if ((x == "Taniec 4") || (x == "taniec 4")) {
		clickEmotion("files/taniec4.png", metinWindowNumber);
	}
	else if ((x == "Taniec 5") || (x == "taniec 5")) {
		clickEmotion("files/taniec5.png", metinWindowNumber);
	}
	else if ((x == "Gumsan Style") || (x == "Gumsan style") || (x == "gumsan Style") || (x == "gumsan style")) {
		clickEmotion("files/taniec6.png", metinWindowNumber);
	}
	else if ((x == "Uwodzi") || (x == "uwodzi")) {
		clickEmotion("files/uwodzic.png", metinWindowNumber);
	}

	/*
	if (x != "nic") {
		operationsOnImage robak;
		operationsOnImage lowienie;
		robak.find("images/fullscreen.png", "files/robak.png");
		lowienie.find("images/fullscreen.png", "files/lowienie.png");
		SetCursorPos(robak.values.x + 10, robak.values.y + 10);
		Sleep(50);
		mouseRightButtonClick();
		SetCursorPos(lowienie.values.x + 10, lowienie.values.y + 10);
		Sleep(50);
		mouseRightButtonClick();


	}
	*/
}


void findAllImages::find(const char* sourceImage, const char* imageToFind, double threshold, int distanceToIgnore) {


	cv::Mat img = cv::imread(sourceImage);
	cv::Mat templ = cv::imread(imageToFind);


	cv::Mat img_gray;
	cv::Mat templ_gray;
	cv::cvtColor(img, img_gray, cv::COLOR_RGB2GRAY);
	cv::cvtColor(templ, templ_gray, cv::COLOR_RGB2GRAY);


	cv::Mat result;
	cv::matchTemplate(img_gray, templ_gray, result, cv::TM_CCOEFF_NORMED);

	cv::Mat result1;
	cv::threshold(result, result1, threshold, 1, cv::THRESH_BINARY);


	cv::Mat resb;
	result1.convertTo(resb, CV_8U, 255);


	std::vector<std::vector<cv::Point>> contours;
	cv::findContours(resb, contours, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);


	cv::Point x2;

	int x5;
	int y5;

	//std::vector<pozycje> coordy;
	if (contours.size()) {


		for (int i = 0; i < contours.size(); ++i)
		{
			x2 = contours[i][0];

			x5 = x2.x;
			y5 = x2.y;


			coordy.push_back(pozycje());
			coordy[i].x = x5;
			coordy[i].y = y5;
		}


		bool swapped;

		for (int i = 0; i < coordy.size() - 1; i++)
		{
			swapped = false;
			for (int j = 0; j < coordy.size() - i - 1; j++)
			{
				if (coordy[j].y > coordy[j + 1].y)
				{
					std::swap(coordy[j], coordy[j + 1]);

					swapped = true;
				}
			}
			if (swapped == false)
				break;
		}



		std::vector<int> row;

		int cos;
		int j = 0;
		while (j < coordy.size()) {
			int nmbOfY = 0;



			cos = coordy[j].y;

			for (int i = 0; i < coordy.size(); i++) {
				if ((cos >= (coordy[i].y - distanceToIgnore)) && ((cos - distanceToIgnore) <= coordy[i].y))
					nmbOfY++;
			}

			row.push_back(nmbOfY);
			j += nmbOfY;


		}

		int nmbOfCheckedY = 0;



		for (int z = 0; z < row.size(); z++) {
			for (int i = 0; i < row[z] - 1; i++)
			{

				swapped = false;
				for (int j = 0; j < row[z] - i - 1; j++)
				{


					if (coordy[nmbOfCheckedY + j].x > coordy[nmbOfCheckedY + j + 1].x)
					{


						std::swap(coordy[nmbOfCheckedY + j], coordy[nmbOfCheckedY + j + 1]);



						swapped = true;
					}

				}
				if (swapped == false)
					break;
			}
			nmbOfCheckedY += row[z];

		}
	}


}

void linkImages(int numberOfImages, const char* imageName, const char* finalImageName) {



	char filename[64];
	int i = 0;
	remove(finalImageName);
	if (numberOfImages == 1) {
		int i = 0;

		sprintf(filename, imageName, i);
		cv::Mat3b img1 = cv::imread(filename);


		cv::imwrite(finalImageName, img1);


	}
	else {





		sprintf(filename, imageName, i);
		cv::Mat3b img1 = cv::imread(filename);


		for (i = 1; i < numberOfImages; i++) {
			sprintf(filename, imageName, i);

			// Load images
			cv::Mat3b img2 = cv::imread(filename);

			// Get dimension of final image
			int rows = img1.rows + img2.rows;
			int cols = img1.cols;

			// Create a black image
			cv::Mat3b res(rows, cols, cv::Vec3b(0, 0, 0));

			// Copy images in correct position
			img1.copyTo(res(cv::Rect(0, 0, img1.cols, img1.rows)));
			img2.copyTo(res(cv::Rect(0, img1.rows, img2.cols, img2.rows)));


			cv::imwrite(finalImageName, res);
			img1 = cv::imread(finalImageName);
		}
	}
}


void changeImageToBlackImage(const char* imageName) {

	cv::Mat3b img1 = cv::imread(imageName);

	cv::Mat3b res(img1.rows, img1.cols, cv::Vec3b(0, 0, 0));

	cv::imwrite(imageName, res);

}