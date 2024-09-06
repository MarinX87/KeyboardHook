#include <windows.h>
#include <stdio.h>


HHOOK hHook;


void simulateKeyPress(WORD keyCode, int times) {
    INPUT ip;
    ip.type = INPUT_KEYBOARD;
    ip.ki.wScan = 0;
    ip.ki.time = 0;
    ip.ki.dwExtraInfo = 0;

    for (int i = 0; i < times; i++) {
      
        ip.ki.wVk = keyCode;
        ip.ki.dwFlags = 0; 
        SendInput(1, &ip, sizeof(INPUT));

      
        ip.ki.dwFlags = KEYEVENTF_KEYUP; 
        SendInput(1, &ip, sizeof(INPUT));
        Sleep(100);
    }
}


LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0) {
       
        if (wParam == WM_KEYDOWN) {
            KBDLLHOOKSTRUCT* pKeyboard = (KBDLLHOOKSTRUCT*)lParam;
            if (pKeyboard->vkCode == 'Q') {
                printf("Q Key Pressed\n");
                simulateKeyPress('Q', 100);

            }
        }
    }

    return CallNextHookEx(hHook, nCode, wParam, lParam);
}

int main() {

    hHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);
    if (hHook == NULL) {
        printf("Failed to install hook!\n");
        return 1;
    }

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    UnhookWindowsHookEx(hHook);
    return 0;
}
