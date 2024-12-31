#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_XML_Parser_Project.h"

class XML_Parser_Project : public QMainWindow
{
    Q_OBJECT

public:
    XML_Parser_Project(QWidget *parent = nullptr);
    ~XML_Parser_Project();

private:
    Ui::XML_Parser_ProjectClass ui;
};
