#include "header/projectmanager.h"
#include <QDebug>
#include <QFile>
#include <QTextCodec>

projectManager::projectManager()
{
	m_number = 0;
	classes.clear();
	nums.clear();
}

projectManager::~projectManager()
{

}

void projectManager::clear()
{
	m_number = 0;
	classes.clear();
	nums.clear();
}

int projectManager::getNumber() const
{
	return m_number;
}

void projectManager::addClass(const classInfo &newClass)
{
	classes.append(newClass);
	++m_number;
	nums.insert(newClass.getID());
	qDebug() << "Add a Class(ID:" << newClass.getID() << ")\n";
}

bool projectManager::removeClass(const int id)
{
	for(int i = 0; i < classes.size(); ++i)
		if(classes[i].getID() == id)
		{
			classes.removeAt(i);
			--m_number;
			nums.remove(id);
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
	int tot;
	in >> tot;//这里不能用m_number, 因为addClass会++m_number
//	qDebug() << "m_number=" << m_number<<endl;
	classInfo tmpClass;
	for(int i = 1; i <= tot; ++i)
	{
//		qDebug() << i <<endl;
		tmpClass.clear();//一定要清空
		tmpClass.readClass(in);
		addClass(tmpClass);
	}

	file.close();
	qDebug() << readFileName << endl;
	return true;
}

QSet<int>& projectManager::getAllId()
{
	return nums;
}

classInfo& projectManager::getClassInfoByRow(const int row)
{
	return classes[row];
}
