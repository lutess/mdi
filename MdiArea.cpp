#include "MdiArea.h"
#include "mainwindow.h"
#include "Utility.h"

MdiArea::MdiArea(QWidget*parent, VBoxLayout* _vBoxLayout, HBoxLayout* _hBoxLayout) : QMdiArea(parent)
{
	Utility::_pMdiArea= this;
	_vBoxLayout->addLayout(_hBoxLayout);
	_hBoxLayout->addWidget(this);
	_vBoxLayout->addStretch();
	setBackground(QBrush(QColor(56, 56, 56)));
	connect(this, SIGNAL(subWindowActivated(QMdiSubWindow*)) , parent, SLOT(windowActivateSignalReceived(QMdiSubWindow*)));
}

MdiArea::~MdiArea()
{}



