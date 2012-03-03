/**********************************************************************
Filename:		CPoint.h
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
Purpose: 		Header information for the CPoint class
*********************************************************************/
#ifndef CPOINT_H
#define CPOINT_H
class CPoint
{
public: 
	COLORREF colour;
	unsigned int thickness;
	int x;
	int y;
	bool isLineBreak; //Determines whether or not a line should be drawn to this point

	/*Creation and Destruction*/
	CPoint(int inx, int iny, COLORREF incolour, unsigned int inthickness, bool inDrawPrevLine);
	CPoint();
};
#endif