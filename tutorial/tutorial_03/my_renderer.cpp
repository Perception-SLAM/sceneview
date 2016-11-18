#include "my_renderer.hpp"

#include <sceneview/sceneview.hpp>

MyRenderer::MyRenderer(const QString &name, QWidget *parent)
    : sv::Renderer(name, parent) {
}

// This method is called once by sv::Viewport when the OpenGL subsystem is
// initialized. Override it to allocate graphics resources required by this
// renderer.
void MyRenderer::InitializeGL() {
  sv::Scene::Ptr scene = GetScene();
  sv::ResourceManager::Ptr resources = GetResources();
  sv::GroupNode* base_node = GetBaseNode();

  // Create a geometry resource from a stock cube.
  sv::StockResources stock(resources);
  sv::GeometryResource::Ptr cube = stock.Cube();

  // Create a material that will be used to control the cube's appearance.
  sv::MaterialResource::Ptr material =
      stock.NewMaterial(sv::StockResources::kUniformColorLighting);
  material->SetParam(sv::kDiffuse, 1.0, 0.5, 0.5, 1.0);

  // Create a draw node from the geometry and material.
  scene->MakeDrawNode(base_node, cube, material);
}
