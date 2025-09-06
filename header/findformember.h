#ifndef FINDFORMEMBER_H
#define FINDFORMEMBER_H

#include <QDialog>

namespace Ui {
	class FindForMember;
}

class FindForMember : public QDialog
{
	Q_OBJECT

public:
	explicit FindForMember(QWidget *parent = nullptr);
	~FindForMember();

	int getChosen();
	int Num();
	QString Name();
	QString Acc();
	QString MemType();

private slots:
	void on_pushButton_clicked();

	void on_pushButton_2_clicked();

	void on_radioButton_toggled(bool checked);

	void on_radioButton_2_toggled(bool checked);

	void on_radioButton_3_toggled(bool checked);

	void on_radioButton_4_toggled(bool checked);

private:
	Ui::FindForMember *ui;
};

#endif // FINDFORMEMBER_H
