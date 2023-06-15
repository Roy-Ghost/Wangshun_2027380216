
// MobileNetV3Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MobileNetV3.h"
#include "MobileNetV3Dlg.h"
#include "afxdialogex.h"
#include <json/json.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

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


// CMobileNetV3Dlg 对话框



CMobileNetV3Dlg::CMobileNetV3Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MOBILENETV3_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMobileNetV3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMobileNetV3Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMobileNetV3Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDCANCEL, &CMobileNetV3Dlg::OnBnClickedCancel)
	ON_EN_CHANGE(IDC_EDIT_FILE_DIR, &CMobileNetV3Dlg::OnEnChangeEditFileDir)
	ON_BN_CLICKED(IDC_BUTTON2, &CMobileNetV3Dlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CMobileNetV3Dlg 消息处理程序

BOOL CMobileNetV3Dlg::OnInitDialog()
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

	ShowWindow(SW_MINIMIZE);

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMobileNetV3Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMobileNetV3Dlg::OnPaint()
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
HCURSOR CMobileNetV3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}






void CMobileNetV3Dlg::OnBnClickedButton1()
{

	CString strFilter = _T("Picture Files (*.bmp;*.jpg;*.jpeg;*.png)|*.bmp;*.jpg;*.jpeg;*.png|All Files (*.*)|*.*||");
	CFileDialog dlg(TRUE, _T("jpg"), NULL, OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST, strFilter, this);

	if (dlg.DoModal() == IDOK)
	{
	/*	CString filePath = dlg.GetPathName();

		// 将选择的图片显示在图片控件中
		CStatic* pImageCtrl = (CStatic*)GetDlgItem(IDC_STATIC_IMAGE);
		CRect rect;
		pImageCtrl->GetClientRect(&rect);

		// 加载图片
		CImage image;
		image.Load(filePath);

		// 创建临时DC
		CDC dc;
		dc.CreateCompatibleDC(NULL);
		dc.SelectObject(image);

		// 创建与控件大小相同的位图
		CBitmap jpg;
		jpg.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());

		// 在位图上进行绘制，以调整图像大小
		CDC memDC;
		memDC.CreateCompatibleDC(NULL);
		memDC.SelectObject(&jpg);
		memDC.StretchBlt(0, 0, rect.Width(), rect.Height(), &dc, 0, 0, image.GetWidth(), image.GetHeight(), SRCCOPY);

		// 在图片控件中显示位图
		pImageCtrl->SetBitmap(jpg);  */
		CString strFileName = dlg.GetPathName();

		CImage image;
		HRESULT hr = image.Load(strFileName);
		if (SUCCEEDED(hr))
		{
			CStatic* pImageCtrl = (CStatic*)GetDlgItem(IDC_STATIC_IMAGE);
			if (pImageCtrl != nullptr)
			{
				CRect rect;
				pImageCtrl->GetClientRect(&rect);
				image.Draw(pImageCtrl->GetDC()->m_hDC, rect);
				pImageCtrl->ReleaseDC(pImageCtrl->GetDC());
				GetDlgItem(IDC_EDIT_FILE_DIR)->SetWindowText(strFileName);
			}
		}
		//文件选择对话框
		CString strFilePath = dlg.GetPathName();
		//文本框写入
		CEdit* pEditSourceFileDir = (CEdit*)GetDlgItem(IDC_EDIT_FILE_DIR);
			if (pEditSourceFileDir)
			{
				pEditSourceFileDir->SetWindowText(strFilePath);
			}
	

		//文本框读取
		CString  strSourceDir;
		CEdit* pEditSourceDir = (CEdit*)GetDlgItem(IDC_EDIT_FILE_DIR);
		if (pEditSourceDir)
		{
		pEditSourceDir->GetWindowText(strSourceDir);
		}
	}
}


void CMobileNetV3Dlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void CMobileNetV3Dlg::OnEnChangeEditFileDir()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CMobileNetV3Dlg::OnBnClickedButton2()
{
	CSocket clientSocket;
	if (clientSocket.Create() && clientSocket.Connect(_T("127.0.0.1"), 35000))
	{
		// 构造 JSON 对象
		rapidjson::Document doc;
		doc.SetObject();
		rapidjson::Value params(rapidjson::kObjectType);
		params.AddMember("name", "John", doc.GetAllocator());
		params.AddMember("age", 30, doc.GetAllocator());
		doc.AddMember("type", "person", doc.GetAllocator());
		doc.AddMember("params", params, doc.GetAllocator());

		// 转换为 JSON 字符串
		rapidjson::StringBuffer buffer;
		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
		doc.Accept(writer);
		CStringA jsonString(buffer.GetString());

		// 发送 JSON 字符串
		clientSocket.Send(jsonString, jsonString.GetLength());

		// 接收响应
		char buffer[1024] = { 0 };
		int len = clientSocket.Receive(buffer, sizeof(buffer) - 1);

		// 解析 JSON 字符串
		rapidjson::Document response;
		response.Parse(buffer);
		CStringA name = response["name"].GetString();
		int age = response["age"].GetInt();

		// 显示响应
		CStringA message;
		message.Format("Name: %s, Age: %d", name, age);
		SetDlgItemTextA(IDC_STATIC_TEXT, (LPCTSTR)message);
	}
	else
	{
		SetDlgItemText(IDC_STATIC_TEXT, _T("连接服务器失败！"));
	}
}
