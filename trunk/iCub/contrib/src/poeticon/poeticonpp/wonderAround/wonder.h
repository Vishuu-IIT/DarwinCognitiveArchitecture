/* 
 * Copyright (C) 2012 Department of Robotics Brain and Cognitive Sciences - Istituto Italiano di Tecnologia
 * Author: Ali Paikan
 * email:  ali.paikan@iit.it
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
#include <string>
#include <yarp/os/ResourceFinder.h>
#include <yarp/os/BufferedPort.h>
#include <yarp/dev/Drivers.h>
#include <yarp/dev/ControlBoardInterfaces.h>
#include <yarp/dev/GazeControl.h>
#include <yarp/dev/CartesianControl.h>
#include <yarp/dev/PolyDriver.h>
#include <yarp/sig/Vector.h>
#include <yarp/math/Rand.h>


YARP_DECLARE_DEVICES(icubmod)

class Wonder
{
   
public:

    Wonder()
    {
       // constructor
    }

    bool open(yarp::os::ResourceFinder &rf);

    bool close();

    void loop(); 

    bool interrupt();


private: 
    void gazeRest();

private:
    yarp::os::BufferedPort<yarp::os::Bottle> targetPort;
    yarp::os::BufferedPort<yarp::os::Bottle> rightArmRelaxPort;
    yarp::os::BufferedPort<yarp::os::Bottle> leftArmRelaxPort;
    yarp::os::BufferedPort<yarp::os::Bottle> faceExpPort;
    yarp::os::BufferedPort<yarp::os::Bottle> graspCmdPort;

    bool leftArmEnabled;
    bool rightArmEnabled;
    std::string faceExpression;
};

   
   



   
