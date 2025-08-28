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

void classMemberInfo::saveClassMember(QTextStream &outStream)
{
	outStream << m_id <<' '<< m_name <<' '<< m_memberType <<' '
			  << m_size <<' '<< m_dataType <<' '<< m_access <<endl;
}

void classMemberInfo::readClassMember(QTextStream &inStream)
{
	inStream >> m_id >> m_name >> m_memberType >> m_size >> m_dataType >> m_access;
}
