#include "loader.h"

QSqlQuery *Loader::Query = nullptr;
QString Loader::ArtworkPath = QString();
ActiveInfo *Loader::Active = nullptr;

PathManager *Loader::Path = nullptr;
StatusManager *Loader::Status = nullptr;

QueueLoader *Loader::Queue = nullptr;
TrackManager *Loader::Track = nullptr;
RecentlyPlayedLoader *Loader::RecentlyPlayed = nullptr;

Loader::Loader(QObject *parent) : QObject(parent) { m_model = nullptr; }

QmlModel *Loader::searchModel() const { return m_searchModel; }

void Loader::search(const QString &text)
{
	m_searchModel->clear();

	if (text.isEmpty()) return;

	QModelIndexList found =
		m_model->match(m_model->index(0, 0), m_searchRole,
					   QVariant::fromValue(text), -1, Qt::MatchContains);

	for (const QModelIndex &index : found)
	{
		QStandardItem *I = m_model->itemFromIndex(index)->clone();
		I->setData(m_model->itemFromIndex(index)->row(), Qt::UserRole);
		m_searchModel->appendRow(I);
	}
}

void Loader::createSearchModel(int searchRole)
{
	m_searchRole = searchRole;
	m_searchModel = new QmlModel(this);

	m_searchModel->addRoles({Add(AlbumRole), Add(ArtistRole),
							 Add(AlbumartistRole), Add(GenreRole),
							 Add(YearRole), Add(IDRole), Add(TrackRole),
							 Add(TitleRole), Add(PathRole), Add(ArtworkRole)});
}

void Loader::sortModel(int role, bool asc)
{
	if (m_model)
	{
		m_model->setSortRole(role);
		m_model->sort(0, asc ? Qt::AscendingOrder : Qt::DescendingOrder);
	}
}

QStandardItem *Loader::recordToItem(const QSqlRecord &record)
{
	auto *item = new QStandardItem;

	item->setData(record.value("rowid"), IDRole);
	item->setData(record.value("title"), TitleRole);
	item->setData(record.value("album"), AlbumRole);
	item->setData(record.value("artist"), ArtistRole);
	item->setData(record.value("albumartist"), AlbumartistRole);
	item->setData(record.value("track"), TrackRole);
	item->setData(record.value("genre"), GenreRole);
	item->setData(record.value("year"), YearRole);
	item->setData(record.value("path"), PathRole);

	return item;
}

bool Loader::sortItemsByRole(int role, QStandardItem *I1, QStandardItem *I2)
{
	return I1->data(role) < I2->data(role);
}

void Loader::sortItemList(std::initializer_list<int> roles,
						  QList<QStandardItem *> &items)
{
	for (auto role : roles)
		std::sort(items.begin(), items.end(), getCompareFunction(role));
}

std::function<bool(QStandardItem *, QStandardItem *)>
Loader::getCompareFunction(int role)
{
	return [&role](QStandardItem *I1, QStandardItem *I2) {
		return Loader::sortItemsByRole(role, I1, I2);
	};
}

void Loader::clear()
{
	if (m_model) m_model->clear();
}

void Loader::searchClicked(const int &index)
{
	clicked(m_searchModel->item(index)->data(Qt::UserRole).toInt());
}

void Loader::searchActionTriggered(const int &type, const int &index,
								   const QVariant &extra)
{
	actionTriggered(
		type, m_searchModel->item(index)->data(Qt::UserRole).toInt(), extra);
	m_searchModel->removeRow(index);
}

QString Loader::getArtwork(const QString &album, const QString &albumArtist)
{
	QString A = ArtworkPath + (album + " " + albumArtist)
								  .toUtf8()
								  .toBase64(QByteArray::Base64UrlEncoding);

	return QFile(A).exists() ? A : "";
}

QmlModel *Loader::model() const { return m_model; }
