#include "Drawer.h"

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
	
	struct Line
	{
		int x1;
		int y1;
		int x2;
		int y2;
	};

	enum DrawingMode
	{
		none = 0,
		line = 1,
		circle = 2,
		ellipse = 3,
		seedFill = 4
	};

	/// <summary>
	/// Сводка для MyForm
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
		System::Windows::Forms::ToolStripMenuItem^  ColorMenuButton;	
		System::Windows::Forms::ColorDialog^  colorPicker;





		System::Windows::Forms::PictureBox^  DrawingAreaPB;
		System::Windows::Forms::ToolStripMenuItem^  заливкаToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^  seedFillToolStripMenuItem;

		System::Drawing::Bitmap^ bm;
		System::Drawing::Graphics^ g;
		SimpleDrawer^ d;
		System::Drawing::Color drawingColor;

		DrawingMode drawingMode;

		System::Collections::Generic::Dictionary<Point, Color>^ buffer;
		bool isMouseDown;

	public:
		MyForm(void);

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MyForm();

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->DrawingAreaPB = (gcnew System::Windows::Forms::PictureBox());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->MainMenuNode = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ClearMenuButton = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ExitMenuButton = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->DrawingMenuNode = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->LineMenuButton = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->CircleMenuButton = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->EllipseMenuButton = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->заливкаToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->seedFillToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ColorMenuButton = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->AboutMenuButton = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->colorPicker = (gcnew System::Windows::Forms::ColorDialog());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DrawingAreaPB))->BeginInit();
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// DrawingAreaPB
			// 
			this->DrawingAreaPB->Location = System::Drawing::Point(0, 34);
			this->DrawingAreaPB->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->DrawingAreaPB->Name = L"DrawingAreaPB";
			this->DrawingAreaPB->Size = System::Drawing::Size(1277, 995);
			this->DrawingAreaPB->TabIndex = 0;
			this->DrawingAreaPB->TabStop = false;
			this->DrawingAreaPB->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pb_MouseDown);
			this->DrawingAreaPB->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::DrawingAreaPB_MouseMove);
			this->DrawingAreaPB->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pb_MouseUp);
			// 
			// menuStrip1
			// 
			this->menuStrip1->ImageScalingSize = System::Drawing::Size(40, 40);
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->MainMenuNode, this->DrawingMenuNode,
					this->AboutMenuButton
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
			this->MainMenuNode->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->ClearMenuButton,
					this->ExitMenuButton
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
			// DrawingMenuNode
			// 
			this->DrawingMenuNode->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
				this->LineMenuButton,
					this->CircleMenuButton, this->EllipseMenuButton, this->заливкаToolStripMenuItem, this->ColorMenuButton
			});
			this->DrawingMenuNode->Name = L"DrawingMenuNode";
			this->DrawingMenuNode->Size = System::Drawing::Size(65, 29);
			this->DrawingMenuNode->Text = L"Draw";
			// 
			// LineMenuButton
			// 
			this->LineMenuButton->Name = L"LineMenuButton";
			this->LineMenuButton->Size = System::Drawing::Size(210, 30);
			this->LineMenuButton->Text = L"Line";
			this->LineMenuButton->Click += gcnew System::EventHandler(this, &MyForm::LineMenuButton_Click);
			// 
			// CircleMenuButton
			// 
			this->CircleMenuButton->Name = L"CircleMenuButton";
			this->CircleMenuButton->Size = System::Drawing::Size(210, 30);
			this->CircleMenuButton->Text = L"Circle";
			this->CircleMenuButton->Click += gcnew System::EventHandler(this, &MyForm::CircleMenuButton_Click);
			// 
			// EllipseMenuButton
			// 
			this->EllipseMenuButton->Name = L"EllipseMenuButton";
			this->EllipseMenuButton->Size = System::Drawing::Size(210, 30);
			this->EllipseMenuButton->Text = L"Ellipse";
			this->EllipseMenuButton->Click += gcnew System::EventHandler(this, &MyForm::EllipseMenuButton_Click);
			// 
			// заливкаToolStripMenuItem
			// 
			this->заливкаToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->seedFillToolStripMenuItem });
			this->заливкаToolStripMenuItem->Name = L"заливкаToolStripMenuItem";
			this->заливкаToolStripMenuItem->Size = System::Drawing::Size(210, 30);
			this->заливкаToolStripMenuItem->Text = L"Fill";
			// 
			// seedFillToolStripMenuItem
			// 
			this->seedFillToolStripMenuItem->Name = L"seedFillToolStripMenuItem";
			this->seedFillToolStripMenuItem->Size = System::Drawing::Size(210, 30);
			this->seedFillToolStripMenuItem->Text = L"Seed fill";
			this->seedFillToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::seedFillToolStripMenuItem_Click);
			// 
			// ColorMenuButton
			// 
			this->ColorMenuButton->Name = L"ColorMenuButton";
			this->ColorMenuButton->Size = System::Drawing::Size(210, 30);
			this->ColorMenuButton->Text = L"Color";
			this->ColorMenuButton->Click += gcnew System::EventHandler(this, &MyForm::ColorMenuButton_Click);
			// 
			// AboutMenuButton
			// 
			this->AboutMenuButton->Name = L"AboutMenuButton";
			this->AboutMenuButton->Size = System::Drawing::Size(74, 29);
			this->AboutMenuButton->Text = L"About";
			this->AboutMenuButton->Click += gcnew System::EventHandler(this, &MyForm::AboutMenuButton_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1284, 1030);
			this->Controls->Add(this->DrawingAreaPB);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->Name = L"MyForm";
			this->Text = L"Seminar N. Sergey Pavlov";
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

		System::Void drawPixelsAndHandleBuffer(System::Collections::Generic::List<Point>^ pixels, const bool & isTemporary);

		System::Void handleDrawObject(const bool & isTemporary);

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

		System::Void seedFillToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		
		System::Void ColorMenuButton_Click(System::Object^  sender, System::EventArgs^  e);
		
		System::Void AboutMenuButton_Click(System::Object^  sender, System::EventArgs^  e);

};
}
