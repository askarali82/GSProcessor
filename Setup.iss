#define ProductName     "GSProcessor"
#define MainExeName     "GSProcessor.exe"

[Setup]
SourceDir                = "{#SourcePath}\bin\Deploy"
AppName                  = {#ProductName}
AppVersion               = "4.1.0"      
VersionInfoVersion       = "4.1.0.0"
AppCopyright             = Samarkand State University, Askarali Azimov
AppPublisher             = Askarali Azimov
DefaultDirName           = "{commonpf32}\{#ProductName}"
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
Name: "{commonprograms}\{#ProductName}\{#ProductName}";   Filename: "{app}\{#MainExeName}";    Tasks: startmenu;
Name: "{commondesktop}\{#ProductName}";                   Filename: "{app}\{#MainExeName}";    Tasks: desktop;

[Tasks]
Name: startmenu; Description: "Create shortcuts on Start Menu";
Name: desktop; Description: "Create shortcut on Desktop";

[Messages]
ConfirmUninstall=Are you sure you want to completely remove %1 and all of its components? \
Please, CLOSE %1 first if it is running.

[Code]
const
  SYS_ENV_KEY = 'SYSTEM\CurrentControlSet\Control\Session Manager\Environment';
  WM_SETTINGCHANGE = $001A;
  SMTO_ABORTIFHUNG = $0002;

function SendMessageTimeout(hWnd: LongInt; Msg: LongInt; wParam: LongInt;
  lParam: string; fuFlags: LongInt; uTimeout: LongInt; var lpdwResult: Cardinal): LongInt;
  external 'SendMessageTimeoutW@user32.dll stdcall';

procedure AddToPath(const Dir: String);
var
  Path: String;
  ResultCode: DWORD;
begin
  if not RegQueryStringValue(HKLM, SYS_ENV_KEY, 'Path', Path) then
  begin
    Path := '';
  end;

  if Pos(Uppercase(Dir) + ';', Uppercase(Path)) > 0 then
  begin
    Exit;
  end;

  Path := Dir + ';' + Path;
  RegWriteExpandStringValue(HKLM, SYS_ENV_KEY, 'Path', Path);

  SendMessageTimeout(HWND_BROADCAST, WM_SETTINGCHANGE, 0, 'Environment', SMTO_ABORTIFHUNG, 5000, ResultCode);
end;

procedure RemoveFromPath(Dir: string);
var
  Path: string;
  P: Integer;
  ResultCode: DWORD;
begin
  if not RegQueryStringValue(HKLM, SYS_ENV_KEY, 'Path', Path) then
  begin
    Exit;
  end;

  Path := ';' + Path + ';';
  P := Pos(';' + Dir + ';', Path);

  if P > 0 then
  begin
    Delete(Path, P, Length(Dir) + 1);
    Path := Copy(Path, 2, Length(Path) - 2);
    RegWriteExpandStringValue(HKLM, SYS_ENV_KEY, 'Path', Path);

    SendMessageTimeout(HWND_BROADCAST, WM_SETTINGCHANGE, 0, 'Environment', SMTO_ABORTIFHUNG, 5000, ResultCode);
  end;
end;

procedure CurStepChanged(CurStep: TSetupStep);
begin
  if CurStep = ssPostInstall then
  begin
    AddToPath(ExpandConstant('{app}\root\bin'));
  end;
end;

procedure CurUninstallStepChanged(CurUninstallStep: TUninstallStep);
begin
  if CurUninstallStep = usPostUninstall then
  begin
    RemoveFromPath(ExpandConstant('{app}\root\bin'));
  end;
end;