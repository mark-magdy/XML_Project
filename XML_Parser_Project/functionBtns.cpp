#include "functionBtns.h"

functionBtns::functionBtns(QWidget* parent)
	: QWidget(parent) {
	QHBoxLayout* btnsLayout = new QHBoxLayout(this);
	btnsLayout->addWidget(Validate);
	btnsLayout->addWidget(Correct);
	btnsLayout->addWidget(ToJSON);
	btnsLayout->addWidget(Beautify);
	btnsLayout->addWidget(Minify);
	btnsLayout->addWidget(Compress);
	btnsLayout->addWidget(DeCompress);
	setLayout(btnsLayout);

	connect(Validate, &QPushButton::clicked, this, &functionBtns::ValidateBtnClick);
	connect(Correct, &QPushButton::clicked, this, &functionBtns::CorrectBtnClick);
	connect(ToJSON, &QPushButton::clicked, this, &functionBtns::ToJSONBtnClick);
	connect(Beautify, &QPushButton::clicked, this, &functionBtns::BeautifyBtnClick);
	connect(Minify, &QPushButton::clicked, this, &functionBtns::MinifyBtnClick);
	connect(Compress, &QPushButton::clicked, this, &functionBtns::CompressBtnClick);
	connect(DeCompress, &QPushButton::clicked, this, &functionBtns::DeCompressBtnClick);
}
