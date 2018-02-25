#include "trackmanager.h"

TrackManager::TrackManager(QObject *parent) : Loader(parent) {}

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

	m_dbmanager->exec(JT, Update({ROW}, {rows}, true), Where({MUSICID}, {ids}));
}

void TrackManager::sortTracksByRow() { sortModel(RowRole); }
