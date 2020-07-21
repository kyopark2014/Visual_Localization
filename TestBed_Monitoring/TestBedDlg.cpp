// TestBedDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestBed.h"
#include "TestBedDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestBedDlg dialog

CTestBedDlg::CTestBedDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestBedDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestBedDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_pImage = NULL;
}

void CTestBedDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestBedDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX,IDC_PANSPEEDC1,m_ctrlPanSpeedC1);
	DDX_Control(pDX,IDC_TILTSPEEDC1,m_ctrlTiltSpeedC1);
	DDX_Control(pDX,IDC_ZOOMSPEEDC1,m_ctrlZoomSpeedC1);
	DDX_Control(pDX,IDC_FOCUSSPEEDC1,m_ctrlFocusSpeedC1);
	DDX_CBIndex(pDX,IDC_PANSPEEDC1,m_PanSpeedC1);
	DDX_CBIndex(pDX,IDC_TILTSPEEDC1,m_TiltSpeedC1);
	DDX_CBIndex(pDX,IDC_ZOOMSPEEDC1,m_ZoomSpeedC1);
	DDX_CBIndex(pDX,IDC_FOCUSSPEEDC1,m_FocusSpeedC1);
	
	DDX_Control(pDX,IDC_PANSPEEDC2,m_ctrlPanSpeedC2);
	DDX_Control(pDX,IDC_TILTSPEEDC2,m_ctrlTiltSpeedC2);
	DDX_Control(pDX,IDC_ZOOMSPEEDC2,m_ctrlZoomSpeedC2);
	DDX_Control(pDX,IDC_FOCUSSPEEDC2,m_ctrlFocusSpeedC2);
	DDX_CBIndex(pDX,IDC_PANSPEEDC2,m_PanSpeedC2);
	DDX_CBIndex(pDX,IDC_TILTSPEEDC2,m_TiltSpeedC2);
	DDX_CBIndex(pDX,IDC_ZOOMSPEEDC2,m_ZoomSpeedC2);
	DDX_CBIndex(pDX,IDC_FOCUSSPEEDC2,m_FocusSpeedC2);

	DDX_Control(pDX,IDC_SAVEINTERVAL,m_ctrlSaveInterval);
	DDX_CBIndex(pDX,IDC_SAVEINTERVAL,m_SaveInterval);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTestBedDlg, CDialog)
	//{{AFX_MSG_MAP(CTestBedDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_MOVEUPC1, OnMoveupC1)
	ON_BN_CLICKED(IDC_MOVEHOMEC1, OnMovehomeC1)
	ON_BN_CLICKED(IDC_MOVERIGHTC1, OnMoverightC1)
	ON_BN_CLICKED(IDC_MOVELEFTC1, OnMoveleftC1)
	ON_BN_CLICKED(IDC_MOVEDOWNC1, OnMovedownC1)
	ON_BN_CLICKED(IDC_MOVEUPC2, OnMoveupC2)
	ON_BN_CLICKED(IDC_MOVEHOMEC2, OnMovehomeC2)
	ON_BN_CLICKED(IDC_MOVERIGHTC2, OnMoverightC2)
	ON_BN_CLICKED(IDC_MOVELEFTC2, OnMoveleftC2)
	ON_BN_CLICKED(IDC_MOVEDOWNC2, OnMovedownC2)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_ZOOMOUTC1, OnZoomoutc1)
	ON_BN_CLICKED(IDC_ZOOMINC1, OnZoominc1)
	ON_BN_CLICKED(IDC_ZOOMOUTC2, OnZoomoutc2)
	ON_BN_CLICKED(IDC_ZOOMINC2, OnZoominc2)
	ON_BN_CLICKED(IDC_FOCUSOUTC1, OnFocusoutc1)
	ON_BN_CLICKED(IDC_FOCUSINC1, OnFocusinc1)
	ON_BN_CLICKED(IDC_FOCUSAUTOC1, OnFocusautoc1)
	ON_BN_CLICKED(IDC_FOCUSOUTC2, OnFocusoutc2)
	ON_BN_CLICKED(IDC_FOCUSAUTOC2, OnFocusautoc2)
	ON_BN_CLICKED(IDC_FOCUSINC2, OnFocusinc2)
	ON_BN_CLICKED(IDC_IRISOUTC1, OnIrisoutc1)
	ON_BN_CLICKED(IDC_IRISINC1, OnIrisinc1)
	ON_BN_CLICKED(IDC_IRISAUTOC1, OnIrisautoc1)
	ON_BN_CLICKED(IDC_IRISOUTC2, OnIrisoutc2)
	ON_BN_CLICKED(IDC_IRISINC2, OnIrisinc2)
	ON_BN_CLICKED(IDC_IRISAUTOC2, OnIrisautoc2)
	ON_BN_CLICKED(IDC_SAVEC1, OnSavec1)	
	ON_BN_CLICKED(IDC_SAVEC2, OnSavec2)
	ON_BN_CLICKED(IDC_SAVEBOTH, OnSaveboth)
	ON_BN_CLICKED(IDC_SNAPSHOT, OnSnapshot)
	ON_CBN_SELCHANGE(IDC_PANSPEEDC1, OnPanspeedc1)
	ON_CBN_SELCHANGE(IDC_TILTSPEEDC1, OnTiltspeedc1)
	ON_CBN_SELCHANGE(IDC_ZOOMSPEEDC1, OnZoomspeedc1)
	ON_CBN_SELCHANGE(IDC_FOCUSSPEEDC1, OnFocusspeedc1) 
	ON_CBN_SELCHANGE(IDC_PANSPEEDC2, OnPanspeedc2)
	ON_CBN_SELCHANGE(IDC_TILTSPEEDC2, OnTiltspeedc2)
	ON_CBN_SELCHANGE(IDC_ZOOMSPEEDC2, OnZoomspeedc2)
	ON_CBN_SELCHANGE(IDC_FOCUSSPEEDC2, OnFocusspeedc2) 
	ON_CBN_SELCHANGE(IDC_SAVEINTERVAL, OnSaveInterval) 
	ON_WM_KEYDOWN()
	ON_BN_CLICKED(IDC_SAVEC3, OnSaveStop)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestBedDlg message handlers

static CString range[] = {"-5", "-4", "-3", "-2", "-1", "0", "1", "2", "3", "4", "5"};
static CString time_range[] = {"0.1", "0.2", "0.5", "1", "2", "5", "10", "60"};

static double angle_z1to3[] = {0.32, 0.65, 1.29, 3.88, 7.75, 11.63, 15.50, 19.38, 23,26, 25.84, 28.42};
static double angle_z4to7[] = {0.32, 0.32, 0.65, 1.94, 3.88,  5.81,  7.75,  9.69, 11.63, 12.92, 14.21};
static double angle_z8to10[]= {0.32, 0.32, 0.32, 0.97, 1.94,  2.91,  3.88,  4.85,  5.81,  6.46,  7.11};

BOOL CTestBedDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
//	m_bmpBack.LoadBitmap(IDB_BACK);
	TimeDepth = 100;  // 0.1s
	SetTimer(0,TimeDepth,NULL);  

	m_pImage = new CxImage;
	int i;
	
	Width = 704+60+6, Height = 480/2+300+170;
//	Width = 1024, Height = 768;

	// Adjust testbed size
	SetWindowPos(NULL,0,0,Width,Height+30,SWP_NOMOVE|SWP_SHOWWINDOW);

	// Load Image From Cameras
	UpdateImageFromCameras();

	//	W = m_pImage->GetWidth();
	//	H = m_pImage->GetHeight();

	// Draw the background 
	iWidth = 704; iHeight = 480;
	sWidth = 300; sHeight = 300; 
	px_c1 = 20; py_c1 = 20;
	px_c2 = iWidth/2+20*2; 	py_c2 = 20;
	px_s = Width/2-sWidth/2; py_s = iHeight/2+140;
	cntc1 = 0, cntc2 = 0;

	// Setup Camera Parameters
	c1.x = 100;
	c1.y = sHeight-1;
	c1.type = 3;
	c1.theta_p = 0;
	c1.zoom_level = 1;
	c1.length = 50;

	// Setup Camera Parameters
	c2.x = sWidth-1;
	c2.y = sHeight-1-50;
	c2.type = 2;
	c2.theta_p = 0;
	c2.zoom_level = 1;
	c2.length = 50;

	for(i=0;i<11;i++) {
		m_ctrlPanSpeedC1.AddString(range[i]);
		m_ctrlTiltSpeedC1.AddString(range[i]);
		m_ctrlZoomSpeedC1.AddString(range[i]);
		m_ctrlFocusSpeedC1.AddString(range[i]);
		m_ctrlPanSpeedC2.AddString(range[i]);
		m_ctrlTiltSpeedC2.AddString(range[i]);
		m_ctrlZoomSpeedC2.AddString(range[i]);
		m_ctrlFocusSpeedC2.AddString(range[i]); 
	}

	for(i=0;i<8;i++) 
		m_ctrlSaveInterval.AddString(time_range[i]);

	// Initialize
	color_R=156,color_G=186,color_B=206;
	c1Save = false, c2Save = false;

	CClientDC dc(this);	
	dcSetup.CreateCompatibleDC(&dc);
	dcMem1.CreateCompatibleDC(&dc);
	dcMem2.CreateCompatibleDC(&dc);

	// Load Bacground Image
	dcBuffer.CreateCompatibleDC(&dc);
//	dcBuffer.SelectObject(&m_bmpBack);
//	dcBuffer.SetBkColor(RGB(color_R,color_G,color_B));
//	dcBuffer.SetTextColor(RGB(255,255,255));
	dcBuffer.DrawText("CAMERA 1",&CRect(px_c1,0,px_c1+iWidth/2,py_c1),DT_CENTER|DT_VCENTER|DT_SINGLELINE);
	dcBuffer.DrawText("CAMERA 2",&CRect(px_c2,0,px_c2+iWidth/2,py_c2),DT_CENTER|DT_VCENTER|DT_SINGLELINE);

	// Set the parameters
	m_PanSpeedC1=1,m_TiltSpeedC1=1,m_ZoomSpeedC1=1,m_FocusSpeedC1=1;
	m_PanSpeedC2=1,m_TiltSpeedC2=1,m_ZoomSpeedC2=1,m_FocusSpeedC2=1;

	CString Order;	

	Order = "/cgi-bin/camctrl.cgi?move=home";
	ExecuteOrder(Order,strServerName1,id1,passwd1);
	ExecuteOrder(Order,strServerName2,id2,passwd2);
	
	Order.Format("/cgi-bin/camctrl.cgi?speedpan=%d",m_PanSpeedC1);
	ExecuteOrder(Order,strServerName1,id1,passwd1);
	Order.Format("/cgi-bin/camctrl.cgi?speedtilt=%d",m_TiltSpeedC1);
	ExecuteOrder(Order,strServerName1,id1,passwd1);
	Order.Format("/cgi-bin/camctrl.cgi?speedzoom=%d",m_ZoomSpeedC1);
	ExecuteOrder(Order,strServerName1,id1,passwd1);
	Order.Format("/cgi-bin/camctrl.cgi?speedapp=%d",m_FocusSpeedC1);
	ExecuteOrder(Order,strServerName1,id1,passwd1);

	Order.Format("/cgi-bin/camctrl.cgi?speedpan=%d",m_PanSpeedC2);
	ExecuteOrder(Order,strServerName2,id2,passwd2);
	Order.Format("/cgi-bin/camctrl.cgi?speedtilt=%d",m_TiltSpeedC2);
	ExecuteOrder(Order,strServerName2,id2,passwd2);
	Order.Format("/cgi-bin/camctrl.cgi?speedzoom=%d",m_ZoomSpeedC2);
	ExecuteOrder(Order,strServerName2,id2,passwd2);
	Order.Format("/cgi-bin/camctrl.cgi?speedapp=%d",m_FocusSpeedC2);
	ExecuteOrder(Order,strServerName2,id2,passwd2);

	// Show background testbed
	UpdateSetup();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTestBedDlg::OnPaint() 
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
		CClientDC dc(this);	
		// Update Bacground
		dc.BitBlt(0,0,1024,768,&dcBuffer,0,0,SRCCOPY);
		// Update Testbed
		UpdateTestBed();

		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTestBedDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTestBedDlg::ShowCameraImages(CString ImageFile1,CString ImageFile2)
{
	// Initialize Camera Image DC
	CClientDC dc(this);	

	CBitmap bitmap1,bitmap2;
	bitmap1.CreateCompatibleBitmap(&dc,iWidth,iHeight);
	bitmap2.CreateCompatibleBitmap(&dc,iWidth,iHeight);

	pOldBitmap1 = dcMem1.SelectObject(&bitmap1);
	pOldBitmap2 = dcMem2.SelectObject(&bitmap2);

	// Load Camera Images
	m_pImage->Load(ImageFile1, CxImage::FindType(ImageFile1));
	m_pImage->Draw(dcMem1,CRect(0,0,iWidth/2,iHeight/2));

	m_pImage->Load(ImageFile2, CxImage::FindType(ImageFile2));
	m_pImage->Draw(dcMem2,CRect(0,0,iWidth/2,iHeight/2));
}

BOOL CTestBedDlg::DestroyWindow() 
{
	KillTimer(0);

	dcSetup.SelectObject(&pOldPen);
	dcSetup.SelectObject(&pOldBrush);
	dcMem1.SelectObject(&pOldBitmap1);
	dcMem2.SelectObject(&pOldBitmap2);

	ReleaseDC(&dcMem1);	
	ReleaseDC(&dcMem2);	
	ReleaseDC(&dcSetup);	
	
	delete m_pImage;

	return CDialog::DestroyWindow();
}

void CTestBedDlg::LoadImageFromCameras(CString strServerName,CString strFile,CString id,CString passwd)
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

void CTestBedDlg::UpdateSetup()
{
	// Initialize Background Testbed
	CClientDC dc(this);	

	CBitmap bitmap;
	bitmap.CreateCompatibleBitmap(&dc,sWidth,sHeight);
	pOldBitmap = dcSetup.SelectObject(&bitmap);
	
	CPen pen;
	pen.CreatePen(PS_SOLID,5,RGB(color_R,color_G,color_B));
	pOldPen = dcSetup.SelectObject(&pen);

	CBrush brush(RGB(color_R,color_G,color_B));
	pOldBrush = dcSetup.SelectObject(&brush);
	dcSetup.Rectangle(0,0,sWidth,sHeight);

	// Load Camera Images
	ShowCameraImages(ImageFile1,ImageFile2);

	DrawCameraSetup(c1);
	DrawCameraSetup(c2);
}

void CTestBedDlg::DrawCameraSetup(param_camera c)
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

	xp1 = (int)(c.x-c.length/2.*cos(theta_c));
	yp1 = (int)(c.y-c.length/2.*sin(theta_c));
	xp2 = (int)(c.x+c.length/2.*cos(theta_c));
	yp2 = (int)(c.y+c.length/2.*sin(theta_c));

	int xr1,yr1,xr2,yr2;

	xr1 = xp1;
	yr1 = sHeight-1-yp1;
	xr2 = xp2;
	yr2 = sHeight-1-yp2;

	dcSetup.SelectStockObject(BLACK_PEN);
	dcSetup.MoveTo(xr1,yr1);
	dcSetup.LineTo(xr2,yr2); 
	CPen pen2;
	pen2.CreatePen(PS_SOLID,2,RGB(50,130,148));
	dcSetup.SelectObject(&pen2);

	int xn,yn,ln=sWidth/3;
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
}

void CTestBedDlg::UpdateTestBed()
{
	CClientDC dc(this);	

	// Show Camera Images
	dc.BitBlt(px_c1,py_c1,iWidth/2,iHeight/2,&dcMem1,0,0,SRCCOPY); // camera 1
	dc.BitBlt(px_c2,py_c2,iWidth/2,iHeight/2,&dcMem2,0,0,SRCCOPY); // camera 2
	dc.BitBlt(px_s,py_s,sWidth,sHeight,&dcSetup,0,0,SRCCOPY); // setup

//	dc.StretchBlt(px_c1,py_c1,iWidth/2,iHeight/2,&dcMem1,0,0,iWidth/2,iHeight/2,SRCCOPY);
//	dc.StretchBlt(px_c2,py_c2,iWidth/2,iHeight/2,&dcMem2,0,0,iWidth/2,iHeight/2,SRCCOPY);
}


void CTestBedDlg::UpdateImageFromCameras()
{
	// Load Image From Cameras
	strServerName1 = "129.49.69.81";  // Camera 1
	ImageFile1 = "video1.jpg";
	id1 = "root";
	passwd1 = "msdl007";
	LoadImageFromCameras(strServerName1,ImageFile1,id1,passwd1);

	strServerName2 = "129.49.69.89";  // Camera 2
	ImageFile2 = "video2.jpg";
	id2 = "root";
	passwd2 = "msdl007";
	LoadImageFromCameras(strServerName2,ImageFile2,id2,passwd2);
}

void CTestBedDlg::ExecuteOrder(CString Order,CString strServerName,CString id,CString passwd)
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

void CTestBedDlg::OnMoveupC1() 
{
	CString Order;
	
	Order = "/cgi-bin/camctrl.cgi?move=up";
	ExecuteOrder(Order,strServerName1,id1,passwd1);

	// Update Image From Cameras
	UpdateImageFromCameras();
	UpdateSetup();
	UpdateTestBed();
}

void CTestBedDlg::OnMovedownC1() 
{
	CString Order;
	
	Order = "/cgi-bin/camctrl.cgi?move=down";
	ExecuteOrder(Order,strServerName1,id1,passwd1);

	// Update Image From Cameras
	UpdateImageFromCameras();
	UpdateSetup();
	UpdateTestBed();
}

void CTestBedDlg::OnMoveleftC1() 
{
	// Update Camera Angle
	double dep=0;
	if(c1.zoom_level<=3) dep = angle_z1to3[m_PanSpeedC1+5];
	else if(c1.zoom_level>3 && c1.zoom_level<=7) dep = angle_z4to7[m_PanSpeedC1+5];
	else if(c1.zoom_level>7) dep = angle_z8to10[m_PanSpeedC1+5];	
	c1.theta_p += dep*pi/180.;

	CString Order;
	
	Order = "/cgi-bin/camctrl.cgi?move=left";
	ExecuteOrder(Order,strServerName1,id1,passwd1);

	// Update Image From Cameras
	UpdateImageFromCameras();
	UpdateSetup();
	UpdateTestBed();
}

void CTestBedDlg::OnMoverightC1() 
{
	// Update Camera Angle
	double dep=0;
	if(c1.zoom_level<=3) dep = angle_z1to3[m_PanSpeedC1+5];
	else if(c1.zoom_level>3 && c1.zoom_level<=7) dep = angle_z4to7[m_PanSpeedC1+5];
	else if(c1.zoom_level>7) dep = angle_z8to10[m_PanSpeedC1+5];	
	c1.theta_p -= dep*pi/180.;

	CString Order;
	
	Order = "/cgi-bin/camctrl.cgi?move=right";
	ExecuteOrder(Order,strServerName1,id1,passwd1);

	// Update Image From Cameras
	UpdateImageFromCameras();
	UpdateSetup();
	UpdateTestBed();
}

void CTestBedDlg::OnMovehomeC1() 
{
	// Upate Camera Angle
	c1.theta_p = 0;
	c1.zoom_level = 1;

	CString Order;
	
	Order = "/cgi-bin/camctrl.cgi?move=home";
	ExecuteOrder(Order,strServerName1,id1,passwd1);

	// Update Image From Cameras
	UpdateImageFromCameras();
	UpdateSetup();
	UpdateTestBed();
}

void CTestBedDlg::OnMoveleftC2() 
{
	// Update Camera Angle
	double dep=0;
	if(c1.zoom_level<=3) dep = angle_z1to3[m_PanSpeedC1+5];
	else if(c1.zoom_level>3 && c1.zoom_level<=7) dep = angle_z4to7[m_PanSpeedC1+5];
	else if(c1.zoom_level>7) dep = angle_z8to10[m_PanSpeedC1+5];	
	c2.theta_p += dep*pi/180.;

	CString Order;
	
	Order = "/cgi-bin/camctrl.cgi?move=left";
	ExecuteOrder(Order,strServerName2,id2,passwd2);

	// Update Image From Cameras
	UpdateImageFromCameras();
	UpdateSetup();
	UpdateTestBed();
}

void CTestBedDlg::OnMoverightC2() 
{
	// Update Camera Angle
	double dep=0;
	if(c1.zoom_level<=3) dep = angle_z1to3[m_PanSpeedC1+5];
	else if(c1.zoom_level>3 && c1.zoom_level<=7) dep = angle_z4to7[m_PanSpeedC1+5];
	else if(c1.zoom_level>7) dep = angle_z8to10[m_PanSpeedC1+5];	
	c2.theta_p -= dep*pi/180.;

	CString Order;
	
	Order = "/cgi-bin/camctrl.cgi?move=right";
	ExecuteOrder(Order,strServerName2,id2,passwd2);

	// Update Image From Cameras
	UpdateImageFromCameras();
	UpdateSetup();
	UpdateTestBed();
}

void CTestBedDlg::OnMoveupC2() 
{
	CString Order;
	
	Order = "/cgi-bin/camctrl.cgi?move=up";
	ExecuteOrder(Order,strServerName2,id2,passwd2);

	// Update Image From Cameras
	UpdateImageFromCameras();
	UpdateSetup();
	UpdateTestBed();
}

void CTestBedDlg::OnMovedownC2() 
{
	// Update Camera Angle
	c1.theta_p = 0;

	CString Order;
	
	Order = "/cgi-bin/camctrl.cgi?move=down";
	ExecuteOrder(Order,strServerName2,id2,passwd2);

	// Update Image From Cameras
	UpdateImageFromCameras();
	UpdateSetup();
	UpdateTestBed();
}

void CTestBedDlg::OnMovehomeC2() 
{
	// Upate Camera Angle
	c2.theta_p = 0;
	c2.zoom_level = 1;

	CString Order;
	
	Order = "/cgi-bin/camctrl.cgi?move=home";
	ExecuteOrder(Order,strServerName2,id2,passwd2);

	// Update Image From Cameras
	UpdateImageFromCameras();
	UpdateSetup();
	UpdateTestBed();
}

void CTestBedDlg::OnTimer(UINT nIDEvent) 
{
	if(nIDEvent==0) {
		// Update Image From Cameras
		UpdateImageFromCameras();
		// Load Camera Images
		ShowCameraImages(ImageFile1,ImageFile2);
//		UpdateSetup();
//		UpdateTestBed();
		CClientDC dc(this);	
		dc.BitBlt(px_c1,py_c1,iWidth/2,iHeight/2,&dcMem1,0,0,SRCCOPY); // camera 1
		dc.BitBlt(px_c2,py_c2,iWidth/2,iHeight/2,&dcMem2,0,0,SRCCOPY); // camera 2

		if(c1Save==true) {
			if(cntc1<1000) {
				char fnamec1[50];
				sprintf(fnamec1,"c1_t%03d.jpg",++cntc1);
				CString SaveFileName1 = fnamec1;	
				m_pImage->Load(ImageFile1, CxImage::FindType(ImageFile1));
				m_pImage->Save(SaveFileName1, CxImage::FindType(SaveFileName1));
			}
		}
		if(c2Save==true) {
			if(cntc2<1000) {
				char fnamec2[50];
				sprintf(fnamec2,"c2_t%03d.jpg",++cntc2);
				CString SaveFileName2 = fnamec2;	
				m_pImage->Load(ImageFile2, CxImage::FindType(ImageFile2));
				m_pImage->Save(SaveFileName2, CxImage::FindType(SaveFileName2));
			}
		}
	}
	CDialog::OnTimer(nIDEvent);
}

void CTestBedDlg::OnZoomoutc1() 
{
	// Update zoom level
	c1.zoom_level--;
	if(c1.zoom_level<1) c1.zoom_level = 1;

	CString Order;
	
	Order = "/cgi-bin/camctrl.cgi?zoom=wide";
	ExecuteOrder(Order,strServerName1,id1,passwd1);

	// Update Image From Cameras
	UpdateImageFromCameras();
	UpdateSetup();
	UpdateTestBed();	
}

void CTestBedDlg::OnZoominc1() 
{
	// Update zoom level
	c1.zoom_level++;
	if(c1.zoom_level>10) c1.zoom_level = 10;

	CString Order;
	
	Order = "/cgi-bin/camctrl.cgi?zoom=tele";
	ExecuteOrder(Order,strServerName1,id1,passwd1);

	// Update Image From Cameras
	UpdateImageFromCameras();
	UpdateSetup();
	UpdateTestBed();	
}

void CTestBedDlg::OnZoomoutc2() 
{
	// Update zoom level
	c2.zoom_level--;
	if(c2.zoom_level<1) c2.zoom_level = 1;

	CString Order;
	
	Order = "/cgi-bin/camctrl.cgi?zoom=wide";
	ExecuteOrder(Order,strServerName2,id2,passwd2);

	// Update Image From Cameras
	UpdateImageFromCameras();
	UpdateSetup();
	UpdateTestBed();	
}

void CTestBedDlg::OnZoominc2() 
{
	// Update zoom level
	c2.zoom_level++;
	if(c2.zoom_level>10) c2.zoom_level = 10;

	CString Order;
	
	Order = "/cgi-bin/camctrl.cgi?zoom=tele";
	ExecuteOrder(Order,strServerName2,id2,passwd2);

	// Update Image From Cameras
	UpdateImageFromCameras();
	UpdateSetup();
	UpdateTestBed();	
}

void CTestBedDlg::OnFocusoutc1() 
{
	CString Order;
	
	Order = "/cgi-bin/camctrl.cgi?focus=stop";
	ExecuteOrder(Order,strServerName1,id1,passwd1);

	// Update Image From Cameras
	UpdateImageFromCameras();
	UpdateSetup();
	UpdateTestBed();	
}

void CTestBedDlg::OnFocusinc1() 
{
	CString Order;
	
	Order = "/cgi-bin/camctrl.cgi?focus=far";
	ExecuteOrder(Order,strServerName1,id1,passwd1);

	// Update Image From Cameras
	UpdateImageFromCameras();
	UpdateSetup();
	UpdateTestBed();
}

void CTestBedDlg::OnFocusautoc1() 
{
	CString Order;
	
	Order = "/cgi-bin/camctrl.cgi?focus=auto";
	ExecuteOrder(Order,strServerName1,id1,passwd1);

	// Update Image From Cameras
	UpdateImageFromCameras();
	UpdateSetup();
	UpdateTestBed();	
}

void CTestBedDlg::OnFocusoutc2() 
{
	CString Order;
	
	Order = "/cgi-bin/camctrl.cgi?focus=stop";
	ExecuteOrder(Order,strServerName2,id2,passwd2);

	// Update Image From Cameras
	UpdateImageFromCameras();
	UpdateSetup();
	UpdateTestBed();
}

void CTestBedDlg::OnFocusinc2() 
{
	CString Order;
	
	Order = "/cgi-bin/camctrl.cgi?focus=far";
	ExecuteOrder(Order,strServerName2,id2,passwd2);

	// Update Image From Cameras
	UpdateImageFromCameras();
	UpdateSetup();
	UpdateTestBed();		
}

void CTestBedDlg::OnFocusautoc2() 
{
	CString Order;
	
	Order = "/cgi-bin/camctrl.cgi?focus=auto";
	ExecuteOrder(Order,strServerName2,id2,passwd2);

	// Update Image From Cameras
	UpdateImageFromCameras();
	UpdateSetup();
	UpdateTestBed();	
}

void CTestBedDlg::OnIrisoutc1() 
{
	CString Order;
	
	Order = "/cgi-bin/camctrl.cgi?iris=stop";
	ExecuteOrder(Order,strServerName1,id1,passwd1);

	// Update Image From Cameras
	UpdateImageFromCameras();
	UpdateSetup();
	UpdateTestBed();	
}

void CTestBedDlg::OnIrisinc1() 
{
	CString Order;
	
	Order = "/cgi-bin/camctrl.cgi?iris=open";
	ExecuteOrder(Order,strServerName1,id1,passwd1);

	// Update Image From Cameras
	UpdateImageFromCameras();
	UpdateSetup();
	UpdateTestBed();
}

void CTestBedDlg::OnIrisautoc1() 
{
	CString Order;
	
	Order = "/cgi-bin/camctrl.cgi?iris=auto";
	ExecuteOrder(Order,strServerName1,id1,passwd1);

	// Update Image From Cameras
	UpdateImageFromCameras();
	UpdateSetup();
	UpdateTestBed();
}

void CTestBedDlg::OnIrisoutc2() 
{
	CString Order;
	
	Order = "/cgi-bin/camctrl.cgi?iris=stop";
	ExecuteOrder(Order,strServerName2,id2,passwd2);

	// Update Image From Cameras
	UpdateImageFromCameras();
	UpdateSetup();
	UpdateTestBed();	
}

void CTestBedDlg::OnIrisinc2() 
{
	CString Order;
	
	Order = "/cgi-bin/camctrl.cgi?iris=open";
	ExecuteOrder(Order,strServerName2,id2,passwd2);

	// Update Image From Cameras
	UpdateImageFromCameras();
	UpdateSetup();
	UpdateTestBed();
}

void CTestBedDlg::OnIrisautoc2() 
{
	CString Order;
	
	Order = "/cgi-bin/camctrl.cgi?iris=auto";
	ExecuteOrder(Order,strServerName2,id2,passwd2);

	// Update Image From Cameras
	UpdateImageFromCameras();
	UpdateSetup();
	UpdateTestBed();
}

void CTestBedDlg::OnSavec1() 
{
	c1Save = !c1Save;
}

void CTestBedDlg::OnSavec2() 
{
	c2Save = !c2Save;	
}

void CTestBedDlg::OnSaveboth() 
{
	c1Save = !c1Save;
	c2Save = !c2Save;
}

void CTestBedDlg::OnSaveStop() 
{
	c1Save = false;
	c2Save = false;
}


void CTestBedDlg::OnSnapshot() 
{
	COleDateTime	m_Date1;
	m_Date1 = COleDateTime::GetCurrentTime();
	CString SaveFileName1 = m_Date1.Format(_T("c1_%Y%D%I%M%S.jpg"));
	m_pImage->Load(ImageFile1, CxImage::FindType(ImageFile1));
	m_pImage->Save(SaveFileName1, CxImage::FindType(SaveFileName1));
	
	COleDateTime	m_Date2;
	m_Date2 = COleDateTime::GetCurrentTime();
	CString SaveFileName2 = m_Date2.Format(_T("c2_%Y%D%I%M%S.jpg"));
	m_pImage->Load(ImageFile2, CxImage::FindType(ImageFile2));
	m_pImage->Save(SaveFileName2, CxImage::FindType(SaveFileName2));
}

void CTestBedDlg::OnPanspeedc1() 
{
	UpdateData(TRUE);

	CString strPanSpeedC1;
	m_ctrlPanSpeedC1.GetLBText(m_PanSpeedC1,strPanSpeedC1);

	CString Order;	
	Order.Format("/cgi-bin/camctrl.cgi?speedpan=%d",m_PanSpeedC1-5);
	ExecuteOrder(Order,strServerName1,id1,passwd1);
	
	UpdateData(FALSE);
}

void CTestBedDlg::OnTiltspeedc1() 
{
	UpdateData(TRUE);

	CString strTiltSpeedC1;
	m_ctrlTiltSpeedC1.GetLBText(m_TiltSpeedC1,strTiltSpeedC1);

	CString Order;	
	Order.Format("/cgi-bin/camctrl.cgi?speedtilt=%d",m_TiltSpeedC1-5);
	ExecuteOrder(Order,strServerName1,id1,passwd1);
	
	UpdateData(FALSE);	
}

void CTestBedDlg::OnZoomspeedc1() 
{
	UpdateData(TRUE);

	CString strZoomSpeedC1;
	m_ctrlZoomSpeedC1.GetLBText(m_ZoomSpeedC1,strZoomSpeedC1);

	CString Order;	
	Order.Format("/cgi-bin/camctrl.cgi?speedzoom=%d",m_ZoomSpeedC1-5);
	ExecuteOrder(Order,strServerName1,id1,passwd1);
	
	UpdateData(FALSE);	
}

void CTestBedDlg::OnFocusspeedc1() 
{
	UpdateData(TRUE);

	CString strFocusSpeedC1;
	m_ctrlFocusSpeedC1.GetLBText(m_FocusSpeedC1,strFocusSpeedC1);

	CString Order;	
	Order.Format("/cgi-bin/camctrl.cgi?speedapp=%d",m_FocusSpeedC1-5);
	ExecuteOrder(Order,strServerName1,id1,passwd1);
	
	UpdateData(FALSE);	
}

void CTestBedDlg::OnPanspeedc2() 
{
	UpdateData(TRUE);

	CString strPanSpeedC2;
	m_ctrlPanSpeedC2.GetLBText(m_PanSpeedC2,strPanSpeedC2);

	CString Order;	
	Order.Format("/cgi-bin/camctrl.cgi?speedpan=%d",m_PanSpeedC2-5);
	ExecuteOrder(Order,strServerName2,id2,passwd2);
	
	UpdateData(FALSE);
}

void CTestBedDlg::OnTiltspeedc2() 
{
	UpdateData(TRUE);

	CString strTiltSpeedC2;
	m_ctrlTiltSpeedC2.GetLBText(m_TiltSpeedC2,strTiltSpeedC2);

	CString Order;	
	Order.Format("/cgi-bin/camctrl.cgi?speedtilt=%d",m_TiltSpeedC2-5);
	ExecuteOrder(Order,strServerName2,id2,passwd2);
	
	UpdateData(FALSE);	
}

void CTestBedDlg::OnZoomspeedc2() 
{
	UpdateData(TRUE);

	CString strZoomSpeedC2;
	m_ctrlZoomSpeedC2.GetLBText(m_ZoomSpeedC2,strZoomSpeedC2);

	CString Order;	
	Order.Format("/cgi-bin/camctrl.cgi?speedzoom=%d",m_ZoomSpeedC2-5);
	ExecuteOrder(Order,strServerName2,id2,passwd2);
	
	UpdateData(FALSE);	
}

void CTestBedDlg::OnFocusspeedc2() 
{
	UpdateData(TRUE);

	CString strFocusSpeedC2;
	m_ctrlFocusSpeedC2.GetLBText(m_FocusSpeedC2,strFocusSpeedC2);

	CString Order;	
	Order.Format("/cgi-bin/camctrl.cgi?speedapp=%d",m_FocusSpeedC2-5);
	ExecuteOrder(Order,strServerName2,id2,passwd2);
	
	UpdateData(FALSE);	
} 

void CTestBedDlg::OnSaveInterval() 
{
	UpdateData(TRUE);

	CString strSaveInterval;
	m_ctrlSaveInterval.GetLBText(m_SaveInterval,strSaveInterval);

	switch(m_SaveInterval)
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

