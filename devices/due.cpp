#include <direct.h>

#include <QDir>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "device.h"
#include "utility.h"

extern std::string MONITOR_BUFFER_DIR;

DeviceArduinoDue::DeviceArduinoDue(const wchar_t* port_name, DWORD baud_rate,
                                   BYTE byte_size, BYTE stop_bits, BYTE parity)
    : SerialPort(port_name, baud_rate, byte_size, stop_bits, parity),
      activate(true),
      count(0) {}

DeviceArduinoDue::~DeviceArduinoDue() {}

SerialCode DeviceArduinoDue::Open() {
  // open serial port
  serial_handle = CreateFile(port_name, GENERIC_READ | GENERIC_WRITE, 0, 0,
                             OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

  // check serial port
  if (serial_handle == INVALID_HANDLE_VALUE) {
    if (GetLastError() == ERROR_FILE_NOT_FOUND) {
      g_out << "serial port does not exist" << '\n';
      return SERIAL_NO_PORT;
    }
    g_out << "some other error occurred" << '\n';
    return SERIAL_FAIL;
  }

  // do basic settings
  DCB serial_params = {0};
  serial_params.DCBlength = sizeof(serial_params);

  if (!GetCommState(serial_handle, &serial_params)) {
    g_out << "error getting serial port state" << '\n';
    return SERIAL_FAIL_TO_GET_STATE;
  }

  serial_params.BaudRate = baud_rate;
  serial_params.ByteSize = byte_size;
  serial_params.StopBits = stop_bits;
  serial_params.Parity = parity;

  if (!SetCommState(serial_handle, &serial_params)) {
    g_out << "error setting serial port state" << '\n';
    return SERIAL_FAIL_TO_SET_STATE;
  }

  // set timeouts
  COMMTIMEOUTS timeout = {0};
  timeout.ReadIntervalTimeout = 50;
  timeout.ReadTotalTimeoutConstant = 50;
  timeout.ReadTotalTimeoutMultiplier = 50;
  timeout.WriteTotalTimeoutConstant = 50;
  timeout.WriteTotalTimeoutMultiplier = 10;

  SetCommTimeouts(serial_handle, &timeout);
  if (!SetCommTimeouts(serial_handle, &timeout)) {
    g_out << "error setting timeout" << '\n';
    return SERIAL_FAIL_TO_SET_TIMEOUT;
  }

  return SERIAL_OK;
}

SerialCode DeviceArduinoDue::Close() {
  if (!CloseHandle(serial_handle)) {
    return SERIAL_FAIL;
  } else {
    return SERIAL_OK;
  }
}

SerialCode DeviceArduinoDue::Read() {
  const int size = 5;
  char buf[size + 1] = {0};
  DWORD dw_bytes_read = 0;

  if (!ReadFile(serial_handle, buf, size, &dw_bytes_read, NULL)) {
    return SERIAL_FAIL_TO_READ;
  } else {
    g_out << buf << '\n';
    return SERIAL_OK;
  }
}

SerialCode DeviceArduinoDue::Write() {
  char buf[] = "go\r";
  DWORD size = (DWORD)strlen(buf);
  DWORD dw_bytes_read = 0;

  if (!WriteFile(serial_handle, buf, size, &dw_bytes_read, NULL)) {
    return SERIAL_FAIL_TO_WRITE;
  } else {
    g_out << buf << '\n';
    return SERIAL_OK;
  }
}

SerialCode DeviceArduinoDue::Login() { return SERIAL_OK; }

SerialCode DeviceArduinoDue::ReadBufferAndSave() {
  _mkdir(MONITOR_BUFFER_DIR.c_str());
  RemoveAllFilesFromDir(MONITOR_BUFFER_DIR.c_str());

  count = 0;
  BYTE buf[MONITOR_BUFFER_SIZE];
  DWORD dw_bytes_read = 0;

  while (activate) {
    if (!ReadFile(serial_handle, buf, MONITOR_BUFFER_SIZE, &dw_bytes_read,
                  NULL)) {
      return SERIAL_FAIL_TO_READ;
    } else {
      std::string name =
          MONITOR_BUFFER_DIR + "\\buf_" + std::to_string(count) + ".bin";
      std::ofstream(name, std::ios::binary)
          .write(reinterpret_cast<char*>(buf), MONITOR_BUFFER_SIZE);
      count++;
    }
  }

  return SERIAL_OK;
}

SerialCode DeviceArduinoDue::SetFreq(int freq) {
  this->frequency = freq;
  int period = (int)(1.0f / (float)freq * 1000000.0f);
  // g_out << period << '\n';
  std::string period_cmd = std::to_string(period);
  std::string buf = period_cmd + "p";
  buf += std::string("\n");
  g_out << buf << '\n';

  char* cmd = CopyStringToNewedCharArray(buf);
  DWORD size = (DWORD)strlen(cmd);
  DWORD dw_bytes_read = 0;

  if (!WriteFile(serial_handle, cmd, size, &dw_bytes_read, NULL)) {
    delete[] cmd;
    return SERIAL_FAIL_TO_WRITE;
  } else {
    delete[] cmd;
    return SERIAL_OK;
  }
}

SerialCode DeviceArduinoDue::GetFreq(int* freq) {
  *freq = this->frequency;
  return SERIAL_OK;
}

SerialCode DeviceArduinoDue::SetPulseWidth(float pw) {
  this->pulse_width = pw;
  float pw_ns = (float)pw * 1000.0f;
  float period_ns = 1.0f / (float)this->frequency * 1000000000.0f;
  int duty_cycle = (int)(pw_ns / period_ns * 255.0f);
  // g_out << pw_ns << '\n';
  std::string pw_cmd = std::to_string(duty_cycle);
  std::string buf = pw_cmd + "d";
  buf += std::string("\n");
  g_out << buf << '\n';

  char* cmd = CopyStringToNewedCharArray(buf);
  DWORD size = (DWORD)strlen(cmd);
  DWORD dw_bytes_read = 0;

  if (!WriteFile(serial_handle, cmd, size, &dw_bytes_read, NULL)) {
    delete[] cmd;
    return SERIAL_FAIL_TO_WRITE;
  } else {
    delete[] cmd;
    return SERIAL_OK;
  }
}

SerialCode DeviceArduinoDue::GetPulseWidth(float* pw) {
  *pw = this->pulse_width;
  return SERIAL_OK;
}

SerialCode DeviceArduinoDue::On() {
  std::string buf = "output on";
  buf += std::string("\r\n");
  g_out << buf << '\n';

  char* cmd = CopyStringToNewedCharArray(buf);
  DWORD size = (DWORD)strlen(cmd);
  DWORD dw_bytes_read = 0;

  if (!WriteFile(serial_handle, cmd, size, &dw_bytes_read, NULL)) {
    delete[] cmd;
    return SERIAL_FAIL_TO_WRITE;
  } else {
    delete[] cmd;
    return SERIAL_OK;
  }
}

SerialCode DeviceArduinoDue::Off() {
  std::string buf = "output off";
  buf += std::string("\r\n");
  g_out << buf << '\n';

  char* cmd = CopyStringToNewedCharArray(buf);
  DWORD size = (DWORD)strlen(cmd);
  DWORD dw_bytes_read = 0;

  if (!WriteFile(serial_handle, cmd, size, &dw_bytes_read, NULL)) {
    delete[] cmd;
    return SERIAL_FAIL_TO_WRITE;
  } else {
    delete[] cmd;
    return SERIAL_OK;
  }
}