#include "MyForm.h"  
#include "Drawer.h"

#include <Windows.h>


using namespace sem1; //пространство имен из заголовочного файла формы
using namespace Drawer; // Логика отрисовки

/*
		   Автор:	Павлов Сергей Юрьевич, ББИ 141, 20.9.2017
Среда разработки:	VS 2015 Community. 
			  OS:	Windows 10

Семинар 1:
Выполнены пункты:	Отрисовка линии, круг, эллипс. То есть, все пункты.
					Логика отрисовки в файлах Drawer.cpp и Drawer.h 


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
	
	//Отрисовка линий разработанной логикой
	DrawLine({ 100, 100, 150, 90 }, Color::Black);
	DrawLine({ 100, 100, 150, 110 }, Color::Black);
	DrawLine({ 100, 100, 50, 90 }, Color::Black);
	DrawLine({ 100, 100, 50, 110 }, Color::Black);
	DrawLine({ 100, 100, 110, 150 }, Color::Black);
	DrawLine({ 100, 100, 90, 150 }, Color::Black);
	DrawLine({ 100, 100, 110, 50 }, Color::Black);
	DrawLine({ 100, 100, 90, 50 }, Color::Black);

	//отрисовка линий стандартной функцией
	g->DrawLine(stdFuncsPen, 200, 100, 250, 90);
	g->DrawLine(stdFuncsPen, 200, 100, 250, 110);
	g->DrawLine(stdFuncsPen, 200, 100, 150, 90);
	g->DrawLine(stdFuncsPen, 200, 100, 150, 110);
	g->DrawLine(stdFuncsPen, 200, 100, 210, 150);
	g->DrawLine(stdFuncsPen, 200, 100, 190, 150);
	g->DrawLine(stdFuncsPen, 200, 100, 210, 50);
	g->DrawLine(stdFuncsPen, 200, 100, 190, 50);

	//отрисовка кругов разработанной логикой
	d->DrawCircle(g, DrawingAreaPB, 100, 200, 15, Color::Black);
	d->DrawCircle(g, DrawingAreaPB, 100, 200, 25, Color::Black);

	//отрисовка кругов стандартной функцией
	g->DrawEllipse(stdFuncsPen, 185, 185, 30, 30);
	g->DrawEllipse(stdFuncsPen, 175, 175, 50, 50);

	//отрисовка эллипсов разработанной логикой
	d->DrawEllipse(g, DrawingAreaPB, 300, 100, 30, 60, Color::Black);
	d->DrawEllipse(g, DrawingAreaPB, 300, 100, 60, 30, Color::Black);

	//отрисовка эллипсов стандартной функцией
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

System::Void sem1::MyForm::pb_MouseDown(System::Object ^ sender, System::Windows::Forms::MouseEventArgs ^ e)
{
	isMouseDown = true;
	if (drawingMode == DrawingMode::none)
	{
		return;
	}
	else if (drawingMode == DrawingMode::line)
	{
		pointStart = getCurMousePBPosition();
	}
	else if (drawingMode == DrawingMode::circle)
	{
		pointStart = getCurMousePBPosition();
	}
	else if (drawingMode == DrawingMode::ellipse)
	{
		pointStart = getCurMousePBPosition();
		Drawer::SimpleDrawer^ d;
		d->DrawEllipse(g, DrawingAreaPB, pointStart.X, pointStart.Y, (int)(Radius1NB->Value), (int)(Radius2NB->Value), drawingColor);
	}
	else if (drawingMode == DrawingMode::seedFill)
	{
		pointStart = getCurMousePBPosition();
		Drawer::SimpleDrawer^ d;
		d->SeedLineFill(g, bm, DrawingAreaPB, pointStart.X, pointStart.Y, drawingColor);
	}
}

System::Void sem1::MyForm::pb_MouseUp(System::Object ^ sender, System::Windows::Forms::MouseEventArgs ^ e)
{
	isMouseDown = false;
	if (drawingMode == DrawingMode::none || drawingMode == DrawingMode::ellipse || drawingMode == DrawingMode::seedFill)
	{
		return;
	}
	else if (drawingMode == DrawingMode::line || drawingMode == DrawingMode::circle)
	{
		pointEnd = getCurMousePBPosition();
		if (drawingMode == DrawingMode::line)
		{
			Drawer::SimpleDrawer^ d;
			//d->DrawLine(g, DrawingAreaPB, pointStart.X, pointStart.Y, pointEnd.X, pointEnd.Y, drawingColor);
			d->PaintPixelArray(g, DrawingAreaPB, buffer);
			buffer->Clear();
			auto pixels = d->GetLinePixels(pointStart.X, pointStart.Y, pointEnd.X, pointEnd.Y);
			d->PaintPixelArray(g, DrawingAreaPB, pixels, drawingColor);
		}
		else if (drawingMode == DrawingMode::circle)
		{
			double unroundedRadius = Math::Sqrt(Math::Pow(pointEnd.X - pointStart.X, 2) + Math::Pow(pointEnd.Y - pointStart.Y, 2));
			int radius = Math::Round(unroundedRadius, 0);
			Drawer::SimpleDrawer^ d;
			d->PaintPixelArray(g, DrawingAreaPB, buffer);
			buffer->Clear();
			auto pixels = d->GetCirclePixels(pointStart.X, pointStart.Y, radius);
			d->PaintPixelArray(g, DrawingAreaPB, pixels, drawingColor);
			//d->DrawCircle(g, DrawingAreaPB, pointStart.X, pointStart.Y, radius, drawingColor);
		}
	}
}

System::Void sem1::MyForm::DrawingAreaPB_MouseMove(System::Object ^ sender, System::Windows::Forms::MouseEventArgs ^ e)
{
	if (drawingMode == DrawingMode::none)
	{
		return;
	}
	else if (drawingMode == DrawingMode::line && isMouseDown)
	{
		pointEnd = getCurMousePBPosition();
		Drawer::SimpleDrawer^ d;
		d->PaintPixelArray(g, DrawingAreaPB, buffer);
		buffer->Clear();
		auto pixels = d->GetLinePixels(pointStart.X, pointStart.Y, pointEnd.X, pointEnd.Y);
		for each (Point P in pixels)
		{
			if (P.X >= bm->Width || P.X < 0 || P.Y >= bm->Height || P.Y < 0)
				continue;
			buffer->Add(P, bm->GetPixel(P.X, P.Y));
		}		
		d->PaintPixelArray(g, DrawingAreaPB, pixels, drawingColor);
	}
	else if (drawingMode == DrawingMode::circle && isMouseDown)
	{
		pointEnd = getCurMousePBPosition();
		double unroundedRadius = Math::Sqrt(Math::Pow(pointEnd.X - pointStart.X, 2) + Math::Pow(pointEnd.Y - pointStart.Y, 2));
		int radius = Math::Round(unroundedRadius, 0);
		Drawer::SimpleDrawer^ d;
		d->PaintPixelArray(g, DrawingAreaPB, buffer);
		buffer->Clear();
		auto pixels = d->GetCirclePixels(pointStart.X, pointStart.Y, radius);
		for each (Point P in pixels)
		{
			if (P.X >= bm->Width || P.X < 0 || P.Y >= bm->Height || P.Y < 0) { continue; }
			if (buffer->ContainsKey(P)) { continue; }

			buffer->Add(P, bm->GetPixel(P.X, P.Y));
		}
		d->PaintPixelArray(g, DrawingAreaPB, pixels, drawingColor);
	}
	else
	{
		return;
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
