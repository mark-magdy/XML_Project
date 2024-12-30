#pragma once
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QLabel>
#include <QPlainTextEdit>

class functionBtns : public QWidget
{
    Q_OBJECT
public:
    explicit functionBtns(QWidget* parent = nullptr);

private slots:
    void ValidateBtnClick();
    void ToJSONBtnClick();
    void BeautifyBtnClick();
    void MinifyBtnClick();
    void CompressBtnClick();
    void DeCompressBtnClick();
    void CorrectBtnClick();

private:
    //MainWindow* glbContext;
    QPushButton* Validate = new QPushButton("Validate", this),
        * Correct = new QPushButton("Correct", this),
        * ToJSON = new QPushButton("ToJSON", this),
        * Beautify = new QPushButton("Beautify", this),
        * Minify = new QPushButton("Minify", this),
        * Compress = new QPushButton("Compress", this),
        * DeCompress = new QPushButton("DeCompress", this);
};
