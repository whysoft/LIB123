//
#include "2.h"
#include "CJsonObject.h"



// 
bool IsOsWin()
{
#ifdef WINENV_
	return true;
#else
	return false;
#endif
}


 
std::string  v_strContent;


void test_json()
{
    std::string strValue;
    std::string s1;
    neb::CJsonObject oJson;

	strValue = " {"
				"\"timeout\":12.5,"
				"\"t2\":\"5\","
				"\"t3\":5,"
				"\"tt\":[]"
			   "}";

	oJson.Parse( strValue );
	s1 = oJson.ToString();
	std::cout << s1 << std::endl;

	double f;
	oJson.Get( "timeout", f );
	std::cout << f << std::endl;

	std::string s;
	oJson.Get( "t3", s );
	std::cout << s << std::endl;

    neb::CJsonObject oj2;

	for( int i = 0; i < 4; i++ )
	{
		oj2.Add( 234 + i );
	}

	oJson.Add( "tt4", oj2 );
  
	neb::CJsonObject oj3;

	for( int i = 0; i < 4; i++ )
	{
		neb::CJsonObject oj2;

		for( int i = 0; i < 4; i++ )
		{
			oj2.Add( 555 + i );
		}

		oj3.Add( oj2 );
	}

	oJson.Add( "tt5", oj3 );

	s1 = oJson.ToString();
	std::cout << s1 << std::endl;

	v_strContent = s1;
}



extern funcandy_t *gp_fc1;
funcandy_t *gp_fc1;



//
void test_web_recv_post()
{
	tbool rc;

	gp_fc1 = new funcandy_t;
	rc = gp_fc1->InitFlow( 8009 ); 
	printf( "gp_fc1 init, rc=%d,Port=%d\n", (int)rc, (int)8009 );

	//upload
	class _test_upload : public funcandy_t::item_t	  
	{
	public:
		_test_upload()
		{
			LinkFc( gp_fc1 );
		}

		virtual tbool lingy( const std::string &strFn , WNava &para , const std::string &strWholePara , funcandy_t::actwebele_t *pweb )
		{
			printf( "----%s---\n", pweb->m_tSvr.m_strRemoteIPAddress.c_str() );

			if( pweb->m_strCmdVerb != "POST" ) return 0;

			neb::CJsonObject oJson;
			std::string strRecv;
			std::string s1;

			pweb->ckPostBody.mk_str( strRecv );
			oJson.Parse( strRecv );

			s1 = oJson.ToString();
			std::cout << s1 << std::endl;
			
			pweb->RtnWebContent( "", s1 );  

			return 1;

			// return 0;
		}

	};
	_test_upload *p_test_upload = new _test_upload;
}



//
void test_web_send_post()
{
	std::string strAddr = "127.0.0.1:8009";  
	std::string strUniFn = "aaa"; 
	std::string strMethod = "POST";
	std::string strTxtType = "";
	std::string strContent = v_strContent;
	SCake		*pckBody = NULL ;
	std::string strRtn1;
	std::string *pstrRtn1 = &strRtn1;
	SCake		ckRtn2 ;
	SCake		*pckRtn2 = &ckRtn2 ;
	std::string strCommuCR = "\r\n";

	funcandy_t::WGet(   strAddr,
						strUniFn,
						strMethod,
						strTxtType,
						strContent,
						pckBody,
						pstrRtn1, 
						pckRtn2,
						strCommuCR );

	printf( "HEADER:\n" );
	printf( "%s:\n" , pstrRtn1->c_str() );


	printf( "BODY:\n" );
	printf( "%s:\n" , pckRtn2->mk_str().c_str() );
}



//
int main(int argc, char* argv[])
{
	test_json();
	test_web_recv_post();
	test_web_send_post();

	if( IsOsWin() ) system("pause");

	return 0;
}


