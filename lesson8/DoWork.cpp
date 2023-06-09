#include "pch.h"
#include "DoWork.h"

HWND	m_hWnd = nullptr;

CDoWork::CDoWork()
{

}

CDoWork::~CDoWork()
{

}

void CDoWork::Init(HWND hwnd)
{
	m_hWnd = hwnd;
}

DWORD WINAPI ThreadStartClassify(LPVOID lpParam)
{

	int errorCode = true;
	int* pErrorCode = new int(errorCode);
	if (m_hWnd)
	{
		::PostMessage(m_hWnd, EVENT_IMAGE_CLASSIFY_FINISHED, 0, (LPARAM)pErrorCode);
	}

	return 0;
}

void CDoWork::TestThread()
{
	CreateThread(NULL, 0, ThreadStartClassify, NULL, 0, NULL);//(LPTHREAD_START_ROUTINE)
}
