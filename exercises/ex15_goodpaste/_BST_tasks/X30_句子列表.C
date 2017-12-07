
参数:
##PARA0#： 没有参数

###
	

//X30_句子列表



//LL_窗初始化之前_aa_X30_句子列表:;



//窗体初始化	
		//


 
LL_LL_窗体开始_aa_X30_句子列表:;


//绘制

 
if(1)
{
	WebFormBegin( "X30_句子列表" );
	
	WebSendString( this->Get_StepCountstr() );
	WebSendString( "X30_句子列表" );
	WebAddCr(3);
	
	////////////////////////////////////////

	WebAddHr();
	WebAddCr();
	WebAddBr();


	////////////////////////////////////////
	
	WebAddButt( "OK_REFRESH", "REFRESH" );
	WebAddBr(3);
	WebAddHr();


	////////////////////////////////////////
	
	WebAddTextarea(	"TXTA_GOODVALUE", "", 7, 33 );
	WebAddBr(1);

	WebAddButt( "OK1", " 保 存 " );
	WebAddBr(3);
	WebAddHr();
	
	
	////////////////////////////////////////
	
	WebAddTextBox( "TEXTBOX_DEL", "" );

	WebAddButt( "OK2", "删除" );
	WebAddBr(3);
	WebAddHr();

	////////////////////////////////////////

	WebAddHr();
	WebAddCr();
	WebAddBr();


	////////////////////////////////////////
	//所有句子 
		
	WebAddTable2Begin();
		
	for( long i = gp_env->m_gt.GetRowCount() - 1; i >= 0; i-- )
	{
		std::vector< std::string > r;

		r.push_back( gp_env->m_gt.GetRow(i).m_goodvalue );
		r.push_back( gp_env->m_gt.GetRow(i).m_dt_stamp );

		WebAddTable2Row( r );
	}
		
	WebAddTable2End();
		
}


//事件
while(1)
{
	#include "等待下一个任意输入_无参.C"{};
	 
	 
	if( GETWEBINPUT("OK_REFRESH") != "" )
	{
		goto LL_LL_窗体开始_aa_X30_句子列表;
	}


	if( GETWEBINPUT("OK1") != "" )
	{
		a_goodtbl_t::ROWTYPE r;

		r.m_dt_stamp = SDte::GetNow().ReadString();
		r.m_goodvalue = GETWEBINPUT_DE( "TXTA_GOODVALUE" );

		if( r.m_goodvalue != "" )
		{
			gp_env->m_gt.Add( r ); 
		}
		
		gp_env->m_gt.SaveF();

		goto LL_LL_窗体开始_aa_X30_句子列表;
	}


	if( GETWEBINPUT("OK2") != "" )
	{
		std::string s1 = GETWEBINPUT_DE( "TEXTBOX_DEL" );

		wl::SStrf::strim(s1);

		for( long i = gp_env->m_gt.GetRowCount() - 1; i >= 0; i-- )
		{
			if( gp_env->m_gt.GetRow(i).m_dt_stamp == s1 )
			{
				gp_env->m_gt.Del( i );
				gp_env->m_gt.SaveF();
	
				goto LL_LL_窗体开始_aa_X30_句子列表;
			}
		}
		
		goto LL_LL_窗体开始_aa_X30_句子列表;
	}

	
	goto LL_LL_窗体开始_aa_X30_句子列表;
}



//LL_LL_窗体结束_aa_X30_句子列表:;


 
