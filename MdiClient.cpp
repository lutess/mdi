#include "MdiClient.h"
#include <QMdiSubWindow>
#include <QCloseEvent>
#include <QFileDialog>
#include "MsgBox.h"
#include "Utility.h"
#include "ColorDialog.h"
#include "FontDialog.h"
//#include <QMdiArea>
//#include <QMenu>
//#include <QMessageBox>
//#include <QFileInfo>
//#include <QTextStream>
//#include "MdiArea.h"
//#include <QIterator>
//#include <QFile>


MdiClient::MdiClient(QWidget *parent, QString nome, int orientamento) : QTextEdit(parent), _defaultName(true), _mdiArea((MdiArea*)parent)
{
	if (nome.isEmpty())
	{
		static int num = 0;
		nome = "untitled";
		QString str; str.setNum(num++);
		nome.append(str + " ");
	}
	else
	{
		QFile file(nome, this); file.open(QIODevice::ReadOnly | QIODevice::Text);
		QTextStream in(&file);
		document()->setHtml(in.readAll());
		file.close();
		_defaultName = false;
	}
	_nome = nome;
	setAttribute(Qt::WA_DeleteOnClose);

	QTextDocument* doc = document();
	doc->setDefaultFont(QFont("Helvetica", 14));
	doc->setDocumentMargin(16);

	int width = _mdiArea->width(), higth = _mdiArea->height();
	doc->setPageSize(QSizeF(width, higth));
	doc->setTextWidth(width);
	setLineWrapColumnOrWidth(width - 32);
	setMinimumSize(width /*- 1*/, higth);
	setMaximumSize(width /*- 1*/, higth);
	setLineWrapMode(QTextEdit::FixedPixelWidth);


	_qMdiSubWindowPtr = ((QMdiArea*)parent)->addSubWindow(this);
	if (_frameless) _qMdiSubWindowPtr->setWindowFlag(Qt::FramelessWindowHint);
	else _qMdiSubWindowPtr->setWindowFlag(Qt::FramelessWindowHint, false);

	Action* act = Utility::_pMainWnd->framelessAction();
	if (_frameless) act->setText("TitleBar");
	else act->setText("NoTitleBar");


	Utility::_pMainWnd->setWindowTitle(qApp->applicationName() + " - " + QFileInfo(_nome).baseName());
	setWindowTitle(_nome);
	document()->setModified(false);

	connect(this, &MdiClient::textChanged, this, &MdiClient::testoCambiatoEvento);
	connect(Utility::_pMainWnd->coloreAction(), &QAction::triggered, this, &MdiClient::colore);
	connect(Utility::_pMainWnd->fontAction(), &QAction::triggered, this, &MdiClient::font);
	connect(Utility::_pMainWnd->framelessAction(), &QAction::triggered, this, &MdiClient::frameless);
	connect(Utility::_pMainWnd->clientWndState(), &QAction::triggered, this, &MdiClient::windowState);

	Action* corrAction = Utility::_pMainWnd->clientWndState();
	if (_maximized) { showMaximized(); corrAction->setText("NormalizzaWindow"); }
	else { showNormal(); corrAction->setText("MassimizzaWindow"); }
}

bool MdiClient::_frameless = true;
bool MdiClient::_maximized = true;

MdiClient::~MdiClient()
{
}


void MdiClient::closeEvent(QCloseEvent* event)
{
	QString str = windowTitle();
	if (_defaultName && !str.compare("untitled0 "))
	{
		QString testo("Untitled0 non puo' essere chiuso.");
		QList <QString> buttons = { "Ok" };
		QString information("E' stata annullata l'operazione.");
		QString details("In void MdiClient::closeEvent(QCloseEvent* event)\n\n"
			"Il nome de mdiClient in oggetto era: " + this->nome());
		MsgBox msg(this, testo, buttons, information, details); msg.exec();
		event->ignore();
		return;
	}
	QList<QMdiSubWindow*> listaQMdiSubWindow = Utility::_pMdiArea->subWindowList();
	QList<QMdiSubWindow*>::iterator it= listaQMdiSubWindow.begin();
	while (QString((*it)->windowTitle()) != str)
		it++;
	(*it)->setFocus();

	if (document()->isModified())
	{
		QString details("In void MdiClient::closeEvent(QCloseEvent* event)\n\n"
			"Il nome de mdiClient in oggetto era: " + this->nome());
		QString information("Cosa intendi fare?");
		QList<QString> buttons = { "Save", "Discard", "Cancel" };
		QString nuovoNome= windowTitle();
		QString argmnt("<html><b>\"" + _nome + "\"</b></html>");
		if (_defaultName)
		{
			QString testo(tr("<html><b>%1</b><br><br>Il documento ha un nome fittizio"
							" per usi inteni all'applicazione,<br>"
							"<u>ma possiede un contenuto</u> piu' o meno modificato.</html>"). arg(nuovoNome));

			MsgBox msg(this, testo, buttons, information, details);
			int ret = msg.exec();
			if (buttons[ret] == "Discard") { event->accept(); return; }
			else if (buttons[ret] == "Cancel") { event->ignore(); return; }

			QString filter("TestoHtm (*.htm);;Testo (*.txt);;Any (*.*)");
			nuovoNome = QFileDialog::getSaveFileName(this, "Salva File", Utility::_dirPredef, filter);
		}
		else
		{
			QString testo("Il documento ha subito delle modifice.\n Vuoi salvare ?");
			MsgBox msg(this, testo, buttons, information, details);
			int ret = msg.exec();
			if (buttons[ret] == "Discard") { event->accept(); return; }
			else if (buttons[ret] == "Cancel") { event->ignore(); return; }

		}
		if (Utility::scriviFile(this, nuovoNome))
		{
			_defaultName = false;
			document()->setModified(false);
			event->accept(); return;
		}
		else
		{
			QString testo("Non e' stato possibile scrivere il file.");
			QList <QString> buttons = { "Ok" };
			QString information("E' stata annullata l'operazione.");
			QString details("In void MdiClient::closeEvent(QCloseEvent* event)\n\n"
							"Il nome de mdiClient in oggetto era: " + this->nome());
			MsgBox msg(this, testo, buttons, information, details); msg.exec();
			event->ignore(); return;
		}
	}
	else event->accept();
}



void MdiClient::colore()
{
	if ((MdiClient*)Utility::_pMdiArea->currentSubWindow()->widget() != this)
		return;
	QColor clr;
	if (textCursor().hasSelection())
		clr = textColor();
	else
		clr = palette().brush(QPalette::WindowText).color();

	ColorDialog cd(clr, this);
	if (cd.exec())
	{
		clr = cd.selectedColor();

		if (textCursor().hasSelection())
			setTextColor(QColor(clr));
		else
		{
			selectAll();
			setTextColor(QColor(clr));
		}
	}
}


void MdiClient::font()
{
	if ((MdiClient*)Utility::_pMdiArea->currentSubWindow()->widget() != this)
		return;
	QFont fnt = currentFont();

	FontDialog fd = FontDialog(fnt, this);
	if (fd.exec())
		fnt= fd.selectedFont();

	QTextCursor cur = textCursor();
	if (cur.hasSelection())
	{
		QTextCharFormat textFrmt;
		textFrmt.setFont(fnt);
		cur.setCharFormat(textFrmt);
	}
	else
		setFont(fnt);
}


void MdiClient::frameless()
{
	static int contatore = 0;
	int cont = _mdiArea->subWindowList().size();

	if (_frameless)
		_qMdiSubWindowPtr->setWindowFlag(Qt::FramelessWindowHint, false);
	else
		_qMdiSubWindowPtr->setWindowFlag(Qt::FramelessWindowHint);

	if (!(++contatore % cont))
	{
		_frameless = !_frameless;
		contatore = 0;
	}

	Action* act = Utility::_pMainWnd->framelessAction();
	if (_frameless) act->setText("TitleBar");
	else act->setText("NoTitleBar");
}


void MdiClient::windowState()
{
	if ((MdiClient*)Utility::_pMdiArea->currentSubWindow()->widget() != this)
		return;

	Action* corrAction = Utility::_pMainWnd->clientWndState();
	if (_maximized)
	{
		showNormal();
		_maximized = false;
		corrAction->setText("MassimizzaWindow");
	}
	else
	{
		showMaximized();
		_maximized = true;
		corrAction->setText("NormalizzaWindow");
	}
}


