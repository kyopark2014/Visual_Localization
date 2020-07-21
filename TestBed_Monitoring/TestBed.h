// TestBed.h : main header file for the TESTBED application
//

#if !defined(AFX_TESTBED_H__26D0ACD1_DB0F_4CD2_9B49_995B371AE2F6__INCLUDED_)
#define AFX_TESTBED_H__26D0ACD1_DB0F_4CD2_9B49_995B371AE2F6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestBedApp:
// See TestBed.cpp for the implementation of this class
//

class CTestBedApp : public CWinApp
{
public:
	CTestBedApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestBedApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTestBedApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTBED_H__26D0ACD1_DB0F_4CD2_9B49_995B371AE2F6__INCLUDED_)
