#pragma once

#include "Pipeline/Geometric/Headers/Node.h"

namespace Application {
namespace Rendering {
  // holds positional information for each bone that the mesh is weighted against
  struct Bone : Geometric::Node
  {
    /*
				Bones will need to hold onto their inverse bind matrix so that we can multiply their LOCAL transfom matrix by it (the multiply this by the model transformation matrix)
				to get the matrix that represents the mesh deformation
			*/

    // this constructor should take in the inverse bind matrix and the local transfromation matrix (the latter to set up it's world/local position)
    // Also, nodes should be able to be set to local or world for their transformations
    // Local nodes should be required to have a parent node to build their final transformation matrix
    Bone(Core::Ptr<State> parentState, Ptr<Node> parentNode, Ptr<Bone> rootBone, std::string name, Core::Math::Float3 position, Core::Math::FQuaternion rotation, Core::Math::Float3 scale);

    // child bones are handled through the Node inheritance

    void Start() override;

    Core::Math::Float4x4 GetBindOffset();

    int GetBoneIndex(std::string name);
    void GetBoneMatrices(std::vector<Core::Math::Float4x4> &boneMatrices, int &offset);

  private:
    Ptr<Bone> RootBone;
    Core::Math::Float4x4 InverseBindMatrix;

    int GetBoneIndex(std::string name, bool &indexFound);
  };
}// namespace Rendering
}// namespace Application
