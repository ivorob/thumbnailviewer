#include "MainWindow.h"

MainWindow::MainWindow(const QString& title, QWidget *parent)
    : QSplitter(parent),
      directoryTreeModel(),
      directoryModel(),
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

    QObject::connect(this->directoryTree, SIGNAL(clicked(const QModelIndex&)), 
            this, SLOT(chooseNewDirectory(const QModelIndex&)));
}

QFileSystemModel *
MainWindow::createDataTreeModel()
{
    this->directoryTreeModel = new QFileSystemModel;
    this->directoryTreeModel->setRootPath("/");
    this->directoryTreeModel->setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
    return this->directoryTreeModel;
}

void
MainWindow::createThumbnailView()
{
    this->thumbnailView = new ThumbnailView(this);
    this->thumbnailView->setViewMode(QListWidget::IconMode);
    this->thumbnailView->setIconSize(QSize(200, 200));
    this->thumbnailView->setResizeMode(QListWidget::Adjust);

    this->thumbnailView->setRootIndex(QModelIndex());
    this->thumbnailView->setModel(createDirectoryModel());
    this->thumbnailView->setSelectionMode(QAbstractItemView::NoSelection);
}

QFileSystemModel *
MainWindow::createDirectoryModel()
{
    this->directoryModel = new QFileSystemModel;
    this->directoryModel->setFilter(QDir::Files);
    this->directoryModel->setNameFilterDisables(false);
    this->directoryModel->setNameFilters(QStringList() << 
            "*.jpg" << "*.png" << "*.jpeg" << "*.bmp" << "*.xpm");
    return this->directoryModel;
}

void
MainWindow::chooseNewDirectory(const QModelIndex& index)
{
    QString directory = this->directoryTreeModel->filePath(index);
    if (QDir(directory).exists()) {
        this->directoryModel->setRootPath(directory);
        this->thumbnailView->setRootIndex(this->directoryModel->index(directory));
    }
}
