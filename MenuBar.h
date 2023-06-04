#pragma once

#include <QMenuBar>
#include "VBoxLayout.h"

class MenuBar  : public QMenuBar
{
	Q_OBJECT

public:
	MenuBar(QWidget *parent, VBoxLayout* ptr);
	~MenuBar();
};
