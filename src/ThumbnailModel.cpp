#include <QtConcurrent>
#include "ThumbnailModel.h"

ThumbnailModel::ThumbnailModel(const QRegExp& fileMask, QObject *parent)
    : QAbstractListModel(parent),
      fileMask(fileMask)
{
}

ThumbnailModel::~ThumbnailModel() {
    this->updateMutex.lock();
    this->updateFunction.waitForFinished();
    this->updateMutex.unlock();
}

int
ThumbnailModel::rowCount(const QModelIndex &parent) const
{
    return this->icons.size();
}

QVariant
ThumbnailModel::data(const QModelIndex &index, int role) const 
{
    if (index.isValid() && role == Qt::DecorationRole &&
        index.row() < icons.size())
    {
        return this->icons[index.row()];
    }

    return QVariant();
}

void
ThumbnailModel::updateDirectory(const QString& directory)
{
    if (this->directory != directory) {
        this->directory = directory;

        beginResetModel();
        this->icons.clear();
        endResetModel();

        fillModel(directory);
    }
}

void
ThumbnailModel::appendList(const QList<QIcon>& iconList)
{
    beginInsertRows(index(0, 0), this->icons.size(), this->icons.size() + iconList.size());
    this->icons.append(iconList);
    endInsertRows();
}

void
ThumbnailModel::fillModel(const QString& directory)
{
    QList<QIcon> iconList;
    QDirIterator it(directory);
    while (it.hasNext()) {
        const QString& filename = it.next();
        if (!this->fileMask.exactMatch(filename)) {
            continue;
        }


        QPixmap pixmap(filename);
        iconList.push_back(QIcon(pixmap.scaled(200, 200, Qt::KeepAspectRatio)));
        if (iconList.size() >= 50) {
            appendList(iconList);
            iconList.clear();
        }
    }

    if (!iconList.empty()) {
        appendList(iconList);
    }
}

