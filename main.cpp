#include <QApplication>
#include <QPushButton>
#include <QPixmap>
#include <QPainter>
#include <QPaintEvent>
#include <iostream>

class ImageButton : public QPushButton {
    Q_OBJECT // макрос который нужен в любом классе наследнике Qt
public:
    ImageButton() = default;
    ImageButton(QWidget *parent);
    // конструктор в качестве аргумента указатель на qwijet позволяет встраивать его в пэрэнт
    // позволяет выстраивать сложные иерархии виджетов внутри окон которые будут разрушаться после закрытия окна
    void paintEvent(QPaintEvent *e) override; // переопределяем метод родительского класса
    QSize sizeHint() const override; // тоже переопределение касается и других классов
    QSize minimumSizeHint() const override;
    void keyPressEvent(QKeyEvent *e) override;
public slots:
    void setUp();  // слоты для действия кнопка нажата и не нажата
    void setDown();
private:
    // объявляем три картинки по имени соответственно
    QPixmap mCurrentButtonPixmap(); // то как на данный момент выглядит кнопка
    QPixmap mButtonDownPixmap();  // в нажатом состоянии
    QPixmap mButtonUpPixmap();  // не в нажатом состоянии
    bool isDown = false; // флаг положения кнопки
};

ImageButton::ImageButton(QWidget *parent) {
    setParent(parent); // передаем родителя он нам больше не потребуется
    setToolTip("Стоп");
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    // приаязка фоточек к переменным
    mButtonUpPixmap() = QPixmap("C:\\Users\\serge\\CLionProjects\\36.2_Abstract_Qt\\UpButton.PNG");
    mButtonDownPixmap() = QPixmap("C:\\Users\\serge\\CLionProjects\\36.2_Abstract_Qt\\DownButton.PNG");
    mCurrentButtonPixmap() = mButtonUpPixmap();
    setGeometry(mCurrentButtonPixmap().rect()); // размеры соответствуют фоточкам
    // выставляем звук кликанья
    connect(this, &QPushButton::clicked, this, &ImageButton::setDown);
    // this в данном случае указывает кто будет получателем данного события
}
// рисуем нашу кнопку
void ImageButton::paintEvent(QPaintEvent *e) {
    QPainter p(this);
    p.drawPixmap(e->rect(), mCurrentButtonPixmap());
}

QSize ImageButton::sizeHint() const {
    return QSize(100, 100);  // размер нашего виджета
}

QSize ImageButton::minimumSizeHint() const {
    return sizeHint();
}

void ImageButton::keyPressEvent(QKeyEvent *e) {
    setDown();  // как кнопка реагирует на нажатие
}

void ImageButton::setDown() {
    mCurrentButtonPixmap() = mButtonDownPixmap();  // при нажатии перересовываем кнопку
    update();  // без update Qt не будет знать что что то изменилось
}

void ImageButton::setUp() {  // похожим образом выглядит метод setUp
    mCurrentButtonPixmap() = mButtonUpPixmap();
    update();
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    ImageButton redButton(nullptr); // наша кнопка будет являтся окном приложения
    redButton.setFixedSize(100, 100); // изначальный размер кнопки
    redButton.move(1000, 400);  // перемещаем кнопку ближе к центру экрана
    // проверяем отклик от программы
    QObject::connect(&redButton, &QPushButton::clicked, [](){std::cout << "clicked";});
    redButton.show();
    return QApplication::exec();
    #include <main.moc>
}