
#include "bu_asynwork_t.h"



//
bu_asynwork_t::bu_asynwork_t() 
{
	m_f = NULL;
}


//
bu_asynwork_t:: ~bu_asynwork_t()
{
	tr_destruct();
}



// 
int bu_asynwork_t::tr_on_user_run()
{
	if(m_f) (this->*m_f)();
	return 0;
}



//-----------------
//-----------------

//
void bu_asynwork_t::Do_demo( std::string s1 )
{
	bu_asynwork_t  *paw;

	SStrf::newobjptr(paw);
	paw->m_f = &bu_asynwork_t::Do_demo_m;

	paw->m_para.let( "a", s1 );

	paw->tr_openx();
}


//
void bu_asynwork_t::Do_demo_m()
{
	std::string s1;

	s1 = m_para.get( "a" );

	WThrd::tr_sleepu( 2.7 );
	
	printf( "%s\n", s1.c_str() );

}

 
//-----------------


//
void bu_asynwork_t::DoPf( void (*pf)() )
{
	bu_asynwork_t  *paw;

	SStrf::newobjptr(paw);
	paw->m_f = &bu_asynwork_t::DoPf_m;
	
	paw->m_para.let( "a", SStrf::b2s(pf) );

	paw->tr_openx();
}

//
void bu_asynwork_t::DoPf_m()
{
	void (*pf)();

	SStrf::s2b( m_para.get("a"), pf );

	pf();
}


 
//-----------------





