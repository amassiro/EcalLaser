# EcalLaser

Plot laser response vs time, from ntuples

Ntuple example:

    scp amassiro@lxplus.cern.ch:/eos/cms/store/group/dpg_ecal/comm_ecal/pedestals_gainratio/Laser2017_noTP.root .
    scp amassiro@lxplus.cern.ch:/eos/cms/store/group/dpg_ecal/comm_ecal/trigger/lkardapo/tuples/transp2017-prompt.root  .

Plot:

    r00t draw.cxx
    r00t draw.cxx\(\"Laser2017_noTP.root\",62,50,1\)
    r00t draw.cxx\(\"transp2017-prompt.root\",62,50,1\)
    
where:

    /home/amassiro/Cern/Code/ECAL