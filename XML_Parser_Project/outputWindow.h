#pragma once
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QLabel>
#include <QPlainTextEdit>

class outputWindow : public QWidget {
    Q_OBJECT

public:
    explicit outputWindow(QWidget* parent = nullptr);
    void setOutputText(const QString& text);


private slots:
    //void saveClick();


private:
    QPushButton* saveBtn = new QPushButton("Save as new File", this);
    QPlainTextEdit* outputEdit;

};
