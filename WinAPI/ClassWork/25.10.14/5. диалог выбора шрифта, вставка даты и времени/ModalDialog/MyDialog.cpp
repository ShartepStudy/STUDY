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
	color=RGB(0,0,0);//текущий цвет текста - черный
	memset(&lf,0,sizeof(lf));//обнуляем структуру LOGFONT
	hFont = CreateFontIndirect(&lf);//создаём новый шрифт с характеристиками по умолчанию
	SendMessage(hEdit,WM_SETFONT,(WPARAM)hFont,1);	
}

void CMyDialog::OnFont()
{
	char buf[100];
	static CHOOSEFONT cf={sizeof(CHOOSEFONT)};//модальный диалог "Шрифт" требует заполнения полей данной структуры
	cf.hwndOwner=hDialog;
	cf.lpLogFont=&lf;
	cf.Flags=CF_EFFECTS /* отображать секцию видоизменения  */
		|CF_FORCEFONTEXIST /* предупреждение о попытке выбрать несуществующий шрифт */
		|CF_INITTOLOGFONTSTRUCT /* для инициализации элементов управления диалога Шрифт используется информация  структуры LOGFONT */
		|CF_SCREENFONTS; // отображать в списке только шрифты, поддерживаемые системой
	if(ChooseFont(&cf))//отображаем диалог Шрифт
	{
		color=cf.rgbColors;//запоминаем выбранный цвет шрифта
		DeleteObject(hFont);//удаляем старый шрифт
		hFont=CreateFontIndirect(&lf);//создаём новый шрифт с характеристиками, установленными в диалоге Шрифт
		SendMessage(hEdit,WM_SETFONT,(WPARAM)hFont,1);//устанавливаем для текстового поля новый шрифт	
		SetFocus(hEdit);//устанавливаем фокус ввода для текстового поля
	}
}

void CMyDialog::SetTimeDate()
{
	char buf[30]={0};
	time_t T=time(NULL);//получаем системное время
	struct tm t=*(localtime(&T));//преобразуем время в соответствии с нашим часовым поясом
	strftime(buf,30,"%H:%M  %d.%m.%Y",&t);//форматируем строку для вывода
	SendMessage(hEdit,EM_REPLACESEL,WPARAM(TRUE)/* возможность отмены последнего действия */,LPARAM (buf));//выводим строку в текущую позицию
	SetFocus(hEdit);//устанавливаем фокус ввода для текстового поля
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
		case WM_CTLCOLOREDIT: //сообщение приходит при необходимости покраски текстового поля
			SetTextColor((HDC)wp,ptr->color);//установим цвет текста
			return 1;
	}
	return 0;
}