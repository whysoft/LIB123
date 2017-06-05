
#ifdef _MT
#define WINENV_
#else
#define LINUENV_
#endif
#ifdef WINENV_
#include <windows.h> 
#include <shellapi.h>
#pragma comment( lib, "ws2_32.lib" )
#include <winsock.h>
#include "atlstr.h" // 
#endif
#include "1.h"



void test_cake_file()
{
	wl::SCake ck1, ck2;
	wl::SFile fl;

	fl.bind( "cake_file.cpp" );
	fl.read(ck1);

	std::cout << "len=" << (int)ck1.len() << std::endl;

	ck2 = ck1;

	ck1.append( ck2 );

	fl.bind( "cake_file.cpp2" );
	fl.write(ck1);
}


//
int main(int argc, char* argv[])
{
	test_cake_file();

	printf( "proc time = %f\n", wl::SDte::e_proctime() );
	wl::WThrd::tr_sleep(9);
	return 0;
}
  

