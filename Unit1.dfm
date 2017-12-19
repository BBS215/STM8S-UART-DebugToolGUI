object Form1: TForm1
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'DebugToolGUI'
  ClientHeight = 176
  ClientWidth = 369
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 13
    Width = 54
    Height = 13
    Caption = 'COM '#1087#1086#1088#1090':'
  end
  object Label_status: TLabel
    Left = 208
    Top = 53
    Width = 80
    Height = 13
    Caption = #1053#1077' '#1087#1086#1076#1082#1083#1102#1095#1077#1085#1086
    Color = clBtnFace
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clRed
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentColor = False
    ParentFont = False
  end
  object Label5: TLabel
    Left = 7
    Top = 53
    Width = 99
    Height = 13
    Caption = #1040#1076#1088#1077#1089' '#1088#1077#1075#1080#1089#1090#1088#1072': 0x'
  end
  object Label6: TLabel
    Left = 21
    Top = 80
    Width = 85
    Height = 13
    Caption = #1044#1072#1085#1085#1099#1077': HEX: 0x'
  end
  object Label7: TLabel
    Left = 70
    Top = 134
    Width = 36
    Height = 13
    Caption = 'BIN: 0b'
  end
  object Label8: TLabel
    Left = 67
    Top = 107
    Width = 24
    Height = 13
    Caption = 'DEC:'
  end
  object Label9: TLabel
    Left = 111
    Top = 158
    Width = 96
    Height = 13
    Caption = '5432109876543210'
  end
  object Label10: TLabel
    Left = 111
    Top = 149
    Width = 36
    Height = 13
    Caption = '111111'
  end
  object Label11: TLabel
    Left = 90
    Top = 153
    Width = 16
    Height = 13
    Caption = 'Bit:'
  end
  object ComboBox_COMPORTS: TComboBox
    Left = 68
    Top = 10
    Width = 88
    Height = 21
    Style = csDropDownList
    TabOrder = 0
  end
  object Button_COMPort_update: TButton
    Left = 162
    Top = 8
    Width = 75
    Height = 25
    Caption = #1054#1073#1085#1086#1074#1080#1090#1100
    TabOrder = 1
    OnClick = Button_COMPort_updateClick
  end
  object Button_read: TButton
    Left = 231
    Top = 75
    Width = 112
    Height = 25
    Caption = #1057#1095#1080#1090#1072#1090#1100' '#1088#1077#1075#1080#1089#1090#1088
    TabOrder = 2
    OnClick = Button_readClick
  end
  object Edit_RegAddr: TEdit
    Left = 108
    Top = 50
    Width = 48
    Height = 21
    MaxLength = 4
    TabOrder = 3
  end
  object CheckBox_RegWidth: TCheckBox
    Left = 162
    Top = 79
    Width = 50
    Height = 17
    Caption = '16 '#1073#1080#1090
    TabOrder = 4
  end
  object Edit_RegDataHEX: TEdit
    Left = 108
    Top = 77
    Width = 48
    Height = 21
    MaxLength = 4
    TabOrder = 5
    Text = '00'
    OnKeyPress = Edit_RegDataHEXKeyPress
    OnKeyUp = Edit_RegDataHEXKeyUp
  end
  object Button_write: TButton
    Left = 231
    Top = 102
    Width = 112
    Height = 25
    Caption = #1047#1072#1087#1080#1089#1072#1090#1100' '#1088#1077#1075#1080#1089#1090#1088
    TabOrder = 6
    OnClick = Button_writeClick
  end
  object Edit_RegDataBIN: TEdit
    Left = 108
    Top = 131
    Width = 110
    Height = 21
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    MaxLength = 16
    ParentFont = False
    TabOrder = 7
    Text = '0000000000000000'
    OnKeyPress = Edit_RegDataBINKeyPress
    OnKeyUp = Edit_RegDataBINKeyUp
  end
  object Edit_RegDataDEC: TEdit
    Left = 108
    Top = 104
    Width = 48
    Height = 21
    MaxLength = 5
    TabOrder = 8
    Text = '0'
    OnKeyPress = Edit_RegDataDECKeyPress
    OnKeyUp = Edit_RegDataDECKeyUp
  end
  object Panel1: TPanel
    Left = 8
    Top = 39
    Width = 353
    Height = 5
    TabOrder = 9
  end
end
