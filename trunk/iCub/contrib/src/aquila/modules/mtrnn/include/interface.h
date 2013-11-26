//##############################################################################################################################################################################################################//
//Aquila - An Open-Source GPU-Accelerated Toolkit for Cognitive and Neuro-Robotics Research																														//
//																																																				//
//Copyright (c) <2012>, <Martin Peniak - www.martinpeniak.com>																																					//
//All rights reserved.																																															//
//																																																				//
//Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:																//
//																																																				//
// - Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.																				//
// - Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.	//
//																																																				//
//THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR	//
//A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT	//
//LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR	//
//TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.																//
//                                                                                                                                                                                                              //
//The views and conclusions contained in the software and documentation are those of the authors and should not be interpreted                                                                                  //
//as representing official policies,either expressed or implied, of the FreeBSD Project.                                                                                                                        //
//##############################################################################################################################################################################################################//

#ifndef INTERFACE_H
#define INTERFACE_H

#include "aquila-nnet-mtrnn.h"
#include "aquila-utility.h"
#include <yarp/os/all.h>
#include <QThread>

using namespace yarp::os;
using namespace aquila;

class Interface : public QThread
{
    Q_OBJECT

public:
	Interface();
    void initialise(ResourceFinder &rf);

private:
    MTRNN *mtrnn;
    Messenger *messenger;

    GPU *gpu;
    QString moduleName;
    QString inputPortName;
    QString outputPortName;
    Bottle command;
    Port inputPort;
    Port outputPort;
    int instance;

    void run();
    void waitForConsole();

private slots:
    void clean();
    void processTrainingStart();
    void processTrainingStop(QVector<float> errors);
    void sendParameters(float learningRate, float momentum, float threshold, float weightRange, int iterations, int seed, int numFastNeurons, int numSlowNeurons, int ioDeltaT, int fastDeltaT, int slowDeltaT, int portUpdateInterval);
    void sendError(int iteration, float error);
    void sendNetwork();

signals:
    void quitting();
};

#endif//INTERFACE_H
