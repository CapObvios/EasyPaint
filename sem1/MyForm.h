#include "Drawer.h"
#include "Types.h"

#pragma once

namespace sem1 {
	
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace std;
	using namespace Drawer;
	using namespace GeometryTypes;

	enum DrawingMode
	{
		none = 0,
		line = 1,
		circle = 2,
		ellipse = 3,
		seedFill = 4,
		polylines = 5,
		cropRect = 6
	};

	/// <summary>
	/// —водка дл€ MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{		
	private: 
		System::Windows::Forms::MenuStrip^  menuStrip1;
		System::Windows::Forms::ToolStripMenuItem^  DrawingMenuNode;		
		System::Windows::Forms::ToolStripMenuItem^  LineMenuButton;
		System::Windows::Forms::ToolStripMenuItem^  CircleMenuButton;
		System::Windows::Forms::ToolStripMenuItem^  EllipseMenuButton;
		System::Windows::Forms::ToolStripMenuItem^  AboutMenuButton;
		System::Windows::Forms::ToolStripMenuItem^  MainMenuNode;
		System::Windows::Forms::ToolStripMenuItem^  ClearMenuButton;
		System::Windows::Forms::ToolStripMenuItem^  ExitMenuButton;
		System::Windows::Forms::ToolStripMenuItem^  fillToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^  seedFillToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^  colorToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^  colorToolStripMenuItem1;
		System::Windows::Forms::ToolStripMenuItem^  polylineFigureToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^  fillActiveFiguresToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^  fillColorToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^  backgroundColorToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^  transformToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^  modifyActiveFiguresToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^  cropActiveLinesToolStripMenuItem;
		System::Windows::Forms::ToolStripSeparator^  toolStripSeparator2;
		System::Windows::Forms::ToolStripSeparator^  toolStripSeparator1;

		System::Windows::Forms::ColorDialog^  colorPicker;
		System::Windows::Forms::PictureBox^  DrawingAreaPB;
		System::Windows::Forms::Button^  applyButton;

		System::Drawing::Bitmap^ bm;
		System::Drawing::Graphics^ g;
		SimpleDrawer^ d;
		System::Drawing::Color drawingColor;
		System::Drawing::Color fillingColor;
		System::Drawing::Color backgroundColor;

		DrawingMode drawingMode;

		System::Drawing::Point polylineStartPoint;
		System::Collections::Generic::List<GeometryTypes::IGeometry^>^ longBufferedObjects;

		bool isMouseDown;
		bool isPolylineBeingDrawn;
		System::Collections::Generic::Dictionary<Point, Color>^ buffer;
		System::Collections::Generic::Dictionary<Point, Color>^ longBuffer;

	public:
		MyForm(void);

	protected:
		/// <summary>
		/// Destructor
		/// </summary>
		~MyForm();

	private:
		/// <summary>
		/// ќб€зательна€ переменна€ конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// “ребуемый метод дл€ поддержки конструктора Ч не измен€йте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->DrawingAreaPB = (gcnew System::Windows::Forms::PictureBox());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->MainMenuNode = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ClearMenuButton = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ExitMenuButton = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->transformToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->modifyActiveFiguresToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->cropActiveLinesToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->DrawingMenuNode = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->LineMenuButton = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->CircleMenuButton = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->EllipseMenuButton = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->polylineFigureToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->fillToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->seedFillToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->fillActiveFiguresToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->colorToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->colorToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->fillColorToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->backgroundColorToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->AboutMenuButton = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->colorPicker = (gcnew System::Windows::Forms::ColorDialog());
			this->applyButton = (gcnew System::Windows::Forms::Button());
			this->toolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->toolStripSeparator2 = (gcnew System::Windows::Forms::ToolStripSeparator());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DrawingAreaPB))->BeginInit();
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// DrawingAreaPB
			// 
			this->DrawingAreaPB->Location = System::Drawing::Point(0, 36);
			this->DrawingAreaPB->Margin = System::Windows::Forms::Padding(2);
			this->DrawingAreaPB->Name = L"DrawingAreaPB";
			this->DrawingAreaPB->Size = System::Drawing::Size(1277, 984);
			this->DrawingAreaPB->TabIndex = 0;
			this->DrawingAreaPB->TabStop = false;
			this->DrawingAreaPB->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pb_MouseDown);
			this->DrawingAreaPB->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::DrawingAreaPB_MouseMove);
			this->DrawingAreaPB->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pb_MouseUp);
			// 
			// menuStrip1
			// 
			this->menuStrip1->ImageScalingSize = System::Drawing::Size(40, 40);
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(6) {
				this->MainMenuNode, this->transformToolStripMenuItem,
					this->DrawingMenuNode, this->fillToolStripMenuItem, this->colorToolStripMenuItem, this->AboutMenuButton
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Padding = System::Windows::Forms::Padding(3, 1, 0, 1);
			this->menuStrip1->Size = System::Drawing::Size(1284, 31);
			this->menuStrip1->TabIndex = 1;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// MainMenuNode
			// 
			this->MainMenuNode->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->MainMenuNode->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->ClearMenuButton,
					this->toolStripSeparator2, this->ExitMenuButton
			});
			this->MainMenuNode->Name = L"MainMenuNode";
			this->MainMenuNode->Size = System::Drawing::Size(50, 29);
			this->MainMenuNode->Text = L"File";
			// 
			// ClearMenuButton
			// 
			this->ClearMenuButton->Name = L"ClearMenuButton";
			this->ClearMenuButton->Size = System::Drawing::Size(210, 30);
			this->ClearMenuButton->Text = L"Clear";
			this->ClearMenuButton->Click += gcnew System::EventHandler(this, &MyForm::ClearMenuButton_Click);
			// 
			// ExitMenuButton
			// 
			this->ExitMenuButton->Name = L"ExitMenuButton";
			this->ExitMenuButton->Size = System::Drawing::Size(210, 30);
			this->ExitMenuButton->Text = L"Exit";
			this->ExitMenuButton->Click += gcnew System::EventHandler(this, &MyForm::ExitMenuButton_Click);
			// 
			// transformToolStripMenuItem
			// 
			this->transformToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->modifyActiveFiguresToolStripMenuItem,
					this->cropActiveLinesToolStripMenuItem
			});
			this->transformToolStripMenuItem->Name = L"transformToolStripMenuItem";
			this->transformToolStripMenuItem->Size = System::Drawing::Size(103, 29);
			this->transformToolStripMenuItem->Text = L"Transform";
			// 
			// modifyActiveFiguresToolStripMenuItem
			// 
			this->modifyActiveFiguresToolStripMenuItem->Name = L"modifyActiveFiguresToolStripMenuItem";
			this->modifyActiveFiguresToolStripMenuItem->Size = System::Drawing::Size(262, 30);
			this->modifyActiveFiguresToolStripMenuItem->Text = L"Modify active figures";
			// 
			// cropActiveLinesToolStripMenuItem
			// 
			this->cropActiveLinesToolStripMenuItem->Name = L"cropActiveLinesToolStripMenuItem";
			this->cropActiveLinesToolStripMenuItem->Size = System::Drawing::Size(262, 30);
			this->cropActiveLinesToolStripMenuItem->Text = L"Crop active lines";
			this->cropActiveLinesToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::cropActiveLinesToolStripMenuItem_Click);
			// 
			// DrawingMenuNode
			// 
			this->DrawingMenuNode->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
				this->LineMenuButton,
					this->CircleMenuButton, this->EllipseMenuButton, this->toolStripSeparator1, this->polylineFigureToolStripMenuItem
			});
			this->DrawingMenuNode->Name = L"DrawingMenuNode";
			this->DrawingMenuNode->Size = System::Drawing::Size(65, 29);
			this->DrawingMenuNode->Text = L"Draw";
			// 
			// LineMenuButton
			// 
			this->LineMenuButton->Name = L"LineMenuButton";
			this->LineMenuButton->Size = System::Drawing::Size(263, 30);
			this->LineMenuButton->Text = L"Line";
			this->LineMenuButton->Click += gcnew System::EventHandler(this, &MyForm::LineMenuButton_Click);
			// 
			// CircleMenuButton
			// 
			this->CircleMenuButton->Name = L"CircleMenuButton";
			this->CircleMenuButton->Size = System::Drawing::Size(263, 30);
			this->CircleMenuButton->Text = L"Circle";
			this->CircleMenuButton->Click += gcnew System::EventHandler(this, &MyForm::CircleMenuButton_Click);
			// 
			// EllipseMenuButton
			// 
			this->EllipseMenuButton->Name = L"EllipseMenuButton";
			this->EllipseMenuButton->Size = System::Drawing::Size(263, 30);
			this->EllipseMenuButton->Text = L"Ellipse";
			this->EllipseMenuButton->Click += gcnew System::EventHandler(this, &MyForm::EllipseMenuButton_Click);
			// 
			// polylineFigureToolStripMenuItem
			// 
			this->polylineFigureToolStripMenuItem->Name = L"polylineFigureToolStripMenuItem";
			this->polylineFigureToolStripMenuItem->Size = System::Drawing::Size(263, 30);
			this->polylineFigureToolStripMenuItem->Text = L"Polyline closed figure";
			this->polylineFigureToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::polylineFigureToolStripMenuItem_Click);
			// 
			// fillToolStripMenuItem
			// 
			this->fillToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->seedFillToolStripMenuItem,
					this->fillActiveFiguresToolStripMenuItem
			});
			this->fillToolStripMenuItem->Name = L"fillToolStripMenuItem";
			this->fillToolStripMenuItem->Size = System::Drawing::Size(45, 29);
			this->fillToolStripMenuItem->Text = L"Fill";
			// 
			// seedFillToolStripMenuItem
			// 
			this->seedFillToolStripMenuItem->Name = L"seedFillToolStripMenuItem";
			this->seedFillToolStripMenuItem->Size = System::Drawing::Size(226, 30);
			this->seedFillToolStripMenuItem->Text = L"Seed fill";
			this->seedFillToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::seedFillToolStripMenuItem_Click);
			// 
			// fillActiveFiguresToolStripMenuItem
			// 
			this->fillActiveFiguresToolStripMenuItem->Name = L"fillActiveFiguresToolStripMenuItem";
			this->fillActiveFiguresToolStripMenuItem->Size = System::Drawing::Size(226, 30);
			this->fillActiveFiguresToolStripMenuItem->Text = L"Fill active figures";
			this->fillActiveFiguresToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::fillActiveFiguresToolStripMenuItem_Click);
			// 
			// colorToolStripMenuItem
			// 
			this->colorToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->colorToolStripMenuItem1,
					this->fillColorToolStripMenuItem, this->backgroundColorToolStripMenuItem
			});
			this->colorToolStripMenuItem->Name = L"colorToolStripMenuItem";
			this->colorToolStripMenuItem->Size = System::Drawing::Size(67, 29);
			this->colorToolStripMenuItem->Text = L"Color";
			// 
			// colorToolStripMenuItem1
			// 
			this->colorToolStripMenuItem1->Name = L"colorToolStripMenuItem1";
			this->colorToolStripMenuItem1->Size = System::Drawing::Size(236, 30);
			this->colorToolStripMenuItem1->Text = L"Contour color";
			this->colorToolStripMenuItem1->Click += gcnew System::EventHandler(this, &MyForm::ColorMenuButton_Click);
			// 
			// fillColorToolStripMenuItem
			// 
			this->fillColorToolStripMenuItem->Name = L"fillColorToolStripMenuItem";
			this->fillColorToolStripMenuItem->Size = System::Drawing::Size(236, 30);
			this->fillColorToolStripMenuItem->Text = L"Fill color";
			this->fillColorToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::fillColorToolStripMenuItem_Click);
			// 
			// backgroundColorToolStripMenuItem
			// 
			this->backgroundColorToolStripMenuItem->Name = L"backgroundColorToolStripMenuItem";
			this->backgroundColorToolStripMenuItem->Size = System::Drawing::Size(236, 30);
			this->backgroundColorToolStripMenuItem->Text = L"Background color";
			this->backgroundColorToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::backgroundColorToolStripMenuItem_Click);
			// 
			// AboutMenuButton
			// 
			this->AboutMenuButton->Name = L"AboutMenuButton";
			this->AboutMenuButton->Size = System::Drawing::Size(74, 29);
			this->AboutMenuButton->Text = L"About";
			this->AboutMenuButton->Click += gcnew System::EventHandler(this, &MyForm::AboutMenuButton_Click);
			// 
			// applyButton
			// 
			this->applyButton->Location = System::Drawing::Point(698, 0);
			this->applyButton->Name = L"applyButton";
			this->applyButton->Size = System::Drawing::Size(75, 31);
			this->applyButton->TabIndex = 2;
			this->applyButton->Text = L"Apply";
			this->applyButton->UseVisualStyleBackColor = true;
			this->applyButton->Click += gcnew System::EventHandler(this, &MyForm::applyButton_Click);
			// 
			// toolStripSeparator1
			// 
			this->toolStripSeparator1->Name = L"toolStripSeparator1";
			this->toolStripSeparator1->Size = System::Drawing::Size(260, 6);
			// 
			// toolStripSeparator2
			// 
			this->toolStripSeparator2->Name = L"toolStripSeparator2";
			this->toolStripSeparator2->Size = System::Drawing::Size(207, 6);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1284, 1030);
			this->Controls->Add(this->applyButton);
			this->Controls->Add(this->DrawingAreaPB);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Margin = System::Windows::Forms::Padding(2);
			this->Name = L"MyForm";
			this->Text = L"Seminar 2. Filling and 2-dim cropping. Sergey Pavlov";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DrawingAreaPB))->EndInit();
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: 
		System::Void DrawLine(const Line line, Color col);

		System::Drawing::Point pointStart, pointEnd;

		System::Void drawPixelsAndHandleBuffer(System::Collections::Generic::List<Point>^ pixels, const bool & isTemporary, const bool & isLongTerm, System::Drawing::Color col, const int & grain);

		System::Void handleDrawObject(const bool & isTemporary, const bool & isLongTerm);

		System::Void pb_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);

		System::Void pb_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);

		System::Void DrawingAreaPB_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);

		System::Drawing::Point getCurMousePBPosition();
		
		System::Void ClearDrawingArea();

		System::Void ExitMenuButton_Click(System::Object^  sender, System::EventArgs^  e);

		System::Void ClearMenuButton_Click(System::Object^  sender, System::EventArgs^  e);

		System::Void LineMenuButton_Click(System::Object^  sender, System::EventArgs^  e);
		
		System::Void CircleMenuButton_Click(System::Object^  sender, System::EventArgs^  e);
		
		System::Void EllipseMenuButton_Click(System::Object^  sender, System::EventArgs^  e);

		System::Void polylineFigureToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);

		System::Void seedFillToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);

		System::Void fillActiveFiguresToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		
		System::Void ColorMenuButton_Click(System::Object^  sender, System::EventArgs^  e);

		System::Void fillColorToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);

		System::Void backgroundColorToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		
		System::Void AboutMenuButton_Click(System::Object^  sender, System::EventArgs^  e);		
		
		System::Void applyButton_Click(System::Object^  sender, System::EventArgs^  e);

		System::Void applyLongBuffer();

		System::Void addObjectToLongBuffer(IGeometry^ object);

		System::Void cropActiveLinesToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);

		System::Void CheckLinesCropping();

		System::Void IsDrawingPolylineStatusChanged(bool isNowDrawing)
		{
			ClearMenuButton						->Enabled = !isNowDrawing;

			transformToolStripMenuItem			->Enabled = !isNowDrawing;
			DrawingMenuNode						->Enabled = !isNowDrawing;
			fillToolStripMenuItem				->Enabled = !isNowDrawing;
			colorToolStripMenuItem				->Enabled = !isNowDrawing;
		}

		System::Void IsCroppingStatusChanged(bool isNowCropping)
		{
			transformToolStripMenuItem			->Enabled = !isNowCropping;
			DrawingMenuNode						->Enabled = !isNowCropping;
			fillToolStripMenuItem				->Enabled = !isNowCropping;
			colorToolStripMenuItem				->Enabled = !isNowCropping;
			ClearMenuButton						->Enabled = !isNowCropping;

			//LineMenuButton						->Enabled = !isNowCropping;
			//CircleMenuButton					->Enabled = !isNowCropping;
			//EllipseMenuButton					->Enabled = !isNowCropping;
			//polylineFigureToolStripMenuItem		->Enabled = !isNowCropping;
			//seedFillToolStripMenuItem			->Enabled = !isNowCropping;
			//fillActiveFiguresToolStripMenuItem	->Enabled = !isNowCropping;
			//cropActiveLinesToolStripMenuItem	->Enabled = !isNowCropping;
		}

};
}
