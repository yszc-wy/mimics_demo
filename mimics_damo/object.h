#pragma once
#include <vtkSmartPointer.h>
#include <qstring.h>
class vtkActor;
class QVTKWidget;
class Object {
public:
	Object();
	Object(const QString &n, const vtkSmartPointer<vtkActor> actor,const QString& q);
	~Object();

	void setVisible(bool visible);
	bool getVisible();
	void deleteObject();

	double color[3];
	QString name;
	QString quality;
	vtkSmartPointer<vtkActor> objActor;

	static QVTKWidget* viewWidget;
};