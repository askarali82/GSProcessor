#define ProductName     "GSProcessor"
#define MainExeName     "GSProcessor.exe"

[Setup]
PrivilegesRequired       = lowest
SourceDir                = "{#SourcePath}\bin\Deploy"
AppName                  = {#ProductName}
AppVersion               = "4.1.0"      
VersionInfoVersion       = "4.1.0.0"
AppCopyright             = Samarkand State University, Askarali Azimov
AppPublisher             = Askarali Azimov
DefaultDirName           = "{localappdata}\Programs\{#ProductName}"
DisableWelcomePage       = no
DisableProgramGroupPage  = yes
UninstallDisplayName     = "{#ProductName}"
UninstallDisplayIcon     = "{app}\{#MainExeName}"
VersionInfoDescription   = Gamma spectrum analysis
SetupIconFile            = "{#SourcePath}\Images\Logo-36x36.ico"
OutputBaseFilename       = "{#ProductName}Setup"
WizardSmallImageFile     = "{#SourcePath}\Images\Logo-48x48.bmp"

[Files]
Source: "*"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs

[Icons]
Name: "{userprograms}\{#ProductName}\{#ProductName}"; Filename: "{app}\{#MainExeName}"; Tasks: startmenu;
Name: "{userdesktop}\{#ProductName}";                 Filename: "{app}\{#MainExeName}"; Tasks: desktop;

[Tasks]
Name: startmenu; Description: "Create shortcuts on Start Menu";
Name: desktop; Description: "Create shortcut on Desktop";

[Messages]
ConfirmUninstall=Are you sure you want to completely remove %1 and all of its components? \
Please, CLOSE %1 first if it is running.

[Registry]
Root: HKCU; Subkey: "Software\Classes\.gsp"; ValueType: string; ValueName: ""; ValueData: "GSProcessor.SpectrumFile"; \
    Flags: uninsdeletevalue

Root: HKCU; Subkey: "Software\Classes\GSProcessor.SpectrumFile"; ValueType: string; ValueName: ""; ValueData: "GSProcessor Spectrum File"; \
    Flags: uninsdeletekey

Root: HKCU; Subkey: "Software\Classes\GSProcessor.SpectrumFile\DefaultIcon"; ValueType: string; ValueName: ""; ValueData: "{app}\GSProcessor.exe,0"; \
    Flags: uninsdeletevalue

Root: HKCU; Subkey: "Software\Classes\GSProcessor.SpectrumFile\shell\open\command"; ValueType: string; ValueName: ""; \
    ValueData: """{app}\GSProcessor.exe"" ""%1"""; Flags: uninsdeletevalue

[Code]
const
  WM_SETTINGCHANGE = $001A;
  SMTO_ABORTIFHUNG = $0002;
  SHCNE_ASSOCCHANGED = $08000000;
  SHCNF_IDLIST = $0000;

function SendMessageTimeout(hWnd: LongInt; Msg: LongInt; wParam: LongInt;
  lParam: string; fuFlags: LongInt; uTimeout: LongInt; var lpdwResult: Cardinal): LongInt;
  external 'SendMessageTimeoutW@user32.dll stdcall';

procedure SHChangeNotify(wEventId: LongInt; uFlags: LongInt; dwItem1: LongInt; dwItem2: LongInt);
  external 'SHChangeNotify@shell32.dll stdcall';

//--------------------------------------------------------------------------------------------------------------
procedure RefreshShellIcons();
begin
  SHChangeNotify(SHCNE_ASSOCCHANGED, SHCNF_IDLIST, 0, 0);
end;
//--------------------------------------------------------------------------------------------------------------
procedure AddToPath(const Dir: String);
var
  Path: String;
  ResultCode: DWORD;
begin
  if not RegQueryStringValue(HKCU, 'Environment', 'Path', Path) then
  begin
    Path := '';
  end;

  if Pos(Uppercase(Dir) + ';', Uppercase(Path)) > 0 then
  begin
    Exit;
  end;

  Path := Dir + ';' + Path;
  RegWriteExpandStringValue(HKCU, 'Environment', 'Path', Path);

  SendMessageTimeout(HWND_BROADCAST, WM_SETTINGCHANGE, 0, 'Environment', SMTO_ABORTIFHUNG, 5000, ResultCode);
end;
//--------------------------------------------------------------------------------------------------------------
procedure RemoveFromPath(Dir: string);
var
  Path: string;
  P: Integer;
  ResultCode: DWORD;
begin
  if not RegQueryStringValue(HKCU, 'Environment', 'Path', Path) then
  begin
    Exit;
  end;

  Path := ';' + Path + ';';
  P := Pos(';' + Dir + ';', Path);

  if P > 0 then
  begin
    Delete(Path, P, Length(Dir) + 1);
    Path := Copy(Path, 2, Length(Path) - 2);
    RegWriteExpandStringValue(HKCU, 'Environment', 'Path', Path);

    SendMessageTimeout(HWND_BROADCAST, WM_SETTINGCHANGE, 0, 'Environment', SMTO_ABORTIFHUNG, 5000, ResultCode);
  end;
end;
//--------------------------------------------------------------------------------------------------------------
procedure CurStepChanged(CurStep: TSetupStep);
begin
  if CurStep = ssPostInstall then
  begin
    AddToPath(ExpandConstant('{app}\root\bin'));
    RefreshShellIcons();
  end;
end;
//--------------------------------------------------------------------------------------------------------------
procedure CurUninstallStepChanged(CurUninstallStep: TUninstallStep);
var
  AppDataFolder: string;
begin
  if CurUninstallStep = usPostUninstall then
  begin
    RemoveFromPath(ExpandConstant('{app}\root\bin'));
    RefreshShellIcons();

    AppDataFolder := ExpandConstant('{userappdata}\{#ProductName}');
    if DirExists(AppDataFolder) then
    begin
      if MsgBox('Do you also want to delete {#ProductName} configuration and log files?' + #13#10 +
                AppDataFolder, mbConfirmation, MB_YESNO) = IDYES then
      begin
        DelTree(AppDataFolder, True, True, True);
      end;
    end;
  end;
end;
//--------------------------------------------------------------------------------------------------------------