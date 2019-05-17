#pragma once

/*
 * Bhtree.cpp
 *
 *  Created on: Feb 3, 2016
 *      Author: peterwhidden
 */
#include "stdio.h"

#include "Body.hpp"
#include "Octant.hpp"

class Bhtree {
		Body* rootBody;

		Body* toDelete;

		Octant* octy;

		Bhtree* UNW;

		Bhtree* UNE;

		Bhtree* USW;

		Bhtree* USE;

		Bhtree* DNW;

		Bhtree* DNE;

		Bhtree* DSW;

		Bhtree* DSE;

	public:
		Bhtree(Octant* __restrict__ o) {
			rootBody = nullptr;
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

		~Bhtree() {
			// check if each is == 0 (null)
			if(UNW != nullptr) {
				delete UNW;
			} //UNW->~Bhtree();

			if(UNE != nullptr) {
				delete UNE;
			} //UNE->~Bhtree();

			if(USW != nullptr) {
				delete USW;
			} //USW->~Bhtree();

			if(USE != nullptr) {
				delete USE;
			} //USE->~Bhtree();

			if(DNW != nullptr) {
				delete DNW;
			} //DNW->~Bhtree();

			if(DNE != nullptr) {
				delete DNE;
			} //DNE->~Bhtree();

			if(DSW != nullptr) {
				delete DSW;
			} //DSW->~Bhtree();

			if(DSE != nullptr) {
				delete DSE;
			} //DSE->~Bhtree();

			if(toDelete != nullptr) {
				delete toDelete;
			}

			delete octy; //octy->~Octant();
			//	if (!isExternal() && rootBody!= NULL && rootBody->velocity.x==0.0) delete rootBody;
			//	delete rootBody;
		}

		bool isExternal() const {
			return UNW == nullptr && UNE == nullptr && USW == nullptr && USE == nullptr &&
				DNW == nullptr && DNE == nullptr && DSW == nullptr && DSE == nullptr;
		}

		void insert(Body* __restrict__ body) {
			if(rootBody == nullptr) {
				rootBody = body;

				return;
			}

			bool isExtern = isExternal();
			Body* updatedBody;

			if(!isExtern) {
				updatedBody = new Body(
					Vector3D(
						(body->position.x * body->mass + rootBody->position.x * rootBody->mass) / (body->mass + rootBody->mass),
						(body->position.y * body->mass + rootBody->position.y * rootBody->mass) / (body->mass + rootBody->mass),
						(body->position.z * body->mass + rootBody->position.z * rootBody->mass) / (body->mass + rootBody->mass)
					),
					Vector3D(0.0, 0.0, 0.0),
					Vector3D(0.0, 0.0, 0.0),
					body->mass + rootBody->mass
				);

				//	delete rootBody;
				if(toDelete != NULL) {
					delete toDelete;
				}

				toDelete = updatedBody;
				rootBody = updatedBody;
				updatedBody = body;
			} else {
				updatedBody = rootBody;
			}

			if(octy->isInU(updatedBody->position)) {
				if(octy->isInN(updatedBody->position)) {
					if(octy->isInE(updatedBody->position)) {
						if(UNE == nullptr) {
							UNE = new Bhtree(octy->mUNE());
						}
						UNE->insert(updatedBody);
					} else {
						if(UNW == nullptr) {
							UNW = new Bhtree(octy->mUNW());
						}
						UNW->insert(updatedBody);
					}
				} else {
					if(octy->isInE(updatedBody->position)) {
						if(USE == nullptr) {
							USE = new Bhtree(octy->mUSE());
						}
						USE->insert(updatedBody);
					} else {
						if(USW == nullptr) {
							USW = new Bhtree(octy->mUSW());
						}
						USW->insert(updatedBody);
					}
				}
			} else {
				if(octy->isInN(updatedBody->position)) {
					if(octy->isInE(updatedBody->position)) {
						if(DNE == nullptr) {
							DNE = new Bhtree(octy->mDNE());
						}
						DNE->insert(updatedBody);
					} else {
						if(DNW == nullptr) {
							DNW = new Bhtree(octy->mDNW());
						}
						DNW->insert(updatedBody);
					}
				} else {
					if(octy->isInE(updatedBody->position)) {
						if(DSE == nullptr) {
							DSE = new Bhtree(octy->mDSE());
						}
						DSE->insert(updatedBody);
					} else {
						if(DSW == nullptr) {
							DSW = new Bhtree(octy->mDSW());
						}
						DSW->insert(updatedBody);
					}
				}
			}

			// if (octy->containsUNW(updatedBody->position))
			// {
			// 	if (UNW == nullptr) { UNW = new Bhtree(octy->mUNW()); }
			// 	UNW->insert(updatedBody);
			// }
			// else if(octy->containsUNE(updatedBody->position))
			// {
			// 	if (UNE == nullptr) { UNE = new Bhtree(octy->mUNE()); }
			// 	UNE->insert(updatedBody);
			// }
			// else if (octy->containsUSW(updatedBody->position))
			// {
			// 	if (USW == nullptr) { USW = new Bhtree(octy->mUSW()); }
			// 	USW->insert(updatedBody);
			// }
			// else if (octy->containsUSE(updatedBody->position))
			// {
			// 	if (USE == nullptr) { USE = new Bhtree(octy->mUSE()); }
			// 	USE->insert(updatedBody);
			// }
			// else if (octy->containsDNW(updatedBody->position))
			// {
			// 	if (DNW == nullptr) { DNW = new Bhtree(octy->mDNW()); }
			// 	DNW->insert(updatedBody);
			// }
			// else if (octy->containsDNE(updatedBody->position))
			// {
			// 	if (DNE == nullptr) { DNE = new Bhtree(octy->mDNE()); }
			// 	DNE->insert(updatedBody);
			// }
			// else if (octy->containsDSW(updatedBody->position))
			// {
			// 	if (DSW == nullptr) { DSW = new Bhtree(octy->mDSW()); }
			// 	DSW->insert(updatedBody);
			// }
			// else
			// {
			// 	if (DSE == nullptr) { DSE = new Bhtree(octy->mDSE()); }
			// 	DSE->insert(updatedBody);
			// }

			if(isExtern) {
				insert(body);
			}
		}

		void interact(Body* __restrict__ body) {
			if(isExternal()) {
				if(rootBody != body) {
					Body::singleInteraction(*body, *rootBody, true, true, false, true, false);
				}
			} else if(octy->getLength() / Vector3D(rootBody->position.x - body->position.x, rootBody->position.y - body->position.y, rootBody->position.z - body->position.z).magnitude() < MAX_DISTANCE) {
				Body::singleInteraction(*body, *rootBody, false, true, false, true, false);
			} else {
				if(UNW != NULL) {
					UNW->interact(body);
				}
				if(UNE != NULL) {
					UNE->interact(body);
				}
				if(USW != NULL) {
					USW->interact(body);
				}
				if(USE != NULL) {
					USE->interact(body);
				}
				if(DNW != NULL) {
					DNW->interact(body);
				}
				if(DNE != NULL) {
					DNE->interact(body);
				}
				if(DSW != NULL) {
					DSW->interact(body);
				}
				if(DSE != NULL) {
					DSE->interact(body);
				}
			}
		}
};



