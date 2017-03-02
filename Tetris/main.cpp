#include"head.h"
#include"resource1.h"
LRESULT CALLBACK WindowProc(HWND hWmd,UINT nMsg,WPARAM wParam,LPARAM lParam);

int WINAPI WinMain(HINSTANCE hinstance,HINSTANCE hPreInstance,LPTSTR lpCmdLine,int nCmdShow)
{ WNDCLASSEX wc;
  HWND hWnd;
  MSG nSg;
  RECT rect;
 
  wc.hbrBackground =(HBRUSH)COLOR_WINDOW;
  wc.cbClsExtra=0;
  wc.cbSize=sizeof(WNDCLASSEX);
  wc.cbWndExtra=0;
  wc.hCursor=LoadCursor(NULL,IDC_ARROW);
  wc.hIcon=LoadIcon(hinstance, MAKEINTRESOURCE(IDI_ICON1));
  wc.hIconSm=NULL;
  wc.hInstance=hinstance;
  wc.lpfnWndProc=WindowProc;
  wc.lpszClassName="els";
  wc.lpszMenuName=NULL;
  wc.style=CS_HREDRAW |CS_VREDRAW;

  if(RegisterClassEx(&wc)==0)
	  {int a=GetLastError();
	   return 0;
      }
  SetRect(&rect,0,0,800,600);
  AdjustWindowRect(&rect,WS_OVERLAPPEDWINDOW,false);
  hWnd=CreateWindowEx(WS_EX_TOPMOST,"els","俄罗斯方块",WS_OVERLAPPEDWINDOW,300,50,rect.right-rect.left,rect.bottom-rect.top,NULL,NULL,hinstance,NULL);
  if(hWnd==NULL)
	  return 0;
  ShowWindow(hWnd,nCmdShow);
  while(GetMessage(&nSg,NULL,0,0))
  { TranslateMessage(&nSg);
    DispatchMessage(&nSg);
  }
  return 0;
}

LRESULT CALLBACK WindowProc(HWND hWmd,UINT nMsg,WPARAM wParam,LPARAM lParam)
{ PAINTSTRUCT pt;
  HDC hDC;
  static HFONT hFont;
  //static HWND btnHwnd1; 
  switch(nMsg)
  { case WM_CREATE:
         //btnHwnd1=CreateWindowEx(0, "button", "重新开始",WS_VISIBLE|WS_CHILD,65,200,100,30,hWmd,(HMENU)0,0,NULL);
		 //btnHwnd2=CreateWindow( TEXT("button"), TEXT("选择方块"),WS_VISIBLE|WS_CHILD,65,250,100,30,hWmd,(HMENU)2,(HINSTANCE)GetWindowLong(hWmd, GWL_HINSTANCE ),NULL);
         onCreate();
		 hFont = CreateFont(
                -16/*高度*/, -8/*宽度*/, 0, 0, 400 /*一般这个值设为400*/,
                FALSE/*不带斜体*/, FALSE/*不带下划线*/, FALSE/*不带删除线*/,
                DEFAULT_CHARSET,  //使用默认字符集
                OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS,  //这行参数不用管
                DEFAULT_QUALITY,  //默认输出质量
                FF_DONTCARE,  //不指定字体族*/
                TEXT("华康娃娃体W5")  //字体名
            );
		 //SendMessage(btnHwnd1, WM_SETFONT, (WPARAM)hFont, NULL);//设置按钮字体
		 //SendMessage(btnHwnd2, WM_SETFONT, (WPARAM)hFont, NULL);//设置按钮字体
		 break;
	case WM_TIMER:
		 onTimer(hWmd);
		 break;
    case WM_PAINT:
		 hDC=BeginPaint(hWmd,&pt);
		 onPaint(hDC);
		 EndPaint(hWmd,&pt);
		 break;
	case WM_KEYDOWN:
		 switch(wParam)
		 { case VK_RETURN:
		        onReturn(hWmd);
		        break;
		   case VK_LEFT:
			    OnLeft(hWmd);
			    break;
		   case VK_RIGHT:
			    OnRight(hWmd);
			    break;
		   case VK_SPACE:
			    OnChangeSqare(hWmd);
		        break;
		   case VK_DOWN:
			    OnDown(hWmd);
		        break;
		 }
		 break;
	/*case WM_COMMAND:
		switch(LOWORD(wParam)) 
		{ case 0: 
		       switch(HIWORD(wParam)) 
			   { case BN_CLICKED: 
			               onCreate();
			               break;
			   }
			   break;
		  default:break;
		}
		break;*/
    case WM_DESTROY:
		 KillTimer(hWmd,DEF_TIMER1);
		 //PlaySound(NULL,NULL,NULL);
         PostQuitMessage(0);
	     break;
  }
	return DefWindowProc(hWmd,nMsg,wParam,lParam);
}
