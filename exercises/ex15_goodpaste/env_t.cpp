//
#include "2.h"
#include "env_t.h"


env_t  *gp_env;



	
//
env_t::env_t()	
{
	m_strName = "hello goodpaste!";
	m_strVer = "V1.02";
	m_strHelp = "hello goodpaste help!";
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





////////////////////////////////////////////////////////////////////////////

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





tbool copy_data_2_file( std::string strDataName, std::string strFn )
{
	WFile fl;
	SCake ck;

	fl.bind( strFn );
	gfBINDDATA( strDataName.c_str(), NULL, NULL, &ck );
	return fl.write( ck );
}






////////////////////////////////////////////////////////////////////////////////////////////

// cli_ter

//
cli_ter::cli_ter()	
{
}



//
cli_ter::~cli_ter()	
{
}



//
void cli_ter::tr_on_pre_thrd()
{
	WThrd::tr_sleep( 9 );
 
	return;
}



//
int cli_ter::tr_on_user_run()
{
	WFile f;
	
	f.bind( "ter.txt" ); // exit the process
	
	if( f.exists() )
	{
		f.erase();
	
		WThrd::tr_sleep( 16 );

		exit( 0 );
	}



	WThrd::tr_sleep( 16 );
 
	return 1;
}




