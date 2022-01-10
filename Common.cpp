#include <vcl.h>
#pragma hdrstop

#include "Common.h"
#include "dir.h"
#include <DateUtils.hpp>
#include <System.StrUtils.hpp>

//---------------------------------------------------------------------------
void Utils::Log(const AnsiString &Func, const AnsiString &Line, AnsiString Msg)
{
	if (Msg == "")
	{
		return;
	}
	try
	{
		static const String OldDirName = GetEnvironmentVariable(L"APPDATA") + L"\\ProcessASW\\";
		static String AppData = GetEnvironmentVariable(L"APPDATA") + L"\\" + Application->Title + L"\\";
		MoveFileW(OldDirName.c_str(), AppData.c_str());
		CreateDir(AppData);
		static String Name = ExtractFileName(GetModuleName(0));
		if (Name == ExtractFileName(GetModuleName(0)))
		{
			const String &TimePart = Now().FormatString(L"DD-MM-YYYY_HH-MM-SS");
			Name = AppData + Name + L"-" + TimePart + L".log";
		}
		static std::unique_ptr<TCriticalSection> Section(new TCriticalSection());
		TScopeLock Lock(Section.get());
		HANDLE File = CreateFileW(
			Name.c_str(),
			GENERIC_READ | GENERIC_WRITE,
			0,
			0,
			OPEN_ALWAYS,
			0,
			0);
		if (File == INVALID_HANDLE_VALUE)
		{
			return;
		}
		if (SetFilePointer(File, 0, 0, FILE_END) != INVALID_SET_FILE_POINTER)
		{
			DWORD Written;
			Msg = Now().FormatString(L"DD.MM.YYYY HH:MM:SS") + " " +
				UIntToStr((unsigned)GetCurrentProcessId()) + " " + UIntToStr((unsigned)GetCurrentThreadId()) + " " +
				Func + L"(" + Line + L"): " + Msg + L"\r\n";
			WriteFile(File, Msg.c_str(), Msg.Length(), &Written, 0);
		}
		CloseHandle(File);
	}
	catch (...)
	{
	}
}
//---------------------------------------------------------------------------
void Utils::LogException(const Exception &E, const AnsiString &Func, const AnsiString &Line)
{
	const AnsiString &ExClsName = const_cast<Exception &>(E).ClassName();
	const AnsiString &Msg = "ERROR(" + ExClsName + "): " + E.Message;
	Utils::Log(Func, Line, Msg);
	MessageBeep(MB_ICONEXCLAMATION);
}
//---------------------------------------------------------------------------
String Utils::RoundFloatValue(const double Value, const int D, const bool DeleteZeroes)
{
	String Result = Sysutils::FloatToStrF(Value, ffFixed, 15, D);
	if (DeleteZeroes)
	{
		bool ZeroFound = Result[Result.Length()] == L'0';
		while (ZeroFound)
		{
			Result = Result.Delete(Result.Length(), 1);
			ZeroFound = Result[Result.Length()] == L'0';
		}
		if (Result[Result.Length()] == L'.' || Result[Result.Length()] == L',')
		{
			Result = Result.Delete(Result.Length(), 1);
		}
	}
    return Result;
}
//---------------------------------------------------------------------------
void Utils::NormalizeStandardSources(
	const TSpectrum &Spc1, TSpectrum &Spc2, const double Energy1, const double Energy2)
{
	String Spectrum1Error = L"NormalizeStandardSources(): 1 - spektrda xatolik bor.";
	String Spectrum2Error = L"NormalizeStandardSources(): 2 - spektrda xatolik bor.";
	if (LangID == 1)
	{
		Spectrum1Error = L"NormalizeStandardSources(): There is an error in spectrum 1.";
		Spectrum2Error = L"NormalizeStandardSources(): There is an error in spectrum 2.";
	}
	CheckError(!Spc1.IsValid(), Spectrum1Error);
	CheckError(!Spc2.IsValid(), Spectrum2Error);
	Spc2 = Spc2.Multiply(Spc1.Duration / Spc2.Duration);
	Spc2.Duration = Spc1.Duration;
	const double S1 = Spc1.CalculateCountByEnergyRange(Energy1, Energy2);
	const double S2 = Spc2.CalculateCountByEnergyRange(Energy1, Energy2);
	Spc2 = Spc2.Multiply(S1 / S2);
	Spc2.ExtraFloatData = Spc1.ExtraFloatData;
	Spc2.ExtraStringData = Spc1.ExtraStringData;
}
//---------------------------------------------------------------------------
String Utils::GetDialogBoxFilterForSpectraFiles()
{
	String Result =
		L"Spektr fayllari (*.gsp;*.asw)|*.gsp;*.asw|"
		L"GSP fayllar (*.gsp)|*.gsp|"
		L"ASW fayllar (*.asw)|*.asw";
	if (LangID == 1)
	{
		Result =
			L"Spectra files (*.gsp;*.asw)|*.gsp;*.asw|"
			L"GSP files (*.gsp)|*.gsp|"
			L"ASW files (*.asw)|*.asw";
	}
    return Result;
}
