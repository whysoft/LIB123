
#ifndef ga_t_H
#define ga_t_H

#include "2.h"
//#include "de_log_t.h"



#define HOUSESTR( lbbx_addr, name )  ( "formid=" + SStrf::sltoa(__LINE__) + "#" + SStrf::b2s(lbbx_addr) + name )




class ga_t 
{
private:
	WCrsc	m_lck;
	std::map< std::string , long > 	m_mAttribute;


public:
	ga_t();
	virtual ~ga_t();
	
	void Set( std::string strName, long value );
	long Get( std::string strName );
};



extern ga_t  *gp_ga;






#endif



