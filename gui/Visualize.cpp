/*
 * Visualize.cpp: implements the visualize tab
 */

#include <QDebug>
#include <QMessageBox>
#include <QPixmap>
#include <QFileDialog>

#include <vtkSmartPointer.h>
#include <vtkStructuredPoints.h>
#include <vtkStructuredPointsReader.h>
#include <vtkCubeSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkPlane.h>
#include <vtkCutter.h>
#include <vtkProperty.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkOBJReader.h>
#include <vtkLookupTable.h>


#include "MainWindow.h"

void MainWindow::visualizeUpdate() {

  if(buildTimesteps() < 1) {
    visualizeDisplay->clear();
    return;
  }
  
  on_origin_valueChanged();
    
  visualizeRender();    
  
  
  visualizeDisplay->update(sim.getDelx().toDouble(), sim.getDely().toDouble(),
                      sim.getDelz().toDouble(),
                      sim.getImax().toDouble(), sim.getJmax().toDouble(),
                      sim.getKmax().toDouble(),
                      sim.getOrigin(0).toDouble(), sim.getOrigin(1).toDouble(), sim.getOrigin(2).toDouble());

  //visualizeDisplay->connectSTL(sim.getStlFilename());
 

}

void MainWindow::on_timesteps_currentItemChanged() {
  visualizeRender();
}
void MainWindow::on_xNormal_toggled() {
  updateSlider();
  visualizeRender();
}
void MainWindow::on_yNormal_toggled() {
  updateSlider();
  visualizeRender();
}
void MainWindow::on_zNormal_toggled() {
  updateSlider();
  visualizeRender();
}
void MainWindow::on_contourVOF_toggled() {
  visualizeRender();
}
void MainWindow::on_contourP_toggled() {
  visualizeRender();
}
void MainWindow::on_contourK_toggled() {
  visualizeRender();
}
void MainWindow::on_showAxis_toggled() {
  if(ui.showAxis->isChecked()) 
    visualizeDisplay->ShowAxis();
  else
    visualizeDisplay->HideAxis();  
  ui.vis->update();
}
void MainWindow::on_showLegend_toggled() {

  if(ui.showLegend->isChecked()) 
    visualizeDisplay->showLegend();
  else
    visualizeDisplay->hideLegend();
      
  ui.vis->update();
}
void MainWindow::on_contourVorticity_toggled() {
  visualizeRender();
} 
void MainWindow::on_showVectors_toggled() {
  visualizeRender();
}
void MainWindow::on_blockObstacles_toggled() {
  visualizeRender();
}
void MainWindow::on_showMesh_toggled() {
  if(ui.showMesh->isChecked())
    visualizeDisplay->ShowMesh();
  else
    visualizeDisplay->HideMesh();
  
  ui.vis->update();
}

void MainWindow::updateSlider() {
  
  double extent, position;
  bool ok;

  if(ui.xNormal->isChecked()) {
    extent = sim.getDelx().toDouble(&ok) * sim.getImax().toDouble(&ok);
  } else if(ui.yNormal->isChecked()) {
    extent = sim.getDely().toDouble(&ok) * sim.getJmax().toDouble(&ok); 
  } else {
    extent = sim.getDelz().toDouble(&ok) * sim.getKmax().toDouble(&ok);
  }

  position = (double) ui.origin->sliderPosition();
  position /= 99;
  position *= extent;

  ui.originText->setText(QString::number(position, 'f', 2));
  
}

void MainWindow::on_origin_valueChanged() {
  updateSlider();

  visualizeRender();
}

int MainWindow::buildTimesteps() {
  int count = 0;

  ui.timesteps->clear();  
  
  sim.trackRewind();

  while(sim.getTrackNext() >= 0) {
    ui.timesteps->addItem(sim.getTrackT());
    count++;
  }
  
  return count;
}

void MainWindow::on_updateRange_toggled() {
  double a, b;
  bool ok_a, ok_b;
  
  a = ui.from->toPlainText().toDouble(&ok_a);
  b = ui.to->toPlainText().toDouble(&ok_b);
  
  if(b>a && ok_a && ok_b && ui.updateRange->isChecked()) {
    visualizeDisplay->setRange(a,b);
    ui.vis->update();
  }
  else {
  	visualizeRender();
  }
}

void MainWindow::on_saveJPEG_clicked() {
  QString file = QFileDialog::getSaveFileName(this, tr("Save Image"), 
    QDir::homePath(), tr("png files (*.png)"));
  QPixmap p = QPixmap::grabWidget(ui.vis);
  p.save(QString(file),0,100);
  
}

void MainWindow::visualizeRender() {

    double origin, del;
    int normal;

    QListWidgetItem *item = ui.timesteps->currentItem();
    if(item == NULL) return;

    QString vtkFile = sim.getTrackN(item->text());
    QString vectFile, volFile;
    vtkFile.append(".vtk");

    vectFile = vtkFile;

    if(ui.contourVOF->isChecked()) {
      vtkFile.prepend("vof_");
    } else if(ui.contourP->isChecked()) {
      vtkFile.prepend("P_");
    } else if(ui.contourK->isChecked()) {
      vtkFile.prepend("k_");
    } else if(ui.contourVorticity->isChecked()) {
      vtkFile.prepend("vorticity_");
    } else {
      vtkFile.prepend("U_");
    }
    vectFile.prepend("vtk/U_");
    volFile = "vtk/fv_0.vtk";
    vtkFile.prepend("vtk/");

    if(!QFile::exists(vtkFile)) {
      QMessageBox msgBox;
      vtkFile.prepend("Failed to open VTK file: ");
      msgBox.setText(vtkFile);
      msgBox.exec();
    }

  origin = ui.originText->text().toDouble();

  if(ui.xNormal->isChecked()) {
    normal = 0;
    del = sim.getDelx().toDouble();
  } else if(ui.yNormal->isChecked()) {
    normal = 1;
    del = sim.getDely().toDouble();
  } else {
    normal = 2;
    del = sim.getDelz().toDouble();
  }

  if(!ui.contourVelocity->isChecked() && !ui.contourVorticity->isChecked()) 
    visualizeDisplay->clip(vtkFile, normal, origin);
  else if(ui.contourVorticity->isChecked())
    visualizeDisplay->clipVector(vtkFile, normal, origin, true);
  else
    visualizeDisplay->clipVector(vtkFile, normal, origin, false);

  if(ui.showVectors->isChecked())
    visualizeDisplay->vector(vectFile, normal, origin);
  else
    visualizeDisplay->hideVector();

  if(ui.blockObstacles->isChecked())
    visualizeDisplay->block(volFile, normal, origin, del);
  if(ui.showMesh->isChecked())
    visualizeDisplay->ShowMesh();
  else
    visualizeDisplay->HideMesh();
    
  if(ui.showAxis->isChecked()) 
    visualizeDisplay->ShowAxis();
  else
    visualizeDisplay->HideAxis();
  if(ui.showLegend->isChecked()) 
    visualizeDisplay->showLegend();
  else
    visualizeDisplay->hideLegend();
  
  double a, b;
  bool ok_a, ok_b;
  
  a = ui.from->toPlainText().toDouble(&ok_a);
  b = ui.to->toPlainText().toDouble(&ok_b);
  
  if(b>a && ok_a && ok_b && ui.updateRange->isChecked()) {
    visualizeDisplay->setRange(a,b);
  }
  
  ui.vis->update();
}
