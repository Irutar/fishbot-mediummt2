#include "ScreenShot.h"


void ScreenShot(const char*BmpName, int xBegin, int yBegin, int Width, int Height) {

	HDC DevC = GetDC(NULL);



	DWORD FileSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + (sizeof(RGBTRIPLE) + 1 * ((Width)*(Height) * 4));
	char *BmpFileData = (char*)GlobalAlloc(0x0040, FileSize);

	PBITMAPFILEHEADER BFileHeader = (PBITMAPFILEHEADER)BmpFileData;
	PBITMAPINFOHEADER  BInfoHeader = (PBITMAPINFOHEADER)&BmpFileData[sizeof(BITMAPFILEHEADER)];

	BFileHeader->bfType = 0x4D42; // BM
	BFileHeader->bfSize = sizeof(BITMAPFILEHEADER);
	BFileHeader->bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

	BInfoHeader->biSize = sizeof(BITMAPINFOHEADER);
	BInfoHeader->biPlanes = 1;
	BInfoHeader->biBitCount = 24;
	BInfoHeader->biCompression = BI_RGB;
	BInfoHeader->biHeight = Height - yBegin;
	BInfoHeader->biWidth = Width - xBegin;

	RGBTRIPLE *Image = (RGBTRIPLE*)&BmpFileData[sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER)];
	RGBTRIPLE color;

	HDC CaptureDC = CreateCompatibleDC(DevC);
	HBITMAP CaptureBitmap = CreateCompatibleBitmap(DevC, Width, Height);
	SelectObject(CaptureDC, CaptureBitmap);
	BitBlt(CaptureDC, 0, 0, Width - xBegin, Height - yBegin, DevC, xBegin, yBegin, SRCCOPY | CAPTUREBLT);
	GetDIBits(CaptureDC, CaptureBitmap, 0, Height, Image, (LPBITMAPINFO)BInfoHeader, DIB_RGB_COLORS);

	DWORD Junk;
	HANDLE FH = CreateFileA(BmpName, GENERIC_WRITE, FILE_SHARE_WRITE, 0, CREATE_ALWAYS, 0, 0);
	WriteFile(FH, BmpFileData, FileSize, &Junk, 0);
	CloseHandle(FH);
	GlobalFree(BmpFileData);
}


void fullScreenShot(const char*BmpName) {
	HWND DesktopHwnd = GetDesktopWindow();
	RECT DesktopParams;
	HDC DevC = GetDC(DesktopHwnd);
	GetWindowRect(DesktopHwnd, &DesktopParams);
	DWORD Width = 1920;
	DWORD Height = 1080;

	DWORD FileSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + (sizeof(RGBTRIPLE) + 1 * (Width*Height * 4));
	char *BmpFileData = (char*)GlobalAlloc(0x0040, FileSize);

	PBITMAPFILEHEADER BFileHeader = (PBITMAPFILEHEADER)BmpFileData;
	PBITMAPINFOHEADER  BInfoHeader = (PBITMAPINFOHEADER)&BmpFileData[sizeof(BITMAPFILEHEADER)];

	BFileHeader->bfType = 0x4D42; // BM
	BFileHeader->bfSize = sizeof(BITMAPFILEHEADER);
	BFileHeader->bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

	BInfoHeader->biSize = sizeof(BITMAPINFOHEADER);
	BInfoHeader->biPlanes = 1;
	BInfoHeader->biBitCount = 24;
	BInfoHeader->biCompression = BI_RGB;
	BInfoHeader->biHeight = Height;
	BInfoHeader->biWidth = Width;

	RGBTRIPLE *Image = (RGBTRIPLE*)&BmpFileData[sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER)];
	RGBTRIPLE color;

	HDC CaptureDC = CreateCompatibleDC(DevC);
	HBITMAP CaptureBitmap = CreateCompatibleBitmap(DevC, Width, Height);
	SelectObject(CaptureDC, CaptureBitmap);
	BitBlt(CaptureDC, 0, 0, Width, Height, DevC, 0, 0, SRCCOPY | CAPTUREBLT);
	GetDIBits(CaptureDC, CaptureBitmap, 0, Height, Image, (LPBITMAPINFO)BInfoHeader, DIB_RGB_COLORS);

	DWORD Junk;
	HANDLE FH = CreateFileA(BmpName, GENERIC_WRITE, FILE_SHARE_WRITE, 0, CREATE_ALWAYS, 0, 0);
	WriteFile(FH, BmpFileData, FileSize, &Junk, 0);
	CloseHandle(FH);
	GlobalFree(BmpFileData);
}
