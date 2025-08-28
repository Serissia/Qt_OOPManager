#ifndef PROJECTMANAGER_H
#define PROJECTMANAGER_H
#include <header/classinfo.h>
#include <QVector>

class projectManager
{
public:
	projectManager();
	virtual ~projectManager();

	void addClass(const classInfo& newClass);//增加classInfo
	bool removeClass(const int id);//按id删除classInfo
	int getNumber()const;
	classInfo* findClassById(const int classId);//按id查找classInfo

	bool saveClassToFile(const QString &saveFileName);
	bool readClassFromFile(const QString &readFileName);
private:
	QVector<classInfo> classes;//下辖类
	int m_number;
};

#endif // PROJECTMANAGER_H
