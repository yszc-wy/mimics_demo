#include "mimics_damo.h"
#include <QtWidgets/QApplication>
#include <QTextCodec>
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	mimics_damo w;
	w.show();
	return a.exec();
}
