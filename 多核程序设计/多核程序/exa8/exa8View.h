// exa8View.h : interface of the CExa8View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EXA8VIEW_H__A54BEEE0_B5BB_43DF_B348_37498501C3EE__INCLUDED_)
#define AFX_EXA8VIEW_H__A54BEEE0_B5BB_43DF_B348_37498501C3EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CExa8View : public CEditView
{
protected: // create from serialization only
	CExa8View();
	DECLARE_DYNCREATE(CExa8View)

// Attributes
public:
	CExa8Doc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExa8View)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual void OnInitialUpdate();
	virtual ~CExa8View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CExa8View)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in exa8View.cpp
inline CExa8Doc* CExa8View::GetDocument()
   { return (CExa8Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXA8VIEW_H__A54BEEE0_B5BB_43DF_B348_37498501C3EE__INCLUDED_)
