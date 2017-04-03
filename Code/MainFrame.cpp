#include "MainFrame.h"

void MediaPlay_v2::MainFrame::OnTick(System::Object ^sender, System::EventArgs ^e)
{
	UNREFERENCED_PARAMETER(sender);
	UNREFERENCED_PARAMETER(e);
	glWindow->Render();
	glWindow->_SwapBuffers();
}