object SpectrumFrame: TSpectrumFrame
  Left = 0
  Top = 0
  Width = 451
  Height = 305
  Align = alClient
  TabOrder = 0
  object Splitter: TSplitter
    Left = 0
    Top = 97
    Width = 451
    Height = 8
    Cursor = crVSplit
    Align = alBottom
    AutoSnap = False
    Color = clGrayText
    MinSize = 100
    ParentColor = False
    ResizeStyle = rsUpdate
    ExplicitTop = 420
    ExplicitWidth = 1014
  end
  object Label13: TLabel
    Left = 33
    Top = 56
    Width = 36
    Height = 13
    Caption = 'Kanal1:'
  end
  object Label14: TLabel
    Left = 33
    Top = 79
    Width = 36
    Height = 13
    Caption = 'Kanal2:'
  end
  object Label15: TLabel
    Left = 33
    Top = 101
    Width = 36
    Height = 13
    Caption = 'Kanal3:'
  end
  object Label16: TLabel
    Left = 33
    Top = 123
    Width = 36
    Height = 13
    Caption = 'Kanal4:'
  end
  object Label17: TLabel
    Left = 33
    Top = 146
    Width = 36
    Height = 13
    Caption = 'Kanal5:'
  end
  object PageControl: TPageControl
    Left = 0
    Top = 105
    Width = 451
    Height = 200
    ActivePage = ParametersTab
    Align = alBottom
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Tahoma'
    Font.Style = []
    OwnerDraw = True
    ParentFont = False
    TabOrder = 0
    OnDrawTab = PageControlDrawTab
    object ParametersTab: TTabSheet
      Caption = '  Parametrlar  '
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitHeight = 0
      object Panel1: TPanel
        Left = 0
        Top = 0
        Width = 443
        Height = 171
        Align = alClient
        BevelOuter = bvNone
        ParentBackground = False
        TabOrder = 0
        object IntensityLabel: TLabel
          Left = 26
          Top = 84
          Width = 82
          Height = 13
          Alignment = taRightJustify
          Caption = 'Intensivlik (CPS):'
        end
        object RealTimeLabel: TLabel
          Left = 12
          Top = 34
          Width = 96
          Height = 13
          Alignment = taRightJustify
          Caption = 'Haqiqiy vaqt (Real):'
        end
        object TotalCountLabel: TLabel
          Left = 17
          Top = 59
          Width = 91
          Height = 13
          Alignment = taRightJustify
          Caption = 'Jami impulslar soni:'
        end
        object SampleVolumeLabel: TLabel
          Left = 238
          Top = 34
          Width = 71
          Height = 13
          Alignment = taRightJustify
          Caption = 'Namuna hajmi:'
        end
        object SampleMassLabel: TLabel
          Left = 226
          Top = 9
          Width = 83
          Height = 13
          Alignment = taRightJustify
          Caption = 'Namuna massasi:'
        end
        object LiveTimeLabel: TLabel
          Left = 15
          Top = 9
          Width = 93
          Height = 13
          Alignment = taRightJustify
          Caption = 'Foydali vaqt (Live):'
        end
        object SampleMassUnitBox: TComboBox
          Left = 397
          Top = 6
          Width = 48
          Height = 21
          Style = csDropDownList
          ItemIndex = 1
          TabOrder = 1
          Text = 'g'
          OnChange = OnDataChange
          Items.Strings = (
            'kg'
            'g')
        end
        object CPSEdit: TEdit
          Left = 115
          Top = 84
          Width = 57
          Height = 21
          TabStop = False
          BevelInner = bvNone
          BevelOuter = bvNone
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
        object SampleVolumeUnitBox: TComboBox
          Left = 397
          Top = 31
          Width = 48
          Height = 21
          Style = csDropDownList
          ItemIndex = 0
          TabOrder = 3
          Text = 'l'
          OnChange = OnDataChange
          Items.Strings = (
            'l'
            'ml'
            'm^3')
        end
        object EnCalGroupBox: TGroupBox
          Left = 492
          Top = 6
          Width = 260
          Height = 163
          Caption = ' Energiya bo'#8216'yicha kalibrovka '
          TabOrder = 4
          TabStop = True
          object PointsLabel: TLabel
            Left = 10
            Top = 22
            Width = 67
            Height = 13
            Caption = 'Nuqtalar soni:'
          end
          object Chan1Label: TLabel
            Left = 5
            Top = 48
            Width = 52
            Height = 13
            Alignment = taRightJustify
            Caption = 'Channel 1:'
          end
          object Chan2Label: TLabel
            Left = 18
            Top = 71
            Width = 39
            Height = 13
            Alignment = taRightJustify
            Caption = 'Kanal 2:'
          end
          object Chan3Label: TLabel
            Left = 18
            Top = 93
            Width = 39
            Height = 13
            Alignment = taRightJustify
            Caption = 'Kanal 3:'
            Enabled = False
          end
          object Chan4Label: TLabel
            Left = 18
            Top = 115
            Width = 39
            Height = 13
            Alignment = taRightJustify
            Caption = 'Kanal 4:'
            Enabled = False
          end
          object Chan5Label: TLabel
            Left = 18
            Top = 138
            Width = 39
            Height = 13
            Alignment = taRightJustify
            Caption = 'Kanal 5:'
            Enabled = False
          end
          object Energy1Label: TLabel
            Left = 143
            Top = 48
            Width = 47
            Height = 13
            Alignment = taRightJustify
            Caption = 'Energy 1:'
          end
          object Energy2Label: TLabel
            Left = 135
            Top = 71
            Width = 55
            Height = 13
            Alignment = taRightJustify
            Caption = 'Energiya 2:'
          end
          object Energy3Label: TLabel
            Left = 135
            Top = 93
            Width = 55
            Height = 13
            Alignment = taRightJustify
            Caption = 'Energiya 3:'
            Enabled = False
          end
          object Energy4Label: TLabel
            Left = 135
            Top = 115
            Width = 55
            Height = 13
            Alignment = taRightJustify
            Caption = 'Energiya 4:'
            Enabled = False
          end
          object Energy5Label: TLabel
            Left = 135
            Top = 138
            Width = 55
            Height = 13
            Alignment = taRightJustify
            Caption = 'Energiya 5:'
            Enabled = False
          end
          object Energy1Edit: TEdit
            Left = 193
            Top = 45
            Width = 52
            Height = 21
            TabOrder = 2
            OnChange = OnDataChange
            OnKeyPress = OnFValueEditKeyPress
          end
          object Channel1Edit: TEdit
            Left = 60
            Top = 45
            Width = 52
            Height = 21
            TabOrder = 1
            OnChange = OnDataChange
            OnKeyPress = OnFValueEditKeyPress
          end
          object Energy2Edit: TEdit
            Left = 193
            Top = 68
            Width = 52
            Height = 21
            TabOrder = 4
            OnChange = OnDataChange
            OnKeyPress = OnFValueEditKeyPress
          end
          object Channel2Edit: TEdit
            Left = 60
            Top = 68
            Width = 52
            Height = 21
            TabOrder = 3
            OnChange = OnDataChange
            OnKeyPress = OnFValueEditKeyPress
          end
          object Energy4Edit: TEdit
            Left = 193
            Top = 112
            Width = 52
            Height = 21
            Enabled = False
            TabOrder = 8
            OnChange = OnDataChange
            OnKeyPress = OnFValueEditKeyPress
          end
          object Channel4Edit: TEdit
            Left = 60
            Top = 112
            Width = 52
            Height = 21
            Enabled = False
            TabOrder = 7
            OnChange = OnDataChange
            OnKeyPress = OnFValueEditKeyPress
          end
          object Energy3Edit: TEdit
            Left = 193
            Top = 90
            Width = 52
            Height = 21
            Enabled = False
            TabOrder = 6
            OnChange = OnDataChange
            OnKeyPress = OnFValueEditKeyPress
          end
          object Channel3Edit: TEdit
            Left = 60
            Top = 90
            Width = 52
            Height = 21
            Enabled = False
            TabOrder = 5
            OnChange = OnDataChange
            OnKeyPress = OnFValueEditKeyPress
          end
          object Energy5Edit: TEdit
            Left = 193
            Top = 135
            Width = 52
            Height = 21
            Enabled = False
            TabOrder = 10
            OnChange = OnDataChange
            OnKeyPress = OnFValueEditKeyPress
          end
          object Channel5Edit: TEdit
            Left = 60
            Top = 135
            Width = 52
            Height = 21
            Enabled = False
            TabOrder = 9
            OnChange = OnDataChange
            OnKeyPress = OnFValueEditKeyPress
          end
          object PointsBox: TComboBox
            Left = 82
            Top = 19
            Width = 51
            Height = 21
            Style = csDropDownList
            ItemIndex = 0
            TabOrder = 0
            Text = '2'
            OnChange = PointsBoxChange
            Items.Strings = (
              '2'
              '3'
              '4'
              '5')
          end
        end
        object RealTimeEdit: TEdit
          Left = 115
          Top = 34
          Width = 80
          Height = 21
          TabStop = False
          BevelInner = bvNone
          BevelOuter = bvNone
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
        object LiveTimeEdit: TEdit
          Left = 115
          Top = 9
          Width = 80
          Height = 21
          TabStop = False
          BevelInner = bvNone
          BevelOuter = bvNone
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
        object SampleMassEdit: TEdit
          Left = 315
          Top = 6
          Width = 80
          Height = 21
          TabOrder = 0
          OnChange = OnDataChange
          OnKeyPress = OnFValueEditKeyPress
        end
        object SampleVolumeEdit: TEdit
          Left = 315
          Top = 31
          Width = 80
          Height = 21
          TabOrder = 2
          OnChange = OnDataChange
          OnKeyPress = OnFValueEditKeyPress
        end
        object TotalCountEdit: TEdit
          Left = 115
          Top = 59
          Width = 80
          Height = 21
          TabStop = False
          BevelInner = bvNone
          BevelOuter = bvNone
          BorderStyle = bsNone
          Color = clBtnFace
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
          ReadOnly = True
          TabOrder = 9
        end
        object CalibrateButton: TButton
          Left = 755
          Top = 9
          Width = 99
          Height = 29
          Caption = 'Kalibrovka qilish'
          Enabled = False
          TabOrder = 5
          OnClick = CalibrateButtonClick
        end
      end
    end
    object RawDataTab: TTabSheet
      Caption = '  Spektr ma'#39'lumotlari  '
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = []
      ImageIndex = 1
      ParentFont = False
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object RawDataTable: TStringGrid
        Left = 0
        Top = 0
        Width = 321
        Height = 171
        Align = alLeft
        Color = clBtnFace
        ColCount = 3
        DefaultColWidth = 90
        DefaultRowHeight = 22
        DoubleBuffered = True
        FixedCols = 0
        RowCount = 1025
        Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goRangeSelect, goDrawFocusSelected, goColSizing]
        ParentDoubleBuffered = False
        TabOrder = 0
        OnKeyDown = RawDataTableKeyDown
        OnMouseDown = RawDataTableMouseDown
        OnMouseUp = RawDataTableMouseUp
      end
    end
    object PeakInfoTab: TTabSheet
      Caption = '  Fotocho'#8216'qqi  '
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = []
      ImageIndex = 2
      ParentFont = False
      OnShow = PeakInfoTabShow
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object Panel2: TPanel
        Left = 0
        Top = 0
        Width = 1045
        Height = 171
        Align = alClient
        BevelOuter = bvNone
        ParentBackground = False
        TabOrder = 0
        object EnergyLabel: TLabel
          Left = 87
          Top = 6
          Width = 50
          Height = 14
          Alignment = taRightJustify
          Caption = 'Energiya:'
        end
        object EnergyValueLabel: TLabel
          Left = 141
          Top = 4
          Width = 25
          Height = 18
          Caption = '0.0'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -15
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object NucleusNameLabel: TLabel
          Left = 141
          Top = 31
          Width = 27
          Height = 18
          Caption = 'X-Y'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -15
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object NucleusLabel: TLabel
          Left = 38
          Top = 33
          Width = 99
          Height = 14
          Alignment = taRightJustify
          Caption = 'Bosh / Ona yadro:'
        end
        object EmitterLabel: TLabel
          Left = 29
          Top = 61
          Width = 109
          Height = 14
          Alignment = taRightJustify
          Caption = #947'-nurlanuvchi yadro:'
        end
        object EmitterNameLabel: TLabel
          Left = 141
          Top = 59
          Width = 27
          Height = 18
          Caption = 'X-Y'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -15
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object SeriesNameLabel: TLabel
          Left = 141
          Top = 115
          Width = 10
          Height = 18
          Caption = 'X'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -15
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object SeriesLabel: TLabel
          Left = 46
          Top = 117
          Width = 91
          Height = 14
          Alignment = taRightJustify
          Caption = 'Radioaktiv qator:'
        end
        object GammaYieldLabel: TLabel
          Left = 12
          Top = 89
          Width = 126
          Height = 14
          Alignment = taRightJustify
          Caption = #947'-nurlanish ehtimoliyati:'
        end
        object GammaYieldValueLabel: TLabel
          Left = 141
          Top = 87
          Width = 25
          Height = 18
          Caption = '0.0'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -15
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
        end
      end
    end
  end
  object SpectrumPanel: TPanel
    Left = 0
    Top = 0
    Width = 451
    Height = 97
    Align = alClient
    BevelOuter = bvNone
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    ShowCaption = False
    TabOrder = 1
    object SpcChart: TChart
      Tag = -1
      Left = 0
      Top = 0
      Width = 1150
      Height = 380
      AllowPanning = pmNone
      Border.Visible = True
      BottomWall.Visible = False
      Foot.Visible = False
      LeftWall.Visible = False
      Legend.LegendStyle = lsSeries
      Legend.TextStyle = ltsValue
      Legend.Visible = False
      MarginBottom = 1
      MarginLeft = 1
      MarginRight = 1
      MarginTop = 1
      RightWall.Visible = True
      SubFoot.Visible = False
      SubTitle.Visible = False
      Title.Font.Height = -12
      Title.Font.Style = [fsBold]
      Title.Text.Strings = (
        'TChart')
      Title.Visible = False
      BottomAxis.Axis.Width = 1
      BottomAxis.Increment = 100.000000000000000000
      BottomAxis.TickLength = 2
      BottomAxis.Title.Caption = 'Energiya, keV'
      BottomAxis.Title.Font.Height = -13
      BottomAxis.Title.Font.Name = 'Tahoma'
      BottomAxis.Title.RoundSize = 12
      BottomAxis.Title.ShapeStyle = fosRoundRectangle
      DepthTopAxis.Grid.Visible = False
      LeftAxis.Automatic = False
      LeftAxis.AutomaticMinimum = False
      LeftAxis.Axis.Width = 1
      LeftAxis.ExactDateTime = False
      LeftAxis.Increment = 100.000000000000000000
      LeftAxis.Title.Caption = 'Impulslar soni'
      LeftAxis.Title.Font.Height = -13
      LeftAxis.Title.Font.Name = 'Tahoma'
      Panning.InsideBounds = True
      Panning.MouseWheel = pmwNone
      RightAxis.Automatic = False
      RightAxis.AutomaticMaximum = False
      RightAxis.AutomaticMinimum = False
      RightAxis.Axis.Width = 1
      RightAxis.Grid.Visible = False
      RightAxis.Labels = False
      RightAxis.LabelsFormat.Visible = False
      TopAxis.Automatic = False
      TopAxis.AutomaticMaximum = False
      TopAxis.AutomaticMinimum = False
      TopAxis.Grid.Visible = False
      TopAxis.Labels = False
      TopAxis.LabelsFormat.Visible = False
      TopAxis.Ticks.Visible = False
      View3D = False
      Zoom.FullRepaint = True
      ZoomWheel = pmwNormal
      OnAfterDraw = SpcChartAfterDraw
      Align = alClient
      Color = clMedGray
      TabStop = False
      TabOrder = 0
      OnMouseMove = SpcChartMouseMove
      ExplicitWidth = 451
      ExplicitHeight = 78
      DefaultCanvas = 'TGDIPlusCanvas'
      PrintMargins = (
        15
        30
        15
        30)
      ColorPaletteIndex = 13
      object SpectrumLine: TLineSeries
        SeriesColor = clBlue
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
    object StatusBar: TStatusBar
      Left = 0
      Top = 380
      Width = 1150
      Height = 19
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      Panels = <
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
      SizeGrip = False
      UseSystemFont = False
      ExplicitTop = 78
      ExplicitWidth = 451
    end
  end
  object TablePopupMenu: TPopupMenu
    Left = 960
    Top = 296
    object CopyMI: TMenuItem
      Caption = 'Nusxa olish'
      ShortCut = 16451
      OnClick = CopyMIClick
    end
  end
end
