#include "pump_view.h"

#include "../widgets/login_subwindow.h"
#include "../widgets/msg_subwindow.h"

extern int g_mode;

PumpView::PumpView(int w, int h, MetParaList* para_list, QWidget* parent)
    : w(w),
      h(h),
      para_list(para_list),
      serial_status(SERIAL_OK),
      QWidget(parent) {
  if (g_mode == Mode::UI_TEST || g_mode == Mode::MONITOR_TEST) {
    serial_status = SERIAL_OK;
    reglo_icc = nullptr;
    SetupUi();
    return;
  }

  std::string str = para_list->list[PUMP_KEYWORD].str;
  std::wstring wstring = L"\\\\.\\" + std::wstring(str.begin(), str.end());
  LPCWSTR port = wstring.data();
  std::wcout << "PumpView:" << port << " " << sizeof(port) << '\n';

  reglo_icc = new DeviceRegloIcc(port, CBR_9600, 8, ONESTOPBIT, NOPARITY);
  serial_status = reglo_icc->Open();

  if (serial_status != SERIAL_OK) {
    MetMsgSubwindow("device RegloIcc open failed");
    reglo_icc = nullptr;
    return;
  } else {
    g_out << "device RegloIcc opened" << '\n';
    SetupUi();
  }
}

PumpView::~PumpView() {
  if (reglo_icc && reglo_icc->Close() != SERIAL_OK) {
    MetMsgSubwindow("device RegloIcc close failed");
  }
}

void PumpView::SetupUi() {
  setFixedWidth(w);
  setFixedHeight(h);

  MetPumpChannelStyle pump_channel_style;
  channel_1 =
      new MetPumpChannel(pump_channel_style, reglo_icc, 1, "Channel 1", this);
  channel_2 =
      new MetPumpChannel(pump_channel_style, reglo_icc, 2, "Channel 2", this);

  layout = new QVBoxLayout(this);
  layout->addWidget(channel_1, 0, Qt::AlignCenter);
  layout->addWidget(channel_2, 0, Qt::AlignCenter);
  setLayout(layout);
}

void PumpView::Read() {
  if (reglo_icc->Read() != SERIAL_OK) {
    MetMsgSubwindow("device RegloIcc read failed");
  }
}

void PumpView::Write() {
  if (reglo_icc->Write() != SERIAL_OK) {
    MetMsgSubwindow("device RegloIcc write failed");
  }
}