#include "Ragdoll.h"

RagDoll::RagDoll(Physx1* physics) : m_physics(physics)
{
	//InitialiseRagDoll();

	m_physicsMaterial = m_physics->m_Physics->createMaterial(0.5f, 0.5f, .5f);


#pragma region RagdollData
	RagdollNode* ragdollData[] =
	{
		new RagdollNode(PxQuat(PxPi / 2.0f, Z_AXIS), NO_PARENT, 1, 3, 1, 1, "lower spine"),
		new RagdollNode(PxQuat(PxPi, Z_AXIS), LOWER_SPINE, 1, 1, -1, 1, "left pelvis"),
		new RagdollNode(PxQuat(0, Z_AXIS), LOWER_SPINE, 1, 1, -1, 1, "right pelvis"),
		new RagdollNode(PxQuat(PxPi / 2.0f + 0.2f, Z_AXIS), LEFT_PELVIS, 5, 2, -1, 1, "L upper leg"),
		new RagdollNode(PxQuat(PxPi / 2.0f - 0.2f, Z_AXIS), RIGHT_PELVIS, 5, 2, -1, 1, "R upper leg"),
		new RagdollNode(PxQuat(PxPi / 2.0f + 0.2f, Z_AXIS), LEFT_UPPER_LEG, 5, 1.75, -1, 1, "L lower leg"),
		new RagdollNode(PxQuat(PxPi / 2.0f - 0.2f, Z_AXIS), RIGHT_UPPER_LEG, 5, 1.75, -1, 1, "R lowerleg"),
		new RagdollNode(PxQuat(PxPi / 2.0f, Z_AXIS), LOWER_SPINE, 1, 3, 1, -1, "upper spine"),
		new RagdollNode(PxQuat(PxPi, Z_AXIS), UPPER_SPINE, 1, 1.5, 1, 1, "left clavicle"),
		new RagdollNode(PxQuat(0, Z_AXIS), UPPER_SPINE, 1, 1.5, 1, 1, "right clavicle"),
		new RagdollNode(PxQuat(PxPi / 2.0f, Z_AXIS), UPPER_SPINE, 1, 1, 1, -1, "neck"),
		new RagdollNode(PxQuat(PxPi / 2.0f, Z_AXIS), NECK, 1, 3, 1, -1, "HEAD"),
		new RagdollNode(PxQuat(PxPi - .3, Z_AXIS), LEFT_CLAVICLE, 3, 1.5, -1, 1, "left upper arm"),
		new RagdollNode(PxQuat(0.3, Z_AXIS), RIGHT_CLAVICLE, 3, 1.5, -1, 1, "right upper arm"),
		new RagdollNode(PxQuat(PxPi - .3, Z_AXIS), LEFT_UPPER_ARM, 3, 1, -1, 1, "left lower arm"),
		new RagdollNode(PxQuat(0.3, Z_AXIS), RIGHT_UPPER_ARM, 3, 1, -1, 1, "right lower arm"),
		nullptr
	};

#pragma endregion
	PxArticulation* ragdollArticulation;

	ragdollArticulation = makeRagdoll(m_physics->m_Physics, ragdollData, PxTransform(PxVec3(0, 5, 0)), .1f, m_physicsMaterial);

	m_physics->m_PhysicsScene->addArticulation(*ragdollArticulation);
}

RagDoll::~RagDoll()
{

}

void RagDoll::InitialiseRagDoll()
{
	//ragdollData = new RagdollNode[]
	//{
	//	RagdollNode(PxQuat(PxPi / 2.0f, Z_AXIS), NO_PARENT, 1, 3, 1, 1, "lower spine"),
	//	RagdollNode(PxQuat(PxPi, Z_AXIS), LOWER_SPINE, 1, 1, -1, 1, "left pelvis"),
	//	RagdollNode(PxQuat(0, Z_AXIS), LOWER_SPINE, 1, 1, -1, 1, "right pelvis"),
	//	RagdollNode(PxQuat(PxPi / 2.0f + 0.2f, Z_AXIS), LEFT_PELVIS, 5, 2, -1, 1, "L upper leg"),
	//	RagdollNode(PxQuat(PxPi / 2.0f - 0.2f, Z_AXIS), RIGHT_PELVIS, 5, 2, -1, 1, "R upper leg"),
	//	RagdollNode(PxQuat(PxPi / 2.0f + 0.2f, Z_AXIS), LEFT_UPPER_LEG, 5, 1.75, -1, 1, "L lower leg"),
	//	RagdollNode(PxQuat(PxPi / 2.0f - 0.2f, Z_AXIS), RIGHT_UPPER_LEG, 5, 1.75, -1, 1, "R lowerleg"),
	//	RagdollNode(PxQuat(PxPi / 2.0f, Z_AXIS), LOWER_SPINE, 1, 3, 1, -1, "upper spine"),
	//	RagdollNode(PxQuat(PxPi, Z_AXIS), UPPER_SPINE, 1, 1.5, 1, 1, "left clavicle"),
	//	RagdollNode(PxQuat(0, Z_AXIS), UPPER_SPINE, 1, 1.5, 1, 1, "right clavicle"),
	//	RagdollNode(PxQuat(PxPi / 2.0f, Z_AXIS), UPPER_SPINE, 1, 1, 1, -1, "neck"),
	//	RagdollNode(PxQuat(PxPi / 2.0f, Z_AXIS), NECK, 1, 3, 1, -1, "HEAD"),
	//	RagdollNode(PxQuat(PxPi - .3, Z_AXIS), LEFT_CLAVICLE, 3, 1.5, -1, 1, "left upper arm"),
	//	RagdollNode(PxQuat(0.3, Z_AXIS), RIGHT_CLAVICLE, 3, 1.5, -1, 1, "right upper arm"),
	//	RagdollNode(PxQuat(PxPi - .3, Z_AXIS), LEFT_UPPER_ARM, 3, 1, -1, 1, "left lower arm"),
	//	RagdollNode(PxQuat(0.3, Z_AXIS), RIGHT_UPPER_ARM, 3, 1, -1, 1, "right lower arm"),
	//};


}

PxArticulation* RagDoll::makeRagdoll(PxPhysics* m_phyiscs, RagdollNode** nodeArray, PxTransform worldpos, float scaleFactor, PxMaterial* ragdollMaterial)
{
	//create the articulation for our ragdolll
	PxArticulation *articulation = m_phyiscs->createArticulation();
	RagdollNode** currentNode = nodeArray;


	//whiule there are more nodes to process
	//RagdollNode* parentNode = nullptr;

	//get scaled values for capsule
	
	while (*currentNode!=nullptr)
	{
		//get a point to the current node
		RagdollNode* currentNodePtr = *currentNode;
		//create a pointer ready to hold the parent node pointer if there is one
		RagdollNode* parentNode = nullptr;

		//get scaled value for capsule
		float radius = currentNodePtr->radius*scaleFactor;
		float halfLength = currentNodePtr->halfLength*scaleFactor;
		float childHalfLength = radius + halfLength;
		float parentHalfLength = 0; //will be set later if there is a parent
		PxArticulationLink* parentLinkPtr = NULL;
		currentNodePtr->scaleGlobalPos = worldpos.p;

		if (currentNodePtr->parentNodeIdx != NO_PARENT)
		{

			//if there is a parent then we need to work out our local position
			parentNode = *(nodeArray + currentNodePtr->parentNodeIdx);
			//get a point to the link for the parent 
			parentLinkPtr = parentNode->linkPtr;
			parentHalfLength = (parentNode->radius + parentNode->halfLength) *scaleFactor;

			//Work out the local position of the node
			PxVec3 currentRelative = currentNodePtr->childLinkPos * currentNodePtr->globalRotation.rotate(PxVec3(childHalfLength, 0, 0));
			PxVec3 parentRelative = -currentNodePtr->parentLinkPos * parentNode->globalRotation.rotate(PxVec3(parentHalfLength, 0, 0));

			currentNodePtr->scaleGlobalPos = parentNode->scaleGlobalPos - (parentRelative + currentRelative);
		}

		//build the transform for the link
		PxTransform linkTransform = PxTransform(currentNodePtr->scaleGlobalPos, currentNodePtr->globalRotation);

		//Create the link in the articulation
		PxArticulationLink* link = articulation->createLink(parentLinkPtr, linkTransform);

		//add the pointer to this link into the ragdoll data so we have it for later when we want to link to it
		currentNodePtr->linkPtr = link;

		float jointSpace = .01; //gap between joints
		float capsuleHalfLength = (halfLength > jointSpace ? halfLength - jointSpace : 0) + .01f;
		PxCapsuleGeometry capsule(radius, capsuleHalfLength);

		link->createShape(capsule, *ragdollMaterial); //add a capsule collider to the link
		PxRigidBodyExt::updateMassAndInertia(*link, 50.0f); //adds some mass , mass should really be part of the data!  "YOU WOULD THINK! >:O #RAGE"

		if (currentNodePtr->parentNodeIdx != NO_PARENT)
		{

			//Gets the pointer to the joint from the link
			PxArticulationJoint* joint = link->getInboundJoint();

			//Get the relative rotation of this link
			PxQuat frameRotation = parentNode->globalRotation.getConjugate() * currentNodePtr->globalRotation;
			//sets the parent contrainer frame
			PxTransform parentConstraintFrame = PxTransform(PxVec3(currentNodePtr->parentLinkPos * parentHalfLength, 0, 0), frameRotation);

			//sets the child constraint frame (this the constraint frame of the newly added link)
			PxTransform thisConstraintFrame = PxTransform(PxVec3(currentNodePtr->childLinkPos * childHalfLength, 0, 0));


			joint->setParentPose(parentConstraintFrame);
			joint->setChildPose(thisConstraintFrame);
			//set up the poses for the joint so it is in the correct place
			joint->setStiffness(20);
			joint->setDamping(20);
			joint->setSwingLimit(0.4f, 0.4f);
			joint->setSwingLimitEnabled(true);
			joint->setTwistLimit(-0.1f, 0.1f);
			joint->setTwistLimitEnabled(true);

		}
			
		currentNode++;
	}

	//while (*currentNode != NULL)
	//{
	//	//get a point to the current node
	//	RagdollNode* currentNodePtr = *currentNode;
	//	//create a pointer ready to hold the parent node pointer if there is one
	//	RagdollNode* parentNode = nullptr;
	//
	//	//get scaled value for capsule
	//	float radius = currentNodePtr->radius*scaleFactor;
	//
	//	currentNode++;
	//
	//}

	return articulation;


}