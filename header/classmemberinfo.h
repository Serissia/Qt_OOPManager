#ifndef CLASSMEMBERINFO_H
#define CLASSMEMBERINFO_H
#include <QString>
#include <QTextStream>

class classMemberInfo
{
public:
	classMemberInfo();
	classMemberInfo(const int id, const QString name, const QString memtype,
					const int size, const QString datatype, const QString access);
	classMemberInfo(const int id, const QString name, const QString memtype,
					const QString datatype, const QString access);
	classMemberInfo(const classMemberInfo& classMemberTemp);
	classMemberInfo& operator=(const classMemberInfo& classMemberTemp);
	virtual ~classMemberInfo();

	void saveClassMember(QTextStream &outStream);
	void readClassMember(QTextStream &inStream);//文件读写classMemberInfo

	int getID()const;
private:
	//类成员信息：成员编号、成员名称、成员类型（数据或函数）、
	//内存字节数（数据成员）、数据类型、可访问性（公有、私有、保护）等
	int		m_id;
	QString m_name;
	QString m_memberType;//具体输入由增加界面管控防止非法
	int		m_size;
	QString m_dataType;
	QString m_access;
};

#endif // CLASSMEMBERINFO_H
