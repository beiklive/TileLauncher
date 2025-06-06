// Copyright (c) 2025. All rights reserved.
// Author: beiklive
// Date: 2025-05-09
#ifndef _INCLUDE_GLOBAL_H_
#define _INCLUDE_GLOBAL_H_

#include "logger.h"
#include "json.h"
#include "tool.h"
#include "PinyinLookup.h"

#include <QFile>
#include <QDebug>
#include <QVariant>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QResizeEvent>

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QPainter>
#include <QList>
#include <iostream>
// 定义窗口四个角和四个边的枚举
enum WindowParts
{
    NONE = 0,   // 0000 (无)
    TOP = 1,    // 0001 (上边)
    BOTTOM = 2, // 0010 (下边)
    LEFT = 4,   // 0100 (左边)
    RIGHT = 8,  // 1000 (右边)
};

enum ButtonMode
{
    BM_NONE,
    BM_FILE,
    BM_FOLDER,
    BM_INDEX
};



// 判断是否是 Windows 系统
#if defined(Q_OS_WIN)
    #define IS_WINDOWS 1
#else
    #define IS_WINDOWS 0
#endif

// 判断是否是 macOS 系统
#if defined(Q_OS_MACOS) || defined(Q_OS_MAC)
    #define IS_MACOS 1
#else
    #define IS_MACOS 0
#endif


#define THEME_NAME(obj, name) obj->setProperty("styleclass", name);

#define ICON_DEFAULT "assets/icons/default.svg"
#define ICON_LOGO "assets/icons/logo.png"
#define ICON_WINDOW_CLOSE "assets/icons/icon_close.svg"
#define ICON_WINDOW_MINIMIZE "assets/icons/icon_minimize.svg"
#define ICON_WINDOW_MAXIMIZE "assets/icons/icon_maximize.svg"
#define ICON_WINDOW_RESTORE "assets/icons/icon_restore.svg"

#define ICON_DIR_UP "assets/icons/dir_up.svg"
#define ICON_DIR_DOWN "assets/icons/dir_down.svg"



#endif // _INCLUDE_GLOBAL_H_