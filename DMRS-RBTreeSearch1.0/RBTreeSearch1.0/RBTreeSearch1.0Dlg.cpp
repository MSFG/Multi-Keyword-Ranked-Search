// RBTreeSearch1.0Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "RBTreeSearch1.0.h"
#include "RBTreeSearch1.0Dlg.h"

#include "RBTreeSearch.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CRBTreeSearch10Dlg �Ի���




CRBTreeSearch10Dlg::CRBTreeSearch10Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRBTreeSearch10Dlg::IDD, pParent)
	, m_keywords(_T(""))
	/*, m_result_list(_T(""))*/
	//, m_topk_result(_T(""))
	, m_time(_T(""))
	, m_path(_T(""))
	, m_keywordNum(_T(""))
	, m_docNum(_T(""))
	, m_indexTime(_T(""))
	, m_numK(0)
	, m_WSTime(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRBTreeSearch10Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_KEYWORDS, m_keywords);
	//DDX_LBString(pDX, IDC_RESULT_LIST, m_result_list);
	//DDX_Text(pDX, IDC_TOPK_RESULT, m_topk_result);
	DDX_Text(pDX, IDC_TIME, m_time);
	DDX_Control(pDX, IDC_RESULT_LIST, m_ListCtrl);
	DDX_Text(pDX, IDC_FILE_PATH, m_path);
	DDX_Text(pDX, IDC_KEYWORD_NUM, m_keywordNum);
	DDX_Text(pDX, IDC_DOC_NUM, m_docNum);
	DDX_Text(pDX, IDC_INDEX_TIME, m_indexTime);
	DDX_Text(pDX, IDC_NUM_K, m_numK);
	DDX_Text(pDX, IDC_WS_TIME, m_WSTime);
}

BEGIN_MESSAGE_MAP(CRBTreeSearch10Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_TestButton, &CRBTreeSearch10Dlg::OnBnClickedTestbutton)
	ON_BN_CLICKED(IDC_BROWSE, &CRBTreeSearch10Dlg::OnBnClickedBrowse)
END_MESSAGE_MAP()


// CRBTreeSearch10Dlg ��Ϣ�������

BOOL CRBTreeSearch10Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	//��ȡ��ǰ��չ��ʽ
	DWORD dwStyle = m_ListCtrl.GetExtendedStyle();
	//ѡ��ĳ��ʹ���и�����report���
	dwStyle = LVS_EX_FULLROWSELECT;
	//�����ߣ�report���
	dwStyle |= LVS_EX_GRIDLINES;
	//��itemǰ����checkout�ؼ�(��ѡ)
	//       dwStyle |= LVS_EX_CHECKBOXED;
	m_ListCtrl.SetExtendedStyle(dwStyle);
	CRect rect;
	m_ListCtrl.GetWindowRect(&rect);

	int listwidth = rect.Width();

	m_ListCtrl.InsertColumn(0, "NO", LVCFMT_LEFT, listwidth/5, -1);
	m_ListCtrl.InsertColumn(1, "FileName", LVCFMT_LEFT, 2*listwidth/5, -1);
	m_ListCtrl.InsertColumn(2,"Score",LVCFMT_LEFT,2*listwidth/5, -1);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CRBTreeSearch10Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CRBTreeSearch10Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CRBTreeSearch10Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CRBTreeSearch10Dlg::OnBnClickedTestbutton()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	m_keywords.Empty();
	UpdateData(TRUE);
	//m_topk_result.Empty();
	m_ListCtrl.DeleteAllItems();
	
	if (m_keywords=="")
	{
		MessageBox("please input keywords","��ʾ");
		return;
	}
	if (m_numK==0)
	{
		MessageBox("please input number","��ʾ");
		return;
	}
	vector<string> keywords_list;
	//keywords_list.clear();
	CString strsplit=" ";
	CString temp=m_keywords;
	CString strleft;
	while (!temp.IsEmpty())
	{
		int pp=temp.Find(strsplit,0);
		if (pp!=-1)
		{
			strleft=temp.Left(pp);
			string keyword(strleft.GetBuffer());
			strleft.ReleaseBuffer();
			keywords_list.push_back(keyword);
			temp=temp.Right(temp.GetLength()-pp-strsplit.GetLength());
		}
		else if (temp.GetLength()>0)
		{
			string keyword(temp.GetBuffer());
			temp.ReleaseBuffer();
			keywords_list.push_back(keyword);
			temp.Empty();
		}
	}

	if (m_path.IsEmpty())
	{
		AfxMessageBox("Caution: Dataset is empty!",MB_OK,0);
		return;
	}
	
	RBTreeSearch Test_One;
	vector<CString> result_list;
	if (m_path.CompareNoCase(m_path_state)==0)
	{
		Test_One.startSearch(keywords_list,m_time,result_list,m_numK,m_WSTime);
		for (int ti=0;ti<result_list.size();ti+=2)
		{
			CString s;
			s.Format("%d",ti/2+1);
			m_ListCtrl.InsertItem(ti/2,s);
			m_ListCtrl.SetItemText(ti/2,1,result_list[ti]);
			m_ListCtrl.SetItemText(ti/2,2,result_list[ti+1]);		
		}
	}
	else
	{
		if(Test_One.ConstructRBTree(m_path,m_keywordNum,m_docNum,m_indexTime))
		{
			Test_One.startSearch(keywords_list,m_time,result_list,m_numK,m_WSTime);
			for (int ti=0;ti<result_list.size();ti+=2)
			{
				CString s;
				s.Format("%d",ti/2+1);
				m_ListCtrl.InsertItem(ti/2,s);
				m_ListCtrl.SetItemText(ti/2,1,result_list[ti]);
				m_ListCtrl.SetItemText(ti/2,2,result_list[ti+1]);		
			}
		}
		else AfxMessageBox("Caution!",MB_OK,0);
	}
	
	m_path_state=m_path;
	/*m_keywords_state=m_keywords;*/
	UpdateData(FALSE);
}

void CRBTreeSearch10Dlg::OnBnClickedBrowse()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	m_time.Empty();
	m_WSTime.Empty();
	m_indexTime.Empty();	
	m_keywordNum.Empty();
	m_docNum.Empty();
	
	
	m_path ="";
	m_path_state="";
	UpdateData(FALSE);



	//m_numK=0;


	char szTempDir[MAX_PATH];  //-----MAX_PATH==260
	CString szTitle="ѡ����Ҫ�����ļ���";
	BROWSEINFO bi; 
	ZeroMemory(&bi, sizeof(bi));
	bi.hwndOwner = AfxGetMainWnd()->GetSafeHwnd();  //�����ھ��
	bi.pidlRoot = NULL;              //LPITEMIDLIST���ͣ�ָ����ʼ�ĸ�Ŀ¼������Ϊ��
	bi.pszDisplayName = NULL; 
	bi.lpszTitle = szTitle;          //�Ի������
	bi.ulFlags = BIF_RETURNONLYFSDIRS; 
	bi.lpfn = NULL; 

	//CString strFoldName;
	//vector <CString > strFilePaths;

	LPITEMIDLIST pidl = SHBrowseForFolder(&bi); 
	if (!pidl) 
	{ 
		return; 	
	}  
	BOOL bSuccess = SHGetPathFromIDList(pidl,szTempDir);  
	LPMALLOC pMalloc;
	if(SUCCEEDED(SHGetMalloc(&pMalloc)))
	{
		pMalloc->Free(pidl);
		pMalloc->Release();
	}
	if (!bSuccess) 
	{ 
		return;
	}
	else
	{
		m_path = szTempDir;       //��ȡĿ¼·��
	}

	
	UpdateData(FALSE);
}
