#pragma once
#include "Shape.h"
#include <QWidget>
#include <QVector>
#include <QMouseEvent>

class ShapeWidget : public QWidget {
    Q_OBJECT
        QVector<Shape*> shapes;
    Shape* active = nullptr;
    QPoint lastPos;
public:
    ShapeWidget(QWidget* parent = nullptr) : QWidget(parent) {}

    void addShape(Shape* s) {
        shapes.push_back(s);
        update();
    }

    void removeShape(Shape* s) {
        shapes.removeOne(s);
        delete s;
        update();
    }

protected:
    void paintEvent(QPaintEvent*) override {
        QPainter p(this);
        for (auto s : shapes) s->draw(&p);
    }

    void mousePressEvent(QMouseEvent* e) override {
        for (int i = shapes.size() - 1; i >= 0; --i) {
            if (shapes[i]->contains(e->pos())) {
                active = shapes[i];
                // поднимаем на передний план
                shapes.remove(i);
                shapes.push_back(active);
                lastPos = e->pos();
                update();
                break;
            }
        }
    }

    void mouseMoveEvent(QMouseEvent* e) override {
        if (active) {
            QPoint delta = e->pos() - lastPos;
            active->move(delta.x(), delta.y());
            lastPos = e->pos();
            update();
        }
    }

    void mouseReleaseEvent(QMouseEvent*) override {
        active = nullptr;
    }
};
