#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow) {
	ui->setupUi(this);
	setFixedSize(width(), height());

	view = new FieldView(ui->centralwidget);
	ui->centralwidget->layout()->addWidget(view);

	QGraphicsScene *scene = new QGraphicsScene();
	scene->setSceneRect(0, 0, 400, 400);

	view->setScene(scene);
	view->addBorder();

	infoLabel = new QLabel();
	ui->centralwidget->layout()->addWidget(infoLabel);

	connect(view, SIGNAL(info(QString)), this, SLOT(updateInfo(QString)));
	connect(view, SIGNAL(updateScore(int)), ui->scoreDisplay, SLOT(display(int)));
	connect(ui->startButton, SIGNAL(clicked(bool)), view, SLOT(start()));
	connect(ui->pauseButton, SIGNAL(clicked(bool)), view, SLOT(pause()));
}

MainWindow::~MainWindow() {
	delete ui;
}

void MainWindow::updateInfo(QString str) {
	infoLabel->setText(str);
}
