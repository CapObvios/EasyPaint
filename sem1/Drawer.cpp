#include "Drawer.h"
#include "Types.h"

#include <Windows.h>

	using namespace std;
	using namespace System::Drawing;
	using namespace System;
	using namespace System::Windows::Forms;
	using namespace Drawer;
	using namespace System::Collections::Generic;

	System::Void Drawer::SimpleDrawer::DrawLine(System::Drawing::Graphics ^ g, System::Windows::Forms::PictureBox ^ DrawingAreaPB, const int & x1, const int & y1, const int & x2, const int & y2, System::Drawing::Color col)
	{		
		auto pixels = GetLinePixels(x1, y1, x2, y2);
		PaintPixelArray(g, DrawingAreaPB, pixels, col);
	}

	System::Void Drawer::SimpleDrawer::DrawCircle(System::Drawing::Graphics ^ g, System::Windows::Forms::PictureBox ^ DrawingAreaPB, const int & x0, const int & y0, const int & R, Color col)
	{
		auto pixels = GetCirclePixels(x0, y0, R);
		PaintPixelArray(g, DrawingAreaPB, pixels, col);
	}

	System::Void Drawer::SimpleDrawer::DrawEllipse(System::Drawing::Graphics ^ g, System::Windows::Forms::PictureBox ^ DrawingAreaPB, const int & x0, const int & y0, const int & a, const int & b, System::Drawing::Color col)
	{
		auto pixels = GetEllipsePixels(x0, y0, a, b);
		PaintPixelArray(g, DrawingAreaPB, pixels, col);
	}

	System::Collections::Generic::List<System::Drawing::Point>^ Drawer::SimpleDrawer::GetLinePixels(const int & x1, const int & y1, const int & x2, const int & y2)
	{
		List<Point>^ points = gcnew List<Point>();


		int x = x1, y = y1, dy, dx, sx, sy;

		dx = Math::Abs(x2 - x);
		dy = Math::Abs(y2 - y);
		sx = Math::Sign(x2 - x);
		sy = Math::Sign(y2 - y);

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

		int E = 2 * *UndefChDelta - *DefChDelta;

		points->Add(Point(x, y));

		for (size_t i = 1; i <= *DefChDelta; i++)
		{
			*DefChanged += *DefChSign;

			if (E < 0) 
			{
				E += 2 * *UndefChDelta;
			}
			else
			{
				E += -2 * *DefChDelta + 2 * *UndefChDelta;
				*UndefChanged += *UndefChSign;
			}

			points->Add(Point(x, y));
		}		
		return points;
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

			if (D < 0 && T <= 0)
			{
				x++;
				D += (2 * x + 1)*b*b;
			}
			else if (D > 0 && T > 0)
			{
				y--;
				D += (-2 * y + 1)*a*a;
			}
			else
			{
				x++; y--;
				D += (2 * x + 1)*b*b + (-2 * y + 1)*a*a;
			}

			int xRefl = x - x0, yRefl = y - y0;


		} while (y >= lim);

		return points;
	}

	System::Void Drawer::SimpleDrawer::SeedLineFill(System::Drawing::Graphics ^ g, System::Drawing::Bitmap^ bm, System::Windows::Forms::PictureBox ^ DrawingAreaPB, const int & x0, const int & y0, System::Drawing::Color col)
	{
		SolidBrush^ brush = gcnew SolidBrush(col);

		Color^ colorToOverride = bm->GetPixel(x0, y0);
		
		if (colorToOverride->ToArgb() == col.ToArgb())
			return;
		 
		Stack<Point> PixelsToCheck;
		int xmin = 0, xmax = bm->Size.Width - 1, ymin = 0, ymax = bm->Size.Height - 1;

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

	System::Collections::Generic::List<System::Drawing::Point>^ Drawer::SimpleDrawer::GetFillGeometryObjectsPixels(System::Collections::Generic::List<GeometryTypes::IGeometry^>^ objects, long& meanX)
	{
		List<Point>^ points = gcnew List<Point>();

		GeometryTypes::Line polylineInitialLine;
		bool isDrawingPolyline = false;
		bool shouldAvoidPolylineInitialPoint = false;

		for (size_t i = 0; i < objects->Count; i++)
		{		
			List<Point>^ curPoints = gcnew List<Point>();
			//Get the figure lonely Y-axis pixels
			if (objects[i]->GetFigureType() == GeometryTypes::FigureType::lineObj)
			{
				auto pStart = objects[i]->GetStartPoint();
				auto pEnd = objects[i]->GetEndPoint();
				curPoints = GetLinePixels(pStart.X, pStart.Y, pEnd.X, pEnd.Y);

				if (!isDrawingPolyline) // we weren't drawing a polyline before
				{
					isDrawingPolyline = true;

					polylineInitialLine.X1 = pStart.X;
					polylineInitialLine.Y1 = pStart.Y;
					polylineInitialLine.X2 = pEnd.X;
					polylineInitialLine.Y2 = pEnd.Y;
				}

				// we got the initial polyline point
				if (isDrawingPolyline && pEnd.Equals(polylineInitialLine.GetStartPoint()))
				{
					isDrawingPolyline = false; // end of polyline

					int diff1 = pEnd.Y - pStart.Y, diff2 = pEnd.Y - polylineInitialLine.Y2;
					if (Math::Sign(diff1) != Math::Sign(diff2))
					{
						shouldAvoidPolylineInitialPoint = true;
					}
					else
					{
						shouldAvoidPolylineInitialPoint = false;
					}
				}
				else
				{
					// join lines
					while (i + 1 < objects->Count && objects[i + 1]->GetFigureType() == GeometryTypes::FigureType::lineObj)
					{
						auto pNextStart = objects[i + 1]->GetStartPoint();
						auto pNextEnd = objects[i + 1]->GetEndPoint();

						if (pEnd.Equals(pNextStart))
						{
							// compare signs
							int diff1 = pEnd.Y - pStart.Y, diff2 = pEnd.Y - pNextEnd.Y;
							if (Math::Sign(diff1) != Math::Sign(diff2) && !(diff1 == 0 || diff2 == 0)) // signs differ => we need to join the points and then filter them, assuming pixels lay on one line
							{
								i++;
								pStart = pNextStart;
								pEnd = pNextEnd;

								curPoints->AddRange(GetLinePixels(pStart.X, pStart.Y, pEnd.X, pEnd.Y));
							}
							else // signs are equal => we need to double the points, so we go further
							{
								break;
							}
						}
						else if (isDrawingPolyline && pEnd.Equals(polylineInitialLine.GetStartPoint()))
						{
							isDrawingPolyline = false; // end of polyline

							int diff1 = pEnd.Y - pStart.Y, diff2 = pEnd.Y - polylineInitialLine.Y2;
							if (Math::Sign(diff1) != Math::Sign(diff2))
							{
								shouldAvoidPolylineInitialPoint = true;
							}
							else
							{
								shouldAvoidPolylineInitialPoint = false;
							}
							break;
						}
					}
				}
			}
			else if (objects[i]->GetFigureType() == GeometryTypes::FigureType::circleObj)
			{
				auto circle = ((GeometryTypes::Circle)objects[i]);
				curPoints = GetCirclePixels(circle.X0, circle.Y0, circle.R);
			}
			else if (objects[i]->GetFigureType() == GeometryTypes::FigureType::ellipseObj)
			{
				auto ellipse = ((GeometryTypes::Ellipse)objects[i]);
				curPoints = GetEllipsePixels(ellipse.X0, ellipse.Y0, ellipse.A, ellipse.B);
			}

			//Filter them 
			
			Dictionary<int, Point> filtered;

			for each (auto %pixel in curPoints)
			{
				if (objects[i]->GetFigureType() == GeometryTypes::FigureType::lineObj)
				{
					if (!filtered.ContainsKey(pixel.Y) && (!shouldAvoidPolylineInitialPoint || pixel.Y != polylineInitialLine.Y1))
					{
						filtered.Add(pixel.Y, pixel);
						meanX += pixel.X;
					}
				}
				else if (objects[i]->GetFigureType() == GeometryTypes::FigureType::circleObj || objects[i]->GetFigureType() == GeometryTypes::FigureType::ellipseObj)
				{
					auto centralPoint = objects[i]->GetStartPoint();

					bool isLeftSide = !filtered.ContainsKey(pixel.Y) && pixel.X <= centralPoint.X;
					bool isRightSide = !filtered.ContainsKey(pixel.Y + 2 * objects[i]->GetEndPoint().Y) && pixel.X > centralPoint.X;
					
					if (isLeftSide)
					{
						filtered.Add(pixel.Y, pixel);
						meanX += pixel.X;
					}
					else if (isRightSide)
					{
						filtered.Add(pixel.Y + 2 * objects[i]->GetEndPoint().Y, pixel);
						meanX += pixel.X;
					}

				}
			}

			points->AddRange(filtered.Values);
		}

		meanX /= points->Count;

		return points;
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
