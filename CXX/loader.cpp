#include "loader.h"

QSqlQuery *Loader::Query = nullptr;
QString Loader::ArtworkPath = QString();

Loader::Loader(QObject *parent) : QObject(parent) { m_model = nullptr; }

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

QString Loader::getArtwork(const QString &album, const QString &albumArtist)
{
	QString A = ArtworkPath + (album + " " + albumArtist)
								  .toUtf8()
								  .toBase64(QByteArray::Base64UrlEncoding);

	return QFile(A).exists() ? A : "";
}
