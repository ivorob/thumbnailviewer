#include <QPainter>
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
