
// MobileNetV3.h: PROJECT_NAME 应用程序的主头文件
//
#include <atlimage.h>
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含 'pch.h' 以生成 PCH"
#endif

#include "resource.h"		// 主符号


// CMobileNetV3App:
// 有关此类的实现，请参阅 MobileNetV3.cpp
//

class CMobileNetV3App : public CWinApp
{
public:
	CMobileNetV3App();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CMobileNetV3App theApp;

