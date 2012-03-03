/**********************************************************************
Filename:		PointBuffer.cpp
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
Purpose: 		A buffer that holds CPoint objects and will dynamically
				increase in size as it gets bigger
*********************************************************************/
#include <Windows.h>
#include <stdio.h>
#include "CPoint.h"
#include "PointBuffer.h"
#include "Ass1.h"

PointBuffer::PointBuffer(int max, int infSize)
{
	points = new CPoint*[max];
	capacity = max;
	inflateSize = infSize;
	numPoints = 0;
	nextPoint = 0;
}

PointBuffer::~PointBuffer()
{
	CleanUp();
}

/********************************************************************
Function Name: 	AddPoint
Purpose: 		Adds a point to the buffer
In parameters:	newPoint - the point to add
Version: 		1.0
Author: 		William Collins
**********************************************************************/
void PointBuffer::AddPoint(CPoint *newPoint)
{
	//Check to see if it is time to inflate the buffer
	if (numPoints == capacity)
	{
		Inflate();
	}
	points[numPoints] = newPoint;
	numPoints++;
}

/********************************************************************
Function Name: 	Inflate
Purpose: 		Moves the buffer to a new memory block, and increases the capacity
Version: 		1.0
Author: 		William Collins
**********************************************************************/
void PointBuffer::Inflate()
{
	//Copy buffer contents to new memory area
	CPoint **tempPointBuffer = new CPoint*[capacity + inflateSize];
	capacity += inflateSize;
	for (unsigned int i = 0; i < numPoints; i++)
	{
		tempPointBuffer[i] = points[i];
	}

	delete []points;
	points = tempPointBuffer;
}

/********************************************************************
Function Name: 	CleanUp
Purpose: 		Frees up all the used dynamic memory in the buffer
Version: 		1.0
Author: 		William Collins
**********************************************************************/
void PointBuffer::CleanUp()
{
	//Release memory used by the buffer
	for (unsigned int i = 0; i < numPoints; i++)
	{
		delete points[i];
	}
	delete [] points;
}

/********************************************************************
Function Name: 	GetNextPoint
Purpose: 		Goes in the buffer and finds the next point relative
				to the marker
Out parameters: The next point
Version: 		1.0
Author: 		William Collins
**********************************************************************/
CPoint *PointBuffer::GetNextPoint()
{
	if (nextPoint < numPoints)
	{
		return points[nextPoint++];
	}
	else 
	{
		return NULL;
	}
}

/********************************************************************
Function Name: 	GetLastPoint
Purpose: 		Get the current last point in the buffer
Out parameters: The last point
Version: 		1.0
Author: 		William Collins
**********************************************************************/
CPoint *PointBuffer::GetLastPoint()
{
	if (numPoints == 0)
		return NULL;
	return points[numPoints-1];
}

/********************************************************************
Function Name: 	Rewind
Purpose: 		Sets the marker back to the beginning of the buffer
Version: 		1.0
Author: 		William Collins
**********************************************************************/
void PointBuffer::Rewind()
{
	nextPoint = 0;
}

/********************************************************************
Function Name: 	GetNumPoints
Purpose: 		Get the number of points in the buffer
Out parameters: number of points in the buffer
Version: 		1.0
Author: 		William Collins
**********************************************************************/
unsigned int PointBuffer::GetNumPoints()
{
	return numPoints;
}

/********************************************************************
Function Name: 	LoadBuffer
Purpose: 		Loads a buffer from a file of points
In parameters:	name of file to load
Version: 		1.0
Author: 		William Collins
**********************************************************************/
void PointBuffer::LoadBuffer(char *filename)
{
	unsigned int pCount;
	CPoint *point;
	FILE *file;
	fopen_s(&file, filename, "a+b");

	CleanUp();
	points = new CPoint*[capacity];
	numPoints = 0;

	fread(&pCount, sizeof(unsigned int), 1, file);
	for (unsigned int i = 0; i < pCount; i++)
	{
		point = new CPoint();
		fread(point, sizeof(CPoint), 1, file);
		AddPoint(point);
	}
	fclose(file);
	MessageBoxPrintf(TEXT("Points Loaded"), TEXT("%d points loaded."), numPoints);
}

/********************************************************************
Function Name: 	SaveBuffer
Purpose: 		Saves the buffer to a file
In parameters:	Name of the file to save
Version: 		1.0
Author: 		William Collins
**********************************************************************/
void PointBuffer::SaveBuffer(char *filename)
{
	CPoint *point;
	FILE *file; 
	fopen_s(&file, filename, "wb");

	fwrite(&numPoints, sizeof(unsigned int), 1, file);
	for (unsigned int i = 0; i < numPoints; i++)
	{
		point = GetNextPoint();
		fwrite(point, sizeof(CPoint), 1, file);
	}
	
	fclose(file);
	Rewind();
	MessageBoxPrintf(TEXT("Points Saved"), TEXT("%d points saved."), numPoints);
}
