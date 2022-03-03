#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <WinUser.h>

LRESULT CALLBACK nkro(int code, WPARAM wParam, LPARAM lParam)
{
	int KeyTotalPress = 0;

	int KeyPressA = 0;
	int KeyPressB = 0;
	int KeyPressC = 0;
	int KeyPressD = 0;

	bool lastKeyPressA = false;
	bool lastKeyPressB = false;
	bool lastKeyPressC = false;
	bool lastKeyPressD = false;

	double KeyPressCount = 0;

	while (1)
	{
		for (;;)
		{
			WORD state1 = GetAsyncKeyState(0x57);									// W		키 상태 읽기.
			WORD state2 = GetAsyncKeyState(0x41);									// A		
			WORD state3 = GetAsyncKeyState(0x53);									// S		
			WORD state4 = GetAsyncKeyState(0x44);									// D		


			KeyPressA = 0 != (state1 & 0x8000);										// 		키 눌림, 안눌림 확인.  
			KeyPressB = 0 != (state2 & 0x8000);										// 
			KeyPressC = 0 != (state3 & 0x8000);										// 
			KeyPressD = 0 != (state4 & 0x8000);										// 

			KeyTotalPress = KeyPressA + KeyPressB + KeyPressC + KeyPressD;

			if (KeyPressA && KeyTotalPress <= 2)									// 		키 눌림 인가?
			{
				if (!lastKeyPressA)													// 		이전 상태가 안눌림 인가?
				{
					KeyPressCount++;												// 		상태 바뀌었으므로, 1회 눌림.
				}
			}

			if (KeyPressB && KeyTotalPress <= 2)									// 		키 눌림 인가?
			{
				if (!lastKeyPressB)													// 		이전 상태가 안눌림 인가?
				{
					KeyPressCount++;												// 		상태 바뀌었으므로, 1회 눌림.
				}
			}

			if (KeyPressC && KeyTotalPress <= 2)									// 		키 눌림 인가?
			{
				if (!lastKeyPressC)													// 		이전 상태가 안눌림 인가?
				{
					KeyPressCount++;												// 		상태 바뀌었으므로, 1회 눌림ww
				}
			}

			if (KeyPressD && KeyTotalPress <= 2)									// 		키 눌림 인가?
			{
				if (!lastKeyPressD)													// 		이전 상태가 안눌림 인가?
				{
					KeyPressCount++;												// 		상태 바뀌었으므로, 1회 눌림.
				}
			}

			lastKeyPressA = KeyPressA;												// 		키 상태 기억.
			lastKeyPressB = KeyPressB;												// 
			lastKeyPressC = KeyPressC;												//
			lastKeyPressD = KeyPressD;												// w

			if (KeyTotalPress > 2)
			{
				break;
			}

			printf("KeyState=%d KeyCount=%f\n", KeyTotalPress, KeyPressCount);		// 출력.
		}
	}
	return CallNextHookEx(NULL, code, wParam, lParam);
}

int main()
{
	HHOOK keyboardHook = 0;

	keyboardHook = SetWindowsHookExA(WH_KEYBOARD_LL, nkro, GetModuleHandleA(NULL), 0);

	if (keyboardHook == 0)
	{
		printf("Failed\n");
		return -1;
	}
	printf("OK\n");

	MSG msg;

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	UnhookWindowsHookEx(keyboardHook);

	return 0;
}
