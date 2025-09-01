#ifndef NEWMEMBERDIALOG_H
#define NEWMEMBERDIALOG_H

#include <QDialog>
#include <QSet>

namespace Ui {
	class newmemberdialog;
}

class newmemberdialog : public QDialog
{
	Q_OBJECT

public:
	explicit newmemberdialog(QWidget *parent = nullptr,
							 const QSet<int>& dataSet = QSet<int>());
	~newmemberdialog();

	int Number();
	QString Name();
	QString MemType();
	int Size();
	QString DataType();
	QString Acc();

private slots:
	void on_lineMem_activated(int index);

	void on_pushButton_2_clicked();

	void on_pushButton_clicked();

private:
	Ui::newmemberdialog *ui;
	QSet<int> m_id;
};

#endif // NEWMEMBERDIALOG_H
