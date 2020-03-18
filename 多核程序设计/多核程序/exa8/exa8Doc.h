// exa8Doc.h : interface of the CExa8Doc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EXA8DOC_H__F816E86E_FF23_415D_A94E_0FF93FCDBA94__INCLUDED_)
#define AFX_EXA8DOC_H__F816E86E_FF23_415D_A94E_0FF93FCDBA94__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CExa8Doc : public CDocument
{
protected: // create from serialization only
	CExa8Doc();
	DECLARE_DYNCREATE(CExa8Doc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExa8Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CExa8Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CExa8Doc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXA8DOC_H__F816E86E_FF23_415D_A94E_0FF93FCDBA94__INCLUDED_)
