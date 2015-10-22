// Copyright [2015] Albert Huang

#include "sceneview/group_node.hpp"

#include <cassert>
#include <deque>
#include <vector>

#include "sceneview/camera_node.hpp"
#include "sceneview/light_node.hpp"
#include "sceneview/draw_node.hpp"
#include "sceneview/scene.hpp"

namespace sv {

GroupNode::GroupNode(const QString& name) :
  SceneNode(name) {
}

SceneNode* GroupNode::AddChild(SceneNode* child) {
  children_.push_back(child);
  assert(!child->ParentNode());
  child->SetParentNode(this);
  return child;
}

AxisAlignedBox GroupNode::BoundingBox(const QMatrix4x4& lhs_transform) {
  AxisAlignedBox result;
  const QMatrix4x4 transform = lhs_transform * GetTransform();
  for (auto& child : children_) {
    AxisAlignedBox box = child->BoundingBox(transform);
    if (box.Valid()) {
      result.IncludeBox(box);
    }
  }
  return result;
}

void GroupNode::CopyAsChildren(Scene* scene, GroupNode* root) {
  const std::vector<SceneNode*>& tocopy_children = root->Children();
  std::deque<SceneNode*>
    to_process(tocopy_children.begin(), tocopy_children.end());

  SetTranslation(root->Translation());
  SetRotation(root->Rotation());
  SetScale(root->Scale());
  SetVisible(root->Visible());

  while (!to_process.empty()) {
    SceneNode* to_copy = to_process.front();
    to_process.pop_front();
    SceneNode* node_copy = nullptr;

    switch (to_copy->NodeType()) {
      case SceneNodeType::kGroupNode:
        {
          GroupNode* child = scene->MakeGroup(this, Scene::kAutoName);
          GroupNode* group_to_copy =
            dynamic_cast<GroupNode*>(to_copy);
          child->CopyAsChildren(scene, group_to_copy);
          node_copy = child;
        }
        break;
      case SceneNodeType::kCameraNode:
        {
          CameraNode* child = scene->MakeCamera(this, Scene::kAutoName);
          const CameraNode* camera_to_copy =
            dynamic_cast<const CameraNode*>(to_copy);
          child->CopyFrom(*camera_to_copy);
          node_copy = child;
        }
        break;
      case SceneNodeType::kLightNode:
        {
          LightNode* child = scene->MakeLight(this, Scene::kAutoName);
          const LightNode* light_to_copy =
            dynamic_cast<const LightNode*>(to_copy);
//          *child = *light_to_copy;
          (void)light_to_copy;
          node_copy = child;
        }
        break;
      case SceneNodeType::kDrawNode:
        {
          DrawNode* node_to_copy =
            dynamic_cast<DrawNode*>(to_copy);
          DrawNode* child = scene->MakeDrawNode(this, Scene::kAutoName);
          for (const Drawable::Ptr& item : node_to_copy->Drawables()) {
            child->Add(item);
          }
          node_copy = child;
        }
        break;
    }

    node_copy->SetTranslation(to_copy->Translation());
    node_copy->SetRotation(to_copy->Rotation());
    node_copy->SetScale(to_copy->Scale());
    node_copy->SetVisible(to_copy->Visible());
  }
}

void GroupNode::RemoveChild(SceneNode* child) {
  auto iter = std::find(children_.begin(), children_.end(), child);
  if (iter != children_.end()) {
    children_.erase(iter);
  } else {
    throw std::invalid_argument("Not a child of this group node\n");
  }
}

}  // namespace sv
