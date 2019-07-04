#ifndef QUEUELOADER_H
#define QUEUELOADER_H

#include "loader.h"
#include "mediaplayer.h"

#include <QMediaPlaylist>

class QueueLoader : public Loader
{
    Q_OBJECT

    void smartAdd();
    void smartSet(const int& row);
    void smartPlay(const int& row);

    MediaPlayer* m_player;
    QMediaPlaylist* m_playlist;

private slots:
    void songPlayed();
    void changeActiveRow(const int& row);

public:
    explicit QueueLoader(QObject* parent = nullptr);

    QMediaPlayer* player() const;
    QMediaPlaylist* playlist() const;

    void playItems(QList<QStandardItem*>& items, const int& index);
    void playRootItem(QStandardItem* item, const int& index);

    void addItems(const QList<QStandardItem*>& items);
    void addRootItem(QStandardItem* item);

    void addItem(QStandardItem* item);

public:
    void clear();
    void load() {}

    virtual void clicked(const int& index);

    virtual void actionTriggered(const int& type, const int& index,
                                 const QVariant& extra = QVariant());
};

#endif  // QUEUELOADER_H
