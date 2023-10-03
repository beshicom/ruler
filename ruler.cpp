


//
//	ruler
//
//	sunce 2023/10/03 by beshi
//



#include	<windows.h>
#include	"ruler.h"



HINSTANCE	hInstance;

char	AppName[] = "Ruler";
char	RulerCN[] = "RulerCN";
HWND	ghWnd;
int		giX, giY, giWidth, giHeight;
int		gnMode = 0;		// マウスについていくときは not0
int		giDispWidth, giDispHeight;


LRESULT WndProc ( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );



int WinMain ( HINSTANCE hInst, HINSTANCE hPrevInst,
												char * CmdLine, int CmdShow )
{

	hInstance = hInst;

	giX = 100;
	giY = 100;
	giWidth = 100;
	giHeight = 100;

	// 画面のサイズ
	giDispWidth =  GetSystemMetrics( SM_CXSCREEN );
	giDispHeight = GetSystemMetrics( SM_CYSCREEN );

	// ウイドウクラスの登録
	{
	WNDCLASSEX	wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC)WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInst;
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = RulerCN;
	HICON	hI = LoadIcon( NULL, IDI_APPLICATION );
	wc.hIcon = hI;
	wc.hIconSm = hI;
	wc.hCursor = LoadCursor( NULL, IDC_ARROW );
	RegisterClassEx( &wc );
	}// end

	// ウインドウの作成
	giX = 0;
	giY = giDispHeight / 2;
	giWidth = giDispWidth;
	giHeight = 50;
	ghWnd = CreateWindowEx( NULL, RulerCN, AppName, WS_POPUP | WS_BORDER,
						giX, giY, giWidth, giHeight, NULL, NULL, hInst, NULL );
	ShowWindow( ghWnd, CmdShow );
	UpdateWindow( ghWnd );

	// メッセージループ
	MSG		msg;
	while(  GetMessage( &msg, NULL, 0, 0 ) != 0 ){
		TranslateMessage( &msg );
		DispatchMessage( &msg );
	}

	return msg.wParam;

}
// WinMain()



LRESULT WndProc ( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{

	switch( uMsg ){

	case WM_DESTROY:
		{
		PostQuitMessage( NULL );
		}
		break;	// WM_DESTROY

	case WM_PAINT:
		{
		PAINTSTRUCT	ps;
		BeginPaint( hWnd, &ps );
		char	t[] =
				"Push left button to move ruler. Push right button to quit.";
		SetTextColor( ps.hdc, RGB(255,255,255) );
		SetBkColor( ps.hdc, RGB(0,0,0) );
		TextOut( ps.hdc, 0, 0, t, lstrlen(t) );
		EndPaint( hWnd, &ps );
		}
		break;	// WM_PAINT

	case WM_LBUTTONDOWN:
		{
		gnMode ^= 1;
		}
		break;	// WM_LBUTTONDOWN

	case WM_RBUTTONDOWN:
		{
		POINT	pt;
		pt.x = LOWORD( lParam );
		pt.y = HIWORD( lParam );
		HMENU	h = LoadMenu( hInstance, "MyMenu" );
		HMENU	hs = GetSubMenu( h, 0 );
		ClientToScreen( hWnd, &pt );
		TrackPopupMenu( hs, TPM_LEFTALIGN, pt.x, pt.y, 0, hWnd, NULL );
		DestroyMenu( h );
		}
		break;	// WM_RBUTTONDOWN

	case WM_MOUSEMOVE:
		{
		if( gnMode == 0 )	break;
		POINT	pt;
		pt.x = LOWORD( lParam );
		pt.y = HIWORD( lParam );
		ClientToScreen( hWnd, &pt );
		giY = pt.y - giHeight / 2;
		MoveWindow( hWnd, giX, giY, giWidth, giHeight, TRUE );
		}
		break;	// WM_MOVEMOUSE

	case WM_COMMAND:
		{
		switch( LOWORD(wParam) ){

		case IDM_EXIT:
			{
			DestroyWindow( hWnd );
			}
			break;	// IDM_EXIT

		default:
			{
			return DefWindowProc( hWnd, uMsg, wParam, lParam );
			}

		}// switch
		}// end
		break;	// WM_COMMAND

	default:
		{
		return DefWindowProc( hWnd, uMsg, wParam, lParam );
		}

	}// switch


	return 0;

}
// WndProc()



