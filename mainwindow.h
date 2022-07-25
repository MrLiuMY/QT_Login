#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlDriver>
#include <QSqlRecord>
#include <QDebug>
#include <QTimer>
#include <QFile>
#include <QFileDialog>
#include <QByteArray>
#include <QTextCodec>
#include <QListWidgetItem>      //列表框空间头文件
#include <QFileDialog>          //文件对话框控件
#include <QStringList>          //字符串容器
#include <QDir>                 //目录类头文件
#include <QString>
#include <QMessageBox>
namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget* parent = 0);
	~MainWindow();

private slots:
	void on_userinbtn_clicked();

	void on_changepasswordbtn_clicked();

	void on_forgetpasswordbtn_clicked();

	void on_creatuserbtn_clicked();

	void on_adduserbtn_clicked();

	void on_loginusenewbtn_clicked();

	void on_surebtn_clicked();

	void on_findpwdbtn_clicked();

	void on_backloginbtn_clicked();

	void on_storepasswordbtn_clicked();

	void on_cancelchangepasswordbtn_clicked();

	void on_backloginbtn2_clicked();

	void on_addiconbtn_clicked();

	void errorinfo(QString errorinfo);

	void waitingshow();
	void on_usernamelineEdit1_textChanged(const QString& arg1);

private:
	QTimer* timer1;
	int waitingcount1;
	int waitingcount2;
	QString insert_sql; /*= "insert into user values(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)";    //插入数据*/
	QLabel* labshow[5];
	QString select_all_sql;/* = "select * from user";*/
	QByteArray userimagedata;
	Ui::MainWindow* ui;
};

#endif // MAINWINDOW_H
