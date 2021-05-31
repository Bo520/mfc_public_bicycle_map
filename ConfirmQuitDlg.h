#pragma once


// ConfirmQuitDlg 对话框

class ConfirmQuitDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ConfirmQuitDlg)

public:
	ConfirmQuitDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~ConfirmQuitDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ConfirmQuit };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
