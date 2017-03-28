#include "MainWindow.h"

MainWindow::MainWindow(const QString& title, QWidget *parent)
    : QSplitter(parent),
      directoryTreeModel(),
      iconModel(),
      directoryTree(),
      thumbnailView()
{
    initUi(title);
}

void
MainWindow::initUi(const QString& title)
{
    createDirectoryTree();
    createThumbnailView();

    setStretchFactor(0, 1);
    setStretchFactor(1, 3);

    setWindowTitle(title);
}

void
MainWindow::createDirectoryTree()
{
    this->directoryTree = new QTreeView(this);
    this->directoryTree->setModel(createDataTreeModel());
    this->directoryTree->setExpanded(directoryTreeModel->index(0, 0), true);
    this->directoryTree->hideColumn(1);
    this->directoryTree->hideColumn(2);
    this->directoryTree->hideColumn(3);
    this->directoryTree->header()->hide();

    QObject::connect(this->directoryTree, SIGNAL(clicked(const QModelIndex&)), 
            this, SLOT(chooseNewDirectory(const QModelIndex&)));
}

QFileSystemModel *
MainWindow::createDataTreeModel()
{
    this->directoryTreeModel = new QFileSystemModel;
    this->directoryTreeModel->setRootPath("/");
    this->directoryTreeModel->setFilter(QDir::AllDirs | QDir::NoDotAndDotDot | QDir::Drives);
    return this->directoryTreeModel;
}

void
MainWindow::createThumbnailView()
{
    this->thumbnailView = new ThumbnailView(this);
    this->thumbnailView->setWrapping(true);
    this->thumbnailView->setViewMode(QListWidget::IconMode);
    this->thumbnailView->setIconSize(QSize(200, 200));
    this->thumbnailView->setResizeMode(QListView::Adjust);
    this->thumbnailView->setSelectionMode(QAbstractItemView::NoSelection);
    this->thumbnailView->setModel(createIconModel());
}

ThumbnailModel *
MainWindow::createIconModel()
{
    this->iconModel = new ThumbnailModel(QRegExp(".+\\.jpg|.+\\.png|.+\\.xpm", Qt::CaseInsensitive), this);
    return this->iconModel;
}

void
MainWindow::chooseNewDirectory(const QModelIndex& index)
{
    QString directory = this->directoryTreeModel->filePath(index);
    if (QDir(directory).exists()) {
        this->iconModel->updateDirectory(directory);
    }
}
