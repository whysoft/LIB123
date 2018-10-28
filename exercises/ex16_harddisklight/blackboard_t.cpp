﻿
#include "2.h"
#include "blackboard_t.h"


#ifdef WINENV_
#include "wingdi.h"
#else
//
#endif



#ifdef WINENV_
#pragma comment( lib, "gdi32.lib" ) 
#endif



blackboard_t  *gp_blackboard;



//
blackboard_t::blackboard_t()
{
}




//
blackboard_t::~blackboard_t()
{
}




//
void blackboard_t::DrawScreenPixel( int x, int y, SBmp::RGB_t c )
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

	if( fp == NULL )
	{
		printf( "cannot open fb0(DrawScreenPixel)\n" );
	}

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
void blackboard_t::DrawLineGreen( long value )
{
	long x;
	SBmp::RGB_t C;

	C.R = 255;
	C.G = 255;
	C.B = 255;

	for( x = 0 ; x < value; x++ )
	{
		this->DrawScreenPixel( x, 0, C );
		this->DrawScreenPixel( x, 1, C );
		this->DrawScreenPixel( x, 2, C );
		this->DrawScreenPixel( x, 3, C );
	}	 
}



//
void blackboard_t::DrawLineRed( long value )
{
	long x;
	SBmp::RGB_t C;

	C.R = 255;
	C.G = 0;
	C.B = 0;

	for( x = 0 ; x < value; x++ )
	{
		this->DrawScreenPixel( x, 0, C );
		this->DrawScreenPixel( x, 1, C );
		this->DrawScreenPixel( x, 2, C );
		this->DrawScreenPixel( x, 3, C );
	}	 
}



//
long blackboard_t::GetValue( std::string strAddr )
{
	WTcpCellc cc;
	std::string s1;
	SCake ck;
	tbool rc;

	rc = cc.Conn( strAddr );

	if( !rc )
	{
		rc = cc.Conn( strAddr );

		if( !rc )
		{
			return 0;
		}
	}
	

	s1 = "GET /AA?BB HTTP/1.0\r\n";
	s1 += "\r\n";

	cc.send_str( s1 );

	cc.recv_ln( ck, "\r\n\r\n" );
	if( ck.len() )
	{
		long l;

		l = SStrf::satol( ck.mk_str() );

		if( l > m_width ) l = m_width;

		return l;
	}

	return 0;
}


