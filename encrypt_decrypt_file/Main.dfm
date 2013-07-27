object MainForm: TMainForm
  Left = 350
  Top = 239
  Width = 456
  Height = 381
  AutoSize = True
  Caption = 'MainForm'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 448
    Height = 272
    Align = alClient
    Caption = ' '
    TabOrder = 0
    object Bevel1: TBevel
      Left = 16
      Top = 80
      Width = 417
      Height = 9
      Shape = bsBottomLine
    end
    object cbInFile: TComboBox
      Left = 16
      Top = 16
      Width = 313
      Height = 22
      Style = csOwnerDrawVariable
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ItemHeight = 16
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
      TabOrder = 0
    end
    object btnInFile: TBitBtn
      Left = 352
      Top = 16
      Width = 75
      Height = 25
      Caption = #23548#20837#25991#20214'(&I)'
      TabOrder = 1
      OnClick = btnInFileClick
    end
    object btnOutFile: TBitBtn
      Left = 352
      Top = 56
      Width = 75
      Height = 25
      Caption = #23548#20986#25991#20214'(&O)'
      TabOrder = 2
      OnClick = btnOutFileClick
    end
    object DirectoryListBox1: TDirectoryListBox
      Left = 16
      Top = 99
      Width = 310
      Height = 135
      ItemHeight = 16
      TabOrder = 3
      OnChange = DirectoryListBox1Change
    end
    object eOutFile: TEdit
      Left = 16
      Top = 56
      Width = 313
      Height = 21
      ParentShowHint = False
      ShowHint = True
      TabOrder = 4
    end
    object ProgressBar1: TProgressBar
      Left = 1
      Top = 254
      Width = 446
      Height = 17
      Align = alBottom
      Min = 0
      Max = 100
      TabOrder = 5
    end
    object CheckBoxKey: TCheckBox
      Left = 336
      Top = 224
      Width = 97
      Height = 17
      Caption = #26159#21542#38656#35201#23494#38053'  '
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = #23435#20307
      Font.Style = []
      ParentFont = False
      TabOrder = 6
      OnClick = CheckBoxKeyClick
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 272
    Width = 448
    Height = 56
    Align = alBottom
    Caption = ' '
    TabOrder = 1
    object btnEncrypt: TBitBtn
      Left = 56
      Top = 18
      Width = 75
      Height = 25
      Caption = #25991#20214#21152#23494'(&E)'
      TabOrder = 0
      OnClick = btnEncryptClick
    end
    object btnhDecrypt: TBitBtn
      Left = 184
      Top = 20
      Width = 75
      Height = 23
      Caption = #25991#20214#35299#23494'(&D)'
      TabOrder = 1
      OnClick = btnhDecryptClick
    end
    object btnCancel: TBitBtn
      Left = 312
      Top = 20
      Width = 75
      Height = 23
      Caption = #21462#28040'(&P)'
      TabOrder = 2
      OnClick = btnCancelClick
    end
  end
  object StatusBar1: TStatusBar
    Left = 0
    Top = 328
    Width = 448
    Height = 19
    Panels = <
      item
        Width = 300
      end
      item
        Width = 50
      end>
    ParentShowHint = False
    ShowHint = True
    SimplePanel = False
    OnDblClick = StatusBar1DblClick
  end
  object OpenDialog1: TOpenDialog
    Left = 376
    Top = 272
  end
  object SaveDialog1: TSaveDialog
    Left = 408
    Top = 272
  end
  object Timer1: TTimer
    OnTimer = Timer1Timer
    Left = 376
    Top = 136
  end
end
