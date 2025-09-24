#include "dynamicwidgetcollection.h"


DynamicWidgetCollection::DynamicWidgetCollection()
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    QHBoxLayout* buttonLayout = new QHBoxLayout();

    QPushButton* addButton = new QPushButton("Add a widget", this);
    connect(addButton, &QPushButton::clicked, this, &DynamicWidgetCollection::addRandomWidget);

    QPushButton* connectButton = new QPushButton("Connect widgets", this);
    connect(connectButton, &QPushButton::clicked, this, &DynamicWidgetCollection::connectAllWidgets);

    QPushButton* clearButton = new QPushButton("Clear", this);
    connect(clearButton, &QPushButton::clicked, this, &DynamicWidgetCollection::clearWidgets);

    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(connectButton);
    buttonLayout->addWidget(clearButton);

    m_widgetsLayout = new QVBoxLayout(); // layout for dynamically added widgets

    m_infoLabel = new QLabel("Collection is empty", this);
    m_infoLabel->setAlignment(Qt::AlignCenter);

    mainLayout->addLayout(buttonLayout);
    mainLayout->addWidget(m_infoLabel);
    mainLayout->addLayout(m_widgetsLayout);

    setWindowTitle("Dynamic widgets collection");
    resize(500, 500);
}

DynamicWidgetCollection::~DynamicWidgetCollection()
{
    clearWidgets();
}

void DynamicWidgetCollection::addRandomWidget()
{
    QWidget* newWidget = nullptr;

    int randomType = QRandomGenerator::global()->bounded(4);

    switch (randomType) {
    case 0:
        newWidget = new QLabel(QString("Label %1").arg(m_widgets.size() + 1), this);
        newWidget->setProperty("alignment", Qt::AlignCenter);
        newWidget->setProperty("frameShape", QFrame::Box);
        break;
    case 1:
        newWidget = new QSlider(Qt::Horizontal, this);
        newWidget->setProperty("minimum", 0);
        newWidget->setProperty("maximum", 100);
        newWidget->setProperty("value", QRandomGenerator::global()->bounded(101));
        break;
    case 2:
        newWidget = new QScrollBar(Qt::Horizontal, this);
        newWidget->setProperty("minimum", 0);
        newWidget->setProperty("maximum", 100);
        newWidget->setProperty("value", QRandomGenerator::global()->bounded(101));
        break;
    case 3:
        newWidget = new QSpinBox(this);
        newWidget->setProperty("minimum", 0);
        newWidget->setProperty("maximum", 100);
        newWidget->setProperty("value", QRandomGenerator::global()->bounded(101));
        break;
    }

    if (!newWidget)
        throw std::runtime_error("Failed to create widget: unknown type or allocation error");

    
    m_widgets.append(newWidget);
    m_widgetsLayout->addWidget(newWidget);
    updateInfoLabel();
}


void DynamicWidgetCollection::connectAllWidgets()
{
    if (m_widgets.size() < 2) {
        QMessageBox::warning(this, "Warning", "At least 2 widgets required for connection.");
        return;
    }

    disconnectAllConnections();

    for (int i = 0; i < m_widgets.size(); ++i) {
        for (int j = i + 1; j < m_widgets.size(); ++j) {
            connectWidgets(m_widgets[i], m_widgets[j]);
        }
    }
    updateInfoLabel();
    QMessageBox::information(this, "Success",
        QString("Connected %1 widgets").arg(m_widgets.size()));
}

void DynamicWidgetCollection::clearWidgets()
{
    disconnectAllConnections();

    for (QWidget* widget : m_widgets) {
        m_widgetsLayout->removeWidget(widget);
        delete widget;
    }
    m_widgets.clear();
    updateInfoLabel();
}

void DynamicWidgetCollection::connectWidgets(QWidget* widget1, QWidget* widget2)
{
    const QMetaObject* meta1 = widget1->metaObject();
    const QMetaObject* meta2 = widget2->metaObject();

    bool isWidget1Numerical = isNumericalType(meta1);
    bool isWidget1Label = isLabelType(meta1);

    bool isWidget2Numerical = isNumericalType(meta2);
    bool isWidget2Label = isLabelType(meta2);

    if (isWidget1Numerical && isWidget2Numerical) {
        QMetaObject::Connection conn1 = QObject::connect(widget1, SIGNAL(valueChanged(int)), widget2, SLOT(setValue(int)));
        QMetaObject::Connection conn2 = QObject::connect(widget2, SIGNAL(valueChanged(int)), widget1, SLOT(setValue(int)));

        if (conn1) m_connections.append(conn1);
        if (conn2) m_connections.append(conn2);
    }

    else if (isWidget1Numerical && isWidget2Label) {
        QMetaObject::Connection conn = QObject::connect(widget1, SIGNAL(valueChanged(int)), widget2, SLOT(setNum(int)));
        if (conn) m_connections.append(conn);

        QVariant value = widget1->property("value");
        if (value.isValid()) {
            widget2->setProperty("text", QString::number(value.toInt()));
        }
    }
    else if (isWidget1Label && isWidget2Numerical) {
        QMetaObject::Connection conn = QObject::connect(widget2, SIGNAL(valueChanged(int)), widget1, SLOT(setNum(int)));
        if (conn) m_connections.append(conn);

        QVariant value = widget2->property("value");
        if (value.isValid()) {
            widget1->setProperty("text", QString::number(value.toInt()));
        }
    }
}

bool DynamicWidgetCollection::isNumericalType(const QMetaObject* meta)
{
    QString className = meta->className();
    return className == "QSlider" || className == "QScrollBar" || className == "QSpinBox";
}

bool DynamicWidgetCollection::isLabelType(const QMetaObject* meta)
{
    return QString(meta->className()) == "QLabel";
}

void DynamicWidgetCollection::disconnectAllConnections()
{
    for (QMetaObject::Connection connection : m_connections) {
        QObject::disconnect(connection);
    }
    m_connections.clear();
}

void DynamicWidgetCollection::updateInfoLabel()
{
    int connectionCount = m_connections.size();
    m_infoLabel->setText(QString("Widgets: %1, Connections: %2").arg(m_widgets.size()).arg(connectionCount));
}
