#include <QtConcurrent>
#include "ThumbnailModel.h"

ThumbnailModel::ThumbnailModel(const QRegExp& fileMask, QObject *parent)
    : QAbstractListModel(parent),
      fileMask(fileMask)
{
}

ThumbnailModel::~ThumbnailModel() {
    setStoppedFlag(true);
    this->updateFunction.waitForFinished();
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

        setStoppedFlag(true);
        this->updateFunction.waitForFinished();
        setStoppedFlag(false);

        this->updateFunction = QtConcurrent::run(this, &ThumbnailModel::fillModel, directory);
    }
}

void
ThumbnailModel::setStoppedFlag(bool value)
{
    QMutexLocker locker(&this->mutex);
    this->stopped = value;
}

bool
ThumbnailModel::isNeedToStop() const
{
    QMutexLocker locker(&this->mutex);
    return this->stopped;
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
    size_t totalSize = 0;
    while (it.hasNext()) {
        const QString& filename = it.next();
        if (!this->fileMask.exactMatch(filename)) {
            continue;
        }

        totalSize += QFile(filename).size();

        QPixmap pixmap(filename);
        iconList.push_back(QIcon(pixmap.scaled(200, 200, Qt::KeepAspectRatio)));
        if (totalSize > 15 *1024 * 1024) { //handle maximum 5Mb
            appendList(iconList);
            iconList.clear();
            totalSize = 0;

            if (isNeedToStop()) {
                return;
            }
        }
    }

    if (!iconList.empty()) {
        appendList(iconList);
    }
}

