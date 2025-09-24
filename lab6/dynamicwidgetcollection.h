#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QSlider>
#include <QScrollBar>
#include <QSpinBox>
#include <QMetaObject>
#include <QMetaMethod>
#include <QList>
#include <QMessageBox>
#include <QFrame>
#include <QRandomGenerator>


class DynamicWidgetCollection : public QWidget
{
    Q_OBJECT

public:
    //explicit DynamicWidgetCollection(QWidget* parent = nullptr);
    explicit DynamicWidgetCollection();
    ~DynamicWidgetCollection();

public slots:
    void addRandomWidget();
    void connectAllWidgets();
    void clearWidgets();

private:
    void connectWidgets(QWidget* widget1, QWidget* widget2);
    bool isNumericalType(const QMetaObject* meta);
    bool isLabelType(const QMetaObject* meta);
    void disconnectAllConnections();
    void updateInfoLabel();

    QVBoxLayout* m_widgetsLayout; // layout для размещения добавляемых виджетов
    QLabel* m_infoLabel; // метка для отображения информации о количестве виджетов и соединений
    QList<QWidget*> m_widgets; // коллекция для хранения указателей на все добавленные виджеты
    QList<QMetaObject::Connection> m_connections; // коллекция для хранения всех установленных соединений
    // дисконнектятся сами при деструкторе у объекта; смысл листа только в кол-ве элементов
};