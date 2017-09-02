

#pragma once

#ifndef MD5_GFUNC_MD5_H
#define MD5_GFUNC_MD5_H

#include <string>


extern unsigned char * md5_encode( void *data, unsigned long len , unsigned char d[16] )  ;

extern unsigned char * md5_file(const char *filename, unsigned char d[16] ) ;

extern char * md5_string ( unsigned char d[16], char *outbuf);


extern std::string md5str_data ( void *pdata , unsigned long len );

extern std::string md5str_file ( std::string filename );




#endif




