
#include "renderwin.h"

#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyDataAlgorithm.h>
#include <vtkPolyDataReader.h>
#include <vtkProperty.h>
#include <vtkCamera.h>
#include <vtkSmartPointer.h>

#include <iostream>

using namespace std;

namespace snow {
RenderWin::RenderWin(void) {
}

RenderWin::~RenderWin(void) {

}

void RenderWin::start(const std::string& file_path) {
    cout << "rend file:" << file_path << endl;    
    vtkSmartPointer<vtkPolyDataReader> reader =
        vtkSmartPointer<vtkPolyDataReader>::New();
    reader->SetFileName(file_path.c_str());
    reader->Update();

    //vtkSmartPointer<vtkPolyDataAlgorithm> al =
    //    vtkSmartPointer<vtkPolyDataAlgorithm>::New();
    //al->SetInputData(reader->GetOutput());

    vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputData(reader->GetOutput());
    //mapper->SetInputConnection(al->GetOutputPort());

    vtkSmartPointer<vtkActor> cylinderActor =
    vtkSmartPointer<vtkActor>::New();
    cylinderActor->SetMapper(mapper);
    cylinderActor->GetProperty()->SetColor(1.0000, 0.3882, 0.2784);
    cylinderActor->GetProperty()->SetRepresentationToWireframe();
    cylinderActor->RotateX(30.0);
    cylinderActor->RotateY(-45.0);

    vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
    renderer->AddActor(cylinderActor);
    renderer->SetBackground(0.1, 0.2, 0.4);
    // Zoom in a little by accessing the camera and invoking its "Zoom" method.
    renderer->ResetCamera();
    //renderer->GetActiveCamera()->Zoom(1.5);

    // The render window is the actual GUI window
    // that appears on the computer screen
    vtkSmartPointer<vtkRenderWindow> renderWindow =
      vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->SetSize(200, 200);
    renderWindow->AddRenderer(renderer);

    // The render window interactor captures mouse events
    // and will perform appropriate camera or actor manipulation
    // depending on the nature of the events.
    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
      vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor->SetRenderWindow(renderWindow);

    // This starts the event loop and as a side effect causes an initial render.
    renderWindowInteractor->Start();
}

}
