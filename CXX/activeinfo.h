#ifndef ACTIVEINFO_H
#define ACTIVEINFO_H

#include <QObject>
#include <QVariant>

class ActiveInfo : public QObject
{
	Q_OBJECT

	Q_PROPERTY(int queueRow READ queueRow NOTIFY rowChanged)
	Q_PROPERTY(QString titleInfo READ titleInfo NOTIFY rowChanged)
	Q_PROPERTY(QString albumInfo READ albumInfo NOTIFY rowChanged)
	Q_PROPERTY(QString artistInfo READ artistInfo NOTIFY rowChanged)
	Q_PROPERTY(QString artworkInfo READ artworkInfo NOTIFY rowChanged)
	Q_PROPERTY(qint64 idInfo READ idInfo NOTIFY rowChanged)

	Q_PROPERTY(bool repeatable READ repeatable WRITE setRepeatable NOTIFY
				   repeatableChanged)
	Q_PROPERTY(bool shufflable READ shufflable WRITE setShufflable NOTIFY
				   shufflableChanged)

	int m_queueRow;
	qint64 m_idInfo;
	bool m_repeatable;
	bool m_shufflable;

	QString m_titleInfo;
	QString m_albumInfo;
	QString m_artistInfo;
	QString m_artworkInfo;

public:
	explicit ActiveInfo(QObject *parent = nullptr);

	int queueRow() const;
	qint64 idInfo() const;
	bool repeatable() const;
	bool shufflable() const;

	QString titleInfo() const;
	QString albumInfo() const;
	QString artistInfo() const;
	QString artworkInfo() const;

	void setIdInfo(const qint64 &idInfo);
	void setTitleInfo(const QString &titleInfo);
	void setAlbumInfo(const QString &albumInfo);
	void setArtistInfo(const QString &artistInfo);
	void setArtworkInfo(const QString &artworkInfo);

	void setQueueRow(int queueRow);

public slots:
	void setRepeatable(bool repeatable);
	void setShufflable(bool shufflable);

signals:
	void rowChanged(int queueRow);
	void repeatableChanged(bool repeatable);
	void shufflableChanged(bool shufflable);

	void showMessage(QVariant value);
};

#endif  // ACTIVEINFO_H
