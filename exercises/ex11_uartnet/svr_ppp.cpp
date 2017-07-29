//
#include "2.h"
#include "env_t.h"
#include "svr_ppp.h"



// ppp
	
//
svr_ppp::svr_ppp()	
{
}



//
svr_ppp::~svr_ppp()	
{
}



//
void svr_ppp::tr_on_pre_thrd()
{
	WThrd::tr_sleep( 9 );
 
	copy_data_2_file( "ppp_server.txt" , "/etc/ppp/options.ttyS2" );

	return;
}



//
int svr_ppp::tr_on_user_run()
{
	WThrd::tr_sleep( 5 );
 
	WFile::run_exe( "/usr/sbin/pppd /dev/ttyS2 nodetach" );

	return 1;
}





// dns

//
svr_dns::svr_dns()	
{
}



//
svr_dns::~svr_dns()	
{
}



//
void svr_dns::tr_on_pre_thrd()
{
	WThrd::tr_sleep( 33 );
 
	return;
}



//
int svr_dns::tr_on_user_run()
{
	WThrd::tr_sleep( 33 );
 
	copy_data_2_file( "resolv.conf.txt" , "/etc/resolv.conf" );
	
	return 1;
}






// route

//
svr_route::svr_route()	
{
}



//
svr_route::~svr_route()	
{
}



//
void svr_route::tr_on_pre_thrd()
{

	WThrd::tr_sleep( 33 );
 
	return;
}



//
int svr_route::tr_on_user_run()
{
	return 0;
	WThrd::tr_sleep( 133 );
	WFile::run_exe( "route delete default" );
 
	WThrd::tr_sleep( 1 );
	WFile::run_exe( "route add default gw 192.168.41.1 dev wlan5" );
 
	WThrd::tr_sleep( 133 );
	return 0;
}







// myip

//
svr_myip::svr_myip()	
{
}



//
svr_myip::~svr_myip()	
{
}



//
void svr_myip::tr_on_pre_thrd()
{

	WThrd::tr_sleep( 33 );
 
	return;
}



//
int svr_myip::tr_on_user_run()
{
	WThrd::tr_sleep( 33 );
 
	return 0;
}





// iptables

//
svr_iptables::svr_iptables()	
{
}



//
svr_iptables::~svr_iptables()	
{
}



//
void svr_iptables::tr_on_pre_thrd()
{
	WThrd::tr_sleep( 33 );

	WFile::run_exe( "sudo iptables -t nat -A POSTROUTING -o wlan5 -j MASQUERADE" );
	WFile::run_exe( "sudo iptables -A FORWARD -i ppp0 -o wlan5 -j ACCEPT" ); 

	return;
}



//
int svr_iptables::tr_on_user_run()
{
	WThrd::tr_sleep( 33 );
 
	return 0;
}






// ipforward

//
svr_ipforward::svr_ipforward()	
{
}



//
svr_ipforward::~svr_ipforward()	
{
}



//
void svr_ipforward::tr_on_pre_thrd()
{
	WThrd::tr_sleep( 33 );
 
	return;
}



//
int svr_ipforward::tr_on_user_run()
{
	WFile::run_exe( "echo \"1\">/proc/sys/net/ipv4/ip_forward" );


	WThrd::tr_sleep( 233 );
 
	return 1;
}







// reboot

//
svr_reboot::svr_reboot()	
{
}



//
svr_reboot::~svr_reboot()	
{
}


static int counter;

//
void svr_reboot::tr_on_pre_thrd()
{
	WThrd::tr_sleep( 33 );
 
	counter = 0;
	return;
}



//
int svr_reboot::tr_on_user_run()
{
	WThrd::tr_sleep( 66 );
 
	wl::WTcpCellc tc;

	if( !tc.Conn( "qq.com", 80 ) )
	{
		counter ++;
	}
	else
		counter = 0;

	if( counter > 2 )
		WFile::run_exe( "reboot" );

	return 1;
}





