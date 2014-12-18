/* C:B**************************************************************************
This software is Copyright 2014 Michael Romeo <r0m30@r0m30.com>

This file is part of msed.

msed is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

msed is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with msed.  If not, see <http://www.gnu.org/licenses/>.

 * C:E********************************************************************** */
#pragma once
class MsedCommand;
// class MsedResponse;
class MsedSession;

#include "MsedStructures.h"
#include "MsedLexicon.h"
#include "MsedResponse.h"   // wouldn't take class
#include <vector>

using namespace std;

class MsedBaseDev {
public:
    MsedBaseDev();
    ~MsedBaseDev();
    virtual uint8_t
    sendCmd(ATACOMMAND cmd, uint8_t protocol, uint16_t comID,
            void * buffer, uint16_t bufferlen) = 0;

    uint8_t exec(MsedCommand * cmd, MsedResponse &response, uint8_t protocol = 0x01);
    uint8_t isOpal2();
    uint8_t isOpal1();
    uint8_t isEprise();
    uint8_t isANYSSC();
     uint8_t MBREnabled();
    uint8_t isPresent();
    uint16_t comID();
    void getFirmwareRev(uint8_t bytes[8]);
    void getModelNum(uint8_t bytes[40]);
    void getSerialNum(uint8_t bytes[20]);
    
	uint8_t takeOwnership(char * newpassword);
	uint8_t getDefaultPassword();
	uint8_t getTable(vector<uint8_t> table, uint16_t startcol,
		uint16_t endcol);
	uint8_t setSIDPassword(char * oldpassword, char * newpassword,
		uint8_t hasholdpwd = 1, uint8_t hashnewpwd = 1);
	uint8_t setTable(vector<uint8_t> table, OPAL_TOKEN name,
		vector<uint8_t> value);
	uint8_t setTable(vector<uint8_t> table, OPAL_TOKEN name,
		OPAL_TOKEN value);
	uint8_t diskQuery();
	uint8_t activateLockingSP(char * password);
	uint8_t revertLockingSP(char * password, uint8_t keep = 0);
	uint8_t getAuth4User(char * userid, uint8_t column, std::vector<uint8_t> &userData);
	uint8_t enableUser(char * password, char * userid);
	uint8_t setNewPassword(char * password, char * userid, char * newpassword);
	uint8_t setLockingRange(uint8_t lockingrange, uint8_t lockingstate,
			char * Admin1Password);
	uint8_t SetLockingSPvalue(OPAL_UID table_uid, OPAL_TOKEN name, OPAL_TOKEN value,
			char * password, char * msg = (char *) "New Value Set");
	uint8_t revertTPer(char * password, uint8_t PSID = 0);
	uint8_t loadPBA(char * password, char * filename);
	uint8_t initialsetup(char * password);
	uint8_t dumpTable(char * password);
	uint8_t nextTable(MsedSession * session, vector<uint8_t> table,
		vector<uint8_t> startkey);
protected:
	// not working, I have no idea why
	 uint8_t revertnoerase(char * SIDPassword, char * Admin1Password);
	//
	void puke();
    virtual void osmsSleep(uint32_t milliseconds) = 0;
    /** Decode the Discovery 0 response. Scans the D0 response and creates structure
     * that can be queried later as required.This code also takes care of
     * the endianess conversions either via a bitswap in the structure or executing
     * a macro when the input buffer is read.
     */
    void discovery0();
    virtual void identify() = 0;
    const char * dev;
    uint8_t isOpen = FALSE;
    OPAL_DiskInfo disk_info;
	MsedResponse response;
	MsedSession *session;

};