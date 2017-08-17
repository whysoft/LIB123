
参数:
##PARA0#： 没有参数

###
	

//X50_输入信息



LL_窗初始化之前_aa_X50_输入信息:;



//窗体初始化	
		//


 
LL_LL_窗体开始_aa_X50_输入信息:;


//绘制

 
if(1)
{
	WebFormBegin( "2017同学会登记系统" );
	
	WebSendString( this->Get_StepCountstr() );
	WebSendString( "输入信息" );
	WebAddCr(3);
	
	
	WebSendString( "输入姓名，汉字姓名全名，例如:万关茗" );
	WebAddBr();
	WebAddTextBox( "student_name", "" );
	WebAddCr(3);


	WebSendString( "输入学号，例如:08931135" );
	WebAddBr();
	WebAddTextBox( "student_num", "" );
	WebAddCr(3);

	
	WebSendString( "输入班级，例如:11班" );
	WebAddBr();
	WebAddTextBox( "student_class", "" );
	WebAddCr(3);

	
	WebSendString( "已交费额(元)，例如:123.45" );
	WebAddBr();
	WebAddTextBox( "student_money", "" );
	WebAddCr(3);


	WebSendString( "是否参加，是或否" );
	WebAddBr();
	WebAddTextBox( "student_take", "" );
	WebAddCr(3);



	WebAddButt( "OK1", "保存" );
	WebAddBr(2);
	

	WebAddButt( "OK2", "取消" );
	WebAddBr(2);


	WebAddButt( "OK3", "查看列表" );
	WebAddBr(2);


	WebAddCr();
	WebAddBr();
}


//事件
while(1)
{
	#include "等待下一个任意输入_无参.C"{};
	 
	 
	if( GETWEBINPUT("OK1") != "" )
	{
		if(1)
		{
			MYAUTOLOCK( gp_env->m_ma.m_ut_tbl_lck );

			a_mates_t::ROWTYPE r;

			r.m_name = GETWEBINPUT_DE( "student_name" );

			r.m_num  = GETWEBINPUT_DE( "student_num" );

			r.m_class = GETWEBINPUT_DE( "student_class" );

			r.m_money = SStrf::satof( GETWEBINPUT_DE( "student_money" ) );

			r.m_take = GETWEBINPUT_DE( "student_take" );
			
			r.m_ip = m_tSvr.m_strRemoteIPAddress;

			//r.m_stamp_create 
			//r.m_stamp_modi 

			//look up
			for( long j = 0; j < gp_env->m_ma.ut_GetRowAmount(); j++ )
			{
				a_mates_t::ROWTYPE &r2( gp_env->m_ma.GetRow( j ) );

				if( r2.m_name == r.m_name )
				{
					std::string sOld = r2.m_stamp_create;
					std::string s1 = r.Serialize();
					r2.Unserialize( s1.c_str() );
					r2.m_stamp_modi = SDte::GetNow().ReadString();
					r2.m_stamp_create = sOld;
					r.m_name = "";
					break;
				}
			}

			if( r.m_name != "" )
			{
				gp_env->m_ma.Add( r );
			}


			gp_env->m_ma.SaveF();
		}


		#include "X60_保存消息框.C"{};
		 
	
		goto LL_窗初始化之前_aa_X50_输入信息;
	}
	
		
	
	if( GETWEBINPUT("OK2") != "" )
	{
		goto LL_窗初始化之前_aa_X50_输入信息;
	}

		

	if( GETWEBINPUT("OK3") != "" )
	{
		#include "X70_数据列表.C"{};

		goto LL_窗初始化之前_aa_X50_输入信息;
	}


	
	goto LL_LL_窗体开始_aa_X50_输入信息;
}



//LL_LL_窗体结束_aa_X50_输入信息:;


 
