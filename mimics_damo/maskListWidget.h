#pragma once
#include <qwidget.h>
#include <memory>
class QTableWidget;
class Mask;
class QLabel;
class QToolButton;
class QToolBar;
class MaskListWidget :public QWidget 
{
	Q_OBJECT
public:
	MaskListWidget(QWidget *parent = 0);
	~MaskListWidget();
	//void setMaskList(std::shared_ptr<std::list<std::shared_ptr<Mask>>> maskListPtr);
	/*void setMaskList(std::shared_ptr<QList<std::shared_ptr<Mask>>> maskListPtr);*/
	void setMaskMap(std::shared_ptr<QMap<QString, std::shared_ptr<Mask>>> maskMapPtr);
	//void setCurrentMaskPtr(std::weak_ptr<Mask>* maskPtr);
	void setCurrentMaskName(const QString& mask);
	void setItemText(int row, int column, const QString& text);
	void updateMaskList(const QString &newMaskName);
	//const QToolButton* getNewButton()
	//{
	//	return newButton;
	//}
	void setNewButtonAction(QAction *action);
	void setCalculateButtonAction(QAction *action);
	void setEditButtonAction(QAction *action);
	//void updateMaskList();
signals:
	void changeCurrentMask(QString mask);
	void deleteMask(QString mask_name);
	void changeCurrentMaskName(QString mask_name,int row,int column);
	void maskVisible(QString mask_name, bool visible);
private slots:
	void setChanges(int row, int column);
	void updateCurrentNameAndMask(int row, int column);
	void deleteMask();
	//void showQMap();
private:
	void addRow();
	std::shared_ptr<Mask> maskPtrOf(int row);

	QTableWidget *tableWidget;
	QLabel *label;
	QToolButton *newButton;
	QToolButton *editButton;
	QToolButton *deleteButton;
	QToolButton *calculateButton;
	//QToolBar *toolBar;
	//std::shared_ptr<std::list<std::shared_ptr<Mask>>> maskPtrListPtr;
	//std::shared_ptr<QList<std::shared_ptr<Mask>>> maskPtrQListPtr; //需要将其绑定到list上
	QAction *deleteAction;
	std::shared_ptr<QMap<QString, std::shared_ptr<Mask>>> maskPtrQMapPtr;
	QString currentName;
	//std::weak_ptr<Mask>* currentMaskPtr;
	//std::shared_ptr<QString> currentMaskName;
	bool createItemFlag;
};