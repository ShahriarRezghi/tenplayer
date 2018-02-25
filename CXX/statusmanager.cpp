#include "statusmanager.h"

StatusManager::StatusManager(QObject *parent) : QObject(parent)
{
	m_top = 0;
	m_value = 0;
	m_file = "";
	m_status = "";
	m_loading = false;
	m_refreshing = false;
	m_needsRefresh = false;
}

void StatusManager::setTop(int top)
{
	if (m_top == top) return;

	m_top = top;
	emit topChanged(m_top);
}

void StatusManager::setValue(int value)
{
	if (m_value == value) return;

	m_value = value;
	emit valueChanged(m_value);
}

void StatusManager::setFile(QString file)
{
	if (m_file == file) return;

	m_file = file;
	emit fileChanged(m_file);
}

void StatusManager::setStatus(QString status)
{
	if (m_status == status) return;

	m_status = status;
	emit statusChanged(m_status);
}

void StatusManager::setLoading(bool loading)
{
	if (m_loading == loading) return;

	m_loading = loading;
	emit loadingChanged(m_loading);
}

void StatusManager::setRefreshing(bool refreshing)
{
	if (m_refreshing == refreshing) return;

	m_refreshing = refreshing;
	emit refreshingChanged(m_refreshing);
}

void StatusManager::setNeedsRefresh(bool needsRefresh)
{
	if (m_needsRefresh == needsRefresh) return;

	m_needsRefresh = needsRefresh;
	emit needsRefreshChanged(m_needsRefresh);
}

int StatusManager::top() const { return m_top; }
int StatusManager::value() const { return m_value; }
QString StatusManager::file() const { return m_file; }
QString StatusManager::status() const { return m_status; }
bool StatusManager::loading() const { return m_loading; }
bool StatusManager::refreshing() const { return m_refreshing; }
bool StatusManager::needsRefresh() const { return m_needsRefresh; }
