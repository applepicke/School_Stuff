/**********************************************************************
Filename:		ass1.cpp
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
Purpose: 		A simple painting application that lets you save your work
*********************************************************************/
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include "resource.h"
#include "CPoint.h"
#include "PointBuffer.h"
#include "Ass1.h"

/*Globals*/
PointBuffer *pb = new PointBuffer( POINT_ARR_INIT, POINT_ARR_INC );

/********************************************************************
Function Name: 	WinMain
Purpose: 		Creates the application window
Version: 		1.0
Author: 		William Collins
**********************************************************************/
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PSTR szCmdLine, int iCmdShow)
{
	     
	static TCHAR szAppName[] = TEXT ("Willy's Assignment") ;
    HWND        hwnd ;
    MSG         msg ;
    WNDCLASS    wndclass ;

    wndclass.style         = CS_HREDRAW | CS_VREDRAW ;
    wndclass.lpfnWndProc   = WndProc ;
    wndclass.cbClsExtra    = 0 ;
    wndclass.cbWndExtra    = 0 ;
    wndclass.hInstance     = hInstance ;
    wndclass.hIcon         = LoadIcon (NULL, IDI_APPLICATION) ;
    wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW) ;
    wndclass.hbrBackground = (HBRUSH) GetStockObject (BLACK_BRUSH) ;
    wndclass.lpszMenuName  = MAKEINTRESOURCE(IDR_MENU1);
    wndclass.lpszClassName = szAppName ;

    RegisterClass (&wndclass);
    hwnd = CreateWindow (szAppName,TEXT (WINDOW_TITLE),WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,hInstance,NULL) ;                     
     
    ShowWindow (hwnd, iCmdShow) ;
    UpdateWindow (hwnd) ;
	     
    while (GetMessage (&msg, NULL, 0, 0)){
		TranslateMessage (&msg) ;
		DispatchMessage (&msg) ;
    }

	delete pb;

    return msg.wParam ;
}

/********************************************************************
Function Name: 	WndProc
Purpose: 		A callback that handles messages from the application message queue
Version: 		1.0
Author: 		William Collins
**********************************************************************/
LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
 
	static properties menuProps;
	static bool mouseDown = false;
	static HDC hdc;
	static PAINTSTRUCT ps;

    switch (message){
		case WM_COMMAND:
			DetermineMenuProps(&menuProps, wParam);
			InvalidateRect(hwnd, NULL, true);
			return 0;
		case WM_CREATE:
			return 0;
		case WM_PAINT:
			hdc = BeginPaint(hwnd, &ps);
			DrawCanvas(hdc);
			EndPaint(hwnd, &ps);
			return 0;  
		case WM_DESTROY:
			PostQuitMessage (0) ;
			return 0 ;
		case WM_LBUTTONDOWN:
			mouseDown = true;
			return 0; 
		case WM_MOUSEMOVE:
			if (mouseDown)
			{
				CPoint *newPoint = new CPoint(LOWORD(lParam), HIWORD(lParam), menuProps.colour, menuProps.thickness, true);
				hdc = GetDC(hwnd);
				DrawToNextPoint(hdc, NULL, newPoint);
				ReleaseDC(hwnd, hdc);
				pb->AddPoint(newPoint);
			}
			return 0;
		case WM_LBUTTONUP:
			CPoint *newPoint = new CPoint(LOWORD(lParam), HIWORD(lParam), menuProps.colour, menuProps.thickness, false);
			pb->AddPoint(newPoint);
			mouseDown = false;
			return 0; 
 	}

    return DefWindowProc (hwnd, message, wParam, lParam) ;
}

/********************************************************************
Function Name: 	DrawCanvas
Purpose: 		Draws all of the lines on the screen
In parameters:	HDC - a device context to draw with
Version: 		1.0
Author: 		William Collins
**********************************************************************/
void DrawCanvas(HDC hdc)
{
	CPoint *currentPoint = pb->GetNextPoint();
	CPoint *nextPoint = pb->GetNextPoint();
	HPEN oldPen = NULL, newPen = NULL;

	while (nextPoint != NULL)
	{
		DrawToNextPoint(hdc, currentPoint, nextPoint);

		currentPoint = nextPoint;
		nextPoint = pb->GetNextPoint();
	}
	pb->Rewind();
}

/********************************************************************
Function Name: 	DrawToNextPoint
Purpose: 		Add a line to the existing lines on the screen.
In parameters:	HDC - device context to draw with
				prevPoint - the starting point for the line
				nextPoint - the end point for the line
Version: 		1.0
Author: 		William Collins
**********************************************************************/
void DrawToNextPoint(HDC hdc, CPoint *prevPoint, CPoint *nextPoint)
{
	HPEN oldPen = NULL, newPen = NULL;

	//Check once to see if caller sent a previous point to draw from
	if (prevPoint == NULL) {
		//Get the last point to draw from. Make sure there is something to get
		if ((prevPoint = pb->GetLastPoint()) == NULL){
			return;
		}
	}

	newPen = CreatePen( PS_SOLID, prevPoint->thickness, prevPoint->colour );
	oldPen = (HPEN)SelectObject(hdc, newPen);

	MoveToEx( hdc, prevPoint->x, prevPoint->y, NULL );
	if (prevPoint->isLineBreak)
	{
		LineTo(hdc, nextPoint->x, nextPoint->y);
	}

	SelectObject(hdc, oldPen);
	DeleteObject(newPen);
}

/********************************************************************
Function Name: 	ClearPoints
Purpose: 		clears all the points on the screen
Version: 		1.0
Author: 		William Collins
**********************************************************************/
void ClearPoints()
{
	pb->~PointBuffer();
	pb = new PointBuffer( POINT_ARR_INIT, POINT_ARR_INC );
}

/********************************************************************
Function Name: 	DetermineMenuProps
Purpose: 		Determine the menu properties based on the wParam of the 
				event
In parameters:	props - properties structure to modify
				wParam - the event code to analyze
Version: 		1.0
Author: 		William Collins
**********************************************************************/
void DetermineMenuProps(properties *props, WPARAM wParam)
{
	switch (LOWORD(wParam))
	{
		case ID_FILE_OPEN40001:
			pb->LoadBuffer(SAVE_FILE);
			break;
		case ID_FILE_SAVE40002:
			pb->SaveBuffer(SAVE_FILE);
			break;
		case ID_PENCOLOUR_BLUE:
			props->colour = BLUE;
			break;
		case ID_PENCOLOUR_GREEN:
			props->colour = GREEN;
			break;
		case ID_PENCOLOUR_INDIGO:
			props->colour = INDIGO;
			break;
		case ID_PENCOLOUR_ORANGE:
			props->colour = ORANGE;
			break;
		case ID_PENCOLOUR_RED:
			props->colour = RED;
			break;
		case ID_PENCOLOUR_VIOLET:
			props->colour = VIOLET;
			break;
		case ID_PENCOLOUR_YELLOW:
			props->colour = YELLOW;
			break;
		case ID_PENTHICKNESS_1:
			props->thickness = 1;
			break;
		case ID_PENTHICKNESS_2:
			props->thickness = 2;
			break;
		case ID_PENTHICKNESS_3:
			props->thickness = 3;
			break;
		case ID_PENTHICKNESS_4:
			props->thickness = 4;
			break;
		case ID_PENTHICKNESS_5:
			props->thickness = 5;
			break;
		case ID_LINES_CLEAR:
			ClearPoints();
			break;
		default:
			break;

	}
}

/********************************************************************
Function Name: 	MessageBoxPrintf
Purpose: 		Shows a message box in a convenient easy to call printf
				style function. Stolen from Petzold.
Version: 		1.0
Author: 		Petzold
**********************************************************************/
int CDECL MessageBoxPrintf (TCHAR * szCaption, TCHAR * szFormat, ...)
{
     TCHAR   szBuffer [1024] ;
     va_list pArgList ;
     va_start (pArgList, szFormat) ;
     _vsntprintf_s (szBuffer, sizeof (szBuffer) / sizeof (TCHAR), 
                  szFormat, pArgList) ;
     va_end (pArgList) ;

     return MessageBox (NULL, szBuffer, szCaption, 0) ;
}

/********************************************************************
Function Name: 	OutputDebugStringPrintf
Purpose: 		A nice convenient equivalent to printf. Stolen from class and
				Petzold.
Version: 		1.0
Author: 		Andrew Tyler and Petzold
**********************************************************************/
void OutputDebugStringPrintf(TCHAR *szFormat, ...)
{
	 TCHAR   szBuffer [1024] ;
     va_list pArgList ;
     va_start (pArgList, szFormat) ;
     _vsntprintf_s (szBuffer, sizeof (szBuffer) / sizeof (TCHAR), 
                  szFormat, pArgList) ;
     va_end (pArgList) ;

	 OutputDebugString(szBuffer);
}


