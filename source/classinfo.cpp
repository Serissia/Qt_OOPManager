#include "header/classinfo.h"
#include <QDebug>

classInfo::classInfo()
{
	nums.clear();
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
	nums = classTemp.nums;
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
	nums = classTemp.nums;
	return *this;
}

int classInfo::getID() const
{
	return m_id;
}

int classInfo::getNum() const
{
	return members.size();
}

int classInfo::getSize() const
{
	int sum = 0;
	for(auto i:members)
		sum += i.getSize();
	return sum;
}

QSet<int>& classInfo::getAllId()
{
	return nums;
}

classMemberInfo& classInfo::getClassMemInfoByRow(const int row)
{
	return members[row];
}

QString classInfo::getAuthor() const
{
	return m_author;
}

QString classInfo::getBaseName() const
{
	return m_baseName;
}

QString classInfo::getDate() const
{
	return m_date.toString("yyyy/M/d");
}

QString classInfo::getFunction() const
{
	return m_function;
}

QString classInfo::getName() const
{
	return m_name;
}

QVector<classMemberInfo>& classInfo::getMems()
{
	return members;
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

void classInfo::setMembers(QVector<classMemberInfo>& newMems)
{
	members = newMems;
	nums.clear();
	for(auto i:newMems)
		nums.insert(i.getID());
}

void classInfo::addMember(const classMemberInfo &m)
{
	members.append(m);
	nums.insert(m.getID());
	qDebug() << "Add a classMember(ID:" << m.getID()
			 << ") in Class(ID:" << getID() << ")\n";
}

bool classInfo::removeMember(const int id)
{
	for(int i = 0; i < members.size(); ++i)
		if(members[i].getID() == id)
		{
			members.removeAt(i);
			nums.remove(id);
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
	outStream << m_id <<"\n"<< (m_name.isEmpty() ? "&" : m_name) <<"\n"
			  << (m_baseName.isEmpty() ? "&" : m_baseName) <<"\n"
			  << (m_function.isEmpty() ? "&" : m_function) <<"\n"
			  << m_date.toString("yyyy/M/d") <<"\n"
			  << (m_author.isEmpty() ? "&" : m_author);
	outStream <<"\n"<< members.size() <<endl;
	for(auto i:members)
		i.saveClassMember(outStream);
}

void classInfo::readClass(QTextStream &inStream)
{
	QString tmpDate, placeHolder = "&";
//	qDebug() << "readClass"<<endl;
	inStream >> m_id >> m_name >> m_baseName >> m_function >> tmpDate >> m_author;
	if(m_name == placeHolder) m_name.clear();
	if(m_baseName == placeHolder) m_baseName.clear();
	if(m_function == placeHolder) m_function.clear();
	if(m_author == placeHolder) m_author.clear();
	m_date = QDate::fromString(tmpDate, "yyyy/M/d");//额外进行转换
	int memSize;
	inStream >> memSize;
//	qDebug() << memSize <<endl;
	classMemberInfo tmpMember;
	for(int i = 1; i <= memSize; ++i)
	{
		tmpMember.readClassMember(inStream);
		members.append(tmpMember);
	}
}

void classInfo::clear()
{
	members.clear();
	nums.clear();
}
