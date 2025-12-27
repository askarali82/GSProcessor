object MainForm: TMainForm
  Left = 165
  Top = 62
  Caption = 'GSProcessor'
  ClientHeight = 607
  ClientWidth = 1184
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Menu = MainMenu
  OldCreateOrder = False
  Position = poDesigned
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object MainMenu: TMainMenu
    Left = 136
    Top = 16
    object File: TMenuItem
      Caption = '&Fayl'
      object OpenMI: TMenuItem
        Action = OpenFileAction
      end
      object ReopenMI: TMenuItem
        Caption = 'Qaytadan ochish'
        Visible = False
      end
      object N1: TMenuItem
        Caption = '-'
      end
      object SaveMI: TMenuItem
        Action = SaveAction
      end
      object SaveInTextFormatMI: TMenuItem
        Caption = '&Matnli formatida saqlash'
        Enabled = False
        object OnlyCountsMI: TMenuItem
          Caption = 'Faqat impulslar soni'
          OnClick = OnSaveInTextFormatMIClick
        end
        object CountsInChannelsMI: TMenuItem
          Caption = 'Impulslar soni kanal masshtabida'
          OnClick = OnSaveInTextFormatMIClick
        end
        object CountsInEnergiesMI: TMenuItem
          Caption = 'Impulslar soni energiya masshtabida'
          OnClick = OnSaveInTextFormatMIClick
        end
      end
      object N2: TMenuItem
        Caption = '-'
      end
      object ExitMI: TMenuItem
        Caption = 'Chiqish'
        OnClick = ExitMIClick
      end
    end
    object Analyze: TMenuItem
      Caption = '&Tahlil'
      object DecompositionMI: TMenuItem
        Action = DecompositionMethodAction
      end
    end
    object Tools: TMenuItem
      Caption = '&Asboblar'
      object SettingsMI: TMenuItem
        Caption = '&Sozlamalar'
        OnClick = SettingsMIClick
      end
      object Chiziqlimasshtab1: TMenuItem
        Action = LinLogAction
      end
      object est1: TMenuItem
        Caption = 'Test'
        Visible = False
      end
    end
    object Help: TMenuItem
      Caption = '&Yordam'
      object UserManualMI: TMenuItem
        Caption = '&Qo'#8216'llanma'
      end
      object AboutProgramMI: TMenuItem
        Caption = 'Dastur &haqida...'
        OnClick = AboutProgramMIClick
      end
    end
  end
  object ActionList: TActionList
    Left = 32
    Top = 16
    object OpenFileAction: TAction
      Caption = '&Ochish'
      ShortCut = 16463
      OnExecute = OpenFileActionExecute
    end
    object SaveAction: TAction
      Caption = '&Saqlash'
      ShortCut = 16467
      OnExecute = SaveActionExecute
      OnUpdate = SaveActionUpdate
    end
    object DecompositionMethodAction: TAction
      Caption = 'Tarkibiy &qismlarga ajratish'
      OnExecute = DecompositionMethodActionExecute
    end
    object LinLogAction: TAction
      Caption = 'Chiziqli masshtab'
      Checked = True
      ShortCut = 16460
      OnExecute = LinLogActionExecute
      OnUpdate = LinLogActionUpdate
    end
  end
  object OpenDialog: TOpenDialog
    Options = [ofHideReadOnly, ofPathMustExist, ofFileMustExist, ofEnableSizing]
    Left = 231
    Top = 17
  end
  object SaveDialog: TSaveDialog
    DefaultExt = 'txt'
    Filter = 'Matnli fayllar|*.txt'
    Options = [ofOverwritePrompt, ofHideReadOnly, ofPathMustExist, ofEnableSizing]
    Left = 320
    Top = 16
  end
end
