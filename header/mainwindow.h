#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <header/projectmanager.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

private slots:
	void on_actionOpen_triggered();//打开文件按钮

	void on_actionSave_triggered();//保存文件按钮

	void on_actionNew_triggered();//新建类按钮

private:
	Ui::MainWindow *ui;
	projectManager m_InfoManager;
};
#endif // MAINWINDOW_H
