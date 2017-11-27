
#include "2.h"
#include "env_t.h"
#include "ActiveWeb_t.h"

#include "On_flow2.xpp"




//
std::string ActiveWeb_t::Get_StepCountstr()
{
	return ( "(" + SStrf::sultoa(m_pafdata->m_env0.m_StepCount) + ")" );
}



#if 0
void ActiveWeb_t::On_flow2( int *pstate )
{
	WebFormBegin( "子网列表" );

	//MYAUTOLOCK( g_pss15tbl->m_Lck );

	//WebAddTable2Begin();
	//
	//WebAddTable2Row( g_pss15tbl->m_vecSubnet );
	//
	//WebAddTable2End();

	//WebAddTable2( g_pss15tbl->m_vecSubnet_sc, g_pss15tbl->m_vecSubnet_cc );

}
#endif




#if 0
tbool ActiveWeb_t::On_StaticFlow()
{
	return 0;

	this->m_WebFormBeginDoneFlag = 1;

		std::string strOut;

		strOut = "HTTP/1.0 200 OK\r\n";
		strOut += "Server: NotApache/" + wl::SDte::GetNow().ReadStringPack() + "\r\n";
		strOut += "Cache-Control: no-cache\r\n";
		strOut += "Pragma: no-cache\r\n";

		//strOut += "Content-Type: image/jpg; charset=gb2312\r\n";
		if( m_RawMode )
		{
			strOut += "Content-Type: text/plain; charset=gb2312\r\n";
		}
		else
		{
			strOut += "Content-Type: text/html; charset=gb2312\r\n";
		}

		strOut += "Connection: close\r\n";
		strOut += "\r\n";

	WebSendString( strOut );

	WebSendString( "{JSON(JavaScript Object Notation, JS 对象标记) " );


	return 1;
}
#endif








