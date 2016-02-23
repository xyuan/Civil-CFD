/*
 * SolverDialog.h 
 *
 * User interface for solver dialog
 */

#ifndef SOLVER_DIALOG_H
#define SOLVER_DIALOG_H

#include <QDialog>
#include <QProcess>

#include "ui_solver.h"

#include "Simulation.h"

class SolverDialog : public QDialog {

  Q_OBJECT

public:

  SolverDialog(Simulation &sim, QString appPath);

private slots:
  void error(QProcess::ProcessError error);
  void finished(int exitCode, QProcess::ExitStatus status);
  void stateChanged(QProcess::ProcessState state);
  void readyReadStandardOutput();
  void on_Return_clicked();
  void on_Stop_clicked();

private:
  Ui::Solver ui;

  QProcess *process;

  bool stopped;
  double stopT;
};



#endif