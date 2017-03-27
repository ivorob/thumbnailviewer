#ifndef __THUMBNAILVIEWER_THUMBNAIL_VIEW_H__
#define __THUMBNAILVIEWER_THUMBNAIL_VIEW_H__

#include <QListWidget>

class ThumbnailView : public QListWidget {
    Q_OBJECT
public:
    ThumbnailView(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *event) override;
};

#endif //__THUMBNAILVIEWER_THUMBNAIL_VIEW_H__
