#ifndef INVALIDINPUTDIALOG_H
#define INVALIDINPUTDIALOG_H

#include <QDialog>

namespace Ui {
	class invalidInputDialog;
}

class invalidInputDialog : public QDialog
{
	Q_OBJECT

public:
	explicit invalidInputDialog(QWidget *parent = nullptr,
								const int newid = 0);
	void setId(const int id);
	~invalidInputDialog();
	/*ok按钮通过ui文件绑定到close()*/

private:
	Ui::invalidInputDialog *ui;
	int recId;//推荐id
};

#endif // INVALIDINPUTDIALOG_H
