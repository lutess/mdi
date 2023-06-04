#pragma once

#include <QAction>
#include "Menu.h"

class Action  : public QAction
{
	Q_OBJECT

public:
	Action(QObject*parent, QString, Menu*, bool checkable= false);
	~Action();

	QString nome() { return _nome; }

private:
	QString _nome;
};
