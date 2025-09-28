#pragma once
#include <QMainWindow>
#include <QGraphicsScene>
#include <QPushButton>
#include <QGraphicsView>
#include <QVBoxLayout>

class MainWindow : public QMainWindow {
    Q_OBJECT
        QGraphicsScene* scene;
public:
    MainWindow(QWidget* parent = nullptr);
};
