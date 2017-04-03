#pragma once
#include "GLUtility.h"

#pragma region Namespace
namespace Forms = System::Windows::Forms;
namespace Comp = System::ComponentModel;
namespace Draw = System::Drawing;
#pragma endregion //Namespace

using namespace System;
using namespace System::Data;
using namespace System::Collections;
using namespace Comp;
using namespace Forms;
using namespace Draw;


namespace MediaPlay_v2 
{
	public ref class MainFrame : public Form
	{
	public:
		MainFrame(void)
		{
			InitializeComponent();
			//Create window
			glWindow = gcnew GLUtility(this, 800, 600);
		}

	protected:
		~MainFrame()
		{
			if (components)
			{
				delete components;
			}
		}
		Comp::Container ^components;
		Forms::Timer^  timer;

	private:
		GLUtility ^ glWindow;

		

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew Comp::Container());
			this->timer = (gcnew Forms::Timer(this->components));

			this->SuspendLayout();
			//
			//Timer
			//
			this->timer->Tick += gcnew System::EventHandler(this, &MediaPlay_v2::MainFrame::OnTick);
			this->timer->Enabled = true;
			this->timer->Interval = 10; //10 miliseconds per tick

			// 
			// GLUtility
			// 
			this->AutoScaleDimensions = Draw::SizeF(6, 13);
			this->AutoScaleMode = Forms::AutoScaleMode::Font;
			this->ClientSize = Draw::Size(800, 600);
			this->Name = L"windowMainFrame";
			this->Text = L"Media Play";
			this->ResumeLayout(false);
		}

		
#pragma endregion
		void OnTick(System::Object ^sender, System::EventArgs ^e);
	};
}


