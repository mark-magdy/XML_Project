#include "outputWindow.h"

outputWindow::outputWindow(QWidget* parent)
    : QWidget(parent) {
    outputEdit = new QPlainTextEdit(this);
    outputEdit->setReadOnly(true);  // Make the text output field read-only
    outputEdit->setPlaceholderText("OUTPUT");
    QFont font;
    font.setFamily("Courier");
    font.setFixedPitch(true);
    font.setPointSize(10);
    outputEdit->setFont(font);
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(outputEdit);
    layout->addWidget(saveBtn);
    
    setLayout(layout);

    //setWindowTitle("Output Code");
    resize(350, 300);
}

void outputWindow::setOutputText(const QString& text) {
    outputEdit->setPlainText(text);
}