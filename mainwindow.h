#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "fieldview.h"
#include "user.h"
#include "bullet.h"
#include "borderline.h"
#include <QMainWindow>
#include <QLayout>

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

private:
	Ui::MainWindow *ui;
	FieldView *view;
	User *user;
};
#endif // MAINWINDOW_H
