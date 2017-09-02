//
#include "2.h"
#include "iostream"
#include "env_t.h"
#include "gfunc_md5.h"



#define MAKE_CURR_FULLFNAME (std::string(cstraFPath) + *it)

int main(int argc, char* argv[])
{
	
	std::cout << "long term precious BK. V1.11" << std::endl;
	Sleep(1234);

	//get working path
	CString cstrFPath = wl::WMsg::GetProcExeFilePathTS();
	CStringA cstraFPath = cstrFPath;


	//get all file list 
	wl::WFile wf;
	std::vector<std::string> vecSrcFileList;

	wf.ListAllFile( cstraFPath.GetString(), "*.*", vecSrcFileList );


	std::map<std::string,std::string> mapMd5GoodFn;

	for( std::vector<std::string>::iterator it = vecSrcFileList.begin();
		 it != vecSrcFileList.end();
		 ++it)
	{
		if( it->find( "19" ) == 0 || it->find( "20" ) == 0 || it->find( ".exe" ) == it->size() - 4 ) 
		{
			//GoodFn
			std::string t;
			mapMd5GoodFn[ t = md5str_file( MAKE_CURR_FULLFNAME ) ] = "a";
			std::cout << "calc md5: " << t << " " << *it << std::endl;
			continue;
		}
	}

	std::cout << std::endl;
	
	for( std::vector<std::string>::iterator it = vecSrcFileList.begin();
		 it != vecSrcFileList.end();
		 ++it)
	{
		std::string strNewFn;
		std::string strCmd;

		//skip list items with good filename format, begin with '20'
		if( it->find( "19" ) == 0 || it->find( "20" ) == 0 || it->find( ".exe" ) == it->size() - 4 ) 
		{
			//GoodFn
			continue;
		}

		//skip dup new files
		if( !mapMd5GoodFn[ md5str_file( MAKE_CURR_FULLFNAME ) ].empty() )
		{
			wl::WFile::erase(MAKE_CURR_FULLFNAME);
			std::cout << "erase " << MAKE_CURR_FULLFNAME << std::endl;
			continue;
		}


		//trim 0
		strNewFn = *it;

		wl::SStrf::striml( strNewFn, "0_" );
		if( strNewFn != *it )
		{
			strCmd = "rename \"" + MAKE_CURR_FULLFNAME + "\"  \"" + strNewFn + "\"";
			std::cout << strCmd << std::endl;
			system( strCmd.c_str() );
			*it = strNewFn;
		}


		//get new filename
		wl::SDte dt;

		wl::WFile::GetFileModiTime( MAKE_CURR_FULLFNAME, dt , FILE_SHARE_READ );

		if( dt.m_year == 0 ) continue;

		strNewFn = dt.ReadStringPack();
		wl::SStrf::sreplstr( strNewFn, ".", "_" );
		strNewFn += "_" + *it;


		//form rename command
		strCmd = "rename \"" + MAKE_CURR_FULLFNAME + "\"  \"" + strNewFn + "\"";
		std::cout << strCmd << std::endl;
		system( strCmd.c_str() );
	}


	system("pause");
	return 0;
}

