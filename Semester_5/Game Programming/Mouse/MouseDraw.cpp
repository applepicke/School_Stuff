/* MouseDraw.cpp
Adds mouse handlers to the code from HelloWin. The MOUSEMOVE handler gets its own DC for painting.
Because there is no code in the PAINT handler, the contents of the client area will not survive resizing
*/

#include <windows.h>
    

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM) ;

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PSTR szCmdLine, int iCmdShow)
{
     static TCHAR szAppName[] = TEXT ("MouseMov") ;
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
     hwnd = CreateWindow (szAppName,TEXT ("Mouse Draw"),WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,hInstance,NULL) ;                     
     
     ShowWindow (hwnd, iCmdShow) ;
     UpdateWindow (hwnd) ;
     
     while (GetMessage (&msg, NULL, 0, 0)){
          TranslateMessage (&msg) ;
          DispatchMessage (&msg) ;
     }
     return msg.wParam ;
}

LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
	
	// these must be static because they must survive from one call of WndProc to the next
	static BOOL bDraw = FALSE;										// can we draw?
	static POINT ptPrevious;										// save the previous point
	
	HDC         hdc ;
          
     switch (message){
		case WM_CREATE:
			return 0 ;

		case WM_PAINT:
			ValidateRect(hwnd,NULL);								// clears the update region.
			return 0 ;
          
		case WM_DESTROY:
			PostQuitMessage (0) ;
			return 0 ;
   
		case WM_LBUTTONDOWN:										// the left mouse button is pressed
			bDraw = TRUE;
			ptPrevious.x = LOWORD(lParam); 
			ptPrevious.y = HIWORD(lParam); 
			return 0; 
 
		case WM_MOUSEMOVE:											// the mouse is moved
			if(bDraw) {												// drawing occurs only if the left mouse button is down
				hdc = GetDC(hwnd);									//get a common device context for drawing
				MoveToEx(hdc, ptPrevious.x, ptPrevious.y, NULL);	// from the previous point
				LineTo(hdc,LOWORD(lParam) ,HIWORD(lParam) );		// to this point
				ReleaseDC(hwnd, hdc);								// - or it's a resource leak
			
				ptPrevious.x = LOWORD(lParam);						// then update the previous point
				ptPrevious.y = HIWORD(lParam);
			} 
  			return 0; 

		case WM_LBUTTONUP:											// the left mouse button is released
			bDraw = FALSE; 
			return 0; 

 	}

    return DefWindowProc (hwnd, message, wParam, lParam) ;
}

