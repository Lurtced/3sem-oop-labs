#include "mainwindow.h"
#include <QGraphicsView>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsPolygonItem>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    auto* view = new QGraphicsView;
    scene = new QGraphicsScene(this);
    view->setScene(scene);

    auto* addRect = new QPushButton("Добавить прямоугольник");
    auto* addEllipse = new QPushButton("Добавить эллипс");
    auto* addTriangle = new QPushButton("Добавить треугольник");

    connect(addRect, &QPushButton::clicked, this, [this]() {
        auto* r = new QGraphicsRectItem(0, 0, 80, 50);
        r->setBrush(Qt::green);
        r->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
        scene->addItem(r);
        });

    connect(addEllipse, &QPushButton::clicked, this, [this]() {
        auto* e = new QGraphicsEllipseItem(0, 0, 80, 80);
        e->setBrush(Qt::yellow);
        e->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
        scene->addItem(e);
        });

    connect(addTriangle, &QPushButton::clicked, this, [this]() {
        QPolygonF poly;
        poly << QPointF(0, 60) << QPointF(40, 0) << QPointF(80, 60);
        auto* t = new QGraphicsPolygonItem(poly);
        t->setBrush(Qt::red);
        t->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
        scene->addItem(t);
        });

    auto* layout = new QVBoxLayout;
    layout->addWidget(view);
    layout->addWidget(addRect);
    layout->addWidget(addEllipse);
    layout->addWidget(addTriangle);

    auto* central = new QWidget;
    central->setLayout(layout);
    setCentralWidget(central);
}
