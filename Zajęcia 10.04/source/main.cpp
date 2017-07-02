#include <Windows.h>
#include "res.h"

bool isGameOn = false;  //czy gra zosta砤 zacz阾a
bool isFirstPlayerTurn = true;  //czyj ruch
bool isFieldOccupiedByFirstPlayer[3][3];
bool isFieldOccupiedBySecondPlayer[3][3];
bool isDraw = false;  //czy remis
int lRuch;  //liczba wykonanych ruch體

int a = 0;
int tab[3][3] = {   { 234, 45, 124 },
                    { 547, 67, 34 },
                    { 678, 768, 435 } };


HBITMAP hBitmapGameBoard;
HBITMAP hBitmapX;
HBITMAP hBitmapO;
HBITMAP hBitmapStart;
HBITMAP hBitmapReset;
HINSTANCE hInst;
bool CheckWinningCondition()
{
  if (
    //sprawdzenie poziomo
    tab[0][0] == tab[0][1] && tab[0][1] == tab[0][2] ||
    tab[1][0] == tab[1][1] && tab[1][1] == tab[1][2] ||
    tab[2][0] == tab[2][1] && tab[2][1] == tab[2][2] ||
    //sprawdzenie pionowo
    tab[0][0] == tab[1][0] && tab[1][0] == tab[2][0] ||
    tab[0][1] == tab[1][1] && tab[1][1] == tab[2][1] ||
    tab[0][2] == tab[1][2] && tab[1][2] == tab[2][2] ||
    //sprawdzenie na ukos
    tab[0][0] == tab[1][1] && tab[1][1] == tab[2][2] ||
    tab[0][2] == tab[1][1] && tab[1][1] == tab[2][0]
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
void DrawBitmap(HDC hdc)
{
  HDC hDCBitmap;
  hDCBitmap = CreateCompatibleDC(hdc);
  SelectObject(hDCBitmap, hBitmapGameBoard);
  BitBlt(hdc, 0, 0, 236, 217, hDCBitmap, 0, 0, SRCCOPY);
  DeleteDC(hDCBitmap);
}
void DrawX(HDC hdc, int x, int y)
{
  HDC hDCBitmap;
  hDCBitmap = CreateCompatibleDC(hdc);
  SelectObject(hDCBitmap, hBitmapX);
  BitBlt(hdc, x, y, 67, 75, hDCBitmap, 0, 0, SRCCOPY);
  DeleteDC(hDCBitmap);
}
void DrawO(HDC hdc, int x, int y)
{
  HDC hDCBitmap;
  hDCBitmap = CreateCompatibleDC(hdc);
  SelectObject(hDCBitmap, hBitmapO);
  BitBlt(hdc, x, y, 57, 54, hDCBitmap, 0, 0, SRCCOPY);
  DeleteDC(hDCBitmap);
}

LRESULT CALLBACK ButtonWndProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  switch (uMsg)
  {
  case WM_PAINT:
  {
    HDC hdc = GetDC(hwndDlg);
    DrawBitmap(hdc);
    /*HDC hDCBitmap;
    hDCBitmap = CreateCompatibleDC(hdc);
    SelectObject(hDCBitmap, hBitmapGameBoard);
    BitBlt(hdc, 0, 0, 236, 217, hDCBitmap, 0, 0, SRCCOPY);
    DeleteDC(hDCBitmap);*/
    ReleaseDC(hwndDlg, hdc);
  }
  return 0;
  default:
    return DefWindowProc(hwndDlg, uMsg, wParam, lParam);
    //return CallWindowProc(wpOrgButtonProc, hwnd, uMsg, wParam, lParam);
  }
}

INT_PTR CALLBACK DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  switch (uMsg)
  {
    case WM_INITDIALOG:
    {
      hBitmapGameBoard = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_PLANSZA));
      hBitmapX = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_X));
      hBitmapO = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_O));
      hBitmapStart = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_START));
      hBitmapReset = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_RESET));

      HWND hwndButton = GetDlgItem(hwndDlg, IDC_BUTTON_START);
      WNDPROC wpOrgButtonProc = (WNDPROC)SetWindowLong(hwndButton, -4, (LONG)ButtonWndProc);
    }
    return TRUE;

    case WM_COMMAND:
    {
      switch (HIWORD(wParam))
      {
      case BN_CLICKED:    //zdarzenie klikni阠ia
        switch (LOWORD(wParam))
        {
        case IDC_BUTTON_START:
          if (isGameOn == false)
          {
            isGameOn = true; 
            a = 0;
            for (int i = 0; i < 3; i++)
              for (int j = 0; j < 3; j++)
                tab[i][j] = a++;
            isDraw = false;
            lRuch = 0;
            CheckRadioButton(hwndDlg, IDC_RADIO1, IDC_RADIO2, IDC_RADIO1);
            CHAR szText[500];
            HWND hwndStatic = GetDlgItem(hwndDlg, IDC_STATIC_SHOW);
            wsprintf(szText, "Gra rozpocz阾a");
            SetWindowText(hwndStatic, szText);
            HWND hwndButtonStart = GetDlgItem(hwndDlg, IDC_BUTTON_START);
            wsprintf(szText, "Stop");
            SetWindowText(hwndButtonStart, szText);

            //Rysowanie siatki gry
            HDC hdc = GetDC(hwndDlg);
            DrawBitmap(hdc);
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
            HWND hwndStatic = GetDlgItem(hwndDlg, IDC_STATIC_SHOW);
            HWND hwndButtonStart = GetDlgItem(hwndDlg, IDC_BUTTON_START);
            CHAR szText[500];
            wsprintf(szText, "Gra wstrzymana");
            SetWindowText(hwndStatic, szText);
            wsprintf(szText, "Start");
            SetWindowText(hwndButtonStart, szText);
          }
        }
        return TRUE;
      }
    }
    return FALSE;

    case WM_LBUTTONDOWN: {
      //CHAR szText[200];
      if (isGameOn == true)
      {
        int x = LOWORD(lParam); int y = HIWORD(lParam);
        if ((x > 0 && x < 236) && (y > 0 && y < 217))
        {
          int fieldX = (x - 0) / 79;
          int fieldY = (y - 0) / 72;
          if ((isFieldOccupiedByFirstPlayer[fieldX][fieldY] == false) &&
            (isFieldOccupiedBySecondPlayer[fieldX][fieldY] == false))
          {
            x = fieldX * 79 + 79 / 2;
            y = fieldY * 72 + 72 / 2;
            HDC hdc = GetDC(hwndDlg);
            if (isFirstPlayerTurn == true)
            {
              DrawX(hdc, x - 34, y - 38);
              isFieldOccupiedByFirstPlayer[fieldX][fieldY] = true;
              tab[fieldX][fieldY] = 'X';
              CheckRadioButton(hwndDlg, IDC_RADIO1, IDC_RADIO2, IDC_RADIO2);
              if (CheckWinningCondition()) 
              {
                HWND hwndStatic = GetDlgItem(hwndDlg, IDC_STATIC_SHOW);
                CHAR szText[500];
                wsprintf(szText, "Wygrana X, aby zacz规 od nowa, wci渘ij start");
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
                wsprintf(szText, "Remis,aby zacz规 od nowa, wci渘ij start");
                SetWindowText(hwndStatic, szText);
                isGameOn = false;
                HWND hwndButton_start = GetDlgItem(hwndDlg, IDC_BUTTON_START);
                wsprintf(szText, "Start");
                SetWindowText(hwndButton_start, szText);
              }
            }
            else
            {
              DrawO(hdc, x - 29, y - 27);
              isFieldOccupiedBySecondPlayer[fieldX][fieldY] = true;
              tab[fieldX][fieldY] = 'O';
              CheckRadioButton(hwndDlg, IDC_RADIO1, IDC_RADIO2, IDC_RADIO1);
              if (CheckWinningCondition())
              {
                HWND hwndStatic = GetDlgItem(hwndDlg, IDC_STATIC_SHOW);
                CHAR szText[500];
                wsprintf(szText, "Wygrana O, aby zacz规 od nowa, wci渘ij start");
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
                wsprintf(szText, "Remis,aby zacz规 od nowa, wci渘ij start");
                SetWindowText(hwndStatic, szText);
                isGameOn = false;
                HWND hwndButton_start = GetDlgItem(hwndDlg, IDC_BUTTON_START);
                wsprintf(szText, "Start");
                SetWindowText(hwndButton_start, szText);
              }
            }
            ReleaseDC(hwndDlg, hdc);
            isFirstPlayerTurn = !isFirstPlayerTurn; //prze彻czanie graczy
          }
        }
      }
    }
      return TRUE;

    case WM_PAINT:
    {
      HDC hdc = GetDC(hwndDlg);
      DrawBitmap(hdc);
  /*
      for (int iFieldX = 0; iFieldX < 3; iFieldX++)
      {
        for (int iFieldY = 0; iFieldY < 3; iFieldY++)
        {
          if (isFieldOccupiedByFirstPlayer[iFieldX][iFieldY] == true)
          {
            DrawX(hdc, iFieldX, iFieldY);
          }
          if (isFieldOccupiedBySecondPlayer[iFieldX][iFieldY] == true)
          {
            DrawO(hdc, iFieldX, iFieldY);
          }
        }
      }*/
      ReleaseDC(hwndDlg, hdc);
      return DefWindowProc(hwndDlg, uMsg, wParam, lParam);
    }
    return TRUE;

    case WM_CLOSE: //komunikat zamkni阠ia okienka
    {
      DestroyWindow(hwndDlg);
      PostQuitMessage(0);
      for (int i = 0; i < 5; i++) { DeleteObject(hBitmapGameBoard + i); }
      return TRUE;
    }
  }
  return FALSE;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
  hInst = hInstance;
  HWND hwndMainWindow = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_MAINVIEW), NULL, DialogProc);
  ShowWindow(hwndMainWindow, iCmdShow);
  MSG msg = {};
  while (GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  return 0;
}