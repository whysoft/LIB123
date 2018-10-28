//
#include "2.h"
#include "ga_t.h"
#include "env_t.h"
#include "bu_quickflow_t.h"
#include "bu_actweb_t.h"
#include "bu_asynwork_t.h"
#include "blackboard_t.h"



 
int main( int argc, char* argv[] )
{
	gp_ga = new ga_t();


	gp_env = new env_t();
	gp_env->m_nvCmdLn.InterpCmdLine( argc, argv );


	//WNava nvCmdLn;
	WNava &nvCmdLn( gp_env->m_nvCmdLn );


	if( nvCmdLn.get( "--help" ) != "" || nvCmdLn.get( "-help" ) != "" || nvCmdLn.get( "-h" ) != "" )
	{
		printf( "PRJ NAME=%s VER=%s\n", gp_env->m_strName.c_str(), gp_env->m_strVer.c_str() );
		printf( "%s\n", gp_env->m_strHelp.c_str() );
		
		goto L_MAINEND;
	}


	bu_asynwork_t::Do_demo( gp_env->m_strName );
	bu_asynwork_t::Do_demo( gp_env->m_strVer );
	bu_asynwork_t::Do_demo( gp_env->m_strSysVerInternal );



	if( nvCmdLn.get( "-c" ) == "" )
	{
		tbool rc;
		tuint16 uiPortOut;

		rc = bu_actweb_t::NewActweb( 12000 , &uiPortOut );
	 

		while(1)
		{
			//char sz[999];
			std::string s1;
			std::vector< std::string > vInfo;

			//std::cin.getline( sz, 999 );

			std::getline( std::cin, s1 );

			printf( "%s\n", s1.c_str() ); 

			SStrvs::vsa_imp( s1, std::string(" "), 1, vInfo );

			if( vInfo.size() >= 10 )
			{
				gp_env->m_Num = SStrf::satol( vInfo[8] ) + SStrf::satol( vInfo[9] );
				//if( gp_env->m_Num > 1000 ) gp_env->m_Num = 1000;
			}

			printf( "%ld\n", gp_env->m_Num );
		}

		goto L_MAINEND;
	}


	if( nvCmdLn.get( "-c" ) == "client" )
	{
		gp_blackboard = new blackboard_t();
		gp_blackboard->m_width = SStrf::satol( nvCmdLn.get( "-width" ) );

		long valOld, valNew;

		valOld = valNew = 0;
		
		while(1)
		{
			valNew = gp_blackboard->GetValue( nvCmdLn.get( "-addr" ) );
	
			gp_blackboard->DrawLineGreen( valOld );
			gp_blackboard->DrawLineRed( valNew );

			valOld = valNew;

			WThrd::tr_sleepu( 0.9 );
		}

		goto L_MAINEND;
	}



	//show error msg, 不能解释的命令行参数。	 
	printf( "%s %s\n", gp_env->m_strName.c_str(), gp_env->m_strVer.c_str() );
	printf( "i cannot explain command line.\n" );


L_MAINEND:
	//if( IsOsWin() )
	//{
	//	int i;
	//	//system("pause");
	//	i = WFile::run_exe("pause");
	//}
	//
	WThrd::tr_sleep( 1 );

	return 0;
}





