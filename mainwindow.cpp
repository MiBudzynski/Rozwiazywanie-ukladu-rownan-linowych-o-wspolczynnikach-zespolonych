#include "mainwindow.h"
#include "kod.h"
#include "Interval.h"

#include <QRadioButton>
#include <QVBoxLayout>
#include <QPushButton>
#include <QButtonGroup>
#include <QMessageBox>
#include <QLineEdit>
#include <QDialog>
#include <QLabel>
#include <QRegularExpression>
#include <QTextEdit>

cplxmatrix convertToMatrix(const QString& input)
{
    QStringList rows = input.split('\n');

    int n = rows.size();
    cplxmatrix a(n, cplxvector(n + 1, std::complex<long double>(0, 0)));

    for (int i = 0; i < n; ++i) {
        QStringList rowData = rows[i].split(' ');

        for (int j = 0; j < n + 1; ++j) {
            long double real = rowData[2 * j].toDouble();
            long double imag = rowData[2 * j + 1].toDouble();
            a[i][j] = std::complex<long double>(real, imag);
        }
    }

    return a;
}

QString convertToString(const cplxvector& x) {
    QString result;

    for (const auto& complex : x) {
        result += QString::number(static_cast<long double>(complex.real()), 'e', 16) + " " + QString::number(static_cast<long double>(complex.imag()), 'e', 16) + "\n";
    }

    return result.trimmed();  // Usuwamy końcowy znak nowej linii
}

cplxmatrixp convertToMatrixp1(const QString& input)
{
    QStringList rows = input.split('\n');

    int n = rows.size();
    cplxmatrixp a(n, cplxvectorp(n + 1, Complexp(inter(0, 0),inter(0, 0))));

    for (int i = 0; i < n; ++i) {
        QStringList rowData = rows[i].split(' ');

        for (int j = 0; j < n + 1; ++j) {
            long double real = rowData[2 * j].toDouble();
            long double imag = rowData[2 * j + 1].toDouble();
            a[i][j] = Complexp(inter(real, real) , inter(imag, imag));
        }
    }

    return a;
}

cplxmatrixp convertToMatrixp2(const QString& input)
{
    QStringList rows = input.split('\n');

    int n = rows.size();
    cplxmatrixp a(n, cplxvectorp(n + 1, Complexp(inter(0, 0),inter(0, 0))));

    for (int i = 0; i < n; ++i) {
        QStringList rowData = rows[i].split(' ');

        for (int j = 0; j < n+1; ++j) {
            long double real1 = rowData[4 * j].toDouble();
            long double real2 = rowData[4 * j+1].toDouble();
            long double imag1 = rowData[4 * j+2].toDouble();
            long double imag2 = rowData[4 * j+3].toDouble();
            a[i][j] = Complexp(inter(real1, real2) , inter(imag1, imag2));
        }
    }

    return a;
}

QString convertToStringp(const cplxvectorp& x) {
    QString result;

    for (const auto& pom : x){
        /*QString::number(static_cast<long double>(pom.real().a)*/

        string lr, pr, li, pi;
        pom.real().IEndsToStrings(lr, pr);
        pom.imag().IEndsToStrings(li, pi);

        result += "(" + QString::fromStdString(lr) + " " +
                  QString::fromStdString(pr) + " ) rozmiar przedzialu: " +
                  QString::number(QString::fromStdString(pr).toDouble() - QString::fromStdString(lr).toDouble(), 'e', 3)
                  + " ,(" + QString::fromStdString(li) + " " +
                  QString::fromStdString(pi) + " ) rozmiar przedzialu:" +
                  QString::number(QString::fromStdString(pi).toDouble() - QString::fromStdString(li).toDouble(), 'e', 3) + "\n";

        //Complexp(inter(real, real) , inter(imag, imag))
    }

    return result.trimmed();  // Usuwamy końcowy znak nowej linii
}


class Window1 : public QDialog {
public:
    Window1(const QString& title): QDialog()
    {
        setWindowTitle(title);
        resize(600, 50);

        auto layout = new QVBoxLayout(this);

        auto lineEdit1 = new QLineEdit(this);
        auto textEdit1 = new QTextEdit(this);
        auto resultLabel = new QLabel(this);

        lineEdit1->setPlaceholderText("Wprowadz ilosc rownan n");
        textEdit1->setPlaceholderText("Wprowadz rownania\n Liczba rzeczywista1,1 Liczba urojona1,1 Liczba rzeczywista1,2, Liczba urojona1,2...\n Liczba rzeczywista2,1 Liczba urojona2,1...");

        textEdit1->setFixedHeight(100);

        QPushButton* calculateButton = new QPushButton("Oblicz", this);
        connect(calculateButton, &QPushButton::clicked, [ lineEdit1, textEdit1, resultLabel]()
        {
            int n = lineEdit1->text().toInt();
            QString equations = textEdit1->toPlainText();

            cplxmatrix a(n, cplxvector(n + 1, Complex(0, 0)));
            a = convertToMatrix(equations);

            cplxvector x(n);
            int st;

            //odpalenie kodu
            complexmatrix(n, a, x, st);

            QString result = convertToString(x);

            if (st == 0)
            resultLabel->setText("Wynik: Liczba rzeczywista, Liczba urojona\n" + result);
            else
            resultLabel->setText("Wynik:\nSt=2, Brak rozwiazania");
        });

        layout->addWidget(lineEdit1);
        layout->addWidget(textEdit1);
        layout->addWidget(calculateButton);
        layout->addWidget(resultLabel);

        setLayout(layout);
    }
};

class Window2 : public QDialog {
public:
    Window2(const QString& title): QDialog()
    {
        setWindowTitle(title);
        resize(600, 50);

        auto layout = new QVBoxLayout(this);

        auto lineEdit1 = new QLineEdit(this);
        auto textEdit1 = new QTextEdit(this);
        auto resultLabel = new QLabel(this);

        lineEdit1->setPlaceholderText("Wprowadz ilosc rownan n");
        textEdit1->setPlaceholderText("Wprowadz rownania\n Liczba rzeczywista1,1 Liczba urojona1,1 Liczba rzeczywista1,2, Liczba urojona1,2...\n Liczba rzeczywista2,1 Liczba urojona2,1...");

        textEdit1->setFixedHeight(100);

        QPushButton* calculateButton = new QPushButton("Oblicz", this);
        connect(calculateButton, &QPushButton::clicked, [ lineEdit1, textEdit1, resultLabel]()
                {
                    int n = lineEdit1->text().toInt();
                    QString equations = textEdit1->toPlainText();

                    cplxmatrixp a(n);
                    a = convertToMatrixp1(equations);

                    cplxvectorp x(n);
                    int st;

                    //odpalenie kodu
                    complexmatrixp(n, a, x, st);

                    QString result = convertToStringp(x);

                    if (st == 0)
                        resultLabel->setText("Wynik: Liczba rzeczywista, Liczba urojona\n" + result);
                    else
                        resultLabel->setText("Wynik:\nSt=2, Brak rozwiazania");
                });

        layout->addWidget(lineEdit1);
        layout->addWidget(textEdit1);
        layout->addWidget(calculateButton);
        layout->addWidget(resultLabel);

        setLayout(layout);
    }
};

class Window3 : public QDialog {
public:
    Window3(const QString& title): QDialog()
    {
        setWindowTitle(title);
        resize(700, 50);

        auto layout = new QVBoxLayout(this);

        auto lineEdit1 = new QLineEdit(this);
        auto textEdit1 = new QTextEdit(this);
        auto resultLabel = new QLabel(this);

        lineEdit1->setPlaceholderText("Wprowadz ilosc rownan n");
        textEdit1->setPlaceholderText("Wprowadz rownania\n Przedzial rzeczywisty1,1 Przedzial urojony1,1 Przedzial rzeczywisty1,2, Przedzial urojonyy1,2...\n Przedzial rzeczywisty2,1 Przedzial urojony2,1...");

        textEdit1->setFixedHeight(100);

        QPushButton* calculateButton = new QPushButton("Oblicz", this);
        connect(calculateButton, &QPushButton::clicked, [ lineEdit1, textEdit1, resultLabel]()
                {
                    int n = lineEdit1->text().toInt();
                    QString equations = textEdit1->toPlainText();

                    cplxmatrixp a(n);
                    a = convertToMatrixp2(equations);

                    cplxvectorp x(n);
                    int st;

                    //odpalenie kodu
                    complexmatrixp(n, a, x, st);

                    QString result = convertToStringp(x);

                    if (st == 0)
                        resultLabel->setText("Wynik: Liczba rzeczywista, Liczba urojona\n" + result);
                    else
                        resultLabel->setText("Wynik:\nSt=2, Brak rozwiazania");
                });

        layout->addWidget(lineEdit1);
        layout->addWidget(textEdit1);
        layout->addWidget(calculateButton);
        layout->addWidget(resultLabel);

        setLayout(layout);
    }
};

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
{
    auto centralWidget = new QWidget(this);
    auto layout = new QVBoxLayout(centralWidget);

    auto buttonGroup = new QButtonGroup(this);

    auto radio1 = new QRadioButton("Arytmetyka Zmiennopozycyjna", this);
    auto radio2 = new QRadioButton("Arytmetyka Przedziałowa - dane rzeczywiste", this);
    auto radio3 = new QRadioButton("Arytmetyka Przedziałowa - dane przedziałowe", this);

    buttonGroup->addButton(radio1, 1);
    buttonGroup->addButton(radio2, 2);
    buttonGroup->addButton(radio3, 3);

    auto openButton = new QPushButton("Wybierz rodzaj arytmetyki", this);

    connect(openButton, &QPushButton::clicked, [this, buttonGroup]()
    {
        switch(buttonGroup->checkedId()) {
        case 1:
            (new Window1("Arytmetyka Zmiennopozycyjna"))->show();
            break;
        case 2:
            (new Window2("Arytmetyka Przedziałowa - dane rzeczywiste"))->show();
            break;
        case 3:
            (new Window3("Arytmetyka Przedziałowa - dane przedziałowe"))->show();
            break;
        default:
            QMessageBox::warning(this, "UWAZAJ", "Nie wybrales rodzaju arytmetyki");
        }
    });

    layout->addWidget(radio1);
    layout->addWidget(radio2);
    layout->addWidget(radio3);
    layout->addWidget(openButton);
    centralWidget->setLayout(layout);

    setCentralWidget(centralWidget);
}

