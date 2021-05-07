#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <tchar.h>

#include <gdiplus.h>

struct GraphicsPoint{
    int x, y;
};

struct GraphicsRGB{
    int r, g, b, i;
};

class Graphics{
    public:
        Graphics(HWND thisWindow);
        int CloseGraphics();
        HDC thisHDC;
        HWND hWnd;
        PAINTSTRUCT thisPS;

        ULONG_PTR gdiplus_token;
        Gdiplus::GdiplusStartupInput GdiplusStartupInput;

        int FillQuad(GraphicsPoint first, int Tam, HBRUSH Color);
        int Quad(int Tam, GraphicsPoint porition, GraphicsRGB Color);
        int FillRect(GraphicsPoint first, GraphicsPoint to, HBRUSH Color);
        int Rect(GraphicsPoint first, GraphicsPoint to, GraphicsRGB Color);
        int Line(GraphicsPoint from, GraphicsPoint to, GraphicsRGB Color);
        int Image(WCHAR* imagePath, GraphicsPoint position);
        int FillCircle(int Tam, GraphicsPoint position, GraphicsRGB Color);
};

Graphics::Graphics(HWND thisWindow){
    Gdiplus::GdiplusStartup(&this->gdiplus_token, &this->GdiplusStartupInput, NULL);

    this->thisHDC = BeginPaint(thisWindow, &this->thisPS);
    this->hWnd = thisWindow;
}

int Graphics::Quad(int Tam, GraphicsPoint position, GraphicsRGB Color){
    Gdiplus::Graphics gdiplusGraphics(this->thisHDC);
    Gdiplus::Pen pen(Gdiplus::Color(Color.r, Color.g, Color.b, Color.i));
    gdiplusGraphics.DrawRectangle(&pen, position.x, position.y, position.x+Tam, position.y+Tam);
}

int Graphics::FillQuad(GraphicsPoint first, int Tam, HBRUSH Color){
    RECT thisRect = { first.x, first.y, first.x+Tam, first.y+Tam };
    return FillRect(this->thisHDC, &thisRect, (HBRUSH)Color);
};

int Graphics::Line(GraphicsPoint from, GraphicsPoint to, GraphicsRGB Color){
    Gdiplus::Graphics gdiplusGraphics(this->thisHDC);
    Gdiplus::Pen pen(Gdiplus::Color(Color.r, Color.g, Color.b, Color.i));
    gdiplusGraphics.DrawLine(&pen, from.x, from.y, to.x, to.y);
};

int Graphics::FillCircle(int Tam, GraphicsPoint position, GraphicsRGB Color){
    Gdiplus::Graphics gdiplusGraphics(this->thisHDC);
    Gdiplus::SolidBrush brush(Gdiplus::Color(Color.r, Color.g, Color.b, Color.i));
    gdiplusGraphics.FillEllipse(&brush, position.x, position.y, Tam, Tam);
}

int Graphics::Image(WCHAR* imagePath, GraphicsPoint position){
    Gdiplus::Graphics gdiplusGraphics(this->thisHDC);
    Gdiplus::Bitmap bmp(imagePath);
    gdiplusGraphics.DrawImage(&bmp, position.x, position.y);

    return 0;
}

int Graphics::CloseGraphics(){
    Gdiplus::GdiplusShutdown(this->gdiplus_token);
    return EndPaint(this->hWnd, &this->thisPS);
}




int Graphics::Rect(GraphicsPoint first, GraphicsPoint to, GraphicsRGB Color){
    Gdiplus::Graphics gdiplusGraphics(this->thisHDC);
    Gdiplus::Pen pen(Gdiplus::Color(Color.r, Color.g, Color.b, Color.i));
    gdiplusGraphics.DrawRectangle(&pen, from.x, from.y, to.x, to.y);
}

int Graphics::FillRect(GraphicsPoint first, GraphicsPoint to, HBRUSH Color){
    RECT thisRect = { first.x, first.y, to.x, to.y };
    return FillRect(this->thisHDC, &thisRect, (HBRUSH)Color);
};
