#include "header/classinfo.h"
#include <QDebug>

classInfo::classInfo()
{

}

classInfo::~classInfo()
{

}

classInfo::classInfo(const classInfo &classTemp)
{
	m_id = classTemp.m_id;
	m_name = classTemp.m_name;
	m_baseName = classTemp.m_baseName;
	m_function = classTemp.m_function;
	m_date = classTemp.m_date;
	m_author = classTemp.m_author;
	members = classTemp.members;
}

classInfo& classInfo::operator=(const classInfo &classTemp)
{
	m_id = classTemp.m_id;
	m_name = classTemp.m_name;
	m_baseName = classTemp.m_baseName;
	m_function = classTemp.m_function;
	m_date = classTemp.m_date;
	m_author = classTemp.m_author;
	members = classTemp.members;
	return *this;
}

int classInfo::getID() const
{
	return m_id;
}

void classInfo::setId(int id)
{
	m_id = id;
}

void classInfo::setName(QString name)
{
	m_name = name;
}

void classInfo::setBaseName(QString baseName)
{
	m_baseName = baseName;
}

void classInfo::setFunction(QString function)
{
	m_function = function;
}

void classInfo::setDate(QDate date)
{
	m_date = date;
}

void classInfo::setAuthor(QString author)
{
	m_author = author;
}

void classInfo::addMember(const classMemberInfo &m)
{
	members.append(m);
	qDebug() << "Add a classMember(ID:" << m.getID()
			 << ") in Class(ID:" << getID() << ")\n";
}

bool classInfo::removeMember(const int id)
{
	for(int i = 0; i < members.size(); ++i)
		if(members[i].getID() == id)
		{
			members.removeAt(i);
			qDebug() << "Remove a classMember(ID:" << id
					 << ") in Class(ID:" << getID() << ")\n";
			return true;
		}
	return false;//删除失败返回false
}

classMemberInfo* classInfo::findMemberById(const int memberId)
{
	for(int i = 0; i < members.size(); ++i)
		if(members[i].getID() == memberId)
			return &members[i];
	return nullptr;//未找到返回空指针
}

void classInfo::saveClass(QTextStream &outStream)
{
	outStream << m_id <<"\n"<< m_name <<"\n"<< m_baseName <<"\n"
			  << m_function <<"\n"<< m_date.toString("yyyy/MM/dd") <<"\n"<< m_author;
	outStream <<"\n"<< members.size() <<endl;
	for(auto i:members)
		i.saveClassMember(outStream);
}

void classInfo::readClass(QTextStream &inStream)
{
	QString tmpDate;
	inStream >> m_id >> m_name >> m_baseName >> m_function >> tmpDate >> m_author;
	m_date = QDate::fromString(tmpDate, "yyyy/MM/dd");//额外进行转换
	int memSize = 0;
	inStream >> memSize;
	classMemberInfo tmpMember;
	for(int i = 1; i <= memSize; ++i)
	{
		tmpMember.readClassMember(inStream);
		members.append(tmpMember);
	}
}
