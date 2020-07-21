// TestbedDlg.h : header file
//

#if !defined(AFX_TESTBEDDLG_H__C3937E4C_EE32_4219_8CD5_C6E68DF4E38A__INCLUDED_)
#define AFX_TESTBEDDLG_H__C3937E4C_EE32_4219_8CD5_C6E68DF4E38A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTestbedDlg dialog

#define pi 3.14159265

struct param_camera {
	int x;
	int y;
	double theta_p;
	double type;
	double zoom_level;
	double length;
};

class CTestbedDlg : public CDialog
{
// Construction
public:
	CTestbedDlg(CWnd* pParent = NULL);	// standard constructor

	// Image 
	CxImage *m_pImage;
	CDC dcMem1;
	CDC dcSetup;
	int iWidth,iHeight;
	int sWidth,sHeight;
	int Width,Height;
	CString strImageFileName1,_strImageFileName1;
	int xc1,yc1;  // Image Window Postion
	int xs,ys;  // Setup Window Position
	int px,py;  // coordinate of object
	double **gauss;
	int cntc1;
	int color_R,color_G,color_B;
	int m_bCalibration;

	param_camera c1,c2;

	void UpdateSetup();
	void DrawCameraSetup(param_camera c);
	void UpdateTestBed();

	// Camera Interface
	CInternetSession m_Session;
	CHttpConnection *m_pConnection;
	CHttpFile *m_pFile;

	void LoadImageFromCamera(CString strServerName,CString strFile,CString id,CString passwd);
	void UpdateImageFromCamera(CString strServerName,CString id,CString passwd);
	CString strServerName1,id1,passwd1;

	// Object Isolation
	void FindFace();
	void GaussDistribution();
	double GetCorrelation(int t[3],int r[3]);
	double CheckWeight(int px,int py,int **detect);
	void ShowBox();
	void DrawObject();

	// Camera Control
	int TimeDepth;
	void AdjustCamera(int px,int py,CString strServerName,CString id,CString passwd);
	void ExecuteOrder(CString Order,CString strServerName,CString id,CString passwd);


// Dialog Data
	//{{AFX_DATA(CTestbedDlg)
	enum { IDD = IDD_TESTBED_DIALOG };
	CComboBox	m_ctrlFocusSpeedC1;
	CComboBox	m_ctrlZoomSpeedC1;
	CComboBox	m_ctrlTiltSpeedC1;
	CComboBox	m_ctrlPanSpeedC1;
	CComboBox	m_ctrlSaveInterval;
	int		m_Savec1;
	int		m_nSaveInterval;
	int		m_nPanSpeedC1;
	int		m_nTiltSpeedC1;
	int		m_nZoomSpeedC1;
	int		m_nFocusSpeedC1;
	int		m_nIsolation;
	int		m_nTrace;
	int		m_nSelectC1;
	CString	m_strObjectCoordinate;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestbedDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTestbedDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSnapshot();
	afx_msg void OnMoveupc1();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnMovedownc1();
	afx_msg void OnMoveleftc1();
	afx_msg void OnMoverightc1();
	afx_msg void OnMovehomec1();
	afx_msg void OnZoominc1();
	afx_msg void OnZoomoutc1();
	afx_msg void OnFocusinc1();
	afx_msg void OnFocusoutc1();
	afx_msg void OnFocusautoc1();
	afx_msg void OnIrisinc1();
	afx_msg void OnIrisoutc1();
	afx_msg void OnIrisautoc1();
	afx_msg void OnSavec1stop();
	afx_msg void OnSavec2start();
	afx_msg void OnChangeSaveinterval();
	afx_msg void OnChangePanspeedc1();
	afx_msg void OnChangeTiltspeedc1();
	afx_msg void OnChangeZoomspeedc1();
	afx_msg void OnChangeFocusspeedc1();
	afx_msg void OnIsolationc1stop();
	afx_msg void OnIsolationc2start();
	afx_msg void OnTracec1stop();
	afx_msg void OnIsolationc1start();
	afx_msg void OnSelectcamera1();
	afx_msg void OnSelectcamera2();
	afx_msg void OnObjectCoordinate();
	afx_msg void OnCalibration();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTBEDDLG_H__C3937E4C_EE32_4219_8CD5_C6E68DF4E38A__INCLUDED_)
