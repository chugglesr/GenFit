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

namespace genfit {
/*
void ConstField::get(const double&, const double&, const double&, double& Bx, double& By, double& Bz) const {
  Bx = field_.X();
  By = field_.Y();
  Bz = field_.Z();
}
*/

///
/*
void ConstField::get(const double& posX, const double& posY, const double& posZ, double& Bx, double& By, double& Bz) const {
    //non-uniform
    TVector3 tmp(0,0,15);//kGauss
    std::string hold = "i";
    std::string name2;
    gGeoManager->FindNode(posX,posY,posZ);
    if(gGeoManager->FindNode(posX,posY,posZ)){
        //gGeoManager->FindNode(posX,posY,posZ)->GetName()[0];
	std::string name3(1, gGeoManager->FindNode(posX,posY,posZ)->GetName()[0]);
        name2 = name3;
        name2.c_str();
	//std::cout << name2.c_str() << std::endl;
        if (name2.c_str()==hold){
            std::cout << "posX =" << posX <<"\t posY =" << posY
	              <<"\t posZ =" << posZ << std::endl; 
            Bx = tmp.X();
            By = tmp.Y();
            Bz = tmp.Z();
        }
        else { 
            Bx = 0;
            By = 0;
            Bz = 0;
        }
    }
    // Bx = field_.X(); 
    // By = field_.Y(); 
    // Bz = field_.Z(); 
}*/


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
  TVector3 tmp(0,0,-15);//kGauss

  double Zmin = -200;
  double Zmax = 200;

  double Ymin1 = -100;
  double Ymax1 = -50;

  double Ymin2 = -50;
  double Ymax2 = 50;

  double Ymin3 = 50;
  double Ymax3 = 100;

  double Xmin = 0;
  double Xmax = 410;

  double z_iron[33]={13.5, 20.5, 27.5, 56.5, 68.0, 78.0, 102.0, 109.0, 120.0, 127.0,
		     151.5, 158.5, 170.0, 177.0, 200.0, 207.0, 214.0, 221.0, 250.0,
		     257.0, 264.0, 293.0, 300.0, 307.0, 314.0, 338.0, 345.0, 352.0,
		     359.0, 383.0, 390.0, 397.0, 403.0};

  for(int i=0; i<33; i++)
    z_iron[i]=z_iron[i]-13.0;

  Bx=0;
  By=0;
  Bz=0;
  std::string hold = "i";
  std::string name2;

  if(gGeoManager->FindNode(posX,posY,posZ)){
	std::string name3(1, gGeoManager->FindNode(posX,posY,posZ)->GetName()[0]);
        name2 = name3;
        //name2.c_str();
        //std::cout << name2.c_str() << std::endl;
        if (name2.c_str()==hold){ 
	    double x = posX;
      	    double y = posY;
     	    double z = posZ;
     	    std::cout << x << " " << y << " " << z << std::endl;
	    if(x>Xmin&&x<Xmax&&y>Ymin1&&y<Ymax1&&z>Zmin&&z<Zmax){
		for(int i=0; i<33; i++){
		  if(x>z_iron[i]-3./2&&x<z_iron[i]+3./2){
		    Bx = 0;
		    By = 0;
		    Bz = -tmp.Z();
		    std::cout << "+" << std::endl;
		  }
		}
	      }

           if(x>Xmin&&x<Xmax&&y>Ymin2&&y<Ymax2&&z>Zmin&&z<Zmax){
		for(int i=0; i<33; i++){
		  if(x>z_iron[i]-3.0/2&&x<z_iron[i]+3.0/2){
		    Bx = 0;
		    By = 0;
		    Bz = tmp.Z();
		    		    std::cout << "-" << std::endl;
		  }
		}
	      }

           if(x>Xmin&&x<Xmax&&y>Ymin3&&y<Ymax3&&z>Zmin&&z<Zmax){
		for(int i=0; i<33; i++){
		  if(x>z_iron[i]-3.0/2&&x<z_iron[i]+3.0/2){
		    Bx = 0;
		    By = 0;
		    Bz = -tmp.Z();
		    		    std::cout << "+" << std::endl;
		  }
		}
	      }
	   else { 
             Bx = 0;
             By = 0;
             Bz = 0;
 	   }

        }


  }
  else { 
            Bx = 0;
            By = 0;
            Bz = 0;
  }
}
} // End of namespace genfit 
