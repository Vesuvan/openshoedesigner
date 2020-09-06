///////////////////////////////////////////////////////////////////////////////
// Name               : MidiPort.h
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 26.09.2017
// Copyright          : (C) 2017 Tobias Schaefer <tobiassch@users.sourceforge.net>
// Licence            : GNU General Public License version 3.0 (GPLv3)
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef SRC_CONTROLLER_MIDIPORT_H_
#define SRC_CONTROLLER_MIDIPORT_H_

/*!\class MidiPort
 * \brief Connection to MIDI Instruments
 *
 * This class encapsulates the library portmidi to connect to MIDI inputs.
 * Latency compensation is not used.
 */

#include "../Config.h"

#if !(defined(linux) || defined(__linux))
#undef _USE_MIDI
#endif

#ifdef _USE_MIDI
#include "portmidi.h"
#endif
#include <cstddef>
#include <string>
#include <cstdint>

#include <memory>
#include <vector>
#include <array>
#include <set>

class MidiDevice {
	friend class MidiPort;
public:
	MidiDevice(const std::string & name);
	virtual ~MidiDevice();

	void Close(void);

	bool operator==(const std::string & name) const;

	bool IsOpen(void) const; //!< Has this instance an open connection to a device?
	bool IsInput(void) const;
	bool IsOutput(void) const;
	bool IsBidirectional(void) const;
	std::string GetName(void) const;

	void Send(uint8_t from = 0, uint8_t to = 255);
	void Flush(void);
	bool Poll(void);
	bool PollEvent(uint8_t *data0, uint8_t *data1, uint8_t *data2);

	std::array <uint8_t, 256> cc; // MIDI CC values
private:
	std::string name;
	std::array <uint8_t, 256> ccold; // Old MIDI CC values to determin changes to send out

#ifdef _USE_MIDI
	PmEvent buffer[1];
	PortMidiStream *input = NULL;
	PortMidiStream *output = NULL;
#endif
};

class MidiPort {
public:
	enum class Direction {
		Input, Output, Bidirectional
	};

	MidiPort();
	MidiPort(const MidiPort& other) = delete;
	MidiPort& operator=(const MidiPort& other) = delete;
	virtual ~MidiPort();

//	void CycleLibrary(void); //!< Closes all open connections and cycles the portmidi library. Needed when a new device is connected, while the software is running.

	std::set <std::string> GetDeviceNames(void) const;
	int GetDeviceCount(void) const;

	int GetDefaultInputDevice(void) const;
	int GetDefaultOutputDevice(void) const;

	std::string GetDeviceName(int nr) const;
	std::string GetDeviceInterfaceName(int nr) const;

	bool IsDeviceInput(int nr) const;
	bool IsDeviceOutput(int nr) const;
	bool IsDeviceAvailable(int nr) const; //!< i.e. not used by this class or somebody else.

	std::shared_ptr <MidiDevice> Open(const std::string & name,
			Direction direction);

	void Close(const std::string & name);
	void Close(size_t idx);
	void CloseAll(void);

	std::shared_ptr <MidiDevice> GetFirstOpenDevice(Direction direction);

	bool IsLastInstance(void) const;

	std::string error;

private:
	std::vector <std::shared_ptr <MidiDevice>> devices;
#ifdef _USE_MIDI
	PmError status;
	PmError length;
	static std::string DecodeError(PmError err);
#endif
private:
	// The instance counter is needed, because the Pm_Initialize() and Pm_Terminate() functions are global.
	static size_t instancecounter;
};

#endif /* SRC_CONTROLLER_MIDIPORT_H_ */
