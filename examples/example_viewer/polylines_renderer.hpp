#ifndef SCENEVIEW_EXAMPLES_POLYLINES_RENDERER_HPP__
#define SCENEVIEW_EXAMPLES_POLYLINES_RENDERER_HPP__

#include <QTime>

#include <sceneview/sceneview.hpp>

namespace vis_examples {

/**
 * Demonstrates building a draw node with custom geometry that gets dynamically
 * updated over time.
 */
class PolylinesRenderer : public sv::Renderer {
  Q_OBJECT

 public:
    PolylinesRenderer(const QString& name, QObject* parent = 0);

    void InitializeGL() override;

    void RenderBegin() override;

 private:
    void UpdateGeometry();

    sv::MaterialResource::Ptr material_;
    sv::GeometryResource::Ptr geom_;
    sv::DrawNode* draw_node_;

    QTime start_time_;
    double angle_;

    std::unique_ptr<sv::ParamWidget> widget_;
    sv::GeometryData gdata_;
};

}  // namespace vis_examples

#endif  // SCENEVIEW_EXAMPLES_POLYLINES_RENDERER_HPP__
