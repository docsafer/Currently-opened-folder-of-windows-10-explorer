#pragma once
class CWin10ExplorerCurrentFolders
{
public:
	CWin10ExplorerCurrentFolders();
	~CWin10ExplorerCurrentFolders();
	static DWORD Get(vector<CString> &aryPaths);
private:
	static BOOL RefreshShellView(HWND hWnd, LPARAM lParam);
	static CString CheckShellSpecialFolder(CString strPath);
private:
	static TCHAR m_szWin10Class[][32];
};

