///////////////////////////////////////////////////////////////////////////////
// Name               : MidiPort.cpp
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

#include "MidiPort.h"

#include <algorithm>
#include <cassert>
#include <iostream>

size_t MidiPort::instancecounter = 0;

MidiDevice::MidiDevice(const std::string & name)
		: name(name)
{
	cc.fill(0);
	ccold.fill(0);
}

MidiDevice::~MidiDevice()
{
	Close();
}

void MidiDevice::Close(void)
{
#ifdef _USE_MIDI
	if(input != NULL) Pm_Close(input);
	input = NULL;
	if(output != NULL) Pm_Close(output);
	output = NULL;
#endif
}

bool MidiDevice::operator ==(const std::string& name)const
{
	return name.compare(this->name) == 0;
}

bool MidiDevice::IsOpen(void) const
{
#ifdef _USE_MIDI
	return (input != NULL) || (output != NULL);
#else
	return false;
#endif
}

bool MidiDevice::IsInput(void) const
{
#ifdef _USE_MIDI
	return input != NULL;
#else
	return false;
#endif
}

bool MidiDevice::IsOutput(void) const
{
#ifdef _USE_MIDI
	return output != NULL;
#else
	return false;
#endif
}

bool MidiDevice::IsBidirectional(void) const
{
#ifdef _USE_MIDI
	return (input != NULL) && (output != NULL);
#else
	return false;
#endif
}

std::string MidiDevice::GetName(void) const
{
	return name;
}

void MidiDevice::Send(uint8_t from, uint8_t to)
{
	for(size_t n = from; n < to; ++n)
		ccold[n] = cc[n] + 1;
}

bool MidiDevice::Poll(void)
{
	bool flag = false;
#ifdef _USE_MIDI
	if(output != NULL){
		for(size_t n = 0; n < cc.size(); ++n){
			if(cc[n] != ccold[n]){
				buffer[0].message = Pm_Message(0xB0, n, cc[n]);
				buffer[0].timestamp = 0;
				Pm_Write(output, buffer, 1);
				ccold[n] = cc[n];
			}
		}
	}
	if(input != NULL){
		while(Pm_Poll(input)){
			if(Pm_Read(input, buffer, 1) > 0){
				uint8_t ch = Pm_MessageData1(buffer[0].message);
				uint8_t val = Pm_MessageData2(buffer[0].message);
				flag |= (val != cc[ch]);
				cc[ch] = ccold[ch] = val;
			}
		}
	}
#endif
	return flag;
}

void MidiDevice::Flush(void)
{
#ifdef _USE_MIDI
	if(input == NULL) return;
	//	Pm_SetFilter(midi, PM_FILT_CONTROL);
	while(Pm_Poll(input))
		Pm_Read(input, buffer, 1);
#endif
}

bool MidiDevice::PollEvent(uint8_t* data0, uint8_t* data1, uint8_t* data2)
{
#ifdef _USE_MIDI
	if(input == NULL) return false;
	if(!Pm_Poll(input)) return false;
	if(Pm_Read(input, buffer, 1) > 0){
		*data0 = Pm_MessageStatus(buffer[0].message);
		*data1 = Pm_MessageData1(buffer[0].message);
		*data2 = Pm_MessageData2(buffer[0].message);
		return true;
	}
#endif
	return false;
}

MidiPort::MidiPort()
{
#ifdef _USE_MIDI
	status = pmNoError;
	length = pmNoData;
#endif

	instancecounter++;
#ifdef _USE_MIDI
	if(instancecounter == 1) Pm_Initialize();
#endif
}

MidiPort::~MidiPort()
{
#ifdef _USE_MIDI
	CloseAll();

	if(instancecounter == 1) Pm_Terminate();
#endif
	assert(instancecounter > 0);
	instancecounter--;
}

inline bool operator==(const std::shared_ptr <MidiDevice>& device,
		const std::string & name)
{
	return ((*device) == name);
}

std::shared_ptr <MidiDevice> MidiPort::Open(const std::string& name,
		Direction direction)
{
	std::shared_ptr <MidiDevice> temp(nullptr);
#ifdef _USE_MIDI
	auto it = std::find(devices.begin(), devices.end(), name);
	if(it == devices.end()){
		temp = std::make_shared <MidiDevice>(name);
		devices.push_back(temp);
	}else{
		temp = *it;
	}

	PmDeviceID id = 0;
	const PmDeviceInfo * info = Pm_GetDeviceInfo(id);
	while(info != NULL){
		if(name.compare(info->name) == 0 && info->input
				&& (direction == Direction::Input
						|| direction == Direction::Bidirectional)){
			if(temp->input == NULL){
				PmError err = Pm_OpenInput(&(temp->input), id, NULL, 100, NULL,
				NULL);
				if(err != pmNoError){
					std::cout << "Error opening MIDI input: "
							<< DecodeError(err) << '\n';
					temp->input = NULL;
				}
			}
		}
		if(name.compare(info->name) == 0 && info->output
				&& (direction == Direction::Output
						|| direction == Direction::Bidirectional)){
			if(temp->output == NULL){
				PmError err = Pm_OpenOutput(&(temp->output), id, NULL, 100,
				NULL,
				NULL, 0);
				if(err != pmNoError){
					std::cout << "Error opening MIDI output: "
							<< DecodeError(err) << '\n';
					temp->output = NULL;
				}
			}
		}
		info = Pm_GetDeviceInfo(++id);
	}
	temp->Flush();
#endif
	return temp;
}

bool MidiPort::IsLastInstance(void) const
{
	return (instancecounter == 1);
}

//void MidiPort::CycleLibrary(void)
//{
//	this->Close();
//	if(instancecounter == 1){
//#ifdef _USE_MIDI
//		Pm_Terminate();
//		Pm_Initialize();
//#endif
//	}else{
//		// More than one instance: This causes problems for the other instances that are unaware of this cycling.
//	}
//}

int MidiPort::GetDefaultInputDevice(void) const
{
#ifdef _USE_MIDI
	return Pm_GetDefaultInputDeviceID();
#else
	return -1;
#endif
}

int MidiPort::GetDefaultOutputDevice(void) const
{
#ifdef _USE_MIDI
	return Pm_GetDefaultOutputDeviceID();
#else
	return -1;
#endif
}

std::set <std::string> MidiPort::GetDeviceNames(void) const
{
	std::set <std::string> temp;
#ifdef _USE_MIDI
	int idx = 0;
	const PmDeviceInfo* info = Pm_GetDeviceInfo(idx);
	while(info != NULL){
		temp.insert(info->name);
		++idx;
		info = Pm_GetDeviceInfo(idx);
	}
#endif
	return temp;
}

int MidiPort::GetDeviceCount(void) const
{
	int temp = 0;
#ifdef _USE_MIDI
	while(Pm_GetDeviceInfo(temp) != NULL)
		temp++;
#endif
	return temp;
}

std::string MidiPort::GetDeviceName(int nr) const
{
#ifdef _USE_MIDI
	const PmDeviceInfo* temp = Pm_GetDeviceInfo(nr);
	if(temp == NULL){
		return std::string("");
	}
	std::string name = temp->name;
	return name;
#else
	return std::string("");
#endif
}

std::string MidiPort::GetDeviceInterfaceName(int nr) const
{
#ifdef _USE_MIDI
	const PmDeviceInfo* temp = Pm_GetDeviceInfo(nr);
	if(temp == NULL){
		return std::string("");
	}
	std::string name = temp->interf;
	return name;
#else
	return std::string("");
#endif
}

bool MidiPort::IsDeviceInput(int nr) const
{
#ifdef _USE_MIDI
	const PmDeviceInfo* temp = Pm_GetDeviceInfo(nr);
	if(temp == NULL) return false;
	return temp->input;
#else
	return false;
#endif
}

bool MidiPort::IsDeviceOutput(int nr) const
{
#ifdef _USE_MIDI
	const PmDeviceInfo* temp = Pm_GetDeviceInfo(nr);
	if(temp == NULL) return false;
	return temp->output;
#else
	return false;
#endif
}

bool MidiPort::IsDeviceAvailable(int nr) const
{
#ifdef _USE_MIDI
	const PmDeviceInfo* temp = Pm_GetDeviceInfo(nr);
	if(temp == NULL) return false;
	return !temp->opened;
#else
	return false;
#endif
}

void MidiPort::Close(const std::string& name)
{
	auto it = std::find(devices.begin(), devices.end(), name);
	if(it != devices.end()) (*it)->Close();
}

void MidiPort::Close(size_t idx)
{
	devices[idx]->Close();
}

void MidiPort::CloseAll(void)
{
	for(auto & device : devices)
		device->Close();
}

std::shared_ptr <MidiDevice> MidiPort::GetFirstOpenDevice(Direction direction)
{
#ifdef _USE_MIDI
	if(direction == Direction::Input){
		for(auto & device : devices)
			if(device->input != NULL) return device;
	}
	if(direction == Direction::Output){
		for(auto & device : devices)
			if(device->output != NULL) return device;
	}
	if(direction == Direction::Bidirectional){
		for(auto & device : devices)
			if(device->input != NULL && device->output != NULL) return device;
	}
#endif
	return nullptr;
}

#ifdef _USE_MIDI
std::string MidiPort::DecodeError(PmError err)
{
	return std::string(Pm_GetErrorText(err));
//	switch(err){
//	case pmNoError:
//		return "";
//	case pmHostError:
//		return "Host error.";
//	case pmInvalidDeviceId:
//		return "Invalid device id.";
//	case pmInsufficientMemory:
//		return "Insufficient memory.";
//	case pmBufferTooSmall:
//		return "Buffer too small.";
//	case pmBufferOverflow:
//		return "Buffer overflow.";
//	case pmBadPtr:
//		return "Bad pointer.";
//	case pmInternalError:
//		return "Internal error.";
//	case pmBufferMaxSize:
//		return "Max buffer size.";
//	default:
//		return "Unknown error.";
//	}
//	return "";
}

#endif
