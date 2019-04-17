#pragma once
#include <qwidget.h>
#include <memory>
class QTableWidget;
class Object;
class QLabel;
class QToolButton;
class QAction;
class ObjListWidget :public QWidget
{
	Q_OBJECT
public:
	ObjListWidget(QWidget *parent = 0);
	~ObjListWidget();
	void setExportButtonAction(QAction *action);
	void setObjectMap(std::shared_ptr<QMap<QString, std::shared_ptr<Object>>> objectMapPtr);
private slots:
	void setChanges(int, int);
	void updateCurrentNameAndObject(int, int);
	void deleteObject();
	void updateObjectList(const QString &newObjectName);
private:
	void addRow();
	QString currentName;
	QTableWidget *tableWidget;
	QLabel *label;
	QToolButton *exportButton;
	QToolButton *deleteButton;
	QAction *deleteAction;
	bool createItemFlag;
	//QAction *exportAction;
	std::shared_ptr<QMap<QString, std::shared_ptr<Object>>> objPtrQMapPtr;
};