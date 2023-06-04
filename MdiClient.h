#pragma once

#include <QTextEdit>
#include "MdiArea.h"

class MdiClient  : public QTextEdit
{
	Q_OBJECT

public:
	MdiClient(QWidget *parent, QString, int orientamento);
	~MdiClient();
	QString nome() { return _nome; }
	bool isDefaultNome() { return _defaultName; };
	void setDefaultNome(bool buleiano= true) { _defaultName = buleiano; }

public slots:
	void colore();
	void font();
	void frameless();
	void windowState();

private:
	QString _nome;
	bool _defaultName;
	void closeEvent(QCloseEvent* );
	void testoCambiatoEvento() { document()->setModified(document()->isModified()); }
	MdiArea *_mdiArea;
	QMdiSubWindow* _qMdiSubWindowPtr;

	static bool _frameless;
	static bool _maximized;
private:

};
