#ifdef WINENV_
#pragma warning(push)
#pragma warning(disable: 4996)
#pragma warning(disable: 4786)
//#include <windows.h>
#include <shellapi.h>
#pragma comment( lib, "ws2_32.lib" )
#include <winsock.h>
#include "atlstr.h"

/*
X011 project 
WHYSOFT league 2007-09
ALL RIGHTS RESERVED.
S series designed for standard C++, any OS, 32bit compatible.
W series designed for windows
*/

#ifndef X011__H_w_sbase_h
#define X011__H_w_sbase_h


#define X011_NAMESPACE_BEGIN namespace wl {
#define X011_NAMESPACE_END                }


#include <iterator> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>



X011_NAMESPACE_BEGIN

//basic types
typedef		double					tdouble; //8 bytes
typedef		char					tint8;
typedef		unsigned char			tuint8;
typedef		short					tint16;
typedef		unsigned short			tuint16;
typedef		long					tint32;
typedef		unsigned long			tuint32;

typedef     __int64                 tint64;
typedef    unsigned __int64         tuint64; //scanf("%I64d",&a);printf("%I64d",a);scanf("%lld",&a);printf("%lld",a);Dev-C++的g++编译器，它使用的是"%I64d"而非"%lld"。 


//derived types
typedef		tint8				tchar;
typedef		int					tbool; 

//mem based types
typedef		tuint32			tsize;
typedef		tint32			toffset;



X011_NAMESPACE_END





#endif




/*
standard C lib pack
all SECURE matters are packed here.
*/

#ifndef X011__H_w_SClib_h
#define X011__H_w_SClib_h


#pragma warning(push)
#pragma warning(disable: 4996)


X011_NAMESPACE_BEGIN


class SClib
{

public:

	SClib(){;}

	~SClib(){;}

	typedef int (* PT_sscanf)( const char *buffer, const char *format , ... );
	static PT_sscanf p_sscanf() { return sscanf; }

	typedef int (* PT_sprintf)( char *, const char *, ... );
	static PT_sprintf p_sprintf() { return sprintf; }

	typedef char * (* PT_strcpy)( char *strDestination, const char *strSource );
	static PT_strcpy p_strcpy() { return strcpy; }


	typedef tm * (* PT_localtime)( const time_t * );
	static PT_localtime p_localtime() { return localtime; }

	typedef FILE * (* PT_fopen)( const char *filename, const char *mode );
	static PT_fopen p_fopen(){ return fopen; }


	typedef char * (* PT_ltoa)( long value, char *str, int radix );
	static PT_ltoa p_ltoa() { return ltoa; }


}; //end class SClib





X011_NAMESPACE_END


#pragma warning(pop)



#endif





/*
base string func
*/

#ifndef X011__H_w_sstrf_h
#define X011__H_w_sstrf_h



X011_NAMESPACE_BEGIN


class SStrf
{

public:

	//SStrf(){;}

	virtual ~SStrf(){;}


	template < class T >
	static T * AddressOf( T & obj )
	{
		return reinterpret_cast<T *>(&reinterpret_cast<char&>(obj));
	}


	template< class T >
	static T * newobjptr( T * & p )
	{
		try
		{
			p = new T;
		}
		catch(...)
		{
			p = NULL;
		}

		return p;
	}

	
	template< class T >
	static T * newobjptr()  // wl::SStrf::newobjptr<bu_sop_t>()->tr_openx();
	{
		T *  p;
		return newobjptr(p);
	}


	static void * smalloc( tsize i )
	{
		return malloc( i );
	}


	static void sfree(void *s)
	{
		free(s);
	}



	static tuint16 smkU16( tuint8 c1, tuint8 c2) //lower byte is c1, comes first
	{
	   tuint16 ilow,ihigh;
	   ilow =  (tuint16)c1;
	   ihigh = (tuint16)c2;
	   ihigh <<= 8;
	   return ihigh + ilow;
	}


	template< class T >
	static T & chgendian( T & val )
	{
		if( sizeof(T) != 1 ) srev( (tchar *)&val, sizeof(T) ) ;
		return val;
	}

	template< class T >
	static T chgendian2( T val )
	{
		return chgendian(val);
	}
	

	
	static tbool readbit( void * pbin , int sufx )  
	{
		if( sufx < 0 )
		{
			return 0;
		}

		tuint8 * pbin2 = (tuint8 *)pbin;
		tuint8 cSrc;
		int iOffset ;

		cSrc = pbin2[sufx / 8];

		//iOffset = 7 - (sufx % 8);
		iOffset =  (sufx % 8);

		cSrc >>= iOffset;
		cSrc &= 1;
		return cSrc;
	}

	
	static tbool readbit( tuint8 bindata , int sufx )  
	{
		return readbit( &bindata, sufx );
	}


	static void writebit( void * pbin , int sufx , tbool val )
	{
		if( sufx < 0 )
		{
			return ;
		}

		val = val?1:0; 

		tuint8 * pbin2 = (tuint8 *)pbin;
		int cSrc;
		int iOffset ;

		cSrc = pbin2[sufx / 8];

		//iOffset = 7 - (sufx % 8);
		iOffset = (sufx % 8);

		cSrc >>= iOffset;
		cSrc &= 1;

		if( cSrc == val ) return ;

		int i = 1;
		i <<= iOffset;

		pbin2[sufx / 8] ^= i;
	}


	static std::string & bit2str( tchar c, std::string & strrtn )
	{
		strrtn = "01234567";
		for( int i = 0; i < 8; i++ ) strrtn[i] = readbit( &c, i ) ? '1' : '0' ;
		return strrtn;
	}

	static std::string bit2str( tchar c )
	{
		std::string str;
		return bit2str( c, str );
	}

	static tchar & str2bit( std::string str, tchar & c )
	{
		//......12345678  --是高位补0
		str += "00000000";
		for( int i = 0; i < 8; i++ ) writebit( &c, i , str[i]=='0' ? 0 : 1 );
		return c;
	}

	static tchar str2bit( std::string str )
	{
		tchar c;
		return str2bit( str, c );
	}


	static void initrand( int seed = 0 ) //sets the generator to a random starting point. better than srand()
	{
		tint32 j=(tint16)(0x0555&(time(0)*seed));
		for(tint32 i=0;i<j;++i) rand();
	}


	static tdouble rand1( int iShouldInitSeed = 0 )
	{
		if( iShouldInitSeed ) initrand( iShouldInitSeed );
		return (tdouble)rand()/(tdouble)RAND_MAX;
	}


	static void *smemcpy( void *dest, const void *src, tsize count )
	{
		return memcpy(dest,src,count);//memcpy
	}


	static void * smemset( void *dest, tchar c, tsize count )
	{
		return memset( dest, (int)c, (size_t)count );
	}


	template< class T >
	static void * smemset( T * dest, tchar c = 0 )
	{
		return memset( dest, (int)c, sizeof(T) );
	}




	static tchar * scpy( tchar *strDestination, const tchar *strSource )
	{
		return (*SClib::p_strcpy())( strDestination, strSource );
	}


	static tsize slen( const tchar * s ) //串长度
	{
		if(s==NULL) return (tsize)0;
		return (tsize)strlen(s);
	}


	static tbool sishex(tchar c)//是16进制
	{
		return  (c>='0'&&c<='9')||(c>='A'&&c<='F')||(c>='a'&&c<='f');
	}

	static tbool sishex(const tchar *s)
	{
		if(s==NULL) return 0;
		for(;*s;s++) if(!sishex(*s)) return 0;
		return 1;
	}

	static tbool sisdec(tchar c) //是10进制
	{
		return  (c>='0'&&c<='9');
	}

	static tbool sisdec(const tchar *s)
	{
		if(s==NULL) return 0;
		for(;*s;s++) if(!sisdec(*s)) return 0;
		return 1;
	}


	static tchar *sltoa( tint32 i, tchar *buf, int radix = 10 )
	{
		return (*SClib::p_ltoa())(i, buf, radix);
	}


	static std::string sltoa( tint32 i, int radix = 10 )
	{
		tchar c[55];
		std::string buf;
		buf = sltoa( i, c, radix );
		return buf;
	}

	static tint32 satol( const tchar *s ) { return(s==NULL)?0:(tint32)atol(s); }

	static tint32 satol( const std::string & s ) { return satol(s.c_str()); }


	
	static std::string sultoa( tuint32 i )
	{
		std::stringstream stream;
		stream << i;
		return stream.str();
	}

	
	static tuint32 satoul( std::string  s ) 
	{ 
		return strtoul(s.c_str(),NULL,10); 
	}



	static tchar * sftoa( tdouble f , tchar * buf , int decimal_digits = -1 )
	//static tchar * sftoa( tdouble f, tchar *buf )
	{
		std::string s1;

		if( decimal_digits < 0 )
		{
			s1 = "%f";
		}
		else
		{			
			s1 = "%." + sltoa(decimal_digits) + "f";
		}

		(*SClib::p_sprintf())( buf, s1.c_str(), f );

		return buf;
	}

	static std::string sftoa( tdouble f , int decimal_digits = -1 )
	{
		if( decimal_digits < -1 ) decimal_digits = -1;
		std::vector<tchar> v( 22 + decimal_digits );
		tchar * c;
		c = &(v[0]);
		return  sftoa( f, c , decimal_digits );
	}


	static tdouble satof( const tchar *s )
	{
		if(s==NULL) return 0.0;
		return (tdouble)atof(s);
	}


	static tdouble satof( const std::string & s )
	{
		return satof(s.c_str());
	}


	static int scmpi( const tchar *a, const tchar *b )	//case insensitive
	{
		if(a==NULL&&b==NULL) return 0;
		if(a==NULL&&b!=NULL) return -1;
		if(a!=NULL&&b==NULL) return 1;
		const tchar *t1;
		const tchar *t2;
		tchar c1, c2;
		toffset i;
		t1 = a;
		t2 = b;
		for( i=0;t1[i]&&t2[i];i++ )
		{
			c1=t1[i]; c2=t2[i];
			if(c1>='a'&&c1<='z') c1+=('A'-'a');
			if(c2>='a'&&c2<='z') c2+=('A'-'a');
			if(c1!=c2) return c1-c2;
		}
		return t1[i]-t2[i];
	}


	static int scmpin( const tchar *a, const tchar *b, tsize count ) //case insensitive
	{
		if(a==NULL&&b==NULL) return 0;
		if(a==NULL&&b!=NULL) return -1;
		if(a!=NULL&&b==NULL) return 1;
		const tchar *t1;
		const tchar *t2;
		tchar c1, c2;
		tsize i;
		t1 = a;
		t2 = b;
		for( i=0;t1[i]&&t2[i]&&i<count;i++ )
		{
			c1=t1[i]; c2=t2[i];
			if(c1>='a'&&c1<='z')c1+=('A'-'a');
			if(c2>='a'&&c2<='z')c2+=('A'-'a');
			if(c1!=c2)return c1-c2;
		}
		if(i>0) i--;
		return t1[i]-t2[i];
	}


	static int scmpin( const tchar *a, const tchar *b ) //case insensitive
	{
		return scmpin(a,b,slen(b));
	}




	static int scmpn( const tchar *a, const tchar *b, tsize count )
	{
		if(!count) return 0; //if no len, then equal.
		if(a==NULL&&b==NULL) return 0;
		if(a==NULL&&b!=NULL) return -1; // a<b
		if(a!=NULL&&b==NULL) return 1;  // a>b
		return strncmp(a,b,count);
	}


	static int scmpn( const tchar *a, const tchar *b ) //assume count is len of b.
	{
		return scmpn(a,b,slen(b));
	}




	static int scmp( const tchar *a, const tchar *b )
	{
		if(a==NULL&&b==NULL) return 0;
		if(a==NULL&&b!=NULL) return -1;
		if(a!=NULL&&b==NULL) return 1;
		return strcmp(a,b);
	}


	static tchar * sucase( tchar *s )
	{
		toffset i;
		if(s==NULL) return NULL;
		for(i=0;s[i]!=0;i++){
			if(s[i]>='a'&&s[i]<='z')s[i] = s[i] -'a' + 'A' ;
		}
		return s;
	}

	
	static std::string & sucase( std::string & str )
	{
		tchar * szstr;
		szstr = (tchar *)smalloc( (tsize)str.size() + 1 );
		scpy( szstr, str.c_str() );
		sucase( szstr );
		str = szstr;
		sfree( szstr );
		return str;
	}


	static tchar * slcase( tchar *s )
	{
		toffset i;
		if(s==NULL) return NULL;
		for(i=0;s[i]!=0;i++){
			if(s[i]>='A'&&s[i]<='Z')s[i] = s[i] -'A' + 'a' ;
		}
		return s;
	}


	static std::string & slcase( std::string & str )
	{
		tchar * szstr;
		szstr = (tchar *)smalloc( (tsize)str.size() + 1 );
		scpy( szstr, str.c_str() );
		slcase( szstr );
		str = szstr;
		sfree( szstr );
		return str;
	}



	//指出最后一个字符的指针.可以向左偏移。
	//偏移量0代表最末一个字节，而不是c00. but if s is "", return the pointer to c00 .
	template< class Pchar_CPchar_T >	/*Pchar_CPchar_T可能是const或非const的字节指针*/
	static Pchar_CPchar_T splast( Pchar_CPchar_T s, toffset offset2left = 0 /*正数代表向左方*/ )	
	{
		Pchar_CPchar_T t = s;
		if(!s||!*s) return t; //
		toffset i,j ;
		j = (toffset)slen(s);
		i = j - 1 - offset2left ;
		t=s+(i<0?0:i);
		return t;//最多退到s本身。
	}



	static const tchar * sstr( const tchar * s, const tchar *substr ) 
	{
		if(!s||!substr||!(*s)||!(*substr)) return NULL;
		return (const tchar *)strstr(s,substr); 
	}

	static tchar * sstr( tchar * s, const tchar *substr ) 
	{
		if(!s||!substr||!(*s)||!(*substr)) return NULL;
		return (tchar *)strstr(s,substr); 
	}


	template< class Pchar_CPchar_T >
	static Pchar_CPchar_T sstr( Pchar_CPchar_T s, tchar subc )
	{
		tchar t[2];
		t[0]=subc;
		t[1]=0;
		return sstr(s,t) ;
	}


	static tchar * srev( tchar * s, tsize len ) 
	{
		tsize u;
		toffset  x, y, i, a, b;
		u = len;
		u >>= 1;
		x = u;
		y = (toffset)len - 1;
		for(i=0;i<x;i++) {
			a = i;
			b = y - i; 
			s[a] ^= s[b];
			s[b] ^= s[a];
			s[a] ^= s[b];
		}
		return s;
	}


	static tchar *srev( tchar * s )
	{
		return srev(s,slen(s));
	}


	static tchar * sreplch( tchar * source, tsize len, tchar c1, tchar c2 )	//对于来源二进制串中所有的c1替换成c2
	{
		tsize i;
		for(i=0;source&&i<len;i++) {
			if(source[i]==c1) source[i]=c2;
		}
		return source;
	}


	static tchar * sreplch( tchar * source, tchar c1, tchar c2 )	//所有的c1替换成c2
	{
		return sreplch(source, slen(source), c1, c2);
	}


	static std::string & sreplstr( std::string & str, const tchar *string_to_replace, const tchar *new_string )   
	{
		if( string_to_replace && new_string )
		{
			//   Find   the   first   string   to   replace   
			std::string::size_type   index   =   str.find(string_to_replace);   
			//   while   there   is   one   
			while(index   !=   std::string::npos)   
			{   
				//   Replace   it   
				str.replace(index,   strlen(string_to_replace),   new_string);   
				//   Find   the   next   one   
				index   =   str.find(string_to_replace,   index   +   strlen(new_string));   
			}   
		}
		return   str;   
	}


	static std::string & sreplstr( std::string & str, const std::string & string_to_replace, const std::string & new_string ) 
	{
		return sreplstr( str, string_to_replace.c_str(), new_string.c_str() ) ;
	}

	//static std::string & sreplstr( std::string & str,  std::string * string_to_replace,  std::string * new_string ) 
	//{
	//	if( string_to_replace==NULL) return str;
	//	if( new_string==NULL) return str;
	//	return sreplstr( str, string_to_replace->c_str(), new_string->c_str() ) ;
	//}

	//static std::string & sreplstr( std::string & str,  std::string  string_to_replace,  std::string  new_string ) 
	//{
	//	return sreplstr( str, string_to_replace.c_str(), new_string.c_str() ) ;
	//}



	// 3 trim functions below:

	//a trim base func:
	static std::string & str_trim_base( tchar *(*f)( tchar *, const tchar * ), std::string & str, const tchar *str_space="\r\n \t" )
	{
		tchar * pstr;
		pstr = (tchar *)smalloc( (tsize)str.size() + 1 );
		scpy( pstr, str.c_str() );
		str = (*f)( pstr, str_space );
		sfree( pstr );
		return str;
	}


	//right trim 

	static tchar * strimr( tchar * s, tchar a_space ) //right trim, tchar. trim series knl
	{
		toffset i;
		for(i=slen(s)-1;i>=0;i--)
			if(s[i]==a_space)
				s[i]=0;
			else
				break;
		return s;
	}

	static tchar * strimr( tchar * s, const tchar *str_space="\r\n \t" ) //right trim, tchar*. trim series knl
	{
		toffset i;
		for( i=slen(s)-1; i >= 0; i-- )
			if( sstr(str_space,s[i]) != NULL )
				s[i]=0;
			else
				break;
		return s;
	}

	static std::string & strimr( std::string & str, const tchar * str_space = "\r\n \t" )
	{
		return str_trim_base( strimr, str, str_space );
	}


	//left trim 

	static tchar * striml( tchar * s, tchar a_space )	//left trim
	{
		return srev( strimr(srev(s), a_space) ) ;
	}

	static tchar * striml( tchar * s, const tchar * str_space = "\r\n \t" )		//left trim
	{
		return srev( strimr(srev(s), str_space) ) ;
	}

	static std::string & striml( std::string & str, const tchar * str_space = "\r\n \t" )
	{
		tchar * pstr;
		pstr = (tchar *)smalloc( (tsize)str.size() + 1 );
		scpy( pstr, str.c_str() );
		str = striml( pstr, str_space );
		sfree( pstr );
		return str;
	}


	//double trim

	static tchar * strim( tchar * s, tchar a_space  ) // double trim
	{
		return  striml( strimr(s,a_space), a_space) ;
	}

	static tchar * strim( tchar * s, const tchar * str_space = "\r\n \t" ) // double trim
	{
		return  striml( strimr(s,str_space), str_space) ;
	}

	static std::string & strim( std::string & str, const tchar * str_space = "\r\n \t" )
	{
		return str_trim_base( strim , str, str_space );
	}

	//trim functions end.



	static tchar * sleft( tchar * s, tsize n ) //left right mid series knl
	{
		if(n>slen(s)) return s;
		s[n]=0;
		return s;
	}


	static tchar * sright( tchar * s, tsize n )
	{
		return srev(sleft(srev(s), n));
	}


	static tchar * smid( tchar * s, tsize a_pos, tsize a_len )
	{
		sright(s, slen(s) - a_pos );
		sleft(s, a_len);
		return s;
	}



	static const tchar * seq_dirno()
	{
		return "0123456789ACEFHKLMPQSTUWXYZ"; //dirnogjbv	 27 left
	}



	static std::string seq( std::string strCurNum, tbool isFixLen = 1, const tchar * s_symbset = NULL )
	{
		static tchar c[1];
		tchar * s_num;
		tint16 *lia ;
		tint16 ulia;
		tint32 i,j,k;

		c[0]=0;
		if(slen(s_symbset)<2) s_symbset = seq_dirno();
		s_num = (tchar*)smalloc( (tsize)strCurNum.size() + 2 );
		if(!s_num) return "";
		lia = (tint16 *)smalloc( (slen(s_num) + 1)*sizeof(tint16) );
		if(!lia)
		{
			sfree(s_num);
			return "";
		}

		scpy( s_num, strCurNum.c_str() );
		
		if(!(*s_num)) {
			s_num[0]=s_symbset[0];
			s_num[1]=0;
		}

		j = slen(s_num) ;
		for(i=0;i<j;i++)
		{
			const char *t = sstr( s_symbset, s_num[i] );
			if(!t)
				lia[i] = 0;
			else
				lia[i] = (tint16)( t - s_symbset );			
		}

		lia[j-1] ++;
		k = slen(s_symbset) ;
		ulia = 0;
		for(i=j-1;i>=0;i--)
		{
			if(lia[i] >= k)
			{
				lia[i] -= (tint16)k;
				if(i>0)
					lia[i-1]++;
				else
					ulia++;
			}
		}

		for( i=0;i<j;i++ )
		{
			s_num[i] = s_symbset[ lia[i] ];
		}

		if( (!isFixLen) && ulia )	//如果不是固定长度，则处理最高位进位。
		{
			srev(s_num);
			s_num[j] = s_symbset[ulia];
			s_num[j+1] = 0;
			srev(s_num);
		}

		strCurNum = s_num;
		sfree(s_num);
		sfree(lia);
		return strCurNum;
	}




	static tchar bs_esc() { return 'b'; }/*b被合成后应该换成%*/



	static tbool bs_inset( tchar c ) //in direct expression set
	{
		if(c==bs_esc()) return 0; //if is esc then is not in the set
		if(c>='a'&&c<='z') return 1;
		if(c>='0'&&c<='9') return 1;
		if(c>='A'&&c<='Z') return 1;
		return 0;
	}


	static tsize bs_ensize( const tchar *s, tsize len ) 
	{
		tsize i;
		tchar *t1, *t2, *t3;
		if(s==NULL) return 0;
		i=0;
		t1=(tchar*)s;
		t3=t1+len;
		for( t2=t1; t2<t3; t2++ )
			i += bs_inset(*t2)?(1*sizeof(tchar)):(3*sizeof(tchar));

		return i+(sizeof(tchar)); //must be sz-string after encode. a tchar for '\0'
	} 


	static tsize bs_ensize( const tchar *s ) 
	{ 
		return bs_ensize( s, slen(s) + 1 );
	}


	static tchar * bs_en( const tchar *s, tsize len, tchar *destbuf )
	{
		tchar *ss1, *ss2, *ss3, *sd1;
		tbool rc;
		int l;
		if(s==NULL||destbuf==NULL) return NULL;
		ss1 = (tchar*)s;
		ss3 = ss1 + len;
		sd1 = destbuf;

		for( ss2=ss1; ss2<ss3; ss2++)
		{
			rc = 0;

			do //fakedo 0
			{
				if( !bs_inset(*ss2) ) //不在圈里，崩溃。
				{ 
					rc = 1;
					break;
				}

				*sd1 = *ss2;         //没崩溃时的处理。
				sd1++;

			}while(0);

			if(rc) {    //崩溃时的处理。
				l = (tuint8)(*ss2);
				(*SClib::p_sprintf())( sd1, "%c%02X", bs_esc(), l );
				sd1 += (3*sizeof(tchar));
			}
		}
		*sd1=0;//to form a sz. bs_ensize has reported this space up there
		return destbuf;
	}


	static tchar * bs_en( const tchar *s, tchar *destbuf )
	{
		return bs_en( s, slen(s) + 1, destbuf );
	}

	static std::string  & bs_en( std::string & strData ) //the data includes the sz00.
	{
		std::string s1( 3 + bs_ensize( strData.c_str(), (tsize)strData.length() ) , 'a' );

		bs_en( strData.c_str(), &(s1[0]) );

		return strData = s1.c_str();
	}

	static std::string  & bs_de( std::string & strData )  
	{
		std::string s1( strData + "123" );

		bs_de( strData.c_str(), &(s1[0]) );

		return strData = s1.c_str();
	}


	static tsize bs_desize( const tchar *s , tchar(*apf1)()=bs_esc )
	{
		toffset j,i;
		tsize  k;
		if(s==NULL) return 0;
		
		for( i=0,j=(toffset)slen(s),k=0;i<j; ) 
			if(	(i+2<j)				&&
				s[i]==(*apf1)( )	&&
				sishex(s[i+1])		&&
				sishex(s[i+2])  )
			{
				k++;
				i+=3;
			}
			else
			{
				i++;
				k++;
			}
		return k;
	}


	static tchar * bs_de( const tchar *s, tchar *dest , tchar(*apf1)()=bs_esc ) //the dest buffer can be the same of the source. safe to overlay
	{
		if(s==NULL||dest==NULL) return dest;
		toffset i,j,k;
		toffset a1,a2;
		tchar ss[2]; 
		ss[1]=0;

		for(i=0,j=(toffset)slen(s),k=0;i<j; ) {
			if(	(i+2<j)			&&
				s[i]==(*apf1)( )&&
				sishex(s[i+1])	&&
				sishex(s[i+2])	 )
			{
				ss[0]=s[i+1];
				sucase(ss);
				a1 = (ss[0] <= '9' ? ss[0] - '0' : ss[0] - 'A' + 10) * 16 ;

				ss[0]=s[i+2];
				sucase(ss);
				a2 = (ss[0] <= '9' ? ss[0] - '0' : ss[0] - 'A' + 10) ;

				*(tchar *)(dest+k) = (tuint8)(a1+a2);
				k++;
				i+=3;
			}else{
				dest[k] = s[i];
				k++;
				i++;
			}
		}

		return dest;
	}


	static tchar * bs_de( tchar *source_dest , tchar(*apf1)()=bs_esc ) //the dest buffer is the source. safe to overlay
	{
		return bs_de(source_dest,source_dest,apf1);
	}

	

	template< class T >
	static std::string b2s( /*const*/ T & sourcedata )
	{
		std::string str1;
		tchar * szstr;
		szstr = (tchar *)smalloc( sizeof(T) * 3 + 3 );
		bs_en( (const char *)reinterpret_cast<const char *>(&reinterpret_cast</*const*/ char& >(sourcedata)), sizeof(T), szstr );
		str1 = szstr;
		sfree( szstr );
		return str1;
	}

	
	template< class T >
	static T & s2b( std::string strSource, T & destdata )
	{
		bs_de( strSource.c_str(), reinterpret_cast<tchar *>(&reinterpret_cast<char& >(destdata))  );
		return destdata;
	}

	template< class T >
	static T s2b( std::string strSource )
	{
		T destdata;
		bs_de( strSource.c_str(), reinterpret_cast<tchar *>(&reinterpret_cast<char& >(destdata))  );
		return destdata;
	}


}; //end class SStrf 





X011_NAMESPACE_END





#define MOONLOGSTR  \
	( "**" + /*wl::SDte::GetNow().ReadStringPack() + "|" +*/ std::string(__FILE__) + "|" + std::string(__FUNCTION__) + "|" + wl::SStrf::sltoa(__LINE__) )






#endif




/*
calculate func
*/

#ifndef X011__H_w_SCalc_h
#define X011__H_w_SCalc_h



X011_NAMESPACE_BEGIN


class SCalc
{

public:

	//SCalc(){;}

	virtual ~SCalc(){;}
	
	
	
	static tint32 max_divisor( tint32 a, tint32 b) //得出来a就是a和b的最大公约数
	{
		tint32 temp; 
		while(b!=0) //---判断余数是否为0,为0了,就是最大公约数了a 
		{ 
		temp=a%b; //a数去除b数的余数赋值给temp 
		a=b;      //把b数赋值给a 
		b=temp;   //把余数赋值给b
		} 
		return a;
	}


	static tbool quadratic_equation_root( tdouble a, tdouble b, tdouble c, tdouble *x1, tdouble *x2) //求一元二次方程的根
	{
		if(b*b<4*a*c) return 0; 
		*x1=(sqrt(b*b-4*a*c)-b)/(2*a); 
		*x2=(-sqrt(b*b-4*a*c)-b)/(2*a); 
		return 1; 
	}


	static std::string dseal( const std::string & strData , tsize out_len , const tchar *szMethod = ""  )
	{
		return dseal( strData.c_str(), SStrf::slen( strData.c_str() ) , out_len , szMethod );
	}


	static std::string dseal( const tchar *s, tsize len, tsize out_len, const tchar *szMethod = "" )
	{
		// 指定目标长度 十进制数字摘要 dseal V1.0
		tuint32 i, j;
		tchar *t, *t0;
		std::string strOut("");
		if(!s||/*!len||*/!out_len||!szMethod) return "";
		for(j=len+out_len,i=0;;i++)
		{
			j = ++j + chksum(s, len) + chksum(szMethod,SStrf::slen(szMethod));
			j = ++j * chksum(strOut.c_str(),(tsize)strOut.size()) * (len^10) * out_len ; 
			j = 0x7FffFFff & (j ^ (~j * ~i + (len ^ out_len)) * (~j+~j*~i+~i));
			strOut += SStrf::sltoa(j);
			if( out_len+11 < strOut.size() ) break ;
		}
		t0 = t = (tchar*)SStrf::smalloc( (tsize)strOut.size()+1 );
		if(!t) return "";
		SStrf::scpy( t, strOut.c_str() );
		SStrf::srev(t);
		if(*t=='0') t++;		 
		t[out_len] = 0;
		strOut=t;
		SStrf::sfree(t0);
		return strOut;
	}


	
	static tuint32 chksum( const tchar *s, tsize len)
	{
		tuint32 j=0;
		if(SStrf::slen(s)==0)
			return 0;
		while(len--)
		{
			j += (tuint8)s[len]+(len+1);
			j &= 0x7FffFFff;
		}
		return j;
	}



	static tchar * xor( tchar * Src, tsize len, tuint8 x )
	{
		tsize i;
		tuint8 *s=(tuint8 *)Src;
		if( !s || !len ) return (tchar*)s;
		for(i=0;i<len;i++) s[i] ^= x;
		return (tchar*)s;
	}


}; //end class SCalc





X011_NAMESPACE_END

#endif





/*
string
vector string
*/

#ifndef X011__H_w_sstrvs_h
#define X011__H_w_sstrvs_h



X011_NAMESPACE_BEGIN



class SStrvs
{

public:

	//SStrvs(){;} 

	virtual ~SStrvs(){;}

	
	template < class StrT > /* for string or wstring*/
	static tsize vsa_impbylen( const StrT & strsource, typename StrT::size_type ilen, std::vector<StrT> & vecrtn )
	{
		StrT s1(strsource);
		typedef typename StrT::size_type sizetypeB;

		while( !s1.empty() )
		{
			sizetypeB i = ilen <= s1.size() ? ilen : s1.size();
			StrT s2 = s1.substr( 0, i );
			vecrtn.push_back(s2);
			s1.erase( 0, i );
		}
		return (tsize)vecrtn.size();
	}




	//

	template < class StrT > /* for string or wstring*/
	static tsize vsa_imp( const StrT & ssource, const StrT & ssep, tbool istoken, std::vector<StrT> & rtnlst )
	//static tsize vsa_imp( const StrT & ssource, StrT ssep, tbool istoken, std::vector<StrT> & rtnlst )
	{
		std::vector<tint32> vAbuf, vBbuf;
		tint32  ltmpn,ltmpm,ltmpi,ltmpj,ltmpk, ltmpb1, ltmpb2;
		typedef typename StrT::size_type sizetypeB;
		sizetypeB ssti;

		ltmpm = ltmpi = ltmpj = 0;
		ltmpn = (tint32)ssource.size();
		ltmpk = (tint32)ssep.size();

		do //fakedo
		{
			if(ltmpk==0)
			{
				rtnlst.push_back(ssource);
				break;
			}

			do 
			{
				if(ltmpm>=ltmpn) break;
				ssti = ssource.find( ssep, ltmpm ); //the knl. find() return from 0 on.
				if(ssti==StrT::npos) break;
				ltmpi = (tint32)ssti;
				ltmpm = ltmpi;

				vAbuf.push_back(ltmpi);  
				ltmpj ++;
				ltmpm += ltmpk;

			} while(1);

			ltmpb1 = 0 ; // lowerbound(vAbuf) 
			ltmpb2 = ltmpj - 1 ; // upperbound(vAbuf)

			ltmpj = 0;
			vBbuf.push_back(ltmpj);
			for(ltmpi=ltmpb1;ltmpi<=ltmpb2;ltmpi++){
				ltmpj = vAbuf[ltmpi];
				vBbuf.push_back(ltmpj);
				vBbuf.push_back(ltmpj+ltmpk);
			}
			vBbuf.push_back( ltmpn );

			ltmpj = (tint32)vBbuf.size();
			for(ltmpi=0;ltmpi<ltmpj;ltmpi+=2)
			{
				ltmpm = vBbuf[ltmpi];
				ltmpn = vBbuf[ltmpi+1];
				ltmpk = ltmpn - ltmpm;

				if(istoken&&ltmpk==0){
					;
				}else
					rtnlst.push_back( ssource.substr( ltmpm, ltmpk ) ); //the knl. substr(pos{suffix},len)

			}
			
		}while(0);

		return (tsize)rtnlst.size();//vector size目前已经被占用了的位置个数。
	}


	template < class StrT > /* for string or wstring*/
	static tsize vsa_hm( const StrT & ssource, const StrT & ssep, tbool istoken )
	{
		return vsa_imp( ssource, ssep, istoken, std::vector<StrT>() );
	}

	
	//iwhich is suffix. from 0 on.
	template < class StrT > /* for string or wstring*/
	static StrT vsa_get( const StrT & ssource, const StrT & ssep, tbool istoken, tsize iwhich )
	//static StrT vsa_get( const StrT & ssource, StrT ssep, tbool istoken, tsize iwhich )
	{
		std::vector<StrT> tmplst;
		if( iwhich<vsa_imp( ssource, ssep, istoken, tmplst ) )
			return tmplst[iwhich];
		else
			return StrT();
	}

	template < class StrT >  
	static StrT vsa_get( const StrT & ssource, const typename StrT::value_type *ssep, tbool istoken, tsize iwhich )
	{
			return vsa_get( ssource,  StrT(ssep),  istoken,  iwhich );
	}
	

	//2V get
	/* the para have 3 parts. 1=the source. 2=settings. 3=the coordinate */
	template < class StrT > 
	static StrT vsa2v_get( const StrT & ssource, 

						  const StrT & ssepTR,
						  tbool		istokenTR,
						  const StrT & ssepTD,
						  tbool		istokenTD,

						  tsize iwhichTR,  tsize iwhichTD		)

	{
		std::vector<StrT> tmplst1, tmplst2;
		if( iwhichTR<vsa_imp( ssource, ssepTR, istokenTR, tmplst1 ) )
		{
			if( iwhichTD<vsa_imp( tmplst1[iwhichTR], ssepTD, istokenTD, tmplst2 ) )
				return tmplst2[iwhichTD];
		}
		return StrT();
	}


	//2V prpt
	/*   */
	template < class StrT > 
	static std::map<StrT,StrT> & vsa2v_prpt( const StrT & ssource, 
											 const StrT & ssepTR,
											 const StrT & ssepTD, 
											 std::map<StrT,StrT> & mapRtn	)
	{
		std::vector<StrT> vecTmpTR, vecTmpTD;
		typedef typename std::vector<StrT>::iterator iteratortypeB;
		iteratortypeB itTR;
		vsa_imp( ssource, ssepTR, 1, vecTmpTR );
		for( itTR = vecTmpTR.begin(); itTR!=vecTmpTR.end(); ++itTR)
		{
			vsa_imp( *itTR, ssepTD, 1, vecTmpTD );
			vecTmpTD.push_back( StrT() );
			vecTmpTD.push_back( StrT() );
			mapRtn.insert( std::pair<StrT,StrT>( vecTmpTD[0], vecTmpTD[1] ) );
			vecTmpTD.clear();
		}
		return mapRtn;
	}


};//end class SStrvs





X011_NAMESPACE_END

#endif






/*
set operation
*/

#ifndef X011__H_w_SSetu_h
#define X011__H_w_SSetu_h



X011_NAMESPACE_BEGIN



class SSetu
{

public:

	//SSetu(){;} 

	virtual ~SSetu(){;}
	

	//all containers must have same element type.
	template < class CntnrT, class ELET >
	static tsize vs_setch( CntnrT &vset1, CntnrT &vset2, std::vector<ELET> &rtnlst )
	{
		typedef typename CntnrT::iterator iteratortypeB;
		iteratortypeB it1, it2;
		tsize i;
		i=0;
		for( it1=vset1.begin(); it1!=vset1.end(); it1++)
		{
			it2 = std::find( vset2.begin(), vset2.end(), *it1 );
			if( it2 == vset2.end() ) //can't find in set2 then means only in set1
			{
				rtnlst.push_back( *it1 );
				i++;
			}
		}
		return i;
	}


	//all containers must have same element type.
	template < class CntnrT, class ELET >
	static tsize vs_setj( CntnrT &vset1, CntnrT &vset2, std::vector<ELET> &rtnlst )
	{
		typedef typename CntnrT::iterator iteratortypeB;
		iteratortypeB it1, it2;
		tsize i;
		i=0;
		for( it1=vset1.begin(); it1!=vset1.end(); it1++)
		{
			it2 = std::find( vset2.begin(), vset2.end(), *it1 );
			if( it2 != vset2.end() ) //can find in set2 then means both in 2 sets
			{
				rtnlst.push_back( *it1 );
				i++;
			}
		}
		return i;
	}


	//first 2 containers must have same element type.
	template < class CntnrT, class ELET >
	static tsize vs_setgroup( const CntnrT & vsource, std::vector<ELET> & rtncontent, std::vector<int> & rtnsubsum )
	{
		CntnrT v2, v3; //same as the source type
		typedef typename CntnrT::iterator iteratortypeB;
		iteratortypeB  it1,  itNewEnd2;
		int i;

		v2 = vsource;
		std::sort( v2.begin(), v2.end() );
		v3 = v2;

		itNewEnd2 = std::unique( v2.begin(), v2.end() );

		for( it1=v2.begin(); it1!=itNewEnd2; it1++)
		{
			rtncontent.push_back( *it1 );
			i = (int)std::count( v3.begin(), v3.end(), *it1 );
			rtnsubsum.push_back(i);
		}
		return (tsize)v2.size();
	}


	template < class CntnrT, class ELET >
	static tsize vs_setgroup( const CntnrT & vsource, std::vector<ELET> & rtncontent )
	{
		std::vector<int> v;
		return vs_setgroup( vsource, rtncontent, v );
	}


	template < class ELET >
	static tsize vs_setgroup( std::vector<ELET> & _a_content )  //用本身返回
	{
		std::vector<ELET> _a_aa1;
		tsize i = vs_setgroup( _a_content, _a_aa1 );
		_a_content = _a_aa1;
		return i;
	}





	template < class ELET >
	static ELET & vs_groupbig( std::vector<ELET> & memo, std::vector<int> & subsum )
	{
		typedef typename std::vector<ELET>::iterator iteratortypeB;
		iteratortypeB it1;
		std::vector<int>::iterator it2, it3;
		int i;

		i=0;
		for( it3=it2=subsum.begin(); it2!=subsum.end(); ++it2)
		{
			if( *it2>i )
			{
				i = *it2;  //keep the best val
				it3 = it2; //keep the best pos
			}
		}

		it1 = memo.begin() + ( it3 - subsum.begin() );
		return *it1;
	}


	template < class ELET >
	static ELET & vs_groupsmall( std::vector<ELET> & memo, std::vector<int> & subsum )
	{
		typename std::vector<ELET>::iterator it1;
		std::vector<int>::iterator it2, it3;
		int i;

		i=0;
		for( it3=it2=subsum.begin(); it2!=subsum.end(); ++it2)
		{
			if( *it2<i || i==0 )
			{
				i = *it2;  //keep the best val
				it3 = it2; //keep the best pos
			}
		}

		it1 = memo.begin() + ( it3 - subsum.begin() );
		return *it1;
	}


	//删除最旧的重复项
	template < class ELET >
	static void StableDelOld( std::vector<ELET> & v )
	{
		for( typename std::vector<ELET>::iterator it = v.begin(); it != v.end(); )
		{
			typename std::vector<ELET>::iterator it2;

			it2 = it + 1;

			if( std::find( it2, v.end(), *it ) != v.end() )
			{
				//found
				v.erase( it );
				it = v.begin();
			}
			else
				++it;
		}
	}


	//删除 指定的 重复项
	template < class CNTNRT, class ELET >
	//static void StableDel( CNTNRT & v , const ELET & val )
	static void StableDel( CNTNRT & v , ELET val )
	{
		for( typename CNTNRT::iterator it = v.begin(); it != v.end(); )
		{
			if( *it == val )
			{
				//found
				v.erase( it );
				it = v.begin();
			}
			else
				++it;
		}
	}

};//end SSetu





X011_NAMESPACE_END

#endif






/*
cake, cakel
provide raw memory
*/

#ifndef X011__H_w_scake_h
#define X011__H_w_scake_h




X011_NAMESPACE_BEGIN



template < class CT >
class SCake_base
{
public:
	typedef /*typename*/ CT CkEle_t;

private:

	CT		*m_pbuf; 
	tsize	m_mysize; //元素个数，不是字节数。 it is not byte num, it is num of ele.

	mutable std::vector<CT>  m_FastAppendBuf;

private:

	void init(void) { 	m_pbuf=NULL; 	m_mysize=0; }

	void freeall(void)
	{
		if(m_pbuf) delete [] m_pbuf;
		m_mysize=0;
		init();
	}

public:

	SCake_base() {  init(); }
	
	SCake_base( const SCake_base<CT> & cakesource )
	{
		init(); 
		let(cakesource);
	}

	SCake_base( CT c ) { init(); let(&c,1); }

	SCake_base( const CT *psource, tsize isize ) { init(); let(psource,isize); }

	SCake_base( const tchar *psource ) { init(); lets(psource); } //for char* only

	SCake_base( const std::string & s) { init(); lets(s); } //for char* only


	virtual ~SCake_base( ) { freeall(); }


	//static std::string & trim( std::string & strCell, const tchar *str_space="\r\n \t" ) // double trim
	//{
	//	SCake ckCell;
	//	ckCell.lets( strCell );
	//	SStrf::strim( ckCell, str_space );
	//	return strCell = ckCell;
	//}

	//static std::string & trim( std::string & strCell, const tchar *str_space="\r\n \t" ) // double trim
	//{
	//	return wl::SStrf::strim( strCell );
	//}


	void copybuf( const CT *psource, CT *pdest, tsize isize, toffset iDestOffsetWhere = 0 )
	{
		if( psource == pdest && iDestOffsetWhere == 0 ) return;//think about c=c c.let(c) , same obj operations

		if( psource && pdest && isize )
		{
			for( tsize jtmp=iDestOffsetWhere; jtmp<isize+iDestOffsetWhere; jtmp++ )
				pdest[jtmp] = psource[jtmp-iDestOffsetWhere]; 
		}
	}
	

	void redim( tsize iNewSize, tbool reserve=0 )
	{
		if( iNewSize <= len() && iNewSize > len()/2 )
		{
			m_mysize = iNewSize;
		}
		else
		{
			CT *lbuf;
			if(iNewSize==0)
			{
				freeall();
				return;
			}
			lbuf = new CT[iNewSize] ;
			if(reserve) copybuf( m_pbuf, lbuf, iNewSize<m_mysize?iNewSize:m_mysize );
			freeall();
			m_pbuf = lbuf;
			m_mysize = iNewSize;
		}
	}

	const CT * buf_const() const
	{
		//FastAppendEnd();

		return m_pbuf;
	}


	CT * buf()
	{
		FastAppendEnd();

		return m_pbuf;
	}

	tsize len() const
	{ 
		return m_mysize;
	}

	void let( const CT *psource, tsize isize ) //knl
	{
		FastAppendEnd();

		redim(isize);
		copybuf( psource, m_pbuf, isize );
	}


	void let( const SCake_base<CT> & cakesource ) 
	{
		let( cakesource.buf_const(), cakesource.len() );
	}


	void lets( const CT *psource, CT c00 )
	{
		tsize i;
		const CT *p2;
		for(i=1,p2=psource;*p2!=c00;p2++)
			i++; //the c00 occupy one room. it is belong to data.
		let( psource, i );
	}


 	void lets( const tchar *psource ) //knl
	{
		if(psource)
		{
			redim( SStrf::slen(psource) + 1 );
			tsize jtmp;
			for( jtmp=0; psource[jtmp]; jtmp++ )
			{
				m_pbuf[jtmp] = psource[jtmp];
			}
			m_pbuf[jtmp] = 0;//the c00 occupy one room. it is belong to data.
		}
	}


	void lets( const std::string & s) { lets(s.c_str()); }

	void lets( tint32 i)  { lets( SStrf::sltoa(i) ); }

	void lets( tdouble d) { lets( SStrf::sftoa(d) ); }

	SCake_base<CT> & dump( SCake_base<CT> & cake2 ) //dump head part into cake2. keep the remaining(right part)
	{
		tsize iGoneSize;
		cake2.let( buf(), iGoneSize = ( len() < cake2.len() ? len() : cake2.len() ) ); // len()-iGoneSize= remain size or 0.
		SCake_base<CT> * ptmpcake = new SCake_base<CT>(*this);
		let( ptmpcake->buf() + iGoneSize, len() - iGoneSize );
		delete ptmpcake;
		return cake2;
	}


	SCake_base<CT> & cut( tsize howmany ) //cut off the right part. keep and return the left part.
	{
		if( howmany<=m_mysize) m_mysize -= howmany;
		else m_mysize = 0;
		return *this;
	}


	
	SCake_base<CT> & FastAppend( const SCake_base<CT> & cake2 ) // append into temp buf, refresh later
	{
		if( !this->m_pbuf ) return this->append(cake2);

		if(cake2.len()==0)
		{
			return *this;
		}

		this->m_mysize += cake2.len();
		std::copy( cake2.buf_const(), cake2.buf_const() + cake2.len(), std::back_inserter(m_FastAppendBuf) ); 

		return *this;
	}

	void FastAppendEnd()  
	{
		if( m_FastAppendBuf.empty() ) return;

		std::vector<CT>  FastBuf2(m_FastAppendBuf);

		m_FastAppendBuf.clear(); // append will call let() or buf(), which will call me again. clear to prevent it
		this->m_mysize -= (tsize)FastBuf2.size();
		this->append( &(FastBuf2[0]), (tsize)FastBuf2.size() );
	}



	SCake_base<CT> & append( const SCake_base<CT> & cake2 ) //bin style append 
	{
		if(cake2.len()==0)
		{
			//
		}
		else
		{
			CT *lbuf1;
			const CT *lbuf2;
			tsize len1,len2;
			lbuf1 = buf();
			lbuf2 = cake2.buf_const();
			len1 = len();
			len2 = cake2.len();
			redim( len1+len2, 1 );
			copybuf( lbuf2, buf(), len2, len1 );
		}
		return *this;
	}

	SCake_base<CT> & append( const CT *psource, tsize isize )
	{
		if( isize==0 || !psource )
		{
			//
		}
		else
		{
			CT *lbuf1;
			const CT *lbuf2;
			tsize len1,len2;
			lbuf1 = buf();
			lbuf2 = psource;
			len1 = len();
			len2 = isize;
			redim( len1+len2, 1 );
			copybuf( lbuf2, buf(), len2, len1 );
		}
		return *this;
	}

	SCake_base<CT> & append( CT val )
	{
		return append( &val, 1 );
	}


public:	//operators

	/*
	如果有
	class B {...}
	class D : public B {...}
	那，在D中显式调用B的operator =的方法是：
	D& operator = (const D& rhs) {
		this->B::operator =(rhs);  // 或者也可以写*static_cast<B*>(this) = *static_cast<const B*>(&rhs);
		// ...
		return *this;
	}*/

	SCake_base<CT> & operator = ( const SCake_base<CT> & cake2 )
	{
		let(cake2);
		return *this;
	}


	operator CT * ( )
	{
		return buf();
	}

    
	operator const CT * ( ) const
	{
		return buf_const();
	}

	int operator < ( const SCake_base<CT> & cake2 ) const
	{
		return ( (int)buf_const() < (int)cake2.buf_const() );
	}


}; //end of class SCake_base declare




////////////////////////////////////////////////////////////////////////////////
//a cake for tchar 

class SCake : public SCake_base<tchar>
{

public:
	
	SCake():SCake_base<tchar>( ) { }

	SCake(const SCake & ckSrc):SCake_base<tchar>( ckSrc ) {  }


	SCake(const SCake_base<tchar> & ckSrc):SCake_base<tchar>( ckSrc ) {  }

	SCake( tchar c ):SCake_base<tchar>( c ) {  }
	//wl::tuint8 cu;
	//cu = 0xff;
	//wl::SCake ck( cu );

	SCake(const tchar * psrc, tsize isize):SCake_base<tchar>( psrc, isize ) {  }

	SCake(const tchar *psrc):SCake_base<tchar>( psrc ) {  }

	SCake(const std::string & s):SCake_base<tchar>( s) { } 


	SCake & bs_en()
	{
		SCake *pck = new SCake;
		pck->redim( SStrf::bs_ensize( buf(), len() ) );
		SStrf::bs_en( buf(), len(), pck->buf() );
		*this = *pck;
		delete pck;
		return *this;
	}


	SCake & bs_de() //如果传入的bstr==""则bs_de()之后本CAKE变为NULL指针的长度为0的一个CAKE。
	{
		tsize iDatalen = SStrf::bs_desize( buf() );
		SStrf::bs_de( buf() );
		redim( iDatalen, 1 );
		return *this;
	}


	tchar * mk_sz()
	{
		append( SCake("") );
		return buf();
	}

	std::string & mk_str( std::string & strOut ) const
	{
		if( this->len() )
		{
			return strOut = std::string( this->buf_const(), this->len() );
		}
		return strOut = "";
	}

	std::string mk_str() const
	{
		std::string s1;
		return mk_str(s1);
	}




public:	//operators

	SCake & operator = ( const SCake & cake2 )
	{
		let(cake2);
		return *this;
	}



}; //end of class SCake  






///////////////////////////////////////////////////////////////////////////////
template < class cakeT, class CT >
class SCakel_base2 {

private:

	std::vector<cakeT *> m_vknl;

	void collect( tbool szstyle=1 ) //if szstyle, don't record middle sz00. record the last sz00 ofcourse
	{
		cakeT  * psc;
		tsize wholesize,copypoint;
		typename std::vector<cakeT *>::iterator it;
		for( wholesize=0,it=m_vknl.begin(); it!=m_vknl.end(); ++it )
		{
			wholesize += (*it)->len( );
			if(szstyle&&(*it)->len( )) wholesize--;
		}
		if(szstyle) wholesize++;
		psc = new cakeT ;
		psc->redim(wholesize);
		for( copypoint=0,it=m_vknl.begin(); it!=m_vknl.end(); ++it )
		{
			psc->copybuf( (*it)->buf(), psc->buf(),	(*it)->len(), copypoint );
			copypoint += (*it)->len();
			if(szstyle) copypoint--;
		}
		clean( );
		m_vknl.push_back( psc );
	}


private:

	SCakel_base2( const SCakel_base2 & ckl )
	{
		;
	}

public:

	SCakel_base2( ) { ; }

	virtual ~SCakel_base2( )
	{
		for( typename std::vector<cakeT *>::iterator it=m_vknl.begin();it!=m_vknl.end();++it)
			delete *it;
	} //this method doesn't destruct m_vknl, so faster.


	tsize hm(void) const
	{
		return (tsize)m_vknl.size();
	}


	std::vector<cakeT *> & knl( ) {
		return m_vknl;
	}


	cakeT  * get( tsize iwhere ) const
	{
		return ( hm( )==0 || iwhere>=hm( ) )?NULL:m_vknl[iwhere];
		//don't use & because user can modi the static obj. 
		//if clear the static obj every time then can't used in multi-thread env.
	}


	cakeT  * get( ) const 
	{
		return get( hm( )-1 );
	}


	cakeT  * get0( )
	{
		return get(0);
	}


	void add( const cakeT  & cakesource, tsize iwhere )
	{
		cakeT  * psc;
		psc = new cakeT ( cakesource );
		if(iwhere>hm()) iwhere=hm();
		m_vknl.insert( m_vknl.begin()+iwhere, psc );
	}


	void add( const cakeT  & cakesource )
	{
		cakeT  * psc;
		psc = new cakeT ( cakesource );	//psc->let( cakesource.buf(), cakesource.len() );
		m_vknl.push_back( psc );
	}


	void add0( cakeT  & cakesource ) { add(cakesource,0); }


	void del( tsize iwhere )
	{
		typename std::vector<cakeT *>::iterator it;
		if( !( hm( )==0 || iwhere>=hm( ) ) )
		{
			it = m_vknl.begin( ) + iwhere;
			delete *it;
			m_vknl.erase( it );
		}
	}

	void del()  { del(hm()-1); }

	void del0() { del(0); }


	void clean()
	{
		tsize iremain = 0;
		while( hm() > iremain )
			del();
	}

	void clean( tsize iremain )
	{
		while( hm() > iremain )
			del();
	}


	void clean0( tsize iremain = 0 )
	{
		while( hm() > iremain )
			del0();
	}

	void collectb( ) { collect(0); }

	void collects( ) { collect(1); }


	
	void scatter( const cakeT  & ckSrc , CT cSepC )//see cake, scatter it and append
	{
		tsize p1,p2;
		cakeT  ckTmp;
		for(p1=p2=0;p2<ckSrc.len();p2++)  
		{
			if( *(ckSrc+p2)==cSepC )
			{
				ckTmp.let( ckSrc+p1, p2-p1+1 );
				add( ckTmp );
				p1=p2+1;
			}
		}

		//see the last time, whether successed.
		if(p2) //if the for above runed at least once
		{
			p2--;
			if( *(ckSrc+p2)!=cSepC )
			{
				ckTmp.let( ckSrc+p1, p2-p1+1 );
				ckTmp.append( cakeT ( &cSepC,1 ) );
				add( ckTmp );
			}
		}
	}


	void scatter( CT cSepC=0 )// 
	{
		do //fakedo
		{
			if(hm()>1)
				collectb();

			if(hm()==0)
				break;

			scatter( *get0() , cSepC );

			del0();

		}while(0);
	}


	SCakel_base2<cakeT,CT> & append( const SCakel_base2<cakeT,CT> & cakel2 )
	{
		tsize len2,lcount;
		len2 = cakel2.hm();
		for(lcount=0;lcount<len2;lcount++)
		{
			add( *(cakel2.get(lcount)) );
		}
		return *this;
	}
	

public: //operators


	operator std::vector<cakeT *> & ( )
	{
		return knl( );
	}


	SCakel_base2<cakeT,CT> & operator = ( const SCakel_base2<cakeT,CT> & cakel2 )
	{
		clean();
		return append(cakel2);
	}


};
//end of class cakel_base2





/////////////////////////////////////////////////////////////////////////////////

template < class CT >
class SCakel_base : public SCakel_base2<  SCake_base<CT>, CT >
{
private:

	SCakel_base( const SCakel_base & ckl )
	{
		;
	}

public: 

	SCakel_base( ) { ; }


public: //operators

	SCakel_base<CT> & operator = ( const SCakel_base<CT> & cakel2 )
	{
		SCakel_base2<  SCake_base<CT>, CT >::clean();		
		return append(cakel2);
	}

};





//////////////////////////////////////////////////////////////////////////////////

//typedef SCake_base<tchar> SCake;

class SCakel : public SCakel_base2< SCake, tchar > 
{
private:

	SCakel( const SCakel & ckl )
	{
		;
	}

public:

	SCakel( ) { 	}

public:

	SCakel & append( const SCakel & cakel2 )
	{
		tsize len2,lcount;
		len2 = cakel2.hm();
		for(lcount=0;lcount<len2;lcount++)
		{
			add( *(cakel2.get(lcount)) );
		}
		return *this;
	}

public: //operators

	SCakel & operator = ( const SCakel & cakel2 )
	{
		clean();
		return append(cakel2);
	}

};






X011_NAMESPACE_END

#endif




/*
date, time, event
universal arithmetic
*/

#ifndef X011__H_w_sdte_h
#define X011__H_w_sdte_h




X011_NAMESPACE_BEGIN



class SDte
{
// id/od  it/ot  ie/oe

public:

	int m_year;
	int m_mon;
	int m_day;
	int m_hour;
	int m_min;
	int m_sec;
	//int m_msec;

private:

	static tbool d_is_leap_year(int y)
	{
		return y%400==0||y%4==0&&y%100!=0;
		/*If n Mod 400 = 0 Or (n Mod 4 = 0 And n Mod 100 <> 0) Then yes */
	}


	static int d_day_of_year(int y)
	{
		return d_is_leap_year(y)?366:365;
	}


	static int d_day_of_month(int y, int m)
	{
		tint8 Array[]={0, 31, 28, 31,30,31,30,31,31,30,31,30,31};
		if(m<1||m>12) m=1;
		return (int)(m==2 ? Array[m] + (d_is_leap_year(y)?1:0) : Array[m]);
	}


	static tchar * d_odget( SCakel_base<tchar> & abuf, tint32 od )
	{
		abuf.add( SCake_base<tchar>("000000000") );
		if(od<0) od *= -1;
		abuf.add( SCake_base<tchar>( SStrf::sltoa(od) ) );
		abuf.collects( );
		return abuf.get( )->buf( );
	}


	//now->l
	static time_t dt_mk(void)  
	{
		struct tm tmm, *tp;
		time_t timer;
		time(&timer);
		tp = (*SClib::p_localtime())(&timer);//struct tm *localtime( const time_t *timer );
		memcpy(&tmm, tp, sizeof(struct tm));
		return mktime(&tmm);
	}


	// l->t
	static int dt_mk( struct tm *ptm , time_t tmr)
	{
		struct tm *tp;
		tp = (*SClib::p_localtime())(&tmr);
		if(ptm!=NULL&&tp!=NULL) memcpy(ptm, tp, sizeof(struct tm));
		return tp!=NULL;	 
	}


	// l->s
	static void dt_mknow( int& y, int&m, int& d, int& hh, int& mi, int& ss ) //standard chg interface!!!
	{
		struct tm tmm;
		struct tm *tp;
		memset(tp=&tmm, 0, sizeof(struct tm));
		dt_mk(tp, dt_mk());
		y = tp->tm_year+1900;
		m = tp->tm_mon+1;
		d = tp->tm_mday;
		hh = tp->tm_hour;
		mi = tp->tm_min;
		ss = tp->tm_sec;
	}

	///////////////////////////////////////
	

	static struct tm & RegulateTmYear4( struct tm & t )
	{
		if( t.tm_year <= 999 )
		{
			t.tm_year += 1900;
		}
		return t;
	}

	static struct tm & RegulateTmYear2( struct tm & t )
	{
		if( t.tm_year > 1900 )
		{
			t.tm_year -= 1900;
		}
		return t;
	}


	static struct tm & Now( struct tm & t )
	{
		struct tm *tp;
		memset(tp=&t, 0, sizeof(struct tm));
		dt_mk(tp, dt_mk());
		tp->tm_year+=1900;
		return t;
	}


		
	//tm->l
	static time_t tm2l( struct tm t )
	{
		RegulateTmYear2(t);

		return mktime(&t);	//time_t mktime( struct tm *timeptr );
	}


	//l->tm
	static struct tm l2tm( time_t tmr )
	{
		struct tm *tp;
		struct tm tm2;

		SStrf::smemset(&tm2);

		//tp = localtime(&tmr);
		tp = (*SClib::p_localtime())(&tmr);

		if(tp!=NULL) memcpy(&tm2, tp, sizeof(struct tm));

		return tm2;	 
	}



	static tint32 idmk( const tchar * sDateTime )
	{
		if(!sDateTime) return 0;
		int y, m, d;
		(*SClib::p_sscanf())( sDateTime, "%d-%d-%d", &y, &m, &d );
		return idmk(y,m,d);
	}


	static tint32 idmk(int y, int m, int d, tint32 offset=0)//参数说明：年、月、日、偏移量日(正数为未来)
	{
		tint32 i,j;
		for(j=0,i=0;i<=(y-1);i++) j += d_day_of_year(i);
		for(i=1;i<=(m-1);i++) j += d_day_of_month(y,i); 
		return j = j + d + offset;
	}


	static int odgety( tint32 od )
	{
		tchar *t;
		SCakel_base<tchar> abuf;
		t = d_odget( abuf, od );
		t = SStrf::splast(t,3);
		*t=0; 
		return (int)SStrf::satol(t-4);
	}


	static int odgetm( tint32 od )
	{
		tchar *t;
		SCakel_base<tchar> abuf;
		t = d_odget( abuf, od );
		t = SStrf::splast(t,1);
		*t=0; 
		return (int)SStrf::satol(t-2);
	}


	static int odgetd( tint32 od )
	{
		tchar *t;
		SCakel_base<tchar> abuf;
		t = d_odget( abuf, od );
		t = SStrf::splast(t,0);
		return (int)SStrf::satol(t-1);
	}


	static tint32 id2o( tint32 id )
	{
		tint32 i1, i2, i3, i4;
		if(id<=0) 	 id=1;
		for(i1=0;id>d_day_of_year(i1);) {
			id -= d_day_of_year(i1);
			i1++;
		}
		for(i2=1;id>d_day_of_month(i1,i2);) {
			id -= d_day_of_month(i1,i2);
			i2++;
		}
		i3 = id;
		return i4 = 10000*i1 + 100*i2 + i3;
	}


	static tint32 od2i( tint32 od )
	{
		return idmk( odgety(od), odgetm(od), odgetd(od) );
	}


	static int idgety( tint32 id ) { return odgety( id2o(id) ); }

	static int idgetm( tint32 id ) { return odgetm( id2o(id) ); }

	static int idgetd( tint32 id ) { return odgetd( id2o(id) ); }

	static tint32 idnow( ) { int y,m,d,hh,mi,ss; dt_mknow(y,m,d,hh,mi,ss); return idmk(y,m,d); }

	static tint32 odnow( ) { return id2o(idnow()); }


	///////////////////////////////////////////////////////////////////////

	static tint32 itmk( const tchar * sDateTime )
	{
		if(!sDateTime) return 0;
		int h, m, s, i;
		(*SClib::p_sscanf())( sDateTime, "%d-%d-%d %d:%d:%d", &i, &i, &i, &h, &m, &s );
		return itmk(h, m, s);
	}

	
	static tint32 itmk(int h, int m, int s) 
	{
		return h*60*60+m*60+s;
	}

	static tint32 itgeth(tint32 it)		{	return it/3600; 	}

	static tint32 itgetm(tint32 it)		{	return it%3600/60; 	}

	static tint32 itgets(tint32 it)		{	return it%60;	}


	static tint32 it2o(tint32 it)
	{
		tchar s[7];
		(*SClib::p_sprintf())( s, "%02d%02d%02d", itgeth(it), itgetm(it), itgets(it) );
		return SStrf::satol(s);
	}


	static tint32 ot2i(tint32 ot)
	{
		SCake_base<tchar> ca("000000", 6);
		ca.append( SCake_base<tchar>(SStrf::sltoa(ot)) );
		int h,m,s;
		(*SClib::p_sscanf())( SStrf::splast(ca.buf(), 5), "%2d%2d%2d", &h,&m,&s);
		return itmk(h,m,s);	
	}


	static tint32 itnow( ) { int y,m,d,hh,mi,ss; dt_mknow(y,m,d,hh,mi,ss); return itmk(hh,mi,ss); }

	static tint32 otnow( ) { return it2o(itnow()); }

	static tdouble iemk( tint32 id, tint32 it) { return  id + (tdouble)it/(tdouble)86400; }


	static tdouble ie2o( tint32 id, tint32 it)
	{
		tint8 s[16];
		(*SClib::p_sprintf())(s, "%ld.%06ld", id2o(id), it2o(it) ); 
		return SStrf::satof(s);
	}

	static tdouble ie2o(tdouble ie)
	{
		tdouble d1, d2;
		d1 = floor(ie);
		d2 = 0.5 + ( (ie - floor(ie)) * 86400 ) ; 
		return ie2o((tint32)d1, (tint32)d2);
	}


	static tdouble oe2i(double oe)//return ie
	{
		tdouble od, ot;
		od = floor(oe);
		ot = 0.5 + ( (oe - floor(oe)) * 1e6 ) ;
		return iemk( od2i((tint32)od), ot2i((tint32)ot) );
	}


	static tdouble ienow()
	{
		return iemk( idnow(), itnow() );
	}

	
	static tdouble oenow() 
	{ 
		return ie2o( ienow() ); 
	}


	
	static std::string Db_oe( tint32 idNow=0, tint32 itNow=-1 ) //2008-02-13 15:22:33
	{
		if(idNow==0 ) idNow=idnow();
		if(itNow==-1) itNow=itnow();
		tchar sBuf[33];
		(*SClib::p_sprintf())(sBuf,"%d-%02d-%02d %02d:%02d:%02d",
					 idgety(idNow), idgetm(idNow), idgetd(idNow),  
					 itgeth(itNow), itgetm(itNow), itgets(itNow)	);
		return sBuf;
	}


	static std::string Pack_oe( tint32 idNow=0, tint32 itNow=-1 ) //20080213.152233
	{
		if(idNow==0 ) idNow=idnow();
		if(itNow==-1) itNow=itnow();
		return  SStrf::sftoa( ie2o( iemk( idNow, itNow ) ) );
	}



public:

	SDte()
	{
		m_year= 0;
		m_mon= 0;
		m_day= 0;
		m_hour= 0;
		m_min= 0;
		m_sec= 0;
		//m_msec= 0;
	}

	SDte( std::string str_dte )
	{
		if(str_dte=="") this->MakeNow();
		else
			Make( str_dte );
	}

	SDte( int iHour, int iMin, int iSec )
	{
		this->MakeNow();
		this->m_hour= iHour;
		this->m_min= iMin;
		this->m_sec= iSec;
	}

	virtual ~SDte() { ; }


	static double e_proctime()  //return seconds.
	{
		return (double)clock()/(double)CLOCKS_PER_SEC;
	}



	SDte & Make( std::string str_dte )
	{
		if( str_dte.find( "-" ) != std::string::npos && str_dte.find( ":" ) != std::string::npos ) // datetime
		{
			(*SClib::p_sscanf())( str_dte.c_str(), "%d-%d-%d %d:%d:%d", &m_year, &m_mon, &m_day, &m_hour, &m_min, &m_sec );
			return *this;
		}

		if( str_dte.find( "-" ) != std::string::npos && str_dte.find( ":" ) == std::string::npos ) // date
		{
			(*SClib::p_sscanf())( str_dte.c_str(), "%d-%d-%d", &m_year, &m_mon, &m_day );
			m_hour = 	m_min = m_sec = 0;
			return *this;
		}

		if( str_dte.find( "-" ) == std::string::npos && str_dte.find( ":" ) != std::string::npos ) // time
		{
			(*SClib::p_sscanf())( str_dte.c_str(), "%d:%d:%d", &m_hour, &m_min, &m_sec );
			m_year = m_mon  = 	m_day  =0;
			return *this;
		}

		tint32 oiid, oiit;

		if( str_dte.find( " " ) != std::string::npos ) //see od and ot
		{
			oiid = (tint32)SStrf::satol( SStrvs::vsa_get( str_dte, std::string(" "), 1, 0 ) );
			oiit = (tint32)SStrf::satol( SStrvs::vsa_get( str_dte, std::string(" "), 1, 1 ) );
		}
		else
		{
			oiid = (tint32)SStrf::satol( str_dte );
			oiit = 0;
		}
	
		oiid = this->od2i( oiid );
		oiit = this->ot2i( oiit );

		m_year = idgety( oiid );
		m_mon  = idgetm( oiid );
		m_day  = idgetd( oiid );

		m_hour = itgeth( oiit );
		m_min = itgetm(  oiit );
		m_sec = itgets(  oiit );


		//rebuild the datetime

		tint32 i;

		i = itmk( m_hour, m_min, m_sec );
		m_day += i / 86400;
		i %= 86400;
		m_hour = itgeth( i );
		m_min = itgetm( i );
		m_sec = itgets( i );

		i = idmk( m_year, m_mon, m_day );
		m_year = idgety( i );
		m_mon  = idgetm( i );
		m_day  = idgetd( i );


		return *this;	
	}


	static tbool IsValidDate( std::string strVal ) //yyyymmdd
	{
		if( strVal.length() != 8 ) return 0;
		std::string s1,s2;
		SDte d1;
		s1 = strVal + " 001122";
		d1.Make( s1 );
		s2 = d1.ReadStringPack();		 
		SStrf::sreplstr( s1, " ", "." );
		if( s1 != s2 ) return 0;
		return 1;
	}



	static tbool IsValidTime( std::string strVal ) //hhmiss
	{
		if( strVal.length() != 6 ) return 0;

		std::string s1 ;
		
		s1 = strVal.substr( 0, 2 );
		int i1 = SStrf::satol( s1 );
		if( i1 >= 24 ) return 0;

		s1 = strVal.substr( 2, 2 );
		i1 = SStrf::satol( s1 );
		if( i1 >= 60 ) return 0;

		s1 = strVal.substr( 4, 2 );
		i1 = SStrf::satol( s1 );
		if( i1 >= 60 ) return 0;

		return 1;
	}




	static tbool IsValidDateTime( std::string strVal ) //yyyymmddhhmiss
	{
		if( strVal.length() != 14 ) return 0;

		std::string s1,s2;
		SDte d1;
		s2 = strVal;
		s2.insert( 8, " " );
		d1.Make( s2 );
		s1 = d1.ReadStringPack();		 
		SStrf::sreplstr( s2, " ", "." );
		if( s1 != s2 ) return 0;
		return 1;
	}






	SDte & MakeNow()
	{
		struct tm  tnow;
		this->Now(tnow);
		m_year= tnow.tm_year;
		m_mon = tnow.tm_mon+1;
		m_day = tnow.tm_mday;
		m_hour= tnow.tm_hour;
		m_min = tnow.tm_min;
		m_sec = tnow.tm_sec;
		return *this;
	}


	static SDte GetNow()  //  wl::SDte::GetNow().ReadStringPack().c_str()
	{
		SDte s; 
		return s.MakeNow();
	}


	tint32 DiffDay( const SDte & dte2 ) const
	{
		tint32 d1, d2;

		d1 = this->idmk( m_year, m_mon, m_day ) ;
		d2 = dte2.idmk( dte2.m_year, dte2.m_mon, dte2.m_day ) ;

		return d1 - d2;
	}


	tdouble DiffSec( const SDte & dte2 ) const
	{
		tdouble d1, d2;

		d1 = (double)this->itmk( m_hour, m_min, m_sec );
		d2 = (double)dte2.itmk( dte2.m_hour, dte2.m_min, dte2.m_sec );

		return d1 - d2 + DiffDay(dte2) * 86400.0;
	}


	tint32 DiffSecInt( const SDte & dte2 ) const
	{
		tint32 d1, d2;

		d1 = (tint32)this->itmk( m_hour, m_min, m_sec );
		d2 = (tint32)dte2.itmk( dte2.m_hour, dte2.m_min, dte2.m_sec );

		return d1 - d2 + DiffDay(dte2) * 86400;
		/*	long a1,a2;
			a1 = wl::SDte("").DiffSecInt( wl::SDte("1970-1-1 00:00:00") );
			a2 = time(0);
			printf( "%X\n", a1 );
			printf( "%X\n", a2 );
			printf( "%X %u\n", a1-a2, a1-a2 );
		   a2的值小了8小时。
			*/
	}


	int WeekDay() const
	{
		int i2 = this->DiffDay( wl::SDte() );
		return (i2 - 2 ) % 7;
	}


	SDte & Relative( const SDte & dte2 )
	{
		m_year += dte2.m_year;
		m_mon  += dte2.m_mon;
		m_day  += dte2.m_day;
		m_hour += dte2.m_hour;
		m_min  += dte2.m_min;
		m_sec  += dte2.m_sec;

		tint32 i;

		i = itmk( m_hour, m_min, m_sec );
		m_day += i / 86400;
		i %= 86400;
		m_hour = itgeth( i );
		m_min = itgetm( i );
		m_sec = itgets( i );

		i = idmk( m_year, m_mon, m_day );
		m_year = idgety( i );
		m_mon  = idgetm( i );
		m_day  = idgetd( i );

		return *this;
	}

	
	SDte & RelativeSec( tint32 sec2 )
	{
		SDte dte2;
		dte2.m_year = dte2.m_mon = dte2.m_day = dte2.m_hour = dte2.m_min = 0;
		dte2.m_sec = sec2;
		return Relative(dte2);
	}



	std::string ReadString() const //2008-02-13 15:22:33
	{
		tchar sBuf[33];
		(*SClib::p_sprintf())(sBuf,"%d-%02d-%02d %02d:%02d:%02d",
					 m_year, m_mon, m_day,  
					 m_hour, m_min, m_sec	);
		return sBuf;
	}

	std::string ReadStrDate() const // 2008-02-13 
	{
		tchar sBuf[33];
		(*SClib::p_sprintf())(sBuf,"%d-%02d-%02d",
					 m_year, m_mon, m_day );
		return sBuf;
	}

	std::string ReadStrTime() const // 15:22:33
	{
		tchar sBuf[33];
		(*SClib::p_sprintf())(sBuf,"%02d:%02d:%02d",
					 m_hour, m_min, m_sec	);
		return sBuf;
	}


	std::string ReadStringPack( char c = '.' ) const //20080213.152233
	{
		tchar sBuf[33];
		(*SClib::p_sprintf())(sBuf,"%d%02d%02d%c%02d%02d%02d",
					 m_year, m_mon, m_day,  c , 
					 m_hour, m_min, m_sec	);
		return sBuf;
	}

	std::string ReadStrPackDate() const //20080213
	{
		tchar sBuf[33];
		(*SClib::p_sprintf())(sBuf,"%d%02d%02d",
					 m_year, m_mon, m_day 	);
		return sBuf;
	}

	std::string ReadStrPackTime() const // 152233
	{
		tchar sBuf[33];
		(*SClib::p_sprintf())(sBuf,"%02d%02d%02d",
					 m_hour, m_min, m_sec	);
		return sBuf;
	}


	std::string Read_dt1() const //dd-MMM-yyyy
	{
		tchar sBuf[33];
		const tchar *s2[] = {"aa","Jan", "Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec" };
		(*SClib::p_sprintf())(sBuf,"%d-%s-%d",
								m_day,s2[m_mon], m_year );
		return sBuf;
	}


	operator std::string () const
	{
		return ReadStringPack() ;
	}


};//end of SDte






X011_NAMESPACE_END

#endif




/*
file new,del,select,read,write
*/

#ifndef X011__H_w_sfile_h
#define X011__H_w_sfile_h




X011_NAMESPACE_BEGIN



class SFile
{

private:

	std::string m_strFilename;

public:

	SFile()
	{
		bind("");
	}


	SFile( std::string fn )
	{
		bind(fn);
	}


	virtual ~SFile()
	{ ;
	}


	static std::string GetPathSep()
	{
		return "\\";
	}


	static std::string MkDir2Path( std::string strPathOrDir ) 
	{
		if( strPathOrDir.length() )
		{
			const tchar * t;
			t = SStrf::splast( strPathOrDir.c_str() );
			if( *t == GetPathSep()[0] )
			{
				return strPathOrDir;
			}
		}
		
		return strPathOrDir + GetPathSep();
	}


	

	static void Dir2Path( std::string & strPathOrDir ) 
	{
		strPathOrDir = MkDir2Path(strPathOrDir);
	}





	void bind( std::string fn )
	{
		m_strFilename = fn;
	}



	tbool bind_nofile( std::string strPath, const tchar * pszExt = NULL , int iThreadId = 0 ) // ext不一定必须带点
	{
		static int iName1 = 0;
		tdouble dName2;
		int k=0;
		std::string strNameExt(pszExt?pszExt:".tmp");
		std::string strGoodPathfilename;

		// 
		strPath = MkDir2Path( strPath );

		if( pszExt && *pszExt!='.' ) strNameExt = std::string(".") + pszExt;

		do
		{
			iName1--;
			dName2 = SStrf::rand1();
			strGoodPathfilename = strPath + "h" + SStrf::sltoa(iName1) + "_" + SStrf::sltoa(iThreadId) + SStrf::sftoa(dName2) + strNameExt;
			bind(strGoodPathfilename);
			if(canoutput()) return 1;
			if( k ++ > 9 )
			{
				if(!erase())
				{
					bind("");
					return 0;
				}
			}
		}while(1);
	}


	std::string filename() const
	{
		return m_strFilename;
	}


	//operator std::string & () 
	//{
	//	return m_strFilename;
	//}

	operator std::string () const
	{
		return m_strFilename; 
	}

	operator const tchar * () const
	{
		return m_strFilename.c_str();
	}


	tbool erase()
	{
		return 0==remove( m_strFilename.c_str() )?1:0;
	}

	static tbool erase(std::string strfilename)
	{
		return 0==remove( strfilename.c_str() )?1:0;
	}


	tbool exists()
	{
		FILE *fp;
		tbool rc;
		if( m_strFilename=="" )
		{
			return 0;
		}
		fp = (*SClib::p_fopen())( m_strFilename.c_str(), "rb" );
		if(fp==NULL) rc=0;
		if(fp!=NULL)
		{
			rc=1; fclose(fp);
		}
		return rc;
	}


	tbool caninput()
	{
		return exists();
	}


	tbool canoutputabs()
	{ 
		FILE *fp;
		fp = (*SClib::p_fopen())(m_strFilename.c_str(),"wb");
		if(fp==NULL) return 0;
		fclose(fp);
		return erase();
	}


	tbool canoutput()
	{	//safely create. means if exists then can't .
		if(exists()) return 0;
		return canoutputabs();
	}


	tsize len()
	{
		if( !exists() ) return 0;
		tsize flen;
		FILE *fp;
		fp = (*SClib::p_fopen())( m_strFilename.c_str(), "rb" );
		fseek( fp,0,SEEK_END );
		flen=ftell(fp);
		fclose(fp);
		return flen;
	}


	tbool read( SCake_base<tchar> & buf, tsize a_extra_bytes = 0 ) //bin read
	{
		if(!this->exists()) return 0;
		FILE *fp;

		fp = (*SClib::p_fopen())( m_strFilename.c_str(), "rb" );
		if( fp == NULL )
		{
			return 0;
		}

		tsize flen;
		fseek( fp,0,SEEK_END );
		flen=ftell(fp);
		fseek( fp,0,SEEK_SET );


		//if( flen == 0) 
		//{
		//	fclose(fp);
		//	return 0 ;
		//}


		buf.redim( flen + a_extra_bytes );

		if(a_extra_bytes) 
		{
			SStrf::smemset( buf.buf(), 0, flen + a_extra_bytes ); //the a_extra_bytes may be > 1
			//*( buf.buf() + ( flen + a_extra_bytes ) - 1 ) = 0;
		}

		if(flen) fread( buf.buf(), flen, 1, fp );

		fclose(fp);

		return 1;
	}


	tbool read_str( SCake_base<tchar> & buf ) // read content and add a c00 to form a string //read str means read an extra c00.
	{
		return this->read( buf, 1 );
	}


	tbool read_str( std::string & strRtnBuf )
	{
		SCake_base<tchar> buf;
		strRtnBuf = "";
		if( read_str(buf) )
		{
			strRtnBuf = buf.buf();
			return 1;
		}
		return 0;
	}


	tbool read_vecstr( std::vector<std::string> & vecLines, std::string strSep, tbool istoken = 1 )
	{
		wl::SCake ckData;
		if( !read_str( ckData ) ) return 0;
		if( !ckData.len() ) return 0;
		SStrvs::vsa_imp( std::string(ckData.buf()), strSep, istoken, vecLines );
		return 1;
	}



	tbool write( const void * pbuf, tsize len, tbool bIsAppend = 0 ) //bin write
	{
		FILE *fp;
		tbool rc;

		rc=0;

		do
		{
			if( len == 0 ) break;
			if( !pbuf ) break;
			fp = (*SClib::p_fopen())( m_strFilename.c_str( ), bIsAppend?"ab":"wb" );
			if(fp==NULL) break;
			rc = fwrite( pbuf, len, 1, fp )?1:0 ;
			fclose(fp);
		}while(0);

		return rc?1:0 ;
	}



	tbool write( const SCake_base<tchar> & buf, tbool bIsAppend = 0 ) //bin write
	{
		FILE *fp;
		tbool rc;

		rc=0;

		do
		{
			if( buf.len()==0 ) break;
			if( !buf.buf_const() ) break;
			fp = (*SClib::p_fopen())( m_strFilename.c_str( ), bIsAppend?"ab":"wb" );
			if(fp==NULL) break;
			rc = fwrite( buf.buf_const(), buf.len(), 1, fp )?1:0 ;
			fclose(fp);
		}while(0);

		return rc?1:0 ;
	}


	tbool write_str( const tchar * buf, tbool bIsAppend = 0 )//write a string. not include the sz c00. //write str means not write c00.
	{
		FILE *fp;
		tbool rc;

		rc=0;

		do
		{
			if( NULL == buf ) break;
			fp = (*SClib::p_fopen())( m_strFilename.c_str(), bIsAppend?"ab":"wb" );
			if(fp==NULL) break;
			if( fwrite( buf, SStrf::slen(buf), 1, fp ) )//if slen(buf)==0 then write a 0 len file.
			{
				rc = 1; 
			}
			else
			{
				rc = 0;
			}
			fclose(fp);

		}while(0);

		return rc?1:0 ;
	}


	tbool write_str( const std::string & buf, tbool bIsAppend = 0 )//not include the sz c00.
	{
		return write_str( buf.c_str(), bIsAppend );
	}


	tbool write_vecstr( const std::vector<std::string> & vecLines, std::string strSep, tbool bIsAppend = 0 )
	{
		std::string strOut;

		for( std::vector<std::string>::const_iterator it = vecLines.begin(); it != vecLines.end(); ++it )
		{
			strOut += *it + strSep;
		}

		return write_str(strOut, bIsAppend);
	}


	//
	tbool IsHeadOf( SFile & me2 )
	{
		if( !SStrf::scmpi( this->filename().c_str(), me2.filename().c_str() ) ) return 0; //same file, not include.
		if( !this->exists() ) return 0;
		if( !me2.exists()   ) return 0;

		tsize i1, i2;

		if( (i1 = this->len()) == 0 ) return 0;
		if( (i2 = me2.len()) == 0   ) return 0;

		if( i1 > i2 ) return 0;

		SCake ck1, ck2;

		this->read( ck1 );
		me2.read( ck2 );

		if( !memcmp( ck1.buf(), ck2.buf(), i1 ) ) return 1;

		return 0;
	}

	
	//
	tbool IsHeadOf( std::string strme2 )
	{
		SFile sf2;
		sf2.bind(strme2);
		return IsHeadOf(sf2);
	}

};//end SFile





X011_NAMESPACE_END

#endif







/*
SNava  means NAme-VAlue pair
*/

#ifndef X011__H_w_SNava_h
#define X011__H_w_SNava_h



X011_NAMESPACE_BEGIN



template< class nameT, class valueT >
class SNava_base
{
public:

	typedef typename std::map< nameT, valueT >::iterator	MAP_MAPKNL_IT;
	typedef typename std::map< nameT, valueT >::const_iterator  MAP_MAPKNL_CONSTIT;

	MAP_MAPKNL_IT m_it4name;

public:

	std::map< nameT, valueT >  m_mapKnl;
	

public:

	virtual ~SNava_base() {;} 
	

	void clear()
	{
		m_mapKnl.clear();
	}


	tbool IsEmpty()
	{
		if( m_mapKnl.empty() ) return 1;
		return 0;
	}


	tbool let( const nameT & name, const valueT & val )
	{
		//m_mapKnl.insert( std::pair< nameT, valueT >( name, val ) ); //if there already have one value, the insert will do nothing.
		m_mapKnl[name] = val; //this method will overwrite the current value, if existed.
		return 1;
	}


	tbool get( const nameT & name, valueT & val )
	{
		MAP_MAPKNL_IT it;
		it = m_mapKnl.find( name );
		if( it != m_mapKnl.end() )
		{
			val = it->second;
			return 1;
		}
		return 0;
		//return m_mapKnl[name];
	}


	valueT & get( const nameT & name )
	{
		return m_mapKnl[name];
	}


	tbool del( const nameT & name )
	{
		MAP_MAPKNL_IT it;
		it = m_mapKnl.find( name );
		if( it != m_mapKnl.end() )
		{
			m_mapKnl.erase(it);
			return 1;
		}
		return 0;
	}


	tbool GetFirstName( nameT & Name )
	{
		m_it4name = m_mapKnl.begin();
		if( m_it4name != m_mapKnl.end() )
		{
			Name = m_it4name->first;
			return 1;
		}
		return 0;
	}


	tbool GetNextName( nameT & Name )
	{
		m_it4name ++;
		if( m_it4name != m_mapKnl.end() )
		{
			Name = m_it4name->first;
			return 1;
		}
		return 0;
	}


	tbool operator < ( const SNava_base & rhs) const
	{
		return ( m_mapKnl < rhs.m_mapKnl ? 1 : 0 );
	}

	tbool operator <= ( const SNava_base & rhs) const
	{
		return ( m_mapKnl <= rhs.m_mapKnl ? 1 : 0 );
	}

	tbool operator > ( const SNava_base & rhs) const
	{
		return ( m_mapKnl > rhs.m_mapKnl ? 1 : 0 );
	}

	tbool operator >= ( const SNava_base & rhs) const
	{
		return ( m_mapKnl >= rhs.m_mapKnl ? 1 : 0 );
	}

	tbool operator == ( const SNava_base & rhs) const
	{
		return ( m_mapKnl == rhs.m_mapKnl ? 1 : 0 );
	}
};




class SNavass : public SNava_base< std::string, std::string >
{
private:

	static void seri_element_en( SCake & ck )
	{
		if( ck.len() == 0 ) return;
		ck.bs_en();
	}

	static void seri_element_de( SCake & ck )
	{
		if( ck.len() == 0 ) return;
		ck.bs_de();
		if( !ck.buf() ) ck.lets(""); //because "" means NULL pointer, just prevent this.
	}

public:
	virtual ~SNavass() {;} 
	
	
	void imp( const std::string & ssource, std::string ssepTR, std::string ssepTD )
	{
		SStrvs::vsa2v_prpt( ssource, ssepTR, ssepTD , m_mapKnl );  
	}

	
	void trimall()
	{
		std::map< std::string, std::string > mapTmp = m_mapKnl;

		this->clear();

		for( MAP_MAPKNL_IT it = mapTmp.begin(); it != mapTmp.end(); ++it )
		{
			std::string s1 = it->first;
			std::string s2 = it->second;

			SStrf::strim( s1 );
			SStrf::strim( s2 );

			this->let( s1, s2 ); 
		}
	}


	tbool serialize( std::string & strOut ) const
	{
		strOut = "";

		SCake ckTmp;

		for( MAP_MAPKNL_CONSTIT it = m_mapKnl.begin(); it != m_mapKnl.end(); ++it )
		{
			ckTmp.lets( it->first );
			seri_element_en( ckTmp );
			strOut += ckTmp.buf();

			strOut += "(";

			ckTmp.lets( it->second );
			seri_element_en( ckTmp );
			strOut += ckTmp.buf();

			strOut += ")";
		}

		return 1;
	}


	tbool unserialize( const std::string & strData )
	{
		std::map< std::string, std::string > mapTmp;
		SCake ckTmp1,ckTmp2;

		SStrvs::vsa2v_prpt( strData, std::string(")"), std::string("(") , mapTmp );
		this->clear();

		for( MAP_MAPKNL_IT it = mapTmp.begin(); it != mapTmp.end(); ++it )
		{
			ckTmp1.lets( it->first );
			seri_element_de( ckTmp1 );
			ckTmp2.lets( it->second );
			seri_element_de( ckTmp2 );

			let( std::string(ckTmp1.buf()), std::string(ckTmp2.buf()) ); 
		}

		return 1;
	}

};




X011_NAMESPACE_END

#endif




/*
 Peco operation , 排列组合问题
*/

#ifndef X011__H_w_SPeco_h
#define X011__H_w_SPeco_h



X011_NAMESPACE_BEGIN


template < class itT >	//all containers must be same type.
class SPeco
{
public:
	
	typedef typename std::vector< itT > RTNVEC_T;
	typedef typename std::vector< itT >::iterator RTNVEC_IT;

private:

	std::vector< itT >  m_begin;
	std::vector< itT >  m_end;

	std::vector< itT >  m_beginBak;
	std::vector< itT >  m_endBak;

	tbool m_canfetchflag;

	std::set< RTNVEC_T > m_comb_buf;

public:

	SPeco(){ GotoBegin();} 

	virtual ~SPeco(){;}
	
public:	 

	void RegIt( itT itbegin , itT itend )
	{
		if( itbegin != itend )
		{
			m_begin.push_back( itbegin );
			m_end.push_back( itend );

			m_beginBak.push_back( itbegin );
			m_endBak.push_back( itend );
		}
	}


	void GotoBegin()
	{
		m_begin = m_beginBak;
		m_end = m_endBak;

		m_comb_buf.clear();

		m_canfetchflag = 1;
	}


	//排列
	tbool Fetch( RTNVEC_T & v_rtn ) //元素个数等于注册次数, 当前指向未处理的一个元素
	{
		v_rtn.clear();

		typename std::vector<itT>::size_type i;
		tbool plusflag(1);

		if( m_canfetchflag == 0 ) return m_canfetchflag;

		for( i = 0 ; i < m_begin.size() ; i++ )
		{
			itT & myit( m_begin[i] );

			v_rtn.push_back( myit );	//在RegIt中保证不会注册空。

			if( plusflag )
			{
				myit++;
				plusflag = 0;
			}

			if( myit == m_end[i] ) 
			{
				myit = m_beginBak[i];
				plusflag = 1;
			}
		}

		if( plusflag ) //最后一组仍然指示下一组需要进位，则说明现在返回的是最后一个排列。再次调用fetch则会从头。
		{
			m_canfetchflag = 0;
		}

		return 1;
	}


	//排列
	tbool FetchNodup( RTNVEC_T & v_rtn ) //元素不可重复出现.
	{
		tbool b;

		for( ; ; )
		{
			b = Fetch( v_rtn );
			
			if( !b )
				return 0;

			std::vector< itT > v2;

			SSetu::vs_setgroup( v_rtn, v2 );

			if( v_rtn.size() == v2.size() )
				return b;
		}
	}


	//组合
	void MakeComb( tbool HaveDup = 1 ) //填充comb buf
	{
		m_comb_buf.clear();

		do
		{
			RTNVEC_T v;
			tbool b;

			if( HaveDup ) b = Fetch( v );
			else b = FetchNodup( v );

			if( !b )
			{
				break;
			}

			std::sort( v.begin(), v.end() );

			m_comb_buf.insert( v );
			 
		}while( 1 );
	}


	//从buf 中取得组合
	tbool FetchComb( RTNVEC_T & v_rtn ) //
	{
		if( m_comb_buf.empty() ) return 0;

		v_rtn = * m_comb_buf.begin();

		m_comb_buf.erase( m_comb_buf.begin() );
		
		return 1;
	}


};//end SPeco





X011_NAMESPACE_END

#endif






/*
binary knl
anti-bayes arithmatic
*/

#ifndef X011__H_w_SAbys_h
#define X011__H_w_SAbys_h




X011_NAMESPACE_BEGIN



class SAbys
{

private:

	SCake		m_knowledge_cake;
	tsize		m_knowledge_cur_pos;
	tdouble		m_data_knowledge_ratio;
	
	//data, knowledge, mixeddata 
	/*data can be any bin data. evalute bstr first to transfer it into sz format.
	  knowledge can be any bin format. mix them.
	  knowledge should be a sz and without its last c00. this would be better to transmit.
	  also, knowledge is supposed to have not \n, for the mixed result may transmit through internet.

	  mixeddata: a cake. bin mixed. the last c00 is out of range. just for debug use.
	  unmix: turn mixeddata(a cake) to original data. return a cake.
	*/
 
public:

	SAbys() 
	{ 
		init( 23.6 );
	}

	SAbys( tdouble ratio ) 
	{ 
		init( ratio );
	}

	SAbys( const SCake & cakeKnow ) 
	{  
		init(cakeKnow);
	}

	virtual ~SAbys( )
	{ ; }


	void init( tdouble data_knowledge_ratio = 1.0 )
	{
		SStrf::initrand(); 
		SCake ckTmp( SStrf::sftoa( SStrf::rand1() ) + SStrf::sftoa( SStrf::rand1() ) );
		ckTmp.cut(1);
		init( ckTmp , data_knowledge_ratio );
	}


	void init( const SCake & knowledge_cake , tdouble data_knowledge_ratio = 1.0 )
	{
		if(knowledge_cake.len()>0)
			m_knowledge_cake = knowledge_cake;
		else
			init(data_knowledge_ratio);
		m_knowledge_cur_pos = (tsize)(m_knowledge_cake.len() * SStrf::rand1());
		m_data_knowledge_ratio = data_knowledge_ratio>0?data_knowledge_ratio:1;
	}


	void mix( const SCake & ck_Data /*IN*/ , 
			  SCake & ck_Mixeddata /*OUT*/ ,
			  tchar chSep = '('		)
	{
		SCake ck_dubious_data = ck_Data;
		ck_dubious_data.bs_en();

		SStrf::srev( ck_dubious_data );
		tsize iKnowLen = (tsize)(ck_Data.len()/m_data_knowledge_ratio);
		ck_Mixeddata.redim( ck_dubious_data.len() + iKnowLen + 1 );
		SStrf::scpy( ck_Mixeddata, ck_dubious_data );
		ck_dubious_data.cut(1);
		tsize iPnt = ck_dubious_data.len();
		*(ck_Mixeddata.buf()+iPnt) = chSep;
		iPnt++;
		for(ck_Mixeddata.cut(1);iPnt!=ck_Mixeddata.len();iPnt++)
		{
			m_knowledge_cur_pos++;
			if(m_knowledge_cur_pos>=m_knowledge_cake.len()) m_knowledge_cur_pos=0;
			*(ck_Mixeddata.buf()+iPnt) = *(m_knowledge_cake.buf()+m_knowledge_cur_pos);
		}
		*(ck_Mixeddata.buf()+iPnt) = 0;
	}

	std::string mix( const SNavass & nv )
	{
		std::string str;
		nv.serialize(str);
		SCake ck1( str );
		SCake ck2;
		mix( ck1, ck2 );
		return ck2.buf();
	}

	std::string & mix( const std::string & str , std::string & strOut )
	{
		SCake ck1( str );
		SCake ck2;
		mix( ck1, ck2 );
		strOut = ck2.buf();
		return strOut;
	}


	void unmix(  const SCake & ck_Mixeddata,		 /*IN*/ 
				 SCake	 & ck_Data					/*out*/	,
				 tchar chSep = '('		)
	{
		SCake ck0("");
		SCake ckMixDataWriteable( ck_Mixeddata );

		ckMixDataWriteable.append( ck0 );

		tchar strSep[2];

		strSep[0] = chSep;
		strSep[1] = 0;

		ck_Data.lets( SStrvs::vsa_get( std::string(ckMixDataWriteable), std::string(strSep), 1, 0 ) );
		SStrf::srev( ck_Data );
		tsize iDatalen = SStrf::bs_desize( ck_Data );
		//SStrf::bs_de( ck_Data );
		ck_Data.bs_de();
		ck_Data.redim( iDatalen, 1 );
	}

	void unmix( const std::string & strSource, SNavass & nv )
	{
		SCake ck1( strSource );
		SCake ck2;
		unmix( ck1, ck2 );
		ck2.mk_sz();
		nv.unserialize( std::string(ck2) );
	}
	
	std::string & unmix( const std::string & strSource, std::string & strOut )
	{
		SCake ck1( strSource );
		SCake ck2;
		unmix( ck1, ck2 );
		ck2.mk_sz();
		strOut = ck2.buf();
		return strOut;
	}

	
	void envelop( 	const SCake & ckKeyWord, 
					const SCake & ckHead, const SCake & ckTail, const SCake & ck_src, SCake & ck_destbuf )
	{
		//if  KeyWord is in  Head, then change Head, let Head doesn't contain KeyWord. one char change for once would be enough.
	}
	
	tbool unenvelop( const SCake & ckKeyWord, 
					 const SCake & ck_src, SCake & ck_destbuf	)
	{
		return 1;
	}

};
//end class SAbys 





X011_NAMESPACE_END

#endif




/*
rice
*/

#ifndef X011__H_w_IRice_h
#define X011__H_w_IRice_h




X011_NAMESPACE_BEGIN



class IRice
{

protected:

	SCake m_ckDataL2CacheBuf;


protected:

	tsize sys_recv( SCake & ckDataBuf )
	{
		int i = on_sys_recv(ckDataBuf); //no matter how long received, just got the rtn.
		if(i)
		{
			return i;
		}
		else
		{
			ckDataBuf.redim(0);
			return 0;
		}
	}


	tsize sys_send( const SCake & ckDataBuf )
	{
		return on_sys_send(ckDataBuf);
	}



public:

	IRice( )
	{
		//
	}


	virtual ~IRice( )
	{ ; }


	void ClearL2Cache()	
	{
		m_ckDataL2CacheBuf.redim(0);
	}


	tbool send_str( std::string s ) //return if send success
	{
		return send_str(s.c_str());
	}

	
	tbool send_str( const tchar *s ) //return if send success //write str means not write c00.
	{
		SCake ckTmp(s);
		ckTmp.cut(1);
		return send_bin( ckTmp );
	}


	tbool send_bin( const SCake & ckData )
	{
		tsize rc, k;
		if(ckData.len()==0) return 0;
		for(k=0;;)
		{
			SCake ckTmp(ckData.buf_const()+k, ckData.len()-k);
			rc = sys_send( ckTmp );
			if(rc==0) return 0;
			k += rc;
			if(k>=ckData.len()) break;
		}
		return 1;
	}


	template<class T>
	tbool send_bin( T adata )
	{
		SCake ck;
		ck.let( (SCake::CkEle_t*)&adata, sizeof(T) );
		return send_bin(ck);
	}


	//tbool send_esc( SCake ckData , tchar a1, tchar a2, tchar a3 ) //for com use
	//{
	//	ckData.comesc_en(a1,a2,a3);
	//	return send_bin( ckData );
	//}




	tbool recv_bin( SCake & ckData ) //current available data
	{
		SCake ckTmp;

		if( m_ckDataL2CacheBuf.len() == 0 )//如果不判断，上来就接收，会block在这里。
		{
			sys_recv( ckTmp ); //没有L2数据时我们才真去接收.
			m_ckDataL2CacheBuf.append(ckTmp);//其实这里就是直接等于收到的所有数据。
		}
		else
		{
			//
		}

		ckData = m_ckDataL2CacheBuf;
		m_ckDataL2CacheBuf.redim(0);
		return ckData.len()==0?0:1;
	}


	tbool recv_all( SCake & ckData ) //all data of this session
	{
		SCake ckTmp;
		do
		{
			if( !sys_recv( ckTmp ) ) break;
			m_ckDataL2CacheBuf.append(ckTmp);

			if( !on_chk_L2CacheLen( m_ckDataL2CacheBuf ) ) break; //chk long data

		}while(ckTmp.len()>0);

		ckData = m_ckDataL2CacheBuf;
		m_ckDataL2CacheBuf.redim(0);
		return ckData.len()==0?0:1;
	}


	
	tbool recv_all_f( SCake & ckData ) //all data of this session, fast append
	{
		SCake ckTmp;
		do
		{
			if( !sys_recv( ckTmp ) ) break;
			//m_ckDataL2CacheBuf.append(ckTmp);
			m_ckDataL2CacheBuf.FastAppend(ckTmp);

			//if( !on_chk_L2CacheLen( m_ckDataL2CacheBuf ) ) break; //chk long data

		}while(ckTmp.len()>0);

		m_ckDataL2CacheBuf.FastAppendEnd();

		ckData = m_ckDataL2CacheBuf;
		m_ckDataL2CacheBuf.redim(0);
		return ckData.len()==0?0:1;
	}


	tbool recv_len( SCake & ckData , tsize iWantDataLen ) //appointed lenth of data
	{
		SCake ckTmp;

		while( m_ckDataL2CacheBuf.len()< iWantDataLen )
		{
			if( !sys_recv( ckTmp ) ) break;

			//m_ckDataL2CacheBuf.append(ckTmp);
			m_ckDataL2CacheBuf.FastAppend(ckTmp);
		}

		m_ckDataL2CacheBuf.FastAppendEnd();
		
		ckData.redim(iWantDataLen);
		m_ckDataL2CacheBuf.dump( ckData );//maybe dumped less than appointed len of data, if not enough len of data available and remote died.
		return ckData.len()+m_ckDataL2CacheBuf.len()==0?0:1;
	}


	
	tbool recv_ln( SCake & ckData , const std::vector<std::string> & vecstrSeperate, std::string * pstrRealSep=NULL ) //pstrRealSep to return real seperator 
	{
		SCake ckTmp;
		tchar * pSep;
		SCake ckSepDumpTmp;
		
		do
		{
			SCake ckTmpL2Cache2;
			ckTmpL2Cache2 = m_ckDataL2CacheBuf;
			ckTmpL2Cache2.mk_sz();
			
			pSep = NULL;

			if(pstrRealSep) *pstrRealSep = "";

			//pSep = SStrf::sstr( m_ckDataL2CacheBuf, strSeperate );	//the L2cache is not a sz. use strstr will cause run-time error.
			for( std::vector<std::string>::const_iterator it = vecstrSeperate.begin();
				 it != vecstrSeperate.end();
				 ++it )
			{
				pSep = SStrf::sstr( ckTmpL2Cache2, it->c_str() );
				if( pSep )
				{
					if(pstrRealSep) *pstrRealSep = *it;

					ckSepDumpTmp.lets(*it);
					ckSepDumpTmp.cut(1); //the strSeperate is sz. remove the last '\0'
					break;
				}
			}
			
			
			if( pSep )
			{
				//ckData.redim( (tsize)(pSep - m_ckDataL2CacheBuf.buf() ) ); 
				ckData.redim( (tsize)(pSep - ckTmpL2Cache2.buf() ) );
				
				m_ckDataL2CacheBuf.dump( ckData );
				m_ckDataL2CacheBuf.dump( ckSepDumpTmp ); //get rid of the leading sep str in L2Cache. 
				return 1;
			}
			
			if( !sys_recv( ckTmp ) ) break;
			m_ckDataL2CacheBuf.append(ckTmp);

			if( !on_chk_L2CacheLen( m_ckDataL2CacheBuf ) ) break; //chk long line

		}while(ckTmp.len()>0);

		ckData = m_ckDataL2CacheBuf;	//找到sep的情况已在while中return。这里是收失败时的情况了。
		m_ckDataL2CacheBuf.redim(0);
		return ckData.len()==0?0:1;
	}

		
	tbool recv_ln( SCake & ckData , const tchar * strSeperate = "\n" ) //use Seperate
	{
		if( strSeperate && std::string(strSeperate) == "\r\n\r\n\r\n" )
			return recv_ln2( ckData , strSeperate );
		
		SCake ckTmp;
		tchar *pSep;
		SCake ckSepDumpTmp(strSeperate);
		
		ckSepDumpTmp.cut(1); //the strSeperate is sz. remove the last '\0'
		
		do
		{
			SCake ckTmpL2Cache2;
			ckTmpL2Cache2 = m_ckDataL2CacheBuf;
			ckTmpL2Cache2.mk_sz();
			
			//pSep = SStrf::sstr( m_ckDataL2CacheBuf, strSeperate );	//the L2cache is not a sz. use strstr will cause run-time error.
			pSep = SStrf::sstr( ckTmpL2Cache2, strSeperate );
			
			if( pSep )
			{
				//ckData.redim( (tsize)(pSep - m_ckDataL2CacheBuf.buf() ) ); 
				ckData.redim( (tsize)(pSep - ckTmpL2Cache2.buf() ) );
				
				m_ckDataL2CacheBuf.dump( ckData );
				m_ckDataL2CacheBuf.dump( ckSepDumpTmp ); //get rid of the leading sep str in L2Cache. 
				return 1;
			}
			
			if( !sys_recv( ckTmp ) ) break;

			m_ckDataL2CacheBuf.append(ckTmp);

			if( !on_chk_L2CacheLen( m_ckDataL2CacheBuf ) ) break; //chk long line

		}while(ckTmp.len()>0);

		ckData = m_ckDataL2CacheBuf;	//找到sep的情况已在while中return。这里是收失败时的情况了。
		m_ckDataL2CacheBuf.redim(0);
		return ckData.len()==0?0:1;
	}



	tbool recv_ln( SCake & ckData , tchar cSeperate ) //use Seperate
	{
		tchar t[2];
		t[0]=cSeperate;
		t[1]=0;
		return recv_ln(ckData,t) ;
	}

	

	tbool recv_ln2( SCake & ckData , const tchar * strSeperate )  //no buf-limit-check and _fast
	{
		SCake ckTmp;
		tchar *pSep;
		SCake ckSepDumpTmp(strSeperate);
		
		ckSepDumpTmp.cut(1); 


		std::vector<tchar>  vec_m_ckTmpL2CacheBuf;
		std::copy( m_ckDataL2CacheBuf.buf(), m_ckDataL2CacheBuf.buf() + m_ckDataL2CacheBuf.len(), std::back_inserter(vec_m_ckTmpL2CacheBuf) );

		long lLastChkOffset(0);

		do
		{
			vec_m_ckTmpL2CacheBuf.push_back(0);
			
			pSep = SStrf::sstr( &(vec_m_ckTmpL2CacheBuf[lLastChkOffset]), strSeperate );

			vec_m_ckTmpL2CacheBuf.pop_back();


			if( pSep )
			{
				//restore m-buf
				//
				if( vec_m_ckTmpL2CacheBuf.empty() )
					m_ckDataL2CacheBuf.redim(0);
				else
					m_ckDataL2CacheBuf.let( &(vec_m_ckTmpL2CacheBuf[0]), (tsize)vec_m_ckTmpL2CacheBuf.size() );

				vec_m_ckTmpL2CacheBuf.clear();
				//end restore

				SCake ckTmpL2Cache2;
				ckTmpL2Cache2 = m_ckDataL2CacheBuf;
				ckTmpL2Cache2.mk_sz();

				pSep = SStrf::sstr( ckTmpL2Cache2, strSeperate );

				ckData.redim( (tsize)(pSep - ckTmpL2Cache2.buf() ) );
				
				m_ckDataL2CacheBuf.dump( ckData );
				m_ckDataL2CacheBuf.dump( ckSepDumpTmp ); 
				return 1;
			}
			else
			{
				//if( !pSep) then we must modify the lLastChkOffset
				lLastChkOffset = (long)vec_m_ckTmpL2CacheBuf.size() - (long)ckSepDumpTmp.len();
				if( lLastChkOffset < 0 ) lLastChkOffset = 0;				 
			}

			
			if( !sys_recv( ckTmp ) ) break;

			std::copy( ckTmp.buf(), ckTmp.buf() + ckTmp.len(), std::back_inserter(vec_m_ckTmpL2CacheBuf) ); 
			/*
			将一个vector连接另一个vector末尾的最佳方法是什么？ 	
			v1.insert(v1.end(),   v2.begin(),   v2.end()   );   
			because   vector::insert   will   calculate   the   size   of   inserted   elemenets   and   allocate   the   space   only   once,   then   copy   the   data   from   v2   to   v1.
			---------
			这是最快的办法：   
			std::copy(v2.begin(),   v2.end(),   std::back_inserter(v1));
			*/

			//if( !on_chk_L2CacheLen( m_ckDataL2CacheBuf ) ) break; 

		}while(ckTmp.len()>0);

		
		//restore m-buf
		//
		if( vec_m_ckTmpL2CacheBuf.empty() )
			m_ckDataL2CacheBuf.redim(0);
		else
			m_ckDataL2CacheBuf.let( &(vec_m_ckTmpL2CacheBuf[0]), (tsize)vec_m_ckTmpL2CacheBuf.size() );

		vec_m_ckTmpL2CacheBuf.clear();
		//end restore


		ckData = m_ckDataL2CacheBuf;
		m_ckDataL2CacheBuf.redim(0);
		return ckData.len()==0?0:1;
	}



public:

	virtual tbool on_chk_L2CacheLen( const SCake & ckCurrentL2Cache )
	{
		return 1;
	}


	virtual int on_sys_recv( SCake & ckDataBuf ) //return the real recv len
	{
		return 0;
	}


	virtual int on_sys_send( const SCake & ckDataBuf ) //return the successfully sent len
	{
		return 0;
	}


};//end SRice





X011_NAMESPACE_END

#endif




/*
ICursor interface
*/

#ifndef X011__H_w_ICursor_h
#define X011__H_w_ICursor_h



X011_NAMESPACE_BEGIN


template < class envT, class tblT, class rowT >
class ICursor
{

private:

	tbool		 m_bIsEnvOpen;
	tbool		 m_bIsTblOpen;

	
public:

	ICursor( )
	{
		m_bIsEnvOpen = m_bIsTblOpen = 0;
	}


	virtual ~ICursor( )
	{ 
		//CloseB();
	}

	
public:

	typedef envT envTYPE;
	typedef tblT tblTYPE;
	typedef rowT rowTYPE;

	
public:

	tbool GetIsEnvOpen()
	{
		return m_bIsEnvOpen;
	}

	tbool GetIsTblOpen()
	{
		return m_bIsTblOpen;
	}
	
	
public:

	tbool OpenEnv( envTYPE & _env )
	{
		CloseEnv();	
		return m_bIsEnvOpen = OnOpenEnv(_env);
	}

	tbool OpenTbl( tblTYPE & _tbl )
	{
		CloseTbl();
		return m_bIsTblOpen = OnOpenTbl(_tbl);
	}

	tbool FetchRow( rowTYPE & _row )
	{
		return OnFetchRow( _row );
	}

	void CloseTbl()
	{
		if( GetIsTblOpen() ) OnCloseTbl();
		m_bIsTblOpen=0;
	}

	void CloseEnv()
	{
		if( GetIsEnvOpen() ) OnCloseEnv();
		m_bIsEnvOpen=0;
	}


public:

	virtual tbool OnOpenEnv( envTYPE & _env )
	{
		return 0;
	}

	virtual tbool OnOpenTbl( tblTYPE & _tbl )
	{
		return 0;
	}

	virtual tbool OnFetchRow( rowTYPE & _row )
	{
		return 0;
	}
	
	virtual void OnCloseTbl()
	{
		return;
	}
	
	virtual void OnCloseEnv()
	{
		return;
	}

};//end ICursor







//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



//a cursor data store

template < class IDS_ELE_TYPET >
class ICursorDs_base : public ICursor < std::string,  // envT,
										std::string,  // tblT, 
										std::vector<IDS_ELE_TYPET>  > // rowT  
{
public:

	typedef IDS_ELE_TYPET IDSeleTYPE; 

public:

	virtual ~ICursorDs_base( )
	{ ;
	}
	 

};//end ICursorDs_base




//a cursor data store

class ICursorDs	: public ICursorDs_base < std::string > 
{

public:

	virtual ~ICursorDs( )
	{ ;
	}
	 

};//end ICursorDs






X011_NAMESPACE_END

#endif






/*
W series
CriticalSection 
*/

/*用法例
wl::WCrsc 	m_cmapLock;
static wl::WCrsc m_csCmdDataPoolLock;

volatile  wl::WCrsc aLock( this->m_cmapLock );
*/

#ifndef X011__H_w_wcrsc_h
#define X011__H_w_wcrsc_h


X011_NAMESPACE_BEGIN


class WCrsc 
{

private:

	CRITICAL_SECTION * m_pcsFather;


private:
	//to copy the object is not allowed.

	/*WCrsc & operator = (const WCrsc & rhs)
	{
		return *this;
	}*/

	//WCrsc(const WCrsc & rhs)
	//{;}

	void LockCrsc( WCrsc & Crsc_father )
	{
		EnterCriticalSection( m_pcsFather = Crsc_father.m_pcsSelf );
	}


public:

	CRITICAL_SECTION * m_pcsSelf;


public:

	WCrsc()
	{
		m_pcsFather = NULL;
		m_pcsSelf = NULL;

		m_pcsSelf = new CRITICAL_SECTION;
		InitializeCriticalSection( m_pcsSelf );
	}
    

	WCrsc( WCrsc & Crsc_father)
	{
		m_pcsFather = NULL;
		m_pcsSelf = NULL;
		
		LockCrsc( Crsc_father );
	}

	WCrsc( WCrsc * pCrsc_father)
	{
		m_pcsFather = NULL;
		m_pcsSelf = NULL;
		
		if( pCrsc_father ) LockCrsc( *pCrsc_father );
	}


	virtual ~WCrsc()
	{
		if( m_pcsFather != NULL )
		{
			LeaveCriticalSection( m_pcsFather );
			return;
		}
		
		if( m_pcsFather == NULL )
		{
			if( m_pcsSelf != NULL )
			{
				DeleteCriticalSection( m_pcsSelf );
				delete m_pcsSelf;
				return;
			}
		}
	}

}; //end class 




X011_NAMESPACE_END

#endif





/*
w_WUniTblCh,   char型字符串支持的sqllike
*/

// 


#ifndef X011__W_WUNITBLCH_H
#define X011__W_WUNITBLCH_H




X011_NAMESPACE_BEGIN



class unitbl_base_t
{
public:
	wl::WCrsc		m_ut_tbl_lck; 
	
public:
	virtual ~unitbl_base_t() {;}

	virtual void ut_ClearTbl() = 0;

	virtual int ut_GetColAmount() = 0;
	virtual std::string ut_GetColName( int iColNum ) = 0;

	virtual long ut_GetRowAmount() = 0;

	virtual std::string ut_GetRowSeriStr( long lRowNum ) = 0; 

	virtual std::string ut_GetItemStr( long lRowNum, std::string strColName ) = 0; 
	virtual std::string ut_GetItemStr( long lRowNum, int iColNum ) = 0; 

	virtual void ut_SetItemByStr( long lRowNum, std::string strColName, std::string strValPARA  ) = 0; 
	virtual void ut_SetItemByStr( long lRowNum, int iColNum ,           std::string strValPARA  ) = 0; 

	virtual long ut_AddRow() = 0;
	virtual long ut_AddRow( std::string strRowSeriStr) = 0;

	virtual std::string & ut_SeriTbl( std::string & strOut )=0;
	virtual unitbl_base_t & ut_UnseriTbl( const std::string & strIn, int biAppend ) = 0;

	virtual void ut_DelRowf( long lRowNum ) = 0; 
	virtual void ut_DelRow( long lRowNum ) = 0; 
};





template<class T>
class unitbl_t : public unitbl_base_t , public T 
{
public:
	virtual ~unitbl_t() {;}


public:

	virtual void ut_ClearTbl()
	{
		T::Clear();
	}

	virtual int ut_GetColAmount()
	{
		return T::GetRow(-1).GetColAmount() ;
	}


	virtual std::string ut_GetColName( int iColNum ) 
	{
		return T::GetRow(-1).GetColName( iColNum );
	}


	virtual long ut_GetRowAmount() 
	{
		return T::GetRowCount( );
	}

	virtual std::string ut_GetRowSeriStr( long lRowNum ) 
	{
		return T::GetRow(lRowNum).Serialize();
	}
	

	virtual std::string ut_GetItemStr( long lRowNum, std::string strColName )
	{
		std::string s1;
		T::GetRow(lRowNum).GetColStr( strColName, s1 );
		return s1;
	}


	virtual std::string ut_GetItemStr( long lRowNum, int iColNum )
	{
		std::string s1;
		T::GetRow(lRowNum).GetColStr( iColNum, s1 );
		return s1;
	}
 
	virtual void ut_SetItemByStr( long lRowNum, std::string strColName, std::string strValPARA ) 
	{
		T::GetRow(lRowNum).SetColVal( strColName, strValPARA );
	}

	virtual void ut_SetItemByStr( long lRowNum, int iColNum ,           std::string strValPARA ) 
	{
		T::GetRow(lRowNum).SetColVal( iColNum, strValPARA );
	}

	virtual long ut_AddRow() 
	{
		T::Add(T::GetRow(-1));
		return T::GetRowCount() - 1 ;
	}

	virtual long ut_AddRow( std::string strRowSeriStr ) 
	{
		typename T::ROWTYPE row1;
		row1.Unserialize( strRowSeriStr.c_str() );
		T::Add(row1);
		return T::GetRowCount() - 1 ;
	}

	
	virtual std::string & ut_SeriTbl( std::string & strOut )
	{
		return T::Serialize( strOut );
	}


	virtual unitbl_base_t & ut_UnseriTbl( const std::string & strIn, int biAppend )
	{
		T::Unserialize( strIn.c_str() , biAppend )	;
		return *this;
	}


	virtual void ut_DelRowf( long lRowNum ) 
	{
		T::DelInternal( lRowNum );
	}

	virtual void ut_DelRow( long lRowNum )
	{
		T::Del( lRowNum );
	}

};




X011_NAMESPACE_END

#endif



/*
W series
hwnd and sndmsg routines 
*/

// 

#ifndef X011__H_w_wmsg_h
#define X011__H_w_wmsg_h


X011_NAMESPACE_BEGIN


class WMsg
{

private:

	static BOOL CALLBACK EnumHwndProc( HWND hwnd, LPARAM lParam )	//后一个参数是pvec,得到HWND 的一个vec
	{
		std::vector< HWND > * pvecHwnd;
		//i = GetWindowTextLengthA(hwnd);
		//GetWindowTextA(hwnd, ivp_winlist->cf_getlastrow()->cf_readtop(), i-1 );
		pvecHwnd = (std::vector < HWND > *)lParam;
		pvecHwnd->push_back(hwnd);
		return 1;
	}

 
public:

	WMsg()
	{
		 
	}

	//virtual ~WMsg()	{ 	}


	static tsize snapshot( std::vector< HWND > & vecRtnHwndBuf )
	{
		vecRtnHwndBuf.clear();
		EnumWindows( EnumHwndProc, (LPARAM)&vecRtnHwndBuf );
		return (tsize)vecRtnHwndBuf.size();
	}


	static tsize snapshot( HWND hwnd, std::vector< HWND > & vecRtnHwndBuf ) //EnumChildWindows
	{
		vecRtnHwndBuf.clear();
		EnumChildWindows(hwnd, EnumHwndProc, (LPARAM)&vecRtnHwndBuf );
		return (tsize)vecRtnHwndBuf.size();
	}



	static tsize snapshot( HWND HwndContainer, std::map< std::string , HWND > & mapHdl ) // 
	{
		std::vector< HWND > vecHwndBuf;

		if( HwndContainer == 0 )
			snapshot( vecHwndBuf );
		else
			snapshot( HwndContainer, vecHwndBuf );

		for( std::vector<HWND>::iterator it= vecHwndBuf.begin(); it != vecHwndBuf.end(); ++it )
		{
			std::string s;
			
			s = WMsg::win_text( *it );
			if( s.empty() ) continue;

			mapHdl.insert( std::pair< std::string , HWND >( s, *it ) );
		}

		return (tsize)mapHdl.size();
	}


	static tsize snapshot( std::string strHwndContainer, std::map< std::string , HWND > & mapHdl ) // 
	{
		HWND iInput = 0;
		(*SClib::p_sscanf()) ( ("0"+strHwndContainer).c_str(), "%x", &iInput );

		return snapshot( iInput, mapHdl );
	}




///////////以下试验中：

typedef		struct 
{
	HWND hh1;
	DWORD dwProcId;
	DWORD dwThreadId;
	HANDLE hh3;
}	Hnd3TYPE;


	static tsize GetH3( std::vector<Hnd3TYPE> & vout ) //HWND与HANDLE对照表,多个窗口对应一个进程
	{
		//std::vector<HWND> & vHwnd, std::vector<DWORD> & vProcId, std::vector<HANDLE> & vHandle
		std::map< std::string , HWND > mapHdl;
		HWND parenthwnd ;
		DWORD dwProcId ;
		DWORD dwThreadId ;
		HANDLE hProcess ;

		snapshot( "0", mapHdl );

		for( std::map< std::string , HWND >::iterator it= mapHdl.begin(); it != mapHdl.end(); ++it )
		{
			parenthwnd = it->second ;
			::GetWindowThreadProcessId( parenthwnd, &dwProcId );
			dwThreadId = ::GetWindowThreadProcessId(parenthwnd, NULL);
			hProcess = ::OpenProcess( PROCESS_QUERY_INFORMATION, FALSE, dwProcId );   

			Hnd3TYPE h3;

			h3.hh1 = parenthwnd;
			h3.dwProcId = dwProcId;
			h3.dwThreadId = dwThreadId;
			h3.hh3 = hProcess;

			//CString s;
			//s = GetLastErrorMsgTS();

			vout.push_back( h3 );
		}

		return (tsize)vout.size();
	}


	static HWND GetProc1Hwnd( DWORD dwProcId ) // 多个窗口对应一个进程,此处返回任一个
	{
		std::vector<Hnd3TYPE>  vout;

		GetH3( vout );

		for( std::vector<Hnd3TYPE>::iterator it= vout.begin(); it != vout.end(); ++it )
		{
			if( dwProcId == it->dwProcId ) return it->hh1;
		}
 
		return (HWND)0;
	}



	static PROCESS_INFORMATION OpenNewProc( CString cstrCmd, int nShow = SW_NORMAL )  
	{
		STARTUPINFO si; //一些必备参数设置 
		memset(&si, 0, sizeof(STARTUPINFO));
		si.dwFlags = STARTF_USESHOWWINDOW;
		si.wShowWindow = nShow;
		PROCESS_INFORMATION pi; //必备参数设置结束 

		std::vector< TCHAR > vCmdBuf( cstrCmd.GetString(), cstrCmd.GetString() + cstrCmd.GetLength() ) ;
		vCmdBuf.push_back((TCHAR)0);

		CreateProcess( NULL, &(vCmdBuf[0]), NULL,NULL,FALSE,0,NULL,NULL,&si, &pi );

		return pi;

		//DWORD dwProcessID = pi.dwProcessId;
		//DWORD dwThreadID = 0;

		//THREADENTRY32 te32 = {sizeof(te32)};
		//HANDLE hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD,0);
		//if( Thread32First( hThreadSnap, &te32) )
		//{
		//	do{
		//		if( dwProcessID == te32.th32OwnerProcessID )
		//		{
		//			dwThreadID = te32.th32ThreadID;
		//			break;
		//		}
		//	}while( Thread32Next( hThreadSnap, &te32) );
		//}

		//CloseHandle(hThreadSnap);
	}


	static HWND GetNewWnd( CString cstrCmd, int nShow = SW_NORMAL )  
	{
		DWORD h1;
		HWND  h2;

		h1 = OpenNewProc( cstrCmd, nShow ).dwProcessId;
		Sleep(1234);
		h2 = GetProc1Hwnd( h1 );

		return h2;
	}


/////////// 试验中 


	static std::string win_text( HWND hwnd )
	{
		int iTextLen ;//= (int)SendMessageA( hwnd, WM_GETTEXTLENGTH ,0, (long)0 );
		
		iTextLen = GetWindowTextLength( hwnd );

		SCake ckText;

		iTextLen *= 4;
		ckText.redim( iTextLen );

		if( GetWindowTextA( hwnd , ckText.buf(), iTextLen ) )
		{
			return ckText.buf();
		}
		else
		{
			return ""; //if win text wrong, rtn a "" string.
		}		
	}


	static CString win_text2( HWND hwnd , int iStringLen )
	{
		CString s;
		DWORD result;
		SendMessageTimeout( hwnd, WM_GETTEXT, iStringLen, (LPARAM)s.GetBuffer(iStringLen), 0, 1000, &result); 
		CString s1(s);
		s.ReleaseBuffer();
		return s1;
	}



	static void key_char( BYTE c )
	{
		do//fakedo
		{
			/*if(c>='A'&&c<='Z'||c>='0'&&c<='9')
			{
				keybd_event(c, 0, 0,			 	0);
				keybd_event(c, 0, KEYEVENTF_KEYUP,  0);
				break;
			}*/

			/*if(c>='a'&&c<='z' ){
				key_char( c-'a'+'A' ) ;
				break;
			}*/

			tuint16 u;
			u = VkKeyScanA(c);
			c= (tuint8)u;


			if(0)
			{
			if(u&0x0100) keybd_event(VK_LSHIFT, 0, 0,			 	0);

				 keybd_event(c, 0, 0,			 	 0);
				 keybd_event(c, 0, KEYEVENTF_KEYUP,  0);

			if(u&0x0100) keybd_event(VK_LSHIFT, 0, KEYEVENTF_KEYUP,	0);
			}


			if(1) //for win98 and xp
			{
			if(u&0x0100) keybd_event(VK_SHIFT, 0, 0,			 	0);

				 keybd_event(c, 0, 0,			 	 0);
				 keybd_event(c, 0, KEYEVENTF_KEYUP,  0);

			if(u&0x0100) keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP,	0);
			}


		}while(0);
	}


	static void key_plain( tchar cInput )
	{
		key_char((BYTE)cInput);
	}


	static void key_plain( const tchar * strInputSeq )
	{
		for( ; strInputSeq && *strInputSeq; strInputSeq++ )
		{
			key_plain(*strInputSeq);
		}
	}


	//multi format universal send key
	static void key_ctrl( const tchar * strInputSeq )
	{
		const tchar * t = strInputSeq;
		const tchar * sKeyWord;
		int iState=0;

		for(;t&&*t;)
		{
			do //fakedo
			{
				// the tag is case insensitive

				sKeyWord =  "<capslock>"; if( !wl::SStrf::scmpin( t, sKeyWord ) ) { keybd_event(20, 0, 0,			 	 0); t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "</capslock>"; if( !wl::SStrf::scmpin( t, sKeyWord ) ) { keybd_event(20, 0, KEYEVENTF_KEYUP, 0); t += SStrf::slen(sKeyWord); break; }

				sKeyWord =  "<numlock>";  if( !wl::SStrf::scmpin( t, sKeyWord ) )  { keybd_event(VK_NUMLOCK, 0, 0,			 	 0);  t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "</numlock>"; if( !wl::SStrf::scmpin( t, sKeyWord ) ) {   keybd_event(VK_NUMLOCK, 0, KEYEVENTF_KEYUP, 0); t += SStrf::slen(sKeyWord); break; }

				sKeyWord = "<scrolllock>"; 	if( !wl::SStrf::scmpin( t, sKeyWord ) ) { keybd_event(VK_SCROLL, 0, 0,			 	 0); t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "</scrolllock>"; if( !wl::SStrf::scmpin( t, sKeyWord ) ) { keybd_event(VK_SCROLL, 0, KEYEVENTF_KEYUP, 0); t += SStrf::slen(sKeyWord); break; }

				sKeyWord =  "<win>";	if( !wl::SStrf::scmpin( t, sKeyWord ) ) { keybd_event(VK_LWIN, 0, 0, 0);				t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "</win>";	if( !wl::SStrf::scmpin( t, sKeyWord ) ) { keybd_event(VK_LWIN, 0, KEYEVENTF_KEYUP, 0);  t += SStrf::slen(sKeyWord); break; }




				//here below there are diff between xp and 98, see http://www.codeproject.com/kb/cpp/togglekeys.aspx
				if(0)
				{
				sKeyWord =  "<shift>";	if( !wl::SStrf::scmpin( t, sKeyWord ) ) { keybd_event(VK_LSHIFT, 0, 0, 0);				 t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "</shift>";	if( !wl::SStrf::scmpin( t, sKeyWord ) ) { keybd_event(VK_LSHIFT, 0, KEYEVENTF_KEYUP, 0); t += SStrf::slen(sKeyWord); break; }

				sKeyWord =  "<ctrl>";	if( !wl::SStrf::scmpin( t, sKeyWord ) ) { keybd_event(VK_LCONTROL, 0, 0, 0);				t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "</ctrl>";	if( !wl::SStrf::scmpin( t, sKeyWord ) ) { keybd_event(VK_LCONTROL, 0, KEYEVENTF_KEYUP, 0);  t += SStrf::slen(sKeyWord); break; }

				sKeyWord =  "<alt>";	if( !wl::SStrf::scmpin( t, sKeyWord ) ) { keybd_event(VK_LMENU, 0, 0, 0);				t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "</alt>";	if( !wl::SStrf::scmpin( t, sKeyWord ) ) { keybd_event(VK_LMENU, 0, KEYEVENTF_KEYUP, 0); t += SStrf::slen(sKeyWord); break; }
				}

				if(1)
				{
				sKeyWord =  "<shift>";	if( !wl::SStrf::scmpin( t, sKeyWord ) ) { keybd_event(VK_SHIFT, 0, 0, 0);				 t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "</shift>";	if( !wl::SStrf::scmpin( t, sKeyWord ) ) { keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0); t += SStrf::slen(sKeyWord); break; }

				sKeyWord =  "<ctrl>";	if( !wl::SStrf::scmpin( t, sKeyWord ) ) { keybd_event(VK_CONTROL, 0, 0, 0);				t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "</ctrl>";	if( !wl::SStrf::scmpin( t, sKeyWord ) ) { keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);  t += SStrf::slen(sKeyWord); break; }

				sKeyWord =  "<alt>";	if( !wl::SStrf::scmpin( t, sKeyWord ) ) { keybd_event(VK_MENU, 0, 0, 0);				t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "</alt>";	if( !wl::SStrf::scmpin( t, sKeyWord ) ) { keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0); t += SStrf::slen(sKeyWord); break; }
				}




				sKeyWord =  "<tab>"; if( !wl::SStrf::scmpin( t, sKeyWord ) ) { keybd_event(VK_TAB, 0, 0,			 	 0); t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "</tab>"; if( !wl::SStrf::scmpin( t, sKeyWord ) ) { keybd_event(VK_TAB, 0, KEYEVENTF_KEYUP, 0);   t += SStrf::slen(sKeyWord); break; }

				sKeyWord =  "<esc>"; if( !wl::SStrf::scmpin( t, sKeyWord ) ) { keybd_event(VK_ESCAPE, 0, 0,			 	 0); t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "</esc>"; if( !wl::SStrf::scmpin( t, sKeyWord ) ) { keybd_event(VK_ESCAPE, 0, KEYEVENTF_KEYUP, 0); t += SStrf::slen(sKeyWord); break; }

				sKeyWord =  "<enter>"; if( !wl::SStrf::scmpin( t, sKeyWord ) ) { keybd_event(VK_RETURN, 0, 0,			 	 0); t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "</enter>"; if( !wl::SStrf::scmpin( t, sKeyWord ) ) { keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0); t += SStrf::slen(sKeyWord); break; 	}

				sKeyWord =  "<back>"; if( !wl::SStrf::scmpin( t, sKeyWord ) ) { 	keybd_event(VK_BACK, 0, 0,			 	 0); t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "</back>"; if( !wl::SStrf::scmpin( t, sKeyWord ) ) { keybd_event(VK_BACK, 0, KEYEVENTF_KEYUP, 0); t += SStrf::slen(sKeyWord); break; }

				sKeyWord =  "<insert>";  if( !wl::SStrf::scmpin( t, sKeyWord ) ) { keybd_event(VK_NUMLOCK, 0, 0,			 0); t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "</insert>";  if( !wl::SStrf::scmpin( t, sKeyWord ) ) { keybd_event(VK_INSERT, 0, KEYEVENTF_KEYUP, 0); t += SStrf::slen(sKeyWord); break; }

				sKeyWord =  "<DELETE>";  if( !wl::SStrf::scmpin( t, sKeyWord ) ) { keybd_event(VK_DELETE, 0, 0, 0);				t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "</DELETE>";  if( !wl::SStrf::scmpin( t, sKeyWord ) ) { keybd_event(VK_DELETE, 0, KEYEVENTF_KEYUP, 0); t += SStrf::slen(sKeyWord); break; }

				sKeyWord =  "<HOME>";  if( !wl::SStrf::scmpin( t, sKeyWord ) ) { keybd_event(VK_HOME, 0, 0, 0);				t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "</HOME>";  if( !wl::SStrf::scmpin( t, sKeyWord ) ) { keybd_event(VK_HOME, 0, KEYEVENTF_KEYUP, 0); t += SStrf::slen(sKeyWord); break; }

				sKeyWord =  "<END>";  if( !wl::SStrf::scmpin( t, sKeyWord ) ) { keybd_event(VK_END, 0, 0, 0);				t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "</END>";  if( !wl::SStrf::scmpin( t, sKeyWord ) ) { keybd_event(VK_END, 0, KEYEVENTF_KEYUP, 0); t += SStrf::slen(sKeyWord); break; }

				// pageup pagedown begin
				sKeyWord =  "<PGUP>";  if( !wl::SStrf::scmpin( t, sKeyWord ) ) { keybd_event(VK_PRIOR, 0, 0, 0);				t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "</PGUP>";  if( !wl::SStrf::scmpin( t, sKeyWord ) ) { keybd_event(VK_PRIOR, 0, KEYEVENTF_KEYUP, 0);  t += SStrf::slen(sKeyWord); break; }
				sKeyWord =  "<PGDN>";  if( !wl::SStrf::scmpin( t, sKeyWord ) ) { keybd_event(VK_NEXT, 0, 0, 0);				   t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "</PGDN>";  if( !wl::SStrf::scmpin( t, sKeyWord ) ) { keybd_event(VK_NEXT, 0, KEYEVENTF_KEYUP, 0);  t += SStrf::slen(sKeyWord); break; }
				// pageup pagedown end!

				sKeyWord =  "<LEFT>";  if( !wl::SStrf::scmpin( t, sKeyWord ) ) { keybd_event(VK_LEFT, 0, 0, 0);				t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "</LEFT>";  if( !wl::SStrf::scmpin( t, sKeyWord ) ) { keybd_event(VK_LEFT, 0, KEYEVENTF_KEYUP, 0); t += SStrf::slen(sKeyWord); break; }

				sKeyWord =  "<uP>";  if( !wl::SStrf::scmpin( t, sKeyWord ) ) { keybd_event(VK_UP, 0, 0, 0);				t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "</UP>";  if( !wl::SStrf::scmpin( t, sKeyWord ) ) { keybd_event(VK_UP, 0, KEYEVENTF_KEYUP, 0); t += SStrf::slen(sKeyWord); break; }

				sKeyWord =  "<RIGHT>";  if( !wl::SStrf::scmpin( t, sKeyWord ) ) { keybd_event(VK_RIGHT, 0, 0, 0);				t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "</RIGHT>";  if( !wl::SStrf::scmpin( t, sKeyWord ) ) { keybd_event(VK_RIGHT, 0, KEYEVENTF_KEYUP, 0); t += SStrf::slen(sKeyWord); break; }

				sKeyWord =  "<DOWN>";  if( !wl::SStrf::scmpin( t, sKeyWord ) ) { keybd_event(VK_DOWN, 0, 0, 0);				t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "</DOWN>";  if( !wl::SStrf::scmpin( t, sKeyWord ) ) { keybd_event(VK_DOWN, 0, KEYEVENTF_KEYUP, 0); t += SStrf::slen(sKeyWord); break; }


				sKeyWord = "<F1>";	if( !wl::SStrf::scmpin( t,sKeyWord ) ) { keybd_event( VK_F1,	 0, 0, 0); t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "<F2>";	if( !wl::SStrf::scmpin( t,sKeyWord ) ) { keybd_event( VK_F2,	 0, 0, 0); t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "<F3>";	if( !wl::SStrf::scmpin( t,sKeyWord ) ) { keybd_event( VK_F3,	 0, 0, 0); t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "<F4>";	if( !wl::SStrf::scmpin( t,sKeyWord ) ) { keybd_event( VK_F4,	 0, 0, 0); t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "<F5>";	if( !wl::SStrf::scmpin( t,sKeyWord ) ) { keybd_event( VK_F5,	 0, 0, 0); t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "<F6>";	if( !wl::SStrf::scmpin( t,sKeyWord ) ) { keybd_event( VK_F6,	 0, 0, 0); t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "<F7>";	if( !wl::SStrf::scmpin( t,sKeyWord ) ) { keybd_event( VK_F7,	 0, 0, 0); t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "<F8>";	if( !wl::SStrf::scmpin( t,sKeyWord ) ) { keybd_event( VK_F8,	 0, 0, 0); t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "<F9>";	if( !wl::SStrf::scmpin( t,sKeyWord ) ) { keybd_event( VK_F9,	 0, 0, 0); t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "<F10>";	if( !wl::SStrf::scmpin( t,sKeyWord ) ) { keybd_event( VK_F10,	 0, 0, 0); t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "<F11>";	if( !wl::SStrf::scmpin( t,sKeyWord ) ) { keybd_event( VK_F11,	 0, 0, 0); t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "<F12>";	if( !wl::SStrf::scmpin( t,sKeyWord ) ) { keybd_event( VK_F12,	 0, 0, 0); t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "<F13>";	if( !wl::SStrf::scmpin( t,sKeyWord ) ) { keybd_event( VK_F13,	 0, 0, 0); t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "<F14>";	if( !wl::SStrf::scmpin( t,sKeyWord ) ) { keybd_event( VK_F14,	 0, 0, 0); t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "<F15>";	if( !wl::SStrf::scmpin( t,sKeyWord ) ) { keybd_event( VK_F15,	 0, 0, 0); t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "<F16>";	if( !wl::SStrf::scmpin( t,sKeyWord ) ) { keybd_event( VK_F16,	 0, 0, 0); t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "<F17>";	if( !wl::SStrf::scmpin( t,sKeyWord ) ) { keybd_event( VK_F17,	 0, 0, 0); t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "<F18>";	if( !wl::SStrf::scmpin( t,sKeyWord ) ) { keybd_event( VK_F18,	 0, 0, 0); t += SStrf::slen(sKeyWord); break; }

				sKeyWord = "</F1>";	if( !wl::SStrf::scmpin( t,sKeyWord ) ) { keybd_event( VK_F1,	 0, KEYEVENTF_KEYUP, 0); t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "</F2>";	if( !wl::SStrf::scmpin( t,sKeyWord ) ) { keybd_event( VK_F2,	 0, KEYEVENTF_KEYUP, 0); t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "</F3>";	if( !wl::SStrf::scmpin( t,sKeyWord ) ) { keybd_event( VK_F3,	 0, KEYEVENTF_KEYUP, 0); t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "</F4>";	if( !wl::SStrf::scmpin( t,sKeyWord ) ) { keybd_event( VK_F4,	 0, KEYEVENTF_KEYUP, 0); t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "</F5>";	if( !wl::SStrf::scmpin( t,sKeyWord ) ) { keybd_event( VK_F5,	 0, KEYEVENTF_KEYUP, 0); t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "</F6>";	if( !wl::SStrf::scmpin( t,sKeyWord ) ) { keybd_event( VK_F6,	 0, KEYEVENTF_KEYUP, 0); t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "</F7>";	if( !wl::SStrf::scmpin( t,sKeyWord ) ) { keybd_event( VK_F7,	 0, KEYEVENTF_KEYUP, 0); t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "</F8>";	if( !wl::SStrf::scmpin( t,sKeyWord ) ) { keybd_event( VK_F8,	 0, KEYEVENTF_KEYUP, 0); t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "</F9>";	if( !wl::SStrf::scmpin( t,sKeyWord ) ) { keybd_event( VK_F9,	 0, KEYEVENTF_KEYUP, 0); t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "</F10>";	if( !wl::SStrf::scmpin( t,sKeyWord ) ) { keybd_event( VK_F10,	 0, KEYEVENTF_KEYUP, 0); t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "</F11>";	if( !wl::SStrf::scmpin( t,sKeyWord ) ) { keybd_event( VK_F11,	 0, KEYEVENTF_KEYUP, 0); t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "</F12>";	if( !wl::SStrf::scmpin( t,sKeyWord ) ) { keybd_event( VK_F12,	 0, KEYEVENTF_KEYUP, 0); t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "</F13>";	if( !wl::SStrf::scmpin( t,sKeyWord ) ) { keybd_event( VK_F13,	 0, KEYEVENTF_KEYUP, 0); t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "</F14>";	if( !wl::SStrf::scmpin( t,sKeyWord ) ) { keybd_event( VK_F14,	 0, KEYEVENTF_KEYUP, 0); t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "</F15>";	if( !wl::SStrf::scmpin( t,sKeyWord ) ) { keybd_event( VK_F15,	 0, KEYEVENTF_KEYUP, 0); t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "</F16>";	if( !wl::SStrf::scmpin( t,sKeyWord ) ) { keybd_event( VK_F16,	 0, KEYEVENTF_KEYUP, 0); t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "</F17>";	if( !wl::SStrf::scmpin( t,sKeyWord ) ) { keybd_event( VK_F17,	 0, KEYEVENTF_KEYUP, 0); t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "</F18>";	if( !wl::SStrf::scmpin( t,sKeyWord ) ) { keybd_event( VK_F18,	 0, KEYEVENTF_KEYUP, 0); t += SStrf::slen(sKeyWord); break; }


				sKeyWord = "<sleep>";
				if( !wl::SStrf::scmpin( t, sKeyWord ) )
				{
					Sleep(500);
					t += SStrf::slen(sKeyWord);
					break;
				}

				sKeyWord = "<sleep0>"; if( !wl::SStrf::scmpin( t, sKeyWord ) )
				{ Sleep(66); t += SStrf::slen(sKeyWord); break; 	}

				sKeyWord = "<sleep1>"; if( !wl::SStrf::scmpin( t, sKeyWord ) )
				{ Sleep(123); t += SStrf::slen(sKeyWord); break; 	}

				sKeyWord = "<sleep2>"; if( !wl::SStrf::scmpin( t, sKeyWord ) )
				{ Sleep(234); t += SStrf::slen(sKeyWord); break; 	}

				sKeyWord = "<sleep3>"; if( !wl::SStrf::scmpin( t, sKeyWord ) )
				{ Sleep(345); t += SStrf::slen(sKeyWord); break; 	}

				sKeyWord = "<sleep4>"; if( !wl::SStrf::scmpin( t, sKeyWord ) )
				{ Sleep(456); t += SStrf::slen(sKeyWord); break; 	}

				sKeyWord = "<sleep5>"; if( !wl::SStrf::scmpin( t, sKeyWord ) )
				{ Sleep(567); t += SStrf::slen(sKeyWord); break; 	}

				sKeyWord = "<sleep6>"; if( !wl::SStrf::scmpin( t, sKeyWord ) )
				{ Sleep(678); t += SStrf::slen(sKeyWord); break; 	}

				sKeyWord = "<sleep7>"; if( !wl::SStrf::scmpin( t, sKeyWord ) )
				{ Sleep(789); t += SStrf::slen(sKeyWord); break; 	}

				sKeyWord = "<sleep8>"; if( !wl::SStrf::scmpin( t, sKeyWord ) )
				{ Sleep(890); t += SStrf::slen(sKeyWord); break; 	}

				sKeyWord = "<sleep9>"; if( !wl::SStrf::scmpin( t, sKeyWord ) )
				{ Sleep(999); t += SStrf::slen(sKeyWord); break; 	}


				sKeyWord = "<c>";
				if( !wl::SStrf::scmpin( t, sKeyWord ) )
				{
					iState=1;
					t += SStrf::slen(sKeyWord);
					break;
				}

				sKeyWord = "</c>";
				if( !wl::SStrf::scmpin( t, sKeyWord ) )
				{
					iState=0;	//只能靠/c关掉，不能自动关掉。因为<c>之后都要持续打开，输入连续字母
					t += SStrf::slen(sKeyWord);
					break;
				}


				//k 是后来加的好像不好用

				sKeyWord = "<k>";
				if( !wl::SStrf::scmpin( t, sKeyWord ) )
				{
					iState= 2;
					t += SStrf::slen(sKeyWord);
					break;
				}

				sKeyWord = "</k>";
				if( !wl::SStrf::scmpin( t, sKeyWord ) )
				{
					iState=0;
					t += SStrf::slen(sKeyWord);
					break;
				}


				if(iState == 1) key_plain( *t );

				if( iState == 2 )
				{
					BYTE c;
					c = (BYTE)(*t);
					keybd_event(c, 0, 0,			 	0);
					keybd_event(c, 0, KEYEVENTF_KEYUP,  0);
				}

				t++;

			}while(0);

		} //end for

	}


	static tbool get_key_down( int vKey )
	{
		return (GetAsyncKeyState(vKey) & 0x8000) ? 1 : 0;
		 //e.g.: if( wl::WMsg::get_key_down(VK_LCONTROL) ) system("pause");
		/*e.g.: 
		if( wl::WMsg::get_key_down(VK_LCONTROL) &&	
			wl::WMsg::get_key_down(VK_RCONTROL)	)
		{
			break;
		}*/
	}



	//mouse functions:

	static POINT mou_get( POINT * ppo = NULL )
	{
		POINT po;
		SStrf::smemset(&po);
		if( ppo ) *ppo = po;
		if( !GetCursorPos( &po ) ) return po;
		if( ppo ) *ppo = po;
		return po;
	}

	static void mou_get( long &x, long &y )
	{
		POINT po = mou_get();
		x = po.x ;
		y = po.y ;
	}

	static void mou_move( long x, long y )
	{ 
		double fScreenWidth = ::GetSystemMetrics( SM_CXSCREEN )-1; 
		double fScreenHeight = ::GetSystemMetrics( SM_CYSCREEN )-1; 
		double fx = x*(65535.0f/fScreenWidth);
		double fy = y*(65535.0f/fScreenHeight);
		//INPUT Input={0};
		//Input.type = INPUT_MOUSE;
		//Input.mi.dwFlags = MOUSEEVENTF_MOVE|MOUSEEVENTF_ABSOLUTE;
		//Input.mi.dx = fx;
		//Input.mi.dy = fy;
		//::SendInput(1,&Input,sizeof(INPUT));

		mouse_event( MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE, static_cast<DWORD>(fx), static_cast<DWORD>(fy), 0, 0 );
	}

	static void mou_left( long x, long y , int itimes = 1 )
	{
		double fScreenWidth = ::GetSystemMetrics( SM_CXSCREEN )-1; 
		double fScreenHeight = ::GetSystemMetrics( SM_CYSCREEN )-1; 
		double fx = x*(65535.0f/fScreenWidth);
		double fy = y*(65535.0f/fScreenHeight);

		mou_move( x, y );

		for( int i = 0 ; i < itimes ; i++ )
		{
			mouse_event ( MOUSEEVENTF_LEFTDOWN , 0, 0, 0, 0 );
			mouse_event ( MOUSEEVENTF_LEFTUP,    0, 0, 0, 0 );
		}
	}

	static void mou_right( long x, long y , int itimes = 1 )
	{
		double fScreenWidth = ::GetSystemMetrics( SM_CXSCREEN )-1; 
		double fScreenHeight = ::GetSystemMetrics( SM_CYSCREEN )-1; 
		double fx = x*(65535.0f/fScreenWidth);
		double fy = y*(65535.0f/fScreenHeight);

		mou_move( x, y );

		for( int i = 0 ; i < itimes ; i++ )
		{
			mouse_event ( MOUSEEVENTF_RIGHTDOWN  , 0, 0, 0, 0 );
			mouse_event ( MOUSEEVENTF_RIGHTUP,     0, 0, 0, 0 );
		}
	}


	//

	static void win_state_max( HWND hwnd )
	{
		SendMessage( hwnd, 274, 61488,		 0 );	//SC_MAXIMIZE		 MoveWindow     ShowWindow
	} 

	static void win_state_normal( HWND hwnd )
	{
		SendMessage( hwnd, 274, SC_RESTORE,  0 );
	}

	static void win_state_min( HWND hwnd )
	{
		SendMessage( hwnd, 274, 61472,		 0 ); //SC_MINIMIZE
	}


	static void win_close(HWND hwnd)
	{
		SendMessage( hwnd, 0x10, 0,	0 );
	}



	static void win_fore(HWND hwnd)
	{
		SetForegroundWindow(hwnd);
				/*this->SetCapture();
				wl::WMsg::win_fore(this->m_hWnd);
				ReleaseCapture();*/
	}



	static HWND win_getfore(void)
	{
		return GetForegroundWindow();
	}

	static void win_show(HWND hwnd, int nCmdShow)
	{
		ShowWindow (hwnd, nCmdShow);
		//例如: ShowWindow(FindWindowA(0, "ywinputwnd"), 8)
		//		ShowWindow(FindWindowA(0, "ywinputwnd"), 0)

		//nCmdShow为窗口指定可视性方面的一个命令
//		SW_HIDE	隐藏窗口，活动状态给另一个窗口
//		SW_MINIMIZE	最小化窗口，活动状态给令一个窗口
//		SW_RESTORE	用原来的大小和位置显示一个窗口，同时令其进入活动状态
//		SW_SHOW	用当前的大小和位置显示一个窗口，同时令其进入活动状态
//		SW_SHOWMAXIMIZED	最大化窗口，并将其激活
//		SW_SHOWMINIMIZED	最小化窗口，并将其激活
//		SW_SHOWMINNOACTIVE	最小化一个窗口，同时不改变活动窗口
//		SW_SHOWNA	用当前的大小和位置显示一个窗口，不改变活动窗口
//		SW_SHOWNOACTIVATE	用最近的大小和位置显示一个窗口，同时不改变活动窗口
//		SW_SHOWNORMAL	与SW_RESTORE相同
	}

	static void win_pos( HWND hWnd, HWND hWndInsertAfter , int X, int Y, int cx, int cy, UINT uFlags)
	{
		SetWindowPos(hWnd,hWndInsertAfter ,X, Y, cx, cy, uFlags);

		//例如:SetWindowPos(FindWindowA(0, "ywinputwnd"), -1, 0, 0, 400, 50, &H40)

		//hWndInsertAfter，窗口句柄。在窗口列表中，窗口hwnd会置于这个窗口句柄的后面。也可能选用下述值之一：	
		//HWND_BOTTOM	将窗口置于窗口列表底部
		//HWND_TOP	将窗口置于Z序列的顶部；Z序列代表在分级结构中，窗口针对一个给定级别的窗口显示的顺序
		//HWND_TOPMOST	将窗口置于列表顶部，并位于任何最顶部窗口的前面
		//HWND_NOTOPMOST	将窗口置于列表顶部，并位于任何最顶部窗口的后面

		//x	Long，窗口新的x坐标。如hwnd是一个子窗口，则x用父窗口的客户区坐标表示	
		//y	Long，窗口新的y坐标。如hwnd是一个子窗口，则y用父窗口的客户区坐标表示	
		//cx	Long，指定新的窗口宽度	
		//cy	Long，指定新的窗口高度

		//uFlags，包含了旗标的一个整数	
		//SWP_DRAWFRAME	围绕窗口画一个框
		//SWP_HIDEWINDOW	隐藏窗口
		//SWP_NOACTIVATE	不激活窗口
		//SWP_NOMOVE	保持当前位置（x和y设定将被忽略）
		//SWP_NOREDRAW	窗口不自动重画
		//SWP_NOSIZE	保持当前大小（cx和cy会被忽略）
		//SWP_NOZORDER	保持窗口在列表的当前位置（hWndInsertAfter将被忽略）
		//SWP_SHOWWINDOW	显示窗口
		//SWP_FRAMECHANGED	强迫一条WM_NCCALCSIZE消息进入窗口，即使窗口的大小没有改变
	}



	static void win_scrsave()
	{
		std::vector< HWND > vecHnd;
		snapshot( vecHnd );
		if( vecHnd.size() ) SendMessage( vecHnd[0], WM_SYSCOMMAND, SC_SCREENSAVE, 0);
	}

	
	static void win_scr_down()
	{
		std::vector< HWND > vecHnd;
		snapshot( vecHnd );
		if( vecHnd.size() ) SendMessage( vecHnd[0], WM_SYSCOMMAND,  SC_MONITORPOWER, 2 );//2= 关闭显示器  
	}


	static void win_scr_low()
	{
		std::vector< HWND > vecHnd;
		snapshot( vecHnd );
		if( vecHnd.size() ) SendMessage( vecHnd[0], WM_SYSCOMMAND,  SC_MONITORPOWER, 1 );//根据MSDN，这个参数如果是1，则 表示显示器处于低能耗状态。 
	}
	
	
	static void win_power( tbool bReboot = 0 , tbool bPowerCmdEnabled = 0 , UINT uPowerCmd = 0 )
	{
		if(bPowerCmdEnabled)
		{
			ExitWindowsEx( uPowerCmd , 0 );
		}
		else
		{
			if ( GetVersion() < 0x80000000 )
			{
				//Win2000&WinNT实现的代码
				UINT shutmethod = bReboot?(EWX_REBOOT|EWX_FORCE):(EWX_POWEROFF|EWX_FORCE);
				HANDLE hToken;
				TOKEN_PRIVILEGES tkp;
				if( OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES|TOKEN_QUERY, &hToken) )
				{
					LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid);
					tkp.PrivilegeCount = 1;
					tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
					AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0);
					ExitWindowsEx( (UINT)shutmethod , 0);
				}
			}
			else
			{
				//Win9x实现的代码
				ExitWindowsEx( bReboot?EWX_REBOOT:EWX_POWEROFF, 0 );
			}
		}
	}


	static HANDLE win_run(  std::string strExePathfile, 
							std::string strArgs, 
							int nShow = SW_MINIMIZE, //SW_NORMAL
							DWORD d_wait_time = INFINITE /*0 为立即返*/ ) 
	{
		//RunAs
		//CreateProcessAsUser


		SHELLEXECUTEINFOA ShExecInfo = {0};
		ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFOA);
		ShExecInfo.fMask  = SEE_MASK_NOCLOSEPROCESS;
		ShExecInfo.hwnd   = NULL;
		ShExecInfo.lpVerb = NULL;
		ShExecInfo.lpFile = strExePathfile.c_str(); //"command";		
		ShExecInfo.lpParameters  = strArgs.c_str(); //"/c dir *.* > c:\\a.txt";	
		ShExecInfo.lpDirectory   = NULL;
		ShExecInfo.nShow    = nShow; //SW_SHOW;
		ShExecInfo.hInstApp = NULL;	
		ShellExecuteExA(&ShExecInfo);
		WaitForSingleObject(ShExecInfo.hProcess, d_wait_time/*in milliseconds*/);
		return ShExecInfo.hProcess;
		
		/*HANDLE h;
		h = wl::WMsg::win_run( "notepad", "" , SW_NORMAL , 0 );	或：	win_run( "cmd" , "/c net start EODService" );
		printf( "%p", h );	
		TerminateProcess( h , 3 );
		
		或：
		_bstr_t s2 = "/c \"" + m_bstrTmpFilename + "\"";
		WMsg::win_run( "cmd", (char*)s2 , SW_HIDE );
		*/
	}



	
	static tbool UseCustomResource( int res, CString strType, SCake & rtnCakeBuf )
	{
		//定位我们的自定义资源，这里因为我们是从本模块定位资源，所以将句柄简单地置为NULL即可
		HRSRC hRsrc = FindResource( NULL, MAKEINTRESOURCE(res), strType.GetString() ); 
		if (NULL == hRsrc)
			return 0;
		//获取资源的大小
		DWORD dwSize = SizeofResource(NULL, hRsrc); 
		if (0 == dwSize)
			return 0;
		//加载资源
		HGLOBAL hGlobal = LoadResource(NULL, hRsrc); 
		if (NULL == hGlobal)
			return 0;
		//锁定资源
		LPVOID pBuffer = LockResource(hGlobal); 
		if (NULL == pBuffer)
			return 0;
		//success
		rtnCakeBuf.let( (tchar*)pBuffer, dwSize );
		return 1;
	}


	static std::string GetEnvStr( std::string strEnvStrName )
	{
		tchar szEnvStrBuf[32767] = {0};
		if( GetEnvironmentVariableA( strEnvStrName.c_str(), szEnvStrBuf, 32767 ) )
		{
			return szEnvStrBuf;
		}
		else
		{
			return "";
		}
	}




#ifdef VC6_COMPATIBLE_X011_
	//
#else
	static CString GetEnvStrTS( CString strEnvStrName )
	{
		CString EnvStr;
		if( EnvStr.GetEnvironmentVariable(strEnvStrName) )
		{
			return EnvStr;
		}
		else
		{
			return _T("");
		}
	}
#endif
 



	static std::string CutTail( std::string strSrc, std::string strChar )
	{
		if( strChar.size() != 1 )
		{
			return strSrc;
		}
		std::string::size_type nPos;
		nPos = strSrc.find_last_of( strChar[0] );
		if( nPos != std::string::npos )
		{
			strSrc[nPos+1] = 0;
		}
		return strSrc.c_str();
	}

	

	static CString CutTailTS( CString strSrc, CString strChar )
	{
		if( strChar.GetLength() != 1 )
		{
			return strSrc;
		}
		int nPos;
		nPos = strSrc.ReverseFind( strChar[0] );
		if( nPos >= 0 ) strSrc = strSrc.Left(nPos) + strChar;
		return strSrc;
	}
	
	

	static std::string GetProcExePathFilename()	//got the full pathfilename
	{
		tchar szFilename[ _MAX_DRIVE + _MAX_PATH + _MAX_FNAME + _MAX_EXT ] = {0};
		if( GetModuleFileNameA( NULL, szFilename, _MAX_DRIVE + _MAX_PATH + _MAX_FNAME + _MAX_EXT ) )
		{
			return szFilename;
		}
		else
		{
			return "";
		}
	}


	static CString GetProcExePathFilenameTS()
	{
		TCHAR szFilename[ _MAX_DRIVE + _MAX_PATH + _MAX_FNAME + _MAX_EXT ] = {0};
		if( GetModuleFileName( NULL, szFilename, _MAX_DRIVE + _MAX_PATH + _MAX_FNAME + _MAX_EXT ) )
		{
			return szFilename;
		}
		else
		{
			return _T("");
		}
	}


	static CString GetProcExeFilePathTS()
	{
		return  CutTailTS(GetProcExePathFilenameTS(), _T("\\"));
	}


	static std::string GetProcExeFilePath()
	{
		return  CutTail(GetProcExePathFilename(), "\\");
	}



	static tbool WriteIniFile( CString strFile, CString strSection, CString strKey, CString strVal )
	{
		//::WritePrivateProfileString("StudentInfo","Name","张三","c:\\stud\\student.ini"); 
		//the content will be:
		//[StudentInfo]
		//Name=张三
		return ::WritePrivateProfileString( strSection, strKey, strVal, strFile ) ? 1 : 0 ;
		//The name of the section is case-independent;
	}


	static CString ReadIniFileTS( CString strFile, CString strSection, CString strKey, int iMaxEleNum=MAX_PATH )
	{
		//iMaxEleNum = strlen + \0 .  total ele num = iMaxEleNum
		CString str;
		//The GetPrivateProfileString function is not case-sensitive; the strings can be a combination of uppercase and lowercase letters.
		::GetPrivateProfileString( strSection, strKey, _T(""), str.GetBuffer( iMaxEleNum ), iMaxEleNum, strFile );
		str.ReleaseBuffer();
		return str;
	}




#ifdef VC6_COMPATIBLE_X011_
	//
#else
	static std::string ReadIniFile( CString strFile, CString strSection, CString strKey, int iMaxEleNum=MAX_PATH )
	{
		CString str;
		str = ReadIniFileTS( strFile, strSection, strKey, iMaxEleNum );
		return CStringA(str).GetString();
	}
#endif




	static std::string MkUId()
	{
		static tint32 i = 1;
		int i2 = (int)time(0) * (int)GetCurrentThreadId() * (int)GetCurrentProcessId();
		int j;
		void *p = SStrf::smalloc(3);
		memcpy( &j, &p, sizeof(int) );
		SStrf::sfree(p);

		double dd = SStrf::rand1() * i * i2 * j * SDte::e_proctime();
		
		std::reverse( (char*)(&dd), (char*)(&dd) + sizeof(double) );

		tchar szBuf[33];
		SClib::p_sprintf()( szBuf, "%x%u", *(int*)(&dd) + j + i , i++ );

		return szBuf;
	}




	static CString GetLastErrorMsgTS()
	{
		DWORD nErr;
		LPVOID lpMsgBuf;
		FormatMessage( 
			FORMAT_MESSAGE_ALLOCATE_BUFFER | 
			FORMAT_MESSAGE_FROM_SYSTEM | 
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			nErr = GetLastError(),
			0, // Default language
			(LPTSTR) &lpMsgBuf,
			0,
			NULL 
		);
		CString str;
		str.Format( _T("GetLastError = %u, %s"), nErr, (LPCTSTR)lpMsgBuf );
		LocalFree( lpMsgBuf );
		return str;
	}



#ifdef VC6_COMPATIBLE_X011_
	//
#else
	static std::string GetLastErrorMsg()
	{
		DWORD nErr;
		LPVOID lpMsgBuf;
		FormatMessage( 
			FORMAT_MESSAGE_ALLOCATE_BUFFER | 
			FORMAT_MESSAGE_FROM_SYSTEM | 
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			nErr = GetLastError(),
			0, // Default language
			(LPTSTR) &lpMsgBuf,
			0,
			NULL 
		);
		// Process any inserts in lpMsgBuf.
		// ...
		// Display the string.
		CString str;
		str.Format( _T("GetLastError = %u, %s"), nErr, (LPCTSTR)lpMsgBuf );
		// Free the buffer.
		LocalFree( lpMsgBuf );

		return CStringA(str).GetString();
	}
#endif



}; //end class WMsg 






/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef VC6_COMPATIBLE_X011_
		//
#else
		 

#ifdef _WINSVC_

class WSvc
{
private:

	CString m_strSZSERVICENAME	; //			_T("VirRervice")
	CString m_strSZSERVICEDISPLAYNAME;	//		_T("Windows Debug Service Manager")
	CString m_strSERVICEDescript;	//	 

private:

	SERVICE_STATUS				m_g_ssServiceStatus;
	SERVICE_STATUS_HANDLE		m_g_sshServiceStatusHandle;


protected:

	static WSvc & Instance()
	{
		static WSvc a;
		return a;
	}


private:
		
	static void WINAPI ServiceCtrlHandler( DWORD dwControl )
	{
		switch (dwControl)
		{

			//下面虽然添加了暂停、继续等请求的处理代码，但没有实际作用
			//这是为什么呢？到了下面的KServiceMain函数里面就明白了...

			case SERVICE_CONTROL_PAUSE:
			Instance().m_g_ssServiceStatus.dwCurrentState = SERVICE_PAUSE_PENDING;
			// TODO: add code to set dwCheckPoint & dwWaitHint
			// This value need to try a lot to confirm 
			// ...
			::SetServiceStatus( Instance().m_g_sshServiceStatusHandle, &(Instance().m_g_ssServiceStatus) );
			// TODO: add code to pause the service
			// not called in this service
			// ...
			Instance().m_g_ssServiceStatus.dwCurrentState = SERVICE_PAUSED;
			// TODO: add code to set dwCheckPoint & dwWaitHint to 0
			break;

			case SERVICE_CONTROL_CONTINUE:
			Instance().m_g_ssServiceStatus.dwCurrentState = SERVICE_CONTINUE_PENDING;
			// TODO: add code to set dwCheckPoint & dwWaitHint
			::SetServiceStatus( Instance().m_g_sshServiceStatusHandle, &(Instance().m_g_ssServiceStatus) );
			// TODO: add code to unpause the service
			// not called in this service
			// ...
			Instance().m_g_ssServiceStatus.dwCurrentState = SERVICE_RUNNING;
			// TODO: add code to set dwCheckPoint & dwWaitHint to 0
			break;

			case SERVICE_CONTROL_STOP:
			Instance().m_g_ssServiceStatus.dwCurrentState = SERVICE_STOP_PENDING;
			// TODO: add code to set dwCheckPoint & dwWaitHint
			::SetServiceStatus( Instance().m_g_sshServiceStatusHandle, &(Instance().m_g_ssServiceStatus) );
			// TODO: add code to stop the service
			Stop();
			Instance().m_g_ssServiceStatus.dwCurrentState = SERVICE_STOPPED;
			// TODO: add code to set dwCheckPoint & dwWaitHint to 0
			break;

			case SERVICE_CONTROL_SHUTDOWN:
			// TODO: add code for system shutdown
			// as quick as possible
			break;

			case SERVICE_CONTROL_INTERROGATE:
			// TODO: add code to set the service status
			// ...
			Instance().m_g_ssServiceStatus.dwCurrentState = SERVICE_RUNNING;
			break;
		}

		::SetServiceStatus( Instance().m_g_sshServiceStatusHandle, &(Instance().m_g_ssServiceStatus) );
	}



	static void WINAPI KServiceMain( DWORD argc, LPTSTR * argv )
	{
		Instance().m_g_ssServiceStatus.dwServiceType = SERVICE_WIN32;
		Instance().m_g_ssServiceStatus.dwCurrentState = SERVICE_START_PENDING;
		Instance().m_g_ssServiceStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP;//上面的问题的答案就在这里
		Instance().m_g_ssServiceStatus.dwWin32ExitCode = 0;
		Instance().m_g_ssServiceStatus.dwServiceSpecificExitCode = 0;
		Instance().m_g_ssServiceStatus.dwCheckPoint = 0;
		Instance().m_g_ssServiceStatus.dwWaitHint = 0;

		Instance().m_g_sshServiceStatusHandle = ::RegisterServiceCtrlHandler( Instance().m_strSZSERVICENAME, ServiceCtrlHandler );

		if ( Instance().m_g_sshServiceStatusHandle == (SERVICE_STATUS_HANDLE)0 )
		{
			return;
		}

		bool bInitialized = false;
		// Initialize the service
		// ...
		Start();

		bInitialized = true;

		Instance().m_g_ssServiceStatus.dwCheckPoint = 0;
		Instance().m_g_ssServiceStatus.dwWaitHint = 0;
		if (!bInitialized )
		{
			Instance().m_g_ssServiceStatus.dwCurrentState = SERVICE_STOPPED;
			Instance().m_g_ssServiceStatus.dwWin32ExitCode = ERROR_SERVICE_SPECIFIC_ERROR;
			Instance().m_g_ssServiceStatus.dwServiceSpecificExitCode = 1;
		}
		else
		{
			Instance().m_g_ssServiceStatus.dwCurrentState = SERVICE_RUNNING;
		}
		::SetServiceStatus( Instance().m_g_sshServiceStatusHandle, &(Instance().m_g_ssServiceStatus) );
		return;
	}


	static void Start()
	{
		//LogEvent("Service Starting...");
		Instance().OnStart();
	}


	static void Stop()
	{
		//LogEvent("Service Stoped.");
		Instance().OnStop();
	}


	/////////====================== ===========


public:

	WSvc()
	{ 
		m_strSZSERVICENAME = _T("");
	}


	virtual ~WSvc()	
	{ ;
	}


	static void Init( CString cstrSvcName, CString cstrSvcDisp, CString cstrSvcDiscript )
	{
		WSvc & A(Instance());

		A.m_strSZSERVICENAME = cstrSvcName;
		A.m_strSZSERVICEDISPLAYNAME =cstrSvcDisp;
		A.m_strSERVICEDescript = cstrSvcDiscript;

		//(*this) = A;
	}


	static tbool SvcDispatcher( CString sname )
	{
		CString sname1;
		sname1.Format( _T("%s"), sname );

		SERVICE_TABLE_ENTRY  e[2] ;

		e[0].lpServiceName = (LPTSTR)sname1.GetString();
		e[0].lpServiceProc = KServiceMain;

		e[1].lpServiceName = NULL;
		e[1].lpServiceProc = NULL;
		 
		return ::StartServiceCtrlDispatcher(e)==0?0:1;
	}



	static tbool SvcDispatcher()	///SvcDispatcher will wait every service thread to return.
	{
		WSvc & A(Instance());
		return SvcDispatcher( A.m_strSZSERVICENAME );
	}



	virtual void OnStart()
	{
		;
	}


	virtual void OnStop()
	{
		;
	}


	/////////=======================================================


	static tbool SCM_InstallService( 
									CString strSvcExeFilename, // if "", then use process exe fullfilename.
									CString strSvcName, 
									CString strSvcDisplayName, 
									CString strSvcDescript, 
									std::string & strErrMsg	 ,
									tbool isAutoStart = 1	) 
	{
		CStringA strErrMsg1("");
		tbool rc(0);

		SC_HANDLE schSCManager = OpenSCManager( NULL, NULL, SC_MANAGER_CREATE_SERVICE); 

		if (schSCManager==0) 
		{
			strErrMsg1.Format( "OpenSCManager failed. %s", WMsg::GetLastErrorMsg().c_str() );
			rc = 0;
			goto L_FuncEnd;
		}
		

		if( strSvcExeFilename == _T("") )
		{
			TCHAR szFilename[256];
			::GetModuleFileName(NULL, szFilename, 255);
			strSvcExeFilename = szFilename;
		}

		SC_HANDLE schService ;
		schService = CreateService
			( 
				schSCManager,                /* SCManager database      */ 
				strSvcName,               /* name of service         */ 
				strSvcDisplayName,        /* service name to display */ 
				SERVICE_ALL_ACCESS,          /* desired access          */ 
				SERVICE_WIN32_OWN_PROCESS|SERVICE_INTERACTIVE_PROCESS ,   /* service type            */ 
				isAutoStart?SERVICE_AUTO_START:SERVICE_DEMAND_START ,     /* start type              */ 
				SERVICE_ERROR_NORMAL,        /* error control type      */ 
				strSvcExeFilename,                  /* service's binary        */ 
				NULL,                        /* no load ordering group  */ 
				NULL,                        /* no tag identifier       */ 
				NULL,                        /* no dependencies         */ 
				NULL,                       /* LocalSystem account     */ 
				NULL                        /* no password             */ 
			);


		if ( schService == NULL ) 
		{
			strErrMsg1.Format( "Failed to create service `%s`. %s", CStringA(strSvcName), WMsg::GetLastErrorMsg().c_str() );
			CloseServiceHandle(schSCManager);
			rc = 0;
			goto L_FuncEnd;
		}
		

		SERVICE_DESCRIPTION  ServiceDesc;
		//TCHAR szDescription[MAX_PATH];
		//_tcscpy( szDescription, strSvcDescript );
		//std::copy( (LPTSTR)(LPCTSTR)strSvcDescript.GetString(), 1 + strSvcDescript.GetLength() + (LPTSTR)(LPCTSTR)strSvcDescript.GetString(), szDescription );
		ServiceDesc.lpDescription   =   (LPTSTR)(LPCTSTR)strSvcDescript.GetString();
		::ChangeServiceConfig2( schService,  SERVICE_CONFIG_DESCRIPTION,  &ServiceDesc );

		//printf( "Service %s installed\n", CStringA(SZSERVICENAME) );
		rc = 1;

		CloseServiceHandle(schService); 
 
		CloseServiceHandle(schSCManager);

   L_FuncEnd:{;}
		strErrMsg = strErrMsg1.GetString();
		return rc;		
	}



	static tbool  SCM_UnInstallService( CString strSvcName , std::string & strErrmsg ) 
	{
		CStringA strErrMsg1("");
		tbool rc(0);

		SC_HANDLE schSCManager = OpenSCManager( NULL, NULL, SC_MANAGER_ALL_ACCESS); 

		if (schSCManager==0) 
		{
			strErrMsg1.Format( "OpenSCManager failed. %s", WMsg::GetLastErrorMsg().c_str() );
			rc = 0;
			goto L_FuncEnd;
		}
	

		SC_HANDLE schService;
		schService = OpenService( schSCManager, strSvcName, SERVICE_ALL_ACCESS );

		if (schService==0) 
		{
			strErrMsg1.Format( "OpenService failed. %s", WMsg::GetLastErrorMsg().c_str() );
			rc = 0;
			goto L_FuncEnd;
		}
	 

		if(!DeleteService(schService)) 
		{
			strErrMsg1.Format( "Failed to delete service. %s", WMsg::GetLastErrorMsg().c_str() );
			rc = 0;
			goto L_FuncEnd;
		}
		
		//printf( "Service %s removed\n", CStringA(SZSERVICENAME) );
		rc = 1;
 
		CloseServiceHandle(schService); 
 
		CloseServiceHandle(schSCManager);

	L_FuncEnd:{;}
		strErrmsg = strErrMsg1.GetString();
		return rc;
	}



	static tbool SCM_SetAutoStartService( 
										CString strServiceName, 
										std::string & strErrmsg , /* out */
										tbool isAutoStart = 1	 )
	{
		SC_HANDLE schSCManager = NULL;
		schSCManager = OpenSCManager( NULL, NULL, SC_MANAGER_ALL_ACCESS);
		if (schSCManager == NULL)
		{
			strErrmsg = "Failed to open SCManager. " + WMsg::GetLastErrorMsg();
			return 0;
		}
		SC_HANDLE schService = OpenService(
			schSCManager,
			strServiceName, 
			SERVICE_ALL_ACCESS);

		if (schService == NULL)
		{
			strErrmsg = "Failed to open service. " + WMsg::GetLastErrorMsg();
			return 0;
		}

		//auto start sevice in next reboot time.
		BOOL bret = ChangeServiceConfig(schService, SERVICE_NO_CHANGE,

			isAutoStart?SERVICE_AUTO_START:SERVICE_DEMAND_START , // 

			SERVICE_NO_CHANGE, NULL, NULL, NULL, NULL, NULL,
			NULL, NULL);

		if(!bret)
		{
			strErrmsg = "failed to configure service. " + WMsg::GetLastErrorMsg();
		}
		else
		{
			//SC_TRACE(_T("Successfully make %s auto_start"), m_szServiceName);
		}

		CloseServiceHandle(schService);
		CloseServiceHandle(schSCManager);

		return bret?1:0;
	}



	static bool SCM_ChgStartAccount( CString m_szServiceName, CString strUserName, CString strUserPwd , std::string & strErrmsg )
	{
		SC_HANDLE schSCManager = NULL;
		schSCManager = OpenSCManager( NULL, NULL, SC_MANAGER_ALL_ACCESS);
		if (schSCManager == NULL)
		{
			strErrmsg = "Failed to open SCManager. " + WMsg::GetLastErrorMsg();
			return false;
		}
		SC_HANDLE schService = OpenService(
			schSCManager,
			m_szServiceName, 
			SERVICE_ALL_ACCESS);

		if (schService == NULL)
		{
			strErrmsg = "Failed to open service. " + WMsg::GetLastErrorMsg();
			return false;
		}

		//auto start sevice in next reboot time.
		BOOL bret = ChangeServiceConfig(schService, SERVICE_NO_CHANGE,
			SERVICE_AUTO_START, SERVICE_NO_CHANGE, NULL, NULL, NULL, NULL, strUserName, strUserPwd, NULL);

		if(!bret)
		{
			strErrmsg = "failed to configure service. " + WMsg::GetLastErrorMsg();
			return false; 
		}
		else
		{
			//SC_TRACE(_T("Successfully make %s auto_start"), m_szServiceName);
		}

		CloseServiceHandle(schService);
		CloseServiceHandle(schSCManager);
		return true;
	}


		
	// simple Install
	 
	static void SimpleInstallService()  
	{
		WSvc & A(Instance());
		std::string strerr;

		WSvc::SCM_InstallService( _T("") , A.m_strSZSERVICENAME, A.m_strSZSERVICEDISPLAYNAME, A.m_strSERVICEDescript, strerr );

		if ( !strerr.empty() )
		{
			printf( "%s\n", strerr.c_str() );
		}
		else
		{
			printf( "ok in i\n" );
		}
	}


	static void SuperInstSvc() 
	{
		std::vector<std::string> vecs1;
		std::string strMyexePathFname = WMsg::GetProcExePathFilename();
		std::string strMyexeFname;

		SStrvs::vsa_imp( strMyexePathFname, std::string("\\"), 1, vecs1 );

		if( !vecs1.empty() )
		{
			std::vector<std::string>::iterator it = vecs1.end();
			it--;
			strMyexeFname = *it;

			std::string s1;		//因为%SystemRoot%中没空格所以以下有些情况可以不加引号了。

			s1 = "cmd /c copy \"" + strMyexePathFname + "\" %SystemRoot%\\";
			s1 += strMyexeFname;
			system(s1.c_str());
			printf( "copied.\n" );

			s1 = "netsh firewall add allowedprogram ";
			s1 += "\"%SystemRoot%\\" + strMyexeFname + "\" ";
			s1 += strMyexeFname;
			system(s1.c_str());
			printf( "sh ed.\n" );

			s1 = "cmd /c %SystemRoot%\\" + strMyexeFname + " -i";
			system(s1.c_str());
		}
	}



	static void SimpleUnInstallService() 
	{
		WSvc & A(Instance());
		std::string strerr;

		WSvc::SCM_UnInstallService( A.m_strSZSERVICENAME, strerr );

		if ( !strerr.empty() )
		{
			printf( "%s\n", strerr.c_str() );
		}
		else
		{
			printf( "ok in un\n" );
		}
	}


	
	static tbool SimpInst( int argc, CString argv ) 
	{
		if ( argc == 2 && argv[1] == _T('i') ) //就地注svc
		{
			SimpleInstallService();
			return 1;
		}

		if ( argc == 2 && argv[1] == _T('s') ) //拷到win目录，同名，注svc，netsh开例外
		{
			SuperInstSvc();
			return 1;
		}

		if ( argc == 2 && argv[1] == _T('-') )
		{
			SimpleUnInstallService();
			return 1;
		}

		return 0;
	}




}
; //end class WSvc 


#endif //_WINSVC_


#endif	//VC6_COMPATIBLE_X011_






X011_NAMESPACE_END

#endif




/*
windows file 
*/

#ifndef X011__H_w_WFile_h
#define X011__H_w_WFile_h




X011_NAMESPACE_BEGIN



class WFile : public SFile
{

private:



public:

	WFile( )
	{
		;
	}


	virtual ~WFile( )
	{ ;
	}



	void rename( std::string strNewNameNoDir )
	{
		std::string strCmd;

		strCmd = "ren \"";
		strCmd += this->filename();
		strCmd += "\" ";
		strCmd += "\"" + strNewNameNoDir + "\"";

		system( strCmd.c_str() );
	}


	static tbool FileAttriIsDir( std::string strFullPathName )
	{
		DWORD i = GetFileAttributesA( strFullPathName.c_str() );
		if( i == INVALID_FILE_ATTRIBUTES )
		{
			return 0;
		}
		return ( i & FILE_ATTRIBUTE_DIRECTORY ) ? 1 : 0 ;
	}




	static void ListFile(	std::string strRootPathOrDir,	// e.g. "c:\\"  or  "c:\\t"。if you don't specify the rootdir, it will be '\\'
							std::string strPattern,			//e.g. "*.mp3"	"*"
							std::vector<std::string> & vecstrRtnBuf	, 
							tbool bIncludeDirName,
							tbool bIncludeFileName, 
							tbool bRetFullName	)	
	{
		//we don't clear vecstrRtnBuf, so, you can append filenames

		WIN32_FIND_DATAA FindFileData;
		HANDLE hFind = INVALID_HANDLE_VALUE;

		std::string strPathPattern;

		strPathPattern = MkDir2Path( strRootPathOrDir ) + strPattern;
	
		hFind = FindFirstFileA( strPathPattern.c_str(), &FindFileData); // 
	
		do 
		{
			if (hFind == INVALID_HANDLE_VALUE)
			{
				break;
			}

			std::string strFn( FindFileData.cFileName );
			std::string strFullFn( MkDir2Path( strRootPathOrDir ) + strFn );
			std::string strOut;

			if( bRetFullName )
			{
				strOut = strFullFn;
			}
			else
			{
				strOut = strFn;
			}

			if( strFn != "." && strFn != ".." )
			{
				if( bIncludeDirName && FileAttriIsDir( strFullFn ) )
				{
					vecstrRtnBuf.push_back( strOut );
				}

				if( bIncludeFileName && !FileAttriIsDir( strFullFn ) )
				{
					vecstrRtnBuf.push_back( strOut );
				}
			}
			
		}while( FindNextFileA(hFind, &FindFileData) != 0 );
		
		FindClose(hFind);

		////make the strPattern affective
		//for( std::vector<std::string>::iterator it1 = vecstrRtnBuf.begin(); it1 != vecstrRtnBuf.end();  )
		//{
		//	std::string s2( strPattern );

		//	if( s2.size() < 3 ) break;
		//	if( s2[0] != '*' ) break;
		//	if( s2[1] != '.' ) break;
		//	if( s2[2] == '*' ) break;

		//	std::string s1( *it1 );

		//	std::reverse( s1.begin(), s1.end() );

		//	s2.erase( s2.begin() );
		//	std::reverse( s2.begin(), s2.end() );

		//	if( s1.find(s2) != 0 ) // not pattern, erase it
		//	{
		//		it1 = vecstrRtnBuf.erase( it1 );
		//	}
		//	else
		//		it1++;
		//}// end for

	}


	static void ListAllFile(	std::string strRootPathOrDir,		// e.g. "c:\\"  or  "c:\\t"。if you don't specify the rootdir, it will be '\\'
								std::string strPattern,				//e.g. "*.mp3"	"*"
								std::vector<std::string> & vecstrRtnBuf	, 
								tbool bIncludeDirName  = 0 ,
								tbool bIncludeFileName = 1 , 
								tbool bRetFullName     = 0 ,
								tbool bRecursive       = 0	)
	{
		//we don't clear vecstrRtnBuf, so, you can append filenames

		if( bRecursive )
		{
			std::vector<std::string>  vecBuf1;
			std::vector<std::string>::iterator itBuf1;
			std::vector<std::string>  vecBuf2;
			std::vector<std::string>  vecBuf_FullName;

			vecBuf1.push_back( strRootPathOrDir );

			do{
				vecBuf2.clear();

				itBuf1 = vecBuf1.begin();

				if( itBuf1 == vecBuf1.end() ) 
				{
					break;
				}

				ListFile( *itBuf1, "*", vecBuf2, 1, 0, 1 ); //record what next to do .
				vecBuf_FullName.insert( vecBuf_FullName.end(), vecBuf2.begin(), vecBuf2.end() ); 

				vecBuf1.erase( itBuf1 ); //del the processed folder

				vecBuf1.insert( vecBuf1.end(), vecBuf2.begin(), vecBuf2.end() ); //insert the new found folders.

			}while(1);

			if( 1 )
			{
				for( std::vector<std::string>::iterator it = vecBuf_FullName.begin();
					 it != vecBuf_FullName.end();
					 ++it )
				{
					ListFile( *it, strPattern, vecstrRtnBuf, bIncludeDirName, bIncludeFileName, bRetFullName ); //record the result.
				}
				ListFile( strRootPathOrDir, strPattern, vecstrRtnBuf, bIncludeDirName, bIncludeFileName, bRetFullName );
			}
		}
		else
		{
			ListFile( strRootPathOrDir, strPattern, vecstrRtnBuf, bIncludeDirName, bIncludeFileName, bRetFullName );
		}
	}



	//
	static void DelHalf( std::string strRootDir, std::string strPattern )			//e.g. "*.mp3"	"*", but this func is slow
	{
		std::vector<std::string>  vecstrRtnBuf;

		ListFile( strRootDir, strPattern, vecstrRtnBuf, 0, 1, 1 );

		for( std::vector<std::string>::iterator it1 = vecstrRtnBuf.begin(); it1 != vecstrRtnBuf.end(); ++it1 )
		{
			for( std::vector<std::string>::iterator it2 = vecstrRtnBuf.begin(); it2 != vecstrRtnBuf.end(); ++it2 )
			{
				SFile f1, f2;
				f1.bind( *it1 );
				f2.bind( *it2 );
				if( f1.IsHeadOf(f2) ) f1.erase();
			} // end for it2
		} // end for it1 
	}


	//
	static void DelHalf_fast( std::string strRootDir, std::string strPattern, tsize iMinLen )			//e.g. "*.mp3"	"*", but this func is fast
	{
		struct FileStat_t
		{ 
			std::string strFullFn;
			std::string strFileDSeal;
			tsize iFileLen;
			tbool tbExists;
		} ;
		std::vector<std::string>  vecstrRtnBuf;
		std::vector<FileStat_t>  vecFileStat;

		ListFile( strRootDir, strPattern, vecstrRtnBuf, 0, 1, 1 );

		for( std::vector<std::string>::iterator it1 = vecstrRtnBuf.begin(); it1 != vecstrRtnBuf.end(); ++it1 )
		{
			SFile fl ;
			SCake ck;
			FileStat_t fs;

			fl.bind( *it1 );
			fs.strFullFn = *it1;
			fs.iFileLen = fl.len();
			fs.tbExists = fs.iFileLen < iMinLen ? 0 : 1 ;
			if( !fs.tbExists )
			{
				fl.erase();
				continue;
			}
			fl.read( ck );
			fs.strFileDSeal = SCalc::dseal( ck.buf(), iMinLen, 123 );

			vecFileStat.push_back( fs );
		} // end for it1 


		//.now traverse the dseal
		for( std::vector<FileStat_t>::iterator it2 = vecFileStat.begin(); it2 != vecFileStat.end(); ++it2 )
		{
			for( std::vector<FileStat_t>::iterator it3 = vecFileStat.begin(); it3 != vecFileStat.end(); ++it3 )
			{
				if( !(it2->tbExists && it3->tbExists) ) continue;
				if( it2->strFileDSeal != it3->strFileDSeal ) continue;
				if( it2->strFullFn == it3->strFullFn ) continue;
				
				std::vector<FileStat_t>::iterator it4 = it3;
				if( it2->iFileLen < it3->iFileLen ) it4 = it2;
				
				SFile::erase( it4->strFullFn );
				it4->tbExists = 0;

				printf( "%s\n", it4->strFullFn.c_str() );
			} // end for it3
		} // end for it2 

	}



	tbool bind_tmpfile( const tchar * pszExt = NULL , int iThreadId = 0 ) //GetCurrentThreadId()
	{
		std::string  strEnvTmpPath;
		strEnvTmpPath = WMsg::GetEnvStr( "TMP" );
		if( strEnvTmpPath == "" ) return 0;
		return bind_nofile( strEnvTmpPath, pszExt, iThreadId );
	}


 
	//pack和unpack,在vaio上测试，906M的目录，读取用4分钟，写盘用5分钟。共约9分钟。
	static void PackFolder( std::string strWorkPathOrDir, SCake & ckOut )
	{
		//std::vector<tchar> v1;
		std::string strWorkPath;
		std::vector<std::string>::iterator it;
		std::vector<std::string> vDirFullNameLst;
		std::vector<std::string> vDirNameLst;
		std::vector<std::string> vFileFullPathNameLst;
		std::vector<std::string> vFileRelaPathNameLst;
		std::vector<std::string> vFileLenLst;
		std::string strInfoHeader;

		//TR use 0, TD use 1
		std::string strTD = "\t"; 
		std::string strTR = "\n";


		strWorkPath = MkDir2Path( strWorkPathOrDir ) ;


		//get vDirNameLst

		ListAllFile( strWorkPath, "*.*", vDirFullNameLst, 1, 0, 1, 1 );

		for( it = vDirFullNameLst.begin(); it != vDirFullNameLst.end(); ++it )
		{
			const char *p;
			p = it->c_str() + strWorkPath.size();
			vDirNameLst.push_back(p);
		}

		//distinct vDirNameLst

		SSetu::vs_setgroup( vDirNameLst );


		//get file rela_path name
 
		ListAllFile( strWorkPath, "*.*", vFileFullPathNameLst, 0, 1, 1, 1 );

		for( it = vFileFullPathNameLst.begin(); it != vFileFullPathNameLst.end(); ++it )
		{
			const char *p;
			p = it->c_str() + strWorkPath.size();
			vFileRelaPathNameLst.push_back(p);
		}
	 

		//get file len

		tint32 iLenAmount=0;

		for( it = vFileFullPathNameLst.begin(); it != vFileFullPathNameLst.end(); ++it )
		{
			SFile sf;
			tint32 i;

			sf.bind( *it );
			i = sf.len();
			iLenAmount += i;
			vFileLenLst.push_back( SStrf::sltoa( i ) );
		}


		//create 3 info_list to a InfoHeader
		
		for( it = vDirNameLst.begin(); it != vDirNameLst.end(); ++it )
		{
			strInfoHeader += *it;
			strInfoHeader += strTD;  
		}
		strInfoHeader += strTR;

		for( it = vFileRelaPathNameLst.begin(); it != vFileRelaPathNameLst.end(); ++it )
		{
			strInfoHeader += *it;
			strInfoHeader += strTD;  
		}
		strInfoHeader += strTR;

		for( it = vFileLenLst.begin(); it != vFileLenLst.end(); ++it )
		{
			strInfoHeader += *it;
			strInfoHeader += strTD;  
		}
		strInfoHeader += strTR;



		//get file bin

		ckOut.redim( iLenAmount + (tsize)strInfoHeader.size() + 1 );

		tchar *p1;

		p1 = ckOut.buf();

		//put info header
		SStrf::smemcpy( p1, strInfoHeader.c_str(), (tsize)strInfoHeader.size() );
		p1 += (tsize)strInfoHeader.size();

		*p1 = 0;
		p1 ++;

		std::vector<std::string>::iterator it2;

		it2 = vFileLenLst.begin();
		for( it = vFileFullPathNameLst.begin(); it != vFileFullPathNameLst.end(); ++it, ++it2 )
		{
			SCake ck;
			SFile sf;

			sf.bind( *it );
			sf.read( ck );

			if( ck.len() )
			{
				SStrf::smemcpy( p1, ck.buf(), (tint32)ck.len() <  SStrf::satol( *it2 ) ? (tint32)ck.len() :  SStrf::satol( *it2 ) );				
			}

			//p1 += ck.len();
			p1 += SStrf::satol( *it2 );
		}

	}


 
	static void UnPackFolder( std::string strWorkPathOrDir, const SCake & ckIn , std::vector<std::string> *pvDirFullNameLst = NULL, std::vector<std::string> *pvFileFullPathNameLst = NULL )
	{
		if( ckIn.len() == 0 ) return;
		
		//std::for_each( ckIn.buf(), ckIn.buf() + ckIn.len(), xor2() );

		//std::vector<tchar> v1;
		std::string strWorkPath;
		std::vector<std::string>::iterator it;
		std::vector<std::string> vDirFullNameLst;
		std::vector<std::string> vDirNameLst;
		std::vector<std::string> vFileFullPathNameLst;
		std::vector<std::string> vFileRelaPathNameLst;
		std::vector<std::string> vFileLenLst;
		std::string strInfoHeader;

		
		//TR use 0, TD use 1
		std::string strTD = "\t";
		std::string strTR = "\n";

		strWorkPath = MkDir2Path( strWorkPathOrDir ) ;

		strInfoHeader = (const char*)ckIn.buf_const();


		//create all DIRs

		SStrvs::vsa_imp( SStrvs::vsa_get( strInfoHeader, strTR, 0, 0 ), strTD, 1, vDirNameLst );

		std::sort( vDirNameLst.begin(), vDirNameLst.end() ); //此时可以保证短的目录名在前,CreateDirectory可以逐级正常工作了.

		for( it = vDirNameLst.begin(); it != vDirNameLst.end(); ++it )
		{
			std::string s1;
			s1 = MkDir2Path( strWorkPathOrDir ) + *it ;
			vDirFullNameLst.push_back( s1 );

			CString cs1;
			cs1 = s1.c_str();
			::CreateDirectory( cs1, NULL );
			//::SHCreateDirectoryEx(NULL, cs1, NULL);
		}


		//get all full filenames

		SStrvs::vsa_imp( SStrvs::vsa_get( strInfoHeader, strTR, 0, 1 ), strTD, 1, vFileRelaPathNameLst );

		for( it = vFileRelaPathNameLst.begin(); it != vFileRelaPathNameLst.end(); ++it )
		{
			std::string s1;
			s1 = MkDir2Path( strWorkPathOrDir ) + *it ;
			vFileFullPathNameLst.push_back( s1 );
		}


		//get all file len

		SStrvs::vsa_imp( SStrvs::vsa_get( strInfoHeader, strTR, 0, 2 ), strTD, 1, vFileLenLst );


		//return lists
		if( pvDirFullNameLst != NULL ) *pvDirFullNameLst = vDirFullNameLst;
		if( pvFileFullPathNameLst != NULL ) *pvFileFullPathNameLst = vFileFullPathNameLst;


		//create all files

		const tchar *p1;

		p1 = ckIn.buf_const() + strInfoHeader.size() + 1;

		//v1.insert( v1.end(), ckIn.buf_const() + strInfoHeader.size() + 1 , ckIn.buf_const() + ckIn.len() );
		//ckIn.redim(0); //ckIn is useless now, free the memory.

		for( ; !vFileFullPathNameLst.empty(); )
		{
			std::string s1;
			tint32 i1;

			s1 = vFileFullPathNameLst.front();
			i1 = SStrf::satol( vFileLenLst.front() );

			if( p1 > ckIn.buf_const() + ckIn.len() ) break;

			SFile sf;

			sf.bind( s1 );

			sf.write( p1, (tsize)i1 );

			vFileFullPathNameLst.erase( vFileFullPathNameLst.begin() );
			vFileLenLst.erase( vFileLenLst.begin() );

			p1 += i1;
		}
		
	}


	////////////convert code


	static std::wstring Utf8toWch( const std::string & s )
	{
		int  unicodeLen = MultiByteToWideChar( CP_UTF8, 0, s.c_str(), -1, NULL, 0 );
		wchar_t *  pUnicode;  
		pUnicode = new  wchar_t[unicodeLen+1];  
		MultiByteToWideChar( CP_UTF8, 0, s.c_str(), -1, pUnicode, unicodeLen );

		std::wstring ws;
		ws = pUnicode;
		delete [] pUnicode; 
		return ws;
	}


	static std::string & ChtoUtf8( std::string & s )
	{
		std::string ss2( 3 * s.length() + 3 , 'a' );
		WideCharToMultiByte(CP_UTF8, 0, CStringW(s.c_str()), -1, &(ss2[0]), (int)ss2.length(), NULL,FALSE);
		return s = ss2.c_str();
	}


	static std::string & Utf8toCh( std::string & s )
	{
		std::wstring ws = Utf8toWch( s );
		 DWORD dwNum = WideCharToMultiByte(CP_OEMCP,NULL,ws.c_str(),-1,NULL,0,NULL,FALSE);
		 char *psText = new char[dwNum];
		 WideCharToMultiByte (CP_OEMCP,NULL, ws.c_str(),-1,psText,dwNum,NULL,FALSE);
		 s = psText;
		 delete []psText;
		 return s;
	}



	//windows local functions:

	static tbool SetFileToCurrentTime( std::string strFullPathName )
	{
		SYSTEMTIME st;
		SDte t;
		GetSystemTime(&st);    // gets current time

		t.m_year  =  st.wYear    ;
		t.m_mon   =  st.wMonth  ;
		t.m_day =  st.wDay   ;
		t.m_hour = st.wHour  ;
		t.m_min  = st.wMinute  ;
		t.m_sec  = st.wSecond  ;

		return SetFileToTheTime( strFullPathName, t );
	}


	static tbool SetFileToTheTime( std::string strFullPathName, SDte __tm ) 
	{
		HANDLE hFile;

		hFile = CreateFileA( strFullPathName.c_str(), 
							  FILE_ALL_ACCESS, FILE_SHARE_WRITE|FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, 0 ); 

		if( hFile == INVALID_HANDLE_VALUE ) 
		{
			return 0;
		}

		//FILETIME SYSTEMTIME 

		FILETIME ft;
		BOOL f;

		SYSTEMTIME st;

		SStrf::smemset( &st );

		st.wYear =   __tm.m_year;
		st.wMonth  =  __tm.m_mon;
		st.wDay    =  __tm.m_day;
		st.wHour   =  __tm.m_hour;
		st.wMinute =  __tm.m_min;
		st.wSecond =  __tm.m_sec;

		SystemTimeToFileTime( &st, &ft );  // converts to file time format

		//f = SetFileTime(hFile, (LPFILETIME) NULL, (LPFILETIME) NULL, &ft);          // sets last-write time for file
		f = SetFileTime(hFile, &ft, &ft, &ft);     

		CloseHandle(hFile);

		return f;
	}




	SDte GetFileModiTime()
	{
		SDte t;
		if( GetFileModiTime( this->filename(), t ) ) return t;
		return SDte();
	}
	

	static tbool GetFileModiTime( std::string strFullPathName , SDte & __tm, DWORD dwDesiredAccess = FILE_SHARE_READ ) //FILE_ALL_ACCESS
	{
		HANDLE hFile;
		
		//hFile = CreateFileA( strFullPathName.c_str(), dwDesiredAccess, FILE_SHARE_WRITE|FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, 0 ); 
		hFile = CreateFileA( strFullPathName.c_str(), dwDesiredAccess, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, 0 ); 

		if( hFile == INVALID_HANDLE_VALUE ) 
		{
			return 0;
		}

		FILETIME ft;
		FILETIME ft1;
		BOOL f;

		f = GetFileTime(hFile, &ft, &ft, &ft1); //ft1 is used.

		CloseHandle(hFile);

		if( !f )
		{
			return 0;
		}

		SYSTEMTIME stUTC, stLocal;

		FileTimeToSystemTime(&ft1, &stUTC);
		SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal);

		SYSTEMTIME st = stLocal; 


#ifdef VC6_COMPATIBLE_X011_
		SDte  t( __tm );	//we use this line, for compatible of VC6
#else
		SDte & t( __tm ); //don't use this line, for VC higher than VC6
#endif


		SStrf::smemset( &t );

		t.m_year  =  st.wYear    ;
		t.m_mon   =  st.wMonth  ;
		t.m_day =  st.wDay   ;
		t.m_hour = st.wHour  ;
		t.m_min  = st.wMinute  ;
		t.m_sec  = st.wSecond  ;

		return f?1:0;
	}



};//end class WFile






X011_NAMESPACE_END


#endif







/*
WNava , nava with utf8 <--> ch converter
*/

#ifndef X011__H_W_WNAVA_H
#define X011__H_W_WNAVA_H



X011_NAMESPACE_BEGIN



class WNava : public SNavass 
{
private:


public:

	virtual ~WNava() {;} 


	//static tbool IsUtf8Base()	// 本文件必须在结合成1.h以后以utf8形式保存,才能使win与linu下自动产生正确结果.平时不用.或结合项目仿照此另做函数完成相同任务.
	//{
	//	const char * p = "初";
	//	return p[2] ? 1 : 0 ;
	//}


	
	void impconf( const std::string & ssource, std::string ssepTR = "\n", std::string ssepTD = "=", std::string strMemoLineHead = "#" )
	{
		//以下算法，数据中允许有TD

		std::vector<std::string>  vecLines;
		SStrvs::vsa_imp( ssource, ssepTR, 1, vecLines );
		for( std::vector<std::string>::iterator it = vecLines.begin(); it != vecLines.end(); ++it )
		{
			std::string::size_type i;

			i = it->find(ssepTD);
			if( i == std::string::npos ) continue;

			SStrf::strim( *it );
			if( it->find(strMemoLineHead) == 0 ) continue;

			(*it)[i] = 0;
			this->let( it->c_str(), it->c_str() + i + ssepTD.size() );
		}

		this->trimall();
	}


	typedef std::string & (* P_t) ( std::string & );


	void AtoB( P_t pf )
	{
		std::map< std::string, std::string > mapTmp = m_mapKnl;

		this->clear();

		for( MAP_MAPKNL_IT it = mapTmp.begin(); it != mapTmp.end(); ++it )
		{
			std::string s1 = it->first;
			std::string s2 = it->second;

			(*pf)( s1 );
			(*pf)( s2 );

			let( s1, s2 ); 
		}
	}


	void ChtoUtf8()
	{
		AtoB( WFile::ChtoUtf8 );
	}

	void Utf8toCh()
	{
		AtoB( WFile::Utf8toCh );
	}


};




X011_NAMESPACE_END

#endif




/*
W series
Windows 32-Bit Registry API. 
*/
 

#ifndef X011__H_WReg32_h
#define X011__H_WReg32_h


X011_NAMESPACE_BEGIN


class WReg32 {

private:

public:

	WReg32()
	{
	}

	virtual ~WReg32()
	{ 
	}


	static tbool ChkSection( HKEY hkPrimKey, LPCSTR lpszSection )
	{
		tbool bRc = 0;

		try
		{
			do//fakedo
			{
                if( !lpszSection )
				{
					bRc=0;
					break;
				}

				HKEY hkReg;
				LONG lResult = ERROR_EXCEPTION_IN_SERVICE;

				lResult = RegOpenKeyExA(hkPrimKey, lpszSection, 0, KEY_READ, &hkReg);

				if( lResult != ERROR_SUCCESS )
				{
					bRc=0;
					break;
				}

				bRc = 1;

				lResult = RegCloseKey(hkReg);

			}while(0);
		}
		catch(...)
		{
			return bRc=0;
		}

		return bRc;
	}


	static tbool ChkEntry( HKEY hkPrimKey, LPCSTR lpszSection, LPCSTR lpszEntry )
	{
		BOOL fRet = FALSE;

		try
		{
			if( lpszSection )
			{
				HKEY hkReg;
				LONG lResult = ERROR_EXCEPTION_IN_SERVICE;

				lResult = RegOpenKeyExA(hkPrimKey, lpszSection, 0, KEY_READ, &hkReg);

				if( lResult == ERROR_SUCCESS )
				{
					try
					{
						DWORD dwType, dwCount;

						lResult = RegQueryValueExA(hkReg, lpszEntry, NULL, &dwType, NULL, &dwCount);

						if( lResult == ERROR_SUCCESS )
						{
							fRet = TRUE;
						}
					}
					catch(...)	{	;}
					
					lResult = RegCloseKey(hkReg);
				}
			}
		}
		catch(...)	{;	}

		return fRet?1:0;
	}


	static UINT ReadUInt( HKEY hkPrimKey, LPCSTR lpszSection, LPCSTR lpszEntry )
	{
		UINT uiRet = 0;

		try
		{
			if( lpszSection && lpszEntry )
			{
				HKEY hkReg;
				LONG lResult = ERROR_EXCEPTION_IN_SERVICE;
				BOOL fError = TRUE;

				lResult = RegOpenKeyExA(hkPrimKey, lpszSection, 0, KEY_READ, &hkReg);

				if( lResult == ERROR_SUCCESS )
				{
					try
					{
						DWORD dwValue=0;
						DWORD dwType;
						DWORD dwCount = sizeof(DWORD);

						lResult = RegQueryValueExA(hkReg, lpszEntry, NULL, &dwType, (LPBYTE)&dwValue, &dwCount);

						if( lResult == ERROR_SUCCESS )
						{
							uiRet = (UINT)dwValue;
							fError = FALSE;
						}
					}
					catch(...)	{;		}

					lResult = RegCloseKey(hkReg);
				}

			}
	
		}
		catch(...)	{	;	}

		return uiRet;
	}


	static tbool WriteInt( HKEY hkPrimKey, LPCSTR lpszSection, LPCSTR lpszEntry, int iValue )
	{
		BOOL fRet = FALSE;

		try
		{
			BOOL fError = TRUE;

			if( lpszSection && lpszEntry)
			{
				HKEY hkReg;
				LONG lResult = ERROR_EXCEPTION_IN_SERVICE;
				DWORD dw;

				// Open the key and create the key if not existing
				lResult = RegCreateKeyExA(hkPrimKey, lpszSection, 0, REG_NONE, REG_OPTION_VOLATILE, KEY_WRITE, NULL, &hkReg, &dw);

				if(lResult ==  ERROR_SUCCESS)
				{
					try
					{
						lResult = RegSetValueExA(hkReg, lpszEntry, 0, REG_DWORD, (LPBYTE)&iValue, sizeof(int));
	                    
						if (lResult == ERROR_SUCCESS) 
						{
							fError = FALSE;
							fRet = TRUE;    
						}

						lResult = RegCloseKey(hkReg);
					}
					catch(...)	{	;		}
				}
			}
		}
		catch(...)	{	;}

		return !!fRet;
	}



	static std::string ReadStr( HKEY hkPrimKey, LPCSTR lpszSection, LPCSTR lpszEntry )
	{
		SCake ckRet;

		try
		{

			BOOL fError = TRUE;

			if( lpszSection && lpszEntry)
			{
				HKEY hkReg;
				LONG lResult = ERROR_EXCEPTION_IN_SERVICE;

				lResult = RegOpenKeyExA(hkPrimKey, lpszSection, 0, KEY_READ, &hkReg);

				if( lResult == ERROR_SUCCESS )
				{
					try
					{
						DWORD dwType, dwCount;

						lResult = RegQueryValueExA(hkReg, lpszEntry, NULL, &dwType, NULL, &dwCount);

						if( lResult == ERROR_SUCCESS )
						{
							ckRet.redim(dwCount);
							lResult = RegQueryValueExA(hkReg, lpszEntry, NULL, &dwType, (LPBYTE)ckRet.buf(), &dwCount);

							if( lResult == ERROR_SUCCESS )
							{
								fError = FALSE;
							}
	
						}
					}
					catch(...)		{		;	}

					lResult = RegCloseKey(hkReg);
				}

			}
		
		}
		catch(...)	{	;	}

		return ckRet.buf()?ckRet.buf():"";
	}


	static tbool WriteStr( HKEY hkPrimKey, LPCSTR lpszSection, LPCSTR lpszEntry, std::string strValue )
	{
		BOOL fRet = FALSE;

		try
		{
			BOOL fError = TRUE;

			if( lpszSection && lpszEntry )
			{
				HKEY hkReg;
				LONG lResult = ERROR_EXCEPTION_IN_SERVICE;
				DWORD dw;

				// Open the key and create the key if not existing
				lResult = RegCreateKeyExA(hkPrimKey, lpszSection, 0, REG_NONE, REG_OPTION_VOLATILE, KEY_WRITE, NULL, &hkReg, &dw);

				if(lResult ==  ERROR_SUCCESS)
				{
					try
					{
						lResult = RegSetValueExA(hkReg, lpszEntry, 0, REG_SZ, (LPBYTE)strValue.c_str(), (int)strlen(strValue.c_str()) );
						if (lResult == ERROR_SUCCESS) 
						{
							fError = FALSE;
							fRet = TRUE;    
						}
						lResult = RegCloseKey(hkReg);
					}
					catch(...)	{;	}
				}
			}
		}
		catch(...)
		{
			;
		}

		return !!fRet;
	}


	
	static int EnumEntry( HKEY hkPrimKey, LPCSTR lpszSection, std::vector<std::string> & vecRtn )
	{
		enum { MAX_VALUE_NAME = 255, MAX_VALUE_DATA = 4096 	}; 
		tchar szName[MAX_VALUE_NAME];
		BYTE lpData[MAX_VALUE_DATA];
		DWORD cchName = MAX_VALUE_NAME; 
		DWORD ccbData = MAX_VALUE_DATA;
		int iIndex = 0;
		LONG lRet = ERROR_SUCCESS;

		HKEY hKey;

		lRet = RegOpenKeyExA(hkPrimKey, lpszSection, 0,KEY_READ, &hKey);
		if (lRet != ERROR_SUCCESS) return 0;

		for (iIndex=0; lRet != ERROR_NO_MORE_ITEMS; ++iIndex) 
		{ 
			cchName = MAX_VALUE_NAME; 
			ccbData = MAX_VALUE_DATA;
			szName[0] = '\0'; 
			lpData[0] = '\0';
			lRet = RegEnumValueA(hKey, iIndex,szName, &cchName ,NULL ,NULL,lpData, &ccbData); 
			if (lRet == ERROR_SUCCESS ) 
			{
				//if(*szName)
					vecRtn.push_back( std::string((tchar*)szName) );
			}
		}

		return iIndex;
	}


	static int EnumSection( HKEY hkPrimKey, LPCSTR lpszSection, std::vector<std::string> & vecRtn )
	{
		enum { MAX_VALUE_NAME = 255, MAX_VALUE_DATA = 4096 	}; 
		tchar szName[MAX_VALUE_NAME];
		tchar lpData[MAX_VALUE_DATA];
		DWORD cchName = MAX_VALUE_NAME; 
		DWORD ccbData = MAX_VALUE_DATA;
		int iIndex = 0;
		LONG lRet = ERROR_SUCCESS;

		HKEY hKey;

		lRet = RegOpenKeyExA(hkPrimKey, lpszSection, 0,KEY_READ, &hKey);
		if (lRet != ERROR_SUCCESS) return 0;

		for (iIndex=0; lRet != ERROR_NO_MORE_ITEMS; ++iIndex) 
		{ 
			cchName = MAX_VALUE_NAME; 
			ccbData = MAX_VALUE_DATA;
			szName[0] = '\0'; 
			lpData[0] = '\0';
			lRet = RegEnumKeyA( hKey, iIndex, lpData, MAX_VALUE_NAME);
			if (lRet == ERROR_SUCCESS ) 
			{
				//if(*lpData)
					vecRtn.push_back( std::string((tchar*)lpData) );
			}
		}

		return iIndex;
	}


}; //end class 




X011_NAMESPACE_END

#endif


/*
W series
thread class
*/

// 


#ifndef X011__H_w_wthrd_h
#define X011__H_w_wthrd_h



//if X011__WL_WIN_THRD_H_WIN_VER_SHOULD_BE_USED defined, use win ver multi thread , which might cause mem leak.
//X011__WL_WIN_THRD_H_WIN_VER_SHOULD_BE_USED will be defined when _MT not defined, which means the prj is not under multi thread compile env.
#ifndef _MT
#ifndef X011__WL_WIN_THRD_H_WIN_VER_SHOULD_BE_USED
#define X011__WL_WIN_THRD_H_WIN_VER_SHOULD_BE_USED
#endif
#endif



#ifdef  X011__WL_WIN_THRD_H_WIN_VER_SHOULD_BE_USED
//
#else
#include <process.h>
#endif



X011_NAMESPACE_BEGIN


/*
usage
should be
template< T >
class A : public  T 
{
}
*/

class WThrd
{

private:

	volatile HANDLE	 m_hThread;	//handle to thread knl 
	volatile int m_iAutoDel;
	volatile int m_iShouldBreak;
	volatile int m_iLive;

	volatile int m_iOpened;


#ifdef  X011__WL_WIN_THRD_H_WIN_VER_SHOULD_BE_USED
static DWORD WINAPI ThreadProc(LPVOID lpParam)
#else
static unsigned int WINAPI ThreadProc(void * lpParam)
#endif
	{
		WThrd *pThis=reinterpret_cast<WThrd*>(lpParam);

		try
		{
			//pThis->m_iLive = 1;

			pThis->tr_on_knl_run();

			//pThis->m_hThread=INVALID_HANDLE_VALUE;

			pThis->tr_shouldbrk();

			pThis->m_iLive = 0;

			if(pThis->m_iAutoDel)
			{
				try
				{
					delete pThis;
				}
				catch (...)
				{
					return (DWORD)0;
				}
			}
			return (DWORD)0;
		}
		catch(...)
		{
			try
			{
				delete pThis;
			}
			catch (...)
			{
				return (DWORD)0;
			}
			return (DWORD)0;
		}
		return (DWORD)0;
	}


private:

	WThrd & operator = (const WThrd & rhs)
	{
		return *this;
	}


	WThrd(const WThrd & rhs)
	{;}


public:

	WThrd()
	{
		m_hThread = INVALID_HANDLE_VALUE; 
		m_iAutoDel = 0;
		m_iShouldBreak = 0;
		m_iLive = 0;
		m_iOpened = 0;
	}


	virtual ~WThrd()
	{
		if( !m_iOpened ) return;

		try
		{
			tr_shouldbrk();

			//if( tr_wait( 4567 ) ) //如果是Heap型自删除的，则析构总是在本线程中执行，wait等于自己等自己，肯定要永远wait.如果是栈型变量，则析构是在主线程中执行的，与本类的run肯定不在同一线程中，所以看上去能行。
			//{
			//	//tr_Terminate();
			//	Beep(234,9);
			//	Beep(1294,9);
			//	Beep(234,9);
			//	return;
			//}

			if( !m_iAutoDel )
				tr_wait();

			tr_closehandl();
		}
		catch(...)
		{; }
	}


public:

	static std::string tr_GetCurrentThreadId()
	{
		char sz1[22];
		SClib::p_sprintf()( sz1, "%p", GetCurrentThreadId() );
		return sz1;
	}


	HANDLE tr_GetHnd() const
	{
		return m_hThread;
	}


	static void tr_sleep( int iSec , double dSec = 0.0 )	// 参数为整数秒和小于一秒的小数秒。 
	{
		if( iSec > 0 )
			Sleep( iSec * 1000 );

		if( dSec > 0.0 )
		{
			Sleep( static_cast<int>(dSec * 1000 * 1) );
		}
	}


	void tr_open()
	{
		m_hThread = INVALID_HANDLE_VALUE;

		m_iLive = 1;

#ifdef  X011__WL_WIN_THRD_H_WIN_VER_SHOULD_BE_USED
		//create a new thread and run it. WIN ver.
		DWORD i;
		m_hThread = ::CreateThread (
			NULL,			//缺省的安全性
			0,				//缺省的堆栈
			ThreadProc,		//类范围的线程进程
			reinterpret_cast<LPVOID>(this),	//向过程发送this指针
			0,				//没有特殊的创建标志 如果在dwCreationFlags中用了CREATE_SUSPENDED特性，那么线程并不马上执行，而是先挂起，等到调用ResumeThread后才开始启动线程，在这个过程中可以调用函数：　　BOOLSetThreadPriority(HANDLEhThread,intnPriority);　　来设置线程的优先权。　　当线程的函数返回后，线程自动中止。
			&i	);			// 返回线程ID
#else
		//C ver
		unsigned int i;
		m_hThread = (HANDLE) ::_beginthreadex(
			NULL,			//缺省的安全性
			0,				//缺省的堆栈
			ThreadProc,		//类范围的线程进程
			reinterpret_cast<LPVOID>(this),	//向过程发送this指针
			0,				//
			&i	);			// 返回线程ID

#endif

		if( !m_hThread )
		{
			m_iLive = 0;
		}

		if( tr_isRunning() )
		{
			m_iOpened = 1;
		}
	}



	void tr_openx() //if openx, don't wait this thread. because it will be deleted any time. don't call any func out side the obj in other thrd.
	{
		m_iAutoDel = 1;
		tr_open();
	}




	void tr_shouldbrk()
	{
		m_iShouldBreak = 1;
	}


	int tr_isShouldBrk() const
	{
		return m_iShouldBreak;
	}



	int tr_isRunning()
	{
		 return m_iLive;//由于无法自动地从不运行转化到运行状态，所以此函数主要用于探测是否已经从运行变为了不运行状态。
	}


	void tr_Terminate()
	{
		if( !m_iOpened ) return;

		try
		{
			if( m_hThread != INVALID_HANDLE_VALUE )
			{
				TerminateThread( m_hThread, 0 );
			}
		}
		catch (...)
		{	;
		}
	}

	void tr_closehandl()
	{
		tr_shouldbrk();

		if( m_hThread != INVALID_HANDLE_VALUE )
		{
			try
			{

#ifdef  X011__WL_WIN_THRD_H_WIN_VER_SHOULD_BE_USED
				::CloseHandle(m_hThread); 
#else
				//_endthread or _endthreadex is called automatically when the thread returns from the routine passed as a parameter to _beginthread or _beginthreadex.

				::CloseHandle(m_hThread);
#endif
			}
			catch (...)
			{
				;
			}
		}

		try
		{
			m_hThread = INVALID_HANDLE_VALUE; 
		}
		catch (...)
		{
			;
		}
	}



	//wait to thread end. 
	//if timeout then 1, means thread living.
	//if invalid thread then 0,
	//if wait to thread end then means thread dead. then 0.
	int tr_wait( DWORD dwMilliseconds=INFINITE )
	{
		if( !m_iOpened ) return 0;

		try
		{
			do//fake do
			{
				if( m_hThread == INVALID_HANDLE_VALUE )
					return 0;

				if( WAIT_TIMEOUT==::WaitForSingleObject(m_hThread,dwMilliseconds) )
					return 1;
				
				return 0;

			}while(0);

		}
		catch(...)
		{
			return 0;
		}
	}




	void tr_priority(int nPrio) 
	{
		/*
		THREAD_PRIORITY_ABOVE_NORMAL
		THREAD_PRIORITY_BELOW_NORMAL
		THREAD_PRIORITY_HIGHEST
		THREAD_PRIORITY_IDLE
		THREAD_PRIORITY_LOWEST
		THREAD_PRIORITY_NORMAL
		THREAD_PRIORITY_TIME_CRITICAL */
		::SetThreadPriority(m_hThread,nPrio);
	}




	void tr_priority_high() { 	tr_priority( THREAD_PRIORITY_ABOVE_NORMAL ); }


	void tr_priority_low()  { 	tr_priority( THREAD_PRIORITY_BELOW_NORMAL ); }


	void tr_priority_normal() { 	tr_priority( THREAD_PRIORITY_NORMAL ); }




	//
	void tr_suspend()
	{
		::SuspendThread(m_hThread);
	}



	//
	void tr_resume()
	{
		::ResumeThread(m_hThread);
	}




	virtual void tr_on_knl_run()
	{
		//SStrf::initrand( (int)((int)time(0) ^ (int)GetCurrentThreadId()) );
		SStrf::initrand( (int)((int)time(0) * (int)GetCurrentThreadId()) );

		while(1)
		{
			if( !tr_on_user_run() ) break;

			if( m_iShouldBreak ) break;
		}
	}
 


	virtual int tr_on_user_run() //return 0 will cause knl_run break;
	{
		return 0;
	}


	virtual tbool tr_OnMgrPrepare() // for WThrdMgr 
	{
		return 1;
	}

}; //end class 




///=================================================city



class WThrdCity
{
public:

		class WThrd2 : public WThrd 
		{

		friend class WThrdCity;

		private:
			WThrdCity * m_pWThrdCity;

			int tr_on_user_run() // 
			{
				return OnRun() ;
			}

		public:

			WThrd2()
			{
				m_pWThrdCity = NULL;
			}

			virtual ~WThrd2()
			{
				if( m_pWThrdCity ) m_pWThrdCity->RemoveEle(*this);
			}

			virtual int OnRun() 
			{
				return 0;
			}

		};

		
	typedef  WThrd2  WThrdEle;

	friend WThrdEle;


private:

	std::vector< WThrdEle * >  m_vecThrdLst;
	
	WCrsc m_crscThrdLst;

	WCrsc m_crscThrdOpenFunc;


	int AddEle( WThrdEle & t )
	{
		WCrsc aLock( this->m_crscThrdLst );
		WThrdEle * p = SStrf::AddressOf( t );

		m_vecThrdLst.push_back( p );
		return GetThrdAmount();
	}

	int RemoveEle( WThrdEle & t )
	{
		WCrsc aLock( this->m_crscThrdLst );
		WThrdEle * p = SStrf::AddressOf( t );

		std::vector< WThrdEle * >::iterator it = std::find( m_vecThrdLst.begin(), m_vecThrdLst.end(), p );
		if( it != m_vecThrdLst.end() )
		{
			m_vecThrdLst.erase( it );
		}
		return GetThrdAmount();
	}


public:

	int m_iLimit;

	tbool m_bWithOpenFailRetry;

public:

	WThrdCity( int iLimit = 123 )
	{
		m_iLimit = iLimit;
		m_bWithOpenFailRetry = 0;
	}


	int GetThrdAmount() const 
	{
		return (int)m_vecThrdLst.size();
	}
	
	

	void CleanStoppedThrd()
	{
		WCrsc aLock ( m_crscThrdOpenFunc );
		WCrsc a2Lock( m_crscThrdLst );

		std::vector< WThrdEle * >::iterator it;

		for( it = m_vecThrdLst.begin();
			 it != m_vecThrdLst.end();
			 ++it	)
		{
			if( (*it)->tr_isRunning() )
			{
				//
			}
			else
			{
				(*it)->m_pWThrdCity = NULL; //delete会调用析构函数清理Lst，所以先要禁掉。
				delete *it;
				it = m_vecThrdLst.erase( it );
			}
		}
		
	}



	tbool OpenThrd( WThrdEle & t )
	{
		WCrsc aLock( m_crscThrdOpenFunc );

		if( GetThrdAmount() >= m_iLimit )
		{
			//m_bWithOpenFailRetry here
			return 0;
		}

		AddEle( t );

		t.m_pWThrdCity = this;
		t.tr_open();

		return 1;
	}


	tbool OpenThrdHp( WThrdEle * t1 ) //open for when it is in heap
	{
		WCrsc aLock( m_crscThrdOpenFunc );

		if( !t1 ) return 0;

		if( GetThrdAmount() >= m_iLimit )
		{
			//m_bWithOpenFailRetry here
			return 0;
		}


		//WThrdEle & t(*t1); //don't use this line, for compatible of VC6

		AddEle( *t1 ); //此处只能形成非精确的数量控制。例如只差一个就到m_iLimit时，可能有2个线程都打算开新线程，并且都判断出尚未到m_iLimit，这样，就可能新增2个ele，从而略超控制数。

		( *t1 ).m_pWThrdCity = this;
		( *t1 ).tr_openx();

		return 1;
	}



	template< class ThrdEle_T > 
	tbool OpenThrdHp()
	{
		//WCrsc aLock( m_crscThrdOpenFunc );

		WThrdEle * p = new ThrdEle_T ;

		return OpenThrdHp(p); //不好用。如果返回0，则会丢失一个指针，无人释放。
	}


	//tbool OpenThrdWithRetry();
	//tbool OpenFreeThrd();
	//tbool OpenFreeThrdWithRetry();


};



typedef  WThrdCity::WThrd2  WThrdEle;





X011_NAMESPACE_END

#endif





/*
 
thread mgr, use with ele and env
*/

// 


#ifndef X011__H_W_WTHRDMGR_H
#define X011__H_W_WTHRDMGR_H


 


X011_NAMESPACE_BEGIN

 

//====================================================WThrdMgr

/*
用法是:
每一个工作原子是继承thrd,并需要env pointer。ele里只有算法，没有建立连接的过程，不要等待。but maybe recv and wait.
继承WThrdMgr，并指出工作原子。有env成员
重写OnMgrPrepare，为每个ele赋予env的指针.
也许重写tr_OnMgrPrepare()
这2个重写是真正block住的地方。
外界同步调用BirthEle，或启动本线程使其异步工作。
*/

template < class ThreadEle_T > 
class WThrdMgr : public WThrd 
{
private:


public:
	typedef		ThreadEle_T	 	ThrEle_t;
	volatile tbool  m_biMgrShouldBreak;
	int  m_iFailWaitTimesec; // if birth fail, wait this.
	tbool  m_biIsMultiEleType;

public:
	WThrdMgr()
	{
		m_biMgrShouldBreak = 0;
		m_iFailWaitTimesec = 3;
		m_biIsMultiEleType = 1;
	}

	virtual ~WThrdMgr()
	{;	}

	
	virtual tbool OnMgrPrepare( ThrEle_t & t ) // use 引用是表明到此处时必有对象存在 而不可能是NULL pointer   
	{
		return 1;
	}


	virtual int tr_on_user_run() 
	{
		BirthEle();
		return 0;
	}


	virtual ThrEle_t * MgrPrepare()   // new an ele, set its para, return the pointer. if fail, delete the pointer, return NULL. i'll not open or openx here.
	{
		ThrEle_t * p = new ThrEle_t;

		if( !p ) return NULL;

		if( !OnMgrPrepare(*p) ) /// 先准备环境 
		{
			delete p;
			return NULL;
		}

		if( ! p->tr_OnMgrPrepare() ) // 再准备个体  
		{
			delete p;
			return NULL;
		}
		
		return p;
	}


	//entrance:

	void BirthEle()
	{
		for( ; ; )
		{
			if( m_biMgrShouldBreak ) break;
			
			if( tr_isShouldBrk() ) break;
			
			ThrEle_t * p = MgrPrepare();
			if( p != NULL )
			{
				if( m_biIsMultiEleType )
				{
					p->tr_openx();
				}
				else  
				{
					p->tr_open();
					p->tr_wait();
					delete p;
				}
			}
			else
			{
				WThrd::tr_sleep( m_iFailWaitTimesec > 0 ? m_iFailWaitTimesec : 2 );
			}
		}
	}

};


 



X011_NAMESPACE_END

#endif



//应用案例: 
//
//class AEle : public wl::WThrd 
//{
//public:
//	wl::WTcpListener * m_pLsn;
//	wl::WTcpCells  m_tSvr;
//	
//
//	virtual int tr_on_user_run() 
//	{
//		wl::WTcpCells &tSvr(m_tSvr);
//
//		for(;;)
//		{
//			wl::SCake ck;
//			char s[222];
//			
//			tSvr.recv_len( ck, 1 );
//			if( ck.len() == 0 ) break;
//
//			printf(     "`%c` %d\r\n", *ck.buf(), *ck.buf() );
//			sprintf( s, "`%c` %d\r\n", *ck.buf(), *ck.buf() );
//			tSvr.send_str( s );
//
//			if( *ck.buf() == 27 ) break;
//		}
//
//		return 0;
//	}
//};
//
//
//class AMgr : public wl::WThrdMgr< AEle>
//{
//public:
//	wl::WTcpListener  m_Lsn;
//
//	AMgr()
//	{
//		m_Lsn.Listen( 7878 );
//		m_biIsMultiEleType = 0;
//	}
//
//	virtual ~AMgr() { ; }
//
//	virtual wl::tbool OnMgrPrepare( ThrEle_t & t ) // 
//	{
//		t.m_pLsn = &m_Lsn;
//		
//		if( !t.m_tSvr.Conn( m_Lsn ) ) return 0;
//		//t.m_tSvr.killer_up(6);
//
//		return 1;
//	}
//
//};
//
//
//
//
//void test_tcpserver()
//{
//	AMgr a;
//
//	a.BirthEle();
//}
//


/*
w_WSnd  sound
*/

// 


#ifndef X011__w_WSnd_H
#define X011__w_WSnd_H


#include <mmsystem.h>
#pragma comment(lib, "WINMM.LIB")



X011_NAMESPACE_BEGIN



class WSnd
{
public:
	
public:
	virtual ~WSnd() {;}

public:

	static void PlayWav( std::string strFile )
	{
		PlaySoundA( strFile.c_str(), NULL, SND_FILENAME | SND_SYNC ); 
	}
};






X011_NAMESPACE_END

#endif





/*
net
W series
tcp net env , init env
*/

// 

#ifndef X011__H_w_wtcp_a01env_net_env_init_h
#define X011__H_w_wtcp_a01env_net_env_init_h
 

 

X011_NAMESPACE_BEGIN




//////////////////////环境准备：Net打开和关闭

class WNet_lib_env_init 
{
private:

	int iOpenedByMe;

	static int Net_lib_open(void)
	{
		int ZEROIFSUCCESSFUL = 0;
		WSADATA		Wa;
		return ZEROIFSUCCESSFUL == WSAStartup( MAKEWORD(2,0), &Wa );
	}

	static int Net_lib_close(void)
	{
		return WSACleanup(); 
	}

public:

	WNet_lib_env_init()
	{
		SOCKET socTestSock;

		iOpenedByMe = 0;
		socTestSock = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
		if( socTestSock == INVALID_SOCKET )
		{
			if( Net_lib_open() ) iOpenedByMe = 1;
		}
		else
		{
			closesocket(socTestSock);
		}
	 }

	~WNet_lib_env_init()
	{
		if(iOpenedByMe)
		{
			Net_lib_close();
		}
	}
};


//prepare net lib env, use global obj.
static volatile  WNet_lib_env_init  wl_win_net_lib_env___23dmg3n67_obj;



X011_NAMESPACE_END

#endif



/*
W series
tcp cell base: WTcpDisConnable
*/

// 

#ifndef X011__H_w_WTcpDisConnable_h
#define X011__H_w_WTcpDisConnable_h


X011_NAMESPACE_BEGIN


class WTcpDisConnable : public IRice
{

private:

	WTcpDisConnable & operator = (const WTcpDisConnable & rhs)
	{
		return *this;
	}

	WTcpDisConnable(const WTcpDisConnable & rhs)
	{;}


public:
	class MyTimeKiller : public WThrd 
	{
	public:
		WTcpDisConnable * m_ph;
		int  m_i;
		int  m_iMaxSec;
		double  m_d;
		double  m_dMaxSec2;

		MyTimeKiller( WTcpDisConnable * ph, int iMaxSec, double dMaxSec2 = 0.0 )
		{
			m_ph = ph;
			m_i = 0;
			m_iMaxSec = iMaxSec;
			m_d = 0.0;
			m_dMaxSec2 = dMaxSec2;
		}

		virtual ~MyTimeKiller()
		{
			m_i = 0;
			tr_shouldbrk();

			//openx时,就是m_iAutoDel,此时不能析构时等自己.//tr_wait();
			//本例中是用open()打开线程，在基类中已经做好，会析构等自己。
			//一切取决于析构是不是本线程。如果是本线程同时负责析构，这时就会自己等自己而死锁.
		}


		virtual int tr_on_user_run()
		{
			if( m_i <= m_iMaxSec )
			{
				m_i++;
				if( m_i > m_iMaxSec )
				{
					//if(m_ph) m_ph->DisConn();
					//return 0;
				}
				else
				{
					WThrd::tr_sleep(1);
					return 1;
				}
			}

			if( m_d < m_dMaxSec2 ) // return as many as possible. we want many chances to Not to disconn and to end this thrd.
			{
				m_d += m_dMaxSec2;
				WThrd::tr_sleep( 0 , m_dMaxSec2 );
				return 1;
			}

			if( this->tr_isShouldBrk() ) return 0;

			if(m_ph) m_ph->DisConn();
			return 0;
		}
	};


	MyTimeKiller * m_pkiller;


	void killer_up( int iMaxSec ) //超时就会形成类似对方断线的效果。构造时即启动线程 
	{
		killer_dn() ;
		m_pkiller = new MyTimeKiller( this, iMaxSec );
		m_pkiller->tr_open();
	}


	void killer_dn() 
	{
		if( m_pkiller != NULL )
		{
			delete m_pkiller;
			m_pkiller = NULL;
		}
	}

public:

	WTcpDisConnable()
	{
		m_pkiller = NULL;
	}

	virtual ~WTcpDisConnable()
	{
		killer_dn() ;         
	}


 
	virtual void DisConn()  // CDUP\net\w_WMoonMan.h中重写本方法，但又调用了本方法，以便利用本方法中所定义的行为，而且虚函数OnDisConn()的调用又让控制权回到了 w_WMoonMan.h
	{
		/* IRice:: */ ClearL2Cache();

		OnDisConn();
	}


public:

	virtual void OnDisConn() { ; } // 让它有函数体而不是=0，为了防止在子类都析构了但本类还未析构时突然发生timekill，调用空函数之错。


}; //end class 




X011_NAMESPACE_END

#endif





/*
W series
tcp cell 
*/

// 

#ifndef X011__H_w_wtcp_cell_h
#define X011__H_w_wtcp_cell_h


X011_NAMESPACE_BEGIN


class WTcpCell : public WTcpDisConnable 
{
		
protected:

	SOCKET			m_socRemote;


private:

	WTcpCell & operator = (const WTcpCell & rhs)
	{
		return *this;
	}

	WTcpCell(const WTcpCell & rhs)
	{;}


public:

	WTcpCell()
	{
		m_socRemote = INVALID_SOCKET;
		 
	}

	virtual ~WTcpCell()
	{
		DisConn();
	}


public:

	SOCKET GetRemoteSoc () const
	{
		return m_socRemote;
	} 
	

	static std::string getselfname()
	{
		tchar ss[1024] = {0};
		gethostname(ss,1024);  //机器的主机名
		return ss;
	}


	static std::string getipbyname( std::string name )
	{
		hostent * host;
		std::vector<std::string> vecNameParts;

		wl::SStrvs::vsa_imp( name, std::string("."), 1, vecNameParts );
		if( vecNameParts.size()==4 &&
			SStrf::sisdec(vecNameParts[0].c_str()) &&
			SStrf::sisdec(vecNameParts[1].c_str()) &&
			SStrf::sisdec(vecNameParts[2].c_str()) &&
			SStrf::sisdec(vecNameParts[3].c_str())		)
			return name;

		if( name.size() == 0 )
			name = getselfname();

		host = gethostbyname(name.c_str());

		if(host==NULL)
			return "";

		if( host->h_addr_list[0] )
		{
			struct in_addr addr;
			memmove( &addr, host->h_addr_list[0], 4 );
			return inet_ntoa(addr);
		}

		return "";
	}


	static std::string getnamebyip( std::string strIP )
	{
		DWORD dwIPAddr;
		dwIPAddr = inet_addr(strIP.c_str());//strIP是IP地址,字符串，如192.168.0.1。
		if(dwIPAddr == INADDR_NONE)
		{
			return "";//IP地址不合法
		}
		else
		{
			hostent * p=gethostbyaddr( (const char *)&dwIPAddr, 4, PF_INET ); //这里要强制转换，很多初学者常常卡在这里了。
			if(!p)
			{
				return "";//找不到相应的名字。
			}
			else
			{
				return p->h_name;//找到名字了，字符串。
			}
		}
	}



public:

	virtual void OnDisConn()
	{
		if( m_socRemote == INVALID_SOCKET ) return;

		try
		{	
			shutdown( m_socRemote, 2 ); 
			closesocket(m_socRemote); 
			m_socRemote = INVALID_SOCKET ;
		}
		catch(...) 
		{
			m_socRemote = INVALID_SOCKET;
		}
	}


public:

	virtual int on_get_defaultrecv_buf_len() //return the   len
	{
		return 255;
	}

	virtual int on_sys_recv( SCake & ckDataBuf ) //return the recv len
	{
		int iDefaultBufLen = on_get_defaultrecv_buf_len();
		ckDataBuf.redim( iDefaultBufLen );

		int i;
		SOCKET s = m_socRemote;

		if(s==INVALID_SOCKET)
		{
			return 0;
		}

		i = (int)::recv(s, ckDataBuf.buf(), (int)ckDataBuf.len(), 0);
		if(i==SOCKET_ERROR||i==0)
		{
			return i = 0;
		}

		ckDataBuf.cut( iDefaultBufLen-i );

		return i;
	}


	virtual int on_sys_send( const SCake & ckDataBuf ) //return the successfully sent len
	{
		int i;
		SOCKET s = m_socRemote;
		if(s==INVALID_SOCKET) return 0; //      if(len>66) len=66;

		i = (int)::send(s, ckDataBuf, (int)ckDataBuf.len(), 0);
		//i = (int)::send( s, ckDataBuf, (int)ckDataBuf.len() > 66 ? 66 : (int)ckDataBuf.len(), 0 );

		if(i==SOCKET_ERROR)
			i = 0;
		return i;
	}


}; //end class 




X011_NAMESPACE_END

#endif





/*
W series
tcp cellc
*/

// 

#ifndef X011__H_w_wtcp_cellc_h
#define X011__H_w_wtcp_cellc_h


X011_NAMESPACE_BEGIN


class WTcpCellc : public WTcpCell
{

private:

	WTcpCellc & operator = (const WTcpCellc & rhs)
	{
		return *this;
	}

	WTcpCellc(const WTcpCellc & rhs)
	{;}


public:


	WTcpCellc()
	{
	}



	virtual ~WTcpCellc()
	{
	}




	tbool Conn( std::string name, u_short port )
	{
		struct	sockaddr_in		saddr ;

		DisConn();

		m_socRemote = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );

		if( m_socRemote == INVALID_SOCKET )
		{
			return 0;
		}

		//we should zero mem here.
		SStrf::smemset( (void*)&saddr, 0, sizeof(saddr) );
	 
		saddr.sin_family = AF_INET; 
			//saddr.sin_addr.S_un.S_addr = inet_addr( getipbyname(name).c_str() );
			saddr.sin_addr.s_addr = inet_addr( getipbyname(name).c_str() );
		saddr.sin_port = htons( (u_short)port );

		if(SOCKET_ERROR == ::connect( m_socRemote, (struct sockaddr *)&saddr, sizeof(saddr) )  )
		{
			return 0;
		}

		return 1;
	}




	tbool Conn( std::string name, std::string port )
	{
		return this->Conn( name, static_cast<u_short>(SStrf::satol(port.c_str()) ) );
	}




	tbool Conn( std::string nameOraddr ) //like  192.168.1.29:2345  or  name.com:456
	{
		try
		{
			std::vector<std::string> vecNameParts;
			SStrvs::vsa_imp( nameOraddr, std::string(":"), 1, vecNameParts );
			vecNameParts.push_back( std::string("") );
			vecNameParts.push_back( std::string("") );
			return this->Conn( vecNameParts[0], vecNameParts[1] );
		}
		catch(...)
		{
			//printf("bad when %s\n", nameOraddr.c_str() );
			return 0;
		}
	}


}; //end class 




X011_NAMESPACE_END

#endif


/*
W series
tcp cell Listener
*/

// 

#ifndef X011__H_w_WTcpListener_h
#define X011__H_w_WTcpListener_h


X011_NAMESPACE_BEGIN


class WTcpListener
{

private:

	SOCKET	m_socLocalListener;
	//std::string m_strRemoteIPAddress;


private:

	WTcpListener & operator = (const WTcpListener & rhs)
	{
		return *this;
	}

	WTcpListener(const WTcpListener & rhs)
	{;}


public:

	u_short		m_port;

	u_long		m_u_in_addr;


	WTcpListener( )
	{
		m_socLocalListener = INVALID_SOCKET;
		//m_strRemoteIPAddress="";
		m_port = 0;
	}

	virtual ~WTcpListener( )
	{
		this->StopListen();
	}


	//operator const std::string & ( ) const
	//{
	//	return m_strRemoteIPAddress;
	//}
    


	tbool Listen( u_short port,  u_long a_in_addrip = INADDR_ANY, int listener_num = 4 )
	{
		struct	sockaddr_in	 saddr;

		m_port = port;
		m_u_in_addr = a_in_addrip;

		if ( 0 == port )
		{
			//return 0;		port=0 means any available port, so, it is right.
		}
		
		m_socLocalListener = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );

		if( m_socLocalListener == INVALID_SOCKET )
		{
			return 0;
		}

		//we should zero mem here.
		SStrf::smemset( (void*)&saddr, 0, sizeof(saddr) );

		saddr.sin_family = AF_INET; 
		saddr.sin_port = htons( (u_short)port );
		saddr.sin_addr.s_addr = a_in_addrip;	//INADDR_LOOPBACK;//inet_addr(cf_getipbyname("",ss)); // ;//INADDR_ANY; //saddr.sin_addr.s_addr = inet_addr( "127.0.0.1" ); // ;//INADDR_ANY; 
		
		if( SOCKET_ERROR == bind( m_socLocalListener, (struct sockaddr *)&saddr, sizeof(saddr) ))
		{
			this->StopListen();
			return 0;
		}

		return 0 == ::listen( m_socLocalListener, listener_num )?1:0;
	}


	tbool Listen( u_short uport, const tchar * sz_addrip ) //bind an appointed ip
	{
		if( sz_addrip && *sz_addrip )
		{
			return this->Listen( uport, inet_addr( sz_addrip ) ) ;
		}
		
		return this->Listen( uport );
	}


	tbool Listen( std::string strport, const tchar * sz_addrip )
	{
		return this->Listen( (u_short)SStrf::satol(strport) , sz_addrip );
	}



	tbool Listen( std::string straddr ) //like  192.168.1.29:2345  or  name.com:456
	{
		try
		{
			std::vector<std::string> vecNameParts;
			SStrvs::vsa_imp( straddr, std::string(":"), 1, vecNameParts );
			if( vecNameParts.size() == 1 )
			{
				vecNameParts.insert( vecNameParts.begin(), std::string("") );
			}

			vecNameParts.push_back( std::string("") );
			vecNameParts.push_back( std::string("") );
			return Listen( vecNameParts[1], vecNameParts[0].c_str() );
		}
		catch(...)
		{
			return 0;
		}
	}



	void StopListen(void)
	{
		if( m_socLocalListener != INVALID_SOCKET )
		{
			closesocket( m_socLocalListener );
			m_socLocalListener = INVALID_SOCKET;
		}
	}


	tbool AcceptNewSvr( SOCKET & socNewSvr, std::string & strRtnRemoteIP )
	{
		struct	sockaddr_in	 from;
		int nSize;

		if( m_socLocalListener == INVALID_SOCKET )
		{
			return 0;
		}

		nSize= sizeof(from);
		socNewSvr = ::accept( m_socLocalListener, (struct sockaddr *)&from, &nSize ); //socNewSvr now have a new value
		if( socNewSvr == INVALID_SOCKET )
		{
			strRtnRemoteIP = "";
			return 0;
		}
		else
		{
			strRtnRemoteIP = inet_ntoa( from.sin_addr ) ; //此时对方的port也是有意义的,不一定与本机的bind的port相同
			return 1;
		}
	}


}; //end class 




X011_NAMESPACE_END

#endif




/*
W series
tcp cells
*/

// 

#ifndef X011__H_w_wtcp_cells_h
#define X011__H_w_wtcp_cells_h


X011_NAMESPACE_BEGIN


class WTcpCells : public WTcpCell
{
	
public:

	std::string m_strRemoteIPAddress;


private:

	WTcpCells & operator = (const WTcpCells & rhs)
	{
		return *this;
	}

	WTcpCells(const WTcpCells & rhs)
	{;}


public:

	WTcpCells()
	{
		m_strRemoteIPAddress="";
	}


	virtual ~WTcpCells()
	{	m_strRemoteIPAddress="";
	}



	operator const std::string & () const
	{
		return m_strRemoteIPAddress;
	}



	std::string GetRemoteIPAddress() const
	{
		return m_strRemoteIPAddress;
	}



	tbool Conn( WTcpListener & aListener)
	{
		int iRc;

		iRc = aListener.AcceptNewSvr( m_socRemote , m_strRemoteIPAddress );

		if(!iRc) return 0;

		//m_strRemoteIPAddress = aListener; //本行会有多线程问题，改为用以上AcceptNewSvr带回IP.
		return 1;
	}


	tbool Conn( WTcpListener * pListener)
	{
		if(!pListener)
			return 0;

		return this->Conn(*pListener);
	}


}; //end class 




X011_NAMESPACE_END


#endif






/*
W series
tcp Http commands
*/

// 

#ifndef X011__H_w_WTcpHttp_h
#define X011__H_w_WTcpHttp_h


X011_NAMESPACE_BEGIN


class WTcpHttp : public WTcpCellc
{
public: 

	typedef std::map< std::string, std::string >	MAP_HTTPHEADPARA;
	typedef MAP_HTTPHEADPARA::iterator				MAP_HTTPHEADPARA_IT;
	typedef MAP_HTTPHEADPARA::value_type			MAP_HTTPHEADPARA_VT;


private: 

	MAP_HTTPHEADPARA m_mapUrlHeadPara;

	MAP_HTTPHEADPARA m_mapSvrRtnHeadPara; 


private:

	WTcpHttp & operator = (const WTcpHttp & rhs)
	{
		return *this;
	}

	WTcpHttp(const WTcpHttp & rhs)
	{;}


public:

	std::string m_strProxyAddr;


public:

	WTcpHttp()
	{
		m_strProxyAddr = "";
		ClearUrlHeadPara();
	}


	WTcpHttp( int iMaxSec ) // 本httptcp应为一次性使用法。
	{
		killer_up( iMaxSec );

		m_strProxyAddr = "";
		ClearUrlHeadPara();
	}


	virtual ~WTcpHttp()
	{
		m_strProxyAddr = "";
	}




	static std::string GetRegIEProxyAddr()
	{
		std::string strProxyAddr("");
		int iProxyEnable;
		SCake ckProxySetting;

		do//fakedo
		{
			iProxyEnable = WReg32::ReadUInt( HKEY_CURRENT_USER, 
											"Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings", 
											"ProxyEnable"	);
			if( !iProxyEnable )
			{
				break;
			}

			strProxyAddr = WReg32::ReadStr( HKEY_CURRENT_USER, 
											"Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings", 
											"ProxyServer"	);
			
			ckProxySetting.lets( strProxyAddr );

			if( !SStrf::sstr( ckProxySetting, '=' ) ) //there is no '=', means addr is pure ip:port grammar. return it.
			{
				break;
			}
			
			std::map<std::string,std::string> mapProxyPrpt;
			SStrf::slcase(ckProxySetting);
			SStrvs::vsa2v_prpt( std::string(ckProxySetting), std::string(";"), std::string("="), mapProxyPrpt );

			strProxyAddr = mapProxyPrpt[std::string("http")];

		}while(0);

		return strProxyAddr;
	}


	const std::string & SetProxyAddr( std::string strPxyAddr )
	{
		return m_strProxyAddr = strPxyAddr;
	}


	const std::string & SetProxyAddrAuto()
	{
		return SetProxyAddr( GetRegIEProxyAddr() );
	}



	void ClearUrlHeadPara()
	{
		m_mapUrlHeadPara.clear();
	}


	void AddUrlHeadPara( std::string strName, std::string strValue )
	{
		m_mapUrlHeadPara.insert( MAP_HTTPHEADPARA_VT( strName, strValue ) ); 
	}



	void ClearSvrRtnHeadPara()
	{
		m_mapSvrRtnHeadPara.clear();
	}


	static void MakeHeadParaMap( const std::string & strHeadPart , MAP_HTTPHEADPARA & hm )
	{
		hm.clear();

		std::vector<std::string> vecTmpTR, vecTmpTD;
		std::vector<std::string>::iterator itTR;
		SStrvs::vsa_imp( strHeadPart, std::string("\r\n"), 1, vecTmpTR );
		for( itTR = vecTmpTR.begin(); itTR!=vecTmpTR.end(); ++itTR )
		{
			SCake ck;
			ck.lets( itTR->c_str() );
			tchar *p = SStrf::sstr( ck.buf(), ":" );
			if( p )
			{
				*p = 0;
				p++;
				SStrf::strim( p );
			}
			else
			{
				//p = "";
				p=NULL;
			}

			SStrf::strim( ck.buf() );
			vecTmpTD.push_back( ck.buf() );
			vecTmpTD.push_back( p ? p : "" );
			
			hm.insert( MAP_HTTPHEADPARA_VT( vecTmpTD[0], vecTmpTD[1] ) );
			vecTmpTD.clear();
		}
 
	}


	void ImportSvrRtnHeadPara( const std::string & strHeadPart )
	{
		//ClearSvrRtnHeadPara();

		//SStrvs::vsa2v_prpt( strHeadPart, std::string("\r\n"), std::string(":"), m_mapSvrRtnHeadPara );

		MakeHeadParaMap( strHeadPart, m_mapSvrRtnHeadPara );  
	}


	void ImportSvrRtnHeadPara( SCake ckHeadPart )
	{
		ImportSvrRtnHeadPara( std::string(ckHeadPart.mk_sz() ) );
	}

	MAP_HTTPHEADPARA GetSvrRtnHeadPara() const
	{
		return m_mapSvrRtnHeadPara;
	}

	std::string GetSvrRtnHeadParaVal( const std::string & strParaName )  
	{
		return m_mapSvrRtnHeadPara[strParaName];
	}



	static void GetLine1ParaFromHead( const std::string & strHttpHead, 
										std::string & rstrCmdLine1, 
										std::string & rstrCmdVerb, 
										std::string & rstrProtocolName, 
										std::string & rstrAddr		)
	{
		wl::SCake ck;
		std::string strSep;
		std::string strAddrTmp;

		std::string strCmdLine1, strCmdVerb,strProtocolName, strAddr;

		ck.lets( strHttpHead );

		strCmdLine1 = SStrvs::vsa_get( strHttpHead, std::string("\n"), 1, 0 );
		wl::SStrf::strim( strCmdLine1 );

		strCmdVerb = SStrvs::vsa_get( strCmdLine1, std::string(" "), 1, 0 );

		//第2个空格为结束

		ck.lets( strCmdLine1 );
		for( char *p = wl::SStrf::splast( ck.buf() ); p != ck.buf(); p-- )
		{
			if( *p == ' ' )
			{
				*p = 0;
				break;
			}
		}

		strAddrTmp = ck.buf();

		//如果有 / 却没有 "://",就补一个 "://"

		if( strAddrTmp.find( "/" ) != std::string::npos && strAddrTmp.find( "://" ) == std::string::npos )
		{
			if( strAddrTmp.find( " /" ) != std::string::npos )
			{
				MAP_HTTPHEADPARA m;
				std::string s2(strHttpHead);
				SStrf::slcase( s2 );
				MakeHeadParaMap( s2, m );  
				SStrf::sreplstr( strAddrTmp, " ", " http://" + m["host"] );
			}
			else
			{
				SStrf::sreplstr( strAddrTmp, " ", " http://" );
			}
		}


		//get strProtocolName
		strProtocolName = SStrvs::vsa_get( strAddrTmp, std::string("://"), 1, 0 );
		ck.lets( strProtocolName );
		SStrf::srev( ck.buf() );
		SStrf::sreplch( ck.buf(), ' ', 0 );
		strProtocolName = SStrf::srev( ck.buf() );



		//如果有'/'分隔符就是/，否则分隔符为空格。取串数组下标1 。
		
		if( strAddrTmp.find( "/" ) != std::string::npos )
		{
			strSep = "/"; 
		}
		else
		{
			strSep = " ";
		}
		strAddr = wl::SStrvs::vsa_get( strAddrTmp, strSep, 1, 1 );
		

		//如果没有'：'，则补上":80" 或 443
		if(1)
		{
			std::string str80("80");
			std::string s1(strProtocolName);

			SStrf::slcase( s1 );
			//if( s1 == "ssl" || s1== "https" ) str80 = "443"; 

			if( strAddr.find( ":" ) == std::string::npos ) strAddr += ":" + str80;

			if( *SStrf::splast( strAddr.c_str() ) == ':' ) strAddr += str80;
		}

		//return
		rstrCmdLine1 = strCmdLine1; 
		rstrCmdVerb = strCmdVerb;
		rstrProtocolName = strProtocolName;
		rstrAddr = strAddr;
	}



	static std::string GetHostAddrFromUrl( std::string  strUrl )
	{
		std::string strConnWho;

		//strConnWho = SStrvs::vsa_get( strUrl, std::string("/"), 1, 1 );
		//if( strConnWho == "" ) strConnWho = strUrl;
		//if( !SStrf::sstr(strConnWho.c_str(), ':') ) strConnWho += ":80";

		SStrf::strim( strUrl );
		strUrl = "a " + strUrl + " a"; //form a head format.

		std::string s1;

		GetLine1ParaFromHead( strUrl, s1, s1, s1, strConnWho );

		return strConnWho;
	}



	
	static std::string GetResPathnameFromUrl( std::string  strUrl )
	{
		std::string::size_type ssti;
		std::string s;

		//1. get host addr, without port
		s = GetHostAddrFromUrl( strUrl );
		s = wl::SStrvs::vsa_get( std::string(s), std::string(":"), 1, 0 );


		//2. find host addr in url
		ssti = strUrl.find( s );
		if(ssti==std::string::npos) return "";
		ssti += s.size() /2;


		//3. find 1st '/' after the addr
		ssti = strUrl.find( '/', ssti );
		if(ssti==std::string::npos) return "/";	 //if the result is "", make it "/"


		//4. 
		return strUrl.c_str() + ssti;
	}




	tbool ConnUrl( std::string strUrl )
	{
		tbool iRc;
		std::string strConnWho;

		do //fake do
		{
			iRc = 0;

			strConnWho = GetHostAddrFromUrl( strUrl );

			if( m_strProxyAddr.length() ) strConnWho = m_strProxyAddr;

			if( !Conn( strConnWho ) ) break;

			iRc = 1; 

		}while(0);

		return iRc;
	}



	tbool SendHttpGet( std::string strUrl, std::string strHttpVer = "HTTP/1.0" , tbool bSmartSendResPathname = 1 , tbool bCleanUrlPara = 1 )
	{
		std::string strSnd;
		tbool iRc;
		std::string strConnWho;

		if(bSmartSendResPathname) // 无代理时，切出路径和资源名，去掉主机名，以备下一步去组合成GET命令。否则就是直接拿URL去GET，baidu适合前者，ikaka适合后者，所以要具体对待。
		{
			//根据是否有proxy addr，变更一下

			if( this->m_strProxyAddr != "" ) //有代理，代理会处理resource pathname
			{
				//don't change strUrl.
			}
			else
			{
				//only resource pathname should remained.
				strUrl = GetResPathnameFromUrl( strUrl );
			}
		}

		strSnd =  "GET " + strUrl + " " + strHttpVer + "\r\n";

		AddUrlHeadPara( "Accept-language", "zh-cn" );
		//"Host:ip138\r\n"
		AddUrlHeadPara( "User-Agent", "Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1; .NET CLR 1.1.4322)" ); 
		//"User-agent: IE\n"
		AddUrlHeadPara( "Pragma", "no-cache" );
		AddUrlHeadPara( "cache_control", "no-cache" );
		AddUrlHeadPara( "Cache-Control", "no-cache" );
		//"Connection: Keep-Alive\n"
		// Connection: Keep-Alive
		//"Proxy-Connection: Keep-Alive\r\n";
		// Proxy-Connection: Keep-Alive
		//Proxy-Connection: Keep-Alive	Connection: Keep-Alive   "Connection: close\n"			"Proxy-Connection: close\r\n";
		//Content-Length: 437

		
		for( MAP_HTTPHEADPARA_IT it = m_mapUrlHeadPara.begin(); it != m_mapUrlHeadPara.end(); ++it )
		{
			strSnd += it->first;
			strSnd += ": ";
			strSnd += it->second;
			strSnd += "\r\n";
		}

		if(bCleanUrlPara)
		{
			ClearUrlHeadPara();
		}

		strSnd += "\r\n";


		do//fakedo
		{
			iRc = 0;

			iRc = send_str( strSnd ); 

		}while(0);

		return iRc;
	}


	SCake SimpleHttpGetFile( std::string strUrl )
	{
		WTcpHttp & h(*this);
		std::string & s(strUrl);
		SCake ckTmp;

		//s = "http://proxypac.infra.thales/autoconf/proxy-tsss.pac";
		//s = "http://61.152.200.137/soft/20090329-003-x86.exe";

		//h.SetProxyAddrAuto();
		h.ConnUrl( s );
		AddUrlHeadPara( "Connection", "close" );
		h.SendHttpGet( s, "HTTP/1.0" );

		h.recv_ln( ckTmp, "\r\n\r\n" );

		h.ImportSvrRtnHeadPara( ckTmp );
		int i;
		i = atol( h.GetSvrRtnHeadParaVal( "Content-Length" ).c_str() );

		if( i <= 0 ) return SCake();

		h.recv_len( ckTmp , i );
		h.DisConn();

		return ckTmp;
	}



}; //end class 




X011_NAMESPACE_END

#endif




/*
W series
com eli protocol 
*/

// 

#ifndef X011__H_w_WComeliProtocol_h
#define X011__H_w_WComeliProtocol_h


X011_NAMESPACE_BEGIN


class WComeliProtocol : public WTcpDisConnable 
{
		
public:

	tbool  m_biComportOpened;
	tbool  m_biShouldDisConn;


private:

	WComeliProtocol & operator = (const WComeliProtocol & rhs) 	{ 	return *this; }
	WComeliProtocol(const WComeliProtocol & rhs) {;}


public:

	WComeliProtocol()
	{
		m_biComportOpened = 0;
		m_biShouldDisConn = 0;
		 
	}

	virtual ~WComeliProtocol()
	{
		m_biComportOpened = 0;
		m_biShouldDisConn = 0;
	}


public:
 
	/////////////////////////////for com use, cake util

	typedef tuint8 (* PfChkSum_t) ( tuint8 a, tuint8 b );

	static tuint8 comesc_xor ( tuint8 a, tuint8 b ) { return a ^ b; };
	static tuint8 comesc_add ( tuint8 a, tuint8 b ) { return a + b; };


	static SCake & comesc_en( SCake & ckDataInOut, tuint8 a1, tuint8 a2, tuint8 a3 , PfChkSum_t pf = comesc_add, SCake * pdata2 = NULL ) // 
	{
		//ckDataInOut len ==0 也没关系

		tuint8  ucChkSum(0);
		std::vector<tuint8> v1;
		tuint8 c;

		//add a1
		v1.push_back(a1);

		//add data2
		for( tsize i2 = 0; pdata2 && i2 < pdata2->len(); i2++ )
		{
			c = *(tuint8*)(pdata2->buf()+i2);
			if( c == a1 || c == a2 || c == a3 ) v1.push_back(a2);
			v1.push_back( c );
		}

		//add len
		c = static_cast<tuint8>( ckDataInOut.len() );
		if( c == a1 || c == a2 || c == a3 ) v1.push_back(a2);
		v1.push_back( c );

		//calc data
		for( tsize i = 0; i < ckDataInOut.len(); i++ )
		{
			c = *(tuint8*)(ckDataInOut.buf()+i);
			if( c == a1 || c == a2 || c == a3 ) v1.push_back(a2);
			v1.push_back(c);
		}

		//calc chk sum
		for( tsize i = 0; i < ckDataInOut.len(); i++ )
		{
			ucChkSum = (*pf)( ucChkSum, *(tuint8*)(ckDataInOut.buf()+i) );
		}
		c = ucChkSum;
		if( c == a1 || c == a2 || c == a3 ) v1.push_back(a2);
		v1.push_back(c);

		//add a3
		v1.push_back(a3);

		//到这里v1必然有内容
		ckDataInOut.let( (tchar*)&(v1[0]), (tsize)v1.size() );
 
		return ckDataInOut;
	}


	static int comesc_de( SCake & ckDataInOut, tuint8 a1, tuint8 a2, tuint8 a3 , PfChkSum_t pf = NULL , SCake * pdata2 = NULL ) // return len indicated at beginning of data
	{
		if( ckDataInOut.len() != 0 )
		{
			std::vector<tuint8> v1;
			int flag = 1;

			//.......a1......a2...data...a2....data.....data.....a3......
			//    1       2      3     2     3       2        2      4

			for( tsize i = 0; i < ckDataInOut.len(); i++ )
			{
				tuint8 c = *(tuint8*)(ckDataInOut.buf()+i);
				tuint8 c2;
				
				
				if( flag == 1 )
				{
					if( c == a1 && i == 0 )
					{
						flag = 2;
						continue;
					} 

					if( c == a1 && i != 0 )
					{
						tuint8 c0 = *(tuint8*)(ckDataInOut.buf()+i-1); // c0就是 c之前一个
						if( c == a1 && c0 != a2 ) // 在任意的前导垃圾中找到了起始符a1
						{
							flag = 2;
							continue;
						}
					}

					continue;
				}


				//here we meet the first ch after the a1
				//c
				if( i+1 < ckDataInOut.len() )
				{
					//取2个字节
					c2 = *(tuint8*)(ckDataInOut.buf()+i+1);

					if( c == a2 )
					{
						v1.push_back( c2 );
						i++;
					}
					else
					{
						v1.push_back( c );
					}
				}
				else
				{
					//已经是最后一个字节了.
					if( c != a2 && c != a3 ) v1.push_back( c );
				}
			}//end for

			//到这里v1还不一定有内容
			if(v1.size()<2)
			{
				ckDataInOut.redim(0);
				return 0;
			}

			if( pdata2 != NULL && pdata2->len() != 0 )
			{
				if( v1.size() - pdata2->len() < 2 )
				{
					ckDataInOut.redim(0);
					return 0;
				}

				for( tsize i2 = 0; i2 < pdata2->len(); i2++ )
				{
					tuint8 c = v1[0];
					*(tuint8*)(pdata2->buf()+i2) = c;
					v1.erase( v1.begin() );
				}
			}

			//here we got LEN,DATA,BCC
			if( v1.size() == 2 )
			{
				ckDataInOut.redim(0);
				return v1[0];
			}

			//here we got LEN,DATA,BCC and DATA>=1
			{
				tuint8 ilen = v1[0];
				tuint8 iChkSum = v1[v1.size()-1];
				v1.erase( v1.begin() );
				v1.erase( v1.end() - 1 );
				
				ckDataInOut.let( (tchar*)&(v1[0]), (tsize)v1.size() );

				//calc chk sum
				if( pf )
				{
					tuint8  ucChkSum(0);

					for( tsize i = 0; i < ckDataInOut.len(); i++ )
					{
						ucChkSum = (*pf)( ucChkSum, *(tuint8*)(ckDataInOut.buf()+i) );
					}
					if( iChkSum != ucChkSum )
					{
						ckDataInOut.redim(0);
						return 0;
					}
				}

				if( ilen != ckDataInOut.len() )
				{
					ckDataInOut.redim(0);
					return 0;
				}

				return ilen;
			}
		}

		return 0;
	}



	/////////////////////////////for com use, recv


	tbool recv_comesc( SCake & ckData , tuint8 a2, tuint8 a3 ) 
	{
		SCake ckTmp;
		tsize i = 1;

		do
		{
			if( m_ckDataL2CacheBuf.len() >= 2 )
				for( ; i < m_ckDataL2CacheBuf.len(); i++ )
				{
					tchar c = *(m_ckDataL2CacheBuf.buf()+i);
					tchar c1 = *(m_ckDataL2CacheBuf.buf()+i-1);

					if( c1 != a2 && c == a3 )
					{
						goto L_RECV_ESC; //now i pointing to a3, the tail.
					}
				}

			if( !sys_recv( ckTmp ) ) break;

			m_ckDataL2CacheBuf.append(ckTmp);

		}while(ckTmp.len()>0);

L_RECV_ESC:
		ckData.redim(i+1);
		m_ckDataL2CacheBuf.dump( ckData );
		//ckData.esc_de(a1,a2,a3);
		return ckData.len()+m_ckDataL2CacheBuf.len()==0?0:1;
	}



public:
	
	virtual void OnDisConn()
	{
		m_biShouldDisConn = 1;
	}


	virtual int on_get_defaultrecv_buf_len() //return the buf len. we just want 1 byte.
	{
		return 1;
	}


}; //end class 




X011_NAMESPACE_END

#endif





/*
W series
com eli cell
*/

// 

#ifndef X011__H_w_WComeliCell_h
#define X011__H_w_WComeliCell_h


X011_NAMESPACE_BEGIN


class WComeliCell : public WComeliProtocol 
{
		
protected:

	HANDLE  m_hComport;


private:

	WComeliCell & operator = (const WComeliCell & rhs) 	{ 	return *this; }
	WComeliCell(const WComeliCell & rhs) {;}


public:

	WComeliCell()
	{
		 
	}

	virtual ~WComeliCell()
	{
		if( m_biComportOpened )
		{
			CloseHandle(m_hComport); //关闭COM 
			m_biComportOpened = 0;
		}
	}


public:


	tbool Conn( std::string strname ) // "com=1;start=1;stop=1;speed=9600;parity=O/E/N;datalen=8;timeoutsec=0.150;"
	{
		DisConn();
		
		WNava nv;

		nv.impconf( strname, ";", "=" );

		if( nv.get("com").empty() ) return 0;

		m_hComport = CreateFileA( ("COM"+nv.get("com")).c_str() , GENERIC_READ | GENERIC_WRITE, 
																	0,    // exclusive access 
																	NULL, // no security attributes 
																	OPEN_EXISTING,
																	0,
																	NULL
																	);
		if( m_hComport == NULL || m_hComport == INVALID_HANDLE_VALUE )
		{
			// "串口打开失败";
			return 0;
		}

		m_biComportOpened = 1;

		DCB PortDCB; 
		PortDCB.DCBlength = sizeof(DCB); 
		// 默认串口参数
		GetCommState(m_hComport, &PortDCB);

		PortDCB.fDtrControl = DTR_CONTROL_DISABLE;
		PortDCB.fRtsControl = RTS_CONTROL_DISABLE;

		PortDCB.BaudRate = (int)SStrf::satol( nv.get("speed") );
		PortDCB.ByteSize = (tuint8)SStrf::satol( nv.get("datalen") );
		if( nv.get("parity") == "O" ) PortDCB.Parity = ODDPARITY; 
		else if( nv.get("parity") == "E" ) PortDCB.Parity = EVENPARITY; 
		else if( nv.get("parity") == "N" ) PortDCB.Parity = NOPARITY;
		else
		{
			CloseHandle(m_hComport); //关闭COM 
			m_biComportOpened = 0;
			return 0;
		}
		
		if( nv.get("stop") == "1" ) PortDCB.StopBits = ONESTOPBIT; 
		else if( nv.get("stop") == "1.5" ) PortDCB.StopBits = ONE5STOPBITS; 
		else if( nv.get("stop") == "2" )   PortDCB.StopBits = TWOSTOPBITS; 
		else
		{
			CloseHandle(m_hComport); //关闭COM 
			m_biComportOpened = 0;
			return 0;
		}

		if(! SetCommState(m_hComport, &PortDCB))
		{
			///L"配置串口失败";
			CloseHandle(m_hComport); //关闭COM 
			m_biComportOpened = 0;
			return 0;
		}

		////配置超时值

		if( (int)( SStrf::satof( nv.get("timeoutsec") ) * 1000 ) < 1 )  
		{
			CloseHandle(m_hComport); //关闭COM 
			m_biComportOpened = 0;
			return 0;
		}

		COMMTIMEOUTS CommTimeouts;

		GetCommTimeouts(m_hComport, &CommTimeouts);
		CommTimeouts.ReadIntervalTimeout = MAXDWORD; 
		CommTimeouts.ReadTotalTimeoutMultiplier = 10; 
		CommTimeouts.ReadTotalTimeoutConstant  = (int)( SStrf::satof( nv.get("timeoutsec") ) * 1000 ); 
		CommTimeouts.WriteTotalTimeoutMultiplier = 50; 
		CommTimeouts.WriteTotalTimeoutConstant = (int)( SStrf::satof( nv.get("timeoutsec") ) * 1000 ); 
		if (!SetCommTimeouts(m_hComport, &CommTimeouts))
		{
			///L"不能设置超时参数";
			CloseHandle(m_hComport); //关闭COM 
			m_biComportOpened = 0;
			return 0;
		}

		m_biShouldDisConn = 0;

		return 1;
	}



	virtual void OnDisConn()
	{
		m_biShouldDisConn = 1;
		
		if( m_biComportOpened )
		{
			CloseHandle(m_hComport); 
			m_biComportOpened = 0;
		}
	}



public:


	virtual int on_sys_recv( SCake & ckDataBuf ) //return the recv len, 1 or 0
	{
		if(m_biShouldDisConn)
		{
			return 0;
		}

		ckDataBuf.redim( on_get_defaultrecv_buf_len() );

		DWORD dwBytes;

		ReadFile(m_hComport, ckDataBuf.buf(), ckDataBuf.len(), &dwBytes, 0); 

		if(dwBytes == ckDataBuf.len()) return (int)ckDataBuf.len();

		return 0;
	}


	virtual int on_sys_send( const SCake & ckDataBuf ) //return the successfully sent len
	{
		if(m_biShouldDisConn)
		{
			return 0;
		}

		DWORD ret;

		WriteFile( m_hComport, ckDataBuf.buf_const(), 1 ,&ret, NULL ); //发送 

		if( ckDataBuf.len() % 13 == 3 || SStrf::rand1() > 0.88 )
			WThrd::tr_sleep( 0, 0.001 );

		return (int)ret;
	}


}; //end class 




X011_NAMESPACE_END

#endif





/*
W series
tcp link cell
*/

// 

#ifndef X011__H_w_MOON_MAN_h
#define X011__H_w_MOON_MAN_h



X011_NAMESPACE_BEGIN



template < class CONN_AGENT_T >
class WMoonMan : public WTcpDisConnable
{

private:

	std::string		m_strMManId;
	std::string		m_strMManIdRemote;

	tbool m_iIsConnected;


	int on_sys_recv( SCake & ckDataBuf ) //return the real recv len
	{
		if( !m_iIsConnected ) return 0;
		return OnRecv( ckDataBuf ) ;
	}

	int on_sys_send( const SCake & ckDataBuf ) //return the successfully sent len
	{
		if( !m_iIsConnected ) return 0;
		return OnSend( ckDataBuf );
	}


protected:

	static std::string MkId() 
	{
		return WMsg::MkUId(); 
	}


public:

	WMoonMan() :
	  m_iIsConnected(0)
	{
	}

	virtual ~WMoonMan()
	{
	}


public:

	typedef CONN_AGENT_T  CONN_AGENT_TYPET;


public:

	tbool Conn( CONN_AGENT_TYPET  rd ) //ConnDestTypeT即表达了多个MM对应一个联接的对应关系。例如多个cells中都需要一个listener&。
	{
		SetMManId();
		SetMManIdRemote();
		m_iIsConnected = OnConn( rd )?1:0;
		return m_iIsConnected;
	}
	
	void DisConn()
	{
		m_iIsConnected = 0;

		//OnDisConn();
		WTcpDisConnable::DisConn();
	}

	tbool IsConnected() const
	{
		return m_iIsConnected;
	}


	void SetMManId( std::string strId = "" )  
	{
		if( strId == "" )
			m_strMManId = MkId();
		else
			m_strMManId = strId; 
	}
	

	void SetMManIdRemote( std::string strId = "" )  
	{
		if( strId == "" )
			m_strMManIdRemote = MkId();
		else
			m_strMManIdRemote = strId; 
	}



	std::string GetMManId() const
	{
		return m_strMManId;
	}
	

	std::string GetMManIdRemote() const
	{
		return m_strMManIdRemote;
	}



public:

	virtual tbool OnConn( CONN_AGENT_TYPET  rd ) = 0;
	/*{
		return 0;
	}*/

	virtual void OnDisConn() = 0;
	/*{
		return;
	}*/

	virtual int OnRecv( SCake & ckDataBuf ) = 0;
	/*{
		return 0;
	}*/

	virtual int OnSend( const SCake & ckDataBuf ) = 0;
	/*{
		return 0;
	}*/

}; //end class 




X011_NAMESPACE_END


#endif





/*
W series
tcp link linker
*/

// 

#ifndef X011__H_w_MOON_box_H
#define X011__H_w_MOON_box_H



X011_NAMESPACE_BEGIN



template < class MoonMan_Ta, class MoonMan_Tb >
class WMoonBox : public WThrd 
{

private:
		
	class WMoonBoxThread : public WThrd 
	{
	public:
		WMoonBox * m_Mbox;
		int m_iMManType;

		virtual int tr_on_user_run() 
		{
			if( m_iMManType == 'a' )
			{
				return m_Mbox->RunMMa();
			}
			else
			{
				return m_Mbox->RunMMb();
			}
		}
	};


private:

	MoonMan_Ta * m_pMMa;
	MoonMan_Tb * m_pMMb;

	WMoonBoxThread m_thrdMMa;
	WMoonBoxThread m_thrdMMb;



	virtual int tr_on_user_run() 
	{
		return RunMM3();
	}


	int DeliverAb( WTcpDisConnable * p1, WTcpDisConnable * p2 )
	{
		SCake ckTmp; 
		if( p1->recv_bin( ckTmp ) )
		{
			OnDeliverAb( ckTmp );
			p2->send_bin( ckTmp );
			return 1;
		}
		p2->DisConn();
		return 0;
	}


	int DeliverBa( WTcpDisConnable * p1, WTcpDisConnable * p2 )
	{
		SCake ckTmp; 
		if( p1->recv_bin( ckTmp ) )
		{
			OnDeliverBa( ckTmp );
			p2->send_bin( ckTmp );
			return 1;
		}
		p2->DisConn();
		return 0;
	}


	int RunMMa()
	{
		return DeliverAb( m_pMMa, m_pMMb ); //这里传入SCake &ckTmp; 然后调用OnDeliver()让后代处理通信数据。在before send处进行处理。
	}


	int RunMMb()
	{
		return DeliverBa( m_pMMb, m_pMMa );
	}


	int RunMM3()
	{
		return OnMoonBoxThrdRun( m_thrdMMa, m_thrdMMb );
	}


public:

	WMoonBox() 
	{
		m_pMMa = new MoonMan_Ta();
		m_pMMb = new MoonMan_Tb();
	}


	virtual ~WMoonBox()
	{
		m_thrdMMa.tr_shouldbrk();
		m_thrdMMb.tr_shouldbrk();
		m_pMMa->DisConn();
		m_pMMb->DisConn();
		m_thrdMMa.tr_wait();
		m_thrdMMb.tr_wait();

		if(m_pMMa)
		{
			delete m_pMMa;
		}

		if(m_pMMb)
		{
			delete m_pMMb;
		}
	}


public:

	void Init()
	{
		//m_pMMa->Conn( MkMManID() );
		//m_pMMb->Conn( MkMManID() );
	}


	MoonMan_Ta & GetMMa()
	{
		return * m_pMMa;
	}


	MoonMan_Tb & GetMMb()
	{
		return * m_pMMb;
	}


	void Launch()
	{	
		m_thrdMMa.m_Mbox = this;
		m_thrdMMa.m_iMManType = 'a';
		m_thrdMMb.m_Mbox = this;
		m_thrdMMb.m_iMManType = 'b';

		m_thrdMMa.tr_open();
		m_thrdMMb.tr_open();

		/*if( iWantAutoDelete )
			tr_openx();
		else 	tr_open();*/
	}


public:

	virtual int OnMoonBoxThrdRun( WThrd & thrd_a, WThrd & thrd_b )
	{
		thrd_a.tr_wait();
		thrd_b.tr_wait();
		return 0; //一般对box用new,然后openx(),且不要用pm->tr_wait()，是为了让box在自己的线程中,两个man都结束时销毁所有成员。
	}

	
	virtual void OnDeliverAb( SCake & ckTmp )
	{
		//Beep(123,12);
		//Sleep(34);
		//Beep(123,1);
		//printf( "%d\t", ckTmp.len() );

		return;
	}


	virtual void OnDeliverBa( SCake & ckTmp )
	{
		return;
	}

}; //end class 





X011_NAMESPACE_END


#endif




/*
W series
a moon man simple cell client 
*/

// 

#ifndef X011__H_w_WMManSimpCellc_h
#define X011__H_w_WMManSimpCellc_h



X011_NAMESPACE_BEGIN



template< class Cellc_T = WTcpCellc >
class WMManSimpCellc : public WMoonMan< std::string >
{
public:
	Cellc_T  m_tcpc;

public:

	virtual tbool OnConn( CONN_AGENT_TYPET strAddr )//故意不采用string& 型，可使适应度高些。
	{
		return m_tcpc.Conn( strAddr );
	}

	virtual void OnDisConn()
	{
		m_tcpc.DisConn();
		return;
	}

	virtual int OnRecv( SCake & ckDataBuf ) 
	{
		m_tcpc.recv_bin(ckDataBuf);
		return ckDataBuf.len();
	}

	virtual int OnSend( const SCake & ckDataBuf ) 
	{
		if( m_tcpc.send_bin( ckDataBuf ) )
		{
			return ckDataBuf.len();
		}
		return 0;
	}

}; //end class 




X011_NAMESPACE_END


#endif




/*
W series
a moon man simple cell server 
*/

// 

#ifndef X011__H_w_WMManSimpCells_h
#define X011__H_w_WMManSimpCells_h



X011_NAMESPACE_BEGIN


//template< class Cells_T = WTcpCells >
//class WMManSimpCells;


template< class Cells_T = WTcpCells >
class WMManSimpCells : public WMoonMan< WTcpListener & >
{
public:
	Cells_T m_tcps;

public:

	virtual tbool OnConn( CONN_AGENT_TYPET L )
	{
		return m_tcps.Conn(L);
	}

	virtual void OnDisConn()
	{
		m_tcps.DisConn();
		return;
	}

	virtual int OnRecv( SCake & ckDataBuf ) 
	{
		m_tcps.recv_bin(ckDataBuf);
		return ckDataBuf.len();
	}

	virtual int OnSend( const SCake & ckDataBuf ) 
	{
		if( m_tcps.send_bin( ckDataBuf ) )
		{
			return ckDataBuf.len();
		}
		return 0;
	}

}; //end class 




X011_NAMESPACE_END


#endif





#pragma warning(pop)

#endif

#ifdef LINUENV_

/*
X011 project 
WHYSOFT league 2007-09
ALL RIGHTS RESERVED.
S series designed for standard C++, any OS, 32bit compatible.
W series designed for windows
*/

#ifndef X011__H_w_sbase_h
#define X011__H_w_sbase_h


#define X011_NAMESPACE_BEGIN namespace wl {
#define X011_NAMESPACE_END                }


#include <iterator> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>

#include <sys/dir.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>  // usleep
#include <pthread.h>

#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <termios.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>

#include "iconv.h"

X011_NAMESPACE_BEGIN

//basic types
typedef		double					tdouble; //8 bytes
typedef		char					tint8;
typedef		unsigned char			tuint8;
typedef		short					tint16;
typedef		unsigned short			tuint16;
typedef		long					tint32;
typedef		unsigned long			tuint32;

typedef     long long               tint64;
typedef     unsigned long long      tuint64; //scanf("%I64d",&a);printf("%I64d",a);scanf("%lld",&a);printf("%lld",a);Dev-C++的g++编译器，它使用的是"%I64d"而非"%lld"。 


//derived types
typedef		tint8				tchar;
typedef		int					tbool; 

//mem based types
typedef		tuint32			tsize;
typedef		tint32			toffset;


typedef unsigned long       DWORD;


X011_NAMESPACE_END


#define		SOCKET                int
#define		INVALID_SOCKET                (-1)
#define		closesocket                close 
#define		SOCKET_ERROR            (-1)




#endif




/*
standard C lib pack
all SECURE matters are packed here.
*/

#ifndef X011__H_w_SClib_h
#define X011__H_w_SClib_h





X011_NAMESPACE_BEGIN


class SClib
{

public:

	SClib(){;}

	~SClib(){;}

	typedef int (* PT_sscanf)( const char *buffer, const char *format , ... );
	static PT_sscanf p_sscanf() { return sscanf; }

	typedef int (* PT_sprintf)( char *, const char *, ... );
	static PT_sprintf p_sprintf() { return sprintf; }

	typedef char * (* PT_strcpy)( char *strDestination, const char *strSource );
	static PT_strcpy p_strcpy() { return strcpy; }


	typedef tm * (* PT_localtime)( const time_t * );
	static PT_localtime p_localtime() { return localtime; }

	typedef FILE * (* PT_fopen)( const char *filename, const char *mode );
	static PT_fopen p_fopen(){ return fopen; }


	static char * ltoaB( long _Val, char * _DstBuf, int _Radix)
	{
		if(_Radix==16)
			sprintf(_DstBuf, "%x",  _Val);
		else
			sprintf(_DstBuf, "%ld", _Val);

		return _DstBuf;
	}

	typedef char * (* PT_ltoa)( long value, char *str, int radix );
	static PT_ltoa p_ltoa() { return ltoaB; }


}; //end class SClib





X011_NAMESPACE_END



#endif





/*
base string func
*/

#ifndef X011__H_w_sstrf_h
#define X011__H_w_sstrf_h



X011_NAMESPACE_BEGIN


class SStrf
{

public:

	//SStrf(){;}

	virtual ~SStrf(){;}


	template < class T >
	static T * AddressOf( T & obj )
	{
		return reinterpret_cast<T *>(&reinterpret_cast<char&>(obj));
	}


	template< class T >
	static T * newobjptr( T * & p )
	{
		try
		{
			p = new T;
		}
		catch(...)
		{
			p = NULL;
		}

		return p;
	}

	
	template< class T >
	static T * newobjptr()  // wl::SStrf::newobjptr<bu_sop_t>()->tr_openx();
	{
		T *  p;
		return newobjptr(p);
	}


	static void * smalloc( tsize i )
	{
		return malloc( i );
	}


	static void sfree(void *s)
	{
		free(s);
	}



	static tuint16 smkU16( tuint8 c1, tuint8 c2) //lower byte is c1, comes first
	{
	   tuint16 ilow,ihigh;
	   ilow =  (tuint16)c1;
	   ihigh = (tuint16)c2;
	   ihigh <<= 8;
	   return ihigh + ilow;
	}


	template< class T >
	static T & chgendian( T & val )
	{
		if( sizeof(T) != 1 ) srev( (tchar *)&val, sizeof(T) ) ;
		return val;
	}

	template< class T >
	static T chgendian2( T val )
	{
		return chgendian(val);
	}
	

	
	static tbool readbit( void * pbin , int sufx )  
	{
		if( sufx < 0 )
		{
			return 0;
		}

		tuint8 * pbin2 = (tuint8 *)pbin;
		tuint8 cSrc;
		int iOffset ;

		cSrc = pbin2[sufx / 8];

		//iOffset = 7 - (sufx % 8);
		iOffset =  (sufx % 8);

		cSrc >>= iOffset;
		cSrc &= 1;
		return cSrc;
	}

	
	static tbool readbit( tuint8 bindata , int sufx )  
	{
		return readbit( &bindata, sufx );
	}


	static void writebit( void * pbin , int sufx , tbool val )
	{
		if( sufx < 0 )
		{
			return ;
		}

		val = val?1:0; 

		tuint8 * pbin2 = (tuint8 *)pbin;
		int cSrc;
		int iOffset ;

		cSrc = pbin2[sufx / 8];

		//iOffset = 7 - (sufx % 8);
		iOffset = (sufx % 8);

		cSrc >>= iOffset;
		cSrc &= 1;

		if( cSrc == val ) return ;

		int i = 1;
		i <<= iOffset;

		pbin2[sufx / 8] ^= i;
	}


	static std::string & bit2str( tchar c, std::string & strrtn )
	{
		strrtn = "01234567";
		for( int i = 0; i < 8; i++ ) strrtn[i] = readbit( &c, i ) ? '1' : '0' ;
		return strrtn;
	}

	static std::string bit2str( tchar c )
	{
		std::string str;
		return bit2str( c, str );
	}

	static tchar & str2bit( std::string str, tchar & c )
	{
		//......12345678  --是高位补0
		str += "00000000";
		for( int i = 0; i < 8; i++ ) writebit( &c, i , str[i]=='0' ? 0 : 1 );
		return c;
	}

	static tchar str2bit( std::string str )
	{
		tchar c;
		return str2bit( str, c );
	}


	static void initrand( int seed = 0 ) //sets the generator to a random starting point. better than srand()
	{
		tint32 j=(tint16)(0x0555&(time(0)*seed));
		for(tint32 i=0;i<j;++i) rand();
	}


	static tdouble rand1( int iShouldInitSeed = 0 )
	{
		if( iShouldInitSeed ) initrand( iShouldInitSeed );
		return (tdouble)rand()/(tdouble)RAND_MAX;
	}


	static void *smemcpy( void *dest, const void *src, tsize count )
	{
		return memcpy(dest,src,count);//memcpy
	}


	static void * smemset( void *dest, tchar c, tsize count )
	{
		return memset( dest, (int)c, (size_t)count );
	}


	template< class T >
	static void * smemset( T * dest, tchar c = 0 )
	{
		return memset( dest, (int)c, sizeof(T) );
	}




	static tchar * scpy( tchar *strDestination, const tchar *strSource )
	{
		return (*SClib::p_strcpy())( strDestination, strSource );
	}


	static tsize slen( const tchar * s ) //串长度
	{
		if(s==NULL) return (tsize)0;
		return (tsize)strlen(s);
	}


	static tbool sishex(tchar c)//是16进制
	{
		return  (c>='0'&&c<='9')||(c>='A'&&c<='F')||(c>='a'&&c<='f');
	}

	static tbool sishex(const tchar *s)
	{
		if(s==NULL) return 0;
		for(;*s;s++) if(!sishex(*s)) return 0;
		return 1;
	}

	static tbool sisdec(tchar c) //是10进制
	{
		return  (c>='0'&&c<='9');
	}

	static tbool sisdec(const tchar *s)
	{
		if(s==NULL) return 0;
		for(;*s;s++) if(!sisdec(*s)) return 0;
		return 1;
	}


	static tchar *sltoa( tint32 i, tchar *buf, int radix = 10 )
	{
		return (*SClib::p_ltoa())(i, buf, radix);
	}


	static std::string sltoa( tint32 i, int radix = 10 )
	{
		tchar c[55];
		std::string buf;
		buf = sltoa( i, c, radix );
		return buf;
	}

	static tint32 satol( const tchar *s ) { return(s==NULL)?0:(tint32)atol(s); }

	static tint32 satol( const std::string & s ) { return satol(s.c_str()); }


	
	static std::string sultoa( tuint32 i )
	{
		std::stringstream stream;
		stream << i;
		return stream.str();
	}

	
	static tuint32 satoul( std::string  s ) 
	{ 
		return strtoul(s.c_str(),NULL,10); 
	}



	static tchar * sftoa( tdouble f , tchar * buf , int decimal_digits = -1 )
	//static tchar * sftoa( tdouble f, tchar *buf )
	{
		std::string s1;

		if( decimal_digits < 0 )
		{
			s1 = "%f";
		}
		else
		{			
			s1 = "%." + sltoa(decimal_digits) + "f";
		}

		(*SClib::p_sprintf())( buf, s1.c_str(), f );

		return buf;
	}

	static std::string sftoa( tdouble f , int decimal_digits = -1 )
	{
		if( decimal_digits < -1 ) decimal_digits = -1;
		std::vector<tchar> v( 22 + decimal_digits );
		tchar * c;
		c = &(v[0]);
		return  sftoa( f, c , decimal_digits );
	}


	static tdouble satof( const tchar *s )
	{
		if(s==NULL) return 0.0;
		return (tdouble)atof(s);
	}


	static tdouble satof( const std::string & s )
	{
		return satof(s.c_str());
	}


	static int scmpi( const tchar *a, const tchar *b )	//case insensitive
	{
		if(a==NULL&&b==NULL) return 0;
		if(a==NULL&&b!=NULL) return -1;
		if(a!=NULL&&b==NULL) return 1;
		const tchar *t1;
		const tchar *t2;
		tchar c1, c2;
		toffset i;
		t1 = a;
		t2 = b;
		for( i=0;t1[i]&&t2[i];i++ )
		{
			c1=t1[i]; c2=t2[i];
			if(c1>='a'&&c1<='z') c1+=('A'-'a');
			if(c2>='a'&&c2<='z') c2+=('A'-'a');
			if(c1!=c2) return c1-c2;
		}
		return t1[i]-t2[i];
	}


	static int scmpin( const tchar *a, const tchar *b, tsize count ) //case insensitive
	{
		if(a==NULL&&b==NULL) return 0;
		if(a==NULL&&b!=NULL) return -1;
		if(a!=NULL&&b==NULL) return 1;
		const tchar *t1;
		const tchar *t2;
		tchar c1, c2;
		tsize i;
		t1 = a;
		t2 = b;
		for( i=0;t1[i]&&t2[i]&&i<count;i++ )
		{
			c1=t1[i]; c2=t2[i];
			if(c1>='a'&&c1<='z')c1+=('A'-'a');
			if(c2>='a'&&c2<='z')c2+=('A'-'a');
			if(c1!=c2)return c1-c2;
		}
		if(i>0) i--;
		return t1[i]-t2[i];
	}


	static int scmpin( const tchar *a, const tchar *b ) //case insensitive
	{
		return scmpin(a,b,slen(b));
	}




	static int scmpn( const tchar *a, const tchar *b, tsize count )
	{
		if(!count) return 0; //if no len, then equal.
		if(a==NULL&&b==NULL) return 0;
		if(a==NULL&&b!=NULL) return -1; // a<b
		if(a!=NULL&&b==NULL) return 1;  // a>b
		return strncmp(a,b,count);
	}


	static int scmpn( const tchar *a, const tchar *b ) //assume count is len of b.
	{
		return scmpn(a,b,slen(b));
	}




	static int scmp( const tchar *a, const tchar *b )
	{
		if(a==NULL&&b==NULL) return 0;
		if(a==NULL&&b!=NULL) return -1;
		if(a!=NULL&&b==NULL) return 1;
		return strcmp(a,b);
	}


	static tchar * sucase( tchar *s )
	{
		toffset i;
		if(s==NULL) return NULL;
		for(i=0;s[i]!=0;i++){
			if(s[i]>='a'&&s[i]<='z')s[i] = s[i] -'a' + 'A' ;
		}
		return s;
	}

	
	static std::string & sucase( std::string & str )
	{
		tchar * szstr;
		szstr = (tchar *)smalloc( (tsize)str.size() + 1 );
		scpy( szstr, str.c_str() );
		sucase( szstr );
		str = szstr;
		sfree( szstr );
		return str;
	}


	static tchar * slcase( tchar *s )
	{
		toffset i;
		if(s==NULL) return NULL;
		for(i=0;s[i]!=0;i++){
			if(s[i]>='A'&&s[i]<='Z')s[i] = s[i] -'A' + 'a' ;
		}
		return s;
	}


	static std::string & slcase( std::string & str )
	{
		tchar * szstr;
		szstr = (tchar *)smalloc( (tsize)str.size() + 1 );
		scpy( szstr, str.c_str() );
		slcase( szstr );
		str = szstr;
		sfree( szstr );
		return str;
	}



	//指出最后一个字符的指针.可以向左偏移。
	//偏移量0代表最末一个字节，而不是c00. but if s is "", return the pointer to c00 .
	template< class Pchar_CPchar_T >	/*Pchar_CPchar_T可能是const或非const的字节指针*/
	static Pchar_CPchar_T splast( Pchar_CPchar_T s, toffset offset2left = 0 /*正数代表向左方*/ )	
	{
		Pchar_CPchar_T t = s;
		if(!s||!*s) return t; //
		toffset i,j ;
		j = (toffset)slen(s);
		i = j - 1 - offset2left ;
		t=s+(i<0?0:i);
		return t;//最多退到s本身。
	}



	static const tchar * sstr( const tchar * s, const tchar *substr ) 
	{
		if(!s||!substr||!(*s)||!(*substr)) return NULL;
		return (const tchar *)strstr(s,substr); 
	}

	static tchar * sstr( tchar * s, const tchar *substr ) 
	{
		if(!s||!substr||!(*s)||!(*substr)) return NULL;
		return (tchar *)strstr(s,substr); 
	}


	template< class Pchar_CPchar_T >
	static Pchar_CPchar_T sstr( Pchar_CPchar_T s, tchar subc )
	{
		tchar t[2];
		t[0]=subc;
		t[1]=0;
		return sstr(s,t) ;
	}


	static tchar * srev( tchar * s, tsize len ) 
	{
		tsize u;
		toffset  x, y, i, a, b;
		u = len;
		u >>= 1;
		x = u;
		y = (toffset)len - 1;
		for(i=0;i<x;i++) {
			a = i;
			b = y - i; 
			s[a] ^= s[b];
			s[b] ^= s[a];
			s[a] ^= s[b];
		}
		return s;
	}


	static tchar *srev( tchar * s )
	{
		return srev(s,slen(s));
	}


	static tchar * sreplch( tchar * source, tsize len, tchar c1, tchar c2 )	//对于来源二进制串中所有的c1替换成c2
	{
		tsize i;
		for(i=0;source&&i<len;i++) {
			if(source[i]==c1) source[i]=c2;
		}
		return source;
	}


	static tchar * sreplch( tchar * source, tchar c1, tchar c2 )	//所有的c1替换成c2
	{
		return sreplch(source, slen(source), c1, c2);
	}


	static std::string & sreplstr( std::string & str, const tchar *string_to_replace, const tchar *new_string )   
	{
		if( string_to_replace && new_string )
		{
			//   Find   the   first   string   to   replace   
			std::string::size_type   index   =   str.find(string_to_replace);   
			//   while   there   is   one   
			while(index   !=   std::string::npos)   
			{   
				//   Replace   it   
				str.replace(index,   strlen(string_to_replace),   new_string);   
				//   Find   the   next   one   
				index   =   str.find(string_to_replace,   index   +   strlen(new_string));   
			}   
		}
		return   str;   
	}


	static std::string & sreplstr( std::string & str, const std::string & string_to_replace, const std::string & new_string ) 
	{
		return sreplstr( str, string_to_replace.c_str(), new_string.c_str() ) ;
	}

	//static std::string & sreplstr( std::string & str,  std::string * string_to_replace,  std::string * new_string ) 
	//{
	//	if( string_to_replace==NULL) return str;
	//	if( new_string==NULL) return str;
	//	return sreplstr( str, string_to_replace->c_str(), new_string->c_str() ) ;
	//}

	//static std::string & sreplstr( std::string & str,  std::string  string_to_replace,  std::string  new_string ) 
	//{
	//	return sreplstr( str, string_to_replace.c_str(), new_string.c_str() ) ;
	//}



	// 3 trim functions below:

	//a trim base func:
	static std::string & str_trim_base( tchar *(*f)( tchar *, const tchar * ), std::string & str, const tchar *str_space="\r\n \t" )
	{
		tchar * pstr;
		pstr = (tchar *)smalloc( (tsize)str.size() + 1 );
		scpy( pstr, str.c_str() );
		str = (*f)( pstr, str_space );
		sfree( pstr );
		return str;
	}


	//right trim 

	static tchar * strimr( tchar * s, tchar a_space ) //right trim, tchar. trim series knl
	{
		toffset i;
		for(i=slen(s)-1;i>=0;i--)
			if(s[i]==a_space)
				s[i]=0;
			else
				break;
		return s;
	}

	static tchar * strimr( tchar * s, const tchar *str_space="\r\n \t" ) //right trim, tchar*. trim series knl
	{
		toffset i;
		for( i=slen(s)-1; i >= 0; i-- )
			if( sstr(str_space,s[i]) != NULL )
				s[i]=0;
			else
				break;
		return s;
	}

	static std::string & strimr( std::string & str, const tchar * str_space = "\r\n \t" )
	{
		return str_trim_base( strimr, str, str_space );
	}


	//left trim 

	static tchar * striml( tchar * s, tchar a_space )	//left trim
	{
		return srev( strimr(srev(s), a_space) ) ;
	}

	static tchar * striml( tchar * s, const tchar * str_space = "\r\n \t" )		//left trim
	{
		return srev( strimr(srev(s), str_space) ) ;
	}

	static std::string & striml( std::string & str, const tchar * str_space = "\r\n \t" )
	{
		tchar * pstr;
		pstr = (tchar *)smalloc( (tsize)str.size() + 1 );
		scpy( pstr, str.c_str() );
		str = striml( pstr, str_space );
		sfree( pstr );
		return str;
	}


	//double trim

	static tchar * strim( tchar * s, tchar a_space  ) // double trim
	{
		return  striml( strimr(s,a_space), a_space) ;
	}

	static tchar * strim( tchar * s, const tchar * str_space = "\r\n \t" ) // double trim
	{
		return  striml( strimr(s,str_space), str_space) ;
	}

	static std::string & strim( std::string & str, const tchar * str_space = "\r\n \t" )
	{
		return str_trim_base( strim , str, str_space );
	}

	//trim functions end.



	static tchar * sleft( tchar * s, tsize n ) //left right mid series knl
	{
		if(n>slen(s)) return s;
		s[n]=0;
		return s;
	}


	static tchar * sright( tchar * s, tsize n )
	{
		return srev(sleft(srev(s), n));
	}


	static tchar * smid( tchar * s, tsize a_pos, tsize a_len )
	{
		sright(s, slen(s) - a_pos );
		sleft(s, a_len);
		return s;
	}



	static const tchar * seq_dirno()
	{
		return "0123456789ACEFHKLMPQSTUWXYZ"; //dirnogjbv	 27 left
	}



	static std::string seq( std::string strCurNum, tbool isFixLen = 1, const tchar * s_symbset = NULL )
	{
		static tchar c[1];
		tchar * s_num;
		tint16 *lia ;
		tint16 ulia;
		tint32 i,j,k;

		c[0]=0;
		if(slen(s_symbset)<2) s_symbset = seq_dirno();
		s_num = (tchar*)smalloc( (tsize)strCurNum.size() + 2 );
		if(!s_num) return "";
		lia = (tint16 *)smalloc( (slen(s_num) + 1)*sizeof(tint16) );
		if(!lia)
		{
			sfree(s_num);
			return "";
		}

		scpy( s_num, strCurNum.c_str() );
		
		if(!(*s_num)) {
			s_num[0]=s_symbset[0];
			s_num[1]=0;
		}

		j = slen(s_num) ;
		for(i=0;i<j;i++)
		{
			const char *t = sstr( s_symbset, s_num[i] );
			if(!t)
				lia[i] = 0;
			else
				lia[i] = (tint16)( t - s_symbset );			
		}

		lia[j-1] ++;
		k = slen(s_symbset) ;
		ulia = 0;
		for(i=j-1;i>=0;i--)
		{
			if(lia[i] >= k)
			{
				lia[i] -= (tint16)k;
				if(i>0)
					lia[i-1]++;
				else
					ulia++;
			}
		}

		for( i=0;i<j;i++ )
		{
			s_num[i] = s_symbset[ lia[i] ];
		}

		if( (!isFixLen) && ulia )	//如果不是固定长度，则处理最高位进位。
		{
			srev(s_num);
			s_num[j] = s_symbset[ulia];
			s_num[j+1] = 0;
			srev(s_num);
		}

		strCurNum = s_num;
		sfree(s_num);
		sfree(lia);
		return strCurNum;
	}




	static tchar bs_esc() { return 'b'; }/*b被合成后应该换成%*/



	static tbool bs_inset( tchar c ) //in direct expression set
	{
		if(c==bs_esc()) return 0; //if is esc then is not in the set
		if(c>='a'&&c<='z') return 1;
		if(c>='0'&&c<='9') return 1;
		if(c>='A'&&c<='Z') return 1;
		return 0;
	}


	static tsize bs_ensize( const tchar *s, tsize len ) 
	{
		tsize i;
		tchar *t1, *t2, *t3;
		if(s==NULL) return 0;
		i=0;
		t1=(tchar*)s;
		t3=t1+len;
		for( t2=t1; t2<t3; t2++ )
			i += bs_inset(*t2)?(1*sizeof(tchar)):(3*sizeof(tchar));

		return i+(sizeof(tchar)); //must be sz-string after encode. a tchar for '\0'
	} 


	static tsize bs_ensize( const tchar *s ) 
	{ 
		return bs_ensize( s, slen(s) + 1 );
	}


	static tchar * bs_en( const tchar *s, tsize len, tchar *destbuf )
	{
		tchar *ss1, *ss2, *ss3, *sd1;
		tbool rc;
		int l;
		if(s==NULL||destbuf==NULL) return NULL;
		ss1 = (tchar*)s;
		ss3 = ss1 + len;
		sd1 = destbuf;

		for( ss2=ss1; ss2<ss3; ss2++)
		{
			rc = 0;

			do //fakedo 0
			{
				if( !bs_inset(*ss2) ) //不在圈里，崩溃。
				{ 
					rc = 1;
					break;
				}

				*sd1 = *ss2;         //没崩溃时的处理。
				sd1++;

			}while(0);

			if(rc) {    //崩溃时的处理。
				l = (tuint8)(*ss2);
				(*SClib::p_sprintf())( sd1, "%c%02X", bs_esc(), l );
				sd1 += (3*sizeof(tchar));
			}
		}
		*sd1=0;//to form a sz. bs_ensize has reported this space up there
		return destbuf;
	}


	static tchar * bs_en( const tchar *s, tchar *destbuf )
	{
		return bs_en( s, slen(s) + 1, destbuf );
	}

	static std::string  & bs_en( std::string & strData ) //the data includes the sz00.
	{
		std::string s1( 3 + bs_ensize( strData.c_str(), (tsize)strData.length() ) , 'a' );

		bs_en( strData.c_str(), &(s1[0]) );

		return strData = s1.c_str();
	}

	static std::string  & bs_de( std::string & strData )  
	{
		std::string s1( strData + "123" );

		bs_de( strData.c_str(), &(s1[0]) );

		return strData = s1.c_str();
	}


	static tsize bs_desize( const tchar *s , tchar(*apf1)()=bs_esc )
	{
		toffset j,i;
		tsize  k;
		if(s==NULL) return 0;
		
		for( i=0,j=(toffset)slen(s),k=0;i<j; ) 
			if(	(i+2<j)				&&
				s[i]==(*apf1)( )	&&
				sishex(s[i+1])		&&
				sishex(s[i+2])  )
			{
				k++;
				i+=3;
			}
			else
			{
				i++;
				k++;
			}
		return k;
	}


	static tchar * bs_de( const tchar *s, tchar *dest , tchar(*apf1)()=bs_esc ) //the dest buffer can be the same of the source. safe to overlay
	{
		if(s==NULL||dest==NULL) return dest;
		toffset i,j,k;
		toffset a1,a2;
		tchar ss[2]; 
		ss[1]=0;

		for(i=0,j=(toffset)slen(s),k=0;i<j; ) {
			if(	(i+2<j)			&&
				s[i]==(*apf1)( )&&
				sishex(s[i+1])	&&
				sishex(s[i+2])	 )
			{
				ss[0]=s[i+1];
				sucase(ss);
				a1 = (ss[0] <= '9' ? ss[0] - '0' : ss[0] - 'A' + 10) * 16 ;

				ss[0]=s[i+2];
				sucase(ss);
				a2 = (ss[0] <= '9' ? ss[0] - '0' : ss[0] - 'A' + 10) ;

				*(tchar *)(dest+k) = (tuint8)(a1+a2);
				k++;
				i+=3;
			}else{
				dest[k] = s[i];
				k++;
				i++;
			}
		}

		return dest;
	}


	static tchar * bs_de( tchar *source_dest , tchar(*apf1)()=bs_esc ) //the dest buffer is the source. safe to overlay
	{
		return bs_de(source_dest,source_dest,apf1);
	}

	

	template< class T >
	static std::string b2s( /*const*/ T & sourcedata )
	{
		std::string str1;
		tchar * szstr;
		szstr = (tchar *)smalloc( sizeof(T) * 3 + 3 );
		bs_en( (const char *)reinterpret_cast<const char *>(&reinterpret_cast</*const*/ char& >(sourcedata)), sizeof(T), szstr );
		str1 = szstr;
		sfree( szstr );
		return str1;
	}

	
	template< class T >
	static T & s2b( std::string strSource, T & destdata )
	{
		bs_de( strSource.c_str(), reinterpret_cast<tchar *>(&reinterpret_cast<char& >(destdata))  );
		return destdata;
	}

	template< class T >
	static T s2b( std::string strSource )
	{
		T destdata;
		bs_de( strSource.c_str(), reinterpret_cast<tchar *>(&reinterpret_cast<char& >(destdata))  );
		return destdata;
	}


}; //end class SStrf 





X011_NAMESPACE_END





#define MOONLOGSTR  \
	( "**" + /*wl::SDte::GetNow().ReadStringPack() + "|" +*/ std::string(__FILE__) + "|" + std::string(__FUNCTION__) + "|" + wl::SStrf::sltoa(__LINE__) )






#endif




/*
calculate func
*/

#ifndef X011__H_w_SCalc_h
#define X011__H_w_SCalc_h



X011_NAMESPACE_BEGIN


class SCalc
{

public:

	//SCalc(){;}

	virtual ~SCalc(){;}
	
	
	
	static tint32 max_divisor( tint32 a, tint32 b) //得出来a就是a和b的最大公约数
	{
		tint32 temp; 
		while(b!=0) //---判断余数是否为0,为0了,就是最大公约数了a 
		{ 
		temp=a%b; //a数去除b数的余数赋值给temp 
		a=b;      //把b数赋值给a 
		b=temp;   //把余数赋值给b
		} 
		return a;
	}


	static tbool quadratic_equation_root( tdouble a, tdouble b, tdouble c, tdouble *x1, tdouble *x2) //求一元二次方程的根
	{
		if(b*b<4*a*c) return 0; 
		*x1=(sqrt(b*b-4*a*c)-b)/(2*a); 
		*x2=(-sqrt(b*b-4*a*c)-b)/(2*a); 
		return 1; 
	}


	static std::string dseal( const std::string & strData , tsize out_len , const tchar *szMethod = ""  )
	{
		return dseal( strData.c_str(), SStrf::slen( strData.c_str() ) , out_len , szMethod );
	}


	static std::string dseal( const tchar *s, tsize len, tsize out_len, const tchar *szMethod = "" )
	{
		// 指定目标长度 十进制数字摘要 dseal V1.0
		tuint32 i, j;
		tchar *t, *t0;
		std::string strOut("");
		if(!s||/*!len||*/!out_len||!szMethod) return "";
		for(j=len+out_len,i=0;;i++)
		{
			j = ++j + chksum(s, len) + chksum(szMethod,SStrf::slen(szMethod));
			j = ++j * chksum(strOut.c_str(),(tsize)strOut.size()) * (len^10) * out_len ; 
			j = 0x7FffFFff & (j ^ (~j * ~i + (len ^ out_len)) * (~j+~j*~i+~i));
			strOut += SStrf::sltoa(j);
			if( out_len+11 < strOut.size() ) break ;
		}
		t0 = t = (tchar*)SStrf::smalloc( (tsize)strOut.size()+1 );
		if(!t) return "";
		SStrf::scpy( t, strOut.c_str() );
		SStrf::srev(t);
		if(*t=='0') t++;		 
		t[out_len] = 0;
		strOut=t;
		SStrf::sfree(t0);
		return strOut;
	}


	
	static tuint32 chksum( const tchar *s, tsize len)
	{
		tuint32 j=0;
		if(SStrf::slen(s)==0)
			return 0;
		while(len--)
		{
			j += (tuint8)s[len]+(len+1);
			j &= 0x7FffFFff;
		}
		return j;
	}



	static tchar * xorB( tchar * Src, tsize len, tuint8 x )
	{
		tsize i;
		tuint8 *s=(tuint8 *)Src;
		if( !s || !len ) return (tchar*)s;
		for(i=0;i<len;i++) s[i] ^= x;
		return (tchar*)s;
	}


}; //end class SCalc





X011_NAMESPACE_END

#endif





/*
string
vector string
*/

#ifndef X011__H_w_sstrvs_h
#define X011__H_w_sstrvs_h



X011_NAMESPACE_BEGIN



class SStrvs
{

public:

	//SStrvs(){;} 

	virtual ~SStrvs(){;}

	
	template < class StrT > /* for string or wstring*/
	static tsize vsa_impbylen( const StrT & strsource, typename StrT::size_type ilen, std::vector<StrT> & vecrtn )
	{
		StrT s1(strsource);
		typedef typename StrT::size_type sizetypeB;

		while( !s1.empty() )
		{
			sizetypeB i = ilen <= s1.size() ? ilen : s1.size();
			StrT s2 = s1.substr( 0, i );
			vecrtn.push_back(s2);
			s1.erase( 0, i );
		}
		return (tsize)vecrtn.size();
	}




	//

	template < class StrT > /* for string or wstring*/
	static tsize vsa_imp( const StrT & ssource, const StrT & ssep, tbool istoken, std::vector<StrT> & rtnlst )
	//static tsize vsa_imp( const StrT & ssource, StrT ssep, tbool istoken, std::vector<StrT> & rtnlst )
	{
		std::vector<tint32> vAbuf, vBbuf;
		tint32  ltmpn,ltmpm,ltmpi,ltmpj,ltmpk, ltmpb1, ltmpb2;
		typedef typename StrT::size_type sizetypeB;
		sizetypeB ssti;

		ltmpm = ltmpi = ltmpj = 0;
		ltmpn = (tint32)ssource.size();
		ltmpk = (tint32)ssep.size();

		do //fakedo
		{
			if(ltmpk==0)
			{
				rtnlst.push_back(ssource);
				break;
			}

			do 
			{
				if(ltmpm>=ltmpn) break;
				ssti = ssource.find( ssep, ltmpm ); //the knl. find() return from 0 on.
				if(ssti==StrT::npos) break;
				ltmpi = (tint32)ssti;
				ltmpm = ltmpi;

				vAbuf.push_back(ltmpi);  
				ltmpj ++;
				ltmpm += ltmpk;

			} while(1);

			ltmpb1 = 0 ; // lowerbound(vAbuf) 
			ltmpb2 = ltmpj - 1 ; // upperbound(vAbuf)

			ltmpj = 0;
			vBbuf.push_back(ltmpj);
			for(ltmpi=ltmpb1;ltmpi<=ltmpb2;ltmpi++){
				ltmpj = vAbuf[ltmpi];
				vBbuf.push_back(ltmpj);
				vBbuf.push_back(ltmpj+ltmpk);
			}
			vBbuf.push_back( ltmpn );

			ltmpj = (tint32)vBbuf.size();
			for(ltmpi=0;ltmpi<ltmpj;ltmpi+=2)
			{
				ltmpm = vBbuf[ltmpi];
				ltmpn = vBbuf[ltmpi+1];
				ltmpk = ltmpn - ltmpm;

				if(istoken&&ltmpk==0){
					;
				}else
					rtnlst.push_back( ssource.substr( ltmpm, ltmpk ) ); //the knl. substr(pos{suffix},len)

			}
			
		}while(0);

		return (tsize)rtnlst.size();//vector size目前已经被占用了的位置个数。
	}


	template < class StrT > /* for string or wstring*/
	static tsize vsa_hm( const StrT & ssource, const StrT & ssep, tbool istoken )
	{
		return vsa_imp( ssource, ssep, istoken, std::vector<StrT>() );
	}

	
	//iwhich is suffix. from 0 on.
	template < class StrT > /* for string or wstring*/
	static StrT vsa_get( const StrT & ssource, const StrT & ssep, tbool istoken, tsize iwhich )
	//static StrT vsa_get( const StrT & ssource, StrT ssep, tbool istoken, tsize iwhich )
	{
		std::vector<StrT> tmplst;
		if( iwhich<vsa_imp( ssource, ssep, istoken, tmplst ) )
			return tmplst[iwhich];
		else
			return StrT();
	}

	template < class StrT >  
	static StrT vsa_get( const StrT & ssource, const typename StrT::value_type *ssep, tbool istoken, tsize iwhich )
	{
			return vsa_get( ssource,  StrT(ssep),  istoken,  iwhich );
	}
	

	//2V get
	/* the para have 3 parts. 1=the source. 2=settings. 3=the coordinate */
	template < class StrT > 
	static StrT vsa2v_get( const StrT & ssource, 

						  const StrT & ssepTR,
						  tbool		istokenTR,
						  const StrT & ssepTD,
						  tbool		istokenTD,

						  tsize iwhichTR,  tsize iwhichTD		)

	{
		std::vector<StrT> tmplst1, tmplst2;
		if( iwhichTR<vsa_imp( ssource, ssepTR, istokenTR, tmplst1 ) )
		{
			if( iwhichTD<vsa_imp( tmplst1[iwhichTR], ssepTD, istokenTD, tmplst2 ) )
				return tmplst2[iwhichTD];
		}
		return StrT();
	}


	//2V prpt
	/*   */
	template < class StrT > 
	static std::map<StrT,StrT> & vsa2v_prpt( const StrT & ssource, 
											 const StrT & ssepTR,
											 const StrT & ssepTD, 
											 std::map<StrT,StrT> & mapRtn	)
	{
		std::vector<StrT> vecTmpTR, vecTmpTD;
		typedef typename std::vector<StrT>::iterator iteratortypeB;
		iteratortypeB itTR;
		vsa_imp( ssource, ssepTR, 1, vecTmpTR );
		for( itTR = vecTmpTR.begin(); itTR!=vecTmpTR.end(); ++itTR)
		{
			vsa_imp( *itTR, ssepTD, 1, vecTmpTD );
			vecTmpTD.push_back( StrT() );
			vecTmpTD.push_back( StrT() );
			mapRtn.insert( std::pair<StrT,StrT>( vecTmpTD[0], vecTmpTD[1] ) );
			vecTmpTD.clear();
		}
		return mapRtn;
	}


};//end class SStrvs





X011_NAMESPACE_END

#endif






/*
set operation
*/

#ifndef X011__H_w_SSetu_h
#define X011__H_w_SSetu_h



X011_NAMESPACE_BEGIN



class SSetu
{

public:

	//SSetu(){;} 

	virtual ~SSetu(){;}
	

	//all containers must have same element type.
	template < class CntnrT, class ELET >
	static tsize vs_setch( CntnrT &vset1, CntnrT &vset2, std::vector<ELET> &rtnlst )
	{
		typedef typename CntnrT::iterator iteratortypeB;
		iteratortypeB it1, it2;
		tsize i;
		i=0;
		for( it1=vset1.begin(); it1!=vset1.end(); it1++)
		{
			it2 = std::find( vset2.begin(), vset2.end(), *it1 );
			if( it2 == vset2.end() ) //can't find in set2 then means only in set1
			{
				rtnlst.push_back( *it1 );
				i++;
			}
		}
		return i;
	}


	//all containers must have same element type.
	template < class CntnrT, class ELET >
	static tsize vs_setj( CntnrT &vset1, CntnrT &vset2, std::vector<ELET> &rtnlst )
	{
		typedef typename CntnrT::iterator iteratortypeB;
		iteratortypeB it1, it2;
		tsize i;
		i=0;
		for( it1=vset1.begin(); it1!=vset1.end(); it1++)
		{
			it2 = std::find( vset2.begin(), vset2.end(), *it1 );
			if( it2 != vset2.end() ) //can find in set2 then means both in 2 sets
			{
				rtnlst.push_back( *it1 );
				i++;
			}
		}
		return i;
	}


	//first 2 containers must have same element type.
	template < class CntnrT, class ELET >
	static tsize vs_setgroup( const CntnrT & vsource, std::vector<ELET> & rtncontent, std::vector<int> & rtnsubsum )
	{
		CntnrT v2, v3; //same as the source type
		typedef typename CntnrT::iterator iteratortypeB;
		iteratortypeB  it1,  itNewEnd2;
		int i;

		v2 = vsource;
		std::sort( v2.begin(), v2.end() );
		v3 = v2;

		itNewEnd2 = std::unique( v2.begin(), v2.end() );

		for( it1=v2.begin(); it1!=itNewEnd2; it1++)
		{
			rtncontent.push_back( *it1 );
			i = (int)std::count( v3.begin(), v3.end(), *it1 );
			rtnsubsum.push_back(i);
		}
		return (tsize)v2.size();
	}


	template < class CntnrT, class ELET >
	static tsize vs_setgroup( const CntnrT & vsource, std::vector<ELET> & rtncontent )
	{
		std::vector<int> v;
		return vs_setgroup( vsource, rtncontent, v );
	}


	template < class ELET >
	static tsize vs_setgroup( std::vector<ELET> & _a_content )  //用本身返回
	{
		std::vector<ELET> _a_aa1;
		tsize i = vs_setgroup( _a_content, _a_aa1 );
		_a_content = _a_aa1;
		return i;
	}





	template < class ELET >
	static ELET & vs_groupbig( std::vector<ELET> & memo, std::vector<int> & subsum )
	{
		typedef typename std::vector<ELET>::iterator iteratortypeB;
		iteratortypeB it1;
		std::vector<int>::iterator it2, it3;
		int i;

		i=0;
		for( it3=it2=subsum.begin(); it2!=subsum.end(); ++it2)
		{
			if( *it2>i )
			{
				i = *it2;  //keep the best val
				it3 = it2; //keep the best pos
			}
		}

		it1 = memo.begin() + ( it3 - subsum.begin() );
		return *it1;
	}


	template < class ELET >
	static ELET & vs_groupsmall( std::vector<ELET> & memo, std::vector<int> & subsum )
	{
		typename std::vector<ELET>::iterator it1;
		std::vector<int>::iterator it2, it3;
		int i;

		i=0;
		for( it3=it2=subsum.begin(); it2!=subsum.end(); ++it2)
		{
			if( *it2<i || i==0 )
			{
				i = *it2;  //keep the best val
				it3 = it2; //keep the best pos
			}
		}

		it1 = memo.begin() + ( it3 - subsum.begin() );
		return *it1;
	}


	//删除最旧的重复项
	template < class ELET >
	static void StableDelOld( std::vector<ELET> & v )
	{
		for( typename std::vector<ELET>::iterator it = v.begin(); it != v.end(); )
		{
			typename std::vector<ELET>::iterator it2;

			it2 = it + 1;

			if( std::find( it2, v.end(), *it ) != v.end() )
			{
				//found
				v.erase( it );
				it = v.begin();
			}
			else
				++it;
		}
	}


	//删除 指定的 重复项
	template < class CNTNRT, class ELET >
	//static void StableDel( CNTNRT & v , const ELET & val )
	static void StableDel( CNTNRT & v , ELET val )
	{
		for( typename CNTNRT::iterator it = v.begin(); it != v.end(); )
		{
			if( *it == val )
			{
				//found
				v.erase( it );
				it = v.begin();
			}
			else
				++it;
		}
	}

};//end SSetu





X011_NAMESPACE_END

#endif






/*
cake, cakel
provide raw memory
*/

#ifndef X011__H_w_scake_h
#define X011__H_w_scake_h




X011_NAMESPACE_BEGIN



template < class CT >
class SCake_base
{
public:
	typedef /*typename*/ CT CkEle_t;

private:

	CT		*m_pbuf; 
	tsize	m_mysize; //元素个数，不是字节数。 it is not byte num, it is num of ele.

	mutable std::vector<CT>  m_FastAppendBuf;

private:

	void init(void) { 	m_pbuf=NULL; 	m_mysize=0; }

	void freeall(void)
	{
		if(m_pbuf) delete [] m_pbuf;
		m_mysize=0;
		init();
	}

public:

	SCake_base() {  init(); }
	
	SCake_base( const SCake_base<CT> & cakesource )
	{
		init(); 
		let(cakesource);
	}

	SCake_base( CT c ) { init(); let(&c,1); }

	SCake_base( const CT *psource, tsize isize ) { init(); let(psource,isize); }

	SCake_base( const tchar *psource ) { init(); lets(psource); } //for char* only

	SCake_base( const std::string & s) { init(); lets(s); } //for char* only


	virtual ~SCake_base( ) { freeall(); }


	//static std::string & trim( std::string & strCell, const tchar *str_space="\r\n \t" ) // double trim
	//{
	//	SCake ckCell;
	//	ckCell.lets( strCell );
	//	SStrf::strim( ckCell, str_space );
	//	return strCell = ckCell;
	//}

	//static std::string & trim( std::string & strCell, const tchar *str_space="\r\n \t" ) // double trim
	//{
	//	return wl::SStrf::strim( strCell );
	//}


	void copybuf( const CT *psource, CT *pdest, tsize isize, toffset iDestOffsetWhere = 0 )
	{
		if( psource == pdest && iDestOffsetWhere == 0 ) return;//think about c=c c.let(c) , same obj operations

		if( psource && pdest && isize )
		{
			for( tsize jtmp=iDestOffsetWhere; jtmp<isize+iDestOffsetWhere; jtmp++ )
				pdest[jtmp] = psource[jtmp-iDestOffsetWhere]; 
		}
	}
	

	void redim( tsize iNewSize, tbool reserve=0 )
	{
		if( iNewSize <= len() && iNewSize > len()/2 )
		{
			m_mysize = iNewSize;
		}
		else
		{
			CT *lbuf;
			if(iNewSize==0)
			{
				freeall();
				return;
			}
			lbuf = new CT[iNewSize] ;
			if(reserve) copybuf( m_pbuf, lbuf, iNewSize<m_mysize?iNewSize:m_mysize );
			freeall();
			m_pbuf = lbuf;
			m_mysize = iNewSize;
		}
	}

	const CT * buf_const() const
	{
		//FastAppendEnd();

		return m_pbuf;
	}


	CT * buf()
	{
		FastAppendEnd();

		return m_pbuf;
	}

	tsize len() const
	{ 
		return m_mysize;
	}

	void let( const CT *psource, tsize isize ) //knl
	{
		FastAppendEnd();

		redim(isize);
		copybuf( psource, m_pbuf, isize );
	}


	void let( const SCake_base<CT> & cakesource ) 
	{
		let( cakesource.buf_const(), cakesource.len() );
	}


	void lets( const CT *psource, CT c00 )
	{
		tsize i;
		const CT *p2;
		for(i=1,p2=psource;*p2!=c00;p2++)
			i++; //the c00 occupy one room. it is belong to data.
		let( psource, i );
	}


 	void lets( const tchar *psource ) //knl
	{
		if(psource)
		{
			redim( SStrf::slen(psource) + 1 );
			tsize jtmp;
			for( jtmp=0; psource[jtmp]; jtmp++ )
			{
				m_pbuf[jtmp] = psource[jtmp];
			}
			m_pbuf[jtmp] = 0;//the c00 occupy one room. it is belong to data.
		}
	}


	void lets( const std::string & s) { lets(s.c_str()); }

	void lets( tint32 i)  { lets( SStrf::sltoa(i) ); }

	void lets( tdouble d) { lets( SStrf::sftoa(d) ); }

	SCake_base<CT> & dump( SCake_base<CT> & cake2 ) //dump head part into cake2. keep the remaining(right part)
	{
		tsize iGoneSize;
		cake2.let( buf(), iGoneSize = ( len() < cake2.len() ? len() : cake2.len() ) ); // len()-iGoneSize= remain size or 0.
		SCake_base<CT> * ptmpcake = new SCake_base<CT>(*this);
		let( ptmpcake->buf() + iGoneSize, len() - iGoneSize );
		delete ptmpcake;
		return cake2;
	}


	SCake_base<CT> & cut( tsize howmany ) //cut off the right part. keep and return the left part.
	{
		if( howmany<=m_mysize) m_mysize -= howmany;
		else m_mysize = 0;
		return *this;
	}


	
	SCake_base<CT> & FastAppend( const SCake_base<CT> & cake2 ) // append into temp buf, refresh later
	{
		if( !this->m_pbuf ) return this->append(cake2);

		if(cake2.len()==0)
		{
			return *this;
		}

		this->m_mysize += cake2.len();
		std::copy( cake2.buf_const(), cake2.buf_const() + cake2.len(), std::back_inserter(m_FastAppendBuf) ); 

		return *this;
	}

	void FastAppendEnd()  
	{
		if( m_FastAppendBuf.empty() ) return;

		std::vector<CT>  FastBuf2(m_FastAppendBuf);

		m_FastAppendBuf.clear(); // append will call let() or buf(), which will call me again. clear to prevent it
		this->m_mysize -= (tsize)FastBuf2.size();
		this->append( &(FastBuf2[0]), (tsize)FastBuf2.size() );
	}



	SCake_base<CT> & append( const SCake_base<CT> & cake2 ) //bin style append 
	{
		if(cake2.len()==0)
		{
			//
		}
		else
		{
			CT *lbuf1;
			const CT *lbuf2;
			tsize len1,len2;
			lbuf1 = buf();
			lbuf2 = cake2.buf_const();
			len1 = len();
			len2 = cake2.len();
			redim( len1+len2, 1 );
			copybuf( lbuf2, buf(), len2, len1 );
		}
		return *this;
	}

	SCake_base<CT> & append( const CT *psource, tsize isize )
	{
		if( isize==0 || !psource )
		{
			//
		}
		else
		{
			CT *lbuf1;
			const CT *lbuf2;
			tsize len1,len2;
			lbuf1 = buf();
			lbuf2 = psource;
			len1 = len();
			len2 = isize;
			redim( len1+len2, 1 );
			copybuf( lbuf2, buf(), len2, len1 );
		}
		return *this;
	}

	SCake_base<CT> & append( CT val )
	{
		return append( &val, 1 );
	}


public:	//operators

	/*
	如果有
	class B {...}
	class D : public B {...}
	那，在D中显式调用B的operator =的方法是：
	D& operator = (const D& rhs) {
		this->B::operator =(rhs);  // 或者也可以写*static_cast<B*>(this) = *static_cast<const B*>(&rhs);
		// ...
		return *this;
	}*/

	SCake_base<CT> & operator = ( const SCake_base<CT> & cake2 )
	{
		let(cake2);
		return *this;
	}


	operator CT * ( )
	{
		return buf();
	}

    
	operator const CT * ( ) const
	{
		return buf_const();
	}

	int operator < ( const SCake_base<CT> & cake2 ) const
	{
		return ( (int)buf_const() < (int)cake2.buf_const() );
	}


}; //end of class SCake_base declare




////////////////////////////////////////////////////////////////////////////////
//a cake for tchar 

class SCake : public SCake_base<tchar>
{

public:
	
	SCake():SCake_base<tchar>( ) { }

	SCake(const SCake & ckSrc):SCake_base<tchar>( ckSrc ) {  }


	SCake(const SCake_base<tchar> & ckSrc):SCake_base<tchar>( ckSrc ) {  }

	SCake( tchar c ):SCake_base<tchar>( c ) {  }
	//wl::tuint8 cu;
	//cu = 0xff;
	//wl::SCake ck( cu );

	SCake(const tchar * psrc, tsize isize):SCake_base<tchar>( psrc, isize ) {  }

	SCake(const tchar *psrc):SCake_base<tchar>( psrc ) {  }

	SCake(const std::string & s):SCake_base<tchar>( s) { } 


	SCake & bs_en()
	{
		SCake *pck = new SCake;
		pck->redim( SStrf::bs_ensize( buf(), len() ) );
		SStrf::bs_en( buf(), len(), pck->buf() );
		*this = *pck;
		delete pck;
		return *this;
	}


	SCake & bs_de() //如果传入的bstr==""则bs_de()之后本CAKE变为NULL指针的长度为0的一个CAKE。
	{
		tsize iDatalen = SStrf::bs_desize( buf() );
		SStrf::bs_de( buf() );
		redim( iDatalen, 1 );
		return *this;
	}


	tchar * mk_sz()
	{
		append( SCake("") );
		return buf();
	}

	std::string & mk_str( std::string & strOut ) const
	{
		if( this->len() )
		{
			return strOut = std::string( this->buf_const(), this->len() );
		}
		return strOut = "";
	}

	std::string mk_str() const
	{
		std::string s1;
		return mk_str(s1);
	}




public:	//operators

	SCake & operator = ( const SCake & cake2 )
	{
		let(cake2);
		return *this;
	}



}; //end of class SCake  






///////////////////////////////////////////////////////////////////////////////
template < class cakeT, class CT >
class SCakel_base2 {

private:

	std::vector<cakeT *> m_vknl;

	void collect( tbool szstyle=1 ) //if szstyle, don't record middle sz00. record the last sz00 ofcourse
	{
		cakeT  * psc;
		tsize wholesize,copypoint;
		typename std::vector<cakeT *>::iterator it;
		for( wholesize=0,it=m_vknl.begin(); it!=m_vknl.end(); ++it )
		{
			wholesize += (*it)->len( );
			if(szstyle&&(*it)->len( )) wholesize--;
		}
		if(szstyle) wholesize++;
		psc = new cakeT ;
		psc->redim(wholesize);
		for( copypoint=0,it=m_vknl.begin(); it!=m_vknl.end(); ++it )
		{
			psc->copybuf( (*it)->buf(), psc->buf(),	(*it)->len(), copypoint );
			copypoint += (*it)->len();
			if(szstyle) copypoint--;
		}
		clean( );
		m_vknl.push_back( psc );
	}


private:

	SCakel_base2( const SCakel_base2 & ckl )
	{
		;
	}

public:

	SCakel_base2( ) { ; }

	virtual ~SCakel_base2( )
	{
		for( typename std::vector<cakeT *>::iterator it=m_vknl.begin();it!=m_vknl.end();++it)
			delete *it;
	} //this method doesn't destruct m_vknl, so faster.


	tsize hm(void) const
	{
		return (tsize)m_vknl.size();
	}


	std::vector<cakeT *> & knl( ) {
		return m_vknl;
	}


	cakeT  * get( tsize iwhere ) const
	{
		return ( hm( )==0 || iwhere>=hm( ) )?NULL:m_vknl[iwhere];
		//don't use & because user can modi the static obj. 
		//if clear the static obj every time then can't used in multi-thread env.
	}


	cakeT  * get( ) const 
	{
		return get( hm( )-1 );
	}


	cakeT  * get0( )
	{
		return get(0);
	}


	void add( const cakeT  & cakesource, tsize iwhere )
	{
		cakeT  * psc;
		psc = new cakeT ( cakesource );
		if(iwhere>hm()) iwhere=hm();
		m_vknl.insert( m_vknl.begin()+iwhere, psc );
	}


	void add( const cakeT  & cakesource )
	{
		cakeT  * psc;
		psc = new cakeT ( cakesource );	//psc->let( cakesource.buf(), cakesource.len() );
		m_vknl.push_back( psc );
	}


	void add0( cakeT  & cakesource ) { add(cakesource,0); }


	void del( tsize iwhere )
	{
		typename std::vector<cakeT *>::iterator it;
		if( !( hm( )==0 || iwhere>=hm( ) ) )
		{
			it = m_vknl.begin( ) + iwhere;
			delete *it;
			m_vknl.erase( it );
		}
	}

	void del()  { del(hm()-1); }

	void del0() { del(0); }


	void clean()
	{
		tsize iremain = 0;
		while( hm() > iremain )
			del();
	}

	void clean( tsize iremain )
	{
		while( hm() > iremain )
			del();
	}


	void clean0( tsize iremain = 0 )
	{
		while( hm() > iremain )
			del0();
	}

	void collectb( ) { collect(0); }

	void collects( ) { collect(1); }


	
	void scatter( const cakeT  & ckSrc , CT cSepC )//see cake, scatter it and append
	{
		tsize p1,p2;
		cakeT  ckTmp;
		for(p1=p2=0;p2<ckSrc.len();p2++)  
		{
			if( *(ckSrc+p2)==cSepC )
			{
				ckTmp.let( ckSrc+p1, p2-p1+1 );
				add( ckTmp );
				p1=p2+1;
			}
		}

		//see the last time, whether successed.
		if(p2) //if the for above runed at least once
		{
			p2--;
			if( *(ckSrc+p2)!=cSepC )
			{
				ckTmp.let( ckSrc+p1, p2-p1+1 );
				ckTmp.append( cakeT ( &cSepC,1 ) );
				add( ckTmp );
			}
		}
	}


	void scatter( CT cSepC=0 )// 
	{
		do //fakedo
		{
			if(hm()>1)
				collectb();

			if(hm()==0)
				break;

			scatter( *get0() , cSepC );

			del0();

		}while(0);
	}


	SCakel_base2<cakeT,CT> & append( const SCakel_base2<cakeT,CT> & cakel2 )
	{
		tsize len2,lcount;
		len2 = cakel2.hm();
		for(lcount=0;lcount<len2;lcount++)
		{
			add( *(cakel2.get(lcount)) );
		}
		return *this;
	}
	

public: //operators


	operator std::vector<cakeT *> & ( )
	{
		return knl( );
	}


	SCakel_base2<cakeT,CT> & operator = ( const SCakel_base2<cakeT,CT> & cakel2 )
	{
		clean();
		return append(cakel2);
	}


};
//end of class cakel_base2





/////////////////////////////////////////////////////////////////////////////////

template < class CT >
class SCakel_base : public SCakel_base2<  SCake_base<CT>, CT >
{
private:

	SCakel_base( const SCakel_base & ckl )
	{
		;
	}

public: 

	SCakel_base( ) { ; }


public: //operators

	SCakel_base<CT> & operator = ( const SCakel_base<CT> & cakel2 )
	{
		SCakel_base2<  SCake_base<CT>, CT >::clean();		
		return append(cakel2);
	}

};





//////////////////////////////////////////////////////////////////////////////////

//typedef SCake_base<tchar> SCake;

class SCakel : public SCakel_base2< SCake, tchar > 
{
private:

	SCakel( const SCakel & ckl )
	{
		;
	}

public:

	SCakel( ) { 	}

public:

	SCakel & append( const SCakel & cakel2 )
	{
		tsize len2,lcount;
		len2 = cakel2.hm();
		for(lcount=0;lcount<len2;lcount++)
		{
			add( *(cakel2.get(lcount)) );
		}
		return *this;
	}

public: //operators

	SCakel & operator = ( const SCakel & cakel2 )
	{
		clean();
		return append(cakel2);
	}

};






X011_NAMESPACE_END

#endif




/*
date, time, event
universal arithmetic
*/

#ifndef X011__H_w_sdte_h
#define X011__H_w_sdte_h




X011_NAMESPACE_BEGIN



class SDte
{
// id/od  it/ot  ie/oe

public:

	int m_year;
	int m_mon;
	int m_day;
	int m_hour;
	int m_min;
	int m_sec;
	//int m_msec;

private:

	static tbool d_is_leap_year(int y)
	{
		return y%400==0||y%4==0&&y%100!=0;
		/*If n Mod 400 = 0 Or (n Mod 4 = 0 And n Mod 100 <> 0) Then yes */
	}


	static int d_day_of_year(int y)
	{
		return d_is_leap_year(y)?366:365;
	}


	static int d_day_of_month(int y, int m)
	{
		tint8 Array[]={0, 31, 28, 31,30,31,30,31,31,30,31,30,31};
		if(m<1||m>12) m=1;
		return (int)(m==2 ? Array[m] + (d_is_leap_year(y)?1:0) : Array[m]);
	}


	static tchar * d_odget( SCakel_base<tchar> & abuf, tint32 od )
	{
		abuf.add( SCake_base<tchar>("000000000") );
		if(od<0) od *= -1;
		abuf.add( SCake_base<tchar>( SStrf::sltoa(od) ) );
		abuf.collects( );
		return abuf.get( )->buf( );
	}


	//now->l
	static time_t dt_mk(void)  
	{
		struct tm tmm, *tp;
		time_t timer;
		time(&timer);
		tp = (*SClib::p_localtime())(&timer);//struct tm *localtime( const time_t *timer );
		memcpy(&tmm, tp, sizeof(struct tm));
		return mktime(&tmm);
	}


	// l->t
	static int dt_mk( struct tm *ptm , time_t tmr)
	{
		struct tm *tp;
		tp = (*SClib::p_localtime())(&tmr);
		if(ptm!=NULL&&tp!=NULL) memcpy(ptm, tp, sizeof(struct tm));
		return tp!=NULL;	 
	}


	// l->s
	static void dt_mknow( int& y, int&m, int& d, int& hh, int& mi, int& ss ) //standard chg interface!!!
	{
		struct tm tmm;
		struct tm *tp;
		memset(tp=&tmm, 0, sizeof(struct tm));
		dt_mk(tp, dt_mk());
		y = tp->tm_year+1900;
		m = tp->tm_mon+1;
		d = tp->tm_mday;
		hh = tp->tm_hour;
		mi = tp->tm_min;
		ss = tp->tm_sec;
	}

	///////////////////////////////////////
	

	static struct tm & RegulateTmYear4( struct tm & t )
	{
		if( t.tm_year <= 999 )
		{
			t.tm_year += 1900;
		}
		return t;
	}

	static struct tm & RegulateTmYear2( struct tm & t )
	{
		if( t.tm_year > 1900 )
		{
			t.tm_year -= 1900;
		}
		return t;
	}


	static struct tm & Now( struct tm & t )
	{
		struct tm *tp;
		memset(tp=&t, 0, sizeof(struct tm));
		dt_mk(tp, dt_mk());
		tp->tm_year+=1900;
		return t;
	}


		
	//tm->l
	static time_t tm2l( struct tm t )
	{
		RegulateTmYear2(t);

		return mktime(&t);	//time_t mktime( struct tm *timeptr );
	}


	//l->tm
	static struct tm l2tm( time_t tmr )
	{
		struct tm *tp;
		struct tm tm2;

		SStrf::smemset(&tm2);

		//tp = localtime(&tmr);
		tp = (*SClib::p_localtime())(&tmr);

		if(tp!=NULL) memcpy(&tm2, tp, sizeof(struct tm));

		return tm2;	 
	}



	static tint32 idmk( const tchar * sDateTime )
	{
		if(!sDateTime) return 0;
		int y, m, d;
		(*SClib::p_sscanf())( sDateTime, "%d-%d-%d", &y, &m, &d );
		return idmk(y,m,d);
	}


	static tint32 idmk(int y, int m, int d, tint32 offset=0)//参数说明：年、月、日、偏移量日(正数为未来)
	{
		tint32 i,j;
		for(j=0,i=0;i<=(y-1);i++) j += d_day_of_year(i);
		for(i=1;i<=(m-1);i++) j += d_day_of_month(y,i); 
		return j = j + d + offset;
	}


	static int odgety( tint32 od )
	{
		tchar *t;
		SCakel_base<tchar> abuf;
		t = d_odget( abuf, od );
		t = SStrf::splast(t,3);
		*t=0; 
		return (int)SStrf::satol(t-4);
	}


	static int odgetm( tint32 od )
	{
		tchar *t;
		SCakel_base<tchar> abuf;
		t = d_odget( abuf, od );
		t = SStrf::splast(t,1);
		*t=0; 
		return (int)SStrf::satol(t-2);
	}


	static int odgetd( tint32 od )
	{
		tchar *t;
		SCakel_base<tchar> abuf;
		t = d_odget( abuf, od );
		t = SStrf::splast(t,0);
		return (int)SStrf::satol(t-1);
	}


	static tint32 id2o( tint32 id )
	{
		tint32 i1, i2, i3, i4;
		if(id<=0) 	 id=1;
		for(i1=0;id>d_day_of_year(i1);) {
			id -= d_day_of_year(i1);
			i1++;
		}
		for(i2=1;id>d_day_of_month(i1,i2);) {
			id -= d_day_of_month(i1,i2);
			i2++;
		}
		i3 = id;
		return i4 = 10000*i1 + 100*i2 + i3;
	}


	static tint32 od2i( tint32 od )
	{
		return idmk( odgety(od), odgetm(od), odgetd(od) );
	}


	static int idgety( tint32 id ) { return odgety( id2o(id) ); }

	static int idgetm( tint32 id ) { return odgetm( id2o(id) ); }

	static int idgetd( tint32 id ) { return odgetd( id2o(id) ); }

	static tint32 idnow( ) { int y,m,d,hh,mi,ss; dt_mknow(y,m,d,hh,mi,ss); return idmk(y,m,d); }

	static tint32 odnow( ) { return id2o(idnow()); }


	///////////////////////////////////////////////////////////////////////

	static tint32 itmk( const tchar * sDateTime )
	{
		if(!sDateTime) return 0;
		int h, m, s, i;
		(*SClib::p_sscanf())( sDateTime, "%d-%d-%d %d:%d:%d", &i, &i, &i, &h, &m, &s );
		return itmk(h, m, s);
	}

	
	static tint32 itmk(int h, int m, int s) 
	{
		return h*60*60+m*60+s;
	}

	static tint32 itgeth(tint32 it)		{	return it/3600; 	}

	static tint32 itgetm(tint32 it)		{	return it%3600/60; 	}

	static tint32 itgets(tint32 it)		{	return it%60;	}


	static tint32 it2o(tint32 it)
	{
		tchar s[7];
		(*SClib::p_sprintf())( s, "%02d%02d%02d", itgeth(it), itgetm(it), itgets(it) );
		return SStrf::satol(s);
	}


	static tint32 ot2i(tint32 ot)
	{
		SCake_base<tchar> ca("000000", 6);
		ca.append( SCake_base<tchar>(SStrf::sltoa(ot)) );
		int h,m,s;
		(*SClib::p_sscanf())( SStrf::splast(ca.buf(), 5), "%2d%2d%2d", &h,&m,&s);
		return itmk(h,m,s);	
	}


	static tint32 itnow( ) { int y,m,d,hh,mi,ss; dt_mknow(y,m,d,hh,mi,ss); return itmk(hh,mi,ss); }

	static tint32 otnow( ) { return it2o(itnow()); }

	static tdouble iemk( tint32 id, tint32 it) { return  id + (tdouble)it/(tdouble)86400; }


	static tdouble ie2o( tint32 id, tint32 it)
	{
		tint8 s[16];
		(*SClib::p_sprintf())(s, "%ld.%06ld", id2o(id), it2o(it) ); 
		return SStrf::satof(s);
	}

	static tdouble ie2o(tdouble ie)
	{
		tdouble d1, d2;
		d1 = floor(ie);
		d2 = 0.5 + ( (ie - floor(ie)) * 86400 ) ; 
		return ie2o((tint32)d1, (tint32)d2);
	}


	static tdouble oe2i(double oe)//return ie
	{
		tdouble od, ot;
		od = floor(oe);
		ot = 0.5 + ( (oe - floor(oe)) * 1e6 ) ;
		return iemk( od2i((tint32)od), ot2i((tint32)ot) );
	}


	static tdouble ienow()
	{
		return iemk( idnow(), itnow() );
	}

	
	static tdouble oenow() 
	{ 
		return ie2o( ienow() ); 
	}


	
	static std::string Db_oe( tint32 idNow=0, tint32 itNow=-1 ) //2008-02-13 15:22:33
	{
		if(idNow==0 ) idNow=idnow();
		if(itNow==-1) itNow=itnow();
		tchar sBuf[33];
		(*SClib::p_sprintf())(sBuf,"%d-%02d-%02d %02d:%02d:%02d",
					 idgety(idNow), idgetm(idNow), idgetd(idNow),  
					 itgeth(itNow), itgetm(itNow), itgets(itNow)	);
		return sBuf;
	}


	static std::string Pack_oe( tint32 idNow=0, tint32 itNow=-1 ) //20080213.152233
	{
		if(idNow==0 ) idNow=idnow();
		if(itNow==-1) itNow=itnow();
		return  SStrf::sftoa( ie2o( iemk( idNow, itNow ) ) );
	}



public:

	SDte()
	{
		m_year= 0;
		m_mon= 0;
		m_day= 0;
		m_hour= 0;
		m_min= 0;
		m_sec= 0;
		//m_msec= 0;
	}

	SDte( std::string str_dte )
	{
		if(str_dte=="") this->MakeNow();
		else
			Make( str_dte );
	}

	SDte( int iHour, int iMin, int iSec )
	{
		this->MakeNow();
		this->m_hour= iHour;
		this->m_min= iMin;
		this->m_sec= iSec;
	}

	virtual ~SDte() { ; }


	static double e_proctime()  //return seconds.
	{
		return (double)clock()/(double)CLOCKS_PER_SEC;
	}



	SDte & Make( std::string str_dte )
	{
		if( str_dte.find( "-" ) != std::string::npos && str_dte.find( ":" ) != std::string::npos ) // datetime
		{
			(*SClib::p_sscanf())( str_dte.c_str(), "%d-%d-%d %d:%d:%d", &m_year, &m_mon, &m_day, &m_hour, &m_min, &m_sec );
			return *this;
		}

		if( str_dte.find( "-" ) != std::string::npos && str_dte.find( ":" ) == std::string::npos ) // date
		{
			(*SClib::p_sscanf())( str_dte.c_str(), "%d-%d-%d", &m_year, &m_mon, &m_day );
			m_hour = 	m_min = m_sec = 0;
			return *this;
		}

		if( str_dte.find( "-" ) == std::string::npos && str_dte.find( ":" ) != std::string::npos ) // time
		{
			(*SClib::p_sscanf())( str_dte.c_str(), "%d:%d:%d", &m_hour, &m_min, &m_sec );
			m_year = m_mon  = 	m_day  =0;
			return *this;
		}

		tint32 oiid, oiit;

		if( str_dte.find( " " ) != std::string::npos ) //see od and ot
		{
			oiid = (tint32)SStrf::satol( SStrvs::vsa_get( str_dte, std::string(" "), 1, 0 ) );
			oiit = (tint32)SStrf::satol( SStrvs::vsa_get( str_dte, std::string(" "), 1, 1 ) );
		}
		else
		{
			oiid = (tint32)SStrf::satol( str_dte );
			oiit = 0;
		}
	
		oiid = this->od2i( oiid );
		oiit = this->ot2i( oiit );

		m_year = idgety( oiid );
		m_mon  = idgetm( oiid );
		m_day  = idgetd( oiid );

		m_hour = itgeth( oiit );
		m_min = itgetm(  oiit );
		m_sec = itgets(  oiit );


		//rebuild the datetime

		tint32 i;

		i = itmk( m_hour, m_min, m_sec );
		m_day += i / 86400;
		i %= 86400;
		m_hour = itgeth( i );
		m_min = itgetm( i );
		m_sec = itgets( i );

		i = idmk( m_year, m_mon, m_day );
		m_year = idgety( i );
		m_mon  = idgetm( i );
		m_day  = idgetd( i );


		return *this;	
	}


	static tbool IsValidDate( std::string strVal ) //yyyymmdd
	{
		if( strVal.length() != 8 ) return 0;
		std::string s1,s2;
		SDte d1;
		s1 = strVal + " 001122";
		d1.Make( s1 );
		s2 = d1.ReadStringPack();		 
		SStrf::sreplstr( s1, " ", "." );
		if( s1 != s2 ) return 0;
		return 1;
	}



	static tbool IsValidTime( std::string strVal ) //hhmiss
	{
		if( strVal.length() != 6 ) return 0;

		std::string s1 ;
		
		s1 = strVal.substr( 0, 2 );
		int i1 = SStrf::satol( s1 );
		if( i1 >= 24 ) return 0;

		s1 = strVal.substr( 2, 2 );
		i1 = SStrf::satol( s1 );
		if( i1 >= 60 ) return 0;

		s1 = strVal.substr( 4, 2 );
		i1 = SStrf::satol( s1 );
		if( i1 >= 60 ) return 0;

		return 1;
	}




	static tbool IsValidDateTime( std::string strVal ) //yyyymmddhhmiss
	{
		if( strVal.length() != 14 ) return 0;

		std::string s1,s2;
		SDte d1;
		s2 = strVal;
		s2.insert( 8, " " );
		d1.Make( s2 );
		s1 = d1.ReadStringPack();		 
		SStrf::sreplstr( s2, " ", "." );
		if( s1 != s2 ) return 0;
		return 1;
	}






	SDte & MakeNow()
	{
		struct tm  tnow;
		this->Now(tnow);
		m_year= tnow.tm_year;
		m_mon = tnow.tm_mon+1;
		m_day = tnow.tm_mday;
		m_hour= tnow.tm_hour;
		m_min = tnow.tm_min;
		m_sec = tnow.tm_sec;
		return *this;
	}


	static SDte GetNow()  //  wl::SDte::GetNow().ReadStringPack().c_str()
	{
		SDte s; 
		return s.MakeNow();
	}


	tint32 DiffDay( const SDte & dte2 ) const
	{
		tint32 d1, d2;

		d1 = this->idmk( m_year, m_mon, m_day ) ;
		d2 = dte2.idmk( dte2.m_year, dte2.m_mon, dte2.m_day ) ;

		return d1 - d2;
	}


	tdouble DiffSec( const SDte & dte2 ) const
	{
		tdouble d1, d2;

		d1 = (double)this->itmk( m_hour, m_min, m_sec );
		d2 = (double)dte2.itmk( dte2.m_hour, dte2.m_min, dte2.m_sec );

		return d1 - d2 + DiffDay(dte2) * 86400.0;
	}


	tint32 DiffSecInt( const SDte & dte2 ) const
	{
		tint32 d1, d2;

		d1 = (tint32)this->itmk( m_hour, m_min, m_sec );
		d2 = (tint32)dte2.itmk( dte2.m_hour, dte2.m_min, dte2.m_sec );

		return d1 - d2 + DiffDay(dte2) * 86400;
		/*	long a1,a2;
			a1 = wl::SDte("").DiffSecInt( wl::SDte("1970-1-1 00:00:00") );
			a2 = time(0);
			printf( "%X\n", a1 );
			printf( "%X\n", a2 );
			printf( "%X %u\n", a1-a2, a1-a2 );
		   a2的值小了8小时。
			*/
	}


	int WeekDay() const
	{
		int i2 = this->DiffDay( wl::SDte() );
		return (i2 - 2 ) % 7;
	}


	SDte & Relative( const SDte & dte2 )
	{
		m_year += dte2.m_year;
		m_mon  += dte2.m_mon;
		m_day  += dte2.m_day;
		m_hour += dte2.m_hour;
		m_min  += dte2.m_min;
		m_sec  += dte2.m_sec;

		tint32 i;

		i = itmk( m_hour, m_min, m_sec );
		m_day += i / 86400;
		i %= 86400;
		m_hour = itgeth( i );
		m_min = itgetm( i );
		m_sec = itgets( i );

		i = idmk( m_year, m_mon, m_day );
		m_year = idgety( i );
		m_mon  = idgetm( i );
		m_day  = idgetd( i );

		return *this;
	}

	
	SDte & RelativeSec( tint32 sec2 )
	{
		SDte dte2;
		dte2.m_year = dte2.m_mon = dte2.m_day = dte2.m_hour = dte2.m_min = 0;
		dte2.m_sec = sec2;
		return Relative(dte2);
	}



	std::string ReadString() const //2008-02-13 15:22:33
	{
		tchar sBuf[33];
		(*SClib::p_sprintf())(sBuf,"%d-%02d-%02d %02d:%02d:%02d",
					 m_year, m_mon, m_day,  
					 m_hour, m_min, m_sec	);
		return sBuf;
	}

	std::string ReadStrDate() const // 2008-02-13 
	{
		tchar sBuf[33];
		(*SClib::p_sprintf())(sBuf,"%d-%02d-%02d",
					 m_year, m_mon, m_day );
		return sBuf;
	}

	std::string ReadStrTime() const // 15:22:33
	{
		tchar sBuf[33];
		(*SClib::p_sprintf())(sBuf,"%02d:%02d:%02d",
					 m_hour, m_min, m_sec	);
		return sBuf;
	}


	std::string ReadStringPack( char c = '.' ) const //20080213.152233
	{
		tchar sBuf[33];
		(*SClib::p_sprintf())(sBuf,"%d%02d%02d%c%02d%02d%02d",
					 m_year, m_mon, m_day,  c , 
					 m_hour, m_min, m_sec	);
		return sBuf;
	}

	std::string ReadStrPackDate() const //20080213
	{
		tchar sBuf[33];
		(*SClib::p_sprintf())(sBuf,"%d%02d%02d",
					 m_year, m_mon, m_day 	);
		return sBuf;
	}

	std::string ReadStrPackTime() const // 152233
	{
		tchar sBuf[33];
		(*SClib::p_sprintf())(sBuf,"%02d%02d%02d",
					 m_hour, m_min, m_sec	);
		return sBuf;
	}


	std::string Read_dt1() const //dd-MMM-yyyy
	{
		tchar sBuf[33];
		const tchar *s2[] = {"aa","Jan", "Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec" };
		(*SClib::p_sprintf())(sBuf,"%d-%s-%d",
								m_day,s2[m_mon], m_year );
		return sBuf;
	}


	operator std::string () const
	{
		return ReadStringPack() ;
	}


};//end of SDte






X011_NAMESPACE_END

#endif




/*
file new,del,select,read,write
*/

#ifndef X011__H_w_sfile_h
#define X011__H_w_sfile_h




X011_NAMESPACE_BEGIN



class SFile
{

private:

	std::string m_strFilename;

public:

	SFile()
	{
		bind("");
	}


	SFile( std::string fn )
	{
		bind(fn);
	}


	virtual ~SFile()
	{ ;
	}


	static std::string GetPathSep()
	{
		return "/";
	}


	static std::string MkDir2Path( std::string strPathOrDir ) 
	{
		if( strPathOrDir.length() )
		{
			const tchar * t;
			t = SStrf::splast( strPathOrDir.c_str() );
			if( *t == GetPathSep()[0] )
			{
				return strPathOrDir;
			}
		}
		
		return strPathOrDir + GetPathSep();
	}


	

	static void Dir2Path( std::string & strPathOrDir ) 
	{
		strPathOrDir = MkDir2Path(strPathOrDir);
	}





	void bind( std::string fn )
	{
		m_strFilename = fn;
	}



	tbool bind_nofile( std::string strPath, const tchar * pszExt = NULL , int iThreadId = 0 ) // ext不一定必须带点
	{
		static int iName1 = 0;
		tdouble dName2;
		int k=0;
		std::string strNameExt(pszExt?pszExt:".tmp");
		std::string strGoodPathfilename;

		// 
		strPath = MkDir2Path( strPath );

		if( pszExt && *pszExt!='.' ) strNameExt = std::string(".") + pszExt;

		do
		{
			iName1--;
			dName2 = SStrf::rand1();
			strGoodPathfilename = strPath + "h" + SStrf::sltoa(iName1) + "_" + SStrf::sltoa(iThreadId) + SStrf::sftoa(dName2) + strNameExt;
			bind(strGoodPathfilename);
			if(canoutput()) return 1;
			if( k ++ > 9 )
			{
				if(!erase())
				{
					bind("");
					return 0;
				}
			}
		}while(1);
	}


	std::string filename() const
	{
		return m_strFilename;
	}


	//operator std::string & () 
	//{
	//	return m_strFilename;
	//}

	operator std::string () const
	{
		return m_strFilename; 
	}

	operator const tchar * () const
	{
		return m_strFilename.c_str();
	}


	tbool erase()
	{
		return 0==remove( m_strFilename.c_str() )?1:0;
	}

	static tbool erase(std::string strfilename)
	{
		return 0==remove( strfilename.c_str() )?1:0;
	}


	tbool exists()
	{
		FILE *fp;
		tbool rc;
		if( m_strFilename=="" )
		{
			return 0;
		}
		fp = (*SClib::p_fopen())( m_strFilename.c_str(), "rb" );
		if(fp==NULL) rc=0;
		if(fp!=NULL)
		{
			rc=1; fclose(fp);
		}
		return rc;
	}


	tbool caninput()
	{
		return exists();
	}


	tbool canoutputabs()
	{ 
		FILE *fp;
		fp = (*SClib::p_fopen())(m_strFilename.c_str(),"wb");
		if(fp==NULL) return 0;
		fclose(fp);
		return erase();
	}


	tbool canoutput()
	{	//safely create. means if exists then can't .
		if(exists()) return 0;
		return canoutputabs();
	}


	tsize len()
	{
		if( !exists() ) return 0;
		tsize flen;
		FILE *fp;
		fp = (*SClib::p_fopen())( m_strFilename.c_str(), "rb" );
		fseek( fp,0,SEEK_END );
		flen=ftell(fp);
		fclose(fp);
		return flen;
	}


	tbool read( SCake_base<tchar> & buf, tsize a_extra_bytes = 0 ) //bin read
	{
		if(!this->exists()) return 0;
		FILE *fp;

		fp = (*SClib::p_fopen())( m_strFilename.c_str(), "rb" );
		if( fp == NULL )
		{
			return 0;
		}

		tsize flen;
		fseek( fp,0,SEEK_END );
		flen=ftell(fp);
		fseek( fp,0,SEEK_SET );


		//if( flen == 0) 
		//{
		//	fclose(fp);
		//	return 0 ;
		//}


		buf.redim( flen + a_extra_bytes );

		if(a_extra_bytes) 
		{
			SStrf::smemset( buf.buf(), 0, flen + a_extra_bytes ); //the a_extra_bytes may be > 1
			//*( buf.buf() + ( flen + a_extra_bytes ) - 1 ) = 0;
		}

		if(flen) fread( buf.buf(), flen, 1, fp );

		fclose(fp);

		return 1;
	}


	tbool read_str( SCake_base<tchar> & buf ) // read content and add a c00 to form a string //read str means read an extra c00.
	{
		return this->read( buf, 1 );
	}


	tbool read_str( std::string & strRtnBuf )
	{
		SCake_base<tchar> buf;
		strRtnBuf = "";
		if( read_str(buf) )
		{
			strRtnBuf = buf.buf();
			return 1;
		}
		return 0;
	}


	tbool read_vecstr( std::vector<std::string> & vecLines, std::string strSep, tbool istoken = 1 )
	{
		wl::SCake ckData;
		if( !read_str( ckData ) ) return 0;
		if( !ckData.len() ) return 0;
		SStrvs::vsa_imp( std::string(ckData.buf()), strSep, istoken, vecLines );
		return 1;
	}



	tbool write( const void * pbuf, tsize len, tbool bIsAppend = 0 ) //bin write
	{
		FILE *fp;
		tbool rc;

		rc=0;

		do
		{
			if( len == 0 ) break;
			if( !pbuf ) break;
			fp = (*SClib::p_fopen())( m_strFilename.c_str( ), bIsAppend?"ab":"wb" );
			if(fp==NULL) break;
			rc = fwrite( pbuf, len, 1, fp )?1:0 ;
			fclose(fp);
		}while(0);

		return rc?1:0 ;
	}



	tbool write( const SCake_base<tchar> & buf, tbool bIsAppend = 0 ) //bin write
	{
		FILE *fp;
		tbool rc;

		rc=0;

		do
		{
			if( buf.len()==0 ) break;
			if( !buf.buf_const() ) break;
			fp = (*SClib::p_fopen())( m_strFilename.c_str( ), bIsAppend?"ab":"wb" );
			if(fp==NULL) break;
			rc = fwrite( buf.buf_const(), buf.len(), 1, fp )?1:0 ;
			fclose(fp);
		}while(0);

		return rc?1:0 ;
	}


	tbool write_str( const tchar * buf, tbool bIsAppend = 0 )//write a string. not include the sz c00. //write str means not write c00.
	{
		FILE *fp;
		tbool rc;

		rc=0;

		do
		{
			if( NULL == buf ) break;
			fp = (*SClib::p_fopen())( m_strFilename.c_str(), bIsAppend?"ab":"wb" );
			if(fp==NULL) break;
			if( fwrite( buf, SStrf::slen(buf), 1, fp ) )//if slen(buf)==0 then write a 0 len file.
			{
				rc = 1; 
			}
			else
			{
				rc = 0;
			}
			fclose(fp);

		}while(0);

		return rc?1:0 ;
	}


	tbool write_str( const std::string & buf, tbool bIsAppend = 0 )//not include the sz c00.
	{
		return write_str( buf.c_str(), bIsAppend );
	}


	tbool write_vecstr( const std::vector<std::string> & vecLines, std::string strSep, tbool bIsAppend = 0 )
	{
		std::string strOut;

		for( std::vector<std::string>::const_iterator it = vecLines.begin(); it != vecLines.end(); ++it )
		{
			strOut += *it + strSep;
		}

		return write_str(strOut, bIsAppend);
	}


	//
	tbool IsHeadOf( SFile & me2 )
	{
		if( !SStrf::scmpi( this->filename().c_str(), me2.filename().c_str() ) ) return 0; //same file, not include.
		if( !this->exists() ) return 0;
		if( !me2.exists()   ) return 0;

		tsize i1, i2;

		if( (i1 = this->len()) == 0 ) return 0;
		if( (i2 = me2.len()) == 0   ) return 0;

		if( i1 > i2 ) return 0;

		SCake ck1, ck2;

		this->read( ck1 );
		me2.read( ck2 );

		if( !memcmp( ck1.buf(), ck2.buf(), i1 ) ) return 1;

		return 0;
	}

	
	//
	tbool IsHeadOf( std::string strme2 )
	{
		SFile sf2;
		sf2.bind(strme2);
		return IsHeadOf(sf2);
	}

};//end SFile





X011_NAMESPACE_END

#endif







/*
SNava  means NAme-VAlue pair
*/

#ifndef X011__H_w_SNava_h
#define X011__H_w_SNava_h



X011_NAMESPACE_BEGIN



template< class nameT, class valueT >
class SNava_base
{
public:

	typedef typename std::map< nameT, valueT >::iterator	MAP_MAPKNL_IT;
	typedef typename std::map< nameT, valueT >::const_iterator  MAP_MAPKNL_CONSTIT;

	MAP_MAPKNL_IT m_it4name;

public:

	std::map< nameT, valueT >  m_mapKnl;
	

public:

	virtual ~SNava_base() {;} 
	

	void clear()
	{
		m_mapKnl.clear();
	}


	tbool IsEmpty()
	{
		if( m_mapKnl.empty() ) return 1;
		return 0;
	}


	tbool let( const nameT & name, const valueT & val )
	{
		//m_mapKnl.insert( std::pair< nameT, valueT >( name, val ) ); //if there already have one value, the insert will do nothing.
		m_mapKnl[name] = val; //this method will overwrite the current value, if existed.
		return 1;
	}


	tbool get( const nameT & name, valueT & val )
	{
		MAP_MAPKNL_IT it;
		it = m_mapKnl.find( name );
		if( it != m_mapKnl.end() )
		{
			val = it->second;
			return 1;
		}
		return 0;
		//return m_mapKnl[name];
	}


	valueT & get( const nameT & name )
	{
		return m_mapKnl[name];
	}


	tbool del( const nameT & name )
	{
		MAP_MAPKNL_IT it;
		it = m_mapKnl.find( name );
		if( it != m_mapKnl.end() )
		{
			m_mapKnl.erase(it);
			return 1;
		}
		return 0;
	}


	tbool GetFirstName( nameT & Name )
	{
		m_it4name = m_mapKnl.begin();
		if( m_it4name != m_mapKnl.end() )
		{
			Name = m_it4name->first;
			return 1;
		}
		return 0;
	}


	tbool GetNextName( nameT & Name )
	{
		m_it4name ++;
		if( m_it4name != m_mapKnl.end() )
		{
			Name = m_it4name->first;
			return 1;
		}
		return 0;
	}


	tbool operator < ( const SNava_base & rhs) const
	{
		return ( m_mapKnl < rhs.m_mapKnl ? 1 : 0 );
	}

	tbool operator <= ( const SNava_base & rhs) const
	{
		return ( m_mapKnl <= rhs.m_mapKnl ? 1 : 0 );
	}

	tbool operator > ( const SNava_base & rhs) const
	{
		return ( m_mapKnl > rhs.m_mapKnl ? 1 : 0 );
	}

	tbool operator >= ( const SNava_base & rhs) const
	{
		return ( m_mapKnl >= rhs.m_mapKnl ? 1 : 0 );
	}

	tbool operator == ( const SNava_base & rhs) const
	{
		return ( m_mapKnl == rhs.m_mapKnl ? 1 : 0 );
	}
};




class SNavass : public SNava_base< std::string, std::string >
{
private:

	static void seri_element_en( SCake & ck )
	{
		if( ck.len() == 0 ) return;
		ck.bs_en();
	}

	static void seri_element_de( SCake & ck )
	{
		if( ck.len() == 0 ) return;
		ck.bs_de();
		if( !ck.buf() ) ck.lets(""); //because "" means NULL pointer, just prevent this.
	}

public:
	virtual ~SNavass() {;} 
	
	
	void imp( const std::string & ssource, std::string ssepTR, std::string ssepTD )
	{
		SStrvs::vsa2v_prpt( ssource, ssepTR, ssepTD , m_mapKnl );  
	}

	
	void trimall()
	{
		std::map< std::string, std::string > mapTmp = m_mapKnl;

		this->clear();

		for( MAP_MAPKNL_IT it = mapTmp.begin(); it != mapTmp.end(); ++it )
		{
			std::string s1 = it->first;
			std::string s2 = it->second;

			SStrf::strim( s1 );
			SStrf::strim( s2 );

			this->let( s1, s2 ); 
		}
	}


	tbool serialize( std::string & strOut ) const
	{
		strOut = "";

		SCake ckTmp;

		for( MAP_MAPKNL_CONSTIT it = m_mapKnl.begin(); it != m_mapKnl.end(); ++it )
		{
			ckTmp.lets( it->first );
			seri_element_en( ckTmp );
			strOut += ckTmp.buf();

			strOut += "(";

			ckTmp.lets( it->second );
			seri_element_en( ckTmp );
			strOut += ckTmp.buf();

			strOut += ")";
		}

		return 1;
	}


	tbool unserialize( const std::string & strData )
	{
		std::map< std::string, std::string > mapTmp;
		SCake ckTmp1,ckTmp2;

		SStrvs::vsa2v_prpt( strData, std::string(")"), std::string("(") , mapTmp );
		this->clear();

		for( MAP_MAPKNL_IT it = mapTmp.begin(); it != mapTmp.end(); ++it )
		{
			ckTmp1.lets( it->first );
			seri_element_de( ckTmp1 );
			ckTmp2.lets( it->second );
			seri_element_de( ckTmp2 );

			let( std::string(ckTmp1.buf()), std::string(ckTmp2.buf()) ); 
		}

		return 1;
	}

};




X011_NAMESPACE_END

#endif




/*
binary knl
anti-bayes arithmatic
*/

#ifndef X011__H_w_SAbys_h
#define X011__H_w_SAbys_h




X011_NAMESPACE_BEGIN



class SAbys
{

private:

	SCake		m_knowledge_cake;
	tsize		m_knowledge_cur_pos;
	tdouble		m_data_knowledge_ratio;
	
	//data, knowledge, mixeddata 
	/*data can be any bin data. evalute bstr first to transfer it into sz format.
	  knowledge can be any bin format. mix them.
	  knowledge should be a sz and without its last c00. this would be better to transmit.
	  also, knowledge is supposed to have not \n, for the mixed result may transmit through internet.

	  mixeddata: a cake. bin mixed. the last c00 is out of range. just for debug use.
	  unmix: turn mixeddata(a cake) to original data. return a cake.
	*/
 
public:

	SAbys() 
	{ 
		init( 23.6 );
	}

	SAbys( tdouble ratio ) 
	{ 
		init( ratio );
	}

	SAbys( const SCake & cakeKnow ) 
	{  
		init(cakeKnow);
	}

	virtual ~SAbys( )
	{ ; }


	void init( tdouble data_knowledge_ratio = 1.0 )
	{
		SStrf::initrand(); 
		SCake ckTmp( SStrf::sftoa( SStrf::rand1() ) + SStrf::sftoa( SStrf::rand1() ) );
		ckTmp.cut(1);
		init( ckTmp , data_knowledge_ratio );
	}


	void init( const SCake & knowledge_cake , tdouble data_knowledge_ratio = 1.0 )
	{
		if(knowledge_cake.len()>0)
			m_knowledge_cake = knowledge_cake;
		else
			init(data_knowledge_ratio);
		m_knowledge_cur_pos = (tsize)(m_knowledge_cake.len() * SStrf::rand1());
		m_data_knowledge_ratio = data_knowledge_ratio>0?data_knowledge_ratio:1;
	}


	void mix( const SCake & ck_Data /*IN*/ , 
			  SCake & ck_Mixeddata /*OUT*/ ,
			  tchar chSep = '('		)
	{
		SCake ck_dubious_data = ck_Data;
		ck_dubious_data.bs_en();

		SStrf::srev( ck_dubious_data );
		tsize iKnowLen = (tsize)(ck_Data.len()/m_data_knowledge_ratio);
		ck_Mixeddata.redim( ck_dubious_data.len() + iKnowLen + 1 );
		SStrf::scpy( ck_Mixeddata, ck_dubious_data );
		ck_dubious_data.cut(1);
		tsize iPnt = ck_dubious_data.len();
		*(ck_Mixeddata.buf()+iPnt) = chSep;
		iPnt++;
		for(ck_Mixeddata.cut(1);iPnt!=ck_Mixeddata.len();iPnt++)
		{
			m_knowledge_cur_pos++;
			if(m_knowledge_cur_pos>=m_knowledge_cake.len()) m_knowledge_cur_pos=0;
			*(ck_Mixeddata.buf()+iPnt) = *(m_knowledge_cake.buf()+m_knowledge_cur_pos);
		}
		*(ck_Mixeddata.buf()+iPnt) = 0;
	}

	std::string mix( const SNavass & nv )
	{
		std::string str;
		nv.serialize(str);
		SCake ck1( str );
		SCake ck2;
		mix( ck1, ck2 );
		return ck2.buf();
	}

	std::string & mix( const std::string & str , std::string & strOut )
	{
		SCake ck1( str );
		SCake ck2;
		mix( ck1, ck2 );
		strOut = ck2.buf();
		return strOut;
	}


	void unmix(  const SCake & ck_Mixeddata,		 /*IN*/ 
				 SCake	 & ck_Data					/*out*/	,
				 tchar chSep = '('		)
	{
		SCake ck0("");
		SCake ckMixDataWriteable( ck_Mixeddata );

		ckMixDataWriteable.append( ck0 );

		tchar strSep[2];

		strSep[0] = chSep;
		strSep[1] = 0;

		ck_Data.lets( SStrvs::vsa_get( std::string(ckMixDataWriteable), std::string(strSep), 1, 0 ) );
		SStrf::srev( ck_Data );
		tsize iDatalen = SStrf::bs_desize( ck_Data );
		//SStrf::bs_de( ck_Data );
		ck_Data.bs_de();
		ck_Data.redim( iDatalen, 1 );
	}

	void unmix( const std::string & strSource, SNavass & nv )
	{
		SCake ck1( strSource );
		SCake ck2;
		unmix( ck1, ck2 );
		ck2.mk_sz();
		nv.unserialize( std::string(ck2) );
	}
	
	std::string & unmix( const std::string & strSource, std::string & strOut )
	{
		SCake ck1( strSource );
		SCake ck2;
		unmix( ck1, ck2 );
		ck2.mk_sz();
		strOut = ck2.buf();
		return strOut;
	}

	
	void envelop( 	const SCake & ckKeyWord, 
					const SCake & ckHead, const SCake & ckTail, const SCake & ck_src, SCake & ck_destbuf )
	{
		//if  KeyWord is in  Head, then change Head, let Head doesn't contain KeyWord. one char change for once would be enough.
	}
	
	tbool unenvelop( const SCake & ckKeyWord, 
					 const SCake & ck_src, SCake & ck_destbuf	)
	{
		return 1;
	}

};
//end class SAbys 





X011_NAMESPACE_END

#endif




/*
rice
*/

#ifndef X011__H_w_IRice_h
#define X011__H_w_IRice_h




X011_NAMESPACE_BEGIN



class IRice
{

protected:

	SCake m_ckDataL2CacheBuf;


protected:

	tsize sys_recv( SCake & ckDataBuf )
	{
		int i = on_sys_recv(ckDataBuf); //no matter how long received, just got the rtn.
		if(i)
		{
			return i;
		}
		else
		{
			ckDataBuf.redim(0);
			return 0;
		}
	}


	tsize sys_send( const SCake & ckDataBuf )
	{
		return on_sys_send(ckDataBuf);
	}



public:

	IRice( )
	{
		//
	}


	virtual ~IRice( )
	{ ; }


	void ClearL2Cache()	
	{
		m_ckDataL2CacheBuf.redim(0);
	}


	tbool send_str( std::string s ) //return if send success
	{
		return send_str(s.c_str());
	}

	
	tbool send_str( const tchar *s ) //return if send success //write str means not write c00.
	{
		SCake ckTmp(s);
		ckTmp.cut(1);
		return send_bin( ckTmp );
	}


	tbool send_bin( const SCake & ckData )
	{
		tsize rc, k;
		if(ckData.len()==0) return 0;
		for(k=0;;)
		{
			SCake ckTmp(ckData.buf_const()+k, ckData.len()-k);
			rc = sys_send( ckTmp );
			if(rc==0) return 0;
			k += rc;
			if(k>=ckData.len()) break;
		}
		return 1;
	}


	template<class T>
	tbool send_bin( T adata )
	{
		SCake ck;
		ck.let( (SCake::CkEle_t*)&adata, sizeof(T) );
		return send_bin(ck);
	}


	//tbool send_esc( SCake ckData , tchar a1, tchar a2, tchar a3 ) //for com use
	//{
	//	ckData.comesc_en(a1,a2,a3);
	//	return send_bin( ckData );
	//}




	tbool recv_bin( SCake & ckData ) //current available data
	{
		SCake ckTmp;

		if( m_ckDataL2CacheBuf.len() == 0 )//如果不判断，上来就接收，会block在这里。
		{
			sys_recv( ckTmp ); //没有L2数据时我们才真去接收.
			m_ckDataL2CacheBuf.append(ckTmp);//其实这里就是直接等于收到的所有数据。
		}
		else
		{
			//
		}

		ckData = m_ckDataL2CacheBuf;
		m_ckDataL2CacheBuf.redim(0);
		return ckData.len()==0?0:1;
	}


	tbool recv_all( SCake & ckData ) //all data of this session
	{
		SCake ckTmp;
		do
		{
			if( !sys_recv( ckTmp ) ) break;
			m_ckDataL2CacheBuf.append(ckTmp);

			if( !on_chk_L2CacheLen( m_ckDataL2CacheBuf ) ) break; //chk long data

		}while(ckTmp.len()>0);

		ckData = m_ckDataL2CacheBuf;
		m_ckDataL2CacheBuf.redim(0);
		return ckData.len()==0?0:1;
	}


	
	tbool recv_all_f( SCake & ckData ) //all data of this session, fast append
	{
		SCake ckTmp;
		do
		{
			if( !sys_recv( ckTmp ) ) break;
			//m_ckDataL2CacheBuf.append(ckTmp);
			m_ckDataL2CacheBuf.FastAppend(ckTmp);

			//if( !on_chk_L2CacheLen( m_ckDataL2CacheBuf ) ) break; //chk long data

		}while(ckTmp.len()>0);

		m_ckDataL2CacheBuf.FastAppendEnd();

		ckData = m_ckDataL2CacheBuf;
		m_ckDataL2CacheBuf.redim(0);
		return ckData.len()==0?0:1;
	}


	tbool recv_len( SCake & ckData , tsize iWantDataLen ) //appointed lenth of data
	{
		SCake ckTmp;

		while( m_ckDataL2CacheBuf.len()< iWantDataLen )
		{
			if( !sys_recv( ckTmp ) ) break;

			//m_ckDataL2CacheBuf.append(ckTmp);
			m_ckDataL2CacheBuf.FastAppend(ckTmp);
		}

		m_ckDataL2CacheBuf.FastAppendEnd();
		
		ckData.redim(iWantDataLen);
		m_ckDataL2CacheBuf.dump( ckData );//maybe dumped less than appointed len of data, if not enough len of data available and remote died.
		return ckData.len()+m_ckDataL2CacheBuf.len()==0?0:1;
	}


	
	tbool recv_ln( SCake & ckData , const std::vector<std::string> & vecstrSeperate, std::string * pstrRealSep=NULL ) //pstrRealSep to return real seperator 
	{
		SCake ckTmp;
		tchar * pSep;
		SCake ckSepDumpTmp;
		
		do
		{
			SCake ckTmpL2Cache2;
			ckTmpL2Cache2 = m_ckDataL2CacheBuf;
			ckTmpL2Cache2.mk_sz();
			
			pSep = NULL;

			if(pstrRealSep) *pstrRealSep = "";

			//pSep = SStrf::sstr( m_ckDataL2CacheBuf, strSeperate );	//the L2cache is not a sz. use strstr will cause run-time error.
			for( std::vector<std::string>::const_iterator it = vecstrSeperate.begin();
				 it != vecstrSeperate.end();
				 ++it )
			{
				pSep = SStrf::sstr( ckTmpL2Cache2, it->c_str() );
				if( pSep )
				{
					if(pstrRealSep) *pstrRealSep = *it;

					ckSepDumpTmp.lets(*it);
					ckSepDumpTmp.cut(1); //the strSeperate is sz. remove the last '\0'
					break;
				}
			}
			
			
			if( pSep )
			{
				//ckData.redim( (tsize)(pSep - m_ckDataL2CacheBuf.buf() ) ); 
				ckData.redim( (tsize)(pSep - ckTmpL2Cache2.buf() ) );
				
				m_ckDataL2CacheBuf.dump( ckData );
				m_ckDataL2CacheBuf.dump( ckSepDumpTmp ); //get rid of the leading sep str in L2Cache. 
				return 1;
			}
			
			if( !sys_recv( ckTmp ) ) break;
			m_ckDataL2CacheBuf.append(ckTmp);

			if( !on_chk_L2CacheLen( m_ckDataL2CacheBuf ) ) break; //chk long line

		}while(ckTmp.len()>0);

		ckData = m_ckDataL2CacheBuf;	//找到sep的情况已在while中return。这里是收失败时的情况了。
		m_ckDataL2CacheBuf.redim(0);
		return ckData.len()==0?0:1;
	}

		
	tbool recv_ln( SCake & ckData , const tchar * strSeperate = "\n" ) //use Seperate
	{
		if( strSeperate && std::string(strSeperate) == "\r\n\r\n\r\n" )
			return recv_ln2( ckData , strSeperate );
		
		SCake ckTmp;
		tchar *pSep;
		SCake ckSepDumpTmp(strSeperate);
		
		ckSepDumpTmp.cut(1); //the strSeperate is sz. remove the last '\0'
		
		do
		{
			SCake ckTmpL2Cache2;
			ckTmpL2Cache2 = m_ckDataL2CacheBuf;
			ckTmpL2Cache2.mk_sz();
			
			//pSep = SStrf::sstr( m_ckDataL2CacheBuf, strSeperate );	//the L2cache is not a sz. use strstr will cause run-time error.
			pSep = SStrf::sstr( ckTmpL2Cache2, strSeperate );
			
			if( pSep )
			{
				//ckData.redim( (tsize)(pSep - m_ckDataL2CacheBuf.buf() ) ); 
				ckData.redim( (tsize)(pSep - ckTmpL2Cache2.buf() ) );
				
				m_ckDataL2CacheBuf.dump( ckData );
				m_ckDataL2CacheBuf.dump( ckSepDumpTmp ); //get rid of the leading sep str in L2Cache. 
				return 1;
			}
			
			if( !sys_recv( ckTmp ) ) break;

			m_ckDataL2CacheBuf.append(ckTmp);

			if( !on_chk_L2CacheLen( m_ckDataL2CacheBuf ) ) break; //chk long line

		}while(ckTmp.len()>0);

		ckData = m_ckDataL2CacheBuf;	//找到sep的情况已在while中return。这里是收失败时的情况了。
		m_ckDataL2CacheBuf.redim(0);
		return ckData.len()==0?0:1;
	}



	tbool recv_ln( SCake & ckData , tchar cSeperate ) //use Seperate
	{
		tchar t[2];
		t[0]=cSeperate;
		t[1]=0;
		return recv_ln(ckData,t) ;
	}

	

	tbool recv_ln2( SCake & ckData , const tchar * strSeperate )  //no buf-limit-check and _fast
	{
		SCake ckTmp;
		tchar *pSep;
		SCake ckSepDumpTmp(strSeperate);
		
		ckSepDumpTmp.cut(1); 


		std::vector<tchar>  vec_m_ckTmpL2CacheBuf;
		std::copy( m_ckDataL2CacheBuf.buf(), m_ckDataL2CacheBuf.buf() + m_ckDataL2CacheBuf.len(), std::back_inserter(vec_m_ckTmpL2CacheBuf) );

		long lLastChkOffset(0);

		do
		{
			vec_m_ckTmpL2CacheBuf.push_back(0);
			
			pSep = SStrf::sstr( &(vec_m_ckTmpL2CacheBuf[lLastChkOffset]), strSeperate );

			vec_m_ckTmpL2CacheBuf.pop_back();


			if( pSep )
			{
				//restore m-buf
				//
				if( vec_m_ckTmpL2CacheBuf.empty() )
					m_ckDataL2CacheBuf.redim(0);
				else
					m_ckDataL2CacheBuf.let( &(vec_m_ckTmpL2CacheBuf[0]), (tsize)vec_m_ckTmpL2CacheBuf.size() );

				vec_m_ckTmpL2CacheBuf.clear();
				//end restore

				SCake ckTmpL2Cache2;
				ckTmpL2Cache2 = m_ckDataL2CacheBuf;
				ckTmpL2Cache2.mk_sz();

				pSep = SStrf::sstr( ckTmpL2Cache2, strSeperate );

				ckData.redim( (tsize)(pSep - ckTmpL2Cache2.buf() ) );
				
				m_ckDataL2CacheBuf.dump( ckData );
				m_ckDataL2CacheBuf.dump( ckSepDumpTmp ); 
				return 1;
			}
			else
			{
				//if( !pSep) then we must modify the lLastChkOffset
				lLastChkOffset = (long)vec_m_ckTmpL2CacheBuf.size() - (long)ckSepDumpTmp.len();
				if( lLastChkOffset < 0 ) lLastChkOffset = 0;				 
			}

			
			if( !sys_recv( ckTmp ) ) break;

			std::copy( ckTmp.buf(), ckTmp.buf() + ckTmp.len(), std::back_inserter(vec_m_ckTmpL2CacheBuf) ); 
			/*
			将一个vector连接另一个vector末尾的最佳方法是什么？ 	
			v1.insert(v1.end(),   v2.begin(),   v2.end()   );   
			because   vector::insert   will   calculate   the   size   of   inserted   elemenets   and   allocate   the   space   only   once,   then   copy   the   data   from   v2   to   v1.
			---------
			这是最快的办法：   
			std::copy(v2.begin(),   v2.end(),   std::back_inserter(v1));
			*/

			//if( !on_chk_L2CacheLen( m_ckDataL2CacheBuf ) ) break; 

		}while(ckTmp.len()>0);

		
		//restore m-buf
		//
		if( vec_m_ckTmpL2CacheBuf.empty() )
			m_ckDataL2CacheBuf.redim(0);
		else
			m_ckDataL2CacheBuf.let( &(vec_m_ckTmpL2CacheBuf[0]), (tsize)vec_m_ckTmpL2CacheBuf.size() );

		vec_m_ckTmpL2CacheBuf.clear();
		//end restore


		ckData = m_ckDataL2CacheBuf;
		m_ckDataL2CacheBuf.redim(0);
		return ckData.len()==0?0:1;
	}



public:

	virtual tbool on_chk_L2CacheLen( const SCake & ckCurrentL2Cache )
	{
		return 1;
	}


	virtual int on_sys_recv( SCake & ckDataBuf ) //return the real recv len
	{
		return 0;
	}


	virtual int on_sys_send( const SCake & ckDataBuf ) //return the successfully sent len
	{
		return 0;
	}


};//end SRice





X011_NAMESPACE_END

#endif




/*
ICursor interface
*/

#ifndef X011__H_w_ICursor_h
#define X011__H_w_ICursor_h



X011_NAMESPACE_BEGIN


template < class envT, class tblT, class rowT >
class ICursor
{

private:

	tbool		 m_bIsEnvOpen;
	tbool		 m_bIsTblOpen;

	
public:

	ICursor( )
	{
		m_bIsEnvOpen = m_bIsTblOpen = 0;
	}


	virtual ~ICursor( )
	{ 
		//CloseB();
	}

	
public:

	typedef envT envTYPE;
	typedef tblT tblTYPE;
	typedef rowT rowTYPE;

	
public:

	tbool GetIsEnvOpen()
	{
		return m_bIsEnvOpen;
	}

	tbool GetIsTblOpen()
	{
		return m_bIsTblOpen;
	}
	
	
public:

	tbool OpenEnv( envTYPE & _env )
	{
		CloseEnv();	
		return m_bIsEnvOpen = OnOpenEnv(_env);
	}

	tbool OpenTbl( tblTYPE & _tbl )
	{
		CloseTbl();
		return m_bIsTblOpen = OnOpenTbl(_tbl);
	}

	tbool FetchRow( rowTYPE & _row )
	{
		return OnFetchRow( _row );
	}

	void CloseTbl()
	{
		if( GetIsTblOpen() ) OnCloseTbl();
		m_bIsTblOpen=0;
	}

	void CloseEnv()
	{
		if( GetIsEnvOpen() ) OnCloseEnv();
		m_bIsEnvOpen=0;
	}


public:

	virtual tbool OnOpenEnv( envTYPE & _env )
	{
		return 0;
	}

	virtual tbool OnOpenTbl( tblTYPE & _tbl )
	{
		return 0;
	}

	virtual tbool OnFetchRow( rowTYPE & _row )
	{
		return 0;
	}
	
	virtual void OnCloseTbl()
	{
		return;
	}
	
	virtual void OnCloseEnv()
	{
		return;
	}

};//end ICursor







//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



//a cursor data store

template < class IDS_ELE_TYPET >
class ICursorDs_base : public ICursor < std::string,  // envT,
										std::string,  // tblT, 
										std::vector<IDS_ELE_TYPET>  > // rowT  
{
public:

	typedef IDS_ELE_TYPET IDSeleTYPE; 

public:

	virtual ~ICursorDs_base( )
	{ ;
	}
	 

};//end ICursorDs_base




//a cursor data store

class ICursorDs	: public ICursorDs_base < std::string > 
{

public:

	virtual ~ICursorDs( )
	{ ;
	}
	 

};//end ICursorDs






X011_NAMESPACE_END

#endif






/*
linux mutex, like CriticalSection 
*/

/*用法例
wl::WCrsc 	m_cmapLock;
static wl::WCrsc m_csCmdDataPoolLock;

volatile  wl::WCrsc aLock( this->m_cmapLock );
*/

#ifndef X011__H_w_wcrsc_h
#define X011__H_w_wcrsc_h


X011_NAMESPACE_BEGIN


class WCrsc 
{

private:

	//CRITICAL_SECTION * m_pcsFather;
	pthread_mutex_t  * m_pcsFather;



private:
	//to copy the object is not allowed.

	/*WCrsc & operator = (const WCrsc & rhs)
	{
		return *this;
	}*/

	//WCrsc(const WCrsc & rhs)
	//{;}

	void LockCrsc( WCrsc & Crsc_father )
	{
		//EnterCriticalSection( m_pcsFather = Crsc_father.m_pcsSelf );
		pthread_mutex_lock ( m_pcsFather = Crsc_father.m_pcsSelf ); 
	}


public:

	//CRITICAL_SECTION * m_pcsSelf;
	pthread_mutex_t  * m_pcsSelf;


public:

	WCrsc()
	{
		m_pcsFather = NULL;
		m_pcsSelf = NULL;

		//m_pcsSelf = new CRITICAL_SECTION;
		//InitializeCriticalSection( m_pcsSelf );

		m_pcsSelf = new pthread_mutex_t; 
		pthread_mutexattr_t attr; 
		pthread_mutexattr_init(&attr);
		pthread_mutexattr_settype(&attr,PTHREAD_MUTEX_RECURSIVE_NP);
		pthread_mutex_init(m_pcsSelf,&attr); 
		pthread_mutexattr_destroy(&attr); 
	}
    

	WCrsc( WCrsc & Crsc_father)
	{
		m_pcsFather = NULL;
		m_pcsSelf = NULL;
		
		LockCrsc( Crsc_father );
	}

	WCrsc( WCrsc * pCrsc_father)
	{
		m_pcsFather = NULL;
		m_pcsSelf = NULL;
		
		if( pCrsc_father ) LockCrsc( *pCrsc_father );
	}


	virtual ~WCrsc()
	{
		if( m_pcsFather != NULL )
		{
			//LeaveCriticalSection( m_pcsFather );
			pthread_mutex_unlock (m_pcsFather);
			return;
		}
		
		if( m_pcsFather == NULL )
		{
			if( m_pcsSelf != NULL )
			{
				pthread_mutex_destroy( m_pcsSelf );
				delete m_pcsSelf;
				return;
			}
		}
	}

}; //end class 




X011_NAMESPACE_END

#endif





/*
w_WUniTblCh,   char型字符串支持的sqllike
*/

// 


#ifndef X011__W_WUNITBLCH_H
#define X011__W_WUNITBLCH_H




X011_NAMESPACE_BEGIN



class unitbl_base_t
{
public:
	wl::WCrsc		m_ut_tbl_lck; 
	
public:
	virtual ~unitbl_base_t() {;}

	virtual void ut_ClearTbl() = 0;

	virtual int ut_GetColAmount() = 0;
	virtual std::string ut_GetColName( int iColNum ) = 0;

	virtual long ut_GetRowAmount() = 0;

	virtual std::string ut_GetRowSeriStr( long lRowNum ) = 0; 

	virtual std::string ut_GetItemStr( long lRowNum, std::string strColName ) = 0; 
	virtual std::string ut_GetItemStr( long lRowNum, int iColNum ) = 0; 

	virtual void ut_SetItemByStr( long lRowNum, std::string strColName, std::string strValPARA  ) = 0; 
	virtual void ut_SetItemByStr( long lRowNum, int iColNum ,           std::string strValPARA  ) = 0; 

	virtual long ut_AddRow() = 0;
	virtual long ut_AddRow( std::string strRowSeriStr) = 0;

	virtual std::string & ut_SeriTbl( std::string & strOut )=0;
	virtual unitbl_base_t & ut_UnseriTbl( const std::string & strIn, int biAppend ) = 0;

	virtual void ut_DelRowf( long lRowNum ) = 0; 
	virtual void ut_DelRow( long lRowNum ) = 0; 
};





template<class T>
class unitbl_t : public unitbl_base_t , public T 
{
public:
	virtual ~unitbl_t() {;}


public:

	virtual void ut_ClearTbl()
	{
		T::Clear();
	}

	virtual int ut_GetColAmount()
	{
		return T::GetRow(-1).GetColAmount() ;
	}


	virtual std::string ut_GetColName( int iColNum ) 
	{
		return T::GetRow(-1).GetColName( iColNum );
	}


	virtual long ut_GetRowAmount() 
	{
		return T::GetRowCount( );
	}

	virtual std::string ut_GetRowSeriStr( long lRowNum ) 
	{
		return T::GetRow(lRowNum).Serialize();
	}
	

	virtual std::string ut_GetItemStr( long lRowNum, std::string strColName )
	{
		std::string s1;
		T::GetRow(lRowNum).GetColStr( strColName, s1 );
		return s1;
	}


	virtual std::string ut_GetItemStr( long lRowNum, int iColNum )
	{
		std::string s1;
		T::GetRow(lRowNum).GetColStr( iColNum, s1 );
		return s1;
	}
 
	virtual void ut_SetItemByStr( long lRowNum, std::string strColName, std::string strValPARA ) 
	{
		T::GetRow(lRowNum).SetColVal( strColName, strValPARA );
	}

	virtual void ut_SetItemByStr( long lRowNum, int iColNum ,           std::string strValPARA ) 
	{
		T::GetRow(lRowNum).SetColVal( iColNum, strValPARA );
	}

	virtual long ut_AddRow() 
	{
		T::Add(T::GetRow(-1));
		return T::GetRowCount() - 1 ;
	}

	virtual long ut_AddRow( std::string strRowSeriStr ) 
	{
		typename T::ROWTYPE row1;
		row1.Unserialize( strRowSeriStr.c_str() );
		T::Add(row1);
		return T::GetRowCount() - 1 ;
	}

	
	virtual std::string & ut_SeriTbl( std::string & strOut )
	{
		return T::Serialize( strOut );
	}


	virtual unitbl_base_t & ut_UnseriTbl( const std::string & strIn, int biAppend )
	{
		T::Unserialize( strIn.c_str() , biAppend )	;
		return *this;
	}


	virtual void ut_DelRowf( long lRowNum ) 
	{
		T::DelInternal( lRowNum );
	}

	virtual void ut_DelRow( long lRowNum )
	{
		T::Del( lRowNum );
	}

};




X011_NAMESPACE_END

#endif



/*
 linux file 
*/

#ifndef X011__H_w_WFile_h
#define X011__H_w_WFile_h




X011_NAMESPACE_BEGIN



class WFile : public SFile
{

private:



public:

	WFile( )
	{
		;
	}


	virtual ~WFile( )
	{ ;
	}



	void rename( std::string strNewNameCanBeWithNewDir )
	{
		std::string strCmd;

		strCmd = "mv \"";
		strCmd += this->filename();
		strCmd += "\" ";
		strCmd += "\"" + strNewNameCanBeWithNewDir + "\"";

		system( strCmd.c_str() );
	}


	static tbool FileAttriIsDir( std::string strFullPathName )
	{
        struct   stat   stbuf; 

        if(   lstat( strFullPathName.c_str(),   &stbuf )   <   0) 
		{ 
                return   0; 
        } 
        else
		{
			return   (S_ISDIR(stbuf.st_mode))?   1   :   0   ; 
		}
	} 




	static void ListFile(	std::string strRootPathOrDir,	//  
							std::string strPattern,			// in linux, not full functional, only *.abc affect
							std::vector<std::string> & vecstrRtnBuf1	, 
							tbool bIncludeDirName,
							tbool bIncludeFileName, 
							tbool bRetFullName	)	
	{
		//we don't clear vecstrRtnBuf, so, you can append filenames

		std::vector<std::string>  vecstrRtnBuf;

		DIR *pdir;
		struct dirent *pdirent;
		pdir = opendir( strRootPathOrDir.c_str() );

		if( !pdir )
		{
			return;
		}

		while( pdirent = readdir(pdir) )
		{
			std::string strFn( pdirent->d_name );
			std::string strFullFn( MkDir2Path( strRootPathOrDir ) + strFn );
			std::string strOut;
			
			if( bRetFullName )
			{
				strOut = strFullFn;
			}
			else
			{
				strOut = strFn;
			}

			if( strFn == "." || strFn == ".." )  continue;

			if( bIncludeDirName && FileAttriIsDir( strFullFn ) )
			{
				vecstrRtnBuf.push_back( strOut );
			}

			if( bIncludeFileName && !FileAttriIsDir( strFullFn ) )
			{
				vecstrRtnBuf.push_back( strOut );
			}

		} // end while

		closedir(pdir);

		//make the strPattern affective, see *.abc
		for( std::vector<std::string>::iterator it1 = vecstrRtnBuf.begin(); it1 != vecstrRtnBuf.end();  )
		{
			std::string s2( strPattern );

			if( s2.size() < 3 ) break;
			if( s2[0] != '*' ) break;
			if( s2[1] != '.' ) break;
			if( s2[2] == '*' ) break;

			std::string s1( *it1 );

			std::reverse( s1.begin(), s1.end() );

			s2.erase( s2.begin() );
			std::reverse( s2.begin(), s2.end() );

			if( s1.find(s2) != 0 ) // not pattern, erase it
			{
				it1 = vecstrRtnBuf.erase( it1 );
			}
			else
				it1++;
		}// end for, see *.abc

		//make the strPattern affective, see abc.*
		for( std::vector<std::string>::iterator it1 = vecstrRtnBuf.begin(); it1 != vecstrRtnBuf.end();  )
		{
			std::string s2( strPattern ); // might be abc.*

			std::reverse( s2.begin(), s2.end() ); // might be *.cba

			if( s2.size() < 3 ) break;
			if( s2[0] != '*' ) break;
			if( s2[1] != '.' ) break;
			if( s2[2] == '*' ) break;

			//now s2 must be *.cba 
			s2.erase( s2.begin() );
			std::reverse( s2.begin(), s2.end() ); //now s2 must be abc.

			std::string s1( *it1 );

			if( s1.find(s2) != 0 ) // not pattern, erase it
			{
				it1 = vecstrRtnBuf.erase( it1 );
			}
			else
				it1++;
		}// end for, see abc.*


		// 追加劳动成果进入返回变量中。 
		for( std::vector<std::string>::iterator it2 = vecstrRtnBuf.begin(); it2 != vecstrRtnBuf.end(); it2++ )
		{
			vecstrRtnBuf1.push_back(*it2);
		}
	}


	static void ListAllFile(	std::string strRootPathOrDir,		// e.g. "c:\\"  or  "c:\\t"。if you don't specify the rootdir, it will be '\\'
								std::string strPattern,				//e.g. "*.mp3"	"*"
								std::vector<std::string> & vecstrRtnBuf	, 
								tbool bIncludeDirName  = 0 ,
								tbool bIncludeFileName = 1 , 
								tbool bRetFullName     = 0 ,
								tbool bRecursive       = 0	)
	{
		//we don't clear vecstrRtnBuf, so, you can append filenames

		if( bRecursive )
		{
			std::vector<std::string>  vecBuf1;
			std::vector<std::string>::iterator itBuf1;
			std::vector<std::string>  vecBuf2;
			std::vector<std::string>  vecBuf_FullName;

			vecBuf1.push_back( strRootPathOrDir );

			do{
				vecBuf2.clear();

				itBuf1 = vecBuf1.begin();

				if( itBuf1 == vecBuf1.end() ) 
				{
					break;
				}

				ListFile( *itBuf1, "*", vecBuf2, 1, 0, 1 ); //record what next to do .
				vecBuf_FullName.insert( vecBuf_FullName.end(), vecBuf2.begin(), vecBuf2.end() ); 

				vecBuf1.erase( itBuf1 ); //del the processed folder

				vecBuf1.insert( vecBuf1.end(), vecBuf2.begin(), vecBuf2.end() ); //insert the new found folders.

			}while(1);

			if( 1 )
			{
				for( std::vector<std::string>::iterator it = vecBuf_FullName.begin();
					 it != vecBuf_FullName.end();
					 ++it )
				{
					ListFile( *it, strPattern, vecstrRtnBuf, bIncludeDirName, bIncludeFileName, bRetFullName ); //record the result.
				}
				ListFile( strRootPathOrDir, strPattern, vecstrRtnBuf, bIncludeDirName, bIncludeFileName, bRetFullName );
			}
		}
		else
		{
			ListFile( strRootPathOrDir, strPattern, vecstrRtnBuf, bIncludeDirName, bIncludeFileName, bRetFullName );
		}
	}



	//
	static void DelHalf( std::string strRootDir, std::string strPattern )			//e.g. "*.mp3"	"*", but this func is slow
	{
		std::vector<std::string>  vecstrRtnBuf;

		ListFile( strRootDir, strPattern, vecstrRtnBuf, 0, 1, 1 );

		for( std::vector<std::string>::iterator it1 = vecstrRtnBuf.begin(); it1 != vecstrRtnBuf.end(); ++it1 )
		{
			for( std::vector<std::string>::iterator it2 = vecstrRtnBuf.begin(); it2 != vecstrRtnBuf.end(); ++it2 )
			{
				SFile f1, f2;
				f1.bind( *it1 );
				f2.bind( *it2 );
				if( f1.IsHeadOf(f2) ) f1.erase();
			} // end for it2
		} // end for it1 
	}



		struct FileStat_t
		{ 
			std::string strFullFn;
			std::string strFileDSeal;
			tsize iFileLen;
			tbool tbExists;
		} ;
		//
	static void DelHalf_fast( std::string strRootDir, std::string strPattern, tsize iMinLen )			//e.g. "*.mp3"	"*", but this func is fast
	{
		std::vector<std::string>  vecstrRtnBuf;
		std::vector<FileStat_t>  vecFileStat;

		ListFile( strRootDir, strPattern, vecstrRtnBuf, 0, 1, 1 );

		for( std::vector<std::string>::iterator it1 = vecstrRtnBuf.begin(); it1 != vecstrRtnBuf.end(); ++it1 )
		{
			SFile fl ;
			SCake ck;
			FileStat_t fs;

			fl.bind( *it1 );
			fs.strFullFn = *it1;
			fs.iFileLen = fl.len();
			fs.tbExists = fs.iFileLen < iMinLen ? 0 : 1 ;
			if( !fs.tbExists )
			{
				fl.erase();
				continue;
			}
			fl.read( ck );
			fs.strFileDSeal = SCalc::dseal( ck.buf(), iMinLen, 123 );

			vecFileStat.push_back( fs );
		} // end for it1 


		//.now traverse the dseal
		for( std::vector<FileStat_t>::iterator it2 = vecFileStat.begin(); it2 != vecFileStat.end(); ++it2 )
		{
			for( std::vector<FileStat_t>::iterator it3 = vecFileStat.begin(); it3 != vecFileStat.end(); ++it3 )
			{
				if( !(it2->tbExists && it3->tbExists) ) continue;
				if( it2->strFileDSeal != it3->strFileDSeal ) continue;
				if( it2->strFullFn == it3->strFullFn ) continue;
				
				std::vector<FileStat_t>::iterator it4 = it3;
				if( it2->iFileLen < it3->iFileLen ) it4 = it2;
				
				SFile::erase( it4->strFullFn );
				it4->tbExists = 0;

				printf( "%s\n", it4->strFullFn.c_str() );
			} // end for it3
		} // end for it2 

	}



	tbool bind_tmpfile( const tchar * pszExt = NULL , int iThreadId = 0 ) //GetCurrentThreadId()
	{
		std::string  strEnvTmpPath;
		strEnvTmpPath = "/tmp/";
		if( strEnvTmpPath == "" ) return 0;
		return bind_nofile( strEnvTmpPath, pszExt, iThreadId );
	}



	//pack和unpack,在vaio上测试，906M的目录，读取用4分钟，写盘用5分钟。共约9分钟。
	static void PackFolder( std::string strWorkPathOrDir, SCake & ckOut )
	{
		//std::vector<tchar> v1;
		std::string strWorkPath;
		std::vector<std::string>::iterator it;
		std::vector<std::string> vDirFullNameLst;
		std::vector<std::string> vDirNameLst;
		std::vector<std::string> vFileFullPathNameLst;
		std::vector<std::string> vFileRelaPathNameLst;
		std::vector<std::string> vFileLenLst;
		std::string strInfoHeader;

		//TR use 0, TD use 1
		std::string strTD = "\t"; 
		std::string strTR = "\n";


		strWorkPath = MkDir2Path( strWorkPathOrDir ) ;


		//get vDirNameLst

		ListAllFile( strWorkPath, "*.*", vDirFullNameLst, 1, 0, 1, 1 );

		for( it = vDirFullNameLst.begin(); it != vDirFullNameLst.end(); ++it )
		{
			const char *p;
			p = it->c_str() + strWorkPath.size();
			vDirNameLst.push_back(p);
		}

		//distinct vDirNameLst

		SSetu::vs_setgroup( vDirNameLst );


		//get file rela_path name
 
		ListAllFile( strWorkPath, "*.*", vFileFullPathNameLst, 0, 1, 1, 1 );

		for( it = vFileFullPathNameLst.begin(); it != vFileFullPathNameLst.end(); ++it )
		{
			const char *p;
			p = it->c_str() + strWorkPath.size();
			vFileRelaPathNameLst.push_back(p);
		}
	 

		//get file len

		tint32 iLenAmount=0;

		for( it = vFileFullPathNameLst.begin(); it != vFileFullPathNameLst.end(); ++it )
		{
			SFile sf;
			tint32 i;

			sf.bind( *it );
			i = sf.len();
			iLenAmount += i;
			vFileLenLst.push_back( SStrf::sltoa( i ) );
		}


		//create 3 info_list to a InfoHeader
		
		for( it = vDirNameLst.begin(); it != vDirNameLst.end(); ++it )
		{
			strInfoHeader += *it;
			strInfoHeader += strTD;  
		}
		strInfoHeader += strTR;

		for( it = vFileRelaPathNameLst.begin(); it != vFileRelaPathNameLst.end(); ++it )
		{
			strInfoHeader += *it;
			strInfoHeader += strTD;  
		}
		strInfoHeader += strTR;

		for( it = vFileLenLst.begin(); it != vFileLenLst.end(); ++it )
		{
			strInfoHeader += *it;
			strInfoHeader += strTD;  
		}
		strInfoHeader += strTR;



		//get file bin

		ckOut.redim( iLenAmount + (tsize)strInfoHeader.size() + 1 );

		tchar *p1;

		p1 = ckOut.buf();

		//put info header
		SStrf::smemcpy( p1, strInfoHeader.c_str(), (tsize)strInfoHeader.size() );
		p1 += (tsize)strInfoHeader.size();

		*p1 = 0;
		p1 ++;

		std::vector<std::string>::iterator it2;

		it2 = vFileLenLst.begin();
		for( it = vFileFullPathNameLst.begin(); it != vFileFullPathNameLst.end(); ++it, ++it2 )
		{
			SCake ck;
			SFile sf;

			sf.bind( *it );
			sf.read( ck );

			if( ck.len() )
			{
				SStrf::smemcpy( p1, ck.buf(), (tint32)ck.len() <  SStrf::satol( *it2 ) ? (tint32)ck.len() :  SStrf::satol( *it2 ) );				
			}

			//p1 += ck.len();
			p1 += SStrf::satol( *it2 );
		}

	}


 
	static void UnPackFolder( std::string strWorkPathOrDir, const SCake & ckIn , std::vector<std::string> *pvDirFullNameLst = NULL, std::vector<std::string> *pvFileFullPathNameLst = NULL )
	{
		if( ckIn.len() == 0 ) return;
		
		//std::for_each( ckIn.buf(), ckIn.buf() + ckIn.len(), xor2() );

		//std::vector<tchar> v1;
		std::string strWorkPath;
		std::vector<std::string>::iterator it;
		std::vector<std::string> vDirFullNameLst;
		std::vector<std::string> vDirNameLst;
		std::vector<std::string> vFileFullPathNameLst;
		std::vector<std::string> vFileRelaPathNameLst;
		std::vector<std::string> vFileLenLst;
		std::string strInfoHeader;

		
		//TR use 0, TD use 1
		std::string strTD = "\t";
		std::string strTR = "\n";

		strWorkPath = MkDir2Path( strWorkPathOrDir ) ;

		strInfoHeader = (const char*)ckIn.buf_const();


		//create all DIRs

		SStrvs::vsa_imp( SStrvs::vsa_get( strInfoHeader, strTR, 0, 0 ), strTD, 1, vDirNameLst );

		std::sort( vDirNameLst.begin(), vDirNameLst.end() ); //此时可以保证短的目录名在前,CreateDirectory可以逐级正常工作了.

		for( it = vDirNameLst.begin(); it != vDirNameLst.end(); ++it )
		{
			std::string s1;
			s1 = MkDir2Path( strWorkPathOrDir ) + *it ;
			vDirFullNameLst.push_back( s1 );

			//CString cs1;
			//cs1 = s1.c_str();
			//::CreateDirectory( cs1, NULL );
			//::SHCreateDirectoryEx(NULL, cs1, NULL);

			mkdir(s1.c_str(), 0777); 
		}


		//get all full filenames

		SStrvs::vsa_imp( SStrvs::vsa_get( strInfoHeader, strTR, 0, 1 ), strTD, 1, vFileRelaPathNameLst );

		for( it = vFileRelaPathNameLst.begin(); it != vFileRelaPathNameLst.end(); ++it )
		{
			std::string s1;
			s1 = MkDir2Path( strWorkPathOrDir ) + *it ;
			vFileFullPathNameLst.push_back( s1 );
		}


		//get all file len

		SStrvs::vsa_imp( SStrvs::vsa_get( strInfoHeader, strTR, 0, 2 ), strTD, 1, vFileLenLst );


		//return lists
		if( pvDirFullNameLst != NULL ) *pvDirFullNameLst = vDirFullNameLst;
		if( pvFileFullPathNameLst != NULL ) *pvFileFullPathNameLst = vFileFullPathNameLst;


		//create all files

		const tchar *p1;

		p1 = ckIn.buf_const() + strInfoHeader.size() + 1;

		//v1.insert( v1.end(), ckIn.buf_const() + strInfoHeader.size() + 1 , ckIn.buf_const() + ckIn.len() );
		//ckIn.redim(0); //ckIn is useless now, free the memory.

		for( ; !vFileFullPathNameLst.empty(); )
		{
			std::string s1;
			tint32 i1;

			s1 = vFileFullPathNameLst.front();
			i1 = SStrf::satol( vFileLenLst.front() );

			if( p1 > ckIn.buf_const() + ckIn.len() ) break;

			SFile sf;

			sf.bind( s1 );

			sf.write( p1, (tsize)i1 );

			vFileFullPathNameLst.erase( vFileFullPathNameLst.begin() );
			vFileLenLst.erase( vFileLenLst.begin() );

			p1 += i1;
		}
		
	}


	////////////convert code


	static void lf_conv_code( std::string & s , const char *tocode, const char *fromcode )
	{
		iconv_t cd = iconv_open( tocode, fromcode );
		unsigned int inlen  = strlen(s.c_str());
		char *outbuf = (char *)malloc(inlen * 4 );
		memset( outbuf, (int)0, inlen * 4);
		char *in2 = (char*)s.c_str(); 
		char *out2 = outbuf;
		size_t outlen = inlen *4;
		iconv(cd, &in2, (size_t *)&inlen, &out2, &outlen);
		outlen = strlen(outbuf);
		//printf("%s\n",outbuf);
		s = outbuf;
		free(outbuf); 
		iconv_close(cd); 
	}

	
	static std::string & ChtoUtf8( std::string & s )
	{
		lf_conv_code( s, "UTF-8", "GBK" );
		return s;
	}


	static std::string & Utf8toCh( std::string & s )
	{
		lf_conv_code( s, "GBK", "UTF-8" );
		return s;
	}



};//end class WFile





X011_NAMESPACE_END


#endif





/*
WNava , nava with utf8 <--> ch converter
*/

#ifndef X011__H_W_WNAVA_H
#define X011__H_W_WNAVA_H



X011_NAMESPACE_BEGIN



class WNava : public SNavass 
{
private:


public:

	virtual ~WNava() {;} 


	//static tbool IsUtf8Base()	// 本文件必须在结合成1.h以后以utf8形式保存,才能使win与linu下自动产生正确结果.平时不用.或结合项目仿照此另做函数完成相同任务.
	//{
	//	const char * p = "初";
	//	return p[2] ? 1 : 0 ;
	//}


	
	void impconf( const std::string & ssource, std::string ssepTR = "\n", std::string ssepTD = "=", std::string strMemoLineHead = "#" )
	{
		//以下算法，数据中允许有TD

		std::vector<std::string>  vecLines;
		SStrvs::vsa_imp( ssource, ssepTR, 1, vecLines );
		for( std::vector<std::string>::iterator it = vecLines.begin(); it != vecLines.end(); ++it )
		{
			std::string::size_type i;

			i = it->find(ssepTD);
			if( i == std::string::npos ) continue;

			SStrf::strim( *it );
			if( it->find(strMemoLineHead) == 0 ) continue;

			(*it)[i] = 0;
			this->let( it->c_str(), it->c_str() + i + ssepTD.size() );
		}

		this->trimall();
	}


	typedef std::string & (* P_t) ( std::string & );


	void AtoB( P_t pf )
	{
		std::map< std::string, std::string > mapTmp = m_mapKnl;

		this->clear();

		for( MAP_MAPKNL_IT it = mapTmp.begin(); it != mapTmp.end(); ++it )
		{
			std::string s1 = it->first;
			std::string s2 = it->second;

			(*pf)( s1 );
			(*pf)( s2 );

			let( s1, s2 ); 
		}
	}


	void ChtoUtf8()
	{
		AtoB( WFile::ChtoUtf8 );
	}

	void Utf8toCh()
	{
		AtoB( WFile::Utf8toCh );
	}


};




X011_NAMESPACE_END

#endif




/*
linux thread class
*/



#ifndef X011__H_w_wthrd_h
#define X011__H_w_wthrd_h




X011_NAMESPACE_BEGIN



class WThrd
{

private:

	pthread_t   m_hThread;	//handle to thread knl 
	volatile int m_iAutoDel;
	volatile int m_iShouldBreak;
	volatile int m_iLive;
	volatile int m_iShouldDetach;
	volatile int m_iOpened;


	static void * ThreadProc(void * lpParam)
	{
		WThrd *pThis=reinterpret_cast<WThrd*>(lpParam);
		
		pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL); //pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);

		try
		{
			pThis->tr_on_knl_run();

			pThis->tr_shouldbrk();

			pThis->m_iLive = 0;

			if(pThis->m_iAutoDel)
			{
				try
				{
					delete pThis;
				}
				catch (...)
				{
					return((void *)0); 
				}
			}
			return((void *)0);
		}
		catch(...)
		{
			try
			{
				delete pThis;
			}
			catch (...)
			{
				return((void *)0);
			}
			return((void *)0);
		}
		return((void *)0);
	}


private:

	WThrd & operator = (const WThrd & rhs)
	{
		return *this;
	}


	WThrd(const WThrd & rhs)
	{;}


public:

	WThrd()
	{
		//m_hThread = INVALID_HANDLE_VALUE; 
		m_iAutoDel = 0;
		m_iShouldBreak = 0;
		m_iLive = 0;
		m_iShouldDetach = 1;
		m_iOpened = 0;
	}


	virtual ~WThrd()
	{
		if( !m_iOpened ) return;

		try
		{
			tr_shouldbrk();

			//if( tr_wait( 4567 ) ) //如果是Heap型自删除的，则析构总是在本线程中执行，wait等于自己等自己，肯定要永远wait.如果是栈型变量，则析构是在主线程中执行的，与本类的run肯定不在同一线程中，所以看上去能行。
			//{
			//	//tr_Terminate();
			//	Beep(234,9);
			//	Beep(1294,9);
			//	Beep(234,9);
			//	return;
			//}

			if( m_iAutoDel )
				if( m_iShouldDetach ) pthread_detach(m_hThread);  

			if( !m_iAutoDel )
				pthread_join( m_hThread , NULL );

			tr_closehandl();
		}
		catch(...)
		{; }
	}


public:

	static std::string tr_GetCurrentThreadId()
	{
		char sz1[22];
		SClib::p_sprintf()( sz1, "%p", pthread_self() );
		return sz1;
	}


	pthread_t tr_GetHnd() const
	{
		return m_hThread;
	}


	static void tr_sleep( int iSec , double dSec = 0.0 )	// 参数为整数秒和小于一秒的小数秒。  
	{
		if( iSec > 0 )
			sleep( iSec );

		if( dSec > 0.0 )
		{
			usleep( static_cast<int>(dSec * 1000 * 1000) );
		}
	}


	void tr_open()
	{
		//m_hThread = INVALID_HANDLE_VALUE;

		m_iLive = 1;

		//C ver
		int err;

		err = pthread_create( &m_hThread, NULL,  //NULL，则表明我们希望所创建的线程采用默认的属性，也就是jionable。在线程设置为joinable后，可以调用pthread_detach()使之成为detached。但是相反的操作则不可以。还有，如果线程已经调用pthread_join()后，则再调用pthread_detach()则不会有任何效果。
										ThreadProc, reinterpret_cast<void*>(this) );

		if(err != 0) m_iLive = 0;

		if( tr_isRunning() )
		{
			m_iOpened = 1;
		}
	}



	void tr_openx() //if openx, don't wait this thread. because it will be deleted any time. don't call any func out side the obj in other thrd.
	{
		m_iAutoDel = 1;
		tr_open();
	}



	void tr_shouldbrk()
	{
		m_iShouldBreak = 1;
	}


	int tr_isShouldBrk() const
	{
		return m_iShouldBreak;
	}



	int tr_isRunning()
	{
		 return m_iLive;//由于无法自动地从不运行转化到运行状态，所以此函数主要用于探测是否已经从运行变为了不运行状态。
	}


	void tr_Terminate()
	{
		if( !m_iOpened ) return;

		try
		{
			if( tr_isRunning() )
			{
				//kill this pthread
				//int pthread_cancel(pthread_t thread) 
				pthread_cancel(m_hThread); //发送终止信号给thread线程，如果成功则返回0，否则为非0值。发送成功并不意味着thread会终止。 
			}
		}
		catch (...)
		{	;
		}
	}





	void tr_closehandl()
	{
		tr_shouldbrk();
	}


	//wait to thread end. 
	//if timeout then 1, means thread living.
	//if invalid thread then 0,
	//if wait to thread end then means thread dead. then 0.
	int tr_wait( /*DWORD dwMilliseconds=INFINITE*/ )
	{
		if( !m_iOpened ) return 0;

		pthread_join( m_hThread , NULL );
		
		m_iAutoDel = 0;
		m_iShouldDetach = 0;
		 
		return 0;
	}



	virtual void tr_on_knl_run()
	{
		while(1)
		{
			if( !tr_on_user_run() ) break;

			if( m_iShouldBreak ) break;
	
			pthread_testcancel();/*the thread can be killed only here*/
		}
	}
 


	virtual int tr_on_user_run() //return 0 will cause knl_run break;
	{
		return 0;
	}


	virtual tbool tr_OnMgrPrepare() // for WThrdMgr 
	{
		return 1;
	}

}; //end class 




 


///=================================================city

/////////
///
///
//






X011_NAMESPACE_END

#endif




/*
 
thread mgr, use with ele and env
*/

// 


#ifndef X011__H_W_WTHRDMGR_H
#define X011__H_W_WTHRDMGR_H


 


X011_NAMESPACE_BEGIN

 

//====================================================WThrdMgr

/*
用法是:
每一个工作原子是继承thrd,并需要env pointer。ele里只有算法，没有建立连接的过程，不要等待。but maybe recv and wait.
继承WThrdMgr，并指出工作原子。有env成员
重写OnMgrPrepare，为每个ele赋予env的指针.
也许重写tr_OnMgrPrepare()
这2个重写是真正block住的地方。
外界同步调用BirthEle，或启动本线程使其异步工作。
*/

template < class ThreadEle_T > 
class WThrdMgr : public WThrd 
{
private:


public:
	typedef		ThreadEle_T	 	ThrEle_t;
	volatile tbool  m_biMgrShouldBreak;
	int  m_iFailWaitTimesec; // if birth fail, wait this.
	tbool  m_biIsMultiEleType;

public:
	WThrdMgr()
	{
		m_biMgrShouldBreak = 0;
		m_iFailWaitTimesec = 3;
		m_biIsMultiEleType = 1;
	}

	virtual ~WThrdMgr()
	{;	}

	
	virtual tbool OnMgrPrepare( ThrEle_t & t ) // use 引用是表明到此处时必有对象存在 而不可能是NULL pointer   
	{
		return 1;
	}


	virtual int tr_on_user_run() 
	{
		BirthEle();
		return 0;
	}


	virtual ThrEle_t * MgrPrepare()   // new an ele, set its para, return the pointer. if fail, delete the pointer, return NULL. i'll not open or openx here.
	{
		ThrEle_t * p = new ThrEle_t;

		if( !p ) return NULL;

		if( !OnMgrPrepare(*p) ) /// 先准备环境 
		{
			delete p;
			return NULL;
		}

		if( ! p->tr_OnMgrPrepare() ) // 再准备个体  
		{
			delete p;
			return NULL;
		}
		
		return p;
	}


	//entrance:

	void BirthEle()
	{
		for( ; ; )
		{
			if( m_biMgrShouldBreak ) break;
			
			if( tr_isShouldBrk() ) break;
			
			ThrEle_t * p = MgrPrepare();
			if( p != NULL )
			{
				if( m_biIsMultiEleType )
				{
					p->tr_openx();
				}
				else  
				{
					p->tr_open();
					p->tr_wait();
					delete p;
				}
			}
			else
			{
				WThrd::tr_sleep( m_iFailWaitTimesec > 0 ? m_iFailWaitTimesec : 2 );
			}
		}
	}

};


 



X011_NAMESPACE_END

#endif



//应用案例: 
//
//class AEle : public wl::WThrd 
//{
//public:
//	wl::WTcpListener * m_pLsn;
//	wl::WTcpCells  m_tSvr;
//	
//
//	virtual int tr_on_user_run() 
//	{
//		wl::WTcpCells &tSvr(m_tSvr);
//
//		for(;;)
//		{
//			wl::SCake ck;
//			char s[222];
//			
//			tSvr.recv_len( ck, 1 );
//			if( ck.len() == 0 ) break;
//
//			printf(     "`%c` %d\r\n", *ck.buf(), *ck.buf() );
//			sprintf( s, "`%c` %d\r\n", *ck.buf(), *ck.buf() );
//			tSvr.send_str( s );
//
//			if( *ck.buf() == 27 ) break;
//		}
//
//		return 0;
//	}
//};
//
//
//class AMgr : public wl::WThrdMgr< AEle>
//{
//public:
//	wl::WTcpListener  m_Lsn;
//
//	AMgr()
//	{
//		m_Lsn.Listen( 7878 );
//		m_biIsMultiEleType = 0;
//	}
//
//	virtual ~AMgr() { ; }
//
//	virtual wl::tbool OnMgrPrepare( ThrEle_t & t ) // 
//	{
//		t.m_pLsn = &m_Lsn;
//		
//		if( !t.m_tSvr.Conn( m_Lsn ) ) return 0;
//		//t.m_tSvr.killer_up(6);
//
//		return 1;
//	}
//
//};
//
//
//
//
//void test_tcpserver()
//{
//	AMgr a;
//
//	a.BirthEle();
//}
//


/*
w_WSnd  sound
*/



#ifndef X011__w_WSnd_H
#define X011__w_WSnd_H



/* filename: wavplay.c */

#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <linux/soundcard.h>



X011_NAMESPACE_BEGIN



class WSnd
{
public:
	
	struct RIFF_Header{
		char RIFF_ID[4];
		uint32_t RIFF_Size;
		char RIFF_Format[4];
	};

	struct Chunk_Header{
		char Chunk_ID[4];
		uint32_t Chunk_Size;
	};

	struct Wave_Format{
		uint16_t AudioFormat;
		uint16_t NumChannels;
		uint32_t SampleRate;
		uint32_t AvgBytesPerSec;
		uint16_t BlockAlign;
		uint16_t BitsPerSample;
	};

public:
	virtual ~WSnd() {;}

public:

	static void PlayWav( std::string strFile )
	{
		struct RIFF_Header riff_header;
		struct Chunk_Header fmt_chunk, data_chunk;
		struct Wave_Format wavfmt;

		char buf[512];
		FILE * fwave;
		int sndfd;        
		int status;
		int arg;
		int readbytes;
		int writebytes;
		int writed;

		fwave = fopen( strFile.c_str(), "r");
		if( fwave == NULL )
		{
			return;
		}

		fread(&riff_header, 1, sizeof(struct RIFF_Header), fwave);
		if( strncmp(riff_header.RIFF_ID, "RIFF", 4) || strncmp(riff_header.RIFF_Format, "WAVE",4))
		{
			return;
		}

		sndfd = open("/dev/dsp", O_RDWR);
		if (sndfd < 0)
		{
			return;
		}

		fread(&fmt_chunk, 1, sizeof(struct Chunk_Header), fwave);
		if( !strncmp(fmt_chunk.Chunk_ID, "fmt ", 4) )
		{
			/* this is a fmt chunk */
			fread(&wavfmt, 1, sizeof(struct Wave_Format), fwave);

			arg = wavfmt.BitsPerSample;
			status = ioctl(sndfd, SOUND_PCM_WRITE_BITS, &arg);
			if (status == -1)
				perror("SOUND_PCM_WRITE_BITS ioctl failed");
			if (arg != wavfmt.BitsPerSample)
				perror("unable to set sample size");

			arg = wavfmt.NumChannels; 
			status = ioctl(sndfd, SOUND_PCM_WRITE_CHANNELS, &arg);
			if (status == -1)
				perror("SOUND_PCM_WRITE_CHANNELS ioctl failed");
			if (arg != wavfmt.NumChannels)
				perror("unable to set number of channels");

			arg = wavfmt.SampleRate;
			status = ioctl(sndfd, SOUND_PCM_WRITE_RATE, &arg);
			if (status == -1)
				perror("SOUND_PCM_WRITE_WRITE ioctl failed");

			/* skip extra bytes */
			fseek(fwave, fmt_chunk.Chunk_Size - 16 + fmt_chunk.Chunk_Size%2, SEEK_CUR);
		}
		else
		{
			return;
		}

		while( fread(&data_chunk, 1, sizeof(struct Chunk_Header), fwave) != 0 )
		{
			if( !strncmp(data_chunk.Chunk_ID, "data", 4) )
			{
				//printf("Begin Play\n");
				/* this is a data chunk */
				writed = 0;
				while(writed < data_chunk.Chunk_Size)
				{
					readbytes = fread(buf, 1, 512, fwave);
					writebytes = write(sndfd, buf, readbytes);
					if( writebytes != readbytes )
						perror("wrote wrong number of bytes");
					writed += readbytes;
				}
			}
			else
			{
				/* skip unknown chunks */
				fseek(fwave, data_chunk.Chunk_Size + fmt_chunk.Chunk_Size%2, SEEK_CUR);
			}
		}

		fclose(fwave);
		close(sndfd);

		return;
	}
};






X011_NAMESPACE_END

#endif





/*
W series
tcp cell base: WTcpDisConnable
*/

// 

#ifndef X011__H_w_WTcpDisConnable_h
#define X011__H_w_WTcpDisConnable_h


X011_NAMESPACE_BEGIN


class WTcpDisConnable : public IRice
{

private:

	WTcpDisConnable & operator = (const WTcpDisConnable & rhs)
	{
		return *this;
	}

	WTcpDisConnable(const WTcpDisConnable & rhs)
	{;}


public:
	class MyTimeKiller : public WThrd 
	{
	public:
		WTcpDisConnable * m_ph;
		int  m_i;
		int  m_iMaxSec;
		double  m_d;
		double  m_dMaxSec2;

		MyTimeKiller( WTcpDisConnable * ph, int iMaxSec, double dMaxSec2 = 0.0 )
		{
			m_ph = ph;
			m_i = 0;
			m_iMaxSec = iMaxSec;
			m_d = 0.0;
			m_dMaxSec2 = dMaxSec2;
		}

		virtual ~MyTimeKiller()
		{
			m_i = 0;
			tr_shouldbrk();

			//openx时,就是m_iAutoDel,此时不能析构时等自己.//tr_wait();
			//本例中是用open()打开线程，在基类中已经做好，会析构等自己。
			//一切取决于析构是不是本线程。如果是本线程同时负责析构，这时就会自己等自己而死锁.
		}


		virtual int tr_on_user_run()
		{
			if( m_i <= m_iMaxSec )
			{
				m_i++;
				if( m_i > m_iMaxSec )
				{
					//if(m_ph) m_ph->DisConn();
					//return 0;
				}
				else
				{
					WThrd::tr_sleep(1);
					return 1;
				}
			}

			if( m_d < m_dMaxSec2 ) // return as many as possible. we want many chances to Not to disconn and to end this thrd.
			{
				m_d += m_dMaxSec2;
				WThrd::tr_sleep( 0 , m_dMaxSec2 );
				return 1;
			}

			if( this->tr_isShouldBrk() ) return 0;

			if(m_ph) m_ph->DisConn();
			return 0;
		}
	};


	MyTimeKiller * m_pkiller;


	void killer_up( int iMaxSec ) //超时就会形成类似对方断线的效果。构造时即启动线程 
	{
		killer_dn() ;
		m_pkiller = new MyTimeKiller( this, iMaxSec );
		m_pkiller->tr_open();
	}


	void killer_dn() 
	{
		if( m_pkiller != NULL )
		{
			delete m_pkiller;
			m_pkiller = NULL;
		}
	}

public:

	WTcpDisConnable()
	{
		m_pkiller = NULL;
	}

	virtual ~WTcpDisConnable()
	{
		killer_dn() ;         
	}


 
	virtual void DisConn()  // CDUP\net\w_WMoonMan.h中重写本方法，但又调用了本方法，以便利用本方法中所定义的行为，而且虚函数OnDisConn()的调用又让控制权回到了 w_WMoonMan.h
	{
		/* IRice:: */ ClearL2Cache();

		OnDisConn();
	}


public:

	virtual void OnDisConn() { ; } // 让它有函数体而不是=0，为了防止在子类都析构了但本类还未析构时突然发生timekill，调用空函数之错。


}; //end class 




X011_NAMESPACE_END

#endif





/*
W series
tcp cell 
*/

// 

#ifndef X011__H_w_wtcp_cell_h
#define X011__H_w_wtcp_cell_h


X011_NAMESPACE_BEGIN


class WTcpCell : public WTcpDisConnable 
{
		
protected:

	SOCKET			m_socRemote;


private:

	WTcpCell & operator = (const WTcpCell & rhs)
	{
		return *this;
	}

	WTcpCell(const WTcpCell & rhs)
	{;}


public:

	WTcpCell()
	{
		m_socRemote = INVALID_SOCKET;
		 
	}

	virtual ~WTcpCell()
	{
		DisConn();
	}


public:

	SOCKET GetRemoteSoc () const
	{
		return m_socRemote;
	} 
	

	static std::string getselfname()
	{
		tchar ss[1024] = {0};
		gethostname(ss,1024);  //机器的主机名
		return ss;
	}


	static std::string getipbyname( std::string name )
	{
		hostent * host;
		std::vector<std::string> vecNameParts;

		wl::SStrvs::vsa_imp( name, std::string("."), 1, vecNameParts );
		if( vecNameParts.size()==4 &&
			SStrf::sisdec(vecNameParts[0].c_str()) &&
			SStrf::sisdec(vecNameParts[1].c_str()) &&
			SStrf::sisdec(vecNameParts[2].c_str()) &&
			SStrf::sisdec(vecNameParts[3].c_str())		)
			return name;

		if( name.size() == 0 )
			name = getselfname();

		host = gethostbyname(name.c_str());

		if(host==NULL)
			return "";

		if( host->h_addr_list[0] )
		{
			struct in_addr addr;
			memmove( &addr, host->h_addr_list[0], 4 );
			return inet_ntoa(addr);
		}

		return "";
	}


	static std::string getnamebyip( std::string strIP )
	{
		DWORD dwIPAddr;
		dwIPAddr = inet_addr(strIP.c_str());//strIP是IP地址,字符串，如192.168.0.1。
		if(dwIPAddr == INADDR_NONE)
		{
			return "";//IP地址不合法
		}
		else
		{
			hostent * p=gethostbyaddr( (const char *)&dwIPAddr, 4, PF_INET ); //这里要强制转换，很多初学者常常卡在这里了。
			if(!p)
			{
				return "";//找不到相应的名字。
			}
			else
			{
				return p->h_name;//找到名字了，字符串。
			}
		}
	}



public:

	virtual void OnDisConn()
	{
		if( m_socRemote == INVALID_SOCKET ) return;

		try
		{	
			shutdown( m_socRemote, 2 ); 
			closesocket(m_socRemote); 
			m_socRemote = INVALID_SOCKET ;
		}
		catch(...) 
		{
			m_socRemote = INVALID_SOCKET;
		}
	}


public:

	virtual int on_get_defaultrecv_buf_len() //return the   len
	{
		return 255;
	}

	virtual int on_sys_recv( SCake & ckDataBuf ) //return the recv len
	{
		int iDefaultBufLen = on_get_defaultrecv_buf_len();
		ckDataBuf.redim( iDefaultBufLen );

		int i;
		SOCKET s = m_socRemote;

		if(s==INVALID_SOCKET)
		{
			return 0;
		}

		i = (int)::recv(s, ckDataBuf.buf(), (int)ckDataBuf.len(), 0);
		if(i==SOCKET_ERROR||i==0)
		{
			return i = 0;
		}

		ckDataBuf.cut( iDefaultBufLen-i );

		return i;
	}


	virtual int on_sys_send( const SCake & ckDataBuf ) //return the successfully sent len
	{
		int i;
		SOCKET s = m_socRemote;
		if(s==INVALID_SOCKET) return 0; //      if(len>66) len=66;

		i = (int)::send(s, ckDataBuf, (int)ckDataBuf.len(), 0);
		//i = (int)::send( s, ckDataBuf, (int)ckDataBuf.len() > 66 ? 66 : (int)ckDataBuf.len(), 0 );

		if(i==SOCKET_ERROR)
			i = 0;
		return i;
	}


}; //end class 




X011_NAMESPACE_END

#endif





/*
W series
tcp cellc
*/

// 

#ifndef X011__H_w_wtcp_cellc_h
#define X011__H_w_wtcp_cellc_h


X011_NAMESPACE_BEGIN


class WTcpCellc : public WTcpCell
{

private:

	WTcpCellc & operator = (const WTcpCellc & rhs)
	{
		return *this;
	}

	WTcpCellc(const WTcpCellc & rhs)
	{;}


public:


	WTcpCellc()
	{
	}



	virtual ~WTcpCellc()
	{
	}




	tbool Conn( std::string name, u_short port )
	{
		struct	sockaddr_in		saddr ;

		DisConn();

		m_socRemote = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );

		if( m_socRemote == INVALID_SOCKET )
		{
			return 0;
		}

		//we should zero mem here.
		SStrf::smemset( (void*)&saddr, 0, sizeof(saddr) );
	 
		saddr.sin_family = AF_INET; 
			//saddr.sin_addr.S_un.S_addr = inet_addr( getipbyname(name).c_str() );
			saddr.sin_addr.s_addr = inet_addr( getipbyname(name).c_str() );
		saddr.sin_port = htons( (u_short)port );

		if(SOCKET_ERROR == ::connect( m_socRemote, (struct sockaddr *)&saddr, sizeof(saddr) )  )
		{
			return 0;
		}

		return 1;
	}




	tbool Conn( std::string name, std::string port )
	{
		return this->Conn( name, static_cast<u_short>(SStrf::satol(port.c_str()) ) );
	}




	tbool Conn( std::string nameOraddr ) //like  192.168.1.29:2345  or  name.com:456
	{
		try
		{
			std::vector<std::string> vecNameParts;
			SStrvs::vsa_imp( nameOraddr, std::string(":"), 1, vecNameParts );
			vecNameParts.push_back( std::string("") );
			vecNameParts.push_back( std::string("") );
			return this->Conn( vecNameParts[0], vecNameParts[1] );
		}
		catch(...)
		{
			//printf("bad when %s\n", nameOraddr.c_str() );
			return 0;
		}
	}


}; //end class 




X011_NAMESPACE_END

#endif


/*
 为了socklen_t数据类型 
tcp cell Listener
*/

// 

#ifndef X011__H_w_WTcpListener_h
#define X011__H_w_WTcpListener_h


X011_NAMESPACE_BEGIN


class WTcpListener
{

private:

	SOCKET	m_socLocalListener;
	//std::string m_strRemoteIPAddress;


private:

	WTcpListener & operator = (const WTcpListener & rhs)
	{
		return *this;
	}

	WTcpListener(const WTcpListener & rhs)
	{;}


public:

	u_short		m_port;

	u_long		m_u_in_addr;


	WTcpListener( )
	{
		m_socLocalListener = INVALID_SOCKET;
		//m_strRemoteIPAddress="";
		m_port = 0;
	}

	virtual ~WTcpListener( )
	{
		this->StopListen();
	}


	//operator const std::string & ( ) const
	//{
	//	return m_strRemoteIPAddress;
	//}
    


	tbool Listen( u_short port,  u_long a_in_addrip = INADDR_ANY, int listener_num = 4 )
	{
		struct	sockaddr_in	 saddr;

		m_port = port;
		m_u_in_addr = a_in_addrip;

		if ( 0 == port )
		{
			//return 0;		port=0 means any available port, so, it is right.
		}
		
		m_socLocalListener = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );

		if( m_socLocalListener == INVALID_SOCKET )
		{
			return 0;
		}

		//we should zero mem here.
		SStrf::smemset( (void*)&saddr, 0, sizeof(saddr) );

		saddr.sin_family = AF_INET; 
		saddr.sin_port = htons( (u_short)port );
		saddr.sin_addr.s_addr = a_in_addrip;	//INADDR_LOOPBACK;//inet_addr(cf_getipbyname("",ss)); // ;//INADDR_ANY; //saddr.sin_addr.s_addr = inet_addr( "127.0.0.1" ); // ;//INADDR_ANY; 
		
		if( SOCKET_ERROR == bind( m_socLocalListener, (struct sockaddr *)&saddr, sizeof(saddr) ))
		{
			this->StopListen();
			return 0;
		}

		return 0 == ::listen( m_socLocalListener, listener_num )?1:0;
	}


	tbool Listen( u_short uport, const tchar * sz_addrip ) //bind an appointed ip
	{
		if( sz_addrip && *sz_addrip )
		{
			return this->Listen( uport, inet_addr( sz_addrip ) ) ;
		}
		
		return this->Listen( uport );
	}


	tbool Listen( std::string strport, const tchar * sz_addrip )
	{
		return this->Listen( (u_short)SStrf::satol(strport) , sz_addrip );
	}



	tbool Listen( std::string straddr ) //like  192.168.1.29:2345  or  name.com:456
	{
		try
		{
			std::vector<std::string> vecNameParts;
			SStrvs::vsa_imp( straddr, std::string(":"), 1, vecNameParts );
			if( vecNameParts.size() == 1 )
			{
				vecNameParts.insert( vecNameParts.begin(), std::string("") );
			}

			vecNameParts.push_back( std::string("") );
			vecNameParts.push_back( std::string("") );
			return Listen( vecNameParts[1], vecNameParts[0].c_str() );
		}
		catch(...)
		{
			return 0;
		}
	}



	void StopListen(void)
	{
		if( m_socLocalListener != INVALID_SOCKET )
		{
			closesocket( m_socLocalListener );
			m_socLocalListener = INVALID_SOCKET;
		}
	}


	tbool AcceptNewSvr( SOCKET & socNewSvr, std::string & strRtnRemoteIP )
	{
		struct	sockaddr_in	 from;
		socklen_t  nSize;

		if( m_socLocalListener == INVALID_SOCKET )
		{
			return 0;
		}

		nSize= sizeof(from);
		socNewSvr = ::accept( m_socLocalListener, (struct sockaddr *)&from, &nSize ); //socNewSvr now have a new value
		if( socNewSvr == INVALID_SOCKET )
		{
			strRtnRemoteIP = "";
			return 0;
		}
		else
		{
			strRtnRemoteIP = inet_ntoa( from.sin_addr ) ; //此时对方的port也是有意义的,不一定与本机的bind的port相同
			return 1;
		}
	}


}; //end class 




X011_NAMESPACE_END

#endif




/*
W series
tcp cells
*/

// 

#ifndef X011__H_w_wtcp_cells_h
#define X011__H_w_wtcp_cells_h


X011_NAMESPACE_BEGIN


class WTcpCells : public WTcpCell
{
	
public:

	std::string m_strRemoteIPAddress;


private:

	WTcpCells & operator = (const WTcpCells & rhs)
	{
		return *this;
	}

	WTcpCells(const WTcpCells & rhs)
	{;}


public:

	WTcpCells()
	{
		m_strRemoteIPAddress="";
	}


	virtual ~WTcpCells()
	{	m_strRemoteIPAddress="";
	}



	operator const std::string & () const
	{
		return m_strRemoteIPAddress;
	}



	std::string GetRemoteIPAddress() const
	{
		return m_strRemoteIPAddress;
	}



	tbool Conn( WTcpListener & aListener)
	{
		int iRc;

		iRc = aListener.AcceptNewSvr( m_socRemote , m_strRemoteIPAddress );

		if(!iRc) return 0;

		//m_strRemoteIPAddress = aListener; //本行会有多线程问题，改为用以上AcceptNewSvr带回IP.
		return 1;
	}


	tbool Conn( WTcpListener * pListener)
	{
		if(!pListener)
			return 0;

		return this->Conn(*pListener);
	}


}; //end class 




X011_NAMESPACE_END


#endif






/*
W series
com eli protocol 
*/

// 

#ifndef X011__H_w_WComeliProtocol_h
#define X011__H_w_WComeliProtocol_h


X011_NAMESPACE_BEGIN


class WComeliProtocol : public WTcpDisConnable 
{
		
public:

	tbool  m_biComportOpened;
	tbool  m_biShouldDisConn;


private:

	WComeliProtocol & operator = (const WComeliProtocol & rhs) 	{ 	return *this; }
	WComeliProtocol(const WComeliProtocol & rhs) {;}


public:

	WComeliProtocol()
	{
		m_biComportOpened = 0;
		m_biShouldDisConn = 0;
		 
	}

	virtual ~WComeliProtocol()
	{
		m_biComportOpened = 0;
		m_biShouldDisConn = 0;
	}


public:
 
	/////////////////////////////for com use, cake util

	typedef tuint8 (* PfChkSum_t) ( tuint8 a, tuint8 b );

	static tuint8 comesc_xor ( tuint8 a, tuint8 b ) { return a ^ b; };
	static tuint8 comesc_add ( tuint8 a, tuint8 b ) { return a + b; };


	static SCake & comesc_en( SCake & ckDataInOut, tuint8 a1, tuint8 a2, tuint8 a3 , PfChkSum_t pf = comesc_add, SCake * pdata2 = NULL ) // 
	{
		//ckDataInOut len ==0 也没关系

		tuint8  ucChkSum(0);
		std::vector<tuint8> v1;
		tuint8 c;

		//add a1
		v1.push_back(a1);

		//add data2
		for( tsize i2 = 0; pdata2 && i2 < pdata2->len(); i2++ )
		{
			c = *(tuint8*)(pdata2->buf()+i2);
			if( c == a1 || c == a2 || c == a3 ) v1.push_back(a2);
			v1.push_back( c );
		}

		//add len
		c = static_cast<tuint8>( ckDataInOut.len() );
		if( c == a1 || c == a2 || c == a3 ) v1.push_back(a2);
		v1.push_back( c );

		//calc data
		for( tsize i = 0; i < ckDataInOut.len(); i++ )
		{
			c = *(tuint8*)(ckDataInOut.buf()+i);
			if( c == a1 || c == a2 || c == a3 ) v1.push_back(a2);
			v1.push_back(c);
		}

		//calc chk sum
		for( tsize i = 0; i < ckDataInOut.len(); i++ )
		{
			ucChkSum = (*pf)( ucChkSum, *(tuint8*)(ckDataInOut.buf()+i) );
		}
		c = ucChkSum;
		if( c == a1 || c == a2 || c == a3 ) v1.push_back(a2);
		v1.push_back(c);

		//add a3
		v1.push_back(a3);

		//到这里v1必然有内容
		ckDataInOut.let( (tchar*)&(v1[0]), (tsize)v1.size() );
 
		return ckDataInOut;
	}


	static int comesc_de( SCake & ckDataInOut, tuint8 a1, tuint8 a2, tuint8 a3 , PfChkSum_t pf = NULL , SCake * pdata2 = NULL ) // return len indicated at beginning of data
	{
		if( ckDataInOut.len() != 0 )
		{
			std::vector<tuint8> v1;
			int flag = 1;

			//.......a1......a2...data...a2....data.....data.....a3......
			//    1       2      3     2     3       2        2      4

			for( tsize i = 0; i < ckDataInOut.len(); i++ )
			{
				tuint8 c = *(tuint8*)(ckDataInOut.buf()+i);
				tuint8 c2;
				
				
				if( flag == 1 )
				{
					if( c == a1 && i == 0 )
					{
						flag = 2;
						continue;
					} 

					if( c == a1 && i != 0 )
					{
						tuint8 c0 = *(tuint8*)(ckDataInOut.buf()+i-1); // c0就是 c之前一个
						if( c == a1 && c0 != a2 ) // 在任意的前导垃圾中找到了起始符a1
						{
							flag = 2;
							continue;
						}
					}

					continue;
				}


				//here we meet the first ch after the a1
				//c
				if( i+1 < ckDataInOut.len() )
				{
					//取2个字节
					c2 = *(tuint8*)(ckDataInOut.buf()+i+1);

					if( c == a2 )
					{
						v1.push_back( c2 );
						i++;
					}
					else
					{
						v1.push_back( c );
					}
				}
				else
				{
					//已经是最后一个字节了.
					if( c != a2 && c != a3 ) v1.push_back( c );
				}
			}//end for

			//到这里v1还不一定有内容
			if(v1.size()<2)
			{
				ckDataInOut.redim(0);
				return 0;
			}

			if( pdata2 != NULL && pdata2->len() != 0 )
			{
				if( v1.size() - pdata2->len() < 2 )
				{
					ckDataInOut.redim(0);
					return 0;
				}

				for( tsize i2 = 0; i2 < pdata2->len(); i2++ )
				{
					tuint8 c = v1[0];
					*(tuint8*)(pdata2->buf()+i2) = c;
					v1.erase( v1.begin() );
				}
			}

			//here we got LEN,DATA,BCC
			if( v1.size() == 2 )
			{
				ckDataInOut.redim(0);
				return v1[0];
			}

			//here we got LEN,DATA,BCC and DATA>=1
			{
				tuint8 ilen = v1[0];
				tuint8 iChkSum = v1[v1.size()-1];
				v1.erase( v1.begin() );
				v1.erase( v1.end() - 1 );
				
				ckDataInOut.let( (tchar*)&(v1[0]), (tsize)v1.size() );

				//calc chk sum
				if( pf )
				{
					tuint8  ucChkSum(0);

					for( tsize i = 0; i < ckDataInOut.len(); i++ )
					{
						ucChkSum = (*pf)( ucChkSum, *(tuint8*)(ckDataInOut.buf()+i) );
					}
					if( iChkSum != ucChkSum )
					{
						ckDataInOut.redim(0);
						return 0;
					}
				}

				if( ilen != ckDataInOut.len() )
				{
					ckDataInOut.redim(0);
					return 0;
				}

				return ilen;
			}
		}

		return 0;
	}



	/////////////////////////////for com use, recv


	tbool recv_comesc( SCake & ckData , tuint8 a2, tuint8 a3 ) 
	{
		SCake ckTmp;
		tsize i = 1;

		do
		{
			if( m_ckDataL2CacheBuf.len() >= 2 )
				for( ; i < m_ckDataL2CacheBuf.len(); i++ )
				{
					tchar c = *(m_ckDataL2CacheBuf.buf()+i);
					tchar c1 = *(m_ckDataL2CacheBuf.buf()+i-1);

					if( c1 != a2 && c == a3 )
					{
						goto L_RECV_ESC; //now i pointing to a3, the tail.
					}
				}

			if( !sys_recv( ckTmp ) ) break;

			m_ckDataL2CacheBuf.append(ckTmp);

		}while(ckTmp.len()>0);

L_RECV_ESC:
		ckData.redim(i+1);
		m_ckDataL2CacheBuf.dump( ckData );
		//ckData.esc_de(a1,a2,a3);
		return ckData.len()+m_ckDataL2CacheBuf.len()==0?0:1;
	}



public:
	
	virtual void OnDisConn()
	{
		m_biShouldDisConn = 1;
	}


	virtual int on_get_defaultrecv_buf_len() //return the buf len. we just want 1 byte.
	{
		return 1;
	}


}; //end class 




X011_NAMESPACE_END

#endif





/*
linux series , com eli cell
*/

// 

#ifndef X011__H_w_WComeliCell_h
#define X011__H_w_WComeliCell_h


X011_NAMESPACE_BEGIN


class WComeliCell : public WComeliProtocol 
{
		
protected:

	int   m_hComport;


private:

	WComeliCell & operator = (const WComeliCell & rhs) 	{ 	return *this; }
	WComeliCell(const WComeliCell & rhs) {;}

	//timeout
	int  m_itimeoutsec;
	int  m_itimeoutusec;

public:

	WComeliCell()
	{
		 
	}

	virtual ~WComeliCell()
	{
		if( m_biComportOpened )
		{
			close(m_hComport); // 关闭COM  
			m_biComportOpened = 0;
		}
	}


public:


	tbool Conn( std::string strname ) // "com=1;start=1;stop=1;speed=9600;parity=O/E/N;datalen=8;timeoutsec=0.150;"
	{
		DisConn();
		
		WNava nv;
		char ss[222];

		nv.impconf( strname, ";", "=" );

		if( nv.get("com").empty() ) return 0;

		(*SClib::p_sprintf())( ss, "/dev/ttyS%d", (int)SStrf::satol( nv.get("com") ) - 1 );

		m_hComport = open( ss, O_RDWR );

		if ( m_hComport < 0 ) 
		{
			// "串口打开失败";
			return 0;
		}

		m_biComportOpened = 1;


		if(1)
		{
			int speed_arr[] = { B50, B75, B110, B134, B150, B200, B300, B600, B1200, B1800, B2400, B4800, B9600, B19200, B38400, B57600, B115200, B230400 };
			int name_arr[] =  {  50,  75,  110,  134,  150,  200,  300,  600,  1200,  1800,  2400,  4800,  9600,  19200,  38400,  57600,  115200,  230400 };
			int i; 
			int status; 
			struct termios Opt;
			tcgetattr(m_hComport, &Opt); 
			for ( i= 0; i < sizeof(speed_arr) / sizeof(int); i++) 
			{ 
				if ( (int)SStrf::satol( nv.get("speed") ) == name_arr[i] ) 
				{ 
					tcflush(m_hComport, TCIOFLUSH); 
					cfsetispeed(&Opt, speed_arr[i]); 
					cfsetospeed(&Opt, speed_arr[i]); 
					status = tcsetattr(m_hComport, TCSANOW, &Opt); 
					if (status != 0) 
					{ 
						close(m_hComport); // 关闭COM  
						m_biComportOpened = 0;
						return 0;
					} 
					tcflush(m_hComport,TCIOFLUSH); 
					break;
				} 
			} // end for

			if( i >= sizeof(speed_arr) / sizeof(int) )
			{
				close(m_hComport); // 关闭COM  
				m_biComportOpened = 0;
				return 0;
			}
		}


		if(1)
		{ 
			struct termios options; 
			if ( tcgetattr( m_hComport,&options) != 0 ) 
			{ 
				close(m_hComport); // 关闭COM  
				m_biComportOpened = 0;
				return 0;
			}
			options.c_cflag &= ~CSIZE; 
			switch ( (tuint8)SStrf::satol( nv.get("datalen") ) ) 
			{ 
			case 7: 
				options.c_cflag |= CS7; 
				break;
			case 8:
				options.c_cflag |= CS8;
				break; 
			default: 
				close(m_hComport); // 关闭COM  
				m_biComportOpened = 0;
				return 0;
			}
			switch ( nv.get("parity")[0] ) 
			{ 
			case 'n':
			case 'N': 
				options.c_cflag &= ~PARENB; 
				options.c_iflag &= ~INPCK; 
				break; 
			case 'o': 
			case 'O': 
				options.c_cflag |= (PARODD | PARENB); 
				options.c_iflag |= INPCK;
				break; 
			case 'e': 
			case 'E': 
				options.c_cflag |= PARENB; 
				options.c_cflag &= ~PARODD; 
				options.c_iflag |= INPCK; 
				break;
			case 'S': 
			case 's': 
				options.c_cflag &= ~PARENB;
				options.c_cflag &= ~CSTOPB;
				break; 
			default: 
				close(m_hComport); // 关闭COM  
				m_biComportOpened = 0;
				return 0;
			}  
			switch ( (int)SStrf::satol( nv.get("stop") ) )
			{ 
			case 1: 
				options.c_cflag &= ~CSTOPB;
				break; 
			case 2: options.c_cflag |= CSTOPB;
				break;
			default: 
				close(m_hComport); // 关闭COM  
				m_biComportOpened = 0;
				return 0;
			} 
			if ( nv.get("parity")[0] != 'n' && nv.get("parity")[0] != 'N' ) 
				options.c_iflag |= INPCK; 
			tcflush(m_hComport,TCIFLUSH);
			options.c_cc[VTIME] = 0; 
			options.c_cc[VMIN] = 1;

			options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); options.c_oflag &= ~OPOST;
 
			if (tcsetattr(m_hComport,TCSANOW,&options) != 0) 
			{ 
				close(m_hComport); // 关闭COM  
				m_biComportOpened = 0;
				return 0;
			} 
		 
		}


		////配置超时值

		m_itimeoutsec = SStrf::satol( nv.get("timeoutsec") );
		m_itimeoutusec = (int) ( 1000 * 1000 * SStrf::satof( "0." + SStrvs::vsa_get( nv.get("timeoutsec"), ".", 1, 1 ) ) );

		m_biShouldDisConn = 0;

		return 1;
	}



	virtual void OnDisConn()
	{
		m_biShouldDisConn = 1;
		
		if( m_biComportOpened )
		{
			close(m_hComport); // 关闭COM  
			m_biComportOpened = 0;
		}
	}



public:


	virtual int on_sys_recv( SCake & ckDataBuf ) //return the recv len, 1 or 0
	{
		if(m_biShouldDisConn)
		{
			return 0;
		}

		ckDataBuf.redim( on_get_defaultrecv_buf_len() ); // =1

		int retval;
		fd_set rfds;
		struct timeval tv;
		int ret;
		tv.tv_sec = m_itimeoutsec;
		tv.tv_usec = m_itimeoutusec;

		if(m_biComportOpened)
		{
			FD_ZERO(&rfds);
			FD_SET(m_hComport,&rfds);
			retval = select(m_hComport+1,&rfds,NULL,NULL,&tv);
			if( retval < 0 )
			{
				return 0;
			}
			
			if( retval == 0 )
			{
				return 0;
			}

			if( retval > 0 )
			{
				//have data
				ret= read( m_hComport, ckDataBuf.buf(), ckDataBuf.len() );
				return (int)ckDataBuf.len();
			}
		}
	 
		return 0;
	}


	virtual int on_sys_send( const SCake & ckDataBuf ) //return the successfully sent len
	{
		if(m_biShouldDisConn)
		{
			return 0;
		}

		int len   =   0;

		len   = write( m_hComport, ckDataBuf.buf_const(), 1 ); 

		if (len   >   0) 
		{ 
			//if( !( (int)ckDataBuf.len() % 9 ) || SStrf::rand1() > 0.851 ) WThrd::tr_sleep( 0, 0.001 );
			if( ckDataBuf.len() % 13 == 3 || SStrf::rand1() > 0.88 )
				WThrd::tr_sleep( 0, 0.001 );
		}

		return (int)len;
	}


}; //end class 




X011_NAMESPACE_END

#endif





#endif

#ifdef WCEENV_

/*
X011 project 
WHYSOFT league 2007-09
ALL RIGHTS RESERVED.
S series designed for standard C++, any OS, 32bit compatible.
W series designed for windows
*/

#ifndef X011__H_w_sbase_h
#define X011__H_w_sbase_h


#define X011_NAMESPACE_BEGIN namespace wl {
#define X011_NAMESPACE_END                }


#include <iterator> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>



X011_NAMESPACE_BEGIN

//basic types
typedef		double					tdouble; //8 bytes
typedef		char					tint8;
typedef		unsigned char			tuint8;
typedef		short					tint16;
typedef		unsigned short			tuint16;
typedef		long					tint32;
typedef		unsigned long			tuint32;

typedef     __int64                 tint64;
typedef    unsigned __int64         tuint64; //scanf("%I64d",&a);printf("%I64d",a);scanf("%lld",&a);printf("%lld",a);Dev-C++的g++编译器，它使用的是"%I64d"而非"%lld"。 


//derived types
typedef		tint8				tchar;
typedef		int					tbool; 

//mem based types
typedef		tuint32			tsize;
typedef		tint32			toffset;



X011_NAMESPACE_END





#endif




/*
standard C lib pack
all SECURE matters are packed here.
for win ce
*/

#ifndef X011__H_w_SClib_h
#define X011__H_w_SClib_h





X011_NAMESPACE_BEGIN


class SClib
{

public:

	SClib(){;}

	~SClib(){;}

	typedef int (* PT_sscanf)( const char *buffer, const char *format , ... );
	static PT_sscanf p_sscanf() { return sscanf; }

	typedef int (* PT_sprintf)( char *, const char *, ... );
	static PT_sprintf p_sprintf() { return sprintf; }

	typedef char * (* PT_strcpy)( char *strDestination, const char *strSource );
	static PT_strcpy p_strcpy() { return strcpy; }


	typedef tm * (* PT_localtime)( const time_t * );
	static PT_localtime p_localtime() { return localtime; }

	typedef FILE * (* PT_fopen)( const char *filename, const char *mode );
	static PT_fopen p_fopen(){ return fopen; }


	static char * ltoaB( long _Val, char * _DstBuf, int _Radix)
	{
		if(_Radix==16)
			sprintf(_DstBuf, "%x",  _Val);
		else
			sprintf(_DstBuf, "%ld", _Val);

		return _DstBuf;
	}

	typedef char * (* PT_ltoa)( long value, char *str, int radix );
	static PT_ltoa p_ltoa() { return ltoaB; }


}; //end class SClib





X011_NAMESPACE_END



#endif





/*
base string func
*/

#ifndef X011__H_w_sstrf_h
#define X011__H_w_sstrf_h



X011_NAMESPACE_BEGIN


class SStrf
{

public:

	//SStrf(){;}

	virtual ~SStrf(){;}


	template < class T >
	static T * AddressOf( T & obj )
	{
		return reinterpret_cast<T *>(&reinterpret_cast<char&>(obj));
	}


	template< class T >
	static T * newobjptr( T * & p )
	{
		try
		{
			p = new T;
		}
		catch(...)
		{
			p = NULL;
		}

		return p;
	}

	
	template< class T >
	static T * newobjptr()  // wl::SStrf::newobjptr<bu_sop_t>()->tr_openx();
	{
		T *  p;
		return newobjptr(p);
	}


	static void * smalloc( tsize i )
	{
		return malloc( i );
	}


	static void sfree(void *s)
	{
		free(s);
	}



	static tuint16 smkU16( tuint8 c1, tuint8 c2) //lower byte is c1, comes first
	{
	   tuint16 ilow,ihigh;
	   ilow =  (tuint16)c1;
	   ihigh = (tuint16)c2;
	   ihigh <<= 8;
	   return ihigh + ilow;
	}


	template< class T >
	static T & chgendian( T & val )
	{
		if( sizeof(T) != 1 ) srev( (tchar *)&val, sizeof(T) ) ;
		return val;
	}

	template< class T >
	static T chgendian2( T val )
	{
		return chgendian(val);
	}
	

	
	static tbool readbit( void * pbin , int sufx )  
	{
		if( sufx < 0 )
		{
			return 0;
		}

		tuint8 * pbin2 = (tuint8 *)pbin;
		tuint8 cSrc;
		int iOffset ;

		cSrc = pbin2[sufx / 8];

		//iOffset = 7 - (sufx % 8);
		iOffset =  (sufx % 8);

		cSrc >>= iOffset;
		cSrc &= 1;
		return cSrc;
	}

	
	static tbool readbit( tuint8 bindata , int sufx )  
	{
		return readbit( &bindata, sufx );
	}


	static void writebit( void * pbin , int sufx , tbool val )
	{
		if( sufx < 0 )
		{
			return ;
		}

		val = val?1:0; 

		tuint8 * pbin2 = (tuint8 *)pbin;
		int cSrc;
		int iOffset ;

		cSrc = pbin2[sufx / 8];

		//iOffset = 7 - (sufx % 8);
		iOffset = (sufx % 8);

		cSrc >>= iOffset;
		cSrc &= 1;

		if( cSrc == val ) return ;

		int i = 1;
		i <<= iOffset;

		pbin2[sufx / 8] ^= i;
	}


	static std::string & bit2str( tchar c, std::string & strrtn )
	{
		strrtn = "01234567";
		for( int i = 0; i < 8; i++ ) strrtn[i] = readbit( &c, i ) ? '1' : '0' ;
		return strrtn;
	}

	static std::string bit2str( tchar c )
	{
		std::string str;
		return bit2str( c, str );
	}

	static tchar & str2bit( std::string str, tchar & c )
	{
		//......12345678  --是高位补0
		str += "00000000";
		for( int i = 0; i < 8; i++ ) writebit( &c, i , str[i]=='0' ? 0 : 1 );
		return c;
	}

	static tchar str2bit( std::string str )
	{
		tchar c;
		return str2bit( str, c );
	}


	static void initrand( int seed = 0 ) //sets the generator to a random starting point. better than srand()
	{
		SYSTEMTIME sysTime;
		GetLocalTime(&sysTime);
		int i = (int)( sysTime.wSecond + sysTime.wMilliseconds + GetTickCount() );
		tint32 j=(tint16)(0x0555&(i*seed));
		for(tint32 i=0;i<j;++i) rand();
	}


	static tdouble rand1( int iShouldInitSeed = 0 )
	{
		if( iShouldInitSeed ) initrand( iShouldInitSeed );
		return (tdouble)rand()/(tdouble)RAND_MAX;
	}


	static void *smemcpy( void *dest, const void *src, tsize count )
	{
		return memcpy(dest,src,count);//memcpy
	}


	static void * smemset( void *dest, tchar c, tsize count )
	{
		return memset( dest, (int)c, (size_t)count );
	}


	template< class T >
	static void * smemset( T * dest, tchar c = 0 )
	{
		return memset( dest, (int)c, sizeof(T) );
	}




	static tchar * scpy( tchar *strDestination, const tchar *strSource )
	{
		return (*SClib::p_strcpy())( strDestination, strSource );
	}


	static tsize slen( const tchar * s ) //串长度
	{
		if(s==NULL) return (tsize)0;
		return (tsize)strlen(s);
	}


	static tbool sishex(tchar c)//是16进制
	{
		return  (c>='0'&&c<='9')||(c>='A'&&c<='F')||(c>='a'&&c<='f');
	}

	static tbool sishex(const tchar *s)
	{
		if(s==NULL) return 0;
		for(;*s;s++) if(!sishex(*s)) return 0;
		return 1;
	}

	static tbool sisdec(tchar c) //是10进制
	{
		return  (c>='0'&&c<='9');
	}

	static tbool sisdec(const tchar *s)
	{
		if(s==NULL) return 0;
		for(;*s;s++) if(!sisdec(*s)) return 0;
		return 1;
	}


	static tchar *sltoa( tint32 i, tchar *buf, int radix = 10 )
	{
		return (*SClib::p_ltoa())(i, buf, radix);
	}


	static std::string sltoa( tint32 i, int radix = 10 )
	{
		tchar c[55];
		std::string buf;
		buf = sltoa( i, c, radix );
		return buf;
	}

	static tint32 satol( const tchar *s ) { return(s==NULL)?0:(tint32)atol(s); }

	static tint32 satol( const std::string & s ) { return satol(s.c_str()); }


	
	static std::string sultoa( tuint32 i )
	{
		std::stringstream stream;
		stream << i;
		return stream.str();
	}

	
	static tuint32 satoul( std::string  s ) 
	{ 
		return strtoul(s.c_str(),NULL,10); 
	}



	static tchar * sftoa( tdouble f , tchar * buf , int decimal_digits = -1 )
	//static tchar * sftoa( tdouble f, tchar *buf )
	{
		std::string s1;

		if( decimal_digits < 0 )
		{
			s1 = "%f";
		}
		else
		{			
			s1 = "%." + sltoa(decimal_digits) + "f";
		}

		(*SClib::p_sprintf())( buf, s1.c_str(), f );

		return buf;
	}

	static std::string sftoa( tdouble f , int decimal_digits = -1 )
	{
		if( decimal_digits < -1 ) decimal_digits = -1;
		std::vector<tchar> v( 22 + decimal_digits );
		tchar * c;
		c = &(v[0]);
		return  sftoa( f, c , decimal_digits );
	}


	static tdouble satof( const tchar *s )
	{
		if(s==NULL) return 0.0;
		return (tdouble)atof(s);
	}


	static tdouble satof( const std::string & s )
	{
		return satof(s.c_str());
	}


	static int scmpi( const tchar *a, const tchar *b )	//case insensitive
	{
		if(a==NULL&&b==NULL) return 0;
		if(a==NULL&&b!=NULL) return -1;
		if(a!=NULL&&b==NULL) return 1;
		const tchar *t1;
		const tchar *t2;
		tchar c1, c2;
		toffset i;
		t1 = a;
		t2 = b;
		for( i=0;t1[i]&&t2[i];i++ )
		{
			c1=t1[i]; c2=t2[i];
			if(c1>='a'&&c1<='z') c1+=('A'-'a');
			if(c2>='a'&&c2<='z') c2+=('A'-'a');
			if(c1!=c2) return c1-c2;
		}
		return t1[i]-t2[i];
	}


	static int scmpin( const tchar *a, const tchar *b, tsize count ) //case insensitive
	{
		if(a==NULL&&b==NULL) return 0;
		if(a==NULL&&b!=NULL) return -1;
		if(a!=NULL&&b==NULL) return 1;
		const tchar *t1;
		const tchar *t2;
		tchar c1, c2;
		tsize i;
		t1 = a;
		t2 = b;
		for( i=0;t1[i]&&t2[i]&&i<count;i++ )
		{
			c1=t1[i]; c2=t2[i];
			if(c1>='a'&&c1<='z')c1+=('A'-'a');
			if(c2>='a'&&c2<='z')c2+=('A'-'a');
			if(c1!=c2)return c1-c2;
		}
		if(i>0) i--;
		return t1[i]-t2[i];
	}


	static int scmpin( const tchar *a, const tchar *b ) //case insensitive
	{
		return scmpin(a,b,slen(b));
	}




	static int scmpn( const tchar *a, const tchar *b, tsize count )
	{
		if(!count) return 0; //if no len, then equal.
		if(a==NULL&&b==NULL) return 0;
		if(a==NULL&&b!=NULL) return -1; // a<b
		if(a!=NULL&&b==NULL) return 1;  // a>b
		return strncmp(a,b,count);
	}


	static int scmpn( const tchar *a, const tchar *b ) //assume count is len of b.
	{
		return scmpn(a,b,slen(b));
	}




	static int scmp( const tchar *a, const tchar *b )
	{
		if(a==NULL&&b==NULL) return 0;
		if(a==NULL&&b!=NULL) return -1;
		if(a!=NULL&&b==NULL) return 1;
		return strcmp(a,b);
	}


	static tchar * sucase( tchar *s )
	{
		toffset i;
		if(s==NULL) return NULL;
		for(i=0;s[i]!=0;i++){
			if(s[i]>='a'&&s[i]<='z')s[i] = s[i] -'a' + 'A' ;
		}
		return s;
	}

	
	static std::string & sucase( std::string & str )
	{
		tchar * szstr;
		szstr = (tchar *)smalloc( (tsize)str.size() + 1 );
		scpy( szstr, str.c_str() );
		sucase( szstr );
		str = szstr;
		sfree( szstr );
		return str;
	}


	static tchar * slcase( tchar *s )
	{
		toffset i;
		if(s==NULL) return NULL;
		for(i=0;s[i]!=0;i++){
			if(s[i]>='A'&&s[i]<='Z')s[i] = s[i] -'A' + 'a' ;
		}
		return s;
	}


	static std::string & slcase( std::string & str )
	{
		tchar * szstr;
		szstr = (tchar *)smalloc( (tsize)str.size() + 1 );
		scpy( szstr, str.c_str() );
		slcase( szstr );
		str = szstr;
		sfree( szstr );
		return str;
	}



	//指出最后一个字符的指针.可以向左偏移。
	//偏移量0代表最末一个字节，而不是c00. but if s is "", return the pointer to c00 .
	template< class Pchar_CPchar_T >	/*Pchar_CPchar_T可能是const或非const的字节指针*/
	static Pchar_CPchar_T splast( Pchar_CPchar_T s, toffset offset2left = 0 /*正数代表向左方*/ )	
	{
		Pchar_CPchar_T t = s;
		if(!s||!*s) return t; //
		toffset i,j ;
		j = (toffset)slen(s);
		i = j - 1 - offset2left ;
		t=s+(i<0?0:i);
		return t;//最多退到s本身。
	}



	static const tchar * sstr( const tchar * s, const tchar *substr ) 
	{
		if(!s||!substr||!(*s)||!(*substr)) return NULL;
		return (const tchar *)strstr(s,substr); 
	}

	static tchar * sstr( tchar * s, const tchar *substr ) 
	{
		if(!s||!substr||!(*s)||!(*substr)) return NULL;
		return (tchar *)strstr(s,substr); 
	}


	template< class Pchar_CPchar_T >
	static Pchar_CPchar_T sstr( Pchar_CPchar_T s, tchar subc )
	{
		tchar t[2];
		t[0]=subc;
		t[1]=0;
		return sstr(s,t) ;
	}


	static tchar * srev( tchar * s, tsize len ) 
	{
		tsize u;
		toffset  x, y, i, a, b;
		u = len;
		u >>= 1;
		x = u;
		y = (toffset)len - 1;
		for(i=0;i<x;i++) {
			a = i;
			b = y - i; 
			s[a] ^= s[b];
			s[b] ^= s[a];
			s[a] ^= s[b];
		}
		return s;
	}


	static tchar *srev( tchar * s )
	{
		return srev(s,slen(s));
	}


	static tchar * sreplch( tchar * source, tsize len, tchar c1, tchar c2 )	//对于来源二进制串中所有的c1替换成c2
	{
		tsize i;
		for(i=0;source&&i<len;i++) {
			if(source[i]==c1) source[i]=c2;
		}
		return source;
	}


	static tchar * sreplch( tchar * source, tchar c1, tchar c2 )	//所有的c1替换成c2
	{
		return sreplch(source, slen(source), c1, c2);
	}


	static std::string & sreplstr( std::string & str, const tchar *string_to_replace, const tchar *new_string )   
	{
		if( string_to_replace && new_string )
		{
			//   Find   the   first   string   to   replace   
			std::string::size_type   index   =   str.find(string_to_replace);   
			//   while   there   is   one   
			while(index   !=   std::string::npos)   
			{   
				//   Replace   it   
				str.replace(index,   strlen(string_to_replace),   new_string);   
				//   Find   the   next   one   
				index   =   str.find(string_to_replace,   index   +   strlen(new_string));   
			}   
		}
		return   str;   
	}


	static std::string & sreplstr( std::string & str, const std::string & string_to_replace, const std::string & new_string ) 
	{
		return sreplstr( str, string_to_replace.c_str(), new_string.c_str() ) ;
	}

	//static std::string & sreplstr( std::string & str,  std::string * string_to_replace,  std::string * new_string ) 
	//{
	//	if( string_to_replace==NULL) return str;
	//	if( new_string==NULL) return str;
	//	return sreplstr( str, string_to_replace->c_str(), new_string->c_str() ) ;
	//}

	//static std::string & sreplstr( std::string & str,  std::string  string_to_replace,  std::string  new_string ) 
	//{
	//	return sreplstr( str, string_to_replace.c_str(), new_string.c_str() ) ;
	//}



	// 3 trim functions below:

	//a trim base func:
	static std::string & str_trim_base( tchar *(*f)( tchar *, const tchar * ), std::string & str, const tchar *str_space="\r\n \t" )
	{
		tchar * pstr;
		pstr = (tchar *)smalloc( (tsize)str.size() + 1 );
		scpy( pstr, str.c_str() );
		str = (*f)( pstr, str_space );
		sfree( pstr );
		return str;
	}


	//right trim 

	static tchar * strimr( tchar * s, tchar a_space ) //right trim, tchar. trim series knl
	{
		toffset i;
		for(i=slen(s)-1;i>=0;i--)
			if(s[i]==a_space)
				s[i]=0;
			else
				break;
		return s;
	}

	static tchar * strimr( tchar * s, const tchar *str_space="\r\n \t" ) //right trim, tchar*. trim series knl
	{
		toffset i;
		for( i=slen(s)-1; i >= 0; i-- )
			if( sstr(str_space,s[i]) != NULL )
				s[i]=0;
			else
				break;
		return s;
	}

	static std::string & strimr( std::string & str, const tchar * str_space = "\r\n \t" )
	{
		return str_trim_base( strimr, str, str_space );
	}


	//left trim 

	static tchar * striml( tchar * s, tchar a_space )	//left trim
	{
		return srev( strimr(srev(s), a_space) ) ;
	}

	static tchar * striml( tchar * s, const tchar * str_space = "\r\n \t" )		//left trim
	{
		return srev( strimr(srev(s), str_space) ) ;
	}

	static std::string & striml( std::string & str, const tchar * str_space = "\r\n \t" )
	{
		tchar * pstr;
		pstr = (tchar *)smalloc( (tsize)str.size() + 1 );
		scpy( pstr, str.c_str() );
		str = striml( pstr, str_space );
		sfree( pstr );
		return str;
	}


	//double trim

	static tchar * strim( tchar * s, tchar a_space  ) // double trim
	{
		return  striml( strimr(s,a_space), a_space) ;
	}

	static tchar * strim( tchar * s, const tchar * str_space = "\r\n \t" ) // double trim
	{
		return  striml( strimr(s,str_space), str_space) ;
	}

	static std::string & strim( std::string & str, const tchar * str_space = "\r\n \t" )
	{
		return str_trim_base( strim , str, str_space );
	}

	//trim functions end.



	static tchar * sleft( tchar * s, tsize n ) //left right mid series knl
	{
		if(n>slen(s)) return s;
		s[n]=0;
		return s;
	}


	static tchar * sright( tchar * s, tsize n )
	{
		return srev(sleft(srev(s), n));
	}


	static tchar * smid( tchar * s, tsize a_pos, tsize a_len )
	{
		sright(s, slen(s) - a_pos );
		sleft(s, a_len);
		return s;
	}



	static const tchar * seq_dirno()
	{
		return "0123456789ACEFHKLMPQSTUWXYZ"; //dirnogjbv	 27 left
	}



	static std::string seq( std::string strCurNum, tbool isFixLen = 1, const tchar * s_symbset = NULL )
	{
		static tchar c[1];
		tchar * s_num;
		tint16 *lia ;
		tint16 ulia;
		tint32 i,j,k;

		c[0]=0;
		if(slen(s_symbset)<2) s_symbset = seq_dirno();
		s_num = (tchar*)smalloc( (tsize)strCurNum.size() + 2 );
		if(!s_num) return "";
		lia = (tint16 *)smalloc( (slen(s_num) + 1)*sizeof(tint16) );
		if(!lia)
		{
			sfree(s_num);
			return "";
		}

		scpy( s_num, strCurNum.c_str() );
		
		if(!(*s_num)) {
			s_num[0]=s_symbset[0];
			s_num[1]=0;
		}

		j = slen(s_num) ;
		for(i=0;i<j;i++)
		{
			const char *t = sstr( s_symbset, s_num[i] );
			if(!t)
				lia[i] = 0;
			else
				lia[i] = (tint16)( t - s_symbset );			
		}

		lia[j-1] ++;
		k = slen(s_symbset) ;
		ulia = 0;
		for(i=j-1;i>=0;i--)
		{
			if(lia[i] >= k)
			{
				lia[i] -= (tint16)k;
				if(i>0)
					lia[i-1]++;
				else
					ulia++;
			}
		}

		for( i=0;i<j;i++ )
		{
			s_num[i] = s_symbset[ lia[i] ];
		}

		if( (!isFixLen) && ulia )	//如果不是固定长度，则处理最高位进位。
		{
			srev(s_num);
			s_num[j] = s_symbset[ulia];
			s_num[j+1] = 0;
			srev(s_num);
		}

		strCurNum = s_num;
		sfree(s_num);
		sfree(lia);
		return strCurNum;
	}




	static tchar bs_esc() { return 'b'; }/*b被合成后应该换成%*/



	static tbool bs_inset( tchar c ) //in direct expression set
	{
		if(c==bs_esc()) return 0; //if is esc then is not in the set
		if(c>='a'&&c<='z') return 1;
		if(c>='0'&&c<='9') return 1;
		if(c>='A'&&c<='Z') return 1;
		return 0;
	}


	static tsize bs_ensize( const tchar *s, tsize len ) 
	{
		tsize i;
		tchar *t1, *t2, *t3;
		if(s==NULL) return 0;
		i=0;
		t1=(tchar*)s;
		t3=t1+len;
		for( t2=t1; t2<t3; t2++ )
			i += bs_inset(*t2)?(1*sizeof(tchar)):(3*sizeof(tchar));

		return i+(sizeof(tchar)); //must be sz-string after encode. a tchar for '\0'
	} 


	static tsize bs_ensize( const tchar *s ) 
	{ 
		return bs_ensize( s, slen(s) + 1 );
	}


	static tchar * bs_en( const tchar *s, tsize len, tchar *destbuf )
	{
		tchar *ss1, *ss2, *ss3, *sd1;
		tbool rc;
		int l;
		if(s==NULL||destbuf==NULL) return NULL;
		ss1 = (tchar*)s;
		ss3 = ss1 + len;
		sd1 = destbuf;

		for( ss2=ss1; ss2<ss3; ss2++)
		{
			rc = 0;

			do //fakedo 0
			{
				if( !bs_inset(*ss2) ) //不在圈里，崩溃。
				{ 
					rc = 1;
					break;
				}

				*sd1 = *ss2;         //没崩溃时的处理。
				sd1++;

			}while(0);

			if(rc) {    //崩溃时的处理。
				l = (tuint8)(*ss2);
				(*SClib::p_sprintf())( sd1, "%c%02X", bs_esc(), l );
				sd1 += (3*sizeof(tchar));
			}
		}
		*sd1=0;//to form a sz. bs_ensize has reported this space up there
		return destbuf;
	}


	static tchar * bs_en( const tchar *s, tchar *destbuf )
	{
		return bs_en( s, slen(s) + 1, destbuf );
	}

	static std::string  & bs_en( std::string & strData ) //the data includes the sz00.
	{
		std::string s1( 3 + bs_ensize( strData.c_str(), (tsize)strData.length() ) , 'a' );

		bs_en( strData.c_str(), &(s1[0]) );

		return strData = s1.c_str();
	}

	static std::string  & bs_de( std::string & strData )  
	{
		std::string s1( strData + "123" );

		bs_de( strData.c_str(), &(s1[0]) );

		return strData = s1.c_str();
	}


	static tsize bs_desize( const tchar *s , tchar(*apf1)()=bs_esc )
	{
		toffset j,i;
		tsize  k;
		if(s==NULL) return 0;
		
		for( i=0,j=(toffset)slen(s),k=0;i<j; ) 
			if(	(i+2<j)				&&
				s[i]==(*apf1)( )	&&
				sishex(s[i+1])		&&
				sishex(s[i+2])  )
			{
				k++;
				i+=3;
			}
			else
			{
				i++;
				k++;
			}
		return k;
	}


	static tchar * bs_de( const tchar *s, tchar *dest , tchar(*apf1)()=bs_esc ) //the dest buffer can be the same of the source. safe to overlay
	{
		if(s==NULL||dest==NULL) return dest;
		toffset i,j,k;
		toffset a1,a2;
		tchar ss[2]; 
		ss[1]=0;

		for(i=0,j=(toffset)slen(s),k=0;i<j; ) {
			if(	(i+2<j)			&&
				s[i]==(*apf1)( )&&
				sishex(s[i+1])	&&
				sishex(s[i+2])	 )
			{
				ss[0]=s[i+1];
				sucase(ss);
				a1 = (ss[0] <= '9' ? ss[0] - '0' : ss[0] - 'A' + 10) * 16 ;

				ss[0]=s[i+2];
				sucase(ss);
				a2 = (ss[0] <= '9' ? ss[0] - '0' : ss[0] - 'A' + 10) ;

				*(tchar *)(dest+k) = (tuint8)(a1+a2);
				k++;
				i+=3;
			}else{
				dest[k] = s[i];
				k++;
				i++;
			}
		}

		return dest;
	}


	static tchar * bs_de( tchar *source_dest , tchar(*apf1)()=bs_esc ) //the dest buffer is the source. safe to overlay
	{
		return bs_de(source_dest,source_dest,apf1);
	}

	

	template< class T >
	static std::string b2s( /*const*/ T & sourcedata )
	{
		std::string str1;
		tchar * szstr;
		szstr = (tchar *)smalloc( sizeof(T) * 3 + 3 );
		bs_en( (const char *)reinterpret_cast<const char *>(&reinterpret_cast</*const*/ char& >(sourcedata)), sizeof(T), szstr );
		str1 = szstr;
		sfree( szstr );
		return str1;
	}

	
	template< class T >
	static T & s2b( std::string strSource, T & destdata )
	{
		bs_de( strSource.c_str(), reinterpret_cast<tchar *>(&reinterpret_cast<char& >(destdata))  );
		return destdata;
	}

	template< class T >
	static T s2b( std::string strSource )
	{
		T destdata;
		bs_de( strSource.c_str(), reinterpret_cast<tchar *>(&reinterpret_cast<char& >(destdata))  );
		return destdata;
	}


}; //end class SStrf 





X011_NAMESPACE_END





#define MOONLOGSTR  \
	( "**" + /*wl::SDte::GetNow().ReadStringPack() + "|" +*/ std::string(__FILE__) + "|" + std::string(__FUNCTION__) + "|" + wl::SStrf::sltoa(__LINE__) )






#endif




/*
calculate func
*/

#ifndef X011__H_w_SCalc_h
#define X011__H_w_SCalc_h



X011_NAMESPACE_BEGIN


class SCalc
{

public:

	//SCalc(){;}

	virtual ~SCalc(){;}
	
	
	
	static tint32 max_divisor( tint32 a, tint32 b) //得出来a就是a和b的最大公约数
	{
		tint32 temp; 
		while(b!=0) //---判断余数是否为0,为0了,就是最大公约数了a 
		{ 
		temp=a%b; //a数去除b数的余数赋值给temp 
		a=b;      //把b数赋值给a 
		b=temp;   //把余数赋值给b
		} 
		return a;
	}


	static tbool quadratic_equation_root( tdouble a, tdouble b, tdouble c, tdouble *x1, tdouble *x2) //求一元二次方程的根
	{
		if(b*b<4*a*c) return 0; 
		*x1=(sqrt(b*b-4*a*c)-b)/(2*a); 
		*x2=(-sqrt(b*b-4*a*c)-b)/(2*a); 
		return 1; 
	}


	static std::string dseal( const std::string & strData , tsize out_len , const tchar *szMethod = ""  )
	{
		return dseal( strData.c_str(), SStrf::slen( strData.c_str() ) , out_len , szMethod );
	}


	static std::string dseal( const tchar *s, tsize len, tsize out_len, const tchar *szMethod = "" )
	{
		// 指定目标长度 十进制数字摘要 dseal V1.0
		tuint32 i, j;
		tchar *t, *t0;
		std::string strOut("");
		if(!s||/*!len||*/!out_len||!szMethod) return "";
		for(j=len+out_len,i=0;;i++)
		{
			j = ++j + chksum(s, len) + chksum(szMethod,SStrf::slen(szMethod));
			j = ++j * chksum(strOut.c_str(),(tsize)strOut.size()) * (len^10) * out_len ; 
			j = 0x7FffFFff & (j ^ (~j * ~i + (len ^ out_len)) * (~j+~j*~i+~i));
			strOut += SStrf::sltoa(j);
			if( out_len+11 < strOut.size() ) break ;
		}
		t0 = t = (tchar*)SStrf::smalloc( (tsize)strOut.size()+1 );
		if(!t) return "";
		SStrf::scpy( t, strOut.c_str() );
		SStrf::srev(t);
		if(*t=='0') t++;		 
		t[out_len] = 0;
		strOut=t;
		SStrf::sfree(t0);
		return strOut;
	}


	
	static tuint32 chksum( const tchar *s, tsize len)
	{
		tuint32 j=0;
		if(SStrf::slen(s)==0)
			return 0;
		while(len--)
		{
			j += (tuint8)s[len]+(len+1);
			j &= 0x7FffFFff;
		}
		return j;
	}



	static tchar * xor( tchar * Src, tsize len, tuint8 x )
	{
		tsize i;
		tuint8 *s=(tuint8 *)Src;
		if( !s || !len ) return (tchar*)s;
		for(i=0;i<len;i++) s[i] ^= x;
		return (tchar*)s;
	}


}; //end class SCalc





X011_NAMESPACE_END

#endif





/*
string
vector string
*/

#ifndef X011__H_w_sstrvs_h
#define X011__H_w_sstrvs_h



X011_NAMESPACE_BEGIN



class SStrvs
{

public:

	//SStrvs(){;} 

	virtual ~SStrvs(){;}

	
	template < class StrT > /* for string or wstring*/
	static tsize vsa_impbylen( const StrT & strsource, typename StrT::size_type ilen, std::vector<StrT> & vecrtn )
	{
		StrT s1(strsource);
		typedef typename StrT::size_type sizetypeB;

		while( !s1.empty() )
		{
			sizetypeB i = ilen <= s1.size() ? ilen : s1.size();
			StrT s2 = s1.substr( 0, i );
			vecrtn.push_back(s2);
			s1.erase( 0, i );
		}
		return (tsize)vecrtn.size();
	}




	//

	template < class StrT > /* for string or wstring*/
	static tsize vsa_imp( const StrT & ssource, const StrT & ssep, tbool istoken, std::vector<StrT> & rtnlst )
	//static tsize vsa_imp( const StrT & ssource, StrT ssep, tbool istoken, std::vector<StrT> & rtnlst )
	{
		std::vector<tint32> vAbuf, vBbuf;
		tint32  ltmpn,ltmpm,ltmpi,ltmpj,ltmpk, ltmpb1, ltmpb2;
		typedef typename StrT::size_type sizetypeB;
		sizetypeB ssti;

		ltmpm = ltmpi = ltmpj = 0;
		ltmpn = (tint32)ssource.size();
		ltmpk = (tint32)ssep.size();

		do //fakedo
		{
			if(ltmpk==0)
			{
				rtnlst.push_back(ssource);
				break;
			}

			do 
			{
				if(ltmpm>=ltmpn) break;
				ssti = ssource.find( ssep, ltmpm ); //the knl. find() return from 0 on.
				if(ssti==StrT::npos) break;
				ltmpi = (tint32)ssti;
				ltmpm = ltmpi;

				vAbuf.push_back(ltmpi);  
				ltmpj ++;
				ltmpm += ltmpk;

			} while(1);

			ltmpb1 = 0 ; // lowerbound(vAbuf) 
			ltmpb2 = ltmpj - 1 ; // upperbound(vAbuf)

			ltmpj = 0;
			vBbuf.push_back(ltmpj);
			for(ltmpi=ltmpb1;ltmpi<=ltmpb2;ltmpi++){
				ltmpj = vAbuf[ltmpi];
				vBbuf.push_back(ltmpj);
				vBbuf.push_back(ltmpj+ltmpk);
			}
			vBbuf.push_back( ltmpn );

			ltmpj = (tint32)vBbuf.size();
			for(ltmpi=0;ltmpi<ltmpj;ltmpi+=2)
			{
				ltmpm = vBbuf[ltmpi];
				ltmpn = vBbuf[ltmpi+1];
				ltmpk = ltmpn - ltmpm;

				if(istoken&&ltmpk==0){
					;
				}else
					rtnlst.push_back( ssource.substr( ltmpm, ltmpk ) ); //the knl. substr(pos{suffix},len)

			}
			
		}while(0);

		return (tsize)rtnlst.size();//vector size目前已经被占用了的位置个数。
	}


	template < class StrT > /* for string or wstring*/
	static tsize vsa_hm( const StrT & ssource, const StrT & ssep, tbool istoken )
	{
		return vsa_imp( ssource, ssep, istoken, std::vector<StrT>() );
	}

	
	//iwhich is suffix. from 0 on.
	template < class StrT > /* for string or wstring*/
	static StrT vsa_get( const StrT & ssource, const StrT & ssep, tbool istoken, tsize iwhich )
	//static StrT vsa_get( const StrT & ssource, StrT ssep, tbool istoken, tsize iwhich )
	{
		std::vector<StrT> tmplst;
		if( iwhich<vsa_imp( ssource, ssep, istoken, tmplst ) )
			return tmplst[iwhich];
		else
			return StrT();
	}

	template < class StrT >  
	static StrT vsa_get( const StrT & ssource, const typename StrT::value_type *ssep, tbool istoken, tsize iwhich )
	{
			return vsa_get( ssource,  StrT(ssep),  istoken,  iwhich );
	}
	

	//2V get
	/* the para have 3 parts. 1=the source. 2=settings. 3=the coordinate */
	template < class StrT > 
	static StrT vsa2v_get( const StrT & ssource, 

						  const StrT & ssepTR,
						  tbool		istokenTR,
						  const StrT & ssepTD,
						  tbool		istokenTD,

						  tsize iwhichTR,  tsize iwhichTD		)

	{
		std::vector<StrT> tmplst1, tmplst2;
		if( iwhichTR<vsa_imp( ssource, ssepTR, istokenTR, tmplst1 ) )
		{
			if( iwhichTD<vsa_imp( tmplst1[iwhichTR], ssepTD, istokenTD, tmplst2 ) )
				return tmplst2[iwhichTD];
		}
		return StrT();
	}


	//2V prpt
	/*   */
	template < class StrT > 
	static std::map<StrT,StrT> & vsa2v_prpt( const StrT & ssource, 
											 const StrT & ssepTR,
											 const StrT & ssepTD, 
											 std::map<StrT,StrT> & mapRtn	)
	{
		std::vector<StrT> vecTmpTR, vecTmpTD;
		typedef typename std::vector<StrT>::iterator iteratortypeB;
		iteratortypeB itTR;
		vsa_imp( ssource, ssepTR, 1, vecTmpTR );
		for( itTR = vecTmpTR.begin(); itTR!=vecTmpTR.end(); ++itTR)
		{
			vsa_imp( *itTR, ssepTD, 1, vecTmpTD );
			vecTmpTD.push_back( StrT() );
			vecTmpTD.push_back( StrT() );
			mapRtn.insert( std::pair<StrT,StrT>( vecTmpTD[0], vecTmpTD[1] ) );
			vecTmpTD.clear();
		}
		return mapRtn;
	}


};//end class SStrvs





X011_NAMESPACE_END

#endif






/*
set operation
*/

#ifndef X011__H_w_SSetu_h
#define X011__H_w_SSetu_h



X011_NAMESPACE_BEGIN



class SSetu
{

public:

	//SSetu(){;} 

	virtual ~SSetu(){;}
	

	//all containers must have same element type.
	template < class CntnrT, class ELET >
	static tsize vs_setch( CntnrT &vset1, CntnrT &vset2, std::vector<ELET> &rtnlst )
	{
		typedef typename CntnrT::iterator iteratortypeB;
		iteratortypeB it1, it2;
		tsize i;
		i=0;
		for( it1=vset1.begin(); it1!=vset1.end(); it1++)
		{
			it2 = std::find( vset2.begin(), vset2.end(), *it1 );
			if( it2 == vset2.end() ) //can't find in set2 then means only in set1
			{
				rtnlst.push_back( *it1 );
				i++;
			}
		}
		return i;
	}


	//all containers must have same element type.
	template < class CntnrT, class ELET >
	static tsize vs_setj( CntnrT &vset1, CntnrT &vset2, std::vector<ELET> &rtnlst )
	{
		typedef typename CntnrT::iterator iteratortypeB;
		iteratortypeB it1, it2;
		tsize i;
		i=0;
		for( it1=vset1.begin(); it1!=vset1.end(); it1++)
		{
			it2 = std::find( vset2.begin(), vset2.end(), *it1 );
			if( it2 != vset2.end() ) //can find in set2 then means both in 2 sets
			{
				rtnlst.push_back( *it1 );
				i++;
			}
		}
		return i;
	}


	//first 2 containers must have same element type.
	template < class CntnrT, class ELET >
	static tsize vs_setgroup( const CntnrT & vsource, std::vector<ELET> & rtncontent, std::vector<int> & rtnsubsum )
	{
		CntnrT v2, v3; //same as the source type
		typedef typename CntnrT::iterator iteratortypeB;
		iteratortypeB  it1,  itNewEnd2;
		int i;

		v2 = vsource;
		std::sort( v2.begin(), v2.end() );
		v3 = v2;

		itNewEnd2 = std::unique( v2.begin(), v2.end() );

		for( it1=v2.begin(); it1!=itNewEnd2; it1++)
		{
			rtncontent.push_back( *it1 );
			i = (int)std::count( v3.begin(), v3.end(), *it1 );
			rtnsubsum.push_back(i);
		}
		return (tsize)v2.size();
	}


	template < class CntnrT, class ELET >
	static tsize vs_setgroup( const CntnrT & vsource, std::vector<ELET> & rtncontent )
	{
		std::vector<int> v;
		return vs_setgroup( vsource, rtncontent, v );
	}


	template < class ELET >
	static tsize vs_setgroup( std::vector<ELET> & _a_content )  //用本身返回
	{
		std::vector<ELET> _a_aa1;
		tsize i = vs_setgroup( _a_content, _a_aa1 );
		_a_content = _a_aa1;
		return i;
	}





	template < class ELET >
	static ELET & vs_groupbig( std::vector<ELET> & memo, std::vector<int> & subsum )
	{
		typedef typename std::vector<ELET>::iterator iteratortypeB;
		iteratortypeB it1;
		std::vector<int>::iterator it2, it3;
		int i;

		i=0;
		for( it3=it2=subsum.begin(); it2!=subsum.end(); ++it2)
		{
			if( *it2>i )
			{
				i = *it2;  //keep the best val
				it3 = it2; //keep the best pos
			}
		}

		it1 = memo.begin() + ( it3 - subsum.begin() );
		return *it1;
	}


	template < class ELET >
	static ELET & vs_groupsmall( std::vector<ELET> & memo, std::vector<int> & subsum )
	{
		typename std::vector<ELET>::iterator it1;
		std::vector<int>::iterator it2, it3;
		int i;

		i=0;
		for( it3=it2=subsum.begin(); it2!=subsum.end(); ++it2)
		{
			if( *it2<i || i==0 )
			{
				i = *it2;  //keep the best val
				it3 = it2; //keep the best pos
			}
		}

		it1 = memo.begin() + ( it3 - subsum.begin() );
		return *it1;
	}


	//删除最旧的重复项
	template < class ELET >
	static void StableDelOld( std::vector<ELET> & v )
	{
		for( typename std::vector<ELET>::iterator it = v.begin(); it != v.end(); )
		{
			typename std::vector<ELET>::iterator it2;

			it2 = it + 1;

			if( std::find( it2, v.end(), *it ) != v.end() )
			{
				//found
				v.erase( it );
				it = v.begin();
			}
			else
				++it;
		}
	}


	//删除 指定的 重复项
	template < class CNTNRT, class ELET >
	//static void StableDel( CNTNRT & v , const ELET & val )
	static void StableDel( CNTNRT & v , ELET val )
	{
		for( typename CNTNRT::iterator it = v.begin(); it != v.end(); )
		{
			if( *it == val )
			{
				//found
				v.erase( it );
				it = v.begin();
			}
			else
				++it;
		}
	}

};//end SSetu





X011_NAMESPACE_END

#endif






/*
cake, cakel
provide raw memory
*/

#ifndef X011__H_w_scake_h
#define X011__H_w_scake_h




X011_NAMESPACE_BEGIN



template < class CT >
class SCake_base
{
public:
	typedef /*typename*/ CT CkEle_t;

private:

	CT		*m_pbuf; 
	tsize	m_mysize; //元素个数，不是字节数。 it is not byte num, it is num of ele.

	mutable std::vector<CT>  m_FastAppendBuf;

private:

	void init(void) { 	m_pbuf=NULL; 	m_mysize=0; }

	void freeall(void)
	{
		if(m_pbuf) delete [] m_pbuf;
		m_mysize=0;
		init();
	}

public:

	SCake_base() {  init(); }
	
	SCake_base( const SCake_base<CT> & cakesource )
	{
		init(); 
		let(cakesource);
	}

	SCake_base( CT c ) { init(); let(&c,1); }

	SCake_base( const CT *psource, tsize isize ) { init(); let(psource,isize); }

	SCake_base( const tchar *psource ) { init(); lets(psource); } //for char* only

	SCake_base( const std::string & s) { init(); lets(s); } //for char* only


	virtual ~SCake_base( ) { freeall(); }


	//static std::string & trim( std::string & strCell, const tchar *str_space="\r\n \t" ) // double trim
	//{
	//	SCake ckCell;
	//	ckCell.lets( strCell );
	//	SStrf::strim( ckCell, str_space );
	//	return strCell = ckCell;
	//}

	//static std::string & trim( std::string & strCell, const tchar *str_space="\r\n \t" ) // double trim
	//{
	//	return wl::SStrf::strim( strCell );
	//}


	void copybuf( const CT *psource, CT *pdest, tsize isize, toffset iDestOffsetWhere = 0 )
	{
		if( psource == pdest && iDestOffsetWhere == 0 ) return;//think about c=c c.let(c) , same obj operations

		if( psource && pdest && isize )
		{
			for( tsize jtmp=iDestOffsetWhere; jtmp<isize+iDestOffsetWhere; jtmp++ )
				pdest[jtmp] = psource[jtmp-iDestOffsetWhere]; 
		}
	}
	

	void redim( tsize iNewSize, tbool reserve=0 )
	{
		if( iNewSize <= len() && iNewSize > len()/2 )
		{
			m_mysize = iNewSize;
		}
		else
		{
			CT *lbuf;
			if(iNewSize==0)
			{
				freeall();
				return;
			}
			lbuf = new CT[iNewSize] ;
			if(reserve) copybuf( m_pbuf, lbuf, iNewSize<m_mysize?iNewSize:m_mysize );
			freeall();
			m_pbuf = lbuf;
			m_mysize = iNewSize;
		}
	}

	const CT * buf_const() const
	{
		//FastAppendEnd();

		return m_pbuf;
	}


	CT * buf()
	{
		FastAppendEnd();

		return m_pbuf;
	}

	tsize len() const
	{ 
		return m_mysize;
	}

	void let( const CT *psource, tsize isize ) //knl
	{
		FastAppendEnd();

		redim(isize);
		copybuf( psource, m_pbuf, isize );
	}


	void let( const SCake_base<CT> & cakesource ) 
	{
		let( cakesource.buf_const(), cakesource.len() );
	}


	void lets( const CT *psource, CT c00 )
	{
		tsize i;
		const CT *p2;
		for(i=1,p2=psource;*p2!=c00;p2++)
			i++; //the c00 occupy one room. it is belong to data.
		let( psource, i );
	}


 	void lets( const tchar *psource ) //knl
	{
		if(psource)
		{
			redim( SStrf::slen(psource) + 1 );
			tsize jtmp;
			for( jtmp=0; psource[jtmp]; jtmp++ )
			{
				m_pbuf[jtmp] = psource[jtmp];
			}
			m_pbuf[jtmp] = 0;//the c00 occupy one room. it is belong to data.
		}
	}


	void lets( const std::string & s) { lets(s.c_str()); }

	void lets( tint32 i)  { lets( SStrf::sltoa(i) ); }

	void lets( tdouble d) { lets( SStrf::sftoa(d) ); }

	SCake_base<CT> & dump( SCake_base<CT> & cake2 ) //dump head part into cake2. keep the remaining(right part)
	{
		tsize iGoneSize;
		cake2.let( buf(), iGoneSize = ( len() < cake2.len() ? len() : cake2.len() ) ); // len()-iGoneSize= remain size or 0.
		SCake_base<CT> * ptmpcake = new SCake_base<CT>(*this);
		let( ptmpcake->buf() + iGoneSize, len() - iGoneSize );
		delete ptmpcake;
		return cake2;
	}


	SCake_base<CT> & cut( tsize howmany ) //cut off the right part. keep and return the left part.
	{
		if( howmany<=m_mysize) m_mysize -= howmany;
		else m_mysize = 0;
		return *this;
	}


	
	SCake_base<CT> & FastAppend( const SCake_base<CT> & cake2 ) // append into temp buf, refresh later
	{
		if( !this->m_pbuf ) return this->append(cake2);

		if(cake2.len()==0)
		{
			return *this;
		}

		this->m_mysize += cake2.len();
		std::copy( cake2.buf_const(), cake2.buf_const() + cake2.len(), std::back_inserter(m_FastAppendBuf) ); 

		return *this;
	}

	void FastAppendEnd()  
	{
		if( m_FastAppendBuf.empty() ) return;

		std::vector<CT>  FastBuf2(m_FastAppendBuf);

		m_FastAppendBuf.clear(); // append will call let() or buf(), which will call me again. clear to prevent it
		this->m_mysize -= (tsize)FastBuf2.size();
		this->append( &(FastBuf2[0]), (tsize)FastBuf2.size() );
	}



	SCake_base<CT> & append( const SCake_base<CT> & cake2 ) //bin style append 
	{
		if(cake2.len()==0)
		{
			//
		}
		else
		{
			CT *lbuf1;
			const CT *lbuf2;
			tsize len1,len2;
			lbuf1 = buf();
			lbuf2 = cake2.buf_const();
			len1 = len();
			len2 = cake2.len();
			redim( len1+len2, 1 );
			copybuf( lbuf2, buf(), len2, len1 );
		}
		return *this;
	}

	SCake_base<CT> & append( const CT *psource, tsize isize )
	{
		if( isize==0 || !psource )
		{
			//
		}
		else
		{
			CT *lbuf1;
			const CT *lbuf2;
			tsize len1,len2;
			lbuf1 = buf();
			lbuf2 = psource;
			len1 = len();
			len2 = isize;
			redim( len1+len2, 1 );
			copybuf( lbuf2, buf(), len2, len1 );
		}
		return *this;
	}

	SCake_base<CT> & append( CT val )
	{
		return append( &val, 1 );
	}


public:	//operators

	/*
	如果有
	class B {...}
	class D : public B {...}
	那，在D中显式调用B的operator =的方法是：
	D& operator = (const D& rhs) {
		this->B::operator =(rhs);  // 或者也可以写*static_cast<B*>(this) = *static_cast<const B*>(&rhs);
		// ...
		return *this;
	}*/

	SCake_base<CT> & operator = ( const SCake_base<CT> & cake2 )
	{
		let(cake2);
		return *this;
	}


	operator CT * ( )
	{
		return buf();
	}

    
	operator const CT * ( ) const
	{
		return buf_const();
	}

	int operator < ( const SCake_base<CT> & cake2 ) const
	{
		return ( (int)buf_const() < (int)cake2.buf_const() );
	}


}; //end of class SCake_base declare




////////////////////////////////////////////////////////////////////////////////
//a cake for tchar 

class SCake : public SCake_base<tchar>
{

public:
	
	SCake():SCake_base<tchar>( ) { }

	SCake(const SCake & ckSrc):SCake_base<tchar>( ckSrc ) {  }


	SCake(const SCake_base<tchar> & ckSrc):SCake_base<tchar>( ckSrc ) {  }

	SCake( tchar c ):SCake_base<tchar>( c ) {  }
	//wl::tuint8 cu;
	//cu = 0xff;
	//wl::SCake ck( cu );

	SCake(const tchar * psrc, tsize isize):SCake_base<tchar>( psrc, isize ) {  }

	SCake(const tchar *psrc):SCake_base<tchar>( psrc ) {  }

	SCake(const std::string & s):SCake_base<tchar>( s) { } 


	SCake & bs_en()
	{
		SCake *pck = new SCake;
		pck->redim( SStrf::bs_ensize( buf(), len() ) );
		SStrf::bs_en( buf(), len(), pck->buf() );
		*this = *pck;
		delete pck;
		return *this;
	}


	SCake & bs_de() //如果传入的bstr==""则bs_de()之后本CAKE变为NULL指针的长度为0的一个CAKE。
	{
		tsize iDatalen = SStrf::bs_desize( buf() );
		SStrf::bs_de( buf() );
		redim( iDatalen, 1 );
		return *this;
	}


	tchar * mk_sz()
	{
		append( SCake("") );
		return buf();
	}

	std::string & mk_str( std::string & strOut ) const
	{
		if( this->len() )
		{
			return strOut = std::string( this->buf_const(), this->len() );
		}
		return strOut = "";
	}

	std::string mk_str() const
	{
		std::string s1;
		return mk_str(s1);
	}




public:	//operators

	SCake & operator = ( const SCake & cake2 )
	{
		let(cake2);
		return *this;
	}



}; //end of class SCake  






///////////////////////////////////////////////////////////////////////////////
template < class cakeT, class CT >
class SCakel_base2 {

private:

	std::vector<cakeT *> m_vknl;

	void collect( tbool szstyle=1 ) //if szstyle, don't record middle sz00. record the last sz00 ofcourse
	{
		cakeT  * psc;
		tsize wholesize,copypoint;
		typename std::vector<cakeT *>::iterator it;
		for( wholesize=0,it=m_vknl.begin(); it!=m_vknl.end(); ++it )
		{
			wholesize += (*it)->len( );
			if(szstyle&&(*it)->len( )) wholesize--;
		}
		if(szstyle) wholesize++;
		psc = new cakeT ;
		psc->redim(wholesize);
		for( copypoint=0,it=m_vknl.begin(); it!=m_vknl.end(); ++it )
		{
			psc->copybuf( (*it)->buf(), psc->buf(),	(*it)->len(), copypoint );
			copypoint += (*it)->len();
			if(szstyle) copypoint--;
		}
		clean( );
		m_vknl.push_back( psc );
	}


private:

	SCakel_base2( const SCakel_base2 & ckl )
	{
		;
	}

public:

	SCakel_base2( ) { ; }

	virtual ~SCakel_base2( )
	{
		for( typename std::vector<cakeT *>::iterator it=m_vknl.begin();it!=m_vknl.end();++it)
			delete *it;
	} //this method doesn't destruct m_vknl, so faster.


	tsize hm(void) const
	{
		return (tsize)m_vknl.size();
	}


	std::vector<cakeT *> & knl( ) {
		return m_vknl;
	}


	cakeT  * get( tsize iwhere ) const
	{
		return ( hm( )==0 || iwhere>=hm( ) )?NULL:m_vknl[iwhere];
		//don't use & because user can modi the static obj. 
		//if clear the static obj every time then can't used in multi-thread env.
	}


	cakeT  * get( ) const 
	{
		return get( hm( )-1 );
	}


	cakeT  * get0( )
	{
		return get(0);
	}


	void add( const cakeT  & cakesource, tsize iwhere )
	{
		cakeT  * psc;
		psc = new cakeT ( cakesource );
		if(iwhere>hm()) iwhere=hm();
		m_vknl.insert( m_vknl.begin()+iwhere, psc );
	}


	void add( const cakeT  & cakesource )
	{
		cakeT  * psc;
		psc = new cakeT ( cakesource );	//psc->let( cakesource.buf(), cakesource.len() );
		m_vknl.push_back( psc );
	}


	void add0( cakeT  & cakesource ) { add(cakesource,0); }


	void del( tsize iwhere )
	{
		typename std::vector<cakeT *>::iterator it;
		if( !( hm( )==0 || iwhere>=hm( ) ) )
		{
			it = m_vknl.begin( ) + iwhere;
			delete *it;
			m_vknl.erase( it );
		}
	}

	void del()  { del(hm()-1); }

	void del0() { del(0); }


	void clean()
	{
		tsize iremain = 0;
		while( hm() > iremain )
			del();
	}

	void clean( tsize iremain )
	{
		while( hm() > iremain )
			del();
	}


	void clean0( tsize iremain = 0 )
	{
		while( hm() > iremain )
			del0();
	}

	void collectb( ) { collect(0); }

	void collects( ) { collect(1); }


	
	void scatter( const cakeT  & ckSrc , CT cSepC )//see cake, scatter it and append
	{
		tsize p1,p2;
		cakeT  ckTmp;
		for(p1=p2=0;p2<ckSrc.len();p2++)  
		{
			if( *(ckSrc+p2)==cSepC )
			{
				ckTmp.let( ckSrc+p1, p2-p1+1 );
				add( ckTmp );
				p1=p2+1;
			}
		}

		//see the last time, whether successed.
		if(p2) //if the for above runed at least once
		{
			p2--;
			if( *(ckSrc+p2)!=cSepC )
			{
				ckTmp.let( ckSrc+p1, p2-p1+1 );
				ckTmp.append( cakeT ( &cSepC,1 ) );
				add( ckTmp );
			}
		}
	}


	void scatter( CT cSepC=0 )// 
	{
		do //fakedo
		{
			if(hm()>1)
				collectb();

			if(hm()==0)
				break;

			scatter( *get0() , cSepC );

			del0();

		}while(0);
	}


	SCakel_base2<cakeT,CT> & append( const SCakel_base2<cakeT,CT> & cakel2 )
	{
		tsize len2,lcount;
		len2 = cakel2.hm();
		for(lcount=0;lcount<len2;lcount++)
		{
			add( *(cakel2.get(lcount)) );
		}
		return *this;
	}
	

public: //operators


	operator std::vector<cakeT *> & ( )
	{
		return knl( );
	}


	SCakel_base2<cakeT,CT> & operator = ( const SCakel_base2<cakeT,CT> & cakel2 )
	{
		clean();
		return append(cakel2);
	}


};
//end of class cakel_base2





/////////////////////////////////////////////////////////////////////////////////

template < class CT >
class SCakel_base : public SCakel_base2<  SCake_base<CT>, CT >
{
private:

	SCakel_base( const SCakel_base & ckl )
	{
		;
	}

public: 

	SCakel_base( ) { ; }


public: //operators

	SCakel_base<CT> & operator = ( const SCakel_base<CT> & cakel2 )
	{
		SCakel_base2<  SCake_base<CT>, CT >::clean();		
		return append(cakel2);
	}

};





//////////////////////////////////////////////////////////////////////////////////

//typedef SCake_base<tchar> SCake;

class SCakel : public SCakel_base2< SCake, tchar > 
{
private:

	SCakel( const SCakel & ckl )
	{
		;
	}

public:

	SCakel( ) { 	}

public:

	SCakel & append( const SCakel & cakel2 )
	{
		tsize len2,lcount;
		len2 = cakel2.hm();
		for(lcount=0;lcount<len2;lcount++)
		{
			add( *(cakel2.get(lcount)) );
		}
		return *this;
	}

public: //operators

	SCakel & operator = ( const SCakel & cakel2 )
	{
		clean();
		return append(cakel2);
	}

};






X011_NAMESPACE_END

#endif




/*
date, time, event
universal arithmetic
*/

#ifndef X011__H_w_sdte_h
#define X011__H_w_sdte_h




X011_NAMESPACE_BEGIN



class SDte
{
// id/od  it/ot  ie/oe

public:

	int m_year;
	int m_mon;
	int m_day;
	int m_hour;
	int m_min;
	int m_sec;
	//int m_msec;

private:

	static tbool d_is_leap_year(int y)
	{
		return y%400==0||y%4==0&&y%100!=0;
		/*If n Mod 400 = 0 Or (n Mod 4 = 0 And n Mod 100 <> 0) Then yes */
	}


	static int d_day_of_year(int y)
	{
		return d_is_leap_year(y)?366:365;
	}


	static int d_day_of_month(int y, int m)
	{
		tint8 Array[]={0, 31, 28, 31,30,31,30,31,31,30,31,30,31};
		if(m<1||m>12) m=1;
		return (int)(m==2 ? Array[m] + (d_is_leap_year(y)?1:0) : Array[m]);
	}


	static tchar * d_odget( SCakel_base<tchar> & abuf, tint32 od )
	{
		abuf.add( SCake_base<tchar>("000000000") );
		if(od<0) od *= -1;
		abuf.add( SCake_base<tchar>( SStrf::sltoa(od) ) );
		abuf.collects( );
		return abuf.get( )->buf( );
	}


	//now->l
	static time_t dt_mk(void)  
	{
		struct tm tmm, *tp;
		time_t timer;
		time(&timer);
		tp = (*SClib::p_localtime())(&timer);//struct tm *localtime( const time_t *timer );
		memcpy(&tmm, tp, sizeof(struct tm));
		return mktime(&tmm);
	}


	// l->t
	static int dt_mk( struct tm *ptm , time_t tmr)
	{
		struct tm *tp;
		tp = (*SClib::p_localtime())(&tmr);
		if(ptm!=NULL&&tp!=NULL) memcpy(ptm, tp, sizeof(struct tm));
		return tp!=NULL;	 
	}


	// l->s
	static void dt_mknow( int& y, int&m, int& d, int& hh, int& mi, int& ss ) //standard chg interface!!!
	{
		struct tm tmm;
		struct tm *tp;
		memset(tp=&tmm, 0, sizeof(struct tm));
		dt_mk(tp, dt_mk());
		y = tp->tm_year+1900;
		m = tp->tm_mon+1;
		d = tp->tm_mday;
		hh = tp->tm_hour;
		mi = tp->tm_min;
		ss = tp->tm_sec;
	}

	///////////////////////////////////////
	

	static struct tm & RegulateTmYear4( struct tm & t )
	{
		if( t.tm_year <= 999 )
		{
			t.tm_year += 1900;
		}
		return t;
	}

	static struct tm & RegulateTmYear2( struct tm & t )
	{
		if( t.tm_year > 1900 )
		{
			t.tm_year -= 1900;
		}
		return t;
	}


	static struct tm & Now( struct tm & t )
	{
		struct tm *tp;
		memset(tp=&t, 0, sizeof(struct tm));
		dt_mk(tp, dt_mk());
		tp->tm_year+=1900;
		return t;
	}


		
	//tm->l
	static time_t tm2l( struct tm t )
	{
		RegulateTmYear2(t);

		return mktime(&t);	//time_t mktime( struct tm *timeptr );
	}


	//l->tm
	static struct tm l2tm( time_t tmr )
	{
		struct tm *tp;
		struct tm tm2;

		SStrf::smemset(&tm2);

		//tp = localtime(&tmr);
		tp = (*SClib::p_localtime())(&tmr);

		if(tp!=NULL) memcpy(&tm2, tp, sizeof(struct tm));

		return tm2;	 
	}



	static tint32 idmk( const tchar * sDateTime )
	{
		if(!sDateTime) return 0;
		int y, m, d;
		(*SClib::p_sscanf())( sDateTime, "%d-%d-%d", &y, &m, &d );
		return idmk(y,m,d);
	}


	static tint32 idmk(int y, int m, int d, tint32 offset=0)//参数说明：年、月、日、偏移量日(正数为未来)
	{
		tint32 i,j;
		for(j=0,i=0;i<=(y-1);i++) j += d_day_of_year(i);
		for(i=1;i<=(m-1);i++) j += d_day_of_month(y,i); 
		return j = j + d + offset;
	}


	static int odgety( tint32 od )
	{
		tchar *t;
		SCakel_base<tchar> abuf;
		t = d_odget( abuf, od );
		t = SStrf::splast(t,3);
		*t=0; 
		return (int)SStrf::satol(t-4);
	}


	static int odgetm( tint32 od )
	{
		tchar *t;
		SCakel_base<tchar> abuf;
		t = d_odget( abuf, od );
		t = SStrf::splast(t,1);
		*t=0; 
		return (int)SStrf::satol(t-2);
	}


	static int odgetd( tint32 od )
	{
		tchar *t;
		SCakel_base<tchar> abuf;
		t = d_odget( abuf, od );
		t = SStrf::splast(t,0);
		return (int)SStrf::satol(t-1);
	}


	static tint32 id2o( tint32 id )
	{
		tint32 i1, i2, i3, i4;
		if(id<=0) 	 id=1;
		for(i1=0;id>d_day_of_year(i1);) {
			id -= d_day_of_year(i1);
			i1++;
		}
		for(i2=1;id>d_day_of_month(i1,i2);) {
			id -= d_day_of_month(i1,i2);
			i2++;
		}
		i3 = id;
		return i4 = 10000*i1 + 100*i2 + i3;
	}


	static tint32 od2i( tint32 od )
	{
		return idmk( odgety(od), odgetm(od), odgetd(od) );
	}


	static int idgety( tint32 id ) { return odgety( id2o(id) ); }

	static int idgetm( tint32 id ) { return odgetm( id2o(id) ); }

	static int idgetd( tint32 id ) { return odgetd( id2o(id) ); }

	static tint32 idnow( ) { int y,m,d,hh,mi,ss; dt_mknow(y,m,d,hh,mi,ss); return idmk(y,m,d); }

	static tint32 odnow( ) { return id2o(idnow()); }


	///////////////////////////////////////////////////////////////////////

	static tint32 itmk( const tchar * sDateTime )
	{
		if(!sDateTime) return 0;
		int h, m, s, i;
		(*SClib::p_sscanf())( sDateTime, "%d-%d-%d %d:%d:%d", &i, &i, &i, &h, &m, &s );
		return itmk(h, m, s);
	}

	
	static tint32 itmk(int h, int m, int s) 
	{
		return h*60*60+m*60+s;
	}

	static tint32 itgeth(tint32 it)		{	return it/3600; 	}

	static tint32 itgetm(tint32 it)		{	return it%3600/60; 	}

	static tint32 itgets(tint32 it)		{	return it%60;	}


	static tint32 it2o(tint32 it)
	{
		tchar s[7];
		(*SClib::p_sprintf())( s, "%02d%02d%02d", itgeth(it), itgetm(it), itgets(it) );
		return SStrf::satol(s);
	}


	static tint32 ot2i(tint32 ot)
	{
		SCake_base<tchar> ca("000000", 6);
		ca.append( SCake_base<tchar>(SStrf::sltoa(ot)) );
		int h,m,s;
		(*SClib::p_sscanf())( SStrf::splast(ca.buf(), 5), "%2d%2d%2d", &h,&m,&s);
		return itmk(h,m,s);	
	}


	static tint32 itnow( ) { int y,m,d,hh,mi,ss; dt_mknow(y,m,d,hh,mi,ss); return itmk(hh,mi,ss); }

	static tint32 otnow( ) { return it2o(itnow()); }

	static tdouble iemk( tint32 id, tint32 it) { return  id + (tdouble)it/(tdouble)86400; }


	static tdouble ie2o( tint32 id, tint32 it)
	{
		tint8 s[16];
		(*SClib::p_sprintf())(s, "%ld.%06ld", id2o(id), it2o(it) ); 
		return SStrf::satof(s);
	}

	static tdouble ie2o(tdouble ie)
	{
		tdouble d1, d2;
		d1 = floor(ie);
		d2 = 0.5 + ( (ie - floor(ie)) * 86400 ) ; 
		return ie2o((tint32)d1, (tint32)d2);
	}


	static tdouble oe2i(double oe)//return ie
	{
		tdouble od, ot;
		od = floor(oe);
		ot = 0.5 + ( (oe - floor(oe)) * 1e6 ) ;
		return iemk( od2i((tint32)od), ot2i((tint32)ot) );
	}


	static tdouble ienow()
	{
		return iemk( idnow(), itnow() );
	}

	
	static tdouble oenow() 
	{ 
		return ie2o( ienow() ); 
	}


	
	static std::string Db_oe( tint32 idNow=0, tint32 itNow=-1 ) //2008-02-13 15:22:33
	{
		if(idNow==0 ) idNow=idnow();
		if(itNow==-1) itNow=itnow();
		tchar sBuf[33];
		(*SClib::p_sprintf())(sBuf,"%d-%02d-%02d %02d:%02d:%02d",
					 idgety(idNow), idgetm(idNow), idgetd(idNow),  
					 itgeth(itNow), itgetm(itNow), itgets(itNow)	);
		return sBuf;
	}


	static std::string Pack_oe( tint32 idNow=0, tint32 itNow=-1 ) //20080213.152233
	{
		if(idNow==0 ) idNow=idnow();
		if(itNow==-1) itNow=itnow();
		return  SStrf::sftoa( ie2o( iemk( idNow, itNow ) ) );
	}



public:

	SDte()
	{
		m_year= 0;
		m_mon= 0;
		m_day= 0;
		m_hour= 0;
		m_min= 0;
		m_sec= 0;
		//m_msec= 0;
	}

	SDte( std::string str_dte )
	{
		if(str_dte=="") this->MakeNow();
		else
			Make( str_dte );
	}

	SDte( int iHour, int iMin, int iSec )
	{
		this->MakeNow();
		this->m_hour= iHour;
		this->m_min= iMin;
		this->m_sec= iSec;
	}

	virtual ~SDte() { ; }


	static double e_proctime()  //return seconds.
	{
		return (double)clock()/(double)CLOCKS_PER_SEC;
	}



	SDte & Make( std::string str_dte )
	{
		if( str_dte.find( "-" ) != std::string::npos && str_dte.find( ":" ) != std::string::npos ) // datetime
		{
			(*SClib::p_sscanf())( str_dte.c_str(), "%d-%d-%d %d:%d:%d", &m_year, &m_mon, &m_day, &m_hour, &m_min, &m_sec );
			return *this;
		}

		if( str_dte.find( "-" ) != std::string::npos && str_dte.find( ":" ) == std::string::npos ) // date
		{
			(*SClib::p_sscanf())( str_dte.c_str(), "%d-%d-%d", &m_year, &m_mon, &m_day );
			m_hour = m_min = m_sec = 0;
			return *this;
		}

		if( str_dte.find( "-" ) == std::string::npos && str_dte.find( ":" ) != std::string::npos ) // time
		{
			(*SClib::p_sscanf())( str_dte.c_str(), "%d:%d:%d", &m_hour, &m_min, &m_sec );
			m_year = m_mon = m_day = 0;
			return *this;
		}

		m_year = 0;
		m_mon  = 0;
		m_day  = 0;

		m_hour = 0;
		m_min = 0;
		m_sec = 0;

		return *this;	
	}


	static tbool IsValidTime( std::string strVal ) //hhmiss
	{
		if( strVal.length() != 6 ) return 0;

		std::string s1 ;
		
		s1 = strVal.substr( 0, 2 );
		int i1 = SStrf::satol( s1 );
		if( i1 >= 24 ) return 0;

		s1 = strVal.substr( 2, 2 );
		i1 = SStrf::satol( s1 );
		if( i1 >= 60 ) return 0;

		s1 = strVal.substr( 4, 2 );
		i1 = SStrf::satol( s1 );
		if( i1 >= 60 ) return 0;

		return 1;
	}



	SDte & MakeNow()
	{
		SYSTEMTIME sysTime;
		GetLocalTime(&sysTime);

		m_year= sysTime.wYear;
		m_mon = sysTime.wMonth;
		m_day = sysTime.wDay;
		m_hour= sysTime.wHour;
		m_min = sysTime.wMinute;
		m_sec = sysTime.wSecond;
		return *this;
	}


	static SDte GetNow()  //  wl::SDte::GetNow().ReadStringPack().c_str()
	{
		SDte s; 
		return s.MakeNow();
	}


	tint32 DiffDay( const SDte & dte2 ) const
	{
		tint32 d1, d2;

		d1 = this->idmk( m_year, m_mon, m_day ) ;
		d2 = dte2.idmk( dte2.m_year, dte2.m_mon, dte2.m_day ) ;

		return d1 - d2;
	}


	tdouble DiffSec( const SDte & dte2 ) const
	{
		tdouble d1, d2;

		d1 = (double)this->itmk( m_hour, m_min, m_sec );
		d2 = (double)dte2.itmk( dte2.m_hour, dte2.m_min, dte2.m_sec );

		return d1 - d2 + DiffDay(dte2) * 86400.0;
	}


	tint32 DiffSecInt( const SDte & dte2 ) const
	{
		tint32 d1, d2;

		d1 = (tint32)this->itmk( m_hour, m_min, m_sec );
		d2 = (tint32)dte2.itmk( dte2.m_hour, dte2.m_min, dte2.m_sec );

		return d1 - d2 + DiffDay(dte2) * 86400;
	}


	int WeekDay() const
	{
		int i2 = this->DiffDay( wl::SDte() );
		return (i2 - 2 ) % 7;
	}


	SDte & Relative( const SDte & dte2 )
	{
		m_year += dte2.m_year;
		m_mon  += dte2.m_mon;
		m_day  += dte2.m_day;
		m_hour += dte2.m_hour;
		m_min  += dte2.m_min;
		m_sec  += dte2.m_sec;

		tint32 i;

		i = itmk( m_hour, m_min, m_sec );
		m_day += i / 86400;
		i %= 86400;
		m_hour = itgeth( i );
		m_min = itgetm( i );
		m_sec = itgets( i );

		i = idmk( m_year, m_mon, m_day );
		m_year = idgety( i );
		m_mon  = idgetm( i );
		m_day  = idgetd( i );

		return *this;
	}

	
	SDte & RelativeSec( tint32 sec2 )
	{
		SDte dte2;
		dte2.m_year = dte2.m_mon = dte2.m_day = dte2.m_hour = dte2.m_min = 0;
		dte2.m_sec = sec2;
		return Relative(dte2);
	}



	std::string ReadString() const //2008-02-13 15:22:33
	{
		tchar sBuf[33];
		(*SClib::p_sprintf())(sBuf,"%d-%02d-%02d %02d:%02d:%02d",
					 m_year, m_mon, m_day,  
					 m_hour, m_min, m_sec	);
		return sBuf;
	}

	std::string ReadStrDate() const // 2008-02-13 
	{
		tchar sBuf[33];
		(*SClib::p_sprintf())(sBuf,"%d-%02d-%02d",
					 m_year, m_mon, m_day );
		return sBuf;
	}

	std::string ReadStrTime() const // 15:22:33
	{
		tchar sBuf[33];
		(*SClib::p_sprintf())(sBuf,"%02d:%02d:%02d",
					 m_hour, m_min, m_sec	);
		return sBuf;
	}


	std::string ReadStringPack( char c = '.' ) const //20080213.152233
	{
		tchar sBuf[33];
		(*SClib::p_sprintf())(sBuf,"%d%02d%02d%c%02d%02d%02d",
					 m_year, m_mon, m_day,  c , 
					 m_hour, m_min, m_sec	);
		return sBuf;
	}

	std::string ReadStrPackDate() const //20080213
	{
		tchar sBuf[33];
		(*SClib::p_sprintf())(sBuf,"%d%02d%02d",
					 m_year, m_mon, m_day 	);
		return sBuf;
	}

	std::string ReadStrPackTime() const // 152233
	{
		tchar sBuf[33];
		(*SClib::p_sprintf())(sBuf,"%02d%02d%02d",
					 m_hour, m_min, m_sec	);
		return sBuf;
	}


	std::string Read_dt1() const //dd-MMM-yyyy
	{
		tchar sBuf[33];
		const tchar *s2[] = {"aa","Jan", "Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec" };
		(*SClib::p_sprintf())(sBuf,"%d-%s-%d",
								m_day,s2[m_mon], m_year );
		return sBuf;
	}


	operator std::string () const
	{
		return ReadStringPack() ;
	}


};//end of SDte






X011_NAMESPACE_END

#endif




/*
file new,del,select,read,write
for win ce
*/

#ifndef X011__H_w_sfile_h
#define X011__H_w_sfile_h




X011_NAMESPACE_BEGIN



class SFile
{

private:

	std::string m_strFilename;

public:

	SFile()
	{
		bind("");
	}


	SFile( std::string fn )
	{
		bind(fn);
	}


	virtual ~SFile()
	{ ;
	}


	static std::string GetPathSep()
	{
		return "\\";
	}


	static std::string MkDir2Path( std::string strPathOrDir ) 
	{
		if( strPathOrDir.length() )
		{
			const tchar * t;
			t = SStrf::splast( strPathOrDir.c_str() );
			if( *t == GetPathSep()[0] )
			{
				return strPathOrDir;
			}
		}
		
		return strPathOrDir + GetPathSep();
	}


	

	static void Dir2Path( std::string & strPathOrDir ) 
	{
		strPathOrDir = MkDir2Path(strPathOrDir);
	}





	void bind( std::string fn )
	{
		m_strFilename = fn;
	}



	tbool bind_nofile( std::string strPath, const tchar * pszExt = NULL , int iThreadId = 0 ) // ext不一定必须带点
	{
		static int iName1 = 0;
		tdouble dName2;
		int k=0;
		std::string strNameExt(pszExt?pszExt:".tmp");
		std::string strGoodPathfilename;

		// 
		strPath = MkDir2Path( strPath );

		if( pszExt && *pszExt!='.' ) strNameExt = std::string(".") + pszExt;

		do
		{
			iName1--;
			dName2 = SStrf::rand1();
			strGoodPathfilename = strPath + "h" + SStrf::sltoa(iName1) + "_" + SStrf::sltoa(iThreadId) + SStrf::sftoa(dName2) + strNameExt;
			bind(strGoodPathfilename);
			if(canoutput()) return 1;
			if( k ++ > 9 )
			{
				if(!erase())
				{
					bind("");
					return 0;
				}
			}
		}while(1);
	}


	std::string filename() const
	{
		return m_strFilename;
	}


	//operator std::string & () 
	//{
	//	return m_strFilename;
	//}

	operator std::string () const
	{
		return m_strFilename; 
	}

	operator const tchar * () const
	{
		return m_strFilename.c_str();
	}


	static tbool erase(std::string strfilename)
	{
		std::wstring ws1( 2+strfilename.size(), L'-' );
		swprintf( &(ws1[0]), L"%S", strfilename.c_str() );
		return   DeleteFile(&(ws1[0])) ? 1 : 0;
	}

	tbool erase()
	{
		return erase(m_strFilename);
	}


	tbool exists()
	{
		FILE *fp;
		tbool rc;
		if( m_strFilename=="" )
		{
			return 0;
		}
		fp = (*SClib::p_fopen())( m_strFilename.c_str(), "rb" );
		if(fp==NULL) rc=0;
		if(fp!=NULL)
		{
			rc=1; fclose(fp);
		}
		return rc;
	}


	tbool caninput()
	{
		return exists();
	}


	tbool canoutputabs()
	{ 
		FILE *fp;
		fp = (*SClib::p_fopen())(m_strFilename.c_str(),"wb");
		if(fp==NULL) return 0;
		fclose(fp);
		return erase();
	}


	tbool canoutput()
	{	//safely create. means if exists then can't .
		if(exists()) return 0;
		return canoutputabs();
	}


	tsize len()
	{
		if( !exists() ) return 0;
		tsize flen;
		FILE *fp;
		fp = (*SClib::p_fopen())( m_strFilename.c_str(), "rb" );
		fseek( fp,0,SEEK_END );
		flen=ftell(fp);
		fclose(fp);
		return flen;
	}


	tbool read( SCake_base<tchar> & buf, tsize a_extra_bytes = 0 ) //bin read
	{
		if(!this->exists()) return 0;
		FILE *fp;

		fp = (*SClib::p_fopen())( m_strFilename.c_str(), "rb" );
		if( fp == NULL )
		{
			return 0;
		}

		tsize flen;
		fseek( fp,0,SEEK_END );
		flen=ftell(fp);
		fseek( fp,0,SEEK_SET );


		//if( flen == 0) 
		//{
		//	fclose(fp);
		//	return 0 ;
		//}


		buf.redim( flen + a_extra_bytes );

		if(a_extra_bytes) 
		{
			SStrf::smemset( buf.buf(), 0, flen + a_extra_bytes ); //the a_extra_bytes may be > 1
			//*( buf.buf() + ( flen + a_extra_bytes ) - 1 ) = 0;
		}

		if(flen) fread( buf.buf(), flen, 1, fp );

		fclose(fp);

		return 1;
	}


	tbool read_str( SCake_base<tchar> & buf ) // read content and add a c00 to form a string //read str means read an extra c00.
	{
		return this->read( buf, 1 );
	}


	tbool read_str( std::string & strRtnBuf )
	{
		SCake_base<tchar> buf;
		strRtnBuf = "";
		if( read_str(buf) )
		{
			strRtnBuf = buf.buf();
			return 1;
		}
		return 0;
	}


	tbool read_vecstr( std::vector<std::string> & vecLines, std::string strSep, tbool istoken = 1 )
	{
		wl::SCake ckData;
		if( !read_str( ckData ) ) return 0;
		if( !ckData.len() ) return 0;
		SStrvs::vsa_imp( std::string(ckData.buf()), strSep, istoken, vecLines );
		return 1;
	}



	tbool write( const void * pbuf, tsize len, tbool bIsAppend = 0 ) //bin write
	{
		FILE *fp;
		tbool rc;

		rc=0;

		do
		{
			if( len == 0 ) break;
			if( !pbuf ) break;
			fp = (*SClib::p_fopen())( m_strFilename.c_str( ), bIsAppend?"ab":"wb" );
			if(fp==NULL) break;
			rc = fwrite( pbuf, len, 1, fp )?1:0 ;
			fclose(fp);
		}while(0);

		return rc?1:0 ;
	}



	tbool write( const SCake_base<tchar> & buf, tbool bIsAppend = 0 ) //bin write
	{
		FILE *fp;
		tbool rc;

		rc=0;

		do
		{
			if( buf.len()==0 ) break;
			if( !buf.buf_const() ) break;
			fp = (*SClib::p_fopen())( m_strFilename.c_str( ), bIsAppend?"ab":"wb" );
			if(fp==NULL) break;
			rc = fwrite( buf.buf_const(), buf.len(), 1, fp )?1:0 ;
			fclose(fp);
		}while(0);

		return rc?1:0 ;
	}


	tbool write_str( const tchar * buf, tbool bIsAppend = 0 )//write a string. not include the sz c00. //write str means not write c00.
	{
		FILE *fp;
		tbool rc;

		rc=0;

		do
		{
			if( NULL == buf ) break;
			fp = (*SClib::p_fopen())( m_strFilename.c_str(), bIsAppend?"ab":"wb" );
			if(fp==NULL) break;
			if( fwrite( buf, SStrf::slen(buf), 1, fp ) )//if slen(buf)==0 then write a 0 len file.
			{
				rc = 1; 
			}
			else
			{
				rc = 0;
			}
			fclose(fp);

		}while(0);

		return rc?1:0 ;
	}


	tbool write_str( const std::string & buf, tbool bIsAppend = 0 )//not include the sz c00.
	{
		return write_str( buf.c_str(), bIsAppend );
	}


	tbool write_vecstr( const std::vector<std::string> & vecLines, std::string strSep, tbool bIsAppend = 0 )
	{
		std::string strOut;

		for( std::vector<std::string>::const_iterator it = vecLines.begin(); it != vecLines.end(); ++it )
		{
			strOut += *it + strSep;
		}

		return write_str(strOut, bIsAppend);
	}


	//
	tbool IsHeadOf( SFile & me2 )
	{
		if( !SStrf::scmpi( this->filename().c_str(), me2.filename().c_str() ) ) return 0; //same file, not include.
		if( !this->exists() ) return 0;
		if( !me2.exists()   ) return 0;

		tsize i1, i2;

		if( (i1 = this->len()) == 0 ) return 0;
		if( (i2 = me2.len()) == 0   ) return 0;

		if( i1 > i2 ) return 0;

		SCake ck1, ck2;

		this->read( ck1 );
		me2.read( ck2 );

		if( !memcmp( ck1.buf(), ck2.buf(), i1 ) ) return 1;

		return 0;
	}

	
	//
	tbool IsHeadOf( std::string strme2 )
	{
		SFile sf2;
		sf2.bind(strme2);
		return IsHeadOf(sf2);
	}

};//end SFile





X011_NAMESPACE_END

#endif







/*
SNava  means NAme-VAlue pair
*/

#ifndef X011__H_w_SNava_h
#define X011__H_w_SNava_h



X011_NAMESPACE_BEGIN



template< class nameT, class valueT >
class SNava_base
{
public:

	typedef typename std::map< nameT, valueT >::iterator	MAP_MAPKNL_IT;
	typedef typename std::map< nameT, valueT >::const_iterator  MAP_MAPKNL_CONSTIT;

	MAP_MAPKNL_IT m_it4name;

public:

	std::map< nameT, valueT >  m_mapKnl;
	

public:

	virtual ~SNava_base() {;} 
	

	void clear()
	{
		m_mapKnl.clear();
	}


	tbool IsEmpty()
	{
		if( m_mapKnl.empty() ) return 1;
		return 0;
	}


	tbool let( const nameT & name, const valueT & val )
	{
		//m_mapKnl.insert( std::pair< nameT, valueT >( name, val ) ); //if there already have one value, the insert will do nothing.
		m_mapKnl[name] = val; //this method will overwrite the current value, if existed.
		return 1;
	}


	tbool get( const nameT & name, valueT & val )
	{
		MAP_MAPKNL_IT it;
		it = m_mapKnl.find( name );
		if( it != m_mapKnl.end() )
		{
			val = it->second;
			return 1;
		}
		return 0;
		//return m_mapKnl[name];
	}


	valueT & get( const nameT & name )
	{
		return m_mapKnl[name];
	}


	tbool del( const nameT & name )
	{
		MAP_MAPKNL_IT it;
		it = m_mapKnl.find( name );
		if( it != m_mapKnl.end() )
		{
			m_mapKnl.erase(it);
			return 1;
		}
		return 0;
	}


	tbool GetFirstName( nameT & Name )
	{
		m_it4name = m_mapKnl.begin();
		if( m_it4name != m_mapKnl.end() )
		{
			Name = m_it4name->first;
			return 1;
		}
		return 0;
	}


	tbool GetNextName( nameT & Name )
	{
		m_it4name ++;
		if( m_it4name != m_mapKnl.end() )
		{
			Name = m_it4name->first;
			return 1;
		}
		return 0;
	}


	tbool operator < ( const SNava_base & rhs) const
	{
		return ( m_mapKnl < rhs.m_mapKnl ? 1 : 0 );
	}

	tbool operator <= ( const SNava_base & rhs) const
	{
		return ( m_mapKnl <= rhs.m_mapKnl ? 1 : 0 );
	}

	tbool operator > ( const SNava_base & rhs) const
	{
		return ( m_mapKnl > rhs.m_mapKnl ? 1 : 0 );
	}

	tbool operator >= ( const SNava_base & rhs) const
	{
		return ( m_mapKnl >= rhs.m_mapKnl ? 1 : 0 );
	}

	tbool operator == ( const SNava_base & rhs) const
	{
		return ( m_mapKnl == rhs.m_mapKnl ? 1 : 0 );
	}
};




class SNavass : public SNava_base< std::string, std::string >
{
private:

	static void seri_element_en( SCake & ck )
	{
		if( ck.len() == 0 ) return;
		ck.bs_en();
	}

	static void seri_element_de( SCake & ck )
	{
		if( ck.len() == 0 ) return;
		ck.bs_de();
		if( !ck.buf() ) ck.lets(""); //because "" means NULL pointer, just prevent this.
	}

public:
	virtual ~SNavass() {;} 
	
	
	void imp( const std::string & ssource, std::string ssepTR, std::string ssepTD )
	{
		SStrvs::vsa2v_prpt( ssource, ssepTR, ssepTD , m_mapKnl );  
	}

	
	void trimall()
	{
		std::map< std::string, std::string > mapTmp = m_mapKnl;

		this->clear();

		for( MAP_MAPKNL_IT it = mapTmp.begin(); it != mapTmp.end(); ++it )
		{
			std::string s1 = it->first;
			std::string s2 = it->second;

			SStrf::strim( s1 );
			SStrf::strim( s2 );

			this->let( s1, s2 ); 
		}
	}


	tbool serialize( std::string & strOut ) const
	{
		strOut = "";

		SCake ckTmp;

		for( MAP_MAPKNL_CONSTIT it = m_mapKnl.begin(); it != m_mapKnl.end(); ++it )
		{
			ckTmp.lets( it->first );
			seri_element_en( ckTmp );
			strOut += ckTmp.buf();

			strOut += "(";

			ckTmp.lets( it->second );
			seri_element_en( ckTmp );
			strOut += ckTmp.buf();

			strOut += ")";
		}

		return 1;
	}


	tbool unserialize( const std::string & strData )
	{
		std::map< std::string, std::string > mapTmp;
		SCake ckTmp1,ckTmp2;

		SStrvs::vsa2v_prpt( strData, std::string(")"), std::string("(") , mapTmp );
		this->clear();

		for( MAP_MAPKNL_IT it = mapTmp.begin(); it != mapTmp.end(); ++it )
		{
			ckTmp1.lets( it->first );
			seri_element_de( ckTmp1 );
			ckTmp2.lets( it->second );
			seri_element_de( ckTmp2 );

			let( std::string(ckTmp1.buf()), std::string(ckTmp2.buf()) ); 
		}

		return 1;
	}

};




X011_NAMESPACE_END

#endif




/*
rice
*/

#ifndef X011__H_w_IRice_h
#define X011__H_w_IRice_h




X011_NAMESPACE_BEGIN



class IRice
{

protected:

	SCake m_ckDataL2CacheBuf;


protected:

	tsize sys_recv( SCake & ckDataBuf )
	{
		int i = on_sys_recv(ckDataBuf); //no matter how long received, just got the rtn.
		if(i)
		{
			return i;
		}
		else
		{
			ckDataBuf.redim(0);
			return 0;
		}
	}


	tsize sys_send( const SCake & ckDataBuf )
	{
		return on_sys_send(ckDataBuf);
	}



public:

	IRice( )
	{
		//
	}


	virtual ~IRice( )
	{ ; }


	void ClearL2Cache()	
	{
		m_ckDataL2CacheBuf.redim(0);
	}


	tbool send_str( std::string s ) //return if send success
	{
		return send_str(s.c_str());
	}

	
	tbool send_str( const tchar *s ) //return if send success //write str means not write c00.
	{
		SCake ckTmp(s);
		ckTmp.cut(1);
		return send_bin( ckTmp );
	}


	tbool send_bin( const SCake & ckData )
	{
		tsize rc, k;
		if(ckData.len()==0) return 0;
		for(k=0;;)
		{
			SCake ckTmp(ckData.buf_const()+k, ckData.len()-k);
			rc = sys_send( ckTmp );
			if(rc==0) return 0;
			k += rc;
			if(k>=ckData.len()) break;
		}
		return 1;
	}


	template<class T>
	tbool send_bin( T adata )
	{
		SCake ck;
		ck.let( (SCake::CkEle_t*)&adata, sizeof(T) );
		return send_bin(ck);
	}


	//tbool send_esc( SCake ckData , tchar a1, tchar a2, tchar a3 ) //for com use
	//{
	//	ckData.comesc_en(a1,a2,a3);
	//	return send_bin( ckData );
	//}




	tbool recv_bin( SCake & ckData ) //current available data
	{
		SCake ckTmp;

		if( m_ckDataL2CacheBuf.len() == 0 )//如果不判断，上来就接收，会block在这里。
		{
			sys_recv( ckTmp ); //没有L2数据时我们才真去接收.
			m_ckDataL2CacheBuf.append(ckTmp);//其实这里就是直接等于收到的所有数据。
		}
		else
		{
			//
		}

		ckData = m_ckDataL2CacheBuf;
		m_ckDataL2CacheBuf.redim(0);
		return ckData.len()==0?0:1;
	}


	tbool recv_all( SCake & ckData ) //all data of this session
	{
		SCake ckTmp;
		do
		{
			if( !sys_recv( ckTmp ) ) break;
			m_ckDataL2CacheBuf.append(ckTmp);

			if( !on_chk_L2CacheLen( m_ckDataL2CacheBuf ) ) break; //chk long data

		}while(ckTmp.len()>0);

		ckData = m_ckDataL2CacheBuf;
		m_ckDataL2CacheBuf.redim(0);
		return ckData.len()==0?0:1;
	}


	
	tbool recv_all_f( SCake & ckData ) //all data of this session, fast append
	{
		SCake ckTmp;
		do
		{
			if( !sys_recv( ckTmp ) ) break;
			//m_ckDataL2CacheBuf.append(ckTmp);
			m_ckDataL2CacheBuf.FastAppend(ckTmp);

			//if( !on_chk_L2CacheLen( m_ckDataL2CacheBuf ) ) break; //chk long data

		}while(ckTmp.len()>0);

		m_ckDataL2CacheBuf.FastAppendEnd();

		ckData = m_ckDataL2CacheBuf;
		m_ckDataL2CacheBuf.redim(0);
		return ckData.len()==0?0:1;
	}


	tbool recv_len( SCake & ckData , tsize iWantDataLen ) //appointed lenth of data
	{
		SCake ckTmp;

		while( m_ckDataL2CacheBuf.len()< iWantDataLen )
		{
			if( !sys_recv( ckTmp ) ) break;

			//m_ckDataL2CacheBuf.append(ckTmp);
			m_ckDataL2CacheBuf.FastAppend(ckTmp);
		}

		m_ckDataL2CacheBuf.FastAppendEnd();
		
		ckData.redim(iWantDataLen);
		m_ckDataL2CacheBuf.dump( ckData );//maybe dumped less than appointed len of data, if not enough len of data available and remote died.
		return ckData.len()+m_ckDataL2CacheBuf.len()==0?0:1;
	}


	
	tbool recv_ln( SCake & ckData , const std::vector<std::string> & vecstrSeperate, std::string * pstrRealSep=NULL ) //pstrRealSep to return real seperator 
	{
		SCake ckTmp;
		tchar * pSep;
		SCake ckSepDumpTmp;
		
		do
		{
			SCake ckTmpL2Cache2;
			ckTmpL2Cache2 = m_ckDataL2CacheBuf;
			ckTmpL2Cache2.mk_sz();
			
			pSep = NULL;

			if(pstrRealSep) *pstrRealSep = "";

			//pSep = SStrf::sstr( m_ckDataL2CacheBuf, strSeperate );	//the L2cache is not a sz. use strstr will cause run-time error.
			for( std::vector<std::string>::const_iterator it = vecstrSeperate.begin();
				 it != vecstrSeperate.end();
				 ++it )
			{
				pSep = SStrf::sstr( ckTmpL2Cache2, it->c_str() );
				if( pSep )
				{
					if(pstrRealSep) *pstrRealSep = *it;

					ckSepDumpTmp.lets(*it);
					ckSepDumpTmp.cut(1); //the strSeperate is sz. remove the last '\0'
					break;
				}
			}
			
			
			if( pSep )
			{
				//ckData.redim( (tsize)(pSep - m_ckDataL2CacheBuf.buf() ) ); 
				ckData.redim( (tsize)(pSep - ckTmpL2Cache2.buf() ) );
				
				m_ckDataL2CacheBuf.dump( ckData );
				m_ckDataL2CacheBuf.dump( ckSepDumpTmp ); //get rid of the leading sep str in L2Cache. 
				return 1;
			}
			
			if( !sys_recv( ckTmp ) ) break;
			m_ckDataL2CacheBuf.append(ckTmp);

			if( !on_chk_L2CacheLen( m_ckDataL2CacheBuf ) ) break; //chk long line

		}while(ckTmp.len()>0);

		ckData = m_ckDataL2CacheBuf;	//找到sep的情况已在while中return。这里是收失败时的情况了。
		m_ckDataL2CacheBuf.redim(0);
		return ckData.len()==0?0:1;
	}

		
	tbool recv_ln( SCake & ckData , const tchar * strSeperate = "\n" ) //use Seperate
	{
		if( strSeperate && std::string(strSeperate) == "\r\n\r\n\r\n" )
			return recv_ln2( ckData , strSeperate );
		
		SCake ckTmp;
		tchar *pSep;
		SCake ckSepDumpTmp(strSeperate);
		
		ckSepDumpTmp.cut(1); //the strSeperate is sz. remove the last '\0'
		
		do
		{
			SCake ckTmpL2Cache2;
			ckTmpL2Cache2 = m_ckDataL2CacheBuf;
			ckTmpL2Cache2.mk_sz();
			
			//pSep = SStrf::sstr( m_ckDataL2CacheBuf, strSeperate );	//the L2cache is not a sz. use strstr will cause run-time error.
			pSep = SStrf::sstr( ckTmpL2Cache2, strSeperate );
			
			if( pSep )
			{
				//ckData.redim( (tsize)(pSep - m_ckDataL2CacheBuf.buf() ) ); 
				ckData.redim( (tsize)(pSep - ckTmpL2Cache2.buf() ) );
				
				m_ckDataL2CacheBuf.dump( ckData );
				m_ckDataL2CacheBuf.dump( ckSepDumpTmp ); //get rid of the leading sep str in L2Cache. 
				return 1;
			}
			
			if( !sys_recv( ckTmp ) ) break;

			m_ckDataL2CacheBuf.append(ckTmp);

			if( !on_chk_L2CacheLen( m_ckDataL2CacheBuf ) ) break; //chk long line

		}while(ckTmp.len()>0);

		ckData = m_ckDataL2CacheBuf;	//找到sep的情况已在while中return。这里是收失败时的情况了。
		m_ckDataL2CacheBuf.redim(0);
		return ckData.len()==0?0:1;
	}



	tbool recv_ln( SCake & ckData , tchar cSeperate ) //use Seperate
	{
		tchar t[2];
		t[0]=cSeperate;
		t[1]=0;
		return recv_ln(ckData,t) ;
	}

	

	tbool recv_ln2( SCake & ckData , const tchar * strSeperate )  //no buf-limit-check and _fast
	{
		SCake ckTmp;
		tchar *pSep;
		SCake ckSepDumpTmp(strSeperate);
		
		ckSepDumpTmp.cut(1); 


		std::vector<tchar>  vec_m_ckTmpL2CacheBuf;
		std::copy( m_ckDataL2CacheBuf.buf(), m_ckDataL2CacheBuf.buf() + m_ckDataL2CacheBuf.len(), std::back_inserter(vec_m_ckTmpL2CacheBuf) );

		long lLastChkOffset(0);

		do
		{
			vec_m_ckTmpL2CacheBuf.push_back(0);
			
			pSep = SStrf::sstr( &(vec_m_ckTmpL2CacheBuf[lLastChkOffset]), strSeperate );

			vec_m_ckTmpL2CacheBuf.pop_back();


			if( pSep )
			{
				//restore m-buf
				//
				if( vec_m_ckTmpL2CacheBuf.empty() )
					m_ckDataL2CacheBuf.redim(0);
				else
					m_ckDataL2CacheBuf.let( &(vec_m_ckTmpL2CacheBuf[0]), (tsize)vec_m_ckTmpL2CacheBuf.size() );

				vec_m_ckTmpL2CacheBuf.clear();
				//end restore

				SCake ckTmpL2Cache2;
				ckTmpL2Cache2 = m_ckDataL2CacheBuf;
				ckTmpL2Cache2.mk_sz();

				pSep = SStrf::sstr( ckTmpL2Cache2, strSeperate );

				ckData.redim( (tsize)(pSep - ckTmpL2Cache2.buf() ) );
				
				m_ckDataL2CacheBuf.dump( ckData );
				m_ckDataL2CacheBuf.dump( ckSepDumpTmp ); 
				return 1;
			}
			else
			{
				//if( !pSep) then we must modify the lLastChkOffset
				lLastChkOffset = (long)vec_m_ckTmpL2CacheBuf.size() - (long)ckSepDumpTmp.len();
				if( lLastChkOffset < 0 ) lLastChkOffset = 0;				 
			}

			
			if( !sys_recv( ckTmp ) ) break;

			std::copy( ckTmp.buf(), ckTmp.buf() + ckTmp.len(), std::back_inserter(vec_m_ckTmpL2CacheBuf) ); 
			/*
			将一个vector连接另一个vector末尾的最佳方法是什么？ 	
			v1.insert(v1.end(),   v2.begin(),   v2.end()   );   
			because   vector::insert   will   calculate   the   size   of   inserted   elemenets   and   allocate   the   space   only   once,   then   copy   the   data   from   v2   to   v1.
			---------
			这是最快的办法：   
			std::copy(v2.begin(),   v2.end(),   std::back_inserter(v1));
			*/

			//if( !on_chk_L2CacheLen( m_ckDataL2CacheBuf ) ) break; 

		}while(ckTmp.len()>0);

		
		//restore m-buf
		//
		if( vec_m_ckTmpL2CacheBuf.empty() )
			m_ckDataL2CacheBuf.redim(0);
		else
			m_ckDataL2CacheBuf.let( &(vec_m_ckTmpL2CacheBuf[0]), (tsize)vec_m_ckTmpL2CacheBuf.size() );

		vec_m_ckTmpL2CacheBuf.clear();
		//end restore


		ckData = m_ckDataL2CacheBuf;
		m_ckDataL2CacheBuf.redim(0);
		return ckData.len()==0?0:1;
	}



public:

	virtual tbool on_chk_L2CacheLen( const SCake & ckCurrentL2Cache )
	{
		return 1;
	}


	virtual int on_sys_recv( SCake & ckDataBuf ) //return the real recv len
	{
		return 0;
	}


	virtual int on_sys_send( const SCake & ckDataBuf ) //return the successfully sent len
	{
		return 0;
	}


};//end SRice





X011_NAMESPACE_END

#endif




/*
ICursor interface
*/

#ifndef X011__H_w_ICursor_h
#define X011__H_w_ICursor_h



X011_NAMESPACE_BEGIN


template < class envT, class tblT, class rowT >
class ICursor
{

private:

	tbool		 m_bIsEnvOpen;
	tbool		 m_bIsTblOpen;

	
public:

	ICursor( )
	{
		m_bIsEnvOpen = m_bIsTblOpen = 0;
	}


	virtual ~ICursor( )
	{ 
		//CloseB();
	}

	
public:

	typedef envT envTYPE;
	typedef tblT tblTYPE;
	typedef rowT rowTYPE;

	
public:

	tbool GetIsEnvOpen()
	{
		return m_bIsEnvOpen;
	}

	tbool GetIsTblOpen()
	{
		return m_bIsTblOpen;
	}
	
	
public:

	tbool OpenEnv( envTYPE & _env )
	{
		CloseEnv();	
		return m_bIsEnvOpen = OnOpenEnv(_env);
	}

	tbool OpenTbl( tblTYPE & _tbl )
	{
		CloseTbl();
		return m_bIsTblOpen = OnOpenTbl(_tbl);
	}

	tbool FetchRow( rowTYPE & _row )
	{
		return OnFetchRow( _row );
	}

	void CloseTbl()
	{
		if( GetIsTblOpen() ) OnCloseTbl();
		m_bIsTblOpen=0;
	}

	void CloseEnv()
	{
		if( GetIsEnvOpen() ) OnCloseEnv();
		m_bIsEnvOpen=0;
	}


public:

	virtual tbool OnOpenEnv( envTYPE & _env )
	{
		return 0;
	}

	virtual tbool OnOpenTbl( tblTYPE & _tbl )
	{
		return 0;
	}

	virtual tbool OnFetchRow( rowTYPE & _row )
	{
		return 0;
	}
	
	virtual void OnCloseTbl()
	{
		return;
	}
	
	virtual void OnCloseEnv()
	{
		return;
	}

};//end ICursor







//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



//a cursor data store

template < class IDS_ELE_TYPET >
class ICursorDs_base : public ICursor < std::string,  // envT,
										std::string,  // tblT, 
										std::vector<IDS_ELE_TYPET>  > // rowT  
{
public:

	typedef IDS_ELE_TYPET IDSeleTYPE; 

public:

	virtual ~ICursorDs_base( )
	{ ;
	}
	 

};//end ICursorDs_base




//a cursor data store

class ICursorDs	: public ICursorDs_base < std::string > 
{

public:

	virtual ~ICursorDs( )
	{ ;
	}
	 

};//end ICursorDs






X011_NAMESPACE_END

#endif






/*
question and answer record
qar interface
*/

#ifndef X011__H_w_IQar_h
#define X011__H_w_IQar_h



X011_NAMESPACE_BEGIN


template < class QuestionT, class AnswerT >
class IQar
{

private:


public:

	IQar( )
	{
		// 
	}

	virtual ~IQar( ) { ; }


public:

	tbool IsMyQuestion( const QuestionT & a_Question )  
	{
		return OnIsMyQuestion(a_Question);
	}


	tbool Question( const QuestionT & a_Question , AnswerT & a_Answer ) 
	{
		//if( IsMyQuestion( a_Question ) ) //don't use this line. we should call IsMyQuestion explicitly.
		{
			return OnQuestion( a_Question, a_Answer );
		}
		//else
		//{
		//	return 0;
		//}
	}


public:

	virtual tbool OnIsMyQuestion( const QuestionT & a_Question )  
	{
		return 1;
	}


	virtual tbool OnQuestion( const QuestionT & a_Question , AnswerT & a_Answer )
	{
		return 0;
	}


};//end class IQar




X011_NAMESPACE_END

#endif





/*
W series
vector string
*/

#ifndef X011__H_w_wstrvs_h
#define X011__H_w_wstrvs_h



X011_NAMESPACE_BEGIN


class WStrvs {

public:

	//WStrvs(){;} 

	virtual ~WStrvs(){;}

	template < class CStrT > /* for CString */
	static tsize vsa_imp( const CStrT & ssource, const CStrT & ssep, tbool istoken, std::vector<CStrT> & rtnlst )
	{
		std::vector<tint32> vAbuf, vBbuf;
		tint32 ltmp_npointer,ltmp_mpointer,ltmp_calci,ltmp_calcj,ltmp_calck, ltmp_boundb1, ltmp_boundb2;
		tint32 findpos;
		ltmp_mpointer = ltmp_calci = ltmp_calcj = 0;
		ltmp_npointer = (tint32)ssource.GetLength();
		ltmp_calck = (tint32)ssep.GetLength();

		do //fakedo
		{
			if(ltmp_calck==0)
			{
				rtnlst.push_back(ssource);
				break;
			}

			do 
			{
				if(ltmp_mpointer>=ltmp_npointer) break;
				findpos = ssource.Find( ssep, ltmp_mpointer ); //the knl. find() return from 0 on.
				if(findpos==-1) break;
				ltmp_calci = (tint32)findpos;
				ltmp_mpointer = ltmp_calci;

				vAbuf.push_back(ltmp_calci);
				ltmp_calcj ++;
				ltmp_mpointer += ltmp_calck;

			} while(1);

			ltmp_boundb1 = 0 ; // lowerbound(vAbuf) 
			ltmp_boundb2 = ltmp_calcj - 1 ; // upperbound(vAbuf)

			ltmp_calcj = 0;
			vBbuf.push_back(ltmp_calcj);
			for(ltmp_calci=ltmp_boundb1;ltmp_calci<=ltmp_boundb2;ltmp_calci++){
				ltmp_calcj = vAbuf[ltmp_calci];
				vBbuf.push_back(ltmp_calcj);
				vBbuf.push_back(ltmp_calcj+ltmp_calck);
			}
			vBbuf.push_back( ltmp_npointer );

			ltmp_calcj = (tint32)vBbuf.size();
			for(ltmp_calci=0;ltmp_calci<ltmp_calcj;ltmp_calci+=2)
			{
				ltmp_mpointer = vBbuf[ltmp_calci];
				ltmp_npointer = vBbuf[ltmp_calci+1];
				ltmp_calck = ltmp_npointer - ltmp_mpointer;

				if(istoken&&ltmp_calck==0){
					;
				}else
					rtnlst.push_back( ssource.Mid( ltmp_mpointer, ltmp_calck ) ); //the knl. substr(pos{suffix},len)

			}
			
		}while(0);

		return (tsize)rtnlst.size();
	}


	template < class StrT > /* std string style */
	static tsize vsa_hm( const StrT & ssource, const StrT & ssep, tbool istoken )
	{
		return vsa_imp( ssource, ssep, istoken, std::vector<StrT>() );
	}

	
	//iwhich is suffix. from 0 on.
	template < class StrT > /* std string style */
	static StrT vsa_get( const StrT & ssource, const StrT & ssep, tbool istoken, tsize iwhich )
	{
		std::vector<StrT> tmplst;
		if( iwhich<vsa_imp( ssource, ssep, istoken, tmplst ) )
			return tmplst[iwhich];
		else return StrT();
	}
	

	template < class CStrT > /*only for ms CString*/
	static tsize vsa_token( const CStrT &source, const CStrT &tok, std::vector<CStrT> & rtnlst )
	{
		CStrT s1, resToken;
		CStrT sempty;
		int curPos= 0;
		tsize licounter;
		licounter=0;
		s1 = source;
		sempty = "";
		resToken= s1.Tokenize(tok,curPos);
		while( resToken !=sempty )
		{
			licounter++;
			rtnlst.push_back( resToken );
			resToken= s1.Tokenize(tok,curPos);
		}
		return licounter;
	}


	template < class CStrT >
	static tsize vsa_hm( const CStrT & source, const CStrT & tok )
	{
		return vsa_token( source, tok, std::vector<CStrT>() );
	}
	

    //iwhich is suffix. from 0 on.
	template < class CStrT >
	static CStrT vsa_get( const CStrT & source, const CStrT & tok , tsize iwhich )
	{
		std::vector<CStrT> tmplst;
		if( iwhich<vsa_token( source, tok, tmplst ) )
			return tmplst[iwhich];
		else return CStrT();
	}

	
}; //end class 





X011_NAMESPACE_END

#endif



/*
W series
CriticalSection 
*/

/*用法例
wl::WCrsc 	m_cmapLock;
static wl::WCrsc m_csCmdDataPoolLock;

volatile  wl::WCrsc aLock( this->m_cmapLock );
*/

#ifndef X011__H_w_wcrsc_h
#define X011__H_w_wcrsc_h


X011_NAMESPACE_BEGIN


class WCrsc 
{

private:

	CRITICAL_SECTION * m_pcsFather;


private:
	//to copy the object is not allowed.

	/*WCrsc & operator = (const WCrsc & rhs)
	{
		return *this;
	}*/

	//WCrsc(const WCrsc & rhs)
	//{;}

	void LockCrsc( WCrsc & Crsc_father )
	{
		EnterCriticalSection( m_pcsFather = Crsc_father.m_pcsSelf );
	}


public:

	CRITICAL_SECTION * m_pcsSelf;


public:

	WCrsc()
	{
		m_pcsFather = NULL;
		m_pcsSelf = NULL;

		m_pcsSelf = new CRITICAL_SECTION;
		InitializeCriticalSection( m_pcsSelf );
	}
    

	WCrsc( WCrsc & Crsc_father)
	{
		m_pcsFather = NULL;
		m_pcsSelf = NULL;
		
		LockCrsc( Crsc_father );
	}

	WCrsc( WCrsc * pCrsc_father)
	{
		m_pcsFather = NULL;
		m_pcsSelf = NULL;
		
		if( pCrsc_father ) LockCrsc( *pCrsc_father );
	}


	virtual ~WCrsc()
	{
		if( m_pcsFather != NULL )
		{
			LeaveCriticalSection( m_pcsFather );
			return;
		}
		
		if( m_pcsFather == NULL )
		{
			if( m_pcsSelf != NULL )
			{
				DeleteCriticalSection( m_pcsSelf );
				delete m_pcsSelf;
				return;
			}
		}
	}

}; //end class 




X011_NAMESPACE_END

#endif





/*
w_WUniTblCh,   char型字符串支持的sqllike
*/

// 


#ifndef X011__W_WUNITBLCH_H
#define X011__W_WUNITBLCH_H




X011_NAMESPACE_BEGIN



class unitbl_base_t
{
public:
	wl::WCrsc		m_ut_tbl_lck; 
	
public:
	virtual ~unitbl_base_t() {;}

	virtual void ut_ClearTbl() = 0;

	virtual int ut_GetColAmount() = 0;
	virtual std::string ut_GetColName( int iColNum ) = 0;

	virtual long ut_GetRowAmount() = 0;

	virtual std::string ut_GetRowSeriStr( long lRowNum ) = 0; 

	virtual std::string ut_GetItemStr( long lRowNum, std::string strColName ) = 0; 
	virtual std::string ut_GetItemStr( long lRowNum, int iColNum ) = 0; 

	virtual void ut_SetItemByStr( long lRowNum, std::string strColName, std::string strValPARA  ) = 0; 
	virtual void ut_SetItemByStr( long lRowNum, int iColNum ,           std::string strValPARA  ) = 0; 

	virtual long ut_AddRow() = 0;
	virtual long ut_AddRow( std::string strRowSeriStr) = 0;

	virtual std::string & ut_SeriTbl( std::string & strOut )=0;
	virtual unitbl_base_t & ut_UnseriTbl( const std::string & strIn, int biAppend ) = 0;

	virtual void ut_DelRowf( long lRowNum ) = 0; 
	virtual void ut_DelRow( long lRowNum ) = 0; 
};





template<class T>
class unitbl_t : public unitbl_base_t , public T 
{
public:
	virtual ~unitbl_t() {;}


public:

	virtual void ut_ClearTbl()
	{
		T::Clear();
	}

	virtual int ut_GetColAmount()
	{
		return T::GetRow(-1).GetColAmount() ;
	}


	virtual std::string ut_GetColName( int iColNum ) 
	{
		return T::GetRow(-1).GetColName( iColNum );
	}


	virtual long ut_GetRowAmount() 
	{
		return T::GetRowCount( );
	}

	virtual std::string ut_GetRowSeriStr( long lRowNum ) 
	{
		return T::GetRow(lRowNum).Serialize();
	}
	

	virtual std::string ut_GetItemStr( long lRowNum, std::string strColName )
	{
		std::string s1;
		T::GetRow(lRowNum).GetColStr( strColName, s1 );
		return s1;
	}


	virtual std::string ut_GetItemStr( long lRowNum, int iColNum )
	{
		std::string s1;
		T::GetRow(lRowNum).GetColStr( iColNum, s1 );
		return s1;
	}
 
	virtual void ut_SetItemByStr( long lRowNum, std::string strColName, std::string strValPARA ) 
	{
		T::GetRow(lRowNum).SetColVal( strColName, strValPARA );
	}

	virtual void ut_SetItemByStr( long lRowNum, int iColNum ,           std::string strValPARA ) 
	{
		T::GetRow(lRowNum).SetColVal( iColNum, strValPARA );
	}

	virtual long ut_AddRow() 
	{
		T::Add(T::GetRow(-1));
		return T::GetRowCount() - 1 ;
	}

	virtual long ut_AddRow( std::string strRowSeriStr ) 
	{
		typename T::ROWTYPE row1;
		row1.Unserialize( strRowSeriStr.c_str() );
		T::Add(row1);
		return T::GetRowCount() - 1 ;
	}

	
	virtual std::string & ut_SeriTbl( std::string & strOut )
	{
		return T::Serialize( strOut );
	}


	virtual unitbl_base_t & ut_UnseriTbl( const std::string & strIn, int biAppend )
	{
		T::Unserialize( strIn.c_str() , biAppend )	;
		return *this;
	}


	virtual void ut_DelRowf( long lRowNum ) 
	{
		T::DelInternal( lRowNum );
	}

	virtual void ut_DelRow( long lRowNum )
	{
		T::Del( lRowNum );
	}

};




X011_NAMESPACE_END

#endif



/*
W series
clip 
*/


#ifndef X011__H_w_WClp_h
#define X011__H_w_WClp_h


X011_NAMESPACE_BEGIN


class WClp
{

public:

	WClp()
	{
	}

	/*virtual*/ ~WClp()
	{
	}

	static tbool txt_put( std::string txtdata ) 
	{
		tchar *buffer;
		if(OpenClipboard(0)) {
			HGLOBAL clipbuffer;
			EmptyClipboard();
			clipbuffer = GlobalAlloc(GMEM_MOVEABLE, SStrf::slen(txtdata.c_str())+1);
			buffer = (tchar *)GlobalLock(clipbuffer);
			SStrf::scpy( buffer, txtdata.c_str() );
			GlobalUnlock( clipbuffer );
			SetClipboardData( CF_TEXT, clipbuffer );
			CloseClipboard();
			GlobalFree(clipbuffer);
			return 1;
		}else{
			return 0;
		}
	}

	static tbool txt_put( tchar * txtdata ) 
	{
		return txt_put( std::string(txtdata?txtdata:"") );
	}



	static std::string txt_get()
	{
		char *buffer;
		std::string strtmp("");

		if ( OpenClipboard(0) )
		{
			HANDLE hData = GetClipboardData(CF_TEXT); 
			buffer = (char *)GlobalLock(hData);

			if(buffer) 
				strtmp = buffer;

			GlobalUnlock(hData);
			CloseClipboard();
		}
		return strtmp;
	}

	//
	static CString txt_getTS()
	{
		CStringW strtmp(L"");

		if ( OpenClipboard(0) )
		{
			HANDLE hData = GetClipboardData(CF_UNICODETEXT); 
			wchar_t * buffer = (wchar_t *)GlobalLock(hData);

			if(buffer) 
				strtmp = buffer;

			GlobalUnlock(hData);
			CloseClipboard();
		}
		return CString(strtmp);
	}

}; //end class 




X011_NAMESPACE_END

#endif


/*
W series
hwnd and sndmsg routines 
*/

// 

#ifndef X011__H_w_wmsg_h
#define X011__H_w_wmsg_h


X011_NAMESPACE_BEGIN


class WMsg
{

private:

	static BOOL CALLBACK EnumHwndProc( HWND hwnd, LPARAM lParam )	//后一个参数是pvec,得到HWND 的一个vec
	{
		std::vector< HWND > * pvecHwnd;
		//i = GetWindowTextLengthA(hwnd);
		//GetWindowTextA(hwnd, ivp_winlist->cf_getlastrow()->cf_readtop(), i-1 );
		pvecHwnd = (std::vector < HWND > *)lParam;
		pvecHwnd->push_back(hwnd);
		return 1;
	}

 
public:

	WMsg()
	{
		 
	}

	//virtual ~WMsg()	{ 	}


	static tsize snapshot( std::vector< HWND > & vecRtnHwndBuf )
	{
		vecRtnHwndBuf.clear();
		EnumWindows( EnumHwndProc, (LPARAM)&vecRtnHwndBuf );
		return (tsize)vecRtnHwndBuf.size();
	}


	static tsize snapshot( HWND hwnd, std::vector< HWND > & vecRtnHwndBuf ) //EnumChildWindows
	{
		vecRtnHwndBuf.clear();
		EnumChildWindows(hwnd, EnumHwndProc, (LPARAM)&vecRtnHwndBuf );
		return (tsize)vecRtnHwndBuf.size();
	}



	static tsize snapshot( HWND HwndContainer, std::map< std::string , HWND > & mapHdl ) // 
	{
		std::vector< HWND > vecHwndBuf;

		if( HwndContainer == 0 )
			snapshot( vecHwndBuf );
		else
			snapshot( HwndContainer, vecHwndBuf );

		for( std::vector<HWND>::iterator it= vecHwndBuf.begin(); it != vecHwndBuf.end(); ++it )
		{
			std::string s;
			
			s = WMsg::win_text( *it );
			if( s.empty() ) continue;

			mapHdl.insert( std::pair< std::string , HWND >( s, *it ) );
		}

		return (tsize)mapHdl.size();
	}


	static tsize snapshot( std::string strHwndContainer, std::map< std::string , HWND > & mapHdl ) // 
	{
		HWND iInput = 0;
		(*SClib::p_sscanf()) ( ("0"+strHwndContainer).c_str(), "%x", &iInput );

		return snapshot( iInput, mapHdl );
	}




///////////以下试验中：

typedef		struct 
{
	HWND hh1;
	DWORD dwProcId;
	DWORD dwThreadId;
	HANDLE hh3;
}	Hnd3TYPE;


	static tsize GetH3( std::vector<Hnd3TYPE> & vout ) //HWND与HANDLE对照表,多个窗口对应一个进程
	{
		//std::vector<HWND> & vHwnd, std::vector<DWORD> & vProcId, std::vector<HANDLE> & vHandle
		std::map< std::string , HWND > mapHdl;
		HWND parenthwnd ;
		DWORD dwProcId ;
		DWORD dwThreadId ;
		HANDLE hProcess ;

		snapshot( "0", mapHdl );

		for( std::map< std::string , HWND >::iterator it= mapHdl.begin(); it != mapHdl.end(); ++it )
		{
			parenthwnd = it->second ;
			::GetWindowThreadProcessId( parenthwnd, &dwProcId );
			dwThreadId = ::GetWindowThreadProcessId(parenthwnd, NULL);
			hProcess = ::OpenProcess( PROCESS_QUERY_INFORMATION, FALSE, dwProcId );   

			Hnd3TYPE h3;

			h3.hh1 = parenthwnd;
			h3.dwProcId = dwProcId;
			h3.dwThreadId = dwThreadId;
			h3.hh3 = hProcess;

			//CString s;
			//s = GetLastErrorMsgTS();

			vout.push_back( h3 );
		}

		return (tsize)vout.size();
	}


	static HWND GetProc1Hwnd( DWORD dwProcId ) // 多个窗口对应一个进程,此处返回任一个
	{
		std::vector<Hnd3TYPE>  vout;

		GetH3( vout );

		for( std::vector<Hnd3TYPE>::iterator it= vout.begin(); it != vout.end(); ++it )
		{
			if( dwProcId == it->dwProcId ) return it->hh1;
		}
 
		return (HWND)0;
	}




/////////// 试验中 


	static std::string win_text( HWND hwnd )
	{
		int iTextLen ;//= (int)SendMessageA( hwnd, WM_GETTEXTLENGTH ,0, (long)0 );
		
		iTextLen = GetWindowTextLength( hwnd );

		SCake ckText;

		iTextLen *= 4;
		ckText.redim( iTextLen );

		if( GetWindowTextA( hwnd , ckText.buf(), iTextLen ) )
		{
			return ckText.buf();
		}
		else
		{
			return ""; //if win text wrong, rtn a "" string.
		}		
	}


	static CString win_text2( HWND hwnd , int iStringLen )
	{
		CString s;
		DWORD result;
		SendMessageTimeout( hwnd, WM_GETTEXT, iStringLen, (LPARAM)s.GetBuffer(iStringLen), 0, 1000, &result); 
		CString s1(s);
		s.ReleaseBuffer();
		return s1;
	}




	static tbool get_key_down( int vKey )
	{
		return (GetAsyncKeyState(vKey) & 0x8000) ? 1 : 0;
		 //e.g.: if( wl::WMsg::get_key_down(VK_LCONTROL) ) system("pause");
		/*e.g.: 
		if( wl::WMsg::get_key_down(VK_LCONTROL) &&	
			wl::WMsg::get_key_down(VK_RCONTROL)	)
		{
			break;
		}*/
	}



	//mouse functions:

	static POINT mou_get( POINT * ppo = NULL )
	{
		POINT po;
		SStrf::smemset(&po);
		if( ppo ) *ppo = po;
		if( !GetCursorPos( &po ) ) return po;
		if( ppo ) *ppo = po;
		return po;
	}

	static void mou_get( long &x, long &y )
	{
		POINT po = mou_get();
		x = po.x ;
		y = po.y ;
	}

	static void mou_move( long x, long y )
	{ 
		double fScreenWidth = ::GetSystemMetrics( SM_CXSCREEN )-1; 
		double fScreenHeight = ::GetSystemMetrics( SM_CYSCREEN )-1; 
		double fx = x*(65535.0f/fScreenWidth);
		double fy = y*(65535.0f/fScreenHeight);
		//INPUT Input={0};
		//Input.type = INPUT_MOUSE;
		//Input.mi.dwFlags = MOUSEEVENTF_MOVE|MOUSEEVENTF_ABSOLUTE;
		//Input.mi.dx = fx;
		//Input.mi.dy = fy;
		//::SendInput(1,&Input,sizeof(INPUT));

		mouse_event( MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE, static_cast<DWORD>(fx), static_cast<DWORD>(fy), 0, 0 );
	}

	static void mou_left( long x, long y , int itimes = 1 )
	{
		double fScreenWidth = ::GetSystemMetrics( SM_CXSCREEN )-1; 
		double fScreenHeight = ::GetSystemMetrics( SM_CYSCREEN )-1; 
		double fx = x*(65535.0f/fScreenWidth);
		double fy = y*(65535.0f/fScreenHeight);

		mou_move( x, y );

		for( int i = 0 ; i < itimes ; i++ )
		{
			mouse_event ( MOUSEEVENTF_LEFTDOWN , 0, 0, 0, 0 );
			mouse_event ( MOUSEEVENTF_LEFTUP,    0, 0, 0, 0 );
		}
	}

	static void mou_right( long x, long y , int itimes = 1 )
	{
		double fScreenWidth = ::GetSystemMetrics( SM_CXSCREEN )-1; 
		double fScreenHeight = ::GetSystemMetrics( SM_CYSCREEN )-1; 
		double fx = x*(65535.0f/fScreenWidth);
		double fy = y*(65535.0f/fScreenHeight);

		mou_move( x, y );

		for( int i = 0 ; i < itimes ; i++ )
		{
			mouse_event ( MOUSEEVENTF_RIGHTDOWN  , 0, 0, 0, 0 );
			mouse_event ( MOUSEEVENTF_RIGHTUP,     0, 0, 0, 0 );
		}
	}


	//

	static void win_state_max( HWND hwnd )
	{
		SendMessage( hwnd, 274, 61488,		 0 );	//SC_MAXIMIZE		 MoveWindow     ShowWindow
	} 

	static void win_state_normal( HWND hwnd )
	{
		SendMessage( hwnd, 274, SC_RESTORE,  0 );
	}

	static void win_state_min( HWND hwnd )
	{
		SendMessage( hwnd, 274, 61472,		 0 ); //SC_MINIMIZE
	}


	static void win_close(HWND hwnd)
	{
		SendMessage( hwnd, 0x10, 0,	0 );
	}



	static void win_fore(HWND hwnd)
	{
		SetForegroundWindow(hwnd);
				/*this->SetCapture();
				wl::WMsg::win_fore(this->m_hWnd);
				ReleaseCapture();*/
	}



	static HWND win_getfore(void)
	{
		return GetForegroundWindow();
	}

	static void win_show(HWND hwnd, int nCmdShow)
	{
		ShowWindow (hwnd, nCmdShow);
		//例如: ShowWindow(FindWindowA(0, "ywinputwnd"), 8)
		//		ShowWindow(FindWindowA(0, "ywinputwnd"), 0)

		//nCmdShow为窗口指定可视性方面的一个命令
//		SW_HIDE	隐藏窗口，活动状态给另一个窗口
//		SW_MINIMIZE	最小化窗口，活动状态给令一个窗口
//		SW_RESTORE	用原来的大小和位置显示一个窗口，同时令其进入活动状态
//		SW_SHOW	用当前的大小和位置显示一个窗口，同时令其进入活动状态
//		SW_SHOWMAXIMIZED	最大化窗口，并将其激活
//		SW_SHOWMINIMIZED	最小化窗口，并将其激活
//		SW_SHOWMINNOACTIVE	最小化一个窗口，同时不改变活动窗口
//		SW_SHOWNA	用当前的大小和位置显示一个窗口，不改变活动窗口
//		SW_SHOWNOACTIVATE	用最近的大小和位置显示一个窗口，同时不改变活动窗口
//		SW_SHOWNORMAL	与SW_RESTORE相同
	}

	static void win_pos( HWND hWnd, HWND hWndInsertAfter , int X, int Y, int cx, int cy, UINT uFlags)
	{
		SetWindowPos(hWnd,hWndInsertAfter ,X, Y, cx, cy, uFlags);

		//例如:SetWindowPos(FindWindowA(0, "ywinputwnd"), -1, 0, 0, 400, 50, &H40)

		//hWndInsertAfter，窗口句柄。在窗口列表中，窗口hwnd会置于这个窗口句柄的后面。也可能选用下述值之一：	
		//HWND_BOTTOM	将窗口置于窗口列表底部
		//HWND_TOP	将窗口置于Z序列的顶部；Z序列代表在分级结构中，窗口针对一个给定级别的窗口显示的顺序
		//HWND_TOPMOST	将窗口置于列表顶部，并位于任何最顶部窗口的前面
		//HWND_NOTOPMOST	将窗口置于列表顶部，并位于任何最顶部窗口的后面

		//x	Long，窗口新的x坐标。如hwnd是一个子窗口，则x用父窗口的客户区坐标表示	
		//y	Long，窗口新的y坐标。如hwnd是一个子窗口，则y用父窗口的客户区坐标表示	
		//cx	Long，指定新的窗口宽度	
		//cy	Long，指定新的窗口高度

		//uFlags，包含了旗标的一个整数	
		//SWP_DRAWFRAME	围绕窗口画一个框
		//SWP_HIDEWINDOW	隐藏窗口
		//SWP_NOACTIVATE	不激活窗口
		//SWP_NOMOVE	保持当前位置（x和y设定将被忽略）
		//SWP_NOREDRAW	窗口不自动重画
		//SWP_NOSIZE	保持当前大小（cx和cy会被忽略）
		//SWP_NOZORDER	保持窗口在列表的当前位置（hWndInsertAfter将被忽略）
		//SWP_SHOWWINDOW	显示窗口
		//SWP_FRAMECHANGED	强迫一条WM_NCCALCSIZE消息进入窗口，即使窗口的大小没有改变
	}



	static void win_scrsave()
	{
		std::vector< HWND > vecHnd;
		snapshot( vecHnd );
		if( vecHnd.size() ) SendMessage( vecHnd[0], WM_SYSCOMMAND, SC_SCREENSAVE, 0);
	}



	
	static tbool UseCustomResource( int res, CString strType, SCake & rtnCakeBuf )
	{
		//定位我们的自定义资源，这里因为我们是从本模块定位资源，所以将句柄简单地置为NULL即可
		HRSRC hRsrc = FindResource( NULL, MAKEINTRESOURCE(res), strType.GetString() ); 
		if (NULL == hRsrc)
			return 0;
		//获取资源的大小
		DWORD dwSize = SizeofResource(NULL, hRsrc); 
		if (0 == dwSize)
			return 0;
		//加载资源
		HGLOBAL hGlobal = LoadResource(NULL, hRsrc); 
		if (NULL == hGlobal)
			return 0;
		//锁定资源
		LPVOID pBuffer = LockResource(hGlobal); 
		if (NULL == pBuffer)
			return 0;
		//success
		rtnCakeBuf.let( (tchar*)pBuffer, dwSize );
		return 1;
	}






#ifdef VC6_COMPATIBLE_X011_
	//
#else
	static CString GetEnvStrTS( CString strEnvStrName )
	{
		CString EnvStr;
		if( EnvStr.GetEnvironmentVariable(strEnvStrName) )
		{
			return EnvStr;
		}
		else
		{
			return _T("");
		}
	}
#endif
 



	static std::string CutTail( std::string strSrc, std::string strChar )
	{
		if( strChar.size() != 1 )
		{
			return strSrc;
		}
		std::string::size_type nPos;
		nPos = strSrc.find_last_of( strChar[0] );
		if( nPos != std::string::npos )
		{
			strSrc[nPos+1] = 0;
		}
		return strSrc.c_str();
	}

	

	static CString CutTailTS( CString strSrc, CString strChar )
	{
		if( strChar.GetLength() != 1 )
		{
			return strSrc;
		}
		int nPos;
		nPos = strSrc.ReverseFind( strChar[0] );
		if( nPos >= 0 ) strSrc = strSrc.Left(nPos) + strChar;
		return strSrc;
	}
	
	

	static std::string GetProcExePathFilename()	//got the full pathfilename
	{
		tchar szFilename[ _MAX_DRIVE + _MAX_PATH + _MAX_FNAME + _MAX_EXT ] = {0};
		if( GetModuleFileNameA( NULL, szFilename, _MAX_DRIVE + _MAX_PATH + _MAX_FNAME + _MAX_EXT ) )
		{
			return szFilename;
		}
		else
		{
			return "";
		}
	}


	static CString GetProcExePathFilenameTS()
	{
		TCHAR szFilename[ _MAX_DRIVE + _MAX_PATH + _MAX_FNAME + _MAX_EXT ] = {0};
		if( GetModuleFileName( NULL, szFilename, _MAX_DRIVE + _MAX_PATH + _MAX_FNAME + _MAX_EXT ) )
		{
			return szFilename;
		}
		else
		{
			return _T("");
		}
	}


	static CString GetProcExeFilePathTS()
	{
		return  CutTailTS(GetProcExePathFilenameTS(), _T("\\"));
	}


	static std::string GetProcExeFilePath()
	{
		return  CutTail(GetProcExePathFilename(), "\\");
	}




	static std::string MkUId()
	{
		static tint32 i = 1;
		int i2 = (int)time(0) * (int)GetCurrentThreadId() * (int)GetCurrentProcessId();
		int j;
		void *p = SStrf::smalloc(3);
		memcpy( &j, &p, sizeof(int) );
		SStrf::sfree(p);

		double dd = SStrf::rand1() * i * i2 * j * SDte::e_proctime();
		
		std::reverse( (char*)(&dd), (char*)(&dd) + sizeof(double) );

		tchar szBuf[33];
		SClib::p_sprintf()( szBuf, "%x%u", *(int*)(&dd) + j + i , i++ );

		return szBuf;
	}




	static CString GetLastErrorMsgTS()
	{
		DWORD nErr;
		LPVOID lpMsgBuf;
		FormatMessage( 
			FORMAT_MESSAGE_ALLOCATE_BUFFER | 
			FORMAT_MESSAGE_FROM_SYSTEM | 
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			nErr = GetLastError(),
			0, // Default language
			(LPTSTR) &lpMsgBuf,
			0,
			NULL 
		);
		CString str;
		str.Format( _T("GetLastError = %u, %s"), nErr, (LPCTSTR)lpMsgBuf );
		LocalFree( lpMsgBuf );
		return str;
	}



#ifdef VC6_COMPATIBLE_X011_
	//
#else
	static std::string GetLastErrorMsg()
	{
		DWORD nErr;
		LPVOID lpMsgBuf;
		FormatMessage( 
			FORMAT_MESSAGE_ALLOCATE_BUFFER | 
			FORMAT_MESSAGE_FROM_SYSTEM | 
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			nErr = GetLastError(),
			0, // Default language
			(LPTSTR) &lpMsgBuf,
			0,
			NULL 
		);
		// Process any inserts in lpMsgBuf.
		// ...
		// Display the string.
		CString str;
		str.Format( _T("GetLastError = %u, %s"), nErr, (LPCTSTR)lpMsgBuf );
		// Free the buffer.
		LocalFree( lpMsgBuf );

		return CStringA(str).GetString();
	}
#endif



}; //end class WMsg 






/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef VC6_COMPATIBLE_X011_
		//
#else
		 

#ifdef _WINSVC_

class WSvc
{
private:

	CString m_strSZSERVICENAME	; //			_T("VirRervice")
	CString m_strSZSERVICEDISPLAYNAME;	//		_T("Windows Debug Service Manager")
	CString m_strSERVICEDescript;	//	 

private:

	SERVICE_STATUS				m_g_ssServiceStatus;
	SERVICE_STATUS_HANDLE		m_g_sshServiceStatusHandle;


protected:

	static WSvc & Instance()
	{
		static WSvc a;
		return a;
	}


private:
		
	static void WINAPI ServiceCtrlHandler( DWORD dwControl )
	{
		switch (dwControl)
		{

			//下面虽然添加了暂停、继续等请求的处理代码，但没有实际作用
			//这是为什么呢？到了下面的KServiceMain函数里面就明白了...

			case SERVICE_CONTROL_PAUSE:
			Instance().m_g_ssServiceStatus.dwCurrentState = SERVICE_PAUSE_PENDING;
			// TODO: add code to set dwCheckPoint & dwWaitHint
			// This value need to try a lot to confirm 
			// ...
			::SetServiceStatus( Instance().m_g_sshServiceStatusHandle, &(Instance().m_g_ssServiceStatus) );
			// TODO: add code to pause the service
			// not called in this service
			// ...
			Instance().m_g_ssServiceStatus.dwCurrentState = SERVICE_PAUSED;
			// TODO: add code to set dwCheckPoint & dwWaitHint to 0
			break;

			case SERVICE_CONTROL_CONTINUE:
			Instance().m_g_ssServiceStatus.dwCurrentState = SERVICE_CONTINUE_PENDING;
			// TODO: add code to set dwCheckPoint & dwWaitHint
			::SetServiceStatus( Instance().m_g_sshServiceStatusHandle, &(Instance().m_g_ssServiceStatus) );
			// TODO: add code to unpause the service
			// not called in this service
			// ...
			Instance().m_g_ssServiceStatus.dwCurrentState = SERVICE_RUNNING;
			// TODO: add code to set dwCheckPoint & dwWaitHint to 0
			break;

			case SERVICE_CONTROL_STOP:
			Instance().m_g_ssServiceStatus.dwCurrentState = SERVICE_STOP_PENDING;
			// TODO: add code to set dwCheckPoint & dwWaitHint
			::SetServiceStatus( Instance().m_g_sshServiceStatusHandle, &(Instance().m_g_ssServiceStatus) );
			// TODO: add code to stop the service
			Stop();
			Instance().m_g_ssServiceStatus.dwCurrentState = SERVICE_STOPPED;
			// TODO: add code to set dwCheckPoint & dwWaitHint to 0
			break;

			case SERVICE_CONTROL_SHUTDOWN:
			// TODO: add code for system shutdown
			// as quick as possible
			break;

			case SERVICE_CONTROL_INTERROGATE:
			// TODO: add code to set the service status
			// ...
			Instance().m_g_ssServiceStatus.dwCurrentState = SERVICE_RUNNING;
			break;
		}

		::SetServiceStatus( Instance().m_g_sshServiceStatusHandle, &(Instance().m_g_ssServiceStatus) );
	}



	static void WINAPI KServiceMain( DWORD argc, LPTSTR * argv )
	{
		Instance().m_g_ssServiceStatus.dwServiceType = SERVICE_WIN32;
		Instance().m_g_ssServiceStatus.dwCurrentState = SERVICE_START_PENDING;
		Instance().m_g_ssServiceStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP;//上面的问题的答案就在这里
		Instance().m_g_ssServiceStatus.dwWin32ExitCode = 0;
		Instance().m_g_ssServiceStatus.dwServiceSpecificExitCode = 0;
		Instance().m_g_ssServiceStatus.dwCheckPoint = 0;
		Instance().m_g_ssServiceStatus.dwWaitHint = 0;

		Instance().m_g_sshServiceStatusHandle = ::RegisterServiceCtrlHandler( Instance().m_strSZSERVICENAME, ServiceCtrlHandler );

		if ( Instance().m_g_sshServiceStatusHandle == (SERVICE_STATUS_HANDLE)0 )
		{
			return;
		}

		bool bInitialized = false;
		// Initialize the service
		// ...
		Start();

		bInitialized = true;

		Instance().m_g_ssServiceStatus.dwCheckPoint = 0;
		Instance().m_g_ssServiceStatus.dwWaitHint = 0;
		if (!bInitialized )
		{
			Instance().m_g_ssServiceStatus.dwCurrentState = SERVICE_STOPPED;
			Instance().m_g_ssServiceStatus.dwWin32ExitCode = ERROR_SERVICE_SPECIFIC_ERROR;
			Instance().m_g_ssServiceStatus.dwServiceSpecificExitCode = 1;
		}
		else
		{
			Instance().m_g_ssServiceStatus.dwCurrentState = SERVICE_RUNNING;
		}
		::SetServiceStatus( Instance().m_g_sshServiceStatusHandle, &(Instance().m_g_ssServiceStatus) );
		return;
	}


	static void Start()
	{
		//LogEvent("Service Starting...");
		Instance().OnStart();
	}


	static void Stop()
	{
		//LogEvent("Service Stoped.");
		Instance().OnStop();
	}


	/////////====================== ===========


public:

	WSvc()
	{ 
		m_strSZSERVICENAME = _T("");
	}


	virtual ~WSvc()	
	{ ;
	}


	static void Init( CString cstrSvcName, CString cstrSvcDisp, CString cstrSvcDiscript )
	{
		WSvc & A(Instance());

		A.m_strSZSERVICENAME = cstrSvcName;
		A.m_strSZSERVICEDISPLAYNAME =cstrSvcDisp;
		A.m_strSERVICEDescript = cstrSvcDiscript;

		//(*this) = A;
	}


	static tbool SvcDispatcher( CString sname )
	{
		CString sname1;
		sname1.Format( _T("%s"), sname );

		SERVICE_TABLE_ENTRY  e[2] ;

		e[0].lpServiceName = (LPTSTR)sname1.GetString();
		e[0].lpServiceProc = KServiceMain;

		e[1].lpServiceName = NULL;
		e[1].lpServiceProc = NULL;
		 
		return ::StartServiceCtrlDispatcher(e)==0?0:1;
	}



	static tbool SvcDispatcher()	///SvcDispatcher will wait every service thread to return.
	{
		WSvc & A(Instance());
		return SvcDispatcher( A.m_strSZSERVICENAME );
	}



	virtual void OnStart()
	{
		;
	}


	virtual void OnStop()
	{
		;
	}


	/////////=======================================================


	static tbool SCM_InstallService( 
									CString strSvcExeFilename, // if "", then use process exe fullfilename.
									CString strSvcName, 
									CString strSvcDisplayName, 
									CString strSvcDescript, 
									std::string & strErrMsg	 ,
									tbool isAutoStart = 1	) 
	{
		CStringA strErrMsg1("");
		tbool rc(0);

		SC_HANDLE schSCManager = OpenSCManager( NULL, NULL, SC_MANAGER_CREATE_SERVICE); 

		if (schSCManager==0) 
		{
			strErrMsg1.Format( "OpenSCManager failed. %s", WMsg::GetLastErrorMsg().c_str() );
			rc = 0;
			goto L_FuncEnd;
		}
		

		if( strSvcExeFilename == _T("") )
		{
			TCHAR szFilename[256];
			::GetModuleFileName(NULL, szFilename, 255);
			strSvcExeFilename = szFilename;
		}

		SC_HANDLE schService ;
		schService = CreateService
			( 
				schSCManager,                /* SCManager database      */ 
				strSvcName,               /* name of service         */ 
				strSvcDisplayName,        /* service name to display */ 
				SERVICE_ALL_ACCESS,          /* desired access          */ 
				SERVICE_WIN32_OWN_PROCESS|SERVICE_INTERACTIVE_PROCESS ,   /* service type            */ 
				isAutoStart?SERVICE_AUTO_START:SERVICE_DEMAND_START ,     /* start type              */ 
				SERVICE_ERROR_NORMAL,        /* error control type      */ 
				strSvcExeFilename,                  /* service's binary        */ 
				NULL,                        /* no load ordering group  */ 
				NULL,                        /* no tag identifier       */ 
				NULL,                        /* no dependencies         */ 
				NULL,                       /* LocalSystem account     */ 
				NULL                        /* no password             */ 
			);


		if ( schService == NULL ) 
		{
			strErrMsg1.Format( "Failed to create service `%s`. %s", CStringA(strSvcName), WMsg::GetLastErrorMsg().c_str() );
			CloseServiceHandle(schSCManager);
			rc = 0;
			goto L_FuncEnd;
		}
		

		SERVICE_DESCRIPTION  ServiceDesc;
		//TCHAR szDescription[MAX_PATH];
		//_tcscpy( szDescription, strSvcDescript );
		//std::copy( (LPTSTR)(LPCTSTR)strSvcDescript.GetString(), 1 + strSvcDescript.GetLength() + (LPTSTR)(LPCTSTR)strSvcDescript.GetString(), szDescription );
		ServiceDesc.lpDescription   =   (LPTSTR)(LPCTSTR)strSvcDescript.GetString();
		::ChangeServiceConfig2( schService,  SERVICE_CONFIG_DESCRIPTION,  &ServiceDesc );

		//printf( "Service %s installed\n", CStringA(SZSERVICENAME) );
		rc = 1;

		CloseServiceHandle(schService); 
 
		CloseServiceHandle(schSCManager);

   L_FuncEnd:{;}
		strErrMsg = strErrMsg1.GetString();
		return rc;		
	}



	static tbool  SCM_UnInstallService( CString strSvcName , std::string & strErrmsg ) 
	{
		CStringA strErrMsg1("");
		tbool rc(0);

		SC_HANDLE schSCManager = OpenSCManager( NULL, NULL, SC_MANAGER_ALL_ACCESS); 

		if (schSCManager==0) 
		{
			strErrMsg1.Format( "OpenSCManager failed. %s", WMsg::GetLastErrorMsg().c_str() );
			rc = 0;
			goto L_FuncEnd;
		}
	

		SC_HANDLE schService;
		schService = OpenService( schSCManager, strSvcName, SERVICE_ALL_ACCESS );

		if (schService==0) 
		{
			strErrMsg1.Format( "OpenService failed. %s", WMsg::GetLastErrorMsg().c_str() );
			rc = 0;
			goto L_FuncEnd;
		}
	 

		if(!DeleteService(schService)) 
		{
			strErrMsg1.Format( "Failed to delete service. %s", WMsg::GetLastErrorMsg().c_str() );
			rc = 0;
			goto L_FuncEnd;
		}
		
		//printf( "Service %s removed\n", CStringA(SZSERVICENAME) );
		rc = 1;
 
		CloseServiceHandle(schService); 
 
		CloseServiceHandle(schSCManager);

	L_FuncEnd:{;}
		strErrmsg = strErrMsg1.GetString();
		return rc;
	}



	static tbool SCM_SetAutoStartService( 
										CString strServiceName, 
										std::string & strErrmsg , /* out */
										tbool isAutoStart = 1	 )
	{
		SC_HANDLE schSCManager = NULL;
		schSCManager = OpenSCManager( NULL, NULL, SC_MANAGER_ALL_ACCESS);
		if (schSCManager == NULL)
		{
			strErrmsg = "Failed to open SCManager. " + WMsg::GetLastErrorMsg();
			return 0;
		}
		SC_HANDLE schService = OpenService(
			schSCManager,
			strServiceName, 
			SERVICE_ALL_ACCESS);

		if (schService == NULL)
		{
			strErrmsg = "Failed to open service. " + WMsg::GetLastErrorMsg();
			return 0;
		}

		//auto start sevice in next reboot time.
		BOOL bret = ChangeServiceConfig(schService, SERVICE_NO_CHANGE,

			isAutoStart?SERVICE_AUTO_START:SERVICE_DEMAND_START , // 

			SERVICE_NO_CHANGE, NULL, NULL, NULL, NULL, NULL,
			NULL, NULL);

		if(!bret)
		{
			strErrmsg = "failed to configure service. " + WMsg::GetLastErrorMsg();
		}
		else
		{
			//SC_TRACE(_T("Successfully make %s auto_start"), m_szServiceName);
		}

		CloseServiceHandle(schService);
		CloseServiceHandle(schSCManager);

		return bret?1:0;
	}



	static bool SCM_ChgStartAccount( CString m_szServiceName, CString strUserName, CString strUserPwd , std::string & strErrmsg )
	{
		SC_HANDLE schSCManager = NULL;
		schSCManager = OpenSCManager( NULL, NULL, SC_MANAGER_ALL_ACCESS);
		if (schSCManager == NULL)
		{
			strErrmsg = "Failed to open SCManager. " + WMsg::GetLastErrorMsg();
			return false;
		}
		SC_HANDLE schService = OpenService(
			schSCManager,
			m_szServiceName, 
			SERVICE_ALL_ACCESS);

		if (schService == NULL)
		{
			strErrmsg = "Failed to open service. " + WMsg::GetLastErrorMsg();
			return false;
		}

		//auto start sevice in next reboot time.
		BOOL bret = ChangeServiceConfig(schService, SERVICE_NO_CHANGE,
			SERVICE_AUTO_START, SERVICE_NO_CHANGE, NULL, NULL, NULL, NULL, strUserName, strUserPwd, NULL);

		if(!bret)
		{
			strErrmsg = "failed to configure service. " + WMsg::GetLastErrorMsg();
			return false; 
		}
		else
		{
			//SC_TRACE(_T("Successfully make %s auto_start"), m_szServiceName);
		}

		CloseServiceHandle(schService);
		CloseServiceHandle(schSCManager);
		return true;
	}


		
	// simple Install
	 
	static void SimpleInstallService()  
	{
		WSvc & A(Instance());
		std::string strerr;

		WSvc::SCM_InstallService( _T("") , A.m_strSZSERVICENAME, A.m_strSZSERVICEDISPLAYNAME, A.m_strSERVICEDescript, strerr );

		if ( !strerr.empty() )
		{
			printf( "%s\n", strerr.c_str() );
		}
		else
		{
			printf( "ok in i\n" );
		}
	}


	static void SuperInstSvc() 
	{
		std::vector<std::string> vecs1;
		std::string strMyexePathFname = WMsg::GetProcExePathFilename();
		std::string strMyexeFname;

		SStrvs::vsa_imp( strMyexePathFname, std::string("\\"), 1, vecs1 );

		if( !vecs1.empty() )
		{
			std::vector<std::string>::iterator it = vecs1.end();
			it--;
			strMyexeFname = *it;

			std::string s1;		//因为%SystemRoot%中没空格所以以下有些情况可以不加引号了。

			s1 = "cmd /c copy \"" + strMyexePathFname + "\" %SystemRoot%\\";
			s1 += strMyexeFname;
			system(s1.c_str());
			printf( "copied.\n" );

			s1 = "netsh firewall add allowedprogram ";
			s1 += "\"%SystemRoot%\\" + strMyexeFname + "\" ";
			s1 += strMyexeFname;
			system(s1.c_str());
			printf( "sh ed.\n" );

			s1 = "cmd /c %SystemRoot%\\" + strMyexeFname + " -i";
			system(s1.c_str());
		}
	}



	static void SimpleUnInstallService() 
	{
		WSvc & A(Instance());
		std::string strerr;

		WSvc::SCM_UnInstallService( A.m_strSZSERVICENAME, strerr );

		if ( !strerr.empty() )
		{
			printf( "%s\n", strerr.c_str() );
		}
		else
		{
			printf( "ok in un\n" );
		}
	}


	
	static tbool SimpInst( int argc, CString argv ) 
	{
		if ( argc == 2 && argv[1] == _T('i') ) //就地注svc
		{
			SimpleInstallService();
			return 1;
		}

		if ( argc == 2 && argv[1] == _T('s') ) //拷到win目录，同名，注svc，netsh开例外
		{
			SuperInstSvc();
			return 1;
		}

		if ( argc == 2 && argv[1] == _T('-') )
		{
			SimpleUnInstallService();
			return 1;
		}

		return 0;
	}




}
; //end class WSvc 


#endif //_WINSVC_


#endif	//VC6_COMPATIBLE_X011_






X011_NAMESPACE_END

#endif




/*
W series, provide a log class
*/

// 

#ifndef X011__H_w_WLog_h
#define X011__H_w_WLog_h


X011_NAMESPACE_BEGIN


class WLog
{
 
public:

	tbool isEnabled;

	WLog()
	{ 
		EnableLog();
	}

	virtual ~WLog()	{ 	}


	void EnableLog()
	{
		isEnabled = 1;
	}


	void DisableLog()
	{
		isEnabled = 0;
	}


	
#ifndef VC6_COMPATIBLE_X011_
	void LogWritef( int iFilter, LPCSTR Text, ... )
	{
		if( !isEnabled ) return;

		if ( Text == NULL )
		{
			return;
		}

		CStringA sTraceMsgA("");

		// Format the trace text
		va_list args;
		va_start( args, Text );
		sTraceMsgA.AppendFormatV( Text, args );
		va_end(args);

		std::string s( sTraceMsgA.GetString() );
		OnLogWrite(iFilter,s);
	}
 #endif





	
#ifndef VC6_COMPATIBLE_X011_
	void LogWritef( LPCSTR Text, ... )
	{
		if( !isEnabled ) return;

		if ( Text == NULL )
		{
			return;
		}

		CStringA sTraceMsgA("");

		// Format the trace text
		va_list args;
		va_start( args, Text );
		sTraceMsgA.FormatV( Text, args );
		va_end(args);

		std::string s( sTraceMsgA.GetString() );
		OnLogWrite(0,s);
	}
#endif




	
public:

	virtual void OnLogWrite( int iFilter, const std::string & s )
	{
		printf( "%d\t%s\n", iFilter, s.c_str() );
	}

}; //end class WLog 




X011_NAMESPACE_END

#endif




/*
windows file 
*/

#ifndef X011__H_w_WFile_h
#define X011__H_w_WFile_h




X011_NAMESPACE_BEGIN



class WFile : public SFile
{

private:



public:

	WFile( )
	{
		;
	}


	virtual ~WFile( )
	{ ;
	}



	//void rename( std::string strNewNameNoDir )
	//{
	//	std::string strCmd;

	//	strCmd = "ren \"";
	//	strCmd += this->filename();
	//	strCmd += "\" ";
	//	strCmd += "\"" + strNewNameNoDir + "\"";

	//	system( strCmd.c_str() );
	//}


	static tbool FileAttriIsDir( std::string strFullPathName )
	{
		DWORD i = GetFileAttributes( CString(strFullPathName.c_str()) );
		//if( i == INVALID_FILE_ATTRIBUTES )
		//{
		//	return 0;
		//}
		return ( i & FILE_ATTRIBUTE_DIRECTORY ) ? 1 : 0 ;
	}




	static void ListFile(	std::string strRootPathOrDir,	// e.g. "c:\\"  or  "c:\\t"。if you don't specify the rootdir, it will be '\\'
							std::string strPattern,			//e.g. "*.mp3"	"*"
							std::vector<std::string> & vecstrRtnBuf	, 
							tbool bIncludeDirName,
							tbool bIncludeFileName, 
							tbool bRetFullName	)	
	{
		//we don't clear vecstrRtnBuf, so, you can append filenames

		WIN32_FIND_DATAA FindFileData;
		HANDLE hFind = INVALID_HANDLE_VALUE;

		std::string strPathPattern;

		strPathPattern = MkDir2Path( strRootPathOrDir ) + strPattern;
	
		hFind = FindFirstFileA( strPathPattern.c_str(), &FindFileData); // 
	
		do 
		{
			if (hFind == INVALID_HANDLE_VALUE)
			{
				break;
			}

			std::string strFn( FindFileData.cFileName );
			std::string strFullFn( MkDir2Path( strRootPathOrDir ) + strFn );
			std::string strOut;

			if( bRetFullName )
			{
				strOut = strFullFn;
			}
			else
			{
				strOut = strFn;
			}

			if( strFn != "." && strFn != ".." )
			{
				if( bIncludeDirName && FileAttriIsDir( strFullFn ) )
				{
					vecstrRtnBuf.push_back( strOut );
				}

				if( bIncludeFileName && !FileAttriIsDir( strFullFn ) )
				{
					vecstrRtnBuf.push_back( strOut );
				}
			}
			
		}while( FindNextFileA(hFind, &FindFileData) != 0 );
		
		FindClose(hFind);
	}


	static void ListAllFile(	std::string strRootPathOrDir,		// e.g. "c:\\"  or  "c:\\t"。if you don't specify the rootdir, it will be '\\'
								std::string strPattern,				//e.g. "*.mp3"	"*"
								std::vector<std::string> & vecstrRtnBuf	, 
								tbool bIncludeDirName  = 0 ,
								tbool bIncludeFileName = 1 , 
								tbool bRetFullName     = 0 ,
								tbool bRecursive       = 0	)
	{
		//we don't clear vecstrRtnBuf, so, you can append filenames

		if( bRecursive )
		{
			std::vector<std::string>  vecBuf1;
			std::vector<std::string>::iterator itBuf1;
			std::vector<std::string>  vecBuf2;
			std::vector<std::string>  vecBuf_FullName;

			vecBuf1.push_back( strRootPathOrDir );

			do{
				vecBuf2.clear();

				itBuf1 = vecBuf1.begin();

				if( itBuf1 == vecBuf1.end() ) 
				{
					break;
				}

				ListFile( *itBuf1, "*", vecBuf2, 1, 0, 1 ); //record what next to do .
				vecBuf_FullName.insert( vecBuf_FullName.end(), vecBuf2.begin(), vecBuf2.end() ); 

				vecBuf1.erase( itBuf1 ); //del the processed folder

				vecBuf1.insert( vecBuf1.end(), vecBuf2.begin(), vecBuf2.end() ); //insert the new found folders.

			}while(1);

			if( 1 )
			{
				for( std::vector<std::string>::iterator it = vecBuf_FullName.begin();
					 it != vecBuf_FullName.end();
					 ++it )
				{
					ListFile( *it, strPattern, vecstrRtnBuf, bIncludeDirName, bIncludeFileName, bRetFullName ); //record the result.
				}
				ListFile( strRootPathOrDir, strPattern, vecstrRtnBuf, bIncludeDirName, bIncludeFileName, bRetFullName );
			}
		}
		else
		{
			ListFile( strRootPathOrDir, strPattern, vecstrRtnBuf, bIncludeDirName, bIncludeFileName, bRetFullName );
		}
	}



	//
	static void DelHalf( std::string strRootDir, std::string strPattern )			//e.g. "*.mp3"	"*", but this func is slow
	{
		std::vector<std::string>  vecstrRtnBuf;

		ListFile( strRootDir, strPattern, vecstrRtnBuf, 0, 1, 1 );

		for( std::vector<std::string>::iterator it1 = vecstrRtnBuf.begin(); it1 != vecstrRtnBuf.end(); ++it1 )
		{
			for( std::vector<std::string>::iterator it2 = vecstrRtnBuf.begin(); it2 != vecstrRtnBuf.end(); ++it2 )
			{
				SFile f1, f2;
				f1.bind( *it1 );
				f2.bind( *it2 );
				if( f1.IsHeadOf(f2) ) f1.erase();
			} // end for it2
		} // end for it1 
	}


	//pack和unpack,在vaio上测试，906M的目录，读取用4分钟，写盘用5分钟。共约9分钟。
	static void PackFolder( std::string strWorkPathOrDir, SCake & ckOut )
	{
		//std::vector<tchar> v1;
		std::string strWorkPath;
		std::vector<std::string>::iterator it;
		std::vector<std::string> vDirFullNameLst;
		std::vector<std::string> vDirNameLst;
		std::vector<std::string> vFileFullPathNameLst;
		std::vector<std::string> vFileRelaPathNameLst;
		std::vector<std::string> vFileLenLst;
		std::string strInfoHeader;

		//TR use 0, TD use 1
		std::string strTD = "\t"; 
		std::string strTR = "\n";


		strWorkPath = MkDir2Path( strWorkPathOrDir ) ;


		//get vDirNameLst

		ListAllFile( strWorkPath, "*.*", vDirFullNameLst, 1, 0, 1, 1 );

		for( it = vDirFullNameLst.begin(); it != vDirFullNameLst.end(); ++it )
		{
			const char *p;
			p = it->c_str() + strWorkPath.size();
			vDirNameLst.push_back(p);
		}

		//distinct vDirNameLst

		SSetu::vs_setgroup( vDirNameLst );


		//get file rela_path name
 
		ListAllFile( strWorkPath, "*.*", vFileFullPathNameLst, 0, 1, 1, 1 );

		for( it = vFileFullPathNameLst.begin(); it != vFileFullPathNameLst.end(); ++it )
		{
			const char *p;
			p = it->c_str() + strWorkPath.size();
			vFileRelaPathNameLst.push_back(p);
		}
	 

		//get file len

		tint32 iLenAmount=0;

		for( it = vFileFullPathNameLst.begin(); it != vFileFullPathNameLst.end(); ++it )
		{
			SFile sf;
			tint32 i;

			sf.bind( *it );
			i = sf.len();
			iLenAmount += i;
			vFileLenLst.push_back( SStrf::sltoa( i ) );
		}


		//create 3 info_list to a InfoHeader
		
		for( it = vDirNameLst.begin(); it != vDirNameLst.end(); ++it )
		{
			strInfoHeader += *it;
			strInfoHeader += strTD;  
		}
		strInfoHeader += strTR;

		for( it = vFileRelaPathNameLst.begin(); it != vFileRelaPathNameLst.end(); ++it )
		{
			strInfoHeader += *it;
			strInfoHeader += strTD;  
		}
		strInfoHeader += strTR;

		for( it = vFileLenLst.begin(); it != vFileLenLst.end(); ++it )
		{
			strInfoHeader += *it;
			strInfoHeader += strTD;  
		}
		strInfoHeader += strTR;



		//get file bin

		ckOut.redim( iLenAmount + (tsize)strInfoHeader.size() + 1 );

		tchar *p1;

		p1 = ckOut.buf();

		//put info header
		SStrf::smemcpy( p1, strInfoHeader.c_str(), (tsize)strInfoHeader.size() );
		p1 += (tsize)strInfoHeader.size();

		*p1 = 0;
		p1 ++;

		std::vector<std::string>::iterator it2;

		it2 = vFileLenLst.begin();
		for( it = vFileFullPathNameLst.begin(); it != vFileFullPathNameLst.end(); ++it, ++it2 )
		{
			SCake ck;
			SFile sf;

			sf.bind( *it );
			sf.read( ck );

			if( ck.len() )
			{
				SStrf::smemcpy( p1, ck.buf(), (tint32)ck.len() <  SStrf::satol( *it2 ) ? (tint32)ck.len() :  SStrf::satol( *it2 ) );				
			}

			//p1 += ck.len();
			p1 += SStrf::satol( *it2 );
		}

	}


 
 
	static void UnPackFolder( std::string strWorkPathOrDir, const SCake & ckIn , std::vector<std::string> *pvDirFullNameLst = NULL, std::vector<std::string> *pvFileFullPathNameLst = NULL )
	{
		if( ckIn.len() == 0 ) return;
		
		//std::for_each( ckIn.buf(), ckIn.buf() + ckIn.len(), xor2() );

		//std::vector<tchar> v1;
		std::string strWorkPath;
		std::vector<std::string>::iterator it;
		std::vector<std::string> vDirFullNameLst;
		std::vector<std::string> vDirNameLst;
		std::vector<std::string> vFileFullPathNameLst;
		std::vector<std::string> vFileRelaPathNameLst;
		std::vector<std::string> vFileLenLst;
		std::string strInfoHeader;

		
		//TR use 0, TD use 1
		std::string strTD = "\t";
		std::string strTR = "\n";

		strWorkPath = MkDir2Path( strWorkPathOrDir ) ;

		strInfoHeader = (const char*)ckIn.buf_const();


		//create all DIRs

		SStrvs::vsa_imp( SStrvs::vsa_get( strInfoHeader, strTR, 0, 0 ), strTD, 1, vDirNameLst );

		std::sort( vDirNameLst.begin(), vDirNameLst.end() ); //此时可以保证短的目录名在前,CreateDirectory可以逐级正常工作了.

		for( it = vDirNameLst.begin(); it != vDirNameLst.end(); ++it )
		{
			std::string s1;
			s1 = MkDir2Path( strWorkPathOrDir ) + *it ;
			vDirFullNameLst.push_back( s1 );

			CString cs1;
			cs1 = s1.c_str();
			::CreateDirectory( cs1, NULL );
			//::SHCreateDirectoryEx(NULL, cs1, NULL);
		}


		//get all full filenames

		SStrvs::vsa_imp( SStrvs::vsa_get( strInfoHeader, strTR, 0, 1 ), strTD, 1, vFileRelaPathNameLst );

		for( it = vFileRelaPathNameLst.begin(); it != vFileRelaPathNameLst.end(); ++it )
		{
			std::string s1;
			s1 = MkDir2Path( strWorkPathOrDir ) + *it ;
			vFileFullPathNameLst.push_back( s1 );
		}


		//get all file len

		SStrvs::vsa_imp( SStrvs::vsa_get( strInfoHeader, strTR, 0, 2 ), strTD, 1, vFileLenLst );


		//return lists
		if( pvDirFullNameLst != NULL ) *pvDirFullNameLst = vDirFullNameLst;
		if( pvFileFullPathNameLst != NULL ) *pvFileFullPathNameLst = vFileFullPathNameLst;


		//create all files

		const tchar *p1;

		p1 = ckIn.buf_const() + strInfoHeader.size() + 1;

		//v1.insert( v1.end(), ckIn.buf_const() + strInfoHeader.size() + 1 , ckIn.buf_const() + ckIn.len() );
		//ckIn.redim(0); //ckIn is useless now, free the memory.

		for( ; !vFileFullPathNameLst.empty(); )
		{
			std::string s1;
			tint32 i1;

			s1 = vFileFullPathNameLst.front();
			i1 = SStrf::satol( vFileLenLst.front() );

			if( p1 > ckIn.buf_const() + ckIn.len() ) break;

			SFile sf;

			sf.bind( s1 );

			sf.write( p1, (tsize)i1 );

			vFileFullPathNameLst.erase( vFileFullPathNameLst.begin() );
			vFileLenLst.erase( vFileLenLst.begin() );

			p1 += i1;
		}
		
	}


	////////////convert code


	static std::wstring Utf8toWch( const std::string & s )
	{
		int  unicodeLen = MultiByteToWideChar( CP_UTF8, 0, s.c_str(), -1, NULL, 0 );
		wchar_t *  pUnicode;  
		pUnicode = new  wchar_t[unicodeLen+1];  
		MultiByteToWideChar( CP_UTF8, 0, s.c_str(), -1, pUnicode, unicodeLen );

		std::wstring ws;
		ws = pUnicode;
		delete [] pUnicode; 
		return ws;
	}


	static std::string & ChtoUtf8( std::string & s )
	{
		std::string ss2( 3 * s.length() + 3 , 'a' );
		WideCharToMultiByte(CP_UTF8, 0, CStringW(s.c_str()), -1, &(ss2[0]), (int)ss2.length(), NULL,FALSE);
		return s = ss2.c_str();
	}


	static std::string & Utf8toCh( std::string & s )
	{
		std::wstring ws = Utf8toWch( s );
		 DWORD dwNum = WideCharToMultiByte(CP_OEMCP,NULL,ws.c_str(),-1,NULL,0,NULL,FALSE);
		 char *psText = new char[dwNum];
		 WideCharToMultiByte (CP_OEMCP,NULL, ws.c_str(),-1,psText,dwNum,NULL,FALSE);
		 s = psText;
		 delete []psText;
		 return s;
	}



	//windows local functions:

	static tbool SetFileToCurrentTime( std::string strFullPathName )
	{
		SYSTEMTIME st;
		SDte t;
		GetSystemTime(&st);    // gets current time

		t.m_year  =  st.wYear    ;
		t.m_mon   =  st.wMonth  ;
		t.m_day =  st.wDay   ;
		t.m_hour = st.wHour  ;
		t.m_min  = st.wMinute  ;
		t.m_sec  = st.wSecond  ;

		return SetFileToTheTime( strFullPathName, t );
	}


	static tbool SetFileToTheTime( std::string strFullPathName, SDte __tm ) 
	{
		HANDLE hFile;

		hFile = CreateFileA( strFullPathName.c_str(), 
							  FILE_ALL_ACCESS, FILE_SHARE_WRITE|FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, 0 ); 

		if( hFile == INVALID_HANDLE_VALUE ) 
		{
			return 0;
		}

		//FILETIME SYSTEMTIME 

		FILETIME ft;
		BOOL f;

		SYSTEMTIME st;

		SStrf::smemset( &st );

		st.wYear =   __tm.m_year;
		st.wMonth  =  __tm.m_mon;
		st.wDay    =  __tm.m_day;
		st.wHour   =  __tm.m_hour;
		st.wMinute =  __tm.m_min;
		st.wSecond =  __tm.m_sec;

		SystemTimeToFileTime( &st, &ft );  // converts to file time format

		//f = SetFileTime(hFile, (LPFILETIME) NULL, (LPFILETIME) NULL, &ft);          // sets last-write time for file
		f = SetFileTime(hFile, &ft, &ft, &ft);     

		CloseHandle(hFile);

		return f;
	}


};//end class WFile






X011_NAMESPACE_END


#endif







/*
WNava , nava with utf8 <--> ch converter
*/

#ifndef X011__H_W_WNAVA_H
#define X011__H_W_WNAVA_H



X011_NAMESPACE_BEGIN



class WNava : public SNavass 
{
private:


public:

	virtual ~WNava() {;} 


	//static tbool IsUtf8Base()	// 本文件必须在结合成1.h以后以utf8形式保存,才能使win与linu下自动产生正确结果.平时不用.或结合项目仿照此另做函数完成相同任务.
	//{
	//	const char * p = "初";
	//	return p[2] ? 1 : 0 ;
	//}


	
	void impconf( const std::string & ssource, std::string ssepTR = "\n", std::string ssepTD = "=", std::string strMemoLineHead = "#" )
	{
		//以下算法，数据中允许有TD

		std::vector<std::string>  vecLines;
		SStrvs::vsa_imp( ssource, ssepTR, 1, vecLines );
		for( std::vector<std::string>::iterator it = vecLines.begin(); it != vecLines.end(); ++it )
		{
			std::string::size_type i;

			i = it->find(ssepTD);
			if( i == std::string::npos ) continue;

			SStrf::strim( *it );
			if( it->find(strMemoLineHead) == 0 ) continue;

			(*it)[i] = 0;
			this->let( it->c_str(), it->c_str() + i + ssepTD.size() );
		}

		this->trimall();
	}


	typedef std::string & (* P_t) ( std::string & );


	void AtoB( P_t pf )
	{
		std::map< std::string, std::string > mapTmp = m_mapKnl;

		this->clear();

		for( MAP_MAPKNL_IT it = mapTmp.begin(); it != mapTmp.end(); ++it )
		{
			std::string s1 = it->first;
			std::string s2 = it->second;

			(*pf)( s1 );
			(*pf)( s2 );

			let( s1, s2 ); 
		}
	}


	void ChtoUtf8()
	{
		AtoB( WFile::ChtoUtf8 );
	}

	void Utf8toCh()
	{
		AtoB( WFile::Utf8toCh );
	}


};




X011_NAMESPACE_END

#endif




/*
W series
thread class
for win ce
*/

// 


#ifndef X011__H_w_wthrd_h
#define X011__H_w_wthrd_h



//if X011__WL_WIN_THRD_H_WIN_VER_SHOULD_BE_USED defined, use win ver multi thread , which might cause mem leak.
//X011__WL_WIN_THRD_H_WIN_VER_SHOULD_BE_USED will be defined when _MT not defined, which means the prj is not under multi thread compile env.
#ifndef _MT
#ifndef X011__WL_WIN_THRD_H_WIN_VER_SHOULD_BE_USED
#define X011__WL_WIN_THRD_H_WIN_VER_SHOULD_BE_USED
#endif
#endif


#define X011__WL_WIN_THRD_H_WIN_VER_SHOULD_BE_USED



#ifdef  X011__WL_WIN_THRD_H_WIN_VER_SHOULD_BE_USED
//
#else
//#include <process.h>
#endif


 //uintptr_t __cdecl _beginthreadex(__in_opt void * _Security, __in unsigned _StackSize,
 //       __in unsigned (__stdcall * _StartAddress) (void *), __in_opt void * _ArgList, 
 //       __in unsigned _InitFlag, __in_opt unsigned * _ThrdAddr);


X011_NAMESPACE_BEGIN


/*
usage
should be
template< T >
class A : public  T 
{
}
*/

class WThrd
{

private:

	volatile HANDLE	 m_hThread;	//handle to thread knl 
	volatile int m_iAutoDel;
	volatile int m_iShouldBreak;
	volatile int m_iLive;

	volatile int m_iOpened;


#ifdef  X011__WL_WIN_THRD_H_WIN_VER_SHOULD_BE_USED
static DWORD WINAPI ThreadProc(LPVOID lpParam)
#else
static unsigned int WINAPI ThreadProc(void * lpParam)
#endif
	{
		WThrd *pThis=reinterpret_cast<WThrd*>(lpParam);

		try
		{
			//pThis->m_iLive = 1;

			pThis->tr_on_knl_run();

			//pThis->m_hThread=INVALID_HANDLE_VALUE;

			pThis->tr_shouldbrk();

			pThis->m_iLive = 0;

			if(pThis->m_iAutoDel)
			{
				try
				{
					delete pThis;
				}
				catch (...)
				{
					return (DWORD)0;
				}
			}
			return (DWORD)0;
		}
		catch(...)
		{
			try
			{
				delete pThis;
			}
			catch (...)
			{
				return (DWORD)0;
			}
			return (DWORD)0;
		}
		return (DWORD)0;
	}


private:

	WThrd & operator = (const WThrd & rhs)
	{
		return *this;
	}


	WThrd(const WThrd & rhs)
	{;}


public:

	WThrd()
	{
		m_hThread = INVALID_HANDLE_VALUE; 
		m_iAutoDel = 0;
		m_iShouldBreak = 0;
		m_iLive = 0;
		m_iOpened = 0;
	}


	virtual ~WThrd()
	{
		if( !m_iOpened ) return;

		try
		{
			tr_shouldbrk();

			//if( tr_wait( 4567 ) ) //如果是Heap型自删除的，则析构总是在本线程中执行，wait等于自己等自己，肯定要永远wait.如果是栈型变量，则析构是在主线程中执行的，与本类的run肯定不在同一线程中，所以看上去能行。
			//{
			//	//tr_Terminate();
			//	Beep(234,9);
			//	Beep(1294,9);
			//	Beep(234,9);
			//	return;
			//}

			if( !m_iAutoDel )
				tr_wait();

			tr_closehandl();
		}
		catch(...)
		{; }
	}


public:

	static std::string tr_GetCurrentThreadId()
	{
		char sz1[22];
		SClib::p_sprintf()( sz1, "%p", GetCurrentThreadId() );
		return sz1;
	}


	HANDLE tr_GetHnd() const
	{
		return m_hThread;
	}


	static void tr_sleep( int iSec , double dSec = 0.0 )	// 参数为整数秒和小于一秒的小数秒。 
	{
		if( iSec > 0 )
			Sleep( iSec * 1000 );

		if( dSec > 0.0 )
		{
			Sleep( static_cast<int>(dSec * 1000 * 1) );
		}
	}


	void tr_open()
	{
		m_hThread = INVALID_HANDLE_VALUE;

		m_iLive = 1;

#ifdef  X011__WL_WIN_THRD_H_WIN_VER_SHOULD_BE_USED
		//create a new thread and run it. WIN ver.
		DWORD i;
		m_hThread = ::CreateThread (
			NULL,			//缺省的安全性
			0,				//缺省的堆栈
			ThreadProc,		//类范围的线程进程
			reinterpret_cast<LPVOID>(this),	//向过程发送this指针
			0,				//没有特殊的创建标志 如果在dwCreationFlags中用了CREATE_SUSPENDED特性，那么线程并不马上执行，而是先挂起，等到调用ResumeThread后才开始启动线程，在这个过程中可以调用函数：　　BOOLSetThreadPriority(HANDLEhThread,intnPriority);　　来设置线程的优先权。　　当线程的函数返回后，线程自动中止。
			&i	);			// 返回线程ID
#else
		//C ver
		unsigned int i;
		m_hThread = (HANDLE) ::_beginthreadex(
			NULL,			//缺省的安全性
			0,				//缺省的堆栈
			ThreadProc,		//类范围的线程进程
			reinterpret_cast<LPVOID>(this),	//向过程发送this指针
			0,				//
			&i	);			// 返回线程ID

#endif

		if( !m_hThread )
		{
			m_iLive = 0;
		}

		if( tr_isRunning() )
		{
			m_iOpened = 1;
		}
	}



	void tr_openx() //if openx, don't wait this thread. because it will be deleted any time. don't call any func out side the obj in other thrd.
	{
		m_iAutoDel = 1;
		tr_open();
	}




	void tr_shouldbrk()
	{
		m_iShouldBreak = 1;
	}


	int tr_isShouldBrk() const
	{
		return m_iShouldBreak;
	}



	int tr_isRunning()
	{
		 return m_iLive;//由于无法自动地从不运行转化到运行状态，所以此函数主要用于探测是否已经从运行变为了不运行状态。
	}


	void tr_Terminate()
	{
		if( !m_iOpened ) return;

		try
		{
			if( m_hThread != INVALID_HANDLE_VALUE )
			{
				TerminateThread( m_hThread, 0 );
			}
		}
		catch (...)
		{	;
		}
	}

	void tr_closehandl()
	{
		tr_shouldbrk();

		if( m_hThread != INVALID_HANDLE_VALUE )
		{
			try
			{

#ifdef  X011__WL_WIN_THRD_H_WIN_VER_SHOULD_BE_USED
				::CloseHandle(m_hThread); 
#else
				//_endthread or _endthreadex is called automatically when the thread returns from the routine passed as a parameter to _beginthread or _beginthreadex.

				::CloseHandle(m_hThread);
#endif
			}
			catch (...)
			{
				;
			}
		}

		try
		{
			m_hThread = INVALID_HANDLE_VALUE; 
		}
		catch (...)
		{
			;
		}
	}



	//wait to thread end. 
	//if timeout then 1, means thread living.
	//if invalid thread then 0,
	//if wait to thread end then means thread dead. then 0.
	int tr_wait( DWORD dwMilliseconds=INFINITE )
	{
		if( !m_iOpened ) return 0;

		try
		{
			do//fake do
			{
				if( m_hThread == INVALID_HANDLE_VALUE )
					return 0;

				if( WAIT_TIMEOUT==::WaitForSingleObject(m_hThread,dwMilliseconds) )
					return 1;
				
				return 0;

			}while(0);

		}
		catch(...)
		{
			return 0;
		}
	}




	void tr_priority(int nPrio) 
	{
		/*
		THREAD_PRIORITY_ABOVE_NORMAL
		THREAD_PRIORITY_BELOW_NORMAL
		THREAD_PRIORITY_HIGHEST
		THREAD_PRIORITY_IDLE
		THREAD_PRIORITY_LOWEST
		THREAD_PRIORITY_NORMAL
		THREAD_PRIORITY_TIME_CRITICAL */
		::SetThreadPriority(m_hThread,nPrio);
	}




	void tr_priority_high() { 	tr_priority( THREAD_PRIORITY_ABOVE_NORMAL ); }


	void tr_priority_low()  { 	tr_priority( THREAD_PRIORITY_BELOW_NORMAL ); }


	void tr_priority_normal() { 	tr_priority( THREAD_PRIORITY_NORMAL ); }




	//
	void tr_suspend()
	{
		::SuspendThread(m_hThread);
	}



	//
	void tr_resume()
	{
		::ResumeThread(m_hThread);
	}




	virtual void tr_on_knl_run()
	{
		SStrf::initrand( (int)GetCurrentThreadId() );

		while(1)
		{
			if( !tr_on_user_run() ) break;

			if( m_iShouldBreak ) break;
		}
	}
 


	virtual int tr_on_user_run() //return 0 will cause knl_run break;
	{
		return 0;
	}


	virtual tbool tr_OnMgrPrepare() // for WThrdMgr 
	{
		return 1;
	}

}; //end class 




///=================================================city



class WThrdCity
{
public:

		class WThrd2 : public WThrd 
		{

		friend class WThrdCity;

		private:
			WThrdCity * m_pWThrdCity;

			int tr_on_user_run() // 
			{
				return OnRun() ;
			}

		public:

			WThrd2()
			{
				m_pWThrdCity = NULL;
			}

			virtual ~WThrd2()
			{
				if( m_pWThrdCity ) m_pWThrdCity->RemoveEle(*this);
			}

			virtual int OnRun() 
			{
				return 0;
			}

		};

		
	typedef  WThrd2  WThrdEle;

	friend WThrdEle;


private:

	std::vector< WThrdEle * >  m_vecThrdLst;
	
	WCrsc m_crscThrdLst;

	WCrsc m_crscThrdOpenFunc;


	int AddEle( WThrdEle & t )
	{
		WCrsc aLock( this->m_crscThrdLst );
		WThrdEle * p = SStrf::AddressOf( t );

		m_vecThrdLst.push_back( p );
		return GetThrdAmount();
	}

	int RemoveEle( WThrdEle & t )
	{
		WCrsc aLock( this->m_crscThrdLst );
		WThrdEle * p = SStrf::AddressOf( t );

		std::vector< WThrdEle * >::iterator it = std::find( m_vecThrdLst.begin(), m_vecThrdLst.end(), p );
		if( it != m_vecThrdLst.end() )
		{
			m_vecThrdLst.erase( it );
		}
		return GetThrdAmount();
	}


public:

	int m_iLimit;

	tbool m_bWithOpenFailRetry;

public:

	WThrdCity( int iLimit = 123 )
	{
		m_iLimit = iLimit;
		m_bWithOpenFailRetry = 0;
	}


	int GetThrdAmount() const 
	{
		return (int)m_vecThrdLst.size();
	}
	
	

	void CleanStoppedThrd()
	{
		WCrsc aLock ( m_crscThrdOpenFunc );
		WCrsc a2Lock( m_crscThrdLst );

		std::vector< WThrdEle * >::iterator it;

		for( it = m_vecThrdLst.begin();
			 it != m_vecThrdLst.end();
			 ++it	)
		{
			if( (*it)->tr_isRunning() )
			{
				//
			}
			else
			{
				(*it)->m_pWThrdCity = NULL; //delete会调用析构函数清理Lst，所以先要禁掉。
				delete *it;
				it = m_vecThrdLst.erase( it );
			}
		}
		
	}



	tbool OpenThrd( WThrdEle & t )
	{
		WCrsc aLock( m_crscThrdOpenFunc );

		if( GetThrdAmount() >= m_iLimit )
		{
			//m_bWithOpenFailRetry here
			return 0;
		}

		AddEle( t );

		t.m_pWThrdCity = this;
		t.tr_open();

		return 1;
	}


	tbool OpenThrdHp( WThrdEle * t1 ) //open for when it is in heap
	{
		WCrsc aLock( m_crscThrdOpenFunc );

		if( !t1 ) return 0;

		if( GetThrdAmount() >= m_iLimit )
		{
			//m_bWithOpenFailRetry here
			return 0;
		}


		//WThrdEle & t(*t1); //don't use this line, for compatible of VC6

		AddEle( *t1 ); //此处只能形成非精确的数量控制。例如只差一个就到m_iLimit时，可能有2个线程都打算开新线程，并且都判断出尚未到m_iLimit，这样，就可能新增2个ele，从而略超控制数。

		( *t1 ).m_pWThrdCity = this;
		( *t1 ).tr_openx();

		return 1;
	}



	template< class ThrdEle_T > 
	tbool OpenThrdHp()
	{
		//WCrsc aLock( m_crscThrdOpenFunc );

		WThrdEle * p = new ThrdEle_T ;

		return OpenThrdHp(p); //不好用。如果返回0，则会丢失一个指针，无人释放。
	}


	//tbool OpenThrdWithRetry();
	//tbool OpenFreeThrd();
	//tbool OpenFreeThrdWithRetry();


};



typedef  WThrdCity::WThrd2  WThrdEle;





X011_NAMESPACE_END

#endif





/*
 
thread mgr, use with ele and env
*/

// 


#ifndef X011__H_W_WTHRDMGR_H
#define X011__H_W_WTHRDMGR_H


 


X011_NAMESPACE_BEGIN

 

//====================================================WThrdMgr

/*
用法是:
每一个工作原子是继承thrd,并需要env pointer。ele里只有算法，没有建立连接的过程，不要等待。but maybe recv and wait.
继承WThrdMgr，并指出工作原子。有env成员
重写OnMgrPrepare，为每个ele赋予env的指针.
也许重写tr_OnMgrPrepare()
这2个重写是真正block住的地方。
外界同步调用BirthEle，或启动本线程使其异步工作。
*/

template < class ThreadEle_T > 
class WThrdMgr : public WThrd 
{
private:


public:
	typedef		ThreadEle_T	 	ThrEle_t;
	volatile tbool  m_biMgrShouldBreak;
	int  m_iFailWaitTimesec; // if birth fail, wait this.
	tbool  m_biIsMultiEleType;

public:
	WThrdMgr()
	{
		m_biMgrShouldBreak = 0;
		m_iFailWaitTimesec = 3;
		m_biIsMultiEleType = 1;
	}

	virtual ~WThrdMgr()
	{;	}

	
	virtual tbool OnMgrPrepare( ThrEle_t & t ) // use 引用是表明到此处时必有对象存在 而不可能是NULL pointer   
	{
		return 1;
	}


	virtual int tr_on_user_run() 
	{
		BirthEle();
		return 0;
	}


	virtual ThrEle_t * MgrPrepare()   // new an ele, set its para, return the pointer. if fail, delete the pointer, return NULL. i'll not open or openx here.
	{
		ThrEle_t * p = new ThrEle_t;

		if( !p ) return NULL;

		if( !OnMgrPrepare(*p) ) /// 先准备环境 
		{
			delete p;
			return NULL;
		}

		if( ! p->tr_OnMgrPrepare() ) // 再准备个体  
		{
			delete p;
			return NULL;
		}
		
		return p;
	}


	//entrance:

	void BirthEle()
	{
		for( ; ; )
		{
			if( m_biMgrShouldBreak ) break;
			
			if( tr_isShouldBrk() ) break;
			
			ThrEle_t * p = MgrPrepare();
			if( p != NULL )
			{
				if( m_biIsMultiEleType )
				{
					p->tr_openx();
				}
				else  
				{
					p->tr_open();
					p->tr_wait();
					delete p;
				}
			}
			else
			{
				WThrd::tr_sleep( m_iFailWaitTimesec > 0 ? m_iFailWaitTimesec : 2 );
			}
		}
	}

};


 



X011_NAMESPACE_END

#endif



//应用案例: 
//
//class AEle : public wl::WThrd 
//{
//public:
//	wl::WTcpListener * m_pLsn;
//	wl::WTcpCells  m_tSvr;
//	
//
//	virtual int tr_on_user_run() 
//	{
//		wl::WTcpCells &tSvr(m_tSvr);
//
//		for(;;)
//		{
//			wl::SCake ck;
//			char s[222];
//			
//			tSvr.recv_len( ck, 1 );
//			if( ck.len() == 0 ) break;
//
//			printf(     "`%c` %d\r\n", *ck.buf(), *ck.buf() );
//			sprintf( s, "`%c` %d\r\n", *ck.buf(), *ck.buf() );
//			tSvr.send_str( s );
//
//			if( *ck.buf() == 27 ) break;
//		}
//
//		return 0;
//	}
//};
//
//
//class AMgr : public wl::WThrdMgr< AEle>
//{
//public:
//	wl::WTcpListener  m_Lsn;
//
//	AMgr()
//	{
//		m_Lsn.Listen( 7878 );
//		m_biIsMultiEleType = 0;
//	}
//
//	virtual ~AMgr() { ; }
//
//	virtual wl::tbool OnMgrPrepare( ThrEle_t & t ) // 
//	{
//		t.m_pLsn = &m_Lsn;
//		
//		if( !t.m_tSvr.Conn( m_Lsn ) ) return 0;
//		//t.m_tSvr.killer_up(6);
//
//		return 1;
//	}
//
//};
//
//
//
//
//void test_tcpserver()
//{
//	AMgr a;
//
//	a.BirthEle();
//}
//


/*
net
W series
tcp env header and lib
*/

// 

#ifndef X011__H_w_wtcp_a01env_netheaderlib_h
#define X011__H_w_wtcp_a01env_netheaderlib_h


#pragma comment( lib, "ws2.lib" )

#include <winsock.h>

//#pragma comment( lib, "Netapi32.lib" )
//#include <Nb30.h>


 

#endif



/*
net
W series
tcp net env , init env
*/

// 

#ifndef X011__H_w_wtcp_a01env_net_env_init_h
#define X011__H_w_wtcp_a01env_net_env_init_h
 

 

X011_NAMESPACE_BEGIN




//////////////////////环境准备：Net打开和关闭

class WNet_lib_env_init 
{
private:

	int iOpenedByMe;

	static int Net_lib_open(void)
	{
		int ZEROIFSUCCESSFUL = 0;
		WSADATA		Wa;
		return ZEROIFSUCCESSFUL == WSAStartup( 0x0202, &Wa );
	}

	static int Net_lib_close(void)
	{
		return WSACleanup(); 
	}

public:

	WNet_lib_env_init()
	{
		SOCKET socTestSock;

		iOpenedByMe = 0;
		socTestSock = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
		if( socTestSock == INVALID_SOCKET )
		{
			if( Net_lib_open() ) iOpenedByMe = 1;
		}
		else
		{
			closesocket(socTestSock);
		}
	 }

	~WNet_lib_env_init()
	{
		if(iOpenedByMe)
		{
			Net_lib_close();
		}
	}
};


//prepare net lib env, use global obj.
static volatile  WNet_lib_env_init  wl_win_net_lib_env___23dmg3n67_obj;



X011_NAMESPACE_END

#endif



/*
W series
tcp cell base: WTcpDisConnable
*/

// 

#ifndef X011__H_w_WTcpDisConnable_h
#define X011__H_w_WTcpDisConnable_h


X011_NAMESPACE_BEGIN


class WTcpDisConnable : public IRice
{

private:

	WTcpDisConnable & operator = (const WTcpDisConnable & rhs)
	{
		return *this;
	}

	WTcpDisConnable(const WTcpDisConnable & rhs)
	{;}


public:
	class MyTimeKiller : public WThrd 
	{
	public:
		WTcpDisConnable * m_ph;
		int  m_i;
		int  m_iMaxSec;
		double  m_d;
		double  m_dMaxSec2;

		MyTimeKiller( WTcpDisConnable * ph, int iMaxSec, double dMaxSec2 = 0.0 )
		{
			m_ph = ph;
			m_i = 0;
			m_iMaxSec = iMaxSec;
			m_d = 0.0;
			m_dMaxSec2 = dMaxSec2;
		}

		virtual ~MyTimeKiller()
		{
			m_i = 0;
			tr_shouldbrk();

			//openx时,就是m_iAutoDel,此时不能析构时等自己.//tr_wait();
			//本例中是用open()打开线程，在基类中已经做好，会析构等自己。
			//一切取决于析构是不是本线程。如果是本线程同时负责析构，这时就会自己等自己而死锁.
		}


		virtual int tr_on_user_run()
		{
			if( m_i <= m_iMaxSec )
			{
				m_i++;
				if( m_i > m_iMaxSec )
				{
					//if(m_ph) m_ph->DisConn();
					//return 0;
				}
				else
				{
					WThrd::tr_sleep(1);
					return 1;
				}
			}

			if( m_d < m_dMaxSec2 ) // return as many as possible. we want many chances to Not to disconn and to end this thrd.
			{
				m_d += m_dMaxSec2;
				WThrd::tr_sleep( 0 , m_dMaxSec2 );
				return 1;
			}

			if( this->tr_isShouldBrk() ) return 0;

			if(m_ph) m_ph->DisConn();
			return 0;
		}
	};


	MyTimeKiller * m_pkiller;


	void killer_up( int iMaxSec ) //超时就会形成类似对方断线的效果。构造时即启动线程 
	{
		killer_dn() ;
		m_pkiller = new MyTimeKiller( this, iMaxSec );
		m_pkiller->tr_open();
	}


	void killer_dn() 
	{
		if( m_pkiller != NULL )
		{
			delete m_pkiller;
			m_pkiller = NULL;
		}
	}

public:

	WTcpDisConnable()
	{
		m_pkiller = NULL;
	}

	virtual ~WTcpDisConnable()
	{
		killer_dn() ;         
	}


 
	virtual void DisConn()  // CDUP\net\w_WMoonMan.h中重写本方法，但又调用了本方法，以便利用本方法中所定义的行为，而且虚函数OnDisConn()的调用又让控制权回到了 w_WMoonMan.h
	{
		/* IRice:: */ ClearL2Cache();

		OnDisConn();
	}


public:

	virtual void OnDisConn() { ; } // 让它有函数体而不是=0，为了防止在子类都析构了但本类还未析构时突然发生timekill，调用空函数之错。


}; //end class 




X011_NAMESPACE_END

#endif





/*
W series
tcp cell 
*/

// 

#ifndef X011__H_w_wtcp_cell_h
#define X011__H_w_wtcp_cell_h


X011_NAMESPACE_BEGIN


class WTcpCell : public WTcpDisConnable 
{
		
protected:

	SOCKET			m_socRemote;


private:

	WTcpCell & operator = (const WTcpCell & rhs)
	{
		return *this;
	}

	WTcpCell(const WTcpCell & rhs)
	{;}


public:

	WTcpCell()
	{
		m_socRemote = INVALID_SOCKET;
		 
	}

	virtual ~WTcpCell()
	{
		DisConn();
	}


public:

	SOCKET GetRemoteSoc () const
	{
		return m_socRemote;
	} 
	

	static std::string getselfname()
	{
		tchar ss[1024] = {0};
		gethostname(ss,1024);  //机器的主机名
		return ss;
	}


	static std::string getipbyname( std::string name )
	{
		hostent * host;
		std::vector<std::string> vecNameParts;

		wl::SStrvs::vsa_imp( name, std::string("."), 1, vecNameParts );
		if( vecNameParts.size()==4 &&
			SStrf::sisdec(vecNameParts[0].c_str()) &&
			SStrf::sisdec(vecNameParts[1].c_str()) &&
			SStrf::sisdec(vecNameParts[2].c_str()) &&
			SStrf::sisdec(vecNameParts[3].c_str())		)
			return name;

		if( name.size() == 0 )
			name = getselfname();

		host = gethostbyname(name.c_str());

		if(host==NULL)
			return "";

		if( host->h_addr_list[0] )
		{
			struct in_addr addr;
			memmove( &addr, host->h_addr_list[0], 4 );
			return inet_ntoa(addr);
		}

		return "";
	}


	static std::string getnamebyip( std::string strIP )
	{
		DWORD dwIPAddr;
		dwIPAddr = inet_addr(strIP.c_str());//strIP是IP地址,字符串，如192.168.0.1。
		if(dwIPAddr == INADDR_NONE)
		{
			return "";//IP地址不合法
		}
		else
		{
			hostent * p=gethostbyaddr( (const char *)&dwIPAddr, 4, PF_INET ); //这里要强制转换，很多初学者常常卡在这里了。
			if(!p)
			{
				return "";//找不到相应的名字。
			}
			else
			{
				return p->h_name;//找到名字了，字符串。
			}
		}
	}



public:

	virtual void OnDisConn()
	{
		if( m_socRemote == INVALID_SOCKET ) return;

		try
		{	
			shutdown( m_socRemote, 2 ); 
			closesocket(m_socRemote); 
			m_socRemote = INVALID_SOCKET ;
		}
		catch(...) 
		{
			m_socRemote = INVALID_SOCKET;
		}
	}


public:

	virtual int on_get_defaultrecv_buf_len() //return the   len
	{
		return 255;
	}

	virtual int on_sys_recv( SCake & ckDataBuf ) //return the recv len
	{
		int iDefaultBufLen = on_get_defaultrecv_buf_len();
		ckDataBuf.redim( iDefaultBufLen );

		int i;
		SOCKET s = m_socRemote;

		if(s==INVALID_SOCKET)
		{
			return 0;
		}

		i = (int)::recv(s, ckDataBuf.buf(), (int)ckDataBuf.len(), 0);
		if(i==SOCKET_ERROR||i==0)
		{
			return i = 0;
		}

		ckDataBuf.cut( iDefaultBufLen-i );

		return i;
	}


	virtual int on_sys_send( const SCake & ckDataBuf ) //return the successfully sent len
	{
		int i;
		SOCKET s = m_socRemote;
		if(s==INVALID_SOCKET) return 0; //      if(len>66) len=66;

		i = (int)::send(s, ckDataBuf, (int)ckDataBuf.len(), 0);
		//i = (int)::send( s, ckDataBuf, (int)ckDataBuf.len() > 66 ? 66 : (int)ckDataBuf.len(), 0 );

		if(i==SOCKET_ERROR)
			i = 0;
		return i;
	}


}; //end class 




X011_NAMESPACE_END

#endif





/*
W series
tcp cellc
*/

// 

#ifndef X011__H_w_wtcp_cellc_h
#define X011__H_w_wtcp_cellc_h


X011_NAMESPACE_BEGIN


class WTcpCellc : public WTcpCell
{

private:

	WTcpCellc & operator = (const WTcpCellc & rhs)
	{
		return *this;
	}

	WTcpCellc(const WTcpCellc & rhs)
	{;}


public:


	WTcpCellc()
	{
	}



	virtual ~WTcpCellc()
	{
	}




	tbool Conn( std::string name, u_short port )
	{
		struct	sockaddr_in		saddr ;

		DisConn();

		m_socRemote = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );

		if( m_socRemote == INVALID_SOCKET )
		{
			return 0;
		}

		//we should zero mem here.
		SStrf::smemset( (void*)&saddr, 0, sizeof(saddr) );
	 
		saddr.sin_family = AF_INET; 
			//saddr.sin_addr.S_un.S_addr = inet_addr( getipbyname(name).c_str() );
			saddr.sin_addr.s_addr = inet_addr( getipbyname(name).c_str() );
		saddr.sin_port = htons( (u_short)port );

		if(SOCKET_ERROR == ::connect( m_socRemote, (struct sockaddr *)&saddr, sizeof(saddr) )  )
		{
			return 0;
		}

		return 1;
	}




	tbool Conn( std::string name, std::string port )
	{
		return this->Conn( name, static_cast<u_short>(SStrf::satol(port.c_str()) ) );
	}




	tbool Conn( std::string nameOraddr ) //like  192.168.1.29:2345  or  name.com:456
	{
		try
		{
			std::vector<std::string> vecNameParts;
			SStrvs::vsa_imp( nameOraddr, std::string(":"), 1, vecNameParts );
			vecNameParts.push_back( std::string("") );
			vecNameParts.push_back( std::string("") );
			return this->Conn( vecNameParts[0], vecNameParts[1] );
		}
		catch(...)
		{
			//printf("bad when %s\n", nameOraddr.c_str() );
			return 0;
		}
	}


}; //end class 




X011_NAMESPACE_END

#endif


/*
W series
tcp cell Listener
*/

// 

#ifndef X011__H_w_WTcpListener_h
#define X011__H_w_WTcpListener_h


X011_NAMESPACE_BEGIN


class WTcpListener
{

private:

	SOCKET	m_socLocalListener;
	//std::string m_strRemoteIPAddress;


private:

	WTcpListener & operator = (const WTcpListener & rhs)
	{
		return *this;
	}

	WTcpListener(const WTcpListener & rhs)
	{;}


public:

	u_short		m_port;

	u_long		m_u_in_addr;


	WTcpListener( )
	{
		m_socLocalListener = INVALID_SOCKET;
		//m_strRemoteIPAddress="";
		m_port = 0;
	}

	virtual ~WTcpListener( )
	{
		this->StopListen();
	}


	//operator const std::string & ( ) const
	//{
	//	return m_strRemoteIPAddress;
	//}
    


	tbool Listen( u_short port,  u_long a_in_addrip = INADDR_ANY, int listener_num = 4 )
	{
		struct	sockaddr_in	 saddr;

		m_port = port;
		m_u_in_addr = a_in_addrip;

		if ( 0 == port )
		{
			//return 0;		port=0 means any available port, so, it is right.
		}
		
		m_socLocalListener = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );

		if( m_socLocalListener == INVALID_SOCKET )
		{
			return 0;
		}

		//we should zero mem here.
		SStrf::smemset( (void*)&saddr, 0, sizeof(saddr) );

		saddr.sin_family = AF_INET; 
		saddr.sin_port = htons( (u_short)port );
		saddr.sin_addr.s_addr = a_in_addrip;	//INADDR_LOOPBACK;//inet_addr(cf_getipbyname("",ss)); // ;//INADDR_ANY; //saddr.sin_addr.s_addr = inet_addr( "127.0.0.1" ); // ;//INADDR_ANY; 
		
		if( SOCKET_ERROR == bind( m_socLocalListener, (struct sockaddr *)&saddr, sizeof(saddr) ))
		{
			this->StopListen();
			return 0;
		}

		return 0 == ::listen( m_socLocalListener, listener_num )?1:0;
	}


	tbool Listen( u_short uport, const tchar * sz_addrip ) //bind an appointed ip
	{
		if( sz_addrip && *sz_addrip )
		{
			return this->Listen( uport, inet_addr( sz_addrip ) ) ;
		}
		
		return this->Listen( uport );
	}


	tbool Listen( std::string strport, const tchar * sz_addrip )
	{
		return this->Listen( (u_short)SStrf::satol(strport) , sz_addrip );
	}



	tbool Listen( std::string straddr ) //like  192.168.1.29:2345  or  name.com:456
	{
		try
		{
			std::vector<std::string> vecNameParts;
			SStrvs::vsa_imp( straddr, std::string(":"), 1, vecNameParts );
			if( vecNameParts.size() == 1 )
			{
				vecNameParts.insert( vecNameParts.begin(), std::string("") );
			}

			vecNameParts.push_back( std::string("") );
			vecNameParts.push_back( std::string("") );
			return Listen( vecNameParts[1], vecNameParts[0].c_str() );
		}
		catch(...)
		{
			return 0;
		}
	}



	void StopListen(void)
	{
		if( m_socLocalListener != INVALID_SOCKET )
		{
			closesocket( m_socLocalListener );
			m_socLocalListener = INVALID_SOCKET;
		}
	}


	tbool AcceptNewSvr( SOCKET & socNewSvr, std::string & strRtnRemoteIP )
	{
		struct	sockaddr_in	 from;
		int nSize;

		if( m_socLocalListener == INVALID_SOCKET )
		{
			return 0;
		}

		nSize= sizeof(from);
		socNewSvr = ::accept( m_socLocalListener, (struct sockaddr *)&from, &nSize ); //socNewSvr now have a new value
		if( socNewSvr == INVALID_SOCKET )
		{
			strRtnRemoteIP = "";
			return 0;
		}
		else
		{
			strRtnRemoteIP = inet_ntoa( from.sin_addr ) ; //此时对方的port也是有意义的,不一定与本机的bind的port相同
			return 1;
		}
	}


}; //end class 




X011_NAMESPACE_END

#endif




/*
W series
tcp cells
*/

// 

#ifndef X011__H_w_wtcp_cells_h
#define X011__H_w_wtcp_cells_h


X011_NAMESPACE_BEGIN


class WTcpCells : public WTcpCell
{
	
public:

	std::string m_strRemoteIPAddress;


private:

	WTcpCells & operator = (const WTcpCells & rhs)
	{
		return *this;
	}

	WTcpCells(const WTcpCells & rhs)
	{;}


public:

	WTcpCells()
	{
		m_strRemoteIPAddress="";
	}


	virtual ~WTcpCells()
	{	m_strRemoteIPAddress="";
	}



	operator const std::string & () const
	{
		return m_strRemoteIPAddress;
	}



	std::string GetRemoteIPAddress() const
	{
		return m_strRemoteIPAddress;
	}



	tbool Conn( WTcpListener & aListener)
	{
		int iRc;

		iRc = aListener.AcceptNewSvr( m_socRemote , m_strRemoteIPAddress );

		if(!iRc) return 0;

		//m_strRemoteIPAddress = aListener; //本行会有多线程问题，改为用以上AcceptNewSvr带回IP.
		return 1;
	}


	tbool Conn( WTcpListener * pListener)
	{
		if(!pListener)
			return 0;

		return this->Conn(*pListener);
	}


}; //end class 




X011_NAMESPACE_END


#endif






/*
W series
com eli protocol 
*/

// 

#ifndef X011__H_w_WComeliProtocol_h
#define X011__H_w_WComeliProtocol_h


X011_NAMESPACE_BEGIN


class WComeliProtocol : public WTcpDisConnable 
{
		
public:

	tbool  m_biComportOpened;
	tbool  m_biShouldDisConn;


private:

	WComeliProtocol & operator = (const WComeliProtocol & rhs) 	{ 	return *this; }
	WComeliProtocol(const WComeliProtocol & rhs) {;}


public:

	WComeliProtocol()
	{
		m_biComportOpened = 0;
		m_biShouldDisConn = 0;
		 
	}

	virtual ~WComeliProtocol()
	{
		m_biComportOpened = 0;
		m_biShouldDisConn = 0;
	}


public:
 
	/////////////////////////////for com use, cake util

	typedef tuint8 (* PfChkSum_t) ( tuint8 a, tuint8 b );

	static tuint8 comesc_xor ( tuint8 a, tuint8 b ) { return a ^ b; };
	static tuint8 comesc_add ( tuint8 a, tuint8 b ) { return a + b; };


	static SCake & comesc_en( SCake & ckDataInOut, tuint8 a1, tuint8 a2, tuint8 a3 , PfChkSum_t pf = comesc_add, SCake * pdata2 = NULL ) // 
	{
		//ckDataInOut len ==0 也没关系

		tuint8  ucChkSum(0);
		std::vector<tuint8> v1;
		tuint8 c;

		//add a1
		v1.push_back(a1);

		//add data2
		for( tsize i2 = 0; pdata2 && i2 < pdata2->len(); i2++ )
		{
			c = *(tuint8*)(pdata2->buf()+i2);
			if( c == a1 || c == a2 || c == a3 ) v1.push_back(a2);
			v1.push_back( c );
		}

		//add len
		c = static_cast<tuint8>( ckDataInOut.len() );
		if( c == a1 || c == a2 || c == a3 ) v1.push_back(a2);
		v1.push_back( c );

		//calc data
		for( tsize i = 0; i < ckDataInOut.len(); i++ )
		{
			c = *(tuint8*)(ckDataInOut.buf()+i);
			if( c == a1 || c == a2 || c == a3 ) v1.push_back(a2);
			v1.push_back(c);
		}

		//calc chk sum
		for( tsize i = 0; i < ckDataInOut.len(); i++ )
		{
			ucChkSum = (*pf)( ucChkSum, *(tuint8*)(ckDataInOut.buf()+i) );
		}
		c = ucChkSum;
		if( c == a1 || c == a2 || c == a3 ) v1.push_back(a2);
		v1.push_back(c);

		//add a3
		v1.push_back(a3);

		//到这里v1必然有内容
		ckDataInOut.let( (tchar*)&(v1[0]), (tsize)v1.size() );
 
		return ckDataInOut;
	}


	static int comesc_de( SCake & ckDataInOut, tuint8 a1, tuint8 a2, tuint8 a3 , PfChkSum_t pf = NULL , SCake * pdata2 = NULL ) // return len indicated at beginning of data
	{
		if( ckDataInOut.len() != 0 )
		{
			std::vector<tuint8> v1;
			int flag = 1;

			//.......a1......a2...data...a2....data.....data.....a3......
			//    1       2      3     2     3       2        2      4

			for( tsize i = 0; i < ckDataInOut.len(); i++ )
			{
				tuint8 c = *(tuint8*)(ckDataInOut.buf()+i);
				tuint8 c2;
				
				
				if( flag == 1 )
				{
					if( c == a1 && i == 0 )
					{
						flag = 2;
						continue;
					} 

					if( c == a1 && i != 0 )
					{
						tuint8 c0 = *(tuint8*)(ckDataInOut.buf()+i-1); // c0就是 c之前一个
						if( c == a1 && c0 != a2 ) // 在任意的前导垃圾中找到了起始符a1
						{
							flag = 2;
							continue;
						}
					}

					continue;
				}


				//here we meet the first ch after the a1
				//c
				if( i+1 < ckDataInOut.len() )
				{
					//取2个字节
					c2 = *(tuint8*)(ckDataInOut.buf()+i+1);

					if( c == a2 )
					{
						v1.push_back( c2 );
						i++;
					}
					else
					{
						v1.push_back( c );
					}
				}
				else
				{
					//已经是最后一个字节了.
					if( c != a2 && c != a3 ) v1.push_back( c );
				}
			}//end for

			//到这里v1还不一定有内容
			if(v1.size()<2)
			{
				ckDataInOut.redim(0);
				return 0;
			}

			if( pdata2 != NULL && pdata2->len() != 0 )
			{
				if( v1.size() - pdata2->len() < 2 )
				{
					ckDataInOut.redim(0);
					return 0;
				}

				for( tsize i2 = 0; i2 < pdata2->len(); i2++ )
				{
					tuint8 c = v1[0];
					*(tuint8*)(pdata2->buf()+i2) = c;
					v1.erase( v1.begin() );
				}
			}

			//here we got LEN,DATA,BCC
			if( v1.size() == 2 )
			{
				ckDataInOut.redim(0);
				return v1[0];
			}

			//here we got LEN,DATA,BCC and DATA>=1
			{
				tuint8 ilen = v1[0];
				tuint8 iChkSum = v1[v1.size()-1];
				v1.erase( v1.begin() );
				v1.erase( v1.end() - 1 );
				
				ckDataInOut.let( (tchar*)&(v1[0]), (tsize)v1.size() );

				//calc chk sum
				if( pf )
				{
					tuint8  ucChkSum(0);

					for( tsize i = 0; i < ckDataInOut.len(); i++ )
					{
						ucChkSum = (*pf)( ucChkSum, *(tuint8*)(ckDataInOut.buf()+i) );
					}
					if( iChkSum != ucChkSum )
					{
						ckDataInOut.redim(0);
						return 0;
					}
				}

				if( ilen != ckDataInOut.len() )
				{
					ckDataInOut.redim(0);
					return 0;
				}

				return ilen;
			}
		}

		return 0;
	}



	/////////////////////////////for com use, recv


	tbool recv_comesc( SCake & ckData , tuint8 a2, tuint8 a3 ) 
	{
		SCake ckTmp;
		tsize i = 1;

		do
		{
			if( m_ckDataL2CacheBuf.len() >= 2 )
				for( ; i < m_ckDataL2CacheBuf.len(); i++ )
				{
					tchar c = *(m_ckDataL2CacheBuf.buf()+i);
					tchar c1 = *(m_ckDataL2CacheBuf.buf()+i-1);

					if( c1 != a2 && c == a3 )
					{
						goto L_RECV_ESC; //now i pointing to a3, the tail.
					}
				}

			if( !sys_recv( ckTmp ) ) break;

			m_ckDataL2CacheBuf.append(ckTmp);

		}while(ckTmp.len()>0);

L_RECV_ESC:
		ckData.redim(i+1);
		m_ckDataL2CacheBuf.dump( ckData );
		//ckData.esc_de(a1,a2,a3);
		return ckData.len()+m_ckDataL2CacheBuf.len()==0?0:1;
	}



public:
	
	virtual void OnDisConn()
	{
		m_biShouldDisConn = 1;
	}


	virtual int on_get_defaultrecv_buf_len() //return the buf len. we just want 1 byte.
	{
		return 1;
	}


}; //end class 




X011_NAMESPACE_END

#endif





/*
W series
com eli cell
*/

// 

#ifndef X011__H_w_WComeliCell_h
#define X011__H_w_WComeliCell_h


X011_NAMESPACE_BEGIN


class WComeliCell : public WComeliProtocol 
{
		
protected:

	HANDLE  m_hComport;


private:

	WComeliCell & operator = (const WComeliCell & rhs) 	{ 	return *this; }
	WComeliCell(const WComeliCell & rhs) {;}


public:

	WComeliCell()
	{
		 
	}

	virtual ~WComeliCell()
	{
		if( m_biComportOpened )
		{
			CloseHandle(m_hComport); //关闭COM 
			m_biComportOpened = 0;
		}
	}


public:


	tbool Conn( std::string strname ) // "com=1;start=1;stop=1;speed=9600;parity=O/E/N;datalen=8;timeoutsec=0.150;"
	{
		DisConn();
		
		WNava nv;

		nv.impconf( strname, ";", "=" );

		if( nv.get("com").empty() ) return 0;

			//MessageBox( 0, CString(("COM"+nv.get("com")).c_str()) + CString(":"), L"a", 0 );

		m_hComport = CreateFile( CString(("COM"+nv.get("com")).c_str()) + CString(":") ,
																	GENERIC_READ | GENERIC_WRITE, 
																	0,    // exclusive access 
																	NULL, // no security attributes 
																	OPEN_EXISTING,
																	0,
																	NULL
																	);
		if( m_hComport == NULL || m_hComport == INVALID_HANDLE_VALUE )
		{
			// "串口打开失败";
			//MessageBox( 0, CString(MOONLOGSTR.c_str()), L"a", 0 );
			return 0;
		}

		m_biComportOpened = 1;

		DCB PortDCB; 
		PortDCB.DCBlength = sizeof(DCB); 
		// 默认串口参数
		GetCommState(m_hComport, &PortDCB);

				PortDCB.fDtrControl = DTR_CONTROL_DISABLE;
		PortDCB.fRtsControl = RTS_CONTROL_DISABLE;

		PortDCB.BaudRate = (int)SStrf::satol( nv.get("speed") );
		PortDCB.ByteSize = (tuint8)SStrf::satol( nv.get("datalen") );
		if( nv.get("parity") == "O" ) PortDCB.Parity = ODDPARITY; 
		else if( nv.get("parity") == "E" ) PortDCB.Parity = EVENPARITY; 
		else if( nv.get("parity") == "N" ) PortDCB.Parity = NOPARITY;
		else
		{
			CloseHandle(m_hComport); //关闭COM 
			m_biComportOpened = 0;
			return 0;
		}
		
		if( nv.get("stop") == "1" ) PortDCB.StopBits = ONESTOPBIT; 
		else if( nv.get("stop") == "1.5" ) PortDCB.StopBits = ONE5STOPBITS; 
		else if( nv.get("stop") == "2" )   PortDCB.StopBits = TWOSTOPBITS; 
		else
		{
			CloseHandle(m_hComport); //关闭COM 
			m_biComportOpened = 0;
			return 0;
		}

		if(! SetCommState(m_hComport, &PortDCB))
		{
			///L"配置串口失败";
			CloseHandle(m_hComport); //关闭COM 
			m_biComportOpened = 0;
			return 0;
		}

		////配置超时值

		if( (int)( SStrf::satof( nv.get("timeoutsec") ) * 1000 ) < 1 )  
		{
			CloseHandle(m_hComport); //关闭COM 
			m_biComportOpened = 0;
			return 0;
		}

		COMMTIMEOUTS CommTimeouts;

		GetCommTimeouts(m_hComport, &CommTimeouts);
		CommTimeouts.ReadIntervalTimeout = MAXDWORD; 
		CommTimeouts.ReadTotalTimeoutMultiplier = 10; 
		CommTimeouts.ReadTotalTimeoutConstant  = (int)( SStrf::satof( nv.get("timeoutsec") ) * 1000 ); 
		CommTimeouts.WriteTotalTimeoutMultiplier = 50; 
		CommTimeouts.WriteTotalTimeoutConstant = (int)( SStrf::satof( nv.get("timeoutsec") ) * 1000 ); 
		if (!SetCommTimeouts(m_hComport, &CommTimeouts))
		{
			///L"不能设置超时参数";
			CloseHandle(m_hComport); //关闭COM 
			m_biComportOpened = 0;
			return 0;
		}

		m_biShouldDisConn = 0;

		return 1;
	}



	virtual void OnDisConn()
	{
		m_biShouldDisConn = 1;
		
		if( m_biComportOpened )
		{
			CloseHandle(m_hComport); 
			m_biComportOpened = 0;
		}
	}



public:


	virtual int on_sys_recv( SCake & ckDataBuf ) //return the recv len, 1 or 0
	{
		if(m_biShouldDisConn)
		{
			return 0;
		}

		ckDataBuf.redim( on_get_defaultrecv_buf_len() );

		DWORD dwBytes;

		ReadFile(m_hComport, ckDataBuf.buf(), ckDataBuf.len(), &dwBytes, 0); 

		if(dwBytes == ckDataBuf.len()) return (int)ckDataBuf.len();

		return 0;
	}


	virtual int on_sys_send( const SCake & ckDataBuf ) //return the successfully sent len
	{
		if(m_biShouldDisConn)
		{
			return 0;
		}

		DWORD ret;

		WriteFile( m_hComport, ckDataBuf.buf_const(), 1 ,&ret, NULL ); //发送 

		//if( !( (int)ckDataBuf.len() % 9 ) || SStrf::rand1() > 0.851 ) WThrd::tr_sleep( 0, 0.001 );
		if( ckDataBuf.len() % 13 == 3 || SStrf::rand1() > 0.56 )
			WThrd::tr_sleep( 0, 0.001 );

		return (int)ret;
	}


}; //end class 




X011_NAMESPACE_END

#endif





#endif

