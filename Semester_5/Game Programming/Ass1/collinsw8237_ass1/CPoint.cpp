/**********************************************************************
Filename:		CPoint.cpp
Version: 		1.0                                         
Author:			William Collins                                             
Student No:  	040652633                                           
Course Name/Number: Game Programming CST8237                                 
Lab Sect: 		310                                                      
Assignment #:	1
Assignment name:Assignment 1	
Due Date:		February 18, 2012                                           
Submission Date:February 18, 2012
Professor:		Andrew Tyler                                           
Purpose: 		A point that holds information about how it is to be drawn
*********************************************************************/
#include <Windows.h>
#include "CPoint.h"

CPoint::CPoint(int inx, int iny, COLORREF incolour, unsigned int inthickness, bool inIsLineBreak)
{
	x = inx;
	y = iny;
	colour = incolour;
	thickness = inthickness;
	isLineBreak = inIsLineBreak;
}

CPoint::CPoint()
{
	x = 0;
	y = 0;
	colour = RGB(0,0,0);
	thickness = 0;
	isLineBreak = false;
}