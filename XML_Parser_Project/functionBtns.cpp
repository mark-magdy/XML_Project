#include "functionBtns.h"
functionBtns::functionBtns(QWidget* parent)
	: QWidget(parent) {
	QHBoxLayout* btnsLayout = new QHBoxLayout(this);
	btnsLayout->addWidget(Validate);
	btnsLayout->addWidget(ToJSON);
	btnsLayout->addWidget(Beautify);
	btnsLayout->addWidget(Minify);
	btnsLayout->addWidget(Compress);
	btnsLayout->addWidget(DeCompress);
	setLayout(btnsLayout);

	connect(Validate, &QPushButton::clicked, this, &functionBtns::ValidateBtnClick);
	connect(ToJSON, &QPushButton::clicked, this, &functionBtns::ToJSONBtnClick);
	connect(Beautify, &QPushButton::clicked, this, &functionBtns::BeautifyBtnClick);
	connect(Minify, &QPushButton::clicked, this, &functionBtns::MinifyBtnClick);
	connect(Compress, &QPushButton::clicked, this, &functionBtns::CompressBtnClick);
	connect(DeCompress, &QPushButton::clicked, this, &functionBtns::DeCompressBtnClick);
}



void functionBtns::ValidateBtnClick() {
	qDebug() << "Validate button clicked.";
}

void functionBtns::ToJSONBtnClick() {
	qDebug() << "ToJSON button clicked.";
}

void functionBtns::BeautifyBtnClick() {
	qDebug() << "Beautify button clicked.";
}

void functionBtns::MinifyBtnClick() {
	qDebug() << "Minify button clicked.";
}

void functionBtns::CompressBtnClick() {
	qDebug() << "Compress button clicked.";
}

void functionBtns::DeCompressBtnClick() {
	qDebug() << "DeCompress button clicked.";
}


