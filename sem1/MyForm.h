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
		//line(int x0, int y0, int xfin, int yfin)
		//{
		//	x1 = x0;
		//	y1 = y0;
		//	x2 = xfin;
		//	y2 = yfin;
		//}
		int x1;
		int y1;
		int x2;
		int y2;
	};

	/// <summary>
	/// —водка дл€ MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
		Bitmap^ bm;
		Graphics^ g;
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			// 20 september deadline.
			//Graphics^ grp = 
			bm = gcnew Bitmap(pictureBox1->Width, pictureBox1->Height);
			pictureBox1->Image = bm;
			g = Graphics::FromImage(bm);
			g->Clear(Color::White);

			//vector<Line> lines;

			//lines.push_back({ 10, 10, 100, 100 });
			//lines.push_back({ 50, 10, 300, 150 });
			//lines.push_back({ 400, 300, 50, 200 });
			//lines.push_back({ 30, 30, 700, 700 });

			//DrawLines(lines, Color::Blue);

			DrawLine({ 10, 10, 100, 100 }, Color::Red);

			//DrawCircle(100, 100, 60);
			DrawEllipse(100, 100, 60, 60);

			//

			//delete g;
		}




	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^  pictureBox1;

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
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(-2, -7);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(2176, 1514);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Click += gcnew System::EventHandler(this, &MyForm::pictureBox1_Click);
			this->pictureBox1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pb_MouseDown);
			this->pictureBox1->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pb_MouseUp);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(16, 31);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(2167, 1507);
			this->Controls->Add(this->pictureBox1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion

	private: System::Void pictureBox1_Click(System::Object^  sender, System::EventArgs^  e)
	{

	}

			 //private: System::Void DrawLines(const vector<Line> lines, Color^ col)
			 //{
			 //	for (auto line : lines)
			 //	{
			 //		DrawLine(line, col);
			 //	}
			 //}

	private: System::Void DrawLine(const Line line, Color^ col)
	{
		DrawLine(line.x1, line.y1, line.x2, line.y2, col);
	}


	private: System::Void DrawLine(const int& x1, const int& y1, const int& x2, const int& y2, Color^ col)
	{
		SolidBrush^ brush = gcnew SolidBrush(Color::Red);

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

		g->FillRectangle(brush, x, y, 1, 1);

		for (size_t i = 1; i <= *DefChDelta; i++)
		{
			*DefChanged += *DefChSign;

			if (E <= 0)
			{
				E += 2 * *UndefChDelta;
			}
			else
			{
				E -= 2 * *DefChDelta;
				*UndefChanged += *UndefChSign;
			}

			g->FillRectangle(brush, x, y, 1, 1);

		}

		//delete DefChanged;
		//delete UndefChanged;
		//delete DefChSign;
		//delete UndefChSign;
		//delete DefChDelta;
		//delete UndefChDelta;

		pictureBox1->Refresh();
	}

	private: System::Void DrawCircle(const int& x0, const int& y0, const int& R)
	{
		SolidBrush^ brush = gcnew SolidBrush(Color::Red);

		int x = 0, y = R;

		//g->FillRectangle(brush, x, y, 1, 1);

		int D = 2 * (1 - R);
		int lim = 0;

		int T;

		do
		{
			g->FillRectangle(brush, x + x0, y + y0, 1, 1);
			g->FillRectangle(brush, x + x0, -y + y0, 1, 1);
			g->FillRectangle(brush, -x + x0, y + y0, 1, 1);
			g->FillRectangle(brush, -x + x0, -y + y0, 1, 1);

			if (D < 0)
			{
				T = 2 * D + 2 * y - 1;
			}
			else if (D > 0)
			{
				T = 2 * D - 2 * x - 1;
			}

			if (D < 0 && T <= 0) // => 
			{
				x++;
				D += 2 * x + 1;
			}
			else if (D > 0 && T > 0) // => 
			{
				y--;
				D += -2 * y + 1;
			}
			else // D == 0 || близко к диагонали.
			{
				x++; y--;
				D += 2 * x - 2 * y + 2;
			}

			int xRefl = x - x0, yRefl = y - y0;


		} while (y >= lim);

		//g->FillRectangle(brush, x, y, 1, 1);



		pictureBox1->Refresh();
	}
	private: System::Void DrawEllipse(const int& x0, const int& y0, const int& a, const int& b)
	{
		SolidBrush^ brush = gcnew SolidBrush(Color::Red);

		int x = 0, y = b;

		//g->FillRectangle(brush, x, y, 1, 1);

		int D = a*a - 2 * a*a*b + b*b;
		int lim = 0;

		int T;

		do
		{
			g->FillRectangle(brush, x + x0, y + y0, 1, 1);
			g->FillRectangle(brush, x + x0, -y + y0, 1, 1);
			g->FillRectangle(brush, -x + x0, y + y0, 1, 1);
			g->FillRectangle(brush, -x + x0, -y + y0, 1, 1);

			if (D < 0)
			{
				T = 2 * D + (2 * y - 1)*a*a;
			}
			else if (D > 0)
			{
				T = 2 * D - (2 * x + 1)*b*b;
			}

			if (D < 0 && T <= 0) // => 
			{
				x++;
				D += (2 * x + 1)*b*b;
			}
			else if (D > 0 && T > 0) // => 
			{
				y--;
				D += (-2 * y + 1)*a*a;
			}
			else // D == 0 || близко к диагонали.
			{
				x++; y--;
				D += (2 * x + 1)*b*b + (-2 * y + 1)*a*a;
			}

			int xRefl = x - x0, yRefl = y - y0;


		} while (y >= lim);

		//g->FillRectangle(brush, x, y, 1, 1);



		pictureBox1->Refresh();
	}
    private: System::Drawing::Point lineStart, lineEnd;

	private: System::Void pb_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) 
	{
		lineStart = getCurMousePBPosition();
	}
	private: System::Void pb_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) 
	{
		lineEnd = getCurMousePBPosition();
		DrawLine({ lineStart.X, lineStart.Y, lineEnd.X, lineEnd.Y }, Color::Orange);
	}
	private: System::Drawing::Point getCurMousePBPosition()
	{
		Point Cur = Cursor->Position, PB = pictureBox1->PointToScreen(Point(0, 0));
		return Point(Cur.X - PB.X, Cur.Y - PB.Y);
	}

	};
}
