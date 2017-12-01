//
#include "2.h"
#include "env_t.h"
#include "de_log_t.h"
#include "ActiveWeb_t.h"




//
extern "C"
int main(int argc, char* argv[] )
{
	gp_env = new env_t();
	gp_log = new de_log4_t();

	//MakeDiskEnv
	WFile::makedir( "LOG_goodpaste" );
	WFile::makedir( WFile::MkDir2Path("LOG_goodpaste") + "LOG1"  );
	gp_log->Init( "LOG_goodpaste", "LOG1", 22 );

	LOGSTREAM( *gp_log, LOGPOSI << "===================================================" );

	//WNava nv;
	WNava &nv( gp_env->m_nvCmdLn );

	nv.InterpCmdLine( argc, argv );

	if( nv.get( "--help" ) != "" || nv.get( "-help" ) != "" )
	{
		printf( "%s %s\n", gp_env->m_strName.c_str(), gp_env->m_strVer.c_str() );
		printf( "%s\n", gp_env->m_strHelp.c_str() );
		
		exit( 0 );
	}


	SStrf::newobjptr< cli_ter >()->tr_openx();


	gp_env->m_gt.InitSDB( "a_goodtbl_t.h", "." );
	gp_env->m_gt.Load();


	if( 1 )
	{
		AFWEB02::AFlowMgr_t< ActiveWeb_t >::NewFlow( 7009, 8899 );

		while(1)
		{
			WThrd::tr_sleep( 5 );
		}

		goto L_MAINEND;
	}


	//show error msg, 不能解释的命令行参数。	 
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



