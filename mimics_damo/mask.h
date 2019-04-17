#pragma once
#include <vtkSmartPointer.h>
#include <string>
#include "qstring.h"
class vtkImageData;
class vtkAlgorithmOutput;
class vtkImageActor;
class vtkRenderer;
class vtkImageViewer2;
class Mask {
public:
	Mask();
	~Mask();
	void setVisible(bool visible);
	bool getVisible();
	void deleteMask();
	//void setName(const QString &newName) { name = newName; }
	//QString getName() { return name; }
	QString name;  //这个名字作为索引
	int thresholdRange[2];    //阈值范围一旦选出来就是固定的，无论是否用区域增长处理过
	double color[3];
	//bool visible;
	vtkSmartPointer<vtkImageData> imageData;
	vtkSmartPointer<vtkImageActor> imageActor[3];

	//static vtkRenderer* vtkViewRender[3];
	static vtkImageViewer2* imageViewer[3];  //静态vtkSmartPointer会导致这个内存一直有引用没法释放，导致错误
};
