object Form1: TForm1
  Left = 286
  Top = 115
  AlphaBlendValue = 200
  BiDiMode = bdLeftToRight
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = #35745#31639#22120
  ClientHeight = 412
  ClientWidth = 331
  Color = clBlack
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clRed
  Font.Height = -20
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  ParentBiDiMode = False
  Position = poDefault
  PrintScale = poNone
  Visible = True
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 24
  object Client: TPanel
    Left = 0
    Top = 0
    Width = 331
    Height = 412
    Align = alClient
    Caption = ' '
    Color = clBlack
    TabOrder = 0
    object Label1: TLabel
      Left = 24
      Top = 64
      Width = 100
      Height = 24
      Caption = #35745#31639#32467#26524#65306
    end
    object Edit1: TEdit
      Left = 24
      Top = 24
      Width = 297
      Height = 32
      BiDiMode = bdLeftToRight
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -20
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentBiDiMode = False
      ParentFont = False
      TabOrder = 0
      Text = '  0.0'
      OnEnter = Edit1Enter
      OnKeyPress = Edit1KeyPress
    end
    object Button1: TButton
      Left = 24
      Top = 152
      Width = 41
      Height = 33
      Cursor = crHandPoint
      Caption = '4'
      DragKind = dkDock
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clYellow
      Font.Height = -20
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      ParentShowHint = False
      ShowHint = False
      TabOrder = 1
      OnClick = Button1Click
    end
    object Button3: TButton
      Left = 24
      Top = 248
      Width = 41
      Height = 33
      Cursor = crHandPoint
      Caption = '0'
      DragKind = dkDock
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -20
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      ParentShowHint = False
      ShowHint = False
      TabOrder = 2
      OnClick = Button3Click
    end
    object Button4: TButton
      Left = 24
      Top = 104
      Width = 41
      Height = 33
      Cursor = crHandPoint
      Caption = '1'
      DragKind = dkDock
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -20
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      ParentShowHint = False
      ShowHint = False
      TabOrder = 3
      OnClick = Button4Click
    end
    object Button2: TButton
      Left = 24
      Top = 200
      Width = 41
      Height = 33
      Cursor = crHandPoint
      Caption = '7'
      DragKind = dkDock
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -20
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      ParentShowHint = False
      ShowHint = False
      TabOrder = 4
      OnClick = Button2Click
    end
    object Button5: TButton
      Left = 152
      Top = 152
      Width = 41
      Height = 33
      Cursor = crHandPoint
      Caption = '6'
      DragKind = dkDock
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -20
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      ParentShowHint = False
      ShowHint = False
      TabOrder = 5
      OnClick = Button5Click
    end
    object Button7: TButton
      Left = 152
      Top = 104
      Width = 41
      Height = 33
      Cursor = crHandPoint
      Caption = '3'
      DragKind = dkDock
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -20
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      ParentShowHint = False
      ShowHint = False
      TabOrder = 6
      OnClick = Button7Click
    end
    object Button8: TButton
      Left = 152
      Top = 200
      Width = 41
      Height = 33
      Cursor = crHandPoint
      Caption = '9'
      DragKind = dkDock
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -20
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      ParentShowHint = False
      ShowHint = False
      TabOrder = 7
      OnClick = Button8Click
    end
    object Button9: TButton
      Left = 88
      Top = 152
      Width = 41
      Height = 33
      Cursor = crHandPoint
      Caption = '5'
      DragKind = dkDock
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -20
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      ParentShowHint = False
      ShowHint = False
      TabOrder = 8
      OnClick = Button9Click
    end
    object Button10: TButton
      Left = 88
      Top = 248
      Width = 41
      Height = 33
      Cursor = crHandPoint
      Caption = '.'
      DragKind = dkDock
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -20
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      ParentShowHint = False
      ShowHint = False
      TabOrder = 9
      OnClick = Button10Click
    end
    object Button11: TButton
      Left = 88
      Top = 104
      Width = 41
      Height = 33
      Cursor = crHandPoint
      Caption = '2'
      DragKind = dkDock
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -20
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      ParentShowHint = False
      ShowHint = False
      TabOrder = 10
      OnClick = Button11Click
    end
    object Button12: TButton
      Left = 88
      Top = 200
      Width = 41
      Height = 33
      Cursor = crHandPoint
      Caption = '8'
      DragKind = dkDock
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -20
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      ParentShowHint = False
      ShowHint = False
      TabOrder = 11
      OnClick = Button12Click
    end
    object Button13: TButton
      Left = 216
      Top = 152
      Width = 41
      Height = 33
      Cursor = crHandPoint
      Caption = '-'
      DragKind = dkDock
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -20
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      ParentShowHint = False
      ShowHint = False
      TabOrder = 12
      OnClick = Button13Click
    end
    object Button14: TButton
      Left = 216
      Top = 248
      Width = 41
      Height = 33
      Cursor = crHandPoint
      Caption = '/'
      DragKind = dkDock
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -20
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      ParentShowHint = False
      ShowHint = False
      TabOrder = 13
      OnClick = Button14Click
    end
    object Button15: TButton
      Left = 216
      Top = 104
      Width = 41
      Height = 33
      Cursor = crHandPoint
      Caption = '+'
      DragKind = dkDock
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -20
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      ParentShowHint = False
      ShowHint = False
      TabOrder = 14
      OnClick = Button15Click
    end
    object Button16: TButton
      Left = 216
      Top = 200
      Width = 41
      Height = 33
      Cursor = crHandPoint
      Caption = '*'
      DragKind = dkDock
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -20
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      ParentShowHint = False
      ShowHint = False
      TabOrder = 15
      OnClick = Button16Click
    end
    object Button17: TButton
      Left = 272
      Top = 152
      Width = 41
      Height = 33
      Cursor = crHandPoint
      Caption = ')'
      DragKind = dkDock
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -20
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      ParentShowHint = False
      ShowHint = False
      TabOrder = 16
      OnClick = Button17Click
    end
    object Button18: TButton
      Left = 272
      Top = 248
      Width = 41
      Height = 33
      Cursor = crHandPoint
      Hint = #35745#31639#32467#26524
      Caption = '='
      DragKind = dkDock
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -20
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      ParentShowHint = False
      ShowHint = False
      TabOrder = 17
      OnClick = jisuan
    end
    object Button19: TButton
      Left = 272
      Top = 104
      Width = 41
      Height = 33
      Cursor = crHandPoint
      Caption = '('
      DragKind = dkDock
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -20
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      ParentShowHint = False
      ShowHint = False
      TabOrder = 18
      OnClick = Button19Click
    end
    object Button20: TButton
      Left = 272
      Top = 200
      Width = 41
      Height = 33
      Cursor = crHandPoint
      Caption = 'CE'
      DragKind = dkDock
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -20
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      ParentShowHint = False
      ShowHint = False
      TabOrder = 19
      OnClick = ce
    end
    object Button6: TButton
      Left = 152
      Top = 248
      Width = 41
      Height = 33
      Cursor = crHandPoint
      Hint = #21024#38500#36864#22238
      Caption = '<-'
      DragKind = dkDock
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -27
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      ParentShowHint = False
      ShowHint = False
      TabOrder = 20
      OnClick = Backspace
    end
    object Edit2: TEdit
      Left = 128
      Top = 64
      Width = 193
      Height = 32
      Cursor = crNo
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -20
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      ReadOnly = True
      TabOrder = 21
      Text = '  0.0'
    end
    object Panel1: TPanel
      Left = 25
      Top = 296
      Width = 4
      Height = 25
      Caption = ' '
      Color = clLime
      DragKind = dkDock
      TabOrder = 22
      Visible = False
    end
    object Panel2: TPanel
      Left = 32
      Top = 288
      Width = 13
      Height = 5
      Caption = ' '
      Color = clLime
      DragKind = dkDock
      TabOrder = 23
      Visible = False
    end
    object Panel3: TPanel
      Left = 49
      Top = 296
      Width = 4
      Height = 25
      Caption = ' '
      Color = clLime
      DragKind = dkDock
      TabOrder = 24
      Visible = False
    end
    object Panel4: TPanel
      Left = 32
      Top = 320
      Width = 13
      Height = 5
      Caption = ' '
      Color = clLime
      TabOrder = 25
      Visible = False
    end
    object Panel5: TPanel
      Left = 25
      Top = 328
      Width = 4
      Height = 20
      Caption = ' '
      Color = clLime
      TabOrder = 26
      Visible = False
    end
    object Panel9: TPanel
      Left = 64
      Top = 288
      Width = 13
      Height = 5
      Caption = ' '
      Color = clLime
      DragKind = dkDock
      TabOrder = 27
      Visible = False
    end
    object Panel10: TPanel
      Left = 81
      Top = 296
      Width = 4
      Height = 25
      Caption = ' '
      Color = clLime
      DragKind = dkDock
      TabOrder = 28
      Visible = False
    end
    object Panel11: TPanel
      Left = 64
      Top = 320
      Width = 13
      Height = 5
      Caption = ' '
      Color = clLime
      TabOrder = 29
      Visible = False
    end
    object Panel12: TPanel
      Left = 57
      Top = 328
      Width = 4
      Height = 20
      Caption = ' '
      Color = clLime
      TabOrder = 30
      Visible = False
    end
    object Panel13: TPanel
      Left = 64
      Top = 352
      Width = 13
      Height = 5
      Caption = ' '
      Color = clLime
      TabOrder = 31
      Visible = False
    end
    object Panel14: TPanel
      Left = 80
      Top = 328
      Width = 4
      Height = 20
      Caption = ' '
      Color = clLime
      TabOrder = 32
      Visible = False
    end
    object Panel6: TPanel
      Left = 32
      Top = 352
      Width = 13
      Height = 5
      Caption = ' '
      Color = clLime
      TabOrder = 33
      Visible = False
    end
    object Panel7: TPanel
      Left = 49
      Top = 328
      Width = 4
      Height = 20
      Caption = ' '
      Color = clLime
      TabOrder = 34
      Visible = False
    end
    object Panel8: TPanel
      Left = 57
      Top = 296
      Width = 4
      Height = 25
      Caption = ' '
      Color = clLime
      DragKind = dkDock
      TabOrder = 35
      Visible = False
    end
    object Panel15: TPanel
      Left = 88
      Top = 312
      Width = 4
      Height = 10
      Caption = ' '
      Color = clLime
      TabOrder = 36
      Visible = False
    end
    object Panel16: TPanel
      Left = 88
      Top = 328
      Width = 4
      Height = 10
      Caption = ' '
      Color = clLime
      TabOrder = 37
      Visible = False
    end
    object Panel17: TPanel
      Left = 97
      Top = 296
      Width = 4
      Height = 25
      Caption = ' '
      Color = clLime
      DragKind = dkDock
      TabOrder = 38
      Visible = False
    end
    object Panel18: TPanel
      Left = 104
      Top = 288
      Width = 13
      Height = 5
      Caption = ' '
      Color = clLime
      DragKind = dkDock
      TabOrder = 39
      Visible = False
    end
    object Panel19: TPanel
      Left = 121
      Top = 296
      Width = 4
      Height = 25
      Caption = ' '
      Color = clLime
      DragKind = dkDock
      TabOrder = 40
      Visible = False
    end
    object Panel20: TPanel
      Left = 104
      Top = 320
      Width = 13
      Height = 5
      Caption = ' '
      Color = clLime
      TabOrder = 41
      Visible = False
    end
    object Panel21: TPanel
      Left = 97
      Top = 328
      Width = 4
      Height = 20
      Caption = ' '
      Color = clLime
      TabOrder = 42
      Visible = False
    end
    object Panel22: TPanel
      Left = 104
      Top = 352
      Width = 13
      Height = 5
      Caption = ' '
      Color = clLime
      TabOrder = 43
      Visible = False
    end
    object Panel23: TPanel
      Left = 121
      Top = 328
      Width = 4
      Height = 20
      Caption = ' '
      Color = clLime
      TabOrder = 44
      Visible = False
    end
    object Panel24: TPanel
      Left = 128
      Top = 296
      Width = 4
      Height = 25
      Caption = ' '
      Color = clLime
      DragKind = dkDock
      TabOrder = 45
      Visible = False
    end
    object Panel25: TPanel
      Left = 137
      Top = 288
      Width = 13
      Height = 5
      Caption = ' '
      Color = clLime
      DragKind = dkDock
      TabOrder = 46
      Visible = False
    end
    object Panel26: TPanel
      Left = 152
      Top = 296
      Width = 4
      Height = 25
      Caption = ' '
      Color = clLime
      DragKind = dkDock
      TabOrder = 47
      Visible = False
    end
    object Panel27: TPanel
      Left = 136
      Top = 320
      Width = 13
      Height = 5
      Caption = ' '
      Color = clLime
      TabOrder = 48
      Visible = False
    end
    object Panel28: TPanel
      Left = 128
      Top = 328
      Width = 4
      Height = 20
      Caption = ' '
      Color = clLime
      TabOrder = 49
      Visible = False
    end
    object Panel29: TPanel
      Left = 137
      Top = 352
      Width = 13
      Height = 5
      Caption = ' '
      Color = clLime
      TabOrder = 50
      Visible = False
    end
    object Panel30: TPanel
      Left = 153
      Top = 328
      Width = 4
      Height = 20
      Caption = ' '
      Color = clLime
      TabOrder = 51
      Visible = False
    end
    object Panel31: TPanel
      Left = 160
      Top = 312
      Width = 4
      Height = 10
      Caption = ' '
      Color = clLime
      TabOrder = 52
      Visible = False
    end
    object Panel32: TPanel
      Left = 160
      Top = 328
      Width = 4
      Height = 10
      Caption = ' '
      Color = clLime
      TabOrder = 53
      Visible = False
    end
    object Panel33: TPanel
      Left = 169
      Top = 296
      Width = 4
      Height = 25
      Caption = ' '
      Color = clLime
      DragKind = dkDock
      TabOrder = 54
      Visible = False
    end
    object Panel34: TPanel
      Left = 176
      Top = 288
      Width = 13
      Height = 5
      Caption = ' '
      Color = clLime
      DragKind = dkDock
      TabOrder = 55
      Visible = False
    end
    object Panel35: TPanel
      Left = 193
      Top = 296
      Width = 4
      Height = 25
      Caption = ' '
      Color = clLime
      DragKind = dkDock
      TabOrder = 56
      Visible = False
    end
    object Panel36: TPanel
      Left = 176
      Top = 320
      Width = 13
      Height = 5
      Caption = ' '
      Color = clLime
      TabOrder = 57
      Visible = False
    end
    object Panel37: TPanel
      Left = 169
      Top = 328
      Width = 4
      Height = 20
      Caption = ' '
      Color = clLime
      TabOrder = 58
      Visible = False
    end
    object Panel38: TPanel
      Left = 176
      Top = 352
      Width = 13
      Height = 5
      Caption = ' '
      Color = clLime
      TabOrder = 59
      Visible = False
    end
    object Panel39: TPanel
      Left = 193
      Top = 328
      Width = 4
      Height = 20
      Caption = ' '
      Color = clLime
      TabOrder = 60
      Visible = False
    end
    object Panel40: TPanel
      Left = 200
      Top = 296
      Width = 4
      Height = 25
      Caption = ' '
      Color = clLime
      DragKind = dkDock
      TabOrder = 61
      Visible = False
    end
    object Panel41: TPanel
      Left = 209
      Top = 288
      Width = 13
      Height = 5
      Caption = ' '
      Color = clLime
      DragKind = dkDock
      TabOrder = 62
      Visible = False
    end
    object Panel42: TPanel
      Left = 222
      Top = 296
      Width = 4
      Height = 25
      Caption = ' '
      Color = clLime
      DragKind = dkDock
      TabOrder = 63
      Visible = False
    end
    object Panel43: TPanel
      Left = 208
      Top = 320
      Width = 13
      Height = 5
      Caption = ' '
      Color = clLime
      TabOrder = 64
      Visible = False
    end
    object Panel44: TPanel
      Left = 200
      Top = 328
      Width = 4
      Height = 20
      Caption = ' '
      Color = clLime
      TabOrder = 65
      Visible = False
    end
    object Panel45: TPanel
      Left = 209
      Top = 352
      Width = 13
      Height = 5
      Caption = ' '
      Color = clLime
      TabOrder = 66
      Visible = False
    end
    object Panel46: TPanel
      Left = 222
      Top = 328
      Width = 4
      Height = 20
      Caption = ' '
      Color = clLime
      TabOrder = 67
      Visible = False
    end
    object Edit3: TEdit
      Left = 168
      Top = 360
      Width = 97
      Height = 32
      Cursor = crNo
      Color = clNone
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clLime
      Font.Height = -20
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      ReadOnly = True
      TabOrder = 68
    end
    object Edit4: TEdit
      Left = 72
      Top = 360
      Width = 97
      Height = 32
      Cursor = crNo
      Color = clNone
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clLime
      Font.Height = -20
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      ReadOnly = True
      TabOrder = 69
      Text = #29616#22312#26085#26399':'
    end
  end
  object Timer1: TTimer
    OnTimer = Timer1Timer
    Left = 40
    Top = 360
  end
end
