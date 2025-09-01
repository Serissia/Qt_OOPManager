#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <header/projectmanager.h>
#include <QTableView>
#include <header/readonlydelegate.h>
#include <QStyledItemDelegate>
#include <QStandardItemModel>
#include <header/dateeditdelegate.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();
	void showClassInfoTable();//展示所有classInfo

private slots:
	void on_actionOpen_triggered();//打开文件按钮

	void on_actionSave_triggered();//保存文件按钮

	void on_actionNew_triggered();//新建类按钮

	void tableViewUpdate();//在页面上修改后更新

	void onSelectionChanged(const QItemSelection &selected,
							const QItemSelection &deselected);//选中单元格时更新actionMember

	void on_actionMember_triggered();

private:
	Ui::MainWindow *ui;
	projectManager m_InfoManager;

	QTableView *tableView;
	QStyledItemDelegate *defaultDelegate;
	ReadOnlyDelegate *readOnlyDelegate;
	DateEditDelegate *dateEditDelegate;
	QStandardItemModel *model;
};
#endif // MAINWINDOW_H
