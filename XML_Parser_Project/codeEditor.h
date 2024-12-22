#pragma once
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QLabel>
#include <QPlainTextEdit>

class codeEditor : public QWidget {
    Q_OBJECT

public:
    codeEditor(QWidget* parent = nullptr);
private slots:
    void BrowseClick();

private:
    QPlainTextEdit* editor;
    QPushButton* browse = new QPushButton("Browse", this);
};