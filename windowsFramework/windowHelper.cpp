#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <tchar.h>


#define DEFAULT_WINDOW_PROC DefaultWindowProc

LRESULT __stdcall DefaultWindowProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp){
    switch(msg){
        case WM_CLOSE:
        case WM_DESTROY:{
            PostQuitMessage(0);
            break;
        }

        default:{
            return DefWindowProc(hWnd, msg, wp, lp);
            break;
        }
    }
    return 0;
}

class Window{
    public:
        Window();
        int SetTitle(char* title);
        int SetWndProc(WNDPROC WindowProcessFunction);
        int SetInstance(HINSTANCE hInst);
        int MainLoop();
        int SetResize(bool canResize);
        int SetSize(int width, int height);
        int IniciateWindow();
        int SetBackgroundColor(HBRUSH WindowColor);
        int RegisterWindowClass();
        HWND hWnd;
        HINSTANCE hInstance;
        WNDCLASSEX WindowClass;
        char* WindowTitle;
        RECT WindowRect;
        MSG msg;
        bool canResize;
        int width, height;
};

Window::Window(){
    this->WindowClass.cbClsExtra = 0;
    this->WindowClass.cbSize = sizeof(WNDCLASSEX);
    this->WindowClass.cbWndExtra = 0;
    this->WindowClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
    this->WindowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    this->WindowClass.lpszMenuName = NULL;
    this->WindowClass.style = CS_HREDRAW | CS_VREDRAW;
    this->canResize = true;
    this->WindowClass.lpszClassName = _T("WindowClass");
}

int Window::SetBackgroundColor(HBRUSH WindowColor){
    this->WindowClass.hbrBackground = WindowColor;
    return 0;
}

int Window::SetTitle(char* title){
    this->WindowTitle = title;
    return 0;
}

int Window::SetWndProc(WNDPROC WindowProcessFunction){
    this->WindowClass.lpfnWndProc = WindowProcessFunction;
    return 0;
}

int Window::SetInstance(HINSTANCE hInst){
    this->hInstance = hInst;
    return 0;
}

int Window::SetResize(bool canResize){
    this->canResize = canResize;
    return 0;
}

int Window::SetSize(int width, int height){
    this->height = height;
    this->width = width;
    return 0;
}

int Window::RegisterWindowClass(){
    this->WindowClass.hInstance = this->hInstance;
    this->WindowClass.hIcon = LoadIcon(this->hInstance, IDI_APPLICATION);
    this->WindowClass.hIconSm = LoadIcon(this->WindowClass.hInstance, IDI_APPLICATION);


    if(!RegisterClassEx(&this->WindowClass)){
        std::cerr << "[ERROR] Error in function RegisterClassEx!" << std::endl;
        return -1;
    }
    return 0;
}

int Window::IniciateWindow(){
    this->hWnd = CreateWindow(
        this->WindowClass.lpszClassName,
        this->WindowTitle,
        this->canResize ? WS_OVERLAPPEDWINDOW : WS_VISIBLE | WS_SYSMENU | WS_MINIMIZEBOX | WS_CAPTION,
        CW_USEDEFAULT, CW_USEDEFAULT,
        this->width, this->height,
        NULL, NULL, this->hInstance, NULL
    );

    GetClientRect(this->hWnd, &this->WindowRect);
}

int Window::MainLoop(){

    if(!this->hWnd){
        std::cerr << "[ERROR] Error in function CreateWindow!" << std::endl;
        return -1;
    }

    ShowWindow(this->hWnd, true);
    UpdateWindow(this->hWnd);

    while(GetMessage(&this->msg, NULL, 0, 0)){
        TranslateMessage(&this->msg);
        DispatchMessage(&this->msg);
        // switch(msg.message){
        //     case WM_SIZE:{
        //         GetClientRect(this->hWnd, &this->WindowRect);
        //         break;
        //     }
        // }
    }

    return (int)this->msg.wParam;
}
