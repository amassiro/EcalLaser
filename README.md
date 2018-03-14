# EcalLaser

Plot laser response vs time, from ntuples

Ntuple example:

    scp amassiro@lxplus.cern.ch:/eos/cms/store/group/dpg_ecal/comm_ecal/pedestals_gainratio/Laser2017_noTP.root .
    scp amassiro@lxplus.cern.ch:/eos/cms/store/group/dpg_ecal/comm_ecal/trigger/lkardapo/tuples/transp2017-prompt.root  .

Plot:

    r00t draw.cxx
    r00t draw.cxx\(\"Laser2017_noTP.root\",62,50,1\)
    
    EE
    r00t drawComparison.cxx\(\"Laser2017_noTP.root\",\"transp2017-prompt.root\",62,50,1\)
    r00t drawComparison.cxx\(\"Laser2017_noTP.root\",\"transp2017-prompt.root\",62,50,1\)
    r00t drawComparison.cxx\(\"Laser2017_noTP.root\",\"transp2017-prompt.root\",73,91,-1\)
    ix=73, iy=91, iz=-1
    
    EB
    r00t drawComparison.cxx\(\"Laser2017_noTP.root\",\"transp2017-prompt.root\",82,120,0\)
    
    
    r00t drawComparison.cxx\(\"Laser2017_noTP.root\",\"transp2017-prompt-all.root\",82,120,0\)
    r00t drawComparison.cxx\(\"Laser2017_noTP.root\",\"transp2017-prompt-all.root\",20,120,0\)
    
    
    
    
    
where:

    /home/amassiro/Cern/Code/ECAL