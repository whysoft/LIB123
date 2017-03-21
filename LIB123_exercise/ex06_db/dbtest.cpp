// dbtest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "2.h"


int _tmain(int argc, _TCHAR* argv[])
{
	WCsrAdoTbl ct;
	std::string strcnn;
	std::string strtbl;
	WCsrAdoTbl::rowTYPE r;

	CoInitializeEx(NULL,COINIT_MULTITHREADED);

	strcnn = "Provider=MSDASQL.1;Persist Security Info=False;Data Source=aaaa";

	if( !ct.OpenEnv( strcnn ) )
	{
		return 0;
	}

	strtbl = "select OperID from tb_operInfo  ";	 
	ct.OpenTbl( strtbl );
	
	while( ct.FetchRow( r ) )
	{
		std::copy( r.begin(), r.end(), std::ostream_iterator<std::string>(std::cout, " ") );
	}


	CoUninitialize();

	return 0;
}

