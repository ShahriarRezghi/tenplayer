#include "albumloader.h"

AlbumLoader::AlbumLoader(QObject *parent) : Loader(parent)
{
	m_model = new QmlModel(this);
	m_model->addRoles(
		{Add(AlbumRole), Add(AlbumartistRole), Add(GenreRole), Add(YearRole)});
}

void AlbumLoader::load()
{
	clear();

	qDebug() << Query->exec(
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

		m_model->appendRow(item);
	}

	sortModel(AlbumartistRole);
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
	qDebug() << Query->exec();

	while (Query->next())
	{
		auto *item = recordToItem(Query->record());
		item->setData(artwork, ArtworkRole);
		items << item;
	}

	sortItemList({TitleRole, TrackRole}, items);
	return items;
}
