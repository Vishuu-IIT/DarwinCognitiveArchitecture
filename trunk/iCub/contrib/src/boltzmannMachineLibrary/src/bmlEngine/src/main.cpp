// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/* 
 * Copyright (C) 2010 RobotCub Consortium, European Commission FP6 Project IST-004370
 * Authors: Francesco Rea
 * email:   francesco.rea@iit.it
 * website: www.robotcub.org 
 * Permission is granted to copy, distribute, and/or modify this program
 * under the terms of the GNU General Public License, version 2 or any
 * later version published by the Free Software Foundation.
 *
 * A copy of the license can be found at
 * http://www.robotcub.org/icub/license/gpl.txt
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
 * Public License for more details
 */
  
/**
 * @file main.cpp
 * @brief main code for the building of a saliency map based on colour information
 */


#include <iostream>

#include <yarp/os/all.h>
#include <yarp/sig/all.h>

//within the project includes
#include <iCub/BMLEngine.h>
#include <iCub/MachineBoltzmann.h>
#include <iCub/BMLEngine.h>

using namespace yarp::os;
using namespace yarp::sig;


int main(int argc, char * argv[])
{
    Network yarp;
    
    //Matrix m(20000,20000);
    //printf("EOF \n");
    
    Time::turboBoost();
    BMLEngine module; 

    ResourceFinder rf;
    rf.setVerbose(true);
    rf.setDefaultConfigFile("bmlEngine.ini"); //overridden by --from parameter
    rf.setDefaultContext("bmlApplication/conf");   //overridden by --context parameter
    rf.configure("ICUB_ROOT", argc, argv);
 
    module.runModule(rf);
    return 0;
}
