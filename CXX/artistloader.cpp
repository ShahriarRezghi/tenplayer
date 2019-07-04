#include "artistloader.h"
#include "playlistloader.h"
#include "queueloader.h"
#include "trackmanager.h"

ArtistLoader::ArtistLoader(QObject *parent) : Loader(parent)
{
    m_model = new QmlModel(this);
    m_model->addRoles({Add(ArtistRole), Add(ArtworkRole)});

    createSearchModel(ArtistRole);
}

void ArtistLoader::load()
{
    QList<QStandardItem *> items;

    Query->exec(
        "SELECT artist, group_concat(album), group_concat(albumartist) from "
        "music GROUP BY artist;");

    while (Query->next())
    {
        auto *item = new QStandardItem;
        QString artwork;
        auto artist = Query->value(0);

        auto albumList = Query->value(1).toString().split(',').toVector();
        auto albumartistList = Query->value(2).toString().split(',').toVector();

        for (int i = 0; i < albumList.count(); ++i)
            if (!albumList[i].isEmpty() && !albumartistList.isEmpty())
            {
                artwork = getArtwork(albumList[i], albumartistList[i]);
                break;
            }

        item->setData(artist, ArtistRole);
        item->setData(artwork, ArtworkRole);
        items << item;
    }

    emit addItemsToModelFromThread(items);
}

void ArtistLoader::clicked(const int &index)
{
    Track->showItems(getSubItems(m_model->item(index)));
}

void ArtistLoader::actionTriggered(const int &type, const int &index,
                                   const QVariant &extra)
{
    if (type == Remove)
    {
        deleteArtist(m_model->item(index));
        m_model->removeRow(index);
        Status->setNeedsRefresh(true);
        return;
    }

    QList<QStandardItem *> items = getSubItems(m_model->item(index));

    if (type == Play)
        Queue->playItems(items, 0);
    else if (type == AddToQueue)
        Queue->addItems(items);
    else if (type == AddToPlaylist)
        Playlist->addItems(extra.toInt(), items);
    else if (type == ShowDetails)
        Details->showItems(items);
}

void ArtistLoader::deleteArtist(QStandardItem *item)
{
    QVariant artist = item->data(ArtistRole);

    Query->prepare("DELETE FROM music WHERE artist=?;");
    Query->bindValue(0, artist);
    Query->exec();
}

QList<QStandardItem *> ArtistLoader::getSubItems(QStandardItem *item)
{
    QList<QStandardItem *> items;

    auto artist = item->data(ArtistRole);

    Query->prepare("SELECT rowid, * FROM music where artist=?;");
    Query->bindValue(0, artist);
    Query->exec();

    while (Query->next())
    {
        auto *item = recordToItem(Query->record());
        items << item;
    }

    sortItemList({TitleRole, TrackRole, AlbumRole}, items);
    return items;
}

void ArtistLoader::addItemsToModel(const QList<QStandardItem *> &items)
{
    Loader::addItemsToModel(items);
    sortModel(ArtistRole);
}
