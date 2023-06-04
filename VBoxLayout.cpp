#include "VBoxLayout.h"
#include "mainwindow.h"

VBoxLayout::VBoxLayout(QWidget *parent) : QVBoxLayout(parent)
{
	setContentsMargins(0, 0, 0, 0);
}

VBoxLayout::~VBoxLayout()
{}
