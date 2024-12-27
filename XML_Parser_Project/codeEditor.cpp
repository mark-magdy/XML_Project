#include "codeEditor.h"


codeEditor::codeEditor(QWidget* parent)
    : QWidget(parent) {
    editor = new QPlainTextEdit(this);


    QFont font;
    font.setFamily("Consolas");
    font.setFixedPitch(true);
    font.setPointSize(10);
    editor->setFont(font);

    editor->setTabStopDistance(QFontMetricsF(font).horizontalAdvance(' ') * 4); // 4 spaces per tab
    editor->setLineWrapMode(QPlainTextEdit::NoWrap);
    editor->setPlaceholderText("Input: Your XML Code :) ");

    QVBoxLayout* layout = new QVBoxLayout;
    QHBoxLayout* layoutBottom = new QHBoxLayout;


    layout->addWidget(editor);

    browseButton->setFixedWidth(100);
    fileLabel->setText("No file selected");
    fileLabel->setWordWrap(true);
    layoutBottom->addWidget(browseButton);
    layoutBottom->addWidget(fileLabel);
    layout->addLayout(layoutBottom);

    myHighlighter = new CodeHighlighter(editor->document());

    connect(browseButton, &QPushButton::clicked, this, &codeEditor::onBrowseClicked);

    setLayout(layout);

    resize(350, 300);
}




#include <QString>
#include <QFile>
#include <QTextStream>
#include <QIODevice>
QString readFile(const QString& filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return QString("Error please choose a valid file");
    }

    QTextStream in(&file);
    QString fileContent = in.readAll();
    file.close();
    return fileContent;
}
void codeEditor::onBrowseClicked() {
    QString fileName = QFileDialog::getOpenFileName(this, "Open File", "", "All Files (*.*);;Text Files (*.txt);;Images (*.png *.xpm *.jpg)");
    if (!fileName.isEmpty()) {
        fileLabel->setText(fileName);
    }
    editor->setPlainText(readFile(fileName));
}