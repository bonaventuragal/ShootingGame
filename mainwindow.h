#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "fieldview.h"
#include "user.h"
#include "borderline.h"
#include <QMainWindow>
#include <QLayout>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

public slots:
	void updateInfo(QString str);

private:
	Ui::MainWindow *ui;
	FieldView *view;
	User *user;
	QLabel *infoLabel;

};
#endif // MAINWINDOW_H
