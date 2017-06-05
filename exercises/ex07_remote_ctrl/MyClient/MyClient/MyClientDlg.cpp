// MyClientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MyClient.h"
#include "MyClientDlg.h"
#include "afxdialogex.h"
#include "EditInfoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyClientDlg dialog




CMyClientDlg::CMyClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMyClientDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMyClientDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONDOWN()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON1, &CMyClientDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMyClientDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CMyClientDlg message handlers

BOOL CMyClientDlg::OnInitDialog()
{
	INT_PTR nResponse;
	EditInfoDlg dlg1;
	nResponse = dlg1.DoModal();
	if (nResponse == IDCANCEL) this->OnCancel();

	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	SetWindowPos( FromHandle(GetSafeHwnd()),0,0, 1224, 777, SWP_NOZORDER);//具体大小设置
	this->GetDlgItem( IDC_BUTTON1 )->SetWindowText( CString("发出字母A") );
	this->GetDlgItem( IDC_BUTTON2 )->SetWindowText( CString("发出字母B") );
	
	this->SetWindowText( CString("视频监控系统 - 北京中科神盾环境安全技术中心") );
	
	SetTimer(1, 666, NULL); // 

	int ZEROIFSUCCESSFUL = 0;
	WSADATA		Wa;
	ZEROIFSUCCESSFUL = WSAStartup( MAKEWORD(2,0), &Wa );

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMyClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMyClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


static void drawBitmapFormFile1( CString BitmapFilePath, CDC  *pDC, CRect rect )     
{     
	HANDLE   filehandle=::LoadImage( NULL, BitmapFilePath, IMAGE_BITMAP , 0, 0, LR_LOADFROMFILE );     
	if(filehandle!=NULL)     
	{     
		CBitmap   bmp;     
		if(bmp.Attach(filehandle))     
		{     
			BITMAP   bmpInfo;     
			bmp.GetBitmap(&bmpInfo);     
			CDC   dcMemory; 

			dcMemory. CreateCompatibleDC(pDC);
			dcMemory.SelectObject(&bmp);
			pDC->SetStretchBltMode(HALFTONE);

			//pDC->StretchBlt( 0, 0, 800, 600, &dcMemory, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, SRCCOPY );
			pDC->BitBlt( 0, 0, MYWIDTH, MYHEIGHT,  &dcMemory, 0, 0, SRCCOPY);

			bmp.Detach(); 
		}
		//DeleteObject(LoadImage时返回的句丙) 
		DeleteObject(filehandle);
	}     
}  

using namespace Temp;
#include "A10foo1.C"

//
void CMyClientDlg::OnTimer(UINT nIDEvent) 
{
	static CWnd* pwnd;
	CDC* pdc;
	CRect r1;

	if( i == 0 )
	{
		i++;
		//启动线程1
		::_beginthread(  
		foo1
		, 0, NULL );
		std::string ss;
		ss = "del ";
		ss += filename[0];
		system( ss.c_str() );
		ss = "del ";
		ss += filename[1];
		system( ss.c_str() );
	}

	pwnd = this;
	//pdc = pwnd->GetWindowDC();
	pdc = pwnd->GetDC();
	pwnd->GetWindowRect( r1 );

	drawBitmapFormFile1( CString(filename[(i+1)&1]),  pdc, r1 );
	
	ReleaseDC( pdc );
}


void CMyClientDlg::OnLButtonDown( UINT nFlags, CPoint point )
{
	if( point.x >= MYWIDTH || point.y >= MYHEIGHT ) return;
	struct MoustBeh_t Mb;
	Mb.itype = 1;
	Mb.x = point.x;
	Mb.y = point.y;
	foo1(&Mb);
}


void CMyClientDlg::OnLButtonDblClk( UINT nFlags, CPoint point )
{
	if( point.x >= MYWIDTH || point.y >= MYHEIGHT ) return;
	struct MoustBeh_t Mb;
	Mb.itype = 2;
	Mb.x = point.x;
	Mb.y = point.y;
	//foo1(&Mb);
}


void CMyClientDlg::OnRButtonDown( UINT nFlags, CPoint point )
{
	if( point.x >= MYWIDTH || point.y >= MYHEIGHT ) return;
	struct MoustBeh_t Mb;
	Mb.itype = 3;
	Mb.x = point.x;
	Mb.y = point.y;
	foo1(&Mb);
}


void CMyClientDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	struct MoustBeh_t Mb;
	Mb.itype = 4;
	Mb.x = 'A';
	foo1(&Mb);
}


void CMyClientDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	struct MoustBeh_t Mb;
	Mb.itype = 4;
	Mb.x = 'B';
	foo1(&Mb);
}
