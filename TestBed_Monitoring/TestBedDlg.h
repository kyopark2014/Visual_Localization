// TestBedDlg.h : header file
//

#if !defined(AFX_TESTBEDDLG_H__1679C954_7C7C_4661_A20F_968E8F166A6A__INCLUDED_)
#define AFX_TESTBEDDLG_H__1679C954_7C7C_4661_A20F_968E8F166A6A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTestBedDlg dialog
#include "ximage.h"
#include <afxinet.h>
#include <direct.h>

#define pi 3.14159265

struct param_camera {
	int x;
	int y;
	double theta_p;
	double type;
	double zoom_level;
	double length;
};

class CTestBedDlg : public CDialog
{
// Construction
public:
	void DrawCameraSetup(param_camera c);
	void ExecuteOrder(CString Order,CString strServerName,CString id,CString passwd);
	void UpdateImageFromCameras();
	void UpdateTestBed();
	void UpdateSetup();
	void LoadImageFromCameras(CString strServerName,CString strFile,CString id,CString passwd);
	void ShowCameraImages(CString ImageFile1,CString ImageFile2);

	CxImage *m_pImage;

	CTestBedDlg(CWnd* pParent = NULL);	// standard constructor
	int Width,Height,iWidth,iHeight,sWidth,sHeight;
	int px_c1,py_c1,px_c2,py_c2,px_s,py_s;
	int color_R,color_G,color_B;
	bool c1Save,c2Save;
	int cntc1,cntc2;
	unsigned int TimeDepth;

	// Show Images
	CDC dcMem1,dcMem2;
	CDC dcSetup;
	CDC dcBuffer;
	CPen *pOldPen;
	CBrush* pOldBrush;
	CBitmap *pOldBitmap,*pOldBitmap1,*pOldBitmap2;

	// Load Camera Images
	CInternetSession m_Session;
	CHttpConnection *m_pConnection;
	CHttpFile *m_pFile;
	CString strServerName1,strServerName2;
	CString ImageFile1,ImageFile2;
	CString id1,id2;
	CString passwd1,passwd2;
	param_camera c1,c2;

//	CBitmap m_bmpBack;

// Dialog Data
	//{{AFX_DATA(CTestBedDlg)
	enum { IDD = IDD_TESTBED_DIALOG };
	CComboBox m_ctrlPanSpeedC1;
	CComboBox m_ctrlTiltSpeedC1;
	CComboBox m_ctrlZoomSpeedC1;
	CComboBox m_ctrlFocusSpeedC1;
	CComboBox m_ctrlPanSpeedC2;
	CComboBox m_ctrlTiltSpeedC2;
	CComboBox m_ctrlZoomSpeedC2;
	CComboBox m_ctrlFocusSpeedC2;
	int m_PanSpeedC1;
	int m_TiltSpeedC1;
	int m_ZoomSpeedC1;
	int m_FocusSpeedC1;
	int m_PanSpeedC2;
	int m_TiltSpeedC2;
	int m_ZoomSpeedC2;
	int m_FocusSpeedC2;

	CComboBox m_ctrlSaveInterval;
	int m_SaveInterval;
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestBedDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTestBedDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnMoveupC1();
	afx_msg void OnMovedownC1();
	afx_msg void OnMoveleftC1();
	afx_msg void OnMoverightC1();
	afx_msg void OnMovehomeC1();
	
	afx_msg void OnMoveupC2();	
	afx_msg void OnMovedownC2();
	afx_msg void OnMoverightC2();
	afx_msg void OnMoveleftC2();
	afx_msg void OnMovehomeC2();

	afx_msg void OnTimer(UINT nIDEvent);

	afx_msg void OnZoomoutc1();
	afx_msg void OnZoominc1();
	afx_msg void OnZoomoutc2();
	afx_msg void OnZoominc2();

	afx_msg void OnFocusoutc1();
	afx_msg void OnFocusinc1();
	afx_msg void OnFocusautoc1();

	afx_msg void OnFocusoutc2();
	afx_msg void OnFocusinc2();
	afx_msg void OnFocusautoc2();

	afx_msg void OnIrisoutc1();
	afx_msg void OnIrisinc1();
	afx_msg void OnIrisautoc1();

	afx_msg void OnIrisoutc2();
	afx_msg void OnIrisinc2();
	afx_msg void OnIrisautoc2();

	afx_msg void OnSavec1();
	afx_msg void OnSavec2();
	afx_msg void OnSaveboth();
	afx_msg void OnSnapshot();

	afx_msg void OnPanspeedc1();
	afx_msg void OnTiltspeedc1();
	afx_msg void OnZoomspeedc1();
	afx_msg void OnFocusspeedc1();

	afx_msg void OnPanspeedc2();
	afx_msg void OnTiltspeedc2();
	afx_msg void OnZoomspeedc2();
	afx_msg void OnFocusspeedc2(); 

	afx_msg void OnSaveInterval(); 
	afx_msg void OnSaveStop();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTBEDDLG_H__1679C954_7C7C_4661_A20F_968E8F166A6A__INCLUDED_)
