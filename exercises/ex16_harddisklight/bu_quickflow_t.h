
#ifndef K1__bu_quickflow_t_H
#define K1__bu_quickflow_t_H


#include "2.h"



//
class bu_quickflow_boy_t : public WThrd
{
public:
	typedef tuint64  qf_counter_t;

private:
	WCrsc					m_QfLck;
	volatile qf_counter_t	m_iQf;
	volatile double			m_dStep;

public:
	bu_quickflow_boy_t();
	virtual ~bu_quickflow_boy_t(){ tr_destruct(); }

public:
	void GetQf( qf_counter_t & a );		// 当前 QF写入a中	
	tbool IsLongQf( qf_counter_t a, double dSec ); // 当前QF比起a来说，已经 是一个足够长的时间段了	 
	static int GetUpNum();
	virtual int tr_on_user_run();
};





//=============================


//
class bu_quickflow_t 
{
	bu_quickflow_boy_t::qf_counter_t  m_now;

public:
	bu_quickflow_t();
	~bu_quickflow_t(){ }

public:
	tbool IsTimeout( double fSec );  
};







#endif



