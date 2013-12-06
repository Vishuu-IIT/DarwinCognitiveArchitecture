// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-      
/**
* \defgroup icub_controlbasis_libraries Control Basis Libraries
* @ingroup icub_controlbasis_libraries
*
*/
#include "iCubHeadConfigurationVariables.h"

#include <yarp/math/Math.h>

using namespace std;
using namespace yarp::dev;
using namespace yarp::os;
using namespace yarp::sig;
using namespace yarp::math;


void CB::iCubHeadConfigurationVariables::startResource() {
    start();     // mandatory start function
}

bool CB::iCubHeadConfigurationVariables::connectToDevice() {

    // if this is the first time running, need to connec to the PolyDriver.
    bool ok;
    int idx;
    cout << "iCubHeadConfigurationVariables() -- connecting to port..." << endl;

    // if the resource hasnt connected to the YARP device, do it now
    if(!connectedToDevice) {
        if(!connectToDevice()) {
            cout << "Couldn't connect to YARP port in startResource()..." << endl;
            return false;
        }
    }

    //    Property options;
    string local_name = localDevPort + "/client";
    string remote_name = remoteDevPort;
    
    options.put("device", "remote_controlboard");
    options.put("local", local_name.c_str());
    options.put("remote", remote_name.c_str());
    fprintf(stderr, "%s", options.toString().c_str());

    cout << endl << "creating new PolyDriver for " << remoteDevPort << endl;
    dd = new PolyDriver(options);       
    cout << "created." << endl;

    if (!dd->isValid()) {
        cout << "Device not available.  Here are the known devices:" << endl;
        cout << Drivers::factory().toString().c_str() << endl;
        ok = false;
    }    
    ok = dd->view(pos);
    ok &= dd->view(enc);
    ok &= dd->view(lim);
    ok &= dd->view(vel);

    if (!ok) {
        cout << "Problems acquiring interfaces" << endl;
        return ok;
    }
    Time::delay(1);  // necessary to make sure PolyDriver data is correct.

    // now get information from device
    int jnts = 0;
    pos->getAxes(&jnts);

    // get initial joint values (masking unwanted ones)
    double *tmp = new double[jnts];
    enc->getEncoders(tmp);
    idx = 0;
    for(int i = 0; i < mask.size(); i++) {
        if(!mask[i]) continue;
        values[idx] = tmp[i]*TORAD;
        desiredValues[idx] = values[idx]; // set initial desired to first read vals
        idx++;
    }

    // get joint limit information
    double min, max;
    idx = 0;
    for(int i = 0; i < mask.size(); i++) {
        if(!mask[i]) continue;
        lim->getLimits(i, &min, &max);
        minLimits[idx] = min*TORAD;
        maxLimits[idx] = max*TORAD;
        cout << "limits[" << idx << "]: (" << min << "," << max << ")" << endl;
        idx++;
    }    

    // set the connected flag cause everything seems to be okay
    connectedToDevice = true;

    return ok; 

}

bool CB::iCubHeadConfigurationVariables::updateResource() {

    // get current values of config variables from PolyDriver
    bool ok;
    ok = dd->view(pos);
    ok &= dd->view(enc);
    ok &= dd->view(lim);

    if (!ok) {
        cout << "Problems acquiring interfaces" << endl;
        return ok;
    }

    iterations++;

    // get encoder data (6-DOF)
    int jnts = 0;
    pos->getAxes(&jnts);
    double *tmp = new double[jnts];
    enc->getEncoders(tmp);

    // make sure the size of the mask vector matches the total number of DOFs of the device
    if( jnts != mask.size() ) {
        cout << "iCubHeadConfiguration::updateResource() -- number of Joints from iCubHead motor interface mismatch!!" << endl;
        return false;
    }    

    // copy the device positions to the local resource data (masking out values if necessary)
    int idx = 0;
    for(int i = 0; i < mask.size(); i++) {
        if(!mask[i]) continue;
        values[idx++] = tmp[i]*TORAD;
    }

    // set device values for (unmasked) joints
    if(!velocityControlMode) {
        // send to PolyDriver
        if(moveable && !lock) {
            idx = 0;
            for(int i=0; i<mask.size(); i++) {
                if(!mask[i]) continue;
                pos->positionMove(i, desiredValues[idx++]*TODEG);            
            }
            
            //            cout << "current position: [" << values[0] << ", " << values[1]<< ", " << values[2] << "]" << endl;
            //cout << "sending position: [" << desiredValues[0] << ", " << desiredValues[1]<< ", " << desiredValues[2] << "]" << endl;
            //cout << endl;
        }
    } else {
        // send to velocityControl module
        if(moveable && !lock) {            

            Bottle &v = velocityPort.prepare();
            //v.resize(mask.size(),0);       
            idx = 0;
            for(int i=0; i<mask.size(); i++) {
                if(mask[i]) {
                    v.addInt(i);
                    v.addDouble(desiredValues[idx++]*TODEG);            
                }
            }
            velocityPort.write();
            
            /*
            Vector &v = velocityPort.prepare();
            v.resize(mask.size(),0);       
            idx = 0;
            for(int i=0; i<mask.size(); i++) {
                if(mask[i]) {
                    v[i] = desiredValues[idx++]*TODEG;            
                }
            }
            velocityPort.write();
            */
        }
    }

    return ok;
}

void CB::iCubHeadConfigurationVariables::postData() {
            
    // prepare the output bottles to post information           
    yarp::os::Bottle &b0 = outputPort[0]->prepare();
    yarp::os::Bottle &b1 = outputPort[1]->prepare();
    yarp::os::Bottle &b2 = outputPort[2]->prepare();
    
    b0.clear();
    b1.clear();
    b2.clear();

    b0.addInt((int)valid);
    b0.addInt(numDOFs);
    b1.addInt(numDOFs);

    if(usingYaw) {
        virtualInputData[0] = -values[2]; // pan
        virtualInputData[1] =  values[0]; // tilt
        virtualInputData[2] =  values[1]; // yaw
    } else {
        virtualInputData[0] = -values[2]; // pan
        virtualInputData[1] =  values[0]; // tilt
    }

  /*  
    if( (iterations%50)==0 ) {
        cout<<"Read Robot Data:      ["<<values[0]<<", "<<values[1]<<", "<<values[2]<<"]"<<endl;
        if(usingYaw) {  
            cout<<"Mapped to Robot Data: ["<<virtualInputData[0]<<", "<<virtualInputData[1]<<", "<<virtualInputData[2]<<"]"<<endl;
        } else {
            cout<<"Mapped to Robot Data: ["<<virtualInputData[0]<<", "<<virtualInputData[1]<<"]"<<endl;     
        }
    }
  */
    for(int i = 0; i < numDOFs; i++) {
        
        // add position to output port
        b0.addDouble(virtualInputData[i]);
        
        // add limit information to output port
        b1.addDouble(minLimits[i]);
        b1.addDouble(maxLimits[i]);
        
    }
    
    // write the information to the ports
    outputPort[0]->write(); 
    outputPort[1]->write();      
    
    b2.addInt(numLinks);
    for(int i=0; i < numLinks; i++) {
        for(int j = 0; j < 4; j++) {
            b2.addDouble(DHParameters[j][i]);
        }
        b2.addInt(LinkTypes[i]);
    }
    outputPort[2]->write();
    
}

void CB::iCubHeadConfigurationVariables::getInputData() {
    
    // If the resource is not moveable, there shouldn't be an input port.
    // In other words, no other service should be sending inputs to this resource.
    if(!moveable) {
        numInputs = 0;
        for(unsigned int i=0; i<inputPort.size(); i++) {
            inputPort[i]->close();
        }
        inputPort.clear();
        return;
    }
    
    yarp::os::Bottle *b[2];
    yarp::sig::Matrix virtualInData(numDOFs,1);
    yarp::sig::Matrix inData(numDOFs+(int)!usingYaw,1);
    yarp::sig::Vector VinData(numDOFs);
    
    b[0] = inputPort[0]->read(false);      
    b[1] = inputPort[1]->read(false);      
    
    if(b[0]!=NULL) {
        
        // parse joint values
        for(int i = 0; i < numDOFs; i++)  {
            virtualInData[i][0] = b[0]->get(i).asDouble();
        }
    
        mapping.zero();
        mapping[0][1] =  1.0;
        if(usingYaw) {
            mapping[1][2] =  1.0;
        }
        mapping[2][0] = -1.0;
        inData = mapping*virtualInData;            

/*
        cout<<"Setting Virtual Data: ["<<virtualInData[0][0]<<", "
          <<virtualInData[1][0]<<
//          ", "<<virtualInData[2][0]<<
        "]"<<endl;
        
        cout<<"Mapped to Robot Data: ["<<inData[0][0]<<", "<<inData[1][0]<<", "<<inData[2][0]<<"]"<<endl;
*/
        if(usingYaw) {
           VinData[0]=inData[0][0];
           VinData[1]=inData[1][0];
           VinData[2]=inData[2][0];
        } else {
           VinData[0]=inData[0][0];
           VinData[1]=inData[2][0];
        }
        
        // trim input delta by max allowable magnitude
        yarp::sig::Vector trimmed = trimInputData(VinData);
        setDesiredIncrement(trimmed);
        
    }
    
    // see if there has been a lock change
    if(b[1]!=NULL) {
        lock = (bool)(b[1]->get(0).asInt());
    }
    
}
