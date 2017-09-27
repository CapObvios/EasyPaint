#include "Types.h"

#include <Windows.h>

using namespace GeometryTypes;
using namespace System::Drawing;

System::Drawing::Point GeometryTypes::Line::GetStartPoint()
{
	return System::Drawing::Point(X1, Y1);
}

System::Drawing::Point GeometryTypes::Line::GetEndPoint()
{
	return System::Drawing::Point(X2, Y2);
}

FigureType GeometryTypes::Line::GetFigureType()
{
	return FigureType::lineObj;
}

System::Drawing::Color GeometryTypes::Line::GetColor()
{
	return Color;
}

System::Drawing::Point GeometryTypes::Circle::GetStartPoint()
{
	return System::Drawing::Point(X0, Y0);
}

System::Drawing::Point GeometryTypes::Circle::GetEndPoint()
{
	return System::Drawing::Point(X0, Y0 + R);
}

FigureType GeometryTypes::Circle::GetFigureType()
{
	return FigureType::circleObj;
}

System::Drawing::Color GeometryTypes::Circle::GetColor()
{
	return Color;
}

System::Drawing::Point GeometryTypes::Ellipse::GetStartPoint()
{
	return System::Drawing::Point(X0, Y0);
}

System::Drawing::Point GeometryTypes::Ellipse::GetEndPoint()
{
	return System::Drawing::Point(X0 + A, Y0 + B);
}

FigureType GeometryTypes::Ellipse::GetFigureType()
{
	return FigureType::ellipseObj;
}

System::Drawing::Color GeometryTypes::Ellipse::GetColor()
{
	return Color;
}
