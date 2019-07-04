#ifndef ARTISTLOADER_H
#define ARTISTLOADER_H

#include "loader.h"

class ArtistLoader : public Loader
{
    Q_OBJECT

    void deleteArtist(QStandardItem* item);
    QList<QStandardItem*> getSubItems(QStandardItem* item);

private slots:
    void addItemsToModel(const QList<QStandardItem*>& items);

public:
    explicit ArtistLoader(QObject* parent = nullptr);

public:
    void load();

    virtual void clicked(const int& index);

    virtual void actionTriggered(const int& type, const int& index,
                                 const QVariant& extra = QVariant());
};

#endif  // ARTISTLOADER_H
