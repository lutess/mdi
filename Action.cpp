#include "Action.h"
#include <QFont>

Action::Action(QObject*parent, QString title, Menu* ptr, bool checkable) : QAction(parent)
{
	if (ptr) ptr->addAction(this);
	setText(title);
	setFont(QFont ("Helvetica", 12));
	if (checkable)
		setCheckable(true);
	_nome = title;
}

Action::~Action()
{
}
