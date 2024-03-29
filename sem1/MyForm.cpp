﻿#include "MyForm.h"  
#include "Drawer.h"
#include "Types.h"

#include <Windows.h>

#define MAGNETRADIUS 7 

using namespace sem1; //Windows Forms
using namespace Drawer; // Drawing logic
using namespace GeometryTypes; // Types used in the program
using namespace System::Collections::Generic;

/*
		  Author:	Sergey Pavlov, BBI 141, 20.9.2017
		Software:	VS 2015 Community. 
			  OS:	Windows 10

Completed tasks:

	  Seminar 1:	Line, ellipse and circle drawing. Drawing logic is in the Drawer.cpp
	  Seminar 2:	Seed filling, XOR-like filling, lines cropping
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
	fillingColor = Color::Red;
	backgroundColor = Color::White;

	// Initializing required collections
	buffer = gcnew System::Collections::Generic::Dictionary<Point, Color>();
	longBuffer = gcnew System::Collections::Generic::Dictionary<Point, Color>();
	longBufferedObjects = gcnew System::Collections::Generic::List<GeometryTypes::IGeometry^>();
	
	//Initializing picturebox items and preparing it
	bm = gcnew Bitmap(DrawingAreaPB->Width, DrawingAreaPB->Height);
	DrawingAreaPB->Image = bm;
	g = Graphics::FromImage(bm);
	ClearDrawingArea();
		
	// Draw some sample data with custom and standard drawing functions to compare

	//Pen^ stdFuncsPen = gcnew Pen(Color::Red);	
	////custom lines
	//d->DrawLine(g, DrawingAreaPB,100, 100, 150, 90 , Color::Black);
	//d->DrawLine(g, DrawingAreaPB,100, 100, 150, 110, Color::Black);
	//d->DrawLine(g, DrawingAreaPB,100, 100, 50, 90  , Color::Black);
	//d->DrawLine(g, DrawingAreaPB,100, 100, 50, 110 , Color::Black);
	//d->DrawLine(g, DrawingAreaPB,100, 100, 110, 150, Color::Black);
	//d->DrawLine(g, DrawingAreaPB,100, 100, 90, 150 , Color::Black);
	//d->DrawLine(g, DrawingAreaPB,100, 100, 110, 50 , Color::Black);
	//d->DrawLine(g, DrawingAreaPB,100, 100, 90, 50  , Color::Black);
	////built-in lines
	//g->DrawLine(stdFuncsPen, 200, 100, 250, 90);
	//g->DrawLine(stdFuncsPen, 200, 100, 250, 110);
	//g->DrawLine(stdFuncsPen, 200, 100, 150, 90);
	//g->DrawLine(stdFuncsPen, 200, 100, 150, 110);
	//g->DrawLine(stdFuncsPen, 200, 100, 210, 150);
	//g->DrawLine(stdFuncsPen, 200, 100, 190, 150);
	//g->DrawLine(stdFuncsPen, 200, 100, 210, 50);
	//g->DrawLine(stdFuncsPen, 200, 100, 190, 50);

	////custom circles
	//d->DrawCircle(g, DrawingAreaPB, 100, 200, 15, Color::Black);
	//d->DrawCircle(g, DrawingAreaPB, 100, 200, 25, Color::Black);
	////built-in circles
	//g->DrawEllipse(stdFuncsPen, 185, 185, 30, 30);
	//g->DrawEllipse(stdFuncsPen, 175, 175, 50, 50);

	////custom ellipses
	//d->DrawEllipse(g, DrawingAreaPB, 300, 100, 30, 60, Color::Black);
	//d->DrawEllipse(g, DrawingAreaPB, 300, 100, 60, 30, Color::Black);
	////built-in ellipses
	//g->DrawEllipse(stdFuncsPen, 270, 140, 60, 120);
	//g->DrawEllipse(stdFuncsPen, 240, 170, 120, 60);
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

System::Void sem1::MyForm::drawPixelsAndHandleBuffer(System::Collections::Generic::List<Point>^ pixels, const bool & isTemporary, const bool & isLongTerm, System::Drawing::Color col, const int & grain)
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

		// Apply grain
		for (size_t i = 0; i < pixels->Count; i++)
		{
			if (i % grain < grain / 2)
			{
				pixels->RemoveAt(i);
			}
		}
	}	

	d->PaintPixelArray(g, DrawingAreaPB, pixels, col); // transfer pixels to the drawing area
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
			addObjectToLongBuffer(GeometryTypes::Line(pointStart.X, pointStart.Y, pointEnd.X, pointEnd.Y, drawingColor));
			fillActiveFiguresToolStripMenuItem->Enabled = false;
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
			addObjectToLongBuffer(GeometryTypes::Circle(pointStart.X, pointStart.Y, radius, drawingColor));
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
			addObjectToLongBuffer(GeometryTypes::Ellipse(pointStart.X, pointStart.Y, a, b, drawingColor));
		}
	}
	else if (drawingMode == DrawingMode::polylines)
	{
		pixels = d->GetLinePixels(pointStart.X, pointStart.Y, pointEnd.X, pointEnd.Y);
		
		if (isTemporary && isLongTerm)
		{
			addObjectToLongBuffer(GeometryTypes::Line(pointStart.X, pointStart.Y, pointEnd.X, pointEnd.Y, drawingColor));
		}

		if (!isLongTerm)
		{
			auto helpingCirclePixels = d->GetCirclePixels(polylineStartPoint.X, polylineStartPoint.Y, MAGNETRADIUS);
			pixels->AddRange(helpingCirclePixels);
		}
	}
	else if (drawingMode == DrawingMode::cropRect)
	{
		pixels = d->GetRectanglePixels(pointStart.X, pointStart.Y, pointEnd.X, pointEnd.Y);
	}

	drawPixelsAndHandleBuffer(pixels, isTemporary, isLongTerm, drawingColor, 10); // draw pixels, received from a Drawer method
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
		d->SeedLineFill(g, bm, DrawingAreaPB, pointStart.X, pointStart.Y, fillingColor);
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
	else if (drawingMode == DrawingMode::cropRect)
	{
		pointEnd = getCurMousePBPosition();
		handleDrawObject(true, true);

		CheckLinesCropping();
	}
	else if (drawingMode == DrawingMode::polylines)
	{		
		if (!isPolylineBeingDrawn) 
		{ 
			pointStart = getCurMousePBPosition();
			isPolylineBeingDrawn = true;
			polylineStartPoint = pointStart; 
			IsDrawingPolylineStatusChanged(true);
		}
		else
		{			
			pointEnd = getCurMousePBPosition();

			if (Math::Abs(polylineStartPoint.X - pointEnd.X) <= MAGNETRADIUS && Math::Abs(polylineStartPoint.Y - pointEnd.Y) <= MAGNETRADIUS)
			{
				pointEnd = polylineStartPoint;
				isPolylineBeingDrawn = false;
				IsDrawingPolylineStatusChanged(false);
			}

			handleDrawObject(true, true);
			pointStart = pointEnd;
		}
		
	}
}

System::Void sem1::MyForm::DrawingAreaPB_MouseMove(System::Object ^ sender, System::Windows::Forms::MouseEventArgs ^ e)
{
	if (isMouseDown && (drawingMode == DrawingMode::line || drawingMode == DrawingMode::circle || drawingMode == DrawingMode::ellipse || drawingMode == DrawingMode::cropRect))
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
	applyButton->Enabled = false;
	buffer->Clear();
	longBuffer->Clear();
	longBufferedObjects->Clear();

	g->Clear(backgroundColor);
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
	if (longBufferedObjects->Count > 0 || longBuffer->Count > 0)
		applyLongBuffer();
	drawingMode = DrawingMode::seedFill;
}

System::Void sem1::MyForm::cropActiveLinesToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	drawingMode = DrawingMode::cropRect;
}

System::Void sem1::MyForm::fillActiveFiguresToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	// Get the pixels to fill all buffered objects
	auto pixelsForDrawing = d->GetFillGeometryObjectPixels(longBufferedObjects);
	
	// Transfer to the picturebox
	drawPixelsAndHandleBuffer(pixelsForDrawing, false, true, fillingColor, 1);

	// Draw existing borders
	applyLongBuffer();

	DrawingAreaPB->Refresh();
}

System::Void sem1::MyForm::ColorMenuButton_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	colorPicker->ShowDialog();
	drawingColor = colorPicker->Color;
}

System::Void sem1::MyForm::fillColorToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	colorPicker->ShowDialog();
	fillingColor = colorPicker->Color;
}

System::Void sem1::MyForm::backgroundColorToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	colorPicker->ShowDialog();	
	backgroundColor = colorPicker->Color;

	ClearDrawingArea();
}

System::Void sem1::MyForm::AboutMenuButton_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	MessageBox::Show("Project SuperPaint 2.0 Filling.\nAuthor: Sergey Pavlov\nGroup: BBI 141" +
		"\nOne may draw lines, circles and ellipses by pressing holding left mouse button." +
		"\nClosed polyline figures are being drawn by clicking LMB on a drawing area. The last point should be placed at the position of the very first figure point marked with the circle." +
		"\nAll the drawn figures will at first be put to a buffer. One can apply them by clicking the \"Apply\" button." +
		"\nIn the \"Fill\" menu strip one can find 2 different ways of filling figures. First one is a simple seed filling which one should use when all of the figures are applied." +
		"\nThe second filling method fills in all of the closed figures which haven't yet been applied. Filling them this way will automatically apply them." +
		"\nYou can crop the active lines with the respective menu strip. It will first show you the way it will be cropped. After you apply, all of the additional materials will be deleted except the cropped lines." +
		"\nColor is picked in a \"Color\" menu strip. Changing the background color will clear the drawing area." +
		"\nYou can clear the drawing are in a menu strip \"File\"");
}

System::Void sem1::MyForm::applyButton_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	applyLongBuffer();
}

System::Void sem1::MyForm::applyLongBuffer()
{
	applyButton->Enabled = false;

	IsCroppingStatusChanged(false);

	d->PaintPixelArray(g, DrawingAreaPB, longBuffer); //return pixels from the longterm buffer to the drawing area
	longBuffer->Clear(); // clear the longterm pixel buffer

	//Draw longterm objects
	for each (auto %geomObject in longBufferedObjects)
	{
		List<System::Drawing::Point>^ pixels;

		auto pStart = geomObject->GetStartPoint();
		auto pEnd = geomObject->GetEndPoint();

		if (geomObject->GetFigureType() == GeometryTypes::FigureType::lineObj)
		{
			pixels = d->GetLinePixels(pStart.X, pStart.Y, pEnd.X, pEnd.Y);
		}
		else if (geomObject->GetFigureType() == GeometryTypes::FigureType::circleObj)
		{
			pixels = d->GetCirclePixels(pStart.X, pStart.Y, Math::Max(Math::Abs(pEnd.X - pStart.X), Math::Abs(pEnd.Y - pStart.Y)));
		}
		else if (geomObject->GetFigureType() == GeometryTypes::FigureType::ellipseObj)
		{
			pixels = d->GetEllipsePixels(pStart.X, pStart.Y, Math::Abs(pEnd.X - pStart.X), Math::Abs(pEnd.Y - pStart.Y));
		}

		drawPixelsAndHandleBuffer(pixels, false, false, drawingColor, 1);
	}

	fillActiveFiguresToolStripMenuItem->Enabled = true;
	
	longBufferedObjects->Clear(); // clear the longterm buffered objects
}

System::Void sem1::MyForm::addObjectToLongBuffer(GeometryTypes::IGeometry^ object)
{
	longBufferedObjects->Add(object);
	if (longBufferedObjects->Count > 0)
		applyButton->Enabled = true;
}

System::Void sem1::MyForm::CheckLinesCropping()
{
	int minX = Math::Min(pointStart.X, pointEnd.X),
		maxX = Math::Max(pointStart.X, pointEnd.X),
		minY = Math::Min(pointStart.Y, pointEnd.Y),
		maxY = Math::Max(pointStart.Y, pointEnd.Y);

	auto pixelsDict = d->GetCropPixels(longBufferedObjects, minX, minY, maxX, maxY);

	d->PaintPixelArray(g, DrawingAreaPB, longBuffer); //return pixels from the longterm buffer to the drawing area

	longBuffer->Clear(); // clear the longterm pixel buffer

	drawPixelsAndHandleBuffer(pixelsDict[(int)GeometryTypes::VisibilityType::invisible], true, true, Color::Gray, 10);
	drawPixelsAndHandleBuffer(pixelsDict[(int)GeometryTypes::VisibilityType::invisiblePart], true, true, Color::Orange, 10);
	drawPixelsAndHandleBuffer(pixelsDict[(int)GeometryTypes::VisibilityType::visible], true, true, Color::Green, 10);

	auto rectPixels = d->GetRectanglePixels(pointStart.X, pointStart.Y, pointEnd.X, pointEnd.Y);
	if (longBufferedObjects->Count > 0 || longBuffer->Count > 0)
	{
		drawPixelsAndHandleBuffer(rectPixels, true, true, Color::Black, 10);
		IsCroppingStatusChanged(true);
	}
}
