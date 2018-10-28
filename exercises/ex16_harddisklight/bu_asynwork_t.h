
#ifndef K1__bu_asynwork_t_H
#define K1__bu_asynwork_t_H


#include "2.h"



//
class bu_asynwork_t : public WThrd
{
private:
	WNava  m_para;
	void (bu_asynwork_t::*m_f)();	// ´¦Àíº¯Êý 

private:
	virtual int tr_on_user_run();

public:
	bu_asynwork_t();
	virtual ~bu_asynwork_t();

public:
	static 
	void Do_demo( std::string s1 );
	void Do_demo_m();
	
	static 
	void DoPf( void (*pf)() );
	void DoPf_m();


};





#endif



