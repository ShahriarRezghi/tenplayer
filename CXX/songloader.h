#ifndef SONGLOADER_H
#define SONGLOADER_H

#include "loader.h"

class SongLoader : public Loader
{
    Q_OBJECT

private slots:
    void addItemsToModel(const QList<QStandardItem*>& items);

public:
    explicit SongLoader(QObject* parent = nullptr);

public:
    void load();

    virtual void clicked(const int& index);

    virtual void actionTriggered(const int& type, const int& index,
                                 const QVariant& extra = QVariant());
};

#endif  // SONGLOADER_H
