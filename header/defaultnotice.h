#ifndef DEFAULTNOTICE_H
#define DEFAULTNOTICE_H

#include <QDialog>

namespace Ui {
	class DefaultNotice;
}

class DefaultNotice : public QDialog
{
	Q_OBJECT

public:
	explicit DefaultNotice(QWidget *parent = nullptr);
	~DefaultNotice();

	void setContent(QString content);

private:
	Ui::DefaultNotice *ui;
};

#endif // DEFAULTNOTICE_H
