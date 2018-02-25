#include "queueloader.h"

QueueLoader::QueueLoader(QObject *parent) : Loader(parent)
{
	m_player = new QMediaPlayer(this);
	m_playlist = new QMediaPlaylist(this);
	m_model = new QmlModel(this);

	m_player->setPlaylist(m_playlist);

	m_model->addRoles({Add(AlbumRole), Add(AlbumartistRole), Add(GenreRole),
					   Add(YearRole), Add(IDRole), Add(TrackRole),
					   Add(TitleRole), Add(PathRole), Add(ArtworkRole)});
}

void QueueLoader::smartSet(const int &row)
{
	if (!Active->shufflable())
	{
		for (int i = 0; i < m_model->rowCount(); ++i)
		{
			QMediaContent mediaContent(QUrl::fromLocalFile(
				m_model->item(i)->data(PathRole).toString()));
			m_playlist->addMedia(mediaContent);
		}

		m_playlist->setCurrentIndex(row);
		return;
	}

	QList<QStandardItem *> items;
	for (int i = 0; i < m_model->rowCount(); ++i) items << m_model->takeItem(0);

	QStandardItem *currentItem = items[row];
	std::random_shuffle(items.begin(), items.end());

	items.swap(items.indexOf(currentItem), row);

	for (QStandardItem *I : items)
	{
		QMediaContent mediaContent(
			QUrl::fromLocalFile(I->data(PathRole).toString()));
		m_playlist->addMedia(mediaContent);
		m_model->appendRow(I);
	}

	m_playlist->setCurrentIndex(row);
}

void QueueLoader::smartPlay(const int &row)
{
	m_playlist->clear();
	smartSet(row);
	m_player->play();
}

void QueueLoader::smartAdd()
{
	if (!Active->shufflable()) return;

	int currentIndex = m_playlist->currentIndex();

	if (currentIndex < 0)
	{
		smartSet(0);
		return;
	}

	int count = m_model->rowCount() - currentIndex - 1;
	QList<QStandardItem *> items;

	for (int i = 0; i < count; ++i)
		items << m_model->takeItem(currentIndex + 1);

	m_playlist->removeMedia(currentIndex + 1, m_model->rowCount() - 1);

	std::random_shuffle(items.begin(), items.end());

	for (QStandardItem *I : items)
	{
		QMediaContent mediaContent(
			QUrl::fromLocalFile(I->data(PathRole).toString()));
		m_playlist->addMedia(mediaContent);
		m_model->appendRow(I);
	}
}

void QueueLoader::playItems(QList<QStandardItem *> &items, const int &index)
{
	clear();

	if (Active->shufflable())
	{
		QStandardItem *currentItem = items[index];
		std::random_shuffle(items.begin(), items.end());

		items.swap(items.indexOf(currentItem), index);
	}

	for (QStandardItem *I : items)
	{
		QMediaContent mediaContent(
			QUrl::fromLocalFile(I->data(PathRole).toString()));
		m_playlist->addMedia(mediaContent);
		m_model->appendRow(I);
	}

	m_playlist->setCurrentIndex(index);
	m_player->play();
}

void QueueLoader::playRootItem(QStandardItem *item, const int &index)
{
	clear();

	for (int i = 0; i < item->rowCount(); ++i)
		m_model->appendRow(item->child(i)->clone());

	smartSet(index);
	m_player->play();
}

void QueueLoader::addItems(const QList<QStandardItem *> &items)
{
	for (QStandardItem *item : items)
	{
		QMediaContent mediaContent(
			QUrl::fromLocalFile(item->data(PathRole).toString()));
		m_playlist->addMedia(mediaContent);

		m_model->appendRow(item);
	}

	smartAdd();
}

void QueueLoader::addRootItem(QStandardItem *item)
{
	for (int i = 0; i < item->rowCount(); ++i)
	{
		auto I = item->child(i)->clone();

		QMediaContent mediaContent(
			QUrl::fromLocalFile(I->data(PathRole).toString()));
		m_playlist->addMedia(mediaContent);

		m_model->appendRow(I);
	}

	smartAdd();
}

void QueueLoader::addItem(QStandardItem *item)
{
	m_model->appendRow(item->clone());

	QMediaContent mediaContent(
		QUrl::fromLocalFile(item->data(PathRole).toString()));
	m_playlist->addMedia(mediaContent);

	smartAdd();
}

void QueueLoader::clear()
{
	Loader::clear();
	m_playlist->clear();
	m_playlist->setCurrentIndex(-1);
}

void QueueLoader::songPlayed()
{
	int row = m_playlist->currentIndex();
	if (m_playlist->mediaCount() != 0 && row >= 0)
		m_recentLoader->addPlayedItem(m_model->item(row));
}

void QueueLoader::changeActiveRow(const int &row)
{
	if (Active->repeatable() && row < 0)
	{
		m_playlist->setCurrentIndex(0);
		return;
	}

	if (row < 0 || row >= m_model->rowCount())
	{
		Active->setTitleInfo("");
		Active->setAlbumInfo("");
		Active->setArtistInfo("");
		Active->setArtworkInfo("");
	}
	else
	{
		Active->setTitleInfo(m_model->item(row)->data(TitleRole).toString());
		Active->setAlbumInfo(m_model->item(row)->data(AlbumRole).toString());
		Active->setArtistInfo(m_model->item(row)->data(ArtistRole).toString());
		Active->setArtworkInfo(
			m_model->item(row)->data(ArtworkRole).toString());
	}

	Active->setQueueRow(row);
	emit Active->rowChanged(row);
}

QMediaPlayer *QueueLoader::player() const { return m_player; }
QMediaPlaylist *QueueLoader::playlist() const { return m_playlist; }
