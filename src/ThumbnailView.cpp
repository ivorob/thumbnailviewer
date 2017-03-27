#include <QPainter>
#include "ThumbnailView.h"

ThumbnailView::ThumbnailView(QWidget *parent)
    : QListWidget(parent)
{
}

void
ThumbnailView::paintEvent(QPaintEvent *event)
{
    if (model() && model()->rowCount(rootIndex()) > 0) {
        QListWidget::paintEvent(event);
        return;
    }

    QPainter painter(this->viewport());
    painter.setFont(QFont("Times New Roman", 22));
    painter.drawText(rect(), Qt::AlignCenter, "No pictures to display");
}
