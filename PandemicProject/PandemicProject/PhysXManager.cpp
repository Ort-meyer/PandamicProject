#include "PhysXManager.h"


namespace Physics
{
   PhysXManager* PhysXManager::m_singleton = nullptr;
   PhysXManager * PhysXManager::Get()
   {
      // Better error handling. This code is just silly as it is
      if (m_singleton == nullptr)
         m_singleton = new PhysXManager();;
      return m_singleton;
   }


   void PhysXManager::Update(float p_dt)
   {
      m_worldScene->simulate(p_dt);
      m_worldScene->fetchResults(true);
   }
   PhysXManager::PhysXManager()
   {
      static PxDefaultErrorCallback gDefaultErrorCallback;
      static PxDefaultAllocator gDefaultAllocatorCallback;
      m_physxFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, gDefaultAllocatorCallback, gDefaultErrorCallback);
      m_physics = PxCreatePhysics(PX_PHYSICS_VERSION, *m_physxFoundation, PxTolerancesScale());
      m_cpuDispatcher = PxDefaultCpuDispatcherCreate(2); // This, I don't remember
                                                         // Create world scene
      PxSceneDesc t_sceneDesc(m_physics->getTolerancesScale());
      //t_sceneDesc.gravity = PxVec3(0, -9.81, 0);
      t_sceneDesc.gravity = PxVec3(0, -2, 0);
      t_sceneDesc.cpuDispatcher = m_cpuDispatcher;
      t_sceneDesc.filterShader = PxDefaultSimulationFilterShader;
      m_worldScene = m_physics->createScene(t_sceneDesc);

      PxMaterial* t_groundMaterial = m_physics->createMaterial(0.5, 0.5, 0.6);
      PxRigidStatic* t_groundPlane = PxCreatePlane(*m_physics, PxPlane(0, 1, 0, 40), *t_groundMaterial);
      m_worldScene->addActor(*t_groundPlane);;
   }


   PhysXManager::~PhysXManager()
   {
   }
}