object SetClock: TSetClock
  Left = 691
  Top = 136
  BorderStyle = bsDialog
  Caption = 'SetClock'
  ClientHeight = 385
  ClientWidth = 413
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 413
    Height = 344
    ActivePage = TabSheet2
    Align = alClient
    TabIndex = 1
    TabOrder = 0
    object TabSheet1: TTabSheet
      Caption = #26102#38388#26085#26399
      object GroupBox1: TGroupBox
        Left = 209
        Top = 0
        Width = 196
        Height = 316
        Align = alClient
        Caption = #26102#38388
        TabOrder = 0
      end
      object GroupBox2: TGroupBox
        Left = 0
        Top = 0
        Width = 209
        Height = 316
        Align = alLeft
        Caption = #26085#26399
        TabOrder = 1
        object DateTimePicker1: TDateTimePicker
          Left = 8
          Top = 32
          Width = 186
          Height = 21
          CalAlignment = dtaLeft
          Date = 39793.5941822106
          Time = 39793.5941822106
          DateFormat = dfShort
          DateMode = dmComboBox
          Kind = dtkDate
          ParseInput = False
          TabOrder = 0
        end
      end
    end
    object TabSheet2: TTabSheet
      Caption = #30028#38754#35774#32622
      ImageIndex = 1
      object RadioGroup1: TRadioGroup
        Left = 0
        Top = 0
        Width = 201
        Height = 177
        Caption = #39068#33394#35774#32622
        Items.Strings = (
          #26102#38047#32972#26223
          #31186#38024
          #20998#38024
          #26102#38024
          #25968#23383#65292#36793#26694)
        TabOrder = 0
        OnClick = RadioGroup1Click
      end
      object RadioGroup2: TRadioGroup
        Left = 208
        Top = 0
        Width = 201
        Height = 177
        Caption = #22823#23567#35774#32622'(Width)'
        Items.Strings = (
          #26102#38047#25968#23383
          #31186#38024
          #20998#38024#65288#26102#38047#36793#26694#65289
          #26102#38024)
        TabOrder = 1
      end
      object BitBtnSetSize: TBitBtn
        Left = 8
        Top = 274
        Width = 113
        Height = 25
        Hint = #21487#20197#22312#26102#38047#31383#20307#30452#25509#35843#25972
        Caption = #35774#32622#31383#20307#22823#23567
        ParentShowHint = False
        ShowHint = True
        TabOrder = 2
        OnClick = BitBtnSetSizeClick
        Glyph.Data = {
          76010000424D7601000000000000760000002800000020000000100000000100
          04000000000000010000120B0000120B00001000000000000000000000000000
          800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333300000000
          0000333377777777777733330FFFFFFFFFF033337F3FFF3F3FF733330F000F0F
          00F033337F777373773733330FFFFFFFFFF033337F3FF3FF3FF733330F00F00F
          00F033337F773773773733330FFFFFFFFFF033337FF3333FF3F7333300FFFF00
          F0F03333773FF377F7373330FB00F0F0FFF0333733773737F3F7330FB0BF0FB0
          F0F0337337337337373730FBFBF0FB0FFFF037F333373373333730BFBF0FB0FF
          FFF037F3337337333FF700FBFBFB0FFF000077F333337FF37777E0BFBFB000FF
          0FF077FF3337773F7F37EE0BFB0BFB0F0F03777FF3733F737F73EEE0BFBF00FF
          00337777FFFF77FF7733EEEE0000000003337777777777777333}
        NumGlyphs = 2
      end
      object LabeledEdit1: TLabeledEdit
        Left = 215
        Top = 200
        Width = 122
        Height = 21
        EditLabel.Width = 135
        EditLabel.Height = 15
        EditLabel.Caption = #35831#36755#20837#35201#35774#32622#30340#22823#23567
        EditLabel.Font.Charset = ANSI_CHARSET
        EditLabel.Font.Color = clWindowText
        EditLabel.Font.Height = -15
        EditLabel.Font.Name = #23435#20307
        EditLabel.Font.Style = []
        EditLabel.ParentFont = False
        LabelPosition = lpAbove
        LabelSpacing = 3
        TabOrder = 3
        OnExit = LabeledEdit1Exit
        OnKeyPress = LabeledEdit1KeyPress
      end
      object CBTransparent: TCheckBox
        Left = 10
        Top = 193
        Width = 127
        Height = 17
        Caption = #31383#20307#26159#21542#36879#26126
        Checked = True
        State = cbChecked
        TabOrder = 4
        OnClick = CBTransparentClick
      end
      object BitBtnDefault: TBitBtn
        Left = 216
        Top = 272
        Width = 113
        Height = 25
        Caption = #24674#22797#40664#35748#35774#32622
        TabOrder = 5
        OnClick = BitBtnDefaultClick
        Glyph.Data = {
          76010000424D7601000000000000760000002800000020000000100000000100
          04000000000000010000120B0000120B00001000000000000000000000000000
          800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333333333
          3333333333FFFFF3333333333000003333333333F77777FFF333333009999900
          3333333777777777FF33330998FFF899033333777333F3777FF33099FFFCFFF9
          903337773337333777F3309FFFFFFFCF9033377333F3337377FF098FF0FFFFFF
          890377F3373F3333377F09FFFF0FFFFFF90377F3F373FFFFF77F09FCFFF90000
          F90377F733377777377F09FFFFFFFFFFF90377F333333333377F098FFFFFFFFF
          890377FF3F33333F3773309FCFFFFFCF9033377F7333F37377F33099FFFCFFF9
          90333777FF37F3377733330998FCF899033333777FF7FF777333333009999900
          3333333777777777333333333000003333333333377777333333}
        NumGlyphs = 2
      end
      object CBFormStyle: TCheckBox
        Left = 10
        Top = 235
        Width = 151
        Height = 17
        Caption = #31383#20307#26159#21542#24635#22312#26368#19978#38754
        TabOrder = 6
        OnClick = CBFormStyleClick
      end
      object CBTrayIcon: TCheckBox
        Left = 216
        Top = 233
        Width = 99
        Height = 19
        Caption = #26174#31034#25176#30424#22270#26631
        Checked = True
        State = cbChecked
        TabOrder = 7
        OnClick = CBTrayIconClick
      end
    end
    object TabSheet3: TTabSheet
      Caption = #31383#20307#35774#32622
      ImageIndex = 2
      object GroupBox3: TGroupBox
        Left = 0
        Top = 0
        Width = 405
        Height = 105
        Align = alTop
        Caption = #31383#20307#36879#26126#24230
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 0
        object TrackBar1: TTrackBar
          Left = 24
          Top = 36
          Width = 321
          Height = 45
          Max = 225
          Orientation = trHorizontal
          Frequency = 1
          Position = 225
          SelEnd = 0
          SelStart = 0
          TabOrder = 0
          TickMarks = tmBottomRight
          TickStyle = tsManual
          OnChange = TrackBar1Change
        end
      end
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 344
    Width = 413
    Height = 41
    Align = alBottom
    Caption = ' '
    TabOrder = 1
    object BitBtnCancel: TBitBtn
      Left = 32
      Top = 8
      Width = 75
      Height = 25
      Caption = #21462#28040
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 0
      OnClick = BitBtnCancelClick
      Glyph.Data = {
        76010000424D7601000000000000760000002800000020000000100000000100
        04000000000000010000130B0000130B00001000000000000000000000000000
        800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333333333
        333333333333333333333333333333333333333FFF33FF333FFF339993370733
        999333777FF37FF377733339993000399933333777F777F77733333399970799
        93333333777F7377733333333999399933333333377737773333333333990993
        3333333333737F73333333333331013333333333333777FF3333333333910193
        333333333337773FF3333333399000993333333337377737FF33333399900099
        93333333773777377FF333399930003999333337773777F777FF339993370733
        9993337773337333777333333333333333333333333333333333333333333333
        3333333333333333333333333333333333333333333333333333}
      NumGlyphs = 2
    end
    object BitBtnApp: TBitBtn
      Left = 176
      Top = 8
      Width = 75
      Height = 25
      Caption = #24212#29992
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 1
      OnClick = BitBtnAppClick
      Glyph.Data = {
        76010000424D7601000000000000760000002800000020000000100000000100
        04000000000000010000120B0000120B00001000000000000000000000000000
        800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333000000
        000033333377777777773333330FFFFFFFF03FF3FF7FF33F3FF700300000FF0F
        00F077F777773F737737E00BFBFB0FFFFFF07773333F7F3333F7E0BFBF000FFF
        F0F077F3337773F3F737E0FBFBFBF0F00FF077F3333FF7F77F37E0BFBF00000B
        0FF077F3337777737337E0FBFBFBFBF0FFF077F33FFFFFF73337E0BF0000000F
        FFF077FF777777733FF7000BFB00B0FF00F07773FF77373377373330000B0FFF
        FFF03337777373333FF7333330B0FFFF00003333373733FF777733330B0FF00F
        0FF03333737F37737F373330B00FFFFF0F033337F77F33337F733309030FFFFF
        00333377737FFFFF773333303300000003333337337777777333}
      NumGlyphs = 2
    end
    object BitBtnOK: TBitBtn
      Left = 296
      Top = 8
      Width = 75
      Height = 25
      Caption = #30830#23450
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 2
      OnClick = BitBtnOKClick
      Glyph.Data = {
        76010000424D7601000000000000760000002800000020000000100000000100
        04000000000000010000120B0000120B00001000000000000000000000000000
        800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00555555555555
        555555555555555555555555555555555555555555FF55555555555559055555
        55555555577FF5555555555599905555555555557777F5555555555599905555
        555555557777FF5555555559999905555555555777777F555555559999990555
        5555557777777FF5555557990599905555555777757777F55555790555599055
        55557775555777FF5555555555599905555555555557777F5555555555559905
        555555555555777FF5555555555559905555555555555777FF55555555555579
        05555555555555777FF5555555555557905555555555555777FF555555555555
        5990555555555555577755555555555555555555555555555555}
      NumGlyphs = 2
    end
  end
  object ColorDialog1: TColorDialog
    Ctl3D = True
    Left = 352
    Top = 8
  end
end
