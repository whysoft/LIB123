
#ifndef env_t_H
#define env_t_H

#include "2.h"
//#include "de_log_t.h"



class env_t : public WThrd 
{
public:
	std::string		m_strName;
	std::string		m_strVer;
	std::string		m_strHelp;
	
	WNava	m_nvCmdLn;

	SDB_t<a_mates_t>	m_ma;

public:
	env_t();
	virtual ~env_t();
	
	virtual int tr_on_user_run();

};



extern env_t  *gp_env;



#endif



