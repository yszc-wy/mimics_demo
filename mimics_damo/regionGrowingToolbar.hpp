#pragma once
#include <QToolBar>
#include <memory>
class Mask;
class QLabel;
class QComboBox;
class QPushButton;

class RegionGrowingToolBar : public QToolBar {
	Q_OBJECT

public:
	RegionGrowingToolBar(const QString &title, QWidget * parent = Q_NULLPTR);
	~RegionGrowingToolBar();
	void setMaskPtrMapPtr(std::weak_ptr<QMap<QString, std::shared_ptr<Mask>>> maskPtrMapPtr);
	bool initToolBar(std::weak_ptr<const Mask> currentMask);
signals:
	void sourceOrTargetMaskChanged(const QString& sourceMask,const QString& targetMask);
private slots:
	void updateComboBox();
protected:
	void showEvent(QShowEvent* event);
	//void closeEvent(QCloseEvent *event);
private:
	std::weak_ptr<QMap<QString, std::shared_ptr<Mask>>> maskPtrMapPtr;//管理mask资源的只有这个类

	bool recursion;
	QWidget* mainWidget;

	QLabel *sourceLabel;
	QComboBox *sourceComboBox;

	QLabel *arrowLabel;

	QLabel *targetLabel;
	QComboBox *targetComboBox;

	QPushButton *closeButton;
};
