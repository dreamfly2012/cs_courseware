// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "exa8.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

HANDLE g_hBusy;//信号量
HWND hwnd;//窗口对象句柄
int  k=0;
long data1[] = {12,32,47,763,75,43,86,42};
long data2[] = {432,68,36,84,47,73,732,46};
long data3[] = {435,754,37,765,48,785,326,78};
long data4[] = {54,76,93,457,456,34,94,50};
/////////////////////////////////////////////////////////////////////////////
// CMainFrame
//**使用MFC同步类的例子

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};


int QuickSort(long* Array, int iLow, int iHigh)//快速排序程序
{  if(iLow >= iHigh) 
                   return 1;                                                                                                                                                                  
    long pivot = Array[iLow];
    int iLowSaved = iLow;
    int iHighSaved = iHigh;
    while (iLow < iHigh)
    {
          while (Array[iHigh] >= pivot && iHigh > iLow)
                iHigh --;
          Array[iLow] = Array[iHigh];
          while (Array[iLow]< pivot && iLow < iHigh)
           iLow++;
           Array[iHigh] = Array[iLow];
     }
           Array[iLow] = pivot;
           QuickSort(Array,iLowSaved,iHigh-1);
           QuickSort(Array, iLow+1, iHighSaved);
           return 0;
 }

//可以去掉信号量控制部分，查看屏幕呈现结果。
UINT DataProcess(LPVOID p)
{   long* Array = (long*)p;
     char pszMsg[512];
      memset(pszMsg,'\0',512);
      DWORD dwRet;

      int i;
     QuickSort( Array, 0, 7);

	 //获取信号量。
    dwRet = WaitForSingleObject(g_hBusy, INFINITE) ;
    
	 for(i=0; i<8; i++)
      {   sprintf(pszMsg, "%d             ", Array[i]);
           SendMessage(hwnd, EM_REPLACESEL, true, (LPARAM)(pszMsg));
           Sleep(100);
      }
     sprintf(pszMsg, "\r\n");
     SendMessage(hwnd, EM_REPLACESEL, true, (LPARAM)(pszMsg));

	 //释放信号量。
     ReleaseSemaphore(g_hBusy, 1, NULL);//给g_hBusy信号量加1
     
	 return 0;
}



/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


void CMainFrame::Start()
{  
	//创建信号量。
	g_hBusy = CreateSemaphore(NULL, 1, 1, NULL);
 
     hwnd=m_hwndViewEdit;
   
	 //创建四个线程。
	 AfxBeginThread(DataProcess, (LPVOID)data1, THREAD_PRIORITY_NORMAL);
     AfxBeginThread(DataProcess, (LPVOID)data2, THREAD_PRIORITY_NORMAL);
     AfxBeginThread(DataProcess, (LPVOID)data3, THREAD_PRIORITY_NORMAL);
     AfxBeginThread(DataProcess, (LPVOID)data4, THREAD_PRIORITY_NORMAL);

}
