
#ifndef bu_actweb_t_H
#define bu_actweb_t_H


#include "2.h"
#include "bu_actweb_base1_t.h"




//
class bu_actweb_t : public bu_actweb_base1_t
{
public:
	bu_actweb_t();
	virtual ~bu_actweb_t();

public:
	virtual void OnGet( const std::string &strFn , WNava &para , const std::string &strWholePara );

public:
	static tbool NewActweb( tuint16 iport , tuint16 *pPortOut = NULL );
};









#endif

