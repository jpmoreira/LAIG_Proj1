//
//  LG_Essentials.h
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 07/10/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#ifndef LAIG_Proj1_LG_Essentials_h
#define LAIG_Proj1_LG_Essentials_h

#ifdef _WIN32
#include <Windows.h>
#endif


#include <map>
#include <string>
#include <vector>
#include <tinyxml.h>
#include <math.h>



#define LG_LightValue_Not_Set LG_INVALID_DOUBLE
#define LG_LightValue_f_Not_Set LG_INVALID_FLOAT

#define LG_LightList_InitialValue {LG_LightValue_Not_Set,LG_LightValue_Not_Set,LG_LightValue_Not_Set,LG_LightValue_Not_Set}

#define LG_Matrix_InitialValue {LG_LightList_InitialValue,LG_LightList_InitialValue,LG_LightList_InitialValue,LG_LightList_InitialValue}


//#define str_eq( value1 , value2 ) (strcmp(value1,value2)==0)

#define LG_Point3D_Length 3
#define LG_Point2D_Length 2
#define LG_LightArray_Lenght 4
#define LG_Matrix_Dimention 4
#define X_ 0
#define Y_ 1
#define Z_ 2

using  std::vector;
using std::string;
using std::map;

class LG_Node;

typedef map<string , LG_Node *> LG_Node_Map;
typedef vector<string> LG_ID_Vector;
typedef std::pair<string , LG_Node *> LG_Node_Map_Pair;



typedef double LG_Point3D[3];
typedef float LG_Point3D_F[3];
typedef double LG_Point2D[2];
typedef double LG_LightArray[4];
typedef double LG_Matrix[4][4];
typedef float LG_LightArray_f[4];


inline bool str_eq(const string & str1,const string & str2){

    return strcmp(str1.c_str(), str2.c_str())==0;

}

inline bool str_eq(const string * str1,const string * str2){
    
    return strcmp(str1->c_str(), str2->c_str())==0;
    
}


inline bool str_eq(const char * str1,const char * str2){
    
    return strcmp(str1, str2)==0;
    
}

inline bool str_eq(const string & str1,const char * str2){
    
    return strcmp(str1.c_str(), str2)==0;
    
}
inline bool str_eq(const string * str1,const char * str2){
    
    return strcmp(str1->c_str(), str2)==0;
    
}

inline bool str_eq(const char * str1,const string & str2){
    
    return strcmp(str2.c_str(), str1)==0;
    
}

inline bool str_eq(const char * str1,const string * str2){
    
    return strcmp(str2->c_str(), str1)==0;
    
}




#pragma mark - Geometry stuff




inline vector<double> vectorBetweenPoints(LG_Point3D start,LG_Point3D end){

    vector<double> v(3);
    
    v[0]=end[0]-start[0];
    v[1]=end[1]-start[1];
    v[2]=end[2]-start[2];
    
    return v;
}

/**
 
 
 A method thar returns the lenght of a vector
 
 */


inline double vectorLenght(LG_Point3D vect){

    return sqrt(vect[X_]*vect[X_]+vect[Y_]*vect[Y_]+vect[Z_]*vect[Z_]);

}

/**
 
 
 A method thar returns the lenght of a vector
 
 */

inline double vectorLenght(const vector<double>& vect){

    return sqrt(vect[X_]*vect[X_]+vect[Y_]*vect[Y_]+vect[Z_]*vect[Z_]);

}

/**
 
 A method that normalizes a vector
 
 
 */
inline void normalize(vector<double> & vector){

    
    
    double vectDimention=vectorLenght(vector);
    
    
    if(vectDimention!=0){//only if dimention is not zero
        vector[X_]/=vectDimention;
        vector[Y_]/=vectDimention;
        vector[Z_]/=vectDimention;
    }
    
    
}


/**
 
 A method that normalizes a vector
 
 
 */

inline void normalize(LG_Point3D vector){
    
    
    
    double vectDimention=vectorLenght(vector);
    
    
    vector[X_]/=vectDimention;
    vector[Y_]/=vectDimention;
    vector[Z_]/=vectDimention;
    
}


/**
 
 
 A method that returns the dot product between two vectors
 
 */
inline double dotProduct(LG_Point3D vec1,LG_Point3D vec2){

    
    return vec1[X_]*vec2[X_]+vec1[Y_]*vec2[Y_]+vec1[Z_]*vec2[Z_];
    
}

/**
 
 
 A method that returns the dot product between two vectors
 
 */
inline double dotProduct(vector<double> vec1,vector<double> vec2){
    
    
    return vec1[X_]*vec2[X_]+vec1[Y_]*vec2[Y_]+vec1[Z_]*vec2[Z_];
    
}


/**
 
 
 A method that returns the angle between two vectors
 
 
 */

inline double angleBetween(LG_Point3D vec1,LG_Point3D vec2){

    
    
    normalize(vec1);
    normalize(vec2);
    
    
    double cos_Alpha=dotProduct(vec1,vec2);
    
    return acos(cos_Alpha);
    
}

/**
 
 
 A method that returns the angle between two vectors
 
 
 */

inline double angleBetween(vector<double> vec1,vector<double> vec2){
    
    
    
    normalize(vec1);
    normalize(vec2);
    
    
    double cos_Alpha=dotProduct(vec1,vec2);
    
    return acos(cos_Alpha);
    
}


/**
 
 A method that returns a vector representing the cross product between two other vectors
 
 
 @return The cross product between two vectors
 
 */
inline vector<double> crossProduct (vector<double> vec1,vector<double> vec2){

    
    vector<double> crossProd(3);
    
    
    crossProd[X_]=vec1[Y_]*vec2[Z_]-vec1[Z_]*vec2[Y_];
    crossProd[Y_]=vec1[Z_]*vec2[X_]-vec1[X_]*vec2[Z_];
    crossProd[Z_]=vec1[X_]*vec2[Y_]-vec1[Y_]*vec2[X_];
    
    
    return crossProd;
    

}


/**
 
 A method that returns a vector representing the cross product between two other vectors
 
 
 @return The cross product between two vectors
 
 */
inline vector<double> crossProduct (LG_Point3D vec1,LG_Point3D vec2){
    
    
    vector<double> crossProd(3);
    
    
    crossProd[X_]=vec1[Y_]*vec2[Z_]-vec1[Z_]*vec2[Y_];
    crossProd[Y_]=vec1[Z_]*vec2[X_]-vec1[X_]*vec2[Z_];
    crossProd[Z_]=vec1[X_]*vec2[Y_]-vec1[Y_]*vec2[X_];
    
    
    return crossProd;
    
    
}





#endif
