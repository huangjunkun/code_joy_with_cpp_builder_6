object MainForm: TMainForm
  Left = 543
  Top = 238
  AlphaBlendValue = 225
  BorderStyle = bsNone
  Caption = 'MainForm'
  ClientHeight = 266
  ClientWidth = 292
  Color = clMedGray
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PopupMenu = PopupMenu1
  Visible = True
  OnClose = FormClose
  OnCreate = FormCreate
  OnDblClick = FormDblClick
  OnDestroy = FormDestroy
  OnDragDrop = FormDragDrop
  OnDragOver = FormDragOver
  OnKeyUp = FormKeyUp
  OnMouseDown = FormMouseDown
  OnMouseMove = FormMouseMove
  OnPaint = FormPaint
  OnResize = FormResize
  PixelsPerInch = 96
  TextHeight = 13
  object Shape_S: TShape
    Left = 336
    Top = 16
    Width = 30
    Height = 30
    Brush.Color = clLime
    Brush.Style = bsDiagCross
    Pen.Color = clRed
    Shape = stEllipse
    Visible = False
  end
  object Label2: TLabel
    Left = 248
    Top = 16
    Width = 72
    Height = 21
    Caption = 'Label2'
    Font.Charset = ANSI_CHARSET
    Font.Color = clRed
    Font.Height = -21
    Font.Name = #23435#20307
    Font.Style = [fsBold]
    ParentFont = False
    Visible = False
  end
  object Label_Hi: TLabel
    Left = 16
    Top = 416
    Width = 189
    Height = 51
    Caption = 'MyClock'
    Color = clGray
    Font.Charset = GB2312_CHARSET
    Font.Color = clGreen
    Font.Height = -51
    Font.Name = #26999#20307'_GB2312'
    Font.Style = [fsBold]
    ParentColor = False
    ParentFont = False
  end
  object Label1: TLabel
    Left = 64
    Top = 8
    Width = 72
    Height = 21
    Caption = 'Label1'
    Font.Charset = ANSI_CHARSET
    Font.Color = clRed
    Font.Height = -21
    Font.Name = #23435#20307
    Font.Style = [fsBold]
    ParentFont = False
  end
  object StatusBar1: TStatusBar
    Left = 0
    Top = 246
    Width = 292
    Height = 20
    Color = clGray
    Panels = <
      item
        Width = 50
      end>
    SimplePanel = False
  end
  object PopupMenu1: TPopupMenu
    Left = 8
    Top = 48
    object SetItem: TMenuItem
      Caption = '&SetClock '#26102#38047#35774#32622
      OnClick = SetItemClick
    end
    object PauseItem: TMenuItem
      Caption = '&Pause '#26242#20572#26102#38047
      OnClick = PauseItemClick
    end
    object ContinueItem: TMenuItem
      Caption = '&Continue '#32487#32493#26102#38047
      OnClick = ContinueItemClick
    end
    object N2: TMenuItem
      Caption = '-'
    end
    object HideShowItem: TMenuItem
      Caption = '&Hide '#38544#34255'/'#26174#31034#31383#20307
      ShortCut = 16496
      OnClick = HideShowItemClick
    end
    object N1: TMenuItem
      Caption = '-'
    end
    object AboutItem: TMenuItem
      Caption = #20851#20110'...(&A)'
      ShortCut = 112
      OnClick = AboutItemClick
    end
    object ExitItem: TMenuItem
      Caption = '&Exit '#36864#20986' '
      ShortCut = 27
      OnClick = ExitItemClick
    end
  end
  object TimerClock: TTimer
    Interval = 900
    OnTimer = TimerClockTimer
  end
end
