
//
//#一段中文注释	

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
		std::string strConn;
		tbool rc;

		if( IsOsWin() )
		{
			strConn = "com=24;start=1;stop=1;speed=19200;parity=E;datalen=8;timeoutsec=0.50;";
		}
		else
		{
			//strConn = "com=ttyUSB0;start=1;stop=1;speed=19200;parity=E;datalen=8;timeoutsec=0.50;";
			strConn = "com=ttyTEST0;start=1;stop=1;speed=19200;parity=E;datalen=8;timeoutsec=0.50;";
		}
		 
		rc = uart.Conn( strConn );

		if( !rc )
		{
			std::cout << "cannot open uart." << std::endl;
			std::cout << strConn << std::endl;
			goto L_MAINEND;
		}

		std::cout << "open uart ok. " << std::endl;
		std::cout << strConn << std::endl;

		//01 03 01 01 00 01 D4 36
		//01 06 01 01 00 01 18 36
		while(1)
		{
			SCake ck;
			SCake ck2;
			unsigned char *p;
			std::string s1;
			char sz1[1024];

			rc = uart.recv_len( ck, 1 );
			if( ck.len() != 1 ) continue;
			p = (unsigned char *)ck.buf();
			if( *p != 0x01 ) continue;

			rc = uart.recv_len( ck, 1 );
			if( ck.len() != 1 ) continue;
			p = (unsigned char *)ck.buf();
			if( *p == 0x06 )
			{
				int iReg6Name;
				int iReg6Val(0);

				// reg high low
				rc = uart.recv_len( ck, 6 );
				if( ck.len() != 6 ) continue;
				p = (unsigned char *)ck.buf();
				iReg6Name = *p;
				iReg6Name <<= 8;
				iReg6Name += p[1]; 
				iReg6Val = p[2];
				iReg6Val <<= 8;
				iReg6Val += p[3]; 

				s1 = "01 06 ";
				ck2.UnSeri3( s1 );
				ck2.append( ck );
				p = (unsigned char *)ck2.buf() + ck2.len() - 2;
				p[0] = 0xc7;
				p[1] = 0xc8;

				std::cout << __LINE__ << "\t" << ck2.Seri_S() << "\t";
				uart.send_bin( ck2 );

				if( iReg6Name == 0x0101 )
				{
					std::cout << "进门 " << iReg6Val;
				}

				if( iReg6Name == 0x0102 )
				{
					std::cout << "出门 " << iReg6Val;
				}

				std::cout << std::endl;

				continue;
			}

			if( *p == 0x03 )
			{
				int iRegName;
				int iRegLen;
				int iRegVal(0);
				tuint8 *prH;
				tuint8 *prL;

				prL = (tuint8*)(&iRegVal);
				prH = prL + 1;

				// reg high low
				rc = uart.recv_len( ck, 2 );
				if( ck.len() != 2 ) continue;
				p = (unsigned char *)ck.buf();
				iRegName = *p;
				iRegName <<= 8;
				iRegName += p[1]; 

				// len high low, crc
				rc = uart.recv_len( ck, 4 );
				if( ck.len() != 4 ) continue;
				p = (unsigned char *)ck.buf();
				iRegLen = 0;
				iRegLen <<= 8;
				iRegLen += p[1];
				iRegLen *= 2;

				if( iRegName == 0xA205 ) iRegVal = 0x0001;
				if( iRegName == 0xA206 ) iRegVal = 0x0101;

				if( iRegLen == 0x02 )
				{
					//回复	
					sprintf( sz1, "01 03 %02x %02x %02x a5 a5", (int)iRegLen, (int)(*prH), (int)(*prL) ); 
					ck2.UnSeri3( sz1 );
				}
				else
				{
					sprintf( sz1, "01 03 %02x ", (int)iRegLen ); 
					ck2.UnSeri3( sz1 );
					for( int j = 0; j < iRegLen; j++ )
					{
						ck.UnSeri3( "0a" );
						ck2.append( ck );
					}
					ck.UnSeri3( "b5 b5" );
					ck2.append( ck );
				}
			
				std::cout << __LINE__ << "\t" << ck2.Seri_S() << std::endl;
				uart.send_bin( ck2 );
				continue;
			}
		}//end while
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


