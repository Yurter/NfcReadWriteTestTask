#pragma once
#include <QNearFieldManager>

class NfcManagerWrapper : public QObject {

    Q_OBJECT

public:

    NfcManagerWrapper();

signals:

    void                    dataReaded(QString data);

    void                    targetDetected();
    void                    targetLost();

public:

    Q_INVOKABLE void        read16BytesFromBlock(int block_id);
    Q_INVOKABLE void        write4BytesToBlock(int block_id, QString data);

private:

    QNearFieldManager       _manager;
    QNearFieldTarget*       _active_target { nullptr };

};
