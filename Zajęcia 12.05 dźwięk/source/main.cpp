#include <Windows.h>
#include "res.h"
#include <stdio.h>
#include <math.h>
#pragma comment(lib,"winmm.lib")
#define PI 3.141592

int Note(BYTE* pBufferForAudio, int iStart, int iDuration, float fNote, float fDiv)
{
  int i;
  for (i = iStart; i < iStart + iDuration - 200; i++)
  {
    float t = i / fDiv;
    pBufferForAudio[i] = 128 * sin(2 * PI*fNote*t) + 128;
  }
  for (; i < iStart + iDuration; ++i)
  {
    float t = i / fDiv;
    pBufferForAudio[i] = 128;
  }
  return i;
}
/*          OKTAWA DU¯A             */
float fH = 123.47;
/*            OKTAWA MA£A             */
float fc = 130.8;
float fd = 146.8;
float fe = 164.8;
float ff = 174.6;
float fg = 196;
float fa = 220;
float fh = 247;
/*           OKTAWA RAZKREŒLNA                     */
float fc1 = 261.6;
float fd1 = 293.6;
float fe1 = 329.6;
float ff1 = 349.2;
float fg1 = 392;
float fa1 = 400;
float fh1 = 493.9;

float fp = 0;
/*
float fC = 261.626;
float fD = 293.700;
float fD2 = 587.400;   // jako R
float fE = 329.628;
float fF = 349.228;
float fG = 391.995;
float fA = 440.000;   ///ma³e a
float fP = 220.000;   /// du¿e A jako P
float fH = 493.883;
float fGIS = 415.300;   // jako X
float fCIS = 544.400;  //jako Y
float fFIS = 370.000;  //jako Z
const int size_imperialny = 18;*/
const int size_barka = 100;

BYTE* pBufferForAudio = 0;
WAVEFORMATEX pcmWaveFormat;
float S = pcmWaveFormat.nAvgBytesPerSec;
void Song(char *tabNote, double *tabTime, BYTE* pBufferForAudio, int size);

char note_barka[size_barka] = { 'e','e','g','e','p','d','c','H',
'e','e','g','e','p','d','c','H',
'e','e','g','e','p','d','c','H',
'e','e','g','e','p','d','c','H',
'e','e','g','e','p','d','c','H',
'e','e','g','e','p','d','c','H' };
double time_barka[size_barka] = { 24,8,12,4,12,8,32,32,
24,8,12,4,12,8,32,32,
24,8,12,4,12,8,32,32,
24,8,12,4,12,8,32,32,
24,8,12,4,12,8,32,32,
24,8,12,4,12,8,32,32 };

//int Note(BYTE* pBufferForAudio, int iStart, int iDuration, float fNote, float fDiv);

INT_PTR CALLBACK DialogProc(HWND hwndDig, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  switch (uMsg)
  {
  case WM_COMMAND:
    switch (HIWORD(wParam))
    {

    case BN_CLICKED:  //zdarzenie klikniecia na UI
      switch (LOWORD(wParam))
      {
      case IDC_BUTTON1: //klikniecie na naszym przycisku
      {}
      }
    }
    return FALSE;

  case WM_CLOSE:
    DestroyWindow(hwndDig);  //zniszczenie okienka
    PostQuitMessage(0); //umieszczenie w pêtli komunikatów polecenia zakonczenia aplikacji
    return TRUE;
  }
  return FALSE;
}

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrevinstance, PSTR szCmdLine, int iCmdShow)
{
  HWND hwndMainWindow = CreateDialog(hinstance, MAKEINTRESOURCE(IDD_MAINVIEW), NULL, DialogProc);
  ShowWindow(hwndMainWindow, iCmdShow);

  pcmWaveFormat.wFormatTag = WAVE_FORMAT_PCM;
  pcmWaveFormat.nChannels = 1;
  pcmWaveFormat.nSamplesPerSec = 44100L;  // L wartoœæ typu LONG
  pcmWaveFormat.wBitsPerSample = 8;
  pcmWaveFormat.nAvgBytesPerSec = pcmWaveFormat.nSamplesPerSec*pcmWaveFormat.wBitsPerSample / 8;
  pcmWaveFormat.nBlockAlign = 1;
  pcmWaveFormat.cbSize = 0;

  MMRESULT mmResult = 0;
  HWAVEOUT hwo = 0;
  UINT devId;

  for (devId = 0; devId<waveOutGetNumDevs(); devId++)
  {
    mmResult = waveOutOpen(&hwo, devId, &pcmWaveFormat, 0, 0, CALLBACK_NULL);
    if (mmResult == MMSYSERR_NOERROR)break;
  }
  if (mmResult != MMSYSERR_NOERROR) //Gdy nie uda³o sie odtworzyæ karty dŸwiêkowej
  {
    MessageBox(hwndMainWindow, TEXT("Nie znaleziono karty"), TEXT("ERROR"), MB_OK);
    return mmResult;
  }

  BYTE* pBufferForAudio = new BYTE[35 * pcmWaveFormat.nAvgBytesPerSec];   //4 - ile sekund
  int i = 0;

  WAVEHDR whdr;
  ZeroMemory(&whdr, sizeof(WAVEHDR));
  whdr.lpData = reinterpret_cast<LPSTR>(pBufferForAudio);
  /*
  MSG msg = {};
  while (GetMessage(&msg, NULL, 0, 0))
  {
  TranslateMessage(&msg);
  DispatchMessage(&msg);
  }*/

  whdr.dwBufferLength = 35 * pcmWaveFormat.nAvgBytesPerSec;
  {
    Song(note_barka, time_barka, pBufferForAudio, size_barka);
    mmResult = waveOutPrepareHeader(hwo, &whdr, sizeof(WAVEHDR));
    mmResult = waveOutWrite(hwo, &whdr, sizeof(WAVEHDR));
    while ((whdr.dwFlags & WHDR_DONE) != WHDR_DONE)Sleep(100);
    mmResult = waveOutUnprepareHeader(hwo, &whdr, sizeof(WAVEHDR));
  }

  mmResult = waveOutClose(hwo);
  delete[] pBufferForAudio;
  return 0;
}

void Song(char *tabNote, double *tabTime, BYTE* pBufferForAudio, int size)
{
  int i = 0;
  for (int j = 0; j < size; j++)
  {
    switch (tabNote[j])
    {
    case 'e':
      i = Note(pBufferForAudio, i, pcmWaveFormat.nAvgBytesPerSec*(tabTime[j] / 32.0), fe, pcmWaveFormat.nSamplesPerSec);
      break;
    case 'c':
      i = Note(pBufferForAudio, i, pcmWaveFormat.nAvgBytesPerSec*(tabTime[j] / 32.0), fc, pcmWaveFormat.nSamplesPerSec);
      break;
    case 'g':
      i = Note(pBufferForAudio, i, pcmWaveFormat.nAvgBytesPerSec*(tabTime[j] / 32.0), fg, pcmWaveFormat.nSamplesPerSec);
      break;
    case 'H':
      i = Note(pBufferForAudio, i, pcmWaveFormat.nAvgBytesPerSec*(tabTime[j] / 32.0), fH, pcmWaveFormat.nSamplesPerSec);
      break;
    case 'd':
      i = Note(pBufferForAudio, i, pcmWaveFormat.nAvgBytesPerSec*(tabTime[j] / 32.0), fd, pcmWaveFormat.nSamplesPerSec);
      break;
    case 'f':
      i = Note(pBufferForAudio, i, pcmWaveFormat.nAvgBytesPerSec*(tabTime[j] / 32.0), ff, pcmWaveFormat.nSamplesPerSec);
      break;
    case 'a':
      i = Note(pBufferForAudio, i, pcmWaveFormat.nAvgBytesPerSec*(tabTime[j] / 32.0), fa, pcmWaveFormat.nSamplesPerSec);
      break;
    case 'p':
      i = Note(pBufferForAudio, i, pcmWaveFormat.nAvgBytesPerSec*(tabTime[j] / 32.0), fp, pcmWaveFormat.nSamplesPerSec);
    /*case 'X':
      i = Note(pBufferForAudio, i, pcmWaveFormat.nAvgBytesPerSec*(tabTime[j] / 16.0), fGIS, pcmWaveFormat.nSamplesPerSec);
      break;
    case 'Y':
      i = Note(pBufferForAudio, i, pcmWaveFormat.nAvgBytesPerSec*(tabTime[j] / 16.0), fCIS, pcmWaveFormat.nSamplesPerSec);
      break;
    case 'Z':
      i = Note(pBufferForAudio, i, pcmWaveFormat.nAvgBytesPerSec*(tabTime[j] / 16.0), fFIS, pcmWaveFormat.nSamplesPerSec);
      break;
    case 'P':
      i = Note(pBufferForAudio, i, pcmWaveFormat.nAvgBytesPerSec*(tabTime[j] / 16.0), fP, pcmWaveFormat.nSamplesPerSec);
      break;
    case 'R':
      i = Note(pBufferForAudio, i, pcmWaveFormat.nAvgBytesPerSec*(tabTime[j] / 16.0), fD2, pcmWaveFormat.nSamplesPerSec);
      break;*/
    default:
      break;
    }
  }
}

//tak ma wygl¹daæ
//char snotes = "E E E C G E C G E B B B C G E C G E";
//char sTime = "16 16 16 8 4 16 8 4 16 16 16 16 8 4 16 8 4 16";