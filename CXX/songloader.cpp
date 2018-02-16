#include "songloader.h"

SongLoader::SongLoader(QObject *parent) : Loader(parent) {}

void SongLoader::load()
{
	clear();
	qDebug() << Query->exec("SELECT rowid, * FROM music;");
	while (Query->next()) m_model->appendRow(recordToItem(Query->record()));
	sortModel(TitleRole);
}
