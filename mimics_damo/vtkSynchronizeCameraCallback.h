#pragma once
#include <vtkCommand.h>
#include <vtkObject.h>
#include <vtkCamera.h>
#include <vtkRenderer.h>
class vtkSynchronizeCameraCallback : public vtkCommand
{
public:
	static vtkSynchronizeCameraCallback *New()
	{
		return new vtkSynchronizeCameraCallback;
	}

	vtkSynchronizeCameraCallback()
	{

	}
	virtual void Execute(vtkObject *caller, unsigned long event, void *)
	{
		vtkCamera* camera = reinterpret_cast<vtkCamera*>(caller);
		cursorRen->SetActiveCamera(camera);
		cursorRen->Render();
	}
	vtkRenderer *cursorRen;
};