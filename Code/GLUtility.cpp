#include "GLUtility.h"

GLUtility::GLUtility()
{
	
}

GLUtility::GLUtility(Forms::Form ^ originalForm, int width, int height)
{
	CreateParams^ cparam = gcnew CreateParams;

	// Set the position on the form
	cparam->X = 0;
	cparam->Y = 0;
	cparam->Height = height;
	cparam->Width = width;

	// Specify the form as the parent.
	cparam->Parent = originalForm->Handle;

	// Create as a child of the specified parent and make OpenGL compliant (no clipping)
	cparam->Style = WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	// Create the actual window
	this->CreateHandle(cparam);

	m_hdc = GetDC((HWND)this->Handle.ToPointer());

	if (m_hdc)
	{
		_SetPixelFormat(m_hdc);
		ResizeGLScene(width, height);
		Initialize();
	}
}

GLUtility::~GLUtility()
{
	
}

GLint GLUtility::_SetPixelFormat(HDC hdc)
{
	static	PIXELFORMATDESCRIPTOR pfd =				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		32,											// 32 bits => 2^32 = 16 millions color depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		24,											// 24 bits Z-buffer
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};

	GLint  pxFormat;

	// get the device context's best, available pixel format match 
	if ((pxFormat = ChoosePixelFormat(hdc, &pfd)) == 0)
	{
		MessageBox::Show("ChoosePixelFormat Failed");
		return 0;
	}

	// make that match the device context's current pixel format 
	if (SetPixelFormat(hdc, pxFormat, &pfd) == FALSE)
	{
		MessageBox::Show("SetPixelFormat Failed");
		return 0;
	}

	if ((m_hglrc = wglCreateContext(m_hdc)) == NULL)
	{
		MessageBox::Show("wglCreateContext Failed");
		return 0;
	}

	if ((wglMakeCurrent(m_hdc, m_hglrc)) == NULL)
	{
		MessageBox::Show("wglMakeCurrent Failed");
		return 0;
	}

	//Successful
	return 1;
}

GLvoid GLUtility::ResizeGLScene(int width, int height)
{
	if (height == 0)
	{
		height = 1;
	}

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();//Reset matrix

	gluPerspective(45.0f, (GLdouble)width / (GLdouble)height, 0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();//Reset matrix
}

bool GLUtility::Initialize(GLvoid)
{
	glShadeModel(GL_SMOOTH);							// Enable smooth shading
	glClearColor(Color::DarkCyan.R, Color::DarkCyan.G, Color::DarkCyan.B, 1.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really nice perspective calculations
	return TRUE;										// Initialisation went ok
}

void GLUtility::_SwapBuffers(void)
{
	SwapBuffers(m_hdc);
}

void GLUtility::Render(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear screen and depth buffer
	glLoadIdentity();									// Reset the current modelview matrix
	glTranslatef(-1.5f, 0.0f, -6.0f);						// Move left 1.5 units and into the screen 6.0

	glBegin(GL_TRIANGLES);								// Start drawing a triangle
	glColor3f(1.0f, 0.0f, 0.0f);						// Red
	glVertex3f(0.0f, 1.0f, 0.0f);					// Top Of triangle (front)
	glColor3f(0.0f, 1.0f, 0.0f);						// Green
	glVertex3f(-1.0f, -1.0f, 1.0f);					// Left of triangle (front)
	glColor3f(0.0f, 0.0f, 1.0f);						// Blue
	glVertex3f(1.0f, -1.0f, 1.0f);					// Right of triangle (front)
	glColor3f(1.0f, 0.0f, 0.0f);						// Red
	glVertex3f(0.0f, 1.0f, 0.0f);					// Top Of triangle (right)
	glColor3f(0.0f, 0.0f, 1.0f);						// Blue
	glVertex3f(1.0f, -1.0f, 1.0f);					// Left of triangle (right)
	glColor3f(0.0f, 1.0f, 0.0f);						// Green
	glVertex3f(1.0f, -1.0f, -1.0f);					// Right of triangle (right)
	glColor3f(1.0f, 0.0f, 0.0f);						// Red
	glVertex3f(0.0f, 1.0f, 0.0f);					// Top Of triangle (back)
	glColor3f(0.0f, 1.0f, 0.0f);						// Green
	glVertex3f(1.0f, -1.0f, -1.0f);					// Left of triangle (back)
	glColor3f(0.0f, 0.0f, 1.0f);						// Blue
	glVertex3f(-1.0f, -1.0f, -1.0f);					// Right of triangle (back)
	glColor3f(1.0f, 0.0f, 0.0f);						// Red
	glVertex3f(0.0f, 1.0f, 0.0f);					// Top Of triangle (left)
	glColor3f(0.0f, 0.0f, 1.0f);						// Blue
	glVertex3f(-1.0f, -1.0f, -1.0f);					// Left of triangle (left)
	glColor3f(0.0f, 1.0f, 0.0f);						// Green
	glVertex3f(-1.0f, -1.0f, 1.0f);					// Right of triangle (left)
	glEnd();											// Done drawing the pyramid

	glLoadIdentity();									// Reset the current modelview matrix
	glTranslatef(1.5f, 0.0f, -7.0f);						// Move right 1.5 units and into the screen 7.0

	glBegin(GL_QUADS);									// Draw a quad
	glColor3f(0.0f, 1.0f, 0.0f);						// Set The color to green
	glVertex3f(1.0f, 1.0f, -1.0f);					// Top Right of the quad (top)
	glVertex3f(-1.0f, 1.0f, -1.0f);					// Top Left of the quad (top)
	glVertex3f(-1.0f, 1.0f, 1.0f);					// Bottom left of the quad (top)
	glVertex3f(1.0f, 1.0f, 1.0f);					// Bottom right of the quad (top)
	glColor3f(1.0f, 0.5f, 0.0f);						// Set The color to orange
	glVertex3f(1.0f, -1.0f, 1.0f);					// Top Right of the quad (bottom)
	glVertex3f(-1.0f, -1.0f, 1.0f);					// Top Left of the quad (bottom)
	glVertex3f(-1.0f, -1.0f, -1.0f);					// Bottom left of the quad (bottom)
	glVertex3f(1.0f, -1.0f, -1.0f);					// Bottom right of the quad (bottom)
	glColor3f(1.0f, 0.0f, 0.0f);						// Set The color to red
	glVertex3f(1.0f, 1.0f, 1.0f);					// Top Right of the quad (front)
	glVertex3f(-1.0f, 1.0f, 1.0f);					// Top Left of the quad (front)
	glVertex3f(-1.0f, -1.0f, 1.0f);					// Bottom left of the quad (front)
	glVertex3f(1.0f, -1.0f, 1.0f);					// Bottom right of the quad (front)
	glColor3f(1.0f, 1.0f, 0.0f);						// Set The color to yellow
	glVertex3f(1.0f, -1.0f, -1.0f);					// Top Right of the quad (back)
	glVertex3f(-1.0f, -1.0f, -1.0f);					// Top Left of the quad (back)
	glVertex3f(-1.0f, 1.0f, -1.0f);					// Bottom left of the quad (back)
	glVertex3f(1.0f, 1.0f, -1.0f);					// Bottom right of the quad (back)
	glColor3f(0.0f, 0.0f, 1.0f);						// Set The color to blue
	glVertex3f(-1.0f, 1.0f, 1.0f);					// Top Right of the quad (left)
	glVertex3f(-1.0f, 1.0f, -1.0f);					// Top Left of the quad (left)
	glVertex3f(-1.0f, -1.0f, -1.0f);					// Bottom left of the quad (left)
	glVertex3f(-1.0f, -1.0f, 1.0f);					// Bottom right of the quad (left)
	glColor3f(1.0f, 0.0f, 1.0f);						// Set The color to violet
	glVertex3f(1.0f, 1.0f, -1.0f);					// Top Right of the quad (right)
	glVertex3f(1.0f, 1.0f, 1.0f);					// Top Left of the quad (right)
	glVertex3f(1.0f, -1.0f, 1.0f);					// Bottom left of the quad (right)
	glVertex3f(1.0f, -1.0f, -1.0f);					// Bottom right of the quad (right)
	glEnd();
}