#ifndef __THUMBNAILVIEWER_MAIN_WINDOW_H__
#define __THUMBNAILVIEWER_MAIN_WINDOW_H__

#include <QtWidgets>
#include "ThumbnailView.h"
#include "ThumbnailModel.h"

class MainWindow : public QSplitter {
    Q_OBJECT
public:
    MainWindow(const QString& title, QWidget *parent = nullptr);
private:
    QFileSystemModel *createDataTreeModel();
    ThumbnailModel *createIconModel();

    void createDirectoryTree();
    void createThumbnailView();
    void initUi(const QString& title);
private slots:
    void chooseNewDirectory(const QModelIndex& index);
private:
    QFileSystemModel *directoryTreeModel;
    ThumbnailModel *iconModel;
    QTreeView *directoryTree;
    ThumbnailView *thumbnailView;
};

#endif //__THUMBNAILVIEWER_MAIN_WINDOW_H__
