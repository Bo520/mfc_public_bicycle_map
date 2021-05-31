
// CS20180080331Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "CS20180080331.h"
#include "CS20180080331Dlg.h"
#include "afxdialogex.h"
#include "ConfirmQuitDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//一些函数声明
splitedinfo *info = NULL; //声明结构体数组
CStringArray *DivString(CString test);
int VecLength;//文本的行数

splitedinfo* user_info = NULL;//保存用户信息数组

int if_print = 0;  //记录是否在绘制轨迹的全局变量

BOOL input_data = 0; //用于记录用户是否导入了数据

int Start_x, Start_y,End_x,End_y;//轨迹得坐标声明

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCS20180080331Dlg 对话框



CCS20180080331Dlg::CCS20180080331Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CS20180080331_DIALOG, pParent)
	, m_stationid_remain(0)
	, m_stationid_addrass(0)
	, m_edit_id_input(0)
	, m_edit_name(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON_LOGO);
}

void CCS20180080331Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1_display, m_combobox_display);
	DDX_Text(pDX, IDC_EDIT_ID, m_edit_id_input);
	DDX_Control(pDX, IDC_COMBO1, m_combox_track_users);
	DDX_Control(pDX, IDC_COMBO2, m_combox_track_users2);
	DDX_Control(pDX, IDC_STATIC_draw_map, m_draw_map);
	DDX_Control(pDX, IDC_COMBO3, m_combox_station1);
	DDX_Control(pDX, IDC_COMBO4, m_combox_station2);
	DDX_Control(pDX, IDC_EDIT5, m_edit_distance);
	DDX_Text(pDX, IDC_EDIT4, m_edit_name);
}

BEGIN_MESSAGE_MAP(CCS20180080331Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_inputdata, &CCS20180080331Dlg::OnBnClickedButtoninputdata)
ON_BN_CLICKED(IDC_BUTTON_station_location, &CCS20180080331Dlg::OnBnClickedButtonstationlocation)
ON_BN_CLICKED(IDC_BUTTON_search_by_id, &CCS20180080331Dlg::OnBnClickedButtonsearchbyid)
ON_BN_CLICKED(IDC_BUTTON_track_user, &CCS20180080331Dlg::OnBnClickedButtontrackuser)
ON_BN_CLICKED(IDC_BUTTON3, &CCS20180080331Dlg::OnBnClickedButton3)
ON_WM_CTLCOLOR()
ON_BN_CLICKED(IDC_BUTTON1, &CCS20180080331Dlg::OnBnClickedButton1)
ON_WM_MOUSEMOVE()
ON_BN_CLICKED(IDC_BUTTON_track_users, &CCS20180080331Dlg::OnBnClickedButtontrackusers)
ON_CBN_SELCHANGE(IDC_COMBO1, &CCS20180080331Dlg::OnCbnSelchangeCombo1)
ON_CBN_SELCHANGE(IDC_COMBO2, &CCS20180080331Dlg::OnCbnSelchangeCombo2)
ON_BN_CLICKED(IDC_BUTTON2, &CCS20180080331Dlg::OnBnClickedButton2)
ON_CBN_SELCHANGE(IDC_COMBO1_display, &CCS20180080331Dlg::OnCbnSelchangeCombo1display)
ON_WM_MOUSEMOVE()
//ON_WM_NCMBUTTONDOWN()
ON_BN_CLICKED(IDC_BUTTON4, &CCS20180080331Dlg::OnBnClickedButton4)
ON_EN_CHANGE(IDC_EDIT4, &CCS20180080331Dlg::OnEnChangeEdit4)
ON_EN_CHANGE(IDC_EDIT2, &CCS20180080331Dlg::OnEnChangeEdit2)
ON_EN_CHANGE(IDC_EDIT_ID, &CCS20180080331Dlg::OnEnChangeEditId)
ON_CBN_SELCHANGE(IDC_COMBO3, &CCS20180080331Dlg::OnCbnSelchangeCombo3)
ON_WM_LBUTTONDOWN()
ON_WM_LBUTTONUP()
ON_BN_CLICKED(IDC_BUTTON5, &CCS20180080331Dlg::OnBnClickedButton5)
END_MESSAGE_MAP()


// CCS20180080331Dlg 消息处理程序

BOOL CCS20180080331Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码



	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CCS20180080331Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	SetDlgItemText(IDC_EDIT_ID, _T("0"));//清空编辑框
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else if((nID & 0xFFF0) == SC_CLOSE)
	{
		INT_PTR nRes;   //用于保存弹窗的返回值
		ConfirmQuitDlg cfQ;    //创建弹窗对象
		nRes = cfQ.DoModal();   //判断
		if (nRes == IDOK)
		{
			CDialog::OnOK(); //退出程序
		}
		else
		{
			; //继续程序
		}
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCS20180080331Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CCS20180080331Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



CString strContent;  //保存读取的文本,消息处理函数外定义以便其他按钮调用
void CCS20180080331Dlg::OnBnClickedButtoninputdata()
{
	vector<CString> SplitCString(CString strSource, CString ch);
	vector<CString> SplitCString(CString strSource, CString ch);//声明切分函数
	//定义文件对话框
	CFileDialog fdlg(TRUE, NULL, _T("*.*"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT
		, _T("表格文件(*.csv)|*.csv|所有文件(*.*)|*.*|"));
	if (IDCANCEL == fdlg.DoModal())
	{
		return;
	}
	//读取当前对话框选择的文件路径
	CString strPathName = fdlg.GetPathName();

	//打开选择的文件
	//构造文件，同时增加异常处理
	CFile cFile;
	CFileException e;

	if (FALSE == cFile.Open(strPathName, CFile::modeRead, &e))
	{
		CString strException;
		strException.Format(_T("This file could not be opened\n\t error code: %d\n"), e.m_cause);
		MessageBox(strException, _T("kiki Tips:"), MB_OK | MB_ICONERROR);
		return;
	}

	//读取打开的文件内容
	DWORD dwCount, dwFilelenth = (DWORD)cFile.GetLength();
	char* szBuffer = new char[dwFilelenth + 1];
	ZeroMemory(szBuffer, dwFilelenth + 1);
	while (dwCount = cFile.Read(szBuffer, dwFilelenth))
	{
		//拼接读取数据
		strContent += szBuffer;
	}
	//字节转换
	int len = WideCharToMultiByte(CP_UTF8, 0, strContent, strContent.GetLength(), NULL, NULL, NULL, NULL);
	char* pMulticharBuf = new char[len + 1];
	ZeroMemory(pMulticharBuf, sizeof(char) * len);
	WideCharToMultiByte(CP_UTF8, 0, strContent, -1, pMulticharBuf, len, NULL, NULL);

	cFile.Close();
	delete[] szBuffer;
	szBuffer = nullptr;

	input_data = 1; //记录用户导入数据成功了
	
	vector<CString>splitedText1 = SplitCString(strContent, _T("\n"));//按换行符切分好的字符串

	CString strContent1 = strContent;

	strContent1.Replace(_T('\n'), _T(','));//用逗号替代换行符
	vector<CString>splitedText = SplitCString(strContent1, _T(","));//按逗号切分好的字符串

	int vecLength = splitedText1.size(); //获取切分好的字符向量的长度..总共的行数
	VecLength = vecLength;
	for (int i = 0; i < vecLength; i++)
	{
		m_combobox_display.AddString(splitedText1[i]);
	}

	/*把文本分割为整型的StationID、TotalDocks、Docks in Service，字符串型的StationName、Addrass、Status、Location，
	浮点型的Latitude、Longitude，并存入结构体数组*/
	info = new splitedinfo[vecLength]; //动态分配数组内存
	for (int i = 1; i < vecLength; i++) {
		CStringArray* result = DivString(splitedText1[i]);
		CString StationID = result->GetAt(0);
		CString StationName = result->GetAt(1);
		CString Address = result->GetAt(2);
		CString TotalDocks = result->GetAt(3);
		CString DocksinService = result->GetAt(4);
		CString Status = result->GetAt(5);
		CString Latitude = result->GetAt(6);
		CString Longitude = result->GetAt(7);
		CString Location1; //= result->GetAt(8);
		CString Location2; //= result->GetAt(9);

		//转换
		int StationID_int = _wtoi(StationID);
		int TotalDocks_int = _wtoi(TotalDocks);
		int DockesinSerive_int = _wtoi(DocksinService);
		float Latitude_float = _wtof(Latitude);
		float Longitude_float = _wtof(Longitude);
		CString Longitude_2,Latitude_2;
		Longitude_2.Format(_T("%.2f"), Longitude_float);
		Latitude_2.Format(_T("%.2f"), Latitude_float);
		float Longitude_2_f, Latitude_2_f;
		Longitude_2_f = _wtof(Longitude_2);
		Latitude_2_f = _wtof(Latitude_2);


		
		//传递到结构体数组
		info[i].StationName = StationName;
		info[i].Address = Address;
		info[i].Status = Status;
		info[i].Location1 = Location1;
		info[i].Location2 = Location2;
		info[i].StationID = StationID_int;
		info[i].StationID_cst = StationID;
		info[i].DocksinService = DockesinSerive_int;
		info[i].DocksinService_cst = DocksinService;
		info[i].TotalDocks = TotalDocks_int;
		info[i].TotalDocks_cst = TotalDocks;
		info[i].Latitude = Latitude_float;
		info[i].Latitude_cst = Latitude;
		info[i].Longitude_cst = Longitude;
		info[i].Longitude = Longitude_float;
		info[i].Latitude_2 = Latitude_2_f;
		info[i].Longitude_2 = Longitude_2_f;
		info[i].Longitude_cst_2 = Longitude_2;
		info[i].Latitude_cst_2 = Latitude_2;
		
	}
	for (int i = 0; i < vecLength; i++)
	{
		m_combox_station1.AddString(info[i].StationName);
		m_combox_station2.AddString(info[i].StationName);

	}

	int j;
	user_info = new splitedinfo[7];
	for (  j = 0; j < 7; j++)
	{
		user_info[j] = info[1 + rand() % 589];
	}
	m_combox_track_users.AddString(_T("张三"));
	m_combox_track_users.AddString(_T("钟云峰大大佬"));
	m_combox_track_users.AddString(_T("奥力给"));
	m_combox_track_users.AddString(_T("辣笔小新"));
	m_combox_track_users.AddString(_T("大马猴"));
	m_combox_track_users.AddString(_T("我喜欢……"));
	m_combox_track_users.AddString(_T("陈金亮是渣男"));

	m_combox_track_users2.AddString(_T("张三"));
	m_combox_track_users2.AddString(_T("钟云峰大大佬"));
	m_combox_track_users2.AddString(_T("奥力给"));
	m_combox_track_users2.AddString(_T("辣笔小新"));
	m_combox_track_users2.AddString(_T("大马猴"));
	m_combox_track_users2.AddString(_T("我喜欢……"));
	m_combox_track_users2.AddString(_T("陈金亮是渣男"));


	
}


//CString切分函数
vector<CString> SplitCString(CString strSource, CString ch)
{

	vector <CString> vecString;

	int iPos = 0;

	CString strTmp;

	strTmp = strSource.Tokenize(ch, iPos);

	while (strTmp.Trim() != _T(""))

	{

		vecString.push_back(strTmp);

		strTmp = strSource.Tokenize(ch, iPos);

	}
	return vecString;
}



//切分函数!!!!!!!!
CStringArray* DivString(CString test)
{
	CStringArray* m_result = new CStringArray;
	while (TRUE)
	{
		int index = test.Find(_T(","));
		if (index == -1)
		{
			m_result->Add(test);
			return m_result;
		}
		CString test1 = test.Left(index);
		m_result->Add(test1);
		test = test.Right(test.GetLength() - index - 1);
	}
}


//绘制获取站点分布的按钮
void CCS20180080331Dlg::OnBnClickedButtonstationlocation()
{
	if (input_data == 0)
	{
		MessageBox(_T("请先导入数据鸭(｡•́︿•̀｡)"), _T("出错了大兄嘚"), MB_OK | MB_ICONWARNING);
	}//提示用户导入数据
	
	else
	{
		if (if_print == 0)
		{
			ClearWindow();
			//清除画图的痕迹
		}
		

		CDC* pdc;
		pdc = m_draw_map.GetDC();
		CPen new_pen;
		new_pen.CreatePen(1, 8, RGB(128, 0, 128));
		pdc->SelectObject(&new_pen);
		int i = 0;
		for (i = 1; i < VecLength; i++)
		{
			int x = ((87.8 + info[i].Longitude) * 1460.0), y = ((42.1 - info[i].Latitude) * 1960.0);
			int _x = ((87.8 + info[i].Longitude) * 1460.0 + 1.0), _y = ((42.1 - info[i].Latitude) * 1960.0 + 1.0);
			pdc->MoveTo(x, y);
			pdc->LineTo(x, y);
			//pdc->TextOutW(x + 5, y, info[i].StationName);
			//pdc->Rectangle(x - 1, y - 1, x + 1, y + 1);
		}
		ReleaseDC(pdc);
		print_station = 1;
	}
}









void CCS20180080331Dlg::OnBnClickedButtonsearchbyid()
{
	if (input_data == 0)
	{
		MessageBox(_T("请先导入数据鸭(｡•́︿•̀｡)"), _T("出错了大兄嘚"), MB_OK | MB_ICONWARNING);
	} // 提示用户导入数据

	else
	{
		//清除画图的痕迹
		if (if_print == 0) {
			ClearWindow();
		}
		m_combox_track_users.SetCurSel(-1);
		m_combox_track_users2.SetCurSel(-1);
		// 通过id查询站点列出信息并在地图上显示

		int i = 0;
		UpdateData();
		while (i < VecLength)
		{

			if (info[i].StationID == m_edit_id_input)
			{
				SetDlgItemText(IDC_EDIT_Address, info[i].Address);
				SetDlgItemText(IDC_EDIT_stationID, info[i].StationID_cst);
				SetDlgItemText(IDC_EDIT_stationNAME, info[i].StationName);
				SetDlgItemText(IDC_EDIT_totalDocks, info[i].TotalDocks_cst);
				SetDlgItemText(IDC_EDIT_inservice, info[i].DocksinService_cst);
				SetDlgItemText(IDC_EDIT_status, info[i].Status);
				SetDlgItemText(IDC_EDIT_lattitude, info[i].Latitude_cst);
				SetDlgItemText(IDC_EDIT_longitude, info[i].Longitude_cst);//输出
				m_combobox_display.SetCurSel(-1); //清空组合框编辑框

					//在地图上画出该点
				CDC* pDC;
				pDC = m_draw_map.GetDC();
				CPen pen;
				pen.CreatePen(1, 8, RGB(0, 0, 255));
				pDC->SelectObject(&pen);
				int x = ((87.8 - (-info[i].Longitude)) * 1460.0), y = ((42.1 - info[i].Latitude) * 1960.0);
				int _x = ((87.8 - (-info[i].Longitude)) * 1460.0), _y = ((42.1 - info[i].Latitude) * 1960.0);
				pDC->MoveTo(x, y); //划线开始
				pDC->LineTo(_x, _y);
				pDC->TextOutW(x + 5, y, info[i].StationName);
				//pDC->Rectangle(x+10, y, x+30, y+15);
				ReleaseDC(pDC);

				break;
			}
			i++;
			if (i == VecLength)
			{
				MessageBox(_T("大兄嘚数据库中没有此站点ID的信息!"), _T("找不到ID！"), MB_OK | MB_ICONERROR); //查找失败
				SetDlgItemText(IDC_EDIT_ID, _T("0"));//清空编辑框让用户重新输入
			}

		}
	}

}



UINT __cdecl track_user(LPVOID lpParam)//多开一个线程画图
{
	CCS20180080331Dlg* pThisDlg = (CCS20180080331Dlg*)lpParam;//强制转换
	int differ_x = End_x - Start_x;
	int differ_y = End_y - Start_y;
	int ave_x = differ_x / 33, ave_y = differ_y / 33;//每次移动的平均值
	CPen new_pen;
	new_pen.CreatePen(1, 3, RGB(255, 0, 0));
	CDC* new_pDc;
	new_pDc = pThisDlg->m_draw_map.GetDC();
	new_pDc->SelectObject(&new_pen);//重新选择路径的线条
	new_pDc->MoveTo(Start_x + 3, Start_y + 3);
	while (Start_x < End_x - 5 && Start_y < End_y - 5)
	{
		new_pDc->LineTo((Start_x)+rand() % (ave_x + 1), (Start_y)+rand() % (ave_y + 1));
		Start_x += ave_x;
		Start_y += ave_y;
		Sleep(250);
	}
	new_pDc->LineTo(End_x - 6, End_y - 6);
	if_print = 0;
	return 0;
}


void CCS20180080331Dlg::OnBnClickedButtontrackuser()
{
	
	if (input_data == 0)
	{
		MessageBox(_T("请先导入数据鸭(｡•́︿•̀｡)"), _T("出错了大兄嘚"), MB_OK | MB_ICONWARNING);
	}
	else if(if_print != 1) //防止用户不停开启线程卡死
	{
		if (m_combox_track_users.GetCurSel() == -1)
		{
			MessageBox(_T("请先选择一个客户呀(｡•́︿•̀｡)"), _T("出错了大兄嘚"), MB_OK | MB_ICONWARNING);
		}

		// 提示用户导入数据
		else
		{
			if_print = 1;
			AfxBeginThread(track_user, this);
		}
	}
}


	

void CCS20180080331Dlg::OnBnClickedButton3()
{
	// 点击此按钮随机确定一个用户的名字
	int random_located = 1 + rand() % 588; /*m_combox_track_users2.GetCurSel()+1;*/
	if (input_data == 0)
	{
		MessageBox(_T("请先导入数据鸭(｡•́︿•̀｡)"), _T("出错了大兄嘚"), MB_OK | MB_ICONWARNING);
	}
	else if (m_combox_track_users2.GetCurSel() == CB_ERR)
	{
		AfxMessageBox(_T("请先选择一个用户"));
	}
	// 提示用户导入数据
	else 
	{
		m_combox_track_users.SetCurSel(-1);
		m_combobox_display.SetCurSel(-1); //清空组合框编辑框
		//清空显示信息得编辑框
		clear_edite_contral();
		if (if_print != 1)
		{
			ClearWindow();
		}//如果在花轨迹  则不清空
		
		CDC* pDC;
		pDC = m_draw_map.GetDC();
		CPen pen;
		pen.CreatePen(1, 10, RGB(255,0,0));
		pDC->SelectObject(&pen);//创建画笔
		int x = ((87.8 - (-info[random_located].Longitude)) * 1460.0);
		int y = ((42.1 - info[random_located].Latitude) * 1960.0);
		pDC->MoveTo(x, y);
		pDC->LineTo(x, y);
		pDC->TextOutW(x + 6, y, _T("我在这呢!"));

		//显示当前所在的站点信息
		SetDlgItemText(IDC_EDIT_Address, info[random_located].Address);
		SetDlgItemText(IDC_EDIT_stationID, info[random_located].StationID_cst);
		SetDlgItemText(IDC_EDIT_stationNAME, info[random_located].StationName);
		SetDlgItemText(IDC_EDIT_totalDocks, info[random_located].TotalDocks_cst);
		SetDlgItemText(IDC_EDIT_inservice, info[random_located].DocksinService_cst);
		SetDlgItemText(IDC_EDIT_status, info[random_located].Status);
		SetDlgItemText(IDC_EDIT_lattitude, info[random_located].Latitude_cst);
		SetDlgItemText(IDC_EDIT_longitude, info[random_located].Longitude_cst);
		ReleaseDC(pDC);
	}
}








void CCS20180080331Dlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_combox_station1.GetCurSel() == m_combox_station2.GetCurSel())
	{
		AfxMessageBox(_T("请选择两个不同的站点呀"));
	}
	else if (m_combox_station1.GetCurSel()==-1|| m_combox_station2.GetCurSel()==-1||(m_combox_station1.GetCurSel()==-1&& m_combox_station2.GetCurSel()==-1))
	{
		AfxMessageBox(_T("您还没有选择两个站点呀"));

	}
	if(input_data == 0)
	{
		AfxMessageBox(_T("请先导入数据鸭(｡•́︿•̀｡)"));
	}
	else
	{
		double radLat1 = info[m_combox_station1.GetCurSel()].Latitude * 3.141592654 / 180.0;   //角度1˚ = π / 180
		double radLat2 = info[m_combox_station2.GetCurSel()].Latitude * 3.141592654 / 180.0;   //角度1˚ = π / 180
		double a = radLat1 - radLat2;//纬度之差
		double b = info[m_combox_station1.GetCurSel()].Longitude * 3.141592654 / 180.0 - info[m_combox_station2.GetCurSel()].Longitude * 3.141592654 / 180.0;  //经度之差
		double dst = 2 * asin((sqrt(pow(sin(a / 2), 2) + cos(radLat1) * cos(radLat2) * pow(sin(b / 2), 2))));
		dst = dst * 6378.137;
		dst = round(dst * 10000) / 10000;
		CString str;
		str.Format(_T("%f"), dst);
		SetDlgItemText(IDC_EDIT5, str);
		
	}
}


void CCS20180080331Dlg::OnBnClickedButtontrackusers()
{
	// TODO: 在此添加控件通知处理程序代码

	if (input_data == 0)
	{
		MessageBox(_T("请先导入数据鸭(｡•́︿•̀｡)"), _T("出错了大兄嘚"), MB_OK | MB_ICONWARNING);
	}
	else if (if_print != 1) //防止用户不停开启线程卡死
	{
		if (m_combox_track_users.GetCurSel() == -1)
		{
			MessageBox(_T("请先选择一个客户呀(｡•́︿•̀｡)"), _T("出错了大兄嘚"), MB_OK | MB_ICONWARNING);
		}

		// 提示用户导入数据
		else
		{
			if_print = 1;
			AfxBeginThread(track_user, this);
		}
	}
}




void CCS20180080331Dlg::OnCbnSelchangeCombo1()
{
		// 选择一个用户之后就在地图上描绘七点和终点
	if (input_data == 0)
	{
		MessageBox(_T("请先导入数据鸭(｡•́︿•̀｡)"), _T("出错了大兄嘚"), MB_OK | MB_ICONWARNING);
	}
	// 提示用户导入数据
	else if (if_print == 0)
	{
		//刷新用户区
		ClearWindow();
		//清空显示框
		clear_edite_contral();

		m_combox_track_users2.SetCurSel(-1);
		m_combobox_display.SetCurSel(-1); //清空组合框编辑框
		int nSel = m_combox_track_users.GetCurSel();
		//srand((unsigned)time(NULL));//设置时间种子
		int start_x = rand() % 190, end_x = 190 + rand() % (360 - 190 + 1);
		int start_y =40+ rand() % (210-40+1), end_y = 636 + rand() % (784 - 636 + 1);//随机生成起点和终点
		Start_x = start_x;
		Start_y = start_y;
		End_x = end_x;
		End_y = end_y;

		CDC* pDC;
		pDC = m_draw_map.GetDC();
		CPen pen;
		pen.CreatePen(1, 6, RGB(0, 0, 255));
		pDC->SelectObject(&pen);//创建画笔


		int differ_x = end_x - start_x;
		int differ_y = end_y - start_y;//起点和终点x和y坐标的差值

		pDC->MoveTo(start_x, start_y);
		pDC->Rectangle(start_x - 3, start_y - 3, start_x + 3, start_y + 3);
		pDC->TextOutW(start_x + 6, start_y, _T("出发地"));//描绘起点
		Sleep(200);
		pDC->MoveTo(end_x, end_y);
		pDC->Rectangle(end_x - 3, end_y - 3, end_x + 3, end_y + 3);
		pDC->TextOutW(end_x + 6, end_y , _T("目的地"));//描绘终点
		ReleaseDC(pDC);
	}
	else
	{
		m_combox_track_users2.SetCurSel(-1);
		m_combox_track_users.SetCurSel(-1);

	}
}


void CCS20180080331Dlg::OnCbnSelchangeCombo2()
{
	// 选择一个用户，清空其他下拉框
	m_combobox_display.SetCurSel(-1);
	m_combox_track_users.SetCurSel(-1);
	clear_edite_contral();
	//清空显示信息得编辑框
}


void CCS20180080331Dlg::OnBnClickedButton2()
{
	// 点击这个按钮查询有损坏车桩的站点
	if (input_data == 0)
	{
		MessageBox(_T("请先导入数据鸭(｡•́︿•̀｡)"), _T("出错了大兄嘚"), MB_OK | MB_ICONWARNING);
	} // 提示用户导入数据

	else 
	{
		//清除画图的痕迹
		if (if_print == 0)
		{
			ClearWindow();
		}
		m_combox_track_users.SetCurSel(-1);
		m_combox_track_users2.SetCurSel(-1);
		// 通过id查询站点列出信息并在地图上显示

		int i = 0;
		UpdateData();
		while (i < VecLength)
		{

			if (info[i].TotalDocks != info[i].DocksinService)
			{
				m_combobox_display.SetCurSel(-1); //清空组合框编辑框
				m_combox_track_users.SetCurSel(-1);
				m_combox_track_users2.SetCurSel(-1);
				//在地图上画出该点
				CDC* pDC;
				pDC = m_draw_map.GetDC();
				CPen pen;
				pen.CreatePen(1, 8, RGB(255, 0, 0));
				pDC->SelectObject(&pen);
				int x = ((87.8 - (-info[i].Longitude)) * 1460.0), y = ((42.1 - info[i].Latitude) * 1960.0);
				int _x = ((87.8 - (-info[i].Longitude)) * 1460.0), _y = ((42.1 - info[i].Latitude) * 1960.0);
				pDC->MoveTo(x, y);
				pDC->LineTo(x, y);
				pDC->TextOutW(x + 4, y - 8, _T("!!", (info[i].TotalDocks - info[i].DocksinService)));
				ReleaseDC(pDC);
			}
			i++;
		}
		MessageBox(_T("叹号所示站点存在损坏车桩，需要维修(｡•́︿•̀｡)"), _T("查询完毕"), MB_OK | MB_ICONWARNING);
		print_repair = 1;
	}
}


void CCS20180080331Dlg::OnCbnSelchangeCombo1display()
{
	// 查站带你信息，并在地图上显示
	if (input_data == 0)
	{
		MessageBox(_T("请先导入数据鸭(｡•́︿•̀｡)"), _T("出错了大兄嘚"), MB_OK | MB_ICONWARNING);
	}
	else
	{
		if (if_print == 0)
		{
			ClearWindow();
			//清除画图的痕迹
		}

		m_combox_track_users2.SetCurSel(-1);
		m_combox_track_users.SetCurSel(-1);

		int nSel = m_combobox_display.GetCurSel(); //获取索引索引
		SetDlgItemText(IDC_EDIT_Address, info[nSel].Address);
		SetDlgItemText(IDC_EDIT_stationID, info[nSel].StationID_cst);
		SetDlgItemText(IDC_EDIT_stationNAME, info[nSel].StationName);
		SetDlgItemText(IDC_EDIT_totalDocks, info[nSel].TotalDocks_cst);
		SetDlgItemText(IDC_EDIT_inservice, info[nSel].DocksinService_cst);
		SetDlgItemText(IDC_EDIT_status, info[nSel].Status);
		SetDlgItemText(IDC_EDIT_lattitude, info[nSel].Latitude_cst);
		SetDlgItemText(IDC_EDIT_longitude, info[nSel].Longitude_cst);//在编辑框输出信息

		SetDlgItemText(IDC_EDIT_ID, _T("0"));//清空ID编辑框
		CDC* pDC;
		pDC = m_draw_map.GetDC();
		CPen pen;
		pen.CreatePen(1, 8, RGB(255, 0, 0));
		pDC->SelectObject(&pen);
		int x = ((87.8 - (-info[nSel].Longitude)) * 1460.0), y = ((42.1 - info[nSel].Latitude) * 1960.0);
		int _x = ((87.8 - (-info[nSel].Longitude)) * 1460.0), _y = ((42.1 - info[nSel].Latitude) * 1960.0);
		pDC->MoveTo(x, y); 
		pDC->LineTo(_x, _y);//画一个点

		pDC->TextOutW(x + 5, y, info[nSel].StationName);//显示信息
		//pDC->Rectangle(x+10, y, x+30, y+15);
		ReleaseDC(pDC);
	}
}

CString test3, test4;//重写鼠标移动函数，实现地图经纬度和站点显示
void CCS20180080331Dlg::OnMouseMove(UINT nFlags, CPoint point)
{
		GetCursorPos(&point);
		if (input_data == 1)
		{
			CRect map_ctr;
			(this->GetDlgItem(IDC_STATIC_draw_map))->GetWindowRect(&map_ctr);  //获得地图相对屏幕左上角的坐标，/存储到rect_ctr中
			int i = 0;
			int x1 = point.x - map_ctr.left, y1 = point.y - map_ctr.top;//鼠标在地图中的位置
			float n_latitude = (42.1 - y1 / 1960.0);
			float n_longitude = x1 / 1460.0 - 87.8;

			test3.Format(_T("%f"), n_latitude);
			test4.Format(_T("%f"), n_longitude);
			SetDlgItemText(IDC_EDIT3, _T(""));
			SetDlgItemText(IDC_EDIT2, _T(""));
			if (x1 > 0 && x1 < 438 && y1>=0 && y1 < 784)
			{
				SetDlgItemText(IDC_EDIT3, test3);
				SetDlgItemText(IDC_EDIT2, test4);
				for (i = 1; i < VecLength; i++)
				{
					int x = ((87.8 + info[i].Longitude) * 1460.0), y = ((42.1 - info[i].Latitude) * 1960.0);
					int x2 = abs(x - x1), y2 = abs(y - y1);
					if (x2 <= 3 && y2 <= 3)
					{
						SetDlgItemText(IDC_EDIT4, info[i].StationName);
						break;
					}
					else
					{
						SetDlgItemText(IDC_EDIT4, _T(""));
					}
				}

			}
		}
	CDialogEx::OnMouseMove(nFlags, point);
}





void CCS20180080331Dlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	system("start explorer https://github.com/Bo520/Bo_Public_bicycle_management.git");
}


void CCS20180080331Dlg::OnEnChangeEdit4()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	 //TODO:  在此添加控件通知处理程序代码
	//if (py == 1)
	//{
	//	UpdateData();
	//	CString temp;
	//	temp.Format(m_edit_name);
	//	if (temp == _T(""))
	//	{
	//		for (int i = 1; i < VecLength; i++)
	//		{
	//				CDC* dc;
	//				dc = m_draw_map.GetDC();
	//				CPen pen;
	//				pen.CreatePen(1, 6, RGB(128, 0, 128));
	//				dc->SelectObject(&pen);
	//				int x = ((87.8 + info[i].Longitude) * 1460.0), y = ((42.1 - info[i].Latitude) * 1960.0);
	//				dc->MoveTo(x, y);
	//				dc->LineTo(x, y);
	//				ReleaseDC(dc);
	//			
	//		}
	//	}
	//}
}


void CCS20180080331Dlg::OnEnChangeEdit2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CCS20180080331Dlg::OnEnChangeEditId()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CCS20180080331Dlg::OnCbnSelchangeCombo3()
{
	// TODO: 在此添加控件通知处理程序代码
}



void CCS20180080331Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// 鼠标点击站点将站点描红
	GetCursorPos(&point);
	CRect map_ctr1;
	(this->GetDlgItem(IDC_STATIC_draw_map))->GetWindowRect(&map_ctr1);   //获得地图相对屏幕左上角的坐标，/存储到rect_ctr中
	int i = 0;
	if (input_data == 1)
	{

		if (print_station == 1)
		{
			CDC* p;
			p = m_draw_map.GetDC();
			CPen pen;
			pen.CreatePen(1, 8, RGB(255, 0, 0));
			p->SelectObject(&pen);

			for (i = 1; i < VecLength; i++)
			{
				int x = ((87.8 + info[i].Longitude) * 1460.0), y = ((42.1 - info[i].Latitude) * 1960.0);
				int x1 = point.x - map_ctr1.left, y1 = point.y - map_ctr1.top;
				int x2 = abs(x - x1), y2 = abs(y - y1);
				if (x2 <= 4 && y2 <= 4)
				{
					p->MoveTo(x, y);
					p->LineTo(x, y);
					ReleaseDC(p);
					break;
				}

			}

		}
		else if (print_repair == 1||(print_repair==0&&print_station==0))
		{
			CDC* p;
			p = m_draw_map.GetDC();
			CPen pen;
			pen.CreatePen(1, 8, RGB(0, 0, 255));
			p->SelectObject(&pen);

			for (i = 1; i < VecLength; i++)
			{
				int x = ((87.8 + info[i].Longitude) * 1460.0), y = ((42.1 - info[i].Latitude) * 1960.0);
				int x1 = point.x - map_ctr1.left, y1 = point.y - map_ctr1.top;
				int x2 = abs(x - x1), y2 = abs(y - y1);
				if (x2 <= 4 && y2 <= 4)
				{
					p->MoveTo(x, y);
					p->LineTo(x, y);
					ReleaseDC(p);
					break;
				}

			}

		}

	}
	



	CDialogEx::OnLButtonDown(nFlags, point);
}


void CCS20180080331Dlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	GetCursorPos(&point);
	CRect map_ctr2;
	(this->GetDlgItem(IDC_STATIC_draw_map))->GetWindowRect(&map_ctr2);   //获得地图相对屏幕左上角的坐标，/存储到rect_ctr中
	int i = 0;
	if (input_data == 1)
	{
		if (print_station == 1)
		{
			CDC* p;
			p = m_draw_map.GetDC();
			CPen pen;
			pen.CreatePen(1, 8, RGB(128, 0, 128));
			p->SelectObject(&pen);

			for (i = 1; i < VecLength; i++)
			{
				int x = ((87.8 + info[i].Longitude) * 1460.0), y = ((42.1 - info[i].Latitude) * 1960.0);
				int x1 = point.x - map_ctr2.left, y1 = point.y - map_ctr2.top;
				int x2 = abs(x - x1), y2 = abs(y - y1);
				if (x2 <= 4 && y2 <= 4)
				{
					p->MoveTo(x, y);
					p->LineTo(x, y);
					ReleaseDC(p);
					break;
				}

			}

		}
		else if (print_repair == 1 || (print_repair == 0 && print_station == 0))
		{
			CDC* p;
			p = m_draw_map.GetDC();
			CPen pen;
			pen.CreatePen(1, 8, RGB(255, 0, 0));
			p->SelectObject(&pen);

			for (i = 1; i < VecLength; i++)
			{
				int x = ((87.8 + info[i].Longitude) * 1460.0), y = ((42.1 - info[i].Latitude) * 1960.0);
				int x1 = point.x - map_ctr2.left, y1 = point.y - map_ctr2.top;
				int x2 = abs(x - x1), y2 = abs(y - y1);
				if (x2 <= 4 && y2 <= 4)
				{
					p->MoveTo(x, y);
					p->LineTo(x, y);
					ReleaseDC(p);
					break;
				}

			}
			CDialogEx::OnLButtonUp(nFlags, point);
		}
	}
}


void CCS20180080331Dlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	if (if_print == 0)
	{
		ClearWindow();
	}
}
