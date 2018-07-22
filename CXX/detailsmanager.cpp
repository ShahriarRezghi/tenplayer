#include "detailsmanager.h"

DetailsManager::DetailsManager(QObject *parent) : QObject(parent)
{
	m_model = new QmlModel(this);
	m_model->addRoles({Add(AlbumRole), Add(ArtistRole), Add(AlbumartistRole),
					   Add(GenreRole), Add(YearRole), Add(IDRole),
					   Add(TrackRole), Add(TitleRole), Add(PathRole),
					   Add(ArtworkRole)});
}

void DetailsManager::showItem(QStandardItem *item)
{
	m_model->clear();
	m_model->appendRow(item->clone());
}

void DetailsManager::showItems(const QList<QStandardItem *> &items)
{
	m_model->clear();
	for (QStandardItem *item : items) m_model->appendRow(item);
}

QStandardItemModel *DetailsManager::model() const { return m_model; }
