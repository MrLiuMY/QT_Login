#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	ui->stackedWidget_4->setCurrentIndex(0);
	ui->stackedWidget_8->setCurrentIndex(1);
	waitingcount1 = 0;
	waitingcount2 = 0;
	timer1 = new QTimer(this);//定义一个定时器
	timer1->setInterval(200);//设置定时周期为300ms
	connect(timer1, SIGNAL(timeout()), this, SLOT(waitingshow()));

	insert_sql = "insert into user values(?,?,?,?,?,?,?,?,?)";    //插入数据

	select_all_sql = "select * from user";

	labshow[0] = ui->label_654;
	labshow[1] = ui->label_668;
	labshow[2] = ui->label_669;
	labshow[3] = ui->label_670;
	labshow[4] = ui->label_671;
	ui->label_654->hide();
	ui->label_668->hide();
	ui->label_669->hide();
	ui->label_670->hide();
	ui->label_671->hide();
}

MainWindow::~MainWindow()
{
	QSqlDatabase database;
	database.close();
	if (!database.open()) { qDebug() << "close"; }
	delete ui;

}

void MainWindow::on_userinbtn_clicked()
{
	QSqlQuery query;
	bool tttt = false;
	if (!(ui->usernamelineEdit1->text().isEmpty()))

	{

		query.exec("select id from user");
		while (query.next())
		{
			qDebug() << "22355";
			QString uid = query.value("id").toString();
			if ((ui->usernamelineEdit1->text()) == uid)
			{
				tttt = true;

				query.exec(QString("select image from user where id='%1'").arg(ui->usernamelineEdit1->text()));
				query.next();

				QPixmap photo;
				photo.loadFromData(query.value(0).toByteArray(), "JPG");//从数据库读出图片为二进制数据，图片格式为JPG，

				ui->label_566->setPixmap(photo);
				ui->label_566->setScaledContents(true);

				if (!(ui->userpasswordlineEdit1->text().isEmpty()))//验证密码

				{

					query.exec(QString("select password from user where id='%1'").arg(ui->usernamelineEdit1->text()));
					query.next();

					QString pwd = query.value(0).toString();
					if (ui->userpasswordlineEdit1->text() == pwd)//密码正确
					{
						ui->stackedWidget_8->setCurrentIndex(0);
						timer1->start();
					}
					else//密码错误
					{
						QString s = QStringLiteral("密码错误！请重新输入或者找回密码");//密码错误！请重新输入或者找回密码
						errorinfo(s);
					}
				}
			}

		}
		if (tttt == false)
		{
			QString s = QStringLiteral("用户名不存在！请重新输入或者新注册账号");//用户名不存在！请重新输入或者新注册账号";

			errorinfo(s);
		}
	}


	if ((ui->usernamelineEdit1->text().isEmpty()) || (ui->userpasswordlineEdit1->text().isEmpty()))//用户名和密码为空
	{

		QString s = QStringLiteral("用户名或密码不能为空！请重新输入");//用户名或密码不能为空！请重新输入

		errorinfo(s);
	}
}

void MainWindow::on_changepasswordbtn_clicked()
{
	ui->stackedWidget_4->setCurrentIndex(3);

}

void MainWindow::on_forgetpasswordbtn_clicked()
{
	ui->stackedWidget_4->setCurrentIndex(2);
	ui->stackedWidget_6->setCurrentIndex(2);
	ui->stackedWidget_9->setCurrentIndex(1);
}

void MainWindow::on_creatuserbtn_clicked()
{
	ui->stackedWidget_4->setCurrentIndex(1);
}

void MainWindow::on_adduserbtn_clicked()
{
	QSqlQuery my_query;
	bool tt1, tt2, tt3, tt4, tt5, tt6, tt7;
	tt1 = true;
	tt2 = true;
	tt3 = true;
	tt4 = true;
	tt5 = true;
	tt6 = true;
	tt7 = true;
	bool tttt = false;
	if (ui->usernamelineEdit2->text().isEmpty())
	{
		QString s = QStringLiteral("用户名不能为空！请重新输入");//用户名不能为空！请重新输入

		errorinfo(s);
		ui->usernamelineEdit2->setFocus();
		tt1 = false;
		return;
	}

	if (ui->userpasswordlineEdit2->text().isEmpty())
	{
		QString s = QStringLiteral("密码不能为空！请重新输入");//密码不能为空！请重新输入

		errorinfo(s);
		ui->userpasswordlineEdit2->setFocus();
		tt2 = false;
		return;
	}

	if (ui->usercheckpasswordlineEdit->text().isEmpty())
	{
		QString s = QStringLiteral("创建账号失败，请重试！");//确认密码不能为空！请重新输入

		errorinfo(s);
		ui->usercheckpasswordlineEdit->setFocus();
		tt3 = false;
		return;
	}
	if (ui->passwordquestionlineEdit1->text().isEmpty())
	{
		QString s = QStringLiteral("密保问题1答案不能为空！请重新输入");//密保问题1答案不能为空！请重新输入

		errorinfo(s);
		ui->passwordquestionlineEdit1->setFocus();
		tt4 = false;
		return;
	}

	if (ui->passwordquestionlineEdit2->text().isEmpty())
	{
		QString s = QStringLiteral("密保问题2答案不能为空！请重新输入");//密保问题2答案不能为空！请重新输入

		errorinfo(s);
		ui->passwordquestionlineEdit2->setFocus();
		tt5 = false;
		return;
	}

	if (ui->passwordquestionlineEdit3->text().isEmpty())
	{
		QString s = QStringLiteral("密保问题3答案不能为空！请重新输入");//密保问题3答案不能为空！请重新输入

		errorinfo(s);
		ui->passwordquestionlineEdit3->setFocus();
		tt6 = false;
		return;
	}

	if (ui->userpasswordlineEdit2->text() != ui->usercheckpasswordlineEdit->text())
	{
		QString s = QStringLiteral("两次输入的密码不一致！请重新输入！");//两次输入的密码不一致！请重新输入！

		errorinfo(s);
		ui->usercheckpasswordlineEdit->setFocus();
		tt7 = false;
		return;
	}

	if (tt1 && tt2 && tt3 && tt4 && tt5 && tt6 && tt7)
	{
		my_query.exec("select id from user");
		while (my_query.next())
		{
			QString uid = my_query.value("id").toString();
			if ((ui->usernamelineEdit2->text()) == uid)//用户名已存在。请重新输入
			{
				tttt = true;
				QString s = QStringLiteral("用户名已存在，请重新输入！");//创建账号失败，请重试！
				errorinfo(s);
				return;
			}
		}

		if (tttt == false) {
			my_query.prepare(insert_sql);
			my_query.addBindValue(ui->usernamelineEdit2->text());
			my_query.addBindValue(ui->userpasswordlineEdit2->text());
			QVariant var(userimagedata);
			my_query.addBindValue(var);
			my_query.addBindValue(ui->passwordquestioncomboBox1->currentText());
			my_query.addBindValue(ui->passwordquestioncomboBox2->currentText());
			my_query.addBindValue(ui->passwordquestioncomboBox3->currentText());
			my_query.addBindValue(ui->passwordquestionlineEdit1->text());
			my_query.addBindValue(ui->passwordquestionlineEdit2->text());
			my_query.addBindValue(ui->passwordquestionlineEdit3->text());



			if (!my_query.exec())

			{
				QString s = QStringLiteral("创建账号失败，请重试！");//创建账号失败，请重试！

				errorinfo(s);
				return;

			}
			else
			{
				QString s = QStringLiteral("创建账号成功，您可以使用新账号登录！");//创建账号成功，您可以使用新账号登录！

				errorinfo(s);

			}

		}


	}
}

void MainWindow::on_loginusenewbtn_clicked()
{
	ui->stackedWidget_4->setCurrentIndex(0);
}

void MainWindow::on_surebtn_clicked()
{
	bool tttt = false;
	QSqlQuery my_query;

	if (!(ui->usernamelineEdit4->text().isEmpty()))
	{

		my_query.exec("select id from user");
		while (my_query.next())
		{
			QString uid = my_query.value("id").toString();
			if ((ui->usernamelineEdit4->text()) == uid)
			{
				tttt = true;
			}
		}
		if (tttt == true)
		{
			my_query.exec(QString("select passwordquestionid1 from user where id='%1'").arg(ui->usernamelineEdit4->text()));
			my_query.next();
			ui->label_666->setText(my_query.value(0).toString());
			my_query.exec(QString("select passwordquestionid2 from user where id='%1'").arg(ui->usernamelineEdit4->text()));
			my_query.next();
			ui->label_667->setText(my_query.value(0).toString());
			my_query.exec(QString("select passwordquestionid3 from user where id='%1'").arg(ui->usernamelineEdit4->text()));
			my_query.next();
			ui->label_665->setText(my_query.value(0).toString());
			ui->stackedWidget_9->setCurrentIndex(0);
		}
		else//用户名不存在存在，错误
		{
			QString s = QStringLiteral("用户名不存在！请重新输入或者新注册账号");//用户名不存在！请重新输入或者新注册账号

			errorinfo(s);
			ui->usernamelineEdit4->clear();

		}
	}


	if (ui->usernamelineEdit4->text().isEmpty())
	{

		QString s = QStringLiteral("用户名不能为空！请重新输入");//用户名不能为空！请重新输入

		errorinfo(s);
	}

}

void MainWindow::on_findpwdbtn_clicked()
{
	QString pwd1, pwd2, pwd3, pwd4;

	QSqlQuery my_query;
	if ((ui->passwordquestionlineEdit1_2->text().isEmpty()) || (ui->passwordquestionlineEdit2_2->text().isEmpty()) || (ui->passwordquestionlineEdit3_2->text().isEmpty()))
	{
		QString s = QStringLiteral("密保答案不能为空！请重新输入");//密保答案不能为空！请重新输入
		errorinfo(s);
	}
	else
	{

		my_query.exec(QString("select passwordanswer1 from user where passwordquestionid1='%1'").arg(ui->label_666->text()));
		my_query.next();
		pwd1 = my_query.value(0).toString();
		//           ui->label_666->setText(my_query.value(0).toString());
		my_query.exec(QString("select passwordanswer2 from user where passwordquestionid2='%1'").arg(ui->label_667->text()));
		my_query.next();
		pwd2 = my_query.value(0).toString();
		//           ui->label_667->setText(my_query.value(0).toString());
		my_query.exec(QString("select passwordanswer3 from user where passwordquestionid3='%1'").arg(ui->label_665->text()));
		my_query.next();
		pwd3 = my_query.value(0).toString();
		my_query.exec(QString("select password  from user where id='%1'").arg(ui->usernamelineEdit4->text()));
		my_query.next();
		pwd4 = my_query.value(0).toString();
		//           ui->label_665->setText(my_query.value(0).toString());
		if ((ui->passwordquestionlineEdit1_2->text() == pwd1) && (ui->passwordquestionlineEdit2_2->text() == pwd2) && (ui->passwordquestionlineEdit3_2->text() == pwd3))
		{
			ui->stackedWidget_6->setCurrentIndex(0);
			ui->label_644->setText(pwd4);
		}

		else
		{
			ui->stackedWidget_6->setCurrentIndex(1);
		}


	}

}

void MainWindow::on_backloginbtn_clicked()
{
	ui->stackedWidget_4->setCurrentIndex(0);
	ui->stackedWidget_6->setCurrentIndex(2);
	ui->stackedWidget_9->setCurrentIndex(1);
}

void MainWindow::on_storepasswordbtn_clicked()
{
	QSqlQuery my_query;
	bool tt1, tt2, tt3, tt4, tt5;
	tt1 = true;
	tt2 = true;
	tt3 = true;
	tt4 = true;
	tt5 = true;

	if (ui->usernamelineEdit3->text().isEmpty())
	{
		QString s = QStringLiteral("用户名不能为空！请重新输入");//用户名不能为空！请重新输入

		errorinfo(s);
		ui->usernamelineEdit3->setFocus();
		tt1 = false;
		return;

	}

	if (ui->useroldpasswordlineEdit->text().isEmpty())
	{
		QString s = QStringLiteral("旧密码不能为空！请重新输入");//旧密码不能为空！请重新输入

		errorinfo(s);
		ui->useroldpasswordlineEdit->setFocus();
		tt2 = false;
		return;
	}

	if (ui->usernewpasswordlineEdit->text().isEmpty())
	{
		QString s = QStringLiteral("新密码不能为空！请重新输入");

		errorinfo(s);
		ui->usernewpasswordlineEdit->setFocus();
		tt3 = false;
		return;
	}
	if (ui->usernewcheckpasswordlineEdit->text().isEmpty())
	{
		QString s = QStringLiteral("确认密码不能为空！请重新输入");//确认密码不能为空！请重新输入

		errorinfo(s);
		ui->usernewcheckpasswordlineEdit->setFocus();
		tt4 = false;
		return;
	}



	if (ui->usernewpasswordlineEdit->text() != ui->usernewcheckpasswordlineEdit->text())
	{
		QString s = QStringLiteral("两次输入的密码不一致！请重新输入！");//两次输入的密码不一致！请重新输入！

		errorinfo(s);
		ui->usernewcheckpasswordlineEdit->setFocus();
		tt5 = false;
		return;
	}


	if (tt1 && tt2 && tt3 && tt4 && tt5)

	{
		my_query.exec(QString("select password  from user where id='%1'").arg(ui->usernamelineEdit3->text()));
		my_query.next();
		if (ui->useroldpasswordlineEdit->text() == my_query.value(0).toString())//密码验证正确
		{
			if (ui->usernewpasswordlineEdit->text() != ui->useroldpasswordlineEdit->text())//新密码与旧密码不同
			{
				if (ui->usernewcheckpasswordlineEdit->text() == ui->usernewpasswordlineEdit->text())//两次输入的新密码一致
				{
					my_query.exec(QString("update user set password='%1' where id='%2'").arg(ui->usernewpasswordlineEdit->text()).arg(ui->usernamelineEdit3->text()));

					if (!my_query.exec())

					{
						QString s = QStringLiteral("保存新密码失败，请重试！");//保存新密码失败，请重试！

						errorinfo(s);
					}
					else
					{
						QString s = QStringLiteral("保存新密码成功，您可以使用新密码登录！");//保存新密码成功，您可以使用新密码登录！

						errorinfo(s);
					}
				}
				else//两次输入的新密码不一致
				{
					QString s = QStringLiteral("两次输入的密码不一致！请重新输入！");//两次输入的密码不一致！请重新输入！

					errorinfo(s);
					return;
				}

			}
			else//新密码与旧密码同
			{
				QString s = QStringLiteral("新密码不能和旧密码一样！请重新输入！");//新密码不能和旧密码一样！请重新输入！

				errorinfo(s);
				return;
			}

		}
		else
		{
			QString s = QStringLiteral("旧密码不正确，请重试或者找回密码！");//旧密码不正确，请重试或者找回密码！

			errorinfo(s);
			return;
		}



	}

}

void MainWindow::on_cancelchangepasswordbtn_clicked()
{
	ui->usernamelineEdit3->clear();
	ui->useroldpasswordlineEdit->clear();
	ui->usernewpasswordlineEdit->clear();
	ui->usernewcheckpasswordlineEdit->clear();
}

void MainWindow::on_backloginbtn2_clicked()
{
	ui->stackedWidget_4->setCurrentIndex(0);
}

void MainWindow::on_addiconbtn_clicked()
{
	//imagePath的获得方法可以这样写：

	QString imagePath = QFileDialog::getOpenFileName(this, tr("Open File"), "/home", tr("Images (*.jpg)"));

	imagePath.replace("\\", "/");  //转换路径格式,imagePath是图片文件的路径，我这里用的是绝对路径



	QFile* file = new QFile(imagePath); //file为二进制数据文件名

	file->open(QIODevice::ReadOnly);

	userimagedata = file->readAll();

	file->close();
	QPixmap photo;
	photo.loadFromData(userimagedata, "JPG");//从数据库读出图片为二进制数据，图片格式为JPG，
	ui->usericonlab->setPixmap(photo);
	ui->usericonlab->setScaledContents(true);


}
void MainWindow::errorinfo(QString errorinfo)
{
	QMessageBox mb;
	QString s;
	s = errorinfo;
	mb.setText(s);
	mb.exec();
}

void MainWindow::waitingshow()
{
	if (waitingcount1 == 5)
	{
		waitingcount1 = 0;
		for (int i = 0; i < 5; i++) { labshow[i]->hide(); }
		waitingcount1 = 0;
		waitingcount2++;
		if (waitingcount2 > 2)
		{
			waitingcount2 = 0;
			waitingcount1 = 0;
			ui->stackedWidget_4->setCurrentIndex(4);
			timer1->stop();



			for (int j = 0; j < 5; j++)
			{
				labshow[j]->hide();
			}

		}
	}

	labshow[waitingcount1]->show();
	waitingcount1 = waitingcount1 + 1;

}

void MainWindow::on_usernamelineEdit1_textChanged(const QString& arg1)
{
	QSqlQuery query;
	query.exec("select id from user");
	while (query.next())
	{
		QString uid = query.value("id").toString();
		if ((ui->usernamelineEdit1->text()) == uid)
		{


			query.exec(QString("select image from user where id='%1'").arg(ui->usernamelineEdit1->text()));
			query.next();
			QPixmap photo;
			photo.loadFromData(query.value(0).toByteArray(), "JPG");//从数据库读出图片为二进制数据，图片格式为JPG，
			ui->label_566->setPixmap(photo);
			ui->label_566->setScaledContents(true);
		}
	}
}
