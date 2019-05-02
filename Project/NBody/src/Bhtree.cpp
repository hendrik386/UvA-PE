/*
 * Bhtree.cpp
 *
 *  Created on: Feb 3, 2016
 *      Author: peterwhidden
 */
#include "stdio.h"

#include "Octant.cpp"

class Bhtree
{
private:
	body *myBod;

	body *toDelete;
	
	Octant *octy;

	Bhtree *UNW;

	Bhtree *UNE;

	Bhtree *USW;

	Bhtree *USE;

	Bhtree *DNW;

	Bhtree *DNE;

	Bhtree *DSW;

	Bhtree *DSE;

public:
	Bhtree(Octant* __restrict__ o)
	{
		myBod = nullptr;
		toDelete = nullptr;
		octy = o;
		UNW = nullptr;
		UNE = nullptr;
		USW = nullptr;
		USE = nullptr;
		DNW = nullptr;
		DNE = nullptr;
		DSW = nullptr;
		DSE = nullptr;
	}

	~Bhtree()
	{
		// check if each is ==0 (null)
		if (UNW != nullptr) delete UNW; //UNW->~Bhtree();
		if (UNE != nullptr) delete UNE; //UNE->~Bhtree();
		if (USW != nullptr) delete USW; //USW->~Bhtree();
		if (USE != nullptr) delete USE; //USE->~Bhtree();
		if (DNW != nullptr) delete DNW; //DNW->~Bhtree();
		if (DNE != nullptr) delete DNE; //DNE->~Bhtree();
		if (DSW != nullptr) delete DSW; //DSW->~Bhtree();
		if (DSE != nullptr) delete DSE; //DSE->~Bhtree();
		if (toDelete!=nullptr) delete toDelete;
		delete octy; //octy->~Octant();
	//	if (!isExternal() && myBod!= NULL && myBod->velocity.x==0.0) delete myBod;
	//	delete myBod;
	}

	bool isExternal()
	{
		return UNW == nullptr && UNE == nullptr && USW == nullptr && USE == nullptr &&
			   DNW == nullptr && DNE == nullptr && DSW == nullptr && DSE == nullptr;
	}

	void insert(body* __restrict__ insertBod)
	{
		if (myBod == nullptr)
		{
			myBod = insertBod;
		} 
		else //if (!isExternal())
		{
			bool isExtern = isExternal();
			body *updatedBod;
			if (!isExtern)
			{
				updatedBod = new struct body;
				updatedBod->position.x = (insertBod->position.x * insertBod->mass +
								     myBod->position.x * myBod->mass) /
									(insertBod->mass + myBod->mass);
				updatedBod->position.y = (insertBod->position.y * insertBod->mass +
									 myBod->position.y * myBod->mass) /
								  	(insertBod->mass + myBod->mass);
				updatedBod->position.z = (insertBod->position.z * insertBod->mass +
									 myBod->position.z * myBod->mass) /
								  	(insertBod->mass + myBod->mass);

				updatedBod->mass = insertBod->mass+myBod->mass;

			//	delete myBod;
				if (toDelete!=NULL) delete toDelete;
				toDelete = updatedBod;
				myBod = updatedBod;
				updatedBod = insertBod;
			} 
			else {
				updatedBod = myBod;
			}

			if (octy->containsUNW(updatedBod->position))
			{
				if (UNW == nullptr) { UNW = new Bhtree(octy->mUNW()); }
				UNW->insert(updatedBod);
			} 
			else if(octy->containsUNE(updatedBod->position)) 
			{
				if (UNE == nullptr) { UNE = new Bhtree(octy->mUNE()); }
				UNE->insert(updatedBod);
			} 
			else if (octy->containsUSW(updatedBod->position))		
			{
				if (USW == nullptr) { USW = new Bhtree(octy->mUSW()); }
				USW->insert(updatedBod);
			} 
			else if (octy->containsUSE(updatedBod->position))				
			{
				if (USE == nullptr) { USE = new Bhtree(octy->mUSE()); }							
				USE->insert(updatedBod);
			} 
			else if (octy->containsDNW(updatedBod->position))						
			{
				if (DNW == nullptr) { DNW = new Bhtree(octy->mDNW()); }				
				DNW->insert(updatedBod);
			} 
			else if (octy->containsDNE(updatedBod->position))
			{
				if (DNE == nullptr) { DNE = new Bhtree(octy->mDNE()); }
				DNE->insert(updatedBod);
			} 
			else if (octy->containsDSW(updatedBod->position))
			{
				if (DSW == nullptr) { DSW = new Bhtree(octy->mDSW()); }
				DSW->insert(updatedBod);
			} 
			else 
			{
				if (DSE == nullptr) { DSE = new Bhtree(octy->mDSE()); }
				DSE->insert(updatedBod);
			}

			if (isExtern) {
				insert(insertBod);
			}
		}
	}

	double magnitude(vec3* __restrict__ v)
	{
		return sqrt(v->x*v->x+v->y*v->y+v->z*v->z);
	}

	double magnitude( double x, double y, double z)
	{
		return sqrt(x * x + y * y + z * z);
	}

	void singleInteract(body* __restrict__ target, body* __restrict__ other, bool singlePart)
	{
		vec3 posDiff;
		posDiff.x = (target->position.x - other->position.x) * TO_METERS;
		posDiff.y = (target->position.y - other->position.y) * TO_METERS;
		posDiff.z = (target->position.z - other->position.z) * TO_METERS;
		double dist = magnitude(&posDiff);
		double F = TIME_STEP * (G * target->mass * other->mass) / ((dist * dist + SOFTENING * SOFTENING) * dist);

		target->accel.x -= F * posDiff.x / target->mass;
		target->accel.y -= F * posDiff.y / target->mass;
		target->accel.z -= F * posDiff.z / target->mass;
		
		//Friction
	#if ENABLE_FRICTION
		if (singlePart)
		{
			double friction = 0.5/pow(2.0,FRICTION_FACTOR*(
					((dist+SOFTENING))/(TO_METERS)));
		//	cout << friction << "\n";
			if (friction>0.0001 && ENABLE_FRICTION)
			{
				target->accel.x += friction*(other->velocity.x-target->velocity.x)/2;
				target->accel.y += friction*(other->velocity.y-target->velocity.y)/2;
				target->accel.z += friction*(other->velocity.z-target->velocity.z)/2;
			}
		}
	#endif	
	}


	void interactInTree(body* bod) {
		if(isExternal()) {
			if(myBod != bod) {
				singleInteract(bod, myBod, true);
			}
		} else if(octy->getLength() /
			magnitude(
				myBod->position.x - bod->position.x,
				myBod->position.y - bod->position.y,
				myBod->position.z - bod->position.z
			) < MAX_DISTANCE) {
			singleInteract(bod, myBod, false);
		} else {
			if(UNW != NULL) {
				UNW->interactInTree(bod);
			}
			if(UNE != NULL) {
				UNE->interactInTree(bod);
			}
			if(USW != NULL) {
				USW->interactInTree(bod);
			}
			if(USE != NULL) {
				USE->interactInTree(bod);
			}
			if(DNW != NULL) {
				DNW->interactInTree(bod);
			}
			if(DNE != NULL) {
				DNE->interactInTree(bod);
			}
			if(DSW != NULL) {
				DSW->interactInTree(bod);
			}
			if(DSE != NULL) {
				DSE->interactInTree(bod);
			}
		}
	}

};



