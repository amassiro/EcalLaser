//
//---- plot Laser comparison
//

//                                                                                                                               ieta         iphi         -1, 0, +1
void drawComparison(std::string nameInputFile = "Laser2017_noTP.root", std::string nameInputFile2 = "transp2017-prompt.root", int ix = 62, int iy = 50,  int iz = 1) {
  
//   iz -1, +1 -> EE
//         0   -> EB
  
  int isEB = 0;
  if (iz == 0) {
    std::cout << " EB " << std::endl;
    std::cout << " ieta = " << ix << std::endl;
    std::cout << " iphi = " << iy << std::endl;
    isEB = 1;
  }  
  else {
    std::cout << " EE " << std::endl;
    std::cout << " ix = " << ix << std::endl;
    std::cout << " iy = " << iy << std::endl;
    std::cout << " iz = " << iz << std::endl;  
  }
  
  gStyle->SetOptStat(0);
  
  TFile* fileIn = new TFile(nameInputFile.c_str(), "READ");
  TTree* ntu      = (TTree*) fileIn -> Get ("ntu");
  
  TFile* fileIn2 = new TFile(nameInputFile2.c_str(), "READ");
  TTree* ntu2      = (TTree*) fileIn2 -> Get ("LDB");
  
  
  TString laser_string  = Form ("nrv");
  TString time_string  = Form ("time[0]");
  TString toDraw = Form ("%s:%s", laser_string.Data(), time_string.Data());
  TString toCut;
  if (isEB == 0) toCut = Form ("ix==%d && iy==%d && iz==%d", ix, iy, iz);
  if (isEB == 1) toCut = Form ("ix==%d && iy==%d && iz==%d", ix, iy, iz);
  
  std::cout << " toDraw = " << toDraw.Data() << std::endl;
  std::cout << " toCut  = " << toCut.Data()  << std::endl;
  
  ntu->Draw(toDraw.Data(), toCut.Data(), "goff");
  std::cout << " ntu->GetSelectedRows() = " << ntu->GetSelectedRows() << std::endl;
  
  TGraph *gr_laser  = new TGraph(ntu->GetSelectedRows(), ntu->GetV2(), ntu->GetV1());  
  

  //
  //---- different format 
  //
  laser_string  = Form ("cor");
  time_string  = Form ("time[0]");
  toDraw = Form ("%s:%s", laser_string.Data(), time_string.Data());
  if (isEB == 0) toCut = Form ("x==%d && y==%d && z==%d", ix, iy, iz);
  if (isEB == 1) toCut = Form ("eta==%d && phi==%d", ix, iy);
  
  std::cout << " toDraw = " << toDraw.Data() << std::endl;
  std::cout << " toCut  = " << toCut.Data()  << std::endl;  
  ntu2->Draw(toDraw.Data(), toCut.Data(), "goff");
  std::cout << " ntu2->GetSelectedRows() = " << ntu2->GetSelectedRows() << std::endl;
  
  TGraph *gr_laser2  = new TGraph(ntu2->GetSelectedRows(), ntu2->GetV2(), ntu2->GetV1());  
  
  
  //---- style ----
  
  gr_laser->SetMarkerSize  (0.2);               
  gr_laser->SetMarkerStyle (20);              
  gr_laser->SetMarkerColor (kRed);            
  gr_laser->SetLineWidth (1);                 
  gr_laser->SetLineColor (kRed);              
  

  gr_laser2->SetMarkerSize  (0.2);               
  gr_laser2->SetMarkerStyle (21);              
  gr_laser2->SetMarkerColor (kBlue);            
  gr_laser2->SetLineWidth (1);                 
  gr_laser2->SetLineColor (kBlue);              
  
  //---- style (end) ----
  
  
  TCanvas* cclaser = new TCanvas ("cclaser","",1600,600);
  gr_laser->Draw("AP");
  gr_laser2->Draw("P");
  gr_laser->GetYaxis()->SetTitle("transparency");
  gr_laser->GetXaxis()->SetTitle("time");
  gr_laser->GetXaxis()->SetTimeDisplay(1);
  gr_laser->GetXaxis()->SetNdivisions(-503);
  gr_laser->GetXaxis()->SetTimeFormat("%Y-%m-%d %H:%M");
  gr_laser->GetXaxis()->SetTimeOffset(0,"gmt");
  cclaser->SetGrid();
  
  
    
}




