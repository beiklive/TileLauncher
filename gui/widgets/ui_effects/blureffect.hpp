// Copyright (c) 2025. All rights reserved.
// Author: beiklive
// Date: 2025-05-09
#ifndef _INCLUDE_BLUREFFECT_H_
#define _INCLUDE_BLUREFFECT_H_

#include <QPainter>
#include <QGraphicsEffect>
#include <QPixmap>
#include <QGuiApplication>
#include <QScreen>

class BlurWidget : public QWidget
{
public:
    BlurWidget(QWidget *parent = nullptr) : QWidget(parent)
    {
        // 设置窗口属性
        setAttribute(Qt::WA_TranslucentBackground);
        setWindowFlags(Qt::FramelessWindowHint);
    }

protected:
    void paintEvent(QPaintEvent *event)
    {
Q_UNUSED(event);
        
        // 1. 获取屏幕截图作为背景
        QScreen *screen = QGuiApplication::primaryScreen();
        QPixmap background = screen->grabWindow(0, 
                                              this->mapToGlobal(QPoint(0, 0)).x(),
                                              this->mapToGlobal(QPoint(0, 0)).y(),
                                              width(), height());
        
        // 2. 创建模糊效果
        QImage blurredImage(background.size(), QImage::Format_ARGB32_Premultiplied);
        blurredImage.fill(Qt::transparent);
        
        QPainter blurPainter(&blurredImage);
        QGraphicsBlurEffect blurEffect;
        blurEffect.setBlurRadius(15); // 模糊半径
        blurEffect.setBlurHints(QGraphicsBlurEffect::QualityHint); // 质量优先
        
        // 3. 应用模糊效果
        blurPainter.setRenderHint(QPainter::Antialiasing);
        blurPainter.setRenderHint(QPainter::SmoothPixmapTransform);
        blurEffect.draw(&blurPainter);
        blurPainter.drawPixmap(0, 0, background);
        blurPainter.end();
        
        // 4. 绘制模糊背景
        QPainter painter(this);
        painter.drawImage(0, 0, blurredImage);
        
        // 5. 添加半透明覆盖层增强效果
        painter.setBrush(QColor(255, 255, 255, 50)); // 半透明白色
        painter.setPen(Qt::NoPen);
        painter.drawRoundedRect(rect(), 10, 10); // 圆角矩形
    }

    // 高斯模糊实现
    QImage applyGaussianBlur(const QPixmap &pixmap, int radius)
    {
        QImage image = pixmap.toImage();
        if (radius < 1)
            return image;

        // 这里可以使用更高效的高斯模糊算法
        // 例如使用QGraphicsBlurEffect或者第三方库如OpenCV

        // 简单实现（性能较差，仅作示例）
        QImage result(image.size(), QImage::Format_ARGB32_Premultiplied);
        result.fill(Qt::transparent);

        QGraphicsBlurEffect blur;
        blur.setBlurRadius(radius);

        QPainter painter(&result);
        blur.draw(&painter);
        painter.drawImage(0, 0, image);

        return result;
    }
};

#endif // _INCLUDE_BLUREFFECT_H_