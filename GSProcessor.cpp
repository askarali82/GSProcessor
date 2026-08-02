//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <tchar.h>
#include <windows.h>
#include <Vcl.Styles.hpp>
#include <Vcl.Themes.hpp>
#include "Common.h"

USEFORM("ShiftingFormU.cpp", ShiftingForm);
USEFORM("SettingsFormU.cpp", SettingsForm);
USEFORM("SpectrumFrameU.cpp", SpectrumFrame); /* TFrame: File Type */
USEFORM("MainFormU.cpp", MainForm);
USEFORM("BatchProcessingResultsFormU.cpp", BatchProcessingResultsForm);
USEFORM("AxisMinMaxFormU.cpp", AxisMinMaxForm);
USEFORM("AnalysisFormU.cpp", AnalysisForm);
//---------------------------------------------------------------------------
std::atomic<int> LangID = 0;
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
    HANDLE MutexHandle = CreateMutexW(NULL, TRUE, L"Local\\GSP_Instance_Mutex");
    if (MutexHandle != 0 && GetLastError() == ERROR_ALREADY_EXISTS)
    {
        MessageBox(0, L"The application has already been launched.", APP_NAME.c_str(), MB_ICONWARNING | MB_OK);
        HWND Wnd = FindWindowW(L"TMainForm", nullptr);
        wchar_t Buffer[512] = {0};
        if (Wnd && GetWindowTextW(Wnd, Buffer, sizeof(Buffer) / sizeof(wchar_t)) > 0)
        {
            if (String(Buffer).Pos(APP_NAME) > 0)
            {
                FlashWindow(Wnd, 1);
            }
        }
        goto End;
    }

    try
    {
        Application->Initialize();
        Application->MainFormOnTaskBar = true;
        Application->CreateForm(__classid(TMainForm), &MainForm);
        Application->Run();
    }
    catch (Exception &exception)
    {
        Application->ShowException(&exception);
    }
    catch (...)
    {
         try
         {
             throw Exception("");
         }
         catch (Exception &exception)
         {
             Application->ShowException(&exception);
         }
    }

    End:
        if (MutexHandle != 0)
        {
            CloseHandle(MutexHandle);
        }

    return 0;
}
//---------------------------------------------------------------------------
