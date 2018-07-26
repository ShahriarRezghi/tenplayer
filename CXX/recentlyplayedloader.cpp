#include "recentlyplayedloader.h"
#include "playlistloader.h"
#include "queueloader.h"

RecentlyPlayedLoader::RecentlyPlayedLoader(QObject *parent) : Loader(parent)
{
	m_maxRowCount = 100;
	m_model = new QmlModel(this);

	m_model->addRoles({Add(AlbumRole), Add(ArtistRole), Add(AlbumartistRole),
					   Add(GenreRole), Add(YearRole), Add(IDRole),
					   Add(TrackRole), Add(TitleRole), Add(PathRole),
					   Add(ArtworkRole)});

	read();
}

void RecentlyPlayedLoader::save()
{
	QSettings S;
	S.beginGroup("Recent");
	S.setValue("PlayedIDs", m_playedIds);
	S.endGroup();
}

void RecentlyPlayedLoader::read()
{
	QSettings S;
	S.beginGroup("Recent");
	m_playedIds = S.value("PlayedIDs", QStringList()).toStringList();
	S.endGroup();
}

void RecentlyPlayedLoader::addPlayedItem(QStandardItem *I)
{
	QVariant id = I->data(IDRole);

	for (int i = 0; i < m_model->rowCount(); ++i)
		if (m_model->item(i)->data(IDRole) == id)
		{
			m_playedIds.removeAt(i);
			m_model->removeRow(i);
			break;
		}

	m_model->insertRow(0, I->clone());
	m_playedIds.insert(0, id.toString());

	if (m_model->rowCount() > m_maxRowCount)
	{
		m_model->removeRow(m_model->rowCount() - 1);
		m_playedIds.removeLast();
	}

	save();
}

void RecentlyPlayedLoader::load()
{
	QList<QStandardItem *> items;

	for (int i = 0; i < m_playedIds.count(); ++i)
	{
		Query->prepare("SELECT rowid, * FROM music WHERE rowid=?");
		Query->bindValue(0, m_playedIds[i]);
		Query->exec();

		if (!Query->first())
		{
			m_playedIds.removeAt(i);
			--i;
			continue;
		}

		items << recordToItem(Query->record());
	}

	emit addItemsToModelFromThread(items);
}

void RecentlyPlayedLoader::clicked(const int &index)
{
	Queue->playRootItem(m_model->invisibleRootItem(), index);
}

void RecentlyPlayedLoader::actionTriggered(const int &type, const int &index,
										   const QVariant &extra)
{
	if (type == Remove)
	{
		deleteSong(m_model->item(index)->data(IDRole));
		m_model->removeRow(index);
		Status->setNeedsRefresh(true);
		return;
	}

	if (type == Play)
		Queue->playRootItem(m_model->invisibleRootItem(), index);
	else if (type == AddToQueue)
		Queue->addItem(m_model->item(index));
	else if (type == ShowDetails)
		Details->showItem(m_model->item(index));
	else if (type == AddToPlaylist)
		Playlist->addItem(extra.toInt(), m_model->item(index));
}
