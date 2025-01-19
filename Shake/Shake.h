#include <time.h>
#include <stdlib.h>

namespace Shake {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Collections::Generic;

	public ref class Shake : public System::Windows::Forms::Form
	{
	public:
		Shake(void)
		{
			InitializeComponent();
		}

	protected:
		~Shake()
		{
			if (components)
			{
				delete components;
			}
		}

		virtual void OnPaint(System::Object^ sender, PaintEventArgs^ e) override {
			Graphics^ g = e->Graphics;

			Brush^ fruitBrush = gcnew SolidBrush(Color::Red);
			g->FillRectangle(fruitBrush, fruit_Position.X, fruit_Position.Y, blockSize, blockSize);

			Brush^ snakeBrush = gcnew SolidBrush(Color::Green);
			for each(Point el in Shake_Position)
			{
				g->FillRectangle(snakeBrush, el.X, el.Y, blockSize, blockSize);
			}
		}

	private:
		System::ComponentModel::Container^ components;
		List<Point>^ Shake_Position;
		Point fruit_Position;
		const int blockSize = 20;

		int FruitCount = 0; // Fixed spelling
		Label^ scoreLabel; // Added semicolon

		Timer^ timer;
		int deltaX = 0, deltaY = 0; // Renamed for clarity

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->SuspendLayout();
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(600, 600);
			this->Name = L"Shake";
			this->Text = L"Shake";
			this->BackColor = Color::Black;

			// Initialize the score label
			scoreLabel = gcnew Label(); // Corrected memory allocation
			scoreLabel->ForeColor = Color::White; // Fixed typo
			scoreLabel->BackColor = Color::Transparent;
			scoreLabel->Text = "Score: 0"; // Updated text format
			scoreLabel->Location = Point(10, 10); // Fixed typo
			this->Controls->Add(scoreLabel); // Fixed typo

			this->ResumeLayout(false);

			Shake_Position = gcnew List<Point>();
			Shake_Position->Add(Point(100, 100));
			srand(static_cast<unsigned int>(time(NULL)));
			PlaceFruit();

			timer = gcnew Timer();
			timer->Interval = 100;
			timer->Tick += gcnew EventHandler(this, &Shake::OnTimerTick);
			timer->Start();

			this->Paint += gcnew PaintEventHandler(this, &Shake::OnPaint);
			this->KeyDown += gcnew KeyEventHandler(this, &Shake::OnKeyDown);
		}
#pragma endregion

		void PlaceFruit() {
			int maxX = this->ClientSize.Width / blockSize;
			int maxY = this->ClientSize.Height / blockSize;

			do {
				fruit_Position = Point(rand() % maxX * blockSize, rand() % maxY * blockSize);
			} while (Shake_Position->Contains(fruit_Position));
		}

		void OnTimerTick(System::Object^ sender, EventArgs^ e) {
			MoveShake();

			// Check for boundary collisions
			Point head = Shake_Position[0];
			if (head.X < 0 || head.Y < 0 || head.X >= this->ClientSize.Width || head.Y >= this->ClientSize.Height) {
				timer->Stop();
				MessageBox::Show("Game Over");
				return;
			}

			// Check for self-collision
			for (int i = 1; i < Shake_Position->Count; i++) {
				if (head == Shake_Position[i]) {
					timer->Stop();
					MessageBox::Show("Game Over");
					return;
				}
			}

			// Check for fruit collision
			if (head == fruit_Position) {
				GrowthShake();
				FruitCount++; // Increment fruit count
				scoreLabel->Text = "Score: " + FruitCount; // Update score label
				PlaceFruit();
			}

			this->Invalidate(); // Redraw the form
		}

		void GrowthShake() {
			// Do not remove the tail segment when growing
			Point newHead = Shake_Position[0];
			newHead.X += deltaX * blockSize;
			newHead.Y += deltaY * blockSize;

			Shake_Position->Insert(0, newHead); // Insert new head
		}

		void MoveShake() {
			Point newHead = Shake_Position[0];
			newHead.X += deltaX * blockSize;
			newHead.Y += deltaY * blockSize;

			Shake_Position->Insert(0, newHead); // Insert new head
			Shake_Position->RemoveAt(Shake_Position->Count - 1); // Remove the tail
		}

		void OnKeyDown(System::Object^ sender, KeyEventArgs^ e) {
			switch (e->KeyCode) {
			case Keys::Right:
				deltaX = 1; deltaY = 0; break;
			case Keys::Left:
				deltaX = -1; deltaY = 0; break;
			case Keys::Down:
				deltaX = 0; deltaY = 1; break;
			case Keys::Up:
				deltaX = 0; deltaY = -1; break;
			default:
				break;
			}
		}
	};
}
