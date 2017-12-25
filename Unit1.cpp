//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "uart.h"
#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------

void Update_COM_Port_list(void)
{
	std::list<_TCHAR*> port_list;
	int prev_ItemIndex = Form1->ComboBox_COMPORTS->ItemIndex;
	Form1->ComboBox_COMPORTS->Items->Clear();
	Get_port_list(port_list);
	for (std::list<_TCHAR*>::iterator it = port_list.begin(); it != port_list.end(); it++)
		Form1->ComboBox_COMPORTS->Items->Add(*it);
	if (port_list.size() > 0) {
		if (prev_ItemIndex < 0) {
			Form1->ComboBox_COMPORTS->ItemIndex = 0;
		} else {
			Form1->ComboBox_COMPORTS->ItemIndex = prev_ItemIndex;
		}
	} else {
		Form1->ComboBox_COMPORTS->ItemIndex = -1;
		Form1->ComboBox_COMPORTS->Text = L"";
    }
	Free_port_list(port_list);
}


void Edit_RegDataHEX_changed(void)
{
	uint16_t RegData;
	UnicodeString temp_str;
	int i;

	RegData = (uint16_t)wcstoul(Form1->Edit_RegDataHEX->Text.c_str(), NULL, 16);
	temp_str = L"";
	for(i=0;i<16;i++) {
		if (RegData & (1 << i)) {
			temp_str.Insert(L"1", 0);
		} else {
			temp_str.Insert(L"0", 0);
		}
	}
	Form1->Edit_RegDataBIN->Text = temp_str;
	temp_str.printf(L"%d", RegData);
	Form1->Edit_RegDataDEC->Text = temp_str;
}

void Edit_RegDataBIN_changed(void)
{
	uint16_t RegData;
	UnicodeString temp_str;
	RegData = (uint16_t)wcstoul(Form1->Edit_RegDataBIN->Text.c_str(), NULL, 2);
	if (Form1->CheckBox_RegWidth->Checked) temp_str.printf(L"%04x", RegData);
	else temp_str.printf(L"%02x", RegData);
	Form1->Edit_RegDataHEX->Text = temp_str;
	temp_str.printf(L"%d", RegData);
	Form1->Edit_RegDataDEC->Text = temp_str;
}

void Edit_RegDataDEC_changed(void)
{
	uint16_t RegData;
	UnicodeString temp_str;
	int i;

	RegData = (uint16_t)wcstoul(Form1->Edit_RegDataDEC->Text.c_str(), NULL, 10);
	temp_str = L"";
	for(i=0;i<16;i++) {
		if (RegData & (1 << i)) {
			temp_str.Insert(L"1", 0);
		} else {
			temp_str.Insert(L"0", 0);
		}
	}
	Form1->Edit_RegDataBIN->Text = temp_str;
	if (Form1->CheckBox_RegWidth->Checked) temp_str.printf(L"%04x", RegData);
	else temp_str.printf(L"%02x", RegData);
	Form1->Edit_RegDataHEX->Text = temp_str;
}

void ReadReg(void)
{
	int ret;
	uint16_t reg_addr;
	uint8_t width;
	uint16_t reg_data = 0;
	UnicodeString temp_str;

	Form1->Button_read->Enabled = false;
	Form1->Button_write->Enabled = false;
	Application->ProcessMessages();

	if (Form1->ComboBox_COMPORTS->Text.Length() == 0) {
		Form1->Label_status->Caption = L"Выберите COM порт";
		Form1->Label_status->Font->Color = clRed;
		goto exit;
	}
	Form1->Label_status->Caption = L"Чтение регистра...";
	Form1->Label_status->Font->Color = clBlue;
	Application->ProcessMessages();
	if (Form1->Edit_RegAddr->Text.Length() == 0) {
		Form1->Label_status->Caption = L"Введите адрес регистра";
		Form1->Label_status->Font->Color = clRed;
		goto exit;
	}
	reg_addr = (uint16_t)wcstoul(Form1->Edit_RegAddr->Text.c_str(), NULL, 16);
	if (Form1->CheckBox_RegWidth->Checked) width = 16;
	else width = 8;
	ret = Read_Register(Form1->ComboBox_COMPORTS->Text.c_str(), reg_addr, width, &reg_data);
	if (ret) {
		temp_str.printf(L"Ошибка %d", ret);
		Form1->Label_status->Caption = temp_str;
		Form1->Label_status->Font->Color = clRed;
	} else {
		if (Form1->CheckBox_RegWidth->Checked) temp_str.printf(L"%04x", reg_data);
		else temp_str.printf(L"%02x", reg_data);
		Form1->Edit_RegDataHEX->Text = temp_str;
		Edit_RegDataHEX_changed();
		Form1->Label_status->Caption = L"Регистр считан";
		Form1->Label_status->Font->Color = clGreen;
	}

exit:
	Form1->Button_read->Enabled = true;
	Form1->Button_write->Enabled = true;
}

void WriteReg(void)
{
	int ret;
	uint16_t reg_addr;
	uint8_t width;
	uint16_t reg_data;
	UnicodeString temp_str;

	Form1->Button_read->Enabled = false;
	Form1->Button_write->Enabled = false;
	Application->ProcessMessages();

	if (Form1->ComboBox_COMPORTS->Text.Length() == 0) {
		Form1->Label_status->Caption = L"Выберите COM порт";
		Form1->Label_status->Font->Color = clRed;
		goto exit;
	}
	Form1->Label_status->Caption = L"Запись регистра...";
	Form1->Label_status->Font->Color = clBlue;
	Application->ProcessMessages();
	if (Form1->Edit_RegAddr->Text.Length() == 0) {
		Form1->Label_status->Caption = L"Введите адрес регистра";
		Form1->Label_status->Font->Color = clRed;
		goto exit;
	}
	reg_addr = (uint16_t)wcstoul(Form1->Edit_RegAddr->Text.c_str(), NULL, 16);
	if (Form1->CheckBox_RegWidth->Checked) width = 16;
	else width = 8;
	reg_data = (uint16_t)wcstoul(Form1->Edit_RegDataHEX->Text.c_str(), NULL, 16);
	ret = Write_Register(Form1->ComboBox_COMPORTS->Text.c_str(), reg_addr, width, reg_data);
	if (ret) {
		temp_str.printf(L"Ошибка %d", ret);
		Form1->Label_status->Caption = temp_str;
		Form1->Label_status->Font->Color = clRed;
	} else {
		Form1->Label_status->Caption = L"Регистр записан";
		Form1->Label_status->Font->Color = clGreen;
	}

exit:
	Form1->Button_read->Enabled = true;
	Form1->Button_write->Enabled = true;
}


//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
	Update_COM_Port_list();
	Form1->Label_status->Caption = L"";
	Form1->Label_status->Font->Color = clRed;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button_COMPort_updateClick(TObject *Sender)
{
	Update_COM_Port_list();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit_RegDataHEXKeyPress(TObject *Sender, System::WideChar &Key)
{
	if (((Key >= L'0')&&(Key <= L'9'))
		||((Key >= L'a')&&(Key <= L'f'))
		||(Key == L'\b'))
	{
		// OK
	} else {
		Key = 0;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit_RegDataHEXKeyUp(TObject *Sender, WORD &Key, TShiftState Shift)
{
	Edit_RegDataHEX_changed();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit_RegDataBINKeyPress(TObject *Sender, System::WideChar &Key)
{
	if (((Key >= L'0')&&(Key <= L'1'))
		||(Key == L'\b'))
	{
		// OK
	} else {
		Key = 0;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit_RegDataBINKeyUp(TObject *Sender, WORD &Key, TShiftState Shift)
{
	Edit_RegDataBIN_changed();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit_RegDataDECKeyPress(TObject *Sender, System::WideChar &Key)
{
	if (((Key >= L'0')&&(Key <= L'9'))
		||(Key == L'\b'))
	{
		// OK
	} else {
		Key = 0;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit_RegDataDECKeyUp(TObject *Sender, WORD &Key, TShiftState Shift)
{
   Edit_RegDataDEC_changed();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button_readClick(TObject *Sender)
{
	ReadReg();
	Update_COM_Port_list();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button_writeClick(TObject *Sender)
{
	WriteReg();
	Update_COM_Port_list();
}
//---------------------------------------------------------------------------

