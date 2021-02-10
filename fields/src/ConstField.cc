/* Copyright 2008-2010, Technische Universitaet Muenchen,
   Authors: Christian Hoeppner & Sebastian Neubert & Johannes Rauch

   This file is part of GENFIT.

   GENFIT is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as published
   by the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   GENFIT is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with GENFIT.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "ConstField.h"
#include <iostream>
#include <TGeoManager.h>
#include <typeinfo>
#include <cstring>
#include <string>
//lengths
static const double mm  = 1.;
static const double cm  = 10.*mm;
static const double m   = 1000.*mm;

namespace genfit {

/*
void ConstField::get(const double&, const double&, const double&, double& Bx, double& By, double& Bz) const {
  Bx = field_.X();
  By = field_.Y();
  Bz = field_.Z();
}
*/


TVector3 ConstField::get(const TVector3& pos) const {
     
    TVector3 tmp(-150,0,0);// kGauss
    std::string hold = "i";
    std::string name2(1, gGeoManager->FindNode(pos[0],pos[1],pos[2])->GetName()[0]);
    name2.c_str();
   
    if (name2.c_str()==hold) tmp.SetX(-150);//kGauss
    return tmp;
    // return field_; 
}
/*
void ConstField::get(const double& posX, const double& posY, const double& posZ, double& Bx, double& By, double& Bz) const {
  TVector3 tmp(10,0,0); //kGauss
  Bx = 10;
  By = 0; 
  Bz = 0;
}*/


void ConstField::get(const double& posX, const double& posY, const double& posZ, double& Bx, double& By, double& Bz) const {

//non-uniform
  TVector3 tmp(-150,0,0);//kGauss
  Bx=0.; By=0.; Bz=0.;
  double iron_module_z[33] = {7, 14.2, 21, 49.7, 60.7, 71.7,
                              95.9, 102.9, 113.7, 121, 145.2, 151.9,
                              163.1, 170, 193.8, 200.8, 207.8, 214.8,
                              243.7, 250.6, 257.8, 286.5, 293.7, 300.4,
                              307.4, 331.3, 338.3, 345.4, 352.1, 376,
                              383.3, 390.2, 397.1};

  std::string hold = "i";
//  std::string name2;
  double x = posX - 60;
  double y = posY;
  double z = posZ - (275.-200)*cm;
  //std::cout << "(" << posX << ", " << posY << ", " << posZ << ")" 
  //	    << "\t(" << x << ", " << y << ", " << z << ")" << std::endl;
  if(gGeoManager->FindNode(posX,posY,posZ)){
	std::string name3(1, gGeoManager->FindNode(posX,posY,posZ)->GetName()[0]);
        //name2 = name3;
        if (name3.c_str()==hold){ //if node==iron
//	    if(x > -2000 && x < 2000 && y > -1500 && y < 1500 && z > 0 && z < 4000){
//	      for (double i : iron_module_z) {
//	        if (z > i * 10 - 3.0 * 10/2 && z < i * 10 + 3.0 * 10/2) {
	          Bx = tmp.X();

//	        }
//	      }
	    //if in detector vol
//    	    if(y > -.5*m && y < 0.5*m){ Bx = -tmp.X(); 
		    //std::cout << "(" << Bx << ", 0, 0)" << std::endl; 
//		    } // -tmp.X 
//	    else{ Bx = tmp.X(); 
	    	    //std::cout << "(" << Bx << ", 0, 0)" << std::endl; 
//		    } // +tmp.X
//	  } //if in detector vol
  //std::cout << "(" << Bx << ", " << By << ", " << Bz << ")" << std::endl;
  //std::cout << "node = " << name3.c_str() << std::endl;
       } //if node==iron
//    std::cout << "(" << Bx << ", " << By << ", " << Bz << ")" << std::endl;
  } //find node

} // End of non-linear field function


} // End of namespace genfit 
