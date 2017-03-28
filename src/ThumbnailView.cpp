#include <QPainter>
#include <QWheelEvent>
#include <QDebug>
#include "ThumbnailView.h"

ThumbnailView::ThumbnailView(QWidget *parent)
    : QListView(parent)
{
}

void
ThumbnailView::paintEvent(QPaintEvent *event)
{
    if (rootIndex().isValid()) {
        if (model() && model()->rowCount(rootIndex()) > 0) {
            QListView::paintEvent(event);
            return;
        }

        QPainter painter(this->viewport());
        painter.setFont(QFont("Times New Roman", 22));
        painter.drawText(rect(), Qt::AlignCenter, "No pictures to display");
    }
}

void
ThumbnailView::wheelEvent(QWheelEvent *event)
{
    const QSize& size = iconSize();
    if (event->delta() > 0) {
        setIconSize(QSize(std::min(size.height() + 50, 200),
            std::min(size.width() + 50, 200)));
    } else {
        setIconSize(QSize(std::max(size.height() - 50, 50),
            std::max(size.width() - 50, 50)));
    }
}
