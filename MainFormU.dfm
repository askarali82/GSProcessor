object MainForm: TMainForm
  Left = 0
  Top = 0
  Caption = 'GSProcessor'
  ClientHeight = 749
  ClientWidth = 1400
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  WindowState = wsMaximized
  OnResize = FormResize
  DesignSize = (
    1400
    749)
  PixelsPerInch = 96
  TextHeight = 13
  object SamplePanel: TPanel
    Left = 805
    Top = 40
    Width = 593
    Height = 104
    Anchors = [akTop, akRight]
    BevelKind = bkFlat
    BevelOuter = bvNone
    DoubleBuffered = True
    ParentBackground = False
    ParentDoubleBuffered = False
    TabOrder = 5
    DesignSize = (
      589
      100)
    object SmpCh2RightShiftBtn: TSpeedButton
      Left = 564
      Top = 46
      Width = 23
      Height = 22
      Anchors = [akTop, akRight]
      Glyph.Data = {
        9E020000424D9E0200000000000036000000280000000E0000000E0000000100
        1800000000006802000074120000741200000000000000000000FFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFD9D9D9E6E6E6FFFFFFFFFFFFFFFFFFFFFFFF0000FFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFBBBBBB282828E6E6E6FF
        FFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFBBBBBB000000282828E6E6E6FFFFFFFFFFFF0000FFFFFF7B7B7B40404040
        40404040404040404040404040402F2F2F000000000000282828E6E6E6FFFFFF
        0000FFFFFF333333000000000000000000000000000000000000000000000000
        000000000000282828E9E9E90000FFFFFF333333000000000000000000000000
        0000000000000000000000000000000000002C2C2CE9E9E90000FFFFFF7B7B7B
        4040404040404040404040404040404040402F2F2F0000000000002C2C2CE9E9
        E9FFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFBBBB
        BB0000002C2C2CE9E9E9FFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFBBBBBB2C2C2CE9E9E9FFFFFFFFFFFFFFFFFF0000FFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFD9D9D9E9E9E9FFFFFFFF
        FFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        0000}
      OnClick = OnCh2RightShiftBtnClick
    end
    object SmpCh2LeftShiftBtn: TSpeedButton
      Left = 541
      Top = 46
      Width = 23
      Height = 22
      Anchors = [akTop, akRight]
      Glyph.Data = {
        9E020000424D9E0200000000000036000000280000000E0000000E0000000100
        1800000000006802000074120000741200000000000000000000FFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFE9E9
        E9D9D9D9FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFF
        FFFFFFFFFFFFFFE9E9E92C2C2CBBBBBBFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFF0000FFFFFFFFFFFFE9E9E92C2C2C000000BBBBBBFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFE9E9E92C2C2C00
        00000000002F2F2F4040404040404040404040404040404040407B7B7BFFFFFF
        0000E9E9E92C2C2C000000000000000000000000000000000000000000000000
        000000000000333333FFFFFF0000E9E9E9282828000000000000000000000000
        000000000000000000000000000000000000333333FFFFFF0000FFFFFFE6E6E6
        2828280000000000002F2F2F4040404040404040404040404040404040407B7B
        7BFFFFFF0000FFFFFFFFFFFFE6E6E6282828000000BBBBBBFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFE6E6E62828
        28BBBBBBFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFF
        FFFFFFFFFFFFFFFFFFFFE6E6E6D9D9D9FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        0000}
      OnClick = OnCh2LeftShiftBtnClick
    end
    object SmpCh1RightShiftBtn: TSpeedButton
      Left = 487
      Top = 46
      Width = 23
      Height = 22
      Anchors = [akTop, akRight]
      Glyph.Data = {
        9E020000424D9E0200000000000036000000280000000E0000000E0000000100
        1800000000006802000074120000741200000000000000000000FFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFD9D9D9E6E6E6FFFFFFFFFFFFFFFFFFFFFFFF0000FFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFBBBBBB282828E6E6E6FF
        FFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFBBBBBB000000282828E6E6E6FFFFFFFFFFFF0000FFFFFF7B7B7B40404040
        40404040404040404040404040402F2F2F000000000000282828E6E6E6FFFFFF
        0000FFFFFF333333000000000000000000000000000000000000000000000000
        000000000000282828E9E9E90000FFFFFF333333000000000000000000000000
        0000000000000000000000000000000000002C2C2CE9E9E90000FFFFFF7B7B7B
        4040404040404040404040404040404040402F2F2F0000000000002C2C2CE9E9
        E9FFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFBBBB
        BB0000002C2C2CE9E9E9FFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFBBBBBB2C2C2CE9E9E9FFFFFFFFFFFFFFFFFF0000FFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFD9D9D9E9E9E9FFFFFFFF
        FFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        0000}
      OnClick = OnCh1RightShiftBtnClick
    end
    object SmpCh1LeftShiftBtn: TSpeedButton
      Left = 464
      Top = 46
      Width = 23
      Height = 22
      Anchors = [akTop, akRight]
      Glyph.Data = {
        9E020000424D9E0200000000000036000000280000000E0000000E0000000100
        1800000000006802000074120000741200000000000000000000FFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFE9E9
        E9D9D9D9FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFF
        FFFFFFFFFFFFFFE9E9E92C2C2CBBBBBBFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFF0000FFFFFFFFFFFFE9E9E92C2C2C000000BBBBBBFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFE9E9E92C2C2C00
        00000000002F2F2F4040404040404040404040404040404040407B7B7BFFFFFF
        0000E9E9E92C2C2C000000000000000000000000000000000000000000000000
        000000000000333333FFFFFF0000E9E9E9282828000000000000000000000000
        000000000000000000000000000000000000333333FFFFFF0000FFFFFFE6E6E6
        2828280000000000002F2F2F4040404040404040404040404040404040407B7B
        7BFFFFFF0000FFFFFFFFFFFFE6E6E6282828000000BBBBBBFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFE6E6E62828
        28BBBBBBFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFF
        FFFFFFFFFFFFFFFFFFFFE6E6E6D9D9D9FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        0000}
      OnClick = OnCh1LeftShiftBtnClick
    end
    object SmpCh1Label: TLabel
      Left = 444
      Top = 7
      Width = 17
      Height = 13
      Anchors = [akTop, akRight]
      Caption = 'K1:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
    end
    object SmpCh2Label: TLabel
      Left = 521
      Top = 7
      Width = 17
      Height = 13
      Anchors = [akTop, akRight]
      Caption = 'K2:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
    end
    object SampleChart: TChart
      Tag = -1
      Left = 0
      Top = 0
      Width = 440
      Height = 100
      AllowPanning = pmNone
      BottomWall.Visible = False
      LeftWall.Visible = False
      Legend.LegendStyle = lsSeries
      Legend.TextStyle = ltsValue
      Legend.Visible = False
      MarginBottom = 1
      MarginLeft = 1
      MarginRight = 1
      MarginTop = 1
      RightWall.Visible = True
      Title.Font.Charset = RUSSIAN_CHARSET
      Title.Font.Name = 'Microsoft Sans Serif'
      Title.Font.Style = [fsBold]
      Title.Frame.Width = 0
      Title.Text.Strings = (
        'Namuna')
      BottomAxis.Automatic = False
      BottomAxis.AutomaticMaximum = False
      BottomAxis.AutomaticMinimum = False
      BottomAxis.Axis.Width = 1
      BottomAxis.Increment = 400.000000000000000000
      BottomAxis.LabelsFormat.Font.Name = 'Tahoma'
      BottomAxis.LabelsFormat.Shadow.HorizSize = 0
      BottomAxis.LabelsFormat.Shadow.VertSize = 0
      BottomAxis.LabelsFormat.Margins.Left = 0
      BottomAxis.LabelsFormat.Margins.Top = 0
      BottomAxis.LabelsFormat.Margins.Right = 0
      BottomAxis.LabelsFormat.Margins.Bottom = 0
      BottomAxis.Maximum = 3000.000000000000000000
      BottomAxis.TickLength = 2
      BottomAxis.Title.Caption = 'E, keV'
      BottomAxis.Title.Font.Name = 'Tahoma'
      BottomAxis.Title.Font.OutLine.Width = 0
      BottomAxis.Title.RoundSize = 12
      BottomAxis.Title.ShapeStyle = fosRoundRectangle
      LeftAxis.Automatic = False
      LeftAxis.AutomaticMinimum = False
      LeftAxis.Axis.Width = 1
      LeftAxis.AxisValuesFormat = '00e-0'
      LeftAxis.ExactDateTime = False
      LeftAxis.LabelsFormat.Font.Name = 'Tahoma'
      LeftAxis.LabelsFormat.Margins.Left = 0
      LeftAxis.LabelsFormat.Margins.Top = 0
      LeftAxis.LabelsFormat.Margins.Right = 0
      LeftAxis.LabelsFormat.Margins.Bottom = 0
      LeftAxis.Logarithmic = True
      LeftAxis.Title.Caption = 'Impuls'
      LeftAxis.Title.Font.Name = 'Tahoma'
      LeftAxis.Title.Font.OutLine.Width = 0
      LeftAxis.Title.Pen.Width = 0
      LeftAxis.Title.ShapeCallout.Size = 26
      LeftAxis.Title.ShapeStyle = fosRoundRectangle
      Panning.MouseWheel = pmwNone
      RightAxis.Automatic = False
      RightAxis.AutomaticMaximum = False
      RightAxis.AutomaticMinimum = False
      RightAxis.Visible = False
      TopAxis.Automatic = False
      TopAxis.AutomaticMaximum = False
      TopAxis.AutomaticMinimum = False
      TopAxis.Axis.Width = 1
      TopAxis.Labels = False
      TopAxis.LabelsFormat.Visible = False
      TopAxis.Ticks.Visible = False
      View3D = False
      Zoom.Allow = False
      Align = alLeft
      Color = clMedGray
      TabStop = False
      TabOrder = 4
      Anchors = [akLeft, akTop, akRight, akBottom]
      OnDblClick = SampleChartDblClick
      OnMouseMove = OnChartMouseMove
      DefaultCanvas = 'TGDIPlusCanvas'
      PrintMargins = (
        15
        37
        15
        37)
      ColorPaletteIndex = 13
      object SampleSpectrum: TLineSeries
        SeriesColor = clBlue
        Title = 'Spc'
        Brush.BackColor = clDefault
        Dark3D = False
        Pointer.InflateMargins = True
        Pointer.Style = psRectangle
        XValues.Name = 'X'
        XValues.Order = loAscending
        YValues.Name = 'Y'
        YValues.Order = loNone
        Data = {0000000000}
        Detail = {0000000000}
      end
    end
    object SmpChan1Edit: TEdit
      Left = 464
      Top = 4
      Width = 45
      Height = 21
      Anchors = [akTop, akRight]
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
      TabOrder = 0
      OnChange = OnShiftingDataChange
    end
    object SmpDValEdit1: TEdit
      Left = 464
      Top = 27
      Width = 26
      Height = 18
      Anchors = [akTop, akRight]
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -8
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
    end
    object SmpDValEdit2: TEdit
      Left = 541
      Top = 27
      Width = 26
      Height = 18
      Anchors = [akTop, akRight]
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -8
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
    end
    object SmpChan2Edit: TEdit
      Left = 541
      Top = 4
      Width = 45
      Height = 21
      Anchors = [akTop, akRight]
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
      TabOrder = 1
      OnChange = OnShiftingDataChange
    end
  end
  object BkgPanel: TPanel
    Left = 805
    Top = 144
    Width = 593
    Height = 104
    Anchors = [akTop, akRight]
    BevelKind = bkFlat
    BevelOuter = bvNone
    DoubleBuffered = True
    ParentDoubleBuffered = False
    TabOrder = 6
    DesignSize = (
      589
      100)
    object BkgCh1LeftShiftBtn: TSpeedButton
      Left = 464
      Top = 47
      Width = 23
      Height = 22
      Anchors = [akTop, akRight]
      Glyph.Data = {
        9E020000424D9E0200000000000036000000280000000E0000000E0000000100
        1800000000006802000074120000741200000000000000000000FFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFE9E9
        E9D9D9D9FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFF
        FFFFFFFFFFFFFFE9E9E92C2C2CBBBBBBFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFF0000FFFFFFFFFFFFE9E9E92C2C2C000000BBBBBBFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFE9E9E92C2C2C00
        00000000002F2F2F4040404040404040404040404040404040407B7B7BFFFFFF
        0000E9E9E92C2C2C000000000000000000000000000000000000000000000000
        000000000000333333FFFFFF0000E9E9E9282828000000000000000000000000
        000000000000000000000000000000000000333333FFFFFF0000FFFFFFE6E6E6
        2828280000000000002F2F2F4040404040404040404040404040404040407B7B
        7BFFFFFF0000FFFFFFFFFFFFE6E6E6282828000000BBBBBBFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFE6E6E62828
        28BBBBBBFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFF
        FFFFFFFFFFFFFFFFFFFFE6E6E6D9D9D9FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        0000}
      OnClick = OnCh1LeftShiftBtnClick
    end
    object BkgCh2RightShiftBtn: TSpeedButton
      Left = 564
      Top = 47
      Width = 23
      Height = 22
      Anchors = [akTop, akRight]
      Glyph.Data = {
        9E020000424D9E0200000000000036000000280000000E0000000E0000000100
        1800000000006802000074120000741200000000000000000000FFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFD9D9D9E6E6E6FFFFFFFFFFFFFFFFFFFFFFFF0000FFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFBBBBBB282828E6E6E6FF
        FFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFBBBBBB000000282828E6E6E6FFFFFFFFFFFF0000FFFFFF7B7B7B40404040
        40404040404040404040404040402F2F2F000000000000282828E6E6E6FFFFFF
        0000FFFFFF333333000000000000000000000000000000000000000000000000
        000000000000282828E9E9E90000FFFFFF333333000000000000000000000000
        0000000000000000000000000000000000002C2C2CE9E9E90000FFFFFF7B7B7B
        4040404040404040404040404040404040402F2F2F0000000000002C2C2CE9E9
        E9FFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFBBBB
        BB0000002C2C2CE9E9E9FFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFBBBBBB2C2C2CE9E9E9FFFFFFFFFFFFFFFFFF0000FFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFD9D9D9E9E9E9FFFFFFFF
        FFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        0000}
      OnClick = OnCh2RightShiftBtnClick
    end
    object BkgCh2LeftShiftBtn: TSpeedButton
      Left = 541
      Top = 47
      Width = 23
      Height = 22
      Anchors = [akTop, akRight]
      Glyph.Data = {
        9E020000424D9E0200000000000036000000280000000E0000000E0000000100
        1800000000006802000074120000741200000000000000000000FFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFE9E9
        E9D9D9D9FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFF
        FFFFFFFFFFFFFFE9E9E92C2C2CBBBBBBFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFF0000FFFFFFFFFFFFE9E9E92C2C2C000000BBBBBBFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFE9E9E92C2C2C00
        00000000002F2F2F4040404040404040404040404040404040407B7B7BFFFFFF
        0000E9E9E92C2C2C000000000000000000000000000000000000000000000000
        000000000000333333FFFFFF0000E9E9E9282828000000000000000000000000
        000000000000000000000000000000000000333333FFFFFF0000FFFFFFE6E6E6
        2828280000000000002F2F2F4040404040404040404040404040404040407B7B
        7BFFFFFF0000FFFFFFFFFFFFE6E6E6282828000000BBBBBBFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFE6E6E62828
        28BBBBBBFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFF
        FFFFFFFFFFFFFFFFFFFFE6E6E6D9D9D9FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        0000}
      OnClick = OnCh2LeftShiftBtnClick
    end
    object BkgCh1RightShiftBtn: TSpeedButton
      Left = 487
      Top = 47
      Width = 23
      Height = 22
      Anchors = [akTop, akRight]
      Glyph.Data = {
        9E020000424D9E0200000000000036000000280000000E0000000E0000000100
        1800000000006802000074120000741200000000000000000000FFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFD9D9D9E6E6E6FFFFFFFFFFFFFFFFFFFFFFFF0000FFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFBBBBBB282828E6E6E6FF
        FFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFBBBBBB000000282828E6E6E6FFFFFFFFFFFF0000FFFFFF7B7B7B40404040
        40404040404040404040404040402F2F2F000000000000282828E6E6E6FFFFFF
        0000FFFFFF333333000000000000000000000000000000000000000000000000
        000000000000282828E9E9E90000FFFFFF333333000000000000000000000000
        0000000000000000000000000000000000002C2C2CE9E9E90000FFFFFF7B7B7B
        4040404040404040404040404040404040402F2F2F0000000000002C2C2CE9E9
        E9FFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFBBBB
        BB0000002C2C2CE9E9E9FFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFBBBBBB2C2C2CE9E9E9FFFFFFFFFFFFFFFFFF0000FFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFD9D9D9E9E9E9FFFFFFFF
        FFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        0000}
      OnClick = OnCh1RightShiftBtnClick
    end
    object BkgCh2Label: TLabel
      Left = 521
      Top = 8
      Width = 17
      Height = 13
      Anchors = [akTop, akRight]
      Caption = 'K2:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
    end
    object BkgCh1Label: TLabel
      Left = 444
      Top = 8
      Width = 17
      Height = 13
      Anchors = [akTop, akRight]
      Caption = 'K1:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
    end
    object BkgChart: TChart
      Tag = -1
      Left = 0
      Top = 0
      Width = 440
      Height = 100
      AllowPanning = pmNone
      BottomWall.Visible = False
      LeftWall.Visible = False
      Legend.LegendStyle = lsSeries
      Legend.TextStyle = ltsValue
      Legend.Visible = False
      MarginBottom = 1
      MarginLeft = 1
      MarginRight = 1
      MarginTop = 1
      Title.Font.Charset = RUSSIAN_CHARSET
      Title.Font.Name = 'Microsoft Sans Serif'
      Title.Font.Style = [fsBold]
      Title.Text.Strings = (
        'Fon')
      BottomAxis.Automatic = False
      BottomAxis.AutomaticMaximum = False
      BottomAxis.AutomaticMinimum = False
      BottomAxis.Axis.Width = 1
      BottomAxis.Increment = 400.000000000000000000
      BottomAxis.LabelsFormat.Font.Name = 'Tahoma'
      BottomAxis.LabelsFormat.Margins.Left = 0
      BottomAxis.LabelsFormat.Margins.Top = 0
      BottomAxis.LabelsFormat.Margins.Right = 0
      BottomAxis.LabelsFormat.Margins.Bottom = 0
      BottomAxis.Maximum = 3000.000000000000000000
      BottomAxis.TickLength = 2
      BottomAxis.Title.Caption = 'E, keV'
      BottomAxis.Title.Font.Name = 'Tahoma'
      BottomAxis.Title.RoundSize = 12
      BottomAxis.Title.ShapeStyle = fosRoundRectangle
      LeftAxis.Automatic = False
      LeftAxis.AutomaticMinimum = False
      LeftAxis.Axis.Width = 1
      LeftAxis.AxisValuesFormat = '00e-0'
      LeftAxis.LabelsFormat.Font.Name = 'Tahoma'
      LeftAxis.LabelsFormat.Margins.Left = 0
      LeftAxis.LabelsFormat.Margins.Top = 0
      LeftAxis.LabelsFormat.Margins.Right = 0
      LeftAxis.LabelsFormat.Margins.Bottom = 0
      LeftAxis.Logarithmic = True
      LeftAxis.Title.Caption = 'Impuls'
      LeftAxis.Title.Font.Name = 'Tahoma'
      Panning.MouseWheel = pmwNone
      RightAxis.Automatic = False
      RightAxis.AutomaticMaximum = False
      RightAxis.AutomaticMinimum = False
      RightAxis.Visible = False
      TopAxis.Automatic = False
      TopAxis.AutomaticMaximum = False
      TopAxis.AutomaticMinimum = False
      TopAxis.Visible = False
      View3D = False
      Zoom.Allow = False
      Align = alLeft
      Color = clMedGray
      TabStop = False
      TabOrder = 4
      Anchors = [akLeft, akTop, akRight, akBottom]
      OnMouseMove = OnChartMouseMove
      DefaultCanvas = 'TGDIPlusCanvas'
      PrintMargins = (
        15
        37
        15
        37)
      ColorPaletteIndex = 13
      object BkgSpectrum: TLineSeries
        SeriesColor = clBlue
        Title = 'Spc'
        Brush.BackColor = clDefault
        Pointer.InflateMargins = True
        Pointer.Style = psRectangle
        XValues.Name = 'X'
        XValues.Order = loAscending
        YValues.Name = 'Y'
        YValues.Order = loNone
        Data = {0000000000}
        Detail = {0000000000}
      end
    end
    object BkgDValEdit2: TEdit
      Left = 541
      Top = 28
      Width = 26
      Height = 18
      Anchors = [akTop, akRight]
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -8
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
    end
    object BkgDValEdit1: TEdit
      Left = 464
      Top = 28
      Width = 26
      Height = 18
      Anchors = [akTop, akRight]
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -8
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
    end
    object BkgChan2Edit: TEdit
      Left = 541
      Top = 5
      Width = 45
      Height = 21
      Anchors = [akTop, akRight]
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
      TabOrder = 1
      OnChange = OnShiftingDataChange
    end
    object BkgChan1Edit: TEdit
      Left = 464
      Top = 5
      Width = 45
      Height = 21
      Anchors = [akTop, akRight]
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
      TabOrder = 0
      OnChange = OnShiftingDataChange
    end
  end
  object ThPanel: TPanel
    Left = 805
    Top = 248
    Width = 593
    Height = 104
    Anchors = [akTop, akRight]
    BevelKind = bkFlat
    BevelOuter = bvNone
    DoubleBuffered = True
    ParentDoubleBuffered = False
    TabOrder = 7
    DesignSize = (
      589
      100)
    object ThCh1LeftShiftBtn: TSpeedButton
      Left = 464
      Top = 70
      Width = 23
      Height = 22
      Anchors = [akTop, akRight]
      Glyph.Data = {
        9E020000424D9E0200000000000036000000280000000E0000000E0000000100
        1800000000006802000074120000741200000000000000000000FFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFE9E9
        E9D9D9D9FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFF
        FFFFFFFFFFFFFFE9E9E92C2C2CBBBBBBFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFF0000FFFFFFFFFFFFE9E9E92C2C2C000000BBBBBBFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFE9E9E92C2C2C00
        00000000002F2F2F4040404040404040404040404040404040407B7B7BFFFFFF
        0000E9E9E92C2C2C000000000000000000000000000000000000000000000000
        000000000000333333FFFFFF0000E9E9E9282828000000000000000000000000
        000000000000000000000000000000000000333333FFFFFF0000FFFFFFE6E6E6
        2828280000000000002F2F2F4040404040404040404040404040404040407B7B
        7BFFFFFF0000FFFFFFFFFFFFE6E6E6282828000000BBBBBBFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFE6E6E62828
        28BBBBBBFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFF
        FFFFFFFFFFFFFFFFFFFFE6E6E6D9D9D9FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        0000}
      OnClick = OnCh1LeftShiftBtnClick
    end
    object ThCh1RightShiftBtn: TSpeedButton
      Left = 487
      Top = 70
      Width = 23
      Height = 22
      Anchors = [akTop, akRight]
      Glyph.Data = {
        9E020000424D9E0200000000000036000000280000000E0000000E0000000100
        1800000000006802000074120000741200000000000000000000FFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFD9D9D9E6E6E6FFFFFFFFFFFFFFFFFFFFFFFF0000FFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFBBBBBB282828E6E6E6FF
        FFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFBBBBBB000000282828E6E6E6FFFFFFFFFFFF0000FFFFFF7B7B7B40404040
        40404040404040404040404040402F2F2F000000000000282828E6E6E6FFFFFF
        0000FFFFFF333333000000000000000000000000000000000000000000000000
        000000000000282828E9E9E90000FFFFFF333333000000000000000000000000
        0000000000000000000000000000000000002C2C2CE9E9E90000FFFFFF7B7B7B
        4040404040404040404040404040404040402F2F2F0000000000002C2C2CE9E9
        E9FFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFBBBB
        BB0000002C2C2CE9E9E9FFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFBBBBBB2C2C2CE9E9E9FFFFFFFFFFFFFFFFFF0000FFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFD9D9D9E9E9E9FFFFFFFF
        FFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        0000}
      OnClick = OnCh1RightShiftBtnClick
    end
    object ThCh2LeftShiftBtn: TSpeedButton
      Left = 541
      Top = 70
      Width = 23
      Height = 22
      Anchors = [akTop, akRight]
      Glyph.Data = {
        9E020000424D9E0200000000000036000000280000000E0000000E0000000100
        1800000000006802000074120000741200000000000000000000FFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFE9E9
        E9D9D9D9FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFF
        FFFFFFFFFFFFFFE9E9E92C2C2CBBBBBBFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFF0000FFFFFFFFFFFFE9E9E92C2C2C000000BBBBBBFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFE9E9E92C2C2C00
        00000000002F2F2F4040404040404040404040404040404040407B7B7BFFFFFF
        0000E9E9E92C2C2C000000000000000000000000000000000000000000000000
        000000000000333333FFFFFF0000E9E9E9282828000000000000000000000000
        000000000000000000000000000000000000333333FFFFFF0000FFFFFFE6E6E6
        2828280000000000002F2F2F4040404040404040404040404040404040407B7B
        7BFFFFFF0000FFFFFFFFFFFFE6E6E6282828000000BBBBBBFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFE6E6E62828
        28BBBBBBFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFF
        FFFFFFFFFFFFFFFFFFFFE6E6E6D9D9D9FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        0000}
      OnClick = OnCh2LeftShiftBtnClick
    end
    object ThCh2RightShiftBtn: TSpeedButton
      Left = 564
      Top = 70
      Width = 23
      Height = 22
      Anchors = [akTop, akRight]
      Glyph.Data = {
        9E020000424D9E0200000000000036000000280000000E0000000E0000000100
        1800000000006802000074120000741200000000000000000000FFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFD9D9D9E6E6E6FFFFFFFFFFFFFFFFFFFFFFFF0000FFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFBBBBBB282828E6E6E6FF
        FFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFBBBBBB000000282828E6E6E6FFFFFFFFFFFF0000FFFFFF7B7B7B40404040
        40404040404040404040404040402F2F2F000000000000282828E6E6E6FFFFFF
        0000FFFFFF333333000000000000000000000000000000000000000000000000
        000000000000282828E9E9E90000FFFFFF333333000000000000000000000000
        0000000000000000000000000000000000002C2C2CE9E9E90000FFFFFF7B7B7B
        4040404040404040404040404040404040402F2F2F0000000000002C2C2CE9E9
        E9FFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFBBBB
        BB0000002C2C2CE9E9E9FFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFBBBBBB2C2C2CE9E9E9FFFFFFFFFFFFFFFFFF0000FFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFD9D9D9E9E9E9FFFFFFFF
        FFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        0000}
      OnClick = OnCh2RightShiftBtnClick
    end
    object ThCh2Label: TLabel
      Left = 521
      Top = 31
      Width = 17
      Height = 13
      Anchors = [akTop, akRight]
      Caption = 'K2:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object ThCh1Label: TLabel
      Left = 444
      Top = 31
      Width = 17
      Height = 13
      Anchors = [akTop, akRight]
      Caption = 'K1:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object ThE2Label: TLabel
      Left = 521
      Top = 7
      Width = 16
      Height = 13
      Anchors = [akTop, akRight]
      Caption = 'E2:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object ThE1Label: TLabel
      Left = 444
      Top = 7
      Width = 16
      Height = 13
      Anchors = [akTop, akRight]
      Caption = 'E1:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object ThChart: TChart
      Tag = -1
      Left = 0
      Top = 0
      Width = 440
      Height = 100
      AllowPanning = pmNone
      BottomWall.Visible = False
      LeftWall.Visible = False
      Legend.LegendStyle = lsSeries
      Legend.TextStyle = ltsValue
      Legend.Visible = False
      MarginBottom = 1
      MarginLeft = 1
      MarginRight = 1
      MarginTop = 1
      Title.Font.Charset = RUSSIAN_CHARSET
      Title.Font.Name = 'Microsoft Sans Serif'
      Title.Font.Style = [fsBold]
      Title.Margins.Left = 11
      Title.Text.Strings = (
        'Th-232')
      BottomAxis.Automatic = False
      BottomAxis.AutomaticMaximum = False
      BottomAxis.AutomaticMinimum = False
      BottomAxis.Axis.Width = 1
      BottomAxis.Increment = 400.000000000000000000
      BottomAxis.LabelsFormat.Font.Name = 'Tahoma'
      BottomAxis.LabelsFormat.Margins.Left = 0
      BottomAxis.LabelsFormat.Margins.Top = 0
      BottomAxis.LabelsFormat.Margins.Right = 0
      BottomAxis.LabelsFormat.Margins.Bottom = 0
      BottomAxis.Maximum = 3000.000000000000000000
      BottomAxis.TickLength = 2
      BottomAxis.Title.Caption = 'E, keV'
      BottomAxis.Title.Font.Name = 'Tahoma'
      BottomAxis.Title.RoundSize = 12
      BottomAxis.Title.ShapeStyle = fosRoundRectangle
      LeftAxis.Automatic = False
      LeftAxis.AutomaticMinimum = False
      LeftAxis.Axis.Width = 1
      LeftAxis.AxisValuesFormat = '00e-0'
      LeftAxis.LabelsFormat.Font.Name = 'Tahoma'
      LeftAxis.LabelsFormat.Margins.Left = 0
      LeftAxis.LabelsFormat.Margins.Top = 0
      LeftAxis.LabelsFormat.Margins.Right = 0
      LeftAxis.LabelsFormat.Margins.Bottom = 0
      LeftAxis.Logarithmic = True
      LeftAxis.MinimumRound = True
      LeftAxis.Title.Caption = 'Impuls'
      LeftAxis.Title.Font.Name = 'Tahoma'
      Panning.MouseWheel = pmwNone
      RightAxis.Automatic = False
      RightAxis.AutomaticMaximum = False
      RightAxis.AutomaticMinimum = False
      RightAxis.Visible = False
      TopAxis.Automatic = False
      TopAxis.AutomaticMaximum = False
      TopAxis.AutomaticMinimum = False
      TopAxis.Visible = False
      View3D = False
      Zoom.Allow = False
      Align = alLeft
      Color = clMedGray
      TabStop = False
      TabOrder = 6
      Anchors = [akLeft, akTop, akRight, akBottom]
      OnMouseMove = OnChartMouseMove
      DefaultCanvas = 'TGDIPlusCanvas'
      PrintMargins = (
        15
        38
        15
        38)
      ColorPaletteIndex = 13
      object ThSpectrum: TLineSeries
        SeriesColor = clBlue
        Title = 'Spc'
        Brush.BackColor = clDefault
        Pointer.InflateMargins = True
        Pointer.Style = psRectangle
        XValues.Name = 'X'
        XValues.Order = loAscending
        YValues.Name = 'Y'
        YValues.Order = loNone
        Data = {0000000000}
        Detail = {0000000000}
      end
    end
    object ThDValEdit1: TEdit
      Left = 464
      Top = 51
      Width = 26
      Height = 18
      Anchors = [akTop, akRight]
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -8
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 4
    end
    object ThDValEdit2: TEdit
      Left = 541
      Top = 51
      Width = 26
      Height = 18
      Anchors = [akTop, akRight]
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -8
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 5
    end
    object ThChan2Edit: TEdit
      Left = 541
      Top = 28
      Width = 45
      Height = 21
      Anchors = [akTop, akRight]
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
      OnChange = OnShiftingDataChange
    end
    object ThChan1Edit: TEdit
      Left = 464
      Top = 28
      Width = 45
      Height = 21
      Anchors = [akTop, akRight]
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      OnChange = OnShiftingDataChange
    end
    object Energy2Edit: TEdit
      Left = 541
      Top = 4
      Width = 45
      Height = 21
      TabStop = False
      Anchors = [akTop, akRight]
      Color = clBtnFace
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ReadOnly = True
      TabOrder = 1
      OnChange = OnShiftingDataChange
    end
    object Energy1Edit: TEdit
      Left = 464
      Top = 4
      Width = 45
      Height = 21
      TabStop = False
      Anchors = [akTop, akRight]
      Color = clBtnFace
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ReadOnly = True
      TabOrder = 0
      OnChange = OnShiftingDataChange
    end
  end
  object RaPanel: TPanel
    Left = 805
    Top = 352
    Width = 593
    Height = 104
    Anchors = [akTop, akRight]
    BevelKind = bkFlat
    BevelOuter = bvNone
    DoubleBuffered = True
    ParentDoubleBuffered = False
    TabOrder = 8
    DesignSize = (
      589
      100)
    object RaCh1LeftShiftBtn: TSpeedButton
      Left = 464
      Top = 47
      Width = 23
      Height = 22
      Anchors = [akTop, akRight]
      Glyph.Data = {
        9E020000424D9E0200000000000036000000280000000E0000000E0000000100
        1800000000006802000074120000741200000000000000000000FFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFE9E9
        E9D9D9D9FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFF
        FFFFFFFFFFFFFFE9E9E92C2C2CBBBBBBFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFF0000FFFFFFFFFFFFE9E9E92C2C2C000000BBBBBBFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFE9E9E92C2C2C00
        00000000002F2F2F4040404040404040404040404040404040407B7B7BFFFFFF
        0000E9E9E92C2C2C000000000000000000000000000000000000000000000000
        000000000000333333FFFFFF0000E9E9E9282828000000000000000000000000
        000000000000000000000000000000000000333333FFFFFF0000FFFFFFE6E6E6
        2828280000000000002F2F2F4040404040404040404040404040404040407B7B
        7BFFFFFF0000FFFFFFFFFFFFE6E6E6282828000000BBBBBBFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFE6E6E62828
        28BBBBBBFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFF
        FFFFFFFFFFFFFFFFFFFFE6E6E6D9D9D9FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        0000}
      OnClick = OnCh1LeftShiftBtnClick
    end
    object RaCh1RightShiftBtn: TSpeedButton
      Left = 487
      Top = 47
      Width = 23
      Height = 22
      Anchors = [akTop, akRight]
      Glyph.Data = {
        9E020000424D9E0200000000000036000000280000000E0000000E0000000100
        1800000000006802000074120000741200000000000000000000FFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFD9D9D9E6E6E6FFFFFFFFFFFFFFFFFFFFFFFF0000FFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFBBBBBB282828E6E6E6FF
        FFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFBBBBBB000000282828E6E6E6FFFFFFFFFFFF0000FFFFFF7B7B7B40404040
        40404040404040404040404040402F2F2F000000000000282828E6E6E6FFFFFF
        0000FFFFFF333333000000000000000000000000000000000000000000000000
        000000000000282828E9E9E90000FFFFFF333333000000000000000000000000
        0000000000000000000000000000000000002C2C2CE9E9E90000FFFFFF7B7B7B
        4040404040404040404040404040404040402F2F2F0000000000002C2C2CE9E9
        E9FFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFBBBB
        BB0000002C2C2CE9E9E9FFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFBBBBBB2C2C2CE9E9E9FFFFFFFFFFFFFFFFFF0000FFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFD9D9D9E9E9E9FFFFFFFF
        FFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        0000}
      OnClick = OnCh1RightShiftBtnClick
    end
    object RaCh2LeftShiftBtn: TSpeedButton
      Left = 541
      Top = 47
      Width = 23
      Height = 22
      Anchors = [akTop, akRight]
      Glyph.Data = {
        9E020000424D9E0200000000000036000000280000000E0000000E0000000100
        1800000000006802000074120000741200000000000000000000FFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFE9E9
        E9D9D9D9FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFF
        FFFFFFFFFFFFFFE9E9E92C2C2CBBBBBBFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFF0000FFFFFFFFFFFFE9E9E92C2C2C000000BBBBBBFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFE9E9E92C2C2C00
        00000000002F2F2F4040404040404040404040404040404040407B7B7BFFFFFF
        0000E9E9E92C2C2C000000000000000000000000000000000000000000000000
        000000000000333333FFFFFF0000E9E9E9282828000000000000000000000000
        000000000000000000000000000000000000333333FFFFFF0000FFFFFFE6E6E6
        2828280000000000002F2F2F4040404040404040404040404040404040407B7B
        7BFFFFFF0000FFFFFFFFFFFFE6E6E6282828000000BBBBBBFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFE6E6E62828
        28BBBBBBFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFF
        FFFFFFFFFFFFFFFFFFFFE6E6E6D9D9D9FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        0000}
      OnClick = OnCh2LeftShiftBtnClick
    end
    object RaCh2RightShiftBtn: TSpeedButton
      Left = 564
      Top = 47
      Width = 23
      Height = 22
      Anchors = [akTop, akRight]
      Glyph.Data = {
        9E020000424D9E0200000000000036000000280000000E0000000E0000000100
        1800000000006802000074120000741200000000000000000000FFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFD9D9D9E6E6E6FFFFFFFFFFFFFFFFFFFFFFFF0000FFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFBBBBBB282828E6E6E6FF
        FFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFBBBBBB000000282828E6E6E6FFFFFFFFFFFF0000FFFFFF7B7B7B40404040
        40404040404040404040404040402F2F2F000000000000282828E6E6E6FFFFFF
        0000FFFFFF333333000000000000000000000000000000000000000000000000
        000000000000282828E9E9E90000FFFFFF333333000000000000000000000000
        0000000000000000000000000000000000002C2C2CE9E9E90000FFFFFF7B7B7B
        4040404040404040404040404040404040402F2F2F0000000000002C2C2CE9E9
        E9FFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFBBBB
        BB0000002C2C2CE9E9E9FFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFBBBBBB2C2C2CE9E9E9FFFFFFFFFFFFFFFFFF0000FFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFD9D9D9E9E9E9FFFFFFFF
        FFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        0000}
      OnClick = OnCh2RightShiftBtnClick
    end
    object RaCh2Label: TLabel
      Left = 521
      Top = 8
      Width = 17
      Height = 13
      Anchors = [akTop, akRight]
      Caption = 'K2:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
    end
    object RaCh1Label: TLabel
      Left = 444
      Top = 8
      Width = 17
      Height = 13
      Anchors = [akTop, akRight]
      Caption = 'K1:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
    end
    object RaChart: TChart
      Tag = -1
      Left = 0
      Top = 0
      Width = 440
      Height = 100
      AllowPanning = pmNone
      BottomWall.Visible = False
      LeftWall.Visible = False
      Legend.LegendStyle = lsSeries
      Legend.TextStyle = ltsValue
      Legend.Visible = False
      MarginBottom = 1
      MarginLeft = 1
      MarginRight = 1
      MarginTop = 1
      Title.Font.Charset = RUSSIAN_CHARSET
      Title.Font.Name = 'Microsoft Sans Serif'
      Title.Font.Style = [fsBold]
      Title.Text.Strings = (
        'Ra-226')
      BottomAxis.Automatic = False
      BottomAxis.AutomaticMaximum = False
      BottomAxis.AutomaticMinimum = False
      BottomAxis.Axis.Width = 1
      BottomAxis.Increment = 400.000000000000000000
      BottomAxis.LabelsFormat.Font.Name = 'Tahoma'
      BottomAxis.LabelsFormat.Margins.Left = 0
      BottomAxis.LabelsFormat.Margins.Top = 0
      BottomAxis.LabelsFormat.Margins.Right = 0
      BottomAxis.LabelsFormat.Margins.Bottom = 0
      BottomAxis.Maximum = 3000.000000000000000000
      BottomAxis.TickLength = 2
      BottomAxis.Title.Caption = 'E, keV'
      BottomAxis.Title.Font.Name = 'Tahoma'
      BottomAxis.Title.RoundSize = 12
      BottomAxis.Title.ShapeStyle = fosRoundRectangle
      LeftAxis.Automatic = False
      LeftAxis.AutomaticMinimum = False
      LeftAxis.Axis.Width = 1
      LeftAxis.AxisValuesFormat = '00e-0'
      LeftAxis.LabelsFormat.Font.Name = 'Tahoma'
      LeftAxis.LabelsFormat.Margins.Left = 0
      LeftAxis.LabelsFormat.Margins.Top = 0
      LeftAxis.LabelsFormat.Margins.Right = 0
      LeftAxis.LabelsFormat.Margins.Bottom = 0
      LeftAxis.Logarithmic = True
      LeftAxis.Title.Caption = 'Impuls'
      LeftAxis.Title.Font.Name = 'Tahoma'
      Panning.MouseWheel = pmwNone
      RightAxis.Automatic = False
      RightAxis.AutomaticMaximum = False
      RightAxis.AutomaticMinimum = False
      RightAxis.Visible = False
      TopAxis.Automatic = False
      TopAxis.AutomaticMaximum = False
      TopAxis.AutomaticMinimum = False
      TopAxis.Visible = False
      View3D = False
      Zoom.Allow = False
      Align = alLeft
      Color = clMedGray
      TabStop = False
      TabOrder = 4
      Anchors = [akLeft, akTop, akRight, akBottom]
      OnMouseMove = OnChartMouseMove
      DefaultCanvas = 'TGDIPlusCanvas'
      PrintMargins = (
        15
        37
        15
        37)
      ColorPaletteIndex = 13
      object RaSpectrum: TLineSeries
        SeriesColor = clBlue
        Title = 'Spc'
        Brush.BackColor = clDefault
        Pointer.InflateMargins = True
        Pointer.Style = psRectangle
        XValues.Name = 'X'
        XValues.Order = loAscending
        YValues.Name = 'Y'
        YValues.Order = loNone
        Data = {0000000000}
        Detail = {0000000000}
      end
    end
    object RaDValEdit1: TEdit
      Left = 464
      Top = 28
      Width = 26
      Height = 18
      Anchors = [akTop, akRight]
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -8
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
    end
    object RaDValEdit2: TEdit
      Left = 541
      Top = 28
      Width = 26
      Height = 18
      Anchors = [akTop, akRight]
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -8
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
    end
    object RaChan2Edit: TEdit
      Left = 541
      Top = 5
      Width = 45
      Height = 21
      Anchors = [akTop, akRight]
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
      TabOrder = 1
      OnChange = OnShiftingDataChange
    end
    object RaChan1Edit: TEdit
      Left = 464
      Top = 5
      Width = 45
      Height = 21
      Anchors = [akTop, akRight]
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
      TabOrder = 0
      OnChange = OnShiftingDataChange
    end
  end
  object KPanel: TPanel
    Left = 805
    Top = 456
    Width = 593
    Height = 104
    Anchors = [akTop, akRight]
    BevelKind = bkFlat
    BevelOuter = bvNone
    DoubleBuffered = True
    ParentDoubleBuffered = False
    TabOrder = 9
    DesignSize = (
      589
      100)
    object KCh1LeftShiftBtn: TSpeedButton
      Left = 464
      Top = 47
      Width = 23
      Height = 22
      Anchors = [akTop, akRight]
      Glyph.Data = {
        9E020000424D9E0200000000000036000000280000000E0000000E0000000100
        1800000000006802000074120000741200000000000000000000FFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFE9E9
        E9D9D9D9FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFF
        FFFFFFFFFFFFFFE9E9E92C2C2CBBBBBBFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFF0000FFFFFFFFFFFFE9E9E92C2C2C000000BBBBBBFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFE9E9E92C2C2C00
        00000000002F2F2F4040404040404040404040404040404040407B7B7BFFFFFF
        0000E9E9E92C2C2C000000000000000000000000000000000000000000000000
        000000000000333333FFFFFF0000E9E9E9282828000000000000000000000000
        000000000000000000000000000000000000333333FFFFFF0000FFFFFFE6E6E6
        2828280000000000002F2F2F4040404040404040404040404040404040407B7B
        7BFFFFFF0000FFFFFFFFFFFFE6E6E6282828000000BBBBBBFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFE6E6E62828
        28BBBBBBFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFF
        FFFFFFFFFFFFFFFFFFFFE6E6E6D9D9D9FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        0000}
      OnClick = OnCh1LeftShiftBtnClick
    end
    object KCh1RightShiftBtn: TSpeedButton
      Left = 487
      Top = 47
      Width = 23
      Height = 22
      Anchors = [akTop, akRight]
      Glyph.Data = {
        9E020000424D9E0200000000000036000000280000000E0000000E0000000100
        1800000000006802000074120000741200000000000000000000FFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFD9D9D9E6E6E6FFFFFFFFFFFFFFFFFFFFFFFF0000FFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFBBBBBB282828E6E6E6FF
        FFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFBBBBBB000000282828E6E6E6FFFFFFFFFFFF0000FFFFFF7B7B7B40404040
        40404040404040404040404040402F2F2F000000000000282828E6E6E6FFFFFF
        0000FFFFFF333333000000000000000000000000000000000000000000000000
        000000000000282828E9E9E90000FFFFFF333333000000000000000000000000
        0000000000000000000000000000000000002C2C2CE9E9E90000FFFFFF7B7B7B
        4040404040404040404040404040404040402F2F2F0000000000002C2C2CE9E9
        E9FFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFBBBB
        BB0000002C2C2CE9E9E9FFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFBBBBBB2C2C2CE9E9E9FFFFFFFFFFFFFFFFFF0000FFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFD9D9D9E9E9E9FFFFFFFF
        FFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        0000}
      OnClick = OnCh1RightShiftBtnClick
    end
    object KCh2LeftShiftBtn: TSpeedButton
      Left = 541
      Top = 47
      Width = 23
      Height = 22
      Anchors = [akTop, akRight]
      Glyph.Data = {
        9E020000424D9E0200000000000036000000280000000E0000000E0000000100
        1800000000006802000074120000741200000000000000000000FFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFE9E9
        E9D9D9D9FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFF
        FFFFFFFFFFFFFFE9E9E92C2C2CBBBBBBFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFF0000FFFFFFFFFFFFE9E9E92C2C2C000000BBBBBBFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFE9E9E92C2C2C00
        00000000002F2F2F4040404040404040404040404040404040407B7B7BFFFFFF
        0000E9E9E92C2C2C000000000000000000000000000000000000000000000000
        000000000000333333FFFFFF0000E9E9E9282828000000000000000000000000
        000000000000000000000000000000000000333333FFFFFF0000FFFFFFE6E6E6
        2828280000000000002F2F2F4040404040404040404040404040404040407B7B
        7BFFFFFF0000FFFFFFFFFFFFE6E6E6282828000000BBBBBBFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFE6E6E62828
        28BBBBBBFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFF
        FFFFFFFFFFFFFFFFFFFFE6E6E6D9D9D9FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        0000}
      OnClick = OnCh2LeftShiftBtnClick
    end
    object KCh2RightShiftBtn: TSpeedButton
      Left = 564
      Top = 47
      Width = 23
      Height = 22
      Anchors = [akTop, akRight]
      Glyph.Data = {
        9E020000424D9E0200000000000036000000280000000E0000000E0000000100
        1800000000006802000074120000741200000000000000000000FFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFD9D9D9E6E6E6FFFFFFFFFFFFFFFFFFFFFFFF0000FFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFBBBBBB282828E6E6E6FF
        FFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFBBBBBB000000282828E6E6E6FFFFFFFFFFFF0000FFFFFF7B7B7B40404040
        40404040404040404040404040402F2F2F000000000000282828E6E6E6FFFFFF
        0000FFFFFF333333000000000000000000000000000000000000000000000000
        000000000000282828E9E9E90000FFFFFF333333000000000000000000000000
        0000000000000000000000000000000000002C2C2CE9E9E90000FFFFFF7B7B7B
        4040404040404040404040404040404040402F2F2F0000000000002C2C2CE9E9
        E9FFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFBBBB
        BB0000002C2C2CE9E9E9FFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFBBBBBB2C2C2CE9E9E9FFFFFFFFFFFFFFFFFF0000FFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFD9D9D9E9E9E9FFFFFFFF
        FFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        0000}
      OnClick = OnCh2RightShiftBtnClick
    end
    object KCh2Label: TLabel
      Left = 521
      Top = 9
      Width = 17
      Height = 13
      Anchors = [akTop, akRight]
      Caption = 'K2:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
    end
    object KCh1Label: TLabel
      Left = 444
      Top = 9
      Width = 17
      Height = 13
      Anchors = [akTop, akRight]
      Caption = 'K1:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
    end
    object KChart: TChart
      Tag = -1
      Left = 0
      Top = 0
      Width = 440
      Height = 100
      AllowPanning = pmNone
      BottomWall.Visible = False
      LeftWall.Visible = False
      Legend.LegendStyle = lsSeries
      Legend.TextStyle = ltsValue
      Legend.Visible = False
      MarginBottom = 1
      MarginLeft = 1
      MarginRight = 1
      MarginTop = 1
      Title.Font.Charset = RUSSIAN_CHARSET
      Title.Font.Name = 'Microsoft Sans Serif'
      Title.Font.Style = [fsBold]
      Title.Text.Strings = (
        'K-40')
      BottomAxis.Automatic = False
      BottomAxis.AutomaticMaximum = False
      BottomAxis.AutomaticMinimum = False
      BottomAxis.Axis.Width = 1
      BottomAxis.Increment = 400.000000000000000000
      BottomAxis.LabelsFormat.Font.Name = 'Tahoma'
      BottomAxis.LabelsFormat.Margins.Left = 0
      BottomAxis.LabelsFormat.Margins.Top = 0
      BottomAxis.LabelsFormat.Margins.Right = 0
      BottomAxis.LabelsFormat.Margins.Bottom = 0
      BottomAxis.Maximum = 3000.000000000000000000
      BottomAxis.TickLength = 2
      BottomAxis.Title.Caption = 'E, keV'
      BottomAxis.Title.Font.Name = 'Tahoma'
      BottomAxis.Title.RoundSize = 12
      BottomAxis.Title.ShapeStyle = fosRoundRectangle
      LeftAxis.Automatic = False
      LeftAxis.AutomaticMinimum = False
      LeftAxis.Axis.Width = 1
      LeftAxis.AxisValuesFormat = '00e-0'
      LeftAxis.LabelsFormat.Font.Name = 'Tahoma'
      LeftAxis.LabelsFormat.Margins.Left = 0
      LeftAxis.LabelsFormat.Margins.Top = 0
      LeftAxis.LabelsFormat.Margins.Right = 0
      LeftAxis.LabelsFormat.Margins.Bottom = 0
      LeftAxis.Logarithmic = True
      LeftAxis.Title.Caption = 'Impuls'
      LeftAxis.Title.Font.Name = 'Tahoma'
      Panning.MouseWheel = pmwNone
      RightAxis.Automatic = False
      RightAxis.AutomaticMaximum = False
      RightAxis.AutomaticMinimum = False
      RightAxis.Visible = False
      TopAxis.Automatic = False
      TopAxis.AutomaticMaximum = False
      TopAxis.AutomaticMinimum = False
      TopAxis.Visible = False
      View3D = False
      Zoom.Allow = False
      Align = alLeft
      Color = clMedGray
      TabStop = False
      TabOrder = 4
      Anchors = [akLeft, akTop, akRight, akBottom]
      OnMouseMove = OnChartMouseMove
      DefaultCanvas = 'TGDIPlusCanvas'
      PrintMargins = (
        15
        37
        15
        37)
      ColorPaletteIndex = 13
      object KSpectrum: TLineSeries
        SeriesColor = clBlue
        Title = 'Spc'
        Brush.BackColor = clDefault
        Pointer.InflateMargins = True
        Pointer.Style = psRectangle
        XValues.Name = 'X'
        XValues.Order = loAscending
        YValues.Name = 'Y'
        YValues.Order = loNone
        Data = {0000000000}
        Detail = {0000000000}
      end
    end
    object KDValEdit1: TEdit
      Left = 464
      Top = 29
      Width = 26
      Height = 18
      Anchors = [akTop, akRight]
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -8
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
    end
    object KDValEdit2: TEdit
      Left = 541
      Top = 29
      Width = 26
      Height = 18
      Anchors = [akTop, akRight]
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -8
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
    end
    object KChan2Edit: TEdit
      Left = 541
      Top = 6
      Width = 45
      Height = 21
      Anchors = [akTop, akRight]
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
      TabOrder = 1
      OnChange = OnShiftingDataChange
    end
    object KChan1Edit: TEdit
      Left = 464
      Top = 6
      Width = 45
      Height = 21
      Anchors = [akTop, akRight]
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
      TabOrder = 0
      OnChange = OnShiftingDataChange
    end
  end
  object CsPanel: TPanel
    Left = 805
    Top = 560
    Width = 593
    Height = 104
    Anchors = [akTop, akRight]
    BevelKind = bkFlat
    BevelOuter = bvNone
    DoubleBuffered = True
    ParentDoubleBuffered = False
    TabOrder = 10
    DesignSize = (
      589
      100)
    object CsCh1LeftShiftBtn: TSpeedButton
      Left = 464
      Top = 48
      Width = 23
      Height = 22
      Anchors = [akTop, akRight]
      Glyph.Data = {
        9E020000424D9E0200000000000036000000280000000E0000000E0000000100
        1800000000006802000074120000741200000000000000000000FFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFE9E9
        E9D9D9D9FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFF
        FFFFFFFFFFFFFFE9E9E92C2C2CBBBBBBFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFF0000FFFFFFFFFFFFE9E9E92C2C2C000000BBBBBBFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFE9E9E92C2C2C00
        00000000002F2F2F4040404040404040404040404040404040407B7B7BFFFFFF
        0000E9E9E92C2C2C000000000000000000000000000000000000000000000000
        000000000000333333FFFFFF0000E9E9E9282828000000000000000000000000
        000000000000000000000000000000000000333333FFFFFF0000FFFFFFE6E6E6
        2828280000000000002F2F2F4040404040404040404040404040404040407B7B
        7BFFFFFF0000FFFFFFFFFFFFE6E6E6282828000000BBBBBBFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFE6E6E62828
        28BBBBBBFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFF
        FFFFFFFFFFFFFFFFFFFFE6E6E6D9D9D9FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        0000}
      OnClick = OnCh1LeftShiftBtnClick
    end
    object CsCh1RightShiftBtn: TSpeedButton
      Left = 487
      Top = 48
      Width = 23
      Height = 22
      Anchors = [akTop, akRight]
      Glyph.Data = {
        9E020000424D9E0200000000000036000000280000000E0000000E0000000100
        1800000000006802000074120000741200000000000000000000FFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFD9D9D9E6E6E6FFFFFFFFFFFFFFFFFFFFFFFF0000FFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFBBBBBB282828E6E6E6FF
        FFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFBBBBBB000000282828E6E6E6FFFFFFFFFFFF0000FFFFFF7B7B7B40404040
        40404040404040404040404040402F2F2F000000000000282828E6E6E6FFFFFF
        0000FFFFFF333333000000000000000000000000000000000000000000000000
        000000000000282828E9E9E90000FFFFFF333333000000000000000000000000
        0000000000000000000000000000000000002C2C2CE9E9E90000FFFFFF7B7B7B
        4040404040404040404040404040404040402F2F2F0000000000002C2C2CE9E9
        E9FFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFBBBB
        BB0000002C2C2CE9E9E9FFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFBBBBBB2C2C2CE9E9E9FFFFFFFFFFFFFFFFFF0000FFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFD9D9D9E9E9E9FFFFFFFF
        FFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        0000}
      OnClick = OnCh1RightShiftBtnClick
    end
    object CsCh2LeftShiftBtn: TSpeedButton
      Left = 538
      Top = 48
      Width = 23
      Height = 22
      Anchors = [akTop, akRight]
      Glyph.Data = {
        9E020000424D9E0200000000000036000000280000000E0000000E0000000100
        1800000000006802000074120000741200000000000000000000FFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFE9E9
        E9D9D9D9FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFF
        FFFFFFFFFFFFFFE9E9E92C2C2CBBBBBBFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFF0000FFFFFFFFFFFFE9E9E92C2C2C000000BBBBBBFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFE9E9E92C2C2C00
        00000000002F2F2F4040404040404040404040404040404040407B7B7BFFFFFF
        0000E9E9E92C2C2C000000000000000000000000000000000000000000000000
        000000000000333333FFFFFF0000E9E9E9282828000000000000000000000000
        000000000000000000000000000000000000333333FFFFFF0000FFFFFFE6E6E6
        2828280000000000002F2F2F4040404040404040404040404040404040407B7B
        7BFFFFFF0000FFFFFFFFFFFFE6E6E6282828000000BBBBBBFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFE6E6E62828
        28BBBBBBFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFF
        FFFFFFFFFFFFFFFFFFFFE6E6E6D9D9D9FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        0000}
      OnClick = OnCh2LeftShiftBtnClick
    end
    object CsCh2RightShiftBtn: TSpeedButton
      Left = 561
      Top = 48
      Width = 23
      Height = 22
      Anchors = [akTop, akRight]
      Glyph.Data = {
        9E020000424D9E0200000000000036000000280000000E0000000E0000000100
        1800000000006802000074120000741200000000000000000000FFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFD9D9D9E6E6E6FFFFFFFFFFFFFFFFFFFFFFFF0000FFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFBBBBBB282828E6E6E6FF
        FFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFBBBBBB000000282828E6E6E6FFFFFFFFFFFF0000FFFFFF7B7B7B40404040
        40404040404040404040404040402F2F2F000000000000282828E6E6E6FFFFFF
        0000FFFFFF333333000000000000000000000000000000000000000000000000
        000000000000282828E9E9E90000FFFFFF333333000000000000000000000000
        0000000000000000000000000000000000002C2C2CE9E9E90000FFFFFF7B7B7B
        4040404040404040404040404040404040402F2F2F0000000000002C2C2CE9E9
        E9FFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFBBBB
        BB0000002C2C2CE9E9E9FFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFBBBBBB2C2C2CE9E9E9FFFFFFFFFFFFFFFFFF0000FFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFD9D9D9E9E9E9FFFFFFFF
        FFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        0000}
      OnClick = OnCh2RightShiftBtnClick
    end
    object CsCh2Label: TLabel
      Left = 521
      Top = 9
      Width = 17
      Height = 13
      Anchors = [akTop, akRight]
      Caption = 'K2:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
    end
    object CsCh1Label: TLabel
      Left = 444
      Top = 9
      Width = 17
      Height = 13
      Anchors = [akTop, akRight]
      Caption = 'K1:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
    end
    object CsChart: TChart
      Tag = -1
      Left = 0
      Top = 0
      Width = 440
      Height = 100
      AllowPanning = pmNone
      BottomWall.Visible = False
      LeftWall.Visible = False
      Legend.LegendStyle = lsSeries
      Legend.TextStyle = ltsValue
      Legend.Visible = False
      MarginBottom = 1
      MarginLeft = 1
      MarginRight = 1
      MarginTop = 1
      Title.Font.Charset = RUSSIAN_CHARSET
      Title.Font.Name = 'Microsoft Sans Serif'
      Title.Font.Style = [fsBold]
      Title.Text.Strings = (
        'Cs-137')
      BottomAxis.Automatic = False
      BottomAxis.AutomaticMaximum = False
      BottomAxis.AutomaticMinimum = False
      BottomAxis.Axis.Width = 1
      BottomAxis.Increment = 400.000000000000000000
      BottomAxis.LabelsFormat.Font.Name = 'Tahoma'
      BottomAxis.LabelsFormat.Margins.Left = 0
      BottomAxis.LabelsFormat.Margins.Top = 0
      BottomAxis.LabelsFormat.Margins.Right = 0
      BottomAxis.LabelsFormat.Margins.Bottom = 0
      BottomAxis.Maximum = 3000.000000000000000000
      BottomAxis.TickLength = 2
      BottomAxis.Title.Caption = 'E, keV'
      BottomAxis.Title.Font.Name = 'Tahoma'
      BottomAxis.Title.RoundSize = 12
      BottomAxis.Title.ShapeStyle = fosRoundRectangle
      LeftAxis.Automatic = False
      LeftAxis.AutomaticMinimum = False
      LeftAxis.Axis.Width = 1
      LeftAxis.AxisValuesFormat = '00e-0'
      LeftAxis.LabelsFormat.Font.Name = 'Tahoma'
      LeftAxis.LabelsFormat.Margins.Left = 0
      LeftAxis.LabelsFormat.Margins.Top = 0
      LeftAxis.LabelsFormat.Margins.Right = 0
      LeftAxis.LabelsFormat.Margins.Bottom = 0
      LeftAxis.Logarithmic = True
      LeftAxis.Title.Caption = 'Impuls'
      LeftAxis.Title.Font.Name = 'Tahoma'
      Panning.MouseWheel = pmwNone
      RightAxis.Automatic = False
      RightAxis.AutomaticMaximum = False
      RightAxis.AutomaticMinimum = False
      RightAxis.Visible = False
      TopAxis.Automatic = False
      TopAxis.AutomaticMaximum = False
      TopAxis.AutomaticMinimum = False
      TopAxis.Visible = False
      View3D = False
      Zoom.Allow = False
      Align = alLeft
      Color = clMedGray
      TabStop = False
      TabOrder = 4
      Anchors = [akLeft, akTop, akRight, akBottom]
      OnMouseMove = OnChartMouseMove
      DefaultCanvas = 'TGDIPlusCanvas'
      PrintMargins = (
        15
        37
        15
        37)
      ColorPaletteIndex = 13
      object CsSpectrum: TLineSeries
        SeriesColor = clBlue
        Title = 'Spc'
        Brush.BackColor = clDefault
        Pointer.InflateMargins = True
        Pointer.Style = psRectangle
        XValues.Name = 'X'
        XValues.Order = loAscending
        YValues.Name = 'Y'
        YValues.Order = loNone
        Data = {0000000000}
        Detail = {0000000000}
      end
    end
    object CsDValEdit1: TEdit
      Left = 464
      Top = 29
      Width = 26
      Height = 18
      Anchors = [akTop, akRight]
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -8
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
    end
    object CsDValEdit2: TEdit
      Left = 538
      Top = 29
      Width = 26
      Height = 18
      Anchors = [akTop, akRight]
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -8
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
    end
    object CsChan2Edit: TEdit
      Left = 541
      Top = 6
      Width = 45
      Height = 21
      Anchors = [akTop, akRight]
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
      TabOrder = 1
      OnChange = OnShiftingDataChange
    end
    object CsChan1Edit: TEdit
      Left = 464
      Top = 6
      Width = 45
      Height = 21
      Anchors = [akTop, akRight]
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
      TabOrder = 0
      OnChange = OnShiftingDataChange
    end
  end
  object FinalSpcChart: TChart
    Tag = -1
    Left = -1
    Top = 321
    Width = 795
    Height = 389
    AllowPanning = pmNone
    Border.Visible = True
    BottomWall.Visible = False
    LeftWall.Visible = False
    Legend.LegendStyle = lsSeries
    Legend.TextStyle = ltsValue
    Legend.Visible = False
    MarginBottom = 1
    MarginLeft = 1
    MarginRight = 1
    MarginTop = 1
    RightWall.Visible = True
    Title.Font.Name = 'Microsoft Sans Serif'
    Title.Font.Style = [fsBold]
    Title.Margins.Left = 0
    Title.Margins.Top = 0
    Title.Margins.Right = 0
    Title.Margins.Bottom = 0
    Title.Text.Strings = (
      'Natijaviy spektr')
    BottomAxis.Automatic = False
    BottomAxis.AutomaticMaximum = False
    BottomAxis.AutomaticMinimum = False
    BottomAxis.Axis.Width = 1
    BottomAxis.Increment = 400.000000000000000000
    BottomAxis.LabelsFormat.Font.Name = 'Tahoma'
    BottomAxis.Maximum = 3000.000000000000000000
    BottomAxis.TickLength = 2
    BottomAxis.Title.Caption = 'E, keV'
    BottomAxis.Title.Font.Name = 'Tahoma'
    BottomAxis.Title.RoundSize = 12
    BottomAxis.Title.ShapeStyle = fosRoundRectangle
    LeftAxis.Automatic = False
    LeftAxis.AutomaticMinimum = False
    LeftAxis.Axis.Width = 1
    LeftAxis.Increment = 250.000000000000000000
    LeftAxis.LabelsFormat.Font.Name = 'Tahoma'
    LeftAxis.LabelsFormat.Margins.Left = 0
    LeftAxis.LabelsFormat.Margins.Top = 0
    LeftAxis.LabelsFormat.Margins.Right = 0
    LeftAxis.LabelsFormat.Margins.Bottom = 0
    LeftAxis.Minimum = -500.000000000000000000
    LeftAxis.Title.Caption = 'Impuls'
    LeftAxis.Title.Font.Name = 'Tahoma'
    Panning.MouseWheel = pmwNone
    RightAxis.Automatic = False
    RightAxis.AutomaticMaximum = False
    RightAxis.AutomaticMinimum = False
    RightAxis.Axis.Width = 1
    RightAxis.Labels = False
    RightAxis.LabelsFormat.Visible = False
    TopAxis.Automatic = False
    TopAxis.AutomaticMaximum = False
    TopAxis.AutomaticMinimum = False
    TopAxis.Labels = False
    TopAxis.LabelsFormat.Visible = False
    TopAxis.Ticks.Visible = False
    View3D = False
    Zoom.Allow = False
    Color = clMedGray
    TabStop = False
    TabOrder = 11
    OnMouseMove = OnChartMouseMove
    DefaultCanvas = 'TGDIPlusCanvas'
    PrintMargins = (
      15
      37
      15
      37)
    ColorPaletteIndex = 13
    object FinalSpectrum: TLineSeries
      SeriesColor = clBlue
      Title = 'Spc'
      Brush.BackColor = clDefault
      Dark3D = False
      Pointer.InflateMargins = True
      Pointer.Style = psRectangle
      XValues.Name = 'X'
      XValues.Order = loAscending
      YValues.Name = 'Y'
      YValues.Order = loNone
      Data = {0000000000}
      Detail = {0000000000}
    end
  end
  object ThInfoPanel: TPanel
    Left = 0
    Top = 40
    Width = 155
    Height = 278
    Alignment = taLeftJustify
    BevelKind = bkFlat
    BevelOuter = bvNone
    BorderWidth = 2
    DoubleBuffered = True
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentDoubleBuffered = False
    ParentFont = False
    TabOrder = 0
    VerticalAlignment = taAlignTop
    DesignSize = (
      151
      274)
    object ThDurLabel: TLabel
      Left = 2
      Top = 41
      Width = 85
      Height = 13
      Caption = 'O'#39'lch. vaqti (sek):'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object ThPhotoPeakLabel: TLabel
      Left = 2
      Top = 65
      Width = 78
      Height = 13
      Caption = 'Fotocho'#39'qqi, Se:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object ThActLabel: TLabel
      Left = 2
      Top = 89
      Width = 62
      Height = 13
      Caption = 'Aktivligi (Bk):'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object ThMDALabel: TLabel
      Left = 2
      Top = 205
      Width = 63
      Height = 13
      Caption = 'AMA (Bk/kg):'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
    end
    object ThLabel: TLabel
      Left = 2
      Top = 23
      Width = 85
      Height = 11
      Alignment = taCenter
      Caption = 'Etalon namunada'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -9
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object ThSmpLabel: TLabel
      Left = 2
      Top = 115
      Width = 133
      Height = 11
      Alignment = taCenter
      Caption = 'O'#39'rganilayotgan namunada'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -9
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object ThCoeffLabel: TLabel
      Left = 2
      Top = 181
      Width = 38
      Height = 13
      Caption = 'Sn / Se:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
    end
    object ThCoeffCalcLabel: TLabel
      Left = 2
      Top = 157
      Width = 43
      Height = 13
      Cursor = crHandPoint
      Caption = 'Sn / Se:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold, fsUnderline]
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
      OnClick = ThCoeffCalcLabelClick
    end
    object SmpThPhotoPeakLabel: TLabel
      Left = 2
      Top = 133
      Width = 78
      Height = 13
      Caption = 'Fotocho'#39'qqi, Sn:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object SmpThErrorLabel: TLabel
      Left = 2
      Top = 253
      Width = 72
      Height = 13
      Caption = 'Xatolik (Bk/kg):'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object SmpThActLabel: TLabel
      Left = 2
      Top = 229
      Width = 77
      Height = 13
      Caption = 'Aktivligi (Bk/kg):'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object ThUpButton: TSpeedButton
      Left = 59
      Top = 178
      Width = 21
      Height = 21
      Anchors = [akTop, akRight]
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Arial'
      Font.Style = [fsBold]
      Glyph.Data = {
        9E020000424D9E0200000000000036000000280000000E0000000E0000000100
        1800000000006802000074120000741200000000000000000000FFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF7B7B7B3333333333337B7B
        7BFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FF404040000000000000404040FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFF404040000000000000404040FFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF40404000000000
        0000404040FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFF404040000000000000404040FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF404040000000000000404040FFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF404040
        000000000000404040FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFF
        D9D9D9BBBBBBBBBBBB2F2F2F0000000000002F2F2FBBBBBBBBBBBBD9D9D9FFFF
        FFFFFFFF0000FFFFFFFFFFFFE9E9E92C2C2C0000000000000000000000000000
        00000000282828E6E6E6FFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFE9E9E92C2C
        2C000000000000000000000000282828E6E6E6FFFFFFFFFFFFFFFFFF0000FFFF
        FFFFFFFFFFFFFFFFFFFFE9E9E92C2C2C000000000000282828E6E6E6FFFFFFFF
        FFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFE9E9E92C2C2C28
        2828E6E6E6FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFE9E9E9E9E9E9FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        0000}
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
      OnClick = OnEditUpButtonClick
    end
    object ThDownButton: TSpeedButton
      Left = 80
      Top = 178
      Width = 21
      Height = 21
      Anchors = [akTop, akRight]
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Arial'
      Font.Style = [fsBold]
      Glyph.Data = {
        9E020000424D9E0200000000000036000000280000000E0000000E0000000100
        1800000000006802000074120000741200000000000000000000FFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFE9E9E9E9E9E9FFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFE6E6E62828282C2C2CE9E9
        E9FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFE6E6
        E62828280000000000002C2C2CE9E9E9FFFFFFFFFFFFFFFFFFFFFFFF0000FFFF
        FFFFFFFFFFFFFFE6E6E62828280000000000000000000000002C2C2CE9E9E9FF
        FFFFFFFFFFFFFFFF0000FFFFFFFFFFFFE6E6E628282800000000000000000000
        00000000000000002C2C2CE9E9E9FFFFFFFFFFFF0000FFFFFFFFFFFFD9D9D9BB
        BBBBBBBBBB2F2F2F0000000000002F2F2FBBBBBBBBBBBBD9D9D9FFFFFFFFFFFF
        0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF404040000000000000404040FFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF404040
        000000000000404040FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFF404040000000000000404040FFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF4040400000000000004040
        40FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FF404040000000000000404040FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFF404040000000000000404040FFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF7B7B7B33333333
        33337B7B7BFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        0000}
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
      OnClick = OnEditDownButtonClick
    end
    object Label1: TLabel
      Left = 2
      Top = 2
      Width = 147
      Height = 16
      Align = alTop
      Alignment = taCenter
      Caption = 'Th-232'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      ExplicitWidth = 45
    end
    object ThTime: TEdit
      Left = 89
      Top = 40
      Width = 61
      Height = 21
      TabStop = False
      Alignment = taRightJustify
      Anchors = [akTop, akRight]
      BorderStyle = bsNone
      Color = clBtnFace
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ReadOnly = True
      TabOrder = 0
    end
    object ThSum: TEdit
      Left = 89
      Top = 64
      Width = 61
      Height = 21
      TabStop = False
      Alignment = taRightJustify
      Anchors = [akTop, akRight]
      BorderStyle = bsNone
      Color = clBtnFace
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ReadOnly = True
      TabOrder = 1
    end
    object ThActivity: TEdit
      Left = 89
      Top = 88
      Width = 61
      Height = 21
      TabStop = False
      Alignment = taRightJustify
      Anchors = [akTop, akRight]
      BorderStyle = bsNone
      Color = clBtnFace
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ReadOnly = True
      TabOrder = 2
    end
    object ThMDA: TEdit
      Left = 89
      Top = 204
      Width = 61
      Height = 21
      TabStop = False
      Alignment = taRightJustify
      Anchors = [akTop, akRight]
      BorderStyle = bsNone
      Color = clBtnFace
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ParentShowHint = False
      ReadOnly = True
      ShowHint = True
      TabOrder = 6
    end
    object SampleThActivity: TEdit
      Left = 89
      Top = 228
      Width = 61
      Height = 21
      TabStop = False
      Alignment = taRightJustify
      Anchors = [akTop, akRight]
      BorderStyle = bsNone
      Color = clBtnFace
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ReadOnly = True
      TabOrder = 7
    end
    object ThSnSe2: TEdit
      Left = 102
      Top = 178
      Width = 48
      Height = 21
      Alignment = taRightJustify
      Anchors = [akTop, akRight]
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 5
      OnChange = OnParamChange
      OnClick = ParamEditClick
      OnKeyDown = OnKeyDown
    end
    object ThSnSe1: TEdit
      Left = 89
      Top = 156
      Width = 61
      Height = 21
      TabStop = False
      Alignment = taRightJustify
      Anchors = [akTop, akRight]
      BorderStyle = bsNone
      Color = clBtnFace
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ReadOnly = True
      TabOrder = 4
    end
    object SampleThSum: TEdit
      Left = 89
      Top = 132
      Width = 61
      Height = 21
      TabStop = False
      Alignment = taRightJustify
      Anchors = [akTop, akRight]
      BorderStyle = bsNone
      Color = clBtnFace
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ReadOnly = True
      TabOrder = 3
    end
    object SampleThError: TEdit
      Left = 89
      Top = 252
      Width = 61
      Height = 21
      TabStop = False
      Alignment = taRightJustify
      Anchors = [akTop, akRight]
      BorderStyle = bsNone
      Color = clBtnFace
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ReadOnly = True
      TabOrder = 8
    end
  end
  object RaInfoPanel: TPanel
    Left = 159
    Top = 40
    Width = 155
    Height = 278
    Alignment = taLeftJustify
    BevelKind = bkFlat
    BevelOuter = bvNone
    BorderWidth = 2
    DoubleBuffered = True
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentDoubleBuffered = False
    ParentFont = False
    TabOrder = 1
    VerticalAlignment = taAlignTop
    DesignSize = (
      151
      274)
    object RaDurLabel: TLabel
      Left = 2
      Top = 41
      Width = 85
      Height = 13
      Caption = 'O'#39'lch. vaqti (sek):'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object RaPhotoPeakLabel: TLabel
      Left = 2
      Top = 65
      Width = 78
      Height = 13
      Caption = 'Fotocho'#39'qqi, Se:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object RaActLabel: TLabel
      Left = 2
      Top = 89
      Width = 62
      Height = 13
      Caption = 'Aktivligi (Bk):'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object RaMDALabel: TLabel
      Left = 2
      Top = 205
      Width = 63
      Height = 13
      Caption = 'AMA (Bk/kg):'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
    end
    object RaLabel: TLabel
      Left = 2
      Top = 23
      Width = 85
      Height = 11
      Alignment = taCenter
      Caption = 'Etalon namunada'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -9
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object RaSmpLabel: TLabel
      Left = 2
      Top = 115
      Width = 133
      Height = 11
      Alignment = taCenter
      Caption = 'O'#39'rganilayotgan namunada'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -9
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object RaCoeffLabel: TLabel
      Left = 2
      Top = 181
      Width = 38
      Height = 13
      Caption = 'Sn / Se:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
    end
    object RaCoeffCalcLabel: TLabel
      Left = 2
      Top = 157
      Width = 43
      Height = 13
      Cursor = crHandPoint
      Caption = 'Sn / Se:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold, fsUnderline]
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
      OnClick = RaCoeffCalcLabelClick
    end
    object SmpRaPhotoPeakLabel: TLabel
      Left = 2
      Top = 133
      Width = 78
      Height = 13
      Caption = 'Fotocho'#39'qqi, Sn:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object SmpRaErrorLabel: TLabel
      Left = 2
      Top = 253
      Width = 72
      Height = 13
      Caption = 'Xatolik (Bk/kg):'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object SmpRaActLabel: TLabel
      Left = 2
      Top = 229
      Width = 77
      Height = 13
      Caption = 'Aktivligi (Bk/kg):'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object RaDownButton: TSpeedButton
      Left = 80
      Top = 178
      Width = 21
      Height = 21
      Anchors = [akTop, akRight]
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Arial'
      Font.Style = [fsBold]
      Glyph.Data = {
        9E020000424D9E0200000000000036000000280000000E0000000E0000000100
        1800000000006802000074120000741200000000000000000000FFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFE9E9E9E9E9E9FFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFE6E6E62828282C2C2CE9E9
        E9FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFE6E6
        E62828280000000000002C2C2CE9E9E9FFFFFFFFFFFFFFFFFFFFFFFF0000FFFF
        FFFFFFFFFFFFFFE6E6E62828280000000000000000000000002C2C2CE9E9E9FF
        FFFFFFFFFFFFFFFF0000FFFFFFFFFFFFE6E6E628282800000000000000000000
        00000000000000002C2C2CE9E9E9FFFFFFFFFFFF0000FFFFFFFFFFFFD9D9D9BB
        BBBBBBBBBB2F2F2F0000000000002F2F2FBBBBBBBBBBBBD9D9D9FFFFFFFFFFFF
        0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF404040000000000000404040FFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF404040
        000000000000404040FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFF404040000000000000404040FFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF4040400000000000004040
        40FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FF404040000000000000404040FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFF404040000000000000404040FFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF7B7B7B33333333
        33337B7B7BFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        0000}
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
      OnClick = OnEditDownButtonClick
    end
    object RaUpButton: TSpeedButton
      Left = 59
      Top = 178
      Width = 21
      Height = 21
      Anchors = [akTop, akRight]
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Arial'
      Font.Style = [fsBold]
      Glyph.Data = {
        9E020000424D9E0200000000000036000000280000000E0000000E0000000100
        1800000000006802000074120000741200000000000000000000FFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF7B7B7B3333333333337B7B
        7BFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FF404040000000000000404040FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFF404040000000000000404040FFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF40404000000000
        0000404040FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFF404040000000000000404040FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF404040000000000000404040FFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF404040
        000000000000404040FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFF
        D9D9D9BBBBBBBBBBBB2F2F2F0000000000002F2F2FBBBBBBBBBBBBD9D9D9FFFF
        FFFFFFFF0000FFFFFFFFFFFFE9E9E92C2C2C0000000000000000000000000000
        00000000282828E6E6E6FFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFE9E9E92C2C
        2C000000000000000000000000282828E6E6E6FFFFFFFFFFFFFFFFFF0000FFFF
        FFFFFFFFFFFFFFFFFFFFE9E9E92C2C2C000000000000282828E6E6E6FFFFFFFF
        FFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFE9E9E92C2C2C28
        2828E6E6E6FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFE9E9E9E9E9E9FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        0000}
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
      OnClick = OnEditUpButtonClick
    end
    object Label2: TLabel
      Left = 2
      Top = 2
      Width = 147
      Height = 16
      Align = alTop
      Alignment = taCenter
      Caption = 'Ra-226'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      ExplicitWidth = 47
    end
    object RaTime: TEdit
      Left = 89
      Top = 40
      Width = 61
      Height = 21
      TabStop = False
      Alignment = taRightJustify
      Anchors = [akTop, akRight]
      BorderStyle = bsNone
      Color = clBtnFace
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ReadOnly = True
      TabOrder = 0
    end
    object RaSum: TEdit
      Left = 89
      Top = 64
      Width = 61
      Height = 21
      TabStop = False
      Alignment = taRightJustify
      Anchors = [akTop, akRight]
      BorderStyle = bsNone
      Color = clBtnFace
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ReadOnly = True
      TabOrder = 1
    end
    object RaActivity: TEdit
      Left = 89
      Top = 88
      Width = 61
      Height = 21
      TabStop = False
      Alignment = taRightJustify
      Anchors = [akTop, akRight]
      BorderStyle = bsNone
      Color = clBtnFace
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ReadOnly = True
      TabOrder = 2
    end
    object RaMDA: TEdit
      Left = 89
      Top = 204
      Width = 61
      Height = 21
      TabStop = False
      Alignment = taRightJustify
      Anchors = [akTop, akRight]
      BorderStyle = bsNone
      Color = clBtnFace
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ParentShowHint = False
      ReadOnly = True
      ShowHint = True
      TabOrder = 6
    end
    object SampleRaActivity: TEdit
      Left = 89
      Top = 228
      Width = 61
      Height = 21
      TabStop = False
      Alignment = taRightJustify
      Anchors = [akTop, akRight]
      BorderStyle = bsNone
      Color = clBtnFace
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ReadOnly = True
      TabOrder = 7
    end
    object RaSnSe2: TEdit
      Left = 102
      Top = 178
      Width = 48
      Height = 21
      Alignment = taRightJustify
      Anchors = [akTop, akRight]
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 5
      OnChange = OnParamChange
      OnClick = ParamEditClick
      OnKeyDown = OnKeyDown
    end
    object RaSnSe1: TEdit
      Left = 89
      Top = 156
      Width = 61
      Height = 21
      TabStop = False
      Alignment = taRightJustify
      Anchors = [akTop, akRight]
      BorderStyle = bsNone
      Color = clBtnFace
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ReadOnly = True
      TabOrder = 4
    end
    object SampleRaSum: TEdit
      Left = 89
      Top = 132
      Width = 61
      Height = 21
      TabStop = False
      Alignment = taRightJustify
      Anchors = [akTop, akRight]
      BorderStyle = bsNone
      Color = clBtnFace
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ReadOnly = True
      TabOrder = 3
    end
    object SampleRaError: TEdit
      Left = 89
      Top = 252
      Width = 61
      Height = 21
      TabStop = False
      Alignment = taRightJustify
      Anchors = [akTop, akRight]
      BorderStyle = bsNone
      Color = clBtnFace
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ReadOnly = True
      TabOrder = 8
    end
  end
  object KInfoPanel: TPanel
    Left = 318
    Top = 40
    Width = 155
    Height = 278
    Alignment = taLeftJustify
    BevelKind = bkFlat
    BevelOuter = bvNone
    BorderWidth = 2
    DoubleBuffered = True
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentDoubleBuffered = False
    ParentFont = False
    TabOrder = 2
    VerticalAlignment = taAlignTop
    DesignSize = (
      151
      274)
    object KDurLabel: TLabel
      Left = 2
      Top = 41
      Width = 85
      Height = 13
      Caption = 'O'#39'lch. vaqti (sek):'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object KPhotoPeakLabel: TLabel
      Left = 2
      Top = 65
      Width = 78
      Height = 13
      Caption = 'Fotocho'#39'qqi, Se:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object KActLabel: TLabel
      Left = 2
      Top = 89
      Width = 62
      Height = 13
      Caption = 'Aktivligi (Bk):'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object KMDALabel: TLabel
      Left = 2
      Top = 205
      Width = 63
      Height = 13
      Caption = 'AMA (Bk/kg):'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
    end
    object KLabel: TLabel
      Left = 2
      Top = 23
      Width = 85
      Height = 11
      Alignment = taCenter
      Caption = 'Etalon namunada'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -9
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object KSmpLabel: TLabel
      Left = 2
      Top = 115
      Width = 133
      Height = 11
      Alignment = taCenter
      Caption = 'O'#39'rganilayotgan namunada'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -9
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object KCoeffLabel: TLabel
      Left = 2
      Top = 181
      Width = 38
      Height = 13
      Caption = 'Sn / Se:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
    end
    object KCoeffCalcLabel: TLabel
      Left = 2
      Top = 157
      Width = 43
      Height = 13
      Cursor = crHandPoint
      Caption = 'Sn / Se:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold, fsUnderline]
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
      OnClick = KCoeffCalcLabelClick
    end
    object SmpKPhotoPeakLabel: TLabel
      Left = 2
      Top = 133
      Width = 78
      Height = 13
      Caption = 'Fotocho'#39'qqi, Sn:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object SmpKErrorLabel: TLabel
      Left = 2
      Top = 253
      Width = 72
      Height = 13
      Caption = 'Xatolik (Bk/kg):'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object SmpKActLabel: TLabel
      Left = 2
      Top = 229
      Width = 77
      Height = 13
      Caption = 'Aktivligi (Bk/kg):'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object KDownButton: TSpeedButton
      Left = 80
      Top = 178
      Width = 21
      Height = 21
      Anchors = [akTop, akRight]
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Arial'
      Font.Style = [fsBold]
      Glyph.Data = {
        9E020000424D9E0200000000000036000000280000000E0000000E0000000100
        1800000000006802000074120000741200000000000000000000FFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFE9E9E9E9E9E9FFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFE6E6E62828282C2C2CE9E9
        E9FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFE6E6
        E62828280000000000002C2C2CE9E9E9FFFFFFFFFFFFFFFFFFFFFFFF0000FFFF
        FFFFFFFFFFFFFFE6E6E62828280000000000000000000000002C2C2CE9E9E9FF
        FFFFFFFFFFFFFFFF0000FFFFFFFFFFFFE6E6E628282800000000000000000000
        00000000000000002C2C2CE9E9E9FFFFFFFFFFFF0000FFFFFFFFFFFFD9D9D9BB
        BBBBBBBBBB2F2F2F0000000000002F2F2FBBBBBBBBBBBBD9D9D9FFFFFFFFFFFF
        0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF404040000000000000404040FFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF404040
        000000000000404040FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFF404040000000000000404040FFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF4040400000000000004040
        40FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FF404040000000000000404040FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFF404040000000000000404040FFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF7B7B7B33333333
        33337B7B7BFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        0000}
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
      OnClick = OnEditDownButtonClick
    end
    object KUpButton: TSpeedButton
      Left = 59
      Top = 178
      Width = 21
      Height = 21
      Anchors = [akTop, akRight]
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Arial'
      Font.Style = [fsBold]
      Glyph.Data = {
        9E020000424D9E0200000000000036000000280000000E0000000E0000000100
        1800000000006802000074120000741200000000000000000000FFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF7B7B7B3333333333337B7B
        7BFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FF404040000000000000404040FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFF404040000000000000404040FFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF40404000000000
        0000404040FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFF404040000000000000404040FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF404040000000000000404040FFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF404040
        000000000000404040FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFF
        D9D9D9BBBBBBBBBBBB2F2F2F0000000000002F2F2FBBBBBBBBBBBBD9D9D9FFFF
        FFFFFFFF0000FFFFFFFFFFFFE9E9E92C2C2C0000000000000000000000000000
        00000000282828E6E6E6FFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFE9E9E92C2C
        2C000000000000000000000000282828E6E6E6FFFFFFFFFFFFFFFFFF0000FFFF
        FFFFFFFFFFFFFFFFFFFFE9E9E92C2C2C000000000000282828E6E6E6FFFFFFFF
        FFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFE9E9E92C2C2C28
        2828E6E6E6FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFE9E9E9E9E9E9FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        0000}
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
      OnClick = OnEditUpButtonClick
    end
    object Label3: TLabel
      Left = 2
      Top = 2
      Width = 147
      Height = 16
      Align = alTop
      Alignment = taCenter
      Caption = 'K-40'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      ExplicitWidth = 30
    end
    object KTime: TEdit
      Left = 89
      Top = 40
      Width = 61
      Height = 21
      TabStop = False
      Alignment = taRightJustify
      Anchors = [akTop, akRight]
      BorderStyle = bsNone
      Color = clBtnFace
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ReadOnly = True
      TabOrder = 0
    end
    object KSum: TEdit
      Left = 89
      Top = 64
      Width = 61
      Height = 21
      TabStop = False
      Alignment = taRightJustify
      Anchors = [akTop, akRight]
      BorderStyle = bsNone
      Color = clBtnFace
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ReadOnly = True
      TabOrder = 1
    end
    object KActivity: TEdit
      Left = 89
      Top = 88
      Width = 61
      Height = 21
      TabStop = False
      Alignment = taRightJustify
      Anchors = [akTop, akRight]
      BorderStyle = bsNone
      Color = clBtnFace
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ReadOnly = True
      TabOrder = 2
    end
    object KMDA: TEdit
      Left = 89
      Top = 204
      Width = 61
      Height = 21
      TabStop = False
      Alignment = taRightJustify
      Anchors = [akTop, akRight]
      BorderStyle = bsNone
      Color = clBtnFace
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ParentShowHint = False
      ReadOnly = True
      ShowHint = True
      TabOrder = 3
    end
    object SampleKActivity: TEdit
      Left = 89
      Top = 228
      Width = 61
      Height = 21
      TabStop = False
      Alignment = taRightJustify
      Anchors = [akTop, akRight]
      BorderStyle = bsNone
      Color = clBtnFace
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ReadOnly = True
      TabOrder = 4
    end
    object KSnSe2: TEdit
      Left = 102
      Top = 178
      Width = 48
      Height = 21
      Alignment = taRightJustify
      Anchors = [akTop, akRight]
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 5
      OnChange = OnParamChange
      OnClick = ParamEditClick
      OnKeyDown = OnKeyDown
    end
    object KSnSe1: TEdit
      Left = 89
      Top = 156
      Width = 61
      Height = 21
      TabStop = False
      Alignment = taRightJustify
      Anchors = [akTop, akRight]
      BorderStyle = bsNone
      Color = clBtnFace
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ReadOnly = True
      TabOrder = 6
    end
    object SampleKSum: TEdit
      Left = 89
      Top = 132
      Width = 61
      Height = 21
      TabStop = False
      Alignment = taRightJustify
      Anchors = [akTop, akRight]
      BorderStyle = bsNone
      Color = clBtnFace
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ReadOnly = True
      TabOrder = 7
    end
    object SampleKError: TEdit
      Left = 89
      Top = 252
      Width = 61
      Height = 21
      TabStop = False
      Alignment = taRightJustify
      Anchors = [akTop, akRight]
      BorderStyle = bsNone
      Color = clBtnFace
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ReadOnly = True
      TabOrder = 8
    end
  end
  object CsInfoPanel: TPanel
    Left = 477
    Top = 40
    Width = 155
    Height = 278
    Alignment = taLeftJustify
    BevelKind = bkFlat
    BevelOuter = bvNone
    BorderWidth = 2
    DoubleBuffered = True
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentDoubleBuffered = False
    ParentFont = False
    TabOrder = 3
    VerticalAlignment = taAlignTop
    DesignSize = (
      151
      274)
    object CsDurLabel: TLabel
      Left = 2
      Top = 41
      Width = 85
      Height = 13
      Caption = 'O'#39'lch. vaqti (sek):'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object CsPhotoPeakLabel: TLabel
      Left = 2
      Top = 65
      Width = 78
      Height = 13
      Caption = 'Fotocho'#39'qqi, Se:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object CsActLabel: TLabel
      Left = 2
      Top = 89
      Width = 62
      Height = 13
      Caption = 'Aktivligi (Bk):'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object CsMDALabel: TLabel
      Left = 2
      Top = 205
      Width = 63
      Height = 13
      Caption = 'AMA (Bk/kg):'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
    end
    object CsLabel: TLabel
      Left = 2
      Top = 23
      Width = 85
      Height = 11
      Alignment = taCenter
      Caption = 'Etalon namunada'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -9
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object CsSmpLabel: TLabel
      Left = 2
      Top = 115
      Width = 133
      Height = 11
      Alignment = taCenter
      Caption = 'O'#39'rganilayotgan namunada'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -9
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object CsCoeffLabel: TLabel
      Left = 2
      Top = 181
      Width = 38
      Height = 13
      Caption = 'Sn / Se:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
    end
    object CsCoeffCalcLabel: TLabel
      Left = 2
      Top = 157
      Width = 43
      Height = 13
      Cursor = crHandPoint
      Caption = 'Sn / Se:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold, fsUnderline]
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
      OnClick = CsCoeffCalcLabelClick
    end
    object SmpCsPhotoPeakLabel: TLabel
      Left = 2
      Top = 133
      Width = 78
      Height = 13
      Caption = 'Fotocho'#39'qqi, Sn:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object SmpCsErrorLabel: TLabel
      Left = 2
      Top = 253
      Width = 72
      Height = 13
      Caption = 'Xatolik (Bk/kg):'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object SmpCsActLabel: TLabel
      Left = 2
      Top = 229
      Width = 77
      Height = 13
      Caption = 'Aktivligi (Bk/kg):'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object CsDownButton: TSpeedButton
      Left = 80
      Top = 178
      Width = 21
      Height = 21
      Anchors = [akTop, akRight]
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Arial'
      Font.Style = [fsBold]
      Glyph.Data = {
        9E020000424D9E0200000000000036000000280000000E0000000E0000000100
        1800000000006802000074120000741200000000000000000000FFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFE9E9E9E9E9E9FFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFE6E6E62828282C2C2CE9E9
        E9FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFE6E6
        E62828280000000000002C2C2CE9E9E9FFFFFFFFFFFFFFFFFFFFFFFF0000FFFF
        FFFFFFFFFFFFFFE6E6E62828280000000000000000000000002C2C2CE9E9E9FF
        FFFFFFFFFFFFFFFF0000FFFFFFFFFFFFE6E6E628282800000000000000000000
        00000000000000002C2C2CE9E9E9FFFFFFFFFFFF0000FFFFFFFFFFFFD9D9D9BB
        BBBBBBBBBB2F2F2F0000000000002F2F2FBBBBBBBBBBBBD9D9D9FFFFFFFFFFFF
        0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF404040000000000000404040FFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF404040
        000000000000404040FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFF404040000000000000404040FFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF4040400000000000004040
        40FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FF404040000000000000404040FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFF404040000000000000404040FFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF7B7B7B33333333
        33337B7B7BFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        0000}
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
      OnClick = OnEditDownButtonClick
    end
    object CsUpButton: TSpeedButton
      Left = 59
      Top = 178
      Width = 21
      Height = 21
      Anchors = [akTop, akRight]
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Arial'
      Font.Style = [fsBold]
      Glyph.Data = {
        9E020000424D9E0200000000000036000000280000000E0000000E0000000100
        1800000000006802000074120000741200000000000000000000FFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF7B7B7B3333333333337B7B
        7BFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FF404040000000000000404040FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFF404040000000000000404040FFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF40404000000000
        0000404040FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFF404040000000000000404040FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF404040000000000000404040FFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF404040
        000000000000404040FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFF
        D9D9D9BBBBBBBBBBBB2F2F2F0000000000002F2F2FBBBBBBBBBBBBD9D9D9FFFF
        FFFFFFFF0000FFFFFFFFFFFFE9E9E92C2C2C0000000000000000000000000000
        00000000282828E6E6E6FFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFE9E9E92C2C
        2C000000000000000000000000282828E6E6E6FFFFFFFFFFFFFFFFFF0000FFFF
        FFFFFFFFFFFFFFFFFFFFE9E9E92C2C2C000000000000282828E6E6E6FFFFFFFF
        FFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFE9E9E92C2C2C28
        2828E6E6E6FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFE9E9E9E9E9E9FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        0000}
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
      OnClick = OnEditUpButtonClick
    end
    object Label4: TLabel
      Left = 2
      Top = 2
      Width = 147
      Height = 16
      Align = alTop
      Alignment = taCenter
      Caption = 'Cs-137'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      ExplicitWidth = 45
    end
    object CsTime: TEdit
      Left = 89
      Top = 40
      Width = 61
      Height = 21
      TabStop = False
      Alignment = taRightJustify
      Anchors = [akTop, akRight]
      BorderStyle = bsNone
      Color = clBtnFace
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ReadOnly = True
      TabOrder = 0
    end
    object CsSum: TEdit
      Left = 89
      Top = 64
      Width = 61
      Height = 21
      TabStop = False
      Alignment = taRightJustify
      Anchors = [akTop, akRight]
      BorderStyle = bsNone
      Color = clBtnFace
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ReadOnly = True
      TabOrder = 1
    end
    object CsActivity: TEdit
      Left = 89
      Top = 88
      Width = 61
      Height = 21
      TabStop = False
      Alignment = taRightJustify
      Anchors = [akTop, akRight]
      BorderStyle = bsNone
      Color = clBtnFace
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ReadOnly = True
      TabOrder = 2
    end
    object CsMDA: TEdit
      Left = 89
      Top = 204
      Width = 61
      Height = 21
      TabStop = False
      Alignment = taRightJustify
      Anchors = [akTop, akRight]
      BorderStyle = bsNone
      Color = clBtnFace
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ParentShowHint = False
      ReadOnly = True
      ShowHint = True
      TabOrder = 6
    end
    object SampleCsActivity: TEdit
      Left = 89
      Top = 228
      Width = 61
      Height = 21
      TabStop = False
      Alignment = taRightJustify
      Anchors = [akTop, akRight]
      BorderStyle = bsNone
      Color = clBtnFace
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ReadOnly = True
      TabOrder = 7
    end
    object CsSnSe2: TEdit
      Left = 102
      Top = 178
      Width = 48
      Height = 21
      Alignment = taRightJustify
      Anchors = [akTop, akRight]
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 5
      OnChange = OnParamChange
      OnClick = ParamEditClick
      OnKeyDown = OnKeyDown
    end
    object CsSnSe1: TEdit
      Left = 89
      Top = 156
      Width = 61
      Height = 21
      TabStop = False
      Alignment = taRightJustify
      Anchors = [akTop, akRight]
      BorderStyle = bsNone
      Color = clBtnFace
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ReadOnly = True
      TabOrder = 4
    end
    object SampleCsSum: TEdit
      Left = 89
      Top = 132
      Width = 61
      Height = 21
      TabStop = False
      Alignment = taRightJustify
      Anchors = [akTop, akRight]
      BorderStyle = bsNone
      Color = clBtnFace
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ReadOnly = True
      TabOrder = 3
    end
    object SampleCsError: TEdit
      Left = 89
      Top = 252
      Width = 61
      Height = 21
      TabStop = False
      Alignment = taRightJustify
      Anchors = [akTop, akRight]
      BorderStyle = bsNone
      Color = clBtnFace
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ReadOnly = True
      TabOrder = 8
    end
  end
  object SampleInfoPanel: TPanel
    Left = 636
    Top = 40
    Width = 158
    Height = 278
    Alignment = taLeftJustify
    BevelKind = bkFlat
    BevelOuter = bvNone
    BorderWidth = 2
    DoubleBuffered = True
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentDoubleBuffered = False
    ParentFont = False
    TabOrder = 4
    VerticalAlignment = taAlignTop
    DesignSize = (
      154
      274)
    object BePhotoPeakLabel: TLabel
      Left = 2
      Top = 41
      Width = 59
      Height = 13
      Caption = 'Fotocho'#39'qqi:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object BeActLabel: TLabel
      Left = 2
      Top = 89
      Width = 77
      Height = 13
      Cursor = crHandPoint
      Caption = 'Aktivligi (Bk/kg):'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsUnderline]
      ParentFont = False
      OnClick = BeActLabelClick
    end
    object BeMDALabel: TLabel
      Left = 2
      Top = 65
      Width = 63
      Height = 13
      Caption = 'AMA (Bk/kg):'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
    end
    object SmpDensityLabel: TLabel
      Left = 2
      Top = 205
      Width = 66
      Height = 13
      Caption = 'Zichligi (Gr/L):'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object BeErrorLabel: TLabel
      Left = 2
      Top = 112
      Width = 72
      Height = 13
      Caption = 'Xatolik (Bk/kg):'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object SmpTotalMassLabel: TLabel
      Left = 2
      Top = 229
      Width = 85
      Height = 13
      Caption = 'Um. massasi (Gr):'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object SmpSquareLabel: TLabel
      Left = 2
      Top = 253
      Width = 73
      Height = 13
      Caption = 'Yuzasi (Sm^2):'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object SmpLabel: TLabel
      Left = 2
      Top = 138
      Width = 97
      Height = 11
      Alignment = taCenter
      Caption = 'Namuna o'#39'lchamlari'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -9
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object SmpMassLabel: TLabel
      Left = 2
      Top = 180
      Width = 63
      Height = 13
      Caption = 'Massasi (Gr):'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object SmpDurLabel: TLabel
      Left = 2
      Top = 157
      Width = 85
      Height = 13
      Caption = 'O'#39'lch. vaqti (sek):'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object Label5: TLabel
      Left = 2
      Top = 2
      Width = 150
      Height = 16
      Align = alTop
      Alignment = taCenter
      Caption = 'Be-7'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      ExplicitWidth = 30
    end
    object BeSmpLabel: TLabel
      Left = 2
      Top = 23
      Width = 133
      Height = 11
      Alignment = taCenter
      Caption = 'O'#39'rganilayotgan namunada'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -9
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object BeSum: TEdit
      Left = 92
      Top = 40
      Width = 61
      Height = 21
      TabStop = False
      Alignment = taRightJustify
      Anchors = [akTop, akRight]
      BorderStyle = bsNone
      Color = clBtnFace
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ReadOnly = True
      TabOrder = 0
    end
    object BeActivityPerKgOrSq: TEdit
      Tag = 1
      Left = 92
      Top = 88
      Width = 61
      Height = 21
      TabStop = False
      Alignment = taRightJustify
      Anchors = [akTop, akRight]
      BorderStyle = bsNone
      Color = clBtnFace
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ReadOnly = True
      TabOrder = 1
    end
    object BeMDA: TEdit
      Left = 92
      Top = 64
      Width = 61
      Height = 21
      TabStop = False
      Alignment = taRightJustify
      Anchors = [akTop, akRight]
      BorderStyle = bsNone
      Color = clBtnFace
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ParentShowHint = False
      ReadOnly = True
      ShowHint = True
      TabOrder = 2
    end
    object SampleDensity: TEdit
      Left = 92
      Top = 202
      Width = 61
      Height = 21
      Alignment = taRightJustify
      Anchors = [akTop, akRight]
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
      OnChange = OnParamChange
      OnClick = ParamEditClick
    end
    object SampleBeError: TEdit
      Left = 92
      Top = 111
      Width = 61
      Height = 21
      TabStop = False
      Alignment = taRightJustify
      Anchors = [akTop, akRight]
      BorderStyle = bsNone
      Color = clBtnFace
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ReadOnly = True
      TabOrder = 4
    end
    object SampleOrigMass: TEdit
      Left = 92
      Top = 226
      Width = 61
      Height = 21
      Alignment = taRightJustify
      Anchors = [akTop, akRight]
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 5
      OnChange = OnParamChange
      OnClick = ParamEditClick
    end
    object SampleSquare: TEdit
      Left = 92
      Top = 250
      Width = 61
      Height = 21
      Alignment = taRightJustify
      Anchors = [akTop, akRight]
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 6
      OnChange = OnParamChange
      OnClick = ParamEditClick
    end
    object SampleMass: TEdit
      Left = 92
      Top = 180
      Width = 61
      Height = 21
      TabStop = False
      Alignment = taRightJustify
      Anchors = [akTop, akRight]
      BorderStyle = bsNone
      Color = clBtnFace
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ReadOnly = True
      TabOrder = 7
    end
    object SampleTime: TEdit
      Left = 92
      Top = 156
      Width = 61
      Height = 21
      TabStop = False
      Alignment = taRightJustify
      Anchors = [akTop, akRight]
      BorderStyle = bsNone
      Color = clBtnFace
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ReadOnly = True
      TabOrder = 8
    end
  end
  object StatusBar: TStatusBar
    Left = 0
    Top = 730
    Width = 1400
    Height = 19
    Panels = <
      item
        Width = 200
      end
      item
        Width = 150
      end
      item
        Width = 150
      end
      item
        Width = 150
      end
      item
        Width = 50
      end>
  end
  object ToolBarPanel: TPanel
    Left = 0
    Top = 0
    Width = 1400
    Height = 40
    Align = alTop
    BevelOuter = bvNone
    DoubleBuffered = True
    ParentDoubleBuffered = False
    TabOrder = 13
    object SpeedButton1: TSpeedButton
      Left = 1350
      Top = 0
      Width = 50
      Height = 40
      Action = LanguageAction
      Align = alRight
    end
    object ToolBar: TToolBar
      Left = 0
      Top = 0
      Width = 1350
      Height = 40
      Align = alClient
      AutoSize = True
      ButtonHeight = 38
      ButtonWidth = 157
      DoubleBuffered = True
      DrawingStyle = dsGradient
      Images = ImageList
      List = True
      ParentDoubleBuffered = False
      ShowCaptions = True
      TabOrder = 0
      Wrapable = False
      object OpenButton: TToolButton
        Left = 0
        Top = 0
        AutoSize = True
        Caption = 'Ochish'
        ImageIndex = 0
        Indeterminate = True
        Style = tbsTextButton
        OnClick = OpenButtonClick
      end
      object SaveSpectraButton: TToolButton
        Left = 71
        Top = 0
        AutoSize = True
        Caption = 'Saqlash'
        DropdownMenu = SavePopupMenu
        EnableDropdown = True
        ImageIndex = 1
        Indeterminate = True
        Style = tbsDropDown
        OnClick = SaveSpectraButtonClick
      end
      object BatchProcessButton: TToolButton
        Left = 168
        Top = 0
        AutoSize = True
        Caption = 'Ko'#39'p sonli spektrlar tahlili'
        DropdownMenu = BatchProcessingPopupMenu
        EnableDropdown = True
        ImageIndex = 2
        Indeterminate = True
        Style = tbsDropDown
        OnClick = BatchProcessButtonClick
      end
      object ShiftingButton: TToolButton
        Left = 344
        Top = 0
        AutoSize = True
        Caption = 'Spektrni siljitish'
        ImageIndex = 3
        Style = tbsTextButton
        OnClick = ShiftingButtonClick
      end
      object StandardSamplesButton: TToolButton
        Left = 456
        Top = 0
        AutoSize = True
        Caption = 'Etalon namunalar'
        ImageIndex = 4
        Style = tbsTextButton
        OnClick = StandardSamplesButtonClick
      end
      object HelpButton: TToolButton
        Left = 578
        Top = 0
        AutoSize = True
        Caption = 'Dastur haqida'
        ImageIndex = 5
        OnClick = HelpButtonClick
      end
    end
  end
  object OpenDialog: TOpenDialog
    Options = [ofHideReadOnly, ofPathMustExist, ofFileMustExist, ofEnableSizing, ofForceShowHidden]
    Left = 95
    Top = 449
  end
  object SpectraLoadTimer: TTimer
    Enabled = False
    Interval = 300
    OnTimer = OnSpectraLoadTimer
    Left = 112
    Top = 520
  end
  object ImageList: TImageList
    AllocBy = 6
    DrawingStyle = dsTransparent
    Height = 24
    Width = 24
    Left = 568
    Top = 360
    Bitmap = {
      494C010106000800060018001800FFFFFFFFFF10FFFFFFFFFFFFFFFF424D3600
      0000000000003600000028000000600000003000000001002000000000000048
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000EFEFEF0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000004D4D4D00AEAEAE00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000DDDDDD00444444004444
      44004444440044444400DDDDDD00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000404040000101010077777700FDFDFD0000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000A5A5A500000000003E3E
      3E003E3E3E0000000000A5A5A500000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000004040400005050500000000004C4C4C00F0F0F000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000727272000B0B0B00FCFC
      FC00FDFDFD000C0C0C0073737300000000000000000000000000000000000000
      00000000000000000000000000000000000000000000BBBBBB00777777007777
      7700777777001E1E1E0040404000949494000505050027272700777777007777
      7700777777007777770077777700777777007777770077777700777777007777
      77007777770077777700BBBBBB00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00009D9D9D0096969600EAEAEA00F8F8F800818181000E0E0E003A3A3A000000
      0000000000003A3A3A000E0E0E0081818100F8F8F800EAEAEA00969696009D9D
      9D0000000000000000000000000000000000000000007F7F7F00000000000000
      000000000000000000004040400000000000C3C3C30018181800000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000007F7F7F00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000E2E2
      E2000A0A0A0000000000040404001A1A1A000606060066666600D6D6D6000000
      000000000000D5D5D50066666600050505001A1A1A0004040400000000000A0A
      0A00E2E2E200000000000000000000000000000000007F7F7F00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000007F7F7F00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000005858
      58000B0B0B00BCBCBC007B7B7B003C3C3C00CACACA0000000000000000000000
      0000000000000000000000000000CACACA003C3C3C007B7B7B00BCBCBC000B0B
      0B0058585800000000000000000000000000000000007F7F7F00000000000000
      0000000000000000000000000000000000000000000000000000000000009999
      9900999999000000000000000000000000000000000000000000000000000000
      000000000000000000007F7F7F00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000C3C3C3000101
      01006666660000000000000000000000000000000000FEFEFE009C9C9C004F4F
      4F004F4F4F009D9D9D00FEFEFE00000000000000000000000000000000006666
      660001010100C3C3C3000000000000000000000000007F7F7F00000000000000
      0000000000000000000000000000000000000000000000000000000000004040
      4000404040000000000000000000000000000000000000000000000000000000
      000000000000000000007F7F7F00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000E9E9E9003636
      360003030300999999000000000000000000FEFEFE004E4E4E00000000002525
      250025252500000000004E4E4E00FEFEFE000000000000000000999999000303
      030036363600E9E9E9000000000000000000000000007F7F7F00000000000000
      0000000000000000000000000000000000000000000000000000000000004040
      4000404040000000000000000000000000000000000000000000000000000000
      000000000000000000007F7F7F00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000F5F5
      F5004A4A4A0000000000D8D8D800000000009C9C9C0000000000969696000000
      00000000000096969600000000009D9D9D0000000000DADADA00000000004A4A
      4A00F5F5F500000000000000000000000000000000007F7F7F00000000000000
      0000000000000000000000000000000000000000000000000000000000004040
      4000404040000000000000000000000000000000000000000000000000000000
      000000000000000000007F7F7F00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00008F8F8F0000000000F1F1F100000000004E4E4E0025252500000000000000
      00000000000000000000252525004F4F4F0000000000F1F1F100000000008F8F
      8F0000000000000000000000000000000000000000007F7F7F00000000000000
      0000000000000000000000000000000000000000000000000000000000004040
      4000404040000000000000000000000000000000000000000000000000000000
      000000000000000000007F7F7F00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00008F8F8F0000000000F1F1F100000000004E4E4E0025252500000000000000
      00000000000000000000252525004E4E4E0000000000F1F1F100000000008F8F
      8F0000000000000000000000000000000000000000007F7F7F00000000000000
      0000000000000000000000000000000000000000000000000000000000004040
      4000404040000000000000000000000000000000000000000000000000000000
      000000000000000000007F7F7F00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000F5F5
      F5004A4A4A0000000000D8D8D800000000009C9C9C0000000000969696000000
      00000000000096969600000000009C9C9C0000000000D8D8D800000000004A4A
      4A00F5F5F500000000000000000000000000000000007F7F7F00000000000000
      000000000000000000000000000000000000000000000000000000000000A6A6
      A600A6A6A6000000000000000000000000000000000000000000000000000000
      000000000000000000007F7F7F00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000E9E9E9003636
      360003030300999999000000000000000000FEFEFE004E4E4E00000000002525
      250025252500000000004E4E4E00FEFEFE000000000000000000999999000303
      030036363600E9E9E9000000000000000000000000007F7F7F00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000007F7F7F00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000C3C3C3000101
      01006666660000000000000000000000000000000000FEFEFE009C9C9C004E4E
      4E004E4E4E009C9C9C00FEFEFE00000000000000000000000000000000006666
      660001010100C3C3C3000000000000000000000000007F7F7F00000000000000
      0000000000000000000000000000000000000000000000000000000000004040
      4000404040000000000000000000000000000000000000000000000000000000
      000000000000000000007F7F7F00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000005858
      58000B0B0B00BCBCBC007B7B7B003C3C3C00CACACA0000000000000000000000
      0000000000000000000000000000CACACA003C3C3C007B7B7B00BCBCBC000B0B
      0B0058585800000000000000000000000000000000007F7F7F00000000000000
      000000000000000000000000000000000000000000000000000000000000A6A6
      A600A6A6A6000000000000000000000000000000000000000000000000000000
      000000000000000000007F7F7F00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000E2E2
      E2000A0A0A0000000000040404001A1A1A000606060067676700D6D6D6000000
      000000000000D6D6D60067676700060606001A1A1A0004040400000000000A0A
      0A00E2E2E200000000000000000000000000000000007F7F7F00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000007F7F7F00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00009D9D9D0096969600EAEAEA00F8F8F800808080000E0E0E003A3A3A000000
      0000000000003A3A3A000E0E0E0080808000F8F8F800EAEAEA00969696009D9D
      9D0000000000000000000000000000000000000000007F7F7F00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000007F7F7F00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000717171000C0C0C00FDFD
      FD00FDFDFD000C0C0C0072727200000000000000000000000000000000000000
      00000000000000000000000000000000000000000000C3C3C300888888008888
      8800888888008888880088888800888888008888880088888800888888008888
      8800888888008888880088888800888888008888880088888800888888008888
      88008888880088888800C3C3C300000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000A5A5A500000000003E3E
      3E003E3E3E0000000000A5A5A500000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000DDDDDD00444444004444
      44004444440044444400DDDDDD00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000C7C7C7008D8D
      8D00000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000047474700424242003737
      37000F0F0F004242420046464600262626001616160049494900474747001E1E
      1E001E1E1E00484848004A4A4A00161616002626260047474700424242001010
      1000363636004343430047474700000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000F8F8F8002B2B2B000707
      0700D5D5D5000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000007C7C7C00FFFFFF00FFFFFF00DBDB
      DB0038383800FFFFFF00FFFFFF008E8E8E0046464600FFFFFF00FFFFFF006868
      680069696900FFFFFF00FFFFFF00464646008E8E8E00FFFFFF00FFFFFF003333
      3300D6D6D600FFFFFF00FFFFFF007C7C7C000000000000000000000000000000
      00005B5B5B004444440044444400444444004444440044444400444444004444
      440044444400444444004444440052525200FAFAFA0075757500000000000000
      000038383800FCFCFC0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000E5E5E500ECECEC000000000000000000E3E3E300EEEE
      EE00000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000006E6E6E00FFFFFF00FFFFFF00A0A0
      A00000000000F6F6F600FEFEFE00868686003C3C3C00FFFFFF00FFFFFF005F5F
      5F0060606000FFFFFF00FFFFFF003A3A3A0085858500FCFCFC00ECECEC002929
      2900CDCDCD00EAEAEA00FFFFFF006F6F6F000000000000000000000000000000
      0000202020001919190044444400444444004444440044444400444444004444
      440044444400444444004444440096969600C7C7C70003030300000000000000
      0000000000008A8A8A000000000000000000000000000000000000000000EEEE
      EE00BBBBBB00BBBBBB00BBBBBB00BBBBBB00BBBBBB00BBBBBB00BBBBBB00BBBB
      BB00BBBBBB00BBBBBB00BBBBBB00BBBBBB00BBBBBB00BBBBBB00BBBBBB00BBBB
      BB00EEEEEE000000000000000000000000000000000000000000000000000000
      000000000000EBEBEB00060606007E7E7E00E0E0E000E5E5E5005D5D5D001919
      1900FCFCFC000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000060606000E1E1E100919191001111
      11006A6A6A0000000000EEEEEE006B6B6B0038383800DDDDDD00DBDBDB005151
      510050505000DBDBDB00DCDCDC00383838006B6B6B00D8D8D800C8C8C8002929
      29009E9E9E00D0D0D000D8D8D800616161000000000000000000000000000000
      0000202020006060600000000000000000000000000000000000000000000000
      0000000000000000000000000000F8F8F8002B2B2B0000000000000000000000
      00000000000007070700D5D5D50000000000000000000000000000000000BFBF
      BF00000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000BFBFBF000000000000000000000000000000000000000000000000000000
      000000000000F7F7F70024242400000000000000000000000000000000004343
      4300FEFEFE000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000001212120032323200000000009E9E
      9E00FFFFFF00262626002424240014141400020202002A2A2A00292929000A0A
      0A00090909002A2A2A002A2A2A00030303001414140027272700262626000202
      0200242424000000000028282800131313000000000000000000000000000000
      0000202020006060600000000000000000000000000000000000000000000000
      0000000000000000000000000000C1C1C1006666660066666600040404000000
      000051515100666666009A9A9A0000000000000000000000000000000000BFBF
      BF00000000008C8C8C008C8C8C00000000008C8C8C00BBBBBB00BBBBBB00BBBB
      BB00BBBBBB00BBBBBB00BBBBBB008C8C8C00000000008C8C8C008C8C8C000000
      0000BFBFBF00000000000000000000000000000000000000000000000000EBEB
      EB00F7F7F7003B3B3B0000000000535353009797970090909000414141000000
      00005D5D5D0000000000EBEBEB00000000000000000000000000000000000000
      0000000000000000000000000000000000006D6D6D00FDFDFD00CDCDCD000000
      00002A2A2A0021212100FFFFFF007B7B7B003D3D3D00FBFBFB00F6F6F6005B5B
      5B005D5D5D00F6F6F600FFFFFF004949490084848400F7F7F700E1E1E1002C2C
      2C00B9B9B900E7E7E700F4F4F4006E6E6E000000000000000000000000000000
      000020202000606060000000000000000000CCCCCC00BBBBBB00BBBBBB00BBBB
      BB00BBBBBB00F6F6F600000000000000000000000000000000001A1A1A000000
      0000D9D9D900000000000000000000000000000000000000000000000000BFBF
      BF0000000000BFBFBF00BFBFBF0000000000BFBFBF0000000000000000000000
      0000000000000000000000000000BFBFBF0000000000BFBFBF00BFBFBF000000
      0000BFBFBF000000000000000000000000000000000000000000E5E5E5000606
      06002424240000000000A6A6A600000000000000000000000000FEFEFE007F7F
      7F00000000002727270014141400F8F8F8000000000000000000000000000000
      00000000000000000000000000000000000076767600FFFFFF00FFFFFF00ECEC
      EC0000000000F9F9F900FFFFFF008C8C8C0041414100FFFFFF00FFFFFF006666
      660066666600FFFFFF00E2E2E2000000000049494900F2F2F200FFFFFF003030
      3000D5D5D500FDFDFD00FFFFFF00767676000000000000000000000000000000
      0000202020006060600000000000000000004040400000000000000000000000
      000000000000DFDFDF00000000000000000000000000000000002E2E2E000000
      0000EFEFEF00000000000000000000000000000000000000000000000000BFBF
      BF0000000000BFBFBF00BFBFBF0000000000BFBFBF0000000000000000000000
      0000000000000000000000000000BFBFBF0000000000BFBFBF00BFBFBF000000
      0000BFBFBF000000000000000000000000000000000000000000EDEDED007F7F
      7F0000000000545454000000000000000000000000000000000000000000FCFC
      FC002C2C2C000B0B0B0091919100F6F6F6000000000000000000000000000000
      0000000000000000000000000000000000003F3F3F008C8C8C00858585006D6D
      6D0000000000727272008F8F8F004545450000000000909090008E8E8E003131
      3100323232009F9F9F0000000000A8A8A8005C5C5C00454545008A8A8A001818
      180067676700878787008B8B8B003F3F3F000000000000000000000000000000
      000020202000606060000000000000000000CCCCCC00BBBBBB00BBBBBB00BBBB
      BB00BBBBBB00F6F6F60000000000000000000000000000000000454545000606
      0600FEFEFE00000000000000000000000000000000000000000000000000BFBF
      BF0000000000BFBFBF00BFBFBF0000000000BFBFBF0000000000000000000000
      0000000000000000000000000000BFBFBF0000000000BFBFBF00BFBFBF000000
      0000BFBFBF00000000000000000000000000000000000000000000000000E0E0
      E000000000009797970000000000000000000000000000000000000000000000
      00006D6D6D000B0B0B0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000002121210048484800414141004040
      400000000000343434004C4C4C00232323000D0D0D004A4A4A004A4A4A001616
      1600282828003939390000000000FFFFFF00ADADAD0011111100515151000707
      07003C3C3C004141410049494900212121000000000000000000000000000000
      000020202000606060000000000000000000CCCCCC00BBBBBB00BBBBBB00BBBB
      BB00BBBBBB00BBBBBB00BBBBBB00CCCCCC000000000000000000848484005555
      550000000000000000000000000000000000000000000000000000000000BFBF
      BF0000000000BFBFBF00BFBFBF0000000000BFBFBF0000000000000000000000
      0000000000000000000000000000BFBFBF0000000000BFBFBF00BFBFBF000000
      0000BFBFBF00000000000000000000000000000000000000000000000000E4E4
      E400000000009191910000000000000000000000000000000000000000000000
      0000666666000F0F0F0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000007C7C7C00FFFFFF00FFFFFF00DEDE
      DE000000000080808000FFFFFF008E8E8E0046464600FFFFFF00FFFFFF007070
      7000525252003333330065656500000000000404040011111100FFFFFF003333
      3300D5D5D500FFFFFF00FFFFFF007C7C7C000000000000000000000000000000
      0000202020006060600000000000000000004040400000000000000000000000
      0000000000000000000000000000404040000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000BFBF
      BF0000000000BFBFBF00BFBFBF00000000005959590077777700777777007777
      77007777770077777700777777005959590000000000BFBFBF00BFBFBF000000
      0000BFBFBF000000000000000000000000000000000000000000E3E3E3005D5D
      5D0000000000444444000000000000000000000000000000000000000000F7F7
      F70021212100070707006D6D6D00F2F2F2000000000000000000000000000000
      0000000000000000000000000000000000007B7B7B00FFFFFF00FFFFFF00DDDD
      DD00000000001D1D1D00FFFFFF008D8D8D0046464600FFFFFF00FFFFFF007D7D
      7D0000000000A2A2A200FFFFFF0047474700AAAAAA0050505000A2A2A2004646
      4600D5D5D500FFFFFF00FFFFFF007B7B7B000000000000000000000000000000
      000020202000606060000000000000000000CCCCCC00BBBBBB00BBBBBB00BBBB
      BB00BBBBBB00BBBBBB00BBBBBB00CCCCCC0000000000000000008A8A8A005B5B
      5B0000000000000000000000000000000000000000000000000000000000BFBF
      BF0000000000BFBFBF00BFBFBF00000000000000000000000000000000000000
      00000000000000000000000000000000000000000000BFBFBF00BFBFBF000000
      0000BFBFBF000000000000000000000000000000000000000000EEEEEE001919
      1900434343000000000081818100FDFDFD000000000000000000F7F7F7005F5F
      5F00010101004B4B4B0027272700FCFCFC00A6A6A600BFBFBF00000000000000
      0000000000000000000000000000000000001D1D1D00414141003B3B3B003535
      350000000000000000005C5C5C001D1D1D000C0C0C00434343004B4B4B002828
      2800000000003D3D3D00464646000D0D0D00272727001B1B1B000F0F0F001B1B
      1B00303030003D3D3D00414141001D1D1D000000000000000000000000000000
      000020202000606060000000000000000000CCCCCC00BBBBBB00BBBBBB00BBBB
      BB00BBBBBB00BBBBBB00BBBBBB00CCCCCC000000000000000000606060002020
      200000000000000000000000000000000000000000000000000000000000BFBF
      BF0000000000BFBFBF0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000BFBFBF000000
      0000BFBFBF00000000000000000000000000000000000000000000000000FCFC
      FC00FDFDFD005B5B5B00000000002F2F2F006E6E6E0067676700222222000101
      010081818100D5D5D500FBFBFB00DDDDDD001616160046464600EDEDED00ECEC
      EC00EBEBEB000000000000000000000000004343430092929200878787007272
      72003030300018181800585858005858580025252500A1A1A100707070000000
      00004747470095959500979797002121210049494900B3B3B300000000000101
      0100757575008989890092929200434343000000000000000000000000000000
      0000202020006060600000000000000000004040400000000000000000000000
      0000000000000000000000000000404040000000000000000000606060002020
      200000000000000000000000000000000000000000000000000000000000BFBF
      BF0000000000BFBFBF0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000BFBFBF000000
      0000BFBFBF000000000000000000000000000000000000000000000000000000
      00000000000000000000272727000C0C0C000A0A0A000F0F0F00070707004B4B
      4B00D4D4D40008080800333333000101010000000000000000000A0A0A002424
      240032323200FDFDFD00000000000000000076767600FFFFFF00FBFBFB00CFCF
      CF0041414100A5A5A5003D3D3D008F8F8F002C2C2C00FFFFFF00424242000404
      040076767600FFFFFF00FFFFFF004141410089898900FFFFFF00242424000000
      0000DADADA00FBFBFB00FFFFFF00767676000000000000000000000000000000
      000020202000606060000000000000000000CCCCCC00BBBBBB00BBBBBB00BBBB
      BB00BBBBBB00BBBBBB00BBBBBB00CCCCCC0000000000000000005E5E5E002020
      200000000000000000000000000000000000000000000000000000000000BFBF
      BF0000000000BFBFBF0000000000A1A1A1004444440044444400444444004444
      440044444400444444004444440044444400A1A1A10000000000BFBFBF000000
      0000BFBFBF000000000000000000000000000000000000000000000000000000
      000000000000EAEAEA00151515009191910000000000000000006D6D6D002727
      2700FBFBFB00333333000303030077777700CFCFCF00C3C3C3004D4D4D000000
      00007575750000000000000000000000000080808000FFFFFF00FFFFFF00D8D8
      D80038383800FFFFFF001818180018181800000000001F1F1F00727272007A7A
      7A0070707000FFFFFF00FFFFFF004949490091919100FFFFFF00939393000000
      0000E2E2E200FFFFFF00FFFFFF00808080000000000000000000000000000000
      0000202020006060600000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FBFBFB00313131003939
      390000000000000000000000000000000000000000000000000000000000BFBF
      BF0000000000BFBFBF00000000007F7F7F000000000044444400444444004444
      4400444444004444440044444400000000007F7F7F0000000000BFBFBF000000
      0000BFBFBF000000000000000000000000000000000000000000000000000000
      00000000000000000000F8F8F800F6F6F6000000000000000000F1F1F100FCFC
      FC00DDDDDD000101010078787800000000000000000000000000FDFDFD003939
      39001F1F1F0000000000000000000000000009090900111111000C0C0C001212
      1200000000001B1B1B0000000000BDBDBD00FFFFFF0000000000212121000707
      0700010101001313130015151500000000000707070013131300141414000000
      0000141414000D0D0D00111111000A0A0A000000000000000000000000000000
      0000202020006060600000000000000000000000000000000000000000000000
      000000000000000000000000000000000000BABABA0032323200000000009494
      940000000000000000000000000000000000000000000000000000000000BFBF
      BF0000000000BFBFBF00000000007F7F7F000000000000000000000000000000
      0000000000000000000000000000000000007F7F7F00FEFEFE00696969000000
      0000C4C4C4000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000ACAC
      AC001818180000000000D0D0D000000000000000000000000000000000008F8F
      8F000000000020202000E3E3E3000000000056565600C2C2C200B5B5B5009393
      930021212100C0C0C0005E5E5E00313131008989890011111100D0D0D0004949
      490049494900C1C1C100C7C7C7002E2E2E0062626200C0C0C0009F9F9F000000
      00009B9B9B00B5B5B500C1C1C100565656000000000000000000000000000000
      0000202020006060600000000000000000000000000000000000000000000000
      00000000000000000000DEDEDE003535350000000000000000004A4A4A00FCFC
      FC0000000000000000000000000000000000000000000000000000000000BFBF
      BF0000000000BFBFBF00000000007F7F7F000000000000000000000000000000
      000044444400A1A1A10000000000000000007F7F7F006C6C6C00000000006C6C
      6C00FEFEFE000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000C6C6
      C6004A4A4A0000000000C4C4C400000000000000000000000000000000008383
      83000101010063636300ECECEC000000000075757500FFFFFF00F9F9F900D3D3
      D3002E2E2E00F7F7F700FFFFFF005B5B5B0008080800F5F5F500FFFFFF006464
      640064646400FFFFFF00FFFFFF00414141008A8A8A00FFFFFF00F8F8F8000000
      0000C0C0C000FFFFFF00FFFFFF00757575000000000000000000000000000000
      0000202020006060600000000000000000000000000000000000000000000000
      00000000000000000000FBFBFB0024242400000000002C2C2C00F1F1F1000000
      000000000000000000000000000000000000000000000000000000000000BFBF
      BF00000000008C8C8C00BBBBBB005D5D5D0000000000BBBBBB00BBBBBB00BBBB
      BB00000000005D5D5D00BBBBBB000000000017171700000000006C6C6C00FEFE
      FE00000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000ECECEC000A0A0A004F4F4F00FDFDFD000000000000000000EEEEEE001D1D
      1D003838380000000000000000000000000064646400E1E1E100D4D4D400A5A5
      A50029292900CFCFCF00DFDFDF007575750041414100E8E8E800DFDFDF005353
      530055555500E0E0E000E4E4E400383838006F6F6F00F6F6F600000000005858
      580005050500A3A3A300E9E9E900646464000000000000000000000000000000
      0000202020006060600000000000000000000000000000000000000000000000
      00000000000000000000000000004343430016161600DFDFDF00000000000000
      000000000000000000000000000000000000000000000000000000000000BFBF
      BF00000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000066666600FEFEFE000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000ECECEC0024242400000000003B3B3B008F8F8F00848484001E1E1E000000
      00005F5F5F000000000000000000000000001313130028282800000000002424
      240001010100262626002626260013131300020202002B2B2B00292929000A0A
      0A000B0B0B00292929002B2B2B000303030014141400212121002A2A2A00FFFF
      FF00A2A2A2000000000031313100121212000000000000000000000000000000
      0000202020001919190044444400444444004444440044444400444444004444
      440044444400434343002323230007070700C5C5C50000000000000000000000
      000000000000000000000000000000000000000000000000000000000000EEEE
      EE00BBBBBB00BBBBBB00BBBBBB00BBBBBB00BBBBBB00BBBBBB00BBBBBB00BBBB
      BB00BBBBBB00BBBBBB00BBBBBB00BBBBBB00C0C0C000FEFEFE00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000EBEBEB0032323200747474001D1D1D000000000000000000373737005E5E
      5E006A6A6A00FEFEFE0000000000000000006A6A6A00EEEEEE00E2E2E200B2B2
      B2002A2A2A00DEDEDE00EBEBEB00797979003B3B3B00F5F5F500EEEEEE005A5A
      5A005A5A5A00EEEEEE00F5F5F5003C3C3C0077777700FFFFFF000B0B0B003131
      310000000000C1C1C100F8F8F800696969000000000000000000000000000000
      00005B5B5B004444440044444400444444004444440044444400444444004444
      4400444444004444440054545400C5C5C5000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000FDFDFD0000000000000000001E1E1E005D5D5D00000000000000
      0000FEFEFE000000000000000000000000006E6E6E00FFFFFF00E9E9E900CCCC
      CC002B2B2B00E9E9E900FCFCFC00848484003C3C3C00FFFFFF00FFFFFF005D5D
      5D005E5E5E00FFFFFF00FFFFFF003A3A3A0083838300FBFBFB00FFFFFF001B1B
      1B00D5D5D500F8F8F800FCFCFC006F6F6F000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000E1E1E100EAEAEA00000000000000
      0000000000000000000000000000000000007D7D7D00FFFFFF00FFFFFF00D9D9
      D90031313100FFFFFF00FFFFFF009292920045454500FFFFFF00FFFFFF006B6B
      6B006B6B6B00FFFFFF00FFFFFF004545450091919100FFFFFF00FFFFFF003434
      3400DADADA00FFFFFF00FFFFFF007D7D7D000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000131313002A2A2A00272727000000
      00000A0A0A00272727002A2A2A00191919000B0B0B002C2C2C002B2B2B001111
      1100111111002B2B2B002C2C2C000B0B0B00191919002A2A2A00272727000B0B
      0B0000000000272727002B2B2B0013131300424D3E000000000000003E000000
      2800000060000000300000000100010000000000400200000000000000000000
      000000000000000000000000FFFFFF00FFFFFFFBFFFF000000000000FFFFFFF9
      FFFF000000000000FF81FFF87FFF000000000000FF81FFF83FFF000000000000
      FF81FF800001000000000000F0180F810001000000000000E018079FFFF90000
      00000000E07E079FE7F9000000000000C781E39FE7F9000000000000C300C39F
      E7F9000000000000E118879FE7F9000000000000F13C8F9FE7F9000000000000
      F13C8F9FE7F9000000000000E118879FE7F9000000000000C300C39FFFF90000
      00000000C781E39FE7F9000000000000E07E079FE7F9000000000000E018079F
      FFF9000000000000F0180F800001000000000000FF81FF800001000000000000
      FF81FFFFFFFF000000000000FF81FFFFFFFF000000000000FFFFFFFFFFFF0000
      00000000FFFFFFFFFFFF000000000000FFFFCFFFFFFFFFFFFF800001FFFF87FF
      FFFFFFFFFF000000F00003FFFFFFFCCFFF000000F00003E00007F807FF000000
      F3FE01E00007F807FF000004F3FE01E00007E005FF000000F303C7E07E07C1C0
      FF000000F303C7E07E07C3E0FF008000F303C7E07E07E3F3FF000000F300CFE0
      7E07E3F3FF000000F300FFE00007C3E0FF000000F300CFE00007C0C03F000000
      F300CFE3FFC7E00007000000F300CFE3FFC7FC0003000000F300CFE20047F8C0
      07000000F3FF8FE20047FCC1C7000000F3FF0FE27E07FFE1E1000000F3FC0FE2
      7207FFE1E1000000F3FC1FE0000FFFF0C7000000F3FE3FE0001FFFF007200000
      F0007FE0003FFFF003000000F000FFFFFFFFFFFB37000000FFFFFFFFFFFFFFFF
      3F000000FFFFFFFFFFFFFFFFFF10000800000000000000000000000000000000
      000000000000}
  end
  object ShiftingTimer: TTimer
    Enabled = False
    Interval = 700
    OnTimer = OnShiftingTimerTimer
    Left = 200
    Top = 440
  end
  object BatchProcessingPopupMenu: TPopupMenu
    Left = 480
    Top = 443
    object SelectFilesMI: TMenuItem
      Action = SelectFilesAction
    end
    object SelectFolderMI: TMenuItem
      Action = SelectDirectoryAction
      Default = True
    end
  end
  object OpenPopupMenu: TPopupMenu
    Left = 308
    Top = 483
    object Spektrniochish1: TMenuItem
      Action = OpenSpectrumAction
      Default = True
    end
    object Parameterlarorqaliochish1: TMenuItem
      Action = OpenParametersAction
    end
  end
  object SavePopupMenu: TPopupMenu
    Left = 300
    Top = 411
    object Spektralrnisaqlash1: TMenuItem
      Action = SaveSpectraAction
      Default = True
    end
    object Parameterlarnisaqlash1: TMenuItem
      Action = SaveParametersAction
    end
  end
  object ActionList: TActionList
    Left = 692
    Top = 443
    object OpenSpectrumAction: TAction
      Caption = 'Spektrni ochish'
      ShortCut = 16463
      OnExecute = OpenSpectrumActionExecute
    end
    object OpenParametersAction: TAction
      Caption = 'Parameterlar orqali ochish'
      ShortCut = 24655
      OnExecute = OpenParametersActionExecute
    end
    object SaveSpectraAction: TAction
      Caption = 'Spektralrni saqlash'
      ShortCut = 16467
      OnExecute = SaveSpectraActionExecute
    end
    object SaveParametersAction: TAction
      Caption = 'Parameterlarni saqlash'
      ShortCut = 24659
      OnExecute = SaveParametersActionExecute
    end
    object SelectFilesAction: TAction
      Caption = 'Fayllarni tanlash'
      ShortCut = 16450
      OnExecute = SelectFilesActionExecute
    end
    object SelectDirectoryAction: TAction
      Caption = 'Manzilni tanlash'
      ShortCut = 24642
      OnExecute = SelectDirectoryActionExecute
    end
    object LanguageAction: TAction
      Caption = '  UZ  '
      ShortCut = 16460
      OnExecute = LanguageActionExecute
    end
  end
  object SaveDialog: TSaveDialog
    DefaultExt = 'par'
    Options = [ofOverwritePrompt, ofHideReadOnly, ofPathMustExist, ofEnableSizing]
    Left = 416
    Top = 376
  end
end
