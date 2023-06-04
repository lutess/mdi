#include "Utility.h"
#include <QFile>
#include <QFileInfo>
#include "MdiClient.h"
#include "MsgBox.h"


bool Utility::scriviFile(MdiClient* mdiClient, QString str)
{
	QList <QString> buttons = { "Ok" };
	QString information("E' stata annullata l'operazione.");
	QString details("In bool Utility::scriviFile(MdiClient * mdiClient, QString str)\n\n"
					"Il nome de mdiClient in oggetto era: " + mdiClient->nome());
	if (!str.isNull() && !str.isEmpty())
	{
		if (QFile::exists(str)) QFile::remove(str);
		QFile file(str);
		if (file.open(QIODeviceBase::WriteOnly))
		{
			QTextStream out(&file);
			if ((QFileInfo(str)).suffix() == "htm") out << mdiClient->toHtml();
			else if ((QFileInfo(str)).suffix() == "txt") out << mdiClient->toPlainText();
			file.close();
			return true;
		}
		else
		{
			QString testo("Impossibile aprire il file in scrittura.\nDisco pieno?");
			MsgBox msg(0, testo, buttons, information, details); msg.exec();
			return false;
		}
	}
	QString testo("Non e' stato possibile scrivere il file\nperche' il nome era vuoto oppure nullo.");
	MsgBox msg(0, testo, buttons, information, details); msg.exec();
	return false;
}


QString Utility::_dirPredef= "C:\\Users\\lucio\\Documents\\";
MainWindow* Utility::_pMainWnd = nullptr;
MdiArea* Utility::_pMdiArea = nullptr;
double Utility::_MonitorDpi = 102.19865319865319865319865319865;
