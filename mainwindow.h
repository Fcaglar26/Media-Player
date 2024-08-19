#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVideoWidget>
#include <QMediaPlaylist>
#include <QMediaPlayer>
#include <QFileDialog>
#include <QWidget>
#include <QVBoxLayout>
#include <QKeyEvent>
#include <QResizeEvent>
#include <QTime>
#include <QListWidgetItem>
#include "secondwindow.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    friend class secondWindow;
protected:
    void showEvent(QShowEvent *ev);



private slots:
    void on_Button_Open_Play_clicked();
    void on_horizontalSlider_sliderMoved(int value);
    void slot_durationChanged(qint64 duration);
    void slot_positionChanged(qint64 position);
    void endofMedia();
    void on_verticalSlider_valueChanged(int value);
    void keyPressEvent(QKeyEvent *event);
    void on_pushButton_stop_clicked();
    void on_pushButton_continue_clicked();
    void on_pushButtonLoop_clicked();
    void on_pushButton_resize_clicked();
    void setPolicy(Ui::MainWindow &ui, QVideoWidget &video);
    void setButtonIconAndPolicy(QPushButton *button, const QString &iconPath);
    void switchFullscreen(bool isFullScreen);
    void setterPlayerr(QMediaPlayer *player, const QUrl &fileUrl);
    void controlVisible(Ui::MainWindow &ui , bool isVisible);
    void switchColors(const QString &colorStop, const QString &colorContinue, Ui::MainWindow &ui);
    void switchColor(const QString &color, Ui::MainWindow &ui);
    //void getFile(QString &FileName, QUrl &fileUrl);
    void checkMediaStatus(QMediaPlayer::MediaStatus status);
    void setTimeLabel(qint64 duration);
    void setButtonStyles();
    void on_radioButton_1x_clicked();
    void on_radioButton_1_25x_clicked();
    void on_radioButton_2x_clicked();
    void on_pushButton_forward_clicked();
    void on_pushButton_backforward_clicked();
    void addVideoFiles();
    void on_videoPanel_itemClicked(QListWidgetItem *item);
    void on_videoPanel_itemDoubleClicked();
    void on_pushButton_Add_clicked();
    void openFile(QString &fileName, QUrl &fileUrl);
    void applyButtonStyle(QPushButton *button, const QString &color, const QString &hoverColor);
    void setStreaming();
    void on_pushButton_archive_clicked();

private:
    Ui::MainWindow *ui;
    QMediaPlayer *player;
    QVideoWidget *video;
    QMediaPlayer::MediaStatus status;
    qint64 videoDuration;
    QUrl currentFileUrl;
    qint64 sonsure;
    qint64 currentsure;
    secondWindow *secWindow;


    bool is_Paused = true;
    bool is_Muted = false;
    bool isActive;
    bool isFullScreen = false;

  friend class secondWindow;

};
#endif // MAINWINDOW_H
