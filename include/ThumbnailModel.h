#ifndef __THUMBNAILVIEWER_THUMBNAIL_MODEL_H__
#define __THUMBNAILVIEWER_THUMBNAIL_MODEL_H__

#include <QtWidgets>

class ThumbnailModel : public QAbstractListModel {
    Q_OBJECT
public:
    ThumbnailModel(const QRegExp& fileMask, QObject *parent = nullptr);
    ~ThumbnailModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
public slots:
    void updateDirectory(const QString& directory);
private:
    void appendList(const QList<QIcon>& iconList);
    void fillModel(const QString& directory);
private:
    QList<QIcon> icons;
    QRegExp fileMask;
    QFuture<void> updateFunction;
    QMutex updateMutex;
    QString directory;
};

#endif //__THUMBNAILVIEWER_THUMBNAIL_MODEL_H__
