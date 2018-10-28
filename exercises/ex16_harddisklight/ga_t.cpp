//
#include "2.h"
#include "ga_t.h"


ga_t  *gp_ga;



	
//
ga_t::ga_t()	
{

}




//
ga_t::~ga_t()	
{

}



//
void ga_t::Set( std::string strName, long value )
{
	MYAUTOLOCK(m_lck); 

	m_mAttribute[ strName ] = value;
}



//
long ga_t::Get( std::string strName )
{
	MYAUTOLOCK(m_lck); 

	return m_mAttribute[ strName ];
}









