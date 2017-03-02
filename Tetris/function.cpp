#include"head.h"
char arrBackGroud[17][10]={0};
char arrSqare[2][4]={0};
int g_nLine=-1;
int g_nList=-1;
int Score=0;
char NextSqare[2][4]={0};
int Lines=0;
int CurrentIndex;
int NextIndex;
int start=1;

void onPaint(HDC hDC)
{HDC HMemDC=CreateCompatibleDC(hDC);
 HBITMAP hBitmapBack=(HBITMAP)LoadImage(NULL, "back.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);  
 SelectObject(HMemDC,hBitmapBack);
 PaintSqare(HMemDC);
 ShowSqare2(HMemDC);
 ShowScore(HMemDC);
 ShowLines(HMemDC);
 BitBlt(hDC,0,0,800,600,HMemDC,0,0,SRCCOPY);
 DeleteObject(hBitmapBack);
 DeleteDC(HMemDC);
}
void onCreate()
{ ClearScreen();
  srand((unsigned int)time(NULL));
  CurrentIndex=rand()%7;
  CreateRandomSqare();
  CopyToBack();
  NextIndex=rand()%7;
  ShowNext();
}
void PaintSqare(HDC HMemDC)
{ 
  HDC HMemDC2=CreateCompatibleDC(HMemDC);
  HBITMAP hBitmapBack2=(HBITMAP)LoadImage(NULL, "sqare.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);  
  SelectObject(HMemDC2,hBitmapBack2);
  for(int i=0;i<2;i++)
     for(int j=0;j<4;j++)
		 if(NextSqare[i][j]==1)
			   BitBlt(HMemDC,630+j*30,130+i*30,30,30,HMemDC2,0,0,SRCCOPY);
  for(int i=0;i<17;i++)
     for(int j=0;j<10;j++)
		 if(arrBackGroud[i][j]==1)
			 //Rectangle(HMemDC,253+j*30,31+i*30,253+j*30+30,31+i*30+30);
			   BitBlt(HMemDC,253+j*30,31+i*30,30,30,HMemDC2,0,0,SRCCOPY);
 //BitBlt(HMemDC,0,0,800,600,HMemDC2,0,0,SRCCOPY);
 DeleteObject(hBitmapBack2);
 DeleteDC(HMemDC2);
}
void CreateRandomSqare()
{ 
  //int nIndex=6;
  switch(CurrentIndex)
  { case 0:
        arrSqare[0][0]=1;arrSqare[0][1]=1;arrSqare[0][2]=0;arrSqare[0][3]=0;
		arrSqare[1][0]=0;arrSqare[1][1]=1;arrSqare[1][2]=1;arrSqare[1][3]=0;
		g_nLine=0;
        g_nList=3;
        break;
	case 1:
        arrSqare[0][0]=0;arrSqare[0][1]=1;arrSqare[0][2]=1;arrSqare[0][3]=0;
		arrSqare[1][0]=1;arrSqare[1][1]=1;arrSqare[1][2]=0;arrSqare[1][3]=0;
		g_nLine=0;
        g_nList=3;
        break;
	case 2:
        arrSqare[0][0]=0;arrSqare[0][1]=0;arrSqare[0][2]=1;arrSqare[0][3]=0;
		arrSqare[1][0]=1;arrSqare[1][1]=1;arrSqare[1][2]=1;arrSqare[1][3]=0;
		g_nLine=0;
        g_nList=3;
        break;
	case 3:
        arrSqare[0][0]=1;arrSqare[0][1]=0;arrSqare[0][2]=0;arrSqare[0][3]=0;
		arrSqare[1][0]=1;arrSqare[1][1]=1;arrSqare[1][2]=1;arrSqare[1][3]=0;
		g_nLine=0;
        g_nList=3;
        break;
	case 4:
        arrSqare[0][0]=0;arrSqare[0][1]=1;arrSqare[0][2]=0;arrSqare[0][3]=0;
		arrSqare[1][0]=1;arrSqare[1][1]=1;arrSqare[1][2]=1;arrSqare[1][3]=0;
		g_nLine=0;
        g_nList=3;
        break;
	case 5:
        arrSqare[0][0]=0;arrSqare[0][1]=1;arrSqare[0][2]=1;arrSqare[0][3]=0;
		arrSqare[1][0]=0;arrSqare[1][1]=1;arrSqare[1][2]=1;arrSqare[1][3]=0;
        break;
	case 6:
        arrSqare[0][0]=1;arrSqare[0][1]=1;arrSqare[0][2]=1;arrSqare[0][3]=1;
		arrSqare[1][0]=0;arrSqare[1][1]=0;arrSqare[1][2]=0;arrSqare[1][3]=0;
		g_nLine=0;
        g_nList=4;
        break;
  }
  //GetSqareID=nIndex;
}
void CopyToBack()
{ for(int i=0;i<2;i++)
    for(int j=0;j<4;j++)
	    arrBackGroud[i][j+3]=arrSqare[i][j];
}
void onReturn(HWND hWmd)
{ if(start%2==1)
   SetTimer(hWmd,DEF_TIMER1,500,NULL);
  else
  KillTimer(hWmd,DEF_TIMER1);
  start++;
}
void SqareDown()
{ for(int i=16;i>=0;i--)
     for(int j=0;j<10;j++)
		 if(arrBackGroud[i][j]==1)
		 { arrBackGroud[i+1][j]=1;
           arrBackGroud[i][j]=0;
		 }
}
int CanSqareDown()
{ for(int j=0;j<10;j++)
     if(arrBackGroud[16][j]==1)
		 return 0;
  return 1;
}
void onTimer(HWND hWmd)
{ HDC hDC=GetDC(hWmd);
  if(CanSqareDown()==1&&CanSqareDown2()==1)
   { SqareDown();
     g_nLine++;
   }
  else
  { Change1To2();
    DestroyLine();
	if(CanGameOver(hWmd)==1)
	  KillTimer(hWmd,DEF_TIMER1);
	CurrentIndex=NextIndex;
	CreateRandomSqare();
	CopyToBack();
	NextIndex=rand()%7;
	ShowNext();
  }
  onPaint(hDC);
  ReleaseDC(hWmd,hDC);
}
void Change1To2()
{ for(int i=0;i<17;i++)
     for(int j=0;j<10;j++)
        if(arrBackGroud[i][j]==1)
			arrBackGroud[i][j]=2;
}
void ShowSqare2(HDC HMemDC)
{
  HDC HMemDC2=CreateCompatibleDC(HMemDC);
  HBITMAP hBitmapBack2=(HBITMAP)LoadImage(NULL, "sqare.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);  
  SelectObject(HMemDC2,hBitmapBack2);
  for(int i=0;i<17;i++)
     for(int j=0;j<10;j++)
		 if(arrBackGroud[i][j]==2)
			   BitBlt(HMemDC,253+j*30,31+i*30,30,30,HMemDC2,0,0,SRCCOPY);
 DeleteObject(hBitmapBack2);
 DeleteDC(HMemDC2);

}
int CanSqareDown2()
{ for(int i=16;i>=0;i--)
     for(int j=0;j<10;j++)
       if(arrBackGroud[i][j]==1)
		 if(arrBackGroud[i+1][j]==2)
           return 0;
  return 1;
}
void OnLeft(HWND hWmd)
{ HDC hDC=GetDC(hWmd);
  if(CanSqareLeft()==1&&CanSqareLeft2()==1)
  {SqareLeft();
   g_nList--;
   onPaint(hDC);
  }
  ReleaseDC(hWmd,hDC);
}
void SqareLeft()
{ 
  for(int i=0;i<17;i++)
     for(int j=0;j<10;j++)
		 if(arrBackGroud[i][j]==1)
		 { arrBackGroud[i][j-1]=1;
           arrBackGroud[i][j]=0;
		 }
}
int CanSqareLeft()
{ for(int i=0;i<17;i++)
     if(arrBackGroud[i][0]==1)
		 return 0;
  return 1;
}
int CanSqareLeft2()
{ for(int i=0;i<17;i++)
     for(int j=0;j<10;j++)
       if(arrBackGroud[i][j]==1)
		 if(arrBackGroud[i][j-1]==2)
           return 0;
  return 1;
}
void OnRight(HWND hWmd)
{ HDC hDC=GetDC(hWmd);
  if(CanSqareRight()==1&&CanSqareRight2()==1)
  {SqareRight();
   g_nList++;
   onPaint(hDC);
  }
  ReleaseDC(hWmd,hDC);
}
void SqareRight()
{ 
  for(int i=0;i<17;i++)
     for(int j=9;j>=0;j--)
		 if(arrBackGroud[i][j]==1)
		 { arrBackGroud[i][j+1]=1;
           arrBackGroud[i][j]=0;
		 }
}
int CanSqareRight()
{ for(int i=0;i<17;i++)
     if(arrBackGroud[i][9]==1)
		 return 0;
  return 1;
}
int CanSqareRight2()
{ for(int i=0;i<17;i++)
     for(int j=9;j>=0;j--)
       if(arrBackGroud[i][j]==1)
		 if(arrBackGroud[i][j+1]==2)
           return 0;
  return 1;
}
void OnDown(HWND hWmd)
{ onTimer(hWmd);
}
void OnChangeSqare(HWND hWmd)
{ HDC hDC=GetDC(hWmd);
  switch(CurrentIndex)
  { case 0:      
    case 1:	
	case 2:		 
	case 3:		 
	case 4:
		 if(CanSqareChange()==1)
	      Change();
		 else return;
         break;
	case 5:
         return;
	case 6:
 		 if(CanLineChange()==1)
  		 RectChange();
		 else return;
         break;
	default:break;
  }
  onPaint(hDC);
  ReleaseDC(hWmd,hDC);
}
void Change()
{ char Sqare[3][3]={0};
  int t=2;
  for(int i=0;i<3;i++)
	  for(int j=0;j<3;j++)
		  Sqare[i][j]=arrBackGroud[g_nLine+i][g_nList+j];
  for(int i=0;i<3;i++)
	  {for(int j=0;j<3;j++)
         {arrBackGroud[g_nLine+i][g_nList+j]=Sqare[t][i];
          t--;
         }
        t=2;
	   }
}
int CanSqareChange()
{ 
  for(int i=0;i<3;i++)
	 for(int j=0;j<3;j++)
		if(arrBackGroud[g_nLine+i][g_nList+j]==2)
			return 0;
 if(g_nList<0)
	 g_nList=0;
 else if(g_nList+2>9)
	 g_nList=7;
 return 1;
}
void RectChange()
  { if(arrBackGroud[g_nLine][g_nList-1]==1)
   { arrBackGroud[g_nLine][g_nList-1]=0;
     arrBackGroud[g_nLine][g_nList+1]=0;
	 arrBackGroud[g_nLine][g_nList+2]=0;
	 if(arrBackGroud[g_nLine+1][g_nList]==2)
	 {arrBackGroud[g_nLine-1][g_nList]=1;
      arrBackGroud[g_nLine-2][g_nList]=1;
	  arrBackGroud[g_nLine-3][g_nList]=1;
	 }
	 else if(arrBackGroud[g_nLine+2][g_nList]==2)
	 {arrBackGroud[g_nLine-2][g_nList]=1;
      arrBackGroud[g_nLine-1][g_nList]=1;
	  arrBackGroud[g_nLine+1][g_nList]=1;
	 }
	 else if(g_nLine==0)
	 {arrBackGroud[g_nLine+1][g_nList]=1;
      arrBackGroud[g_nLine+2][g_nList]=1;
	  arrBackGroud[g_nLine+3][g_nList]=1;
	  g_nLine=g_nLine+1;
	 }
	 else
	 {
	 arrBackGroud[g_nLine-1][g_nList]=1;
     arrBackGroud[g_nLine+1][g_nList]=1;
	 arrBackGroud[g_nLine+2][g_nList]=1;
	 }
   }

  else if(arrBackGroud[g_nLine-1][g_nList]==1)
  { arrBackGroud[g_nLine-1][g_nList]=0;
    arrBackGroud[g_nLine+1][g_nList]=0;
	arrBackGroud[g_nLine+2][g_nList]=0;
	if(arrBackGroud[g_nLine][g_nList+1]==2||g_nList==9)
	 {arrBackGroud[g_nLine][g_nList-1]=1;
      arrBackGroud[g_nLine][g_nList-2]=1;
	  arrBackGroud[g_nLine][g_nList-3]=1;
	  g_nList=g_nList-2;
	 }
	 else if(arrBackGroud[g_nLine][g_nList+2]==2||g_nList==8)
	 {arrBackGroud[g_nLine][g_nList-2]=1;
      arrBackGroud[g_nLine][g_nList-1]=1;
	  arrBackGroud[g_nLine][g_nList+1]=1;
	  g_nList=g_nList-1;
	 }
	 else if(arrBackGroud[g_nLine][g_nList-1]==2||g_nList==0)
	 {
	 arrBackGroud[g_nLine][g_nList+1]=1;
     arrBackGroud[g_nLine][g_nList+2]=1;
	 arrBackGroud[g_nLine][g_nList+3]=1;
	 g_nList=g_nList+1;
	 }
	else
	{
	arrBackGroud[g_nLine][g_nList-1]=1;
    arrBackGroud[g_nLine][g_nList+1]=1;
	arrBackGroud[g_nLine][g_nList+2]=1;
	}
  }
}
int CanLineChange()
{ 
  int i,j;
  for(i=1;i<4;i++)
	  if(arrBackGroud[g_nLine][g_nList+i]==2||arrBackGroud[g_nLine][g_nList+i]>9)
		  break;
  for(j=1;j<4;j++)
	  if(arrBackGroud[g_nLine][g_nList-j]==2||arrBackGroud[g_nLine][g_nList-j]<0)
		  break;
  if((i-1+j-1)<3)
	  return 0;
  return 1;
}
void DestroyLine()
{ int sum=0;
  int temp=0;
  for(int i=16;i>=0;i--)
    {for(int j=0;j<10;j++)
		sum+=arrBackGroud[i][j];
     if(sum==20)
	 { for(temp=i-1;temp>=0;temp--)
	      for(int k=0;k<10;k++)
			  arrBackGroud[temp+1][k]=arrBackGroud[temp][k];
	   i=17;
	   Score+=10;
	 }
	 sum=0;
  }
}
void ShowScore(HDC hMemDC)
{  static HFONT hFont;
  hFont = CreateFont(
                -20/*高度*/, -10/*宽度*/, 0, 0, 400 /*一般这个值设为400*/,
                FALSE/*不带斜体*/, FALSE/*不带下划线*/, FALSE/*不带删除线*/,
                DEFAULT_CHARSET,  //使用默认字符集
                OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS,  //这行参数不用管
                DEFAULT_QUALITY,  //默认输出质量
                FF_DONTCARE,  //不指定字体族*/
                TEXT("华康娃娃体W5")  //字体名
            );
  SelectObject(hMemDC,hFont);
 char strScore[10]={0};
 itoa(Score,strScore,10);
 int mode = SetBkMode(hMemDC, TRANSPARENT);//设置为透明模式
    RECT rect = { 670, 310, 720, 350 };
    //在矩形中心绘制文字
    DrawText(hMemDC,strScore , -1, &rect, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
    SetBkMode(hMemDC, mode);
}
int CanGameOver(HWND hWmd)
{ for(int j=0;j<10;j++)
    if(arrBackGroud[0][j]==2)
      {MessageBox(hWmd,"       游戏结束","提示",MB_OK);
       return 1;
      }
   return 0;
}
void ShowNext()
{ 
  switch(NextIndex)
  { case 0:
        NextSqare[0][0]=1;NextSqare[0][1]=1;NextSqare[0][2]=0;NextSqare[0][3]=0;
		NextSqare[1][0]=0;NextSqare[1][1]=1;NextSqare[1][2]=1;NextSqare[1][3]=0;
		
        break;
	case 1:
        NextSqare[0][0]=0;NextSqare[0][1]=1;NextSqare[0][2]=1;NextSqare[0][3]=0;
		NextSqare[1][0]=1;NextSqare[1][1]=1;NextSqare[1][2]=0;NextSqare[1][3]=0;
		
        break;
	case 2:
        NextSqare[0][0]=0;NextSqare[0][1]=0;NextSqare[0][2]=1;NextSqare[0][3]=0;
		NextSqare[1][0]=1;NextSqare[1][1]=1;NextSqare[1][2]=1;NextSqare[1][3]=0;
		
        break;
	case 3:
        NextSqare[0][0]=1;NextSqare[0][1]=0;NextSqare[0][2]=0;NextSqare[0][3]=0;
		NextSqare[1][0]=1;NextSqare[1][1]=1;NextSqare[1][2]=1;NextSqare[1][3]=0;
		
        break;
	case 4:
        NextSqare[0][0]=0;NextSqare[0][1]=1;NextSqare[0][2]=0;NextSqare[0][3]=0;
		NextSqare[1][0]=1;NextSqare[1][1]=1;NextSqare[1][2]=1;NextSqare[1][3]=0;
		
        break;
	case 5:
        NextSqare[0][0]=0;NextSqare[0][1]=1;NextSqare[0][2]=1;NextSqare[0][3]=0;
		NextSqare[1][0]=0;NextSqare[1][1]=1;NextSqare[1][2]=1;NextSqare[1][3]=0;
        break;
	case 6:
        NextSqare[0][0]=1;NextSqare[0][1]=1;NextSqare[0][2]=1;NextSqare[0][3]=1;
		NextSqare[1][0]=0;NextSqare[1][1]=0;NextSqare[1][2]=0;NextSqare[1][3]=0;
        break;
  }
}
void ShowLines(HDC hMemDC)
{ Lines=0;
 static HFONT hFont;
  for(int i=16;i>=0;i--)
     {for(int j=0;j<10;j++)
	   if(arrBackGroud[i][j]==2)
	     {Lines+=1;
          break;}
      continue;
     }
  hFont = CreateFont(
                -20/*高度*/, -10/*宽度*/, 0, 0, 400 /*一般这个值设为400*/,
                FALSE/*不带斜体*/, FALSE/*不带下划线*/, FALSE/*不带删除线*/,
                DEFAULT_CHARSET,  //使用默认字符集
                OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS,  //这行参数不用管
                DEFAULT_QUALITY,  //默认输出质量
                FF_DONTCARE,  //不指定字体族*/
                TEXT("华康娃娃体W5")  //字体名
            );
  SelectObject(hMemDC,hFont);
 char strScore[10]={0};
 itoa(Lines,strScore,10);
 int mode = SetBkMode(hMemDC, TRANSPARENT);//设置为透明模式
 RECT rect = { 670,380,720,420 };
    //在矩形中心绘制文字
 DrawText(hMemDC,strScore , -1, &rect, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
 SetBkMode(hMemDC, mode);
}
void ClearScreen()
{ for(int i=0;i<16;i++)
    for(int j=0;j<10;j++)
		arrBackGroud[i][j]=0;
  for(int i=0;i<2;i++)
	  for(int j=0;j<4;j++)
		  NextSqare[i][j]=0;
}