#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <time.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _start(true)
{
    ui->setupUi(this);
    generateProblem(ui->cbTriangle->isChecked(), ui->sbDimension->value());
    t = new QTimer(this);
    connect(t, SIGNAL(timeout()), this, SLOT(updateCountdown()));
    connect(ui->cmdStart,SIGNAL(clicked()), this, SLOT(onStartButton()));

}
void MainWindow::onStartButton(){
    if (_start)
        startCompetition();
    else
        stopCompetition();
}

void MainWindow::updateCountdown()
{
    if (countdown == 0)
    {
        stopCompetition();
        return;
    }
     else
        countdown--;

    ui->labelRun->setText(tr("00:%1").arg(countdown < 10 ? "0"+ QString::number(countdown) : QString::number(countdown)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setEditsVisible(bool vis)
{
    for (int i = 0; i < ui->layAnswer->rowCount(); ++i)
        for (int j = 0; j < ui->layAnswer->columnCount(); ++j)
        {

            QWidget *ed = ui->layAnswer->itemAtPosition(i, j)->widget();
            ed->setVisible(vis);
            ed = (ui->layProblem->itemAtPosition(i, j)->widget());
            ed->setVisible(vis);

        }
}

void MainWindow::switchStart(bool start)
{
    _start = start;
    if (start)
    {
        ui->cmdStart->setText("Start");
    }
    else
    {
        ui->cmdStart->setText("Stop");
    }
    setEditsVisible(!start);
}

void MainWindow::startCompetition()
{
    //everyone goes out of darkness!
    generateProblem(ui->cbTriangle->isChecked(), ui->sbDimension->value());
    switchStart(false);
    countdown = ui->sbDimension->value() == 2 ? 30 : 60;
    t->start(1000);

}

void MainWindow::stopCompetition()
{
    static int calls  = 0;
    calls++;
    qDebug() << "calls to stopCompetition" << calls;
    t->stop();
    setEditsVisible(false);    switchStart(true);
    MatrixXi m = readAnswer();
    MatrixXi ans = input*input;
    if (ans == m)
    {
        ui->labelRun->setText("WIN!");
    }
    else
    {
        ui->labelRun->setText("FAIL!!!");
    }
    std::cout << "Your answer: [ " << m << " ]" << std::endl;
    std::cout << "Correct answer: [ " << ans <<" ]" << std::endl;
    clearForm();

}

void clearLayout(QLayout *layout){
    QLayoutItem *item;
    while((item = layout->takeAt(0))) {
        if (item->layout()) {
            clearLayout(item->layout());
            delete item->layout();
        }
        if (item->widget()) {
            delete item->widget();
        }
        delete item;
    }
}

void MainWindow::clearForm()
{
    switchStart(true);
    clearLayout(ui->layProblem);
    clearLayout(ui->layAnswer);

}

void MainWindow::generateProblem(bool triangle, int n)
{ //Generates a matrix itself for solving
    input.resize(n, n);
    qsrand(time(0));


    for(int i = 0; i<n; ++i)
    {
        for (int j = 0; j<n; ++j)
        {
            if ((i > j) && triangle)
                input(i, j) = 0;
            else
                input(i, j) = qrand() % 21 -10;

            addProblemBox(i, j, input(i, j));
            if (i > 0 || j > 0)
            {
                setTabOrder(ui->layAnswer->itemAtPosition(j == 0 ? i-1 : i,
                                                          j == 0 ? input.cols() - 1 : j - 1
                                                                   )->widget(),
                            ui->layAnswer->itemAtPosition(i, j)->widget());

            }
        }
    }

  switchStart(true);
}

void MainWindow::addProblemBox(int i, int j, int value)
{

    QLineEdit *line = new QLineEdit(QString(value), ui->centralWidget);
    line->setReadOnly(true);
    line->setText(QString::number(value));
    ui->layProblem->addWidget(line, i, j, 1, 1);



    QLineEdit *lineAnswer = new QLineEdit(ui->centralWidget);
    lineAnswer->setValidator(new QIntValidator(-100, 100, this));
    ui->layAnswer->addWidget(lineAnswer, i, j, 1, 1);
}

MatrixXi MainWindow::readAnswer()
{
;
    MatrixXi ans (input.rows(), input.cols());
    int i, j;
    for (i = 0; i < ui->layAnswer->rowCount(); ++i)
        for (j = 0; j < ui->layAnswer->columnCount(); ++j)
        {
            QLineEdit *ed = qobject_cast<QLineEdit*>(ui->layAnswer->itemAtPosition(i, j)->widget());
            if(ed->text().isEmpty())
            {
                ans(i, j) = 0;
            }
            else
                ans(i, j) = ed->text().toInt();

        }

    return ans;
}

