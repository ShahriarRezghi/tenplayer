#ifndef TRACKMANAGER_H
#define TRACKMANAGER_H

#include "loader.h"

class TrackManager : public Loader
{
	Q_OBJECT
public:
	explicit TrackManager(QObject *parent = nullptr);

	void showItems(const QList<QStandardItem *> &items);

	void sortTracksByRow();
	void savePlaylistTrackRows();

public:
	// Loader interface
	void load() {}
};

#endif  // TRACKMANAGER_H
