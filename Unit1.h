//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TComboBox *ComboBox_COMPORTS;
	TLabel *Label1;
	TButton *Button_COMPort_update;
	TLabel *Label_status;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label7;
	TLabel *Label8;
	TLabel *Label9;
	TLabel *Label10;
	TLabel *Label11;
	TButton *Button_read;
	TEdit *Edit_RegAddr;
	TCheckBox *CheckBox_RegWidth;
	TEdit *Edit_RegDataHEX;
	TButton *Button_write;
	TEdit *Edit_RegDataBIN;
	TEdit *Edit_RegDataDEC;
	TPanel *Panel1;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall Button_COMPort_updateClick(TObject *Sender);
	void __fastcall Edit_RegDataHEXKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall Edit_RegDataHEXKeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall Edit_RegDataBINKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall Edit_RegDataBINKeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall Edit_RegDataDECKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall Edit_RegDataDECKeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall Button_readClick(TObject *Sender);
	void __fastcall Button_writeClick(TObject *Sender);






private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
