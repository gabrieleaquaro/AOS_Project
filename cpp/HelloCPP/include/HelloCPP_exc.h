/**
 *       @file  HelloCPP_exc.h
 *      @brief  The HelloCPP BarbequeRTRM application
 *
 * Description: to be done...
 *
 *     @author  Name Surname (nickname), your@email.com
 *
 *     Company  Politecnico di Milano
 *   Copyright  Copyright (c) 20XX, Name Surname
 *
 * This source code is released for free distribution under the terms of the
 * GNU General Public License as published by the Free Software Foundation.
 * =====================================================================================
 */

#ifndef HELLOCPP_EXC_H_
#define HELLOCPP_EXC_H_

#include <bbque/bbque_exc.h>

using bbque::rtlib::BbqueEXC;

class HelloCPP : public BbqueEXC {

public:

	HelloCPP(std::string const & name,
			std::string const & recipe,
			RTLIB_Services_t *rtlib);

private:

	RTLIB_ExitCode_t onSetup();
	RTLIB_ExitCode_t onConfigure(int8_t awm_id);
	RTLIB_ExitCode_t onRun();
	RTLIB_ExitCode_t onMonitor();
	RTLIB_ExitCode_t onSuspend();
	RTLIB_ExitCode_t onRelease();
};

#endif // HELLOCPP_EXC_H_
