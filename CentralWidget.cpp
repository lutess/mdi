#include "CentralWidget.h"
#include "CentralWidget.h"

CentralWidget::CentralWidget(QWidget* parent, MdiArea* _mdiArea, VBoxLayout* _vBoxLayout) : QWidget(parent)
{
	QHBoxLayout* hBoxLay = new QHBoxLayout;
	hBoxLay->addWidget(_mdiArea);
	setLayout(hBoxLay);
	_vBoxLayout->addWidget(this);
}

CentralWidget::~CentralWidget()
{}
