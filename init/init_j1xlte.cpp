/*
   Copyright (c) 2013, The Linux Foundation. All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the following
      disclaimer in the documentation and/or other materials provided
      with the distribution.
    * Neither the name of The Linux Foundation nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.
   THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
   ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
   BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
   BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
   OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
   IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdlib.h>

#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>

#include "vendor_init.h"
#include "property_service.h"
#include "log.h"
#include "util.h"

void property_override(char const prop[], char const value[])
{
    prop_info *pi;

    pi = (prop_info*) __system_property_find(prop);
    if (pi)
        __system_property_update(pi, value, strlen(value));
    else
        __system_property_add(prop, strlen(prop), value, strlen(value));
}

void set_sim_info()

{
	char* simslot_count_path = (char *)"/proc/simslot_count";

    	char simslot_count[2] = "\0";

	FILE* file = fopen(simslot_count_path, "r");

	simslot_count[0] = fgetc(file);

	if (file != NULL) {
		property_set("ro.multisim.simslotcount", simslot_count);
	}
	else {
		ERROR("Could not open /proc/simslot_count");
	}

	fclose(file);

}
void vendor_load_properties()
{
	std::string bl;

	bl = property_get("ro.bootloader");

	if (bl.find("FA51_J120") != std::string::npos) {
	        ERROR("Found LL combination bootloader, setting build properties for SM-J120F");
		property_override("ro.product.model", "SM-J120F");
	} else if (bl.find("FA60_J120") != std::string::npos) {
	        ERROR("Found MM combination bootloader, setting build properties for SM-J120W");
		property_override("ro.product.model", "SM-J120W");
	} else if (bl.find("J120FN") != std::string::npos) {
		property_override("ro.product.model", "SM-J120FN");
	} else if (bl.find("J120F") != std::string::npos) {
		property_override("ro.product.model", "SM-J120F");
	} else if (bl.find("J120M") != std::string::npos) {
		property_override("ro.product.model", "SM-J120M");
	} else if (bl.find("J120ZN") != std::string::npos) {
		property_override("ro.product.model", "SM-J120ZN");
	} else if (bl.find("J120G") != std::string::npos) {
		property_override("ro.product.model", "SM-J120G");
	} else if (bl.find("J120W") != std::string::npos) {
		property_override("ro.product.model", "SM-J120W");
	} else if (bl.find("J120AZ") != std::string::npos) {
		property_override("ro.product.model", "SM-J120AZ");
	} else if (bl.find("J120A") != std::string::npos) {
		property_override("ro.product.model", "SM-J120A");
	} else {
	        ERROR("Could not found any supported device/bootloader, forcing build properties to SM-J120X");
	        property_override("ro.product.model", "SM-J120X");
	}
	set_sim_info();
}
