//
#include "2.h"
#include "env_t.h"



//
int main(int argc, char* argv[])
{
	wl::WComeliCell uart;
	SCake ck;

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


	if(1)
	{
		tbool rc;

		//rc = uart.Conn( "com=ttyS0;start=1;stop=1;speed=9600;parity=N;datalen=8;timeoutsec=0.50;" );
		rc = uart.Conn( "com=ttyUSB0;start=1;stop=1;speed=9600;parity=N;datalen=8;timeoutsec=1.50;" );

		if( IsOsWin() )
		{
			rc = uart.Conn( "com=COM5;start=1;stop=1;speed=9600;parity=N;datalen=8;timeoutsec=0.50;" );
		}

		if( !rc )
		{
			std::cout << "cannot open uart." << std::endl;
			goto L_MAINEND;
		}

		while(1)
		{
			uart.recv_ln( ck , "\r\n" );
		
			if( ck.len() )
			{
				std::string s1;

				s1 = ck.mk_str();
				printf( "`%s`", s1.c_str() );
				std::reverse( s1.begin(), s1.end() );
				printf( "`%s`\n", s1.c_str() );

			}

		}

	}

	//show error msg, ���ܽ��͵������в�����	 
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


