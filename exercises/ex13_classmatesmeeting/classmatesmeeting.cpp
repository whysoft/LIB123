//
#include "2.h"
#include "env_t.h"
#include "ActiveWeb_t.h"




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


	if(1)
	{
		SStrf::newobjptr< AFWEB02::AFlowMgr_t<ActiveWeb_t> >()->NewFlow( 9397, 3600 * 4 );

		while(1)
		{
			WThrd::tr_sleep(3);
		}
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


