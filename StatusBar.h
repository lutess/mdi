#pragma once

#include <QStatusBar>
#include<QVBoxLayout>

class StatusBar  : public QStatusBar
{
	Q_OBJECT

public:
	StatusBar(QWidget*parent, QVBoxLayout*);
	~StatusBar();
};
