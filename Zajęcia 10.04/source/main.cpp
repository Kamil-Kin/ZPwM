#include <Windows.h>
#include "res.h"

bool isGameOn = false;  //czy gra zosta³a zaczêta
bool isFirstPlayerTurn = true;  //czyj ruch
bool isFieldOccupiedByFirstPlayer[3][3];
bool isFieldOccupiedBySecondPlayer[3][3];
bool isDraw = false;  //czy remis
int lRuch;  //liczba wykonanych ruchów

HBITMAP hBitmapGameBoard;
HBITMAP hBitmapX;
HBITMAP hBitmapO;
HBITMAP hBitmapStart;
HBITMAP hBitmapReset;
HINSTANCE hInst;

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

LRESULT CALLBACK ButtonWndProc( HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
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
    case BN_CLICKED:    //zdarzenie klikniêcia
      switch (LOWORD(wParam))
      {
      case IDC_BUTTON_START:
        if (isGameOn == false)
        {
          isGameOn = true; CHAR szText[500];
          /*HWND hwndStatic = GetDlgItem(hwndDlg, IDC_STATIC1);

          wsprintf(szText, "Start");
          SetWindowText(hwndStatic, szText);
          for (int i = 0; i < 9; i++)
          {
          HWND hwndButton = GetDlgItem(hwndDlg, IDC_BUTTON1 + i);
          CHAR szText[500];
          wsprintf(szText, "");
          SetWindowText(hwndButton, szText);
          }*/
          HWND hwndButtonStart = GetDlgItem(hwndDlg, IDC_BUTTON_START);
          wsprintf(szText, "Stop");
          SetWindowText(hwndButtonStart, szText);

          //Rysowanie siatki gry
          /*HDC hdc = GetDC(hwndDlg);
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
          ReleaseDC(hwndDlg, hdc);*/

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
  }
    return FALSE;

  case WM_LBUTTONDOWN:
    //CHAR szText[200];
    if (isGameOn == true)
    {
      int x = LOWORD(lParam); int y = HIWORD(lParam);
      if ((x > 0 && x < 236) && (y > 0 && y < 217))
      {
        int fieldX = (x - 0) / 78;
        int fieldY = (y - 0) / 72;
        if ((isFieldOccupiedByFirstPlayer[fieldX][fieldY] == false) &&
          (isFieldOccupiedBySecondPlayer[fieldX][fieldY] == false))
        {
          x = fieldX * 78 + 39;
          y = fieldY * 72 + 36;
          HDC hdc = GetDC(hwndDlg);
          /*int iMinBoardX = 50;
          int iWidthBoardX = 30;
          int iMinBoardY = 60;
          int iWidthBoardY = 30;
          x = ((x - iMinBoardX) / iWidthBoardX)*iWidthBoardX + iMinBoardX + iWidthBoardX / 2;
          y = ((y - iMinBoardY) / iWidthBoardY)*iWidthBoardY + iMinBoardY + iWidthBoardY / 2;
          */
          if (isFirstPlayerTurn == true)
          {
            DrawX(hdc, x - 34, y - 38);
            isFieldOccupiedByFirstPlayer[fieldX][fieldY] = true;
          }
          else
          {
            DrawO(hdc, x - 29, y - 27);
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
    //BitBlt(hdc, 0, 0, 1920, 1080, GetDC(0), 0, 0, SRCCOPY); // kopiowanie zawartoœci kontekstu graficznego do drugiego
    //DrawBoard(hdc);
    //HPEN hMyPen = CreatePen(PS_SOLID, 5, RGB(255, 255, 0));
    //SelectObject(hdc, hMyPen);

    /*MoveToEx(hdc, 100, 30, NULL);
    LineTo(hdc, 100, 230);
    MoveToEx(hdc, 180, 30, NULL);
    LineTo(hdc, 180, 230);
    MoveToEx(hdc, 40, 100, NULL);
    LineTo(hdc, 240, 100);
    MoveToEx(hdc, 40, 180, NULL);
    LineTo(hdc, 240, 180);*/
    //DrawAllBoards(hdc);
    /*for (int iFieldX = 0; iFieldX < 3; iFieldX++)
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

    //DrawBitmap(hdc);
    //ReleaseDC(hwndDlg, hdc);
  }
    return TRUE;

  case WM_CLOSE:    //komunikat zamkniêcia okienka
    DestroyWindow(hwndDlg);
    PostQuitMessage(0);
    for (int i = 0; i < 5; i++) { DeleteObject(hBitmapGameBoard+i); }
    return TRUE;
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