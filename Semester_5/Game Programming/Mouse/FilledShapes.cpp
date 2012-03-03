/**********************************************************************************************************
 FilledShapes - A.Tyler
Shows GDI shapes filled by the selected brush and outlines by the selected pen
***********************************************************************************************************/

#include <windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM) ;

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PSTR szCmdLine, int iCmdShow)
{
     static TCHAR szAppName[] = TEXT ("FilledShapes") ;
     HWND         hwnd ;
     MSG          msg ;
     WNDCLASS     wndclass ;
	 HMENU	hMenu;

     wndclass.style         = CS_HREDRAW | CS_VREDRAW ;
     wndclass.lpfnWndProc   = WndProc ;
     wndclass.cbClsExtra    = 0 ;
     wndclass.cbWndExtra    = 0 ;
     wndclass.hInstance     = hInstance ;
     wndclass.hIcon         = LoadIcon (NULL, IDI_APPLICATION) ;
     wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW) ;
     wndclass.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH) ;
    // wndclass.lpszMenuName  = NULL ;
	wndclass.lpszMenuName  = MAKEINTRESOURCE(IDR_MENU1); ;
     wndclass.lpszClassName = szAppName ;

    RegisterClass (&wndclass);
   // hMenu = LoadMenu (hInstance, MAKEINTRESOURCE (IDR_MENU1)) ;


    hwnd = CreateWindow (szAppName,TEXT ("Filled GDI Shapes"),WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,hInstance,NULL) ;                     
   //  hwnd = CreateWindow (szAppName,TEXT ("Filled GDI Shapes"),WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,hMenu,hInstance,NULL) ;                     
     
     ShowWindow (hwnd, iCmdShow) ;
     UpdateWindow (hwnd) ;	// sends a WM_PAINT to WndProc  
     
     while (GetMessage (&msg, NULL, 0, 0)){
          TranslateMessage (&msg) ;
          DispatchMessage (&msg) ;
     }
     return msg.wParam ;
}

LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
	static unsigned int GDIType = 0;
	static LOGBRUSH newBrush;
	HBRUSH hOldBrush,hNewBrush;
	static LOGPEN newPen;
	HPEN hOldPen, hNewPen;
	POINT pnt;
	HDC hButtonDC;
	
	// these must be static because they must survive from one loop to the next
	static BOOL bDraw=FALSE;
	static RECT rect;	// left,top,right,bottom
	static COLORREF lastColour;
	static HMENU hMenu;

     switch (message){
	 case WM_COMMAND:
		 hMenu = GetMenu (hwnd) ;
          
          switch (LOWORD (wParam))
          {
          case ID_GDITYPE_ELLIPSE:
			  GDIType = 0;
			  return 0;
          case ID_GDITYPE_ROUNDRECTANGLE:
			  GDIType = 1;
			  return 0;
          case ID_GDITYPE_SQUARERECTANGLE:
			  GDIType = 2;
			  return 0;
          case ID_GDITYPE_PIECHART:
			  GDIType = 3;
			  return 0;
          case ID_GDITYPE_CHORD: 
			  GDIType = 4;
			  return 0;
			 
          case ID_BRUSHSTYLE_SOLID:
			  newBrush.lbStyle = BS_SOLID;
			  return 0;
          case ID_BRUSHSTYLE_HATCHED:
				newBrush.lbStyle = BS_HATCHED;
			  return 0;

           case ID_HATCHSTYLE_HORIZONTAL:
			  newBrush.lbHatch = HS_HORIZONTAL;
			  return 0;
		  case ID_HATCHSTYLE_VERTICAL:
			  newBrush.lbHatch = HS_VERTICAL;
			  return 0;
		  case ID_HATCHSTYLE_DIAGONAL:
			  newBrush.lbHatch = HS_FDIAGONAL;
			  return 0;
		  case ID_HATCHSTYLE_CROSS:
				newBrush.lbHatch = HS_CROSS;
			  return 0;
		  case ID_HATCHSTYLE_DIAGONAL_CROSS:       
				newBrush.lbHatch = HS_DIAGCROSS;
			  return 0;

			case ID_PENSTYLE_SOLID:
			newPen.lopnStyle=PS_SOLID;
			  return 0;
			case ID_PENSTYLE_DASH:
			  newPen.lopnStyle=PS_DASH;
			  return 0 ;			  
          case ID_PENSTYLE_DOT: 
			  newPen.lopnStyle=PS_DOT;
			  return 0 ;
          case ID_PENSTYLE_DASH_DOT: 
			  newPen.lopnStyle=PS_DASHDOT;
			  return 0;
          case ID_PENSTYLE_DASH_DOT_DOT:
			  newPen.lopnStyle=PS_DASHDOTDOT;
			  return 0;
          case ID_PENSTYLE_INSIDEFRAME:
			  newPen.lopnStyle=PS_INSIDEFRAME;
	          return 0;     
          }
          break ;

		case WM_CREATE:
			return 0 ;
		case WM_PAINT:
			return 0 ;
       	case WM_DESTROY:
			PostQuitMessage (0) ;
			return 0 ;
   		case WM_LBUTTONDOWN: // the left mouse button is pressed at the top left of the rectangle
			rect.left = LOWORD(lParam); 
			rect.top = HIWORD(lParam); 
			bDraw=TRUE;
			return 0; 
 		case WM_MOUSEMOVE:
			return 0; 
		case WM_LBUTTONUP: 
			if(bDraw){
				hButtonDC=GetDC(hwnd);
				// get the bottom right coords
				rect.right = LOWORD(lParam); 
				rect.bottom = HIWORD(lParam);
				
				// make a new brush - for the fill
				lastColour=newBrush.lbColor=RGB(rand()%255,rand()%255,rand()%255);
				hNewBrush=CreateBrushIndirect(&newBrush);
				// select the new brush - save the old brush for later
				hOldBrush=(HBRUSH)SelectObject(hButtonDC,hNewBrush);
				
				// make a new pen - for the outline
				pnt.x=rand()%3;	// the width of the pen (1 for anything not solid)
				newPen.lopnWidth=pnt;
				newPen.lopnColor=RGB(rand()%255,rand()%255,rand()%255);
				hNewPen=CreatePenIndirect(&newPen);
				hOldPen=(HPEN)SelectObject(hButtonDC,hNewPen);
				
				// do the drawing
				switch(GDIType){
				case 0:	// An Ellipse
					Ellipse(hButtonDC,rect.left,rect.top,rect.right,rect.bottom);
					break;
				case 1:	// A rectangle with elliptical rounded corners
					RoundRect(hButtonDC,rect.left,rect.top,rect.right,rect.bottom,(rect.right-rect.left)/4,(rect.bottom-rect.top)/3);
					break;
				case 2:	// A rectangle with square corners
					Rectangle(hButtonDC,rect.left,rect.top,rect.right,rect.bottom);
					break;
				case 3:	// A pie chart - a sector is missing
					Pie(hButtonDC,rect.left,rect.top,rect.right,rect.bottom,rect.left,rect.top,rect.right,rect.top);
						break;
				case 4:	// Chord: like a pie but a segment is missing 
					Chord(hButtonDC,rect.left,rect.top,rect.right,rect.bottom,rect.left,rect.top,rect.right,rect.top);
					break;
				}

				// clean up
				SelectObject(hButtonDC,hOldBrush);//replace the old brush
				DeleteObject(hNewBrush);// delete the new brush 
				SelectObject(hButtonDC,hOldPen);//replace the old pen
				DeleteObject(hNewPen);// delete the new pen 

				DeleteDC(hButtonDC);// delete the DC 
			}
		return 0; 
 	}

    return DefWindowProc (hwnd, message, wParam, lParam) ;//the system will handle all other messages
}

