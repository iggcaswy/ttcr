//
//  Node3Di.h
//  ttcr
//
//  Created by Bernard Giroux on 2014-04-21.
//  Copyright (c) 2014 Bernard Giroux. All rights reserved.
//

#ifndef ttcr_Node3Di_h
#define ttcr_Node3Di_h

#include <cmath>
#include <limits>
#include <vector>

#include "Node.h"

template<typename T1, typename T2>
class Node3Di : public Node<T1> {
public:
    Node3Di(const size_t nt) :
	nThreads(nt),
    tt(new T1[nt]),
	x(0.0f), y(0.0f), z(0.0f),
    gridIndex(std::numeric_limits<T2>::max()),
    owners(std::vector<T2>(0)),
    slowness(0),
    primary(0)
    {
		for ( size_t n=0; n<nt; ++n ) {
			tt[n] = std::numeric_limits<T1>::max();
		}
	}
	
    Node3Di(const T1 t, const T1 xx, const T1 yy, const T1 zz, const size_t nt,
			  const size_t i) :
	nThreads(nt),
    tt(new T1[nt]),
    x(xx), y(yy), z(zz),
    gridIndex(std::numeric_limits<T2>::max()),
    owners(std::vector<T2>(0)),
    slowness(0),
    primary(0)
    {
		for ( size_t n=0; n<nt; ++n ) {
			tt[n] = std::numeric_limits<T1>::max();
		}
        tt[i]=t;
    }
	
    Node3Di(const T1 t, const sxyz<T1>& s, const size_t nt,
			  const size_t i) :
	nThreads(nt),
    tt(new T1[nt]),
    x(s.x), y(s.y), z(s.z),
    gridIndex(std::numeric_limits<T2>::max()),
    owners(std::vector<T2>(0)),
    slowness(0),
    primary(0)
    {
		for ( size_t n=0; n<nt; ++n ) {
			tt[n] = std::numeric_limits<T1>::max();
		}
        tt[i]=t;
    }
	
	Node3Di(const Node3Di<T1,T2>& node) :
	nThreads(node.nThreads),
    tt(0),
	x(node.x), y(node.y), z(node.z),
    gridIndex(node.gridIndex),
    owners(node.owners),
    slowness(node.slowness),
    primary(node.primary)
    {
		tt = new T1[nThreads];
		
		for ( size_t n=0; n<nThreads; ++n ) {
			tt[n] = node.tt[n];
		}
	}
	
	~Node3Di() {
		delete [] tt;
	}
	
    // Sets the vectors to the right size of threads and initialize it
    void reinit(const size_t n) {
        tt[n] = std::numeric_limits<T1>::max();
    }
    
    T1 getTT(const size_t n) const { return tt[n]; }
    void setTT(const T1 t, const size_t n ) { tt[n] = t; }
	
	void setXYZindex(const T1 xx, const T1 yy, const T1 zz, const T2 index) {
		x=xx; y=yy; z=zz; gridIndex = index;  }
	void setXYZindex(const sxyz<T1>& s, const T2 index) {
		x=s.x; y=s.y; z=s.z; gridIndex = index;  }
	
    T1 getX() const { return x; }
    void setX(const T1 xx) { x = xx; }
    
    T1 getY() const { return y; }
    void setY(const T1 yy) { y = yy; }
	
    T1 getZ() const { return z; }
    void setZ(const T1 zz) { z = zz; }
    
    T2 getGridIndex() const { return gridIndex; }
    void setGridIndex(const T2 index) { gridIndex = index; }
    
    int getPrimary() const { return primary; };
    void setPrimary( const int o ) { primary = o; }
	
    T1 getNodeSlowness() const { return slowness; }
    void setNodeSlowness(const T1 s) { slowness = s; }
	
    void pushOwner(const T2 o) { owners.push_back(o); }
    const std::vector<T2>& getOwners() const { return owners; }
    
    T1 getDistance( const Node3Di<T1,T2>& node ) const {
        return sqrt( (x-node.x)*(x-node.x) + (y-node.y)*(y-node.y) + (z-node.z)*(z-node.z) );
    }
    
    T1 getDistance( const sxyz<T1>& node ) const {
        return sqrt( (x-node.x)*(x-node.x) + (y-node.y)*(y-node.y) + (z-node.z)*(z-node.z) );
    }
    
	// operator to test if same location
	bool operator==( const sxyz<T1>& node ) const {
		return fabs(x-node.x)<small && fabs(y-node.y)<small && fabs(z-node.z)<small;
	}
	
    size_t getSize() const {
        return 2*sizeof(size_t) + nThreads*sizeof(T1) + 4*sizeof(T1) +
        (1+2*nThreads)*sizeof(T2) + owners.size() * sizeof(T2);
    }
    
	int getDimension() const { return 3; }
	
private:
	size_t nThreads;
    T1 *tt;                         // travel time for the multiple source points
    T1 x;                           // x coordinate [km]
    T1 y;							// y coordinate [km]
    T1 z;                           // z coordinate [km]
    T2 gridIndex;                   // index of this node in the list of the grid
    std::vector<T2> owners;         // indices of cells touching the node
    T1 slowness;					// slowness at the node [s/km], only used by Grid3Dinterp
    int primary;					// indicate the order of the node: 5= primary,
	//  (25:48)= secondary on edges,
	//  (50:71)= secondary on faces, only used by Grid3Dinterp
    
};


#endif