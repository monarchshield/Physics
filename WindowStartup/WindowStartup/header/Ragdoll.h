#ifndef RAGDOLL_H
#define RAGDOLL_H

//#include <PxPhysicsAPI.h>
//#include <PxScene.h>
//#include <pvd\PxVisualDebugger.h>

//Parts which make up our ragdoll
#include "Physx1.h"


struct RagdollNode
{
	PxQuat globalRotation; //rotation of this link in model space - we could have done this relative to the parent node
	PxVec3 scaleGlobalPos; //Position of the link centre in world space

	int parentNodeIdx; //Index of the parent node
	float halfLength; //half length of the capsule for this node
	float radius; // radius of the capsule
	float parentLinkPos; //relative position of link centre in parent to this node. 0 is the centre of node, -1 is left 1 is the right

	float childLinkPos; //relative position of link centre in child
	char* name; //name of the link

	PxArticulationLink* linkPtr;

	//Constructor
	RagdollNode(PxQuat _globalRotation, int _parentNodeIdx, float _halfLength, float _Radius, float _parentLinkpos,
		float _childLinkPos, char* _name) : 
		globalRotation(_globalRotation),
		scaleGlobalPos(0),
		parentNodeIdx(_parentNodeIdx), 
		halfLength(_halfLength), 
		radius(_Radius), 
		parentLinkPos(_parentLinkpos), 
		childLinkPos(_childLinkPos), name(_name),
		linkPtr(nullptr)
	{}

	
};


class RagDoll
{
public:
	RagDoll(Physx1* physics);
	~RagDoll();

	void InitialiseRagDoll();
	PxArticulation* makeRagdoll(PxPhysics* m_phyiscs, RagdollNode** nodeArray, PxTransform worldpos, float scaleFactor, PxMaterial* ragdollMaterial );

	Physx1* m_physics;


enum RagDollParts
{
	NO_PARENT = -1,
	LOWER_SPINE,
	LEFT_PELVIS,
	RIGHT_PELVIS,
	LEFT_UPPER_LEG,
	RIGHT_UPPER_LEG,
	LEFT_LOWER_LEG,
	RIGHT_LOWER_LEG,
	UPPER_SPINE,
	LEFT_CLAVICLE,
	RIGHT_CLAVICLE,
	NECK,
	HEAD,
	LEFT_UPPER_ARM,
	RIGHT_UPPER_ARM,
	LEFT_LOWER_ARM,
	RIGHT_LOWER_ARM,
	TOTAL = RIGHT_LOWER_ARM + 1
};


private:

RagdollNode* ragdollData;
PxArticulation* articulation;
RagdollNode** currentNode;

PxMaterial* m_physicsMaterial;

const PxVec3 X_AXIS = PxVec3(1,0,0);
const PxVec3 Y_AXIS = PxVec3(0,1,0);
const PxVec3 Z_AXIS = PxVec3(0,0,1);


//PxArticulation* articulation;
//RagdollNode* ragdollData[];
//
//	const PxVec3 X_AXIS;
//	const PxVec3 Y_AXIS;
//	const PxVec3 Z_AXIS;
//
};
#endif
