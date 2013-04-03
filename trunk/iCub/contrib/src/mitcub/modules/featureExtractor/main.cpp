

#include <yarp/os/Network.h>
#include <yarp/os/Time.h>

#include "ExtractorModule.h"

int main(int argc, char *argv[])
{
    Network yarp;

    double t0=Time::now();

    while(!yarp.checkNetwork() && Time::now()-t0<3.0)
        Time::delay(0.1);

    if (!yarp.checkNetwork())
        return -1;

    ResourceFinder rf;
    rf.setVerbose(true);
    rf.setDefaultContext("featureExtractor/conf");
    rf.setDefaultConfigFile("config.ini");
    rf.setDefault("name","featureExtractor");
    rf.configure("ICUB_ROOT",argc,argv);

    ExtractorModule mod;

    return mod.runModule(rf);
}


//
//#include <algorithm>
//
//#include "Extractor.h"
//#include "ExtractorFactory.h"
//
//
////includes for the the extractors
//#include "DummyExtractor.h"
//#include "HmaxExtractor.h"
//#include "HighDimensionalityFeatureExtractor.h"
//#include "BagOfWordsExtractor.h"
//
//
//bool update_class_list(vector<string> &class_list, vector<string> &tmp_class_list)
//{
//    for(int i=0; i<tmp_class_list.size(); i++)
//    {
//        bool found=false;
//        for(int j=0; j<class_list.size(); j++)
//        {
//            if(tmp_class_list[i]==class_list[j])
//            {
//                found=true;
//                break;
//            }
//        }
//
//        if(!found)
//            class_list.push_back(tmp_class_list[i]);
//    }
//
//    return true;
//}
//
//
//bool check_class(string class_name, Bottle &labels)
//{
//    bool found=false;
//    for(int i=0; i<labels.size(); i++)
//        if(class_name==labels.get(i).asString().c_str())
//            found=true;
//
//    return found;
//}
//
//
//int main(int argc, char *argv[])
//{
//    //register the extractors in the factory
//    ExtractorFactory::instance().registerExtractor("dummy_extractor",new DummyExtractor());
//    ExtractorFactory::instance().registerExtractor("high_dimensionality_feature_extractor",new HighDimensionalityFeatureExtractor());
//    ExtractorFactory::instance().registerExtractor("hmax_extractor",new HmaxExtractor());
//    ExtractorFactory::instance().registerExtractor("bag_of_words_extractor",new BagOfWordsExtractor());
//
//
//    ResourceFinder rf;
//    rf.setVerbose(true);
//    rf.setDefaultContext("datasetCreator/conf");
//    rf.setDefaultConfigFile("config.ini");
//    rf.configure("ICUB_ROOT",argc,argv);
//
//    Bottle &bGeneral=rf.findGroup("general");
//
//    Bottle &bDatasets=rf.findGroup("extractors");
//
//
//    vector<Extractor*> extractors;
//
//    vector<string> class_list;
//    int feature_size=-1;
//    int n_samples=0;
//    for(int i=1; i<bDatasets.size(); i++)
//    {
//        Extractor *tmp_ext=ExtractorFactory::instance().create(rf,bDatasets.get(i).asList()->get(0).asString().c_str());
//        if(tmp_ext!=NULL)
//        {
//            int tmp_feature_size;
//            tmp_ext->get_feature_size(&tmp_feature_size);
//            if(feature_size=-1)
//                feature_size=tmp_feature_size;
//
//            if(feature_size==tmp_feature_size)
//            {
//
//                int tmp_n_samples;
//                tmp_ext->get_n_samples(&tmp_n_samples);
//                n_samples+=tmp_n_samples;
//
//                //update class_list
//                vector<string> tmp_class_list;
//                tmp_ext->get_class_list(&tmp_class_list);
//                update_class_list(class_list,tmp_class_list);
//
//                extractors.push_back(tmp_ext);
//            }
//        }
//    }
//
//    //sort the list
//    sort(class_list.begin(),class_list.end());
//
//
//    //create the X and Y matrices
//    double *X=new double[n_samples*feature_size];
//    double *Y=new double[n_samples*class_list.size()];
//
//
//    int curr_idx=0;
//
//    for(int i=0; i<extractors.size(); i++)
//    {
//        while(extractors[i]->extract())
//        {
//            Matrix feature_vector;
//            Bottle labels;
//
//            extractors[i]->getFeatureVector(&feature_vector);
//            extractors[i]->getLabels(&labels);
//
//            for(int j=0; j<feature_size; j++)
//                X[curr_idx*feature_size+j]=feature_vector[0][j];
//
//            //set the labels as 0s and 1s
//            for(int j=0; j<class_list.size(); j++)
//            {
//                if(check_class(class_list[j],labels))
//                    Y[curr_idx*class_list.size()+j]=1.0;
//                else
//                    Y[curr_idx*class_list.size()+j]=-1.0;
//            }
//
//            curr_idx++;
//        }
//    }
//
//
//    FILE *test_order=fopen("order.txt","w");
//    FILE *test_x=fopen("X.txt","w");
//    FILE *test_y=fopen("Y.txt","w");
//
//
//
//    for(int j=0; j<class_list.size(); j++)
//    {
//        fprintf(stdout,"%s ",class_list[j].c_str());
//        fprintf(test_order,"%s ",class_list[j].c_str());
//    }
//
//    for(int i=0; i<n_samples; i++)
//    {
//        for(int j=0; j<feature_size; j++)
//            fprintf(test_x,"%f ",X[i*feature_size+j]);
//        fprintf(test_x,"\n");
//
//        for(int j=0; j<class_list.size(); j++)
//            fprintf(test_y,"%f ",Y[i*class_list.size()+j]);
//        fprintf(test_y,"\n");
//    }
//
//    delete [] X;
//    delete [] Y;
//
//    fclose(test_x);
//    fclose(test_y);
//    fclose(test_order);
//
//    return 0;
//}
//
