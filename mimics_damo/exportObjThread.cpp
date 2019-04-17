#include "exportObjThread.hpp"
#include <vtkSmartPointer.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkOBJExporter.h>
#include "object.h"
exportObjThread::exportObjThread()  {
	
}

void exportObjThread::run()
{

	for (auto i : this->objList)
	{
		emit exportingObjStatus(i.lock()->name);
		vtkSmartPointer<vtkRenderer> outputRenderer = vtkSmartPointer<vtkRenderer>::New();
		outputRenderer->AddActor(i.lock()->objActor);

		vtkSmartPointer<vtkRenderWindow> outputRenWin = vtkSmartPointer<vtkRenderWindow>::New();
		outputRenWin->AddRenderer(outputRenderer);

		QString filePrefix = this->filePrefix + "/" + i.lock()->name;
		vtkSmartPointer<vtkOBJExporter> porter = vtkSmartPointer<vtkOBJExporter>::New();
		porter->SetFilePrefix(filePrefix.toStdString().c_str());
		porter->SetInput(outputRenWin);
		porter->Write();
	}
	emit exportingObjStatus("");
	//objList.clear();
}

void exportObjThread::setObjList(const std::vector<std::weak_ptr<Object>> &objList)
{
	this->objList = objList;
}

void exportObjThread::setFilePrefix(const QString& prefix)
{
	this->filePrefix = prefix;
}