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
下一个任务：
修改读写文件系列函数，加上“&”作为默认占位

下下个任务：Done!
重写tableView的单元格，使得用户输入一定合法

下下下个任务：
实现actionFind功能
*/
