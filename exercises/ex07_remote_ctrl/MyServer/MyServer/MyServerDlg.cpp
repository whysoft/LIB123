
// MyServerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MyServer.h"
#include "MyServerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyServerDlg dialog




CMyServerDlg::CMyServerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMyServerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMyServerDlg, CDialogEx)
		ON_WM_TIMER()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CMyServerDlg message handlers

BOOL CMyServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	SetTimer(1, 666, NULL); // 
	this->GetDlgItem( IDC_STATIC )->SetWindowText( CString("监控服务端") );
	this->GetDlgItem( IDC_STATIC2 )->SetWindowText( CString("正在运行") );

	this->SetWindowText( CString("视频监控系统 - 北京中科神盾环境安全技术中心") );

	int ZEROIFSUCCESSFUL = 0;
	WSADATA	 Wa;
	ZEROIFSUCCESSFUL = WSAStartup( MAKEWORD(2,0), &Wa );

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMyServerDlg::OnPaint()
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
HCURSOR CMyServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

#include "bmpf.c"

char * p;
long len;
const char *filename;
SOCKET	soc1;
SOCKET	soc2;
SOCKET	socZUO1;
SOCKET	socZUO2;


void foo1(void *)
{
//::_beginthread(  
//	[&](void *p)
//	{
//		return;
//	};
//	, 0, NULL );

 
 // ::_beginthread(  
	//pftest
	//, 0, NULL );
	while(1)
	{
		if( soc1 == INVALID_SOCKET )
		{
			return ;
		}
		
		while(1)
		{
			if(soc1 != INVALID_SOCKET)
			{
				struct	sockaddr_in	 from;
				int nSize;
				
				nSize= sizeof(from);
			
				soc2 = ::accept( soc1, (struct sockaddr *)&from, &nSize ); //  now have a new value
				
			}
			else
			{ 
				soc2 = INVALID_SOCKET;
			}


			if( soc2 == INVALID_SOCKET )
			{
				break;
			}

			//传送 
			if(soc2!=INVALID_SOCKET)  
			{
				int i;
				 long  k;
			
				k = 0;
				for(;;)
				{
					i = (int)::send( soc2, (char*)((&len)) +k, (int)(4-k), 0);
			
					k +=i;
					if( i == 0 )break;
					if(k>=len) break;
				}
			
			}

			if(soc2!=INVALID_SOCKET)  
			{
				int i;
				 long  k;
			
				k = 0;
				for(;;)
				{
					i = (int)::send( soc2, (char*)(p) +k, (int)(len-k), 0);
			
					k +=i;
					if( i == 0 )break;
					if(k>=len) break;
				}
			
			}

			//、、

			break;
		}

		shutdown( soc2, 2 ); 
		closesocket(soc2); 
	}
}




void foo2(void *)
{
	struct MoustBeh_t Mb;
	int L;

	while(1)
	{
		if( socZUO1 == INVALID_SOCKET )
		{
			return ;
		}
		
		while(1)
		{
			if(socZUO1 != INVALID_SOCKET)
			{
				struct	sockaddr_in	 from;
				int nSize;
				
				nSize= sizeof(from);
			
				socZUO2 = ::accept( socZUO1, (struct sockaddr *)&from, &nSize ); //  now have a new value
				
			}
			else
			{ 
				socZUO2 = INVALID_SOCKET;
			}


			if( socZUO2 == INVALID_SOCKET )
			{
				break;
			}

			//接收 
			if( socZUO2 != INVALID_SOCKET )  
			{
				int i;
			
				L = 0;
			
				for( int j = 0 ; ; j++ )
				{
					i = (int)::recv( socZUO2, (char*)((char*)&Mb) + L , sizeof(Mb) - L, 0 );
				
					if(i==SOCKET_ERROR||i==0) break;
			
					L +=i;
				
					if( L >= sizeof(Mb)) break;
				}
			
			}
			

			//、、

			break;
		}

		//处理各事
		if( Mb.itype == 1 )
		{
			 
			double fScreenWidth = ::GetSystemMetrics( SM_CXSCREEN )-1; 
			double fScreenHeight = ::GetSystemMetrics( SM_CYSCREEN )-1; 
			fScreenWidth=MYWIDTH;fScreenHeight=MYHEIGHT;
			double fx = (double)Mb.x / 800.0 * fScreenWidth;
			double fy = (double)Mb.y / 600.0 * fScreenHeight;
					double ffx = Mb.x*(65535.0f/MYWIDTH);
					double ffy = Mb.y*(65535.0f/MYHEIGHT);
					mouse_event( MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE, static_cast<DWORD>(ffx), static_cast<DWORD>(ffy), 0, 0 );
			mouse_event ( MOUSEEVENTF_LEFTDOWN , 0, 0, 0, 0 );
			mouse_event ( MOUSEEVENTF_LEFTUP,    0, 0, 0, 0 );
			

		}

		if( Mb.itype == 2 )
		{
			 
			double fScreenWidth = ::GetSystemMetrics( SM_CXSCREEN )-1; 
			double fScreenHeight = ::GetSystemMetrics( SM_CYSCREEN )-1; 
			fScreenWidth=MYWIDTH;fScreenHeight=MYHEIGHT;
			double fx = (double)Mb.x / 800.0 * fScreenWidth;
			double fy = (double)Mb.y / 600.0 * fScreenHeight;
					double ffx = Mb.x*(65535.0f/MYWIDTH);
					double ffy = Mb.y*(65535.0f/MYHEIGHT);
					mouse_event( MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE, static_cast<DWORD>(ffx), static_cast<DWORD>(ffy), 0, 0 );
			mouse_event ( MOUSEEVENTF_LEFTDOWN , 0, 0, 0, 0 );
			mouse_event ( MOUSEEVENTF_LEFTUP,    0, 0, 0, 0 );
			mouse_event ( MOUSEEVENTF_LEFTDOWN , 0, 0, 0, 0 );
			mouse_event ( MOUSEEVENTF_LEFTUP,    0, 0, 0, 0 );
			

		}
		
		if( Mb.itype == 3 )
		{
			 
			double fScreenWidth = ::GetSystemMetrics( SM_CXSCREEN )-1; 
			double fScreenHeight = ::GetSystemMetrics( SM_CYSCREEN )-1; 
			fScreenWidth=MYWIDTH;fScreenHeight=MYHEIGHT;
			double fx = (double)Mb.x / 800.0 * fScreenWidth;
			double fy = (double)Mb.y / 600.0 * fScreenHeight;
					double ffx = Mb.x*(65535.0f/MYWIDTH);
					double ffy = Mb.y*(65535.0f/MYHEIGHT);
					mouse_event( MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE, static_cast<DWORD>(ffx), static_cast<DWORD>(ffy), 0, 0 );
			//WMsg::mou_move( long x, long y );
			mouse_event ( MOUSEEVENTF_RIGHTDOWN  , 0, 0, 0, 0 );
			mouse_event ( MOUSEEVENTF_RIGHTUP,     0, 0, 0, 0 );
			

		}
	
		if( Mb.itype == 4 )
		{
			if( Mb.x )
			{
				BYTE c;
				c = (BYTE)(Mb.x);
				keybd_event(c, 0, 0,			 	0);
				keybd_event(c, 0, KEYEVENTF_KEYUP,  0);
			}
			

		}

		shutdown( socZUO2, 2 ); 
		closesocket(socZUO2); 
	}
}




//
void CMyServerDlg::OnTimer(UINT nIDEvent) 
{
	static CRect rect;
	static CWnd* pwnd;
	static int i = 0;
	static int j = 0;

	filename = "d:\\buff.bmp";

	if( i == 0 )
	{
		i++;
		pwnd = GetDesktopWindow();
		//pwnd = this;
		pwnd->GetWindowRect(&rect);
	}

	HBITMAP hMap = CopyScreenToBitmap(rect); 
	SaveBitmapToFile(hMap, CString(filename));

	if( j == 0 )
	{
		j++;

		if(filename)
		{
			FILE *fp;
			fp = fopen( filename , "rb" );
			if(fp==NULL) len = 0;
			else
			{
				fseek( fp,0,SEEK_END );
				len =ftell(fp);
				fclose(fp);
			}
		}
		


		p = (char*)malloc( len );

		//侦听8000，画面通道	
		if(8100)
		{
			struct	sockaddr_in	 saddr;
			u_long a_in_addrip = INADDR_ANY;
			int listener_num = 4;
		
			soc1 = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
		
			if( soc1 != INVALID_SOCKET )
			{
				//we should zero mem here.
				memset( (void*)&saddr, 0, sizeof(saddr) );
		
				saddr.sin_family = AF_INET; 
				saddr.sin_port = htons( (u_short)8100 );
				saddr.sin_addr.s_addr = a_in_addrip;	
				
				if( SOCKET_ERROR != bind( soc1, (struct sockaddr *)&saddr, sizeof(saddr) ) )
				{
					if( 0 != ::listen( soc1, listener_num ) )
					{
						soc1 = INVALID_SOCKET;
					}
				}
				else
				{
					soc1 = INVALID_SOCKET;
				}
			}
		}
		else
		{ 
			soc1 = INVALID_SOCKET;
		}

		if(8200)
		{
			struct	sockaddr_in	 saddr;
			u_long a_in_addrip = INADDR_ANY;
			int listener_num = 4;
		
			socZUO1 = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
		
			if( socZUO1 != INVALID_SOCKET )
			{
				//we should zero mem here.
				memset( (void*)&saddr, 0, sizeof(saddr) );
		
				saddr.sin_family = AF_INET; 
				saddr.sin_port = htons( (u_short)8200 );
				saddr.sin_addr.s_addr = a_in_addrip;	
				
				if( SOCKET_ERROR != bind( socZUO1, (struct sockaddr *)&saddr, sizeof(saddr) ) )
				{
					if( 0 != ::listen( socZUO1, listener_num ) )
					{
						socZUO1 = INVALID_SOCKET;
					}
				}
				else
				{
					socZUO1 = INVALID_SOCKET;
				}
			}
		}
		else
		{ 
			socZUO1 = INVALID_SOCKET;
		}


		//启动线程1
		::_beginthread(  
		foo1
		, 0, NULL );

		//启动线程2
		::_beginthread(  
		foo2
		, 0, NULL );
	}

	if(filename)
	{
		FILE *fp;
		fp = fopen( filename , "rb" );
		if(fp==NULL){}
		else
		{
			long flen;
			fseek( fp,0,SEEK_END );
			flen=ftell(fp);
			fseek( fp,0,SEEK_SET );
			fread( (p), flen, 1, fp );
			fclose(fp);
		}
	}
	

}





