#include "loader.h"

QSqlQuery *Loader::Query = nullptr;
QString Loader::ArtworkPath = QString();
ActiveInfo *Loader::Active = nullptr;

PathManager *Loader::Path = nullptr;
StatusManager *Loader::Status = nullptr;
DetailsManager *Loader::Details = nullptr;

QueueLoader *Loader::Queue = nullptr;
TrackManager *Loader::Track = nullptr;
PlaylistLoader *Loader::Playlist = nullptr;
RecentlyPlayedLoader *Loader::RecentlyPlayed = nullptr;

Loader::Loader(QObject *parent) : QObject(parent)
{
	m_model = nullptr;
	m_searchModel = nullptr;

	connect(this, &Loader::addItemsToModelFromThread, this,
			&Loader::addItemsToModel);
}

QmlModel *Loader::searchModel() const { return m_searchModel; }

void Loader::addItemsToModel(const QList<QStandardItem *> &items)
{
	clear();
	for (auto item : items) m_model->appendRow(item);
}

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

void Loader::deleteSong(const QVariant &id)
{
	Query->prepare("DELETE FROM music WHERE rowid=?;");
	Query->bindValue(0, id);
	Query->exec();
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

	auto album = record.value("album");
	auto albumArtist = record.value("albumartist");

	item->setData(album, AlbumRole);
	item->setData(albumArtist, AlbumartistRole);

	item->setData(record.value("rowid"), IDRole);
	item->setData(record.value("title"), TitleRole);
	item->setData(record.value("artist"), ArtistRole);
	item->setData(record.value("track"), TrackRole);
	item->setData(record.value("disc"), DiscRole);
	item->setData(record.value("genre"), GenreRole);
	item->setData(record.value("year"), YearRole);
	item->setData(record.value("path"), PathRole);

	item->setData(getArtwork(album.toString(), albumArtist.toString()),
				  ArtworkRole);

	return item;
}

void Loader::sortItemList(std::initializer_list<int> roles,
						  QList<QStandardItem *> &items)
{
	for (auto role : roles)
		std::sort(items.begin(), items.end(),
				  [&role](QStandardItem *I1, QStandardItem *I2) {
					  return I1->data(role) < I2->data(role);
				  });
}

void Loader::sortTrackList(QList<QStandardItem *> &items)
{
	auto comp = [](QStandardItem *I1, QStandardItem *I2) {
		auto disc1 = I1->data(DiscRole).toInt();
		auto disc2 = I2->data(DiscRole).toInt();

		if (disc1 != disc2) return disc1 < disc2;

		auto track1 = I1->data(TrackRole).toInt();
		auto track2 = I2->data(TrackRole).toInt();

		if (!track1 && track2)
			return true;
		else if (track1 && !track2)
			return false;
		else if (track1 && track2)
			return track1 < track2;
		else
		{
			auto title1 = I1->data(TitleRole).toString();
			auto title2 = I2->data(TitleRole).toString();

			return title1 < title2;
		}
	};

	std::sort(items.begin(), items.end(), comp);
}

void Loader::clear()
{
	if (m_model) m_model->clear();
	if (m_searchModel) m_searchModel->clear();
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
