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


//Global variables, lengths, dimensions, positions 
static const double mm  = 1.;
static const double cm  = 10.*mm;
static const double m   = 1000.*mm;

const static std::size_t xbins_ = 251;
const static std::size_t ybins_ = 201;

double bx_[xbins_][ybins_]{}, by_[xbins_][ybins_]{}, bz_[xbins_][ybins_]{};

static const double xmin_ = (-2. * m); static const double xmax_ = (2. * m);
static const double ymin_ = (-1.5 * m); static const double ymax_ = (1.5 * m);
static const double zmin_ = (0. * m);   static const double zmax_ = (4. * m);

double iron_module_z[33] = {7, 14.2, 21, 49.7, 60.7, 71.7,
                            95.9, 102.9, 113.7, 121, 145.2, 151.9,
                            163.1, 170, 193.8, 200.8, 207.8, 214.8,
                            243.7, 250.6, 257.8, 286.5, 293.7, 300.4,
                            307.4, 331.3, 338.3, 345.4, 352.1, 376,
                            383.3, 390.2, 397.1};
                            

static const double tesla = (1.e-6*1./1.)*(1.e+9*1.)/(1000.*1000.);                           

const std::string magfield_path = "/home/chuggles/wagasci/wagasci-babymind-monte-carlo/data/geometry/magfield.table";

namespace genfit {

/*
 ///> Will need to modify and place code to read B2Field here
ConstField::B2MagneticField(const std::string& magfield_path){

  std::cout << "\n\nReading B2MagneticField\n\n" << std::endl;  
  ///> reading magfield table
  double ignore;
  std::ifstream data(&magfield_path);
  for (std::size_t i=0; i<xbins_; i++){
    for (std::size_t j=0; j<ybins_; j++){
      data >> ignore >> ignore >> ignore >> bx_[i][j] >> by_[i][j] >> bz_[i][j];   
    }
  } 
}
*/
//////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////LINEAR/////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

TVector3 ConstField::get(const TVector3& pos) const {
     
  TVector3 tmp(0,0,0);// kGauss

  double x = pos.X() + 60*cm;
  double y = pos.Y();
  double z = pos.Z() + 75.*cm;
  
  if (x > xmin_ && x < xmax_ && y > ymin_ && y < ymax_ && z > zmin_ && z < zmax_) {

      tmp.SetX(0.0);
      tmp.SetY(0.0);
      tmp.SetZ(-10);
      
  }
     //std::cout << "Field : (" << tmp.X() << ", " << tmp.Y() << ", " << tmp.Z() << ") \t" << 
     //"Position : (" << x << ", " << y << ", " << z << ")" << std::endl;
     return tmp;
    // return field_; 
}


void ConstField::get(const double& posX, const double& posY, const double& posZ, double& Bx, double& By, double& Bz) const {
  
  double x = posX + 60.*cm;
  double y = posY;
  double z = posZ + 75.*cm;

  if (x > xmin_ && x < xmax_ && y > ymin_ && y < ymax_ && z > zmin_ && z < zmax_) {

      Bx = 0;
      By = 0;
      Bz = -10;
      
  }

//std::cout << "Field : (" << tmp.X() << ", " << tmp.Y() << ", " << tmp.Z() << ") \t" << 
//     "Position : (" << x << ", " << y << ", " << z << ")" << std::endl;

}

//////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////NON-LINEAR/////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
/*
TVector3 ConstField::get(const TVector3& pos) const {
     
  TVector3 tmp(0,0,0);//kGauss

  double x = pos.X() - 60.*cm;
  double y = pos.Y();
  double z = pos.Z() - (275.-200.)*cm;
  if (x > xmin_ && x < xmax_ && y > ymin_ && y < ymax_ && z > zmin_ && z < zmax_) {
    for (double i : iron_module_z) {
      if (z > i * cm - 3.0 * cm / 2 && z < i * cm + 3.0 * cm / 2) {

        tmp.SetX(15); 
        tmp.SetY(0.0); 
        tmp.SetZ(0.0); 
        
        break;
      }
    }
  }
  return tmp;
    // return field_; 
}

void ConstField::get(const double& posX, const double& posY, const double& posZ, double& Bx, double& By, double& Bz) const {

//non-uniform
  TVector3 tmp(0,0,0);//kGauss
  Bx=0.; By=0.; Bz=0.;
  double iron_module_z[33] = {7, 14.2, 21, 49.7, 60.7, 71.7,
                              95.9, 102.9, 113.7, 121, 145.2, 151.9,
                              163.1, 170, 193.8, 200.8, 207.8, 214.8,
                              243.7, 250.6, 257.8, 286.5, 293.7, 300.4,
                              307.4, 331.3, 338.3, 345.4, 352.1, 376,
                              383.3, 390.2, 397.1};

  double x = posX - 60.*cm;
  double y = posY;
  double z = posZ - (275.-200.)*cm;
  if (x > xmin_ && x < xmax_ && y > ymin_ && y < ymax_ && z > zmin_ && z < zmax_) {
    for (double i : iron_module_z) {
      if (z > i * cm - 3.0 * cm / 2 && z < i * cm + 3.0 * cm / 2) {

        tmp.SetX(15);  Bx = 15;
        tmp.SetY(0.0); By = 0;
        tmp.SetZ(0.0); Bz = 0;
        
        break;
      }
    }
  }

} // End of non-linear field function

*/
/*
void ConstField::get(const double& posX, const double& posY, const double& posZ, double& Bx, double& By, double& Bz) const {

//non-uniform
  TVector3 tmp(15,0,0);//kGauss
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
*/

//////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////B2MagneticField///////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
/*
TVector3 ConstField::get(const TVector3& pos) const {
     
  TVector3 magnetic_field(0,0,0);

  double x = pos.X() + 60*cm;
  double y = pos.Y();
  double z = pos.Z() + 75.*cm;
  

  if (x > xmin_ && x < xmax_ && y > ymin_ && y < ymax_ && z > zmin_ && z < zmax_) {

    auto xint = (int) ((double) (x - xmin_) / (xmax_ - xmin_) * xbins_);
    auto yint = (int) ((double) (y - ymin_) / (ymax_ - ymin_) * ybins_);

    for (double i : iron_module_z) {
      if (z > i * cm - 3.0 * cm / 2 && z < i * cm + 3.0 * cm / 2) {
        // The minus sign is there to correct for the fact that the magnetic field simulation is reversed with
        // respect to the actual detector
        magnetic_field.SetX(-bx_[xint][yint] * tesla * 10.); 
        magnetic_field.SetY(by_[xint][yint] * tesla * 10.);
        magnetic_field.SetZ(bz_[xint][yint] * tesla * 10.);
        break;
      }
    }
  }
  std::cout << "B2MagneticField: (" << magnetic_field.X() << ", " << magnetic_field.Y() << ", " << magnetic_field.Z() << ")" << std::endl;
  return magnetic_field;
}

void ConstField::get(const double& posX, const double& posY, const double& posZ, double& Bx, double& By, double& Bz) const {
  TVector3 magnetic_field(0,0,0); // 10 kGauss = 1 Tesla  
  
  double x = posX + 60.*cm;
  double y = posY;
  double z = posZ + 75.*cm;

  if (x > xmin_ && x < xmax_ && y > ymin_ && y < ymax_ && z > zmin_ && z < zmax_) {

    auto xint = (int) ((double) (x - xmin_) / (xmax_ - xmin_) * xbins_);
    auto yint = (int) ((double) (y - ymin_) / (ymax_ - ymin_) * ybins_);

    for (double i : iron_module_z) {
      if (z > i * cm - 3.0 * cm / 2 && z < i * cm + 3.0 * cm / 2) {
        // The minus sign is there to correct for the fact that the magnetic field simulation is reversed with
        // respect to the actual detector
        magnetic_field.SetX(-bx_[xint][yint] * tesla * 10.); Bx = (-bx_[xint][yint] * tesla * 10.);
        magnetic_field.SetY(by_[xint][yint] * tesla * 10.);  By = (by_[xint][yint] * tesla * 10.);
        magnetic_field.SetZ(bz_[xint][yint] * tesla * 10.);  Bz = (bz_[xint][yint] * tesla * 10.);
        break;
      }
    }
  }


}
*/

//////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////RETURN////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
/*
TVector3 ConstField::get(const TVector3& pos) const {
     
  TVector3 tmp(0,0,0);//kGauss

  double x = pos.X() + 60.*cm;
  double y = pos.Y();
  double z = pos.Z() + (275.-200.)*cm;
//  std::cout << "X=" << pos.X() << ", Y=" << pos.Y() << ", Z=" << pos.Z() << std::endl;
  if (x > xmin_ && x < xmax_ && y > ymin_ && y < ymax_ && z > zmin_ && z < zmax_) {
    for (double i : iron_module_z) {
      if (z > i * cm - 3.0 * cm / 2 && z < i * cm + 3.0 * cm / 2) {
        if( y > -500 && y < 500) {
        tmp.SetX(0); 
        }
        else{ tmp.SetX(0);} //Not sure if +/- 
        
        break;
      }
    }
  }
  return tmp;
    // return field_; 
}

void ConstField::get(const double& posX, const double& posY, const double& posZ, double& Bx, double& By, double& Bz) const {

//non-uniform
  TVector3 tmp(0,0,0);//kGauss
  Bx=0.; By=0.; Bz=0.;
  double iron_module_z[33] = {7, 14.2, 21, 49.7, 60.7, 71.7,
                              95.9, 102.9, 113.7, 121, 145.2, 151.9,
                              163.1, 170, 193.8, 200.8, 207.8, 214.8,
                              243.7, 250.6, 257.8, 286.5, 293.7, 300.4,
                              307.4, 331.3, 338.3, 345.4, 352.1, 376,
                              383.3, 390.2, 397.1};

  double x = posX - 60.*cm;
  double y = posY;
  double z = posZ - (275.-200.)*cm;
  //std::cout << "X=" << posX << ", Y=" << posY << ", Z=" << posZ << std::endl;

  if (x > xmin_ && x < xmax_ && y > ymin_ && y < ymax_ && z > zmin_ && z < zmax_) {
    for (double i : iron_module_z) {
      if (z > i * cm - 3.0 * cm / 2 && z < i * cm + 3.0 * cm / 2) {

        if( y > -500 && y < 500) {
        tmp.SetX(0); Bx = 0;
        }
        else{ tmp.SetX(0); Bx = 0;} //Not sure if +/- 
        
        break;
      }
    }
  }

} // End of non-linear field function
*/

} // End of namespace genfit 
