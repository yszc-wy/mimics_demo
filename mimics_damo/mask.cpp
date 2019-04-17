#include "mask.h"
#include <vtkImageActor.h>
#include <vtkImageData.h>
#include <vtkRenderer.h>
#include <qmessagebox.h>
#include <vtkImageViewer2.h>
Mask::Mask()
{
	thresholdRange[0] = 0;
	thresholdRange[1] = 0;
	color[0] = 0;
	color[1] = 0;
	color[2] = 0;
	//visible = true;
}
void Mask::deleteMask()
{
	for (int i = 0; i < 3; ++i)
	{
		Mask::imageViewer[i]->GetRenderer()->RemoveActor(this->imageActor[i]);
		Mask::imageViewer[i]->Render();
	}
}
Mask::~Mask()
{
	//for (int i = 0; i < 3; ++i)
	//{
	//	Mask::imageViewer[i]->GetRenderer()->RemoveActor(this->imageActor[i]);
	//	Mask::imageViewer[i]->Render();
	//}
	//this->imageData->ReleaseData();
}
void Mask::setVisible(bool visible)
{
	int v = visible ? 1 : 0;
	for (int i = 0; i < 3; ++i)
	{
		this->imageActor[i]->SetVisibility(v);
		this->imageActor[i]->Modified();
		Mask::imageViewer[i]->Render();
	}
}
bool Mask::getVisible()
{

	if (this->imageActor[0]->GetVisibility() == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}
//vtkRenderer* Mask::vtkViewRender[3];
vtkImageViewer2* Mask::imageViewer[3];