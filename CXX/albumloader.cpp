#include "albumloader.h"
#include "playlistloader.h"
#include "queueloader.h"
#include "trackmanager.h"

AlbumLoader::AlbumLoader(QObject *parent) : Loader(parent)
{
    m_model = new QmlModel(this);
    m_model->addRoles({Add(AlbumRole), Add(AlbumartistRole), Add(GenreRole),
                       Add(YearRole), Add(ArtworkRole)});

    createSearchModel(AlbumRole);
}

void AlbumLoader::deleteAlbum(QStandardItem *item)
{
    QVariant album = item->data(AlbumRole);
    QVariant albumArtist = item->data(AlbumartistRole);

    Query->prepare("DELETE FROM music WHERE album=?, albumartist=?;");
    Query->bindValue(0, album);
    Query->bindValue(1, albumArtist);
    Query->exec();
}

void AlbumLoader::load()
{
    QList<QStandardItem *> items;

    Query->exec(
        "SELECT album, albumartist, "
        "group_concat(genre), group_concat(year) "
        "FROM music GROUP BY album, albumartist;");

    while (Query->next())
    {
        auto *item = new QStandardItem;
        QString album = Query->value(0).toString();
        QString albumArtist = Query->value(1).toString();

        auto genreList =
            Query->value(2).toString().split(',', QString::SkipEmptyParts);
        auto yearList =
            Query->value(2).toString().split(',', QString::SkipEmptyParts);

        auto genre = genreList.isEmpty() ? "" : genreList.first();
        auto year = yearList.isEmpty() ? "" : yearList.first();

        item->setData(album, AlbumRole);
        item->setData(albumArtist, AlbumartistRole);
        item->setData(getArtwork(album, albumArtist), ArtworkRole);
        item->setData(genre, GenreRole);
        item->setData(year, YearRole);

        items << item;
    }

    emit addItemsToModelFromThread(items);
}

void AlbumLoader::clicked(const int &index)
{
    Track->showItems(getSubItems(m_model->item(index)));
}

void AlbumLoader::actionTriggered(const int &type, const int &index,
                                  const QVariant &extra)
{
    if (type == Remove)
    {
        deleteAlbum(m_model->item(index));
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

QList<QStandardItem *> AlbumLoader::getSubItems(QStandardItem *item)
{
    QList<QStandardItem *> items;

    auto album = item->data(AlbumRole);
    auto albumArtist = item->data(AlbumartistRole);
    auto artwork = item->data(ArtworkRole);

    Query->prepare(
        "SELECT rowid, * FROM music where album=? AND albumartist=?;");
    Query->bindValue(0, album);
    Query->bindValue(1, albumArtist);
    Query->exec();

    while (Query->next())
    {
        auto *item = recordToItem(Query->record());
        item->setData(artwork, ArtworkRole);
        items << item;
    }

    sortTrackList(items);
    return items;
}

void AlbumLoader::addItemsToModel(const QList<QStandardItem *> &items)
{
    Loader::addItemsToModel(items);
    sortModel(AlbumartistRole);
}
