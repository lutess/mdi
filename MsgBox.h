#pragma once

#include <QMessageBox>

class MsgBox  : public QMessageBox
{
	Q_OBJECT

public:
	MsgBox(QWidget* parent, QString testo, QList<QString>stdButtons, QString information= QString(), QString details = QString(),
			QString winTitle = QString(), QMessageBox::Icon= QMessageBox::Warning);
	~MsgBox();
};
