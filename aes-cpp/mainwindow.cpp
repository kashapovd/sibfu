#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

QString byteVectorToQString(QVector<uint8_t> vec) {
    QByteArray byteArray;

    for(const auto &i: vec)
        byteArray.push_back(i);

    auto text = QString::fromUtf8(byteArray);

    return text;
}

QVector<uint8_t> QStringToByteVector(QString text) {
    QByteArray byteArray = text.toUtf8();
    QVector<uint8_t> textBytes;

    for(const auto &i : byteArray)
        textBytes.push_back(i);

    return textBytes;
}

void MainWindow::on_encryptButton_clicked() {
    QVector<uint8_t> plainBytes = QStringToByteVector(aes::textCompletion(ui->plainTextEdit->toPlainText()));
    QVector<uint8_t> key = QStringToByteVector(ui->lineKeyEdit->text().trimmed());
    QString cipherBytes;
    QVector<uint8_t> block(cryptor.blockSize);

    int n = 0;
    for(const auto &i: plainBytes) {
        block[n++] = i;

        if(n == 16) {
            block = cryptor.encode(block, key);
            for(const auto &j : block)
                cipherBytes += QString::number(j) + ":";
            n = 0;
        }
    }

    ui->plainTextEdit_2->clear();
    ui->plainTextEdit_2->appendPlainText(cipherBytes);
}

void MainWindow::on_decryptButton_clicked() {
    auto cipherBytes = ui->plainTextEdit_2->toPlainText();
    auto key = QStringToByteVector(ui->lineKeyEdit->text());
    QVector<uint8_t> plainBytes;
    QVector<uint8_t> block(cryptor.blockSize);

    int n = 0;
    QString s;
    for(const auto &i : cipherBytes) {
        if(i == ":") {
            if(s != "") block[n++] = s.toInt();
            s = "";
        }
        else s = s + i;

        if(n == 16) {
            block = cryptor.decode(block, key);
            for(const auto &j : block) plainBytes.push_back(j);
            n = 0;
        }
    }

    ui->plainTextEdit->clear();
    ui->plainTextEdit->setPlainText(byteVectorToQString(plainBytes).trimmed());
}

void MainWindow::on_comboBox_activated(const QString &arg) {
    if (arg == "aes128") {
        cryptor.setMode(aes::mode::aes128);
    }
    else if (arg == "aes192")
        cryptor.setMode(aes::mode::aes192);
    else
        cryptor.setMode(aes::mode::aes256);
}
