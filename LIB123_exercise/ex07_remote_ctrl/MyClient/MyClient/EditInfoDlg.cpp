// EditInfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MyClient.h"
#include "EditInfoDlg.h"
#include "afxdialogex.h"


// EditInfoDlg dialog

IMPLEMENT_DYNAMIC(EditInfoDlg, CDialog)

EditInfoDlg::EditInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(EditInfoDlg::IDD, pParent)
{

}

EditInfoDlg::~EditInfoDlg()
{
}

void EditInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control (pDX, IDC_LIST1, m_list1);
}

BOOL EditInfoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	this->GetDlgItem( IDC_BUTTON1 )->SetWindowText( CString("装载IP地址数据") );
	this->GetDlgItem( IDC_BUTTON2 )->SetWindowText( CString("添加") );
	this->GetDlgItem( IDC_BUTTON3 )->SetWindowText( CString("删除数据") );
	DWORD dwStyle = m_list1.GetExtendedStyle();
	dwStyle |= LVS_EX_GRIDLINES;
	dwStyle |= LVS_EX_FULLROWSELECT;//
	m_list1.SetExtendedStyle(dwStyle); 

	return TRUE;  // return TRUE  unless you set the focus to a control
}


BEGIN_MESSAGE_MAP(EditInfoDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &EditInfoDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &EditInfoDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &EditInfoDlg::OnBnClickedButton3)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, OnNMClickList1)
END_MESSAGE_MAP()


// EditInfoDlg message handlers
	using namespace Temp;


void EditInfoDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	m_list1.DeleteAllItems();
	while ( m_list1.DeleteColumn(0) ) {}

	m_list1.InsertColumn(0, _T("机器的IP") );   
	m_list1.InsertColumn(1, _T("备注说明") );

	CRect rect4;
	m_list1.GetClientRect(rect4);  
	m_list1.SetColumnWidth(0,rect4.Width()/2);
	m_list1.SetColumnWidth(1,rect4.Width()/2);

	std::string strcnn;
	std::string strtbl;
	WCsrAdoTbl ct; 
	WCsrAdoTbl::rowTYPE r;

	strcnn = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=D:\\nurse.mdb;Persist Security Info=False;Jet OLEDB:Database Password=a";
	strtbl = "select * from  t_server ";
	if(!ct.OpenEnv( strcnn ))
	{
		MessageBox( _T("数据库文件不存在。请拷贝到D盘根目录下.") , _T("警告"), MB_OK );
		return;
	}
	ct.OpenTbl( strtbl );
	int j = 0;
	while( ct.FetchRow( r ) )
	{
		m_list1.InsertItem( j, _T("aa") );
		m_list1.SetItemText(j, 0, _bstr_t(r[0].c_str()) );  
		m_list1.SetItemText(j, 1, _bstr_t(r[1].c_str()) );  

	}
}


void EditInfoDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	if(1)
	{
		std::string strcnn;
		std::string strtbl;
		WCsrAdoTbl ct; 
		CString s1,s2;
		this->GetDlgItem( IDC_EDIT1 )->GetWindowText( s1 );
		this->GetDlgItem( IDC_EDIT2 )->GetWindowText( s2 );
		if( s1.IsEmpty() || s2.IsEmpty() )
		{
			MessageBox( _T("内容不能为空") , _T("警告"), MB_OK );
			return;
		}
	
		strcnn = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=D:\\nurse.mdb;Persist Security Info=False;Jet OLEDB:Database Password=a";
		strtbl = "Insert into t_server  " 
				" (  a_addr ,  a_memo )values( " 
				"   '#a_addr#' , '#a_memo#' ) ";
		SStrf::sreplstr( strtbl, "#a_addr#", CStringA(s1) );
		SStrf::sreplstr( strtbl, "#a_memo#", CStringA(s2) );
		ct.OpenEnv( strcnn );
		ct.OpenTbl( strtbl );
	}
	OnBnClickedButton1();
}


void EditInfoDlg::OnBnClickedButton3()
{
	// TODO: Add your control notification handler code here
	if(1)
	{
		std::string strcnn;
		std::string strtbl;
		WCsrAdoTbl ct; 
		CString s1,s2;
		this->GetDlgItem( IDC_EDIT1 )->GetWindowText( s1 );
		this->GetDlgItem( IDC_EDIT2 )->GetWindowText( s2 );
		if( s1.IsEmpty() )
		{
			MessageBox( _T("内容不能为空") , _T("警告"), MB_OK );
			return;
		}
	
		strcnn = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=D:\\nurse.mdb;Persist Security Info=False;Jet OLEDB:Database Password=a";
		strtbl = "delete from    t_server  " 
				" where a_addr =  '#a_addr#' ";
		SStrf::sreplstr( strtbl, "#a_addr#", CStringA(s1) ); 
		ct.OpenEnv( strcnn );
		ct.OpenTbl( strtbl );
	}
	OnBnClickedButton1();
}


void EditInfoDlg::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	//// TODO: Add your control notification handler code here
	CString str;
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	str = m_list1.GetItemText( pNMListView->iItem, 0 );
	this->GetDlgItem( IDC_EDIT1 )->SetWindowText( str );
	static char theipaddress[1024];
	sprintf( theipaddress, "%s", CStringA(str) );
	ipaddress = theipaddress;

	str = m_list1.GetItemText( pNMListView->iItem, 1 );
	this->GetDlgItem( IDC_EDIT2 )->SetWindowText( str );
}
