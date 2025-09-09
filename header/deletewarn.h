#ifndef DELETEWARN_H
#define DELETEWARN_H

#include <QDialog>

namespace Ui {
	class DeleteWarn;
}

class DeleteWarn : public QDialog
{
	Q_OBJECT

public:
	explicit DeleteWarn(QWidget *parent = nullptr);
	~DeleteWarn();

	void setContent(const QString content);

private slots:
	void on_pushButton_clicked();

	void on_pushButton_2_clicked();

private:
	Ui::DeleteWarn *ui;
};

#endif // DELETEWARN_H
