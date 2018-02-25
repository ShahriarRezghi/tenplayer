#ifndef RECENTLYPLAYEDLOADER_H
#define RECENTLYPLAYEDLOADER_H

#include "loader.h"

class RecentlyPlayedLoader : public Loader
{
	Q_OBJECT

	QStringList m_playedIds;

	int m_maxRowCount;

	void save();
	void read();

public:
	explicit RecentlyPlayedLoader(QObject *parent = nullptr);

	void addPlayedItem(QStandardItem *I);

	// Loader interface
public:
	void load();
};

#endif  // RECENTLYPLAYEDLOADER_H
