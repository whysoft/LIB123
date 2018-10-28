
#include "2.h"
#include "env_t.h"
#include "bu_actweb_base1_t.h"



//
bu_actweb_base1_t::bu_actweb_base1_t()
{
}


//
bu_actweb_base1_t::~bu_actweb_base1_t()
{
}


//
////	 
//tbool bu_actweb_base1_t::On_StaticFlow()
//{
//	//return 0;
//
//	//this->m_WebFormBeginDoneFlag = 1;
//
//	//	std::string strOut;
//
//	//	strOut = "HTTP/1.0 200 OK\r\n";
//	//	strOut += "Server: NotApache/" + wl::SDte::GetNow().ReadStringPack() + "\r\n";
//	//	strOut += "Cache-Control: no-cache\r\n";
//	//	strOut += "Pragma: no-cache\r\n";
//
//	//	//strOut += "Content-Type: image/jpg; charset=gb2312\r\n";
//	//	if( m_RawMode )
//	//	{
//	//		strOut += "Content-Type: text/plain; charset=gb2312\r\n";
//	//	}
//	//	else
//	//	{
//	//		strOut += "Content-Type: text/html; charset=gb2312\r\n";
//	//	}
//
//	//	strOut += "Connection: close\r\n";
//	//	strOut += "\r\n";
//
//	//WebSendString( strOut );
//
//	//WebSendString( "{JSON(JavaScript Object Notation, JS 对象标记) " );
//
//	std::string s1, s2;
//	std::string::size_type i;
//
//	s1 = this->m_strUPfn;
//	i = s1.find_last_of( '/' );
//
//	if( i != std::string::npos ) s2 = s1.c_str() + i + 1; 
//
//	s1 = SStrvs::vsa_get( s2, std::string("?"), 0, 0 );
//
//	this->OnGet( s1 , this->m_nvHTTPGET );
//
//	return 1;
//}
//	


//	 
void bu_actweb_base1_t::RtnWebContent( std::string strType, std::string strContent, SCake *pck /*= NULL*/ )
{
	if( strType == "RAW" )
	{
		if( !strContent.empty() )
		{
			m_tSvr.send_str( strContent );
		}

		if( pck && pck->len() )
			m_tSvr.send_bin( *pck );
	}
	else
	{
		std::string strOut;

		strOut = "HTTP/1.0 200 OK\r\n";
		strOut += "Server: NotApache/" + SDte::GetNow().ReadStringPack() + WFile::MkRUStr()+ "\r\n";
		strOut += "Cache-Control: no-cache\r\n";
		strOut += "Pragma: no-cache\r\n";

		//strOut += "Content-Type: text/plain; charset=gb2312\r\n";
		//strOut += "Content-Type: text/html; charset=gb2312\r\n";
		//strOut += "Content-Type: image/jpg; charset=gb2312\r\n";
		if( strType == "" )
		{
			strOut += "Content-Type: text/plain; charset=gb2312\r\n";
		}
		else
		{
			strOut += "Content-Type: " + strType + "; charset=gb2312\r\n";
		}

		if( pck && pck->len() )
		{
			strOut += "Content-Length: " + SStrf::sltoa( (int)pck->len() ) + "\r\n";
		}

		strOut += "Connection: close\r\n";
		strOut += "\r\n";
		m_tSvr.send_str( strOut );

		if( pck && pck->len() )
		{
			m_tSvr.send_bin( *pck );
		}
		else
		{
			m_tSvr.send_str( strContent );
		}
	}
}


//	 
void bu_actweb_base1_t::OnGet( const std::string &strFn , WNava &para , const std::string &strWholePara )
{
	// judge Fn and para

	// send RtnWebContent

}

 

