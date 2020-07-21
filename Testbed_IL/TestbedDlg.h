// TestbedDlg.h : header file
//

#if !defined(AFX_TESTBEDDLG_H__2345B4A4_75EA_4633_9BC5_33E59667DE00__INCLUDED_)
#define AFX_TESTBEDDLG_H__2345B4A4_75EA_4633_9BC5_33E59667DE00__INCLUDED_

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

#define	pw 51
#define	ph 51

class CTestbedDlg : public CDialog
{
// Construction
public:
	CTestbedDlg(CWnd* pParent = NULL);	// standard constructor

	CxImage *m_pImage1,*m_pImage2,*m_pImage3;	
	int Width,Height;
	int iWidth,iHeight;
	int sWidth,sHeight;
	CDC dcMem1,dcMem2,dcSetup;
	int xc1,yc1,xc2,yc2;
	int xs,ys;
	int px1,py1,px2,py2;
	int m_nPanSpeedC1,m_nTiltSpeedC1,m_nZoomSpeedC1;
	int m_nPanSpeedC2,m_nTiltSpeedC2,m_nZoomSpeedC2;

	void UpdateTestBed();
	void UpdateSetup();
	void DrawCameraSetup(param_camera c);
	void ExecuteOrder(CString Order,CString strServerName,CString id,CString passwd);
	void UploadInstructionToCamera(CString Order,CString strServerName,CString id,CString passwd);
	void ExecuteInstruction(CString strServerName,CString id,CString passwd);
	void AdjustCamera1();
	void AdjustCamera2();
	void InitializeSetup();
	void DrawPoint(int x,int y,int type);

	// Camera Interface
	param_camera c1,c2;
	CInternetSession m_Session;
	CHttpConnection *m_pConnection;
	CHttpFile *m_pFile;
	CString strServerName1,id1,passwd1;
	CString strServerName2,id2,passwd2;

	CString strImageFileName1,_strImageFileName1;
	CString strImageFileName2,_strImageFileName2;

	int	TimeDepth,cnt;

	void LoadImageFromCamera(CString strServerName,CString strFile,CString id,CString passwd);
	void UpdateImageFromCamera1();
	void UpdateImageFromCamera2();

	// Object Isolation
	void FindFace1();
	void FindFace2();
	void GaussDistribution();
	double GetCorrelation(int t[3],int r[3]);
	double CheckWeight(int px,int py,int **detect);
	void DrawObject1();
	void DrawObject2();
	void ShowBox1();
	void ShowBox2();

	RGBQUAD hat1,hat2;
	double **gauss;

	// Localization
	double GetDeltau(double d);
	int FindNearD(double d);
	void DoLocalization(double xe,double ye,double upp1,double upp2,double theta_c1,double theta_c2);
	double GetNewZoomFactor(double dp);

// Dialog Data
	//{{AFX_DATA(CTestbedDlg)
	enum { IDD = IDD_TESTBED_DIALOG };
	CComboBox	m_ctrlSaveInterval;
	CString	m_strObjectCoordinateC1;
	CString	m_strObjectCoordinateC2;
	int		m_bSave;
	int		m_bIsolation;
	int		m_bTrace;
	int		m_nSaveInterval;
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
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnMoveupc1();
	afx_msg void OnMovedownc1();
	afx_msg void OnMoveleftc1();
	afx_msg void OnMoverightc1();
	afx_msg void OnMovehomec1();
	afx_msg void OnZoominc1();
	afx_msg void OnZoomoutc1();
	afx_msg void OnCoordinatec1();
	afx_msg void OnMoveupc2();
	afx_msg void OnMovedownc2();
	afx_msg void OnMoveleftc2();
	afx_msg void OnMoverightc2();
	afx_msg void OnMovehomec2();
	afx_msg void OnZoominc2();
	afx_msg void OnZoomoutc2();
	afx_msg void OnCoordinatec2();
	afx_msg void OnSnapshot();
	afx_msg void OnSavestop();
	afx_msg void OnSavestart();
	afx_msg void OnIsolationstop();
	afx_msg void OnIsolationstart();
	afx_msg void OnTracestop();
	afx_msg void OnTracestart();
	afx_msg void OnChangeSaveinterval();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTBEDDLG_H__2345B4A4_75EA_4633_9BC5_33E59667DE00__INCLUDED_)
