#include <QtWidgets>
#include "MainWindow.h"

MainWindow::MainWindow(const QString& title, QWidget *parent)
    : QWidget(parent)
{
    initUi(title);
}

void
MainWindow::initUi(const QString& title)
{
    createDirectoryTree();
    createThumbnailView();

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(this->directoryTree, 1);
    mainLayout->addWidget(thumbnailView, 3);

    setLayout(mainLayout);
    setWindowTitle(title);
}

void
MainWindow::createDirectoryTree()
{
    this->directoryTree = new QTreeView;
    this->directoryTree->setModel(createDataModel());
    this->directoryTree->setExpanded(directoryModel->index(0, 0), true);
    this->directoryTree->hideColumn(1);
    this->directoryTree->hideColumn(2);
    this->directoryTree->hideColumn(3);
}

QFileSystemModel *
MainWindow::createDataModel()
{
    this->directoryModel = new QFileSystemModel;
    this->directoryModel->setRootPath("/");
    this->directoryModel->setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
    return this->directoryModel;
}

void
MainWindow::createThumbnailView()
{
    this->thumbnailView = new QListWidget;
    this->thumbnailView->setViewMode(QListWidget::IconMode);
    this->thumbnailView->setIconSize(QSize(200, 200));
    this->thumbnailView->setResizeMode(QListWidget::Adjust);

    this->thumbnailView->addItem(new QListWidgetItem(QIcon("pictures/earth.jpg"), "Earth"));
    this->thumbnailView->addItem(new QListWidgetItem(QIcon("pictures/space.jpg"), "Space"));
    this->thumbnailView->setSelectionMode(QAbstractItemView::NoSelection);
}
