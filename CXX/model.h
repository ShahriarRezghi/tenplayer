#ifndef MODEL_H
#define MODEL_H

#include <QHash>
#include <QStandardItemModel>
#include <initializer_list>
#define Add(N) std::make_pair(N, QmlModel::fixRoleName(#N).toUtf8())

class QmlModel : public QStandardItemModel
{
	QHash<int, QByteArray> m_roles;

public:
	QmlModel(QObject *parent = 0) : QStandardItemModel(parent) {}

	static QString fixRoleName(QString name)
	{
		name = name.toLower();
		if (name.endsWith("role")) name.remove(name.count() - 4, 4);

		name += "Role";
		return name;
	}

	QHash<int, QByteArray> roleNames() const { return m_roles; }

	void addRoles(std::initializer_list<std::pair<int, QByteArray>> list)
	{
		for (const auto &P : list) m_roles[P.first] = P.second;
	}
};

#endif  // MODEL_H
