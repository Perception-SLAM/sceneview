#ifndef SCENEVIEW_EXAMPLES_MODEL_RENDERER_HPP__
#define SCENEVIEW_EXAMPLES_MODEL_RENDERER_HPP__

#include <sceneview/renderer.hpp>
#include <sceneview/group_node.hpp>
#include <sceneview/mesh_node.hpp>
#include <sceneview/material_resource.hpp>
#include <sceneview/param_widget.hpp>

namespace vis_examples {

class ModelRenderer : public sceneview::Renderer {
  Q_OBJECT

 public:
    ModelRenderer(const QString& name, QObject* parent = 0);

    void InitializeGL() override;

    void ShutdownGL() override;

    QWidget* GetWidget() override { return params_.get(); }

    void LoadModel(const QString& filename);

 private slots:
    void ParamChanged(const QString& name);

 private:
    void LoadModelGL();

    void ClearModel();

    sceneview::MaterialResource::Ptr material_;
    std::vector<sceneview::MeshNode*> shapes_;

    std::unique_ptr<sceneview::ParamWidget> params_;
    sceneview::GroupNode* node_;

    bool gl_initialized_;
    QString model_fname_;
};

}  // namespace vis_examples

#endif  // SCENEVIEW_EXAMPLES_MODEL_RENDERER_HPP__
