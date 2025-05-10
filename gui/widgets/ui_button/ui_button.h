#ifndef WIN10MENUBUTTON_H
#define WIN10MENUBUTTON_H

#include <QPushButton>
#include <QPropertyAnimation>

class Win10MenuButton : public QPushButton
{
    Q_OBJECT
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)
    
public:
    explicit Win10MenuButton(QWidget *parent = nullptr);
    
    void setActive(bool active);
    void setExpanded(bool expanded);
    
    QColor backgroundColor() const;
    void setBackgroundColor(const QColor &color);
    
protected:
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    
private:
    QColor m_normalColor = Qt::transparent;
    QColor m_hoverColor = QColor(240, 240, 240);
    QColor m_activeColor = QColor(230, 230, 230);
    QColor m_currentColor = m_normalColor;
    
    bool m_isActive = false;
    bool m_isExpanded = false;
    
    QPropertyAnimation *m_colorAnimation;
};

#endif // WIN10MENUBUTTON_H