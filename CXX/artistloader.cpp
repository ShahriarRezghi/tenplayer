#include "artistloader.h"
#include "trackmanager.h"

ArtistLoader::ArtistLoader(QObject *parent) : Loader(parent)
{
	m_model = new QmlModel(this);
	m_model->addRoles({Add(ArtistRole), Add(ArtworkRole)});

	createSearchModel(ArtistRole);
}

void ArtistLoader::load()
{
	clear();

	qDebug() << Query->exec(
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
		m_model->appendRow(item);
	}

	sortModel(ArtistRole);
}

void ArtistLoader::clicked(const int &index)
{
	Track->showItems(getSubItems(m_model->item(index)));
}

QList<QStandardItem *> ArtistLoader::getSubItems(QStandardItem *item)
{
	QList<QStandardItem *> items;

	auto artist = item->data(ArtistRole);
	auto artwork = item->data(ArtworkRole);

	Query->prepare("SELECT rowid, * FROM music where artist=?;");
	Query->bindValue(0, artist);
	qDebug() << Query->exec();

	while (Query->next())
	{
		auto *item = recordToItem(Query->record());
		item->setData(artwork, ArtworkRole);
		items << item;
	}

	sortItemList({TitleRole}, items);
	return items;
}
