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
任务1：Done!
修改读写文件系列函数，加上“&”作为默认占位

任务2：Done!
重写tableView的单元格，使得用户输入一定合法

任务3：
实现actionFind功能

任务4：
修改ui文件
*/
