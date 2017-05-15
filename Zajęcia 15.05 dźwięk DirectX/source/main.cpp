#include <Windows.h>
#include "res.h"
#include <stdio.h>
#include <math.h>
#pragma comment(lib,"winmm.lib")
#pragma comment (lib, "dsound.lib")
#include "dsound.h"
#define PI 3.141592

int Note(BYTE* pBufferForAudio, int iStart, int iDuration, float fNote, float fDiv)
{
  int i;
  for (i = iStart; i < iStart + iDuration - 200; i++)
  {
    float t = i / fDiv;
    pBufferForAudio[i] = (128 * sin(2 * PI*fNote*t) + 128 
                        + 128 * sin(2 * PI*fNote*1.0/2.0*t) + 128)/2;
  }
  for (; i < iStart + iDuration; ++i)
  {
    float t = i / fDiv;
    pBufferForAudio[i] = 128;
  }
  return i;
}

int Echo(BYTE* pBufferForAudio, int iStart, int iDuration, int iDelay, float iAttenuate, int iDelay2, float iAttenuate2, int iDelay3, float iAttenuate3)
{
  BYTE* tmp = new BYTE[iDuration];
  memcpy(tmp, pBufferForAudio, iDuration);
  for (int i = 0; i < iDuration; i++) 
  {
    int iSample = 0;
    int iSample2 = 0;
    int iSample3 = 0;
    if (i - iDelay > 0)
      iSample = tmp[i - iDelay] - 128;
    if (i - iDelay2 > 0)
      iSample2 = tmp[i - iDelay2] - 128;
    if (i - iDelay3 > 0)
      iSample3 = tmp[i - iDelay3] - 128;
      //pBufferForAudio[i] = (tmp[i] + tmp[i - iDelay] * iAttenuate) / (1.0 + iAttenuate);
    pBufferForAudio[i] = ((tmp[i] - 128.0) + iSample*iAttenuate + iSample2*iAttenuate2 + iSample3*iAttenuate3) / (1.0 + iAttenuate + iAttenuate2 + iAttenuate3) + 128;
 }
  delete[] tmp;
  return 0;
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
//pauza
float fp = 0;

const int size = 100;

BYTE* pBufferForAudio = 0;
WAVEFORMATEX pcmWaveFormat;
float S = pcmWaveFormat.nAvgBytesPerSec;
void Song(char *tabNote, double *tabTime, BYTE* pBufferForAudio, int size);

char note_[size] = { 'e','e','g','e','p','d','c','H',
'e','e','g','e','p','d','c','H',
'e','e','g','e','p','d','c','H',
'e','e','g','e','p','d','c','H',
'e','e','g','e','p','d','c','H',
'e','e','g','e','p','d','c','H' };
double time_[size] = { 24,8,12,4,10,8,32,32,
24,8,12,4,10,8,32,32,
24,8,12,4,10,8,32,32,
24,8,12,4,10,8,32,32,
24,8,12,4,10,8,32,32,
24,8,12,4,10,8,32,32 };

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

  IDirectSound8 *DS8 = NULL;
  DirectSoundCreate8(NULL, &DS8, NULL);
  if (DS8 == NULL) 
  {
    MessageBox(0, TEXT("Nie mo¿na utworzyæ DirectSound"), TEXT("Error"), MB_OK);
  }
  if (DS8->SetCooperativeLevel(hwndMainWindow, DSSCL_NORMAL) != DS_OK)
    MessageBox(0, TEXT("Nie mo¿na ustaawiæ wymaganego trybu pracy"), TEXT("Error"), MB_OK);

  MMRESULT mmResult = 0;
  HWAVEOUT hwo = 0;
  UINT devId;

  /*for (devId = 0; devId<waveOutGetNumDevs(); devId++)
  {
    mmResult = waveOutOpen(&hwo, devId, &pcmWaveFormat, 0, 0, CALLBACK_NULL);
    if (mmResult == MMSYSERR_NOERROR)break;
  }
  if (mmResult != MMSYSERR_NOERROR) //Gdy nie uda³o sie odtworzyæ karty dŸwiêkowej
  {
    MessageBox(hwndMainWindow, TEXT("Nie znaleziono karty"), TEXT("ERROR"), MB_OK);
    return mmResult;
  }*/

  BYTE* pBufferForAudio = new BYTE[35 * pcmWaveFormat.nAvgBytesPerSec];   //4 - ile sekund
  int i = 0;

  WAVEHDR whdr;
  ZeroMemory(&whdr, sizeof(WAVEHDR));
  whdr.lpData = reinterpret_cast<LPSTR>(pBufferForAudio);

  whdr.dwBufferLength = 35 * pcmWaveFormat.nAvgBytesPerSec;
  //{
  Song(note_, time_, pBufferForAudio, size);
  Echo(pBufferForAudio, 0, whdr.dwBufferLength, 44000 / 3, 0.5, 44000 / 2, 0.4, 34000, 0.3);

  IDirectSoundBuffer *DSB;
  DSBUFFERDESC DSBD;
  memset(&DSBD, 0, sizeof(DSBUFFERDESC));
  DSBD.dwSize = sizeof(DSBUFFERDESC);
  DSBD.dwFlags = DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLFREQUENCY;
  DSBD.dwBufferBytes = whdr.dwBufferLength;
  DSBD.lpwfxFormat = &pcmWaveFormat;

  if (DS8->CreateSoundBuffer(&DSBD, &DSB, NULL) != DS_OK)
  {
    MessageBox(0, TEXT("Nie mo¿na utworzyæ DirectSoundBuffer"), TEXT("Error"), MB_OK);
  }
  DSB->SetVolume(0xFFFF);
  void *ptr1, *ptr2;
  DWORD l1, l2;
  DSB->Lock(0, whdr.dwBufferLength, &ptr1, &l1, &ptr2, &l2, DSBLOCK_ENTIREBUFFER);
  if (ptr1) memcpy(ptr1, pBufferForAudio, l1);
  if (ptr2) memcpy(ptr2, pBufferForAudio + l1, l2);

  DSB->Unlock(ptr1, l1, ptr2, l2);

  DSB->Play(0, 0, 0);

  MSG msg = {};
  while (GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
    }
   /* mmResult = waveOutPrepareHeader(hwo, &whdr, sizeof(WAVEHDR));
    mmResult = waveOutWrite(hwo, &whdr, sizeof(WAVEHDR));
    while ((whdr.dwFlags & WHDR_DONE) != WHDR_DONE)Sleep(100);
    mmResult = waveOutUnprepareHeader(hwo, &whdr, sizeof(WAVEHDR));*/
  //}
    DS8->Release();
  //mmResult = waveOutClose(hwo);
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