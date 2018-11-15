# EcalLaser

Plot laser response vs time, from ntuples

Ntuple example:

    scp amassiro@lxplus.cern.ch:/eos/cms/store/group/dpg_ecal/comm_ecal/pedestals_gainratio/Laser2017_noTP.root .
    scp amassiro@lxplus.cern.ch:/eos/cms/store/group/dpg_ecal/comm_ecal/trigger/lkardapo/tuples/transp2017-prompt.root  .

    scp amassiro@lxplus.cern.ch:/eos/cms/store/group/dpg_ecal/comm_ecal/pedestals_gainratio/LaserBlue_noTP_2017_newformat.root /media/amassiro/SAMSUNG/data/ECAL/Laser/
    
    
    
    
Plot:

    r00t draw.cxx
    r00t draw.cxx\(\"Laser2017_noTP.root\",62,50,1\)

    red = noTP 
    blue = prompt
    
    EE
    r00t drawComparison.cxx\(\"Laser2017_noTP.root\",\"transp2017-prompt.root\",62,50,1\)
    r00t drawComparison.cxx\(\"Laser2017_noTP.root\",\"transp2017-prompt.root\",62,50,1\)
    r00t drawComparison.cxx\(\"Laser2017_noTP.root\",\"transp2017-prompt.root\",73,91,-1\)
    ix=73, iy=91, iz=-1
    
    EB
    r00t drawComparison.cxx\(\"Laser2017_noTP.root\",\"transp2017-prompt.root\",82,120,0\)
    
    
    r00t drawComparison.cxx\(\"Laser2017_noTP.root\",\"transp2017-prompt-all.root\",82,120,0\)
    r00t drawComparison.cxx\(\"Laser2017_noTP.root\",\"transp2017-prompt-all.root\",20,120,0\)
    r00t drawComparison.cxx\(\"Laser2017_noTP.root\",\"transp2017-prompt-all.root\",21,120,0\)
    
    r00t drawComparison.cxx\(\"Laser2017_noTP.root\",\"transp2017-prompt-all.root\",-3,25,0\)
    
    r00t drawComparison.cxx\(\"Laser2017_noTP.root\",\"transp2017-prompt-all.root\",-3,25,0\)
    
    

Check single crystal history:

    r00t draw.cxx\(\"LaserBlue_noTP_2017_newformat.root\",65,36,-1\)

    r00t draw.cxx\(\"LaserBlue_noTP_2017_newformat.root\",65,35,-1\)
    r00t draw.cxx\(\"LaserBlue_noTP_2017_newformat.root\",65,37,-1\)

    r00t draw.cxx\(\"LaserBlue_noTP_2017_newformat.root\",64,36,-1\)
    r00t draw.cxx\(\"LaserBlue_noTP_2017_newformat.root\",66,36,-1\)

    
    
where:

    /home/amassiro/Cern/Code/ECAL/EcalLaser/
