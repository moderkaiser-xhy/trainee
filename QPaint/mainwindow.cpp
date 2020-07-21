#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    paint_desk = new PaintDesk(this);
    ui->graphicsView->setScene(paint_desk);

    QPixmap pix;
    pix.load("/home/moderkaiser/thesis/dataset/left/000004.png");
    qreal width = pix.width(); //获得以前图片的宽和高
    qreal height = pix.height();
    paint_desk->setSceneRect(0,0,width,height);
    //paint_desk->setBackgroundBrush(pix);
    //paint_desk->set
    //setCacheMode(QGraphicsView::CacheBackground)
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_star_Button_clicked()
{
    paint_desk->setMode(PaintDesk::StarMode);
}


void MainWindow::on_unite_Button_clicked()
{
   paint_desk->setMode(PaintDesk::UnitMode);
}

void MainWindow::on_hand_Button_clicked()
{
    paint_desk->setMode(PaintDesk::NoMode);
}
