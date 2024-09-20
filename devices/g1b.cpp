#include "device.h"

SerialPort::SerialPort(const wchar_t* port_name,
					   DWORD baud_rate,
				       BYTE byte_size,
					   BYTE stop_bits,
					   BYTE parity) :
	port_name(port_name),
	baud_rate(baud_rate),
	byte_size(byte_size),
	stop_bits(stop_bits),
	parity(parity)
{

}

SerialPort::~SerialPort()
{

}

DeviceG1B::DeviceG1B(const wchar_t* port_name,
					 DWORD baud_rate,
				     BYTE byte_size,
					 BYTE stop_bits,
					 BYTE parity) :
	SerialPort(port_name, baud_rate, byte_size, stop_bits, parity)
{

}

DeviceG1B::~DeviceG1B()
{

}

void DeviceG1B::open()
{
	// open serial port
	serial_handle = CreateFile(port_name,
							   GENERIC_READ | GENERIC_WRITE,
							   0,
							   0,
							   OPEN_EXISTING,
							   FILE_ATTRIBUTE_NORMAL,
							   0);

	// check serial port
	if (serial_handle == INVALID_HANDLE_VALUE) {
		if (GetLastError() == ERROR_FILE_NOT_FOUND) {
			std::cout << "serial port does not exist" << '\n';
		}
		std::cout << "some other error occurred" << '\n';
	}

	// do basic settings
	DCB serial_params = { 0 };
	serial_params.DCBlength = sizeof(serial_params);

	if (!GetCommState(serial_handle, &serial_params)) {
		std::cout << "error getting serial port state" << '\n';
	}

	serial_params.BaudRate = baud_rate;
	serial_params.ByteSize = byte_size;
	serial_params.StopBits = stop_bits;
	serial_params.Parity = parity;

	if (!SetCommState(serial_handle, &serial_params)) {
		std::cout << "error setting serial port state" << '\n';
	}

	// set timeouts
	COMMTIMEOUTS timeout = { 0 };
	timeout.ReadIntervalTimeout = 50;
	timeout.ReadTotalTimeoutConstant = 50;
	timeout.ReadTotalTimeoutMultiplier = 50;
	timeout.WriteTotalTimeoutConstant = 50;
	timeout.WriteTotalTimeoutMultiplier = 10;

	SetCommTimeouts(serial_handle, &timeout);
	if (!SetCommTimeouts(serial_handle, &timeout)) {
		std::cout << "error setting timeout" << '\n';
	}
}

void DeviceG1B::close()
{
	CloseHandle(serial_handle);
}

void DeviceG1B::read()
{
	const int size = 5;
	char buf[size + 1] = { 0 };

	DWORD dwBytesRead = 0;
	if (!ReadFile(serial_handle, buf, size, &dwBytesRead, NULL)) {
		std::cout << "error reading" << '\n';
	}
	else {
		std::cout << buf << '\n';
	}
}

void DeviceG1B::write()
{
	char buf[] = "go\r";
	DWORD size = strlen(buf);

	DWORD dwBytesRead = 0;
	WriteFile(serial_handle, buf, size, &dwBytesRead, NULL);
}
