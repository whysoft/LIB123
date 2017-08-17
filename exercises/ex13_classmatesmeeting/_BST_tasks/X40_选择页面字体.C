
参数:
##PARA0#： 没有参数

###
	

//X40_选择页面字体



//goto LL_窗初始化之前_aa_X40_选择页面字体;
LL_窗初始化之前_aa_X40_选择页面字体:;



//窗体初始化	
		//


 
LL_LL_窗体开始_aa_X40_选择页面字体:;


//绘制

 
if(1)
{
	WebFormBegin( "2017同学会登记系统" );
	
	WebSendString( this->Get_StepCountstr() );
	WebSendString( "欢迎使用2017同学会登记系统" );
	WebAddCr();
	
	
	WebAddButt( "OK1", "手机画面" );
	WebAddBr();
	WebAddBr();
	

	WebAddButt( "OK2", "电脑画面" );
	WebAddBr();
	WebAddBr();


	WebAddCr();

	WebSendString( "2017同学会登记系统" + gp_env->m_strVer );
	WebAddBr();

	WebSendString( "访问者IP：" + m_tSvr.m_strRemoteIPAddress );  
	WebAddBr();
	std::cout << SDte::GetNow().ReadString() << "  " << m_tSvr.m_strRemoteIPAddress << std::endl;
	
	WTcpHttp h;
	h.ImportSvrRtnHeadPara( m_strHttpHead );
	WebSendString( "访问者系统：" + h.GetSvrRtnHeadParaVal( "User-Agent" ) );   
	WebAddBr();

	WebSendString( "服务器时间：" + m_dtnow.ReadString() );  
	WebAddBr();

	WebAddCr();
	WebAddBr();
}


//事件
while(1)
{
	#include "等待下一个任意输入_无参.C"{};
	 
	 
	if( GETWEBINPUT("OK1") != "" )
	{
		(m_pafdata->m_env0).m_BigFontFlag = 1;
	
		goto LL_窗初始化之前_aa_X50_输入信息;
	}
	
	
	if( GETWEBINPUT("OK2") != "" )
	{
		(m_pafdata->m_env0).m_BigFontFlag = 0;
		
		goto LL_窗初始化之前_aa_X50_输入信息;
	}

	
	goto LL_LL_窗体开始_aa_X40_选择页面字体;
}



//LL_LL_窗体结束_aa_X40_选择页面字体:;


 
