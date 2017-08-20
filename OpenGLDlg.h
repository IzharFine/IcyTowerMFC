
// OpenGLDlg.h : header file
//

#pragma once

#include "GlView.h"
#include "afxwin.h"


// COpenGLDlg dialog
class COpenGLDlg : public CDialogEx
{
// Construction
public:
	COpenGLDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OPENGL_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	CGlView* ptrView;
	bool flag = false;
public:
	afx_msg void OnDeltaposMoveX(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposMoveY(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpin2(NMHDR *pNMHDR, LRESULT *pResult);//יד ימין
	afx_msg void OnDeltaposSpin3(NMHDR *pNMHDR, LRESULT *pResult);//יד שמאל
	afx_msg void OnDeltaposSpin4(NMHDR *pNMHDR, LRESULT *pResult);//רגל ימין
	afx_msg void OnDeltaposSpin5(NMHDR *pNMHDR, LRESULT *pResult);//רגל שמאל
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedLoad();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnDeltaposMoveX2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpin6(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpin7(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpin8(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpin9(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposMoveX3(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpin10(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
//	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnBnClickedButton4();
	bool isOver;
	void EndGame();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
//	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
//	virtual BOOL PreTranslateMessage(MSG* pMsg);
	bool isPause;
	afx_msg void OnBnClickedButton5();
	CButton pauseBTN;
};
