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
     
    TVector3 tmp(0,0,15);// kGauss
    std::string hold = "i";
    std::string name2(1, gGeoManager->FindNode(pos[0],pos[1],pos[2])->GetName()[0]);
    name2.c_str();
    if (name2.c_str()==hold) tmp.SetZ(0);//kGauss
    return tmp;
    // return field_; 
}

void ConstField::get(const double& posX, const double& posY, const double& posZ, double& Bx, double& By, double& Bz) const {

//non-uniform
  TVector3 tmp(15,0,0);//kGauss
  Bx=0.;
  By=0.;
  Bz=0.;
  std::string hold = "i";
  std::string name2;
  double x = posX*cm - 60.*cm;
  double y = posY*cm;
  double z = posZ*cm - (275.-200)*cm;
	    
  if(gGeoManager->FindNode(posX,posY,posZ)){
	std::string name3(1, gGeoManager->FindNode(posX,posY,posZ)->GetName()[0]);
        name2 = name3;
        if (name2.c_str()==hold){ //if node==iron
	    if(x > -2000 && x < 2000 && y > -1500 && y < 1500 && z > 0 && z < 4000){
	    //if in detector vol
    	    if(y > -.5*m && y < 0.5*m){ Bx = -tmp.X(); } // -tmp.X 
	    else{ Bx = tmp.X(); } // +tmp.X
	  } //if in detector vol
       } //if node==iron
  } //find node

} // End of non-linear field function

} // End of namespace genfit 
