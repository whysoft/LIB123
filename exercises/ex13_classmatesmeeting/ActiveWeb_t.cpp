
#include "2.h"
#include "env_t.h"
#include "ActiveWeb_t.h"
#include "On_flow2.xpp"



//
//void ActiveWeb_t::On_flow2( int *pstate )
//{
//	WebFormBegin( "×ÓÍøÁÐ±í" );
//
//	//MYAUTOLOCK( g_pss15tbl->m_Lck );
//
//	//WebAddTable2Begin();
//	//
//	//WebAddTable2Row( g_pss15tbl->m_vecSubnet );
//	//
//	//WebAddTable2End();
//
//	//WebAddTable2( g_pss15tbl->m_vecSubnet_sc, g_pss15tbl->m_vecSubnet_cc );
//
//}



	
//
std::string ActiveWeb_t::Get_StepCountstr()
{
	return ( "(" + SStrf::sultoa(m_pafdata->m_env0.m_StepCount) + ")" );
}







