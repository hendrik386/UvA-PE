#include "Bhtree.hpp"

Bhtree::Bhtree(const Octant& rootOctant) : rootOctant(rootOctant) {
}

Bhtree::~Bhtree() {
	// Check if each is == 0 (null)
	if(upNorthWest != nullptr) {
		delete upNorthWest;
	}

	if(upNorthEast != nullptr) {
		delete upNorthEast;
	}

	if(upSouthWest != nullptr) {
		delete upSouthWest;
	}

	if(upSouthEast != nullptr) {
		delete upSouthEast;
	}

	if(downNorthWest != nullptr) {
		delete downNorthWest;
	}

	if(downNorthEast != nullptr) {
		delete downNorthEast;
	}

	if(downSouthWest != nullptr) {
		delete downSouthWest;
	}

	if(downSouthEast != nullptr) {
		delete downSouthEast;
	}

	if(toDelete != nullptr) {
		delete toDelete;
	}

	//	if (!isExternal() && rootBody!= NULL && rootBody->velocity.x==0.0) delete rootBody;
	//	delete rootBody;
}

bool Bhtree::isExternal() const {
	return upNorthWest == nullptr && upNorthEast == nullptr && upSouthWest == nullptr && upSouthEast == nullptr &&
		downNorthWest == nullptr && downNorthEast == nullptr && downSouthWest == nullptr && downSouthEast == nullptr;
}

void Bhtree::insert(Body* body) {
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
		if(toDelete != nullptr) {
			delete toDelete;
		}

		toDelete = updatedBody;
		rootBody = updatedBody;
		updatedBody = body;
	} else {
		updatedBody = rootBody;
	}

	if(rootOctant.isInU(updatedBody->position)) {
		if(rootOctant.isInN(updatedBody->position)) {
			if(rootOctant.isInE(updatedBody->position)) {
				if(upNorthEast == nullptr) {
					upNorthEast = new Bhtree(rootOctant.centerUpNorthEast());
				}
				upNorthEast->insert(updatedBody);
			} else {
				if(upNorthWest == nullptr) {
					upNorthWest = new Bhtree(rootOctant.centerUpNorthWest());
				}
				upNorthWest->insert(updatedBody);
			}
		} else {
			if(rootOctant.isInE(updatedBody->position)) {
				if(upSouthEast == nullptr) {
					upSouthEast = new Bhtree(rootOctant.centerUpSouthEast());
				}
				upSouthEast->insert(updatedBody);
			} else {
				if(upSouthWest == nullptr) {
					upSouthWest = new Bhtree(rootOctant.centerUpSouthWest());
				}
				upSouthWest->insert(updatedBody);
			}
		}
	} else {
		if(rootOctant.isInN(updatedBody->position)) {
			if(rootOctant.isInE(updatedBody->position)) {
				if(downNorthEast == nullptr) {
					downNorthEast = new Bhtree(rootOctant.centerDownNorthEast());
				}
				downNorthEast->insert(updatedBody);
			} else {
				if(downNorthWest == nullptr) {
					downNorthWest = new Bhtree(rootOctant.centerDownNorthWest());
				}
				downNorthWest->insert(updatedBody);
			}
		} else {
			if(rootOctant.isInE(updatedBody->position)) {
				if(downSouthEast == nullptr) {
					downSouthEast = new Bhtree(rootOctant.centerDownSouthEast());
				}
				downSouthEast->insert(updatedBody);
			} else {
				if(downSouthWest == nullptr) {
					downSouthWest = new Bhtree(rootOctant.centerDownSouthWest());
				}
				downSouthWest->insert(updatedBody);
			}
		}
	}

	// if (rootOctant.containsUpNorthWest(updatedBody->position))
	// {
	// 	if (upNorthWest == nullptr) { upNorthWest = new Bhtree(rootOctant.centerUpNorthWest()); }
	// 	upNorthWest->insert(updatedBody);
	// }
	// else if(rootOctant.containsUpNorthEast(updatedBody->position))
	// {
	// 	if (upNorthEast == nullptr) { upNorthEast = new Bhtree(rootOctant.centerUpNorthEast()); }
	// 	upNorthEast->insert(updatedBody);
	// }
	// else if (rootOctant.containsUpSouthWest(updatedBody->position))
	// {
	// 	if (upSouthWest == nullptr) { upSouthWest = new Bhtree(rootOctant.centerUpSouthWest()); }
	// 	upSouthWest->insert(updatedBody);
	// }
	// else if (rootOctant.containsUpSouthEast(updatedBody->position))
	// {
	// 	if (upSouthEast == nullptr) { upSouthEast = new Bhtree(rootOctant.centerUpSouthEast()); }
	// 	upSouthEast->insert(updatedBody);
	// }
	// else if (rootOctant.containsDownNorthWest(updatedBody->position))
	// {
	// 	if (downNorthWest == nullptr) { downNorthWest = new Bhtree(rootOctant.centerDownNorthWest()); }
	// 	downNorthWest->insert(updatedBody);
	// }
	// else if (rootOctant.containsDownNorthEast(updatedBody->position))
	// {
	// 	if (downNorthEast == nullptr) { downNorthEast = new Bhtree(rootOctant.centerDownNorthEast()); }
	// 	downNorthEast->insert(updatedBody);
	// }
	// else if (rootOctant.containsDownSouthWest(updatedBody->position))
	// {
	// 	if (downSouthWest == nullptr) { downSouthWest = new Bhtree(rootOctant.centerDownSouthWest()); }
	// 	downSouthWest->insert(updatedBody);
	// }
	// else
	// {
	// 	if (downSouthEast == nullptr) { downSouthEast = new Bhtree(rootOctant.centerDownSouthEast()); }
	// 	downSouthEast->insert(updatedBody);
	// }

	if(isExtern) {
		insert(body);
	}
}

void Bhtree::interact(Body* body) {
	if(isExternal()) {
		if(rootBody != body) {
			Body::singleInteraction(*body, *rootBody, true, true, false, true, false);
		}
	} else if(rootOctant.getLength() / Vector3D(rootBody->position.x - body->position.x, rootBody->position.y - body->position.y, rootBody->position.z - body->position.z).magnitude() < MAX_DISTANCE) {
		Body::singleInteraction(*body, *rootBody, false, true, false, true, false);
	} else {
		if(upNorthWest != nullptr) {
			upNorthWest->interact(body);
		}
		if(upNorthEast != nullptr) {
			upNorthEast->interact(body);
		}
		if(upSouthWest != nullptr) {
			upSouthWest->interact(body);
		}
		if(upSouthEast != nullptr) {
			upSouthEast->interact(body);
		}
		if(downNorthWest != nullptr) {
			downNorthWest->interact(body);
		}
		if(downNorthEast != nullptr) {
			downNorthEast->interact(body);
		}
		if(downSouthWest != nullptr) {
			downSouthWest->interact(body);
		}
		if(downSouthEast != nullptr) {
			downSouthEast->interact(body);
		}
	}
}
