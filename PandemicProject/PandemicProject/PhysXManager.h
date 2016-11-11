#pragma once
#include <PhysX\PxPhysicsAPI.h>
using namespace physx;
namespace Physics
{
   class PhysXManager
   {
   public:
      static PhysXManager* Get();
      void Update(float p_dt);

      PxFoundation* m_physxFoundation;
      PxPhysics* m_physics;
      PxScene* m_worldScene;
      PxDefaultCpuDispatcher* m_cpuDispatcher;
   private:
      PhysXManager();
      ~PhysXManager();

      static PhysXManager* m_singleton;



   };

}