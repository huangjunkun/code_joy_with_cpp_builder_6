object ShowNameForm: TShowNameForm
  Left = 267
  Top = 177
  BorderStyle = bsNone
  ClientHeight = 364
  ClientWidth = 612
  Color = clBlack
  TransparentColor = True
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  Visible = True
  WindowState = wsMaximized
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object LabelShow: TLabel
    Left = 280
    Top = 72
    Width = 29
    Height = 56
    Font.Charset = GB2312_CHARSET
    Font.Color = clLime
    Font.Height = -56
    Font.Name = #26999#20307'_GB2312'
    Font.Style = [fsBold]
    ParentFont = False
    Transparent = True
    OnDblClick = LabelShowDblClick
  end
  object MainMenu1: TMainMenu
    Left = 336
    Top = 88
  end
end
