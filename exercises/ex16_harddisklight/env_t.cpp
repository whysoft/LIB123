//
#include "2.h"
#include "env_t.h"


env_t  *gp_env;



	
//
env_t::env_t()	
{
	m_strName = "harddisklight";
	m_strVer = "V1.00";
	m_strSysVerInternal = "20181028.163850" + std::string(" ") + std::string(__DATE__) + std::string(" ") + std::string(__TIME__) + std::string(" ");
	m_strHelp = "hello hello harddisklight help!";


	//////
	//MakeDiskEnv
	//WFile::makedir( this->GetDBDir() );
	//WFile::makedir( this->GetLOGDir() ); 

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





//
std::string env_t::GetLOGDir()
{
	std::string s1;

	s1 = this->m_strName;
	SStrf::sucase( s1 );

	return s1 + ".LOG";
}



//
std::string env_t::GetDBDir()
{
	std::string s1;

	s1 = this->m_strName;
	SStrf::sucase( s1 );

	return s1 + ".DB";
}






////////////////////////////////////////////////////////////////////////////
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




//
bool IsExeCharSetUtf8()
{
	const char *p = "亖";
	if( p[2] ) return true;
	return false;
}




//
tbool copy_data_2_file( std::string strDataName, std::string strFn )
{
	WFile fl;
	SCake ck;

	fl.bind( strFn );
	gfBINDDATA( strDataName.c_str(), NULL, NULL, &ck );
	return fl.write( ck );
}





