#pragma once

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

namespace Forms = System::Windows::Forms;
namespace Draw = System::Drawing;
using namespace Forms;
using namespace Draw;

public ref class GLUtility: public Forms::NativeWindow
{
public:
	GLUtility();
	GLUtility(Forms::Form ^ originalForm, int width, int height);

	~GLUtility();
	GLint _SetPixelFormat(HDC hdc);	
	GLvoid ResizeGLScene(int width, int height);
	bool Initialize(GLvoid);
	void Render(void);
	void _SwapBuffers(void);

private:
	HDC m_hdc;
	HGLRC m_hglrc;
};

