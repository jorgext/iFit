#ifndef DATAHANDLER_H
#define DATAHANDLER_H

#include <iostream>
#include <sstream> // for ostringstream
#include <string>
#include <fstream>
#include "TFile.h"
#include "TMinuit.h"
#include "TString.h"
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TMultiGraph.h"
#include "TH1.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TStyle.h"

//
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

#include "graphics.h"
#include "configuration.h"

class myResult {
  /*
  Class storing the resulting parameters of the fit
  This shoudl come out from ifit(), and be built from the minuit object
  */
private:
  std::string m_name = "default result";
public:
  double m_zbin;
  double m_qhat;
  double m_lp;
  double m_sigma_ph;
  double m_dz;
  double m_qhat_err;
  double m_lp_err;
  double m_sigma_ph_err;
  double m_dz_err;
  double m_chi2;
  // constructor
  myResult();
  ~myResult();
};

class myData {
private:
  std::string m_name;
public:
  std::vector<double> m_zbin = {0.32, 0.53, 0.75, 0.94};
  std::vector<double> m_wbin = {0.20/2.0,0.22/2.0,0.22/2.0,0.16/2.0};
  std::vector<double> m_value; 
  std::vector<double> m_value_corrected;
  std::vector<double> m_stat; 
  std::vector<double> m_stat_corrected;
  std::vector<double> m_syst; 
  std::vector<double> m_syst_corrected;
  std::vector<double> m_err; 
  std::vector<double> m_err_corrected;
  std::vector<TGraphErrors*> m_tge; //m_tge[6];
  myData(std::string);
  ~myData();
  void applyCorrection(myData*,double);
  void fill(int,double,double,double);
  void doTGraphErrors();
};

std::vector<myData*> dataHandler(myConfig*);
void conv2double(std::vector<std::string>,double&,double&,double&);
double pow2(double);

#endif