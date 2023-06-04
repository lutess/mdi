#pragma once

#include <QVBoxLayout>

class VBoxLayout  : public QVBoxLayout
{
	Q_OBJECT

public:
	VBoxLayout(QWidget *parent);
	~VBoxLayout();
};
