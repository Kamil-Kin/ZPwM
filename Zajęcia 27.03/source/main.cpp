#include <Windows.h>
#include "res.h"

bool isGameOn = false;  //czy gra zosta³a zaczêta
bool isFirstPlayerTurn = true;  //czyj ruch
bool isFieldOccupiedByFirstPlayer[3][3];
bool isFieldOccupiedBySecondPlayer[3][3];
//bool isDraw = false;  //czy remis
int lRuch;  //liczba wykonanych ruchów
//bool isWithPC = false;  //czy gra z komputerem

//int tab[9] = { 234, 45, 124, 547, 67, 34, 678, 768, 435 };
//Funkcja okreœlaj¹ca warunki wygrania rozgrywki
/*bool CheckWinningCondition(HWND hwndDlg, HWND lParam, int znak)
{
  HWND hwndButton1 = GetDlgItem(hwndDlg, IDC_BUTTON1);
  HWND hwndButton2 = GetDlgItem(hwndDlg, IDC_BUTTON2);
  HWND hwndButton3 = GetDlgItem(hwndDlg, IDC_BUTTON3);
  HWND hwndButton4 = GetDlgItem(hwndDlg, IDC_BUTTON4);
  HWND hwndButton5 = GetDlgItem(hwndDlg, IDC_BUTTON5);
  HWND hwndButton6 = GetDlgItem(hwndDlg, IDC_BUTTON6);
  HWND hwndButton7 = GetDlgItem(hwndDlg, IDC_BUTTON7);
  HWND hwndButton8 = GetDlgItem(hwndDlg, IDC_BUTTON8);
  HWND hwndButton9 = GetDlgItem(hwndDlg, IDC_BUTTON9);
  if (znak == 0)
  {
    if (hwndButton1 == lParam) tab[0] = 0;
    if (hwndButton2 == lParam) tab[1] = 0;
    if (hwndButton3 == lParam) tab[2] = 0;
    if (hwndButton4 == lParam) tab[3] = 0;
    if (hwndButton5 == lParam) tab[4] = 0;
    if (hwndButton6 == lParam) tab[5] = 0;
    if (hwndButton7 == lParam) tab[6] = 0;
    if (hwndButton8 == lParam) tab[7] = 0;
    if (hwndButton9 == lParam) tab[8] = 0;
  }
  else if (znak == 1)
  {
    if (hwndButton1 == lParam) tab[0] = 1;
    if (hwndButton2 == lParam) tab[1] = 1;
    if (hwndButton3 == lParam) tab[2] = 1;
    if (hwndButton4 == lParam) tab[3] = 1;
    if (hwndButton5 == lParam) tab[4] = 1;
    if (hwndButton6 == lParam) tab[5] = 1;
    if (hwndButton7 == lParam) tab[6] = 1;
    if (hwndButton8 == lParam) tab[7] = 1;
    if (hwndButton9 == lParam) tab[8] = 1;
  }

  if (tab[0] == tab[1] && tab[1] == tab[2]
    || tab[3] == tab[4] && tab[4] == tab[5]
    || tab[6] == tab[7] && tab[7] == tab[8]
    || tab[0] == tab[3] && tab[3] == tab[6]
    || tab[1] == tab[4] && tab[4] == tab[7]
    || tab[2] == tab[5] && tab[5] == tab[8]
    || tab[0] == tab[4] && tab[4] == tab[8]
    || tab[2] == tab[4] && tab[4] == tab[6])
    if (((tab[3 * i] == tab[3 * i + 1]) && (tab[3 * i + 1] == tab[3 * i + 2])) ||
    ((tab[i] == tab[i + 3]) && (tab[i + 3] == tab[i + 6])) ||
    ((tab[0] == tab[4] && tab[0] == tab[8])) || ((tab[2] == tab[4] && tab[2] == tab[6])))
    return true;
  else
  {
    lRuch++;
    if (lRuch == 9) isDraw = true;
    return false;
  }
  return false;
}*/

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
          HWND hwndStatic = GetDlgItem(hwndDlg, IDC_STATIC1);
          CHAR szText[500];
          wsprintf(szText, "Start");
          SetWindowText(hwndStatic, szText);
          for (int i = 0; i < 9; i++)
          {
            HWND hwndButton = GetDlgItem(hwndDlg, IDC_BUTTON1 + i);
            CHAR szText[500];
            wsprintf(szText, "");
            SetWindowText(hwndButton, szText);
          }
          HWND hwndButtonStart = GetDlgItem(hwndDlg, IDC_BUTTON_START);
          wsprintf(szText, "Stop");
          SetWindowText(hwndButtonStart, szText);

          //Rysowanie siatki gry
          HDC hdc = GetDC(hwndDlg);
          //LineTo
          //MovetoEx
          //Rectangle
          //TextOut
          //GetPixel
          //SetPixel
          HPEN hMyPen = CreatePen(PS_SOLID, 5, RGB(255, 255, 0));
          SelectObject(hdc, hMyPen);

          MoveToEx(hdc, 100, 30, NULL);
          LineTo(hdc, 100, 230);
          MoveToEx(hdc, 180, 30, NULL);
          LineTo(hdc, 180, 230);
          MoveToEx(hdc, 40, 100, NULL);
          LineTo(hdc, 240, 100);
          MoveToEx(hdc, 40, 180, NULL);
          LineTo(hdc, 240, 180);
          //DeleteObject(hMyPen);
          TextOut(hdc, 0, 0, szText, strlen(szText));
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
          HWND hwndButtonStart = GetDlgItem(hwndDlg, IDC_BUTTON_START);
          CHAR szText[500];
          wsprintf(szText, "Start");
          SetWindowText(hwndButtonStart, szText);
        }
      }
      return TRUE;
    }
    return FALSE;

  case WM_LBUTTONDOWN:
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
          /*int iMinBoardX = 50;
          int iWidthBoardX = 30;
          int iMinBoardY = 60;
          int iWidthBoardY = 30;
          x = ((x - iMinBoardX) / iWidthBoardX)*iWidthBoardX + iMinBoardX + iWidthBoardX / 2;
          y = ((y - iMinBoardY) / iWidthBoardY)*iWidthBoardY + iMinBoardY + iWidthBoardY / 2;*/
          if (isFirstPlayerTurn == true)
          {
            MoveToEx(hdc, x - 30, y - 30, NULL);
            LineTo(hdc, x + 30, y + 30);
            MoveToEx(hdc, x - 30, y + 30, NULL);
            LineTo(hdc, x + 30, y - 30);
            isFieldOccupiedByFirstPlayer[fieldX][fieldY] = true;
          }
          else
          {
            MoveToEx(hdc, x - 30, y - 30, NULL);
            LineTo(hdc, x - 30, y + 30);
            LineTo(hdc, x - 30, y - 30);
            LineTo(hdc, x + 30, y - 30);
            LineTo(hdc, x + 30, y + 30);
            isFieldOccupiedBySecondPlayer[fieldX][fieldY] = true;
          }
          ReleaseDC(hwndDlg, hdc);
          isFirstPlayerTurn = !isFirstPlayerTurn; //prze³¹czanie graczy
        }
      }
    }
    return TRUE;
  case WM_PAINT:
  {
    HDC hdc = GetDC(hwndDlg);
    //DrawBoard(hdc);
    //HPEN hMyPen = CreatePen(PS_SOLID, 5, RGB(255, 255, 0));
    //SelectObject(hdc, hMyPen);

    MoveToEx(hdc, 100, 30, NULL);
    LineTo(hdc, 100, 230);
    MoveToEx(hdc, 180, 30, NULL);
    LineTo(hdc, 180, 230);
    MoveToEx(hdc, 40, 100, NULL);
    LineTo(hdc, 240, 100);
    MoveToEx(hdc, 40, 180, NULL);
    LineTo(hdc, 240, 180);

    //DrawAllBoards(hdc);
    for (int iFieldX = 0; iFieldX < 3; iFieldX++)
    {
      for (int iFieldY = 0; iFieldY < 3; iFieldY++)
      {
        if (isFieldOccupiedByFirstPlayer[iFieldX][iFieldY] == true)
        {
          //DrawX(hdc, iFieldX, iFieldY);
        }
        if (isFieldOccupiedBySecondPlayer[iFieldX][iFieldY] == true)
        {
          //DrawO(hdc, iFieldX, iFieldY);
        }
      }
    }
    ReleaseDC(hwndDlg, hdc);
  }
    return TRUE;

  case WM_CLOSE:    //komunikat zamkniêcia okienka
    DestroyWindow(hwndDlg);
    PostQuitMessage(0);
    return TRUE;
  }
  return FALSE;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow) 
{
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