#include "header/projectmanager.h"
#include <QDebug>
#include <QFile>
#include <QTextCodec>

projectManager::projectManager()
{
	m_number = 0;
	classes.clear();
}

projectManager::~projectManager()
{

}

void projectManager::addClass(const classInfo &newClass)
{
	classes.append(newClass);
	++m_number;
	qDebug() << "Add a Class(ID:" << newClass.getID() << ")\n";
}

bool projectManager::removeClass(const int id)
{
	for(int i = 0; i < classes.size(); ++i)
		if(classes[i].getID() == id)
		{
			classes.removeAt(i);
			--m_number;
			qDebug() << "Remove a Class(ID:" << id << ")\n";
			return true;
		}
	return false;
}

classInfo* projectManager::findClassById(const int classId)
{
	for(int i = 0; i < m_number; ++i)
		if(classes[i].getID() == classId)
			return &classes[i];
	return nullptr;
}

bool projectManager::saveClassToFile(const QString &saveFileName)
{
	QFile file(saveFileName);
	if(!file.open(QFile::WriteOnly | QIODevice::Text))//以只写文本形式打开
		return false;//打开失败返回false
	QTextStream out(&file);
	out.setCodec(QTextCodec::codecForName("System"));//显示汉字

	out << m_number << endl;
	if(m_number > 0)//逐个输出classInfo
		for(int i = 0; i < m_number; ++i)
			classes[i].saveClass(out);

	file.close();
	qDebug() << saveFileName << endl;
	return true;
}

bool projectManager::readClassFromFile(const QString &readFileName)
{
	QFile file(readFileName);
	if(!file.exists()) return false;//文件不存在
	if(!file.open(QIODevice::ReadOnly | QIODevice::Text))//以只读文本形式打开
		return false;
	QTextStream in(&file);
	in.setCodec(QTextCodec::codecForName("system"));
	/*初始化*/
	m_number = 0;
	classes.clear();

	in >> m_number;
	classInfo tmpClass;
	if(m_number > 0)
		for(int i = 0; i < m_number; ++i)
		{
			tmpClass.readClass(in);
			classes.append(tmpClass);
		}

	file.close();
	qDebug() << readFileName << endl;
	return true;
}
