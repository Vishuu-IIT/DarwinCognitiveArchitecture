//##############################################################################################################################################################################################################//
//Aquila - An Open-Source GPU-Accelerated Toolkit for Cognitive and Neuro-Robotics Research																														//
//																																																				//
//Copyright (c) <2012>, YourName                                                                                                                                                                                //
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

#ifndef BLANK_H
#define BLANK_H

#include <omp.h>
#include <QThread>
#include <cuda.h>
#include <cuda_runtime.h>
#include "aquila-utility.h"

using namespace aquila;
using namespace std;

class Blank : public QThread
{
    Q_OBJECT

public:
    Blank();
    ~Blank();

    GPU *gpu;

private:
    bool simulationMode;
    bool running;

    void run();

public:
    bool terminalMode;

    void clean();
    void connectPorts();
    void disconnectPorts();
    bool openPorts(QString portPrefix);
    void stop();
    void setSimulationMode(bool active);
    bool getSimulationMode();

signals:
    void messageSet(QString message);
    void started(int id);
    void stopped(int id);
};

#endif//BLANK_H
