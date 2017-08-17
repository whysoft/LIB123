
参数:
##PARA0#： 没有参数

###
	

//X60_保存消息框



//LL_窗初始化之前_aa_X60_保存消息框:;



//窗体初始化	
		//


 
//LL_LL_窗体开始_aa_X60_保存消息框:;


//绘制

 
if(1)
{
	WebFormBegin( "保存消息框" );
	
	WebSendString( this->Get_StepCountstr() );
	WebSendString( " 保存完成" );
	WebAddCr();
	
	
	WebAddButt( "OK1", "OK" );
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
		//goto LL_窗初始化之前_aa_X60_保存消息框;
	}
	

	
	//goto LL_LL_窗体开始_aa_X60_保存消息框;

	break;
}



//LL_LL_窗体结束_aa_X60_保存消息框:;


 
