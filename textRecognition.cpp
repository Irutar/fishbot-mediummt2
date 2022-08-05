#include "textRecognition.h"

void moveTextFromImageToFile(const char* sourceImage, const char* fileName)
{
	char *outText;

	tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();
	// Initialize tesseract-ocr with English, without specifying tessdata path


	if (api->Init("./tessdata", "pol")) {
		fprintf(stderr, "Could not initialize tesseract.\n");
		exit(1);
	}

	// Open input image with leptonica library
	Pix *image = pixRead(sourceImage);
	api->SetImage(image);
	// Get OCR result
	outText = api->GetUTF8Text();



	std::ofstream file(fileName);
	file << outText;
	file.close();



	// Destroy used object and release memory
	api->End();

	pixDestroy(&image);


}


char getTextFromImages(const char* sourceImage) {
	char *outText;

	tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();
	// Initialize tesseract-ocr with English, without specifying tessdata path


	if (api->Init("./tessdata", "pol")) {
		fprintf(stderr, "Could not initialize tesseract.\n");
		exit(1);
	}

	// Open input image with leptonica library
	Pix *image = pixRead(sourceImage);
	api->SetImage(image);
	// Get OCR result
	outText = api->GetUTF8Text();

	// Destroy used object and release memory
	api->End();

	pixDestroy(&image);

	return *outText;
}


int numberOfSpacesToPress(const char* file, int correctLineNumber) {

	std::ifstream textFile(file);
	std::string line;
	std::regex wzorzec("[[:digit:]]");
	std::smatch wynik;

	int currentLineNumber = 0;

	while (getline(textFile, line)) {
		//std::cout << "dzialam" << std::endl;
		std::sregex_iterator next(line.begin(), line.end(), wzorzec);
		
		std::sregex_iterator end;
		while (next != end) {


			std::smatch match = *next;
			next++;
			if (next == end) {
				currentLineNumber++;
				if (currentLineNumber == correctLineNumber) {
					int temp;
					temp = std::stoi(match.str());
					return temp;
				}

			}
		}
	}

	return -1;


}


std::string checkAnimationType(const char* file) {

	std::ifstream textFile(file);
	std::string line;
	std::regex wzorzec("(u.{1,3}yj[[:space:]]{0,3}animacji:[[:space:]]{0,3}(uwodzi|Uwodzi|Klaszcz|klaszcz|Zgoda|zgoda|Wybaczy|wybaczy|Denerwowa|denerwowa|Smutek|smutek|Odmowa|odmowa|Rozwesela|rozwesela|Drwi|drwi|Rado|rado|powitanie[[:space:]]{0,3}[1-2]|Powitanie[[:space:]]{0,3}[1-2]|taniec[[:space:]]{0,3}[1-5]|Taniec[[:space:]]{0,3}[1-5]|Gumsan[[:space:]]{0,3}Style|Gumsan[[:space:]]{0,3}style|gumsan[[:space:]]{0,3}Style|gumsan[[:space:]]{0,3}style))");
	std::regex wzorzec1("\[0-9]{1,3}");
	std::smatch wynik;

	while (getline(textFile, line)) {
		//std::cout << "dzialam" << std::endl;
		if (regex_search(line, wynik, wzorzec))
		{
			return wynik[2];
		}
	}

	return "nic";


}


