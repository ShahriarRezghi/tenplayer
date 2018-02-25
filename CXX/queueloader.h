#ifndef QUEUELOADER_H
#define QUEUELOADER_H

#include "loader.h"

#include <QMediaPlayer>
#include <QMediaPlaylist>

class QueueLoader : public Loader
{
	Q_OBJECT

	void smartAdd();
	void smartSet(const int &row);
	void smartPlay(const int &row);

	QMediaPlayer *m_player;
	QMediaPlaylist *m_playlist;

private slots:
	void songPlayed();
	void changeActiveRow(const int &row);

public:
	explicit QueueLoader(QObject *parent = nullptr);

	QMediaPlayer *player() const;
	QMediaPlaylist *playlist() const;

	void playItems(QList<QStandardItem *> &items, const int &index);
	void playRootItem(QStandardItem *item, const int &index);

	void addItems(const QList<QStandardItem *> &items);
	void addRootItem(QStandardItem *item);

	void addItem(QStandardItem *item);

	// Loader interface
public:
	void load();
	void clear();
};

#endif  // QUEUELOADER_H
