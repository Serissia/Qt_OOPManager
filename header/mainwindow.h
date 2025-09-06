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
	void showClassInfoTable(int page);//展示所有classInfo
	void FindClass(QVariant, int);

private slots:
	void on_actionOpen_triggered();//打开文件按钮

	void on_actionSave_triggered();//保存文件按钮

	void on_actionNew_triggered();//新建类按钮

	void tableViewUpdate();//在页面上修改后更新

	void onSelectionChanged(const QItemSelection &selected,
							const QItemSelection &deselected);//选中单元格时更新actionMember

	void onDoubleClicked(const QModelIndex &index);//双击[查看详情]

	void on_actionMember_triggered();

	void on_actionFind_triggered();

	void on_actionDelete_triggered();

	void onPageChanged();

private:
	Ui::MainWindow *ui;
	projectManager m_InfoManager[2];//0负责所有, 1负责搜索过后

	QStyledItemDelegate *defaultDelegate[2];
	ReadOnlyDelegate *readOnlyDelegate[2];
	DateEditDelegate *dateEditDelegate[2];
	QStandardItemModel *model[2];

	QTableView *tableView[2];
	QTabWidget *tabWidget;
};
#endif // MAINWINDOW_H
