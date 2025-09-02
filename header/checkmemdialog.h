#ifndef CHECKMEMDIALOG_H
#define CHECKMEMDIALOG_H

#include <QDialog>
#include <QStyledItemDelegate>
#include <QStandardItemModel>
#include <header/readonlydelegate.h>
#include <header/classinfo.h>
#include <header/spinboxdelegate.h>
#include <header/comboboxdelegate.h>
#include <QItemSelection>

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

	void on_ButtonNew_clicked();

	void on_ButtonRe_clicked();

	void on_ButtonDel_clicked();

	void onSelectionChanged(const QItemSelection &selected,
							const QItemSelection &deselected);

private:
	Ui::checkMemDialog *ui;

	QStyledItemDelegate *defaultDelegate;
	ReadOnlyDelegate *readOnlyDelegate;
	SpinBoxDelegate *spinBoxDelegate;
	ComboBoxDelegate *comboBoxDelegate_Mem, *comboBoxDelegate_Acc;
	QStandardItemModel *model;
	classInfo m_class;
};

#endif // CHECKMEMDIALOG_H
