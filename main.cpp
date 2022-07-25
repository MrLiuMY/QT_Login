#include "mainwindow.h"
#include <QApplication>
#include <QApplication>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlDriver>
#include <QSql>


int main(int argc, char* argv[])
{
	QApplication::addLibraryPath("./plugins");
	QSqlDatabase database;
	database = QSqlDatabase::addDatabase("QSQLITE");
	database.setDatabaseName("usersystem.db");//设置文件名

	if (!database.open()) { return false; }
	if (database.open()) { qDebug() << "open"; }

	QSqlQuery my_query;
	QString create_sql = "create table user (id  int primary key,password varchar ,image varchar,passwordquestionid1 varchar  ,passwordquestionid2 varchar ,passwordquestionid3 varchar ,passwordanswer1 varchar ,passwordanswer2 varchar ,passwordanswer3 varchar)"; //创建用户数据表,表名user,
	my_query.prepare(create_sql); //创建表
	my_query.exec();

	if (!my_query.exec()) //查看创建表是否成功

	{
		qDebug() << QObject::tr("Table Create failed");

	}
	else
	{
		qDebug() << "Table Created";
		return true;
	}
	QApplication a(argc, argv);
	MainWindow w;
	w.show();

	return a.exec();
}
