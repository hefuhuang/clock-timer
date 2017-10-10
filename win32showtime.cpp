
#define PI 3.1415926
#include<stdio.h>
#include<math.h>
#include<windows.h>
#include<dos.h>
#include<time.h>
#define ID_TIMER	1
#define TWOPI		(2*3.14159)

LRESULT CALLBACK WindowProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam );
int iCounts;
			struct tm *ptr;
			time_t it;  //����ϵͳʱ���ñ���
//int time;
int WINAPI WinMain(
  HINSTANCE hInstance,       //Ӧ�ó���ľ��ʵ��
  HINSTANCE hPrevInstance,   //��ǰʵ���ľ��
  LPSTR lpCmdLine,        //command line    
  int nCmdShow            //������ʾ���� show state  
  )
{
WNDCLASS wndcls;
wndcls.style=CS_HREDRAW | CS_VREDRAW;  //ˮƽ�ػ��봹ֱ�ػ�  CS_N0CLOSE
wndcls.cbClsExtra=0;
wndcls.cbWndExtra=0;   
wndcls.hbrBackground=(HBRUSH)CreateSolidBrush(RGB(224,200,355));   //������ɫ
wndcls.hCursor=LoadCursor(NULL,IDC_CROSS);    //���
wndcls.hIcon=LoadIcon(NULL,IDI_ASTERISK);    //����ͼ��
wndcls.hInstance=hInstance;
wndcls.lpfnWndProc=WindowProc;
wndcls.lpszClassName="nihao";    //�����ര����
wndcls.lpszMenuName=NULL;   //���ò˵�

RegisterClass(&wndcls);    //ע��

HWND hwnd;    //�������ڱ�ʶ
hwnd=CreateWindow("nihao",// registered class name      
				  "13193109 �ƺ͸�",  // window name
				  WS_OVERLAPPEDWINDOW,   // window style
				  0,0,600,600,NULL,NULL,
				  hInstance,//handle to application instance
				  NULL  // window-creation data
				  );  //���ڵĳ�Ϊ1500 ��Ϊ100
//�����ɹ��󣬷���ϵͳ��������ھ�������򷵻�NULL�����Ҫ��һ�������������hwnd��������


ShowWindow(hwnd ,SW_SHOWNORMAL);      //������ʾ״̬   ������������ʾ
UpdateWindow(hwnd);                   //���´���

SetTimer(hwnd,1,1000,NULL);      
///////////////////////////////////////////////

MSG msg;
while(GetMessage(&msg,NULL,0,0))    //ѭ���õ�����Ϣ
{	
    TranslateMessage(&msg);  //���������Ϣת��Ϊ�ַ���Ϣ

	DispatchMessage(&msg);  //����ϢͶ�ݵ����ڹ���
}
return msg.wParam;
////////////////////////////////////////////////
return 0;
}

LRESULT CALLBACK WindowProc(
  HWND hwnd,      // handle to window
  UINT uMsg,      // message identifier
  WPARAM wParam,  // first message parameter
  LPARAM lParam   // second message parameter
)
{
	switch(uMsg)
	{
	case WM_CREATE:
		::SetTimer(hwnd,111,1000,NULL);
		break;
	case WM_PAINT:
		{
		PAINTSTRUCT ps;   
		HDC			hdc;
		PAINTSTRUCT pt;
 
		hdc = ::BeginPaint(hwnd,&pt);
		SYSTEMTIME tm;
		::GetLocalTime(&tm);

		HBRUSH hb = (HBRUSH)::GetStockObject(DKGRAY_BRUSH);
		::SelectObject(hdc,hb);

		RECT rt;
		::GetClientRect(hwnd,&rt);  //��ȡ��ǰ����λ��

		LONG R,bc;
		bc = min(rt.right - rt.left,rt.bottom - rt.top)/2;
		R=bc*3/4;   //����Բ�뾶
	
		POINT point;
		point.x = (rt.left + rt.right)/2;
		point.y = (rt.bottom + rt.top)/2;   //Բ������

		HPEN hpen = ::CreatePen(PS_SOLID,2,RGB(245,255,255));		
		HPEN hn = (HPEN)::SelectObject(hdc,hpen);

		::SetTextColor(hdc,RGB(255,120,120));
		char sz[20];
		sprintf(sz,"%.2d:%.2d:%.2d",tm.wHour,tm.wMinute,tm.wSecond);
		::TextOut(hdc,20,20 ,sz,strlen(sz));	
		
		::Ellipse(hdc,point.x - R,point.y - R,point.x + R,point.y + R); 
		::Ellipse(hdc,point.x - R,point.y - R,point.x + R,point.y + R); //��Բ
		
		::SelectObject(hdc,hn);


		hpen = ::CreatePen(PS_SOLID,1,RGB(255,0,255));		
		hn = (HPEN)::SelectObject(hdc,hpen);

		POINT p0,p1;
		for(int i = 0 ; i < 60; i++)
		{
			
			p0.x = (long)(point.x + R*sin(PI/30 * i)*1.00f);
			p0.y =(long) (point.y - R*cos(PI/30 * i)*1.00f);
			p1.x = (long)(point.x + R*sin(PI/30 * i)*0.96f);
			p1.y = (long)(point.y - R*cos(PI/30 * i)*0.96f);
						
			::MoveToEx(hdc,p0.x,p0.y,NULL);
			::LineTo(hdc,p1.x,p1.y);                   //��ʾС��̶�
		}
		::SelectObject(hdc,hn);
		for(i = 0 ; i < 60; i += 5)
		{
			
			p0.x = (long)(point.x + R*sin(PI/30 * i)*1.00f);
			p0.y =(long) (point.y - R*cos(PI/30 * i)*1.00f);
			p1.x = (long)(point.x + R*sin(PI/30 * i)*0.90f);
			p1.y = (long)(point.y - R*cos(PI/30 * i)*0.90f);						
			::MoveToEx(hdc,p0.x,p0.y,NULL);
			::LineTo(hdc,p1.x,p1.y);                     //��ʾ���̶�
		}


		::SetTextColor(hdc,RGB(255,120,120));
		int j=0,k =12;
		for(i = 0 ; i < 60; i += 5)
		{
			p1.x = (long)(point.x-5 + R*sin(PI/30 * i)*0.85f);
			p1.y = (long)(point.y -5- R*cos(PI/30 * i)*0.85f);
			if(i == 0)
			{
				char szchar1[10];
				sprintf(szchar1,"%d",k);
				::TextOut(hdc,p1.x,p1.y ,szchar1,strlen(szchar1));
				j++;
			}
			else
			{
				char szchar[10];
				sprintf(szchar,"%d",j);
				::TextOut(hdc,p1.x,p1.y ,szchar,strlen(szchar));	//��ʾ����		
				j++;
			}
			
		}
		char szchar[10];
		sprintf(szchar,"%s","0");
		p1.x = (long)(point.x-6 + R*sin(PI/30 * i)*0.10f);
		p1.y = (long)(point.y-8 - R*cos(PI/30 * i)*0.10f);
		::TextOut(hdc,p1.x,p1.y ,szchar,strlen(szchar)); //����Բ��
	
		::SelectObject(hdc,hn);	

	
		hpen = ::CreatePen(PS_SOLID,1,RGB(0,0,255));		
		hn = (HPEN)::SelectObject(hdc,hpen);

		p0.x = (long)(point.x + R*sin(PI/30 * tm.wSecond)*0.80f);
		p0.y =(long) (point.y - R*cos(PI/30 * tm.wSecond)*0.80f);
		p1.x = (long)(point.x + R*sin(PI/30 * i)*0.10f);
		p1.y = (long)(point.y - R*cos(PI/30 * i)*0.10f);						
		::MoveToEx(hdc,p0.x,p0.y,NULL);
		::LineTo(hdc,p1.x,p1.y);  //����

		hpen = ::CreatePen(PS_SOLID,2,RGB(255,120,255));		
		hn = (HPEN)::SelectObject(hdc,hpen);
		p0.x = (long)(point.x + R*sin(PI/30 * tm.wMinute)*0.61f);
		p0.y =(long) (point.y - R*cos(PI/30 * tm.wMinute)*0.61f);
		p1.x = (long)(point.x + R*sin(PI/30 * i)*0.10f);
		p1.y = (long)(point.y - R*cos(PI/30 * i)*0.10f);						
		::MoveToEx(hdc,p0.x,p0.y,NULL);
		::LineTo(hdc,p1.x,p1.y); 

		hpen = ::CreatePen(PS_SOLID,3,RGB(120,120,120));		
		hn = (HPEN)::SelectObject(hdc,hpen);
		p0.x = (long)(point.x + R*sin(PI/6 * (tm.wHour+(double)(tm.wMinute/60.0)))*0.40f);
		p0.y =(long) (point.y - R*cos(PI/6 * (tm.wHour+(double)(tm.wMinute/60.0)))*0.40f);
		p1.x = (long)(point.x + R*sin(PI/30 * i)*0.10f);
		p1.y = (long)(point.y - R*cos(PI/30 * i)*0.10f);
		::MoveToEx(hdc,p0.x,p0.y,NULL);
		::LineTo(hdc,p1.x,p1.y);	//Сʱ	
		

		Sleep(1);
    	 TextOut(hdc,10,60,"�ƺ͸� 13193109",strlen("�ƺ͸� 13193109"));  //������ʾѧ��
		::EndPaint(hwnd,&pt);
		}
		break;
	case WM_TIMER:
		RECT rt;
		::GetClientRect(hwnd,&rt);
		::InvalidateRect(hwnd,&rt,TRUE);

		break;
	case WM_CLOSE:
		if (IDYES == ::MessageBox(hwnd, "��ȷ�Ϲرմ�����", "������", MB_YESNOCANCEL))
		{
			::DestroyWindow(hwnd);
		}
		::KillTimer(hwnd,111);
		break;

	case WM_DESTROY:
		::PostQuitMessage(0);
		break;

	default:
		return ::DefWindowProc(hwnd,uMsg,wParam,lParam);
	}

	return 0;

}
