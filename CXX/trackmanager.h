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

	virtual void clicked(const int &index);

	virtual void actionTriggered(const int &type, const int &index,
								 const QVariant &extra = QVariant())
	{
	}
};

#endif  // TRACKMANAGER_H
