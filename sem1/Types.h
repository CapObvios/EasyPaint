#pragma once

namespace GeometryTypes
{
	enum FigureType
	{
		lineObj = 0,
		circleObj = 2,
		ellipseObj = 3
	};

	interface class IGeometry
	{
		System::Drawing::Point GetStartPoint();
		System::Drawing::Point GetEndPoint();
		FigureType GetFigureType();
		System::Drawing::Color GetColor();
	};

	value class Line : IGeometry
	{
	public:
		int X1;
		int Y1;
		int X2;
		int Y2;
		System::Drawing::Color Color;
		Line(const int &x1, const int & y1, const int & x2, const int & y2, const System::Drawing::Color col)
		{
			X1 = x1;
			Y1 = y1;
			X2 = x2;
			Y2 = y2;
			Color = col;
		}

		// Inherited from IGeometry
		virtual System::Drawing::Point GetStartPoint();
		virtual System::Drawing::Point GetEndPoint();
		virtual FigureType GetFigureType();
		virtual System::Drawing::Color GetColor();
	};

	value class Circle : IGeometry
	{
	public:
		int X0;
		int Y0;
		int R;
		System::Drawing::Color Color;
		Circle(const int &x0, const int & y0, const int & r, const System::Drawing::Color col)
		{
			X0 = x0;
			Y0 = y0;
			R = r;
			Color = col;
		}

		// Inherited from IGeometry
		virtual System::Drawing::Point GetStartPoint();
		virtual System::Drawing::Point GetEndPoint();
		virtual FigureType GetFigureType();
		virtual System::Drawing::Color GetColor();
	};

	value class Ellipse : IGeometry
	{
	public:
		int X0;
		int Y0;
		int A;
		int B;
		System::Drawing::Color Color;
		Ellipse(const int &x0, const int & y0, const int & a, const int & b, const System::Drawing::Color col)
		{
			X0 = x0;
			Y0 = y0;
			A = a;
			B = b;
			Color = col;
		}

		// Inherited from IGeometry
		virtual System::Drawing::Point GetStartPoint();
		virtual System::Drawing::Point GetEndPoint();
		virtual FigureType GetFigureType();
		virtual System::Drawing::Color GetColor();
	};
}