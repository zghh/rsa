#include "window.h"
#include "ui_window.h"
#include "../core/rsa.h"
#include <QListView>
#include <QDebug>

window::window(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::window)
{
    ui->setupUi(this);
    ui->levelComboBox->setView(new QListView());
    encryptDisable();
    decryptDisable();
}

window::~window()
{
    delete ui;
}

void window::encryptAble()
{
    encryptState = true;
    ui->encryptPushButton->setCursor(Qt::ArrowCursor);
    ui->encryptPushButton->setStyleSheet("border-color:#1890ff;background-color:#1890ff;color:#fff");
}

void window::encryptDisable()
{
    encryptState = false;
    ui->encryptPushButton->setCursor(Qt::ForbiddenCursor);
    ui->encryptPushButton->setStyleSheet("border-color:#f5f5f5;background-color:#f5f5f5;color:rgba(0,0,0,0.25)");
}

void window::decryptptAble()
{
    decryptState = true;
    ui->decryptPushButton->setCursor(Qt::ArrowCursor);
    ui->decryptPushButton->setStyleSheet("border-color:#1890ff;background-color:#1890ff;color:#fff");
}

void window::decryptDisable()
{
    decryptState = false;
    ui->decryptPushButton->setCursor(Qt::ForbiddenCursor);
    ui->decryptPushButton->setStyleSheet("border-color:#f5f5f5;background-color:#f5f5f5;color:rgba(0,0,0,0.25)");
}

void window::on_generateButton_clicked()
{
    QString currentText = ui->levelComboBox->currentText();
    int bit = currentText.left(currentText.indexOf(' ')).toInt();
    this->rsa = RSA(bit);

    char *s = new char[(bit >> 2) + 10];

    rsa.GetP().Out(s);
    QString p(s);
    ui->pTextBrowser->setText(p);

    rsa.GetQ().Out(s);
    QString q(s);
    ui->qTextBrowser->setText(q);

    rsa.GetN().Out(s);
    QString n(s);
    ui->nTextBrowser->setText(n);

    rsa.GetD().Out(s);
    QString d(s);
    ui->dTextBrowser->setText(d);

    rsa.GetE().Out(s);
    QString e(s);
    ui->eTextBrowser->setText(e);

    int len = ui->messageTextEdit->toPlainText().toLocal8Bit().length();
    if (!encryptState && rsa.GetBit() != 0 && len > 0 && len <= (rsa.GetBit() >> 3))
        encryptAble();
    bool isEmpty = (ui->encryptedMessageTextEdit->toPlainText().length() == 0);
    if (!decryptState && rsa.GetBit() != 0 && !isEmpty)
        decryptptAble();

    delete[] s;
}

void window::on_encryptPushButton_clicked()
{
    if (!encryptState)
        return;
    QByteArray ba = ui->messageTextEdit->toPlainText().toLocal8Bit();
    char *message = new char[ba.length() + 10];
    memcpy(message, ba.data(), ba.length() + 5);
    char *ciphertext = new char[(this->rsa.GetBit() >> 2) + 10];
    rsa.Encrypt(message, ciphertext);
    ui->encryptedMessageTextEdit->setText(QString(ciphertext));

    delete[] ciphertext;
    delete[] message;
}

void window::on_decryptPushButton_clicked()
{
    if (!decryptState)
        return;
    QByteArray ba = ui->encryptedMessageTextEdit->toPlainText().toLocal8Bit();
    char *encryptedMessage = new char[ba.length() + 10];
    memcpy(encryptedMessage, ba.data(), ba.length() + 5);
    char *text = new char[(this->rsa.GetBit() >> 2) + 10];
    rsa.Decrypt(encryptedMessage, text);
    ui->messageTextEdit->setText(QString::fromLocal8Bit(text));

    delete[] text;
    delete[] encryptedMessage;
}

void window::on_messageTextEdit_textChanged()
{
    int len = ui->messageTextEdit->toPlainText().toLocal8Bit().length();
    if (!encryptState && rsa.GetBit() != 0 && len > 0 && len <= (rsa.GetBit() >> 3))
        encryptAble();
    if (encryptState && (rsa.GetBit() == 0 || len == 0 || len > (rsa.GetBit() >> 3)))
        encryptDisable();
}

void window::on_encryptedMessageTextEdit_textChanged()
{
    bool isEmpty = (ui->encryptedMessageTextEdit->toPlainText().length() == 0);
    if (!decryptState && rsa.GetBit() != 0 && !isEmpty)
        decryptptAble();
    if (decryptState && (rsa.GetBit() == 0 || isEmpty))
        decryptDisable();
}
