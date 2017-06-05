//
#include "2.h"
#include "env_t.h"




// 
int decode_PicFile( std::string strFn )  
{
	wl::SFile fl;
	wl::SCake ck;
	wl::SCake ck2;
	wl::SCake ck3;
	tchar *p;
	tuint8 *p1;
	int width, height, depth;
	tuint16 X, Y; // Y点高，X字节宽 

	X = 48; // X字节宽   宽度384点 窄型的纸 
	//X = 64; //宽型的纸	512

	fl.bind( strFn );
	fl.read( ck );
	wl::SBmp::Conv2Ck( ck, ck2, width, height, depth );
	if( width != X*8 )
	{
		printf( "width 错数。\n" );
		return 0;
	}

	if( depth != 3 )
	{
		printf( "必须是24位色的bmp图。\n" );
		return 0;
	}

	Y = height;
	ck3.redim( X * Y );

	for( int i = 0; i < X * 8 * Y ; i++ ) // i扫描的是目标2进制点。	
	{
		int cc;
		tbool aaa;

		p = ck2.buf() + i * 3;
		p1 = (tuint8*)p;

		cc = *p1 + *(p1+1) + *(p1+2);
		cc /= 3;
		if( cc > 130 ) aaa = 0;
		else aaa = 1;

		SStrf::writebit_r( ck3.buf(), i, aaa );
	}

	p1 = (tuint8*)&X;

	printf( "29\n118\n48\n0\n%d\n", (int)(*p1) );
	p1++;
	printf( "%d\n", (int)(*p1) );

	p1 = (tuint8*)&Y;
	printf( "%d\n", (int)(*p1) );
	p1++;
	printf( "%d\n", (int)(*p1) );

	for( int i = 0; i < (int)ck3.len(); i++ )	
	{
		p1 = (tuint8*)ck3.buf() + i;

		if( *p1 == 0x1D ) *p1 = 0x2d;//	保护指令	
		if( *p1 == 0x1B ) *p1 = 0x2b;

		printf( "%d\n", (int)(*p1) );
	}

	return 1;
}



//
int main(int argc, char* argv[])
{
	env_t e;

	gp_env = &e;

	WNava &nv( gp_env->m_nvCmdLn );

	nv.InterpCmdLine( argc, argv );

	if( nv.get( "--help" ) != "" || nv.get( "-help" ) != "" || nv.get( "-h" ) != "" )
	{
		printf( "%s %s\n", gp_env->m_strName.c_str(), gp_env->m_strVer.c_str() );
		printf( "%s\n", gp_env->m_strHelp.c_str() );
		
		goto L_MAINEND;
	}

	if(1)
	{
		decode_PicFile( "a.bmp" );
	
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


