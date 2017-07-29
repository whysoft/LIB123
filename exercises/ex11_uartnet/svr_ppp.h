
#ifndef svr_ppp_H
#define svr_ppp_H

#include "2.h"
//#include "de_log_t.h"



// ppp
class svr_ppp : public WThrd 
{
public:

public:
	svr_ppp();
	virtual ~svr_ppp();
	
	virtual void tr_on_pre_thrd();
	virtual int tr_on_user_run();
};



// dns
class svr_dns : public WThrd 
{
public:

public:
	svr_dns();
	virtual ~svr_dns();
	
	virtual void tr_on_pre_thrd();
	virtual int tr_on_user_run();
};



// route
class svr_route : public WThrd 
{
public:

public:
	svr_route();
	virtual ~svr_route();
	
	virtual void tr_on_pre_thrd();
	virtual int tr_on_user_run();
};



// myip
class svr_myip : public WThrd 
{
public:

public:
	svr_myip();
	virtual ~svr_myip();
	
	virtual void tr_on_pre_thrd();
	virtual int tr_on_user_run();
};



// iptables
class svr_iptables : public WThrd 
{
public:

public:
	svr_iptables();
	virtual ~svr_iptables();
	
	virtual void tr_on_pre_thrd();
	virtual int tr_on_user_run();
};




// ipforward
class svr_ipforward : public WThrd 
{
public:

public:
	svr_ipforward();
	virtual ~svr_ipforward();
	
	virtual void tr_on_pre_thrd();
	virtual int tr_on_user_run();
};




// reboot
class svr_reboot : public WThrd 
{
public:

public:
	svr_reboot();
	virtual ~svr_reboot();
	
	virtual void tr_on_pre_thrd();
	virtual int tr_on_user_run();
};





#endif



