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

#define	pw 51
#define	ph 51

/////////////////////////////////////////////////////////////////////////////
// CTestbedDlg dialog

CTestbedDlg::CTestbedDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestbedDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestbedDlg)
	m_Savec1 = 0;
	m_nSaveInterval = -1;
	m_nPanSpeedC1 = -1;
	m_nTiltSpeedC1 = -1;
	m_nZoomSpeedC1 = -1;
	m_nFocusSpeedC1 = -1;
	m_nIsolation = 1;
	m_nTrace = 0;
	m_nSelectC1 = 0;
	m_strObjectCoordinate = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	px = 0, py = 0;
}

void CTestbedDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestbedDlg)
	DDX_Control(pDX, IDC_FOCUSSPEEDC1, m_ctrlFocusSpeedC1);
	DDX_Control(pDX, IDC_ZOOMSPEEDC1, m_ctrlZoomSpeedC1);
	DDX_Control(pDX, IDC_TILTSPEEDC1, m_ctrlTiltSpeedC1);
	DDX_Control(pDX, IDC_PANSPEEDC1, m_ctrlPanSpeedC1);
	DDX_Control(pDX, IDC_SAVEINTERVAL, m_ctrlSaveInterval);
	DDX_Radio(pDX, IDC_SAVEC1STOP, m_Savec1);
	DDX_CBIndex(pDX, IDC_SAVEINTERVAL, m_nSaveInterval);
	DDX_CBIndex(pDX, IDC_PANSPEEDC1, m_nPanSpeedC1);
	DDX_CBIndex(pDX, IDC_TILTSPEEDC1, m_nTiltSpeedC1);
	DDX_CBIndex(pDX, IDC_ZOOMSPEEDC1, m_nZoomSpeedC1);
	DDX_CBIndex(pDX, IDC_FOCUSSPEEDC1, m_nFocusSpeedC1);
	DDX_Radio(pDX, IDC_ISOLATIONC1STOP, m_nIsolation);
	DDX_Radio(pDX, IDC_TRACEC1STOP, m_nTrace);
	DDX_Radio(pDX, IDC_SELECTCAMERA1, m_nSelectC1);
	DDX_Text(pDX, IDC_COORX, m_strObjectCoordinate);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTestbedDlg, CDialog)
	//{{AFX_MSG_MAP(CTestbedDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SNAPSHOT, OnSnapshot)
	ON_BN_CLICKED(IDC_MOVEUPC1, OnMoveupc1)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_MOVEDOWNC1, OnMovedownc1)
	ON_BN_CLICKED(IDC_MOVELEFTC1, OnMoveleftc1)
	ON_BN_CLICKED(IDC_MOVERIGHTC1, OnMoverightc1)
	ON_BN_CLICKED(IDC_MOVEHOMEC1, OnMovehomec1)
	ON_BN_CLICKED(IDC_ZOOMINC1, OnZoominc1)
	ON_BN_CLICKED(IDC_ZOOMOUTC1, OnZoomoutc1)
	ON_BN_CLICKED(IDC_FOCUSINC1, OnFocusinc1)
	ON_BN_CLICKED(IDC_FOCUSOUTC1, OnFocusoutc1)
	ON_BN_CLICKED(IDC_FOCUSAUTOC1, OnFocusautoc1)
	ON_BN_CLICKED(IDC_IRISINC1, OnIrisinc1)
	ON_BN_CLICKED(IDC_IRISOUTC1, OnIrisoutc1)
	ON_BN_CLICKED(IDC_IRISAUTOC1, OnIrisautoc1)
	ON_BN_CLICKED(IDC_SAVEC1STOP, OnSavec1stop)
	ON_BN_CLICKED(IDC_SAVEC2START, OnSavec2start)
	ON_CBN_SELCHANGE(IDC_SAVEINTERVAL, OnChangeSaveinterval)
	ON_CBN_SELCHANGE(IDC_PANSPEEDC1, OnChangePanspeedc1)
	ON_CBN_SELCHANGE(IDC_TILTSPEEDC1, OnChangeTiltspeedc1)
	ON_CBN_SELCHANGE(IDC_ZOOMSPEEDC1, OnChangeZoomspeedc1)
	ON_CBN_EDITCHANGE(IDC_FOCUSSPEEDC1, OnChangeFocusspeedc1)
	ON_BN_CLICKED(IDC_ISOLATIONC1STOP, OnIsolationc1stop)
	ON_BN_CLICKED(IDC_ISOLATIONC2START, OnIsolationc2start)
	ON_BN_CLICKED(IDC_TRACEC1STOP, OnTracec1stop)
	ON_BN_CLICKED(IDC_ISOLATIONC1START, OnIsolationc1start)
	ON_BN_CLICKED(IDC_SELECTCAMERA1, OnSelectcamera1)
	ON_BN_CLICKED(IDC_SELECTCAMERA2, OnSelectcamera2)
	ON_BN_CLICKED(IDC_COORX, OnObjectCoordinate)
	ON_BN_CLICKED(IDC_CALIBRATION, OnCalibration)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestbedDlg message handlers

static CString range[] = {"-5", "-4", "-3", "-2", "-1", "0", "1", "2", "3", "4", "5"};
static CString TimeRange[] = {"0.1", "0.2", "0.5", "1", "2", "5", "10", "60"};

/*static double angle_z1to3[] = {0.32, 0.65, 1.29, 3.88, 7.75, 11.63, 15.50, 19.38, 23,26, 25.84, 28.42};
static double angle_z4to7[] = {0.32, 0.32, 0.65, 1.94, 3.88,  5.81,  7.75,  9.69, 11.63, 12.92, 14.21};
static double angle_z8to10[]= {0.32, 0.32, 0.32, 0.97, 1.94,  2.91,  3.88,  4.85,  5.81,  6.46,  7.11};*/
static double c1_angle_z[]= {2.9, 5.5, 7.9, 10.7, 12.9, 15.8, 18.2};
static double c2_angle_z[]= {3.1, 5.3, 9.5, 10.8, 13.4, 16, 18.3};

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

//	m_bCalibration = 1;

	iWidth = 704; iHeight = 480;
	sWidth = (int)(1196*0.4); sHeight = (int)(730*0.4);
	Width = iWidth + 226; 		Height = iHeight + 400;

	cntc1 = 0;

	color_R=156,color_G=186,color_B=206;

	strServerName1 = "129.49.69.81";  // Camera 2	
	id1 = "root";
	passwd1 = "msdl007";	
	strImageFileName1 = "video1.jpg";

//	COleDateTime	m_Date1;
//	m_Date1 = COleDateTime::GetCurrentTime();
//	strImageFileName1 = m_Date1.Format(_T("c_%Y%D%I%M%S.jpg"));
//	_strImageFileName1 = "_" + strImageFileName1;


	// Setup Camera Parameters
	m_nPanSpeedC1=1,m_nTiltSpeedC1=1,m_nZoomSpeedC1=1,m_nFocusSpeedC1=1;

	c1.x = (int)(sWidth/280.*136.);
	c1.y = (int)(sHeight/170.*(170.-18.));
	c1.type = 3;
	c1.theta_p = 0;
	c1.zoom_level = 1;
	c1.length = 20;

	c2.x = (int)(sWidth/280.*205.)+4;
	c2.y = (int)(sHeight/170.*(170.-18.));
	c2.type = 3;
	c2.theta_p = 0;
	c2.zoom_level = 1;
	c2.length = 20;

	int i;
	for(i=0;i<11;i++) {
		m_ctrlPanSpeedC1.AddString(range[i]);
		m_ctrlTiltSpeedC1.AddString(range[i]);
		m_ctrlZoomSpeedC1.AddString(range[i]);
		m_ctrlFocusSpeedC1.AddString(range[i]);
	} 

	for(i=0;i<8;i++) 
		m_ctrlSaveInterval.AddString(TimeRange[i]);

	CString Order;

	Order = "/cgi-bin/camctrl.cgi?move=home";
	ExecuteOrder(Order,strServerName1,id1,passwd1);

	Order.Format("/cgi-bin/camctrl.cgi?speedpan=%d",m_nPanSpeedC1);
	ExecuteOrder(Order,strServerName1,id1,passwd1);
	Order.Format("/cgi-bin/camctrl.cgi?speedtilt=%d",m_nTiltSpeedC1);
	ExecuteOrder(Order,strServerName1,id1,passwd1);
	Order.Format("/cgi-bin/camctrl.cgi?speedzoom=%d",m_nZoomSpeedC1);
	ExecuteOrder(Order,strServerName1,id1,passwd1);
	Order.Format("/cgi-bin/camctrl.cgi?speedapp=%d",m_nFocusSpeedC1);
	ExecuteOrder(Order,strServerName1,id1,passwd1); 

	// make gauss mask
	GaussDistribution();

	xc1 = 200;
	yc1 = 20;

	xs = xc1;
	ys = iHeight + yc1*2;

	SetWindowPos(NULL,0,0,Width,Height+30,SWP_NOMOVE|SWP_SHOWWINDOW); // Adjust testbed size

	m_pImage = new CxImage;

	// Initialize dcMem
	CClientDC dc(this);	
	dcMem1.CreateCompatibleDC(&dc);
	CBitmap bitmap;
	bitmap.CreateCompatibleBitmap(&dc,iWidth,iHeight);
	dcMem1.SelectObject(&bitmap);

	// Setup
	dcSetup.CreateCompatibleDC(&dc);	
	CBitmap bitmap_setup;
	bitmap_setup.CreateCompatibleBitmap(&dc,sWidth,sHeight);
	dcSetup.SelectObject(&bitmap_setup);

	// Load Image Data from camera;
	UpdateImageFromCamera(strServerName1,id1,passwd1);

	// Update Setup
	UpdateSetup();

	// Update Testbed
	UpdateTestBed();

	// Show Object Coordinate
	OnObjectCoordinate();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

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
		UpdateTestBed();
		CDialog::OnPaint();
	}
}

HCURSOR CTestbedDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTestbedDlg::OnTimer(UINT nIDEvent) 
{
	if(nIDEvent==0) {
		UpdateImageFromCamera(strServerName1,id1,passwd1);

		if(m_Savec1==1) {
			if(cntc1<100) {
				COleDateTime	m_Date1;
				m_Date1 = COleDateTime::GetCurrentTime();
				if(m_nSelectC1==0) _strImageFileName1 = m_Date1.Format(_T("_c1_%Y%D%I%M%S.jpg"));
				else _strImageFileName1 = m_Date1.Format(_T("_c2_%Y%D%I%M%S.jpg"));

				m_pImage->Save(_strImageFileName1, CxImage::FindType(_strImageFileName1));
				cntc1++;
			}
		}
		UpdateTestBed();
	}

	CDialog::OnTimer(nIDEvent);
}

BOOL CTestbedDlg::DestroyWindow() 
{
	KillTimer(0);	

	return CDialog::DestroyWindow();
}

void CTestbedDlg::UpdateTestBed()
{
	CClientDC dc(this);	

	// Show Camera Images
	dc.BitBlt(xc1,yc1,iWidth,iHeight,&dcMem1,0,0,SRCCOPY); // camera 1
	dc.BitBlt(xs,ys,sWidth,sHeight,&dcSetup,0,0,SRCCOPY); // setup
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

void CTestbedDlg::UpdateImageFromCamera(CString strServerName,CString id,CString passwd)
{	
	// Load image from camera
	LoadImageFromCamera(strServerName1,strImageFileName1,id1,passwd1);

	// Load image from memory
	m_pImage->Load(strImageFileName1,CxImage::FindType(strImageFileName1));

	// Object isolation
	if(m_nIsolation) {
		FindFace();
		DrawObject();  // DrawBox in image file
	}

	// Copy Detection result
	m_pImage->Draw(dcMem1,CRect(0,0,iWidth,iHeight));

	// Draw Box in screen
	if(m_nIsolation) {
		ShowBox(); // DrawBox in screen
	}

	// Adjust Camera
	if(m_nTrace) {
		AdjustCamera(px,py,strServerName1,id1,passwd1);
	}
	
	// Show Object Coordinate
	OnObjectCoordinate();

//	if(m_bCalibration==1) {
		CPen pen;
		pen.CreatePen(PS_DOT,1,RGB(255,0,0));
		dcMem1.SelectObject(&pen);

		dcMem1.MoveTo(0,iHeight/2-1);
		dcMem1.LineTo(iWidth-1,iHeight/2-1);
		dcMem1.MoveTo(iWidth/2-1,0);
		dcMem1.LineTo(iWidth/2-1,iHeight-1);
//	}
}

void CTestbedDlg::UpdateSetup()
{
	// Load image from memory
	m_pImage->Load("setup.jpg",CxImage::FindType("setup.jpg"));

	// Copy Detection result
	m_pImage->Draw(dcSetup,CRect(0,0,sWidth,sHeight));
	
	// Update Camera 
	if(m_nSelectC1==0)	DrawCameraSetup(c1);
	else DrawCameraSetup(c2);

	// Show Setup
	CClientDC dc(this);	
	dc.BitBlt(xs,ys,sWidth,sHeight,&dcSetup,0,0,SRCCOPY); // setup
}

void CTestbedDlg::DrawCameraSetup(param_camera c)
{
	int xp1,yp1,xp2,yp2;
	double theta_c;

	if(c.type==1) theta_c = c.theta_p;
	else if(c.type==2) theta_c = c.theta_p + pi/2.;
	else if(c.type==3) theta_c = c.theta_p + pi;
	else if(c.type==4) theta_c = c.theta_p + 3.*pi/2.;

	CPen pen1;
	pen1.CreatePen(PS_SOLID,4,RGB(0,0,0));
	dcSetup.SelectObject(&pen1);

	xp1 = c.x-(int)(c.length/2.*cos(theta_c));
	yp1 = c.y-(int)(c.length/2.*sin(theta_c));
	xp2 = c.x+(int)(c.length/2.*cos(theta_c));
	yp2 = c.y+(int)(c.length/2.*sin(theta_c));

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
	xn = (int)(c.x-ln*sin(theta_c));
	if(xn<0) xn=0;
	yn = (int)(c.y+ln*cos(theta_c));
	if(yn<0) yn=0;

	xr1 = c.x;
	yr1 = sHeight-c.y;
	xr2 = xn;
	yr2 = sHeight-1-yn;

	dcSetup.MoveTo(xr1,yr1);
	dcSetup.LineTo(xr2,yr2); 

	CPen pen3;
	pen3.CreatePen(PS_SOLID,2,RGB(50,130,148));
	dcSetup.SelectObject(&pen3);
	// Range
	xn = (int)(c.x-ln*sin(theta_c+150));
	if(xn<0) xn=0;
	yn = (int)(c.y+ln*cos(theta_c+150));
	if(yn<0) yn=0;

	xr1 = c.x;
	yr1 = sHeight-c.y;
	xr2 = xn;
	yr2 = sHeight-1-yn;

	dcSetup.MoveTo(xr1,yr1);
	dcSetup.LineTo(xr2,yr2); 

	xn = (int)(c.x-ln*sin(theta_c-150));
	if(xn<0) xn=0;
	yn = (int)(c.y+ln*cos(theta_c-150));
	if(yn<0) yn=0;

	xr1 = c.x;
	yr1 = sHeight-c.y;
	xr2 = xn;
	yr2 = sHeight-1-yn;

	dcSetup.MoveTo(xr1,yr1);
	dcSetup.LineTo(xr2,yr2); 
}

//***************************************************************************************************
void CTestbedDlg::FindFace()
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
			color = m_pImage->GetPixelColor(m,n);

			t[0] = color.rgbRed;
			t[1] = color.rgbGreen;
			t[2] = color.rgbBlue;

			dip = 50;

			r[0]=222;
			r[1]=33;
			r[2]=101;  // my hat1

			A = GetCorrelation(t,r);

			if(A>0.90) {
				if(color.rgbRed>r[0]-dip && color.rgbRed<r[0]+dip) {
					if(color.rgbGreen>r[1]-dip && color.rgbGreen<r[1]+dip) {
						if(color.rgbBlue>r[2]-dip && color.rgbBlue<r[2]+dip) {
//							m_pImage->SetPixelColor(m,n,RGB(255,0,0));

							detect[m][n] = 1;
						}
					}
				}
			}

			dip = 20;

			r[0]=144;
			r[1]=17;
			r[2]=60;  // my hat2	
			
			A = GetCorrelation(t,r);

			if(A>0.80) {
				if(color.rgbRed>r[0]-dip && color.rgbRed<r[0]+dip) {
					if(color.rgbGreen>r[1]-dip && color.rgbGreen<r[1]+dip) {
						if(color.rgbBlue>r[2]-dip && color.rgbBlue<r[2]+dip) {
//							m_pImage->SetPixelColor(m,n,RGB(255,0,0));

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
				px = m;
				py = (iHeight-1)-n;
			}
		}
	} 
	if(max<1) {
		px = 0;
		py = 0;
	}

/*	ncolor.rgbRed=0, ncolor.rgbGreen=0, ncolor.rgbBlue=0;
	// show weight for debugging
	for(m=0;m<iWidth;m++) {
		for(n=0;n<iHeight;n++) {
			ncolor.rgbRed=(int)(weight[m][n]/max*255);
			m_pImage->SetPixelColor(m,n,ncolor);
		}
	}    */

/*	ncolor.rgbRed=0, ncolor.rgbGreen=255, ncolor.rgbBlue=0;
	// show weight for debugging
	for(m=0;m<iWidth;m++) {
		for(n=0;n<iHeight;n++) {
			if(weight[m][n]>5) {
				m_pImage->SetPixelColor(m,n,ncolor);
			}
		}
	}   */

	// save detected point
/*	FILE *fp;
	fp = fopen("max.txt","w");

	fprintf(fp,"%4.2lf\n%d/%d\n%d/%d\n",max,px,iWidth,py,iHeight);
	fclose(fp); */

	// save weight for debugging
/*	fp = fopen("weight.txt","w");

	for(m=0;m<iWidth;m++) {
		for(n=0;n<iHeight;n++) {
			fprintf(fp,"%4.2lf ",weight[m][n]);
		}
		fprintf(fp,"\n");
	}
	fclose(fp); */

	// save detect for debugging
/*	fp = fopen("detect.txt","w");

	for(m=0;m<iWidth;m++) {
		for(n=0;n<iHeight;n++) {
			fprintf(fp,"%2d ",detect[m][n]);
		}
		fprintf(fp,"\n");
	}
	fclose(fp);  */

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

/*	FILE *fp;
	fp = fopen("gauss.txt","w");
	for(i=0;i<Ny;i++) {
		for(j=0;j<Nx;j++) {		
			fprintf(fp,"%5.3lf ",gauss[i][j]);
		}
		fprintf(fp,"\n");
	}	*/
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

void CTestbedDlg::DrawObject()
{
	int rx1,ry1,rx2,ry2;

	if(!(px==0 && py==0)) {
		rx1 = px-pw/2;
		if(rx1<0) rx1=0;
		ry1 = py-ph/2;
		if(ry1<0) ry1=0;
		rx2 = px+pw/2;
		if(rx2>iWidth) rx2=iWidth;
		ry2 = py+ph/2;
		if(ry2>iHeight) ry2=iHeight;

		// Make box in image
		m_pImage->DrawLine(rx1,rx2,iHeight-1-ry1,iHeight-1-ry1,RGB(0,0,255));
		m_pImage->DrawLine(rx2,rx2,iHeight-1-ry1,iHeight-1-ry2,RGB(0,0,255));
		m_pImage->DrawLine(rx2,rx1,iHeight-1-ry2,iHeight-1-ry2,RGB(0,0,255));
		m_pImage->DrawLine(rx1,rx1,iHeight-1-ry2,iHeight-1-ry1,RGB(0,0,255));
	}
}

void CTestbedDlg::ShowBox()
{
	CClientDC dc(this);	
	int rx1,ry1,rx2,ry2;

	CRect rect;
	GetWindowRect(&rect);
	
	CBrush brush(RGB(0,0,255));
	CBrush* pOldBrush = dcMem1.SelectObject(&brush);

	CPen pen;
	pen.CreatePen(PS_SOLID,5,RGB(0,0,255));
	CPen* pOldPen = dcMem1.SelectObject(&pen);

	if(!(px==0 && py==0)) {
		rx1 = px-pw/2;
		if(rx1<0) rx1=0;
		ry1	= py-ph/2;
		if(ry1<0) ry1=0;
		rx2 = px+pw/2;
		if(rx2>iWidth) rx2=iWidth;
		ry2 = py+ph/2;
		if(ry2>iHeight) ry2=iHeight;

		dcMem1.MoveTo(rx1,ry1);
		dcMem1.LineTo(rx2,ry1);
		dcMem1.LineTo(rx2,ry2);
		dcMem1.LineTo(rx1,ry2);
		dcMem1.LineTo(rx1,ry1);
	}
}


//***********************************************************************************
void CTestbedDlg::AdjustCamera(int px,int py,CString strServerName,CString id,CString passwd)
{
	CString Order;
	int m_PanSpeed=1, m_TiltSpeed=1;

	int delta_w,delta_h;

	if(!(px==0 && py==0)) {
		delta_w = iWidth/2 - px;
		delta_h = iHeight/2 - py;

		if(abs(delta_w)>50) {
			if(abs(delta_w)<=150) m_PanSpeed = -5;
			else if(abs(delta_w)<=250) m_PanSpeed = -3;
			else if(abs(delta_w)<=350) m_PanSpeed = -1;

			Order.Format("/cgi-bin/camctrl.cgi?speedpan=%d",m_PanSpeed);
			ExecuteOrder(Order,strServerName,id,passwd);

			if(delta_w>0) {
				Order = "/cgi-bin/camctrl.cgi?move=left";
				ExecuteOrder(Order,strServerName,id,passwd);		
			}
			else if(delta_w<0) {
				Order = "/cgi-bin/camctrl.cgi?move=right";
				ExecuteOrder(Order,strServerName,id,passwd);		
			}
		}

		if(abs(delta_h)>100) {
			if(delta_h<=150) m_TiltSpeed = 2;
			else if(delta_h>250) m_TiltSpeed = 5;

			Order.Format("/cgi-bin/camctrl.cgi?speedtilt=%d",m_PanSpeed);
			ExecuteOrder(Order,strServerName,id,passwd);

			if(delta_h>0) {
				Order = "/cgi-bin/camctrl.cgi?move=up";
				ExecuteOrder(Order,strServerName,id,passwd);		
			}
			else if(delta_h<0) {
				Order = "/cgi-bin/camctrl.cgi?move=down";
				ExecuteOrder(Order,strServerName,id,passwd);		
			}
		}
	}
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

void CTestbedDlg::OnSnapshot() 
{
	COleDateTime	m_Date1;
	m_Date1 = COleDateTime::GetCurrentTime();
	CString strSaveFileName1;

	if(m_nSelectC1==0)  strSaveFileName1 = m_Date1.Format(_T("c1_%Y%D%I%M%S.jpg"));
	else   strSaveFileName1 = m_Date1.Format(_T("c2_%Y%D%I%M%S.jpg"));

	m_pImage->Load(strImageFileName1, CxImage::FindType(strImageFileName1));
	m_pImage->Save(strSaveFileName1, CxImage::FindType(strSaveFileName1));	
}

void CTestbedDlg::OnSavec1stop() 
{
	m_Savec1 = 0;
}

void CTestbedDlg::OnSavec2start() 
{
	m_Savec1 = 1;
}

void CTestbedDlg::OnIsolationc1stop() 
{
	m_nIsolation = 0;
}

void CTestbedDlg::OnIsolationc2start() 
{
	m_nIsolation = 1;
}

void CTestbedDlg::OnTracec1stop() 
{
	m_nTrace = 0;
}

void CTestbedDlg::OnIsolationc1start() 
{
	if(m_nIsolation==1)	m_nTrace = 1;
	else	m_nTrace = 0;
}

void CTestbedDlg::OnMoveupc1() 
{
	CString Order;
	
	Order = "/cgi-bin/camctrl.cgi?move=up";
	ExecuteOrder(Order,strServerName1,id1,passwd1);

	// Update Image From Cameras
	UpdateImageFromCamera(strServerName1,id1,passwd1);
	UpdateSetup();
	UpdateTestBed();
}

void CTestbedDlg::OnMovedownc1() 
{
	CString Order;
	
	Order = "/cgi-bin/camctrl.cgi?move=down";
	ExecuteOrder(Order,strServerName1,id1,passwd1);

	// Update Image From Cameras
	UpdateImageFromCamera(strServerName1,id1,passwd1);
	UpdateSetup();
	UpdateTestBed();
}

void CTestbedDlg::OnMoveleftc1() 
{
	// Update Camera Angle
	double dep=0;
/*	if(c1.zoom_level<=3) dep = angle_z1to3[m_nPanSpeedC1+5];
	else if(c1.zoom_level>3 && c1.zoom_level<=7) dep = angle_z4to7[m_nPanSpeedC1+5];
	else if(c1.zoom_level>7) dep = angle_z8to10[m_nPanSpeedC1+5];	*/
	dep = c1_angle_z[m_nPanSpeedC1+5];

	c1.theta_p -= dep*pi/180.;

	CString Order;
	
	Order = "/cgi-bin/camctrl.cgi?move=right";
	ExecuteOrder(Order,strServerName1,id1,passwd1);

	// Update Image From Cameras
	UpdateImageFromCamera(strServerName1,id1,passwd1);
	UpdateSetup();
	UpdateTestBed();	
}

void CTestbedDlg::OnMoverightc1() 
{
	// Update Camera Angle
	double dep=0;
/*	if(c1.zoom_level<=3) dep = angle_z1to3[m_nPanSpeedC1+5];
	else if(c1.zoom_level>3 && c1.zoom_level<=7) dep = angle_z4to7[m_nPanSpeedC1+5];
	else if(c1.zoom_level>7) dep = angle_z8to10[m_nPanSpeedC1+5];	*/
	dep = c1_angle_z[m_nPanSpeedC1+5];

	c1.theta_p += dep*pi/180.;

	CString Order;
	
	Order = "/cgi-bin/camctrl.cgi?move=left";
	ExecuteOrder(Order,strServerName1,id1,passwd1);

	// Update Image From Cameras
	UpdateImageFromCamera(strServerName1,id1,passwd1);
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
	UpdateImageFromCamera(strServerName1,id1,passwd1);
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
	UpdateImageFromCamera(strServerName1,id1,passwd1);
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
	UpdateImageFromCamera(strServerName1,id1,passwd1);
	UpdateSetup();
	UpdateTestBed();	
}

void CTestbedDlg::OnFocusinc1() 
{
	CString Order;
	
	Order = "/cgi-bin/camctrl.cgi?focus=far";
	ExecuteOrder(Order,strServerName1,id1,passwd1);

	// Update Image From Cameras
	UpdateImageFromCamera(strServerName1,id1,passwd1);
	UpdateSetup();
	UpdateTestBed();
}

void CTestbedDlg::OnFocusoutc1() 
{
	CString Order;
	
	Order = "/cgi-bin/camctrl.cgi?focus=stop";
	ExecuteOrder(Order,strServerName1,id1,passwd1);

	// Update Image From Cameras
	UpdateImageFromCamera(strServerName1,id1,passwd1);
	UpdateSetup();
	UpdateTestBed();	
}

void CTestbedDlg::OnFocusautoc1() 
{
	CString Order;
	
	Order = "/cgi-bin/camctrl.cgi?focus=auto";
	ExecuteOrder(Order,strServerName1,id1,passwd1);

	// Update Image From Cameras
	UpdateImageFromCamera(strServerName1,id1,passwd1);
	UpdateSetup();
	UpdateTestBed();	
}

void CTestbedDlg::OnIrisinc1() 
{
	CString Order;
	
	Order = "/cgi-bin/camctrl.cgi?iris=open";
	ExecuteOrder(Order,strServerName1,id1,passwd1);

	// Update Image From Cameras
	UpdateImageFromCamera(strServerName1,id1,passwd1);
	UpdateSetup();
	UpdateTestBed();	
}

void CTestbedDlg::OnIrisoutc1() 
{
	CString Order;
	
	Order = "/cgi-bin/camctrl.cgi?iris=stop";
	ExecuteOrder(Order,strServerName1,id1,passwd1);

	// Update Image From Cameras
	UpdateImageFromCamera(strServerName1,id1,passwd1);
	UpdateSetup();
	UpdateTestBed();	
}

void CTestbedDlg::OnIrisautoc1() 
{
	CString Order;
	
	Order = "/cgi-bin/camctrl.cgi?iris=auto";
	ExecuteOrder(Order,strServerName1,id1,passwd1);

	// Update Image From Cameras
	UpdateImageFromCamera(strServerName1,id1,passwd1);
	UpdateSetup();
	UpdateTestBed();	
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

void CTestbedDlg::OnChangePanspeedc1() 
{
	UpdateData(TRUE);

	CString strPanSpeedC1;
	m_ctrlPanSpeedC1.GetLBText(m_nPanSpeedC1,strPanSpeedC1);
	
	CString Order;	
	Order.Format("/cgi-bin/camctrl.cgi?speedpan=%d",m_nPanSpeedC1-5);
	ExecuteOrder(Order,strServerName1,id1,passwd1);
	
	UpdateData(FALSE);	
}

void CTestbedDlg::OnChangeTiltspeedc1() 
{
	UpdateData(TRUE);

	CString strTiltSpeedC1;
	m_ctrlTiltSpeedC1.GetLBText(m_nTiltSpeedC1,strTiltSpeedC1);

	CString Order;	
	Order.Format("/cgi-bin/camctrl.cgi?speedtilt=%d",m_nTiltSpeedC1-5);
	ExecuteOrder(Order,strServerName1,id1,passwd1);
	
	UpdateData(FALSE);	
}

void CTestbedDlg::OnChangeZoomspeedc1() 
{
	UpdateData(TRUE);

	CString strZoomSpeedC1;
	m_ctrlZoomSpeedC1.GetLBText(m_nZoomSpeedC1,strZoomSpeedC1);

	CString Order;	
	Order.Format("/cgi-bin/camctrl.cgi?speedzoom=%d",m_nZoomSpeedC1-5);
	ExecuteOrder(Order,strServerName1,id1,passwd1);
	
	UpdateData(FALSE);		
}

void CTestbedDlg::OnChangeFocusspeedc1() 
{
	UpdateData(TRUE);

	CString strFocusSpeedC1;
	m_ctrlFocusSpeedC1.GetLBText(m_nFocusSpeedC1,strFocusSpeedC1);

	CString Order;	
	Order.Format("/cgi-bin/camctrl.cgi?speedapp=%d",m_nFocusSpeedC1-5);
	ExecuteOrder(Order,strServerName1,id1,passwd1);
	
	UpdateData(FALSE);		
}

//**********************************************************************************
void CTestbedDlg::OnSelectcamera1() 
{
	m_nSelectC1 = 0;
	strImageFileName1 = "video1.jpg";
	strServerName1 = "129.49.69.81";  // Camera 2	

	// Load Image Data from camera;
	UpdateImageFromCamera(strServerName1,id1,passwd1);

	// Update Setup
	UpdateSetup();

	// Update Testbed
	UpdateTestBed();
}

void CTestbedDlg::OnSelectcamera2() 
{
	m_nSelectC1 = 1;
	strImageFileName1 = "video2.jpg";
	strServerName1 = "129.49.69.89";  // Camera 2

	// Load Image Data from camera;
	UpdateImageFromCamera(strServerName1,id1,passwd1);

	// Update Setup
	UpdateSetup();

	// Update Testbed
	UpdateTestBed();	
}

void CTestbedDlg::OnObjectCoordinate() 
{
	UpdateData(TRUE);

	if(!(px==0 && py==0)) m_strObjectCoordinate.Format("(%3d, %2d)",px,py);
	else	m_strObjectCoordinate.Format("Nothing");

	UpdateData(FALSE);
}

void CTestbedDlg::OnCalibration() 
{
	char szFilter[] = "Image (*.bmp,*.jpg)|*.bmp;*.jpg;|All Files(*.*)|*.*||";

	CFileDialog fileDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, szFilter);
	if(IDOK == fileDlg.DoModal())
	{
		CString strImageFileName = fileDlg.GetPathName();

		m_pImage->Save(strImageFileName, CxImage::FindType(strImageFileName));
	}
	else exit(1);	
}
