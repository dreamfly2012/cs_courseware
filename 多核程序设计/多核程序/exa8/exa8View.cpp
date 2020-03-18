// exa8View.cpp : implementation of the CExa8View class
//

#include "stdafx.h"
#include "exa8.h"

#include "exa8Doc.h"
#include "exa8View.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExa8View

IMPLEMENT_DYNCREATE(CExa8View, CEditView)

BEGIN_MESSAGE_MAP(CExa8View, CEditView)
	//{{AFX_MSG_MAP(CExa8View)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExa8View construction/destruction

CExa8View::CExa8View()
{
	// TODO: add construction code here

}

CExa8View::~CExa8View()
{
}

BOOL CExa8View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// Enable word-wrapping

	return bPreCreated;
}

/////////////////////////////////////////////////////////////////////////////
// CExa8View drawing

void CExa8View::OnDraw(CDC* pDC)
{
	CExa8Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CExa8View diagnostics

#ifdef _DEBUG
void CExa8View::AssertValid() const
{
	CEditView::AssertValid();
}

void CExa8View::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CExa8Doc* CExa8View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CExa8Doc)));
	return (CExa8Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CExa8View message handlers

void CExa8View::OnInitialUpdate()
{   CEditView::OnInitialUpdate();
	
	((CMainFrame*)AfxGetMainWnd())->m_hwndViewEdit = GetEditCtrl().GetSafeHwnd();
    ((CMainFrame*)AfxGetMainWnd())->Start();
}
