#include "Types.h"

#pragma once

namespace Drawer
{
	ref class SimpleDrawer
	{

	public: 
			///<summary>
			/// Draw a line
			///</summary>
			System::Void DrawLine(
				System::Drawing::Graphics^ g,
				System::Windows::Forms::PictureBox^ DrawingAreaPB,
				const int& x1,
				const int& y1,
				const int& x2,
				const int& y2,
				System::Drawing::Color col
			);

			///<summary>
			/// Draw a circle
			///</summary>
			System::Void DrawCircle(
				System::Drawing::Graphics^ g,
				System::Windows::Forms::PictureBox^ DrawingAreaPB,
				const int& x0,
				const int& y0,
				const int& R,
				System::Drawing::Color col
			);

			///<summary>
			/// drawn an ellipse
			///</summary>
			System::Void DrawEllipse(
				System::Drawing::Graphics^ g,
				System::Windows::Forms::PictureBox^ DrawingAreaPB,
				const int& x0,
				const int& y0,
				const int& a,
				const int& b,
				System::Drawing::Color col
			);

			///<summary>
			/// Get line pixels to be drawn
			///</summary>
			System::Collections::Generic::List<System::Drawing::Point>^ GetLinePixels(
				const int & x1,
				const int & y1,
				const int & x2,
				const int & y2
			);

			///<summary>
			/// Get circle pixels to be drawn
			///</summary>
			System::Collections::Generic::List<System::Drawing::Point>^ GetCirclePixels(
				const int& x0,
				const int& y0,
				const int& R
			);

			///<summary>
			/// Get ellipse pixels to be drawn
			///</summary>
			System::Collections::Generic::List<System::Drawing::Point>^ Drawer::SimpleDrawer::GetEllipsePixels(
				const int & x0, 
				const int & y0, 
				const int & a, 
				const int & b
			);

			///<summary>
			/// Get rectangle pixels
			///</summary>
			System::Collections::Generic::List<System::Drawing::Point>^ Drawer::SimpleDrawer::GetRectanglePixels(
				const int & x1,
				const int & y1,
				const int & x2,
				const int & y2
			);

			///<summary>
			/// Fill picturebox with a given seed pixel
			///</summary>
			System::Void SeedLineFill(
				System::Drawing::Graphics^ g,
				System::Drawing::Bitmap^ bm,
				System::Windows::Forms::PictureBox^ DrawingAreaPB,
				const int& x0,
				const int& y0,
				System::Drawing::Color col
			);

			///<summary>
			/// Get given geometry figures seed pixels for XOR-like filling and mean of X-coord
			///</summary>
			System::Collections::Generic::List<System::Drawing::Point>^ GetFillGeometryObjectsSeedPixels(
				System::Collections::Generic::List<GeometryTypes::IGeometry^>^ objects,
				long& meanX
			);

			///<summary>
			/// Get pixels to fill with a XOR-like method based on the seed-pixels and central line
			///</summary>
			System::Collections::Generic::List<System::Drawing::Point>^ GetFillGeometryObjectPixelsBySeed(
				System::Collections::Generic::List<System::Drawing::Point>^ seedPixels,
				long& centralLineX
			);

			///<summary>
			/// Get aproximate pixels to fill in the give geometry objects
			///</summary>
			System::Collections::Generic::List<System::Drawing::Point>^ GetFillGeometryObjectPixels(
				System::Collections::Generic::List<GeometryTypes::IGeometry^>^ objects
			);

			///<summary>
			/// Get pixels, sorted based on their visibility after they're cropped
			///</summary>
			System::Collections::Generic::Dictionary<int, System::Collections::Generic::List<System::Drawing::Point>^>^ GetCropPixels(
				System::Collections::Generic::List<GeometryTypes::IGeometry^>^% objects,
				const int & x1,
				const int & y1,
				const int & x2,
				const int & y2
			);

			///<summary>
			/// Transfer given pixels to a drawing area with the color given
			///</summary>
			System::Void PaintPixelArray(
				System::Drawing::Graphics^ g,
				System::Windows::Forms::PictureBox^ DrawingAreaPB,
				System::Collections::Generic::List<System::Drawing::Point>^ points,
				System::Drawing::Color col
			);

			///<summary>
			/// Transfer given pixel-color dictionary values to a drawing area
			///</summary>
			System::Void PaintPixelArray(
				System::Drawing::Graphics^ g,
				System::Windows::Forms::PictureBox^ DrawingAreaPB,
				System::Collections::Generic::Dictionary<System::Drawing::Point, System::Drawing::Color>^ points
			);

	private:
			///<summary>
			/// Know if a point is inside the rectangle formed by given opposite vertices points
			///</summary>
			bool isPointInsideRect(
				System::Drawing::Point p,
				const int& x1,
				const int& y1,
				const int& x2,
				const int& y2
			);
			
			///<summary>
			/// 
			///</summary>
			static System::Void SortPointList(
				System::Collections::Generic::List<System::Drawing::Point>^ points
			);
	};
}