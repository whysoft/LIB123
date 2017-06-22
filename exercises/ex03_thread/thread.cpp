
#include "2.h"



//
class ThrdA : public wl::WThrd
{
public:
	int  m_iCounter;
	std::string  m_strName;

	ThrdA()
	{
		m_iCounter = 0;
	}

	virtual ~ThrdA()
	{}

	int tr_on_user_run()
	{
		printf("%s%d ", m_strName.c_str(), m_iCounter++);
		tr_sleep( 0, 0.001 );
		return m_iCounter < 99 ? 1 : 0;
	}
};


//
void test_thrd()
{
	for(int i = 0; i < 26; i++ )
	{
		ThrdA *a = new ThrdA;
		a->m_strName = "a";
		a->m_strName[0] += i;
		a->tr_openx();
	}
}



//
int main(int argc, char* argv[])
{
	test_thrd();

	printf( "proc time = %f\n", wl::SDte::e_proctime() );
	wl::WThrd::tr_sleep(9);
	return 0;
}
  

