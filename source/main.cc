#include "main.h"

#define RUN 1

int main(int argc, char *argv[]) {

  myConfig *config = new myConfig();

  double input_energyloss  = std::stoi(argv[1]);
  double input_subtraction = std::stoi(argv[2]);
  double input_correlation = std::stod(argv[3]);
  double max_run = std::stoi(argv[4]);

  config->m_special_run       = true;

  config->m_stat_only         = false;

  config->m_energyloss        = input_energyloss; // false;
  config->m_logbehavior       = false;
  config->m_fermimotion       = false;
  config->m_subtraction       = input_subtraction; // false;
  config->m_correlation       = input_correlation; // -1.0; // for physics -1.0 < rho < 0.0
  config->m_Q2BinOfInterest   = -1;   // value in between 1 and Q2DIM of Q2,x bins. -1 fits all.
  config->m_zBinOfInterest    = -1;   // value in between 1 and ZDIM of z bins. -1 fits all.
  config->m_output_fit        = "testFit.txt";
  config->m_input_pt          = "hermesData.txt";
  // config->Update();
  std::ostringstream foo;
  foo << "iFit: energy loss: " << config->m_energyloss;
  foo << " He subtraction: " << config->m_subtraction;
  foo << " correlation = " << config->m_correlation;
  config->m_comment           = foo.str();

  std::cout << "Running iFit now:" << std::endl;
  int mcMax=1; // this will control how many times I will average
  if (config->m_special_run) {
    mcMax=max_run;
  }
  myResult f;
  TFile *out_file = TFile::Open("output.root","RECREATE");
  TTree* tt = new TTree("tree","tree");
  tt->Branch("zbin",         &f.m_zbin,         "zbin/F");
  tt->Branch("qhat",         &f.m_qhat,         "q-hat/F");
  tt->Branch("lp",           &f.m_lp,           "lp/F");
  tt->Branch("sigma_ph",     &f.m_sigma_ph,     "sigma_ph/F");
  tt->Branch("dz",           &f.m_dz,           "dz/F");
  tt->Branch("qhat_err",     &f.m_qhat_err,     "qhat_err/F");
  tt->Branch("lp_err",       &f.m_lp_err,       "lp_err/F");
  tt->Branch("sigma_ph_err", &f.m_sigma_ph_err, "sigma_ph_err/F");
  tt->Branch("dz_err",       &f.m_dz_err,       "dz_err/F");
  tt->Branch("chi2",         &f.m_chi2,         "chi2/F");
  for (int mc=1; mc<=mcMax; mc++) {
    auto fitOutput = ifit(config);
    int count = 1;
    for (const auto &v : fitOutput) {
      std::cout << "Info: Run #" << mc << " element " << count << " of " << (int)fitOutput.size() << std::endl;
      std::cout << "Info:       z-bin    = " << v->m_zbin << std::endl;
      std::cout << "Info: Value q-hat    = " << v->m_qhat << std::endl;
      std::cout << "Info: Value l_p      = " << v->m_lp << std::endl;
      std::cout << "Info: Value sigma_ph = " << v->m_sigma_ph << std::endl;
      std::cout << "Info: Value dz       = " << v->m_dz << std::endl;
      std::cout << "Info: Error q-hat    = " << v->m_qhat_err << std::endl;
      std::cout << "Info: Error l_p      = " << v->m_lp_err << std::endl;
      std::cout << "Info: Error sigma_ph = " << v->m_sigma_ph_err << std::endl;
      std::cout << "Info: Error dz       = " << v->m_dz_err << std::endl;
      std::cout << "Info:       chi2     = " << v->m_chi2 << std::endl;
      f.m_zbin = v->m_zbin;
      f.m_qhat = v->m_qhat;
      f.m_lp = v->m_lp;
      f.m_sigma_ph = v->m_sigma_ph;
      f.m_dz = v->m_dz;
      f.m_qhat_err = v->m_qhat_err;
      f.m_lp_err = v->m_lp_err;
      f.m_sigma_ph_err = v->m_sigma_ph_err;
      f.m_dz_err = v->m_dz_err;
      f.m_chi2 = v->m_chi2;
      tt->Fill();
      count++;
    }
  }
  out_file->Write();
  out_file->Close();
  std::cout << "Running iFit ended" << std::endl;

  // commnt plotFitOutput if doing special things
  // plotFitOutput(config->m_output_fit);

  // test(); // Test of Model Class
  // auto fc = dataHandler(config); // This is just a test of dataHandler()
  // double zbin[4] = {0.32, 0.53, 0.75, 0.94};
  // for (int a=0; a<3; ++a) {
  //   for (int iz=0; iz<4; ++iz) {
  //     std::cout << zbin[iz] << "\t" << fc[a]->m_value[iz] << "\t" << 0.0 << "\t" << fc[a]->m_err[iz] << std::endl;
  //   }
  // }

  return 0;
}
