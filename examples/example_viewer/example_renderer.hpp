#ifndef SCENEVIEW_EXAMPLE_RENDERER_HPP__
#define SCENEVIEW_EXAMPLE_RENDERER_HPP__

#include <QTime>

#include <sceneview/sceneview.hpp>

namespace vis_examples {

class ExampleRenderer : public sceneview::Renderer {
  Q_OBJECT

 public:
    ExampleRenderer(const QString& name, QObject* parent = 0);

    void InitializeGL() override;

    void RenderBegin() override;

    QWidget* GetWidget() override;

    QVariant SaveState() override;

    void LoadState(const QVariant& val) override;

 private slots:
    void ParamChanged(const QString& name);

 private:
    sceneview::MaterialResource::Ptr material_;
    std::vector<sceneview::MeshNode*> shapes_;

    QTime start_time_;
    double angle_;

    std::unique_ptr<sceneview::ParamWidget> widget_;
};

}  // namespace vis_examples

#endif  // SCENEVIEW_EXAMPLE_RENDERER_HPP__
