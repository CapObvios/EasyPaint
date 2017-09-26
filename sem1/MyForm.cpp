#include "MyForm.h"  
#include "Drawer.h"

#include <Windows.h>

#define MAGNETRADIUS 7 

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

	// Default values
	applyButton->Enabled = false;
	drawingColor = Color::Black;

	// Initializing required collections
	buffer = gcnew System::Collections::Generic::Dictionary<Point, Color>();
	longBuffer = gcnew System::Collections::Generic::Dictionary<Point, Color>();
	longBufferedObjects = gcnew System::Collections::Generic::List<IGeometry^>();
	
	//Initializing picturebox items
	bm = gcnew Bitmap(DrawingAreaPB->Width, DrawingAreaPB->Height);
	DrawingAreaPB->Image = bm;
	g = Graphics::FromImage(bm);
	ClearDrawingArea();
		
	// Draw some sample data with custom and standard drawing functions to compare

	Pen^ stdFuncsPen = gcnew Pen(Color::Red);	
	//custom lines
	d->DrawLine(g, DrawingAreaPB,100, 100, 150, 90 , Color::Black);
	d->DrawLine(g, DrawingAreaPB,100, 100, 150, 110, Color::Black);
	d->DrawLine(g, DrawingAreaPB,100, 100, 50, 90  , Color::Black);
	d->DrawLine(g, DrawingAreaPB,100, 100, 50, 110 , Color::Black);
	d->DrawLine(g, DrawingAreaPB,100, 100, 110, 150, Color::Black);
	d->DrawLine(g, DrawingAreaPB,100, 100, 90, 150 , Color::Black);
	d->DrawLine(g, DrawingAreaPB,100, 100, 110, 50 , Color::Black);
	d->DrawLine(g, DrawingAreaPB,100, 100, 90, 50  , Color::Black);
	//built-in lines
	g->DrawLine(stdFuncsPen, 200, 100, 250, 90);
	g->DrawLine(stdFuncsPen, 200, 100, 250, 110);
	g->DrawLine(stdFuncsPen, 200, 100, 150, 90);
	g->DrawLine(stdFuncsPen, 200, 100, 150, 110);
	g->DrawLine(stdFuncsPen, 200, 100, 210, 150);
	g->DrawLine(stdFuncsPen, 200, 100, 190, 150);
	g->DrawLine(stdFuncsPen, 200, 100, 210, 50);
	g->DrawLine(stdFuncsPen, 200, 100, 190, 50);

	//custom circles
	d->DrawCircle(g, DrawingAreaPB, 100, 200, 15, Color::Black);
	d->DrawCircle(g, DrawingAreaPB, 100, 200, 25, Color::Black);
	//built-in circles
	g->DrawEllipse(stdFuncsPen, 185, 185, 30, 30);
	g->DrawEllipse(stdFuncsPen, 175, 175, 50, 50);

	//custom ellipses
	d->DrawEllipse(g, DrawingAreaPB, 300, 100, 30, 60, Color::Black);
	d->DrawEllipse(g, DrawingAreaPB, 300, 100, 60, 30, Color::Black);
	//built-in ellipses
	g->DrawEllipse(stdFuncsPen, 270, 140, 60, 120);
	g->DrawEllipse(stdFuncsPen, 240, 170, 120, 60);
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
	d->DrawLine(g, DrawingAreaPB, line.X1, line.Y1, line.X2, line.Y2, col);
}

System::Void sem1::MyForm::drawPixelsAndHandleBuffer(System::Collections::Generic::List<Point>^ pixels, const bool & isTemporary, const bool & isLongTerm)
{
	d->PaintPixelArray(g, DrawingAreaPB, buffer); //return pixels from buffer to the drawing area
	buffer->Clear(); // clear buffer
	if (isTemporary) // is a temp line -> fill in the buffer before printing pixels
	{
		for each (Point P in pixels)
		{
			if (P.X >= bm->Width || P.X < 0 || P.Y >= bm->Height || P.Y < 0)
				continue;
			if (!isLongTerm)
			{
				if (buffer->ContainsKey(P))
					continue;
				buffer->Add(P, bm->GetPixel(P.X, P.Y));
			}
			else // if (isLongTerm)
			{
				if (longBuffer->ContainsKey(P))
					continue;
				longBuffer->Add(P, bm->GetPixel(P.X, P.Y));
			}
		}
	}
	d->PaintPixelArray(g, DrawingAreaPB, pixels, drawingColor); // transfer pixels to the drawing area
}

System::Void sem1::MyForm::handleDrawObject(const bool & isTemporary, const bool & isLongTerm)
{
	System::Collections::Generic::List<Point>^ pixels; 

	// getting pixels based on the current application settings
	if (drawingMode == DrawingMode::line)
	{
		pixels = d->GetLinePixels(pointStart.X, pointStart.Y, pointEnd.X, pointEnd.Y);
		if (isTemporary && isLongTerm)
		{
			addObjectToLongBuffer(Line(pointStart.X, pointStart.Y, pointEnd.X, pointEnd.Y, drawingColor));
		}
	}
	else if (drawingMode == DrawingMode::circle)
	{
		//radius
		double unroundedRadius = Math::Sqrt(Math::Pow(pointEnd.X - pointStart.X, 2) + Math::Pow(pointEnd.Y - pointStart.Y, 2));
		int radius = Math::Round(unroundedRadius, 0);
		//get pixels
		pixels = d->GetCirclePixels(pointStart.X, pointStart.Y, radius);
		if (isTemporary && isLongTerm)
		{
			addObjectToLongBuffer(Circle(pointStart.X, pointStart.Y, radius, drawingColor));
		}
	}
	else if (drawingMode == DrawingMode::ellipse)
	{
		//get radiuses
		int a = Math::Abs(pointEnd.X - pointStart.X), b = Math::Abs(pointEnd.Y - pointStart.Y);
		//get pixels
		pixels = d->GetEllipsePixels(pointStart.X, pointStart.Y, a, b);
		if (isTemporary && isLongTerm)
		{
			addObjectToLongBuffer(Ellipse(pointStart.X, pointStart.Y, a, b, drawingColor));
		}
	}
	else if (drawingMode == DrawingMode::polylines)
	{
		pixels = d->GetLinePixels(pointStart.X, pointStart.Y, pointEnd.X, pointEnd.Y);
		
		if (isTemporary && isLongTerm)
		{
			addObjectToLongBuffer(Line(pointStart.X, pointStart.Y, pointEnd.X, pointEnd.Y, drawingColor));
		}

		if (!isLongTerm)
		{
			auto helpingCirclePixels = d->GetCirclePixels(polylineStartPoint.X, polylineStartPoint.Y, MAGNETRADIUS);
			pixels->AddRange(helpingCirclePixels);
		}
	}

	drawPixelsAndHandleBuffer(pixels, isTemporary, isLongTerm); // draw pixels, received from a Drawer method
}

System::Void sem1::MyForm::pb_MouseDown(System::Object ^ sender, System::Windows::Forms::MouseEventArgs ^ e)
{
	if (drawingMode != DrawingMode::polylines)
	{
		pointStart = getCurMousePBPosition();
	}
	isMouseDown = true;
	if (drawingMode == DrawingMode::none)
	{
		return;
	}
	else if (drawingMode == DrawingMode::seedFill)
	{
		d->SeedLineFill(g, bm, DrawingAreaPB, pointStart.X, pointStart.Y, drawingColor);
	}
}

System::Void sem1::MyForm::pb_MouseUp(System::Object ^ sender, System::Windows::Forms::MouseEventArgs ^ e)
{
	isMouseDown = false;	
	if (drawingMode == DrawingMode::line || drawingMode == DrawingMode::circle || drawingMode == DrawingMode::ellipse)
	{	
		pointEnd = getCurMousePBPosition();
		handleDrawObject(true, true);
	}
	else if (drawingMode == DrawingMode::polylines)
	{		
		if (!isPolylineBeingDrawn) 
		{ 
			pointStart = getCurMousePBPosition();
			isPolylineBeingDrawn = true;
			polylineStartPoint = pointStart; 
		}
		else
		{			
			pointEnd = getCurMousePBPosition();

			if (Math::Abs(polylineStartPoint.X - pointEnd.X) <= MAGNETRADIUS && Math::Abs(polylineStartPoint.Y - pointEnd.Y) <= MAGNETRADIUS)
			{
				pointEnd = polylineStartPoint;
				isPolylineBeingDrawn = false;
			}

			handleDrawObject(true, true);
			pointStart = pointEnd;
		}
		
	}
}

System::Void sem1::MyForm::DrawingAreaPB_MouseMove(System::Object ^ sender, System::Windows::Forms::MouseEventArgs ^ e)
{
	if (isMouseDown && (drawingMode == DrawingMode::line || drawingMode == DrawingMode::circle || drawingMode == DrawingMode::ellipse))
	{
		pointEnd = getCurMousePBPosition();
		handleDrawObject(true, false);
	}
	else if (isPolylineBeingDrawn && drawingMode == DrawingMode::polylines)
	{
		pointEnd = getCurMousePBPosition();
		if (Math::Abs(polylineStartPoint.X - pointEnd.X) <= MAGNETRADIUS && Math::Abs(polylineStartPoint.Y - pointEnd.Y) <= MAGNETRADIUS)
		{
			pointEnd = polylineStartPoint;
		}

		handleDrawObject(true, false);
	}
}

System::Drawing::Point sem1::MyForm::getCurMousePBPosition()
{
	Point Cur = Cursor->Position, PB = DrawingAreaPB->PointToScreen(Point(0, 0));
	return Point(Cur.X - PB.X, Cur.Y - PB.Y);
}

System::Void sem1::MyForm::ClearDrawingArea()
{	
	buffer->Clear();
	longBuffer->Clear();
	longBufferedObjects->Clear();

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

System::Void sem1::MyForm::polylineFigureToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	drawingMode = DrawingMode::polylines;
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

System::Void sem1::MyForm::applyButton_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	applyLongBuffer();
}

System::Void sem1::MyForm::applyLongBuffer()
{
	applyButton->Enabled = false;
	d->PaintPixelArray(g, DrawingAreaPB, longBuffer); //return pixels from the longterm buffer to the drawing area
	longBuffer->Clear(); // clear the longterm pixel buffer

	//Draw longterm objects
	for each (auto %geomObject in longBufferedObjects)
	{
		
	}
	
	longBufferedObjects->Clear(); // clear the longterm buffered objects
}

System::Void sem1::MyForm::addObjectToLongBuffer(IGeometry^ object)
{
	longBufferedObjects->Add(object);
	if (longBufferedObjects->Count > 0)
		applyButton->Enabled = true;
}

// Geometry implemetations definition

System::Drawing::Point sem1::Line::GetStartPoint()
{
	return Point(X1, X2);
}

System::Drawing::Point sem1::Line::GetEndPoint()
{
	return Point(X2, Y2);
}

FigureType sem1::Line::GetFigureType()
{
	return FigureType::lineObj;
}

System::Drawing::Color sem1::Line::GetColor()
{
	return Color;
}

System::Drawing::Point sem1::Circle::GetStartPoint()
{
	return Point(X0, Y0);
}

System::Drawing::Point sem1::Circle::GetEndPoint()
{
	return Point(X0 + R, Y0);
}

FigureType sem1::Circle::GetFigureType()
{
	return FigureType::circleObj;
}

System::Drawing::Color sem1::Circle::GetColor()
{
	return Color;
}

System::Drawing::Point sem1::Ellipse::GetStartPoint()
{
	return Point(X0, Y0);
}

System::Drawing::Point sem1::Ellipse::GetEndPoint()
{
	return Point(X0 + A, Y0 + B);
}

FigureType sem1::Ellipse::GetFigureType()
{
	return FigureType::ellipseObj;
}

System::Drawing::Color sem1::Ellipse::GetColor()
{
	return Color;
}
