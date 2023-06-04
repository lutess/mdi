#pragma once

#include <QWidget>
#include "MdiArea.h"
#include "VBoxLayout.h"

class CentralWidget  : public QWidget
{
	Q_OBJECT

public:
	CentralWidget(QWidget* parent, MdiArea* , VBoxLayout* );
	~CentralWidget();
};
