﻿
#ifndef K1__blackboard_t_H
#define K1__blackboard_t_H


#include "2.h"




//
class blackboard_t 
{
public:
	int  m_width;


public:
	blackboard_t();
	~blackboard_t();

public:
	void DrawScreenPixel( int x, int y, SBmp::RGB_t c );

	void DrawLine( int valueOld, int valueNew ); 

	long GetValue( std::string strAddr );

};


extern blackboard_t  *gp_blackboard;





#endif



