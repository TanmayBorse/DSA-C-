// client side code 
#include <winsock2.h>
#include <windows.h>
#include <string>
#include <tchar.h>
#include <iostream>

#pragma comment(lib, "ws2_32.lib")

// Global variables
HWND ListBox;
HWND InputEdit;
HWND SendButton;
SOCKET server; 

// Function prototypes
DWORD WINAPI ServerThread(LPVOID lpParam); // Main server thread function
void OnButtonClick();
DWORD WINAPI clientSend(LPVOID lpParam);
DWORD WINAPI clientReceive(LPVOID lpParam);


LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
    switch (Message) {
                case WM_CREATE:
            // Create a List Box , input field, sendbutton
            ListBox = CreateWindowEx(WS_EX_CLIENTEDGE, _T("LISTBOX"), _T(""),WS_VISIBLE | WS_CHILD | WS_BORDER | LBS_NOTIFY,10, 10, 500, 200,hwnd, (HMENU)1, GetModuleHandle(NULL), NULL);
            InputEdit = CreateWindowEx( WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), WS_VISIBLE | WS_CHILD | WS_BORDER, 10, 220, 300, 25, hwnd, (HMENU)1, GetModuleHandle(NULL), NULL);
            SendButton = CreateWindow( _T("BUTTON"), _T("Send"), WS_VISIBLE | WS_CHILD | WS_BORDER | BS_DEFPUSHBUTTON, 320, 220, 80, 22, hwnd, (HMENU)2, GetModuleHandle(NULL), NULL);
            SendMessage(ListBox, LB_ADDSTRING, 0, (LPARAM)_T("i am client")); // Add items to the list box
        break;

    case WM_COMMAND:
        if (LOWORD(wParam) == 2) 
            OnButtonClick();       
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, Message, wParam, lParam);
    }
    return 0;
}

void OnButtonClick() { 
    TCHAR buffer[256];
    GetWindowText(InputEdit, buffer, sizeof(buffer) / sizeof(buffer[0]));
    if (_tcslen(buffer) != 0 || _tcscspn(buffer, _T("\t\r\n ")) != 0){
    clientSend(&server); 
     TCHAR formattedBuffer[512];
    _stprintf(formattedBuffer, _T("Me: %s"), buffer);
    SendMessage(ListBox, LB_ADDSTRING, 0, (LPARAM)formattedBuffer);  // Add the formatted buffer to the list box
    SetWindowText(InputEdit, _T(""));
    }
}


DWORD WINAPI clientSend(LPVOID lpParam) {
    SOCKET server = *(SOCKET*)lpParam; 
    wchar_t buffer[256] = { 0 };
    
    GetWindowTextW(InputEdit, buffer, sizeof(buffer) / sizeof(wchar_t));

    std::string sendBuffer;
    sendBuffer.resize((wcslen(buffer) + 1) * 4);
    int charsConverted = WideCharToMultiByte(CP_UTF8, 0, buffer, -1, &sendBuffer[0], sendBuffer.size(), NULL, NULL);

    if (charsConverted > 0) {
        if (send(server, sendBuffer.c_str(), charsConverted - 1, 0) == SOCKET_ERROR){
            std::cerr << "send failed with error " << WSAGetLastError() << std::endl;
            return -1;
        }
    } 
    else{
        std::cerr << "WideCharToMultiByte failed with error: " << GetLastError() << std::endl;
        return -1;
    }

    if (wcscmp(buffer, L"exit") == 0) {
        std::cout << "Thank you for using the application" << std::endl;
        return 1;
    }
    SetWindowTextW(InputEdit, L""); 
    return 1;
}


DWORD WINAPI ServerThread(LPVOID lpParam) {
    WSADATA wsaData;
    SOCKADDR_IN addr;
    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed with error: " << WSAGetLastError() << std::endl;
        return -1;
    }

    // Create server socket
    server = socket(AF_INET, SOCK_STREAM, 0);
    if (server == INVALID_SOCKET) {
        std::cout << "Socket creation failed with error: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return -1;
    }

    // Configure server address
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_family = AF_INET;
    addr.sin_port = htons(5555);

    // Connect to the server
    if (connect(server, (SOCKADDR*)&addr, sizeof(addr)) == SOCKET_ERROR) {
        std::cout << "Server connection failed with error: " << WSAGetLastError() << std::endl;
        closesocket(server);
        WSACleanup();
        return -1;
    }
    std::cout << "Connected to server!" << std::endl;
    std::cout << "Now you can use our live chat application. Enter \"exit\" to disconnect" << std::endl;
    // Start the client receive thread
    DWORD tid;
    HANDLE t1 = CreateThread(NULL, 0, clientReceive, &server, 0, &tid);
    if (t1 == NULL) 
        std::cout << "Thread creation error: " << GetLastError() << std::endl;
    // Main thread waits for the client receive thread to finish
    WaitForSingleObject(t1, INFINITE);
    closesocket(server);  // Cleanup
    WSACleanup();
    return 0;
}

DWORD WINAPI clientReceive(LPVOID lpParam) {
    SOCKET server = *(SOCKET*)lpParam;
    TCHAR buffer[1024] = { 0 };

    while (true) {
        int bytesReceived = recv(server, (char*)buffer, sizeof(buffer) - sizeof(TCHAR), 0);
        if (bytesReceived == SOCKET_ERROR) {
            std::cerr << "recv function failed with error " << WSAGetLastError() << std::endl;
            return -1;
        }

        if (bytesReceived == 0) {
            std::cout << "Server Disconnected." << std::endl;
            break;
        }

        buffer[bytesReceived / sizeof(TCHAR)] = '\0';
        SendMessage(ListBox, LB_ADDSTRING, 0,  (LPARAM)buffer);
        memset(buffer, 0, sizeof(buffer));
    }

    return 1;
}
// The 'main' function of Win32 GUI programs: this is where execution starts
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASSEX wc;
    HWND hwnd;
    MSG msg;
    memset(&wc, 0, sizeof(wc));
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszClassName = "WindowClass";
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    if (!RegisterClassEx(&wc)) {
        MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }
    hwnd = CreateWindowEx( WS_EX_CLIENTEDGE, "WindowClass", "Caption", WS_VISIBLE | WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 640, 480, NULL, NULL, hInstance, NULL);
    if (hwnd == NULL) {
        MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }
       
        CreateThread(NULL, 0, ServerThread, NULL, 0, NULL); // Start the server thread
    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}