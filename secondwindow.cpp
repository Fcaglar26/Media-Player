#include "secondwindow.h"
#include "qdebug.h"
#include "qurl.h"
#include "ui_secondwindow.h"
#include "vector"
#include <QMediaPlaylist>
#include <mainwindow.h>


secondWindow::secondWindow(QUrl* fileUrl, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::secondWindow)
    , m_fileUrl(fileUrl)
{
    ui->setupUi(this);

}

secondWindow::~secondWindow()
{
    delete ui;
    delete m_fileUrl;
}
void secondWindow::showEvent(QShowEvent *e)
{
    setMedias();


}

void secondWindow::setMedias()
{

    std::vector<Movies> links{};
    Movies m1;
    m1.name = "Cars";
    m1.url = "https://dn720408.ca.archive.org/0/items/cars-vhs-1/Cars%20Vhs-1.mp4";
    Movies m2;
    m2.name = "Spider-Man Animated Series";
    m2.url = "https://dn720308.ca.archive.org/0/items/spider-mantheanimatedseries/01x01%20Night%20of%20the%20Lizard.mp4";
    Movies m3;
    m3.name = "Scooby-Doo";
    m3.url = "https://dn720309.ca.archive.org/0/items/scooby-doo-where-are-you-what-a-night-for-a-knight_202108/Scooby%20Doo%20Where%20Are%20You%20%20What%20a%20Night%20for%20a%20Knight.ia.mp4";
    Movies m4;
    m4.name = "Bugs Bunny";
    m4.url = "https://archive.org/serve/bugs-bunny-51st-special-cartoon-network/Bugs%20Bunny%2051st%20Special%20Cartoon%20Network.mp4";

    links.push_back(m1);
    links.push_back(m2);
    links.push_back(m3);
    links.push_back(m4);



    for (const auto &movie : links) {
        QListWidgetItem *movieItem = new QListWidgetItem(movie.name);
        qDebug() << "Adding movie:" << movie.name << "with URL:" << movie.url;
        movieItem->setData(Qt::UserRole, movie.url);
        ui->listMovieWidget->addItem(movieItem);
    }

}

void secondWindow::on_ChooseandPlayButton_clicked()
{
    QListWidgetItem *selectedItem = ui->listMovieWidget->currentItem();
    if (selectedItem) {
        *m_fileUrl = selectedItem->data(Qt::UserRole).toString();
        qDebug() << "Basıldı:";
        qDebug() << *m_fileUrl;

    }

    close();
}



