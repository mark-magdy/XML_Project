#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QLabel>
#include <QMainWindow>
#include <QPlainTextEdit>
#include "codeEditor.h"
#include "functionBtns.h"
#include "outputWindow.h"
#include <QMenuBar> 
#include <QMenu> 
#include <QAction>
#include <QMessageBox>
#include "../Backend.h"

QApplication * globalVar ;
class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QMainWindow* parent = nullptr);
    ~MainWindow();

private slots:
    void showAboutDialog();
    void christmasUI();
    void darkUI();
    void lightUI();

public:
    QLabel* label;

    codeEditor* input;
    outputWindow* output;
    functionBtns* functionBtnsObj;

    void createMenus();
};


MainWindow::MainWindow(QMainWindow* parent)
    : QMainWindow(parent), label(new QLabel(this)), input(new codeEditor()), output(new outputWindow()), functionBtnsObj(new functionBtns()) {

    setWindowTitle("XML Parser");
    //setWindowIcon(QIcon("D:/ASU Courses Engineering Junior/data structure/qt trials/XML_project_GUI/XML_project_GUI/icon.jpg"));
    resize(800, 500);
    createMenus();
    QVBoxLayout* mainLayout = new QVBoxLayout;
    QHBoxLayout* inoutLayout = new QHBoxLayout;
    QHBoxLayout* functionBtnsLayout = new QHBoxLayout;

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

    QWidget* centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);
}

MainWindow::~MainWindow() {
    delete label;
    delete input;
    delete output;
    delete functionBtnsObj;
}

//---------------------------------------------------------



void MainWindow::createMenus() {
    // Create a menu bar
    QMenuBar* menuBar = new QMenuBar(this);

    // Create the "File" menu
    QMenu* fileMenu = menuBar->addMenu(tr("&File"));

    // Create actions for the "File" menu
    QAction* exitAction = new QAction(tr("&Exit"), this);
    connect(exitAction, &QAction::triggered, this, &QMainWindow::close);
    fileMenu->addAction(exitAction);

    //------------------------------------------------------------
    QMenu* viewMenu = menuBar->addMenu(tr("&View"));


    QAction* christamsUIAction = new QAction(tr("&ChristamsUI"), this);
    connect(christamsUIAction, &QAction::triggered, this, &MainWindow::christmasUI);
    viewMenu->addAction(christamsUIAction);

    QAction* darkUIAction = new QAction(tr("&DarkUI"), this);
    connect(darkUIAction, &QAction::triggered, this, &MainWindow::darkUI);
    viewMenu->addAction(darkUIAction);

    QAction* lightUIAction = new QAction(tr("&LightUI"), this);
    connect(lightUIAction, &QAction::triggered, this, &MainWindow::lightUI);
    viewMenu->addAction(lightUIAction);

    //----------------------------------------------------
    QMenu* helpMenu = menuBar->addMenu(tr("&Help"));

    // Create actions for the "Help" menu
    QAction* aboutAction = new QAction(tr("&About"), this);
    connect(aboutAction, &QAction::triggered, this, &MainWindow::showAboutDialog);
    helpMenu->addAction(aboutAction);

    // Set the menu bar
    setMenuBar(menuBar);
}

void MainWindow::christmasUI() {
    // Load the stylesheet
    QFile file("style.qss");
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream stream(&file);
        QString stylesheet = stream.readAll();
        globalVar->setStyleSheet(stylesheet);
    }
}

void MainWindow::darkUI() {
    globalVar->setStyleSheet("");
}
void MainWindow::lightUI() {

}
void MainWindow::showAboutDialog() {
    QMessageBox::about(this, tr("About"), tr("Mark was here :)  \n samoooooo 3aleeekkooooooo  "));
}
//----------------------------------------------------------
MainWindow* globalWindow;

int main(int argc, char* argv[]) {
    cout << "hi ;;" << endl; 
    if (argc > 1) {
        command_line(argc,argv);
        return 0;
    }
    QApplication app(argc, argv);
    globalVar = &app; 
    MainWindow* browser= new MainWindow(); 
    globalWindow = browser; 
    app.setStyle("Fusion");
    
    QIcon icon("icon.png");
    browser->setWindowIcon(icon);

    browser->show();
    return app.exec();
}

#include "main.moc"



void functionBtns::ValidateBtnClick() {
    QString curText = globalWindow->input->editor->toPlainText();
    string processStr = curText.toStdString();
    validation test;
    pair<bool, string> isValid = test.check_valid(processStr);
    if (!isValid.first || processStr == "") {
        globalWindow->output->setOutputText(QString::fromStdString(isValid.second));
    }else {
        string temp = "it is VALID code";
        globalWindow->output->setOutputText(QString::fromStdString(temp));
    }
    qDebug() << "Validate button clicked.";
}
void functionBtns::CorrectBtnClick() {
    QString curText = globalWindow->input->editor->toPlainText();
    string processStr = curText.toStdString();
    validation test;
    pair<bool, string> isValid = test.check_valid(processStr);
    if (!isValid.first || processStr == "") { 

        globalWindow->output->setOutputText(QString::fromStdString(isValid.second));
    }else {
        globalWindow->output->setOutputText(curText);
    }
}
void functionBtns::ToJSONBtnClick() {

    qDebug() << "ToJSON button clicked.";

}

void functionBtns::BeautifyBtnClick() {
    QString curText = globalWindow->input->editor->toPlainText(); 
    string processStr = curText.toStdString(); 
    validation test;
    pair<bool, string> isValid = test.check_valid(processStr);
    if (!isValid.first || processStr == "") {
        globalWindow->output->setOutputText(QString::fromStdString(isValid.second));
    }else {
        vector <treeNode*> ret = totree(processStr);
        vector <string> temp;
        node_to_vector(ret, temp);
        prettify(temp);
        string outputStr = "";
        for (auto& i : temp) {
            outputStr += i;
        }
        globalWindow->output->setOutputText(QString::fromStdString(outputStr));
    }
    qDebug() << "Beautify button clicked.";
}

void functionBtns::MinifyBtnClick() {
    QString curText = globalWindow->input->editor->toPlainText();
    string processStr = curText.toStdString();
    //TODO: validate !!
    validation test;
    pair<bool, string> isValid = test.check_valid(processStr);
    if (!isValid.first || processStr=="") {
        globalWindow->output->setOutputText(QString::fromStdString(isValid.second));
    }else {
        vector <treeNode*> ret = totree(processStr);
        vector <string> temp;
        node_to_vector(ret, temp);
        minify(temp);
        string outputStr = "";
        for (auto& i : temp) {
            outputStr += i;
        }
        globalWindow->output->setOutputText(QString::fromStdString(outputStr));
    }
    qDebug() << "Minify button clicked.";
}

void functionBtns::CompressBtnClick() {
    QString curText = globalWindow->input->editor->toPlainText();
    string processStr = curText.toStdString();
    LZ77Compressor compressor;
    vector<Token> ret = compressor.compress(processStr);
    
    qDebug() << "Compress button clicked.";
}

void functionBtns::DeCompressBtnClick() {
    qDebug() << "DeCompress button clicked.";
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



