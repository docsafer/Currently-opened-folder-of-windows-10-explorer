#include "StdAfx.h"
#include "CWin10ExplorerCurrentFolders.h"
#include <Knownfolders.h>
TCHAR CWin10ExplorerCurrentFolders::m_szWin10Class[][32] = { _T("ToolbarWindow32"),_T("Breadcrumb Parent"),
	_T("msctls_progress32"),
	_T("Address Band Root"),
	_T("ReBarWindow32"),
	_T("WorkerW"),
	_T("CabinetWClass") };

CWin10ExplorerCurrentFolders::CWin10ExplorerCurrentFolders()
{
	 
}


CWin10ExplorerCurrentFolders::~CWin10ExplorerCurrentFolders()
{
}
BOOL CWin10ExplorerCurrentFolders::RefreshShellView(HWND hWnd, LPARAM lParam)
{
	if (hWnd)
	{
		int n = 0;
		TCHAR szText[512] = _T("");
		DWORD dwLen = 512;
		GetClassName(hWnd, szText, 512);
		if ((_tcscmp(szText, m_szWin10Class[6]) == 0))
		{
			HWND hwndFind = hWnd;
			for (int i = 5; i >= 0; i--)
			{
				hwndFind = FindWindowEx(hwndFind, NULL, m_szWin10Class[i], NULL);
				if (hwndFind == NULL)
					break;
			}
			if (hwndFind)
			{ 
				if (GetWindowText(hwndFind, szText, 512) > 0)
				{
					TCHAR*  pAddress = _tcschr(szText, _T(':'));
					if (pAddress)
					{
						vector<CString> *paryDirs = (vector<CString> *)lParam;

						CString s = CString(pAddress + 1);
						s.TrimLeft();
						s.TrimRight();
						paryDirs->push_back(s);
 
					}
				}
 				 
			}

		}

	}
	return(TRUE);
}
CString CWin10ExplorerCurrentFolders::Get(CString strPath)
{
	KNOWNFOLDERID fid = GUID_NULL;

	strPath.TrimLeft();
	strPath.TrimRight();

	if (strPath .Compare(_T("Desktop"))==0 || strPath.Compare(_T("◊¿√Ê")) == 0)
		fid = FOLDERID_Desktop;
	else if (strPath.Compare(_T("Documents")) == 0 || strPath.Compare(_T("Œƒµµ")) == 0)
		fid = FOLDERID_Documents;
	else if (strPath.Compare(_T("Music")) == 0 || strPath.Compare(_T("“Ù¿÷")) == 0)
		fid = FOLDERID_Music;
	else if (strPath.Compare(_T("Pictures")) == 0 || strPath.Compare(_T("Õº∆¨")) == 0)
		fid = FOLDERID_Pictures;
	else if (strPath.Compare(_T("Videos")) == 0 || strPath.Compare(_T(" ”∆µ")) == 0)
		fid = FOLDERID_Videos;
	else if (strPath.Compare(_T("Downloads")) == 0 || strPath.Compare(_T("œ¬‘ÿ")) == 0)
		fid = FOLDERID_Downloads;
	else
		return _T("");//not supported
		
	CString sRet;

	if (fid != GUID_NULL)
	{
		WCHAR *pPath;

		if (SHGetKnownFolderPath(fid, 0, NULL, &pPath) == S_OK)
		{ 
			sRet.Format(_T("%s"),pPath);
 			CoTaskMemFree(pPath);
 		}
	}

	return sRet;
}
DWORD CWin10ExplorerCurrentFolders::GetCurrentOpenedFolders(vector<CString> &aryPaths)
{
	EnumWindows((WNDENUMPROC)RefreshShellView, (LPARAM)&aryPaths);

	CString s;
	for (int i =aryPaths.size()-1;i>=0; i--)
	{
		if (aryPaths[i].Find(_T(":\\")) == -1)
		{
			s = CheckShellSpecialPath(aryPaths[i]);
			if (s.IsEmpty())
				aryPaths.erase(aryPaths.begin() + i);
			else
				aryPaths[i] = s;
 		}
	}

	return aryPaths.size();
}