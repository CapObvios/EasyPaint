#include "Drawer.h"
#include "Types.h"

#include <Windows.h>

	using namespace std;
	using namespace System::Drawing;
	using namespace System;
	using namespace System::Windows::Forms;
	using namespace Drawer;
	using namespace System::Collections::Generic;
	using namespace System::Linq;
	using namespace System::Runtime::CompilerServices;

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

	System::Collections::Generic::List<System::Drawing::Point>^ Drawer::SimpleDrawer::GetRectanglePixels(const int & x1, const int & y1, const int & x2, const int & y2)
	{
		auto pixels = gcnew List<Point>();

		for (size_t i = Math::Min(x1,x2); i <= Math::Max(x1, x2); i++)
		{
			pixels->Add(Point(i, y1));
			pixels->Add(Point(i, y2));
		}

		for (size_t j = Math::Min(y1, y2)+1; j < Math::Max(y1, y2); j++)
		{
			pixels->Add(Point(x1, j));
			pixels->Add(Point(x2, j));
		}

		return pixels;		
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

			//DrawingAreaPB->Refresh();

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

	System::Collections::Generic::List<System::Drawing::Point>^ Drawer::SimpleDrawer::GetFillGeometryObjectsSeedPixels(System::Collections::Generic::List<GeometryTypes::IGeometry^>^ objects, long& meanX)
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

				if (pStart.Equals(pEnd)) continue;
				
				curPoints = GetLinePixels(pStart.X, pStart.Y, pEnd.X, pEnd.Y);

				if (!isDrawingPolyline) // we weren't drawing a polyline before
				{
					isDrawingPolyline = true;
					shouldAvoidPolylineInitialPoint = false;

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
					if (Math::Sign(diff1) != Math::Sign(diff2) && !(diff1 == 0 || diff2 == 0)) shouldAvoidPolylineInitialPoint = true;
					else shouldAvoidPolylineInitialPoint = false; 
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
							else // signs are equal => lines form an angle looking away from the perpendicular of the central line, so we need to double the points => we go to the next iteration
							{
								break;
							}
						}
						if (isDrawingPolyline && pEnd.Equals(polylineInitialLine.GetStartPoint()))
						{
							isDrawingPolyline = false; // end of polyline

							int diff1 = pEnd.Y - pStart.Y, diff2 = pEnd.Y - polylineInitialLine.Y2;
							if (Math::Sign(diff1) != Math::Sign(diff2) && !(diff1 == 0 || diff2 == 0)) shouldAvoidPolylineInitialPoint = true;
							else shouldAvoidPolylineInitialPoint = false; 

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

					bool isLeftSide = !filtered.ContainsKey(pixel.Y) && pixel.X < centralPoint.X;
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
		if (points->Count > 0) { meanX /= points->Count; }

		return points;
	}

	System::Collections::Generic::List<System::Drawing::Point>^ Drawer::SimpleDrawer::GetFillGeometryObjectPixelsBySeed(System::Collections::Generic::List<System::Drawing::Point>^ seedPixels, long & centralLineX)
	{
		//Decide which pixels should be filled
		System::Collections::Generic::Dictionary<Point, bool>^ pixelsToFill = gcnew System::Collections::Generic::Dictionary<Point, bool>();

		for each(auto pixel in seedPixels)
		{
			int stepX = Math::Sign(centralLineX - pixel.X);
			while (pixel.X != centralLineX)
			{
				if (!pixelsToFill->ContainsKey(pixel)) { pixelsToFill->Add(pixel, true); }
				else { pixelsToFill[pixel] = !pixelsToFill[pixel]; }
				pixel.X += stepX;
			}

			if (pixel.X == centralLineX && stepX < 0)
			{
				if (!pixelsToFill->ContainsKey(pixel)) { pixelsToFill->Add(pixel, true); }
				else { pixelsToFill[pixel] = !pixelsToFill[pixel]; }
			}
		}

		//Leave only pixels, which should be filled
		auto pixelsForDrawing = gcnew List<System::Drawing::Point>();

		for each (auto %pixelCandidate in pixelsToFill)
		{
			if (pixelCandidate.Value)
			{
				pixelsForDrawing->Add(pixelCandidate.Key);
			}
		}

		return pixelsForDrawing;
	}

	System::Collections::Generic::List<System::Drawing::Point>^ Drawer::SimpleDrawer::GetFillGeometryObjectPixels(System::Collections::Generic::List<GeometryTypes::IGeometry^>^ objects)
	{
		// Get seed pixels and mean value
		long centralLineX = 0;
		auto seedPixels = GetFillGeometryObjectsSeedPixels(objects, centralLineX);

		// Get pixels to fill by seed pixels
		auto pixelsForDrawing = GetFillGeometryObjectPixelsBySeed(seedPixels, centralLineX);

		return pixelsForDrawing;
	}

	System::Collections::Generic::Dictionary<int, System::Collections::Generic::List<System::Drawing::Point>^>^ Drawer::SimpleDrawer::GetCropPixels(System::Collections::Generic::List<GeometryTypes::IGeometry^>^% objects, const int & x1, const int & y1, const int & x2, const int & y2)
	{
		// initialize the dictionary
		Dictionary<int, List<Point>^>^ pixels = gcnew Dictionary<int, List<Point>^>();
		pixels->Add((int)GeometryTypes::VisibilityType::visible, gcnew List<Point>);
		pixels->Add((int)GeometryTypes::VisibilityType::invisiblePart , gcnew List<Point>);
		pixels->Add((int)GeometryTypes::VisibilityType::invisible, gcnew List<Point>);

		List<GeometryTypes::IGeometry^>^ croppedLines = gcnew List<GeometryTypes::IGeometry^>();

		for each (auto geometryFigure in objects)
		{
			if (geometryFigure->GetFigureType() == GeometryTypes::FigureType::lineObj)
			{
				auto pStart = geometryFigure->GetStartPoint();
				auto pEnd = geometryFigure->GetEndPoint();

				Byte pCode = 0;

				if (pStart.X < x1) pCode |= 1;
				if (pStart.X > x2) pCode |= 2;
				if (pStart.Y < y1) pCode |= 4;
				if (pStart.Y > y2) pCode |= 8;

				if (pEnd.X < x1) pCode |= 16;
				if (pEnd.X > x2) pCode |= 32;
				if (pEnd.Y < y1) pCode |= 64;
				if (pEnd.Y > y2) pCode |= 128;

				if (pCode == 0) // completely visible
				{
					pixels[(int)GeometryTypes::VisibilityType::visible]->AddRange(GetLinePixels(pStart.X, pStart.Y, pEnd.X, pEnd.Y));
					croppedLines->Add(geometryFigure);
				}
				else if ((pCode & (pCode >> 4)) > 0)// completely invisible
				{
					pixels[(int)GeometryTypes::VisibilityType::invisible]->AddRange(GetLinePixels(pStart.X, pStart.Y, pEnd.X, pEnd.Y));
				}
				else
				{
					List<Point>^ linePoints = gcnew List<Point>();
					linePoints->Add(pStart); linePoints->Add(pEnd);

					int diffY = pEnd.Y - pStart.Y,
						diffX = pEnd.X - pStart.X;

					int yL = diffX == 0 ? 0 : (diffY*(x1 - pStart.X))/diffX + pStart.Y,
						yR = diffX == 0 ? 0 : (diffY*(x2 - pStart.X))/diffX + pStart.Y,
											  
						xT = diffY == 0 ? 0 : (diffX*(y1 - pStart.Y))/diffY + pStart.X,
						xB = diffY == 0 ? 0 : (diffX*(y2 - pStart.Y))/diffY + pStart.X;

					if (diffX !=0 && yL > y1 && yL < y2 && yL >= Math::Min(pStart.Y, pEnd.Y) && yL <= Math::Max(pStart.Y, pEnd.Y)) { linePoints->Add(Point(x1, yL)); }
					if (diffX !=0 && yR > y1 && yR < y2 && yR >= Math::Min(pStart.Y, pEnd.Y) && yR <= Math::Max(pStart.Y, pEnd.Y)) { linePoints->Add(Point(x2, yR)); }

					if (diffY != 0 && xT > x1 && xT < x2 && xT >= Math::Min(pStart.X, pEnd.X) && xT <= Math::Max(pStart.X, pEnd.X)) { linePoints->Add(Point(xT, y1)); }
					if (diffY != 0 && xB > x1 && xB < x2 && xB >= Math::Min(pStart.X, pEnd.X) && xB <= Math::Max(pStart.X, pEnd.X)) { linePoints->Add(Point(xB, y2)); }
					SortPointList(linePoints);
					int linePointsCount = linePoints->Count;
					for (int i = 0; i < linePointsCount -1; i++)
					{
						if (isPointInsideRect(linePoints[i], x1, y1, x2, y2) && isPointInsideRect(linePoints[i + 1], x1, y1, x2, y2))
						{
							pixels[(int)GeometryTypes::VisibilityType::visible]->AddRange(GetLinePixels(linePoints[i].X, linePoints[i].Y, linePoints[i + 1].X, linePoints[i + 1].Y));
							
							croppedLines->Add(gcnew GeometryTypes::Line(linePoints[i].X, linePoints[i].Y, linePoints[i + 1].X, linePoints[i + 1].Y, ((GeometryTypes::Line)geometryFigure).Color));
						}
						else
						{
							pixels[(int)GeometryTypes::VisibilityType::invisiblePart]->AddRange(GetLinePixels(linePoints[i].X, linePoints[i].Y, linePoints[i + 1].X, linePoints[i + 1].Y));
						}
					}					
				}
			}
		}

		objects = croppedLines;

		return pixels;
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

// Private

	bool Drawer::SimpleDrawer::isPointInsideRect(System::Drawing::Point p, const int & x1, const int & y1, const int & x2, const int & y2)
	{
		if (p.X >= x1 && p.X <= x2 && p.Y >= y1 && p.Y <= y2) 
			return true;

		return false;
	}

	System::Void Drawer::SimpleDrawer::SortPointList(System::Collections::Generic::List<System::Drawing::Point>^ points)
	{
		for (size_t i = 0; i < points->Count - 1; i++)
		{
			for (size_t j = 0; j < points->Count - i -1; j++)
			{
				if (points[j].X > points[j + 1].X
					|| points[j].X == points[j + 1].X && points[j].Y > points[j + 1].Y)
				{
					auto temp = points[j];
					points[j] = points[j + 1];
					points[j + 1] = temp;
				}

			}
		}
	}
