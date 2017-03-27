#ifndef __THUMBNAILVIEWER_MAIN_WINDOW_H__
#define __THUMBNAILVIEWER_MAIN_WINDOW_H__

#include <QWidget>

class MainWindow : public QWidget {
public:
    MainWindow(const QString& title, QWidget *parent = nullptr);
private:
    QFileSystemModel *createDataModel();
    void createDirectoryTree();
    void createThumbnailView();
    void initUi(const QString& title);
private:
    QFileSystemModel *directoryModel;
    QTreeView *directoryTree;
    QListWidget *thumbnailView;
};

#endif //__THUMBNAILVIEWER_MAIN_WINDOW_H__
