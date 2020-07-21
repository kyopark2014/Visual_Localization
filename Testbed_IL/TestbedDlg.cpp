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

#define n_AreaSizeX 280 
#define n_AreaSizeY 170

CTestbedDlg::CTestbedDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestbedDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestbedDlg)
	m_strObjectCoordinateC1 = _T("");
	m_strObjectCoordinateC2 = _T("");
	m_bSave = 0;
	m_bIsolation = 1;
	m_bTrace = 0;
	m_nSaveInterval = -1;
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
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestbedDlg message handlers
double xpr=0,ypr=0;

BOOL CTestbedDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
//	CBitmap SetupBackground;
//	SetupBackground.LoadBitmap(IDB_SETUPBACKGROUND);

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
//	c1.x = (int)(sWidth/280.*136.);
//	c1.y = (int)(sHeight/170.*(170.-18.));
	c1.x = 136;
	c1.y = n_AreaSizeY-1-18;
	c1.type = 3;
	c1.theta_p = 0;
	c1.zoom_level = 1;
	c1.length = 20;

//	c2.x = (int)(sWidth/280.*205.)+4;
//	c2.y = (int)(sHeight/170.*(170.-18.));
	c2.x = 205;
	c2.y = n_AreaSizeY-1-18;
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
//	dcSetup.SelectObject(&SetupBackground);

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
//	InitializeSetup(); 

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
	c1.theta_p += dep;
	ExecuteOrder(Order,strServerName1,id1,passwd1);		
	c1.theta_p += dep;
	ExecuteOrder(Order,strServerName1,id1,passwd1);		
	c1.theta_p += dep;
	ExecuteOrder(Order,strServerName1,id1,passwd1);		
	c1.theta_p += dep;
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
	c2.theta_p -= dep;
	ExecuteOrder(Order,strServerName2,id2,passwd2);		
	c2.theta_p -= dep;
	ExecuteOrder(Order,strServerName2,id2,passwd2);		
	c2.theta_p -= dep;
	ExecuteOrder(Order,strServerName2,id2,passwd2);		
	c2.theta_p -= dep;
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
	double ex1=0,ey1=0,ex2=0,ey2=0,ex3=0,ey3=0,ex4=0,ey4=0;

	// Load image from memory
	m_pImage3->Load("./setup.jpg",CxImage::FindType("setup.jpg"));

	// Copy Detection result
	m_pImage3->Draw(dcSetup,CRect(0,0,sWidth,sHeight));
	
	// Update Camera 
	DrawCameraSetup(c1);
	DrawCameraSetup(c2);

	int up1,up2;
	double xe,ye,theta_c1,theta_c2;
	double dx,dy,upp1,upp2;
	
	if(c1.type==1) theta_c1 = c1.theta_p*pi/180.;
	else if(c1.type==2) theta_c1 = c1.theta_p*pi/180. + pi/2.;
	else if(c1.type==3) theta_c1 = c1.theta_p*pi/180. + pi;
	else if(c1.type==4) theta_c1 = c1.theta_p*pi/180. + 3.*pi/2.;

	if(c2.type==1) theta_c2 = c2.theta_p*pi/180.;
	else if(c2.type==2) theta_c2 = c2.theta_p*pi/180. + pi/2.;
	else if(c2.type==3) theta_c2 = c2.theta_p*pi/180. + pi;
	else if(c2.type==4) theta_c2 = c2.theta_p*pi/180. + 3.*pi/2.;

	// First Iteration
	xe = 160;
	ye = 60;
//	xe = n_AreaSizeX/2-1;
//	ye = n_AreaSizeY/2-1;
//	ye = 10;
	
	up1 = px1-(iWidth/2-1);
	up2 = px2-(iWidth/2-1);


	dy = GetDeltau(xe);
	dx = GetDeltau(ye);

	upp1 = up1/dy;
	upp2 = up2/dx;

	ex1 = xe;
	ey1 = ye;

	DoLocalization(xe,ye,upp1,upp2,theta_c1,theta_c2);
//	DrawPoint((int)xe,(int)ye,11); // Draw E

	// Second Iteration
	dy = GetDeltau(xpr);
	dx = GetDeltau(ypr);

	upp1 = up1/dy;
	upp2 = up2/dx;

	ex2 = xpr;
	ey2 = ypr;

	DoLocalization(xpr,ypr,upp1,upp2,theta_c1,theta_c2);
//	DrawPoint((int)xpr,(int)ypr,12); // Draw E

	// Third Iteration
	dy = GetDeltau(xpr);
	dx = GetDeltau(ypr);

	upp1 = up1/dy;
	upp2 = up2/dx;

	ex3 = xpr;
	ey3 = ypr;

	DoLocalization(xpr,ypr,upp1,upp2,theta_c1,theta_c2); 
	DrawPoint((int)xpr,(int)ypr,13); // Draw E

	ex4 = xpr;
	ey4 = ypr; 

		// Draw P
		DrawPoint((int)xpr,(int)ypr,2);

		FILE *fp;
		fp = fopen("result.txt","w");
		fprintf(fp,"C1(%d/%d,%d/%d)\n",c1.x,n_AreaSizeX,c1.y,n_AreaSizeY);
		fprintf(fp,"C2(%d/%d,%d/%d)\n",c2.x,n_AreaSizeX,c2.y,n_AreaSizeY);

		fprintf(fp,"px1=%d/%d,px2=%d/%d\n",px1,iWidth,px2,iWidth);
		fprintf(fp,"E(%lf,%lf)\n",xe,ye);
		fprintf(fp,"up1=%d,up2=%d\n",up1,up2);
		fprintf(fp,"dx=%lf,dy=%lf\n",dx,dy);
		fprintf(fp,"upp1=%lf,upp2=%lf\n",upp1,upp2);
		fprintf(fp,"theta_c1=%lf,theta_c2=%lf\n",theta_c1,theta_c2);
		fprintf(fp,"xpr=%lf,ypr=%lf\n",xpr,ypr);
		fclose(fp);

		fp = fopen("estimate.txt","w");
		fprintf(fp,"E0(%4.2lf,%4.2lf)\n",ex1,ey1);
		fprintf(fp,"E1(%4.2lf,%4.2lf)\n",ex2,ey2);
		fprintf(fp,"E2(%4.2lf,%4.2lf)\n",ex3,ey3);
		fprintf(fp,"E3(%4.2lf,%4.2lf)\n",ex4,ey4);
		fclose(fp);
}

void CTestbedDlg::DrawPoint(int x,int y,int type)
{
	int rx1,ry1,rx2,ry2;
	int dep=6;
	double x_t,y_t;

	CPen pen;
	if(type == 11) { //Estimate		
		pen.CreatePen(PS_SOLID,2,RGB(0,0,255));		
	}
	else if(type == 12) { //Estimate		
		pen.CreatePen(PS_SOLID,2,RGB(200,0,0));		
	}
	else if(type == 13) { //Estimate		
		pen.CreatePen(PS_SOLID,2,RGB(150,0,0));		
	}
	else { //Object		
		pen.CreatePen(PS_SOLID,2,RGB(0,255,0));		
	}
	dcSetup.SelectObject(&pen);

	x_t = (int)(sWidth/(double)n_AreaSizeX*x);
	y_t = (int)(sHeight/(double)n_AreaSizeY*(n_AreaSizeY-1-y));

	rx1 = (int)(x_t-dep);
	ry1 = (int)(y_t-dep);
	rx2 = (int)(x_t+dep);
	ry2 = (int)(y_t+dep);

	dcSetup.Ellipse(rx1,ry1,rx2,ry2); 
}

void CTestbedDlg::DrawCameraSetup(param_camera c)
{
	int xp1,yp1,xp2,yp2;
	double theta_c;
	int cx,cy;

	if(c.type==1) theta_c = c.theta_p*pi/180.;
	else if(c.type==2) theta_c = c.theta_p*pi/180. + pi/2.;
	else if(c.type==3) theta_c = c.theta_p*pi/180. + pi;
	else if(c.type==4) theta_c = c.theta_p*pi/180. + 3.*pi/2.;

	// Camera Parameters
	cx = (int)(sWidth/(double)n_AreaSizeX*c.x);
	cy = (int)(sHeight/(double)n_AreaSizeY*c.y);

	CPen pen1;
	pen1.CreatePen(PS_SOLID,4,RGB(0,0,0));
	dcSetup.SelectObject(&pen1);

	xp1 = cx-(int)(c.length/2.*cos(theta_c));
	yp1 = cy-(int)(c.length/2.*sin(theta_c));
	xp2 = cx+(int)(c.length/2.*cos(theta_c));
	yp2 = cy+(int)(c.length/2.*sin(theta_c));

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
	xn = (int)(cx-ln*sin(theta_c));
	if(xn<0) xn=0;
	yn = (int)(cy+ln*cos(theta_c));
	if(yn<0) yn=0;

	xr1 = cx;
	yr1 = sHeight-cy;
	xr2 = xn;
	yr2 = sHeight-1-yn;

	dcSetup.MoveTo(xr1,yr1);
	dcSetup.LineTo(xr2,yr2); 

	CPen pen3;
	pen3.CreatePen(PS_SOLID,2,RGB(50,130,148));
	dcSetup.SelectObject(&pen3);
	// Range
	xn = (int)(cx-ln*sin(theta_c+150));
	if(xn<0) xn=0;
	yn = (int)(cy+ln*cos(theta_c+150));
	if(yn<0) yn=0;

	xr1 = cx;
	yr1 = sHeight-cy;
	xr2 = xn;
	yr2 = sHeight-1-yn;

	dcSetup.MoveTo(xr1,yr1);
	dcSetup.LineTo(xr2,yr2); 

	xn = (int)(cx-ln*sin(theta_c-150));
	if(xn<0) xn=0;
	yn = (int)(cy+ln*cos(theta_c-150));
	if(yn<0) yn=0;

	xr1 = cx;
	yr1 = sHeight-cy;
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

	if(max==0) {
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

				c1.theta_p += dep;
			}
			else if(delta_w<0) {
				Order = "/cgi-bin/camctrl.cgi?move=right";
				ExecuteOrder(Order,strServerName1,id1,passwd1);		

				c1.theta_p -= dep;
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
				
				c2.theta_p += dep;
			}
			else if(delta_w<0) {
				Order = "/cgi-bin/camctrl.cgi?move=right";
				ExecuteOrder(Order,strServerName2,id2,passwd2);		

				c2.theta_p -= dep;
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
		UpdateSetup();
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

	c1.theta_p -= dep;

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

	c1.theta_p += dep;

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

	c2.theta_p -= dep;

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

	c2.theta_p += dep;

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

//************************************************************************
#define table_sz 10

double table_1d[table_sz] = {168.4, 106, 78.6, 62.2, 51.6, 44.2, 38.4,  34,  30.8,  27.7};
double table_d[table_sz] =  {   24,  36, 48.0, 60.0, 72.0, 84.0, 96.0, 108, 120.0, 132.0};
double table_z[table_sz] = {1.356,1.280,1.266,1.252,1.246,1.246,1.237,1.232,1.240,1.227};

double CTestbedDlg::GetDeltau(double d)
{
	bool bool_n=1;
	int n;
	double delta_u;
	int near_d;

	for(n=0;n<table_sz;n++) {
		if(d == table_d[n]) {
	        delta_u = table_1d[n];
		    bool_n = 0;
		}
	}

	if(bool_n==1) {
		if (d<table_d[0] || d>table_d[table_sz-1]) {
			double Z,Lc;
			Z = table_z[table_sz-1];
			Lc = d/Z;
			delta_u = iWidth/Lc;
		}
		else {
			near_d = FindNearD(d);
			if(d>table_d[near_d])  {
				delta_u = table_1d[near_d] + (table_1d[near_d+1]-table_1d[near_d])/(d-table_d[near_d]);
			}					
			else {
				delta_u = table_1d[near_d] + (table_1d[near_d]-table_1d[near_d-1])/(table_d[near_d-1]-d);       
			}	
		} 
	}
	return delta_u;
}



int CTestbedDlg::FindNearD(double d)
{
	int i;
	double min_v;
	int min_index=0;

	min_v = fabs(table_d[0]-d);
	for(i=1;i<table_sz;i++) {
		if(fabs(table_d[i]-d)<min_v) {
			min_v = fabs(table_d[i]-d);
			min_index = i;
		}
	}

	return min_index;
}

void CTestbedDlg::DoLocalization(double xe,double ye,double upp1,double upp2,double theta_c1,double theta_c2)
{
	double upe1,upe2;
	double xpp1,ypp1,xpp2,ypp2;
	double xpe1,ype1,xpe2,ype2;
	double delta_u1,delta_u2;
	double delta_uc1,delta_uc2;
	double de1,de2;
	double delta_d1,delta_d2;
	double A,B;
	double Z1,Z1p,Z2,Z2p;
	double upp1p,upp2p;

	int xc1,yc1,xc2,yc2;
	double xp,yp;

	xc1 = c1.x; yc1 = c1.y;
	xc2 = c2.x; yc2 = c2.y;

	// do tracking
	upe1 = (xe-xc1)*cos(theta_c1) + (ye-yc1)*sin(theta_c1);
	upe2 = (xe-xc2)*cos(theta_c2) + (ye-yc2)*sin(theta_c2);

	xpp1 = xc1+upp1*cos(theta_c1);
	ypp1 = yc1+upp1*sin(theta_c1);
	xpp2 = xc2+upp2*cos(theta_c2);
	ypp2 = yc2+upp2*sin(theta_c2);
    
	xpe1 = xc1+upe1*cos(theta_c1);
	ype1 = yc1+upe1*sin(theta_c1);
	xpe2 = xc2+upe2*cos(theta_c2);
	ype2 = yc2+upe2*sin(theta_c2);
    
	delta_u1 = (xpp1-xpe1)*cos(theta_c1)+(ypp1-ype1)*sin(theta_c1);
	delta_u2 = (xpp2-xpe2)*cos(theta_c2)+(ypp2-ype2)*sin(theta_c2);
       
	delta_uc1 = delta_u1 - ((xpp1-xpe1)*(xpp2-xpe2)+(ypp1-ype1)*(ypp2-ype2))/delta_u1;
	delta_uc2 = delta_u2 - ((xpp1-xpe1)*(xpp2-xpe2)+(ypp1-ype1)*(ypp2-ype2))/delta_u2;

	de1 = sqrt(pow((xe-xpe1),2) + pow((ye-ype1),2));
	de2 = sqrt(pow((xe-xpe2),2) + pow((ye-ype2),2));

	delta_d1 = de1 * delta_uc2 / ((xe-xpe1)*cos(theta_c2) + (ye-ype1)*sin(theta_c2));
	delta_d2 = de2 * delta_uc1 / ((xe-xpe2)*cos(theta_c1) + (ye-ype2)*sin(theta_c1));
  
	A = upp1+xc1*cos(theta_c1)+yc1*sin(theta_c1);
	B = upp2+xc2*cos(theta_c2)+yc2*sin(theta_c2);
	xp = (A*sin(theta_c2)-B*sin(theta_c1)) / (cos(theta_c1)*sin(theta_c2)-cos(theta_c2)*sin(theta_c1));
	yp = (A*cos(theta_c2)-B*cos(theta_c1)) / (cos(theta_c2)*sin(theta_c1)-cos(theta_c1)*sin(theta_c2));
      
	Z1 = GetNewZoomFactor(de1);
	Z1p = GetNewZoomFactor(de1+delta_d1);
    
	Z2 = GetNewZoomFactor(de2);
	Z2p = GetNewZoomFactor(de2+delta_d2);
    
	upp1p = upp1*((de1+delta_d1)/de1)*(Z1/Z1p);
	upp2p = upp2*((de2+delta_d2)/de2)*(Z2/Z2p);
   
	A = upp1p+xc1*cos(theta_c1)+yc1*sin(theta_c1);
	B = upp2p+xc2*cos(theta_c2)+yc2*sin(theta_c2);
	xpr = (A*sin(theta_c2)-B*sin(theta_c1)) / (cos(theta_c1)*sin(theta_c2)-cos(theta_c2)*sin(theta_c1));
	ypr = (A*cos(theta_c2)-B*cos(theta_c1)) / (cos(theta_c2)*sin(theta_c1)-cos(theta_c1)*sin(theta_c2)); 

	FILE *fp;
	fp = fopen("A.txt","w");
	fprintf(fp,"C(%d,%d),C2(%d %d)\n",xc1,yc1,xc2,yc2);
	fprintf(fp,"E(%lf,%lf)\n",xe,ye);
	fprintf(fp,"upe1=%lf,upe2=%lf\n",upe1,upe2);
	fprintf(fp,"xp=%lf,yp=%lf\n",xp,yp);
	fprintf(fp,"upp1=%lf,upp2=%lf\n",upp1,upp2);
	fprintf(fp,"upp1p=%lf,upp2p=%lf\n",upp1p,upp2p);
	fprintf(fp,"(Z1/Z1p)=%lf,(Z2/Z2p)=%lf\n",(Z1/Z1p),(Z2/Z2p));
	fprintf(fp,"(de1+delta_d1)/de1=%lf,(de1+delta_d1)/de1=%lf\n",(de1+delta_d1)/de1,(de1+delta_d1)/de1);
	fprintf(fp,"delta_d1=%lf,delta_d2=%lf\n",delta_d1,delta_d2);
	fprintf(fp,"de1=%lf,dp1=%lf\n",de1,de1+delta_d1);
	fprintf(fp,"de2=%lf,dp2=%lf\n",de2,de2+delta_d2);
	fprintf(fp,"Z1=%lf, Z1p=%lf, Z2=%lf, Z2p=%lf\n",Z1,Z1p,Z2,Z2p);
	fprintf(fp,"xpr=%lf,ypr=%lf\n",xpr,ypr);

	fclose(fp);
} 

double CTestbedDlg::GetNewZoomFactor(double d)
{
	double Zp=0;
	int near_d;

	bool bool_k=1;
	for(int k=0; k<table_sz; k++) {
		if(table_d[k] == d) {
	        Zp = table_z[k];
		    bool_k = 0;
		}
	}

	if(bool_k==1)  {
		if (d < table_d[0]) Zp = table_z[0];
		else if (d > table_d[table_sz-1]) Zp = table_z[table_sz-1];
		else {
			near_d = FindNearD(d);
			if(d>table_d[near_d])  {
				Zp = table_z[near_d] + (table_z[near_d+1]-table_z[near_d])/(d-table_z[near_d]);
			}					
			else {
				Zp = table_z[near_d] + (table_z[near_d]-table_z[near_d-1])/(table_z[near_d-1]-d);
			}
		}
	}

	return Zp;
}
