//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
#include <Vcl.Styles.hpp>
#include <Vcl.Themes.hpp>
USEFORM("MainFormU.cpp", MainForm);
USEFORM("SettingsFormU.cpp", SettingsForm);
USEFORM("ShiftingFormU.cpp", ShiftingForm);
USEFORM("BatchProcessingResultsFormU.cpp", BatchProcessingResultsForm);
USEFORM("AxisMinMaxFormU.cpp", AxisMinMaxForm);
//---------------------------------------------------------------------------
std::atomic<int> LangID = 0;
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
    try
    {
        Application->Initialize();
        Application->MainFormOnTaskBar = true;
        Application->CreateForm(__classid(TMainForm), &MainForm);
         Application->CreateForm(__classid(TShiftingForm), &ShiftingForm);
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
    return 0;
}
//---------------------------------------------------------------------------
