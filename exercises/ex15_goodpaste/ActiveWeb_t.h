
#pragma once


#include "2.h"



//
class ActiveWeb_t : public AFWEB02::AWeb_t
{
	std::string Get_StepCountstr();

public:
	virtual void On_flow2( int *pstate );
	//virtual tbool On_StaticFlow();
 
};




