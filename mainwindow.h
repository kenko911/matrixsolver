#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <Eigen/Dense>
using namespace Eigen;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:

    Ui::MainWindow *ui;
    QTimer *t;
    MatrixXi input;
    void generateProblem(bool triangle, int n);
    MatrixXi readAnswer(); //reads answer from user
    void clearForm(); //removes all textboxes
    void addProblemBox(int, int, int); //adds an textbox for matrix i/o to position (i, j) with value(3rd arg)

    int countdown; //countdown
    void setEditsVisible(bool);
    void switchStart(bool);// switches the role of start button
    bool _start;

private slots:
    void startCompetition(); // starts the ball rolling
    void stopCompetition(); // stops
    void onStartButton();
    void updateCountdown(); //updates the "RUN" label
};

#endif // MAINWINDOW_H
