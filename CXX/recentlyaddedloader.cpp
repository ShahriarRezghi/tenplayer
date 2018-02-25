#include "recentlyaddedloader.h"

RecentlyAddedLoader::RecentlyAddedLoader(QObject *parent) : Loader(parent)
{
	m_model = new QmlModel(this);

	m_model->addRoles({Add(AlbumRole), Add(AlbumartistRole), Add(GenreRole),
					   Add(YearRole), Add(IDRole), Add(TrackRole),
					   Add(TitleRole), Add(PathRole), Add(ArtworkRole)});
}

void RecentlyAddedLoader::load()
{
	clear();

	qDebug() << Query->exec(
		"SELECT rowid, * FROM music ORDER BY rowid DESC LIMIT 100;");

	while (Query->next()) m_model->appendRow(recordToItem(Query->record()));
}
