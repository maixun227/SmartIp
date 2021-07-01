#include "customtooltip.h"

#include <mutex>
#include <QTimer>
#include <QPainter>
#include <QPainterPath>

#include "macros.hpp"
#include "core.h"
#include "mainwindow.h"

CustomToolTip::CustomToolTip(QWidget* parent)
    : QLabel(parent)
    , m_timer(new QTimer)
{
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_TransparentForMouseEvents);
    setWindowFlags(Qt::Tool | Qt::FramelessWindowHint);
    hide();
    
    m_timer->setSingleShot(true);
    connect(m_timer, &QTimer::timeout, this, &CustomToolTip::hideToolTip);
    
    setStyleSheet(defaultQSS);
}

void CustomToolTip::installToolTip(QWidget*) {
    static std::once_flag init;
    std::call_once(init, [] {
        s_instance = new CustomToolTip(nullptr);
    });
}
	
void CustomToolTip::showToolTip(const QString& text, int x, int y) {    
    if (s_instance) {
        if (s_instance->text() != text || s_instance->isHidden()) {
            s_instance->m_targetX = x;
            s_instance->m_targetY = y;
            
            static auto pW = pCore->window();
            s_instance->move(
                qBound(pW->x(), x, pW->x() + pW->width() - s_instance->width()),
                qBound(pW->y(), y, pW->y() + pW->height() - s_instance->height())
            );
            
            s_instance->setText(text);
            s_instance->hide();
            s_instance->show();
            
            s_instance->m_timer->stop();
            s_instance->m_timer->start(3000);
        }
    } else {
        return;
    }
}

void CustomToolTip::hideToolTip() {
    if (s_instance) {
        s_instance->hide();
    } else {
        return;
    }
}

void CustomToolTip::resizeEvent(QResizeEvent *) {
    static auto pW = pCore->window();
    s_instance->move(
        qBound(pW->x(), m_targetX, pW->x() + pW->width() - width()),
        qBound(pW->y(), m_targetY, pW->y() + pW->height() - height())
    );
}

void CustomToolTip::paintEvent(QPaintEvent* e) {
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    
//    QPainterPath path;
//    path.addRoundedRect(QRectF(0, 0, width(), height()), 4, 4);
//    QPen pen(QColor(119, 129, 244), 1);
//    p.setPen(pen);
//    p.fillPath(path, QColor(66, 64, 109));
//    p.drawPath(path);
    
//    p.drawRoundedRect(0, 0, width(), height(), 4, 4);
    p.setPen(Qt::transparent);
    p.setBrush(QColor(0, 0, 0, 51));
    p.drawRect(0, 0, width() - 1, height() - 1);
    
    QLabel::paintEvent(e);
}
