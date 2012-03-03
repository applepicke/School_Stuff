/* MouseRectArray.cpp
Adds mouse handlers to the code from HelloWin. 
Illustrates how to generate a WM_PAINT message using InvalidateRect()
Saves the rectangles in an array so they can all be redrawn by the WM_PAINT handler.
Note how output is always clipped to the client area.
*/

#include <windows.h>

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM) ;

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PSTR szCmdLine, int iCmdShow)
{
     
	static TCHAR szAppName[] = TEXT ("MouseRectArray") ;
     HWND         hwnd ;
     MSG          msg ;
     WNDCLASS     wndclass ;

     wndclass.style         = CS_HREDRAW | CS_VREDRAW ;
     wndclass.lpfnWndProc   = WndProc ;
     wndclass.cbClsExtra    = 0 ;
     wndclass.cbWndExtra    = 0 ;
     wndclass.hInstance     = hInstance ;
     wndclass.hIcon         = LoadIcon (NULL, IDI_APPLICATION) ;
     wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW) ;
     wndclass.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH) ;
     wndclass.lpszMenuName  = NULL ;
     wndclass.lpszClassName = szAppName ;

     RegisterClass (&wndclass);
     hwnd = CreateWindow (szAppName,TEXT ("Mouse Rect Array"),WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,hInstance,NULL) ;                     
     
     ShowWindow (hwnd, iCmdShow) ;
     UpdateWindow (hwnd) ;	// sends a WM_PAINT to WndProc (if the update region isn't empty). 
     
     while (GetMessage (&msg, NULL, 0, 0)){
          TranslateMessage (&msg) ;
          DispatchMessage (&msg) ;
     }
     return msg.wParam ;
}

LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
	int i;
	// these must be static because they must survive from one loop to the next
	static RECT rect;	// left,top,right,bottom
	static RECT rectArray[1000];
	static int currIndex=0; // how many saved rects

	HDC         hdc ; // this isn't static because we get a new one each time (CS_OWNDC will get a permanent one)
	PAINTSTRUCT ps; 
	
     switch (message){
		case WM_CREATE:
			return 0 ;

		case WM_PAINT:
			// all the rectangles get drawn
			hdc=BeginPaint(hwnd,&ps); // get a DC and lock the buffer; also clear (Validate) the update region 
			for(i=0;i<currIndex;i++){
				rect=rectArray[i];
				Rectangle(hdc,rect.left, rect.top,rect.right,rect.bottom);	// draw the rectangle
			}
			EndPaint(hwnd,&ps);												// Release the DC - or it's a resource leak
			return 0 ;
          
		case WM_DESTROY:
			PostQuitMessage (0) ;
			return 0 ;
   
		case WM_LBUTTONDOWN: // the left mouse button is pressed at the top left of the rectangle
			rect.left = LOWORD(lParam); 
			rect.top = HIWORD(lParam); 
			return 0; 
 
		case WM_MOUSEMOVE: // the mouse is moved - we don't care
			return 0; 

		case WM_LBUTTONUP: // the left mouse button is released at the bottom right of the rectangle
			rect.right = LOWORD(lParam); 
			rect.bottom = HIWORD(lParam); 
			rectArray[currIndex++]=rect; // save the rectangle

			InvalidateRect(hwnd,NULL,true);	// repaint entire client region
			// when there are no other messages, this will result in a WM_PAINT post
			
			return 0; 
 	}

    return DefWindowProc (hwnd, message, wParam, lParam) ;
}

