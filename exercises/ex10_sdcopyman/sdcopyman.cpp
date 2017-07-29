
//
#include "2.h"
#include "env_t.h"





class sd_writer_t : public WThrd 
{
public:
	volatile int   m_iDdState;
	 

public:
	sd_writer_t()
	{
		m_iDdState = 0;
	}


	virtual ~sd_writer_t()
	{
	}

	
	virtual int tr_on_user_run()
	{
		WFile fl;
		
		WThrd::tr_sleep(3);

		fl.bind( "/dev/sda" );
		if( fl.exists() )
		{
			m_iDdState = 1;

			WFile::run_exe( "dd if=/dev/mmcblk0 of=/dev/sda bs=15123123" );
		}

		m_iDdState = 0;

		while( fl.exists() )
		{
			WThrd::tr_sleep(2);
		}

		return 1;
	}

};




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


	if(1)
	{
		WComeliCell uart;
		tbool rc;
		double totalf;
		double currentf;
		sd_writer_t  sd_writer;
		char szbuf[222];
	
		sd_writer.tr_open();

		WThrd::tr_sleep(3);
		
		rc = uart.Conn( "com=ttyS0;start=1;stop=1;speed=9600;parity=N;datalen=8;timeoutsec=0.50;" );

		//if( IsOsWin() )
		//{
		//	rc = uart.Conn( "com=COM5;start=1;stop=1;speed=9600;parity=N;datalen=8;timeoutsec=0.50;" );
		//}


		//ATCLS
		sprintf( szbuf, "ATCLS;" );
		uart.send_str( szbuf );
		WThrd::tr_sleepu(0.1);


		while(1)
		{
TOTAL_BEGIN:
			totalf = 16E9;
			currentf = 0;
	
			WThrd::tr_sleepu(0.6);

			//if( !rc )
			//{
			//	std::cout << "cannot open uart." << std::endl;
			//	goto L_MAINEND;
			//}
			
			if( sd_writer.m_iDdState == 0 )
			{
				//显示日期
				sprintf( szbuf, "ATS+0,0,%s;", SDte::GetNow().ReadStringPack().c_str() );
				uart.send_str( szbuf );
				WThrd::tr_sleepu(0.1);

				//显示ip
				WFile fl;
				std::string strIp;

				fl.bind( "/tmp/1.txt" );
				fl.erase();

				WFile::run_exe( "ifconfig wlan0 |grep \"inet addr\"| cut -f 2 -d \":\"|cut -f 1 -d \" \">/tmp/1.txt" );

				fl.read_str( strIp );
				wl::SStrf::strim( strIp );
				sprintf( szbuf, "ATS+1,0,%s RDY;", strIp.c_str() );
				uart.send_str( szbuf );
				WThrd::tr_sleepu(0.1);

				goto TOTAL_BEGIN;
			}

			if( 1 )
			{
				sprintf( szbuf, "ATS+1,0,%s;", std::string(16,' ').c_str() );
				uart.send_str( szbuf );
				WThrd::tr_sleepu(0.1);
			}

			while(1)
			{
				WThrd::tr_sleepu(0.8); 

				if( sd_writer.m_iDdState == 0 ) break;
				 
				currentf += 9.9E6;
				 
							
				//显示日期
				sprintf( szbuf, "ATS+0,0,%s;", SDte::GetNow().ReadStringPack().c_str() );
				uart.send_str( szbuf );
				WThrd::tr_sleepu(0.1);

				//显示进度	
				if( wl::SStrf::rand1() < 0.01 )
				{
					sprintf( szbuf, "ATS+1,0,%s;", std::string(16,' ').c_str() );
					uart.send_str( szbuf );
					WThrd::tr_sleepu(0.1);
				}

				sprintf( szbuf, "ATS+1,0,%.2fpercent;", currentf / totalf * 100 );
				uart.send_str( szbuf );
				WThrd::tr_sleepu(0.1);
			}
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


