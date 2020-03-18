// exa8.h : main header file for the EXA8 application
//

#if !defined(AFX_EXA8_H__A6C13AFC_1437_4086_B093_602E9D2E3F56__INCLUDED_)
#define AFX_EXA8_H__A6C13AFC_1437_4086_B093_602E9D2E3F56__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CExa8App:
// See exa8.cpp for the implementation of this class
//

class CExa8App : public CWinApp
{
public:
	CExa8App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExa8App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CExa8App)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXA8_H__A6C13AFC_1437_4086_B093_602E9D2E3F56__INCLUDED_)
