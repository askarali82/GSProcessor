//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
#include <Vcl.Styles.hpp>
#include <Vcl.Themes.hpp>
USEFORM("AnalysisFormU.cpp", AnalysisForm);
USEFORM("SettingsFormU.cpp", SettingsForm);
USEFORM("ShiftingFormU.cpp", ShiftingForm);
USEFORM("AxisMinMaxFormU.cpp", AxisMinMaxForm);
USEFORM("BatchProcessingResultsFormU.cpp", BatchProcessingResultsForm);
USEFORM("MainFormU.cpp", MainForm);
USEFORM("SpectrumFrameU.cpp", SpectrumFrame); /* TFrame: File Type */
//---------------------------------------------------------------------------
std::atomic<int> LangID = 0;
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
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
    return 0;
}
//---------------------------------------------------------------------------
