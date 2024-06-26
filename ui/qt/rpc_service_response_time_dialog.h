/** @file
 *
 * Wireshark - Network traffic analyzer
 * By Gerald Combs <gerald@wireshark.org>
 * Copyright 1998 Gerald Combs
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef __RPC_SERVICE_RESPONSE_TIME_DIALOG_H__
#define __RPC_SERVICE_RESPONSE_TIME_DIALOG_H__

#include "service_response_time_dialog.h"

class QComboBox;

struct _guid_key;
struct _dcerpc_uuid_value;
struct _e_guid_t;
struct _rpc_prog_info_value;

class RpcServiceResponseTimeDialog : public ServiceResponseTimeDialog
{
    Q_OBJECT

public:
    enum RpcFamily {
        DceRpc,
        OncRpc
    };

    RpcServiceResponseTimeDialog(QWidget &parent, CaptureFile &cf, struct register_srt *srt, RpcFamily dlg_type, const QString filter);
    static TapParameterDialog *createDceRpcSrtDialog(QWidget &parent, const QString, const QString opt_arg, CaptureFile &cf);
    static TapParameterDialog *createOncRpcSrtDialog(QWidget &parent, const QString, const QString opt_arg, CaptureFile &cf);

    void addDceRpcProgram(_guid_key *key, struct _dcerpc_uuid_value *value);
    void addDceRpcProgramVersion(_guid_key *key);
    void addOncRpcProgram(uint32_t program, struct _rpc_prog_info_value *value);
    void addOncRpcProgramVersion(uint32_t program, uint32_t version);
    void updateOncRpcProcedureCount(uint32_t program, uint32_t version, int procedure);

    void setDceRpcUuidAndVersion(struct _e_guid_t *uuid, int version);
    void setOncRpcProgramAndVersion(int program, int version);
    void setRpcNameAndVersion(const QString &program_name, int version);

protected:
    virtual void provideParameterData();

public slots:
    void dceRpcProgramChanged(const QString &program_name);
    void oncRpcProgramChanged(const QString &program_name);

private:
    RpcFamily dlg_type_;
    QComboBox *program_combo_;
    QComboBox *version_combo_;
    QList<unsigned> versions_;

    // DCE-RPC
    QMap<QString, struct _guid_key *> dce_name_to_uuid_key_;

    // ONC-RPC
    QMap<QString, uint32_t> onc_name_to_program_;
    int onc_rpc_num_procedures_;

    void clearVersionCombo();
    void fillVersionCombo();

};

#endif // __RPC_SERVICE_RESPONSE_TIME_DIALOG_H__
