#ifndef PROJECTMANAGER_H
#define PROJECTMANAGER_H
#include <header/classinfo.h>
#include <QVector>
#include <QSet>

class projectManager
{
public:
	projectManager();
	virtual ~projectManager();

	void addClass(const classInfo& newClass);//增加classInfo
	bool removeClass(const int id);//按id删除classInfo
	int getNumber()const;
	classInfo* findClassById(const int classId);//按id查找classInfo
	QSet<int>& getAllId();

	bool saveClassToFile(const QString &saveFileName);
	bool readClassFromFile(const QString &readFileName);
private:
	QVector<classInfo> classes;//下辖类
	int m_number;//类总数
	QSet<int> m_id;//所有classInfo的id
};

#endif // PROJECTMANAGER_H
