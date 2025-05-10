#ifndef SIDEBAR_H
#define SIDEBAR_H

#include "global.hpp"
#include "ui_base_widget/baseWidget.h"
#include "ui_button/ui_button.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QPropertyAnimation>
#include <QSizePolicy>
#include <QSpacerItem>
#include <QFrame>

class SideBar : public beiklive::BaseWidget
{
    Q_OBJECT
public:
    explicit SideBar();
    void addButton(const QString &text, const QIcon &icon, const QObject *receiver, const char *slot);

protected:
    // void paintEvent(QPaintEvent *event) override;

private slots:
    void toggleSidebar();

private:
    QPushButton *m_toggleButton;
    beiklive::BaseWidget *m_buttonContainer;
    QSpacerItem *m_spacer;

    QVBoxLayout *m_main_layout;
    QVBoxLayout *m_button_layout;

    bool m_isExpanded;

    int m_normalWidth;
    int m_expandedWidth;
    
    QPropertyAnimation *m_animation;

    void setupUi();
    // void updateButtonStyles();
};

#endif // SIDEBAR_H