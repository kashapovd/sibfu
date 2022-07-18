#ifndef AES_H
#define AES_H

#include <QVector>
#include <QByteArray>

class aes
{
    struct aesSettings {
        uint nb;
        uint nr;
        uint nk;
    } settings;

    aesSettings aes256Settings = {.nb = 4, .nr = 14, .nk=8};
    aesSettings aes192Settings = {.nb = 4, .nr = 12, .nk=6};
    aesSettings aes128Settings = {.nb = 4, .nr = 10, .nk=4};

    using StateVector = QVector<QVector<uint8_t>>;
    StateVector state;

    void subBytes(bool inv = false);
    void shiftRows(bool inv = false);
    void mixColumns(bool inv = false);
    void addRoundKey(QVector<QVector<uint8_t>> keySchedule, uint round = 0);
    QVector<QVector<uint8_t>> keyExpansion(QVector<uint8_t> key);
    void leftRightShift(QVector<uint8_t> &array, uint count, bool inv = false);

    uint8_t mul_by_02(uint8_t num);
    uint8_t mul_by_03(uint8_t num);
    uint8_t mul_by_09(uint8_t num);
    uint8_t mul_by_0b(uint8_t num);
    uint8_t mul_by_0d(uint8_t num);
    uint8_t mul_by_0e(uint8_t num);

public:
    enum mode {aes128, aes192, aes256};
    aes(mode m = aes256);
    void setMode(mode m);
    static QString textCompletion(QString text);
    const uint blockSize = 16;
    QVector<uint8_t> encode(QVector<uint8_t> plainBytes, QVector<uint8_t> key);
    QVector<uint8_t> decode(QVector<uint8_t> cipherBytes, QVector<uint8_t> key);
};
#endif // AES_256_H
