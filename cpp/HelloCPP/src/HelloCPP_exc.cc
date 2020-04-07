/**
 *       @file  HelloCPP_exc.cc
 *      @brief  The HelloCPP BarbequeRTRM application
 *
 * Description: to be done...
 *
 *     @author  Name Surname (nickname), your@email.com
 *
 *     Company  Your Company
 *   Copyright  Copyright (c) 20XX, Name Surname
 *
 * This source code is released for free distribution under the terms of the
 * GNU General Public License as published by the Free Software Foundation.
 * =====================================================================================
 */


#include "HelloCPP_exc.h"

#include <cstdio>
#include <bbque/utils/utility.h>

HelloCPP::HelloCPP(std::string const & name,
		std::string const & recipe,
		RTLIB_Services_t *rtlib) :
	BbqueEXC(name, recipe, rtlib) {

	logger->Warn("New HelloCPP::HelloCPP()");

	// NOTE: since RTLib 1.1 the derived class construct should be used
	// mainly to specify instantiation parameters. All resource
	// acquisition, especially threads creation, should be palced into the
	// new onSetup() method.

	logger->Info("EXC Unique IDentifier (UID): %u", GetUniqueID());

}

RTLIB_ExitCode_t HelloCPP::onSetup() {
	// This is just an empty method in the current implementation of this
	// testing application. However, this is intended to collect all the
	// application specific initialization code, especially the code which
	// acquire system resources (e.g. thread creation)
	logger->Warn("HelloCPP::onSetup()");

	return RTLIB_OK;
}

RTLIB_ExitCode_t HelloCPP::onConfigure(int8_t awm_id) {

	logger->Warn("HelloCPP::onConfigure(): EXC [%s] => AWM [%02d]",
		exc_name.c_str(), awm_id);

	int32_t proc_quota, proc_nr, mem;
	GetAssignedResources(PROC_ELEMENT, proc_quota);
	GetAssignedResources(PROC_NR, proc_nr);
	GetAssignedResources(MEMORY, mem);
	logger->Notice("MayApp::onConfigure(): "
		"EXC [%s], AWM[%02d] => R<PROC_quota>=%3d, R<PROC_nr>=%2d, R<MEM>=%3d",
		exc_name.c_str(), awm_id, proc_quota, proc_nr, mem);

	return RTLIB_OK;
}

RTLIB_ExitCode_t HelloCPP::onRun() {
	RTLIB_WorkingModeParams_t const wmp = WorkingModeParams();

	// Return after 5 cycles
	if (Cycles() >= 5)
		return RTLIB_EXC_WORKLOAD_NONE;

	logger->Notice("HelloCPP::onRun()      : Hello World!");

	return RTLIB_OK;
}

RTLIB_ExitCode_t HelloCPP::onMonitor() {
	RTLIB_WorkingModeParams_t const wmp = WorkingModeParams();

	logger->Warn("HelloCPP::onMonitor()  : EXC [%s]  @ AWM [%02d] "
			"=> cycles [%d], CPS = %.2f",
		exc_name.c_str(), wmp.awm_id, Cycles(), GetCPS());

	return RTLIB_OK;
}

RTLIB_ExitCode_t HelloCPP::onSuspend() {

	logger->Warn("HelloCPP::onSuspend()  : suspension...");

	return RTLIB_OK;
}

RTLIB_ExitCode_t HelloCPP::onRelease() {

	logger->Warn("HelloCPP::onRelease()  : exit");

	return RTLIB_OK;
}
