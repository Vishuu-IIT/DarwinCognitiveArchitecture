// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/**
*
\author Marco Randazzo

Copyright (C) 2008 RobotCub Consortium

CopyPolicy: Released under the terms of the GNU GPL v2.0.

**/

#include <stdio.h>
#include <yarp/dev/PolyDriver.h>
#include <yarp/os/Time.h>
#include <yarp/sig/Vector.h>
#include <yarp/os/RateThread.h>
#include <yarp/os/Network.h>
#include <iostream>
#include <iomanip>
#include <string>

using namespace yarp::dev;
using namespace yarp::sig;
using namespace yarp::os;

using namespace std;

const int THREAD_RATE=10; //ms


class FtThread: public RateThread
{
	public:
	double val[6];
	double off[6];
	bool first_run;
	yarp::os::BufferedPort <Bottle> port;

    FtThread(int r=THREAD_RATE): RateThread(r)
	{
		first_run=true;
		fprintf(stdout,"constructor \n");
	}

    bool threadInit()
    {
		port.open ("/FTsensorTest:i");
		fprintf(stdout,"init \n");
		return true;
    }

    void run()
    {
		Bottle *input = port.read();
		if (input!=NULL)
		{
			if (first_run)
			{
			    for (int i=0; i<input->size(); i++)
				{
					off[i]=input->get(i).asDouble();
				}
				first_run=false;
			}

            //cout << "got " << input->toString().c_str() << endl;
            
            for (int i=0; i<input->size(); i++)
			{
                val[i]=input->get(i).asDouble();
				fprintf(stdout,"%+11.3f",val[i]);
	        }
			fprintf (stdout,"   *****   ");
			for (int i=0; i<input->size(); i++)
			{
				fprintf(stdout,"%+11.3f",val[i]-off[i]);
	        }
			fprintf (stdout,"\n");
		}

		/*
		static double time_old_wd=Time::now();
		double time_wd=Time::now();
		fprintf(stdout,"time%+3.3f       ", time_wd-time_old_wd);
		cout << "       " << output.toString().c_str() << endl;
		time_old_wd=time_wd;
		*/
	}
};

int main(int argc, char *argv[]) 
{
	yarp::os::Network yarp;
	yarp::os::Time::turboBoost();

    if (!yarp.checkNetwork())
	{
		fprintf(stderr, "Sorry YARP network does not seem to be available, is the yarp server available?\n");
        return -1;
	}

    FtThread thread;
    thread.start();

    while(1)
    {
		Time::delay(1);
    }

    thread.stop();
}