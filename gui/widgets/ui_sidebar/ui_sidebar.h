#pragma once

#include "global.hpp"
#include "ui_button/ui_button.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QPropertyAnimation>
#include <QVector>

namespace beiklive {

/**
 * @brief 自定义侧边栏控件，支持展开/收起功能
 */
class ui_sidebar : public beiklive::BaseWidget
{
    Q_OBJECT
public:
    explicit ui_sidebar(QWidget *parent = nullptr);
    int curWidth() const;
    
    /**
     * @brief 向侧边栏添加按钮
     * @param text 按钮文字
     * @param icon 按钮图标
     * @param receiver 信号接收对象
     * @param slot 连接的槽函数
     */
    void addButton(const QString &text, const QIcon &icon, 
                  const QObject *receiver, const char *slot);

private slots:
    void toggleSidebar();  // 切换侧边栏展开状态

private:
    // UI组件
    Ui_Button *m_toggleButton;      // 展开/收起按钮
    BaseWidget *m_buttonContainer;  // 按钮容器
    QVBoxLayout *m_mainLayout;      // 主布局
    QVBoxLayout *m_buttonLayout;    // 按钮布局
    QPropertyAnimation *m_animation; // 展开动画
    
    // 状态
    bool m_isExpanded;     // 是否展开状态
    int m_normalWidth;     // 收起宽度
    int m_expandedWidth;   // 展开宽度
    QVector<Ui_Button *> m_buttons; // 按钮列表

    void setupUi();            // 初始化UI
    void updateButtonStyles(); // 更新按钮样式
};

} // namespace beiklive