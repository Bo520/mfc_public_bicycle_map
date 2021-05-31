// ConfirmQuitDlg.cpp: 实现文件
//

#include "pch.h"
#include "CS20180080331.h"
#include "ConfirmQuitDlg.h"
#include "afxdialogex.h"


// ConfirmQuitDlg 对话框

IMPLEMENT_DYNAMIC(ConfirmQuitDlg, CDialogEx)

ConfirmQuitDlg::ConfirmQuitDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ConfirmQuit, pParent)
{

}

ConfirmQuitDlg::~ConfirmQuitDlg()
{
}

void ConfirmQuitDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ConfirmQuitDlg, CDialogEx)
END_MESSAGE_MAP()


// ConfirmQuitDlg 消息处理程序
