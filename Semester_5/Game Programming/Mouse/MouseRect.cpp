/* MouseRect.cpp
Adds mouse handlers to the code from HelloWin. 
Illustrates how to generate a WM_PAINT message using InvalidateRect()
*/

#include <windows.h>

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM) ;

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PSTR szCmdLine, int iCmdShow)
{
     static TCHAR szAppName[] = TEXT ("MouseRect") ;
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
    // wndclass.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH) ;
	wndclass.hbrBackground = CreateSolidBrush(RGB(0,100,0)) ;
     wndclass.lpszMenuName  = NULL ;
     wndclass.lpszClassName = szAppName ;

     RegisterClass (&wndclass);
     hwnd = CreateWindow (szAppName,TEXT ("Mouse Rect"),WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,hInstance,NULL) ;                     
     
     ShowWindow (hwnd, iCmdShow) ;
     UpdateWindow (hwnd) ;												// sends a WM_PAINT to WndProc. 
     
     while (GetMessage (&msg, NULL, 0, 0)){
          TranslateMessage (&msg) ;
          DispatchMessage (&msg) ;
     }
     return msg.wParam ;
}

LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
	
	// these must be static because they must survive from one loop to the next
	static RECT rect;													// left,top,right,bottom
	
	HDC         hdc ;
    PAINTSTRUCT ps;    
     switch (message){
		case WM_CREATE:
			return 0 ;

		case WM_PAINT:
			// only the most recent rectangle gets drawn on a resize.
			hdc=BeginPaint(hwnd,&ps);									// get a DC and lock the buffer; also clear (Validate) the update region 
			Rectangle(hdc,rect.left, rect.top,rect.right,rect.bottom);	// draw the rectangle
			//Ellipse(hdc,rect.left, rect.top,rect.right,rect.bottom);
			EndPaint(hwnd,&ps);											// Release the DC - or it's a resource leak.
			return 0 ;
          
		case WM_DESTROY:
			PostQuitMessage (0) ;
			return 0 ;
   
		case WM_LBUTTONDOWN: // the left mouse button is pressed at the top left of the rectangle
			rect.left = LOWORD(lParam); 
			rect.top = HIWORD(lParam); 
			return 0; 
 
		case WM_MOUSEMOVE: // the mouse is moved
			return 0; 

		case WM_LBUTTONUP: // the left mouse button is released at the bottom right of the rectangle
		
			rect.right = LOWORD(lParam); 
			rect.bottom = HIWORD(lParam); 

			// will result in a WM_PAINT message shortly, once the message queue is empty 
			InvalidateRect(hwnd,&rect,true);							//puts the rectangle in the update region
			//InvalidateRect(hwnd,NULL,true);							// puts the entire client area in the update region

			// if there is an update region, this will send a WM_PAINT message directly to the app
			UpdateWindow(hwnd); 

			return 0; 
 	}

    return DefWindowProc (hwnd, message, wParam, lParam) ;
}

