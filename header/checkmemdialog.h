#ifndef CHECKMEMDIALOG_H
#define CHECKMEMDIALOG_H

#include <QDialog>
#include <QStyledItemDelegate>
#include <QStandardItemModel>
#include <header/readonlydelegate.h>
#include <header/classinfo.h>

namespace Ui {
	class checkMemDialog;
}

class checkMemDialog : public QDialog
{
	Q_OBJECT

public:
	explicit checkMemDialog(QWidget *parent = nullptr,
							const classInfo& classEdit = classInfo());
	~checkMemDialog();

	void showClassMemInfoTable();//展示对应classInfo的所有类成员
	QVector<classMemberInfo>& getMems();

private slots:
	void tableViewUpdate();//在页面上修改后更新

	void on_pushButton_clicked();

	void on_pushButton_2_clicked();

private:
	Ui::checkMemDialog *ui;

	QStyledItemDelegate *defaultDelegate;
	ReadOnlyDelegate *readOnlyDelegate;
	QStandardItemModel *model;
	classInfo m_class;
};

#endif // CHECKMEMDIALOG_H
