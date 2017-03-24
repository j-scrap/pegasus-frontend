#include "Model.h"


namespace Model {

GameItem::GameItem(QObject* parent)
    : QObject(parent)
{}

GameModel::GameModel(QObject* parent)
    : QAbstractListModel(parent)
{}

void GameModel::append(GameItemPtr& game)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    games << game;
    endInsertRows();
}

int GameModel::rowCount(const QModelIndex&) const {
    return games.count();
}

QVariant GameModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid() || index.row() >= games.count()) {
        Q_ASSERT(false);
        return QVariant();
    }

    GameItemPtr game = games.at(index.row());
    switch (role) {
        case Roles::TitleRole:
            return game->title;
        default:
            break;
    }

    Q_ASSERT(false);
    return QVariant();
}

QHash<int, QByteArray> GameModel::roleNames() const {
    static const QHash<int, QByteArray> roles = {
        { Roles::TitleRole, "title" },
    };

    return roles;
}

PlatformItem::PlatformItem(QObject* parent)
    : QObject(parent)
    , game_model(new GameModel)
{}

PlatformModel::PlatformModel(QObject* parent)
    : QAbstractListModel(parent)
{}

void PlatformModel::append(PlatformItemPtr& platform)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    platforms << platform;
    endInsertRows();
}

int PlatformModel::rowCount(const QModelIndex&) const {
    return platforms.count();
}

QVariant PlatformModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid() || index.row() >= platforms.count()) {
        Q_ASSERT(false);
        return QVariant();
    }

    PlatformItemPtr platform = platforms.at(index.row());
    switch (role) {
        case Roles::ShortNameRole:
            return platform->short_name;
        case Roles::LongNameRole:
            return platform->long_name;
        case Roles::GameModelRole:
            return QVariant::fromValue<QObject*>(platform->game_model.data());
        default:
            break;
    }

    Q_ASSERT(false);
    return QVariant();
}

QHash<int, QByteArray> PlatformModel::roleNames() const {
    static const QHash<int, QByteArray> roles = {
        { Roles::ShortNameRole, "shortName" },
        { Roles::LongNameRole, "longName" },
        { Roles::GameModelRole, "gameModel" },
    };

    return roles;
}

} // namespace Model
