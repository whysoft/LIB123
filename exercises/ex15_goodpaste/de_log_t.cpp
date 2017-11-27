//
#include "2.h"
#include "de_log_t.h"


//

de_log4_t  *gp_log;



//
de_log4_t::de_log4_t()
{
}


//
de_log4_t::~de_log4_t()
{
	while( GetTasksSize() )
	{
		WThrd::tr_sleep(1);
	}
}


 
//
void de_log4_t::LogPrintStr( const std::string & ss )
{
	//return;

	if(0)
	{
		std::string *p;
		
		p = new std::string(ss);

		printf( "%s\n", ss.c_str() );

		this->PostTask( p, 0 );
	}
	else
	{
		printf( "%s\n", ss.c_str() );

		this->WriteStr( ss );
	}
}


//
void de_log4_t::OnRunTask( PLogTaskType_t t ) 
{
	this->WriteStr( *t );
	delete t;
}




