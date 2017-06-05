//
#include "2.h"
#include "env_t.h"



env_t  *gp_env;




#ifdef LINUENV_
#include <signal.h>
struct A
{
	A()
	{
		signal(SIGPIPE, signal_handler);
	}
	static void signal_handler(int sig)
	{
		if( sig==SIGPIPE ) return;
	}
};
static A aaaaa;
#endif



// 
bool IsOsWin()
{
#ifdef WINENV_
	return true;
#else
	return false;
#endif
}




	
//
env_t::env_t()	
{
	m_strName = "bmp-prn-data";
	m_strVer = "V1.2";
	m_strHelp = "bmp-prn-data help";
}



//
env_t::~env_t()	
{
}



//
int env_t::tr_on_user_run()
{

	WThrd::tr_sleep( 33 );
 
	return 1;
}



