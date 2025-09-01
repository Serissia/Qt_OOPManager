#include "header/classmemberinfo.h"

classMemberInfo::classMemberInfo()
{
	m_size = -1;
}

classMemberInfo::~classMemberInfo()
{

}

classMemberInfo::classMemberInfo(const int id, const QString name, const QString memtype,
								 const int size, const QString datatype, const QString access)
{
	m_id = id;
	m_name = name;
	m_memberType = memtype;
	m_size = size;
	m_dataType = datatype;
	m_access = access;
}

classMemberInfo::classMemberInfo(const int id, const QString name, const QString memtype,
				const QString datatype, const QString access)
{
	m_id = id;
	m_name = name;
	m_memberType = memtype;
	m_size = -1;
	m_dataType = datatype;
	m_access = access;
}

classMemberInfo::classMemberInfo(const classMemberInfo& classMemberTemp)
{
	m_id = classMemberTemp.m_id;
	m_name = classMemberTemp.m_name;
	m_memberType = classMemberTemp.m_memberType;
	m_size = classMemberTemp.m_size;
	m_dataType = classMemberTemp.m_dataType;
	m_access = classMemberTemp.m_access;
}

classMemberInfo& classMemberInfo::operator=(const classMemberInfo &classMemberTemp)
{
	m_id = classMemberTemp.m_id;
	m_name = classMemberTemp.m_name;
	m_memberType = classMemberTemp.m_memberType;
	m_size = classMemberTemp.m_size;
	m_dataType = classMemberTemp.m_dataType;
	m_access = classMemberTemp.m_access;
	return *this;
}

int classMemberInfo::getID() const
{
	return m_id;
}

QString classMemberInfo::getAcc() const
{
	return m_access;
}

QString classMemberInfo::getDataType() const
{
	return m_dataType;
}

QString classMemberInfo::getMemType() const
{
	return m_memberType;
}

QString classMemberInfo::getName() const
{
	return m_name;
}

int classMemberInfo::getSize() const
{
	return m_size;
}

void classMemberInfo::setAcc(QString acc)
{
	m_access = acc;
}

void classMemberInfo::setDataType(QString dataType)
{
	m_dataType = dataType;
}

void classMemberInfo::setID(int id)
{
	m_id = id;
}

void classMemberInfo::setMemType(QString memType)
{
	m_memberType = memType;
}

void classMemberInfo::setName(QString name)
{
	m_name = name;
}

void classMemberInfo::setSize(int size)
{
	m_size = size;
}

void classMemberInfo::saveClassMember(QTextStream &outStream)
{
	outStream << m_id <<' '<< m_name <<' '<< m_memberType <<' '
			  << m_size <<' '<< m_dataType <<' '<< m_access <<endl;
}

void classMemberInfo::readClassMember(QTextStream &inStream)
{
	inStream >> m_id >> m_name >> m_memberType >> m_size >> m_dataType >> m_access;
}
