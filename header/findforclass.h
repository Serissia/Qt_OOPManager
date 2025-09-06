#ifndef FINDFORCLASS_H
#define FINDFORCLASS_H

#include <QDialog>

namespace Ui {
	class FindForClass;
}

class FindForClass : public QDialog
{
	Q_OBJECT

public:
	explicit FindForClass(QWidget *parent = nullptr);
	~FindForClass();
	int Num();
	QString Name();
	int Chosen();

private slots:
	void on_pushButton_2_clicked();

	void on_pushButton_clicked();

//	void on_groupBox_toggled(bool arg1);

	void on_radioButton_toggled(bool checked);

	void on_radioButton_2_toggled(bool checked);

private:
	Ui::FindForClass *ui;
};

#endif // FINDFORCLASS_H
