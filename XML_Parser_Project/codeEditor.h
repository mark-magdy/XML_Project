#pragma once
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QLabel>
#include <QPlainTextEdit>

#include "highlighter.h" 

class codeEditor : public QWidget {
    Q_OBJECT

public:
    codeEditor(QWidget* parent = nullptr);
private slots:
    void onBrowseClicked();
private:
    QPlainTextEdit* editor;
    //QLabel* fileLabel = new QLabel("No File Choosen",this);
    //QPushButton* browse = new QPushButton("Browse", this);
    QLabel* fileLabel = new QLabel(this);
    QPushButton* browseButton = new QPushButton("Browse", this);
    CodeHighlighter* myHighlighter ;
};