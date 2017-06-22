
#include "2.h"



void test_navass()
{
	wl::SNavass n, n2;
	int i;
	std::string strSer;

	std::cout << "begin" << std::endl;

	for(i=0;i<111;i++)
	{
		n.let( "a" + wl::SStrf::sltoa(i) , wl::SStrf::sltoa(i) );
	}

	
	n.serialize( strSer );
	
	n.let( "abc", strSer );
	
	//std::cout << strSer << std::endl;

	std::cout << "unserialize" << std::endl;

	n2.unserialize( strSer );

	for(i=0;i<11;i++)
	{
		std::string s;
		n2.get( "a" + wl::SStrf::sltoa(i) , s );
		std::cout << "a" + wl::SStrf::sltoa(i) << "=" << s << std::endl;
	}

	for(i=0;i<11;i++)
	{
		std::cout << "a" + wl::SStrf::sltoa(i) << "=" << n2.get( "a" + wl::SStrf::sltoa(i) ) << std::endl;
	}

	for(i=0;i<11;i++)
	{
		std::cout << "b" + wl::SStrf::sltoa(i) << "=" << n2.get( "b" + wl::SStrf::sltoa(i) ) << std::endl;
	}
}


//
int main(int argc, char* argv[])
{
	test_navass();

	printf( "proc time = %f\n", wl::SDte::e_proctime() );
	wl::WThrd::tr_sleep(9);
	return 0;
}
  

