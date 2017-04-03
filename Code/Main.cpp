#include "MainFrame.h"

using namespace MediaPlay_v2;

[STAThreadAttribute]
int main()
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);


	Application::Run(gcnew MainFrame());
}