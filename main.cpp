#include "header/mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	return a.exec();
}
/*
仿照windows环境变量页面的新建、编辑功能
*/
