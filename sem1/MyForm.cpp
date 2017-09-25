#include "MyForm.h"  
#include "Drawer.h"

#include <Windows.h>


using namespace sem1; //Windows Forms
using namespace Drawer; // Drawing logic

/*
		  Author:	Sergey Pavlov, BBI 141, 20.9.2017
		Software:	VS 2015 Community. 
			  OS:	Windows 10

Seminar 1:
Completed tasks:	Line, ellipse and circle drawing. Drawing logic is in the Drawer.cpp
*/

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	Application::EnableVisualStyles();     
	Application::SetCompatibleTextRenderingDefault(false);     
	Application::Run(gcnew MyForm);   
	return 0;
}

sem1::MyForm::MyForm(void)
{
	InitializeComponent();

	buffer = gcnew System::Collections::Generic::Dictionary<Point, Color>();

	bm = gcnew Bitmap(DrawingAreaPB->Width, DrawingAreaPB->Height);
	DrawingAreaPB->Image = bm;
	g = Graphics::FromImage(bm);

	drawingColor = Color::Black;

	ClearDrawingArea();

	Drawer::SimpleDrawer^ d;

	Pen^ stdFuncsPen = gcnew Pen(Color::Red);
	
	//Îòðèñîâêà ëèíèé ðàçðàáîòàííîé ëîãèêîé
	DrawLine({ 100, 100, 150, 90 }, Color::Black);
	DrawLine({ 100, 100, 150, 110 }, Color::Black);
	DrawLine({ 100, 100, 50, 90 }, Color::Black);
	DrawLine({ 100, 100, 50, 110 }, Color::Black);
	DrawLine({ 100, 100, 110, 150 }, Color::Black);
	DrawLine({ 100, 100, 90, 150 }, Color::Black);
	DrawLine({ 100, 100, 110, 50 }, Color::Black);
	DrawLine({ 100, 100, 90, 50 }, Color::Black);

	//îòðèñîâêà ëèíèé ñòàíäàðòíîé ôóíêöèåé
	g->DrawLine(stdFuncsPen, 200, 100, 250, 90);
	g->DrawLine(stdFuncsPen, 200, 100, 250, 110);
	g->DrawLine(stdFuncsPen, 200, 100, 150, 90);
	g->DrawLine(stdFuncsPen, 200, 100, 150, 110);
	g->DrawLine(stdFuncsPen, 200, 100, 210, 150);
	g->DrawLine(stdFuncsPen, 200, 100, 190, 150);
	g->DrawLine(stdFuncsPen, 200, 100, 210, 50);
	g->DrawLine(stdFuncsPen, 200, 100, 190, 50);

	//îòðèñîâêà êðóãîâ ðàçðàáîòàííîé ëîãèêîé
	d->DrawCircle(g, DrawingAreaPB, 100, 200, 15, Color::Black);
	d->DrawCircle(g, DrawingAreaPB, 100, 200, 25, Color::Black);

	//îòðèñîâêà êðóãîâ ñòàíäàðòíîé ôóíêöèåé
	g->DrawEllipse(stdFuncsPen, 185, 185, 30, 30);
	g->DrawEllipse(stdFuncsPen, 175, 175, 50, 50);

	//îòðèñîâêà ýëëèïñîâ ðàçðàáîòàííîé ëîãèêîé
	d->DrawEllipse(g, DrawingAreaPB, 300, 100, 30, 60, Color::Black);
	d->DrawEllipse(g, DrawingAreaPB, 300, 100, 60, 30, Color::Black);

	//îòðèñîâêà ýëëèïñîâ ñòàíäàðòíîé ôóíêöèåé
	g->DrawEllipse(stdFuncsPen, 270, 140, 60, 120);
	g->DrawEllipse(stdFuncsPen, 240, 170, 120, 60);


	//delete g;
}

sem1::MyForm::~MyForm()
{
	if (components)
	{
		delete components;
	}
}

System::Void sem1::MyForm::DrawLine(const Line line, Color col)
{
	Drawer::SimpleDrawer^ d;
	d->DrawLine(g, DrawingAreaPB, line.x1, line.y1, line.x2, line.y2, col);
}

System::Void sem1::MyForm::drawPixelsAndHandleBuffer(System::Collections::Generic::List<Point>^ pixels, const bool & isTemporary)
{
	d->PaintPixelArray(g, DrawingAreaPB, buffer); //return buffer
	buffer->Clear(); // clear buffer
	if (isTemporary) // is a temp line -> fill in the buffer before printing pixels
	{
		for each (Point P in pixels)
		{
			if (P.X >= bm->Width || P.X < 0 || P.Y >= bm->Height || P.Y < 0)
				continue;
			if (buffer->ContainsKey(P))
				continue;
			buffer->Add(P, bm->GetPixel(P.X, P.Y));
		}
	}
	d->PaintPixelArray(g, DrawingAreaPB, pixels, drawingColor); // transfer pixels to the drawing area
}

System::Void sem1::MyForm::handleDrawObject(const bool & isTemporary)
{
	pointEnd = getCurMousePBPosition();

	System::Collections::Generic::List<Point>^ pixels;

	if (drawingMode == DrawingMode::line)
	{
		pixels = d->GetLinePixels(pointStart.X, pointStart.Y, pointEnd.X, pointEnd.Y);		
	}
	else if (drawingMode == DrawingMode::circle)
	{
		//radius
		double unroundedRadius = Math::Sqrt(Math::Pow(pointEnd.X - pointStart.X, 2) + Math::Pow(pointEnd.Y - pointStart.Y, 2));
		int radius = Math::Round(unroundedRadius, 0);
		//get pixels
		pixels = d->GetCirclePixels(pointStart.X, pointStart.Y, radius);
	}
	else if (drawingMode == DrawingMode::ellipse)
	{
		//get radiuses
		int a = Math::Abs(pointEnd.X - pointStart.X), b = Math::Abs(pointEnd.Y - pointStart.Y);
		//get pixels
		pixels = d->GetEllipsePixels(pointStart.X, pointStart.Y, a, b);
	}

	drawPixelsAndHandleBuffer(pixels, isTemporary);
}

System::Void sem1::MyForm::pb_MouseDown(System::Object ^ sender, System::Windows::Forms::MouseEventArgs ^ e)
{
	pointStart = getCurMousePBPosition();
	isMouseDown = true;
	if (drawingMode == DrawingMode::none)
	{
		return;
	}
	else if (drawingMode == DrawingMode::seedFill)
	{
		pointStart = getCurMousePBPosition();
		d->SeedLineFill(g, bm, DrawingAreaPB, pointStart.X, pointStart.Y, drawingColor);
	}
}

System::Void sem1::MyForm::pb_MouseUp(System::Object ^ sender, System::Windows::Forms::MouseEventArgs ^ e)
{
	isMouseDown = false;
	
	if (drawingMode == DrawingMode::line || drawingMode == DrawingMode::circle || drawingMode == DrawingMode::ellipse)
	{		
		handleDrawObject(false);
	}
}

System::Void sem1::MyForm::DrawingAreaPB_MouseMove(System::Object ^ sender, System::Windows::Forms::MouseEventArgs ^ e)
{
	if (!isMouseDown || drawingMode == DrawingMode::none)
	{
		return;
	}
	else if (drawingMode == DrawingMode::line || drawingMode == DrawingMode::circle || drawingMode == DrawingMode::ellipse)
	{
		handleDrawObject(true);
	}
}

System::Drawing::Point sem1::MyForm::getCurMousePBPosition()
{
	Point Cur = Cursor->Position, PB = DrawingAreaPB->PointToScreen(Point(0, 0));
	return Point(Cur.X - PB.X, Cur.Y - PB.Y);
}

System::Void sem1::MyForm::ClearDrawingArea()
{
	g->Clear(Color::White);
	DrawingAreaPB->Refresh();
}

System::Void sem1::MyForm::ExitMenuButton_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	Application::Exit();
}

System::Void sem1::MyForm::ClearMenuButton_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	ClearDrawingArea();
}

System::Void sem1::MyForm::LineMenuButton_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	drawingMode = DrawingMode::line;
}

System::Void sem1::MyForm::CircleMenuButton_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	drawingMode = DrawingMode::circle;
}

System::Void sem1::MyForm::EllipseMenuButton_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	drawingMode = DrawingMode::ellipse;
}

System::Void sem1::MyForm::seedFillToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	drawingMode = DrawingMode::seedFill;
}

System::Void sem1::MyForm::ColorMenuButton_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	colorPicker->ShowDialog();
	drawingColor = colorPicker->Color;
}

System::Void sem1::MyForm::AboutMenuButton_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	MessageBox::Show("Проект 1. Алгоритмы Брезенхема.\nАвтор: Павлов Сергей Юрьевич\nГруппа: ББИ141" +
		"\nПрограмма отрисовывает линии и круги по зажатию левой кнопки мыши." +
		"\nПри рисовании эллипса необходимо выбрать цифры вверху окна - его радиусы." +
		"\nРисуется по нажатию левой кнопки мыши" +
		"\nВыбор цвета в пункте меню \"Рисование\"" +
		"\nОчистить поле для рисования можно в пункте меню \"Главная\"");
}
