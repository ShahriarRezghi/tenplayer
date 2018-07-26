#ifndef ALBUMLOADER_H
#define ALBUMLOADER_H

#include "loader.h"

class AlbumLoader : public Loader
{
	Q_OBJECT

	void deleteAlbum(QStandardItem *item);
	QList<QStandardItem *> getSubItems(QStandardItem *item);

private slots:
	void addItemsToModel(const QList<QStandardItem *> &items);

public:
	explicit AlbumLoader(QObject *parent = nullptr);

public:
	// Loader interface
	void load();

	virtual void clicked(const int &index);

	virtual void actionTriggered(const int &type, const int &index,
								 const QVariant &extra = QVariant());
};

#endif  // ALBUMLOADER_H
