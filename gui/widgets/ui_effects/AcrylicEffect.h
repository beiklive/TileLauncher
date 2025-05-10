#ifndef ACRYLICEFFECT_H
#define ACRYLICEFFECT_H

#include <QWidget>

class AcrylicEffect {
public:
    explicit AcrylicEffect(QWidget* widget);
    void apply();

private:
    QWidget* m_widget;
    void setAcrylicEffect();
};

#endif // ACRYLICEFFECT_H
