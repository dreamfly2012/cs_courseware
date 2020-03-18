// exa8Doc.cpp : implementation of the CExa8Doc class
//

#include "stdafx.h"
#include "exa8.h"

#include "exa8Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExa8Doc

IMPLEMENT_DYNCREATE(CExa8Doc, CDocument)

BEGIN_MESSAGE_MAP(CExa8Doc, CDocument)
	//{{AFX_MSG_MAP(CExa8Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExa8Doc construction/destruction

CExa8Doc::CExa8Doc()
{
	// TODO: add one-time construction code here

}

CExa8Doc::~CExa8Doc()
{
}

BOOL CExa8Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	((CEditView*)m_viewList.GetHead())->SetWindowText(NULL);

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CExa8Doc serialization

void CExa8Doc::Serialize(CArchive& ar)
{
	// CEditView contains an edit control which handles all serialization
	((CEditView*)m_viewList.GetHead())->SerializeRaw(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CExa8Doc diagnostics

#ifdef _DEBUG
void CExa8Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CExa8Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CExa8Doc commands
