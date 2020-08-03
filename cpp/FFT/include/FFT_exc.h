/**
 *       @file  FFT_exc.cc
 *      @brief  The FFT porting to AEM (original version: http://axbench.org/)
 *
 *     Company  Politecnico di Milano
 *   Copyright  Copyright (c) 2020, Name Surname
 *
 * This source code is released for free distribution under the terms of the
 * GNU General Public License as published by the Free Software Foundation.
 * =====================================================================================
 */

#ifndef FFT_EXC_H_
#define FFT_EXC_H_

#include <iostream>
#include "fann.h"
#include <cmath>
#include <fstream>
#include <time.h>
#include <map>
#include <cstdio>
#include <random>
#include <cstring>
#include <memory>
#include <libgen.h>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/variables_map.hpp>
#include "version.h"
#include <bbque/utils/utility.h>
#include <bbque/utils/logging/logger.h>
#include <bbque/utils/utility.h>
#include <bbque/bbque_exc.h>

// Custom class

class statement //Useful to save and restore radix2DitCooleyTykeyFft
{
  
public :
  void save_state(int i, int N)
  {
    i_m = i;
    N_m = N;
  }
  void setDone()
  {
    work_complete = 1;
  }
  void setProcNr(int num)
  {
    proc_nr = num;
  }
  void unsetFirstRun()
  {
    first_run = 0;
  }
  int isDone() {return work_complete;}
  int isFirstRun() {return first_run;} 
  int getI() {return i_m;}
  int getN() {return N_m;}
  int getProcNr(){return proc_nr;}

private :
  int i_m {0};
  int N_m {2};
  int work_complete{0};
  int first_run{1};
  int proc_nr{1};
};


// Adding complex.hpp && fourier.hpp from the FFT APP //

#define PI 3.1415926535897931
typedef struct {
   float real;
   float imag;
} Complex;

void fftSinCos(float x, float* s, float* c);
float abs(const Complex* x);
float arg(const Complex* x);

void radix2DitCooleyTykeyFft(int k, int* indices, Complex* x, Complex* f, statement *s, int num_proc) ;
void calcFftIndices(int K, int* indices);

//*****************************************************//




using bbque::rtlib::BbqueEXC;

class FFT : public BbqueEXC {
public:

	FFT(std::string const & name,
			std::string const & recipe,
	    RTLIB_Services_t *rtlib,int num, std::string s);

private:
  int* indices; //+
  Complex* x; //+
  Complex* f; //+
  int n; //+
  statement s;
  std::string outputFilename; //+
  std::ofstream outputFileHandler; //+
	RTLIB_ExitCode_t onSetup();
	RTLIB_ExitCode_t onConfigure(int8_t awm_id);
	RTLIB_ExitCode_t onRun();
	RTLIB_ExitCode_t onMonitor();
	RTLIB_ExitCode_t onSuspend();
	RTLIB_ExitCode_t onRelease();
};

#endif // FFT_EXC_H_
