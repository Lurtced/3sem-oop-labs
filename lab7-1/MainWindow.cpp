#include "MainWindow.h"
#include <QToolBar>
#include <QAction>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    widget = new ShapeWidget(this);
    setCentralWidget(widget);

    auto* toolbar = addToolBar("Shapes");
    QAction* rectAct = toolbar->addAction("Rectangle");
    QAction* ellipseAct = toolbar->addAction("Ellipse");
    QAction* triAct = toolbar->addAction("Triangle");
    QAction* delAct = toolbar->addAction("Delete");

    connect(rectAct, &QAction::triggered, this, [this]() {
        widget->addShape(new Rectangle(QRect(50, 50, 100, 60), Qt::yellow));
        });

    connect(ellipseAct, &QAction::triggered, this, [this]() {
        widget->addShape(new Ellipse(QRect(200, 50, 80, 80), Qt::green));
        });

    connect(triAct, &QAction::triggered, this, [this]() {
        widget->addShape(new Triangle(QRect(350, 50, 100, 100), Qt::cyan));
        });

    connect(delAct, &QAction::triggered, this, [this]() {
        widget->removeActiveShape();
        });
}
