// GlView.h: interface for the CGlView class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GLVIEW_H__6EDA23AE_B764_11D5_8D52_0004AC3DB799__INCLUDED_)
#define AFX_GLVIEW_H__6EDA23AE_B764_11D5_8D52_0004AC3DB799__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <gl/GLAUX.H> // Header File For The glaux Library

#define SIZE 3
class CGlView  
{
public:
	CGlView(CWnd *pclWnd);
	~CGlView();

	void vDrawGLScene();

	protected:
	private:
		void vInitGl(int iWidth, int iHeigth);
		BOOL bSetWindowPixelFormat(HDC hDC);
		BOOL bCreateViewGLContext(HDC hDC);

	// members //////////////////////////////////////////////////////////
	public:
	protected:
	private:			
		HGLRC	m_hGLContext;	// required GLContext
		CWnd *m_pclWnd;			// window inwhich opengl will be drawn
		HDC		m_hDC;			// handle to m_pclWnds device context
		float moveX, moveY, moveZ,moveYadYamin, moveYadSmall, moveRegelYamin, moveRegelSmall,rotY;
		float rotateX, rotateY, rotateZ;
public:

	float getMoveZ();
	void setMoveZ(float moveZ);


	float getMoveX();
	float getMoveY();

	float getMoveYadYamin();
	float getMoveYadSmall();

	float getMoveRegelYamin();
	float getMoveRegelSmall();

	void setMoveX(float moveX);
	void setMoveY(float moveY);

	void setMoveYadYamin(float moveYadYamin);
	void setMoveYadSmall(float moveYadSmall);

	void setMoveRegelYamin(float moveRegelYamin);
	void setMoveRegelSmall(float moveRegelSmall);
	void generateTextureFromImageFile();

	float getRotY();
	void setRotY(float rotY);

	//Rotate
	float getRotateX();
	void setRotateX(float rotateX);
	float getRotateY();
	void setRotateY(float rotateY);
	float getRotateZ();
	void setRotateZ(float rotateZ);
private:
	GLuint idTexture[SIZE];
	AUX_RGBImageRec* texture;
public:
	// Get Window Width
	int getWidth();
	int winWidth;
	bool isJump;
	void setJump();
	bool getJump();
	int footCount;
	int flipCount;
	bool isProfile;
	float curYpos;
	float blockSize;
	float robotPos;
	float block1;
	float block2;
	float block3;
	float blockSize2;
	float blockSize3;
	bool isStart;
	bool isLeft;
	float block4;
	float blockSize4;
	float blockSizeV;
	double blockSize2V;
	float blockSize3V;
	float blockSize4V;
	bool isFalling;
	bool isPause;
};

#endif

