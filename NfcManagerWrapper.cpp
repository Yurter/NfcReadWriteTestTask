#include "NfcManagerWrapper.hpp"
#include <QVariant>

NfcManagerWrapper::NfcManagerWrapper() {
    _manager.startTargetDetection();

    connect(&_manager, &QNearFieldManager::targetDetected
            , [&](QNearFieldTarget* target) {
                _active_target = target;
                emit targetDetected();
            }
    );
    connect(&_manager, &QNearFieldManager::targetLost
            , [&](QNearFieldTarget* target) {
                Q_UNUSED(target);
                _active_target = nullptr;
                emit targetLost();
            }
    );
}

void NfcManagerWrapper::read16BytesFromBlock(int block_id) {
    if (_active_target) {
        constexpr auto COMMAND_READ { 0x30 };
        QByteArray command;
        command.push_back(COMMAND_READ);
        command.push_back(block_id);
        connect(_active_target, &QNearFieldTarget::requestCompleted
                , [&](const QNearFieldTarget::RequestId& id) {
                    const auto response { _active_target->requestResponse(id).toByteArray() };
                    const auto is_response_for_data_read_command {
                        response.size() == 16
                    };
                    if (is_response_for_data_read_command) {
                        emit dataReaded(QString { _active_target->requestResponse(id).toByteArray().toHex() }.toUpper());
                    }
                }
        );
        _active_target->sendCommand(command);
    }
}

void NfcManagerWrapper::write4BytesToBlock(int block_id, QString data) {
    if (_active_target) {
        constexpr auto COMMAND_WRITE { 0xA2 };
        QByteArray command;
        command.push_back(COMMAND_WRITE);
        command.push_back(block_id);
        command.push_back(QByteArray::fromHex(data.left(8).toLatin1()));
        _active_target->sendCommand(command);
    }
}
