//server side code
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
SOCKET clientSocket; 

// Function prototypes
DWORD WINAPI ServerThread(LPVOID lpParam); // Main server thread function
void OnButtonClick();
DWORD WINAPI serverSend(LPVOID lpParam);
DWORD WINAPI serverReceive(LPVOID lpParam);


LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
    switch (Message) {
        case WM_CREATE:
                // Create a List Box
                ListBox = CreateWindowEx( WS_EX_CLIENTEDGE, _T("LISTBOX"), _T(""),
                WS_VISIBLE | WS_CHILD | WS_BORDER | LBS_NOTIFY,10, 10, 500, 200,hwnd, (HMENU)1, GetModuleHandle(NULL), NULL);
                
                // Create Input Field
                InputEdit = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""),
                WS_VISIBLE | WS_CHILD | WS_BORDER,10, 220, 300, 25,hwnd, (HMENU)1, GetModuleHandle(NULL), NULL);
                
                // Create Button
                SendButton = CreateWindow( _T("BUTTON"), _T("Send"),
                WS_VISIBLE | WS_CHILD | WS_BORDER | BS_DEFPUSHBUTTON, 320, 220, 80, 22, hwnd, (HMENU)2, GetModuleHandle(NULL), NULL);
                
                // Add items to the list box
                SendMessage(ListBox, LB_ADDSTRING, 0, (LPARAM)_T("I am Server!"));
            
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
        serverSend(&clientSocket); 
        TCHAR formattedBuffer[512];
        _stprintf(formattedBuffer, _T("Me: %s"), buffer);
        SendMessage(ListBox, LB_ADDSTRING, 0, (LPARAM)formattedBuffer);
        SetWindowText(InputEdit, _T(""));
    }
}

DWORD WINAPI ServerThread(LPVOID lpParam) {
    WSADATA wsaData;
    SOCKET serverSocket;
    SOCKADDR_IN serverAddr, clientAddr;
    int clientAddrSize = sizeof(clientAddr);
    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed with error: " << WSAGetLastError() << std::endl;
        return -1;
    }
    // Create server socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "Socket creation failed with error: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return -1;
    }
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(5555);
    // Bind the socket to the local address and port
    if (bind(serverSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Bind failed with error: " << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return -1;
    }
    // Listen for incoming connections
    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "Listen failed with error: " << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return -1;
    }
    std::cout << "Server listening on port 5555..." << std::endl;
    // Accept a client connection
    clientSocket = accept(serverSocket, (SOCKADDR*)&clientAddr, &clientAddrSize);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Accept failed with error: " << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return -1;
    }

    std::cout << "Client connected!" << std::endl;

    // Create threads for sending and receiving
    // HANDLE sendThread = CreateThread(NULL, 0, serverSend, &clientSocket, 0, NULL);
    HANDLE receiveThread = CreateThread(NULL, 0, serverReceive, &clientSocket, 0, NULL);

    // Wait for threads to finish before closing the socket
    // WaitForSingleObject(sendThread, INFINITE);
    WaitForSingleObject(receiveThread, INFINITE);

    // CloseHandle(sendThread);
    CloseHandle(receiveThread);

    closesocket(clientSocket);
    closesocket(serverSocket);
    WSACleanup();
    return 0;
}

DWORD WINAPI serverSend(LPVOID lpParam) {
    
    SOCKET client = *(SOCKET*)lpParam;
    wchar_t buffer[256] = { 0 };
    
    GetWindowTextW(InputEdit, buffer, sizeof(buffer) / sizeof(wchar_t));
    
    std::string sendBuffer;
    sendBuffer.resize((wcslen(buffer) + 1) * 4);
    int charsConverted = WideCharToMultiByte(CP_UTF8, 0, buffer, -1, &sendBuffer[0], sendBuffer.size(), NULL, NULL);

    if (charsConverted > 0) {
        if (send(client, sendBuffer.c_str(), charsConverted - 1, 0) == SOCKET_ERROR) {
            std::cerr << "send failed with error " << WSAGetLastError() << std::endl;
            return -1;
        }
    } 
    else{
        std::cerr << "WideCharToMultiByte failed with error: " << GetLastError() << std::endl;
        return -1;
    }
    if(wcscmp(buffer, L"exit") == 0){
        std::cout << "Client disconnected (server-side exit)." << std::endl;
        return 1;
    }
    SetWindowTextW(InputEdit, L""); 

    return 1;
}

DWORD WINAPI serverReceive(LPVOID lpParam) {
    
    TCHAR buffer[1024] = { 0 };
    SOCKET client = *(SOCKET*)lpParam;
    
    while (true) {
        int bytesReceived = recv(client, (char*)buffer, sizeof(buffer) - sizeof(TCHAR), 0); 
        if (bytesReceived == SOCKET_ERROR) {
            std::cerr << "recv function failed with error " << WSAGetLastError() << std::endl;
            return -1;
        }
        if (bytesReceived == 0) {
            std::cout << "Client Disconnected." << std::endl;
            break; 
        }
        
        buffer[bytesReceived / sizeof(TCHAR)] = '\0';
        SendMessage(ListBox, LB_ADDSTRING, 0, (LPARAM)buffer);
        memset(buffer, 0, sizeof(buffer));
    }

    return 1;
}

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
    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE, "WindowClass", "Caption",
        WS_VISIBLE | WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 640, 480,
        NULL, NULL, hInstance, NULL
    );
    if (hwnd == NULL) {
        MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }
    
    CreateThread(NULL, 0, ServerThread, NULL, 0, NULL);

    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}