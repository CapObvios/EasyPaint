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
			/// Transfer given pixels to a drawing area with the color given
			///</summary>
			System::Void PaintPixelArray(
				System::Drawing::Graphics^ g,
				System::Windows::Forms::PictureBox^ DrawingAreaPB,
				System::Collections::Generic::List<System::Drawing::Point>^ points,
				System::Drawing::Color col
			);

			///<summary>
			/// Transfer given pixel-color dictionary values to a drawing are
			///</summary>
			System::Void PaintPixelArray(
				System::Drawing::Graphics^ g,
				System::Windows::Forms::PictureBox^ DrawingAreaPB,
				System::Collections::Generic::Dictionary<System::Drawing::Point, System::Drawing::Color>^ points
			);
	};
}