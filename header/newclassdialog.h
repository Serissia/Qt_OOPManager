#ifndef NEWCLASSDIALOG_H
#define NEWCLASSDIALOG_H

#include <QDialog>
#include <QSet>

namespace Ui {
	class newClassDialog;
}

class newClassDialog : public QDialog
{
	Q_OBJECT

public:
	explicit newClassDialog(QWidget *parent = nullptr,
							const QSet<int>& dataSet = QSet<int>());
	~newClassDialog();
	//返回编号、类名、基类名、功能、创建日期、作者
	int number();
	QString className();
	QString baseClassName();
	QString function();
	QDate createdDate();
	QString author();

private slots:
	void on_pushButton_2_clicked();//cancel按钮

	void on_pushButton_clicked();

private:
	Ui::newClassDialog *ui;
	QSet<int> m_id;
};

#endif // NEWCLASSDIALOG_H
