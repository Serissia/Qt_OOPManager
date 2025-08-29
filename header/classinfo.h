#ifndef CLASSINFO_H
#define CLASSINFO_H
#include <QString>
#include <QDate>
#include <QVector>
#include <header/classmemberinfo.h>
#include <QTextStream>

class classInfo
{
public:
	classInfo();
	classInfo(const classInfo &classTemp);
	classInfo& operator=(const classInfo &classTemp);
	virtual ~classInfo();

	/*相关private成员读写*/
	int getID()const;
	QString getName()const;
	QString getBaseName()const;
	QString getFunction()const;
	QString getDate()const;
	QString getAuthor()const;
	void setId(int id);
	void setName(QString name);
	void setBaseName(QString baseName);
	void setFunction(QString function);
	void setDate(QDate date);
	void setAuthor(QString author);

	void addMember(const classMemberInfo& m);//增加classMemberInfo
	bool removeMember(const int id);//按id删除classMemberInfo

	classMemberInfo* findMemberById(const int memberId);//按id查找classMemberInfo
	void saveClass(QTextStream &outStream);
	void readClass(QTextStream &inStream);//读写classInfo
private:
	//类信息：编号、类名、基类名、功能、创建日期、作者、类成员数据集
	int		m_id;//唯一
	QString m_name;
	QString m_baseName;
	QString m_function;
	QDate	m_date;
	QString m_author;

	QVector<classMemberInfo> members;//下辖类成员

};

#endif // CLASSINFO_H
