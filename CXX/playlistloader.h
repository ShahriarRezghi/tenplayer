#ifndef PLAYLISTLOADER_H
#define PLAYLISTLOADER_H

#include "loader.h"

class PlaylistLoader : public Loader
{
	Q_OBJECT

	QList<QStandardItem *> getSubItems(QStandardItem *item);

	int lastRowInPlaylist(const QVariant &pid);
	void deletePlaylist(const int &index);

public:
	explicit PlaylistLoader(QObject *parent = nullptr);

	void addPlaylist(const QString &name);
	void addItem(const int &row, QStandardItem *item);
	void addItems(const int &row, QList<QStandardItem *> &items);

	// Loader interface
public:
	void load();

	virtual void clicked(const int &index) {}

	virtual void actionTriggered(const int &type, const int &index,
								 const QVariant &extra = QVariant())
	{
	}
};

#endif  // PLAYLISTLOADER_H
