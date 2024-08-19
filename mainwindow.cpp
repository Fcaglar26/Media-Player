#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,isActive(false)
{
    ui->setupUi(this);

    player = new QMediaPlayer(this); // video oynatma işlemleri için
    video = new QVideoWidget(this); //  üretilen videoyu sunmak için



    connect(player, SIGNAL(durationChanged(qint64)), this, SLOT(slot_durationChanged(qint64)));
    connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(slot_positionChanged(qint64)));
    connect(ui->horizontalSlider, SIGNAL(sliderMoved(int)), this, SLOT(on_horizontalSlider_sliderMoved(int)));
    connect(player,SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)), this, SLOT(checkMediaStatus(QMediaPlayer::MediaStatus)));
    connect(ui->verticalSlider, SIGNAL(valueChanged(int)), this, SLOT(on_verticalSlider_valueChanged(int)));
    connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(setTimeLabel(qint64)));


    setButtonStyles();



}


void MainWindow::showEvent(QShowEvent *ev)
{
    //Videoyu box içinde oynatma kısmı
    QVBoxLayout *layout = new QVBoxLayout(ui->widget_videoWidget);
    layout->addWidget(video);
    addVideoFiles();
    setButtonIconAndPolicy(ui->pushButtonLoop, "/home/firat/İndirilenler/loopicon.png");
    setButtonIconAndPolicy(ui->pushButton_continue, "/home/firat/İndirilenler/playbuton.png");
    // Video çalıştığında ana widgeti taşırmasın
    setPolicy(*ui, *video);



    // login işlemleri için yapılır TODO


}

MainWindow::~MainWindow()
{
    delete ui;
    delete secWindow;



}
void MainWindow::checkMediaStatus(QMediaPlayer::MediaStatus status) {
    switch (status) {
    case QMediaPlayer::NoMedia:

        break;
    case QMediaPlayer::LoadingMedia:

        break;
    case QMediaPlayer::LoadedMedia:

        break;
    case QMediaPlayer::StalledMedia:

        break;
    case QMediaPlayer::BufferingMedia:

        break;
    case QMediaPlayer::BufferedMedia:

        break;
    case QMediaPlayer::EndOfMedia:
        endofMedia();

        break;
    case QMediaPlayer::InvalidMedia:

        break;
    case QMediaPlayer::UnknownMediaStatus:
        break;
    }
}



 void MainWindow:: setPolicy(Ui::MainWindow &ui, QVideoWidget &video)
{
    ui.pushButton_continue->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    ui.pushButton_stop->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    ui.pushButtonLoop->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    ui.pushButton_resize->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    ui.videoPanel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    ui.widget_videoWidget->setFocusPolicy(Qt::StrongFocus);
    ui.pushButton_stop->setFocusPolicy(Qt::NoFocus);
    ui.pushButton_continue->setFocusPolicy(Qt::NoFocus);
    ui.pushButtonLoop->setFocusPolicy(Qt::NoFocus);
    ui.pushButton_resize->setFocusPolicy(Qt::NoFocus);
    ui.horizontalSlider->setFocusPolicy(Qt::NoFocus);
    ui.verticalSlider->setFocusPolicy(Qt::NoFocus);
    ui.radioButton_1x->setFocusPolicy(Qt::NoFocus);
    ui.radioButton_1_25x->setFocusPolicy(Qt::NoFocus);
    ui.radioButton_2x->setFocusPolicy(Qt::NoFocus);
    ui.pushButton_backforward->setFocusPolicy(Qt::NoFocus);
    ui.pushButton_forward->setFocusPolicy(Qt::NoFocus);
    ui.videoPanel->setFocusPolicy(Qt::NoFocus);

    video.setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    video.setAspectRatioMode(Qt::KeepAspectRatio);


}

void MainWindow::controlVisible(Ui::MainWindow &ui , bool isVisible)
{
    ui.pushButtonLoop->setVisible(isVisible);
    ui.horizontalSlider->setVisible(isVisible);
    ui.verticalSlider->setVisible(isVisible);
    ui.Button_Open_Play->setVisible(isVisible);
    ui.videoPanel->setVisible(isVisible);
    ui.pushButton_Add->setVisible(isVisible);
    ui.pushButton_archive->setVisible(isVisible);
}


void MainWindow::setButtonIconAndPolicy(QPushButton *button, const QString &iconPath) {
    button->setIcon(QIcon(iconPath));
    button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

void MainWindow::setterPlayerr(QMediaPlayer *player, const QUrl &fileUrl)
{
    player->setVideoOutput(video);  // Video çıkışını ayarla
    player->setVolume(0);           // Sesi sıfırla
    player->setMedia(fileUrl);      // Medya dosyasını yükle
    player->play();                 // Oynatmayı başlat
}


void MainWindow::on_Button_Open_Play_clicked()
{
    qDebug() << currentFileUrl;
    ui->radioButton_1x->click();

    if (currentFileUrl.isValid())
    {
        setterPlayerr(player, currentFileUrl);
        switchColors("none", "green", *ui);
    }
    else
    {
        qDebug() << "video seçilemedi";
    }
}

void MainWindow::on_videoPanel_itemDoubleClicked()
{
    on_Button_Open_Play_clicked();
}


void MainWindow::on_pushButton_Add_clicked()
{
    QString fileName;
    openFile(fileName, currentFileUrl);

}

void MainWindow::on_videoPanel_itemClicked(QListWidgetItem *item)
{
    currentFileUrl = QUrl::fromLocalFile(item->data(Qt::UserRole).toString());

    qDebug() << "   Current File URL:" << currentFileUrl.toString();
    qDebug() << "File name:" << currentFileUrl.fileName();
    qDebug() << item->data(Qt::UserRole).toString();
}

void MainWindow::on_pushButton_stop_clicked()
{
    player->pause();
    switchColors("red", "white", *ui);
}


void MainWindow::on_pushButton_continue_clicked()
{

    player->play();
    switchColors("white","green", *ui);
}



void MainWindow::on_pushButtonLoop_clicked()
{

    isActive = !isActive;

    if (isActive == true)
    {
        switchColor("grey", *ui);
    }
    else
        switchColor("white", *ui);


    qDebug()<<isActive;


}

void MainWindow::on_radioButton_1x_clicked()
{
    player->setPlaybackRate(1.0);
}


void MainWindow::on_radioButton_1_25x_clicked()
{
    player->setPlaybackRate(1.25);
}


void MainWindow::on_radioButton_2x_clicked()
{
    player->setPlaybackRate(2.0);
}




void MainWindow::on_pushButton_forward_clicked()
{
    qint64 position;
    position = player->position() + 2000; // 2 saniye ileri sar
    player->setPosition(position);
    ui->horizontalSlider->setValue(position);
}


void MainWindow::on_pushButton_backforward_clicked()
{
    qint64 position;
    position = player->position() - 2000; // 2 saniye ileri sar
    player->setPosition(position);
    ui->horizontalSlider->setValue(position);
}


void MainWindow::on_horizontalSlider_sliderMoved(int position)
{

    player->setPosition(position);



}

void MainWindow::slot_durationChanged(qint64 duration)
{
    ui->horizontalSlider->setMaximum(duration);
    qDebug() << duration;
    videoDuration = duration;

}

void MainWindow::slot_positionChanged(qint64 position)
{

    ui->horizontalSlider->setValue(position);

}

void MainWindow::endofMedia()
{
    // Video sona erdiğinde, yeniden başlatmak için kontrol
        if (isActive) {
            player->setPosition(0); // Videoyu başa sar
            player->play();         // Yeniden oynat
        }
        else
        {
            player->stop(); // Döngü etkin değilse durdur
        }
        ui->horizontalSlider->setValue(player->position()); // Slider'ı güncelle
}


void MainWindow::on_verticalSlider_valueChanged(int value)
{

    player->setVolume(value);


}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    int value;
    qint64 position;

    switch (event->key()) {
    case Qt::Key_Up:
        // Sesi artır
        value = player->volume() + 10;
        if (value > 100) value = 100; // maksimum ses seviyesi 100
        player->setVolume(value);
        ui->verticalSlider->setSliderPosition(value);
        break;
    case Qt::Key_Down:
        // Sesi azalt
        value = player->volume() - 10;
        if (value < 0) value = 0; // minimum ses seviyesi 0
        player->setVolume(value);
        ui->verticalSlider->setSliderPosition(value);
        break;
    case Qt::Key_Right:
        // İleri sar
        position = player->position() + 2000; // 2 saniye ileri sar
        if (position > player->duration()) position = player->duration(); // videonun sonuna gelmemesi için kontrol
        player->setPosition(position);
        ui->horizontalSlider->setValue(position);
        break;
    case Qt::Key_Left:
        // Geri sar
        position = player->position() - 2000; // 2 saniye geri sar
        if (position < 0) position = 0; // videonun başına gelmemesi için kontrol
        player->setPosition(position);
        ui->horizontalSlider->setValue(position);
        break;
    default:
        // diğer tuşlar için varsayılan davranış
        QMainWindow::keyPressEvent(event);
        break;
    }
}



void MainWindow::switchColors(const QString &colorStop, const QString &colorContinue, Ui::MainWindow &ui)
{
    QString stopStyle = QString("QPushButton {"
                                "background-color: %1;"
                                "border-radius: 10px;"
                                "border: 2px solid #555;"
                                "color: black;"
                                "padding: 5px;"
                                "min-width: 80px;"
                                "min-height: 25px;"
                                "font-size: 14px;"
                                "}"
                                "QPushButton:hover {"
                                "background-color: red;"
                                "}")
                            .arg(colorStop);

    QString continueStyle = QString("QPushButton {"
                                    "background-color: %1;"
                                    "border-radius: 10px;"
                                    "border: 2px solid #555;"
                                    "color: black;"
                                    "padding: 5px;"
                                    "min-width: 80px;"
                                    "min-height: 25px;"
                                    "font-size: 14px;"
                                    "}"
                                    "QPushButton:hover {"
                                    "background-color: green;"
                                    "}")
                                .arg(colorContinue);

    ui.pushButton_stop->setStyleSheet(stopStyle);
    ui.pushButton_continue->setStyleSheet(continueStyle);

}
void MainWindow::switchColor(const QString &color, Ui::MainWindow &ui)
{
    QString styleSheet = QString("QPushButton {"
                                 "background-color: %1;"
                                "}")
                             .arg(color);

    ui.pushButtonLoop->setStyleSheet(styleSheet);
}

void MainWindow::switchFullscreen(bool isFullScreen) {
    if (!isFullScreen) {
        controlVisible(*ui , false);
        MainWindow::showFullScreen();
    } else {
      controlVisible(*ui , true);
        MainWindow::showNormal();
    }
}


void MainWindow::on_pushButton_resize_clicked()
{
    switchFullscreen(this->isFullScreen);
    this->isFullScreen = !this->isFullScreen;

}

void MainWindow::setTimeLabel(qint64 position){
    int seconds = (position/1000) % 60;
    int minutes = (position/60000) % 60;
    int hours = (position/3600000) % 24;

    QTime time(hours, minutes, seconds);

    // Zamanı "hh:mm:ss" formatında etiket üzerinde gösterme
    ui->timeLabel->setText(time.toString("hh:mm:ss"));

}

void MainWindow::applyButtonStyle(QPushButton *button, const QString &color, const QString &hoverColor) {
    QString styleSheet = QString("QPushButton {"
                                 "background-color: %1;"
                                 "border-radius: 10px;"
                                 "border: 2px solid #555;"
                                 "color: black;"
                                 "padding: 5px;"
                                 "min-width: 80px;"
                                 "min-height: 25px;"
                                 "font-size: 14px;"
                                 "}"
                                 "QPushButton:hover {"
                                 "background-color: %2;"
                                 "font-size: 15px;"
                                 "}")
                             .arg(color)
                             .arg(hoverColor);
    button->setStyleSheet(styleSheet);
}

/*void MainWindow::setButtonStyles()
{
    const QString buttonStyle= QStringLiteral(
        "QPushButton {"
        "background-color: none;"
        "border-radius: 10px;"
        "border: 2px solid #555;"
        "color: black;"
        "padding: 5px;"
        "min-width: 80px;"
        "min-height: 25px;"
        "font-size: 14px;"
        "}"
        );

    const QString playButtonStyle = QStringLiteral(
        "QPushButton:hover {"
        "background-color: green;"
        "font-size: 15px;"
        "}"
        );

    const QString stopButtonStyle = QStringLiteral(
        "QPushButton:hover {"
        "background-color: red;"
        "font-size: 15px;"
        "}"
        );

    ui->pushButton_continue->setStyleSheet(buttonStyle + playButtonStyle);
    ui->pushButton_stop->setStyleSheet(buttonStyle + stopButtonStyle);

    const QString openPlayButtonStyle = QStringLiteral(
        "QPushButton {"
        "background-color: none;"
        "border-radius: 10px;"
        "border: 2px solid #555;"
        "color: black;"
        "padding: 5px;"
        "min-width: 80px;"
        "min-height: 25px;"
        "font-size: 14px;"
        "}"
        "QPushButton:hover {"
        "background-color: grey;"
        "}"
        );

    ui->Button_Open_Play->setStyleSheet(openPlayButtonStyle);
}*/



void MainWindow::addVideoFiles()
{
    QDir dir("/home/firat/Belgeler/mp4");
    for (const QFileInfo &file : dir.entryInfoList(QDir::Files))
    {
        if (file.suffix() == "mp4" || file.suffix() == "mp3")
        {
            QListWidgetItem *item = new QListWidgetItem(file.fileName());
            item->setData(Qt::UserRole, file.absoluteFilePath());
            ui->videoPanel->addItem(item);
            qDebug() << "Added to panel:" << file.fileName();
        }
    }
}


void MainWindow::openFile(QString &fileName, QUrl &fileUrl)
{
    fileName = QFileDialog::getOpenFileName(this, tr("Select File"), "", tr("MP4 Files (*.mp4 *.mp3)"));
    if (!fileName.isEmpty())
    {
        fileUrl = QUrl::fromLocalFile(fileName);
        qDebug() << "Selected file:" << fileName;
        qDebug() << "File URL:" << fileUrl.toString();

        QFileInfo fileInfo(fileName);
        QListWidgetItem *itemManual = new QListWidgetItem(fileInfo.fileName());
        itemManual->setData(Qt::UserRole, fileInfo.absoluteFilePath());
        ui->videoPanel->addItem(itemManual);
    }
}

void MainWindow::setButtonStyles()
{
    applyButtonStyle(ui->pushButton_continue, "green", "darkgreen");
    applyButtonStyle(ui->pushButton_stop, "red", "darkred");
    applyButtonStyle(ui->pushButton_resize, "none", "darkblue");
    applyButtonStyle(ui->Button_Open_Play, "grey", "darkgrey");
    applyButtonStyle(ui->pushButton_resize, "none", "darkgrey");
}

void MainWindow::setStreaming()
{
    QMediaPlaylist *playlist = new QMediaPlaylist;
    playlist->addMedia(
    QUrl("https://dn720408.ca.archive.org/0/items/cars-vhs-1/Cars%20Vhs-1.mp4"));
    player->setPlaylist(playlist);
    player->setVideoOutput(video);
    player->play();

}



void MainWindow::on_pushButton_archive_clicked()
{
    secWindow = new secondWindow(&currentFileUrl,this);
    secWindow->show();
}
