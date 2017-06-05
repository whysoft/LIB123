
#include "2.h"




class TestCells
{
public:

	WTcpListener m_tLsn;
	WTcpCells    m_ts;

	void foo()
	{
		SCake ck;
		
		m_tLsn.Listen( 2220 );

		printf( "listen 2220\n");

		m_ts.Conn( m_tLsn );

		printf( "some one connected. ip=%s\n", m_ts.GetRemoteIPAddress().c_str() );

		while( m_ts.recv_len( ck, 1 ) )
		{
			char c, c2;
			std::string strByte;
			c2 = c = *ck.buf();
			SStrf::byte2binstr( c, strByte );
			std::reverse( strByte.begin(), strByte.end() );
			printf( "%i\t0x%02X\t%s\n", c, c2, strByte.c_str() );

		}

		printf( "bye-bye.\n");
	}

	
	void foo_sendtest()
	{
		WTcpCellc cc;
		SCake ck;

		if( cc.Conn( "127.0.0.1:2220" ) )
		{
			cc.send_str("abcdefg\n");
			cc.DisConn();
		}

		printf( "bye-bye.\n");
	}

};


//
void test_send_4003()
{
	WTcpCellc  tcpc;
	std::string strFn;
	SCake ck1;
	SFile fl;

	strFn = "Para4003.txt";
	if( !fl.exists() )
	{
		printf( "文件不存在。\n" );
		return ;
	}
	fl.bind( strFn );
	fl.read( ck1 );
	if( !tcpc.Conn("127.0.0.1:6001") )
	{
		printf( "无法连。\n" );
		return ;
	}
	tcpc.send_bin( ck1 );
	printf( "文件长度：%d。已发出。\n" , (int)ck1.len() );
	return ;
}



//
int main(int argc, char* argv[])
{
	test_send_4003();
	system("pause");

	return 0;
}
  

