
#ifndef K1_de_log_t_H
#define K1_de_log_t_H

#include "2.h"


typedef std::string * PLogTaskType_t;


//  
class de_log4_t : public LOG4_t< 5 > , public WIdleThrd< PLogTaskType_t >  
{
private:

public:
	de_log4_t();
	virtual ~de_log4_t();

public:
	void LogPrintStr( const std::string & ss );

	virtual void OnRunTask( PLogTaskType_t t );
};



extern de_log4_t  *gp_log;




#endif



