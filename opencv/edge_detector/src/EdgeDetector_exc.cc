/**
 *       @file  EdgeDetector_exc.cc
 *      @brief  The HoughCircles BarbequeRTRM application
 *
 * Description: This program demonstrates an implementation of the Canny Edger Detector.
 *
 *     @author  Gabriele Aquaro, gabriele.aquaro@mail.polimi.it
 *
 *     Company  Politecnico di Milano
 *   Copyright  Copyright (c) 2020, Gabriele Aquaro
 *
 * This source code is released for free distribution under the terms of the
 * GNU General Public License as published by the Free Software Foundation.
 * =====================================================================================
 */


#include "EdgeDetector_exc.h"

#include <cstdio>
#include <bbque/utils/utility.h>

#include <math.h>

using namespace cv;
using namespace std;


int edgeThresh = 1;
int edgeThreshScharr=1;

Mat image, gray, blurImage, edge1, edge2, cedge;
int state1, state2;

const char* window_name1 = "Edge map : Canny default (Sobel gradient)";
const char* window_name2 = "Edge map : Canny with custom gradient (Scharr)";

EdgeDetector::EdgeDetector(string const & name,
		           string const & recipe,
		     	   RTLIB_Services_t *rtlib,
		     	   string filename
		     	   ):
			  BbqueEXC(name, recipe, rtlib),
			  filename(filename)
			  {	
	logger->Notice("New EdgeDetector::EdgeDetector()");
	logger->Notice("EXC Unique IDentifier (UID): %u", GetUniqueID());

}

RTLIB_ExitCode_t EdgeDetector::onSetup() {

	logger->Notice("EdgeDetector::onSetup()");
	help();
	try { 
		// Try to open the image file given as input and catches the correlated exceeptions
		image = imread(samples::findFile(filename), IMREAD_COLOR);
	 } catch (const cv::Exception e) 
	 { 
	 	//If the opening above fails, the aplication uses the stock image
	 	logger->Warn("Cannot read image file: %s\n", filename.c_str());
    		logger->Notice("Using stock image...");
    		image = imread(samples::findFile("fruits.jpg"), IMREAD_COLOR);
    		help();
    	 }
	
    	if(image.empty())
    	{	
    		//Theoretically NEVER happen
    		return RTLIB_ERROR;	
    	}
    	
	open_window = false;
	return RTLIB_OK;
}


RTLIB_ExitCode_t EdgeDetector::onConfigure(int8_t awm_id)
{
       logger->Warn("EdgeDetector::onConfigure(): EXC [%s] => AWM [%02d]",
		exc_name.c_str(), awm_id);
	
	int32_t proc_quota, proc_nr, mem;
	GetAssignedResources(PROC_ELEMENT, proc_quota);
	GetAssignedResources(PROC_NR, proc_nr);
	GetAssignedResources(MEMORY, mem);
	
	logger->Notice("EdgeDetector::onConfigure(): "
		"EXC [%s], AWM[%02d] => R<PROC_quota>=%3d, R<PROC_nr>=%2d, R<MEM>=%3d",
		exc_name.c_str(), awm_id, proc_quota, proc_nr, mem);
        return RTLIB_OK;
}

RTLIB_ExitCode_t EdgeDetector::onRun() {
        
        logger->Notice("EdgeDetector::onRun()");
       	
       	if (!open_window){
	       	cedge.create(image.size(), image.type());
	    	cvtColor(image, gray, COLOR_BGR2GRAY);
	    	
	       	// Create a window
	    	namedWindow(window_name1, 1);
	    	namedWindow(window_name2, 1);
	    	
	    	// create a toolbar
	    	createTrackbar("Canny threshold default", window_name1, &edgeThresh, 100, onTrackbar);
	   	createTrackbar("Canny threshold Scharr", window_name2, &edgeThreshScharr, 400, onTrackbar);
		
		
		// Show the image
	    	onTrackbar(0, 0); 	

	    	open_window = true;
	}
	// Wait for a key stroke; the same function arranges events processing
	waitKey(500);
			    	
        return RTLIB_OK;
}

RTLIB_ExitCode_t EdgeDetector::onMonitor()
{
      	
       	state1 = (int) getWindowProperty(window_name1, WND_PROP_VISIBLE );
       	state2 = (int) getWindowProperty(window_name2, WND_PROP_VISIBLE );
       	if(state1 == 0 and state2 == 0){
       		logger->Notice("EdgeDetector::onMonitor() : Exiting %d %d",  state1,state2); 
        	return RTLIB_EXC_WORKLOAD_NONE;
       	}
       	logger->Notice("EdgeDetector::onMonitor() : Window1 :%d - Window2:%d", state1, state2); 
       	
        return RTLIB_OK;
    
}

RTLIB_ExitCode_t EdgeDetector::onSuspend()
{
	logger->Notice("EdgeDetector::onSuspend()  : suspension...");
	return RTLIB_OK;
}

RTLIB_ExitCode_t EdgeDetector::onRelease()
{
        logger->Notice("EdgeDetector::onRelease()\n");
        destroyWindow(window_name1);
        destroyWindow(window_name2);
        open_window = false;
        logger->Warn("EdgeDetector::onRelease(): Windows closed. Exiting");
        return RTLIB_OK;
}

void EdgeDetector::help()
{
    logger->Notice("\nThis sample demonstrates Canny edge detection\n Call:\n EdgeDetector [image_name -- Default is fruits.jpg]\n");
}

void EdgeDetector::onTrackbar(int, void*)
{
    blur(gray, blurImage, Size(3,3));
    
    // Run the edge detector on grayscale
    Canny(blurImage, edge1, edgeThresh, edgeThresh*3, 3);
    cedge = Scalar::all(0);
    
    image.copyTo(cedge, edge1);
    imshow(window_name1, cedge);
    Mat dx,dy;
    
    Scharr(blurImage,dx,CV_16S,1,0);
    Scharr(blurImage,dy,CV_16S,0,1);
    Canny( dx,dy, edge2, edgeThreshScharr, edgeThreshScharr*3 );
    cedge = Scalar::all(0);
    image.copyTo(cedge, edge2);
    imshow(window_name2, cedge);
}


