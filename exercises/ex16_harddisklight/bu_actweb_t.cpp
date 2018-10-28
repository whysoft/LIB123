
#include "2.h"
#include "env_t.h"
#include "bu_actweb_t.h"



//
bu_actweb_t::bu_actweb_t()
{
}


//
bu_actweb_t::~bu_actweb_t()
{
}





//	 
tbool bu_actweb_t::NewActweb( tuint16 iport , tuint16 *pPortOut /*= NULL*/ )
{
	return AFWEB02::AFlowMgr_t< bu_actweb_t >::NewFlow( iport, 0, pPortOut );
}



//	 
void bu_actweb_t::OnGet( const std::string &strFn , WNava &para , const std::string &strWholePara )
{
	// judge Fn and para

	//
	if( 1 )
	{
		std::string strOut;

		strOut = SStrf::sltoa( gp_env->m_Num );
		strOut += "\r\n\r\n";
		
		this->RtnWebContent( "RAW", strOut );

		return;
	}
 

	// 其它不识别的情况 ： send RtnWebContent
	
	std::string strOut;
	
	strOut = strFn;

	strOut += "{JSON(JavaScript Object Notation, JS 对象标记) ";

	this->RtnWebContent( "", strOut );

	return;
}

