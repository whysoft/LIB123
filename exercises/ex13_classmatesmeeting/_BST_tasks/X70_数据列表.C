
参数:
##PARA0#： 没有参数

###
	

//X70_数据列表



//LL_窗初始化之前_aa_X70_数据列表:;



//窗体初始化	
		//


 
//LL_LL_窗体开始_aa_X70_数据列表:;


//绘制

 
if(1)
{
	WebFormBegin( "2017同学会登记系统 数据列表" );
	
	WebSendString( this->Get_StepCountstr() );
	WebSendString( "目前已来登记的同学列表如下：" );
	WebAddCr();
	
	
	WebAddButt( "OK1", "返回首页" );
	WebAddBr();
	WebAddBr();


	//data list
	//
	MYAUTOLOCK( gp_env->m_ma.m_ut_tbl_lck );


	WebAddTable2Begin();

	std::vector< std::string > row;

	row.clear();
	row.push_back( "姓名" );
	row.push_back( "学号" );
	row.push_back( "班级" );
	row.push_back( "已交费额" );
	row.push_back( "是否参加" );
	row.push_back( "创建日期" );
	row.push_back( "修改日期" );
	row.push_back( "访问者IP" );

	WebAddTable2Row( row, 1 );

	for( long j = 0; j < gp_env->m_ma.ut_GetRowAmount(); j++ )
	{
		SDB_t<a_mates_t> &r2(gp_env->m_ma); 

		row.clear();
		row.push_back( r2.ut_GetItemStr( j, "name" ) );
		row.push_back( r2.ut_GetItemStr( j, "num" ) );
		row.push_back( r2.ut_GetItemStr( j, "class" ) );
		row.push_back( r2.ut_GetItemStr( j, "money" ) );
		row.push_back( r2.ut_GetItemStr( j, "take" ) );
		row.push_back( r2.ut_GetItemStr( j, "stamp_create" ) );
		row.push_back( r2.ut_GetItemStr( j, "stamp_modi" ) );
		row.push_back( r2.ut_GetItemStr( j, "ip" ) );

		WebAddTable2Row( row, 0 );
	}


	WebAddTable2End();



	WebAddButt( "OK1", "返回首页" );
	WebAddBr();
	WebAddBr();
}


//事件
while(1)
{
	#include "等待下一个任意输入_无参.C"{};
	 
	 
	if( GETWEBINPUT("OK1") != "" )
	{
		(m_pafdata->m_env0).m_BigFontFlag = 1;
	
		goto LL_窗初始化之前_aa_X40_选择页面字体;
	}
	
	
	goto LL_窗初始化之前_aa_X40_选择页面字体;
}



//LL_LL_窗体结束_aa_X70_数据列表:;


 
