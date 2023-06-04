#include "StatusBar.h"
#include "mainwindow.h"

StatusBar::StatusBar(QWidget*parent, QVBoxLayout* _vBoxLayout) : QStatusBar(parent)
{
	_vBoxLayout->addWidget(this);
	setStyleSheet("background-color: #111111; color: #dddddd");
	showMessage("StatusBarMessage");
}

StatusBar::~StatusBar()
{}
