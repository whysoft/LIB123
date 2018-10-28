
#include "bu_quickflow_t.h"



//
bu_quickflow_boy_t::bu_quickflow_boy_t()
{
	m_iQf = 0;
	m_dStep = 0.333;
}


 
//
void bu_quickflow_boy_t::GetQf( qf_counter_t & a ) 
{
	MYAUTOLOCK(m_QfLck);

	a = m_iQf;
}


//
tbool bu_quickflow_boy_t::IsLongQf( qf_counter_t a, double dSec )
{
	MYAUTOLOCK(m_QfLck);

	if( (m_iQf - a) * m_dStep >= dSec ) return 1;

	return 0;
}

	

// 
int bu_quickflow_boy_t::tr_on_user_run()
{
	WThrd::tr_sleep( 0, m_dStep );
	if(1)
	{
		MYAUTOLOCK(m_QfLck);	

		m_iQf++;
	}
	return 1;
}




//=============================


static bu_quickflow_boy_t  *iv_pQuickflowboy = NULL;



//
bu_quickflow_t::bu_quickflow_t()
{
	if( iv_pQuickflowboy == NULL )
	{
		iv_pQuickflowboy = new bu_quickflow_boy_t();
		iv_pQuickflowboy->tr_openx();
	}

	iv_pQuickflowboy->GetQf( m_now );
}

 

//
tbool bu_quickflow_t::IsTimeout( double fSec )
{
	if( iv_pQuickflowboy->IsLongQf( m_now, fSec ) ) return 1;

	return 0;
}


