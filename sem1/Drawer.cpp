#include "Drawer.h"

#include <Windows.h>

	using namespace std;
	using namespace System::Drawing;
	using namespace System;
	using namespace System::Windows::Forms;
	using namespace Drawer;
	using namespace System::Collections::Generic;
	///<summary>
	/// Отрисовывает линию
	///</summary>
	System::Void Drawer::SimpleDrawer::DrawLine(System::Drawing::Graphics ^ g, System::Windows::Forms::PictureBox ^ DrawingAreaPB, const int & x1, const int & y1, const int & x2, const int & y2, System::Drawing::Color col)
	{		
		SolidBrush^ brush = gcnew SolidBrush(col);

		int x = x1, y = y1, dy, dx, sx, sy;

		dx = Math::Abs(x2 - x); 
		dy = Math::Abs(y2 - y); 
		sx = Math::Sign(x2 - x);
		sy = Math::Sign(y2 - y);

		// По ходу алгоритма Х и У взаимоисключающе могут быть либо точно изменяющимися, либо неточно. 
		// Назначаем переменные, которые затем будут использоваться в алгоритме
		int*  DefChanged = &x; 
		int*  UndefChanged = &y;
		int*  DefChSign = &sx;
		int*  UndefChSign = &sy;
		int*  DefChDelta = &dx;
		int*  UndefChDelta = &dy;

		if (dy > dx)
		{
			DefChanged = &y;
			UndefChanged = &x;
			DefChSign = &sy;
			UndefChSign = &sx;
			DefChDelta = &dy;
			UndefChDelta = &dx;
		}

		// Изначальное целочисленное значение ошибки, которая отвечает за сдвиг.
		int E = 2 * *UndefChDelta - *DefChDelta;

		g->FillRectangle(brush, x, y, 1, 1);

		for (size_t i = 1; i <= *DefChDelta; i++)
		{
			// Изменяем точно изменяющуюся координату
			*DefChanged += *DefChSign;

			if (E < 0) // Если ошибка меньше нуля - не увеличиваем вторую координату
			{
				E += 2 * *UndefChDelta;
			}
			else // Если ошибка превысила или равна нулю - увеличиваем вторую координату
			{
				E += -2 * *DefChDelta + 2 * *UndefChDelta;
				*UndefChanged += *UndefChSign;
			}

			g->FillRectangle(brush, x, y, 1, 1);
		}

		DrawingAreaPB->Refresh();
	}

	System::Collections::Generic::List<System::Drawing::Point>^ Drawer::SimpleDrawer::GetLinePixels(const int & x1, const int & y1, const int & x2, const int & y2)
	{
		List<Point>^ points = gcnew List<Point>();


		int x = x1, y = y1, dy, dx, sx, sy;

		dx = Math::Abs(x2 - x);
		dy = Math::Abs(y2 - y);
		sx = Math::Sign(x2 - x);
		sy = Math::Sign(y2 - y);

		// По ходу алгоритма Х и У взаимоисключающе могут быть либо точно изменяющимися, либо неточно. 
		// Назначаем переменные, которые затем будут использоваться в алгоритме
		int*  DefChanged = &x;
		int*  UndefChanged = &y;
		int*  DefChSign = &sx;
		int*  UndefChSign = &sy;
		int*  DefChDelta = &dx;
		int*  UndefChDelta = &dy;

		if (dy > dx)
		{
			DefChanged = &y;
			UndefChanged = &x;
			DefChSign = &sy;
			UndefChSign = &sx;
			DefChDelta = &dy;
			UndefChDelta = &dx;
		}

		// Изначальное целочисленное значение ошибки, которая отвечает за сдвиг.
		int E = 2 * *UndefChDelta - *DefChDelta;

		points->Add(Point(x, y));

		for (size_t i = 1; i <= *DefChDelta; i++)
		{
			// Изменяем точно изменяющуюся координату
			*DefChanged += *DefChSign;

			if (E < 0) // Если ошибка меньше нуля - не увеличиваем вторую координату
			{
				E += 2 * *UndefChDelta;
			}
			else // Если ошибка превысила или равна нулю - увеличиваем вторую координату
			{
				E += -2 * *DefChDelta + 2 * *UndefChDelta;
				*UndefChanged += *UndefChSign;
			}

			points->Add(Point(x, y));
		}		
		return points;
	}


	System::Void Drawer::SimpleDrawer::DrawCircle(System::Drawing::Graphics ^ g, System::Windows::Forms::PictureBox ^ DrawingAreaPB, const int & x0, const int & y0, const int & R, Color col)
	{
		SolidBrush^ brush = gcnew SolidBrush(col);

		int x = 0, y = R;

		int D = 2 * (1 - R);
		int lim = 0;

		int T;

		do
		{
			g->FillRectangle(brush, x + x0, y + y0, 1, 1);
			g->FillRectangle(brush, x + x0, -y + y0, 1, 1);
			g->FillRectangle(brush, -x + x0, y + y0, 1, 1);
			g->FillRectangle(brush, -x + x0, -y + y0, 1, 1);

			if (D < 0) // => радиус линии, проходящей через диагональную точку меньше, чем реальный => необходимо брать дальнюю или диагональную
			{
				T = 2 * D + 2 * y - 1;
			}
			else if (D > 0) // Наоборот
			{
				T = 2 * D - 2 * x - 1;
			}

			if (D < 0 && T <= 0) // => Целимся в дальнюю точку && Линия проходит ближе к дальней точке
			{
				x++; // сдвигаемся по Х
				D += 2 * x + 1;
			}
			else if (D > 0 && T > 0) // => Целимся в ближнюю точку && Линия проходит ближе к ближней точке
			{
				y--; // сдвигаемся по У
				D += -2 * y + 1;
			}
			else // D == 0 || близко к диагонали.
			{
				x++; y--; // Сдвигаемся по диагонали
				D += 2 * x - 2 * y + 2;
			}
		} while (y >= lim);

		DrawingAreaPB->Refresh();
	}

	System::Collections::Generic::List<System::Drawing::Point>^ Drawer::SimpleDrawer::GetCirclePixels(const int & x0, const int & y0, const int & R)
	{
		return Drawer::SimpleDrawer::GetEllipsePixels(x0, y0, R, R);
	}

	System::Collections::Generic::List<System::Drawing::Point>^ Drawer::SimpleDrawer::GetEllipsePixels(const int & x0, const int & y0, const int & a, const int & b)
	{
		List<Point>^ points = gcnew List<Point>();
				

		int x = 0, y = b;

		int D = a*a - 2 * a*a*b + b*b;
		int lim = 0;

		int T;

		do
		{
			points->Add(Point( x + x0, y + y0));			
			points->Add(Point( x + x0,-y + y0));
			points->Add(Point(-x + x0, y + y0));
			points->Add(Point(-x + x0,-y + y0));

			if (D < 0)
			{
				T = 2 * D + (2 * y - 1)*a*a;
			}
			else if (D > 0)
			{
				T = 2 * D - (2 * x + 1)*b*b;
			}

			if (D < 0 && T <= 0) // => 
			{
				x++;
				D += (2 * x + 1)*b*b;
			}
			else if (D > 0 && T > 0) // =>
			{
				y--;
				D += (-2 * y + 1)*a*a;
			}
			else // D == 0 || близко к диагонали.
			{
				x++; y--;
				D += (2 * x + 1)*b*b + (-2 * y + 1)*a*a;
			}

			int xRefl = x - x0, yRefl = y - y0;


		} while (y >= lim);

		return points;
	}

	System::Void Drawer::SimpleDrawer::DrawEllipse(System::Drawing::Graphics ^ g, System::Windows::Forms::PictureBox ^ DrawingAreaPB, const int & x0, const int & y0, const int & a, const int & b, System::Drawing::Color col)
	{
		SolidBrush^ brush = gcnew SolidBrush(col);

		int x = 0, y = b;

		int D = a*a - 2 * a*a*b + b*b;
		int lim = 0;

		int T;

		do
		{
			g->FillRectangle(brush, x + x0, y + y0, 1, 1);
			g->FillRectangle(brush, x + x0, -y + y0, 1, 1);
			g->FillRectangle(brush, -x + x0, y + y0, 1, 1);
			g->FillRectangle(brush, -x + x0, -y + y0, 1, 1);

			if (D < 0)
			{
				T = 2 * D + (2 * y - 1)*a*a;
			}
			else if (D > 0)
			{
				T = 2 * D - (2 * x + 1)*b*b;
			}

			if (D < 0 && T <= 0) // => 
			{
				x++;
				D += (2 * x + 1)*b*b;
			}
			else if (D > 0 && T > 0) // =>
			{
				y--;
				D += (-2 * y + 1)*a*a;
			}
			else // D == 0 || близко к диагонали.
			{
				x++; y--;
				D += (2 * x + 1)*b*b + (-2 * y + 1)*a*a;
			}

			int xRefl = x - x0, yRefl = y - y0;


		} while (y >= lim);

		DrawingAreaPB->Refresh();
	}

	System::Void Drawer::SimpleDrawer::SeedLineFill(System::Drawing::Graphics ^ g, System::Drawing::Bitmap^ bm, System::Windows::Forms::PictureBox ^ DrawingAreaPB, const int & x0, const int & y0, System::Drawing::Color col)
	{
		SolidBrush^ brush = gcnew SolidBrush(col);

		Color^ colorToOverride = bm->GetPixel(x0, y0);
		
		if (colorToOverride->ToArgb() == col.ToArgb())
			return;
		 
		Stack<Point> PixelsToCheck;
		int xmin = 0, xmax = bm->Size.Width - 1, ymin = 0, ymax = bm->Size.Height - 1; // Границы окна отрисовки

		// Получить самую правую точку того же цвета от затравочной
		{
			int x = x0;			
			while (x+1 <= xmax && bm->GetPixel(x+1, y0).Equals(colorToOverride))
			{
				x++;
			}
			const Point pointToCheck = Point(x, y0);
			PixelsToCheck.Push(pointToCheck);
		}
		
		while (PixelsToCheck.Count != 0)
		{
			// Закрасить
			Point rightPoint = PixelsToCheck.Peek();
			Point leftPoint = PixelsToCheck.Pop();

			bm->SetPixel(leftPoint.X, leftPoint.Y, col);
			//g->FillRectangle(brush, leftPoint.X, leftPoint.Y, 1, 1);
			
			while (leftPoint.X - 1 >= 0 && bm->GetPixel(leftPoint.X - 1 , leftPoint.Y).Equals(colorToOverride))
			{		
				leftPoint.X -= 1;
				bm->SetPixel(leftPoint.X, leftPoint.Y, col);
				//g->FillRectangle(brush, leftPoint.X, leftPoint.Y, 1, 1);				
			} 

			DrawingAreaPB->Refresh();

			// Проверить вехнюю и нижнюю строчку
			for (int lineStep = -1; lineStep <= 1; lineStep+=2)
			{
				for (size_t i = leftPoint.X; i <= rightPoint.X; i++)
				{
					if (leftPoint.Y + lineStep >= ymin && leftPoint.Y + lineStep <= ymax && bm->GetPixel(i, leftPoint.Y +lineStep).Equals(colorToOverride))
					{
						while (i + 1 <= xmax && bm->GetPixel(i + 1, leftPoint.Y + lineStep).Equals(colorToOverride))
						{
							i++;
						}
						const Point newValToCheck = Point(i, leftPoint.Y + lineStep);
						PixelsToCheck.Push(newValToCheck);
					}
				}
			}
		}		
		DrawingAreaPB->Refresh();
	}

	System::Void Drawer::SimpleDrawer::PaintPixelArray(System::Drawing::Graphics ^ g, System::Windows::Forms::PictureBox ^ DrawingAreaPB, System::Collections::Generic::List<System::Drawing::Point>^ points, System::Drawing::Color col)
	{
		SolidBrush^ br = gcnew SolidBrush(col);

		for each (Point %pt in points)
		{
			g->FillRectangle(br, pt.X, pt.Y, 1, 1);
		}
		DrawingAreaPB->Refresh();
	}

	System::Void Drawer::SimpleDrawer::PaintPixelArray(System::Drawing::Graphics ^ g, System::Windows::Forms::PictureBox ^ DrawingAreaPB, System::Collections::Generic::Dictionary<System::Drawing::Point, System::Drawing::Color>^ points)
	{
		SolidBrush^ br = gcnew SolidBrush(Color::Black);

		for each (auto %pt in points)
		{			
			br->Color = pt.Value;
			g->FillRectangle(br, pt.Key.X, pt.Key.Y, 1, 1);
		}
		DrawingAreaPB->Refresh();
	}
