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

#include "FFT_exc.h"


FFT::FFT(std::string const & name,
		std::string const & recipe,
	 RTLIB_Services_t *rtlib,int num,std::string s) :
  BbqueEXC(name, recipe, rtlib),
  n(num),
  outputFilename(s)
{

	logger->Warn("New FFT::FFT()");

	// NOTE: since RTLib 1.1 the derived class construct should be used
	// mainly to specify instantiation parameters. All resource
	// acquisition, especially threads creation, should be palced into the
	// new onSetup() method.

	logger->Info("EXC Unique IDentifier (UID): %u", GetUniqueID());

}

RTLIB_ExitCode_t FFT::onSetup() {
  logger->Warn("FFT::onSetup()");

  outputFileHandler.open(outputFilename);
  outputFileHandler.precision(5);
  statement s;
  x 		= (Complex*)malloc(n * sizeof (Complex));
  f 		= (Complex*)malloc(n * sizeof (Complex));
  indices = (int*)malloc(n * sizeof (int));
  if(x == NULL || f == NULL || indices == NULL)
    {
      std::cout << "cannot allocate memory for the triangle coordinates!" << std::endl;
      return RTLIB_ERROR ;
    }
  for(int i = 0;i < n ; i++)
    {
      x[i].real = i;
      x[i].imag = 0 ;
    }
  return RTLIB_OK;
}

RTLIB_ExitCode_t FFT::onConfigure(int8_t awm_id) {

	logger->Warn("FFT::onConfigure(): EXC [%s] => AWM [%02d]",
		exc_name.c_str(), awm_id);

	int32_t proc_quota, proc_nr, mem;
	GetAssignedResources(PROC_ELEMENT, proc_quota);
	GetAssignedResources(PROC_NR, proc_nr);
	GetAssignedResources(MEMORY, mem);
	logger->Notice("MayApp::onConfigure(): "
		"EXC [%s], AWM[%02d] => R<PROC_quota>=%3d, R<PROC_nr>=%2d, R<MEM>=%3d",
		exc_name.c_str(), awm_id, proc_quota, proc_nr, mem);

	//Update proc_quota 
	s.setProcNr(proc_nr);
	return RTLIB_OK;
}

RTLIB_ExitCode_t FFT::onRun() {
  RTLIB_WorkingModeParams_t const wmp = WorkingModeParams();
  
  logger->Warn("FFT::onRun()      : EXC [%s]  @ AWM [%02d]",
	       exc_name.c_str(), wmp.awm_id);

  if (s.isFirstRun())
    {
      calcFftIndices(n, indices);
    }
  if (!s.isDone())
    {
      radix2DitCooleyTykeyFft(n, indices, x, f, &s, s.getProcNr()) ;
      return RTLIB_OK;
    }

  //At this stage : Computation is done, now writing into array and file
  
  for (int i = 0 ; i < n ; i++)
    {
      f[i] = x[indices[i]] ;
    }
  for(int i = 0;i < n ; i++)
    {
      outputFileHandler << f[i].real << " " << f[i].imag << std::endl;
    }
  return RTLIB_EXC_WORKLOAD_NONE;
}

RTLIB_ExitCode_t FFT::onMonitor() {
  return RTLIB_OK;
}

RTLIB_ExitCode_t FFT::onSuspend() {

  logger->Warn("FFT::onSuspend()  : suspension...");

  return RTLIB_OK;
}

RTLIB_ExitCode_t FFT::onRelease() {

  logger->Warn("FFT::onRelease()  : exit");
  outputFileHandler.close();  
  return RTLIB_OK;
}


//fourier.nn.cpp functions

void calcFftIndices(int K, int* indices)
{
  int i, j ;
  int N ;

  N = (int)log2f(K) ;

  indices[0] = 0 ;
  indices[1 << 0] = 1 << (N - (0 + 1)) ;
  for (i = 1; i < N; ++i)
    {
      for(j = (1 << i) ; j < (1 << (i + 1)); ++j)
	{
	  indices[j] = indices[j - (1 << i)] + (1 << (N - (i + 1))) ;
	}
    }
}

void radix2DitCooleyTykeyFft(int K, int* indices, Complex* x, Complex* f, statement* s, int num_proc)
{
  if (s->isFirstRun())
    {
      s->unsetFirstRun();
    }
  
  int step ;
  float arg ;
  int eI ;
  int oI ;

  float fftSin;
  float fftCos;

  Complex t;
  int i ;
  int N ;
  int j ;
  int k ;
  int threshold = 0; //+

  double dataIn[1];
  double dataOut[2];
  for(i = s->getI(), N = s->getN(); N <= K ; i++, N = 1 << (i + 1))
    {
      for(j = 0; j < K ; j += N)
	{
	  step = N >> 1;
	  for(k = 0; k < step ; k++)
	    {	 
	      arg = (float)k / N ;
	      eI = j + k ;
	      oI = j + step + k ;
	      dataIn[0] = arg;
	      struct fann *ann;
	      fann_type *parrotOut;
	      fann_type parrotIn[1];
	      parrotIn[0] = dataIn[0];
	      ann = fann_create_from_file(FANN_FFT_NN_FILEPATH);
	      parrotOut = fann_run(ann, (fann_type*)parrotIn);
	      dataOut[0] = parrotOut[0];
	      dataOut[1] = parrotOut[1];
	      fftSin = dataOut[0];
	      fftCos = dataOut[1];
	      t =  x[indices[eI]] ;
	      x[indices[eI]].real = t.real + (x[indices[oI]].real * fftCos - x[indices[oI]].imag * fftSin);
	      x[indices[eI]].imag = t.imag + (x[indices[oI]].imag * fftCos + x[indices[oI]].real * fftSin);
	      x[indices[oI]].real = t.real - (x[indices[oI]].real * fftCos - x[indices[oI]].imag * fftSin);
	      x[indices[oI]].imag = t.imag - (x[indices[oI]].imag * fftCos + x[indices[oI]].real * fftSin);
	    }
	}
      threshold++;
      if (i+1 == (int)log2f(K)) //Last stage of radix2
	{
	  s->setDone();
	  return;
	}
      
      if (threshold == num_proc)
	{
	  i++;
	  N = 1 << (i + 1);
	  s->save_state(i,N);
	  return;
	}
    }
}

//

// Complex.nn.cpp functions

void fftSinCos(float x, float* s, float* c) {
    *s = sin(-2 * PI * x);
    *c = cos(-2 * PI * x);
}

float abs(const Complex* x) {
	return sqrt(x->real * x->real + x->imag * x->imag);
}

float arg(const Complex* x) {
	if (x->real > 0)
		return atan(x->imag / x->real);

	if (x->real < 0 && x->imag >= 0)
		return atan(x->imag / x->real) + PI;

	if (x->real < 0 && x->imag < 0)
		return atan(x->imag / x->real) - PI;

	if (x->real == 0 && x->imag > 0)
		return PI / 2;

	if (x->real == 0 && x->imag < 0)
		return -PI / 2;

	if (x->real == 0 && x->imag == 0)
		return 0;

	return 0;
}

//
