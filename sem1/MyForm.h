#pragma once

namespace sem1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace std;
	
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
		System::Windows::Forms::NumericUpDown^  Radius1NB;		
		System::Windows::Forms::NumericUpDown^  Radius2NB;
		System::Windows::Forms::Label^  Radius1LBL;
		System::Windows::Forms::Label^  Radius2LBL;
		System::Windows::Forms::Label^  label1;
		System::Windows::Forms::PictureBox^  DrawingAreaPB;
		System::Windows::Forms::ToolStripMenuItem^  заливкаToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^  seedFillToolStripMenuItem;

		System::Drawing::Bitmap^ bm;
		System::Drawing::Graphics^ g;
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
			this->Radius1NB = (gcnew System::Windows::Forms::NumericUpDown());
			this->Radius2NB = (gcnew System::Windows::Forms::NumericUpDown());
			this->Radius1LBL = (gcnew System::Windows::Forms::Label());
			this->Radius2LBL = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DrawingAreaPB))->BeginInit();
			this->menuStrip1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Radius1NB))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Radius2NB))->BeginInit();
			this->SuspendLayout();
			// 
			// DrawingAreaPB
			// 
			this->DrawingAreaPB->Location = System::Drawing::Point(0, 53);
			this->DrawingAreaPB->Name = L"DrawingAreaPB";
			this->DrawingAreaPB->Size = System::Drawing::Size(2270, 1542);
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
			this->menuStrip1->Size = System::Drawing::Size(2282, 49);
			this->menuStrip1->TabIndex = 1;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// MainMenuNode
			// 
			this->MainMenuNode->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->ClearMenuButton,
					this->ExitMenuButton
			});
			this->MainMenuNode->Name = L"MainMenuNode";
			this->MainMenuNode->Size = System::Drawing::Size(138, 45);
			this->MainMenuNode->Text = L"Главная";
			// 
			// ClearMenuButton
			// 
			this->ClearMenuButton->Name = L"ClearMenuButton";
			this->ClearMenuButton->Size = System::Drawing::Size(260, 46);
			this->ClearMenuButton->Text = L"Очистить";
			this->ClearMenuButton->Click += gcnew System::EventHandler(this, &MyForm::ClearMenuButton_Click);
			// 
			// ExitMenuButton
			// 
			this->ExitMenuButton->Name = L"ExitMenuButton";
			this->ExitMenuButton->Size = System::Drawing::Size(260, 46);
			this->ExitMenuButton->Text = L"Выход";
			this->ExitMenuButton->Click += gcnew System::EventHandler(this, &MyForm::ExitMenuButton_Click);
			// 
			// DrawingMenuNode
			// 
			this->DrawingMenuNode->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
				this->LineMenuButton,
					this->CircleMenuButton, this->EllipseMenuButton, this->заливкаToolStripMenuItem, this->ColorMenuButton
			});
			this->DrawingMenuNode->Name = L"DrawingMenuNode";
			this->DrawingMenuNode->Size = System::Drawing::Size(177, 45);
			this->DrawingMenuNode->Text = L"Рисование";
			// 
			// LineMenuButton
			// 
			this->LineMenuButton->Name = L"LineMenuButton";
			this->LineMenuButton->Size = System::Drawing::Size(243, 46);
			this->LineMenuButton->Text = L"Линия";
			this->LineMenuButton->Click += gcnew System::EventHandler(this, &MyForm::LineMenuButton_Click);
			// 
			// CircleMenuButton
			// 
			this->CircleMenuButton->Name = L"CircleMenuButton";
			this->CircleMenuButton->Size = System::Drawing::Size(243, 46);
			this->CircleMenuButton->Text = L"Круг";
			this->CircleMenuButton->Click += gcnew System::EventHandler(this, &MyForm::CircleMenuButton_Click);
			// 
			// EllipseMenuButton
			// 
			this->EllipseMenuButton->Name = L"EllipseMenuButton";
			this->EllipseMenuButton->Size = System::Drawing::Size(243, 46);
			this->EllipseMenuButton->Text = L"Эллипс";
			this->EllipseMenuButton->Click += gcnew System::EventHandler(this, &MyForm::EllipseMenuButton_Click);
			// 
			// заливкаToolStripMenuItem
			// 
			this->заливкаToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->seedFillToolStripMenuItem });
			this->заливкаToolStripMenuItem->Name = L"заливкаToolStripMenuItem";
			this->заливкаToolStripMenuItem->Size = System::Drawing::Size(243, 46);
			this->заливкаToolStripMenuItem->Text = L"Заливка";
			// 
			// seedFillToolStripMenuItem
			// 
			this->seedFillToolStripMenuItem->Name = L"seedFillToolStripMenuItem";
			this->seedFillToolStripMenuItem->Size = System::Drawing::Size(307, 46);
			this->seedFillToolStripMenuItem->Text = L"Затравочная";
			this->seedFillToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::seedFillToolStripMenuItem_Click);
			// 
			// ColorMenuButton
			// 
			this->ColorMenuButton->Name = L"ColorMenuButton";
			this->ColorMenuButton->Size = System::Drawing::Size(243, 46);
			this->ColorMenuButton->Text = L"Цвет";
			this->ColorMenuButton->Click += gcnew System::EventHandler(this, &MyForm::ColorMenuButton_Click);
			// 
			// AboutMenuButton
			// 
			this->AboutMenuButton->Name = L"AboutMenuButton";
			this->AboutMenuButton->Size = System::Drawing::Size(216, 45);
			this->AboutMenuButton->Text = L"О программе";
			this->AboutMenuButton->Click += gcnew System::EventHandler(this, &MyForm::AboutMenuButton_Click);
			// 
			// Radius1NB
			// 
			this->Radius1NB->Location = System::Drawing::Point(1284, 9);
			this->Radius1NB->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000, 0, 0, 0 });
			this->Radius1NB->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->Radius1NB->Name = L"Radius1NB";
			this->Radius1NB->Size = System::Drawing::Size(120, 38);
			this->Radius1NB->TabIndex = 2;
			this->Radius1NB->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			// 
			// Radius2NB
			// 
			this->Radius2NB->Location = System::Drawing::Point(1665, 7);
			this->Radius2NB->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000, 0, 0, 0 });
			this->Radius2NB->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->Radius2NB->Name = L"Radius2NB";
			this->Radius2NB->Size = System::Drawing::Size(120, 38);
			this->Radius2NB->TabIndex = 2;
			this->Radius2NB->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			// 
			// Radius1LBL
			// 
			this->Radius1LBL->AutoSize = true;
			this->Radius1LBL->Location = System::Drawing::Point(1032, 9);
			this->Radius1LBL->Name = L"Radius1LBL";
			this->Radius1LBL->Size = System::Drawing::Size(225, 32);
			this->Radius1LBL->TabIndex = 3;
			this->Radius1LBL->Text = L"Первый радиус:";
			// 
			// Radius2LBL
			// 
			this->Radius2LBL->AutoSize = true;
			this->Radius2LBL->Location = System::Drawing::Point(1420, 11);
			this->Radius2LBL->Name = L"Radius2LBL";
			this->Radius2LBL->Size = System::Drawing::Size(218, 32);
			this->Radius2LBL->TabIndex = 3;
			this->Radius2LBL->Text = L"Второй радиус:";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(759, 11);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(245, 32);
			this->label1->TabIndex = 3;
			this->label1->Text = L"Радиусы эллипса";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(16, 31);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(2282, 1597);
			this->Controls->Add(this->Radius2LBL);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->Radius1LBL);
			this->Controls->Add(this->Radius2NB);
			this->Controls->Add(this->Radius1NB);
			this->Controls->Add(this->DrawingAreaPB);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"MyForm";
			this->Text = L"Семинар 1. Брезенхем. Павлов С.Ю.";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DrawingAreaPB))->EndInit();
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Radius1NB))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Radius2NB))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: 
		System::Void DrawLine(const Line line, Color col);

		System::Drawing::Point pointStart, pointEnd;

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
