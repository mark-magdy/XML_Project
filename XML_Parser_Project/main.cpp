#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QLabel>
#include <QPlainTextEdit>
#include<codeEditor.h>
#include<functionBtns.h>
#include <outputWindow.h>

class MainWindow : public QWidget {
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:


private:
    QLabel* label = new QLabel(this);
    codeEditor* input = new codeEditor();
    outputWindow* output = new outputWindow();
    functionBtns* functionBtnsObj = new functionBtns();
};



int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    MainWindow browser;
    browser.show();


    return app.exec();
}
#include "main.moc"




MainWindow::MainWindow(QWidget* parent)
    : QWidget(parent) {
    setWindowTitle("XML Parser");
    setWindowIcon(QIcon("D:\ASU Courses Engineering Junior\data structure\qt trials\XML_project_GUI\XML_project_GUI\icon.jgp"));
    resize(800, 500);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    QHBoxLayout* inoutLayout = new QHBoxLayout(this);
    QHBoxLayout* browseLayout = new QHBoxLayout(this);
    QHBoxLayout* functionBtnsLayout = new QHBoxLayout(this);
    label->setText("XML Parser");
    QFont titleFont("Arial", 20, QFont::Bold);
    label->setFont(titleFont);
    label->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(label);
    inoutLayout->addWidget(input);
    inoutLayout->addWidget(output);
    functionBtnsLayout->addWidget(functionBtnsObj);
    mainLayout->addLayout(inoutLayout);
    mainLayout->addLayout(functionBtnsLayout);

}

MainWindow::~MainWindow() {
}








/*

#include "XML_Parser_Project.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    XML_Parser_Project w;
    w.show();
    return a.exec();
}

*/