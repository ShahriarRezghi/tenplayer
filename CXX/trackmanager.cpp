#include "trackmanager.h"
#include "playlistloader.h"
#include "queueloader.h"

TrackManager::TrackManager(QObject *parent) : Loader(parent)
{
	m_model = new QmlModel(this);
	m_model->addRoles({Add(AlbumRole), Add(ArtistRole), Add(AlbumartistRole),
					   Add(GenreRole), Add(YearRole), Add(IDRole),
					   Add(TrackRole), Add(TitleRole), Add(PathRole),
					   Add(ArtworkRole)});
}

void TrackManager::showItems(const QList<QStandardItem *> &items)
{
	clear();
	for (QStandardItem *item : items) m_model->appendRow(item);
}

void TrackManager::savePlaylistTrackRows()
{
	QVariantList ids;
	QVariantList rows;

	for (int i = 0; i < m_model->rowCount(); ++i)
	{
		ids << m_model->item(i)->data(IDRole);
		rows << m_model->item(i)->data(RowRole);
	}

	Query->exec("BEGIN TRANSACTION");
	Query->prepare("UPDATE mpjoin SET row=? WHERE mid=?;");
	Query->bindValue(0, rows);
	Query->bindValue(1, ids);
	qDebug() << Query->execBatch();
	qDebug() << Query->exec("COMMIT;");
}

void TrackManager::clicked(const int &index)
{
	Queue->playRootItem(m_model->invisibleRootItem(), index);
}

void TrackManager::actionTriggered(const int &type, const int &index,
								   const QVariant &extra)
{
	Q_UNUSED(extra)

	if (type == Remove)
	{
		deleteSong(m_model->item(index)->data(IDRole));
		m_model->removeRow(index);
		Status->setNeedsRefresh(true);
		return;
	}

	if (type == Play)
		clicked(index);
	else if (type == AddToQueue)
		Queue->addItem(m_model->item(index));
	else if (type == AddToPlaylist)
		Playlist->addItem(extra.toInt(), m_model->item(index));
	else if (type == ShowDetails)
		Details->showItem(m_model->item(index));
}

void TrackManager::sortTracksByRow() { sortModel(RowRole); }
