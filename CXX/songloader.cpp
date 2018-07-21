#include "songloader.h"

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
	qDebug() << Query->exec("SELECT rowid, * FROM music;");
	while (Query->next()) m_model->appendRow(recordToItem(Query->record()));
	sortModel(TitleRole);
}
