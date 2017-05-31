#include <Windows.h>
#include "res.h"
#include <ctime>
#include <cstdlib>
#include <cstdio>

bool isGameOn = false;  //czy gra zosta³a zaczêta
bool isFirstPlayerTurn = true;  //czyj ruch
bool isFieldOccupiedByFirstPlayer[3][3];
bool isFieldOccupiedBySecondPlayer[3][3];
bool isDraw = false;  //czy remis
int lRuch;  //liczba wykonanych ruchów
int pole;   //oznaczenie pustego pola na planszy
int lRuchPC = 0;    //liczba wykonanych ruchów w grze z komputerem
int a = 0;
int tab2[3][3] = { {234, 45, 124},
                  {547, 67, 34},
                  {678, 768, 435} };
int tab[9] = {234, 45, 124, 547, 67, 34, 678, 768, 435};
//
//Funkcja okreœlaj¹ca warunki wygrania gracza X
//
bool CheckWinningConditionX()
{
  if (
    //sprawdzenie poziomo
    tab2[0][0] == tab2[0][1] && tab2[0][1] == tab2[0][2] ||
    tab2[1][0] == tab2[1][1] && tab2[1][1] == tab2[1][2] ||
    tab2[2][0] == tab2[1][1] && tab2[1][1] == tab2[2][2] ||
    //sprawdzenie pionowo
    tab2[0][0] == tab2[1][0] && tab2[1][0] == tab2[2][0] ||
    tab2[0][1] == tab2[1][1] && tab2[1][1] == tab2[2][1] ||
    tab2[0][2] == tab2[1][2] && tab2[1][2] == tab2[2][2] ||
    //sprawdzenie na ukos
    tab2[0][0] == tab2[1][1] && tab2[1][1] == tab2[2][2] ||
    tab2[0][2] == tab2[1][1] && tab2[1][1] == tab2[2][0]
    )
    return true;
  else
  {
    lRuch++;
    if (lRuch == 9) isDraw = true;
    return false;
  }
  //return false;
}
//
//Funkcja okreœlaj¹ca warunki wygrania gracza O
//
/*bool CheckWinningConditionO()
{
  lRuchPC++;
  if (
    //sprawdzenie poziomo
    isFieldOccupiedBySecondPlayer[0][0] == isFieldOccupiedBySecondPlayer[0][1] && isFieldOccupiedBySecondPlayer[0][1] == isFieldOccupiedBySecondPlayer[0][2] ||
    isFieldOccupiedBySecondPlayer[1][0] == isFieldOccupiedBySecondPlayer[1][1] && isFieldOccupiedBySecondPlayer[1][1] == isFieldOccupiedBySecondPlayer[1][2] ||
    isFieldOccupiedBySecondPlayer[2][0] == isFieldOccupiedBySecondPlayer[2][1] && isFieldOccupiedBySecondPlayer[2][1] == isFieldOccupiedBySecondPlayer[2][2] ||
    //sprawdzenie pionowo
    isFieldOccupiedBySecondPlayer[0][0] == isFieldOccupiedBySecondPlayer[1][0] && isFieldOccupiedBySecondPlayer[1][0] == isFieldOccupiedBySecondPlayer[2][0] ||
    isFieldOccupiedBySecondPlayer[0][1] == isFieldOccupiedBySecondPlayer[1][1] && isFieldOccupiedBySecondPlayer[1][1] == isFieldOccupiedBySecondPlayer[2][1] ||
    isFieldOccupiedBySecondPlayer[0][2] == isFieldOccupiedBySecondPlayer[1][2] && isFieldOccupiedBySecondPlayer[1][2] == isFieldOccupiedBySecondPlayer[2][2] ||
    //sprawdzenie na ukos
    isFieldOccupiedBySecondPlayer[0][0] == isFieldOccupiedBySecondPlayer[1][1] && isFieldOccupiedBySecondPlayer[1][1] == isFieldOccupiedBySecondPlayer[2][2] ||
    isFieldOccupiedBySecondPlayer[0][2] == isFieldOccupiedBySecondPlayer[1][1] && isFieldOccupiedBySecondPlayer[1][1] == isFieldOccupiedBySecondPlayer[2][0]
    )
    return true;
  else
  {
    lRuch++;
    if (lRuch == 9) isDraw = true;
    return false;
  }
  //return false;
}
*/
//
//Funkcja czyszcz¹ca planszê po zakoñczeniu rozgrywki
//
void Clean_field(HWND hwndDlg) 
{
  for (int i = 0; i < 9; i++) 
  {
    HWND hwndButton = GetDlgItem(hwndDlg, IDC_BUTTON1 + i);
    CHAR szText[500];
    wsprintf(szText, "");
    SetWindowText(hwndButton, szText);
    for (int i = 0; i < 9; i++) { tab[i] = 100 + i; }
  }
}

void drawBoard(HDC hdc) 
{
  //linie pionowe
  MoveToEx(hdc, 100, 30, NULL);
  LineTo(hdc, 100, 240);
  MoveToEx(hdc, 180, 30, NULL);
  LineTo(hdc, 180, 240);
  //linie poziome
  MoveToEx(hdc, 40, 100, NULL);
  LineTo(hdc, 240, 100);
  MoveToEx(hdc, 40, 180, NULL);
  LineTo(hdc, 240, 180);
}
void drawX(HDC hdc, int x, int y) 
{
  MoveToEx(hdc, x - 30, y - 30, NULL);
  LineTo(hdc, x + 30, y + 30);
  MoveToEx(hdc, x - 30, y + 30, NULL);
  LineTo(hdc, x + 30, y - 30);
}
void drawO(HDC hdc, int x, int y) 
{
  Rectangle(hdc, x - 30, y - 30, x + 30, y + 30);
  /*
  MoveToEx(hdc, x - 30, y - 30, NULL);
  LineTo(hdc, x + 30, y - 30);
  MoveToEx(hdc, x - 30, y + 30, NULL);
  LineTo(hdc, x + 30, y + 30);
  MoveToEx(hdc, x - 30, y - 30, NULL);
  LineTo(hdc, x - 30, y + 30);
  MoveToEx(hdc, x + 30, y + 30, NULL);
  LineTo(hdc, x + 30, y - 30);
  */
}

INT_PTR CALLBACK DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) 
{
  switch (uMsg)
  {
    case WM_COMMAND:
      switch (HIWORD(wParam))
      {
      case BN_CLICKED:    //zdarzenie klikniêcia
        switch (LOWORD(wParam))
        {
        case IDC_BUTTON_START:
          if (isGameOn == false)
          {
            isGameOn = true;
            //czyszczenie tablicy pól
            a = 0;
            for (int i = 0; i < 3; i++)
              for (int j = 0; j < 3; j++)
                tab2[i][j] = a++;
            isDraw = false;
            lRuch = 0;
            CheckRadioButton(hwndDlg, IDC_RADIO1, IDC_RADIO2, IDC_RADIO1);
            HWND hwndStatic = GetDlgItem(hwndDlg, IDC_STATIC_SHOW);
            CHAR szText[500];
            wsprintf(szText, "Gra rozpoczêta");
            SetWindowText(hwndStatic, szText);
            //Clean_field(hwndDlg);
            HWND hwndButtonStart = GetDlgItem(hwndDlg, IDC_BUTTON_START);
            wsprintf(szText, "Stop");
            SetWindowText(hwndButtonStart, szText);

            //Rysowanie kolorowej siatki gry
            HDC hdc = GetDC(hwndDlg);
            HPEN hMyPen = CreatePen(PS_SOLID, 5, RGB(0, 0, 255));
            SelectObject(hdc, hMyPen);
            drawBoard(hdc);
            DeleteObject(hMyPen);
            //TextOut(hdc, 0, 0, szText, strlen(szText));
            ReleaseDC(hwndDlg, hdc);

            for (int i = 0; i < 3; i++) 
            {
              for (int j = 0; j < 3; j++) 
              {
                isFieldOccupiedByFirstPlayer[i][j] = false;
                isFieldOccupiedBySecondPlayer[i][j] = false;
              }
            }
          }
          else
          {
            isGameOn = false;
            HWND hwndButton_start = GetDlgItem(hwndDlg, IDC_BUTTON_START);
            HWND hwndStatic = GetDlgItem(hwndDlg, IDC_STATIC_SHOW);
            CHAR szText[500];
            wsprintf(szText, "gra wstrzymana");
            SetWindowText(hwndStatic, szText);
            wsprintf(szText, "Start");
            SetWindowText(hwndButton_start, szText);
          }
        }
        return TRUE;
      }
      return FALSE;

    case WM_LBUTTONDOWN: {
      //CHAR szText[200];
      if (isGameOn == true)
      {
        int x = LOWORD(lParam); int y = HIWORD(lParam);
        if ((x > 30 && x < 240) && (y > 30 && y < 240))
        {
          int fieldX = (x - 10) / 80;
          int fieldY = (y - 10) / 80;
          if ((isFieldOccupiedByFirstPlayer[fieldX][fieldY] == false) &&
            (isFieldOccupiedBySecondPlayer[fieldX][fieldY] == false))
          {
            x = fieldX * 80 + 60; 
            y = fieldY * 80 + 60;
            HDC hdc = GetDC(hwndDlg);
            if (isFirstPlayerTurn == true)
            {
              drawX(hdc, x, y);
              isFieldOccupiedByFirstPlayer[fieldX][fieldY] = true;
              tab2[fieldX][fieldY] = 'X';
              CheckRadioButton(hwndDlg, IDC_RADIO1, IDC_RADIO2, IDC_RADIO2);

              if (CheckWinningConditionX()) 
              {
                HWND hwndStatic = GetDlgItem(hwndDlg, IDC_STATIC_SHOW);
                CHAR szText[500];
                wsprintf(szText, "Wygrana X, aby zacz¹æ od nowa, wciœnij start");
                SetWindowText(hwndStatic, szText);
                isGameOn = false;
                HWND hwndButton_start = GetDlgItem(hwndDlg, IDC_BUTTON_START);
                wsprintf(szText, "Start");
                SetWindowText(hwndButton_start, szText);
              }
              else if (isDraw)
              {
                HWND hwndStatic = GetDlgItem(hwndDlg, IDC_STATIC_SHOW);
                CHAR szText[500];
                wsprintf(szText, "Remis,aby zacz¹æ od nowa, wciœnij start");
                SetWindowText(hwndStatic, szText);
                isGameOn = false;
                HWND hwndButton_start = GetDlgItem(hwndDlg, IDC_BUTTON_START);
                wsprintf(szText, "Start");
                SetWindowText(hwndButton_start, szText);
              }
            }
            else
            {
              drawO(hdc, x, y);
              tab2[fieldX][fieldY] = 'O';
              isFieldOccupiedBySecondPlayer[fieldX][fieldY] = true;
              CheckRadioButton(hwndDlg, IDC_RADIO1, IDC_RADIO2, IDC_RADIO1);

              if (CheckWinningConditionX())
              {
                HWND hwndStatic = GetDlgItem(hwndDlg, IDC_STATIC_SHOW);
                CHAR szText[500];
                wsprintf(szText, "Wygrana O, aby zacz¹æ od nowa, wciœnij start");
                SetWindowText(hwndStatic, szText);
                isGameOn = false;
                HWND hwndButton_start = GetDlgItem(hwndDlg, IDC_BUTTON_START);
                wsprintf(szText, "Start");
                SetWindowText(hwndButton_start, szText);
              }
              else if (isDraw)
              {
                HWND hwndStatic = GetDlgItem(hwndDlg, IDC_STATIC_SHOW);
                CHAR szText[500];
                wsprintf(szText, "Remis,aby zacz¹æ od nowa, wciœnij start");
                SetWindowText(hwndStatic, szText);
                isGameOn = false;
                HWND hwndButton_start = GetDlgItem(hwndDlg, IDC_BUTTON_START);
                wsprintf(szText, "Start");
                SetWindowText(hwndButton_start, szText);
              }
            }
            ReleaseDC(hwndDlg, hdc);
            isFirstPlayerTurn = !isFirstPlayerTurn; //prze³¹czanie graczy
          }
        }
      }
    }
      return TRUE;

    case WM_PAINT:
    {
      HDC hdc = GetDC(hwndDlg);
      HPEN hMyPen = CreatePen(PS_SOLID, 5, RGB(255, 0, 255));
      SelectObject(hdc, hMyPen);
      drawBoard(hdc);
      /*for (int iFieldX = 0; iFieldX < 3; iFieldX++)
      {
        for (int iFieldY = 0; iFieldY < 3; iFieldY++)
        {
          if (isFieldOccupiedByFirstPlayer[iFieldX][iFieldY] == true)
          {
            drawX(hdc, iFieldX, iFieldY);
          }
          if (isFieldOccupiedBySecondPlayer[iFieldX][iFieldY] == true)
          {
            drawO(hdc, iFieldX, iFieldY);
          }
        }
      }*/
      DeleteObject(hMyPen);
      ReleaseDC(hwndDlg, hdc);
    }
      return TRUE;

    case WM_CLOSE:  //komunikat zamkniêcia okienka
    {
      DestroyWindow(hwndDlg);
      PostQuitMessage(0);
      return TRUE; 
    }
  }
  return FALSE;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow) 
{
  HWND hwndMainWindow = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_MAINVIEW), NULL, DialogProc);
  ShowWindow(hwndMainWindow, iCmdShow); 
  srand(time(NULL));
  MSG msg = {};
  while (GetMessage(&msg, NULL, 0, 0)) 
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  return 0;
}