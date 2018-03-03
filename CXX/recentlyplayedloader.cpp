#include "recentlyplayedloader.h"

RecentlyPlayedLoader::RecentlyPlayedLoader(QObject *parent) : Loader(parent)
{
	m_maxRowCount = 100;
	m_model = new QmlModel(this);

	m_model->addRoles({Add(AlbumRole), Add(AlbumartistRole), Add(GenreRole),
					   Add(YearRole), Add(IDRole), Add(TrackRole),
					   Add(TitleRole), Add(PathRole), Add(ArtworkRole)});
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
	for (int i = 0; i < m_playedIds.count(); ++i)
	{
		Query->prepare("SELECT rowid, * FROM music WHERE rowid=?");
		Query->bindValue(0, m_playedIds[i]);
		qDebug() << Query->exec();

		if (!Query->first())
		{
			m_playedIds.removeAt(i);
			--i;
			continue;
		}

		Query->first();
		m_model->appendRow(recordToItem(Query->record()));
	}
}
