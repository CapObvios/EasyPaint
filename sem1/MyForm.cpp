#include "MyForm.h"     
#include <Windows.h> 
#include <vector>

using namespace sem1; //пространство имен из заголовочного файла формы !!! 

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	Application::EnableVisualStyles();     
	Application::SetCompatibleTextRenderingDefault(false);     
	Application::Run(gcnew MyForm);   
	return 0;
}

//#pragma once
//static void DoDrawing(PictureBox^ pb)
//{
//	Graphics ^im = pb->CreateGraphics();
//	Color ^col = gcnew Color();   Pen ^pen = gcnew Pen(col->Red);
//	im->Clear(col->White);
//	im->DrawLine(pen, 5, 5, 10, 10);
//	im->DrawLine(pen, 100, 100, 101, 101);
//	im->DrawLine(pen, 102, 102, 102, 102);
//
//	delete im;
//}

//#pragma endregion

//class Line
//{
//public:
//	Line(int x0, int y0, int xfin, int yfin)
//	{
//		x1 = x0;
//		y1 = y0;
//		x2 = xfin;
//		y2 = yfin;
//	}
//	int x1;
//	int y1;
//	int x2;
//	int y2;
//};

