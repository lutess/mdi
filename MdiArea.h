#pragma once

#include <QMdiArea>
#include "VBoxLayout.h"
#include "HBoxLayout.h"

class MdiArea  : public QMdiArea
{
	Q_OBJECT

private:

public:
	MdiArea(QWidget *parent, VBoxLayout*, HBoxLayout*);
	~MdiArea();

};
