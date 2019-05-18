#include "Bhtree.hpp"

Bhtree::Bhtree(const Octant& rootOctant) : rootOctant(rootOctant) {
}

Bhtree::~Bhtree() {
	if(deleteRootBody) {
		delete rootBody;
	}
}

bool Bhtree::isExternal() const {
	return upNorthWest == nullptr && upNorthEast == nullptr && upSouthWest == nullptr && upSouthEast == nullptr &&
		downNorthWest == nullptr && downNorthEast == nullptr && downSouthWest == nullptr && downSouthEast == nullptr;
}

void Bhtree::insert(Body& body) {
	if(rootBody == nullptr) {
		rootBody = &body;
		deleteRootBody = false;

		return;
	}

	bool isTreeExternal = isExternal();

	Body& updatedBody = isTreeExternal
		? *rootBody
		: body;

	if(!isTreeExternal) {
		rootBody = new Body(
			(body.position * body.mass + rootBody->position * rootBody->mass) / (body.mass + rootBody->mass),
			Vector3D { 0.0, 0.0, 0.0 },
			Vector3D { 0.0, 0.0, 0.0 },
			body.mass + rootBody->mass
		);
		deleteRootBody = true;
	}

	if(rootOctant.isInU(updatedBody.position)) {
		if(rootOctant.isInN(updatedBody.position)) {
			if(rootOctant.isInE(updatedBody.position)) {
				if(upNorthEast == nullptr) {
					upNorthEast = std::make_unique<Bhtree>(rootOctant.centerUpNorthEast());
				}
				upNorthEast->insert(updatedBody);
			} else {
				if(upNorthWest == nullptr) {
					upNorthWest = std::make_unique<Bhtree>(rootOctant.centerUpNorthWest());
				}
				upNorthWest->insert(updatedBody);
			}
		} else {
			if(rootOctant.isInE(updatedBody.position)) {
				if(upSouthEast == nullptr) {
					upSouthEast = std::make_unique<Bhtree>(rootOctant.centerUpSouthEast());
				}
				upSouthEast->insert(updatedBody);
			} else {
				if(upSouthWest == nullptr) {
					upSouthWest = std::make_unique<Bhtree>(rootOctant.centerUpSouthWest());
				}
				upSouthWest->insert(updatedBody);
			}
		}
	} else {
		if(rootOctant.isInN(updatedBody.position)) {
			if(rootOctant.isInE(updatedBody.position)) {
				if(downNorthEast == nullptr) {
					downNorthEast = std::make_unique<Bhtree>(rootOctant.centerDownNorthEast());
				}
				downNorthEast->insert(updatedBody);
			} else {
				if(downNorthWest == nullptr) {
					downNorthWest = std::make_unique<Bhtree>(rootOctant.centerDownNorthWest());
				}
				downNorthWest->insert(updatedBody);
			}
		} else {
			if(rootOctant.isInE(updatedBody.position)) {
				if(downSouthEast == nullptr) {
					downSouthEast = std::make_unique<Bhtree>(rootOctant.centerDownSouthEast());
				}
				downSouthEast->insert(updatedBody);
			} else {
				if(downSouthWest == nullptr) {
					downSouthWest = std::make_unique<Bhtree>(rootOctant.centerDownSouthWest());
				}
				downSouthWest->insert(updatedBody);
			}
		}
	}

	if constexpr (false) {
		if(rootOctant.containsUpNorthWest(updatedBody.position)) {
			if(upNorthWest == nullptr) {
				upNorthWest = std::make_unique<Bhtree>(rootOctant.centerUpNorthWest());
			}
			upNorthWest->insert(updatedBody);
		} else if(rootOctant.containsUpNorthEast(updatedBody.position)) {
			if(upNorthEast == nullptr) {
				upNorthEast = std::make_unique<Bhtree>(rootOctant.centerUpNorthEast());
			}
			upNorthEast->insert(updatedBody);
		} else if(rootOctant.containsUpSouthWest(updatedBody.position)) {
			if(upSouthWest == nullptr) {
				upSouthWest = std::make_unique<Bhtree>(rootOctant.centerUpSouthWest());
			}
			upSouthWest->insert(updatedBody);
		} else if(rootOctant.containsUpSouthEast(updatedBody.position)) {
			if(upSouthEast == nullptr) {
				upSouthEast = std::make_unique<Bhtree>(rootOctant.centerUpSouthEast());
			}
			upSouthEast->insert(updatedBody);
		} else if(rootOctant.containsDownNorthWest(updatedBody.position)) {
			if(downNorthWest == nullptr) {
				downNorthWest = std::make_unique<Bhtree>(rootOctant.centerDownNorthWest());
			}
			downNorthWest->insert(updatedBody);
		} else if(rootOctant.containsDownNorthEast(updatedBody.position)) {
			if(downNorthEast == nullptr) {
				downNorthEast = std::make_unique<Bhtree>(rootOctant.centerDownNorthEast());
			}
			downNorthEast->insert(updatedBody);
		} else if(rootOctant.containsDownSouthWest(updatedBody.position)) {
			if(downSouthWest == nullptr) {
				downSouthWest = std::make_unique<Bhtree>(rootOctant.centerDownSouthWest());
			}
			downSouthWest->insert(updatedBody);
		} else {
			if(downSouthEast == nullptr) {
				downSouthEast = std::make_unique<Bhtree>(rootOctant.centerDownSouthEast());
			}
			downSouthEast->insert(updatedBody);
		}
	}

	if(isTreeExternal) {
		insert(body);
	}
}

void Bhtree::interact(Body* body) {
	if(isExternal()) {
		if(rootBody != body) {
			Body::singleInteraction(*body, *rootBody, true, true, false, true, false);
		}
	} else if(rootOctant.getLength() / (rootBody->position - body->position).magnitude() < MAX_DISTANCE) {
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
