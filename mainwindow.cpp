#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow) {
	ui->setupUi(this);

	view = new FieldView(ui->centralwidget);
	ui->centralwidget->layout()->addWidget(view);

	QGraphicsScene *scene = new QGraphicsScene();
	scene->setSceneRect(0, 0, 400, 400);

	view->setScene(scene);
	view->addUser();

	// border
	BorderLine *topLine = new BorderLine(scene->sceneRect().topLeft(), scene->sceneRect().topRight(), BorderLine::Top);
	BorderLine *bottomLine = new BorderLine(scene->sceneRect().bottomLeft(), scene->sceneRect().bottomRight(), BorderLine::Bottom);
	BorderLine *leftLine = new BorderLine(scene->sceneRect().topLeft(), scene->sceneRect().bottomLeft(), BorderLine::Left);
	BorderLine *rightLine = new BorderLine(scene->sceneRect().topRight(), scene->sceneRect().bottomRight(), BorderLine::Right);
	scene->addItem(topLine);
	scene->addItem(bottomLine);
	scene->addItem(leftLine);
	scene->addItem(rightLine);
}

MainWindow::~MainWindow() {
	delete ui;
}
