#include<windows.h>
#include<time.h>
#define DEF_TIMER1 1234
void onPaint(HDC hDC);
void onCreate();
void onReturn(HWND hWmd);
void onTimer(HWND hWmd);
void OnLeft(HWND hWmd);
void OnRight(HWND hWmd);
void OnDown(HWND hWmd);
void OnChangeSqare(HWND hWmd);

void PaintSqare(HDC HMemDC);
void CopyToBack();
void SqareDown();
void Change1To2();
void ShowSqare2(HDC hMemDC);
void SqareLeft();
void SqareRight();
void Change();
void RectChange();
void DestroyLine();
void ShowScore(HDC hMemDC);
void ShowNext();
void ShowLines(HDC hMemDC);
void CreateRandomSqare();
void ClearScreen();

int CanSqareDown();
int CanSqareDown2();
int CanSqareLeft();
int CanSqareLeft2();
int CanSqareRight();
int CanSqareRight2();
int CanSqareChange();
int CanLineChange();
int CanGameOver(HWND hWmd);

