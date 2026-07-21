object SettingsForm: TSettingsForm
  Left = 0
  Top = 0
  Caption = 'Sozlamalar'
  ClientHeight = 653
  ClientWidth = 950
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PopupMode = pmAuto
  Position = poMainFormCenter
  OnResize = FormResize
  OnShow = FormShow
  DesignSize = (
    950
    653)
  PixelsPerInch = 96
  TextHeight = 13
  object ShowBottomButton: TSpeedButton
    Left = 461
    Top = 594
    Width = 30
    Height = 30
    Flat = True
    Glyph.Data = {
      F6060000424DF606000000000000360000002800000018000000180000000100
      180000000000C0060000120B0000120B00000000000000000000FFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFAFAFAFAFAFAFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFB0B0B04D4D4D4D4D
      4DABABABFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFAEAEAE
      4D4D4D4D4D4D4D4D4D4D4D4DAEAEAEFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFB0B0B04D4D4D8181817575757575758686864D4D4DABABABFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFB0B0B04D4D4D818181FAFAFA7A7A7A7A7A7AFCFCFC8686864D
      4D4DABABABFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFB0B0B04D4D4D818181FAFAFAFFFFFF7A7A7A7A7A
      7AFFFFFFFCFCFC8686864D4D4DABABABFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFAEAEAE4D4D4D868686FCFCFCFFFFFF
      FFFFFF7A7A7A7A7A7AFFFFFFFFFFFFFCFCFC8686864D4D4DAEAEAEFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFBBBBBB838383FA
      FAFAFFFFFFFFFFFFFFFFFF7A7A7A7A7A7AFFFFFFFFFFFFFFFFFFFCFCFC868686
      B6B6B6FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF7A7A7A7A7A7AFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF7A7A7A7A7A
      7AFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFF7A7A7A7A7A7AFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFF7A7A7A7A7A7AFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF7A7A7A7A7A7AFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF7A7A7A7A7A
      7AFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFF7A7A7A7A7A7AFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFF7A7A7A7A7A7AFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF7A7A7A7A7A7AFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF7A7A7A7A7A
      7AFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF}
    Layout = blGlyphTop
    OnClick = ShowBottomButtonClick
  end
  object SaveButton: TButton
    Left = 774
    Top = 610
    Width = 75
    Height = 25
    Anchors = [akRight, akBottom]
    Caption = '&Saqlash'
    TabOrder = 0
    OnClick = SaveButtonClick
  end
  object CloseButton: TButton
    Left = 856
    Top = 610
    Width = 75
    Height = 25
    Anchors = [akRight, akBottom]
    Cancel = True
    Caption = '&Yopish'
    ModalResult = 8
    TabOrder = 1
  end
  object ScrollBox: TScrollBox
    Left = 0
    Top = 0
    Width = 950
    Height = 588
    HorzScrollBar.Smooth = True
    HorzScrollBar.Style = ssHotTrack
    HorzScrollBar.Tracking = True
    VertScrollBar.Smooth = True
    VertScrollBar.Style = ssHotTrack
    VertScrollBar.Tracking = True
    Align = alTop
    Anchors = [akLeft, akTop, akRight, akBottom]
    BevelInner = bvNone
    BevelOuter = bvNone
    DoubleBuffered = True
    ParentDoubleBuffered = False
    TabOrder = 2
    OnMouseWheel = ScrollBoxMouseWheel
    object ImageCorrect: TImage
      Left = 793
      Top = 38
      Width = 24
      Height = 24
      AutoSize = True
      Center = True
      Picture.Data = {
        0954506E67496D61676589504E470D0A1A0A0000000D49484452000000180000
        00180806000000E0773DF8000003244944415478DAED936B48935118C79FB39B
        EFDC3BDD74735BAD72A589A559B6C4CA6E0BC5EE17E92A45885D908C2222A28C
        90A80F5DB082C4AE8481545618943AAC4433AD30932ED2D49C9A9B59AD2DD7E6
        BBBD7B4F7B0BA472A560F5C93F9C4FE7E1FF7BCE79FE0F827F2C3404F82F00C5
        4E0591129FB2ADC9DC7455BF4D6FFCAB002283100894826B39AB721667976637
        B736B6EAF029DCF657006406C927861305E9BAF4E593474F06B3C50C5945594D
        F001E6D88EDA3A060508D818C013A945F92B1356AE8E5647630CF89B5797B50B
        97D495DCA9DC52B9D02720727FE4F2A498A4EDC575C5E9868306832F73C92609
        57AC145F5C103F7F5D84622C300CC698C188F160C8AFCD771B5B8C6BBB8F7717
        F601046C0D5832293AE64AF2F844C1F52745ED26A359673A616AFEB126282D88
        13A80A3C3377CAACB450D948604D198FD788E140D18B5B9E670DF5694C1E93DF
        6706F24C79B246A3BEA98B9A49202E60DA43A3F2DA9A96B76D269D39D76C646B
        8253839174B8F4F40CAD76F330B9123C1E6FD734001FF8B8C250C53C7EF97413
        95475DF8B1A15E40F89EF03B89DAB864AE40001C1E7C3B9866A0F2E1B3E6B726
        F31C578FBB432A95E424C44FC894AB64E0F1DEB1E6041242FD9B065C515F93E1
        3CEBCCFBF53B7B01E406724C8842727FB63676048FE0632E1F1087E7BDA6185C
        75EFB5C162EBBE3F7D5AC46659A88435673BC7422446ADAD9D8CFEC983EDF6F3
        F653BEE6F5D30C44EB45116AA5FCDEF4A9E12A4C00E2F211FB120C5F30EA7ED7
        039230D2DBB108239A8B288713BF6F7781FE51F52EEB45DBB1DFA5AD4F8A44A9
        A2711A55C8DDD819214ACACF015E08461C368218689A06ABFD23A69C2E84DB65
        F8F92BCB5ECBA54F87FF14679F7B40AE20276854C16561896E99D3FF8B17F2BD
        12B3697173807E2183478FBB0E580B6CD9FDEDCB6F178D5C46C686A983F5516B
        982087C88E10C73B789A03AE6A192E2FEB3C64BB61DBD79FF91F01ACFC17F9C7
        458E92976A3341E2143AC0755706C5851D477A686A37554AE141035811F388A9
        B1635525131324E2CBE71A4F521ED70EAACC3520F3010158C9978AE3C442BF29
        5D9FEDB9F6DB3DCC40CD070C188C8600FDEA2B39BF4128AA481E380000000049
        454E44AE426082}
      Visible = False
    end
    object ImageIncorrect: TImage
      Left = 742
      Top = 38
      Width = 24
      Height = 24
      AutoSize = True
      Center = True
      Picture.Data = {
        0954506E67496D61676589504E470D0A1A0A0000000D49484452000000180000
        00180806000000E0773DF80000040C4944415478DADD955D4C5B6518C79FF79C
        7EAC2D1F1DED6A0714DBB51DA5C810506250468A0A9A4CB3E885268652A98BD1
        78B3A98BD311B3B8442F8CEECEEC032C5DA66E5113B338B31AD814CDB6184166
        3F28E3F0D1A1B44821DB282DB5F0FA9C0354C533D4446FF626BDE8F33ECFFFF7
        7CF52D81FFF9905B13F031CB166B1A1A7C098EFB76361279B685D22531BF0E00
        46ABD31DCEAFA9B9377EFE7CD3E3C9E4C4DF023E0230B0003DF6E75A2CB14BDF
        C3745FD09300703F0DF027C86114DF880C4D85D555F8A083FADF39C2A143E313
        00576F0A380150CC009C2B7DD4612EBBDB417ECD53C08523EFD1E9C048D72C42
        5E58811C42F14DBC7899C955E772838C4869E8876FC8E007A787D1C1F114C084
        28C00B10B438AA6D96EA06A0999584F50570E9B8078682A3DE30423268AA4471
        7399D159FB244ACDCC096E4C6E0E8C0CF541F8D417834E00BB28E07D80A31B8D
        BA672A1F6AA68B2976F58EB2C53AE2FBE414044363C7794385EDF696C69D8FD1
        A5E86CD6476E2A24FD273F847870F418B6739728E02D4C4483D9151837B5DAB7
        D793F475A10A4AD18F316D86D3673E0706BFEE687E982C45A6E86ABC5CAFA6C1
        733D241E8E786E60957BFE30AFBF0CF96016A26DB5DD55030BF1B4605FC48FC4
        5228E016B94904F1540694E64208747F09712EDAC58BEF5DB30CA26B7A002105
        FC108D1A57A9DD4653D1A4E02744124255C5C504144ACAE46748A8FB6B981E8E
        797012EE7D6BC46F0AE04FFB32A4536BD4386D362BCC47AE0391CB8162D689F1
        71906A59984CA6213E3EEB45F1B67611F17501FB119087001D02AC1B24243118
        5BBD127AAFB2E9E99554864C8D4D772511F0FABF01BCB22CDE719B51EBAA5248
        E9426892D09539085BC5378ADF1C7B11E9C72A62A3BF7810E27EE39FB4E8657E
        A5515C6FD2B9EA1532C80427848CF9C84479091F4095810861562A91A0AD3795
        A151EE67BE12F79BEB0D798F42C6E426D31D9BCD45ADCD0A29807F2CDB931BDB
        ACB03B9110420EA954907B79E8F7C06D5BE12C56121D1EEF526ED9E2DECB71E2
        6BFA5A91F69841AD76EF94B0543210CEFE88AEDD594E5E44F16B57C6BC7CA4DA
        6A72BE9BA3A279FDFEAC4F067DCECA3600A3D674B6F87C6E51C0FE125DB0B6B2
        A2ACF1423F85E919E16EAEAA82BE944890A9A1112FF6BE2DB3BCAE9D855BCD2D
        6FE7A888AAEFF272915A0DB9D850073F7E3710DA1D89883F15ED4AB9819D5FE8
        B9E7FEEDE6FA8100CC9714C1C1C43C70E1613EF3B6332BFD6DC2394910622BB5
        38F7A994A08CFC04BD9577C0C5EEAF38562673B4A7D3E28F1D7F70DD0C68ECA9
        7EA4C9E21F19077F20DC859D6FFB6CCDF07620241F2155F6D2D6BA8A72EA3BF9
        2987B36A3CB0DE73BD7A5E35E98D542EF5A526677AE373C95DDEC525D11D6F65
        59A6D660386A379BEF0BF9FD0F3C1F8B5D5DEB738BFE27FF97E7376E298F2887
        18CA1E0000000049454E44AE426082}
      Visible = False
    end
    object Label1: TLabel
      Left = 35
      Top = 835
      Width = 26
      Height = 13
      Caption = 'Be-7'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label10: TLabel
      Left = 35
      Top = 170
      Width = 26
      Height = 13
      Caption = 'K-40'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label11: TLabel
      Left = 35
      Top = 194
      Width = 39
      Height = 13
      Caption = 'Cs-137'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label12: TLabel
      Left = 35
      Top = 272
      Width = 39
      Height = 13
      Caption = 'Namuna'
    end
    object Label13: TLabel
      Left = 35
      Top = 296
      Width = 40
      Height = 13
      Caption = 'Th-232'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label14: TLabel
      Left = 557
      Top = 272
      Width = 99
      Height = 13
      Caption = 'Spektr faylining nomi'
    end
    object Label16: TLabel
      Left = 135
      Top = 272
      Width = 235
      Height = 13
      Caption = 'Aktivligi (Bk), xatoligi (%) va qayd qilingan sanasi'
    end
    object Label18: TLabel
      Left = 35
      Top = 739
      Width = 40
      Height = 13
      Caption = 'Th-232'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label19: TLabel
      Left = 135
      Top = 446
      Width = 235
      Height = 13
      Caption = 'Aktivligi (Bk), xatoligi (%) va qayd qilingan sanasi'
    end
    object Label20: TLabel
      Left = 35
      Top = 763
      Width = 41
      Height = 13
      Caption = 'Ra-226'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label21: TLabel
      Left = 557
      Top = 446
      Width = 99
      Height = 13
      Caption = 'Spektr faylining nomi'
    end
    object Label22: TLabel
      Left = 35
      Top = 787
      Width = 26
      Height = 13
      Caption = 'K-40'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label23: TLabel
      Left = 35
      Top = 470
      Width = 40
      Height = 13
      Caption = 'Th-232'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label24: TLabel
      Left = 35
      Top = 446
      Width = 39
      Height = 13
      Caption = 'Namuna'
    end
    object Label25: TLabel
      Left = 35
      Top = 494
      Width = 41
      Height = 13
      Caption = 'Ra-226'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label26: TLabel
      Left = 35
      Top = 518
      Width = 26
      Height = 13
      Caption = 'K-40'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label27: TLabel
      Left = 35
      Top = 542
      Width = 39
      Height = 13
      Caption = 'Cs-137'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label28: TLabel
      Left = 35
      Top = 811
      Width = 39
      Height = 13
      Caption = 'Cs-137'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label29: TLabel
      Left = 35
      Top = 216
      Width = 55
      Height = 13
      Caption = 'Tabiiy fon'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label3: TLabel
      Left = 35
      Top = 368
      Width = 39
      Height = 13
      Caption = 'Cs-137'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label30: TLabel
      Left = 35
      Top = 390
      Width = 55
      Height = 13
      Caption = 'Tabiiy fon'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label31: TLabel
      Left = 35
      Top = 564
      Width = 55
      Height = 13
      Caption = 'Tabiiy fon'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label32: TLabel
      Left = 216
      Top = 717
      Width = 49
      Height = 13
      Caption = 'keV gacha'
    end
    object Label33: TLabel
      Left = 35
      Top = 717
      Width = 39
      Height = 13
      Caption = 'Namuna'
    end
    object Label34: TLabel
      Left = 557
      Top = 98
      Width = 99
      Height = 13
      Caption = 'Spektr faylining nomi'
    end
    object Label35: TLabel
      Left = 397
      Top = 98
      Width = 105
      Height = 13
      Caption = 'Spektr o'#8216'lchangan kun'
    end
    object Label36: TLabel
      Left = 397
      Top = 272
      Width = 105
      Height = 13
      Caption = 'Spektr o'#8216'lchangan kun'
    end
    object Label37: TLabel
      Left = 397
      Top = 446
      Width = 105
      Height = 13
      Caption = 'Spektr o'#8216'lchangan kun'
    end
    object Label4: TLabel
      Left = 35
      Top = 122
      Width = 40
      Height = 13
      Caption = 'Th-232'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label40: TLabel
      Left = 35
      Top = 98
      Width = 39
      Height = 13
      Caption = 'Namuna'
    end
    object Label5: TLabel
      Left = 35
      Top = 344
      Width = 26
      Height = 13
      Caption = 'K-40'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label6: TLabel
      Left = 35
      Top = 320
      Width = 41
      Height = 13
      Caption = 'Ra-226'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label7: TLabel
      Left = 135
      Top = 98
      Width = 235
      Height = 13
      Caption = 'Aktivligi (Bk), xatoligi (%) va qayd qilingan sanasi'
    end
    object Label8: TLabel
      Left = 35
      Top = 146
      Width = 41
      Height = 13
      Caption = 'Ra-226'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label9: TLabel
      Left = 135
      Top = 717
      Width = 38
      Height = 13
      Caption = 'keV dan'
    end
    object Title1Label: TLabel
      Left = 226
      Top = 75
      Width = 304
      Height = 13
      Caption = 'Zichligi 200 gr/l dan 500 gr/l gacha bo'#8216'lgan namunalar'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Title2Label: TLabel
      Left = 226
      Top = 248
      Width = 311
      Height = 13
      Caption = 'Zichligi 800 gr/l dan 1100 gr/l gacha bo'#8216'lgan namunalar'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Title3Label: TLabel
      Left = 226
      Top = 423
      Width = 318
      Height = 13
      Caption = 'Zichligi 1500 gr/l dan 1800 gr/l gacha bo'#8216'lgan namunalar'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object EnergiesTitleLabel: TLabel
      Left = 12
      Top = 684
      Width = 511
      Height = 19
      Caption = 'Foydalaniluvchi fotocho'#8216'qqilar sohalari (chap va o'#8216'ng nuqtalari)'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object SamplesTitleLabel: TLabel
      Left = 12
      Top = 9
      Width = 204
      Height = 19
      Caption = 'Etalon va fon namunalari'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object OtherSettingsTitleLabel: TLabel
      Left = 12
      Top = 889
      Width = 153
      Height = 19
      Caption = 'Boshqa sozlamalar'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object DetectorNameLabel: TLabel
      Left = 35
      Top = 44
      Width = 111
      Height = 13
      Caption = 'Detektor / Geometriya:'
    end
    object LanguageLabel: TLabel
      Left = 35
      Top = 927
      Width = 165
      Height = 13
      Caption = 'Interfeys tili (Interface language):'
    end
    object BeEnergy1Edit: TEdit
      Left = 135
      Top = 832
      Width = 58
      Height = 21
      TabOrder = 4
      Text = '430'
    end
    object BeEnergy2Edit: TEdit
      Left = 216
      Top = 832
      Width = 58
      Height = 21
      TabOrder = 5
      Text = '525'
    end
    object Bkg1Button: TButton
      Left = 843
      Top = 211
      Width = 26
      Height = 25
      Caption = '...'
      TabOrder = 6
      OnClick = BrowseButtonClick
    end
    object Bkg1FileName: TEdit
      Left = 557
      Top = 213
      Width = 284
      Height = 21
      TabOrder = 7
      OnChange = FileNameChange
    end
    object Bkg2Button: TButton
      Left = 843
      Top = 385
      Width = 26
      Height = 25
      Caption = '...'
      TabOrder = 8
      OnClick = BrowseButtonClick
    end
    object Bkg2FileName: TEdit
      Left = 557
      Top = 387
      Width = 284
      Height = 21
      TabOrder = 9
      OnChange = FileNameChange
    end
    object Bkg3Button: TButton
      Left = 843
      Top = 559
      Width = 26
      Height = 25
      Caption = '...'
      TabOrder = 10
      OnClick = BrowseButtonClick
    end
    object Bkg3FileName: TEdit
      Left = 557
      Top = 561
      Width = 284
      Height = 21
      TabOrder = 11
      OnChange = FileNameChange
    end
    object Cs1ActivityEdit: TEdit
      Left = 135
      Top = 191
      Width = 58
      Height = 21
      TabOrder = 12
    end
    object Cs1Button: TButton
      Left = 843
      Top = 187
      Width = 26
      Height = 25
      Caption = '...'
      TabOrder = 13
      OnClick = BrowseButtonClick
    end
    object Cs1Date: TDateTimePicker
      Left = 235
      Top = 191
      Width = 117
      Height = 21
      Date = 45742.000000000000000000
      Time = 0.380861782410647700
      TabOrder = 14
    end
    object Cs1ErrorEdit: TEdit
      Left = 197
      Top = 191
      Width = 34
      Height = 21
      TabOrder = 15
    end
    object Cs1FileName: TEdit
      Left = 557
      Top = 189
      Width = 284
      Height = 21
      TabOrder = 16
      OnChange = FileNameChange
    end
    object Cs1MesDate: TDateTimePicker
      Left = 397
      Top = 191
      Width = 117
      Height = 21
      Date = 45742.000000000000000000
      Time = 0.418707719909434700
      TabOrder = 17
    end
    object Cs2ActivityEdit: TEdit
      Left = 135
      Top = 365
      Width = 58
      Height = 21
      TabOrder = 18
    end
    object Cs2Button: TButton
      Left = 843
      Top = 361
      Width = 26
      Height = 25
      Caption = '...'
      TabOrder = 19
      OnClick = BrowseButtonClick
    end
    object Cs2Date: TDateTimePicker
      Left = 235
      Top = 365
      Width = 117
      Height = 21
      Date = 45742.000000000000000000
      Time = 0.418708159719244600
      TabOrder = 20
    end
    object Cs2ErrorEdit: TEdit
      Left = 197
      Top = 365
      Width = 34
      Height = 21
      TabOrder = 21
    end
    object Cs2FileName: TEdit
      Left = 557
      Top = 363
      Width = 284
      Height = 21
      TabOrder = 22
      OnChange = FileNameChange
    end
    object Cs2MesDate: TDateTimePicker
      Left = 397
      Top = 365
      Width = 117
      Height = 21
      Date = 45742.000000000000000000
      Time = 0.418707719909434700
      TabOrder = 23
    end
    object Cs3ActivityEdit: TEdit
      Left = 135
      Top = 539
      Width = 58
      Height = 21
      TabOrder = 24
    end
    object Cs3Button: TButton
      Left = 843
      Top = 535
      Width = 26
      Height = 25
      Caption = '...'
      TabOrder = 25
      OnClick = BrowseButtonClick
    end
    object Cs3Date: TDateTimePicker
      Left = 235
      Top = 539
      Width = 117
      Height = 21
      Date = 45742.000000000000000000
      Time = 0.418708784724003600
      TabOrder = 26
    end
    object Cs3ErrorEdit: TEdit
      Left = 197
      Top = 539
      Width = 34
      Height = 21
      TabOrder = 27
    end
    object Cs3FileName: TEdit
      Left = 557
      Top = 537
      Width = 284
      Height = 21
      TabOrder = 28
      OnChange = FileNameChange
    end
    object Cs3MesDate: TDateTimePicker
      Left = 397
      Top = 539
      Width = 117
      Height = 21
      Date = 45742.000000000000000000
      Time = 0.418707719909434700
      TabOrder = 29
    end
    object CsEnergy1Edit: TEdit
      Left = 135
      Top = 808
      Width = 58
      Height = 21
      TabOrder = 30
      Text = '612'
    end
    object CsEnergy2Edit: TEdit
      Left = 216
      Top = 784
      Width = 58
      Height = 21
      TabOrder = 31
      Text = '709'
    end
    object K1ActivityEdit: TEdit
      Left = 135
      Top = 167
      Width = 58
      Height = 21
      TabOrder = 32
    end
    object K1Button: TButton
      Left = 843
      Top = 163
      Width = 26
      Height = 25
      Caption = '...'
      TabOrder = 33
      OnClick = BrowseButtonClick
    end
    object K1Date: TDateTimePicker
      Left = 235
      Top = 167
      Width = 117
      Height = 21
      Date = 45742.000000000000000000
      Time = 0.380587037034274500
      TabOrder = 34
    end
    object K1ErrorEdit: TEdit
      Left = 197
      Top = 167
      Width = 34
      Height = 21
      TabOrder = 35
    end
    object K1FileName: TEdit
      Left = 557
      Top = 165
      Width = 284
      Height = 21
      TabOrder = 36
      OnChange = FileNameChange
    end
    object K1MesDate: TDateTimePicker
      Left = 397
      Top = 167
      Width = 117
      Height = 21
      Date = 45742.000000000000000000
      Time = 0.418707719909434700
      TabOrder = 37
    end
    object K2ActivityEdit: TEdit
      Left = 135
      Top = 341
      Width = 58
      Height = 21
      TabOrder = 38
    end
    object K2Button: TButton
      Left = 843
      Top = 337
      Width = 26
      Height = 25
      Caption = '...'
      TabOrder = 39
      OnClick = BrowseButtonClick
    end
    object K2Date: TDateTimePicker
      Left = 235
      Top = 341
      Width = 117
      Height = 21
      Date = 45742.000000000000000000
      Time = 0.418708240744308600
      TabOrder = 40
    end
    object K2ErrorEdit: TEdit
      Left = 197
      Top = 341
      Width = 34
      Height = 21
      TabOrder = 41
    end
    object K2FileName: TEdit
      Left = 557
      Top = 339
      Width = 284
      Height = 21
      TabOrder = 42
      OnChange = FileNameChange
    end
    object K2MesDate: TDateTimePicker
      Left = 397
      Top = 341
      Width = 117
      Height = 21
      Date = 45742.000000000000000000
      Time = 0.418707719909434700
      TabOrder = 43
    end
    object K3ActivityEdit: TEdit
      Left = 135
      Top = 515
      Width = 58
      Height = 21
      TabOrder = 44
    end
    object K3Button: TButton
      Left = 843
      Top = 511
      Width = 26
      Height = 25
      Caption = '...'
      TabOrder = 45
      OnClick = BrowseButtonClick
    end
    object K3Date: TDateTimePicker
      Left = 235
      Top = 515
      Width = 117
      Height = 21
      Date = 45742.000000000000000000
      Time = 0.418708680554118500
      TabOrder = 46
    end
    object K3ErrorEdit: TEdit
      Left = 197
      Top = 515
      Width = 34
      Height = 21
      TabOrder = 47
    end
    object K3FileName: TEdit
      Left = 557
      Top = 513
      Width = 284
      Height = 21
      TabOrder = 48
      OnChange = FileNameChange
    end
    object K3MesDate: TDateTimePicker
      Left = 397
      Top = 515
      Width = 117
      Height = 21
      Date = 45742.000000000000000000
      Time = 0.418707719909434700
      TabOrder = 49
    end
    object KEnergy1Edit: TEdit
      Left = 135
      Top = 784
      Width = 58
      Height = 21
      TabOrder = 50
      Text = '1385'
    end
    object KEnergy2Edit: TEdit
      Left = 216
      Top = 808
      Width = 58
      Height = 21
      TabOrder = 51
      Text = '1540'
    end
    object Ra1ActivityEdit: TEdit
      Left = 135
      Top = 143
      Width = 58
      Height = 21
      TabOrder = 52
    end
    object Ra1Button: TButton
      Left = 843
      Top = 139
      Width = 26
      Height = 25
      Caption = '...'
      TabOrder = 53
      OnClick = BrowseButtonClick
    end
    object Ra1Date: TDateTimePicker
      Left = 235
      Top = 143
      Width = 117
      Height = 21
      Date = 45742.000000000000000000
      Time = 0.380290173612593200
      TabOrder = 54
    end
    object Ra1ErrorEdit: TEdit
      Left = 197
      Top = 143
      Width = 34
      Height = 21
      TabOrder = 55
    end
    object Ra1FileName: TEdit
      Left = 557
      Top = 141
      Width = 284
      Height = 21
      TabOrder = 56
      OnChange = FileNameChange
    end
    object Ra1MesDate: TDateTimePicker
      Left = 397
      Top = 143
      Width = 117
      Height = 21
      Date = 45742.000000000000000000
      Time = 0.418707719909434700
      TabOrder = 57
    end
    object Ra2ActivityEdit: TEdit
      Left = 135
      Top = 317
      Width = 58
      Height = 21
      TabOrder = 58
    end
    object Ra2Button: TButton
      Left = 843
      Top = 313
      Width = 26
      Height = 25
      Caption = '...'
      TabOrder = 59
      OnClick = BrowseButtonClick
    end
    object Ra2Date: TDateTimePicker
      Left = 235
      Top = 317
      Width = 117
      Height = 21
      Date = 45742.000000000000000000
      Time = 0.418708333330869200
      TabOrder = 60
    end
    object Ra2ErrorEdit: TEdit
      Left = 197
      Top = 317
      Width = 34
      Height = 21
      TabOrder = 61
    end
    object Ra2FileName: TEdit
      Left = 557
      Top = 315
      Width = 284
      Height = 21
      TabOrder = 62
      OnChange = FileNameChange
    end
    object Ra2MesDate: TDateTimePicker
      Left = 397
      Top = 317
      Width = 117
      Height = 21
      Date = 45742.000000000000000000
      Time = 0.418707719909434700
      TabOrder = 63
    end
    object Ra3ActivityEdit: TEdit
      Left = 135
      Top = 491
      Width = 58
      Height = 21
      TabOrder = 64
    end
    object Ra3Button: TButton
      Left = 843
      Top = 487
      Width = 26
      Height = 25
      Caption = '...'
      TabOrder = 65
      OnClick = BrowseButtonClick
    end
    object Ra3Date: TDateTimePicker
      Left = 235
      Top = 491
      Width = 117
      Height = 21
      Date = 45742.000000000000000000
      Time = 0.418708599536330400
      TabOrder = 66
    end
    object Ra3ErrorEdit: TEdit
      Left = 197
      Top = 491
      Width = 34
      Height = 21
      TabOrder = 67
    end
    object Ra3FileName: TEdit
      Left = 557
      Top = 489
      Width = 284
      Height = 21
      TabOrder = 68
      OnChange = FileNameChange
    end
    object Ra3MesDate: TDateTimePicker
      Left = 397
      Top = 491
      Width = 117
      Height = 21
      Date = 45742.000000000000000000
      Time = 0.418707719909434700
      TabOrder = 69
    end
    object RaEnergy1Edit: TEdit
      Left = 135
      Top = 760
      Width = 58
      Height = 21
      TabOrder = 70
      Text = '1677'
    end
    object RaEnergy2Edit: TEdit
      Left = 216
      Top = 760
      Width = 58
      Height = 21
      TabOrder = 71
      Text = '1846'
    end
    object Th1ActivityEdit: TEdit
      Left = 135
      Top = 119
      Width = 58
      Height = 21
      TabOrder = 72
    end
    object Th1Button: TButton
      Left = 843
      Top = 115
      Width = 26
      Height = 25
      Caption = '...'
      TabOrder = 73
      OnClick = BrowseButtonClick
    end
    object Th1Date: TDateTimePicker
      Left = 235
      Top = 119
      Width = 117
      Height = 21
      Date = 45742.000000000000000000
      Time = 0.418707719909434700
      TabOrder = 74
    end
    object Th1ErrorEdit: TEdit
      Left = 197
      Top = 119
      Width = 34
      Height = 21
      TabOrder = 75
    end
    object Th1FileName: TEdit
      Left = 557
      Top = 117
      Width = 284
      Height = 21
      TabOrder = 76
      OnChange = FileNameChange
    end
    object Th1MesDate: TDateTimePicker
      Left = 397
      Top = 119
      Width = 117
      Height = 21
      Date = 45742.000000000000000000
      Time = 0.418707719909434700
      TabOrder = 77
    end
    object Th2ActivityEdit: TEdit
      Left = 135
      Top = 293
      Width = 58
      Height = 21
      TabOrder = 78
    end
    object Th2Button: TButton
      Left = 843
      Top = 289
      Width = 26
      Height = 25
      Caption = '...'
      TabOrder = 79
      OnClick = BrowseButtonClick
    end
    object Th2Date: TDateTimePicker
      Left = 235
      Top = 293
      Width = 117
      Height = 21
      Date = 45742.000000000000000000
      Time = 0.418708414348657200
      TabOrder = 80
    end
    object Th2ErrorEdit: TEdit
      Left = 197
      Top = 293
      Width = 34
      Height = 21
      TabOrder = 81
    end
    object Th2FileName: TEdit
      Left = 557
      Top = 291
      Width = 284
      Height = 21
      TabOrder = 82
      OnChange = FileNameChange
    end
    object Th2MesDate: TDateTimePicker
      Left = 397
      Top = 293
      Width = 117
      Height = 21
      Date = 45742.000000000000000000
      Time = 0.418707719909434700
      TabOrder = 83
    end
    object Th3ActivityEdit: TEdit
      Left = 135
      Top = 467
      Width = 58
      Height = 21
      TabOrder = 84
    end
    object Th3Button: TButton
      Left = 843
      Top = 463
      Width = 26
      Height = 25
      Caption = '...'
      TabOrder = 85
      OnClick = BrowseButtonClick
    end
    object Th3Date: TDateTimePicker
      Left = 235
      Top = 467
      Width = 117
      Height = 21
      Date = 45742.000000000000000000
      Time = 0.418708518518542400
      TabOrder = 86
    end
    object Th3ErrorEdit: TEdit
      Left = 197
      Top = 467
      Width = 34
      Height = 21
      TabOrder = 87
    end
    object Th3FileName: TEdit
      Left = 557
      Top = 465
      Width = 284
      Height = 21
      TabOrder = 88
      OnChange = FileNameChange
    end
    object Th3MesDate: TDateTimePicker
      Left = 397
      Top = 467
      Width = 117
      Height = 21
      Date = 45742.000000000000000000
      Time = 0.418707719909434700
      TabOrder = 89
    end
    object ThEnergy1Edit: TEdit
      Left = 135
      Top = 736
      Width = 58
      Height = 21
      TabOrder = 90
      Text = '2500'
    end
    object ThEnergy2Edit: TEdit
      Left = 216
      Top = 736
      Width = 58
      Height = 21
      TabOrder = 91
      Text = '2720'
    end
    object ShowResultsWithMDA: TCheckBox
      Left = 35
      Top = 956
      Width = 197
      Height = 17
      Caption = 'Natijalarni <AMA ko'#8216'rinishida yoz'
      Checked = True
      State = cbChecked
      TabOrder = 92
    end
    object Be7PhotopeakEffEdit: TLabeledEdit
      Left = 225
      Top = 601
      Width = 108
      Height = 21
      Hint = '3 xil zichliklar uchun. Har birini nuqta-vergul bilan ajrating.'
      EditLabel.Width = 184
      EditLabel.Height = 13
      EditLabel.Caption = 'Be-7 uchun fotocho'#39'qqi effektivligi, %:'
      LabelPosition = lpLeft
      LabelSpacing = 5
      ParentShowHint = False
      ShowHint = True
      TabOrder = 93
      TextHint = 'Mas: 4.1; 3.5; 3'
    end
    object Be7SystematicErrorEdit: TLabeledEdit
      Left = 225
      Top = 626
      Width = 60
      Height = 21
      EditLabel.Width = 160
      EditLabel.Height = 13
      EditLabel.Caption = 'Be-7 uchun sistematik xatolik, %:'
      LabelPosition = lpLeft
      LabelSpacing = 29
      ParentShowHint = False
      ShowHint = True
      TabOrder = 94
    end
    object Point1FWHMEdit: TLabeledEdit
      Left = 174
      Top = 1011
      Width = 50
      Height = 21
      EditLabel.Width = 117
      EditLabel.Height = 13
      EditLabel.Caption = '1-nuqtadagi YBTK (keV):'
      LabelPosition = lpLeft
      LabelSpacing = 23
      ParentShowHint = False
      ShowHint = True
      TabOrder = 96
    end
    object Point1EnergyEdit: TLabeledEdit
      Left = 174
      Top = 984
      Width = 50
      Height = 21
      EditLabel.Width = 135
      EditLabel.Height = 13
      EditLabel.Caption = '1-nuqtadagi Energiya (keV):'
      LabelPosition = lpLeft
      LabelSpacing = 5
      ParentShowHint = False
      ShowHint = True
      TabOrder = 95
    end
    object Point2EnergyEdit: TLabeledEdit
      Left = 174
      Top = 1049
      Width = 50
      Height = 21
      EditLabel.Width = 135
      EditLabel.Height = 13
      EditLabel.Caption = '2-nuqtadagi Energiya (keV):'
      LabelPosition = lpLeft
      LabelSpacing = 5
      ParentShowHint = False
      ShowHint = True
      TabOrder = 97
    end
    object Point2FWHMEdit: TLabeledEdit
      Left = 174
      Top = 1076
      Width = 50
      Height = 21
      EditLabel.Width = 117
      EditLabel.Height = 13
      EditLabel.Caption = '2-nuqtadagi YBTK (keV):'
      LabelPosition = lpLeft
      LabelSpacing = 23
      ParentShowHint = False
      ShowHint = True
      TabOrder = 98
    end
    object DetectorSelector: TComboBox
      Left = 153
      Top = 40
      Width = 197
      Height = 21
      Style = csDropDownList
      TabOrder = 0
      OnChange = OnDetectorSelectorChange
    end
    object AddDetectorButton: TBitBtn
      Left = 354
      Top = 37
      Width = 26
      Height = 26
      Caption = '+'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      OnClick = AddDetectorButtonClick
    end
    object DeleteDetectorButton: TBitBtn
      Left = 383
      Top = 37
      Width = 26
      Height = 26
      Caption = #8211
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      OnClick = DeleteDetectorButtonClick
    end
    object DetectorEditor: TEdit
      Left = 153
      Top = 40
      Width = 197
      Height = 21
      TabOrder = 3
      Visible = False
      OnEnter = DetectorEditorEnter
      OnExit = DetectorEditorExit
      OnKeyDown = DetectorEditorKeyDown
    end
    object LanguageBox: TComboBox
      Left = 207
      Top = 924
      Width = 128
      Height = 21
      Style = csDropDownList
      ItemIndex = 0
      TabOrder = 99
      Text = 'O'#8216'zbekcha (Uzbek)'
      Items.Strings = (
        'O'#8216'zbekcha (Uzbek)'
        'English')
    end
  end
  object OpenDialog: TOpenDialog
    Options = [ofHideReadOnly, ofPathMustExist, ofFileMustExist, ofEnableSizing, ofForceShowHidden]
    Left = 807
    Top = 1
  end
end
