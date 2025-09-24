/*
Установить библиотеку и среду разработки Qt.
Написать графическую программу "Hello World" со следующей функциональностью:
создать свой класс - наследник от QWidget;
создать виджет QLabel с надписью "Hello World", создать QPushButton кнопку выполняющую выход из приложения;
разместить несколько объектов виджетов используюя метод позиционирования setGeometry внутри базового виджета.
В проекте не должны присутствовать лишние заголовочные файлы или файлы форм.
*/

#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QWidget>
#include <QCheckBox>
#include <QSlider>
#include <QRadioButton>
#include <QTextEdit>
#include <QLineEdit>


class MyWidget : public QWidget {
    Q_OBJECT
public:
    explicit MyWidget(QWidget* parent = nullptr) : QWidget(parent) {
        setWindowTitle("Hello World Program");
        setFixedSize(300, 350); // увеличили размер, чтобы всё поместилось

        // QLabel
        QLabel* label = new QLabel("Hello World!", this);
        label->setGeometry(20, 20, 200, 30);
        label->setStyleSheet("font-size: 16pt; font-weight: bold; font-style: italic");

        // QLineEdit
        QLineEdit* edit = new QLineEdit(this);
        edit->setGeometry(20, 70, 260, 30);
        edit->setPlaceholderText("Enter your name...");

        // QCheckBox
        QCheckBox* agree = new QCheckBox("I agree", this);
        agree->setGeometry(20, 120, 150, 20);

        // QSlider
        QSlider* slider = new QSlider(Qt::Horizontal, this);
        slider->setGeometry(20, 150, 260, 30);
        slider->setRange(0, 100);
        slider->setValue(50);

        // QTextEdit
        QTextEdit* textEdit = new QTextEdit(this);
        textEdit->setGeometry(20, 200, 260, 80);
        textEdit->setPlaceholderText("Leave a comment...");

        // QPushButton
        QPushButton* btn = new QPushButton("Exit", this);
        btn->setGeometry(20, 300, 80, 30);
        connect(btn, &QPushButton::clicked, qApp, &QCoreApplication::quit);
    }
};

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    MyWidget w;
    w.show();
    return app.exec();
}


#include "main.moc"