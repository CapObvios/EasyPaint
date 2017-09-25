#pragma once

namespace Drawer
{
	ref class SimpleDrawer
	{

	public: 
			///<summary>
			/// Отрисовать линию по заданным координатам, элементу графики и поля для рисования.
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
			/// Получить список координат пикселей линии, подлежащих закрашиванию.
			///</summary>
			System::Collections::Generic::List<System::Drawing::Point>^ GetLinePixels(
				const int & x1,
				const int & y1,
				const int & x2,
				const int & y2
			);

			///<summary>
			/// Отрисовать круг по заданным координатам центра и радиусу, элементу графики и поля для рисования.
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
			/// Получить список координат пикселей круга, подлежащих закрашиванию.
			///</summary>
			System::Collections::Generic::List<System::Drawing::Point>^ GetCirclePixels(
				const int& x0,
				const int& y0,
				const int& R
			);

			///<summary>
			/// Получить список координат пикселей эллипса, подлежащих закрашиванию.
			///</summary>
			System::Collections::Generic::List<System::Drawing::Point>^ Drawer::SimpleDrawer::GetEllipsePixels(
				const int & x0, 
				const int & y0, 
				const int & a, 
				const int & b
			);

			///<summary>
			/// Отрисовать эллипс по заданным координатам центра и двум радиусам, элементу графики и поля для рисования.
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
			/// Затравочная построчная заливка
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
			/// Закрасить массив пикселей цветом
			///</summary>
			System::Void PaintPixelArray(
				System::Drawing::Graphics^ g,
				System::Windows::Forms::PictureBox^ DrawingAreaPB,
				System::Collections::Generic::List<System::Drawing::Point>^ points,
				System::Drawing::Color col
			);

			///<summary>
			/// Закрасить массив пикселей указанным
			///</summary>
			System::Void PaintPixelArray(
				System::Drawing::Graphics^ g,
				System::Windows::Forms::PictureBox^ DrawingAreaPB,
				System::Collections::Generic::Dictionary<System::Drawing::Point, System::Drawing::Color>^ points
			);
	};
}