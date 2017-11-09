//
#include "2.h"
#include "env_t.h"



#ifdef WINENV_
#include "wingdi.h"
#else
//
#endif


//
class MyBlackBoard_t : public SimpPaper
{
public:

	//
	MyBlackBoard_t()
	{
		m_backColor  = MKRGB( 0x00, 0x00, 0x00 );

		//m_foreColor  = MKRGB( 0xff, 0xf0, 0x00 );	 
		m_foreColor  = m_backColor;
	}


	//
	virtual ~MyBlackBoard_t()
	{ 
	}


	//
	virtual void OnPoint( int x, int y ) 
	{
		this->PaperPutPixel( x, y, m_foreColor );

		SBmp::RGB_t c = m_foreColor;

#ifdef WINENV_
		HWND h;
		HDC hdc;
		COLORREF a;
		 
		h = GetDesktopWindow();
		hdc = GetWindowDC(h);

		SStrf::smemcpy( &a, &c, sizeof(a) );

		SetPixel( hdc, x, y, a );
		
		ReleaseDC(h,hdc);
#else
		FILE * fp;
		long iBeginOffset;

		fp = fopen( "/dev/fb0" , "wb" );
		iBeginOffset = y * this->m_width + x;
		iBeginOffset *= 4;
		fseek( fp, iBeginOffset, SEEK_SET );
		fwrite( &(c.R), 1, 1, fp );
		fwrite( &(c.G), 1, 1, fp );
		fwrite( &(c.B), 1, 1, fp );
		
		fclose(fp);

#endif

	}


	//
	virtual void OnPoint_bg( int x, int y ) 
	{
		return;

		this->PaperPutPixel( x, y, m_backColor );
	
		SBmp::RGB_t c = m_backColor;

#ifdef WINENV_
		HWND h;
		HDC hdc;
		COLORREF a;
		 
		h = GetDesktopWindow();
		hdc = GetWindowDC(h);

		SStrf::smemcpy( &a, &c, sizeof(a) );

		SetPixel( hdc, x, y, a );
		
		ReleaseDC(h,hdc);
#else
		FILE * fp;
		long iBeginOffset;

		fp = fopen( "/dev/fb0" , "wb" );
		iBeginOffset = y * this->m_width + x;
		iBeginOffset *= 4;
		fseek( fp, iBeginOffset, SEEK_SET );
		fwrite( &(c.R), 1, 1, fp );
		fwrite( &(c.G), 1, 1, fp );
		fwrite( &(c.B), 1, 1, fp );
		
		fclose(fp);

#endif

	} 
		

	// new func
	void DrawScreenPixel( int x, int y, SBmp::RGB_t c )
	{
#ifdef WINENV_
		HWND h;
		HDC hdc;
		COLORREF a;
		 
		h = GetDesktopWindow();
		hdc = GetWindowDC(h);

		wl::SStrf::smemcpy( &a, &c, sizeof(a) );

		SetPixel( hdc, x, y, a );
		
		ReleaseDC(h,hdc);
#else
		FILE * fp;
		long iBeginOffset;

		fp = fopen( "/dev/fb0" , "wb" );
		iBeginOffset = y * this->m_width + x;
		iBeginOffset *= 4;
		fseek( fp, iBeginOffset, SEEK_SET );
		fwrite( &(c.R), 1, 1, fp );
		fwrite( &(c.G), 1, 1, fp );
		fwrite( &(c.B), 1, 1, fp );
		
		fclose(fp);

#endif

	}


	//
	void rand_forecolor()
	{
		m_foreColor.R = (tuint8)( SStrf::rand1() * 255 );
		m_foreColor.G = (tuint8)( SStrf::rand1() * 255 );
		m_foreColor.B = (tuint8)( SStrf::rand1() * 255 );
	}
};


///////////////////////////////////
//
class values_t 
{
public:
	SDte m_dt_old;
	SDte m_dt;
	std::string m_str_ip_old;
	std::string m_str_ip;

	//
	values_t()
	{
		m_dt.MakeNow();
		m_dt_old = m_dt;
	}


	//
	~values_t()
	{ 
	}


	//
	std::string get_ip_str()
	{
		if( IsOsWin() )
		{
			return "222.333.444.555";
		}

		//显示ip
		WFile fl;
		std::string strIp;

		fl.bind( "/tmp/1.txt" );
		fl.erase();

		WFile::run_exe( "ifconfig wlan0 |grep \"inet addr\"| cut -f 2 -d \":\"|cut -f 1 -d \" \">/tmp/1.txt" );

		fl.read_str( strIp );
		SStrf::strim( strIp );

		if( strIp == "" )
		{
			WFile::run_exe( "ifconfig wlan0 |grep \"inet \">/tmp/1.txt" );
			fl.read_str( strIp );
			SStrf::strim( strIp );
		}

		return strIp; 
	}


	//
	void refresh()
	{
		m_dt.MakeNow();
		m_str_ip = get_ip_str();
	}

	//
	void trace_up()
	{
		m_dt_old = m_dt;
		m_str_ip_old = m_str_ip;
	}


};






//
tbool do_clock( WNava & nvCmdLn )
{
	if( nvCmdLn.get( "-c" ) == "clock" )
	{
		values_t v;
		
		v.refresh();
		v.trace_up();

		while(1)
		{
			MyBlackBoard_t sp;
			double x, y;
			std::string strContent;


			sp.AttachHZK( gfBINDDATA("ASC16"), gfBINDDATA("HZK16F") );
			sp.Init( SStrf::satol( nvCmdLn.get( "-w" ) ) , SStrf::satol( nvCmdLn.get( "-h" ) ) );

			v.refresh();


			// draw txt on sp with scale



			//////////////

			//small number, erase old
			strContent = v.m_dt_old.ReadString();
			x = 90.0 / 1366.0 * sp.m_width;
			y = 80.0 / 768.0 * sp.m_height;
			sp.m_foreColor = sp.m_backColor;
			sp.PrintText( strContent , (int)x, (int)y, 
												1 , 0, 1 ,
												3.0 / 1366.0 * sp.m_width , 
												3.0 / 768.0 * sp.m_height	);

			//small number, draw new
			strContent = v.m_dt.ReadString(); 
			sp.rand_forecolor();
			y = sp.PrintText( strContent , (int)x, (int)y, 
												1 , 0, 1 ,
												3.0 / 1366.0 * sp.m_width , 
												3.0 / 768.0 * sp.m_height	);



			//////////////

			//big number, erase old
			strContent = v.m_dt_old.ReadStrTime();
			x = 90.0 / 1366.0 * sp.m_width;
			y += 80.0 / 768.0 * sp.m_height;
			sp.m_foreColor = sp.m_backColor;
			sp.PrintText( strContent, (int)x, (int)y, 
													1 , 0, 1 ,
													18.0 / 1366.0 * sp.m_width , 
													29.0 / 768.0 * sp.m_height		);

			// draw new
			strContent = v.m_dt.ReadStrTime();
			sp.rand_forecolor();
			y = sp.PrintText( strContent, (int)x, (int)y, 
													1 , 0, 1 ,
													18.0 / 1366.0 * sp.m_width , 
													29.0 / 768.0 * sp.m_height		);



			//////////////

			//ip number, erase old
			strContent = v.m_str_ip_old;
			x = 90.0 / 1366.0 * sp.m_width;
			y += 0.0 / 768.0 * sp.m_height;
			sp.m_foreColor = sp.m_backColor;
			sp.PrintText( strContent, (int)x, (int)y, 
													1 , 0, 1 ,
													6.0 / 1366.0 * sp.m_width , 
													6.0 / 768.0 * sp.m_height		);

			// ip, draw new
			strContent = v.m_str_ip;
			sp.rand_forecolor();
			y = sp.PrintText( strContent, (int)x, (int)y, 
													1 , 0, 1 ,
													6.0 / 1366.0 * sp.m_width , 
													6.0 / 768.0 * sp.m_height		);



	
			v.trace_up();
			

			if( v.m_dt.m_sec == 0 )
			{
				for( int y = 0; y < sp.m_height; y++ ) 
				{
					for( int x = 0; x < sp.m_width; x++ ) 
					{
						sp.DrawScreenPixel( (int)x, (int)y, sp.PaperGetPixel( x, y ) );
					}
				}
			}


			//WThrd::tr_sleep( 1 );
		}

		return 1;
	}

	return 0;
}




//
int main(int argc, char* argv[])
{
	env_t e;

	gp_env = &e;

	WNava &nv( gp_env->m_nvCmdLn );

	nv.InterpCmdLine( argc, argv );

	if( nv.get( "--help" ) != "" || nv.get( "-help" ) != "" )
	{
		printf( "%s %s\n", gp_env->m_strName.c_str(), gp_env->m_strVer.c_str() );
		printf( "%s\n", gp_env->m_strHelp.c_str() );
		
		goto L_MAINEND;
	}


	if( do_clock( nv ) )
	{
		goto L_MAINEND;
	}


	//show error msg, 不能解释的命令行参数。	 
	printf( "%s %s\n", gp_env->m_strName.c_str(), gp_env->m_strVer.c_str() );
	printf( "i cannot explain command line.\n" );


L_MAINEND:
	if( IsOsWin() )
	{
		int i;
		//system("pause");
		i = WFile::run_exe("pause");
	}
	return 0;
}


