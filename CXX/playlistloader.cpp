#include "playlistloader.h"
#include "queueloader.h"
#include "trackmanager.h"

PlaylistLoader::PlaylistLoader(QObject *parent) : Loader(parent)
{
	m_model = new QmlModel(this);
	m_model->addRoles({Add(TitleRole), Add(ArtworkRole)});
}

void PlaylistLoader::load()
{
	clear();

	qDebug() << Query->exec("SELECT rowid, name FROM playlist;");

	while (Query->next())
	{
		auto *item = new QStandardItem;
		item->setData(Query->value(0), IDRole);
		item->setData(Query->value(1), TitleRole);
		m_model->appendRow(item);
	}

	sortModel(TitleRole);
}

void PlaylistLoader::clicked(const int &index)
{
	Track->showItems(getSubItems(m_model->item(index)));
}

void PlaylistLoader::actionTriggered(const int &type, const int &index,
									 const QVariant &extra)
{
	Q_UNUSED(extra)

	QList<QStandardItem *> items = getSubItems(m_model->item(index));

	if (type == Play)
		Queue->playItems(items, 0);
	else if (type == AddToQueue)
		Queue->addItems(items);
	else if (type == ShowDetails)
		Details->showItems(items);
	else if (type == Remove)
		deletePlaylist(index);
}

void PlaylistLoader::addPlaylist(const QString &name)
{
	Query->prepare("INSERT INTO playlist VALUES(?);");
	Query->bindValue(0, name);
	Query->exec();

	auto id = Query->lastInsertId();

	QStandardItem *item = new QStandardItem;
	item->setData(id, IDRole);
	item->setData(name, TitleRole);
	m_model->appendRow(item);
}

QList<QStandardItem *> PlaylistLoader::getSubItems(QStandardItem *item)
{
	QList<QStandardItem *> items;
	auto pid = item->data(IDRole);

	Query->prepare(
		"SELECT *, row FROM music, mpjoin "
		"WHERE music.rowid=mpjoin.mid AND mpjoin.pid=?;");  // TODO select
															// mpjoin.row,
															// music. returns
															// false
	Query->bindValue(0, pid);
	qDebug() << Query->exec();

	while (Query->next())
	{
		auto *item = recordToItem(Query->record());
		item->setData(Query->value("row"), RowRole);
		items << item;
	}

	return items;
}

int PlaylistLoader::lastRowInPlaylist(const QVariant &pid)
{
	Query->prepare(
		"SELECT row FROM mpjoin WHERE pid=? ORDER BY row DESC LIMIT 1;");
	Query->bindValue(0, pid);
	qDebug() << Query->exec();

	if (Query->first())
		return Query->value(0).toInt();
	else
		return -1;
}

void PlaylistLoader::deletePlaylist(const int &index)
{
	QVariant id = m_model->item(index)->data(IDRole);
	m_model->removeRow(index);

	Query->prepare("DELETE FROM playlist WHERE rowid=?;");
	Query->bindValue(0, id);
	qDebug() << Query->exec();

	Query->prepare("DELETE FROM mpjoin WHERE pid=?;");
	Query->bindValue(0, id);
	qDebug() << Query->exec();
}

void PlaylistLoader::addItem(const int &row, QStandardItem *item)
{
	QVariant itemid = item->data(IDRole);
	QVariant playlistid = m_model->item(row)->data(IDRole);

	int lastRow = lastRowInPlaylist(playlistid);
	++lastRow;

	Query->exec("INSERT INTO mpjoin	VALUES(?, ?, ?);");
	Query->bindValue(0, playlistid);
	Query->bindValue(1, itemid);
	Query->bindValue(2, lastRow);
	qDebug() << Query->exec();
}

void PlaylistLoader::addItems(const int &row, QList<QStandardItem *> &items)
{
	QVariant pid = m_model->item(row)->data(IDRole);
	int lastrow = lastRowInPlaylist(row);

	QVariantList playlistids;
	QVariantList musicids;
	QVariantList rows;

	for (QStandardItem *item : items)
	{
		++lastrow;
		rows.append(lastrow);
		playlistids.append(pid);
		musicids.append(item->data(IDRole));

		delete item;  // TODO nessesary?
	}

	qDebug() << Query->exec("BEGIN TRANSACTION");
	Query->prepare("INSERT INTO mpjoin VALUES(?, ?, ?);");
	Query->bindValue(0, playlistids);
	Query->bindValue(1, musicids);
	Query->bindValue(2, rows);
	qDebug() << Query->execBatch();
	qDebug() << Query->exec("COMMIT;");
}
