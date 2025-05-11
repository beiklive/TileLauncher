#ifndef ACRYLICEFFECT_H
#define ACRYLICEFFECT_H

#include <QWidget>
#ifdef Q_OS_WIN

class AcrylicEffect {
public:
    explicit AcrylicEffect(QWidget* widget);
    void apply();

private:
    QWidget* m_widget;
    void setAcrylicEffect();
};
#endif

#endif // ACRYLICEFFECT_H
