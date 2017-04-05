#include "MainFrame.h"
#include "ContextManager.h"
#include "Model.h"
using namespace MediaPlay_v2;

[STAThreadAttribute]
int main()
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	ContextManager *c = new ContextManager();
	//Model *m=new Model();
	//m->LoadModel();

	Application::Run(gcnew MainFrame());
}