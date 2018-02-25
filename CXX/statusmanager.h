#ifndef STATUSMANAGER_H
#define STATUSMANAGER_H

#include <QObject>

class StatusManager : public QObject
{
	Q_OBJECT

	Q_PROPERTY(int top READ top WRITE setTop NOTIFY topChanged)
	Q_PROPERTY(int value READ value WRITE setValue NOTIFY valueChanged)
	Q_PROPERTY(QString file READ file WRITE setFile NOTIFY fileChanged)
	Q_PROPERTY(QString status READ status WRITE setStatus NOTIFY statusChanged)
	Q_PROPERTY(bool loading READ loading WRITE setLoading NOTIFY loadingChanged)

	Q_PROPERTY(bool refreshing READ refreshing WRITE setRefreshing NOTIFY
				   refreshingChanged)

	Q_PROPERTY(bool needsRefresh READ needsRefresh WRITE setNeedsRefresh NOTIFY
				   needsRefreshChanged)

	int m_top;
	int m_value;
	QString m_file;
	QString m_status;
	bool m_loading;
	bool m_refreshing;
	bool m_needsRefresh;

public:
	explicit StatusManager(QObject *parent = nullptr);

	int top() const;
	int value() const;
	QString file() const;
	QString status() const;
	bool loading() const;
	bool refreshing() const;
	bool needsRefresh() const;

signals:

	void topChanged(int top);
	void valueChanged(int value);
	void fileChanged(QString file);
	void statusChanged(QString status);
	void loadingChanged(bool loading);
	void refreshingChanged(bool refreshing);
	void needsRefreshChanged(bool needsRefresh);

public slots:
	void setTop(int top);
	void setValue(int value);
	void setFile(QString file);
	void setStatus(QString status);
	void setLoading(bool loading);
	void setRefreshing(bool refreshing);
	void setNeedsRefresh(bool needsRefresh);
};

#endif  // STATUSMANAGER_H
