
#ifndef env_t_H
#define env_t_H

#include "2.h"
#include "a_goodtbl_t.h"



class env_t : public WThrd 
{
public:
	std::string		m_strName;
	std::string		m_strVer;
	std::string		m_strHelp;
	
	WNava	m_nvCmdLn;

public:
	SDB_t<a_goodtbl_t>	m_gt;

public:
	env_t();
	virtual ~env_t();
	
	virtual int tr_on_user_run();

};



extern env_t  *gp_env;






////////////////////////////////////////////////////////////////////////////////////////////



// ter  ¼ì²â½áÊø±ê¼Ç
class cli_ter : public WThrd 
{
public:

public:
	cli_ter();
	virtual ~cli_ter();
	
	virtual void tr_on_pre_thrd();
	virtual int tr_on_user_run();
};






#endif



