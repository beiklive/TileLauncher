#include "AcrylicEffect.h"

#ifdef Q_OS_WIN
#include <windows.h>
#include <dwmapi.h>

AcrylicEffect::AcrylicEffect(QWidget* widget) : m_widget(widget) {}

void AcrylicEffect::apply() {
    setAcrylicEffect();
}


extern "C" {
    // 如果未定义，手动添加 ACCENT_STATE 和 WINDOWCOMPOSITIONATTRIB
    typedef enum _ACCENT_STATE {
        ACCENT_DISABLED = 0,
        ACCENT_ENABLE_GRADIENT = 1,
        ACCENT_ENABLE_TRANSPARENTGRADIENT = 2,
        ACCENT_ENABLE_BLURBEHIND = 3,          // 普通模糊（Win10 早期版本）
        ACCENT_ENABLE_ACRYLICBLURBEHIND = 4,   // 亚克力效果（Win10 1803+）
        ACCENT_INVALID_STATE = 5
    } ACCENT_STATE;

    typedef enum _WINDOWCOMPOSITIONATTRIB {
        WCA_UNDEFINED = 0,
        WCA_ACCENT_POLICY = 19
    } WINDOWCOMPOSITIONATTRIB;

    // ACCENT_POLICY 结构体
    typedef struct _ACCENT_POLICY {
        ACCENT_STATE AccentState;
        DWORD AccentFlags;
        DWORD GradientColor;
        DWORD AnimationId;
    } ACCENT_POLICY;

    // WINCOMPATTRDATA 结构体
    typedef struct _WINCOMPATTRDATA {
        WINDOWCOMPOSITIONATTRIB Attribute;
        PVOID Data;
        SIZE_T SizeOfData;
    } WINCOMPATTRDATA;

    // 声明 SetWindowCompositionAttribute 函数（通常 user32.dll 已提供）
    typedef BOOL(WINAPI* pfnSetWindowCompositionAttribute)(HWND, WINCOMPATTRDATA*);
}

void AcrylicEffect::setAcrylicEffect() {
    HWND hwnd = (HWND)m_widget->winId();

    //m_widget->setWindowFlags(Qt::FramelessWindowHint);
    m_widget->setAttribute(Qt::WA_TranslucentBackground);

    const HINSTANCE hModule = LoadLibrary(TEXT("user32.dll"));
    if (hModule) {
        auto SetWindowCompositionAttribute = (pfnSetWindowCompositionAttribute)GetProcAddress(hModule, "SetWindowCompositionAttribute");
        if (SetWindowCompositionAttribute) {
            ACCENT_POLICY accent = { ACCENT_ENABLE_ACRYLICBLURBEHIND , 2, 0x55000000, 0 };
            WINCOMPATTRDATA data = { WCA_ACCENT_POLICY, &accent, sizeof(accent) };
            SetWindowCompositionAttribute(hwnd, &data);
        }
        FreeLibrary(hModule);
    }
}
#endif
