// MyClientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MyClient.h"
#include "MyClientDlg.h"
#include "afxdialogex.h"

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
END_MESSAGE_MAP()


// CMyClientDlg message handlers

BOOL CMyClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	SetWindowPos(FromHandle(GetSafeHwnd()),0,0,999,600,SWP_NOZORDER);//具体大小设置
	
	SetTimer(1, 1111, NULL); // 

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
	HANDLE   filehandle=::LoadImage(NULL,BitmapFilePath,IMAGE_BITMAP,0,0,LR_LOADFROMFILE);     
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
			pDC->StretchBlt( 0, 0, 800, 600, &dcMemory, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, SRCCOPY );
			bmp.Detach(); 
		}     
	}     
}  


using namespace Temp;
static int i = 0;
static char *filename[] = { "d:\\buff0.bmp", "d:\\buff1.bmp" };

//
void CMyClientDlg::OnTimer(UINT nIDEvent) 
{
	static CWnd* pwnd;
	CDC* pdc;
	CRect r1;

	i++;
	pwnd = this;
	pdc = pwnd->GetWindowDC();
	pwnd->GetWindowRect( r1 );

	drawBitmapFormFile1( CString(filename[i&1]),  pdc, r1 );
	
	ReleaseDC( pdc );
}


void CMyClientDlg::OnLButtonDown( UINT nFlags, CPoint point )
{
   
}


void CMyClientDlg::OnLButtonDblClk( UINT nFlags, CPoint point )
{
   
}


void CMyClientDlg::OnRButtonDown( UINT nFlags, CPoint point )
{
   
}





