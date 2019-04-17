#pragma once
#include <QThread>
#include <qstring.h>
#include <memory>
#include <vtkSmartPointer.h>
class QVTKWidget;
class Mask;
class Object;
class vtkRenderer;
class CalculateObjThread : public QThread {
	Q_OBJECT

public:
	CalculateObjThread();
	~CalculateObjThread();
	void setCalMaskAndCheckedId(std::weak_ptr<Mask> mask,int id);
	void setObjPtrQMapPtr(std::shared_ptr<QMap<QString, std::shared_ptr<Object>>> objMapPtr);
	void setRen(vtkSmartPointer<vtkRenderer> ren);
	//void setVTKWidget(QVTKWidget *widget);
signals:
	void changeProcess(const QString& a, int value);
	void objectListChange(const QString & newObjectName);
protected:
	void run();
private:

	std::weak_ptr<Mask> calMask;
	std::shared_ptr<QMap<QString, std::shared_ptr<Object>>> objPtrQMapPtr;//obj资源管理
	vtkSmartPointer<vtkRenderer> ren_3dViewer;
	//QVTKWidget *widget_3dViewer;
	int checkedId;
};
