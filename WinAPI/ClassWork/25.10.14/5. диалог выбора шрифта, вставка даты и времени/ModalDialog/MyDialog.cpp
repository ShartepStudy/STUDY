#include "MyDialog.h"

CMyDialog* CMyDialog::ptr=NULL;

CMyDialog::CMyDialog(void)
{
	ptr = this;
}

CMyDialog::~CMyDialog(void)
{

}

void CMyDialog::OnInitDialog(HWND h)
{
	hDialog=h;
	hEdit=GetDlgItem(hDialog,IDC_EDIT1);
	color=RGB(0,0,0);//������� ���� ������ - ������
	memset(&lf,0,sizeof(lf));//�������� ��������� LOGFONT
	hFont = CreateFontIndirect(&lf);//������ ����� ����� � ���������������� �� ���������
	SendMessage(hEdit,WM_SETFONT,(WPARAM)hFont,1);	
}

void CMyDialog::OnFont()
{
	char buf[100];
	static CHOOSEFONT cf={sizeof(CHOOSEFONT)};//��������� ������ "�����" ������� ���������� ����� ������ ���������
	cf.hwndOwner=hDialog;
	cf.lpLogFont=&lf;
	cf.Flags=CF_EFFECTS /* ���������� ������ �������������  */
		|CF_FORCEFONTEXIST /* �������������� � ������� ������� �������������� ����� */
		|CF_INITTOLOGFONTSTRUCT /* ��� ������������� ��������� ���������� ������� ����� ������������ ����������  ��������� LOGFONT */
		|CF_SCREENFONTS; // ���������� � ������ ������ ������, �������������� ��������
	if(ChooseFont(&cf))//���������� ������ �����
	{
		color=cf.rgbColors;//���������� ��������� ���� ������
		DeleteObject(hFont);//������� ������ �����
		hFont=CreateFontIndirect(&lf);//������ ����� ����� � ����������������, �������������� � ������� �����
		SendMessage(hEdit,WM_SETFONT,(WPARAM)hFont,1);//������������� ��� ���������� ���� ����� �����	
		SetFocus(hEdit);//������������� ����� ����� ��� ���������� ����
	}
}

void CMyDialog::SetTimeDate()
{
	char buf[30]={0};
	time_t T=time(NULL);//�������� ��������� �����
	struct tm t=*(localtime(&T));//����������� ����� � ������������ � ����� ������� ������
	strftime(buf,30,"%H:%M  %d.%m.%Y",&t);//����������� ������ ��� ������
	SendMessage(hEdit,EM_REPLACESEL,WPARAM(TRUE)/* ����������� ������ ���������� �������� */,LPARAM (buf));//������� ������ � ������� �������
	SetFocus(hEdit);//������������� ����� ����� ��� ���������� ����
}

BOOL CALLBACK CMyDialog::DlgProc(HWND hWnd,UINT mes,WPARAM wp,LPARAM lp)
{
	switch(mes)
	{
		case WM_CLOSE:
			EndDialog(hWnd,0);
			break;
		case WM_INITDIALOG:
			ptr->OnInitDialog(hWnd);
			break;
		case WM_COMMAND:
			if(LOWORD(wp)==IDC_BUTTON1)
				ptr->OnFont();
			else if(LOWORD(wp)==IDC_BUTTON2)
				ptr->SetTimeDate();
			break;
		case WM_CTLCOLOREDIT: //��������� �������� ��� ������������� �������� ���������� ����
			SetTextColor((HDC)wp,ptr->color);//��������� ���� ������
			return 1;
	}
	return 0;
}