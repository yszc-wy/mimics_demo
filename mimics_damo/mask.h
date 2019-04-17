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
	QString name;  //���������Ϊ����
	int thresholdRange[2];    //��ֵ��Χһ��ѡ�������ǹ̶��ģ������Ƿ����������������
	double color[3];
	//bool visible;
	vtkSmartPointer<vtkImageData> imageData;
	vtkSmartPointer<vtkImageActor> imageActor[3];

	//static vtkRenderer* vtkViewRender[3];
	static vtkImageViewer2* imageViewer[3];  //��̬vtkSmartPointer�ᵼ������ڴ�һֱ������û���ͷţ����´���
};
