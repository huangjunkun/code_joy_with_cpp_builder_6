object MainForm: TMainForm
  Left = 198
  Top = 169
  Width = 592
  Height = 580
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
  object TreeView1: TTreeView
    Left = 200
    Top = 424
    Width = 241
    Height = 97
    Indent = 19
    TabOrder = 0
    Items.Data = {
      040000001A0000000000000000000000FFFFFFFFFFFFFFFF0000000000000000
      01311A0000000000000000000000FFFFFFFFFFFFFFFF00000000000000000132
      1A0000000000000000000000FFFFFFFFFFFFFFFF000000000300000001331A00
      00000000000000000000FFFFFFFFFFFFFFFF000000000000000001311A000000
      0000000000000000FFFFFFFFFFFFFFFF000000000000000001321A0000000000
      000000000000FFFFFFFFFFFFFFFF000000000000000001331A00000000000000
      00000000FFFFFFFFFFFFFFFF00000000000000000134}
  end
  object Button1: TButton
    Left = 480
    Top = 424
    Width = 75
    Height = 25
    Caption = 'Button1'
    TabOrder = 1
    OnClick = Button1Click
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 193
    Height = 546
    Align = alLeft
    TabOrder = 2
    DesignSize = (
      193
      546)
    object DriveComboBox1: TDriveComboBox
      Left = 8
      Top = 8
      Width = 177
      Height = 19
      Anchors = [akLeft, akTop, akRight]
      DirList = DirectoryListBox1
      TabOrder = 0
    end
    object DirectoryListBox1: TDirectoryListBox
      Left = 9
      Top = 33
      Width = 176
      Height = 168
      Anchors = [akLeft, akTop, akRight]
      FileList = FileListBox1
      ItemHeight = 16
      TabOrder = 1
    end
    object FilterComboBox1: TFilterComboBox
      Left = 8
      Top = 408
      Width = 177
      Height = 21
      Anchors = [akLeft, akTop, akRight]
      FileList = FileListBox1
      Filter = #25991#26412#25991#26723'(*.txt)|*.txt|All files (*.*)|*.*|C++'#28304#25991#20214'(*.cpp)|*.cpp'
      TabOrder = 2
    end
    object FileListBox1: TFileListBox
      Left = 8
      Top = 208
      Width = 177
      Height = 193
      Anchors = [akLeft, akTop, akRight]
      ItemHeight = 13
      Mask = '*.txt'
      TabOrder = 3
    end
  end
  object ListBox1: TListBox
    Left = 216
    Top = 8
    Width = 348
    Height = 377
    ItemHeight = 13
    TabOrder = 3
  end
end
