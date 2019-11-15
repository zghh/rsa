#ifndef WINDOW_H
#define WINDOW_H

#include "../core/rsa.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui
{
class window;
}
QT_END_NAMESPACE

class window : public QMainWindow
{
    Q_OBJECT

public:
    window(QWidget *parent = nullptr);
    ~window();
    void encryptAble();
    void encryptDisable();
    void decryptptAble();
    void decryptDisable();

private slots:
    void on_generateButton_clicked();

    void on_encryptPushButton_clicked();

    void on_decryptPushButton_clicked();

    void on_messageTextEdit_textChanged();

    void on_encryptedMessageTextEdit_textChanged();

private:
    Ui::window *ui;
    RSA rsa;
    bool encryptState;
    bool decryptState;
};
#endif // WINDOW_H
