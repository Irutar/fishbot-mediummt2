#include "mouseAndKeyboard.h"

void mouseLeftButtonClick()
{
	INPUT    Input = { 0 };
	// left down 
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	::SendInput(1, &Input, sizeof(INPUT));

	// left up
	::ZeroMemory(&Input, sizeof(INPUT));
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
	::SendInput(1, &Input, sizeof(INPUT));
}


void mouseRightButtonClick()
{
	INPUT    Input = { 0 };
	// right down 
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
	::SendInput(1, &Input, sizeof(INPUT));

	// right up
	::ZeroMemory(&Input, sizeof(INPUT));
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
	::SendInput(1, &Input, sizeof(INPUT));
}


void keyboardDirectXPress(int input) {
	
	INPUT KEY_B;

	KEY_B.type = INPUT_KEYBOARD;
	KEY_B.ki.time = 0;
	KEY_B.ki.wVk = 0;
	KEY_B.ki.dwExtraInfo = 0;
	KEY_B.ki.dwFlags = KEYEVENTF_SCANCODE;
	KEY_B.ki.wScan = input;

	SendInput(1, &KEY_B, sizeof(INPUT));
	Sleep(30);
	KEY_B.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
	SendInput(1, &KEY_B, sizeof(INPUT));
	KEY_B.ki.dwFlags = KEYEVENTF_SCANCODE;

}


void testInput(int input) {
	
	INPUT inp[2];
	memset(inp, 0, sizeof(INPUT));
	inp[0].type = INPUT_KEYBOARD;
	inp[0].ki.dwFlags = KEYEVENTF_SCANCODE;
	inp[1] = inp[0];
	inp[1].ki.dwFlags |= KEYEVENTF_KEYUP;      // keyup event

	inp[0].ki.wScan = inp[1].ki.wScan = input;      // inp[0] = keydown, inp[1] = keyup   
	SendInput(2, inp, sizeof(INPUT));
}


void pasteFromKeyboard() {
	INPUT ip;
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;


	// Press the "Ctrl" key
	ip.ki.wVk = VK_CONTROL;
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	// Press the "V" key
	ip.ki.wVk = 'V';
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	// Release the "V" key
	ip.ki.wVk = 'V';
	ip.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &ip, sizeof(INPUT));

	// Release the "Ctrl" key
	ip.ki.wVk = VK_CONTROL;
	ip.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &ip, sizeof(INPUT));
}


void mouseLeftDown() {
	INPUT    Input = { 0 };
	// left down 
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	::SendInput(1, &Input, sizeof(INPUT));

}


void mouseLeftUp() {
	INPUT    Input = { 0 };
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
	::SendInput(1, &Input, sizeof(INPUT));
}