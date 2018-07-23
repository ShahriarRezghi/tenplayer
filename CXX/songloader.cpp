#include "songloader.h"
#include "playlistloader.h"
#include "queueloader.h"

SongLoader::SongLoader(QObject *parent) : Loader(parent)
{
	m_model = new QmlModel(this);
	m_model->addRoles({Add(AlbumRole), Add(ArtistRole), Add(AlbumartistRole),
					   Add(GenreRole), Add(YearRole), Add(IDRole),
					   Add(TrackRole), Add(TitleRole), Add(PathRole),
					   Add(ArtworkRole)});

	createSearchModel(TitleRole);
}

void SongLoader::load()
{
	clear();
	Query->exec("SELECT rowid, * FROM music;");
	while (Query->next()) m_model->appendRow(recordToItem(Query->record()));
	sortModel(TitleRole);
}

void SongLoader::clicked(const int &index)
{
	Queue->playRootItem(m_model->invisibleRootItem(), index);
}

void SongLoader::actionTriggered(const int &type, const int &index,
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
	else if (type == AddToPlaylist)
		Playlist->addItem(extra.toInt(), m_model->item(index));
	else if (type == ShowDetails)
		Details->showItem(m_model->item(index));
}
