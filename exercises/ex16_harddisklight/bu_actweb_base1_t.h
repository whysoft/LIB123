
#ifndef bu_actweb_base1_t_H
#define bu_actweb_base1_t_H


#include "2.h"




//
class bu_actweb_base1_t : public AFWEB02::AWeb2_t
{
public:
	bu_actweb_base1_t();
	virtual ~bu_actweb_base1_t();

public:
	void RtnWebContent( std::string strType, std::string strContent, SCake *pck = NULL );
	
	virtual void OnGet( const std::string &strFn , WNava &para , const std::string &strWholePara );
};









#endif

