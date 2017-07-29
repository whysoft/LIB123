//
#include "2.h"
#include "env_t.h"
#include "svr_ppp.h"
#include "cli_ppp.h"



//
tbool do_ppp_server( WNava & nvCmdLn )
{
	if( nvCmdLn.get( "-c" ) == "server" )
	{
		SStrf::newobjptr< svr_ppp >()->tr_openx();
		SStrf::newobjptr< svr_dns >()->tr_openx();
		SStrf::newobjptr< svr_route >()->tr_openx();
		SStrf::newobjptr< svr_myip >()->tr_openx();
		SStrf::newobjptr< svr_iptables >()->tr_openx();
		SStrf::newobjptr< svr_ipforward >()->tr_openx();
		SStrf::newobjptr< svr_reboot >()->tr_openx();

		while(1)
		{
			WThrd::tr_sleep( 3 );
		}

		return 1;
	}

	return 0;
}



//
tbool do_ppp_cli( WNava & nvCmdLn )
{
	if( nvCmdLn.get( "-c" ) == "cli" )
	{
		SStrf::newobjptr< cli_ppp >()->tr_openx();
		SStrf::newobjptr< cli_dns >()->tr_openx();
		SStrf::newobjptr< cli_route >()->tr_openx();
		SStrf::newobjptr< cli_myip >()->tr_openx();
		SStrf::newobjptr< cli_iptables >()->tr_openx();
		SStrf::newobjptr< cli_ipforward >()->tr_openx();
		SStrf::newobjptr< cli_reboot >()->tr_openx();

		while(1)
		{
			WThrd::tr_sleep( 3 );
		}

		return 1;
	}

	return 0;
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


	if( do_ppp_server( nv ) )
	{
		goto L_MAINEND;
	}

	if( do_ppp_cli( nv ) )
	{
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


