object AxisMinMaxForm: TAxisMinMaxForm
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'Axis Min/Max values'
  ClientHeight = 98
  ClientWidth = 377
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poOwnerFormCenter
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object Button1: TButton
    Left = 287
    Top = 16
    Width = 75
    Height = 25
    Caption = 'OK'
    Default = True
    ModalResult = 1
    TabOrder = 2
  end
  object MinEdit: TLabeledEdit
    Left = 38
    Top = 16
    Width = 121
    Height = 21
    EditLabel.Width = 20
    EditLabel.Height = 13
    EditLabel.Caption = 'Min:'
    LabelPosition = lpLeft
    TabOrder = 0
  end
  object MaxEdit: TLabeledEdit
    Left = 38
    Top = 54
    Width = 121
    Height = 21
    EditLabel.Width = 24
    EditLabel.Height = 13
    EditLabel.Caption = 'Max:'
    LabelPosition = lpLeft
    TabOrder = 1
  end
  object Button2: TButton
    Left = 287
    Top = 47
    Width = 75
    Height = 25
    Cancel = True
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 3
  end
end
