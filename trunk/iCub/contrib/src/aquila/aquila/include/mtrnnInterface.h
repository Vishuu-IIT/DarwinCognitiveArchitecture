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

#ifndef MTRNN_INTERFACE_H
#define MTRNN_INTERFACE_H

#include "interface.h"

/*! Interface between MTRNN GUI and MTRNN module */
class MTRNNInterface : public Interface
{
    Q_OBJECT

public:
    MTRNNInterface(GUI *pGUI);

    void sendTrainingFileData(int numControlNeurons, int numLinguisticNeurons, int numVisionNeurons, int numActionNeurons, int numSequences, int sequenceWidth, float minValue, float maxValue, QVector<int> seqenceSteps, QVector<float> sequenceData, int maxSequenceSteps, int totalSequenceSteps);
    void sendTrainingRequest(QString fileName);
    void sendTrainingRequest();
    void sendSaveRequest(QString fileName);
    void sendNetworkRequest();

protected:
    void processPortData();

private:
    void processNetwork();
    void processErrors();

public slots:
    void sendParameters(float learningRate, float momentum, float weightRange, float threshold, int iterations, int seed, int numFastNeurons, int numSlowNeurons, int ioDeltaT, int fastDeltaT, int slowDeltaT, int plotUpdateInterval);

signals:
    void errorReceived(int iteration, float error);
    void networkReceived(QVector<float> network);
    void errorsReceived(QVector<float> errors);
    void parametersReceived(float learningRate, float momentum, float weightRange, float threshold, int iterations, int seed, int numFastNeurons, int numSlowNeurons, int ioDeltaT, int fastDeltaT, int slowDeltaT, int plotUpdateInterval);
};

#endif//MTRNN_INTERFACE_H
