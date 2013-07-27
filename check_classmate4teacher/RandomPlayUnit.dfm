object PlayRandomForm: TPlayRandomForm
  Left = 371
  Top = 357
  BorderStyle = bsNone
  Caption = 'PlayRandomForm'
  ClientHeight = 138
  ClientWidth = 423
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  OnKeyPress = FormKeyPress
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 0
    Top = 0
    Width = 423
    Height = 138
    Align = alClient
    AutoSize = False
    Caption = 'Label1'
    Font.Charset = ANSI_CHARSET
    Font.Color = clRed
    Font.Height = -96
    Font.Name = #23435#20307
    Font.Style = []
    ParentFont = False
  end
  object Timer1: TTimer
    Interval = 1
    OnTimer = Timer1Timer
    Left = 8
    Top = 8
  end
end
