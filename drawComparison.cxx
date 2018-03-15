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
  
  std::cout << "   toDraw = " << toDraw.Data() << std::endl;
  std::cout << "   toCut  = " << toCut.Data()  << std::endl;
  
  ntu->Draw(toDraw.Data(), toCut.Data(), "goff");
  std::cout << "   ntu->GetSelectedRows() = " << ntu->GetSelectedRows() << std::endl;
  
  TGraph *gr_laser  = new TGraph(ntu->GetSelectedRows(), ntu->GetV2(), ntu->GetV1());  
  

  //
  //---- different format 
  //
  laser_string  = Form ("cor");
  time_string  = Form ("time[0]");
  toDraw = Form ("%s:%s", laser_string.Data(), time_string.Data());
  if (isEB == 0) toCut = Form ("x==%d && y==%d && z==%d", ix, iy, iz);
  if (isEB == 1) toCut = Form ("eta==%d && phi==%d", ix, iy);
  
  std::cout << "   toDraw = " << toDraw.Data() << std::endl;
  std::cout << "   toCut  = " << toCut.Data()  << std::endl;  
  ntu2->Draw(toDraw.Data(), toCut.Data(), "goff");
  std::cout << "   ntu2->GetSelectedRows() = " << ntu2->GetSelectedRows() << std::endl;
  
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
  
  
  
  TCanvas* cclaserratio = new TCanvas ("cclaserratio","",1600,600);
  TGraph *gr_laser_ratio  = new TGraph();
  TGraph *gr_laser_difference  = new TGraph();

  TGraph *gr_laser_1  = new TGraph();
  TGraph *gr_laser_2  = new TGraph();
  TGraph *gr_laser_2_1time  = new TGraph();
  
  int totpoints = ntu2->GetSelectedRows();
  int totpoints2 = totpoints;
  if (totpoints > ntu->GetSelectedRows()) {
    totpoints = ntu->GetSelectedRows();
  }
  int ipoint = 0;
  int jpoint = 0;
  int lastjpoint = 0;
  for (int i=0; i<totpoints; i++) {
    //---- 30 minutes window  30 * 60 seconds
    for (int j=lastjpoint; j<(lastjpoint+10); j > lastjpoint ?  j += ((lastjpoint - j)*2 ) : j += ((lastjpoint - j)*2 + 1 ) ) {
//       std::cout << " i = " << i << std::endl;
//       std::cout << " j = " << j << std::endl;
//             std::cout << "     lastjpoint = " << lastjpoint << std::endl;
//             std::cout << "     j >  lastjpoint    = " << int(j >  lastjpoint) << std::endl;
//             std::cout << "     ((lastjpoint - j)*2    ) = " << ((lastjpoint - j)*2    ) << " ---> " <<  j + ((lastjpoint - j)*2    )  << std::endl;
//             std::cout << "     ((lastjpoint - j)*2 + 1) = " << ((lastjpoint - j)*2 + 1) << " ---> " <<  j + ((lastjpoint - j)*2 +1 )  << std::endl;
            //       
      //
      //           x
      //
//       for (int j=(lastjpoint-10); j<(lastjpoint+10); j++) {
      if ((j>=0) && (j<totpoints2) ) {
        if ( abs(ntu->GetV2()[i] - ntu2->GetV2()[j]) <  60*30) {   
          gr_laser_ratio->SetPoint      (ipoint, ntu->GetV2()[i], (ntu2->GetV1()[j] ? ntu->GetV1()[i] / ntu2->GetV1()[j] : 0) );  
          gr_laser_difference->SetPoint (ipoint, ntu->GetV2()[i], ntu->GetV1()[i] - ntu2->GetV1()[j] );  
          
          gr_laser_1->SetPoint (ipoint, ntu->GetV2()[i], ntu->GetV1()[i] );  
          gr_laser_2->SetPoint (ipoint, ntu2->GetV2()[j], ntu2->GetV1()[j] );  
          gr_laser_2_1time->SetPoint (ipoint, ntu->GetV2()[i], ntu2->GetV1()[j] );  
          
          
          ipoint++;
          
          jpoint=j;
          jpoint++;
          
          lastjpoint=j;
          
          break;        
        }
      }
    }
  }
  std::cout << " ipoint = " << ipoint << std::endl;
  std::cout << " jpoint = " << jpoint << std::endl;
  
  
  gr_laser_ratio->SetMarkerSize  (0.2);               
  gr_laser_ratio->SetMarkerStyle (21);              
  gr_laser_ratio->SetMarkerColor (kMagenta);            
  gr_laser_ratio->SetLineWidth (1);                 
  gr_laser_ratio->SetLineColor (kMagenta);              
  
  
  gr_laser_ratio->Draw("AP");
  gr_laser_ratio->GetYaxis()->SetTitle("transparency ratio");
  gr_laser_ratio->GetXaxis()->SetTitle("time");
  gr_laser_ratio->GetXaxis()->SetTimeDisplay(1);
  gr_laser_ratio->GetXaxis()->SetNdivisions(-503);
  gr_laser_ratio->GetXaxis()->SetTimeFormat("%Y-%m-%d %H:%M");
  gr_laser_ratio->GetXaxis()->SetTimeOffset(0,"gmt");
  cclaserratio->SetGrid();
  




  TCanvas* cclaserdifference = new TCanvas ("cclaserdifference","",1600,600);
  
  gr_laser_difference->SetMarkerSize  (0.2);               
  gr_laser_difference->SetMarkerStyle (21);              
  gr_laser_difference->SetMarkerColor (kMagenta);            
  gr_laser_difference->SetLineWidth (1);                 
  gr_laser_difference->SetLineColor (kMagenta);              
  
  
  gr_laser_difference->Draw("AP");
  gr_laser_difference->GetYaxis()->SetTitle("transparency difference");
  gr_laser_difference->GetXaxis()->SetTitle("time");
  gr_laser_difference->GetXaxis()->SetTimeDisplay(1);
  gr_laser_difference->GetXaxis()->SetNdivisions(-503);
  gr_laser_difference->GetXaxis()->SetTimeFormat("%Y-%m-%d %H:%M");
  gr_laser_difference->GetXaxis()->SetTimeOffset(0,"gmt");
  cclaserdifference->SetGrid();
  
  
  
  //---- style ----
  
  gr_laser_1->SetMarkerSize  (0.2);               
  gr_laser_1->SetMarkerStyle (20);              
  gr_laser_1->SetMarkerColor (kRed);            
  gr_laser_1->SetLineWidth (1);                 
  gr_laser_1->SetLineColor (kRed);              
  
  
  gr_laser_2->SetMarkerSize  (0.2);               
  gr_laser_2->SetMarkerStyle (21);              
  gr_laser_2->SetMarkerColor (kBlue);            
  gr_laser_2->SetLineWidth (1);                 
  gr_laser_2->SetLineColor (kBlue);              

  gr_laser_2_1time->SetMarkerSize  (0.2);               
  gr_laser_2_1time->SetMarkerStyle (21);              
  gr_laser_2_1time->SetMarkerColor (kGreen);            
  gr_laser_2_1time->SetLineWidth (1);                 
  gr_laser_2_1time->SetLineColor (kGreen);              
  
  
  
  
  //---- style (end) ----
  
  
  TCanvas* cclasercomp = new TCanvas ("cclasercomp","laser comp",1600,600);
  
  gr_laser_1->Draw("AP");
  gr_laser_2_1time->Draw("P");
  gr_laser_2->Draw("P");
  gr_laser_1->GetYaxis()->SetTitle("transparency");
  gr_laser_1->GetXaxis()->SetTitle("time");
  gr_laser_1->GetXaxis()->SetTimeDisplay(1);
  gr_laser_1->GetXaxis()->SetNdivisions(-503);
  gr_laser_1->GetXaxis()->SetTimeFormat("%Y-%m-%d %H:%M");
  gr_laser_1->GetXaxis()->SetTimeOffset(0,"gmt");
  cclasercomp->SetGrid();
  
  
  
    
}




