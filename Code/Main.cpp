#include "MainFrame.h"
#include "ContextManager.h"
using namespace MediaPlay_v2;

[STAThreadAttribute]
int main()
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	ContextManager *c = new ContextManager();
	Vertex *v;
	c->LoadModel("/../Asset/Man.obj", v);

	Application::Run(gcnew MainFrame());
}