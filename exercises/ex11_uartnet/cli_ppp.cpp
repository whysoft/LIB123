//
#include "2.h"
#include "env_t.h"
#include "cli_ppp.h"



// ppp
	
//
cli_ppp::cli_ppp()	
{
}



//
cli_ppp::~cli_ppp()	
{
}



//
void cli_ppp::tr_on_pre_thrd()
{
	WThrd::tr_sleep( 9 );
 
	copy_data_2_file( "ppp_client.txt" , "/etc/ppp/options.ttyS2" );

	return;
}




//
int cli_ppp::tr_on_user_run()
{
	WThrd::tr_sleep( 5 );
 
	WFile::run_exe( "/usr/sbin/pppd /dev/ttyS2 nodetach" );

	return 1;
}






// dns

//
cli_dns::cli_dns()	
{
}



//
cli_dns::~cli_dns()	
{
}



//
void cli_dns::tr_on_pre_thrd()
{
	WThrd::tr_sleep( 33 );
 
	return;
}



//
int cli_dns::tr_on_user_run()
{
	WThrd::tr_sleep( 33 );
	
	copy_data_2_file( "resolv.conf.txt" , "/etc/resolv.conf" );
 
	return 1;
}






// route

//
cli_route::cli_route()	
{
}



//
cli_route::~cli_route()	
{
}



//
void cli_route::tr_on_pre_thrd()
{

	WThrd::tr_sleep( 33 );
 
	return;
}



//
int cli_route::tr_on_user_run()
{
	WThrd::tr_sleep( 133 );
	WFile::run_exe( "route delete default" );
 
	WThrd::tr_sleep( 1 );
	WFile::run_exe( "route add default gw 192.168.11.1 dev ppp0" );
 
	WThrd::tr_sleep( 133 );
	return 1;
}







// myip

//
cli_myip::cli_myip()	
{
}



//
cli_myip::~cli_myip()	
{
}



//
void cli_myip::tr_on_pre_thrd()
{
	WThrd::tr_sleep( 33 );
 
	return;
}



//
int cli_myip::tr_on_user_run()
{
	WThrd::tr_sleep( 33 );
 
	WFile::run_exe( "ifconfig eth0 192.168.3.1" );
	WThrd::tr_sleep( 633 );
	
	return 0;
}





// iptables

//
cli_iptables::cli_iptables()	
{
}



//
cli_iptables::~cli_iptables()	
{
}



//
void cli_iptables::tr_on_pre_thrd()
{
	WThrd::tr_sleep( 33 );

	WFile::run_exe( "sudo iptables -t nat -A POSTROUTING -o ppp0 -j MASQUERADE" );
	WFile::run_exe( "sudo iptables -A FORWARD -i eth0 -o ppp0 -j ACCEPT" );
 
	return;
}



//
int cli_iptables::tr_on_user_run()
{
	WThrd::tr_sleep( 33 );
	
	return 0;
}






// ipforward

//
cli_ipforward::cli_ipforward()	
{
}



//
cli_ipforward::~cli_ipforward()	
{
}



//
void cli_ipforward::tr_on_pre_thrd()
{

	WThrd::tr_sleep( 33 );
 
	return;
}



//
int cli_ipforward::tr_on_user_run()
{
	WFile::run_exe( "echo \"1\">/proc/sys/net/ipv4/ip_forward" );


	WThrd::tr_sleep( 233 );
 
	return 1;
}







// reboot

//
cli_reboot::cli_reboot()	
{
}



//
cli_reboot::~cli_reboot()	
{
}



//
void cli_reboot::tr_on_pre_thrd()
{

	WThrd::tr_sleep( 33 );
 
	return;
}



//
int cli_reboot::tr_on_user_run()
{
	WThrd::tr_sleep( 33 );
 
	return 0;
}







// cli_ter

//
cli_ter::cli_ter()	
{
}



//
cli_ter::~cli_ter()	
{
}



//
void cli_ter::tr_on_pre_thrd()
{
	WThrd::tr_sleep( 5 );
 
	return;
}



//
int cli_ter::tr_on_user_run()
{
	WFile f;
	
	f.bind( "ter.txt" ); // exit the process
	
	if( f.exists() )
	{
		f.erase();

		exit( 0 );
	}



	WThrd::tr_sleep( 6 );
 
	return 1;
}




