// Testbed.h : main header file for the TESTBED application
//

#if !defined(AFX_TESTBED_H__5E91FB5D_07B6_4A7A_A2F5_B32FBB2D37B8__INCLUDED_)
#define AFX_TESTBED_H__5E91FB5D_07B6_4A7A_A2F5_B32FBB2D37B8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestbedApp:
// See Testbed.cpp for the implementation of this class
//

class CTestbedApp : public CWinApp
{
public:
	CTestbedApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestbedApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTestbedApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTBED_H__5E91FB5D_07B6_4A7A_A2F5_B32FBB2D37B8__INCLUDED_)
