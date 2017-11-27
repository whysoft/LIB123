//
#include "2.h"
#include "env_t.h"


env_t  *gp_env;



	
//
env_t::env_t()	
{
	m_strName = "2017 classmates meeting reg service";
	m_strVer = "V1.00";
	m_strHelp = "2017 classmates meeting reg service";
	bu_backoffi2_mgr_t<>::Def( 9902 );
	
	m_ma.InitSDB( "a_mates_t", "." );
	m_ma.Load();
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




#include "A-bind_data.xpp"



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




