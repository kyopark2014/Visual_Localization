// TestbedDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Testbed.h"
#include "TestbedDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestbedDlg dialog
static CString TimeRange[] = {"0.1", "0.2", "0.5", "1", "2", "5", "10", "60"};

/*static double angle_z1to3_c1[] = {0.32, 0.65, 1.29, 3.88, 7.75, 11.63, 15.50, 19.38, 23,26, 25.84, 28.42};
static double angle_z4to7_c1[] = {0.32, 0.32, 0.65, 1.94, 3.88,  5.81,  7.75,  9.69, 11.63, 12.92, 14.21};
static double angle_z8to10_c1[]= {0.32, 0.32, 0.32, 0.97, 1.94,  2.91,  3.88,  4.85,  5.81,  6.46,  7.11};

static double angle_z1to3_c2[] = {0.32, 0.65, 1.29, 3.88, 7.75, 11.63, 15.50, 19.38, 23,26, 25.84, 28.42};
static double angle_z4to7_c2[] = {0.32, 0.32, 0.65, 1.94, 3.88,  5.81,  7.75,  9.69, 11.63, 12.92, 14.21};
static double angle_z8to10_c2[]= {0.32, 0.32, 0.32, 0.97, 1.94,  2.91,  3.88,  4.85,  5.81,  6.46,  7.11}; */
static double c1_angle_z[]= {2.9, 5.5, 7.9, 10.7, 12.9, 15.8, 18.2};
static double c2_angle_z[]= {3.1, 5.3, 9.5, 10.8, 13.4, 16, 18.3};

CTestbedDlg::CTestbedDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestbedDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestbedDlg)
	m_strObjectCoordinateC1 = _T("");
	m_strObjectCoordinateC2 = _T("");
	m_bSave = 0;
	m_bIsolation = 1;
	m_bTrace = 1;
	m_nSaveInterval = -1;
	m_strAngles = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_pImage1 = NULL;
	m_pImage2 = NULL;
	m_pImage3 = NULL;
	cnt = 0;
	px1=0, py1=0, px2=0, py2=0;

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestbedDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestbedDlg)
	DDX_Control(pDX, IDC_SAVEINTERVAL, m_ctrlSaveInterval);
	DDX_Text(pDX, IDC_COORDINATEC1, m_strObjectCoordinateC1);
	DDX_Text(pDX, IDC_COORDINATEC2, m_strObjectCoordinateC2);
	DDX_Radio(pDX, IDC_SAVESTOP, m_bSave);
	DDX_Radio(pDX, IDC_ISOLATIONSTOP, m_bIsolation);
	DDX_Radio(pDX, IDC_TRACESTOP, m_bTrace);
	DDX_CBIndex(pDX, IDC_SAVEINTERVAL, m_nSaveInterval);
	DDX_Text(pDX, IDC_ANGLES, m_strAngles);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTestbedDlg, CDialog)
	//{{AFX_MSG_MAP(CTestbedDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_MOVEUPC1, OnMoveupc1)
	ON_BN_CLICKED(IDC_MOVEDOWNC1, OnMovedownc1)
	ON_BN_CLICKED(IDC_MOVELEFTC1, OnMoveleftc1)
	ON_BN_CLICKED(IDC_MOVERIGHTC1, OnMoverightc1)
	ON_BN_CLICKED(IDC_MOVEHOMEC1, OnMovehomec1)
	ON_BN_CLICKED(IDC_ZOOMINC1, OnZoominc1)
	ON_BN_CLICKED(IDC_ZOOMOUTC1, OnZoomoutc1)
	ON_BN_CLICKED(IDC_COORDINATEC1, OnCoordinatec1)
	ON_BN_CLICKED(IDC_MOVEUPC2, OnMoveupc2)
	ON_BN_CLICKED(IDC_MOVEDOWNC2, OnMovedownc2)
	ON_BN_CLICKED(IDC_MOVELEFTC2, OnMoveleftc2)
	ON_BN_CLICKED(IDC_MOVERIGHTC2, OnMoverightc2)
	ON_BN_CLICKED(IDC_MOVEHOMEC2, OnMovehomec2)
	ON_BN_CLICKED(IDC_ZOOMINC2, OnZoominc2)
	ON_BN_CLICKED(IDC_ZOOMOUTC2, OnZoomoutc2)
	ON_BN_CLICKED(IDC_COORDINATEC2, OnCoordinatec2)
	ON_BN_CLICKED(IDC_SNAPSHOT, OnSnapshot)
	ON_BN_CLICKED(IDC_SAVESTOP, OnSavestop)
	ON_BN_CLICKED(IDC_SAVESTART, OnSavestart)
	ON_BN_CLICKED(IDC_ISOLATIONSTOP, OnIsolationstop)
	ON_BN_CLICKED(IDC_ISOLATIONSTART, OnIsolationstart)
	ON_BN_CLICKED(IDC_TRACESTOP, OnTracestop)
	ON_BN_CLICKED(IDC_TRACESTART, OnTracestart)
	ON_CBN_SELCHANGE(IDC_SAVEINTERVAL, OnChangeSaveinterval)
	ON_BN_CLICKED(IDC_ANGLES, OnAngles)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestbedDlg message handlers

BOOL CTestbedDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	TimeDepth = 100;  // 0.1s
	SetTimer(0,TimeDepth,NULL);  

	Width = 1024, Height = 768;
	iWidth = 704; iHeight = 480;
	sWidth = (int)(1196*0.595); sHeight = (int)(730*0.595);
	SetWindowPos(NULL,0,0,Width,Height+30,SWP_NOMOVE|SWP_SHOWWINDOW); // Adjust testbed size

	m_pImage1 = new CxImage;
	m_pImage2 = new CxImage;
	m_pImage3 = new CxImage;

	// Camera Setup
	strServerName1 = "129.49.69.81";  // Camera 1
	id1 = "root";
	passwd1 = "msdl007";	
	strImageFileName1 = "video1.jpg";

	strServerName2 = "129.49.69.89";  // Camera 2	
	id2 = "root";
	passwd2 = "msdl007";	
	strImageFileName2 = "video2.jpg";

	xc1 = 156;
	yc1 = 20;

	xc2 = xc1+iWidth/2+6;
	yc2 = yc1;

	xs = xc1;
	ys = iHeight/2 + yc1*2;

	// Camera Parameters
	c1.x = 136;
	c1.y = 170-18;
	c1.type = 3;
	c1.theta_p = 0;
	c1.zoom_level = 1;
	c1.length = 20;

	c2.x = 205+1;
	c2.y = 170-18;
	c2.type = 3;
	c2.theta_p = 0;
	c2.zoom_level = 1;
	c2.length = 20;

	m_nPanSpeedC1=-1, m_nTiltSpeedC1=5, m_nZoomSpeedC1=1;
	m_nPanSpeedC2=-1, m_nTiltSpeedC2=5, m_nZoomSpeedC2=1;

	for(int i=0;i<8;i++) 
		m_ctrlSaveInterval.AddString(TimeRange[i]);

	// Initialize for object isolation;
	GaussDistribution();
	hat1.rgbRed = 222, hat1.rgbGreen=33, hat1.rgbBlue=101;
	hat2.rgbRed = 144, hat2.rgbGreen=17, hat2.rgbBlue=60;

	// Initialize dcMem
	CClientDC dc(this);	
	dcMem1.CreateCompatibleDC(&dc);
	CBitmap bitmap1;
	bitmap1.CreateCompatibleBitmap(&dc,iWidth/2,iHeight/2);
	CBitmap *pOldBitmap1 = dcMem1.SelectObject(&bitmap1);

	dcMem2.CreateCompatibleDC(&dc);
	CBitmap bitmap2;
	bitmap2.CreateCompatibleBitmap(&dc,iWidth/2,iHeight/2);
	CBitmap *pOldBitmap2 = dcMem2.SelectObject(&bitmap2);

	// Setup
	dcSetup.CreateCompatibleDC(&dc);	
	CBitmap bitmap_setup;
	bitmap_setup.CreateCompatibleBitmap(&dc,sWidth,sHeight);
	CBitmap *pOldBitmap3 = dcSetup.SelectObject(&bitmap_setup);

	// Initializa Camera Postion
	CString Order;	

	Order = "/cgi-bin/camctrl.cgi?move=home";
	ExecuteOrder(Order,strServerName1,id1,passwd1);
	ExecuteOrder(Order,strServerName2,id2,passwd2);
	
	Order.Format("/cgi-bin/camctrl.cgi?speedpan=%d",m_nPanSpeedC1);
	ExecuteOrder(Order,strServerName1,id1,passwd1);
	Order.Format("/cgi-bin/camctrl.cgi?speedtilt=%d",m_nTiltSpeedC1);
	ExecuteOrder(Order,strServerName1,id1,passwd1);
	Order.Format("/cgi-bin/camctrl.cgi?speedzoom=%d",m_nZoomSpeedC1);
	ExecuteOrder(Order,strServerName1,id1,passwd1);

	Order.Format("/cgi-bin/camctrl.cgi?speedpan=%d",m_nPanSpeedC2);
	ExecuteOrder(Order,strServerName2,id2,passwd2);
	Order.Format("/cgi-bin/camctrl.cgi?speedtilt=%d",m_nTiltSpeedC2);
	ExecuteOrder(Order,strServerName2,id2,passwd2);
	Order.Format("/cgi-bin/camctrl.cgi?speedzoom=%d",m_nZoomSpeedC2);
	ExecuteOrder(Order,strServerName2,id2,passwd2);

	// For User Interface
	InitializeSetup();

	// Load Image Data from camera;
	UpdateImageFromCamera1();
	UpdateImageFromCamera2();
	UpdateSetup();
	UpdateTestBed();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTestbedDlg::InitializeSetup()
{
	CString Order;	
	double dep=0;

	// Camera 1
/*	if(c1.zoom_level<=3) dep = angle_z1to3_c1[m_nPanSpeedC1+5];
	else if(c1.zoom_level>3 && c1.zoom_level<=7) dep = angle_z4to7_c1[m_nPanSpeedC1+5];
	else if(c1.zoom_level>7) dep = angle_z8to10_c1[m_nPanSpeedC1+5];	*/
	dep = c1_angle_z[m_nPanSpeedC1+5];

	Order = "/cgi-bin/camctrl.cgi?move=left";
	ExecuteOrder(Order,strServerName1,id1,passwd1);		
	c1.theta_p += dep*pi/180.;
	ExecuteOrder(Order,strServerName1,id1,passwd1);		
	c1.theta_p += dep*pi/180.;
	ExecuteOrder(Order,strServerName1,id1,passwd1);		
	c1.theta_p += dep*pi/180.;
	ExecuteOrder(Order,strServerName1,id1,passwd1);		
	c1.theta_p += dep*pi/180.;
	Order = "/cgi-bin/camctrl.cgi?move=down";
	ExecuteOrder(Order,strServerName1,id1,passwd1);		
	ExecuteOrder(Order,strServerName1,id1,passwd1);		
	ExecuteOrder(Order,strServerName1,id1,passwd1);		
	ExecuteOrder(Order,strServerName1,id1,passwd1);		
	ExecuteOrder(Order,strServerName1,id1,passwd1);		

	// Camera 2
/*	if(c2.zoom_level<=3) dep = angle_z1to3_c2[m_nPanSpeedC2+5];
	else if(c2.zoom_level>3 && c2.zoom_level<=7) dep = angle_z4to7_c2[m_nPanSpeedC2+5];
	else if(c2.zoom_level>7) dep = angle_z8to10_c2[m_nPanSpeedC2+5];	 */
	dep = c2_angle_z[m_nPanSpeedC2+5];

	Order = "/cgi-bin/camctrl.cgi?move=right";
	ExecuteOrder(Order,strServerName2,id2,passwd2);		
	c2.theta_p -= dep*pi/180.;
	ExecuteOrder(Order,strServerName2,id2,passwd2);		
	c2.theta_p -= dep*pi/180.;
	ExecuteOrder(Order,strServerName2,id2,passwd2);		
	c2.theta_p -= dep*pi/180.;
	ExecuteOrder(Order,strServerName2,id2,passwd2);		
	c2.theta_p -= dep*pi/180.;
	Order = "/cgi-bin/camctrl.cgi?move=down";
	ExecuteOrder(Order,strServerName2,id2,passwd2);		
	ExecuteOrder(Order,strServerName2,id2,passwd2);		
	ExecuteOrder(Order,strServerName2,id2,passwd2);		
	ExecuteOrder(Order,strServerName2,id2,passwd2);		
	ExecuteOrder(Order,strServerName2,id2,passwd2);		
}

void CTestbedDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

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
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTestbedDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BOOL CTestbedDlg::DestroyWindow() 
{
	KillTimer(0);	
	ReleaseDC(&dcMem1);
	ReleaseDC(&dcMem2);
	delete m_pImage1;
	delete m_pImage2;
	delete m_pImage3;
	
	return CDialog::DestroyWindow();
}

void CTestbedDlg::UpdateTestBed()
{
	CClientDC dc(this);	

	// Show Camera Images
	dc.BitBlt(xc1,yc1,iWidth/2,iHeight/2,&dcMem1,0,0,SRCCOPY); // camera 1
	dc.BitBlt(xc2,yc2,iWidth/2,iHeight/2,&dcMem2,0,0,SRCCOPY); // camera 1
	dc.BitBlt(xs,ys,sWidth,sHeight,&dcSetup,0,0,SRCCOPY); // setup

	OnCoordinatec1(); // Show coordinate in Camera1
	OnCoordinatec2(); // Show coordinate in Camera2
}

void CTestbedDlg::UpdateSetup()
{
	// Load image from memory
	m_pImage3->Load("setup.jpg",CxImage::FindType("setup.jpg"));

	// Copy Detection result
	m_pImage3->Draw(dcSetup,CRect(0,0,sWidth,sHeight));
	
	// Update Camera 
	DrawCameraSetup(c1);
	DrawCameraSetup(c2);

	// Show Setup
//	CClientDC dc(this);	
//	dc.BitBlt(xs,ys,sWidth,sHeight,&dcSetup,0,0,SRCCOPY); // setup
}

void CTestbedDlg::DrawCameraSetup(param_camera c)
{
	int xp1,yp1,xp2,yp2;
	double theta_c;

	int xc,yc;
	xc = (int)(sWidth/280.*c.x);
	yc = (int)(sHeight/170.*c.y);

	if(c.type==1) theta_c = c.theta_p;
	else if(c.type==2) theta_c = c.theta_p + pi/2.;
	else if(c.type==3) theta_c = c.theta_p + pi;
	else if(c.type==4) theta_c = c.theta_p + 3.*pi/2.;

	CPen pen1;
	pen1.CreatePen(PS_SOLID,4,RGB(0,0,0));
	dcSetup.SelectObject(&pen1);

	xp1 = xc-(int)(c.length/2.*cos(theta_c));
	yp1 = yc-(int)(c.length/2.*sin(theta_c));
	xp2 = xc+(int)(c.length/2.*cos(theta_c));
	yp2 = yc+(int)(c.length/2.*sin(theta_c));

	int xr1,yr1,xr2,yr2;

	xr1 = xp1;
	yr1 = sHeight-1-yp1;
	xr2 = xp2;
	yr2 = sHeight-1-yp2;

	dcSetup.SelectStockObject(BLACK_PEN);
	dcSetup.MoveTo(xr1,yr1);
	dcSetup.LineTo(xr2,yr2); 
	CPen pen2;
	pen2.CreatePen(PS_DOT,1,RGB(50,130,148));
	dcSetup.SelectObject(&pen2);

	int xn,yn,ln=sWidth/5;
	xn = (int)(xc-ln*sin(theta_c));
	if(xn<0) xn=0;
	yn = (int)(yc+ln*cos(theta_c));
	if(yn<0) yn=0;

	xr1 = xc;
	yr1 = sHeight-yc;
	xr2 = xn;
	yr2 = sHeight-1-yn;

	dcSetup.MoveTo(xr1,yr1);
	dcSetup.LineTo(xr2,yr2); 

	CPen pen3;
	pen3.CreatePen(PS_SOLID,2,RGB(50,130,148));
	dcSetup.SelectObject(&pen3);
	// Range
	xn = (int)(xc-ln*sin(theta_c+150));
	if(xn<0) xn=0;
	yn = (int)(yc+ln*cos(theta_c+150));
	if(yn<0) yn=0;

	xr1 = xc;
	yr1 = sHeight-yc;
	xr2 = xn;
	yr2 = sHeight-1-yn;

	dcSetup.MoveTo(xr1,yr1);
	dcSetup.LineTo(xr2,yr2); 

	xn = (int)(xc-ln*sin(theta_c-150));
	if(xn<0) xn=0;
	yn = (int)(yc+ln*cos(theta_c-150));
	if(yn<0) yn=0;

	xr1 = xc;
	yr1 = sHeight-yc;
	xr2 = xn;
	yr2 = sHeight-1-yn;

	dcSetup.MoveTo(xr1,yr1);
	dcSetup.LineTo(xr2,yr2); 
}

//****************************************************************************************************
void CTestbedDlg::FindFace1()
{
	int m,n;

	int t[3]={0,};
	int r[3]={222,33,101};  // my hat	
	
	int dip=50;
	double A;
	int i,j;

	int **detect;
	double **weight;

	detect = (int **)malloc(sizeof(int)*iWidth);
	if(detect==NULL) exit(-1);
	for(i=0;i<iWidth;i++) {
		detect[i] = (int *)malloc(sizeof(int)*iHeight);
		if(detect[i]==NULL) exit(-1);
	}
	for(i=0;i<iWidth;i++)
		for(j=0;j<iHeight;j++) detect[i][j] = 0;

	weight = (double **)malloc(sizeof(double)*iWidth);
	if(weight==NULL) exit(-1);
	for(i=0;i<iWidth;i++) {
		weight[i] = (double *)malloc(sizeof(double)*iHeight);
		if(weight[i]==NULL) exit(-1);
	}
	for(i=0;i<iWidth;i++)
		for(j=0;j<iHeight;j++) weight[i][j] = 0; 

	// detection based on hyperspectral algorithm
	RGBQUAD color;
	
	for(m=0;m<iWidth;m++) {
		for(n=0;n<iHeight;n++) {
			color = m_pImage1->GetPixelColor(m,n);

			t[0] = color.rgbRed;
			t[1] = color.rgbGreen;
			t[2] = color.rgbBlue;

			dip = 50;

			r[0]=hat1.rgbRed;
			r[1]=hat1.rgbGreen;
			r[2]=hat1.rgbBlue;  // my hat1

			A = GetCorrelation(t,r);

			if(A>0.90) {
				if(color.rgbRed>r[0]-dip && color.rgbRed<r[0]+dip) {
					if(color.rgbGreen>r[1]-dip && color.rgbGreen<r[1]+dip) {
						if(color.rgbBlue>r[2]-dip && color.rgbBlue<r[2]+dip) {
							detect[m][n] = 1;
						}
					}
				}
			}

			dip = 20;

			r[0]=hat2.rgbRed;
			r[1]=hat2.rgbGreen;
			r[2]=hat2.rgbBlue;  // my hat1
			
			A = GetCorrelation(t,r);

			if(A>0.80) {
				if(color.rgbRed>r[0]-dip && color.rgbRed<r[0]+dip) {
					if(color.rgbGreen>r[1]-dip && color.rgbGreen<r[1]+dip) {
						if(color.rgbBlue>r[2]-dip && color.rgbBlue<r[2]+dip) {
							detect[m][n] = 1;
						}
					}
				}
			} 
		}
	}

	// find maximum detected area
	double max = 0;
	for(m=0;m<iWidth;m+=5) {
		for(n=0;n<iHeight;n+=5) {
			weight[m][n] = CheckWeight(m,n,detect);
			if(weight[m][n]>max) {
				max = weight[m][n];
				px1 = m;
				py1 = (iHeight-1)-n;
			}
		}
	} 

	if(max<1) {
		px1 = 0;
		py1 = 0;
	}

	for(i=0;i<iWidth;i++) free(detect[i]),free(weight[i]);
	free(detect),free(weight); 
}

void CTestbedDlg::FindFace2()
{
	int m,n;

	int t[3]={0,};
	int r[3]={222,33,101};  // my hat	
	
	int dip=50;
	double A;
	int i,j;

	int **detect;
	double **weight;

	detect = (int **)malloc(sizeof(int)*iWidth);
	if(detect==NULL) exit(-1);
	for(i=0;i<iWidth;i++) {
		detect[i] = (int *)malloc(sizeof(int)*iHeight);
		if(detect[i]==NULL) exit(-1);
	}
	for(i=0;i<iWidth;i++)
		for(j=0;j<iHeight;j++) detect[i][j] = 0;

	weight = (double **)malloc(sizeof(double)*iWidth);
	if(weight==NULL) exit(-1);
	for(i=0;i<iWidth;i++) {
		weight[i] = (double *)malloc(sizeof(double)*iHeight);
		if(weight[i]==NULL) exit(-1);
	}
	for(i=0;i<iWidth;i++)
		for(j=0;j<iHeight;j++) weight[i][j] = 0; 

	// detection based on hyperspectral algorithm
	RGBQUAD color;
	
	for(m=0;m<iWidth;m++) {
		for(n=0;n<iHeight;n++) {
			color = m_pImage2->GetPixelColor(m,n);

			t[0] = color.rgbRed;
			t[1] = color.rgbGreen;
			t[2] = color.rgbBlue;

			dip = 50;

			r[0]=hat1.rgbRed;
			r[1]=hat1.rgbGreen;
			r[2]=hat1.rgbBlue;  // my hat1

			A = GetCorrelation(t,r);

			if(A>0.90) {
				if(color.rgbRed>r[0]-dip && color.rgbRed<r[0]+dip) {
					if(color.rgbGreen>r[1]-dip && color.rgbGreen<r[1]+dip) {
						if(color.rgbBlue>r[2]-dip && color.rgbBlue<r[2]+dip) {
							detect[m][n] = 1;
						}
					}
				}
			}

			dip = 20;

			r[0]=hat2.rgbRed;
			r[1]=hat2.rgbGreen;
			r[2]=hat2.rgbBlue;  // my hat1
			
			A = GetCorrelation(t,r);

			if(A>0.80) {
				if(color.rgbRed>r[0]-dip && color.rgbRed<r[0]+dip) {
					if(color.rgbGreen>r[1]-dip && color.rgbGreen<r[1]+dip) {
						if(color.rgbBlue>r[2]-dip && color.rgbBlue<r[2]+dip) {
							detect[m][n] = 1;
						}
					}
				}
			} 
		}
	}

	// find maximum detected area
	double max = 0;
	for(m=0;m<iWidth;m+=5) {
		for(n=0;n<iHeight;n+=5) {
			weight[m][n] = CheckWeight(m,n,detect);
			if(weight[m][n]>max) {
				max = weight[m][n];
				px2 = m;
				py2 = (iHeight-1)-n;
			}
		}
	} 

	if(max<1) {
		px2 = 0;
		py2 = 0;
	}

	for(i=0;i<iWidth;i++) free(detect[i]),free(weight[i]);
	free(detect),free(weight); 
}

void CTestbedDlg::GaussDistribution()
{
	int Nx,Ny,i,j;
	double sigma=8;
	double dep=0.5;
	double x,y;

	Nx = pw;
	Ny = ph;

	gauss = (double **)malloc(sizeof(double)*Ny);
	if(gauss==NULL) exit(-1);
	for(j=0;j<Ny;j++) {
		gauss[j] = (double *)malloc(sizeof(double)*Nx);
		if(gauss[j]==NULL) exit(-1);
	}
	for(i=0;i<Ny;i++)
		for(j=0;j<Nx;j++)	gauss[i][j] = 0; 

	for(i=0;i<Ny;i++) {
		for(j=0;j<Nx;j++) {	
			x = -(Nx*dep)/2.+i*dep;
			y = -(Ny*dep)/2.+j*dep;
			gauss[i][j] = exp(-(pow((x/sigma),2)+pow((y/sigma),2)));
		}
	}
}

double CTestbedDlg::GetCorrelation(int t[3],int r[3])
{
	double u=0,d1=0,d2=0;
	double A=0,d=0;
	int k;

	for(k=0;k<3;k++) {
		u = u+t[k]*r[k];
		d1 = d1+t[k]*t[k];
		d2 = d2+r[k]*r[k];
	}

	d = sqrt(d1)*sqrt(d2); 
         
	if(d==0) A = 1;
	else A = 1.0-acos(u/d);

	return A;
}

double CTestbedDlg::CheckWeight(int px,int py,int **detect)
{
	int x0=0,y0=0,x1=0,y1=0;
	double weight=0;
	int i,j,m,n;

	for(i=0;i<pw;i++) {
		for(j=0;j<ph;j++) {
			m = px+i-pw/2;
			n = py+j-ph/2;
			if((m>=0 && m<iWidth) && (n>=0 && n<iHeight)) {
				if(detect[m][n]==1 || detect[m][n]==2) weight += gauss[i][j];
			}
		}
	}
	return weight; 
}

void CTestbedDlg::DrawObject1()
{
	int rx1,ry1,rx2,ry2;

	if(!(px1==0 && py1==0)) {
		rx1 = px1-pw/2;
		if(rx1<0) rx1=0;
		ry1 = py1-ph/2;
		if(ry1<0) ry1=0;
		rx2 = px1+pw/2;
		if(rx2>iWidth) rx2=iWidth;
		ry2 = py1+ph/2;
		if(ry2>iHeight) ry2=iHeight;

		// Make box in image
		m_pImage1->DrawLine(rx1,rx2,iHeight-1-ry1,iHeight-1-ry1,RGB(0,0,255));
		m_pImage1->DrawLine(rx2,rx2,iHeight-1-ry1,iHeight-1-ry2,RGB(0,0,255));
		m_pImage1->DrawLine(rx2,rx1,iHeight-1-ry2,iHeight-1-ry2,RGB(0,0,255));
		m_pImage1->DrawLine(rx1,rx1,iHeight-1-ry2,iHeight-1-ry1,RGB(0,0,255));
	}
}

void CTestbedDlg::DrawObject2()
{
	int rx1,ry1,rx2,ry2;

	if(!(px2==0 && py2==0)) {
		rx1 = px2-pw/2;
		if(rx1<0) rx1=0;
		ry1 = py2-ph/2;
		if(ry1<0) ry1=0;
		rx2 = px2+pw/2;
		if(rx2>iWidth) rx2=iWidth;
		ry2 = py2+ph/2;
		if(ry2>iHeight) ry2=iHeight;

		// Make box in image
		m_pImage2->DrawLine(rx1,rx2,iHeight-1-ry1,iHeight-1-ry1,RGB(0,0,255));
		m_pImage2->DrawLine(rx2,rx2,iHeight-1-ry1,iHeight-1-ry2,RGB(0,0,255));
		m_pImage2->DrawLine(rx2,rx1,iHeight-1-ry2,iHeight-1-ry2,RGB(0,0,255));
		m_pImage2->DrawLine(rx1,rx1,iHeight-1-ry2,iHeight-1-ry1,RGB(0,0,255));
	}
}


void CTestbedDlg::ShowBox1()
{
	CClientDC dc(this);	
	int rx1,ry1,rx2,ry2;

	if(!(px1==0 && py1==0)) {
		CRect rect;
		GetWindowRect(&rect);
	
		CBrush brush(RGB(0,0,255));
		CBrush* pOldBrush = dcMem1.SelectObject(&brush);

		CPen pen;
		pen.CreatePen(PS_SOLID,5,RGB(0,0,255));
		CPen* pOldPen = dcMem1.SelectObject(&pen);

		rx1 = (px1-pw/2)/2;
		if(rx1<0) rx1=0;
		ry1 = (py1-ph/2)/2;
		if(ry1<0) ry1=0;
		rx2 = (px1+pw/2)/2;
		if(rx2>iWidth/2) rx2=iWidth/2;
		ry2 = (py1+ph/2)/2;
		if(ry2>iHeight/2) ry2=iHeight/2;

		dcMem1.MoveTo(rx1,ry1);
		dcMem1.LineTo(rx2,ry1);
		dcMem1.LineTo(rx2,ry2);
		dcMem1.LineTo(rx1,ry2);
		dcMem1.LineTo(rx1,ry1);
	}
}

void CTestbedDlg::ShowBox2()
{
	CClientDC dc(this);	
	int rx1,ry1,rx2,ry2;

	if(!(px2==0 && py2==0)) {
		CRect rect;
		GetWindowRect(&rect);
	
		CBrush brush(RGB(0,0,255));
		CBrush* pOldBrush = dcMem2.SelectObject(&brush);

		CPen pen;
		pen.CreatePen(PS_SOLID,5,RGB(0,0,255));
		CPen* pOldPen = dcMem2.SelectObject(&pen);

		rx1 = (px2-pw/2)/2;
		if(rx1<0) rx1=0;
		ry1 = (py2-ph/2)/2;
		if(ry1<0) ry1=0;
		rx2 = (px2+pw/2)/2;
		if(rx2>iWidth/2) rx2=iWidth/2;
		ry2 = (py2+ph/2)/2;
		if(ry2>iHeight/2) ry2=iHeight/2;

		dcMem2.MoveTo(rx1,ry1);
		dcMem2.LineTo(rx2,ry1);
		dcMem2.LineTo(rx2,ry2);
		dcMem2.LineTo(rx1,ry2);
		dcMem2.LineTo(rx1,ry1);
	}
}

//****************************************************************************************************
void CTestbedDlg::LoadImageFromCamera(CString strServerName,CString strFile,CString id,CString passwd)
{
	INTERNET_PORT nPort = 80;
	
	m_pConnection = m_Session.GetHttpConnection(strServerName,nPort,id,passwd);
	if (!m_pConnection)
	{
		AfxMessageBox("Fail to connect", MB_OK);
		m_pConnection = NULL;
		return;
	}

    if (m_pConnection != NULL)
    {
        m_pFile = m_pConnection->OpenRequest(CHttpConnection::HTTP_VERB_GET,
			"/cgi-bin/video.jpg",NULL,1,NULL,NULL,INTERNET_FLAG_RELOAD); 
		
        if (m_pFile != NULL)
        {
            DWORD dwStatus;

			m_pFile->AddRequestHeaders("User-Agent: GetWebFile/1.0\r\n",
				HTTP_ADDREQ_FLAG_ADD_IF_NEW);

            m_pFile->SendRequest();
            m_pFile->QueryInfoStatusCode(dwStatus);

			if (dwStatus == HTTP_STATUS_OK)
			{
				char buf[2000];
				int numread;
				CString filepath;
				filepath.Format("%s", strFile);
				CFile myfile(filepath,CFile::modeCreate|CFile::modeWrite|CFile::typeBinary);
				while ((numread = m_pFile->Read(buf,sizeof(buf)-1)) > 0)
				{
					buf[numread] = '\0';
					strFile += buf;
					myfile.Write(buf, numread);
				}
				myfile.Close();
			}
        }
    }
	delete m_pFile;
	delete m_pConnection;
}

void CTestbedDlg::UpdateImageFromCamera1()
{	
	// Load image from camera
	LoadImageFromCamera(strServerName1,strImageFileName1,id1,passwd1);
	
	// Load image from memory
	m_pImage1->Load(strImageFileName1,CxImage::FindType(strImageFileName1));
	
	// Object isolation
	if(m_bIsolation) {
		FindFace1();
		DrawObject1();  // DrawBox in image file
	}

	// Copy Detection result
	m_pImage1->Draw(dcMem1,CRect(0,0,iWidth/2,iHeight/2));
	// Draw Box in screen
	if(m_bIsolation) {
		ShowBox1(); // DrawBox in screen
	}

	// Adjust Camera
	if(m_bTrace) {
		AdjustCamera1();
	}	

	OnAngles();
}

void CTestbedDlg::UpdateImageFromCamera2()
{	
	// Load image from camera
	LoadImageFromCamera(strServerName2,strImageFileName2,id2,passwd2);
	// Load image from memory
	m_pImage2->Load(strImageFileName2,CxImage::FindType(strImageFileName2));
	// Object isolation
	if(m_bIsolation) {
		FindFace2();
		DrawObject2();  // DrawBox in image file
	}
	// Copy Detection result
	m_pImage2->Draw(dcMem2,CRect(0,0,iWidth/2,iHeight/2));
	// Draw Box in screen
	if(m_bIsolation) {
		ShowBox2(); // DrawBox in screen
	}

	// Adjust Camera
	if(m_bTrace) {
		AdjustCamera2();
	}

	OnAngles();
}

void CTestbedDlg::AdjustCamera1()
{
	CString Order;

	int delta_w,delta_h;
	double dep=0;

/*	if(c1.zoom_level<=3) dep = angle_z1to3_c1[m_nPanSpeedC1+5];
	else if(c1.zoom_level>3 && c1.zoom_level<=7) dep = angle_z4to7_c1[m_nPanSpeedC1+5];
	else if(c1.zoom_level>7) dep = angle_z8to10_c1[m_nPanSpeedC1+5];	*/
	dep = c1_angle_z[m_nPanSpeedC1+5];

	if(!(px1==0 && py1==0)) {
		delta_w = iWidth/2 - px1;
		delta_h = iHeight/2 - py1;

		if(abs(delta_w)>50) {
			if(abs(delta_w)<=150) m_nPanSpeedC1 = -5;
			else if(abs(delta_w)<=250) m_nPanSpeedC1 = -3;
			else if(abs(delta_w)<=350) m_nPanSpeedC1 = -1;

			Order.Format("/cgi-bin/camctrl.cgi?speedpan=%d",m_nPanSpeedC1);
			ExecuteOrder(Order,strServerName1,id1,passwd1);

			if(delta_w>0) {
				Order = "/cgi-bin/camctrl.cgi?move=left";
				ExecuteOrder(Order,strServerName1,id1,passwd1);		

				c1.theta_p += dep*pi/180.;
			}
			else if(delta_w<0) {
				Order = "/cgi-bin/camctrl.cgi?move=right";
				ExecuteOrder(Order,strServerName1,id1,passwd1);		

				c1.theta_p -= dep*pi/180.;
			}
		}

		if(abs(delta_h)>100) {
			if(delta_h<=150) m_nTiltSpeedC1 = 2;
			else if(delta_h>250) m_nTiltSpeedC1 = 5;

			Order.Format("/cgi-bin/camctrl.cgi?speedtilt=%d",m_nPanSpeedC1);
			ExecuteOrder(Order,strServerName1,id1,passwd1);

			if(delta_h>0) {
				Order = "/cgi-bin/camctrl.cgi?move=up";
				ExecuteOrder(Order,strServerName1,id1,passwd1);		
			}
			else if(delta_h<0) {
				Order = "/cgi-bin/camctrl.cgi?move=down";
				ExecuteOrder(Order,strServerName1,id1,passwd1);		
			}
		}
	}

	UpdateSetup();
	UpdateTestBed();
}

void CTestbedDlg::AdjustCamera2()
{
	CString Order;

	int delta_w,delta_h;
	double dep=0;

/*	if(c2.zoom_level<=3) dep = angle_z1to3_c2[m_nPanSpeedC2+5];
	else if(c2.zoom_level>3 && c2.zoom_level<=7) dep = angle_z4to7_c2[m_nPanSpeedC2+5];
	else if(c2.zoom_level>7) dep = angle_z8to10_c2[m_nPanSpeedC2+5];	*/
	dep = c2_angle_z[m_nPanSpeedC2+5];

	if(!(px2==0 && py2==0)) {
		delta_w = iWidth/2 - px2;
		delta_h = iHeight/2 - py2;

		if(abs(delta_w)>50) {
			if(abs(delta_w)<=150) m_nPanSpeedC2 = -5;
			else if(abs(delta_w)<=250) m_nPanSpeedC2 = -3;
			else if(abs(delta_w)<=350) m_nPanSpeedC2 = -1;

			Order.Format("/cgi-bin/camctrl.cgi?speedpan=%d",m_nPanSpeedC2);
			ExecuteOrder(Order,strServerName2,id2,passwd2);

			if(delta_w>0) {
				Order = "/cgi-bin/camctrl.cgi?move=left";
				ExecuteOrder(Order,strServerName2,id2,passwd2);		
				
				c2.theta_p += dep*pi/180.;
			}
			else if(delta_w<0) {
				Order = "/cgi-bin/camctrl.cgi?move=right";
				ExecuteOrder(Order,strServerName2,id2,passwd2);		

				c2.theta_p -= dep*pi/180.;
			}
		}

		if(abs(delta_h)>100) {
			if(delta_h<=150) m_nTiltSpeedC2 = 2;
			else if(delta_h>250) m_nTiltSpeedC2 = 5;

			Order.Format("/cgi-bin/camctrl.cgi?speedtilt=%d",m_nPanSpeedC2);
			ExecuteOrder(Order,strServerName2,id2,passwd2);

			if(delta_h>0) {
				Order = "/cgi-bin/camctrl.cgi?move=up";
				ExecuteOrder(Order,strServerName2,id2,passwd2);		
			}
			else if(delta_h<0) {
				Order = "/cgi-bin/camctrl.cgi?move=down";
				ExecuteOrder(Order,strServerName2,id2,passwd2);		
			}
		}
	}

	UpdateSetup();
	UpdateTestBed();
}

void CTestbedDlg::ExecuteOrder(CString Order,CString strServerName,CString id,CString passwd)
{
	INTERNET_PORT nPort = 80;
	
	m_pConnection = m_Session.GetHttpConnection(strServerName,nPort,id,passwd);
	if (!m_pConnection)
	{
		AfxMessageBox("Fail to connect", MB_OK);
		m_pConnection = NULL;
		return;
	}

    if (m_pConnection != NULL)
    {
		m_pFile = m_pConnection->OpenRequest(CHttpConnection::HTTP_VERB_GET,
			Order,NULL,1,NULL,NULL,INTERNET_FLAG_RELOAD); 

		m_pFile->SendRequest();
    }
	delete m_pFile;
	delete m_pConnection;
}

void CTestbedDlg::OnTimer(UINT nIDEvent) 
{
	if(nIDEvent==0) {
		COleDateTime	m_Date;
		m_Date = COleDateTime::GetCurrentTime();

		UpdateImageFromCamera1();
		UpdateImageFromCamera2();
		if(cnt<100) {
			if(m_bSave==1) {
				_strImageFileName1 = m_Date.Format(_T("_c1_%Y%D%I%M%S.jpg"));
				m_pImage1->Save(_strImageFileName1, CxImage::FindType(_strImageFileName1));

				_strImageFileName2 = m_Date.Format(_T("_c2_%Y%D%I%M%S.jpg"));
				m_pImage2->Save(_strImageFileName2, CxImage::FindType(_strImageFileName2));
			}
		} 
		UpdateTestBed();
	}	

	CDialog::OnTimer(nIDEvent);
}

void CTestbedDlg::OnMoveupc1() 
{
	CString Order;
	
	Order = "/cgi-bin/camctrl.cgi?move=up";
	ExecuteOrder(Order,strServerName1,id1,passwd1);

	// Update Image From Camera
	UpdateImageFromCamera1();
	UpdateSetup();
	UpdateTestBed();
}

void CTestbedDlg::OnMovedownc1() 
{
	CString Order;
	
	Order = "/cgi-bin/camctrl.cgi?move=down";
	ExecuteOrder(Order,strServerName1,id1,passwd1);

	// Update Image From Camera
	UpdateImageFromCamera1();
	UpdateSetup();
	UpdateTestBed();	
}

void CTestbedDlg::OnMoveleftc1() 
{
	// Update Camera Angle
	double dep=0;
/*	if(c1.zoom_level<=3) dep = angle_z1to3_c1[m_nPanSpeedC1+5];
	else if(c1.zoom_level>3 && c1.zoom_level<=7) dep = angle_z4to7_c1[m_nPanSpeedC1+5];
	else if(c1.zoom_level>7) dep = angle_z8to10_c1[m_nPanSpeedC1+5];	*/
	dep = c1_angle_z[m_nPanSpeedC1+5];

	c1.theta_p -= dep*pi/180.;

	CString Order;
	
	Order = "/cgi-bin/camctrl.cgi?move=right";
	ExecuteOrder(Order,strServerName1,id1,passwd1);

	// Update Image From Cameras
	UpdateImageFromCamera1();
	UpdateSetup();
	UpdateTestBed();	
}

void CTestbedDlg::OnMoverightc1() 
{
	// Update Camera Angle
	double dep=0;
/*	if(c1.zoom_level<=3) dep = angle_z1to3_c1[m_nPanSpeedC1+5];
	else if(c1.zoom_level>3 && c1.zoom_level<=7) dep = angle_z4to7_c1[m_nPanSpeedC1+5];
	else if(c1.zoom_level>7) dep = angle_z8to10_c1[m_nPanSpeedC1+5];	*/
	dep = c1_angle_z[m_nPanSpeedC1+5];

	c1.theta_p += dep*pi/180.;

	CString Order;
	
	Order = "/cgi-bin/camctrl.cgi?move=left";
	ExecuteOrder(Order,strServerName1,id1,passwd1);

	// Update Image From Cameras
	UpdateImageFromCamera1();
	UpdateSetup();
	UpdateTestBed();	
}

void CTestbedDlg::OnMovehomec1() 
{
	// Upate Camera Angle
	c1.theta_p = 0;
	c1.zoom_level = 1;

	CString Order;
	
	Order = "/cgi-bin/camctrl.cgi?move=home";
	ExecuteOrder(Order,strServerName1,id1,passwd1);

	// Update Image From Cameras
	UpdateImageFromCamera1();
	UpdateSetup();
	UpdateTestBed();	
}

void CTestbedDlg::OnZoominc1() 
{
	// Update zoom level
	c1.zoom_level++;
	if(c1.zoom_level>10) c1.zoom_level = 10;

	CString Order;
	
	Order = "/cgi-bin/camctrl.cgi?zoom=tele";
	ExecuteOrder(Order,strServerName1,id1,passwd1);

	// Update Image From Cameras
	UpdateImageFromCamera1();
	UpdateSetup();
	UpdateTestBed();		
}

void CTestbedDlg::OnZoomoutc1() 
{
	// Update zoom level
	c1.zoom_level--;
	if(c1.zoom_level<1) c1.zoom_level = 1;

	CString Order;
	
	Order = "/cgi-bin/camctrl.cgi?zoom=wide";
	ExecuteOrder(Order,strServerName1,id1,passwd1);

	// Update Image From Cameras
	UpdateImageFromCamera1();
	UpdateSetup();
	UpdateTestBed();	
}

void CTestbedDlg::OnCoordinatec1() 
{
	UpdateData(TRUE);

	if(!(px1==0 && py1==0)) m_strObjectCoordinateC1.Format("(%3d, %3d)",px1,py1);
	else	m_strObjectCoordinateC1.Format("Nothing");

	UpdateData(FALSE);	
}

void CTestbedDlg::OnMoveupc2() 
{
	CString Order;
	
	Order = "/cgi-bin/camctrl.cgi?move=up";
	ExecuteOrder(Order,strServerName2,id2,passwd2);

	// Update Image From Camera
	UpdateImageFromCamera2();
	UpdateSetup();
	UpdateTestBed();
}

void CTestbedDlg::OnMovedownc2() 
{
	CString Order;
	
	Order = "/cgi-bin/camctrl.cgi?move=down";
	ExecuteOrder(Order,strServerName2,id2,passwd2);

	// Update Image From Camera
	UpdateImageFromCamera2();
	UpdateSetup();
	UpdateTestBed();	
}

void CTestbedDlg::OnMoveleftc2() 
{
	// Update Camera Angle
	double dep=0;
/*	if(c2.zoom_level<=3) dep = angle_z1to3_c2[m_nPanSpeedC2+5];
	else if(c2.zoom_level>3 && c2.zoom_level<=7) dep = angle_z4to7_c2[m_nPanSpeedC2+5];
	else if(c2.zoom_level>7) dep = angle_z8to10_c2[m_nPanSpeedC2+5];	*/
	dep = c2_angle_z[m_nPanSpeedC2+5];

	c2.theta_p -= dep*pi/180.;

	CString Order;
	
	Order = "/cgi-bin/camctrl.cgi?move=right";
	ExecuteOrder(Order,strServerName2,id2,passwd2);

	// Update Image From Cameras
	UpdateImageFromCamera2();
	UpdateSetup();
	UpdateTestBed();	
}

void CTestbedDlg::OnMoverightc2() 
{
	// Update Camera Angle
	double dep=0;
/*	if(c2.zoom_level<=3) dep = angle_z1to3_c2[m_nPanSpeedC2+5];
	else if(c2.zoom_level>3 && c2.zoom_level<=7) dep = angle_z4to7_c2[m_nPanSpeedC2+5];
	else if(c2.zoom_level>7) dep = angle_z8to10_c2[m_nPanSpeedC2+5];	*/
	dep = c2_angle_z[m_nPanSpeedC2+5];

	c2.theta_p += dep*pi/180.;

	CString Order;
	
	Order = "/cgi-bin/camctrl.cgi?move=left";
	ExecuteOrder(Order,strServerName2,id2,passwd2);

	// Update Image From Cameras
	UpdateImageFromCamera2();
	UpdateSetup();
	UpdateTestBed();	
}

void CTestbedDlg::OnMovehomec2() 
{
	// Upate Camera Angle
	c2.theta_p = 0;
	c2.zoom_level = 1;

	CString Order;
	
	Order = "/cgi-bin/camctrl.cgi?move=home";
	ExecuteOrder(Order,strServerName2,id2,passwd2);

	// Update Image From Cameras
	UpdateImageFromCamera2();
	UpdateSetup();
	UpdateTestBed();	
}

void CTestbedDlg::OnZoominc2() 
{
	// Update zoom level
	c2.zoom_level++;
	if(c2.zoom_level>10) c2.zoom_level = 10;

	CString Order;
	
	Order = "/cgi-bin/camctrl.cgi?zoom=tele";
	ExecuteOrder(Order,strServerName2,id2,passwd2);

	// Update Image From Cameras
	UpdateImageFromCamera2();
	UpdateSetup();
	UpdateTestBed();		
}

void CTestbedDlg::OnZoomoutc2() 
{
	// Update zoom level
	c2.zoom_level--;
	if(c2.zoom_level<1) c2.zoom_level = 1;

	CString Order;
	
	Order = "/cgi-bin/camctrl.cgi?zoom=wide";
	ExecuteOrder(Order,strServerName2,id2,passwd2);

	// Update Image From Cameras
	UpdateImageFromCamera2();
	UpdateSetup();
	UpdateTestBed();	
}

void CTestbedDlg::OnCoordinatec2() 
{
	UpdateData(TRUE);

	if(!(px2==0 && py2==0)) m_strObjectCoordinateC2.Format("(%3d, %3d)",px2,py2);
	else	m_strObjectCoordinateC2.Format("Nothing");

	UpdateData(FALSE);	
}

void CTestbedDlg::OnSnapshot() 
{
	COleDateTime	m_Date;
	m_Date = COleDateTime::GetCurrentTime();
	CString strSnapshotFileName1,strSnapshotFileName2;

	strSnapshotFileName1 = m_Date.Format(_T("c1_%Y%D%I%M%S.jpg"));
	strSnapshotFileName2 = m_Date.Format(_T("c2_%Y%D%I%M%S.jpg"));

	m_pImage1->Save(strSnapshotFileName1,CxImage::FindType(strSnapshotFileName1));	
	m_pImage2->Save(strSnapshotFileName2,CxImage::FindType(strSnapshotFileName2));	
}


void CTestbedDlg::OnSavestop() 
{
	m_bSave = 0;
}

void CTestbedDlg::OnSavestart() 
{
	m_bSave = 1;	
}

void CTestbedDlg::OnIsolationstop() 
{
	m_bIsolation = 0;	
}

void CTestbedDlg::OnIsolationstart() 
{
	m_bIsolation = 1;	
}

void CTestbedDlg::OnTracestop() 
{
	m_bTrace = 0;
}

void CTestbedDlg::OnTracestart() 
{
	m_bTrace = 1;	
}

void CTestbedDlg::OnChangeSaveinterval() 
{
UpdateData(TRUE);

	CString strSaveInterval;
	m_ctrlSaveInterval.GetLBText(m_nSaveInterval,strSaveInterval);

	switch(m_nSaveInterval)
	{
		case 0 : TimeDepth = 100; break;  // 0.1
		case 1 : TimeDepth = 200; break; // 0.2
		case 2 : TimeDepth = 500; break; // 0.5
		case 3 : TimeDepth = 1000; break; // 1
		case 4 : TimeDepth = 2000; break; // 2
		case 5 : TimeDepth = 5000; break; // 5
		case 6 : TimeDepth = 10000; break; // 10
		case 7 : TimeDepth = 60000; break; // 60
	}
	KillTimer(0);
	SetTimer(0,TimeDepth,NULL);
	
	UpdateData(FALSE);		
}

/*void CTestbedDlg::OnPositionc1() 
{
	UpdateData(TRUE);

	double theta_c1;

	if(c1.type==1) theta_c1 = c1.theta_p;
	else if(c1.type==2) theta_c1 = c1.theta_p + pi/2.;
	else if(c1.type==3) theta_c1 = c1.theta_p + pi;
	else if(c1.type==4) theta_c1 = c1.theta_p + 3.*pi/2.;

	m_strPositionC1.Format("(%3d, %3d), %3.0lf\'",c1.x,c1.y,theta_c1*180./pi);

	UpdateData(FALSE);	
} */


void CTestbedDlg::OnAngles() 
{
	UpdateData(TRUE);

	double theta_c1,theta_c2;

	if(c1.type==1) theta_c1 = c1.theta_p;
	else if(c1.type==2) theta_c1 = c1.theta_p + pi/2.;
	else if(c1.type==3) theta_c1 = c1.theta_p + pi;
	else if(c1.type==4) theta_c1 = c1.theta_p + 3.*pi/2.;

	if(c2.type==1) theta_c2 = c2.theta_p;
	else if(c2.type==2) theta_c2 = c2.theta_p + pi/2.;
	else if(c2.type==3) theta_c2 = c2.theta_p + pi;
	else if(c2.type==4) theta_c2 = c2.theta_p + 3.*pi/2.;

	m_strAngles.Format("Angles (%3d\', %3d\')",(int)(theta_c1*180./pi),(int)(theta_c2*180./pi));

	UpdateData(FALSE);	
}

