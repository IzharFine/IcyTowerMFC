// GlView.cpp: implementation of the CGlView class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GlView.h"

#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGlView::CGlView(CWnd *pclWnd)
	: moveX(0)
	, moveY(0)
	, moveZ(0)
	, rotY(-90)
	, moveYadYamin(90)
	, moveYadSmall(90)
	, moveRegelYamin(90)
	, moveRegelSmall(90)
	, rotateX(0)
	, rotateY(0)
	, rotateZ(0)
	, winWidth(0)
	, isJump(false)
	, footCount(0)
	, flipCount(0)
	, isProfile(false)
	, curYpos(-8.5)
	, blockSize(-27.5)
	, robotPos(-35.5)
	, block1(-42.5)
	, block2(-33.5)
	, block3(-25)
	, blockSize2(-6)
	, blockSize3(-8.6)
	, isStart(false)
	, isLeft(false)
	, block4(-16.5)
	, blockSize4(-10.5)
	, blockSizeV(27.5)
	, blockSize2V(5)
	, blockSize3V(10)
	, blockSize4V(10)
	, isFalling(false)
	, isPause(true)
{
	m_pclWnd = pclWnd;
	m_hDC = GetDC(pclWnd->m_hWnd);
	BOOL bSuccess;

	RECT rect;
	m_pclWnd->GetClientRect(&rect);
	int iWidth = rect.right - rect.left;
	int iHeight = rect.bottom - rect.top;

	winWidth = iWidth;

	bSuccess = bSetWindowPixelFormat(m_hDC);
	ASSERT(&bSuccess);

	bSuccess = bCreateViewGLContext(m_hDC);
	ASSERT(&bSuccess);

	vInitGl(iWidth, iHeight);
}

// +
// *****************************************************************************
//   Module      :  CGlView::~CGlView()
//   Access      :  Public
//   Input       :  None
//   Output      :  None
//   Return Val  :  None
//   Exceptions  :  None
//   Desc        :  This function is the one and only destructor. It provides
//									clean up and performs any needed shutdown procedures
//
//   Notes       :  None
// *****************************************************************************
// -
CGlView::~CGlView()
{
	// make the rendering context not current
	if (wglGetCurrentContext() != NULL)
		wglMakeCurrent(NULL, NULL);

	// delete the Context
	if (m_hGLContext != NULL)
	{
		wglDeleteContext(m_hGLContext);
		m_hGLContext = NULL;
	}
}


// +
// *****************************************************************************
//   Module      :  void CGlView::DrawGLScene()	
//   Access      :  Public
//   Input       :  None
//   Output      :  None
//   Return Val  :  None
//   Exceptions  :  None
//   Desc        :  This function is called contiously to provide realtime OpenGl
//									drawing
//
//   Notes       :  Place all reatime rendering code here
// *****************************************************************************
// -
void CGlView::vDrawGLScene()
{
	//glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();
	glTranslatef(0.0f, 25, -12.0f);
	glPushMatrix();
	glTranslatef(0, -25, -50);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, idTexture[0]);//env.bmp
	glPushMatrix();
	glScalef(25,30, 1);
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glTexCoord2f(0, 0);
	glVertex3f(-4, -3, 0);
	glTexCoord2f(0, 3);
	glVertex3f(-4, 3, 0);
	glTexCoord2f(7, 3);
	glVertex3f(4, 3, 0);
	glTexCoord2f(7, 0);
	glVertex3f(4, -3, 0);
	glEnd();
	glPopMatrix();
	glPopMatrix();
	//הזזת צירים

	GLUquadricObj* obj;
	obj = gluNewQuadric();
	gluQuadricTexture(obj, true);

	//Disable color and light effects
	glDisable(GL_TEXTURE_2D);
	

	//BLOX
	glPushMatrix();
	glTranslatef(0, block1, -30);
	glColor3f(0.1f, 0.1f, 0.1f);
	glRectf(blockSize, 0, blockSizeV, 1.5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, block2, -30);
	glColor3f(0.5f, 0.5f, 0.5f);
	glRectf(blockSize2, 0, blockSize2V, 1.5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, block3, -30);
	glColor3f(0.9f, 0.9f, 0.9f);
	glRectf(blockSize3, 0, blockSize3V, 1.5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, block4, -30);
	glColor3f(0.9f, 0.5f, 0.9f);
	glRectf(blockSize4, 0, blockSize4V, 1.5);
	glPopMatrix();

	glTranslatef(moveX, moveY, moveZ);

	//סיבוב צירים
	glRotatef(rotateX, 1, 0, 0);
	glRotatef(rotateY, 0, 1, 0);
	glRotatef(rotateZ, 0, 0, 1);

	////Enable color and light effects
	//glEnable(GL_COLOR_MATERIAL);
	//glEnable(GL_LIGHT0);
	//glEnable(GL_LIGHTING);
	//glEnable(GL_TEXTURE_2D);




	//Disable color and light effects
	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	
	//Enable color and light effects
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);

	//סיבוב צירים
	//glRotatef(45, 1, 0, 0);

	//כיווץ/מתיחה
	//glScalef(1.0, 0.5, 1);

	//axes
	//glBegin(GL_LINES);	
	//    //x  RED
	//    glColor3f(1.0f,0.0f,0.0f);						
	//	glVertex3f( -3.0f, 0.0f, 0.0f);	
	//	glVertex3f( 3.0f, 0.0f, 0.0f);	
	//    //y  GREEN 
	//    glColor3f(0.0f,1.0f,0.0f);						
	//	glVertex3f( 0.0f, -3.0f, 0.0f);	
	//	glVertex3f( 0.0f, 3.0f, 0.0f);	
	//    //z  BLUE
	//    glColor3f(0.0f,0.0f,1.0f);						
	//	glVertex3f( 0.0f, 0.0f, -3.0f);	
	//	glVertex3f( 0.0f, 0.0f, 3.0f);	
 //   glEnd();

	//Triangle
	//glBegin(GL_TRIANGLES);
	//	glColor3f(1.0f, 1.0f, 0.0f);
	//	glVertex3f(-2.0f, 0.0f, 0.0f);
	//	glVertex3f(0.0f, 2.0f, 0.0f);
	//	glVertex3f(2.0f, 0.0f, 0.0f);
	//glEnd();

	//QUAD
	//glBegin(GL_QUADS);
	//	glColor3f(1.0f, 1.0f, 1.0f);
	//	glVertex3f(-2.0f, 0.0f, 0.0f);
	//	glColor3f(1.0f, 0.0f, 0.0f);
	//	glVertex3f(2.0f, 0.0f, 0.0f);
	//	glColor3f(1.0f, 1.0f, 0.0f);
	//	glVertex3f(1.0f, -1.0f, 0.0f);
	//	glColor3f(1.0f, 0.0f, 1.0f);
	//	glVertex3f(-1.0f, -1.0f, 0.0f);
	//glEnd();

	//Polygon
	//glBegin(GL_POLYGON);


	







	glTranslatef(0, 3, -14);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, idTexture[2]);//earth.bmp




	//glTranslatef(7, 0, -7); // FIXED POSITION

		glTranslatef(0, robotPos, -14);
	if (isProfile)
	{
		glRotatef(90, 0, 180, 0); // PROFILE
	}
	if (isLeft)
	{
		glRotatef(-90, 0, 180, 0);
	}

	glRotatef(rotY, 1, 0, 0);//axis(0,0,0) z up
	glColor3f(0.1f, 0.1f, 0.1f);
	gluCylinder(obj, 1, 0, 3, 5, 5);//קרו1

	
	//FIXED POSITION
	glRotatef(90, 1, 0, 0);//axis(0,0,0) z toward us
	glColor3f(1, 0, 0);
	gluSphere(obj, 1.1, 16, 16);//ראש



	//KEREN 1
	glPushMatrix();
	glRotatef(-90, 1, 5, 0);//axis(0,0,0) z up
	glColor3f(0.1f, 0.1f, 0.1f);
	gluCylinder(obj, 1, 0, 2, 5, 5);//קרו2
	glPopMatrix();


	//KEREN 2
	glPushMatrix();
	glRotatef(-90, 1, -5, 0);//axis(0,0,0) z up
	glColor3f(0.1f, 0.1f, 0.1f);
	gluCylinder(obj, 1, 0, 2, 5, 5);//קרו3
	glPopMatrix();


	//EYES
	glPushMatrix();//axis(0,0,0) z toward us
	glTranslatef(0.6f, -0.2f, 0.9f);
	glColor3f(1, 1, 1);
	glPushMatrix();
	glScalef(1.0f, 0.5f, 1.0f);//y=-0.5y
	gluSphere(obj, 0.25, 32, 32);//עין ימין
	glPopMatrix();
	glScalef(1.0f, 0.5f, 1.0f);//y=-0.5y
	glTranslatef(-1.2f, 0, 0);
	gluSphere(obj, 0.25, 32, 32);//עין שמאל
	glPopMatrix();//axis(0,0,0) z toward us

	//ZAVAR
	glPushMatrix();
	glRotatef(90, 1, 0, 0);//axis(0,0,0) z down
	glColor3f(0.1f, 0.7f, 0.1f);
	gluCylinder(obj, 0.5, 0.5, 1.6, 16, 16);//צוואר
	glRotatef(-90, 1, 0, 0);//axis(0,0,0) z toward us
	glPopMatrix();


	//KTEFAIM
	glPushMatrix();
	glTranslatef(0, -1.5, 0);
	glRotatef(90, 1, 0, 0);//axis(0,0,0) z down
	glColor3f(0.1f, 0.4f, 0.1f);
	gluCylinder(obj, 0.5, 2, 1, 16, 16);//חיבור בין גוף לצוואר
	//glRotatef(-90, 1, 0, 0);//axis(0,0,0) z toward us
	glPopMatrix();

	//TAHTIT
	glPushMatrix();
	glTranslatef(0, -4.0, 0);
	glRotatef(-90, 1, 0, 0);//axis(0,0,0) z down
	glColor3f(0.1f, 0.4f, 0.1f);
	gluCylinder(obj, 0,1.7, 0.1, 32, 32);//סגירה לפני הרגליים
	glPopMatrix();

	//SEMEL
	glPushMatrix();
	glTranslatef(0, -3.0,1.8);
	glRotatef(0, 1, 0, 0);//axis(0,0,0) z down
	glColor3f(0.8, 0.8, 0.8);
	gluCylinder(obj, 0, 0.7, 0.1, 32, 32);//עיגול בטן
	glPopMatrix();

	//BETEN
	glPushMatrix();
	glTranslatef(0, -2.5, 0);
	glRotatef(90, 1, 0, 0);//axis(0,0,0) z down
	glColor3f(0.1f, 0.7f, 0.1f);
	gluCylinder(obj, 2, 1.7, 1.7, 16, 16);//גוף
	glRotatef(-90, 1, 0, 0);//axis(0,0,0) z toward us
	glPopMatrix();

	//KATEF YAMIN
	glPushMatrix();
	glTranslatef(2, -2.0, 0);
	glRotatef(90, 1, 0, 0);//axis(0,0,0) z down
	glColor3f(0.1f, 0.4f, 0.1f);
	gluCylinder(obj, 0.7, 0.7,0.5, 16, 16);//כתף ימין
	glPopMatrix();

	//KATEF SMOL
	glPushMatrix();
	glTranslatef(-2, -1.6, 0);
	glRotatef(90, 1, 0, 0);//axis(0,0,0) z down
	glColor3f(0.1f, 0.4f, 0.1f);
	gluCylinder(obj, 0, 0.7, 0.4, 32, 32);//סגירה כתף ימין עליון
	glPopMatrix();


	//???????
	glPushMatrix();
	glTranslatef(-2, -2.6, 0);
	glRotatef(-90, 1, 0, 0);//axis(0,0,0) z down
	glColor3f(0.1f, 0.4f, 0.1f);
	gluCylinder(obj, 0, 0.7, 0.1, 32, 32);//סגירה כתף ימין תחתון
	glPopMatrix();


	//KATEF YAMIN
	glPushMatrix();
	glTranslatef(-2, -2.0, 0);
	glRotatef(90, 1, 0, 0);//axis(0,0,0) z down
	glColor3f(0.1f, 0.4f, 0.1f);
	gluCylinder(obj, 0.7, 0.7, 0.5, 16, 16);//כתף שמאל
	glPopMatrix();

	//KATEF YAMIN
	glPushMatrix();
	glTranslatef(2, -1.6, 0);
	glRotatef(90, 1, 0, 0);//axis(0,0,0) z down
	glColor3f(0.1f, 0.4f, 0.1f);
	gluCylinder(obj, 0, 0.7, 0.4, 32, 32);//סגירה כתף שמאל עליון
	glPopMatrix();


	//????????????
	glPushMatrix();
	glTranslatef(2, -2.6, 0);
	glRotatef(-90, 1, 0, 0);//axis(0,0,0) z down
	glColor3f(0.1f, 0.4f, 0.1f);
	gluCylinder(obj, 0, 0.7, 0.1, 32, 32);//סגירה כתף ימין תחתון
	glPopMatrix();


	//להזיז את rotate(x,0,0,0)את X
	//YADAIM
	glPushMatrix();
	glTranslatef(2.5, -2.5, 0);
	glRotatef(moveYadYamin, 1, 0, 0);//axis(0,0,0) z down
	glColor3f(0.1f, 0.1f, 0.1f);
	gluCylinder(obj, 0.4, 0.4, 2.5, 16, 16);//יד ימין
	glRotatef(-90, 1, 0, 0);//axis(0,0,0) z toward us

	glTranslatef(0, -2.5, 0);
	glRotatef(moveYadYamin, 1, 0, 0);//axis(0,0,0) z toward us
	glColor3f(1, 0, 0);
	gluSphere(obj, 0.4, 16, 16);//כף יד ימין
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2.5, -2.5, 0);
	glRotatef(moveYadSmall, 1, 0, 0);//axis(0,0,0) z down
	glColor3f(0.1f, 0.1f, 0.1f);
	gluCylinder(obj, 0.4, 0.4, 2.5, 16, 16);//יד שמאל
	glRotatef(-90, 1, 0, 0);//axis(0,0,0) z toward us

	glTranslatef(0, -2.5, 0);
	glRotatef(moveYadSmall, 1, 0, 0);//axis(0,0,0) z toward us
	glColor3f(1, 0, 0);
	gluSphere(obj, 0.4, 16, 16);//כף יד שמאל

	glPopMatrix();

	//RAGLAIM
	glPushMatrix();
	glTranslatef(1.3, -4, 0);
	glRotatef(moveRegelYamin, 1, 0, 0);//axis(0,0,0) z down
	glColor3f(0.1f, 0.1f, 0.1f);
	gluCylinder(obj, 0.4, 0.4, 2.5, 16, 16);//רגל ימין
	glRotatef(-90, 1, 0, 0);//axis(0,0,0) z toward us

	glTranslatef(0, -2.7, 0);
	glRotatef(90, 1, 0, 0);//axis(0,0,0) z toward us
	glColor3f(1, 0, 0);
	gluSphere(obj, 0.5, 32, 32);//כף רגל ימין
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.3, -4, 0);
	glRotatef(moveRegelSmall, 1, 0, 0);//axis(0,0,0) z down
	glColor3f(0.1f, 0.1f, 0.1f);
	gluCylinder(obj, 0.4, 0.4, 2.5, 16, 16);//רגל שמאל
	glRotatef(-90, 1, 0, 0);//axis(0,0,0) z toward us

	glTranslatef(0, -2.7, 0);
	glRotatef(90, 1, 0, 0);//axis(0,0,0) z toward us
	glColor3f(1, 0, 0);
	gluSphere(obj, 0.5, 32, 32);//כף רגל שמאל
	glPopMatrix();





	//Disable color and light effects
	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);

	////Disk
	//gluDisk(obj, 2.5f, 3.0f, 4, 4);

	////Partial Disk
	//gluPartialDisk(obj, 2.5f, 3.0f, 32, 32, -90, 180);

	gluDeleteQuadric(obj);


	// swap the buffer
	SwapBuffers(m_hDC);

}

// +
// *****************************************************************************
//   Module      :  BOOL CGlView::SetWindowPixelFormat(HDC hDC)
//   Access      :  Private
//   Input       :  hDC - Handle to the GL windwos device context
//   Output      :  None
//   Return Val  :  TRUE  - success
//									FALSE - failure
//   Exceptions  :  None
//   Desc        :  This function sets up the required pixelformat descriptor
//
//   Notes       :  None
// *****************************************************************************
// -
BOOL CGlView::bSetWindowPixelFormat(HDC hDC)
{
	PIXELFORMATDESCRIPTOR pixelDesc;

	pixelDesc.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pixelDesc.nVersion = 1;

	pixelDesc.dwFlags =

		PFD_DRAW_TO_WINDOW |// Format Must Support Window
		PFD_SUPPORT_OPENGL |// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,	// Must Support Double Buffering
		PFD_TYPE_RGBA,		// Request An RGBA Format
		32,					// Select A 16Bit Color Depth
		0, 0, 0, 0, 0, 0,	// Color Bits Ignored (?)
		0,					// No Alpha Buffer
		0,					// Shift Bit Ignored (?)
		0,					// No Accumulation Buffer
		0, 0, 0, 0,			// Accumulation Bits Ignored (?)
		16,					// 16Bit Z-Buffer (Depth Buffer)  
		0,					// No Stencil Buffer
		0,					// No Auxiliary Buffer (?)
		PFD_MAIN_PLANE,		// Main Drawing Layer
		0,					// Reserved (?)
		0, 0, 0;			// Layer Masks Ignored (?)

	int iGLPixelIndex = ChoosePixelFormat(hDC, &pixelDesc);
	ASSERT(&iGLPixelIndex);

	if (SetPixelFormat(hDC, iGLPixelIndex, &pixelDesc))
		return false;

	return TRUE;
}

// +
// *****************************************************************************
//   Module      :  BOOL CGlView::CreateViewGLContext(HDC hDC)
//   Access      :  Private
//   Input       :  hDC - Handle to the GL windwos device context
//   Output      :  None
//   Return Val  :  TRUE  - success
//									FALSE - failure
//   Exceptions  :  None
//   Desc        :  This function sets up the required GLContext
//
//   Notes       :  None
// *****************************************************************************
// -
BOOL CGlView::bCreateViewGLContext(HDC hDC)
{
	m_hGLContext = wglCreateContext(hDC);
	if (m_hGLContext == NULL)
		return FALSE;

	if (wglMakeCurrent(hDC, m_hGLContext) == FALSE)
		return FALSE;

	return TRUE;
}

// +
// *****************************************************************************
//   Module      :  void CGlView::InitGl(int iWidth, int iHeigth)
//   Access      :  Private
//   Input       :  iWidth  - width of the window
//									iHeight - height of the window
//   Output      :  None
//   Return Val  :  None
//   Exceptions  :  None
//   Desc        :  This function initializes all OpenGL rendering specifics
//
//   Notes       :  None
// *****************************************************************************
// -
void CGlView::vInitGl(int iWidth, int iHeigth)
{

	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glViewport(0, 0, iWidth, iHeigth);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f, (GLfloat)iWidth / (GLfloat)iHeigth, 0.45f, 100.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	generateTextureFromImageFile();
}

void CGlView::generateTextureFromImageFile()
{
	glGenTextures(SIZE, idTexture);

	const char* imageFileName[SIZE] = { "images\\earth.bmp", "images\\env.bmp", "images\\flower.bmp" };

	for (int i = 0; i < SIZE; i++)
	{
		texture = auxDIBImageLoadA(imageFileName[i]);//loads the width, height, colors from the image file (*.bmp) into opengl structure (AUX_RGBImageRec).

		if (texture)
		{
			glBindTexture(GL_TEXTURE_2D, idTexture[i]);//working on idTexture[i]
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//if the target is smaller than the source then minimize it using LINEAR algorithm.
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//if the target is bigger than the source then maximize it using LINEAR algorithm.
			glTexImage2D(GL_TEXTURE_2D, 0, 3, texture->sizeX, texture->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture->data);//save texture in memory.
			free(texture);
			texture = NULL;
		}
	}
}


float CGlView::getMoveX()
{
	return moveX;
}

void CGlView::setMoveX(float moveX)
{
	this->moveX = moveX;
}

float CGlView::getMoveZ()
{
	return moveZ;
}

void CGlView::setMoveZ(float moveZ)
{
	this->moveZ = moveZ;
}

float CGlView::getMoveY()
{
	return moveY;
}

void CGlView::setMoveY(float moveY)
{
	this->moveY = moveY;
}

float CGlView::getMoveYadYamin()
{
	return moveYadYamin;
}

void CGlView::setMoveYadYamin(float moveYadYamin)
{
	this->moveYadYamin = moveYadYamin;
}

float CGlView::getMoveYadSmall()
{
	return moveYadSmall;
}

void CGlView::setMoveYadSmall(float moveYadSmall)
{
	this->moveYadSmall = moveYadSmall;
}

float CGlView::getMoveRegelYamin()
{
	return moveRegelYamin;
}

void CGlView::setMoveRegelYamin(float moveRegelYamin)
{
	this->moveRegelYamin = moveRegelYamin;
}

float CGlView::getMoveRegelSmall()
{
	return moveRegelSmall;
}

void CGlView::setMoveRegelSmall(float moveRegelSmall)
{
	this->moveRegelSmall = moveRegelSmall;
}

float CGlView::getRotY()
{
	return rotY;
}

void CGlView::setRotY(float rotY)
{
	this->rotY = rotY;
}

float CGlView::getRotateX()
{
	return rotateX;
}

void CGlView::setRotateX(float rotateX)
{
	this->rotateX = rotateX;
}

float CGlView::getRotateY()
{
	return rotateY;
}

void CGlView::setRotateY(float rotateY)
{
	this->rotateY = rotateY;
}

// Get Window Width
int CGlView::getWidth()
{
	return winWidth;
}



void CGlView::setJump()
{
	if (isJump)
		isJump = false;
	else
		isJump = true;
}


bool CGlView::getJump()
{
	return isJump;
}
