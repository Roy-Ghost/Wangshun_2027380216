
// EfficientNetDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "EfficientNet.h"
#include "EfficientNetDlg.h"
#include "afxdialogex.h"
#include "CSettingDlg.h"
#include <string>
#include "DoWork.h"

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


// CEfficientNetDlg 对话框



CEfficientNetDlg::CEfficientNetDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_EFFICIENTNET_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEfficientNetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CEfficientNetDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CEfficientNetDlg::OnBnClickedButtonOpen)
	ON_BN_CLICKED(IDC_BUTTON2, &CEfficientNetDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTONPre, &CEfficientNetDlg::OnBnClickedButtonpre)
END_MESSAGE_MAP()


// CEfficientNetDlg 消息处理程序

BOOL CEfficientNetDlg::OnInitDialog()
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

void CEfficientNetDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CEfficientNetDlg::OnPaint()
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
HCURSOR CEfficientNetDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CEfficientNetDlg::OnBnClickedButtonOpen()
{
	// TODO: 在此添加控件通知处理程序代码

	TCHAR szBuffer[MAX_PATH] = { 0 };
	BROWSEINFO bi;
	ZeroMemory(&bi, sizeof(BROWSEINFO));
	bi.hwndOwner = NULL;
	bi.pszDisplayName = szBuffer;
	bi.lpszTitle = _T("从下面选文件夹目录:");
	bi.ulFlags = BIF_RETURNFSANCESTORS; //BIF_BROWSEINCLUDEFILES
	LPITEMIDLIST idl = SHBrowseForFolder(&bi);
	if (NULL == idl)
	{
		return;
	}
	SHGetPathFromIDList(idl, szBuffer);
	if (szBuffer)
	{
		std::wstring strFilePath = szBuffer;

		//文本框写入
		CEdit* pEditSourceFileDir = (CEdit*)GetDlgItem(IDC_EDIT_FILE_DIR);
		if (pEditSourceFileDir)
		{
			pEditSourceFileDir->SetWindowText(szBuffer);
		}
	}


	//文本框读取
	CString  strSourceDir;
	CEdit* pEditSourceDir = (CEdit*)GetDlgItem(IDC_EDIT_FILE_DIR);
	if (pEditSourceDir)
	{
		pEditSourceDir->GetWindowText(strSourceDir);
	}
}



void CEfficientNetDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// 检测鼠标左键按下,point为鼠标位置
	SetDlgItemText(IDC_EDIT_FILE_DIR, L"检测鼠标左键按下");
}

void CEfficientNetDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	// 检测鼠标右键按下
	SetDlgItemText(IDC_EDIT_FILE_DIR, L"检测鼠标右键按下");
}



void CEfficientNetDlg::OnBnClickedButtonpre()
{
	// TODO: 在此添加控件通知处理程序代码
}
