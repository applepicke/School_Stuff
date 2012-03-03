/**********************************************************************
Filename:		Ass1.h
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
Purpose: 		Header information for assignment 1
*********************************************************************/
#ifndef ASS1_H
#define ASS1_h
/*Initial buffer sizes*/
#define POINT_ARR_INIT 500 //The number of initial point structures created
#define POINT_ARR_INC 200 //Amount of point structures to add when initial array is filled

/* Colour constants*/
#define RED RGB(200, 0, 0)
#define ORANGE RGB(255, 125, 0)
#define YELLOW RGB(255, 255, 0)
#define GREEN RGB(0, 225, 0)
#define BLUE RGB(0, 0, 225)
#define INDIGO RGB(75, 0, 130)
#define VIOLET RGB(238, 130, 238)

#define WINDOW_TITLE "Willy's Paint Playhouse"
#define SAVE_FILE "lines.sav"

//Classes
class properties {
public:
	COLORREF colour;
	unsigned int thickness;	
	properties(): colour(BLUE), thickness(1){}
};

/*Function Prototypes*/
LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM);
void SavePoints();
void LoadPoints();
void DrawCanvas(HDC);
void ClearPoints();
void DetermineMenuProps(properties *, WPARAM);
int CDECL MessageBoxPrintf (TCHAR *, TCHAR *, ...);
void OutputDebugStringPrintf(TCHAR *, ...);
void DrawToNextPoint(HDC, CPoint*, CPoint*);
#endif