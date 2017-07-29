
#ifndef cli_ppp_H
#define cli_ppp_H

#include "2.h"
//#include "de_log_t.h"



// ppp
class cli_ppp : public WThrd 
{
public:

public:
	cli_ppp();
	virtual ~cli_ppp();
	
	virtual void tr_on_pre_thrd();
	virtual int tr_on_user_run();
};



// dns
class cli_dns : public WThrd 
{
public:

public:
	cli_dns();
	virtual ~cli_dns();
	
	virtual void tr_on_pre_thrd();
	virtual int tr_on_user_run();
};



// route
class cli_route : public WThrd 
{
public:

public:
	cli_route();
	virtual ~cli_route();
	
	virtual void tr_on_pre_thrd();
	virtual int tr_on_user_run();
};



// myip
class cli_myip : public WThrd 
{
public:

public:
	cli_myip();
	virtual ~cli_myip();
	
	virtual void tr_on_pre_thrd();
	virtual int tr_on_user_run();
};



// iptables
class cli_iptables : public WThrd 
{
public:

public:
	cli_iptables();
	virtual ~cli_iptables();
	
	virtual void tr_on_pre_thrd();
	virtual int tr_on_user_run();
};




// ipforward
class cli_ipforward : public WThrd 
{
public:

public:
	cli_ipforward();
	virtual ~cli_ipforward();
	
	virtual void tr_on_pre_thrd();
	virtual int tr_on_user_run();
};




// reboot
class cli_reboot : public WThrd 
{
public:

public:
	cli_reboot();
	virtual ~cli_reboot();
	
	virtual void tr_on_pre_thrd();
	virtual int tr_on_user_run();
};





#endif



