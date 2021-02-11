/**
 *       @file  EdgeDetector_exc.h
 *      @brief  The Canny Edge Detector BarbequeRTRM application
 *
 * Description: This program demonstrates usage of the Canny edge detector
 *
 *     @author  Aquaro Gabriele, gabriele.aquaro@mail.polimi.it
 *
 *     Company  Politecnico di Milano
 *   Copyright  Copyright (c) 2021, Aquaro Gabriele
 *
 * This source code is released for free distribution under the terms of the
 * GNU General Public License as published by the Free Software Foundation.
 * =====================================================================================
 */

#ifndef EDGEDETECTOR_EXC_H_
#define EDGEDETECTOR_EXC_H_

#include <bbque/bbque_exc.h>

#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <stdio.h>
#include <iostream>


using bbque::rtlib::BbqueEXC;

class EdgeDetector : public BbqueEXC {


std::string filename;
bool open_window;

public:
	
	EdgeDetector(std::string const & name,
		     std::string const & recipe,
		     RTLIB_Services_t *rtlib,
		     std::string filename
		     	   );
	
private:

	RTLIB_ExitCode_t onSetup();
	RTLIB_ExitCode_t onConfigure(int8_t awm_id);
	RTLIB_ExitCode_t onRun();
	RTLIB_ExitCode_t onMonitor();
	RTLIB_ExitCode_t onSuspend();
	RTLIB_ExitCode_t onRelease();
	size_t Work();
	void help();
	static void onTrackbar(int, void*);
};

#endif // EDGEDETECTOR_EXC_H_
