#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow) {
	ui->setupUi(this);

	view = new FieldView(ui->centralwidget);
	ui->centralwidget->layout()->addWidget(view);

	QGraphicsScene *scene = new QGraphicsScene();
	view->setScene(scene);

	user = new User();
	user->setPos(view->width() / 2, view->height() / 2);
	scene->addItem(user);
}

MainWindow::~MainWindow() {
	delete ui;
}
