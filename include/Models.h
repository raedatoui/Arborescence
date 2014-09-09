//
//  Models.h
//  Cellule
//
//  Created by Raed Atoui on 8/31/12.
//
//

#ifndef Cellule_Models_h
#define Cellule_Models_h

#endif
#pragma once

//#include <boost/lexical_cast.hpp>

using namespace std;


struct FigureData {
	
	int numClones;
	
	std::string file;
	std::string name;

    float scale;
	float width;
	float height;
    float x;
    float y;
    float coeff;
	int zIndex;
	float alpha;
	std::string blend;
    
    float speed;
	float angle;
	
	std::vector<FigureData> layers; //nested data
    
    FigureData()
    {
        alpha = 1.0f;
        blend = "";
        name = "";
        file = "";

        scale = 1.0f;
        speed = 0;
        x = 0;
        y = 0;
    }
	std::string toString()
	{
		std::string res = name;
//		res = name +
//			"\n\tx: " + boost::lexical_cast<std::string>(x) +
//			"\t\ty: " + boost::lexical_cast<std::string>(y) +
//			"\t\tw: " + boost::lexical_cast<std::string>(width) +
//			"\t\th: " + boost::lexical_cast<std::string>(height) +
//			"\t\talpha: " + boost::lexical_cast<std::string>(alpha) +
//            "\t\tcoeff: " + boost::lexical_cast<std::string>(coeff) +
//			"\t\tangle: " + boost::lexical_cast<std::string>(angle*0.0174532925) + "\n\n";
		
		return res;
	}
};