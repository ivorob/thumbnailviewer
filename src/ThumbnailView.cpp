#include <QPainter>
#include <QPainterPath>
#include <QWheelEvent>
#include <QItemDelegate>
#include "ThumbnailView.h"

namespace {

class BorderedIconItemDelegate : public QItemDelegate {
public:
    BorderedIconItemDelegate(int margin, QObject *parent = nullptr)
        : QItemDelegate(parent),
          margin(margin)
    {
    }

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override {
        const QVariant& data = index.data(Qt::DecorationRole);
        if (data.canConvert<QIcon>()) {
            const QIcon& icon = data.value<QIcon>();
            drawIcon(painter, icon, option.rect);
            drawBorder(painter, option.rect);
        }
    }

    QSize sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const override {
        return QSize(option.decorationSize.width() + this->margin,
                     option.decorationSize.height() + this->margin);
    }
private:
    void drawIcon(QPainter *painter, const QIcon& icon, const QRect& rect) const {
        const QPixmap& pixmap = icon.pixmap(rect.width() - this->margin, rect.height() - this->margin);

        int deltaX = (rect.width() - pixmap.width()) / 2;
        int deltaY = (rect.height() - pixmap.height()) / 2;
        painter->drawPixmap(rect.x() + deltaX, rect.y() + deltaY, pixmap);
    }

    void drawBorder(QPainter *painter, const QRect& rect) const {
        QPainterPath path;
        QRect newRect = rect;
        newRect -= QMargins(margin / 2, margin / 2, margin / 2, margin / 2);
        path.addRoundedRect(newRect, margin / 2, margin /2);
        QPen pen(Qt::gray, 3);
        painter->setPen(pen);
        painter->drawPath(path);
    }
private:
    int margin;
};

}

ThumbnailView::ThumbnailView(QWidget *parent)
    : QListView(parent)
{
    setItemDelegateForColumn(0, new BorderedIconItemDelegate(10));
}

void
ThumbnailView::paintEvent(QPaintEvent *event)
{
    if (model() && model()->rowCount() > 0) {
        QListView::paintEvent(event);
        return;
    }

    QPainter painter(this->viewport());
    painter.setFont(QFont("Times New Roman", 22));
    painter.drawText(rect(), Qt::AlignCenter, "No pictures to display");
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
