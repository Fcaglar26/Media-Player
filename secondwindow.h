#ifndef SECONDWINDOW_H
#define SECONDWINDOW_H


#include "qurl.h"
#include <QWidget>

struct Movies {
    QString name{};
    QUrl url{};
};

namespace Ui {
class secondWindow;
}

class secondWindow : public QWidget
{
    Q_OBJECT

public:
    explicit secondWindow(QUrl* fileUrl, QWidget *parent = nullptr);
    ~secondWindow();

signals:
    void videoSelected(const QString &url);

private slots:
    void on_ChooseandPlayButton_clicked();
    //void playVideoFromUrl(const QString &url);

private:
    Ui::secondWindow *ui;
    void showEvent(QShowEvent *e);
    void setMedias();

    QString name;
    QUrl url;
    //Movies movies;
    QUrl* m_fileUrl = nullptr;
};

#endif // SECONDWINDOW_H
