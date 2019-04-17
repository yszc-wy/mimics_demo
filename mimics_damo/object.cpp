#include "object.h"
#include <vtkActor.h>
#include <vtkProperty.h>
#include <QVTKWidget.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRendererCollection.h>
Object::Object()
{
}
Object::Object(const QString &n, const vtkSmartPointer<vtkActor> actor, const QString& q):name(n),objActor(actor),quality(q)
{
}
Object::~Object()
{
	
}
void Object::setVisible(bool visible)
{
	int v = visible ? 1 : 0;

	this->objActor->SetVisibility(v);
	this->objActor->Modified();
	
	Object::viewWidget->GetRenderWindow()->Render();

}
bool Object::getVisible()
{
	int t=this->objActor->GetVisibility();
	if (t != 0)
	{
		return true;
	}
	return false;
}
void Object::deleteObject()
{
	Object::viewWidget->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->RemoveActor(this->objActor);
	Object::viewWidget->GetRenderWindow()->Render();
}
QVTKWidget* Object::viewWidget;