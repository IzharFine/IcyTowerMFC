
// OpenGLDlg.cpp : implementation file
//

#include "stdafx.h"
#include "OpenGL.h"
#include "OpenGLDlg.h"
#include "afxdialogex.h"
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// COpenGLDlg dialog



COpenGLDlg::COpenGLDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_OPENGL_DIALOG, pParent)
	, isOver(true)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void COpenGLDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON4, pauseBTN);
}

BEGIN_MESSAGE_MAP(COpenGLDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
//	ON_NOTIFY(UDN_DELTAPOS, IDC_MOVEX, &COpenGLDlg::OnDeltaposMovex)
//ON_NOTIFY(UDN_DELTAPOS, IDC_MOVEX, &COpenGLDlg::OnDeltaposMovex)
ON_NOTIFY(UDN_DELTAPOS, IDC_MOVE_X, &COpenGLDlg::OnDeltaposMoveX)
//ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, &COpenGLDlg::OnDeltaposMoveY)
ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, &COpenGLDlg::OnDeltaposMoveY)
ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN2, &COpenGLDlg::OnDeltaposSpin2)

ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN4, &COpenGLDlg::OnDeltaposSpin4)
ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN5, &COpenGLDlg::OnDeltaposSpin5)
ON_BN_CLICKED(IDC_BUTTON1, &COpenGLDlg::OnBnClickedButton1)
ON_BN_CLICKED(IDC_BUTTON2, &COpenGLDlg::OnBnClickedButton2)
ON_BN_CLICKED(IDC_BUTTON3, &COpenGLDlg::OnBnClickedButton3)
ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN6, &COpenGLDlg::OnDeltaposSpin6)
ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN7, &COpenGLDlg::OnDeltaposSpin7)
ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN8, &COpenGLDlg::OnDeltaposSpin8)
ON_NOTIFY(UDN_DELTAPOS, IDC_MOVE_X3, &COpenGLDlg::OnDeltaposMoveX3)
ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN10, &COpenGLDlg::OnDeltaposSpin10)
ON_WM_TIMER()
ON_WM_MOUSEMOVE()
//ON_WM_MOUSEWHEEL()
ON_BN_CLICKED(IDC_BUTTON4, &COpenGLDlg::OnBnClickedButton4)
ON_WM_MOUSEACTIVATE()
ON_WM_LBUTTONDOWN()
//ON_WM_KEYDOWN()
ON_BN_CLICKED(IDC_BUTTON5, &COpenGLDlg::OnBnClickedButton5)
END_MESSAGE_MAP()


// COpenGLDlg message handlers

BOOL COpenGLDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	//ptrView = new CGlView(this);
	CWnd* wnd = GetDlgItem(IDC_PICTURE);
	ptrView = new CGlView(wnd);
	PlaySoundA((LPCSTR)"\icy.wav", NULL, SND_ASYNC);
	
	//SetTimer(1, 10, NULL);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void COpenGLDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void COpenGLDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();

		ptrView->vDrawGLScene();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR COpenGLDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void COpenGLDlg::OnDeltaposMoveX(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	// TODO: Add your control notification handler code here
	ptrView->setMoveX(ptrView->getMoveX() - 0.5*pNMUpDown->iDelta);
	ptrView->vDrawGLScene();

	*pResult = 0;
}





void COpenGLDlg::OnDeltaposMoveY(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	ptrView->setMoveY(ptrView->getMoveY() - 0.5*pNMUpDown->iDelta);
	ptrView->vDrawGLScene();

	*pResult = 0;
}



void COpenGLDlg::OnDeltaposSpin2(NMHDR *pNMHDR, LRESULT *pResult)//הזזת יד ימין
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	ptrView->setMoveYadYamin(ptrView->getMoveYadYamin() - 0.9*pNMUpDown->iDelta);
	ptrView->vDrawGLScene();

	*pResult = 0;
}





void COpenGLDlg::OnDeltaposSpin4(NMHDR *pNMHDR, LRESULT *pResult)//הזזת רגל ימין
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	if (ptrView->getMoveRegelYamin()<=190 && ptrView->getMoveRegelYamin()>0)
	{
		ptrView->setMoveRegelYamin(ptrView->getMoveRegelYamin() - 0.9*pNMUpDown->iDelta);
		ptrView->vDrawGLScene();
	}
	else
	{
		ptrView->setMoveRegelYamin(90);
	}
	

	*pResult = 0;
}


void COpenGLDlg::OnDeltaposSpin5(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	if (ptrView->getMoveRegelSmall() <= 190 && ptrView->getMoveRegelSmall() > 0)
	{
		ptrView->setMoveRegelSmall(ptrView->getMoveRegelSmall() - 0.9*pNMUpDown->iDelta);
		ptrView->vDrawGLScene();
	}
	else
	{
		ptrView->setMoveRegelSmall(90);
	}
	*pResult = 0;
}





void COpenGLDlg::OnBnClickedButton1()
{
	isOver = true;
	ptrView->setMoveRegelYamin(90);
	ptrView->setMoveRegelSmall(90);
	ptrView->setMoveYadYamin(90);
	ptrView->setMoveYadSmall(90);
	ptrView->setMoveX(0);
	ptrView->setMoveY(0);
	ptrView->setMoveZ(0);
	ptrView->setRotY(-90);

	ptrView->setRotateX(0);
	ptrView->setRotateY(0);

	ptrView->isJump = false;
	ptrView->footCount = 0;
	ptrView->flipCount = 0;
	ptrView->isProfile = false;
	ptrView->curYpos = -8.5;
	ptrView->blockSize = -27.5;
	ptrView->robotPos = -35.5;
		ptrView->block1 = -42.5;
		ptrView->block2 = -33.5;
		ptrView->block3 = -25;
		ptrView->blockSize2 = -6;
		ptrView->blockSize3 = -8.6;
		ptrView->isStart = false;
		ptrView->isLeft = false;
		ptrView->block4 = -16.5;
		ptrView->blockSize4 = -10.5;
		ptrView->blockSizeV = 27.5;
		ptrView->blockSize2V = 5;
		ptrView->blockSize3V = 10;
		ptrView->blockSize4V = 10;
		ptrView->isFalling = false;

		PlaySoundA((LPCSTR)"\icy.wav", NULL, SND_ASYNC);


	//ptrView->setRotateZ(0);
	ptrView->vDrawGLScene();
	//לאפס מחדש הכל

}



void COpenGLDlg::OnBnClickedButton2()//save
{
	// TODO: Add your control notification handler code here
	// Create some elliptic region as demonstration
	CRect rect;
	GetClientRect(&rect);
	CRgn rgn;
	rgn.CreateRectRgn(0, 0, rect.Width() + 50, rect.Height() + 50);
	
	// Get the size in bytes of our created region
	int iSize = rgn.GetRegionData(NULL, sizeof(RGNDATA));

	// Allocate memory to hold the region data
	RGNDATA* pData = (RGNDATA*)calloc(iSize, 1);
	pData->rdh.dwSize = iSize;

	// Get the region data
	int iSize2 = rgn.GetRegionData(pData, iSize);
	// Sanity check
	if (iSize != iSize2)
		AfxMessageBox(_T("Something wrong with GetRegionData..."));

	// Save region data to a file
	CFile f(_T("test_region.rgn"), CFile::modeCreate | CFile::modeWrite);
	f.Write(pData, iSize);
	f.Close();

	// Free allocated memory
	free(pData);
}


void COpenGLDlg::OnBnClickedButton3()//load
{

	CFile f(_T("test_region.rgn"), CFile::modeRead);

	// Get size of the file
	int iSize = f.GetLength();
	RGNDATA* pData = (RGNDATA*)calloc(iSize, 1);

	// Read region data from file
	f.Read(pData, iSize);
	f.Close();

	// Create region from loaded region data
	CRgn rgn;
	rgn.CreateFromData(NULL, iSize, pData);

	// As a demonstration, set the loaded region as window region
	// so it is visually clear that it got loaded correctly.
	SetWindowRgn(rgn, TRUE);
	// Free allocated memory
	free(pData);
}




void COpenGLDlg::OnDeltaposSpin6(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	ptrView->setRotY(ptrView->getRotY() - 0.5*pNMUpDown->iDelta);
	ptrView->vDrawGLScene();

	*pResult = 0;
}


void COpenGLDlg::OnDeltaposSpin7(NMHDR *pNMHDR, LRESULT *pResult)
{

		LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
		// TODO: Add your control notification handler code here

		ptrView->setMoveZ(ptrView->getMoveZ() - 0.5*pNMUpDown->iDelta);
		ptrView->vDrawGLScene();

		*pResult = 0;
	
}


void COpenGLDlg::OnDeltaposSpin8(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here

	ptrView->setRotateX(ptrView->getRotateX() + 5 * pNMUpDown->iDelta);
	ptrView->vDrawGLScene();

	*pResult = 0;
}


void COpenGLDlg::OnDeltaposSpin9(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}


void COpenGLDlg::OnDeltaposMoveX3(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here

	ptrView->setRotateY(ptrView->getRotateY() - 5 * pNMUpDown->iDelta);
	ptrView->vDrawGLScene();

	*pResult = 0;
}


void COpenGLDlg::OnDeltaposSpin10(NMHDR *pNMHDR, LRESULT *pResult)//יד שמאל
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	ptrView->setMoveYadSmall(ptrView->getMoveYadSmall() - 0.9*pNMUpDown->iDelta);
	ptrView->vDrawGLScene();

	*pResult = 0;
}


void COpenGLDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (ptrView->isStart)
	{
		//ptrView->curYpos -= 0.1;
		ptrView->block1 -= 0.1;
		ptrView->block2 -= 0.1;
		ptrView->block3 -= 0.1;
		ptrView->block4-= 0.1;
	}

	CDialogEx::OnTimer(nIDEvent);
	if (ptrView->getJump())
	{
		ptrView->setRotY(ptrView->getRotY() + 10);
		if (ptrView->flipCount<71)
		{
			if (ptrView->flipCount < 36)
			{
				//ptrView->curYpos -= 0.1;
				//ptrView->setMoveY(ptrView->getMoveY() + 0.1);
				ptrView->robotPos += 0.4;
				ptrView->block1 -= 0.2;
				ptrView->block2 -= 0.2;
				ptrView->block3 -= 0.2;
				ptrView->block4 -= 0.2;
			}
			//else
			//{
			//	ptrView->setMoveY(ptrView->getMoveY() - 0.33);
			//}
			ptrView->flipCount++;
		}
		else
		{
			ptrView->setJump();
			ptrView->flipCount = 0;
		}
	}
	if (ptrView->footCount < 15)
	{
		ptrView->footCount++;
		ptrView->setMoveYadSmall(ptrView->getMoveYadSmall() + 2);
		ptrView->setMoveYadYamin(ptrView->getMoveYadYamin() - 2);
		ptrView->setMoveRegelYamin(ptrView->getMoveRegelYamin() + 3);
		ptrView->setMoveRegelSmall(ptrView->getMoveRegelSmall() - 3);
	}
	else if (ptrView->footCount < 30)
	{
		ptrView->setMoveYadSmall(ptrView->getMoveYadSmall() - 2);
		ptrView->setMoveYadYamin(ptrView->getMoveYadYamin() + 2);
		ptrView->footCount++;
		ptrView->setMoveRegelYamin(ptrView->getMoveRegelYamin() - 3);
		ptrView->setMoveRegelSmall(ptrView->getMoveRegelSmall() + 3);
	}
	else
		ptrView->footCount = 0;
	if (ptrView->block1 <= -43.5)
	{
		ptrView->block1 = -8.5;
		do
		{
			ptrView->blockSize = (rand() % 26 + 1) - (rand() % 55 + 1);
			ptrView->blockSizeV = (rand() % 26 + 1) - (rand() % 55 + 1);
			if (ptrView->blockSize > ptrView->blockSizeV)
			{
				int change = ptrView->blockSize;
				ptrView->blockSize = ptrView->blockSizeV;
				ptrView->blockSizeV = change;
			}
		} while (ptrView->blockSizeV - ptrView->blockSize <= 12);
	}
	else if (ptrView->block2 <= -43.5)
	{
		ptrView->block2 = -8.5;
		do
		{
		ptrView->blockSize2 = (rand() % 26 + 1) - (rand() % 55 + 1);
		ptrView->blockSize2V = (rand() % 26 + 1) - (rand() % 55 + 1);
		if (ptrView->blockSize2 > ptrView->blockSize2V)
		{
			int change = ptrView->blockSize2;
			ptrView->blockSize2 = ptrView->blockSize2V;
			ptrView->blockSize2V = change;
		}
		} while (ptrView->blockSize2V - ptrView->blockSize2 <= 12);
	}
	else if (ptrView->block3 <= -43.5)
	{
		do
		{
			ptrView->block3 = -8.5;
			ptrView->blockSize3 = (rand() % 26 + 1) - (rand() % 55 + 1);
			ptrView->blockSize3V = (rand() % 26 + 1) - (rand() % 55 + 1);
			if (ptrView->blockSize3 > ptrView->blockSize3V)
			{
				int change = ptrView->blockSize3;
				ptrView->blockSize3 = ptrView->blockSize3V;
				ptrView->blockSize3V = change;
			}
		} while (ptrView->blockSize3V - ptrView->blockSize3 <= 12);
	}
	else if (ptrView->block4 <= -43.5)
	{
		ptrView->block4 = -8.5;
		do
		{
		ptrView->blockSize4 = (rand() % 26 + 1) - (rand() % 55 + 1);
		ptrView->blockSize4V = (rand() % 26 + 1) - (rand() % 55 + 1);
		if (ptrView->blockSize4 > ptrView->blockSize4V)
		{
			int change = ptrView->blockSize4;
			ptrView->blockSize4 = ptrView->blockSize4V;
			ptrView->blockSize4V = change;
		}
		} while (ptrView->blockSize4V - ptrView->blockSize4 <= 12);
	}
	if ((ptrView->robotPos - 7.05 <= ptrView->block1 && ptrView->robotPos - 6.95 >= ptrView->block1) && !((ptrView->getMoveX() >= (ptrView->blockSize) && ptrView->getMoveX() <= ptrView->blockSizeV))
		|| (ptrView->robotPos - 7.05 <= ptrView->block2 && ptrView->robotPos - 6.95 >= ptrView->block2) && !((ptrView->getMoveX() >= (ptrView->blockSize2) && ptrView->getMoveX() <= ptrView->blockSize2V))
		|| (ptrView->robotPos - 7.05 <= ptrView->block3 && ptrView->robotPos - 6.95 >= ptrView->block3) && !((ptrView->getMoveX() >= (ptrView->blockSize3) && ptrView->getMoveX() <= ptrView->blockSize3V))
		|| (ptrView->robotPos - 7.05 <= ptrView->block4 && ptrView->robotPos - 6.95 >= ptrView->block4) && !((ptrView->getMoveX() >= (ptrView->blockSize4) && ptrView->getMoveX() <= ptrView->blockSize4V))
		|| !(ptrView->robotPos - 7.05 <= ptrView->block1 && ptrView->robotPos - 6.95 >= ptrView->block1 ||
			ptrView->robotPos - 7.05 <= ptrView->block2 && ptrView->robotPos - 6.95 >= ptrView->block2 ||
			ptrView->robotPos - 7.05 <= ptrView->block3 && ptrView->robotPos - 6.95 >= ptrView->block3 ||
			ptrView->robotPos - 7.05 <= ptrView->block4 && ptrView->robotPos - 6.95 >= ptrView->block4))
	{
		if (!ptrView->isJump)
		{
			ptrView->robotPos -= 0.2;
			ptrView->isFalling = true;
		}
	}
	else
		ptrView->isFalling = false;
	if (ptrView->robotPos <= -43.5)
	{
		if (isOver)
			EndGame();
	}
	ptrView->vDrawGLScene();
}

//ptrView->blockSize2 = (rand() % 28 + 1) - (rand() % 55 + 1);


void COpenGLDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CDialogEx::OnMouseMove(nFlags, point);
	if (!ptrView->isPause) {
		if (point.x > ptrView->getMoveX() + 300 && ptrView->getMoveX() < 20) // NEED TO FIX 11
		{
			ptrView->isLeft = false;
			ptrView->setMoveX(ptrView->getMoveX() + 0.5);
			ptrView->isProfile = true;
		}
		else if (point.x < ptrView->getMoveX() + 300 && ptrView->getMoveX()>-20) // NEED TO FIX 11
		{
			ptrView->isProfile = false;
			ptrView->setMoveX(ptrView->getMoveX() - 0.5);
			ptrView->isLeft = true;
		}
		else
		{
			ptrView->isLeft = false;
			ptrView->isProfile = false;
		}
	}
}



//BOOL COpenGLDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
//{
//
//	// TODO: Add your message handler code here and/or call default
//	if (!ptrView->isFalling)
//	{
//		ptrView->setJump();
//		
//	}
//	ptrView->isStart = true;
//	return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
//}




void COpenGLDlg::OnBnClickedButton4()
{
	ptrView->isPause = !ptrView->isPause;
	if (ptrView->isPause)
	{
		pauseBTN.SetWindowTextW(L"Start");
		SetTimer(1, 99999999, NULL);
	}
	else
	{
		pauseBTN.SetWindowTextW(L"Pause");
		SetTimer(1, 10, NULL);
	}
	// TODO: Add your control notification handler code here
}


void COpenGLDlg::EndGame()
{
	isOver = !isOver;
	AfxMessageBox(_T("GAME OVER"));
	OnBnClickedButton1();
}




void COpenGLDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	if (!ptrView->isFalling && !ptrView->isPause)
	{
		ptrView->setJump();
		switch (rand() % 3 + 1)
		{
		case 1:PlaySoundA((LPCSTR)"\jump1.wav", NULL, SND_ASYNC);
			break;
		case 2:PlaySoundA((LPCSTR)"\jump2.wav", NULL, SND_ASYNC);
			break;
		case 3:PlaySoundA((LPCSTR)"\jump3.wav", NULL, SND_ASYNC);
			break;
		}
		ptrView->isStart = true;
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}


//void COpenGLDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
//{
//
//
//	if (nChar == VK_DOWN)
//		AfxMessageBox(_T("Down"));
//	if (nChar == VK_RIGHT)
//		AfxMessageBox(_T("Right"));
//	if (nChar == VK_LEFT)
//		AfxMessageBox(_T("LEft"));
//	if (nChar == VK_UP)
//		AfxMessageBox(_T("Up"));
//
//	// TODO: Add your message handler code here and/or call default
//	if (!ptrView->isFalling)
//	{
//		ptrView->setJump();
//
//	}
//	ptrView->isStart = true;
//
//	// else, DO call base class
//	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
//}



//BOOL COpenGLDlg::PreTranslateMessage(MSG* pMsg)
//{
//	// TODO: Add your specialized code here and/or call the base class
//	if (pMsg->message == WM_KEYDOWN)
//	{
//		if (pMsg->message == VK_DOWN)
//			AfxMessageBox(_T("Down"));
//		if (pMsg->message == VK_RIGHT)
//			AfxMessageBox(_T("Right"));
//		if (pMsg->message == VK_LEFT)
//			AfxMessageBox(_T("LEft"));
//		if (pMsg->message == VK_UP)
//			AfxMessageBox(_T("Up"));
//	}
//	return CDialogEx::PreTranslateMessage(pMsg);
//}


void COpenGLDlg::OnBnClickedButton5()
{
	ptrView->isProfile = !ptrView->isProfile;
	ptrView->vDrawGLScene();
	// TODO: Add your control notification handler code here
}
