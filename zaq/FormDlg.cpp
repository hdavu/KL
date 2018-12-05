

// zaqDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Form.h"
#include "FormDlg.h"
#include "afxdialogex.h"
#include "DetectorImage.h"
#include "TrackingVideo.h"
#pragma region AutoGenarateByMFC

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define FILE_CASCADE "C:\\Users\\Administrator\\Desktop\\trainGUI\\Train\\2banh\\train2banh-13-10-6-(tam-thoi-lay-cai-nay)\\classifier\\cascade.xml"

// CzaqDlg dialog



CFormDlg::CFormDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ZAQ_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFormDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CFormDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_btn_Anh, &CFormDlg::OnBnClickedbtnAnh)
	ON_BN_CLICKED(IDC_btn_thoat, &CFormDlg::OnBnClickedbtnthoat)
	ON_BN_CLICKED(IDC_btn_Show, &CFormDlg::OnBnClickedbtnShow)
	ON_BN_CLICKED(ID_btn_Video, &CFormDlg::OnBnClickedbtnVideo)
	ON_BN_CLICKED(IDC_BUTTON1, &CFormDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_btn_Pause, &CFormDlg::OnBnClickedbtnPause)
END_MESSAGE_MAP()


// CzaqDlg message handlers

BOOL CFormDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CFormDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CFormDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

#pragma endregion


/*
	
*/
void CFormDlg::OnBnClickedbtnAnh()
{
	CString Filter = _T("image files (*.bmp; *.jpg) |*.bmp;*.jpg|All Files(*.*) | *.* || ");
	CFileDialog Load(TRUE, _T("*.jpg"), NULL, OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY, Filter, NULL);
	Load.m_ofn.lpstrTitle = _T("Load Image");

	if (Load.DoModal() == IDOK)
	{
		//get path of image
		string filename;
		CString path; path = Load.GetPathName();
		wstring path2 = (std::wstring)path;
		filename.assign(path2.begin(), path2.end());
		
		//load this image to src
		Mat src = imread(filename, 1);

		//find vehicle 
		DetectorImage *detectorImage = new DetectorImage(src);
		
		//get result and free memory
		Mat dst;
		Mat resultClone;

		detectorImage->GetResult().copyTo(resultClone);
		delete detectorImage;
		
		//show the result
		resize(resultClone, dst, cv::Size(resultClone.cols / 2, resultClone.rows / 2));
		
	
		imshow("Hien thi anh", dst);
		

		moveWindow("Hien thi anh", 150, 100);
		
		imwrite("C:\\Users\\Administrator\\Desktop\\LUU\\img\\xx.jpg", dst);
	}
}




/*
	1.Thoát chương trình
*/
void CFormDlg::OnBnClickedbtnthoat()
{
	CDialogEx::OnCancel();
}


void CFormDlg::OnBnClickedbtnVideo()
{

	CString Filter = _T("video files (*.mp4) |*.mp4|All Files(*.*) | *.* || ");
	CFileDialog Load(TRUE, _T("*.mp4"), NULL, OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY, Filter, NULL);
	Load.m_ofn.lpstrTitle = _T("Load Video");

	if (Load.DoModal() == IDOK)
	{
		//get path of image
		string filename;
		CString path; path = Load.GetPathName();
		wstring path2 = (std::wstring)path;
		filename.assign(path2.begin(), path2.end());

		//load this image to src
		//Mat src = imread(filename, 1);

		//find vehicle 
		//TrackingVideo *trackingVideo = new TrackingVideo(FILE_CASCADE,filename);

		TrackingVideo::GetInstanceStartUp(FILE_CASCADE, filename);

		//get result and free memory
		
		TrackingVideo::GetInstance()->Play();
		TrackingVideo::Destroy();
	}
}

void CFormDlg::OnBnClickedButton1()
{

	TrackingVideo::GetInstance()->SetStatusOfPlay();
	// TODO: Add your control notification handler code here
}


void CFormDlg::OnBnClickedbtnPause()
{

	// TODO: Add your control notification handler code here
}


/*

*/
void CFormDlg::OnBnClickedbtnShow()
{
	TrackingVideo::GetInstance()->SetStatusOfPlay();

}
