/**********************************************************************
Filename:		PointBuffer.h
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
Purpose: 		Header information for the PointBuffer class
*********************************************************************/
#ifndef POINTBUFFER_H
#define POINTBUFFER_H
class PointBuffer
{
	CPoint **points;	//The points in this buffer
	int capacity;		//Determines when the buffer will be inflated
	unsigned int numPoints;		//Number of points currently in the buffer
	int inflateSize;	//How much the buffer will inflate when max is hit
	unsigned int nextPoint;		//Index of next point in the buffer. For convenience.

	void Inflate();
	void CleanUp();
public:
	PointBuffer(int max, int infSize);
	~PointBuffer();
	void AddPoint(CPoint *point);
	CPoint *GetNextPoint();
	CPoint *GetLastPoint();
	void Rewind();
	unsigned int GetNumPoints();

	void LoadBuffer(char *filename);
	void SaveBuffer(char *filename);
};
#endif