// Grid3D is the class template of an object containing the 3D grid and the function
// to perform raytracing
//
//  Grid.h
//  ttcr
//
//  Created by Bernard Giroux on 2013-01-10.
//  Copyright (c) 2013 Bernard Giroux. All rights reserved.
//

/*
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef ttcr_Grid3D_h
#define ttcr_Grid3D_h

#include <fstream>

#include "ttcr_t.h"

namespace ttcr {
    
    template<typename T1, typename T2>
    class Grid3D {
    public:
        
        virtual ~Grid3D() {}
        
        virtual void raytrace(const std::vector<sxyz<T1>>& Tx,
                             const std::vector<T1>& t0,
                             const std::vector<sxyz<T1>>& Rx,
                             std::vector<T1>& traveltimes,
                             const size_t threadNo=0) const {}
        
        virtual void raytrace(const std::vector<sxyz<T1>>& Tx,
                             const std::vector<T1>& t0,
                             const std::vector<const std::vector<sxyz<T1>>*>& Rx,
                             std::vector<std::vector<T1>*>& traveltimes,
                             const size_t=0) const {}
        
        virtual void raytrace(const std::vector<sxyz<T1>>& Tx,
                             const std::vector<T1>& t0,
                             const std::vector<sxyz<T1>>& Rx,
                             std::vector<T1>& traveltimes,
                             std::vector<std::vector<sxyz<T1>>>& r_data,
                             const size_t threadNo=0) const {}
        
        virtual void raytrace(const std::vector<sxyz<T1>>& Tx,
                             const std::vector<T1>& t0,
                             const std::vector<const std::vector<sxyz<T1>>*>& Rx,
                             std::vector<std::vector<T1>*>& traveltimes,
                             std::vector<std::vector<std::vector<sxyz<T1>>>*>& r_data,
                             const size_t=0) const {}
        
        virtual void raytrace(const std::vector<sxyz<T1>>& Tx,
                             const std::vector<T1>& t0,
                             const std::vector<sxyz<T1>>& Rx,
                             std::vector<T1>& traveltimes,
                             std::vector<std::vector<sxyz<T1>>>& r_data,
                             T1& v0,
                             const size_t threadNo=0) const {}
        
        virtual void raytrace(const std::vector<sxyz<T1>>& Tx,
                             const std::vector<T1>& t0,
                             const std::vector<sxyz<T1>>& Rx,
                             std::vector<T1>& traveltimes,
                             std::vector<std::vector<sxyz<T1>>>& r_data,
                             T1& v0,
                             std::vector<std::vector<sijv<T1>>>& m_data,
                             const size_t threadNo=0) const {}

        virtual void raytrace(const std::vector<sxyz<T1>>& Tx,
                             const std::vector<T1>& t0,
                             const std::vector<sxyz<T1>>& Rx,
                             std::vector<T1>& traveltimes,
                             std::vector<std::vector<siv<T1>>>& l_data,
                             const size_t threadNo=0) const {}

        virtual void raytrace(const std::vector<sxyz<T1>>& Tx,
                             const std::vector<T1>& t0,
                             const std::vector<sxyz<T1>>& Rx,
                             std::vector<T1>& traveltimes,
                             std::vector<std::vector<sxyz<T1>>>& r_data,
                             std::vector<std::vector<siv<T1>>>& l_data,
                             const size_t threadNo=0) const {}

        virtual void setSlowness(const std::vector<T1>& s) {}
        virtual void setChi(const std::vector<T1>& x) {}
        virtual void setPsi(const std::vector<T1>& x) {}
        
        virtual void setSourceRadius(const double) {}
        
        virtual size_t getNumberOfNodes() const { return 1; }
        virtual size_t getNumberOfCells() const { return 1; }
        
        virtual void saveTT(const std::string &, const int, const size_t nt=0,
                            const int format=1) const {}
        
        virtual const T1 getXmin() const { return 1; }
        virtual const T1 getXmax() const { return 1; }
        virtual const T1 getYmin() const { return 1; }
        virtual const T1 getYmax() const { return 1; }
        virtual const T1 getZmin() const { return 1; }
        virtual const T1 getZmax() const { return 1; }
        
        virtual const int get_niter() const { return 1; }
        virtual const int get_niterw() const { return 1; }
        
        virtual const size_t getNthreads() const { return 1; }
        
        virtual void dump_secondary(std::ofstream&) const {};
        
#ifdef VTK
        virtual void saveModelVTU(const std::string &, const bool saveSlowness=true,
                                  const bool savePhysicalEntity=false) const {}
        virtual void saveModelVTR(const std::string &, const double*,
                                  const bool saveSlowness=true,
                                  const int verbose=0) const {}
#endif
    };
    
}

#endif
